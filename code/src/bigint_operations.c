
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

/* void __extended_gcd(BigInt* a, BigInt* b, BigInt* u, BigInt* v)
{
	//TODO

}*/
void __montgomery_convert(BigInt* res, BigInt* x, BigInt* p)
{
	bigint_copy(res,x);
	/*n is the R parameter in the Montgomery convertion*/

	uint64_t n = p->significant_octets * 8;
	uint64_t i;
    
	for (i = 0; i < n; ++i)
   	{
		bigint_left_shift_inplace(res);
		if(bigint_is_greater(res,p))
		{
			bigint_sub_inplace(res,p);
		} 
	}
}

void __montgomery_revert(BigInt* rev, BigInt* x,BigInt* p)
{
	bigint_copy(rev,x);

	uint64_t n = p->significant_octets * 8;
	uint64_t i;

	for (i = 0; i < n; ++i)
	{
		if(bigint_is_even(rev))
		{
			bigint_right_shift_inplace(rev);
		}
		else
		{
			bigint_add_inplace(rev,p);
			bigint_right_shift_inplace(rev);
		}
	}
}

void montgomery_mul(BigInt* res, BigInt* x, BigInt* y, BigInt* p)
{
	BigInt x_mont;
	BigInt y_mont;

	__montgomery_convert(&x_mont,x,p);
	__montgomery_convert(&y_mont,y,p);

	/* This is -p^-1 mod b*/
	int pbar = -1;

	/*Set res to 0*/
	uint32_t k = 0;
	bigint_from_uint32(res,k);

	/*We take the smallest power of 2 that is bigger than p*/
	int n = p->significant_octets * 8;
	int i;

	uint8_t y0 = y_mont.octets[0] & 0x1;
	for (i = 0; i < n; ++i) 
	{
		// ui <- (z0 +xi*y0)*pbar mod b
		uint8_t z0 = res->octets[0] & 0x1;
		uint8_t xi = (x_mont.octets[0]) & 0x1;
		bigint_right_shift_inplace(&x_mont);		
		uint64_t ui = ((z0 + xi*y0)*pbar) % B;

		//Z <- (Z + xiy + ui*p)/b
		
		if(xi)
		{
			bigint_add_inplace(res, &y_mont);
		}
		if(ui)
		{
			bigint_add_inplace(res, p);
		}

		bigint_right_shift_inplace(res);
		

	}
	if(bigint_is_greater(res,p))
	{
		bigint_sub_inplace(res,p);
	}
	bigint_free(&x_mont);
	bigint_free(&y_mont);
}


void bigint_left_shift_inplace(BigInt* a)
{
    BIGINT_ASSERT_VALID(a);
    
    // Increase size of the buffer if necessary
    uint64_t original_octets = a->significant_octets;
    if (a->octets[a->significant_octets-1] > 0x7F)
    {
        uchar* new_octets = (uchar*)malloc(a->significant_octets + 1);
        memcpy(new_octets, a->octets, a->significant_octets);
        free(a->octets);
        
        a->octets = new_octets;
        a->significant_octets += 1;
        a->allocated_octets = a->significant_octets;
    }
    
    // Left shift octets by one, propagating the carry across octets.
    uchar carry = 0;
    for (uint64_t i = 0; i < original_octets; i++)
    {
        uchar cur_carry = carry;
        carry = a->octets[i] >> 7;
		__COUNT_OP(&global_opcount);
        /*LOG_DEBUG("Octet %llu (%02hhX) is shifted by one (%02hhX) and added "
            "to the carry (%hhu) resulting in %02hhX", i, a->octets[i],
            a->octets[i] << 1, cur_carry, cur_carry + (a->octets[i] << 1));*/
        a->octets[i] = cur_carry + (a->octets[i] << 1);
    }
    
    // Add carry to last octet if necessary
    if (carry > 0)
    {
        a->octets[original_octets] = carry;
        /*LOG_DEBUG("Carry (%hhu) added to octet %llu resulting in (%02hhX)",
            carry, original_octets + 1, a->octets[original_octets + 1]);*/
    }
}

void bigint_right_shift_inplace(BigInt* a)
{
    BIGINT_ASSERT_VALID(a);
    
    // Right shift octets by one, propagating the carry across octets.
    uchar carry = 0;
    for (uint64_t i = a->significant_octets; i > 0; i--)
    {
        uchar cur_carry = carry;
        carry = a->octets[i-1] << 7;
        /*LOG_DEBUG("Octet %llu (%02hhX) is shifted by one (%02hhX) and added "
            "to the carry (%hhu) resulting in %02hhX", i-1, a->octets[i-1],
            a->octets[i-1] << 1, cur_carry, cur_carry + (a->octets[i-1] << 1));*/
        a->octets[i-1] = cur_carry + (a->octets[i-1] >> 1);
    }
    
    // Check if the number of significant octets decreased
    if (a->octets[a->significant_octets-1] == 0 && a->significant_octets > 1)
        a->significant_octets--;
}

void bigint_modulo_inplace(BigInt* a, BigInt* mod)
{
	BigInt test;
	bigint_from_uint32(&test,0);

	if(bigint_are_equal(&test,mod))
	{
		printf("Impossible to apply mod 0");
	}
	bigint_free(&test);	

	if(bigint_is_greater(mod,a))
	{
		return;
	}
	else
	{
		while(bigint_is_greater(a,mod))
		{
			bigint_sub_inplace(a,mod);
		}
	}
}

void bigint_add_inplace(BigInt* a, BigInt* b)
{
	BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);

	uint32_t carry = 0;
	uint32_t a_bytes = a->significant_octets;
	
	// Extends a if b is larger
	if(a->significant_octets < b->significant_octets)
	{
		a->significant_octets = b->significant_octets;
		a->allocated_octets = b->significant_octets;
		uchar* new_octets = realloc(a->octets, sizeof(uchar) * a->significant_octets);
		if (new_octets) 
		{
			a->octets = new_octets;
			for(uint32_t n = a_bytes; n < a->significant_octets; n++)
			{
				a->octets[n] = 0;
			}
		}			
	}
	a_bytes = a->significant_octets;
	uint64_t i = 0;
	// Execute adding and propagate carry
	for (; i < a_bytes; i++)
    {	
		uint32_t atemp;
		uint32_t btemp;
		if(i <= b->significant_octets-1)
		{
			atemp = (uint32_t)a->octets[i];
			btemp = (uint32_t)b->octets[i];
			carry = (carry + atemp + btemp);
		}
		else
		{
			atemp = (uint32_t)a->octets[i];
			carry = (carry + atemp);
		}

		a->octets[i] = carry & 0xFF;	
		carry = carry>>8;		
    }
	// If needed, allocate 1 more byte for the carry
	if(carry > 0)
	{
		a->significant_octets += 1;
		a->allocated_octets += 1;
		uchar* newOctets = realloc(a->octets, sizeof(uchar) * a->significant_octets);
		if (newOctets) 
		{
			a->octets = newOctets;
			a->octets[i] = carry;
		}	
	}	
}


void bigint_sub_inplace(BigInt* a, BigInt* b)
{
    // Negative representation is not implemented
    if(bigint_is_greater(b,a))
    {
	printf("! a < b ");
    } 
    else 
    {
	BIGINT_ASSERT_VALID(a);
	BIGINT_ASSERT_VALID(b);

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
		tmp_borrow = 1;
		atemp = atemp + 0xFF + 1;
	    }
	    else
	    {
		tmp_borrow = 0;
	    }

	    atemp = atemp - btemp;
	    a->octets[i] = atemp;
	    borrow = tmp_borrow;
	}

	char reallocate = 0;
	stop = 0;
	for(int j = count - 1; j >= 0 && !stop; j--)
	{
	    if(a->octets[j] != 0) 
	    {
		a->significant_octets = j + 1;
		stop = 1;
	    }
	    else
	    {
		reallocate = 1;
	    }
	}

	if(reallocate)
	{
	    a->allocated_octets += a->significant_octets;
	    uchar* newOctets = realloc(a->octets, sizeof(uchar) * a->significant_octets);
	    if (newOctets) 
	    {
		a->octets = newOctets;
	    }
	}
    }
}

/*

// Implementation not completed, appearently this is unnecessary

// Based on algorithm 14.61 and note 14.64 of /doc/handbook_crypto.pdf
void __binary_extended_gcd(BigInt* a, BigInt* b, BigInt* v, BigInt* x, BigInt* y)
{
	// 1)
	BigInt g;
	bigint_from_uint32(&g, 1);
	
	// 2)
	while (bigint_is_even(x) && bigint_is_even(y))
	{
		bigint_right_shift_inplace(x);
		bigint_right_shift_inplace(y);
		bigint_left_shift_inplace(&g);
	}
	
	// 3)
	BigInt u, A, B, C, D;
	bigint_copy(&u, &x);
	bigint_copy(v, &y);
	bigint_from_uint32(&A, 1);
	bigint_from_uint32(&B, 0);
	bigint_from_uint32(&C, 0);
	bigint_from_uint32(&D, 1);
	
	// 4)
	int pos_B = 1;
	while (bigint_is_even(&u))
	{
		// 4.1)
		bigint_right_shift_inplace(&u);
		
		// 4.2)
		if (bigint_is_even(&A) && bigint_is_even(&B))
		{
			bigint_right_shift_inplace(&A);
			bigint_right_shift_inplace(&B);
		}
		else
		{
			bigint_add_inplace(&A, &y);
			bigint_right_shift_inplace(&A);
			
			// Trick for handling negative numbers
			if (pos_B)
			{
				if (bigint_is_greater(x, &B))
				{
					BigInt tB;
					bigint_copy(&tB, x);
					bigint_sub_inplace(&tB, &B);
					bigint_copy(&B, &tB)
					bigint_free(&tB);
					pos_B = 0;
				}
				else
				{
					bigint_sub_inplace(&B, x);
				}
			}
			else
			{
				bigint_add_inplace(&B, x);
			}
			bigint_right_shift_inplace(&B);
		}
	}
	
	// 5)
	int pos_D = 1;
	while (bigint_is_even(v))
	{
		// 5.1)
		bigint_right_shift_inplace(v);
		
		// 5.2)
		if (bigint_is_even(&C) && bigint_is_even(&D))
		{
			bigint_right_shift_inplace(&C);
			bigint_right_shift_inplace(&D);
		}
		else
		{
			bigint_add_inplace(&C, &y);
			bigint_right_shift_inplace(&C);
			
			// Trick for handling negative numbers
			if (pos_D)
			{
				if (bigint_is_greater(x, &D))
				{
					BigInt tD;
					bigint_copy(&tD, x);
					bigint_sub_inplace(&tD, &D);
					bigint_copy(&D, &tD)
					bigint_free(&tD);
					pos_D = 0;
				}
				else
				{
					bigint_sub_inplace(&D, x);
				}
			}
			else
			{
				bigint_add_inplace(&D, x);
			}
			bigint_right_shift_inplace(&D);
		}
	}
	
	// 6)
	if (bigint_is_greater(&v, &u))
	{
		bigint_sub_inplace(v, &u);
		
	}
}*/

// Based on algorithm 2.22 of doc/fields_arithmetic.pdf
void bigint_divide(BigInt* dest, BigInt* b, BigInt* a, BigInt* p)
{
	LOG_DEBUG("Performing division...");
	
	#ifndef NDEBUG
	BigInt zero;
	bigint_from_uint32(&zero, 0);
	assert(!bigint_are_equal(&zero, a));
	assert(!bigint_are_equal(&zero, b));
	#endif
	
	// 1)
	BigInt u, v;
	bigint_copy(&u, a);
	bigint_copy(&v, p);
	
	// 2)
	BigInt x1, x2;
	bigint_copy(&x1, b);
	bigint_from_uint32(&x2, 0);
	
	// 3)
	BigInt one;
	bigint_from_uint32(&one, 1);
	while (!bigint_are_equal(&u, &one) && !bigint_are_equal(&v, &one))
	{
		// 3.1)
		while (bigint_is_even(&u))
		{
			bigint_right_shift_inplace(&u);
			if (!bigint_is_even(&x1))
				bigint_add_inplace(&x1, p);
			bigint_right_shift_inplace(&x1);
		}
		
		// 3.2)
		while (bigint_is_even(&v))
		{
			bigint_right_shift_inplace(&v);
			if (!bigint_is_even(&x2))
				bigint_add_inplace(&x2, p);
			bigint_right_shift_inplace(&x2);
		}
		
		// 3.3
		if (bigint_is_greater(&v, &u))
		{
			bigint_sub_inplace(&v, &u);
			if (bigint_is_greater(&x1, &x2))
				bigint_add_inplace(&x2, p);
			bigint_sub_inplace(&x2, &x1);
		}
		else
		{
			bigint_sub_inplace(&u, &v);
			if(bigint_is_greater(&x2, &x1))
				bigint_add_inplace(&x1, p);
			bigint_sub_inplace(&x1, &x2);
		}
	}
	
	// 4)
	if (bigint_are_equal(&u, &one))
		bigint_copy(dest, &x1);
	else
		bigint_copy(dest, &x2);
}
