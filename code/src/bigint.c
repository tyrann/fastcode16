#include <assert.h>

#include "bigint.h"
#include "logging/logging.h"

void bigint_free(BigInt* a)
{    
    BIGINT_ASSERT_VALID(a);
    
    free(a->octets)
    a->octets = 0;
    a->allocated_octets = 0;
    a->significant_octets = 0;
}

bigint_from_uint64(BigInt* dest, uint64_t num)
{
    // Find number of octets needed
    uint64_t num_octets;
    for (num_octets = 8; num_octets > 1; num_octets--)
    {
        uint64_t octet = num & (0xFF << (8 * (num_octets - 1)));
        if (octet != 0) break;
    }
    if (i == 0) i = 1;
    
    // Create result object
    BigInt result = { 0, 0, 0 };
}

int bigint_are_equal(const BigInt* a, const BigInt* b)
{
    BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
    
    // If the number of octets is different, then the
    // numbers are different
    if (a->significant_octets != b->significant_octets)
        return false;
    
    // Check that all significant octets match
    for (uint64_t i = 0; i < a->significant_octets; i++)
    {
        if (a->octets[i] != b->octets[i])
            return false;
    }
    
    return true;
}

