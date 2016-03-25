#include <assert.h>
#include <stdlib.h>

#include "bigint.h"
#include "logging/logging.h"

void bigint_free(BigInt* a)
{    
    BIGINT_ASSERT_VALID(a);
    
    free(a->octets)
    a->octets = 0;
    a->allocated_octets = 0;
    a->significant_octets = 0;
}

void bigint_from_uint32(BigInt* dest, uint32_t num)
{
    bigint_from_uint64(dest, (uint64_t)num);
}

void bigint_from_uint64(BigInt* dest, uint64_t num)
{
    // Find number of octets needed
    uint64_t num_octets;
    for (num_octets = 8; num_octets > 1; num_octets--)
    {
        uint64_t octet = num & (0xFF << (8 * (num_octets - 1)));
        if (octet != 0) break;
    }
    
    // Create result object
    dest->allocated_octets = num_octets;
    dest->significant_octets = num_octets;
    dest->octets = (char*)malloc(sizeof(char) * num_octets);
    assert(dest->octets != 0);
    
    // Copy the number to the allocate doctets
    for (uint64_t i = 0; i < num_octets; i++)
    {
        dest->octets[i] = (char)((num >> i * 8) & 0xFF);
    }
}

void bigint_from_hex_string(BigInt* dest, const char* num)
{
    assert(num != 0);
    
    // Ignore possible leading zeros
    uint64_t i = 0;
    uint64_t prefix_digits = 0;
    while (num[i] != '\0' && num[i] == '0')
    {
        prefix_digits++;
        i++;
    }
    
    // Find the number of octets needed
    uint64_t digits = 0;
    while (num[i] != '\0')
    {
        digits++;
        i++;
    }
    uint64_t num_octets = (digits + 1) / 2;
    
    // Create result object
    dest->allocated_octets = num_octets;
    dest->significant_octets = num_octets;
    dest->octets = (char*)malloc(sizeof(char) * num_octets);
    assert(dest->octets != 0);
    
    // Copy digits
}

int bigint_are_equal(const BigInt* a, const BigInt* b)
{
    BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);
    
    // If the number of octets is different, then the
    // numbers are different
    if (a->significant_octets != b->significant_octets)
        return false;
    
    // Check that all significant octets match
    for (uint64_t i = 0; i < a->significant_octets; i++)
    {
        if (a->octets[i] != b->octets[i])
            return false;
    }
    
    return true;
}