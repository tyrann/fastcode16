
#ifndef __BIGINT_UTILITIES_H_
#define __BIGINT_UTILITIES_H_

#include "bigint.h"
#include <assert.h>

// Clear the passed BigInt object, setting its value to zero
void bigint_clear(BigInt a);

// Returns 1 if a and b represent the same number, 0 otherwise
int bigint_are_equal(const BigInt a, const BigInt b);

// Returns 1 if a is greater than b, 0 otherwise
int bigint_is_greater(const BigInt a, const BigInt b);

// Returns 1 if a is even, 0 otherwise
int bigint_is_even(BigInt a);

// Create a copy of a BigInt
void bigint_copy(BigInt dest, const BigInt a);

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

#endif
