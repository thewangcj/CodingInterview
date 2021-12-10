#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "hash_table.h"

static ht_item *ht_new_item(const char *k, const char *v)
{
    ht_item *i = malloc(sizeof(ht_item));
    i->key     = strdup(k);
    i->value   = strdup(v);
    return i;
}

ht_hash_table *ht_new()
{
    ht_hash_table *ht = malloc(sizeof(ht_hash_table));
    ht->count         = 0;
    ht->size          = HT_INIT_SIZE;
    ht->items         = calloc((size_t)ht->size, sizeof(ht_item *));
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