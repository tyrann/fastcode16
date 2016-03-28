#include <assert.h>
#include <stdlib.h>

#include "bigint.h"
#include "logging/logging.h"

void bigint_free(BigInt* a)
{    
    BIGINT_ASSERT_VALID(a);
    
    free(a->octets);
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
    LOG_DEBUG("Converting number: %#18llX", num);
    for (num_octets = 8; num_octets > 1; num_octets--)
    {
        uint64_t mask = 0xFFULL << (8 * (num_octets - 1));
        LOG_DEBUG("Mask = %#18llX", mask);
        uint64_t octet = num & mask;
        LOG_DEBUG("Octet = %#18llX", octet);
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
        dest->octets[i] = (char)((num >> i * 8) & 0xFFULL);
    }
}

void bigint_from_hex_string(BigInt* dest, const char* num)
{
    assert(num != 0);
    
    // Ignore possible leading zeros
    uint64_t i = 0;
    while (num[i] != '\0' && num[i] == '0')
    {
        i++;
    }
    uint64_t prefix_digits = i;
    
    // Find the number of octets needed
    while (num[i] != '\0')
    {
        i++;
    }
    uint64_t total_digits = i;
    uint64_t significant_digits = total_digits - prefix_digits;
    uint64_t num_octets = (significant_digits + 1) / 2;
    if (num_octets == 0) num_octets = 1;
    
    // Create result object
    dest->allocated_octets = num_octets;
    dest->significant_octets = num_octets;
    dest->octets = (char*)malloc(sizeof(char) * num_octets);
    assert(dest->octets != 0);
    
    // Copy digits
    if (significant_digits == 0)
    {
        dest->octets[0] = 0;
    }
    else
    {
        uint64_t j = prefix_digits;
        char octet_string[] = "00";
        uint64_t octet_id = 0;
        
        // In case the number of digits id odd, read the first one
        // alone
        if (significant_digits % 2 == 1)
        {
            octet_string[1] = num[j];
            dest->octets[octet_id] = (char)strtol(octet_string, 0, 16);
            octet_id++;
            j++;
        }
        for (; j < total_digits; j+=2)
        {
            octet_string[0] = num[j];
            octet_string[1] = num[j+1];
            dest->octets[octet_id] = (char)strtol(octet_string, 0, 16);
            octet_id++;
        }
    }
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