
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
#include <inttypes.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>
#define WORDSIZE 64
#define B 2

uint64_t global_opcount = 0;
uint64_t global_index_count = 0;
uint64_t p_prime = 0;

/*
 * sets p_prime to -p^-1 (mod 2^64)
 */
void __montgomery_init(const BigInt p)
{
	BigInt prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
	if(bigint_are_equal(prime, p))
	{
		p_prime = 17472529885292845177UL;
		return;
	}
	prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001");
	if(bigint_are_equal(prime, p))
	{
		p_prime = 18446744073709551615UL;
		return;
	}
	prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
	if(bigint_are_equal(prime, p))
	{
		p_prime = 15580212934572586289UL;
		return;
	}
	prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF");
	if(bigint_are_equal(prime, p))
	{
		p_prime = 4294967297UL;
		return;
	}
	prime = bigint_from_hex_string(BI_MONTGOMERY_INIT_PRIME_TAG, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
	if(bigint_are_equal(prime, p))
	{
		p_prime = 1UL;
		return;
	}
}

void __montgomery_convert(BigInt res, const BigInt x, const BigInt p)
{
	__montgomery_init(p);
	bigint_copy(res, x);
	/*n is the R parameter in the Montgomery convertion*/

	uint64_t n = p->significant_blocks * 8 * 8;
	__COUNT_OP(&global_opcount, 1);
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
	__COUNT_OP(&global_opcount, 1);
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

void montgomery_mul(BigInt res, const BigInt x, const BigInt y, const BigInt p)
{
	BigInt x_mont = GET_BIGINT_PTR(BI_MONTGOMERYMUL_XMONT_TAG);
	BigInt y_mont = GET_BIGINT_PTR(BI_MONTGOMERYMUL_YMONT_TAG);

	bigint_copy(x_mont, x);
	bigint_copy(y_mont, y);

	/*Set res to 0*/
	bigint_copy(res, bigint_zero);

	uint64_t u, a_0, y_0, x_i;
	unsigned __int128 tmp;
	y_0 = y->blocks[0];
	BigInt dummy1 = GET_BIGINT_PTR(BI_DUMMY1_TAG);
	BigInt dummy2 = GET_BIGINT_PTR(BI_DUMMY2_TAG);
	for (unsigned int i = 0; i < p->significant_blocks; ++i)
	{
		a_0 = res->blocks[0];
		x_i = x->blocks[i];
		tmp = (a_0 + ((unsigned __int128)x_i * (unsigned __int128)y_0)) * p_prime;
		u = tmp;
		bigint_copy(dummy1, y);
		multiply_inplace(dummy1, x_i);
		bigint_copy(dummy2, p);
		multiply_inplace(dummy2, u);
		bigint_add_inplace(res, dummy1);
		bigint_add_inplace(res, dummy2);
		bigint_right_shift_inplace_64(res);

		__COUNT_INDEX(&global_index_count, 1);
	}
	
	if(bigint_is_greater(res, p))
	{
		bigint_sub_inplace(res, p);
	}
}

void multiply_inplace(BigInt a, uint64_t b)
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
		result = (uint64_t)tmp;
		uint64_t sig_blocks = a->significant_blocks;
		carry = tmp >> 64;
		for(unsigned int i = 0; i < sig_blocks + 1; i++)
		{
			carry2 = _addcarry_u64(carry2, carry_current, result, (unsigned long long*)&(a->blocks)[i]);
			if(a->blocks[i] > 0 )
			{
				a->significant_blocks = i+1;
			}
			if(i+1 < sig_blocks) {
				tmp = ((unsigned  __int128)a->blocks[i+1]) * ((unsigned  __int128)b);
			}
			else
			{
				tmp = 0;
			}
			result = (uint64_t)tmp;
			carry_current = carry;
			carry = tmp >> 64;
		}
	}
}

void bigint_left_shift_inplace(BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    
    // Left shift octets by one, propagating the carry across octets.
    uint64_t carry = 0;
    for (uint64_t i = 0; i < a->significant_blocks; i++)
    {
        uint64_t cur_carry = carry;
        carry = a->blocks[i] >> 63;
		__COUNT_OP(&global_opcount, 1);
    
        a->blocks[i] = cur_carry + (a->blocks[i] << 1);
		__COUNT_OP(&global_opcount, 1);
		__COUNT_INDEX(&global_index_count, 1);
    }
    
    // Add carry to last octet if necessary
    if (carry > 0)
    {
		__COUNT_OP(&global_opcount, 1);
        a->blocks[a->significant_blocks] = carry;
		a->significant_blocks++;
		memset(a->blocks + a->significant_blocks, 0, (ROUND_UP_MUL4(a->significant_blocks) - a->significant_blocks) * 8);
    }
}

void bigint_right_shift_inplace(BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    
    // Right shift octets by one, propagating the carry across octets.
    uint64_t carry = 0;
    for (uint64_t i = a->significant_blocks; i > 0; i--)
    {
        uint64_t cur_carry = carry;
        carry = a->blocks[i-1] << 63;
		__COUNT_OP(&global_opcount, 2);

        a->blocks[i-1] = cur_carry + (a->blocks[i-1] >> 1);
		__COUNT_OP(&global_opcount, 3);
		__COUNT_INDEX(&global_index_count, 1);
    }
    
    // Check if the number of significant octets decreased
    if (a->blocks[a->significant_blocks-1] == 0 && a->significant_blocks > 1)
	{
		__COUNT_OP(&global_opcount, 2);
        a->significant_blocks--;
		__COUNT_OP(&global_opcount, 1);
	}
}

void bigint_right_shift_inplace_64(BigInt a)
{
    BIGINT_ASSERT_VALID(a);

    for (uint64_t i = 0; i < a->significant_blocks; i++)
    {
        a->blocks[i] = a->blocks[i+1];
		__COUNT_INDEX(&global_index_count, 1);
    }
	a->blocks[a->significant_blocks-1] = 0U;

	if(a->significant_blocks > 1)
	{
		a->significant_blocks--;
	}
	__COUNT_INDEX(&global_opcount, 2);
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
		__COUNT_OP(&global_opcount, 2);
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
			__COUNT_OP(&global_opcount, 2);
		}
		else
		{
			if (carry == 0) break;
			carry = _addcarry_u64(carry, a->blocks[i], 0, (unsigned long long*)&(a->blocks)[i]);
			__COUNT_OP(&global_opcount, 1);
		}
    }
	// If needed, allocate 1 more block for the carry
	if(carry > 0)
	{
		a->significant_blocks += 1;
		__COUNT_OP(&global_opcount, 1);
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
			__COUNT_OP(&global_opcount, 1);
	    }
	    else
	    {
			if (borrow == 0) break;
			borrow = _subborrow_u64(borrow, 0, a->blocks[i], (unsigned long long*)&(a->blocks)[i]);
			__COUNT_OP(&global_opcount, 1);
	    }
	}

	for(; a->significant_blocks > 1; a->significant_blocks--)
	{
		if (a->blocks[a->significant_blocks-1] != 0) break;
		__COUNT_OP(&global_opcount, 3);
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
			__COUNT_OP(&global_opcount, 1);
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
