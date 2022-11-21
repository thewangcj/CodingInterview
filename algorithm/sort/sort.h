/**
 * @file sort.h
 * @author wang.changjie (wang.changjie@embedway.com)
 * @brief 系统程序员成长计划排序算法源码：冒泡、快速、归并
 *        代码里有 void * 转成 int 的代码，垃圾代码，这两个字节长度都一样
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SORT_H
#define SORT_H

#include "../../data_structure/tools.h"

Ret bubble_sort(void** array, size_t nr, DataCompareFunc cmp);
Ret quick_sort(void** array, size_t nr, DataCompareFunc cmp);
Ret merge_sort(void** array, size_t nr, DataCompareFunc cmp);

#endif/*SORT_H*/