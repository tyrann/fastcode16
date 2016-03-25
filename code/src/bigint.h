#include <stdint.h>

// Structure for big integers. Supports unsigned integres
// with value <= 2^(8*2^64). Only unsigned numbers are supported at the 
// moment. If signed number are required open issue to @dotPiano.
typedef struct 
{
    // The number of octets (bytes) allocated for the storing the number
    uint64_t allocated_octets;

    // The number of octets (bytes) actually used storing the number
    uint64_t significant_octets;

    // Pointer to the buffer containing the octets of the number
    char* octets;
} BigInt;

// Release the octets buffer of a number. This frees up memory, but
// using the number results invalid afterwards 
void bigint_free(BigInt* a);

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

// Returns trure is a and b represent the same number, false otherwise
bool bigint_are_equal(const BigInt* a, const BigInt* b);

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