
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
#define WORDSIZE 64
#define B 2

#define PRINT_SIMD 0
#define __AVX2 0
#define USE_INLINE_ASM

#if PRINT_SIMD > 0
	#define PRINT_AVX_U64(f)	printf("%llu %llu %llu %llu \n", f[0], f[1], f[2], f[3]);
	#define PRINT_AVX_D(f)   	printf("%lf %lf %lf %lf \n", f[0], f[1], f[2], f[3]);
#else
	#define PRINT_AVX_U64(f)	
	#define PRINT_AVX_D(f)   	
#endif

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })
	 
uint64_t mul_opcount = 0;
uint64_t add_opcount = 0;
uint64_t shift_opcount = 0;
uint64_t avx_opcount = 0;
uint64_t global_index_count = 0;

uint64_t p_prime = 0;
BigInt montgomery_inverse_two;

void __montgomery_init(const BigInt p)
{
	montgomery_inverse_two = GET_BIGINT_PTR(BI_MONTGOMERY_INIT_INVERSE_TWO_TAG);
	BigInt prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
	if(bigint_are_equal(prime, p))
	{
		montgomery_inverse_two = bigint_from_hex_string(BI_MONTGOMERY_INIT_INVERSE_TWO_TAG, "800000000000000000000000000000000000000000000000");
		p_prime = 17472529885292845177UL;
		return;
	}
	prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001");
	if(bigint_are_equal(prime, p))
	{
		montgomery_inverse_two = bigint_from_hex_string(BI_MONTGOMERY_INIT_INVERSE_TWO_TAG, "7fffffffffffffffffffffff80000000");
		p_prime = 18446744073709551615UL;
		return;
	}
	prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
	if(bigint_are_equal(prime, p))
	{
		montgomery_inverse_two = bigint_from_hex_string(BI_MONTGOMERY_INIT_INVERSE_TWO_TAG, "8000000000000000000000000000000000000000000000000000000000000000");
		p_prime = 15580212934572586289UL;
		return;
	}
	prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF");
	//SECP384R1
	if(bigint_are_equal(prime, p))
	{
		montgomery_inverse_two = bigint_from_hex_string(BI_MONTGOMERY_INIT_INVERSE_TWO_TAG, "800000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
		p_prime = 4294967297UL;
		return;
	}
	prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
	if(bigint_are_equal(prime, p))
	{
		montgomery_inverse_two = bigint_from_hex_string(BI_MONTGOMERY_INIT_INVERSE_TWO_TAG, "40000000000000");
		p_prime = 1UL;
		return;
	}
}

void __montgomery_convert(BigInt res, const BigInt x, const BigInt p)
{
	bigint_copy(res, x);
	/*n is the R parameter in the Montgomery convertion*/

	uint64_t n = p->significant_blocks * 8 * 8;
	__COUNT_OP(&mul_opcount, 1);
	uint64_t i;
    
	for (i = 0; i < n; ++i)
   	{
		bigint_left_shift_inplace(res);
		if(bigint_is_greater(res, p))
		{
			bigint_sub_inplace(res, p);
		} 
	__COUNT_INDEX(&global_index_count, 1);
	}
}

void __montgomery_revert(BigInt rev, const BigInt x, const BigInt p)
{
	bigint_copy(rev, x);

	uint64_t n = p->significant_blocks * 8 * 8;
	__COUNT_OP(&mul_opcount, 1);
	uint64_t i;

	for (i = 0; i < n; ++i)
	{
		if(bigint_is_even(rev))
		{
			bigint_right_shift_inplace(rev);
		}
		else
		{
			bigint_add_inplace(rev, p);
			bigint_right_shift_inplace(rev);
		}
		__COUNT_INDEX(&global_index_count, 1);
	}
}

typedef unsigned long long int uint64;

#ifdef USE_INLINE_ASM
#define BIGINT_MUL_ADD_RSHIFT_INPLACE_X2_BODY(mul_size) \
{\
	unsigned char add_carry_1 = 0; \
	unsigned char add_carry_2 = 0; \
	uint64 low_m1, hi_m1, carry_m1; \
	uint64 low_m2, hi_m2, carry_m2, zero = 0; \
 	\
	BigInt tmp = GET_BIGINT_PTR(BI_MONTGOMERYMUL_TMP1_TAG); \
 	\
	if (b != 0 && d != 0) \
	{ \
		/* Block 0 */ \
		__asm__ __volatile__("addq $0, %0;" : "+r"(zero) : : "cc"); \
		low_m1 = _mulx_u64(a->blocks[0], b, &carry_m1); \
		__asm__ __volatile__( \
			"adcx %2, %1;" \
			"movq %1, %0;" \
			: "=m"(tmp->blocks[0]), "+r"(low_m1) \
			: ""(res->blocks[0]) \
			: "cc" \
		); \
		\
		/* Blocks 1 : mul_size-1 */ \
		for (unsigned int i = 1; i < mul_size; i++) { \
			low_m1 = _mulx_u64(a->blocks[i], b, &hi_m1); \
			__asm__ __volatile__( \
				"adox %3, %1;" \
				"adcx %2, %1;" \
				"movq %1, %0;" \
				: "=m"(tmp->blocks[i]), "+r"(low_m1) \
				: "m"(res->blocks[i]), "r"(carry_m1) \
				: "cc" \
			); \
			carry_m1 = hi_m1; \
		} \
		\
		low_m2 = _mulx_u64(c->blocks[0], d, &carry_m2); \
		__asm__ __volatile__( \
			"adox %4, %2;" \
			"adcx %3, %2;" \
			"movq %2, %0;" \
			"setc %1;" \
			: "=m"(tmp->blocks[mul_size]), "=r"(add_carry_1), "+r"(carry_m1) \
			: ""(res->blocks[mul_size]), "r"(zero) \
			: "cc" \
		); \
		\
		__asm__ __volatile__("addq $0, %0;" : "+r"(zero) : : "cc"); \
		__asm__ __volatile__( \
			"adcx %1, %0;" \
			: "+r"(low_m2) \
			: ""(tmp->blocks[0]) \
			: "cc" \
		); 	\
		\
		for (unsigned int i = 1; i < mul_size; i++) { \
			low_m2 = _mulx_u64(c->blocks[i], d, &hi_m2); \
			__asm__ __volatile__( \
				"adox %3, %1;" \
				"adcx %2, %1;" \
				"movq %1, %0;" \
				: "=m"(res->blocks[i-1]), "+r"(carry_m2) \
				: ""(tmp->blocks[i]), "r"(low_m2) \
				: "cc" \
			); \
			carry_m2 = hi_m2; \
		} \
 		\
		__asm__ __volatile__( \
			"adox %4, %2;" \
			"adcx %3, %2;" \
			"movq %2, %0;" \
			"setc %1;" \
			: "=m"(res->blocks[mul_size-1]), "=r"(add_carry_2), "+r"(carry_m2) \
			: ""(tmp->blocks[mul_size]), "r"(zero) \
			: "cc" \
		); \
 		\
		/* Block mul_size + 1 */ \
		res->blocks[mul_size] = res->blocks[mul_size+1] + (uint64_t)add_carry_1 + (uint64_t)add_carry_2; \
		res->blocks[mul_size + 1] = 0; \
		\
	} \
	else if (b != 0) \
	{ \
		/* Block 0 */ \
		 __asm__ __volatile__("addq $0, %0;" : "+r"(zero) : : "cc"); \
		low_m1 = _mulx_u64(a->blocks[0], b, &carry_m1); \
		__asm__ __volatile__( \
			"adcx %1, %0;" \
			: "+r"(low_m1) \
			: ""(res->blocks[0]) \
			: "cc" \
		); \
		/* Blocks 1 : mul_size-1 */\
		for (unsigned int i = 1; i < mul_size; i++) { \
			low_m1 = _mulx_u64(a->blocks[i], b, &hi_m1); \
			__asm__ __volatile__( \
				"adox %3, %1;" \
				"adcx %2, %1;" \
				"movq %1, %0;" \
				: "=m"(res->blocks[i-1]), "+r"(low_m1) \
				: "m"(res->blocks[i]), "r"(carry_m1) \
				: "cc" \
			); \
			carry_m1 = hi_m1; \
		} \
 		\
		/* Block mul_size */\
		__asm__ __volatile__( \
			"adox %4, %2;" \
			"adcx %3, %2;" \
			"movq %2, %0;" \
			"setc %1;" \
			: "=m"(res->blocks[mul_size-1]), "=r"(add_carry_1), "+r"(carry_m1) \
			: ""(res->blocks[mul_size]), "r"(zero) \
			: "cc" \
		); \
 		\
		/* Block mul_size + 1 */\
		res->blocks[mul_size] += (uint64_t)add_carry_1; \
	} \
	else if (d != 0) \
	{ \
		/* Block 0 */\
		__asm__ __volatile__("addq $0, %0;" : "+r"(zero) : : "cc"); \
		low_m2 = _mulx_u64(c->blocks[0], d, &carry_m2); \
		__asm__ __volatile__( \
			"adcx %1, %0;" \
			: "+r"(low_m2) \
			: ""(res->blocks[0]) \
			: "cc" \
		); \
 		\
		/* Blocks 1 : mul_size-1 */\
		for (unsigned int i = 1; i < mul_size; i++) { \
			low_m2 = _mulx_u64(c->blocks[i], d, &hi_m2); \
			__asm__ __volatile__( \
				"adox %3, %1;" \
				"adcx %2, %1;" \
				"movq %1, %0;" \
				: "=m"(res->blocks[i-1]), "+r"(low_m2) \
				: "m"(res->blocks[i]), "r"(carry_m2) \
				: "cc" \
			); \
			carry_m2 = hi_m2; \
		} \
 		\
		/* Block mul_size */\
		__asm__ __volatile__( \
			"adox %4, %2;" \
			"adcx %3, %2;" \
			"movq %2, %0;" \
			"setc %1;" \
			: "=m"(res->blocks[mul_size-1]), "=r"(add_carry_2), "+r"(carry_m2) \
			: ""(res->blocks[mul_size]), "r"(zero) \
			: "cc" \
		); \
 		\
		/* Block mul_size + 1 */\
		res->blocks[mul_size] += (uint64_t)add_carry_2; \
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
#else
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
			__COUNT_OP(&mul_opcount, 1); \
			__COUNT_OP(&add_opcount, 2); \
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
		\
			__COUNT_INDEX(&global_index_count, 1); \
			__COUNT_OP(&mul_opcount, 1); \
			__COUNT_OP(&add_opcount, 2); \
			\
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
		__COUNT_OP(&mul_opcount, 2); \
		__COUNT_OP(&add_opcount, 8); \
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
			__COUNT_OP(&mul_opcount, 1); \
			__COUNT_OP(&add_opcount, 2); \
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
		__COUNT_OP(&mul_opcount, 1); \
		__COUNT_OP(&add_opcount, 4); \
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
			__COUNT_OP(&mul_opcount, 1); \
			__COUNT_OP(&add_opcount, 2); \
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
		__COUNT_OP(&mul_opcount, 1); \
		__COUNT_OP(&add_opcount, 4); \
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
#endif

#define DECLARE_BIGINT_MUL_ADD_RSHIFT_INPLACE_X2(size) \
void bigint_mul_add_rshift_inplace_x2_ ## size (BigInt res, const BigInt a, const uint64_t b, const BigInt c, const uint64_t d) \
{ \
	BIGINT_MUL_ADD_RSHIFT_INPLACE_X2_BODY(size); \
}

/*void bigint_mul_add_rshift_inplace_x2_generic(BigInt restrict res, const BigInt restrict a, const uint64_t b, const BigInt restrict c, const uint64_t d, const uint64_t mul_size)
{
	BIGINT_MUL_ADD_RSHIFT_INPLACE_X2_BODY(mul_size)
}*/

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

void montgomery_mul_x2(BigInt restrict res1, const BigInt x1, const BigInt y1, BigInt restrict res2, const BigInt x2, const BigInt y2, const BigInt p)
{
	assert(p_prime != 0);
	
	bigint_copy(res1, bigint_zero);
	bigint_copy(res2, bigint_zero);
	
	uint64_t u1, u2, a1_0, a2_0, y1_0, y2_0, x1_i, x2_i;
	y1_0 = y1->blocks[0];
	y2_0 = y2->blocks[0];
	
	// Clear memory
	uint64_t mul_size = p->significant_blocks;
	if (y1->significant_blocks < mul_size)
		memset(y1->blocks + y1->significant_blocks, 0, (ROUND_UP_MUL4(mul_size) - y1->significant_blocks) * 8);
	if (y2->significant_blocks < mul_size)
		memset(y2->blocks + y2->significant_blocks, 0, (ROUND_UP_MUL4(mul_size) - y2->significant_blocks) * 8);
	memset(res1->blocks, 0, ROUND_UP_MUL4(mul_size + 2) * 8);
	memset(res2->blocks, 0, ROUND_UP_MUL4(mul_size + 2) * 8);
	
	for (unsigned int i = 0; i < p->significant_blocks; ++i)
	{
		a1_0 = res1->blocks[0];
		a2_0 = res2->blocks[0];
		if(x1->significant_blocks > i) {
			x1_i = x1->blocks[i];
		} else {
			x1_i = 0;
		}
		if(x2->significant_blocks > i) {
			x2_i = x2->blocks[i];
		} else {
			x2_i = 0;
		}
		
		u1 = (a1_0 + (x1_i * y1_0)) * p_prime;
		u2 = (a2_0 + (x2_i * y2_0)) * p_prime;
		__COUNT_OP(&add_opcount, 2);
		__COUNT_OP(&mul_opcount, 4);
		
		switch (mul_size) {
 		case 1:
			bigint_mul_add_rshift_inplace_x2_1(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_1(res2, y2, x2_i, p, u2);
    		break;
		case 2:
			bigint_mul_add_rshift_inplace_x2_2(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_2(res2, y2, x2_i, p, u2);
    		break;
		case 3:
			bigint_mul_add_rshift_inplace_x2_3(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_3(res2, y2, x2_i, p, u2);
    		break;
		case 4:
			bigint_mul_add_rshift_inplace_x2_4(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_4(res2, y2, x2_i, p, u2);
    		break;
		case 5:
			bigint_mul_add_rshift_inplace_x2_5(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_5(res2, y2, x2_i, p, u2);
    		break;
		case 6:
			bigint_mul_add_rshift_inplace_x2_6(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_6(res2, y2, x2_i, p, u2);
    		break;
		case 7:
			bigint_mul_add_rshift_inplace_x2_7(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_7(res2, y2, x2_i, p, u2);
    		break;
		case 8:
			bigint_mul_add_rshift_inplace_x2_8(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_8(res2, y2, x2_i, p, u2);
    		break;
		case 9:
			bigint_mul_add_rshift_inplace_x2_9(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_9(res2, y2, x2_i, p, u2);
    		break;
		case 10:
			bigint_mul_add_rshift_inplace_x2_10(res1, y1, x1_i, p, u1);
			bigint_mul_add_rshift_inplace_x2_10(res2, y2, x2_i, p, u2);
    		break;
 		default:
		 	assert("ERROR: no specialized version of bigint_mul_add_rshift_inplace_x2 available");
			/*bigint_mul_add_rshift_inplace_x2_generic(res1, y1, x1_i, p, u1, mul_size);
			bigint_mul_add_rshift_inplace_x2_generic(res2, y2, x2_i, p, u2, mul_size);*/
    		break;
		 } 
		 
		__COUNT_INDEX(&global_index_count, 1);
	}
	
	res1->significant_blocks = mul_size + 1;
	res2->significant_blocks = mul_size + 1;
	while(res1->blocks[res1->significant_blocks-1] == 0 && res1->significant_blocks > 1) res1->significant_blocks--;
	while(res2->blocks[res2->significant_blocks-1] == 0 && res2->significant_blocks > 1) res2->significant_blocks--;
	
	if(bigint_is_greater(res1, p))
	{
		bigint_sub_inplace(res1, p);
	}
	if(bigint_is_greater(res2, p))
	{
		bigint_sub_inplace(res2, p);
	}
}

void montgomery_mul(BigInt restrict res, const BigInt x, const BigInt y, const BigInt p)
{
	assert(p_prime != 0);
	
	//Set res to 0
	bigint_copy(res, bigint_zero);
	uint64_t u, a_0, y_0, x_i;
	y_0 = y->blocks[0];
	
	// Clear memory
	uint64_t mul_size = p->significant_blocks;
	if (y->significant_blocks < mul_size)
	{
		memset(y->blocks + y->significant_blocks, 0, (ROUND_UP_MUL4(mul_size) - y->significant_blocks) * 8);
		__COUNT_OP(&mul_opcount, 1);
		__COUNT_OP(&add_opcount, 2);
	}
	memset(res->blocks, 0, ROUND_UP_MUL4(mul_size + 2) * 8);
	__COUNT_OP(&mul_opcount, 1);
	__COUNT_OP(&add_opcount, 1);
	
	for (unsigned int i = 0; i < p->significant_blocks; ++i)
	{
		a_0 = res->blocks[0];
		if(x->significant_blocks > i) {
			x_i = x->blocks[i];
		} else {
			x_i = 0;
		}
		u = (a_0 + (x_i * y_0)) * p_prime;
		__COUNT_OP(&add_opcount, 1);
		__COUNT_OP(&mul_opcount,2);
		
		// ===================================================
		//     > Original code (equivalent of the
		//       bigint_mul_add_rshift_inplace_x2 function)
		// bigint_copy(tmp1, y_inital); 
		// bigint_multiply_inplace(tmp1, x_i); 
		// bigint_copy(tmp2, p); 
		// bigint_multiply_inplace(tmp2, u); 
		// bigint_add_inplace(res, tmp1); 
		// bigint_add_inplace(res, tmp2); 
		// bigint_right_shift_inplace_64(res); 
		// ===================================================
		switch (mul_size) {
 		case 1:
			bigint_mul_add_rshift_inplace_x2_1(res, y, x_i, p, u);
    		break;
		case 2:
			bigint_mul_add_rshift_inplace_x2_2(res, y, x_i, p, u);
    		break;
		case 3:
			bigint_mul_add_rshift_inplace_x2_3(res, y, x_i, p, u);
    		break;
		case 4:
			bigint_mul_add_rshift_inplace_x2_4(res, y, x_i, p, u);
    		break;
		case 5:
			bigint_mul_add_rshift_inplace_x2_5(res, y, x_i, p, u);
    		break;
		case 6:
			bigint_mul_add_rshift_inplace_x2_6(res, y, x_i, p, u);
    		break;
		case 7:
			bigint_mul_add_rshift_inplace_x2_7(res, y, x_i, p, u);
    		break;
		case 8:
			bigint_mul_add_rshift_inplace_x2_8(res, y, x_i, p, u);
    		break;
		case 9:
			bigint_mul_add_rshift_inplace_x2_9(res, y, x_i, p, u);
    		break;
		case 10:
			bigint_mul_add_rshift_inplace_x2_10(res, y, x_i, p, u);
    		break;
 		default:
		 	assert("ERROR: no specialized version of bigint_mul_add_rshift_inplace_x2 available");
			/*bigint_mul_add_rshift_inplace_x2_generic(res, y, x_i, p, u, mul_size);*/
    		break;
		 } 
	
		__COUNT_INDEX(&global_index_count, 1);
	}
	
	res->significant_blocks = mul_size + 1;
	__COUNT_OP(&add_opcount, 1);
	while(res->blocks[res->significant_blocks-1] == 0 && res->significant_blocks > 1)
	{
		res->significant_blocks--;
		__COUNT_OP(&add_opcount, 2); 
	}
	
	if(bigint_is_greater(res, p))
	{
		bigint_sub_inplace(res, p);
	}
}

void bigint_mul_add_inplace(BigInt res, const BigInt a, const uint64_t b, const uint64_t mul_size)
{
	unsigned char add_carry = 0, add_carry_1 = 0;
	unsigned long long int mul_low, mul_hi, mul_carry, temp;
	if(b != 0)
	{
		// Block 0
		mul_low = _mulx_u64(a->blocks[0], b, &mul_carry);
		add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[0], mul_low, (unsigned long long*)&(res->blocks)[0]);
		
		// Blocks 1 : mul_size-1
		for(unsigned int i = 1; i < mul_size; i++)
		{
			__COUNT_INDEX(&global_index_count, 1);
			__COUNT_OP(&add_opcount, 1);
			__COUNT_OP(&mul_opcount, 2);

		
			mul_low = _mulx_u64(a->blocks[i], b, &mul_hi);
			add_carry = _addcarryx_u64(add_carry, mul_carry, mul_low, &temp);
			add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[i], temp, (unsigned long long*)&(res->blocks)[i]);
			mul_carry = mul_hi;
		}
		
		// Block mul_size
		_addcarryx_u64(add_carry, mul_carry, 0, &temp);
		add_carry_1 = _addcarryx_u64(add_carry_1, res->blocks[mul_size], temp, (unsigned long long*)&(res->blocks)[mul_size]);
			
		// Block mul_size + 1
		res->blocks[mul_size+1] += (uint64_t)add_carry_1;
		__COUNT_OP(&add_opcount, 5);
		__COUNT_OP(&mul_opcount, 1);

	}
}

void bigint_multiply(BigInt res, const BigInt a, const uint64_t b)
{
	unsigned char add_carry = 0;
	unsigned long long int mul_low, mul_hi, mul_carry;
	res->significant_blocks = a->significant_blocks;
	if(b == 0)
	{
		bigint_copy(res, bigint_zero);
	}
	else
	{
		res->blocks[0] = _mulx_u64(a->blocks[0], b, &mul_carry);
		for(unsigned int i = 1; i < a->significant_blocks; i++)
		{
			__COUNT_INDEX(&global_index_count, 1);
			__COUNT_OP(&add_opcount, 1);
			__COUNT_OP(&mul_opcount, 1);
			
			mul_low = _mulx_u64(a->blocks[i], b, &mul_hi);
			add_carry = _addcarryx_u64(add_carry, mul_carry, mul_low, (unsigned long long*)&(res->blocks)[i]);
			mul_carry = mul_hi;
		}
		
		_addcarryx_u64(add_carry, mul_carry, 0, (unsigned long long*)&(res->blocks)[a->significant_blocks]);
		if (res->blocks[a->significant_blocks] > 0)
		{
			res->significant_blocks += 1;
			__COUNT_OP(&add_opcount, 1);
			__COUNT_INDEX(&global_index_count, 1);
		}
		
		__COUNT_INDEX(&global_index_count, 1);
		__COUNT_OP(&add_opcount, 1);
		__COUNT_OP(&mul_opcount, 1);

	}
}

void bigint_multiply_inplace(BigInt a, uint64_t b)
{
	unsigned __int128 tmp;
	uint64_t carry = 0;
	uint64_t carry_current = 0;
	uint64_t result;
	char carry2 = 0;
	if(b == 0)
	{
		bigint_copy(a, bigint_zero);
	}
	else
	{
		tmp = ((unsigned  __int128)a->blocks[0]) * ((unsigned  __int128)b);
		__COUNT_OP(&mul_opcount, 1);
		result = (uint64_t)tmp;
		uint64_t sig_blocks = a->significant_blocks;
		carry = tmp >> 64;
		__COUNT_OP(&shift_opcount, 1);
		for(unsigned int i = 0; i < sig_blocks + 1; i++)
		{
			__COUNT_INDEX(&global_index_count, 1);
			carry2 = _addcarry_u64(carry2, carry_current, result, (unsigned long long*)&(a->blocks)[i]);
			__COUNT_OP(&add_opcount,1);
			if(a->blocks[i] > 0 )
			{
				a->significant_blocks = i+1;
				__COUNT_OP(&add_opcount,1);
			}
			if(i+1 < sig_blocks) {
				tmp = ((unsigned  __int128)a->blocks[i+1]) * ((unsigned  __int128)b);
				__COUNT_OP(&mul_opcount,1);
				__COUNT_INDEX(&global_index_count, 2);
			}
			else
			{
				tmp = 0;
			}
			result = (uint64_t)tmp;
			carry_current = carry;
			carry = tmp >> 64;
			__COUNT_OP(&shift_opcount,1);
			__COUNT_INDEX(&global_index_count, 1);
		}
	}
}

void bigint_left_shift_inplace(BigInt a)
{
    BIGINT_ASSERT_VALID(a);
#if __AVX2 == 2	
   /*Version 1
	* This is not implemented because of the complexity of the carry propagation" */
   
#else
   
    // Left shift octets by one, propagating the carry across octets.
    uint64_t carry = 0;
    for (uint64_t i = 0; i < a->significant_blocks; i++)
    {
        uint64_t cur_carry = carry;
        carry = a->blocks[i] >> 63;
		__COUNT_OP(&shift_opcount, 1);
    
        a->blocks[i] = cur_carry + (a->blocks[i] << 1);
		__COUNT_OP(&add_opcount, 1);
		__COUNT_OP(&shift_opcount, 1);
		__COUNT_INDEX(&global_index_count, 1);
    }
    
    // Add carry to last octet if necessary
    if (carry > 0)
    {
        a->blocks[a->significant_blocks] = carry;
		a->significant_blocks++;
		memset(a->blocks + a->significant_blocks, 0, (ROUND_UP_MUL4(a->significant_blocks) - a->significant_blocks) * 8);
		__COUNT_OP(&add_opcount, 3);
		__COUNT_OP(&mul_opcount, 1);
    }

#endif
}

void bigint_right_shift_inplace(BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    
#if __AVX2 > 0	
	/*Version 1*/
    for (uint64_t i = 0; i <= a->significant_blocks; i+=4)
    {
		__m256i l0 = _mm256_castpd_si256(_mm256_load_pd((double *)a->blocks + i));
		__m256i l1 = _mm256_castpd_si256(_mm256_load_pd((double *)a->blocks + i + 4));

		__m256i perm128 = _mm256_permute2f128_si256(l0,l1, 0x21);
		__m256d tmp = _mm256_shuffle_pd(_mm256_castsi256_pd(l0), _mm256_castsi256_pd(perm128), 0x15);
		//long long int * pr = (long long int *)&tmp;
				
		//[x1 x2 x3 x4] << 63 
		__m256i hi_shift = _mm256_slli_epi64(_mm256_castpd_si256(tmp),0x3F);

		//[x0 x1 x2 x3] >> 1 
		__m256i lo_shift = _mm256_srli_epi64(l0,0x1); 
		__m256i ret = _mm256_add_epi64(hi_shift,lo_shift);

		_mm256_store_pd((double *)a->blocks + i, _mm256_castsi256_pd(ret)); 
		// Check if the number of significant octets decreased
		__COUNT_OP(&add_opcount, 2);
		__COUNT_OP(&avx_opcount, 5);
		
	}
	if (a->blocks[a->significant_blocks-1] == 0 && a->significant_blocks > 1)
	{
		__COUNT_OP(&add_opcount, 2);
		a->significant_blocks--;
	}
#else
    // Right shift octets by one, propagating the carry across octets.
    uint64_t carry = 0;
    for (uint64_t i = a->significant_blocks; i > 0; i--)
    {
        uint64_t cur_carry = carry;
        carry = a->blocks[i-1] << 63;
		__COUNT_OP(&shift_opcount, 2);
		__COUNT_INDEX(&global_index_count, 1);

        a->blocks[i-1] = cur_carry + (a->blocks[i-1] >> 1);
		__COUNT_OP(&add_opcount, 1);
		__COUNT_OP(&shift_opcount, 1);
		__COUNT_INDEX(&global_index_count, 1);
    }
    
    // Check if the number of significant octets decreased
    if (a->blocks[a->significant_blocks-1] == 0 && a->significant_blocks > 1)
	{
		__COUNT_OP(&add_opcount, 2);
        a->significant_blocks--;
	}
#endif

}

void bigint_right_shift_inplace_64(BigInt a)
{
    BIGINT_ASSERT_VALID(a);
#if __AVX2 > 0	
	/*Version 1*/
    for (uint64_t i = 0; i <= a->significant_blocks; i+=4)
    {
		__m256i l0 = _mm256_castpd_si256(_mm256_load_pd((double *)a->blocks + i));
		__m256i l1 = _mm256_castpd_si256(_mm256_load_pd((double *)a->blocks + i + 4));
		__m256i perm128 = _mm256_permute2f128_si256(l0,l1, 0x21);
		__m256d ret = _mm256_shuffle_pd(_mm256_castsi256_pd(l0), _mm256_castsi256_pd(perm128), 0x15);
		//PRINT_AVX_U64((long long int *)&ret);
		_mm256_store_pd((double *)a->blocks + i, ret); 

		__COUNT_OP(&avx_opcount, 2);
		__COUNT_OP(&add_opcount, 2);
		__COUNT_INDEX(&global_index_count, 1);

	}
	if(a->significant_blocks > 1)
	{
		a->significant_blocks--;
		__COUNT_OP(&add_opcount, 1);
	}
#else

	//SISD Version	
    for (uint64_t i = 0; i < a->significant_blocks; i++)
    {
        a->blocks[i] = a->blocks[i+1];
		__COUNT_INDEX(&global_index_count, 2);
    }
	a->blocks[a->significant_blocks-1] = 0U;
	__COUNT_OP(&add_opcount, 1);

	if(a->significant_blocks > 1)
	{
		a->significant_blocks--;
		__COUNT_OP(&add_opcount, 1);
	}

#endif
}

void bigint_modulo_inplace(BigInt a, const BigInt mod)
{
	assert(bigint_are_equal(bigint_zero, mod) != 1);

	while(!bigint_is_greater(mod, a))
		bigint_sub_inplace(a, mod);
}

void bigint_add_inplace(BigInt a, const BigInt b)
{
	BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
	
	// Extends a if b is larger
	if(a->significant_blocks < b->significant_blocks)
	{
		memset(a->blocks + a->significant_blocks, 0, (ROUND_UP_MUL4(b->significant_blocks) - a->significant_blocks) * 8);
		__COUNT_OP(&add_opcount, 2);
		__COUNT_OP(&mul_opcount, 1);
		a->significant_blocks = b->significant_blocks;

	}

	// Execute adding and propagate carry
	uint64_t i = 0;
	unsigned char carry = 0;
	for (; i < a->significant_blocks; i++)
    {
		__COUNT_INDEX(&global_index_count, 1);
		if(i < b->significant_blocks)
		{
			carry = _addcarry_u64(carry, a->blocks[i], b->blocks[i], (unsigned long long*)&(a->blocks)[i]);
			__COUNT_OP(&add_opcount, 1);
		}
		else
		{
			if (carry == 0) break;
			carry = _addcarry_u64(carry, a->blocks[i], 0, (unsigned long long*)&(a->blocks)[i]);
			__COUNT_OP(&add_opcount, 1);
		}
    }
	// If needed, allocate 1 more block for the carry
	if(carry > 0)
	{
		a->significant_blocks += 1;
		__COUNT_OP(&add_opcount, 1);
		a->blocks[i] = (uint64_t)carry;
	}	
}

void bigint_sub_inplace(BigInt a, const BigInt b)
{
	BIGINT_ASSERT_VALID(a);
	BIGINT_ASSERT_VALID(b);
	
    // Negative representation is not implemented
    assert(!bigint_is_greater(b, a));

	uint64_t i = 0;
	unsigned char borrow = 0;
	for (; i < a->significant_blocks; i++)
	{
		__COUNT_INDEX(&global_index_count, 1);
	    if(i < b->significant_blocks)
	    {
			borrow = _subborrow_u64(borrow, b->blocks[i], a->blocks[i], (unsigned long long*)&(a->blocks)[i]);
			__COUNT_OP(&add_opcount, 1);
	    }
	    else
	    {
			if (borrow == 0) break;
			borrow = _subborrow_u64(borrow, 0, a->blocks[i], (unsigned long long*)&(a->blocks)[i]);
			__COUNT_OP(&add_opcount, 1);
	    }
	}

	for(; a->significant_blocks > 1; a->significant_blocks--)
	{
		if (a->blocks[a->significant_blocks-1] != 0) break;
		__COUNT_OP(&add_opcount, 1);
		__COUNT_INDEX(&global_index_count, 1);
	}
}

void bigint_add_inplace_mod(BigInt a, const BigInt b, const BigInt p)
{
	bigint_add_inplace(a, b);
	bigint_modulo_inplace(a, p);
}

void bigint_sub_inplace_mod(BigInt a, const BigInt b, const BigInt p)
{
	if(bigint_is_greater(a,b))
	{
		bigint_sub_inplace(a, b);
	}
	else
	{
		BigInt inverse = GET_BIGINT_PTR(BI_BIGINT_SUB_INPLACE_MOD_INVERSE_TAG);
		bigint_copy(inverse, p);
		bigint_sub_inplace(inverse, b);
		bigint_add_inplace(a, inverse);
		bigint_modulo_inplace(a, p);
	}
}

// Based on algorithm 2.22 of doc/fields_arithmetic.pdf
void bigint_divide(BigInt dest, const BigInt b, const BigInt a, const BigInt p)
{
	assert(!bigint_are_equal(bigint_zero, a));
	
	if (bigint_are_equal(b, bigint_zero))
	{
		bigint_copy(dest, bigint_zero);
	}
	else
	{
		// 1)
		BigInt u = GET_BIGINT_PTR(BI_DIVIDE_U_TAG);
		BigInt v = GET_BIGINT_PTR(BI_DIVIDE_V_TAG);
		bigint_copy(u, a);
		bigint_copy(v, p);
	
		// 2)
		BigInt x1 = GET_BIGINT_PTR(BI_DIVIDE_X1_TAG);
		bigint_copy(x1, b);
		BigInt x2 = bigint_from_uint64(BI_DIVIDE_X2_TAG, 0);
	
		// 3)
		while (!bigint_are_equal(u, bigint_one) && !bigint_are_equal(v, bigint_one))
		{
			// 3.1)
			while (bigint_is_even(u))
			{
				bigint_right_shift_inplace(u);
				if (!bigint_is_even(x1))
					bigint_add_inplace(x1, p);
				bigint_right_shift_inplace(x1);
			}
			
			// 3.2)
			while (bigint_is_even(v))
			{
				bigint_right_shift_inplace(v);
				if (!bigint_is_even(x2))
					bigint_add_inplace(x2, p);
				bigint_right_shift_inplace(x2);
			}
			
			// 3.3
			if (bigint_is_greater(v, u))
			{
				bigint_sub_inplace(v, u);
				if (bigint_is_greater(x1, x2))
					bigint_add_inplace(x2, p);
				bigint_sub_inplace(x2, x1);
			}
			else
			{
				bigint_sub_inplace(u, v);
				if(bigint_is_greater(x2, x1))
					bigint_add_inplace(x1, p);
				bigint_sub_inplace(x1, x2);
			}
		}
	
		// 4)
		if (bigint_are_equal(u, bigint_one))
			bigint_copy(dest, x1);
		else
			bigint_copy(dest, x2);
	}
}
