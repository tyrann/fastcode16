#include "bigint_operations.h"
#include "bigint_structure.h"
#include "bigint_conversion.h"
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
	uint32_t k = 0;
	bigint_from_uint32(res, k);

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
int bigint_is_greater(BigInt* a, BigInt* b)
{
	if(a->significant_octets > b->significant_octets)
	{
		return 1;
	}
	else if(b->significant_octets > a->significant_octets)
	{
		return 0;
	}
	else
	{
		int high_byte = a->significant_octets;
		int i;

		for (i = high_byte; i < 0; i--) 
		{
			if(a->octets[high_byte] > b->octets[high_byte])
			{
				return 1;
			} 
		}
		return 0;
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
