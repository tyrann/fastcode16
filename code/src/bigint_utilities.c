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


void bigint_print(BigInt val)
{
	char *val_str = bigint_to_hex_string(val);
	printf("%s\n", val_str);
	free(val_str);
}

void bigint_print_prime(char *label, const BigInt val, const BigInt prime)
{
	BigInt tmp = GET_BIGINT_PTR(BI_BIGINT_PRINT_PRIME_TAG);
	__montgomery_revert(tmp, val, prime);
	char *val_str = bigint_to_hex_string(tmp);
	printf("%s: %s\n", label, val_str);
	free(val_str);
}
