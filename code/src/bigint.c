#include <assert.h>

#include "bigint.h"
#include "logging/logging.h"

#define ASSERT_VALID_BIGINT(num) \
{ \
    assert(num != 0); \
    assert(num->octets != 0); \
    assert(num->allocated_octets > 0); \
    assert(num->significant_octets > 0); \
}

void bigint_free(BigInt* a) {
    
    ASSERT_VALID_BIGINT(a);
    
    free(a->octets)
    a->octets = 0;
    a->allocated_octets = 0;
    a->significant_octets = 0;
}

bool bigint_are_equal(const BigInt* a, const BigInt* b)
{
    ASSERT_VALID_BIGINT(a);
    ASSERT_VALID_BIGINT(b);
    
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