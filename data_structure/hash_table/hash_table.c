#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

static ht_item HT_DELETED_ITEM = { NULL, NULL };

static int is_prime(const int x)
{
    if (x < 2) {
        return -1;
    }
    if (x < 4) {
        return 1;
    }
    if ((x % 2) == 0) {
        return 0;
    }
    for (size_t i = 3; i <= floor(sqrt((double)x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}

int next_prime(int x)
{
    while (is_prime(x) != 1) {
        x++;
    }
    return x;
}

static ht_item *ht_new_item(const char *k, const char *v)
{
    ht_item *i = malloc(sizeof(ht_item));
    i->key     = strdup(k);
    i->value   = strdup(v);
    return i;
}

static ht_hash_table *ht_new_sized(const int base_size)
{
    ht_hash_table *table = malloc(sizeof(ht_hash_table));
    table->base_size     = base_size;
    table->size          = next_prime(table->base_size);
    table->count         = 0;
    table->items         = calloc((size_t)table->size, sizeof(ht_item *));
    return table;
}

static void ht_resize(ht_hash_table *table, const int base_size)
{
    if (base_size < HT_INIT_SIZE) {
        return;
    }
    ht_hash_table *new_table = ht_new_sized(base_size);
    for (size_t i = 0; i < table->size; i++) {
        ht_item *item = table->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            ht_insert(new_table, item->key, item->value);
        }
    }

    table->base_size = new_table->base_size;
    table->count     = new_table->count;

    // To delete new_table, we give it table's size and items
    const int tmp_size = table->size;
    table->size        = new_table->size;
    new_table->size    = tmp_size;

    ht_item **tmp_items = table->items;
    table->items        = new_table->items;
    new_table->items    = tmp_items;

    ht_del_hash_table(new_table);
}

ht_hash_table *ht_new() { return ht_new_sized(HT_INIT_SIZE); }

static void ht_resize_up(ht_hash_table *table)
{
    const int new_size = table->base_size * 2;
    ht_resize(table, new_size);
}

static void ht_resize_down(ht_hash_table *table)
{
    const int new_size = table->base_size / 2;
    ht_resize(table, new_size);
}

static void ht_del_item(ht_item *item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void ht_del_hash_table(ht_hash_table *table)
{
    for (size_t i = 0; i < table->size; i++) {
        ht_item *item = table->items[i];
        if (NULL != item) ht_del_item(item);
    }
    free(table->items);
    free(table);
}

static int ht_hash(const char *s, const int a, const int m)
{
    long hash       = 0;
    const int len_s = strlen(s);
    for (size_t i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i + 1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}

static int ht_get_hash(const char *s, const int num_buckets, const int attempt)
{
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table *table, const char *key, const char *value)
{
    const int load = table->count * 100 / table->size;
    if (load > 70) {
        ht_resize_up(table);
    }
    ht_item *item = ht_new_item(key, value);
    int index     = ht_get_hash(item->key, table->size, 0);
    ht_item *curr = table->items[index];
    int i         = 0;
    while (NULL != curr) {
        if (curr != &HT_DELETED_ITEM) {
            // update
            if (strcmp(curr->key, key) == 0) {
                ht_del_item(curr);
                table->items[index] = item;
                return;
            }
        }
        index = ht_get_hash(item->key, table->size, i);
        curr  = table->items[index];
        i++;
    }
    table->items[index] = item;
    table->count++;
}

char *ht_search(ht_hash_table *table, const char *key)
{
    int index     = ht_get_hash(key, table->size, 0);
    ht_item *curr = table->items[index];
    int i         = 1;
    while (NULL != curr) {
        if (curr != &HT_DELETED_ITEM) {
            if (strcmp(curr->key, key) == 0) {
                return curr->value;
            }
        }
        int index = ht_get_hash(key, table->size, i);
        curr      = table->items[index];
        i++;
    }
    return NULL;
}

void ht_delete(ht_hash_table *table, const char *key)
{
    const int load = table->count * 100 / table->size;
    if (load < 10) {
        ht_resize_down(table);
    }
    int index     = ht_get_hash(key, table->size, 0);
    ht_item *curr = table->items[index];
    int i         = 1;
    while (NULL != curr) {
        if (curr != &HT_DELETED_ITEM) {
            if (strcmp(curr->key, key) == 0) {
                ht_del_item(curr);
                table->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, table->size, i);
        curr  = table->items[index];
        i++;
    }
    table->count--;
}