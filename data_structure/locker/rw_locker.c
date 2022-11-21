#include "rw_locker.h"

// 读写锁的状态
typedef enum _RwLockerMode {
    RW_LOCKER_NONE,
    RW_LOCKER_WR,
    RW_LOCKER_RD,
    RW_LOCKER_NR
} RwLockerMode;

struct _RwLocker
{
    int readers;
    RwLockerMode mode;
    Locker *rw_locker;
    // readers 计数器锁
    Locker *rd_locker;
};

RwLocker *rw_locker_create(Locker *rw_locker, Locker *rd_locker)
{
    RwLocker *this = NULL;
    return_val_if_fail(rw_locker != NULL && rd_locker != NULL, NULL);

    this = (RwLocker *)malloc(sizeof(RwLocker));
    if (this != NULL) {
        this->readers   = 0;
        this->mode      = RW_LOCKER_NONE;
        this->rw_locker = rw_locker;
        this->rd_locker = rd_locker;
    }

    return this;
}

Ret rw_locker_wrlock(RwLocker *this)
{
    Ret ret = RET_OK;
    return_val_if_fail(this != NULL, RET_INVALID_PARAMS);

    if ((ret = locker_lock(this->rw_locker)) == RET_OK) {
        this->mode = RW_LOCKER_WR;
    }

    return ret;
}

Ret rw_locker_rdlock(RwLocker *this)
{
    Ret ret = RET_OK;
    return_val_if_fail(this != NULL, RET_INVALID_PARAMS);

    if ((ret = locker_lock(this->rd_locker)) == RET_OK) {
        this->readers++;
        if (this->readers == 1) {
            ret        = locker_lock(this->rw_locker);
            this->mode = RW_LOCKER_RD;
        }
        locker_unlock(this->rd_locker);
    }

    return ret;
}

Ret rw_locker_unlock(RwLocker *this)
{
    Ret ret = RET_OK;
    return_val_if_fail(this != NULL, RET_INVALID_PARAMS);

    if (this->mode == RW_LOCKER_WR) {
        this->mode = RW_LOCKER_NONE;
        ret        = locker_unlock(this->rw_locker);
    } else {
        assert(this->mode == RW_LOCKER_RD);
        if ((ret = locker_lock(this->rd_locker)) == RET_OK) {
            this->readers--;
            if (this->readers == 0) {
                this->mode = RW_LOCKER_NONE;
                ret        = locker_unlock(this->rw_locker);
            }
            locker_unlock(this->rd_locker);
        }
    }

    return ret;
}

void rw_locker_destroy(RwLocker *this)
{
    if (this != NULL) {
        locker_destroy(this->rd_locker);
        locker_destroy(this->rw_locker);
        this->rd_locker = this->rw_locker = NULL;
        SAFE_FREE(this);
    }

    return;
}