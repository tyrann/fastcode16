#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bigint.h"
#include "logging/logging.h"

BigInt bigint_from_uint32(uint32_t tag, uint32_t num)
{
    return bigint_from_uint64(tag, (uint64_t)num);
}

BigInt bigint_from_uint64(uint32_t tag, uint64_t num)
{
    BigInt dest = GET_BIGINT_PTR(tag);
    
    // Find number of octets needed
    uint64_t num_octets;
    for (num_octets = 8; num_octets > 1; num_octets--)
    {
        uint64_t mask = 0xFFULL << (8 * (num_octets - 1));
        uint64_t octet = num & mask;
        if (octet != 0) break;
    }
    
    // Copy the number to the allocate doctets
    dest->significant_octets = num_octets;
    for (uint64_t i = 0; i < num_octets; i++)
        dest->octets[i] = (uchar)((num >> i * 8) & 0xFFULL);
    
    return dest;
}

BigInt bigint_from_hex_string(uint32_t tag, const char* num)
{
    assert(num != 0);
    BigInt dest = GET_BIGINT_PTR(tag);
    
    // Ignore possible leading zeros
    uint64_t i = 0;
    while (num[i] != '\0' && num[i] == '0')
        i++;
    
    uint64_t prefix_digits = i;
    
    // Find the number of octets needed
    while (num[i] != '\0')
        i++;
    
    uint64_t total_digits = i;
    uint64_t significant_digits = total_digits - prefix_digits;
    uint64_t num_octets = (significant_digits + 1) / 2;
    if (num_octets == 0) num_octets = 1;
    
    // Create result object
    dest->significant_octets = num_octets;
    
    // Copy digits
    if (significant_digits == 0)
    {
        dest->octets[0] = 0;
    }
    else
    {
        uint64_t j = prefix_digits;
        char octet_string[] = "00";
        uint64_t octet_id = num_octets - 1;
        
        // In case the number of digits id odd, read the first one
        // alone
        if (significant_digits % 2 == 1)
        {
            octet_string[1] = num[j];
            dest->octets[octet_id] = (uchar)strtol(octet_string, 0, 16);
            octet_id--;
            j++;
        }
        for (; j < total_digits; j+=2)
        {
            octet_string[0] = num[j];
            octet_string[1] = num[j+1];
            dest->octets[octet_id] = (uchar)strtol(octet_string, 0, 16);
            octet_id--;
        }
    }
    
    return dest;
}

char* bigint_to_hex_string(const BigInt num)
{
    BIGINT_ASSERT_VALID(num);
    
    // Determine the number of characters necessary to store the number
    // and allocate a buffer of the same size
    uint64_t num_chars = num->significant_octets * 2;
    if (num->octets[num->significant_octets-1] <= 0x0F)
        num_chars--;
    char* result = (char*)malloc(num_chars+1);
    result[num_chars] = '\0';
        
    // Convert the octets to a string representation
    // the intermediate copy is necessary in order to avoid writing
    // the string termination character to the final string.
    uint64_t i = 0;
    char temp[] = "00";
    for (; i + 1 < num->significant_octets; i++)
    {
        sprintf((char*)temp, "%02hhX", num->octets[i]);
        strncpy(&result[num_chars-i*2-2], (char*)temp, 2);
    }
    
    // Special case for the last octet (may fit in only one char)
    if (num->octets[i] <= 0x0F)
    {
        sprintf((char*)temp, "%01hhX", num->octets[i]);
        strncpy(&result[0], (char*)temp, 1);
    }
    else
    {
        sprintf((char*)temp, "%02hhX", num->octets[i]);
        strncpy(&result[0], (char*)temp, 2);
    }
    
    return result;
}
