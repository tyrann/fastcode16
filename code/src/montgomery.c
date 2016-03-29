#include "montgomery.h"

#define WORDSIZE 64
#define B 2

void __extended_gcd(BigInt* a, BigInt* b, BigInt* u, BigInt* v)
{
	//TODO
	return 0;

}
void __montgomery_convert(BigInt* x, BigInt* p, BigInt* res)
{
	bigint_copy(res,x);
	/*n is the R parameter in the Montgomery convertion*/
	int n = WORDSIZE * 10;
	int i;
	for (i = 0; i < n; ++i)
   	{
		bigint_shift_left_inplace(res,1);
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
			bigint_shift_right_inplace(rev,1);
		}
		else
		{
			bigint_add_inplace(rev,p);
			bigint_shift_right_inplace(rev,1);
		}
	}
}

void montgomery_mul(BigInt* x, BigInt* y, BigInt* p, BigInt* res)
{
	/* This is -p^-1 mod b*/
	int pbar = 1;
	bigint_set_zero(res);

	int n = WORDSIZE * 10;
	int i;
	int oct;

	uint8_t z0 = res->octets[0] & 0x1;
	uint8_t y0 = y->octets[0] & 0x1;
	for (i = 0, oct = 0; i < n; ++i, oct = i/8) 
	{
		// ui <- (z0 +xi*y0)*pbar mod b
		int shift = i % oct;
		uint8_t xi = (x->octets[i] >> shift) & 0x1;
		uint64_t u = ((z0 + xi*y0)*pbar) % B;

		//Z <- (Z + xiy + ui*p)/b
		//TODO


	}
	if(bigint_is_greater(res,p))
	{
		bigint_sub_inplace(res,p);
	}
}

