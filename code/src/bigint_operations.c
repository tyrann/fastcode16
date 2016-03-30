#include "bigint_operations.h"
#include "bigint_utilities.h"

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
	uchar accumulator = 0;
	// count stores the minimal number of digits between a and b
	uint64_t count = (a->significant_octets > b->significant_octets) ? b->significant_octets : a->significant_octets;	
	uint64_t i = 0;
	for (; i < count; i++)
    {
        accumulator = accumulator + a->octets[i] + b->octets[i];
		b->octets[i] = accumulator & 0xFF;
		accumulator = accumulator >> 8;
    }
	
	for (i = count; (i < b->significant_octets) && (accumulator!=0); i++)
	{
		accumulator += b->octets[i];
		b->octets[i] = accumulator & 0xFF;
		accumulator = accumulator >> 8;
	}
}


void bigint_sub_inplace(BigInt* a, BigInt* b)
{
	BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
	// negation of b 
	for (unsigned int i = 0; i < b->significant_octets; i++)
    {
		b->octets[i] = b->octets[i] & 0xFF;
    }
	// add 1 to the end of b 
    BigInt c;	
	bigint_from_uint64(&c, 1);
	bigint_add_inplace(&c, b);
	bigint_add_inplace(a, b);
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



