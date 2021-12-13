#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__
// 根据 https://github.com/jamesroutley/write-a-hash-table 使用开放地址法实现的 hash 表

#define HT_INIT_SIZE 53
#define HT_PRIME_1   7
#define HT_PRIME_2   13

typedef struct
{
    char *key;
    char *value;
} ht_item;

typedef struct
{
    int size;
    int count;
    int base_size;
    ht_item **items;
} ht_hash_table;

ht_hash_table *ht_new();
void ht_del_hash_table(ht_hash_table *table);
void ht_insert(ht_hash_table *ht, const char *key, const char *value);
char *ht_search(ht_hash_table *ht, const char *key);
void ht_delete(ht_hash_table *h, const char *key);
#endif