#ifndef LINEAR_CONTAINER_H
#define LINEAR_CONTAINER_H

#include "../tools.h"

DECLS_BEGIN

struct _LinearContainer;
typedef struct _LinearContainer LinearContainer;

typedef Ret (*LinearContainerInsert)(LinearContainer *this, size_t index,
                                     void *data);
typedef Ret (*LinearContainerPrepend)(LinearContainer *this, void *data);
typedef Ret (*LinearContainerAppend)(LinearContainer *this, void *data);
typedef Ret (*LinearContainerDelete)(LinearContainer *this, size_t index);
typedef Ret (*LinearContainerGetByIndex)(LinearContainer *this, size_t index,
                                         void **data);
typedef Ret (*LinearContainerSetByIndex)(LinearContainer *this, size_t index,
                                         void *data);
typedef size_t (*LinearContainerLength)(LinearContainer *this);
typedef int (*LinearContainerFind)(LinearContainer *this, DataCompareFunc cmp,
                                   void *ctx);
typedef Ret (*LinearContainerForeach)(LinearContainer *this,
                                      DataVisitFunc visit, void *ctx);
typedef void (*LinearContainerDestroy)(LinearContainer *this);

struct _LinearContainer
{
    LinearContainerInsert insert;
    LinearContainerPrepend prepend;
    LinearContainerAppend append;
    LinearContainerDelete del;
    LinearContainerGetByIndex get_by_index;
    LinearContainerSetByIndex set_by_index;
    LinearContainerLength length;
    LinearContainerFind find;
    LinearContainerForeach foreach;
    LinearContainerDestroy destroy;

    char priv[0];
};

static inline Ret linear_container_insert(LinearContainer *this, size_t index,
                                          void *data)
{
    return_val_if_fail(this != NULL && this->insert != NULL,
                       RET_INVALID_PARAMS);

    return this->insert(this, index, data);
}

static inline Ret linear_container_prepend(LinearContainer *this, void *data)
{
    return_val_if_fail(this != NULL && this->prepend != NULL,
                       RET_INVALID_PARAMS);

    return this->prepend(this, data);
}

static inline Ret linear_container_append(LinearContainer *this, void *data)
{
    return_val_if_fail(this != NULL && this->append != NULL,
                       RET_INVALID_PARAMS);

    return this->append(this, data);
}

static inline Ret linear_container_delete(LinearContainer *this, size_t index)
{
    return_val_if_fail(this != NULL && this->del != NULL, RET_INVALID_PARAMS);

    return this->del(this, index);
}

static inline Ret linear_container_get_by_index(LinearContainer *this,
                                                size_t index, void **data)
{
    return_val_if_fail(this != NULL && this->get_by_index != NULL,
                       RET_INVALID_PARAMS);

    return this->get_by_index(this, index, data);
}

static inline Ret linear_container_set_by_index(LinearContainer *this,
                                                size_t index, void *data)
{
    return_val_if_fail(this != NULL && this->set_by_index != NULL,
                       RET_INVALID_PARAMS);

    return this->set_by_index(this, index, data);
}

static inline size_t linear_container_length(LinearContainer *this)
{
    return_val_if_fail(this != NULL && this->length != NULL, 0);

    return this->length(this);
}

static inline int linear_container_find(LinearContainer *this,
                                        DataCompareFunc cmp, void *ctx)
{
    return_val_if_fail(this != NULL && this->find != NULL, -1);

    return this->find(this, cmp, ctx);
}

static inline Ret linear_container_foreach(LinearContainer *this,
                                           DataVisitFunc visit, void *ctx)
{
    return_val_if_fail(this != NULL && this->foreach != NULL,
                       RET_INVALID_PARAMS);

    return this->foreach (this, visit, ctx);
}

static inline void linear_container_destroy(LinearContainer *this)
{
    return_if_fail(this != NULL && this->destroy != NULL);

    return this->destroy(this);
}

DECLS_END

#endif /*LINEAR_CONTAINER_H*/