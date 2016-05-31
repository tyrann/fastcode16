#include <stdlib.h>
#include <string.h>

#include "logging/logging.h"
#include "opcount/opcount.h"
#include "bigint_operations.h"
#include "bigint_structure.h"
#include "bigint_conversion.h"
#include "bigint_utilities.h"
#include <stdint.h>

#include <x86intrin.h>
#include <immintrin.h>
#include <inttypes.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef unsigned long long int uint64;

#define BIGINT_MUL_ADD_RSHIFT_INPLACE_X2_BODY(mul_size) \
{\
	unsigned char add_carry_m1 = 0, add_carry_1 = 0; \
	unsigned char add_carry_m2 = 0, add_carry_2 = 0; \
	uint64 low_m1, hi_m1, carry_m1, temp_m1; \
	uint64 low_m2, hi_m2, carry_m2, temp_m2, unused; \
 	\
	BigInt tmp = GET_BIGINT_PTR(BI_MONTGOMERYMUL_TMP1_TAG); \
 	\
	if (b != 0 && d != 0) \
	{ \
		/* Block 0 */ \
		low_m1 = _mulx_u64(a->blocks[0], b, &carry_m1); \
		add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[0], low_m1, (uint64*)&tmp->blocks[0]); \
		 \
		/* Blocks 1 : mul_size-1 */ \
		for (unsigned int i = 1; i < mul_size; i++) { \
			__COUNT_INDEX(&global_index_count, 1); \
			__COUNT_OP(&global_opcount, 6); \
 			\
			low_m1 = _mulx_u64(a->blocks[i], b, &hi_m1); \
			add_carry_m1 = _addcarryx_u64(add_carry_m1, carry_m1, low_m1, &temp_m1); \
			add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[i], temp_m1, (uint64*)&tmp->blocks[i]); \
			carry_m1 = hi_m1; \
		} \
		 \
		_addcarryx_u64(add_carry_m1, carry_m1, 0, &temp_m1); \
		add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[mul_size], temp_m1, (uint64*)&tmp->blocks[mul_size]); \
		 \
		low_m2 = _mulx_u64(c->blocks[0], d, &carry_m2); \
		add_carry_2 = _addcarryx_u64(add_carry_2, tmp->blocks[0], low_m2, &unused); \
		 \
		for (unsigned int i = 1; i < mul_size; i++) { \
			low_m2 = _mulx_u64(c->blocks[i], d, &hi_m2); \
			add_carry_m2 = _addcarryx_u64(add_carry_m2, carry_m2, low_m2, &temp_m2); \
			add_carry_2 = _addcarryx_u64(add_carry_2, tmp->blocks[i], temp_m2, (uint64*)&(res->blocks)[i-1]); \
			carry_m2 = hi_m2; \
		} \
 		\
		/* Block mul_size */ \
		_addcarryx_u64(add_carry_m2, carry_m2, 0, &temp_m2); \
		add_carry_2 = _addcarryx_u64(add_carry_2, tmp->blocks[mul_size], temp_m2, (uint64*)&(res->blocks)[mul_size-1]); \
 		\
		/* Block mul_size + 1 */ \
		res->blocks[mul_size] = res->blocks[mul_size+1] + (uint64_t)add_carry_1 + (uint64_t)add_carry_2; \
		res->blocks[mul_size + 1] = 0; \
		 \
		__COUNT_OP(&global_opcount, 10); \
	} \
	else if (b != 0) \
	{ \
		/* Block 0 */ \
		low_m1 = _mulx_u64(a->blocks[0], b, &carry_m1); \
		add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[0], low_m1, &unused); \
 		\
		/* Blocks 1 : mul_size-1 */\
		for (unsigned int i = 1; i < mul_size; i++) { \
			__COUNT_INDEX(&global_index_count, 1); \
			__COUNT_OP(&global_opcount, 3); \
 			\
			low_m1 = _mulx_u64(a->blocks[i], b, &hi_m1); \
			add_carry_m1 = _addcarryx_u64(add_carry_m1, carry_m1, low_m1, &temp_m1); \
			add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[i], temp_m1, (uint64*)&(res->blocks)[i-1]); \
			carry_m1 = hi_m1; \
		} \
 		\
		/* Block mul_size */\
		_addcarryx_u64(add_carry_m1, carry_m1, 0, &temp_m1); \
		add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[mul_size], temp_m1, (uint64*)&(res->blocks)[mul_size-1]); \
 		\
		/* Block mul_size + 1 */\
		res->blocks[mul_size] += (uint64_t)add_carry_1; \
		 \
		__COUNT_OP(&global_opcount, 5); \
	} \
	else if (d != 0) \
	{ \
		/* Block 0 */\
		low_m2 = _mulx_u64(c->blocks[0], d, &carry_m2); \
		add_carry_2 = _addcarryx_u64(add_carry_2, res->blocks[0], low_m2, &unused); \
 		\
		/* Blocks 1 : mul_size-1 */\
		for (unsigned int i = 1; i < mul_size; i++) { \
			__COUNT_INDEX(&global_index_count, 1); \
			__COUNT_OP(&global_opcount, 3); \
 			\
			low_m2 = _mulx_u64(c->blocks[i], d, &hi_m2); \
			add_carry_m2 = _addcarryx_u64(add_carry_m2, carry_m2, low_m2, &temp_m2); \
			add_carry_2 = _addcarryx_u64(add_carry_2, res->blocks[i], temp_m2, (uint64*)&(res->blocks)[i-1]); \
			carry_m2 = hi_m2; \
		} \
 		\
		/* Block mul_size */\
		_addcarryx_u64(add_carry_m2, carry_m2, 0, &temp_m2); \
		add_carry_2 = _addcarryx_u64(add_carry_2, res->blocks[mul_size], temp_m2, (uint64*)&(res->blocks)[mul_size-1]); \
 		\
		/* Block mul_size + 1 */\
		res->blocks[mul_size] += (uint64_t)add_carry_2; \
		 \
		__COUNT_OP(&global_opcount, 5); \
	} \
	else \
	{ \
		for (uint64_t i = 0; i < mul_size + 1; i++) \
    	{ \
        	res->blocks[i] = res->blocks[i+1]; \
			__COUNT_INDEX(&global_index_count, 2); \
    	} \
		res->blocks[mul_size + 1] = 0U; \
	} \
}

#define DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(size) \
void bigint_mul_add_rshift_inplace_x2_ ## size (BigInt res, const BigInt a, const uint64_t b, const BigInt c, const uint64_t d) \
{ \
	BIGINT_MUL_ADD_RSHIFT_INPLACE_X2_BODY(size); \
}

/*
void bigint_mul_add_rshift_inplace_x2_generic(BigInt restrict res, const BigInt restrict a, const uint64_t b, const BigInt restrict c, const uint64_t d, const uint64_t mul_size)
{
	BIGINT_MUL_ADD_RSHIFT_INPLACE_X2_BODY(mul_size)
}
*/
/*
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(1);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(2);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(3);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(4);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(5);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(6);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(7);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(8);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(9);
DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(10);
*/