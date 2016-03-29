
#ifndef __BIGINT_CONVERSION_H_
#define __BIGINT_CONVERSION_H_

// Create a BigInt object from a 32bit unsigned integer
void bigint_from_uint32(BigInt* dest, uint32_t num);

// Create a BigInt object from a 64bit unsigned integer
void bigint_from_uint64(BigInt* dest, uint64_t num);

// Create a BigInt object from a string containing the hexadecimal
// representation of a number
void bigint_from_hex_string(BigInt* dest, const char* num);

// Create a textual hexadecimal representation of a BigInt number.
// WARNING: the returned char buffer must be deallocated by the caller
// using free(...)
char* bigint_to_hex_string(const BigInt* num);

// Checks if a BigInt object is currently valid
#define BIGINT_ASSERT_VALID(num) \
{ \
    assert(num != 0); \
    assert(num->octets != 0); \
    assert(num->allocated_octets > 0); \
    assert(num->significant_octets > 0); \
}

#endif