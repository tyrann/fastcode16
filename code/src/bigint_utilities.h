
#ifndef __BIGINT_UTILITIES_H_
#define __BIGINT_UTILITIES_H_

#include "bigint.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logging/logging.h"
#include "opcount/opcount.h"

extern uint64_t global_index_count;
extern uint64_t add_opcount;

// Clear the passed BigInt object, setting its value to zero
void bigint_clear(BigInt a);

// Returns 1 if a and b represent the same number, 0 otherwise
int bigint_are_equal(const BigInt a, const BigInt b);

void bigint_print(BigInt val);
void bigint_print_prime(char *label, const BigInt val, const BigInt prime);

// Checks if a BigInt object is currently valid
#define BIGINT_ASSERT_VALID(num) \
{ \
    assert(num != 0); \
    assert(num->significant_blocks > 0); \
}

// Round an integer up to the next multiple of 4
#define ROUND_UP_MUL4(num) ((num + 3) & ~3)

// Returns 1 if a is greater than b, 0 otherwise
static inline int bigint_is_greater(const BigInt a, const BigInt b)
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
				__COUNT_OP(&add_opcount,2);
				return 1;
			}
			else if(b->blocks[i-1] > a->blocks[i-1])
			{
				__COUNT_OP(&add_opcount,2);
				return 0;
			} 

		__COUNT_OP(&global_index_count,1);
		}
		return 0;
	}
}

// Returns 1 if a is even, 0 otherwise);
static inline int bigint_is_even(const BigInt a)
{
    BIGINT_ASSERT_VALID(a);
    if((a->blocks[0] & 1) == 1)
    {
		__COUNT_OP(&global_index_count,1);
	    return 0;
    }
    return 1;
}


// Create a copy of a BigInt
static inline void bigint_copy(BigInt dest, const BigInt a)
{
	BIGINT_ASSERT_VALID(a);
    assert(dest != 0);
    
    dest->significant_blocks = a->significant_blocks;
    memcpy(dest->blocks, a->blocks, ROUND_UP_MUL4(dest->significant_blocks) * 8);
}

#endif
