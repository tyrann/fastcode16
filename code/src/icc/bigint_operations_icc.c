#include <x86intrin.h>
#include <immintrin.h>
#include <inttypes.h>

#ifdef __INTEL_COMPILER
typedef unsigned long uint64;
#else
typedef unsigned long long uint64;
#endif

// Size in bytes of the memory allocated for bigint objects
#ifndef BIGINT_SIZE
    #define BIGINT_SIZE 160
#endif

// Alignment of bigint buffers in bytes
#define BIGINT_ALIGNMENT 32

// Size of the header informations of a BigInt (one uint64_t field)
#define BIGINT_HEADER_SIZE 8
#define BIGINT_HEADER_PADDING (BIGINT_ALIGNMENT - (BIGINT_HEADER_SIZE % BIGINT_ALIGNMENT))
#define BIGINT_BLOCKS_COUNT (BIGINT_SIZE - BIGINT_HEADER_SIZE - BIGINT_HEADER_PADDING) / 8

#if (BIGINT_SIZE / BIGINT_ALIGNMENT) * BIGINT_ALIGNMENT != BIGINT_SIZE
    #error "Please specify BIGINT_SIZE as a multiple of BIGINT_ALIGNMENT"
#endif

typedef uint64_t block;
typedef unsigned char uchar;

// Structure for big integers. Supports unsigned integres
// with value <= 2^(8*2^64). Only unsigned numbers are supported at the 
// moment.
typedef struct 
{
    // The number of octets (bytes) actually used storing the number
    uint64_t significant_blocks;
    
    // Padding bytes. This guarantees the required alignment on the octets array
    #if BIGINT_HEADER_PADDING != 0
    unsigned char __padding[BIGINT_HEADER_PADDING];
    #endif
    
    // Pointer to the buffer containing the octets of the number
    block blocks[BIGINT_BLOCKS_COUNT];
    
} __BigInt;

typedef __BigInt* BigInt;

// Nice trick for static assertions
// http://www.pixelbeat.org/programming/gcc/static_assert.html

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

#define BI_MONTGOMERYMUL_TMP1_TAG 14

#define __COUNT_OP(a, b)
#define __COUNT_INDEX(a, b)

// =======================================================================
// =======================================================================

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
__attribute((cdecl)) void bigint_mul_add_rshift_inplace_x2_ ## size (BigInt restrict res, const BigInt restrict a, const uint64_t b, const BigInt restrict c, const uint64_t d) \
{ \
	BIGINT_MUL_ADD_RSHIFT_INPLACE_X2_BODY(size); \
}

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