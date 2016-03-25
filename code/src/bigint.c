#include <assert.h>

#include "bigint.h"
#include "logging/logging.h"

void bigint_free(BigInt* a) {
    
    BIGINT_ASSERT_VALID(a);
    
    free(a->octets)
    a->octets = 0;
    a->allocated_octets = 0;
    a->significant_octets = 0;
}

bool bigint_are_equal(const BigInt* a, const BigInt* b)
{
    BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
    
    // If the number of octets is different, then the
    // numbers are different
    if (a->significant_octets != b->significant_octets)
        return false;
    
    // Check that all significant octets match
    for (uint64_t i = 0; i < a->significant_octets)
    {
        if (a->octets[i] != b->octets[i])
            return false;
    }
    
    return true;
}