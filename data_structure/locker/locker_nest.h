/**
 * @file locker_nest.h
 * @author wang.changjie (wang.changjie@embedway.com)
 * @brief 可重入锁，通过计数器实现，将 locker 包装了一层，装饰器模式
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "locker.h"

#ifndef LOCKER_NEST_H
#define LOCKER_NEST_H

DECLS_BEGIN

// 返回线程ID
typedef int (*TaskSelfFunc)(void);
Locker* locker_nest_create(Locker* real_locker, TaskSelfFunc task_self);

DECLS_END

#endif/*LOCKER_NEST_H*/