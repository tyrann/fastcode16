
#ifndef __BIGINT_UTILITIES_H_
#define __BIGINT_UTILITIES_H_

#include "bigint.h"

// Release the octets buffer of a number. This frees up memory, but
// using the number results invalid afterwards 
void bigint_free(BigInt* a);

// Returns 1 if a and b represent the same number, 0 otherwise
int bigint_are_equal(const BigInt* a, const BigInt* b);

// Create a copy of a BigInt
void bigint_copy(BigInt* dest, const BigInt* a);

// Checks if a BigInt object is currently valid
#define BIGINT_ASSERT_VALID(num) \
{ \
    assert(num != 0); \
    assert(num->octets != 0); \
    assert(num->allocated_octets > 0); \
    assert(num->significant_octets > 0); \
}

#endif