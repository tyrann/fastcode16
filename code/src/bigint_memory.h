#ifndef __BIGINT_MEMORY_H_
#define __BIGINT_MEMORY_H_

#include "bigint_constants.h"
#include "bigint_structure.h"

extern block* __bigint_buffer;
extern block* __bigint__precomputation_buffer;
extern BigInt bigint_zero;
extern BigInt bigint_one;
extern BigInt bigint_two;
extern BigInt bigint_three;

void bigint_create_buffer();
void bigint_destroy_buffer();
void bigint_create_precomputation_buffer();
void bigint_destroy_precomputatino_buffer();
BigInt get_precomputed_bigint(unsigned int i);
#define GET_BIGINT_PTR(tag) ((BigInt)(__bigint_buffer + (tag * (BIGINT_SIZE / 8))))
#define MAX_NUMBER_OF_POINTS 576

#endif
