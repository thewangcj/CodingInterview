#ifndef LINEAR_CONTAINER_DLIST_H
#define LINEAR_CONTAINER_DLIST_H

#include "linear_container.h"

DECLS_BEGIN

LinearContainer* linear_container_dlist_create(DataDestroyFunc data_destroy, void* ctx);

DECLS_END

#endif/*LINEAR_CONTAINER_DLIST_H*/