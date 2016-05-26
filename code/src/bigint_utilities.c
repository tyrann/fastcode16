#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bigint.h"
#include "logging/logging.h"
#include "opcount/opcount.h"

extern uint64_t global_opcount;
extern uint64_t global_index_count;

void bigint_clear(BigInt a)
{    
    BIGINT_ASSERT_VALID(a);
    
    memset(a->blocks, 0, ROUND_UP_MUL4(a->significant_blocks) * 8);
    a->significant_blocks = 1;
}

int bigint_are_equal(const BigInt a, const BigInt b)
{
    BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
    
    // If the number of octets is different, then the
    // numbers are different
    if (a->significant_blocks != b->significant_blocks)
	{
        return 0;
	}
	
    // Check that all significant octets match
    for (uint64_t i = 0; i < a->significant_blocks; i++)
    {
        if (a->blocks[i] != b->blocks[i])
		{
            return 0;
        }
		__COUNT_OP(&global_index_count,1);
    }
    
    return 1;
}

void bigint_copy(BigInt dest, const BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    assert(dest != 0);
    
    dest->significant_blocks = a->significant_blocks;
    memcpy(dest->blocks, a->blocks, ROUND_UP_MUL4(dest->significant_blocks) * 8);
}

int bigint_is_greater(const BigInt a, const BigInt b)
{
	BIGINT_ASSERT_VALID(a);
	BIGINT_ASSERT_VALID(b);
	
	uint64_t a_high = a->significant_blocks;
	uint64_t b_high = b->significant_blocks;

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
			if(a->blocks[i-1] > b->blocks[i-1])
			{
				__COUNT_OP(&global_opcount,2);
				return 1;
			}
			else if(b->blocks[i-1] > a->blocks[i-1])
			{
				__COUNT_OP(&global_opcount,2);
				return 0;
			} 

		__COUNT_OP(&global_index_count,1);
		}
		return 0;
	}
}

int bigint_is_even(const BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    if((a->blocks[0] & 1) == 1)
    {
		__COUNT_OP(&global_index_count,1);
	    return 0;
    }
    return 1;
}

void bigint_print(BigInt val)
{
	char *val_str = bigint_to_hex_string(val);
	printf("%s\n", val_str);
	free(val_str);
}

void bigint_print_prime(char *label, const BigInt val, const BigInt prime)
{
	BigInt tmp = GET_BIGINT_PTR(BI_TEMPORARY_TAG);
	__montgomery_revert(tmp, val, prime);
	char *val_str = bigint_to_hex_string(tmp);
	printf("%s: %s\n", label, val_str);
	free(val_str);
}
