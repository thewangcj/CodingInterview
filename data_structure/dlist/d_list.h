//
// Created by wang.changjie on 2021/7/16.
//

#ifndef CODINGINTERVIEW_D_LIST_H
#define CODINGINTERVIEW_D_LIST_H
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif /*__cplusplus*/

    typedef enum D_LIST_RET_T
    {
        DLIST_RET_OK,
        DLIST_RET_OOM,
        DLIST_RET_STOP,
        DLIST_RET_INVALID_PARAMS,
        DLIST_RET_FAIL
    } D_LIST_RET;

    struct d_list_t;
    typedef struct d_list_t d_list;

    typedef D_LIST_RET (*d_list_data_print_fun)(void *data);
    typedef D_LIST_RET (*d_list_data_visit_fun)(void *ctx, void *data);
    typedef void (*data_destroy_func)(void *ctx, void *data);
    typedef int (*data_cmp_fun)(void *ctx, void *data);

    d_list *dlist_create(data_destroy_func, void *);
    void dlist_destroy(d_list *this);

    D_LIST_RET dlist_insert(d_list *this, size_t index, void *data);
    D_LIST_RET dlist_prepend(d_list *this, void *data);
    D_LIST_RET dlist_append(d_list *this, void *data);
    D_LIST_RET dlist_delete(d_list *this, size_t index);
    D_LIST_RET dlist_get_by_index(d_list *this, size_t index, void **data);
    D_LIST_RET dlist_set_by_index(d_list *this, size_t index, void *data);
    size_t dlist_length(d_list *this);
    int dlist_find(d_list* this, data_cmp_fun cmp, void* ctx);
    D_LIST_RET dlist_print(d_list *this, d_list_data_print_fun print);
    D_LIST_RET dlist_foreach(d_list *this, d_list_data_visit_fun visit, void *ctx);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif //CODINGINTERVIEW_D_LIST_H
