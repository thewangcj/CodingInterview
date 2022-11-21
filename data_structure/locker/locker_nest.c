#include "locker_nest.h"

typedef struct _PrivInfo
{
	int owner;
	int refcount;
	Locker* real_locker;
	TaskSelfFunc task_self;
}PrivInfo;

static Ret  locker_nest_lock(Locker* this)
{
	Ret ret = RET_OK;
	PrivInfo* priv = (PrivInfo*)this->priv;

	if(priv->owner == priv->task_self())
	{
		priv->refcount++;
	}
	else
	{
		if( (ret = locker_lock(priv->real_locker)) == RET_OK)
		{
			priv->refcount = 1;
			priv->owner = priv->task_self();
		}
	}

	return ret;
}

static Ret  locker_nest_unlock(Locker* this)
{
	Ret ret = RET_OK;
	PrivInfo* priv = (PrivInfo*)this->priv;

	return_val_if_fail(priv->owner == priv->task_self(), RET_FAIL);
	
	priv->refcount--;
	if(priv->refcount == 0)
	{
		priv->owner = 0;
		ret = locker_unlock(priv->real_locker);
	}

	return ret;
}

static void  locker_nest_destroy(Locker* this)
{
	PrivInfo* priv = (PrivInfo*)this->priv;

	priv->owner = 0;
	priv->refcount = 0;
	locker_destroy(priv->real_locker);
	priv->real_locker = NULL;

	SAFE_FREE(this);

	return;
}

Locker* locker_nest_create(Locker* real_locker, TaskSelfFunc task_self)
{
	Locker* this = NULL;
	return_val_if_fail(real_locker != NULL && task_self != NULL, NULL);
	
	this = (Locker*)malloc(sizeof(Locker) + sizeof(PrivInfo));

	if(this != NULL)
	{
		PrivInfo* priv = (PrivInfo*)this->priv;

		this->lock    = locker_nest_lock;
		this->unlock  = locker_nest_unlock;
		this->destroy = locker_nest_destroy;

		priv->owner = 0;
		priv->refcount = 0;
		priv->real_locker = real_locker;
		priv->task_self = task_self;
	}

	return this;
}

