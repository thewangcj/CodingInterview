/**
 * @file rw_locker.h
 * @author wang.changjie (wang.changjie@embedway.com)
 * @brief 读写锁
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "locker.h"

#ifndef RW_LOCKR_H
#define RW_LOCKER_H

struct _RwLocker;
typedef struct _RwLocker RwLocker;

RwLocker* rw_locker_create(Locker* rw_locker, Locker* rd_locker);

Ret rw_locker_wrlock(RwLocker* this);
Ret rw_locker_rdlock(RwLocker* this);
Ret rw_locker_unlock(RwLocker* this);

void rw_locker_destroy(RwLocker* this);

#endif/*RW_LOCKER_H*/