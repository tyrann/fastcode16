
#ifndef __BIGINT_CONVERSION_H_
#define __BIGINT_CONVERSION_H_

// Create a BigInt object from a 32bit unsigned integer
BigInt bigint_from_uint32(uint32_t tag, uint32_t num);

// Create a BigInt object from a 64bit unsigned integer
BigInt bigint_from_uint64(uint32_t tag, uint64_t num);

// Create a BigInt object from a string containing the hexadecimal
// representation of a number
BigInt bigint_from_hex_string(uint32_t tag, const char* num);

// Create a textual hexadecimal representation of a BigInt number.
// WARNING: the returned char buffer must be deallocated by the caller
// using free(...)
char* bigint_to_hex_string(const BigInt num);

#endif