
#include <stdlib.h>
#include <string.h>

#include "logging/logging.h"
#include "opcount/opcount.h"
#include "bigint_operations.h"
#include "bigint_structure.h"
#include "bigint_conversion.h"
#include "bigint_utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define WORDSIZE 64
#define B 2

uint64_t global_opcount = 0;
uint64_t global_index_count = 0;

void __montgomery_convert(BigInt res, const BigInt x, const BigInt p)
{
	bigint_copy(res, x);
	/*n is the R parameter in the Montgomery convertion*/

	uint64_t n = p->significant_octets * 8;
	__COUNT_OP(&global_opcount, 1);
	uint64_t i;
    
	for (i = 0; i < n; ++i)
   	{
		bigint_left_shift_inplace(res);
		if(bigint_is_greater(res, p))
		{
			bigint_sub_inplace(res, p);
		} 
	}
}

void __montgomery_revert(BigInt rev, const BigInt x, const BigInt p)
{
	bigint_copy(rev, x);

	uint64_t n = p->significant_octets * 8;
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
	}
}

void montgomery_mul(BigInt res, const BigInt x, const BigInt y, const BigInt p)
{
	BigInt x_mont = GET_BIGINT_PTR(BI_MONTGOMERYMUL_XMONT_TAG);
	BigInt y_mont = GET_BIGINT_PTR(BI_MONTGOMERYMUL_YMONT_TAG);

	__montgomery_convert(x_mont, x, p);
	__montgomery_convert(y_mont, y, p);

	/* This is -p^-1 mod b*/
	int pbar = -1;

	/*Set res to 0*/
	bigint_copy(res, bigint_zero);

	/*We take the smallest power of 2 that is bigger than p*/
	int n = p->significant_octets * 8;
	__COUNT_OP(&global_opcount, 1);
	int i;

	uint8_t y0 = y_mont->octets[0] & 0x1;
	for (i = 0; i < n; ++i) 
	{
		// ui <- (z0 +xi*y0)*pbar mod b
		uint8_t z0 = res->octets[0] & 0x1;
		uint8_t xi = (x_mont->octets[0]) & 0x1;
		bigint_right_shift_inplace(x_mont);		
		uint64_t ui = ((z0 + xi*y0)*pbar) % B;
		__COUNT_OP(&global_opcount, 4);
		
		//Z <- (Z + xiy + ui*p)/b
		
		if(xi)
		{
			bigint_add_inplace(res, y_mont);
		}
		if(ui)
		{
			bigint_add_inplace(res, p);
		}

		bigint_right_shift_inplace(res);
	}
	
	if(bigint_is_greater(res, p))
	{
		bigint_sub_inplace(res, p);
	}
}


void bigint_left_shift_inplace(BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    
    // Left shift octets by one, propagating the carry across octets.
    uchar carry = 0;
    for (uint64_t i = 0; i < a->significant_octets; i++)
    {
        uchar cur_carry = carry;
        carry = a->octets[i] >> 7;
		__COUNT_OP(&global_opcount, 1);
    
        a->octets[i] = cur_carry + (a->octets[i] << 1);
		__COUNT_OP(&global_opcount, 1);
		__COUNT_INDEX(&global_index_count, 1);
    }
    
    // Add carry to last octet if necessary
    if (carry > 0)
    {
		__COUNT_OP(&global_opcount, 1);
        a->octets[a->significant_octets] = carry;
		a->significant_octets++;
    }
}

void bigint_right_shift_inplace(BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    
    // Right shift octets by one, propagating the carry across octets.
    uchar carry = 0;
    for (uint64_t i = a->significant_octets; i > 0; i--)
    {
        uchar cur_carry = carry;
        carry = a->octets[i-1] << 7;
		__COUNT_OP(&global_opcount, 1);
        a->octets[i-1] = cur_carry + (a->octets[i-1] >> 1);
		__COUNT_OP(&global_opcount, 1);
    }
    
    // Check if the number of significant octets decreased
    if (a->octets[a->significant_octets-1] == 0 && a->significant_octets > 1)
	{
		__COUNT_OP(&global_opcount, 1);
        a->significant_octets--;
		__COUNT_OP(&global_opcount, 1);
	}
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

	uint32_t carry = 0;
	uint32_t a_bytes = a->significant_octets;
	
	// Extends a if b is larger
	if(a->significant_octets < b->significant_octets)
	{
		__COUNT_OP(&global_opcount, 1);
		memset(a->octets + a->significant_octets, 0, b->significant_octets - a->significant_octets);
		a->significant_octets = b->significant_octets;
	}

	a_bytes = a->significant_octets;
	uint64_t i = 0;
	// Execute adding and propagate carry
	for (; i < a_bytes; i++)
    {	
		uint32_t atemp;
		uint32_t btemp;
		__COUNT_OP(&global_opcount, 1);
		if(i <= b->significant_octets-1)
		{
			atemp = (uint32_t)a->octets[i];
			btemp = (uint32_t)b->octets[i];
			carry = (carry + atemp + btemp);
			__COUNT_OP(&global_opcount, 2);
		}
		else
		{
			atemp = (uint32_t)a->octets[i];
			carry = (carry + atemp);
			__COUNT_OP(&global_opcount, 1);
		}

		a->octets[i] = carry & 0xFF;	
		carry = carry >> 8;
		__COUNT_OP(&global_opcount, 1);
    }
	// If needed, allocate 1 more byte for the carry
	if(carry > 0)
	{
		a->significant_octets += 1;
		__COUNT_OP(&global_opcount, 1);
		a->octets[i] = carry;
	}	
}

void bigint_sub_inplace(BigInt a, const BigInt b)
{
	BIGINT_ASSERT_VALID(a);
	BIGINT_ASSERT_VALID(b);
	
    // Negative representation is not implemented
    assert(!bigint_is_greater(b, a));

	uint64_t count = a->significant_octets;
	uint64_t i = 0;
	uint8_t borrow = 0;
	uint8_t tmp_borrow = 0;
	char stop = 0;
		
	for (; i < count && !stop; i++)
	{
	    uint32_t atemp = (uint32_t)a->octets[i];
	    uint32_t btemp;
	    if(i < b->significant_octets)
	    {
			btemp = (uint32_t)b->octets[i];
	    }
	    else
	    {
			stop = 1;
			btemp = 0;
	    }

	    if(borrow) 
	    {
			stop = 0;
			btemp++;
	    }

	    if(btemp > atemp)
	    {
			__COUNT_OP(&global_opcount, 1);
			tmp_borrow = 1;
			atemp = atemp + 0xFF + 1;
			__COUNT_OP(&global_opcount, 2);
	    }
	    else
	    {
			tmp_borrow = 0;
	    }

	    atemp = atemp - btemp;
		__COUNT_OP(&global_opcount, 1);
	    a->octets[i] = atemp;
	    borrow = tmp_borrow;
	}

	stop = 0;
	for(int j = count - 1; j >= 0 && !stop; j--)
	{
	    if(a->octets[j] != 0) 
	    {
			a->significant_octets = j + 1;
			__COUNT_OP(&global_opcount, 1);
			stop = 1;
	    }
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
		BigInt x2 = bigint_from_uint32(BI_DIVIDE_X2_TAG, 0);
	
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
