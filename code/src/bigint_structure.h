
#ifndef __BIGINT_STRUCTURE_H_
#define __BIGINT_STRUCTURE_H_

#include <stdint.h>
#include "bigint_constants.h"

typedef unsigned char uchar;

// Structure for big integers. Supports unsigned integres
// with value <= 2^(8*2^64). Only unsigned numbers are supported at the 
// moment.
typedef struct 
{
    // The number of octets (bytes) actually used storing the number
    uint64_t significant_octets;
    
    // Padding bytes. This guarantees the required alignment on the octets array
    #if BIGINT_HEADER_PADDING != 0
    uchar __padding[BIGINT_HEADER_PADDING];
    #endif
    
    // Pointer to the buffer containing the octets of the number
    uchar octets[BIGINT_OCTETS_COUNT];
    
} __BigInt;

typedef __BigInt* BigInt;

// Nice trick for static assertions
// http://www.pixelbeat.org/programming/gcc/static_assert.html
#define __ASSERT_CONCAT_(a, b) a##b
#define __ASSERT_CONCAT(a, b) __ASSERT_CONCAT_(a, b)
#define static_assert(e) enum { __ASSERT_CONCAT(assert_line_, __LINE__) = 1/(!!(e)) }

static_assert(sizeof(__BigInt) == BIGINT_SIZE);

#endif