#include "bigint_operations.h"
#include "bigint_utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define WORDSIZE 64
#define B 2


/* void __extended_gcd(BigInt* a, BigInt* b, BigInt* u, BigInt* v)
{
	//TODO

}
void __montgomery_convert(BigInt* x, BigInt* p, BigInt* res)
{
	bigint_copy(res,x);
	/\*n is the R parameter in the Montgomery convertion*\/
	int n = WORDSIZE * 10;
	int i;
	for (i = 0; i < n; ++i)
   	{
		bigint_left_shift_inplace(res);
		if(bigint_is_greater(res,p))
		{
			bigint_sub_inplace(res,p);
		} 
	}
}

void __montgomery_revert(BigInt* x,BigInt* p, BigInt* rev)
{
	bigint_copy(rev,x);

	int n = WORDSIZE * 10;
	int i;

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

void montgomery_mul(BigInt* x, BigInt* y, BigInt* p, BigInt* res)
{
	/\* This is -p^-1 mod b*\/
	int pbar = 1;
	bigint_set_zero(res);

	int n = WORDSIZE * 10;
	int i;
	int oct;

	uint8_t y0 = y->octets[0] & 0x1;
	for (i = 0, oct = 0; i < n; ++i, oct = i/8) 
	{
		// ui <- (z0 +xi*y0)*pbar mod b
		uint8_t z0 = res->octets[0] & 0x1;
		int shift = i % oct;
		uint8_t xi = (x->octets[i] >> shift) & 0x1;
		uint64_t ui = ((z0 + xi*y0)*pbar) % B;

		//Z <- (Z + xiy + ui*p)/b
		BigInt xiy;
		BigInt uip;
		
		if(xi)
		{
			 bigint_copy(&xiy, y);
		}
		if(ui)
		{
			bigint_copy(&uip, p);
		}

		bigint_add_inplace(&xiy, &uip);
		bigint_add_inplace(res, &xiy);
		bigint_right_shift_inplace(res);
		

	}
	if(bigint_is_greater(res,p))
	{
		bigint_sub_inplace(res,p);
	}
}
*/

void bigint_add_inplace(BigInt* a, BigInt* b)
{
	BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
	uint32_t accumulator = 0;
	// count stores the minimal number of digits between a and b
	uint64_t count = (a->significant_octets > b->significant_octets) ? b->significant_octets : a->significant_octets;	
	uint64_t i = 0;
	// Execute adding
	for (; i < count; i++)
    {		
		uint32_t atemp = (uint32_t)a->octets[i];
		uint32_t btemp = (uint32_t)b->octets[i];
        accumulator = (accumulator + atemp + btemp);
		a->octets[i] = accumulator & 0xFF;	
		accumulator = accumulator>>8;		
    }
	// Extend bigint a to allocate more bytes
	if(accumulator>0)
	{
		a->significant_octets += 1;
		a->allocated_octets += 1;
		uchar* newOctets = realloc(a->octets, sizeof(uchar) * a->significant_octets);
		if (newOctets) 
		{
			a->octets = newOctets;
			a->octets[i] = 0;
		}	
	}	
	// Adds the carry to bigint a
	for (i = count; (i < a->significant_octets) && (accumulator!=0); i++)
	{
		accumulator += a->octets[i];
		a->octets[i] = accumulator & 0xFF;
		accumulator = accumulator >> 8;
	}
}


void bigint_sub_inplace(BigInt* a, BigInt* b)
{
	BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
	// count stores the minimum number of digits between a and b
	uint64_t count = (a->significant_octets > b->significant_octets) ? b->significant_octets : a->significant_octets;	
	uint64_t i = 0;
	for (; i < count; i++)
    {		
		uint32_t atemp = (uint32_t)a->octets[i];
		uint32_t btemp = (uint32_t)b->octets[i];
		int borrow = 0;
		borrow = (atemp < btemp);
		btemp = ~((uint32_t)b->octets[i])+1;
		if(borrow)
		{
			atemp = atemp + 0xFF + 1 + btemp;
			a->octets[i+1] -= 1;
		}
		else
		{
			atemp = atemp + btemp;
		}
		a->octets[i] = atemp;	
    }
	// Empty the 0 top bytes
	uint64_t emptyBytes = 0;
	int stopFlag = 0;
	for (uint64_t i = a->significant_octets; (i>0)&&(!stopFlag); i--)
	{
		if(a->octets[i]==0)
		{
			emptyBytes +=1;
		}
		else
		{
			stopFlag = 1;
		}
		
	}
	// Extend bigint a to allocate more bytes
	if(emptyBytes>0)
	{
		a->significant_octets -= emptyBytes-1;
		a->allocated_octets -= emptyBytes-1;
		uchar* newOctets = realloc(a->octets, sizeof(uchar) * a->significant_octets);
		if (newOctets) 
		{
			a->octets = newOctets;
		}	
	}	

}

int bigint_is_even(BigInt* a)
{
    BIGINT_ASSERT_VALID(a);
    if((a->octets[0] & 1) == 1)
    {
	return 0;
    }
    return 1;
}



