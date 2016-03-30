
#ifndef __BIGINT_STRUCTURE_H_
#define __BIGINT_STRUCTURE_H_

#include <stdint.h>

typedef unsigned char uchar;

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
    uchar* octets;
} BigInt;

#endif