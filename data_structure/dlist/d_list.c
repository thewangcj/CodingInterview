#include "d_list.h"
#include "../tools.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct d_list_node_t
{
    struct d_list_node_t *prev;
    struct d_list_node_t *next;
    void *data;
};

struct d_list_t
{
    d_list_node *first;
    void *data_destroy_ctx;
    data_destroy_func data_destroy;
};

/*
 * 创建一个双向链表
 */
d_list *dlist_create(data_destroy_func data_destroy, void *ctx)
{
    d_list *list = malloc(sizeof(d_list));
    if (list != NULL) {
        list->first            = NULL;
        list->data_destroy     = data_destroy;
        list->data_destroy_ctx = ctx;
    }
    return list;
}

static void dlist_destroy_data(d_list *thiz, void *data)
{
    if (thiz->data_destroy != NULL) {
        thiz->data_destroy(thiz->data_destroy_ctx, data);
    }
}

static void dlist_node_destroy(d_list *thiz, d_list_node *node)
{
    if (node != NULL) {
        node->next = NULL;
        node->prev = NULL;
        dlist_destroy_data(thiz, node->data);
        free(node);
    }

    return;
}

void dlist_destroy(d_list *thiz)
{
    d_list_node *iter = thiz->first;
    d_list_node *next = NULL;

    while (iter != NULL) {
        next = iter->next;
        dlist_node_destroy(thiz, iter);
        iter = next;
    }
    thiz->first = NULL;
    free(thiz);
    return;
}

///
/// \param data
/// \return
static d_list_node *dlist_node_create(void *data)
{
    d_list_node *node = malloc(sizeof(d_list_node));
    if (node != NULL) {
        node->prev = NULL;
        node->next = NULL;
        node->data = data;
    }
    return node;
}

/// 获取 index (0开始)位置的结点
/// \param thiz 链表
/// \param index 索引
/// \param fail_return_last 决定当 index 超出链表长度时是返回最后一个还是 NULL
/// \return
static d_list_node *dlist_get_node(d_list *thiz, size_t index,
                                   int fail_return_last)
{
    d_list_node *iter = thiz->first;

    while (iter != NULL && iter->next != NULL && index > 0) {
        iter = iter->next;
        index--;
    }

    if (!fail_return_last) {
        iter = index > 0 ? NULL : iter;
    }

    return iter;
}

D_LIST_RET dlist_insert(d_list *thiz, size_t index, void *data)
{
    return_val_if_fail((thiz != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *cursor = NULL;
    d_list_node *node   = NULL;

    if ((node = dlist_node_create(data)) == NULL) {
        return DLIST_RET_OOM;
    }

    // 链表为空，还没有元素
    if (thiz->first == NULL) {
        thiz->first = node;
        return DLIST_RET_OK;
    }

    cursor = dlist_get_node(thiz, index, 1);

    if (index < dlist_length(thiz)) {
        if (thiz->first == cursor) {
            thiz->first = node;
        } else {
            cursor->prev->next = node;
            node->prev         = cursor->prev;
        }
        node->next   = cursor;
        cursor->prev = node;
    } else {
        // index 超出了 length，从尾部插入
        cursor->next = node;
        node->prev   = cursor;
    }
    return DLIST_RET_OK;
}

D_LIST_RET dlist_prepend(d_list *thiz, void *data)
{
    return dlist_insert(thiz, 0, data);
}

D_LIST_RET dlist_append(d_list *thiz, void *data)
{
    return dlist_insert(thiz, -1, data);
}

D_LIST_RET dlist_delete(d_list *thiz, size_t index)
{
    return_val_if_fail((thiz != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *cursor = dlist_get_node(thiz, index, 0);

    if (cursor != NULL) {
        if (cursor == thiz->first) {
            thiz->first = cursor->next;
        }

        if (cursor->next != NULL) {
            cursor->next->prev = cursor->prev;
        }

        if (cursor->prev != NULL) {
            cursor->prev->next = cursor->next;
        }

        dlist_node_destroy(thiz, cursor);
    }

    return DLIST_RET_OK;
}

D_LIST_RET dlist_get_by_index(d_list *thiz, size_t index, void **data)
{
    return_val_if_fail((thiz != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *cursor = dlist_get_node(thiz, index, 0);
    if (cursor != NULL) {
        *data = cursor->data;
        return DLIST_RET_OK;
    }
    return DLIST_RET_FAIL;
    ;
}

D_LIST_RET dlist_set_by_index(d_list *thiz, size_t index, void *data)
{
    return_val_if_fail((thiz != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *cursor = dlist_get_node(thiz, index, 0);
    if (cursor != NULL) {
        cursor->data = data;
        return DLIST_RET_OK;
    }
    return DLIST_RET_FAIL;
    ;
}

/// 返回链表的长度
/// \param thiz
/// \return
size_t dlist_length(d_list *thiz)
{
    if (thiz == NULL) return 0;
    size_t len        = 0;
    d_list_node *iter = thiz->first;
    while (iter != NULL) {
        len++;
        iter = iter->next;
    }
    return len;
}

int dlist_find(d_list *thiz, data_cmp_fun cmp, void *ctx)
{
    return_val_if_fail((thiz != NULL), DLIST_RET_INVALID_PARAMS);
    int i             = 0;
    d_list_node *iter = NULL;

    iter = thiz->first;
    while (iter != NULL) {
        if (cmp(ctx, iter->data) == 0) {
            break;
        }
        i++;
        iter = iter->next;
    }

    return i;
}

D_LIST_RET dlist_print(d_list *thiz, d_list_data_print_fun print)
{
    d_list_node *iter = thiz->first;

    while (iter != NULL) {
        print(iter->data);

        iter = iter->next;
    }

    return DLIST_RET_OK;
}

D_LIST_RET dlist_foreach(d_list *thiz, d_list_data_visit_fun visit, void *ctx)
{
    return_val_if_fail((thiz != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *iter = thiz->first;
    D_LIST_RET ret    = DLIST_RET_OK;
    while (iter != NULL && ret == DLIST_RET_OK) {
        ret  = visit(ctx, iter->data);
        iter = iter->next;
    }

    return ret;
}