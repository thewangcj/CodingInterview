/**
 * @file d_array.h
 * @author wang.changjie (wang.changjie@embedway.com)
 * @brief 系统程序员成长计划动态数组源码
 *        修改了一些命名和编译问题
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../tools.h"
#include <stdio.h>

#ifndef DARRAY_H
#define DARRAY_H

DECLS_BEGIN

struct _d_array;
typedef struct _d_array d_array;

d_array *darray_create(DataDestroyFunc data_destroy, void *ctx);

Ret darray_insert(d_array *thiz, size_t index, void *data);
Ret darray_prepend(d_array *thiz, void *data);
Ret darray_append(d_array *thiz, void *data);
Ret darray_delete(d_array *thiz, size_t index);
Ret darray_get_by_index(d_array *thiz, size_t index, void **data);
Ret darray_set_by_index(d_array *thiz, size_t index, void *data);
size_t darray_length(d_array *thiz);
int darray_find(d_array *thiz, DataCompareFunc cmp, void *ctx);
Ret darray_foreach(d_array *thiz, DataVisitFunc visit, void *ctx);

void darray_destroy(d_array *thiz);

DECLS_END

#endif /*DARRAY_H*/