#include "montgomery.h"

#define WORDSIZE 64

int __extended_gcd(BigInt a, BigInt b)
{
	//TODO
	return 0;

}
void __montgomery_convert(BigInt x, BigInt p, BigInt* res)
{
	bigint_copy(res,x);
	/*n is the R parameter in the Montgomery convertion*/
	int n = WORDSIZE * 10;
	int i;
	for (i = 0; i < n; ++i)
   	{
		bigint_shift_left(res,1);
		if(bigint_is_greater(res,p))
		{
			bigint_sub(res,p);
		} 
	}
}

void __montgomery_revert(BigInt x,BigInt p, BigInt* rev)
{
	bigint_copy(rev,x);

	int n = WORDSIZE * 10;
	int i;

	for (i = 0; i < n; ++i)
	{
		if(bigint_is_even(rev))
		{
			bigint_shift_right(rev,1);
		}
		else
		{
			bigint_add(rev,p);
			bigint_shift_right(rev,1);
		}
	}
}

void montgomery_mul(BigInt x, BigInt y, BigInt p, BigInt* res)
{
	//TODO	
}
