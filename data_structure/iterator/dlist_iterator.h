#ifndef DLIST_ITERATOR_H
#define DLIST_ITERATOR_H

#include "../dlist/d_list.h"
#include "iterator.h"

DECLS_BEGIN

Iterator *dlist_iterator_create(d_list *dlist);

DECLS_END

#endif /*DLIST_ITERATOR_H*/