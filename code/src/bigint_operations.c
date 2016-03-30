
#include <stdlib.h>
#include <string.h>

#include "logging/logging.h"
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
int bigint_is_greater(const BigInt* const a, const BigInt* const b)
{
	BIGINT_ASSERT_VALID(a);
	BIGINT_ASSERT_VALID(b);
	
	uint64_t a_high = a->significant_octets;
	uint64_t b_high = b->significant_octets;

	if(a_high > b_high)
	{
		return 1;
	}
	else if(b_high > a_high)
	{
		return 0;
	}
	else
	{
		uint64_t high_byte = a_high;
		int i;

		for (i = high_byte; i > 0; --i)
		{
			if(a->octets[i-1] > b->octets[i-1])
			{
				return 1;
			}
			else if(b->octets[i-1] > a->octets[i-1])
			{
				return 0;
			} 
		}
		return 0;
	
	}
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
        LOG_DEBUG("Octet %llu (%02hhX) is shifted by one (%02hhX) and added "
            "to the carry (%hhu) resulting in %02hhX", i, a->octets[i],
            a->octets[i] << 1, cur_carry, cur_carry + (a->octets[i] << 1));
        a->octets[i] = cur_carry + (a->octets[i] << 1);
    }
    
    // Add carry to last octet if necessary
    if (carry > 0)
    {
        a->octets[original_octets] = carry;
        LOG_DEBUG("Carry (%hhu) added to octet %llu resulting in (%02hhX)",
            carry, original_octets + 1, a->octets[original_octets + 1]);
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
        LOG_DEBUG("Octet %llu (%02hhX) is shifted by one (%02hhX) and added "
            "to the carry (%hhu) resulting in %02hhX", i-1, a->octets[i-1],
            a->octets[i-1] << 1, cur_carry, cur_carry + (a->octets[i-1] << 1));
        a->octets[i-1] = cur_carry + (a->octets[i-1] >> 1);
    }
    
    // Check if the number of significant octets decreased
    if (a->octets[a->significant_octets-1] == 0 && a->significant_octets > 1)
        a->significant_octets--;
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
