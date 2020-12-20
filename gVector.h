gVector.h & gVector.c


#ifndef GVECTOR_H
#define GVECTOR_H
#include "generic.h"
#include "status.h"

typedef void *GVECTOR;

GVECTOR generic_vector_init_default(Status (*item_assignment)(Item*, Item),void (*item_destroy)(Item*));

void generic_vector_destroy(GVECTOR *phVector);

int generic_vector_get_capacity(GVECTOR hVector);

int generic_vector_get_size(GVECTOR hVector);

Status generic_vector_push_back(GVECTOR hVector, Item item);

Status generic_vector_pop_back(GVECTOR hVector);

Item generic_vector_at(GVECTOR hVector, unsigned int index);

Boolean generic_vector_empty(GVECTOR hVector);

#endif
