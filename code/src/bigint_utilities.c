#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bigint.h"
#include "logging/logging.h"

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
        LOG_DEBUG("Two BigInt are different because they have a different "
            "number of significant octets");
        return 0;
    }
    
    // Check that all significant octets match
    for (uint64_t i = 0; i < a->significant_octets; i++)
    {
        if (a->octets[i] != b->octets[i])
        {
            LOG_DEBUG("Two BigInt are different because they have different "
                "octets");
            return 0;
        }
    }
    
    LOG_DEBUG("Two BigInt are equal");
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