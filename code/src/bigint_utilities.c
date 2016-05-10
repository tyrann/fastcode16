#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bigint.h"
#include "logging/logging.h"

void bigint_clear(BigInt a)
{    
    BIGINT_ASSERT_VALID(a);
    
    memset(a->octets, 0, a->significant_octets);
    a->significant_octets = 1;
}

int bigint_are_equal(const BigInt a, const BigInt b)
{
    BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
    
    // If the number of octets is different, then the
    // numbers are different
    if (a->significant_octets != b->significant_octets)
        return 0;
    
    // Check that all significant octets match
    for (uint64_t i = 0; i < a->significant_octets; i++)
    {
        if (a->octets[i] != b->octets[i])
            return 0;
    }
    
    return 1;
}

void bigint_copy(BigInt dest, const BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    assert(dest != 0);
    
    dest->significant_octets = a->significant_octets;
    memcpy(dest->octets, a->octets, dest->significant_octets);
}

int bigint_is_greater(const BigInt a, const BigInt b)
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

int bigint_is_even(const BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    if((a->octets[0] & 1) == 1)
    {
	    return 0;
    }
    return 1;
}