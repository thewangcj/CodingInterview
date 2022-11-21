#include "locker_pthread.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct _PrivInfo
{
    pthread_mutex_t mutex;
} PrivInfo;

static Ret locker_pthread_lock(Locker *this)
{
    PrivInfo *priv = (PrivInfo *)this->priv;

    int ret = pthread_mutex_lock(&priv->mutex);

    return ret == 0 ? RET_OK : RET_FAIL;
}

static Ret locker_pthread_unlock(Locker *this)
{
    PrivInfo *priv = (PrivInfo *)this->priv;

    int ret = pthread_mutex_unlock(&priv->mutex);

    return ret == 0 ? RET_OK : RET_FAIL;
}

static void locker_pthread_destroy(Locker *this)
{
    PrivInfo *priv = (PrivInfo *)this->priv;

    int ret = pthread_mutex_destroy(&priv->mutex);

    SAFE_FREE(this);

    return;
}

Locker *locker_pthread_create(void)
{
    Locker *this = (Locker *)malloc(sizeof(Locker) + sizeof(PrivInfo));

    if (this != NULL) {
        PrivInfo *priv = (PrivInfo *)this->priv;

        this->lock    = locker_pthread_lock;
        this->unlock  = locker_pthread_unlock;
        this->destroy = locker_pthread_destroy;

        pthread_mutex_init(&(priv->mutex), NULL);
    }

    return this;
}