//
// Created by wang.changjie on 2021/7/16.
//

#ifndef CODINGINTERVIEW_D_LIST_H
#define CODINGINTERVIEW_D_LIST_H
#include "../tools.h"
#include <stddef.h>

DECLS_BEGIN

typedef enum D_LIST_RET_T {
    DLIST_RET_OK,
    DLIST_RET_OOM,
    DLIST_RET_STOP,
    DLIST_RET_INVALID_PARAMS,
    DLIST_RET_FAIL
} D_LIST_RET;

typedef D_LIST_RET (*d_list_data_print_fun)(void *data);
typedef D_LIST_RET (*d_list_data_visit_fun)(void *ctx, void *data);
typedef void (*data_destroy_func)(void *ctx, void *data);
typedef int (*data_cmp_fun)(void *ctx, void *data);

struct d_list_node_t
{
    struct d_list_node_t *prev;
    struct d_list_node_t *next;
    void *data;
};
typedef struct d_list_node_t d_list_node;

struct d_list_t
{
    d_list_node *first;
    void *data_destroy_ctx;
    data_destroy_func data_destroy;
};
typedef struct d_list_t d_list;

d_list *dlist_create(data_destroy_func, void *);
void dlist_destroy(d_list *thiz);

D_LIST_RET dlist_insert(d_list *thiz, size_t index, void *data);
D_LIST_RET dlist_prepend(d_list *thiz, void *data);
D_LIST_RET dlist_append(d_list *thiz, void *data);
D_LIST_RET dlist_delete(d_list *thiz, size_t index);
D_LIST_RET dlist_get_by_index(d_list *thiz, size_t index, void **data);
D_LIST_RET dlist_set_by_index(d_list *thiz, size_t index, void *data);
size_t dlist_length(d_list *thiz);
int dlist_find(d_list *thiz, data_cmp_fun cmp, void *ctx);
D_LIST_RET dlist_print(d_list *thiz, d_list_data_print_fun print);
D_LIST_RET dlist_foreach(d_list *thiz, d_list_data_visit_fun visit, void *ctx);

DECLS_END

#endif // CODINGINTERVIEW_D_LIST_H
