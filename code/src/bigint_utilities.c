#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bigint.h"
#include "logging/logging.h"
#include "opcount/opcount.h"

extern uint64_t global_opcount;
extern uint64_t global_index_count;

void bigint_free(BigInt* a)
{    
    BIGINT_ASSERT_VALID(a);
    
    free(a->octets);
    a->octets = 0;
    a->allocated_octets = 0;
    a->significant_octets = 0;
}

int bigint_are_equal(const BigInt* a, const BigInt* b)
{
    BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
    
    // If the number of octets is different, then the
    // numbers are different
    if (a->significant_octets != b->significant_octets)
    {
        /* LOG_DEBUG("Two BigInt are different because they have a different "
            "number of significant octets"); */
        return 0;
    }
    
    // Check that all significant octets match
    for (uint64_t i = 0; i < a->significant_octets; i++)
    {
        if (a->octets[i] != b->octets[i])
        {
            /* LOG_DEBUG("Two BigInt are different because they have different "
                "octets"); */
            return 0;
        }
	__COUNT_OP(&global_index_count,1);
    }
    
    // LOG_DEBUG("Two BigInt are equal");
    return 1;
}

void bigint_copy(BigInt* dest, const BigInt* a)
{
    BIGINT_ASSERT_VALID(a);
    assert(dest != 0);
    
    dest->allocated_octets = a->allocated_octets;
    dest->significant_octets = a->significant_octets;
    dest->octets = (uchar*)malloc(dest->allocated_octets);
    memcpy(dest->octets, a->octets, dest->allocated_octets);
}

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
				__COUNT_OP(&global_opcount,2);
				return 1;
			}
			else if(b->octets[i-1] > a->octets[i-1])
			{
				__COUNT_OP(&global_opcount,2);
				return 0;
			} 

		__COUNT_OP(&global_index_count,1);
		}
		return 0;
	
	}
}

int bigint_is_even(BigInt* a)
{
    BIGINT_ASSERT_VALID(a);
    if((a->octets[0] & 1) == 1)
    {
		__COUNT_OP(&global_index_count,1);
	    return 0;
    }
    return 1;
}
