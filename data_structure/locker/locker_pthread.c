#include "locker_pthread.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct _PrivInfo
{
    pthread_mutex_t mutex;
} PrivInfo;

static Ret locker_pthread_lock(Locker *thiz)
{
    PrivInfo *priv = (PrivInfo *)thiz->priv;

    int ret = pthread_mutex_lock(&priv->mutex);

    return ret == 0 ? RET_OK : RET_FAIL;
}

static Ret locker_pthread_unlock(Locker *thiz)
{
    PrivInfo *priv = (PrivInfo *)thiz->priv;

    int ret = pthread_mutex_unlock(&priv->mutex);

    return ret == 0 ? RET_OK : RET_FAIL;
}

static void locker_pthread_destroy(Locker *thiz)
{
    PrivInfo *priv = (PrivInfo *)thiz->priv;

    int ret = pthread_mutex_destroy(&priv->mutex);

    SAFE_FREE(thiz);

    return;
}

Locker *locker_pthread_create(void)
{
    Locker *thiz = (Locker *)malloc(sizeof(Locker) + sizeof(PrivInfo));

    if (thiz != NULL) {
        PrivInfo *priv = (PrivInfo *)thiz->priv;

        thiz->lock    = locker_pthread_lock;
        thiz->unlock  = locker_pthread_unlock;
        thiz->destroy = locker_pthread_destroy;

        pthread_mutex_init(&(priv->mutex), NULL);
    }

    return thiz;
}