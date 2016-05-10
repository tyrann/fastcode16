#ifndef __BIGINT_MEMORY_H_
#define __BIGINT_MEMORY_H_

#include "bigint_constants.h"
#include "bigint_structure.h"

extern uchar* __bigint_buffer;
extern BigInt bigint_zero;
extern BigInt bigint_one;

void bigint_create_buffer();
void bigint_destroy_buffer();
#define GET_BIGINT_PTR(tag) ((BigInt)(__bigint_buffer + (tag * BIGINT_SIZE)))

#endif