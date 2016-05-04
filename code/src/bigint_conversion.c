#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bigint.h"
#include "logging/logging.h"

void bigint_from_uint32(BigInt* dest, uint32_t num)
{
    bigint_from_uint64(dest, (uint64_t)num);
}

void bigint_from_uint64(BigInt* dest, uint64_t num)
{
    // Find number of octets needed
    uint64_t num_octets;
    // LOG_DEBUG("Converting number: %#llX", num);
    for (num_octets = 8; num_octets > 1; num_octets--)
    {
        uint64_t mask = 0xFFULL << (8 * (num_octets - 1));
        // LOG_DEBUG("Mask = %#llX", mask);
        uint64_t octet = num & mask;
        // LOG_DEBUG("Octet = %#llX", octet);
        if (octet != 0) break;
    }
    
    // Create result object
    dest->allocated_octets = num_octets;
    dest->significant_octets = num_octets;
    dest->octets = (uchar*)malloc(sizeof(uchar) * num_octets);
    assert(dest->octets != 0);
    
    // Copy the number to the allocate doctets
    for (uint64_t i = 0; i < num_octets; i++)
    {
        dest->octets[i] = (uchar)((num >> i * 8) & 0xFFULL);
    }
}

void bigint_from_hex_string(BigInt* dest, const char* num)
{
    assert(num != 0);
    // LOG_DEBUG("Converting number: %s", num);
    
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
    
    /* LOG_DEBUG("Found %llu digits (%llu prefix, %llu significant). "
        "Number requires %llu octets.", total_digits, prefix_digits,
        significant_digits, num_octets);*/
    
    // Create result object
    dest->allocated_octets = num_octets;
    dest->significant_octets = num_octets;
    dest->octets = (uchar*)malloc(sizeof(uchar) * num_octets);
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
        uint64_t octet_id = num_octets - 1;
        
        // In case the number of digits id odd, read the first one
        // alone
        if (significant_digits % 2 == 1)
        {
            octet_string[1] = num[j];
            dest->octets[octet_id] = (uchar)strtol(octet_string, 0, 16);
            /*LOG_DEBUG("Octet %llu (%#hhX) parsed from string %s.",
                octet_id, dest->octets[octet_id], octet_string);*/
            octet_id--;
            j++;
        }
        for (; j < total_digits; j+=2)
        {
            octet_string[0] = num[j];
            octet_string[1] = num[j+1];
            dest->octets[octet_id] = (uchar)strtol(octet_string, 0, 16);
            /*LOG_DEBUG("Octet %llu (%#hhX) parsed from string %s.",
                octet_id, dest->octets[octet_id], octet_string);*/
            octet_id--;
        }
    }
}

char* bigint_to_hex_string(const BigInt* num)
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
       /* LOG_DEBUG("Octet %llu (%02hhX) copied to chars %llu-%llu",
            i, num->octets[i], num_chars-i*2-2, num_chars-i*2-1);*/
    }
    
    // Special case for the last octet (may fit in only one char)
    if (num->octets[i] <= 0x0F)
    {
        sprintf((char*)temp, "%01hhX", num->octets[i]);
        strncpy(&result[0], (char*)temp, 1);
        /*LOG_DEBUG("Octet %llu (%01hhX) copied to char %llu",
            i, num->octets[i], 0ULL);*/
    }
    else
    {
        sprintf((char*)temp, "%02hhX", num->octets[i]);
        strncpy(&result[0], (char*)temp, 2);
        /*LOG_DEBUG("Octet %llu (%02hhX) copied to chars %llu-%llu",
            i, num->octets[i], 0ULL, 1ULL);*/
    }
    
    /*LOG_DEBUG("%llu octets converted to %llu characters, generating the "
        "string '%s'", num->significant_octets, num_chars, result);*/
    return result;
}
