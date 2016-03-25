#include <stdint.h>

#ifndef __BIGINT_H_
#define __BIGINT_H_

// Structure for big integers. Supports unsigned integres
// with value <= 2^(2^64). Only unsigned numbers are supported at the 
// moment. If signed number are required open issue to @dotPiano.
typedef struct 
{
    // The number of octets (bytes) allocated for the storing the number
    uint64_t octets_count;

    // The number of bits actually used for describing the number
    uint64_t bits_count;
   
    // Pointer to the buffer containing the octets of the number
    char* octets;
} BigInt;

// Create a BigInt object from a 32bit unsigned integer
BigInt bigint_from_uint32(uint32_t num);

// Create a BigInt object from a 64bit unsigned integer
BigInt bigint_from_uint64(uint64_t num);

// Create a BigInt object from a string containing the hexadecimal
// representation of a number
BigInt bigint_from_hex_string(const char* num);

// Create a textual hexadecimal representation of a BigInt number.
// WARNING: the returned char buffer must be deallocated by the caller
// using free(...)
char* bigint_to_hex_string(const BigInt* num);

// Add two BigInts and return the result in a new object
BigInt add(const BigInt* a, const BigInt* b);

// Multiply two BigInts and return the result in a new object
BigInt mul(const BigInt* a, const BigInt* b);

// Add two BigInts in a prime finite field Fp of size p, and return the
// result in a new object ("Addition modulo p").
BigInt add_Fp(const BigInt* a, const BigInt* b, const BigInt* p);

// Multiply two BigInts in a prime finite field Fp of size p, and return the
// result in a new object ("Multiplication modulo p").
BigInt mul_Fp(const BigInt* a, const BigInt* b, const BigInt* p);

#endif
