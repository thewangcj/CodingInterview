#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#define HT_INIT_SIZE 53

typedef struct
{
    char *key;
    char *value;
} ht_item;

typedef struct
{
    int size;
    int count;
    ht_item **items;
} ht_hash_table;

ht_hash_table *ht_new();
void ht_del_hash_table(ht_hash_table *table);

#endif