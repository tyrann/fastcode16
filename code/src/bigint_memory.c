#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "bigint_memory.h"

block* __bigint_buffer = 0;
block* __bigint__precomputation_buffer = 0;
BigInt bigint_zero;
BigInt bigint_one;
BigInt bigint_two;
BigInt bigint_three;

void __create_default_bigints()
{
    bigint_zero = GET_BIGINT_PTR(BI_COMMONS_ZERO_TAG);
    bigint_zero->significant_blocks = 1;
    bigint_zero->blocks[0] = 0x0;
    
    bigint_one = GET_BIGINT_PTR(BI_COMMONS_ONE_TAG);
    bigint_one->significant_blocks = 1;
    bigint_one->blocks[0] = 0x1;
    
    bigint_two = GET_BIGINT_PTR(BI_COMMONS_TWO_TAG);
    bigint_two->significant_blocks = 1;
    bigint_two->blocks[0] = 0x2;
    
    bigint_three = GET_BIGINT_PTR(BI_COMMONS_THREE_TAG);
    bigint_three->significant_blocks = 1;
    bigint_three->blocks[0] = 0x3;
}

void bigint_create_buffer()
{
    int res = posix_memalign(
        (void**)&__bigint_buffer,
        BIGINT_ALIGNMENT,
        BI_TAGS_COUNT * BIGINT_SIZE);

    if (res == 0)
    {
        assert("posix_memalign failed!");
    }
    assert(__bigint_buffer != 0);

    memset(__bigint_buffer, 0, BI_TAGS_COUNT * BIGINT_SIZE);

	res = posix_memalign(
		(void**)&__bigint__precomputation_buffer,
		BIGINT_ALIGNMENT,
		MAX_NUMBER_OF_POINTS * 3 * BIGINT_SIZE);

	if (res == 0)
	{
		assert("posix_memalign failed!");
	}
	assert(__bigint__precomputation_buffer != 0);

	memset(__bigint__precomputation_buffer, 0, MAX_NUMBER_OF_POINTS * 3 * BIGINT_SIZE);

    __create_default_bigints();
}

void bigint_destroy_buffer()
{
    assert(__bigint_buffer != 0);
    free(__bigint_buffer);
    assert(__bigint__precomputation_buffer != 0);
    free(__bigint__precomputation_buffer);
}

BigInt get_precomputed_bigint(unsigned int i)
{
	return (BigInt)(__bigint__precomputation_buffer + (i * (BIGINT_SIZE / 8)));
}
