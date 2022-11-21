#include "d_list.h"
#include "../tools.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct d_list_node_t
{
    struct d_list_node_t *prev;
    struct d_list_node_t *next;
    void *data;
} d_list_node;

struct d_list_t
{
    d_list_node *first;
    void *data_destroy_ctx;
    data_destroy_func data_destroy;
};
typedef struct d_list_t d_list;

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

static void dlist_destroy_data(d_list *this, void *data)
{
    if (this->data_destroy != NULL) {
        this->data_destroy(this->data_destroy_ctx, data);
    }
}

static void dlist_node_destroy(d_list *this, d_list_node *node)
{
    if (node != NULL) {
        node->next = NULL;
        node->prev = NULL;
        dlist_destroy_data(this, node->data);
        free(node);
    }

    return;
}

void dlist_destroy(d_list *this)
{
    d_list_node *iter = this->first;
    d_list_node *next = NULL;

    while (iter != NULL) {
        next = iter->next;
        dlist_node_destroy(this, iter);
        iter = next;
    }
    this->first = NULL;
    free(this);
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
/// \param this 链表
/// \param index 索引
/// \param fail_return_last 决定当 index 超出链表长度时是返回最后一个还是 NULL
/// \return
static d_list_node *dlist_get_node(d_list *this, size_t index,
                                   int fail_return_last)
{
    d_list_node *iter = this->first;

    while (iter != NULL && iter->next != NULL && index > 0) {
        iter = iter->next;
        index--;
    }

    if (!fail_return_last) {
        iter = index > 0 ? NULL : iter;
    }

    return iter;
}

D_LIST_RET dlist_insert(d_list *this, size_t index, void *data)
{
    return_val_if_fail((this != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *cursor = NULL;
    d_list_node *node   = NULL;

    if ((node = dlist_node_create(data)) == NULL) {
        return DLIST_RET_OOM;
    }

    // 链表为空，还没有元素
    if (this->first == NULL) {
        this->first = node;
        return DLIST_RET_OK;
    }

    cursor = dlist_get_node(this, index, 1);

    if (index < dlist_length(this)) {
        if (this->first == cursor) {
            this->first = node;
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

D_LIST_RET dlist_prepend(d_list *this, void *data)
{
    return dlist_insert(this, 0, data);
}

D_LIST_RET dlist_append(d_list *this, void *data)
{
    return dlist_insert(this, -1, data);
}

D_LIST_RET dlist_delete(d_list *this, size_t index)
{
    return_val_if_fail((this != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *cursor = dlist_get_node(this, index, 0);

    if (cursor != NULL) {
        if (cursor == this->first) {
            this->first = cursor->next;
        }

        if (cursor->next != NULL) {
            cursor->next->prev = cursor->prev;
        }

        if (cursor->prev != NULL) {
            cursor->prev->next = cursor->next;
        }

        dlist_node_destroy(this, cursor);
    }

    return DLIST_RET_OK;
}

D_LIST_RET dlist_get_by_index(d_list *this, size_t index, void **data)
{
    return_val_if_fail((this != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *cursor = dlist_get_node(this, index, 0);
    if (cursor != NULL) {
        *data = cursor->data;
        return DLIST_RET_OK;
    }
    return DLIST_RET_FAIL;
    ;
}

D_LIST_RET dlist_set_by_index(d_list *this, size_t index, void *data)
{
    return_val_if_fail((this != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *cursor = dlist_get_node(this, index, 0);
    if (cursor != NULL) {
        cursor->data = data;
        return DLIST_RET_OK;
    }
    return DLIST_RET_FAIL;
    ;
}

/// 返回链表的长度
/// \param this
/// \return
size_t dlist_length(d_list *this)
{
    if (this == NULL) return 0;
    size_t len        = 0;
    d_list_node *iter = this->first;
    while (iter != NULL) {
        len++;
        iter = iter->next;
    }
    return len;
}

int dlist_find(d_list *this, data_cmp_fun cmp, void *ctx)
{
    return_val_if_fail((this != NULL), DLIST_RET_INVALID_PARAMS);
    int i             = 0;
    d_list_node *iter = NULL;

    iter = this->first;
    while (iter != NULL) {
        if (cmp(ctx, iter->data) == 0) {
            break;
        }
        i++;
        iter = iter->next;
    }

    return i;
}

D_LIST_RET dlist_print(d_list *this, d_list_data_print_fun print)
{
    d_list_node *iter = this->first;

    while (iter != NULL) {
        print(iter->data);

        iter = iter->next;
    }

    return DLIST_RET_OK;
}

D_LIST_RET dlist_foreach(d_list *this, d_list_data_visit_fun visit, void *ctx)
{
    return_val_if_fail((this != NULL), DLIST_RET_INVALID_PARAMS);
    d_list_node *iter = this->first;
    D_LIST_RET ret    = DLIST_RET_OK;
    while (iter != NULL && ret == DLIST_RET_OK) {
        ret  = visit(ctx, iter->data);
        iter = iter->next;
    }

    return ret;
}