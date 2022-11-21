/**
 * @file locker.h
 * @author wang.changjie (wang.changjie@embedway.com)
 * @brief 系统程序员成长计划 locker，锁的接口和实现做了分离
 * @version 0.1
 * @date 2022-11-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "../../data_structure/tools.h"

#ifndef LOCKER_H
#define LOCKER_H

DECLS_BEGIN

struct _Locker;
typedef struct _Locker Locker;

typedef Ret (*LockerLockFunc)(Locker *this);
typedef Ret (*LockerUnlockFunc)(Locker *this);
typedef void (*LockerDestroyFunc)(Locker *this);

struct _Locker
{
    LockerLockFunc lock;
    LockerUnlockFunc unlock;
    LockerDestroyFunc destroy;
    // priv 用于存放和锁的具体实现
    char priv[0];
};

static inline Ret locker_lock(Locker *this)
{
    return_val_if_fail(this != NULL && this->lock != NULL, RET_INVALID_PARAMS);

    return this->lock(this);
}

static inline Ret locker_unlock(Locker *this)
{
    return_val_if_fail(this != NULL && this->unlock != NULL,
                       RET_INVALID_PARAMS);

    return this->unlock(this);
}

static inline void locker_destroy(Locker *this)
{
    return_if_fail(this != NULL && this->destroy != NULL);

    this->destroy(this);

    return;
}

DECLS_END

#endif /*LOCKER_H*/