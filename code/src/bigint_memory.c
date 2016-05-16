#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>

#include "bigint_memory.h"

uchar* __bigint_buffer = 0;
BigInt bigint_zero;
BigInt bigint_one;
BigInt bigint_two;
BigInt bigint_three;

void __create_default_bigints()
{
    bigint_zero = GET_BIGINT_PTR(BI_COMMONS_ZERO_TAG);
    bigint_zero->significant_octets = 1;
    bigint_zero->octets[0] = 0x0;
    
    bigint_one = GET_BIGINT_PTR(BI_COMMONS_ONE_TAG);
    bigint_one->significant_octets = 1;
    bigint_one->octets[0] = 0x1;
    
    bigint_two = GET_BIGINT_PTR(BI_COMMONS_TWO_TAG);
    bigint_two->significant_octets = 1;
    bigint_two->octets[0] = 0x2;
    
    bigint_three = GET_BIGINT_PTR(BI_COMMONS_THREE_TAG);
    bigint_three->significant_octets = 1;
    bigint_three->octets[0] = 0x3;
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
    __create_default_bigints();
}

void bigint_destroy_buffer()
{
    assert(__bigint_buffer != 0);
    free(__bigint_buffer);
}