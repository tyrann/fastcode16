
#include <stdlib.h>
#include <string.h>

#include "logging/logging.h"
#include "bigint_operations.h"
#include "bigint_structure.h"
#include "bigint_conversion.h"
#include "bigint_utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define WORDSIZE 64
#define B 2

/* void __extended_gcd(BigInt* a, BigInt* b, BigInt* u, BigInt* v)
{
	//TODO

}
void __montgomery_convert(BigInt* x, BigInt* p, BigInt* res)
{
	bigint_copy(res,x);
	/\*n is the R parameter in the Montgomery convertion*\/
	int n = WORDSIZE * 10;
	int i;
	for (i = 0; i < n; ++i)
   	{
		bigint_left_shift_inplace(res);
		if(bigint_is_greater(res,p))
		{
			bigint_sub_inplace(res,p);
		} 
	}
}

void __montgomery_revert(BigInt* x,BigInt* p, BigInt* rev)
{
	bigint_copy(rev,x);

	int n = WORDSIZE * 10;
	int i;

	for (i = 0; i < n; ++i)
	{
		if(bigint_is_even(rev))
		{
			bigint_right_shift_inplace(rev);
		}
		else
		{
			bigint_add_inplace(rev,p);
			bigint_right_shift_inplace(rev);
		}
	}
}

void montgomery_mul(BigInt* x, BigInt* y, BigInt* p, BigInt* res)
{
	/\* This is -p^-1 mod b*\/
	int pbar = 1;
	uint32_t k = 0;
	bigint_from_uint32(res, k);

	int n = WORDSIZE * 10;
	int i;
	int oct;

	uint8_t y0 = y->octets[0] & 0x1;
	for (i = 0, oct = 0; i < n; ++i, oct = i/8) 
	{
		// ui <- (z0 +xi*y0)*pbar mod b
		uint8_t z0 = res->octets[0] & 0x1;
		int shift = i % oct;
		uint8_t xi = (x->octets[i] >> shift) & 0x1;
		uint64_t ui = ((z0 + xi*y0)*pbar) % B;

		//Z <- (Z + xiy + ui*p)/b
		BigInt xiy;
		BigInt uip;
		
		if(xi)
		{
			 bigint_copy(&xiy, y);
		}
		if(ui)
		{
			bigint_copy(&uip, p);
		}

		bigint_add_inplace(&xiy, &uip);
		bigint_add_inplace(res, &xiy);
		bigint_right_shift_inplace(res);
		

	}
	if(bigint_is_greater(res,p))
	{
		bigint_sub_inplace(res,p);
	}
}
*/
int bigint_is_greater(const BigInt* const a, const BigInt* const b)
{
	BIGINT_ASSERT_VALID(a);
	BIGINT_ASSERT_VALID(b);
	
	uint64_t a_high = a->significant_octets;
	uint64_t b_high = b->significant_octets;

	if(a_high > b_high)
	{
		return 1;
	}
	else if(b_high > a_high)
	{
		return 0;
	}
	else
	{
		uint64_t high_byte = a_high;
		int i;

		for (i = high_byte; i > 0; --i)
		{
			if(a->octets[i-1] > b->octets[i-1])
			{
				return 1;
			}
			else if(b->octets[i-1] > a->octets[i-1])
			{
				return 0;
			} 
		}
		return 0;
	
	}
}

void bigint_left_shift_inplace(BigInt* a)
{
    BIGINT_ASSERT_VALID(a);
    
    // Increase size of the buffer if necessary
    uint64_t original_octets = a->significant_octets;
    if (a->octets[a->significant_octets-1] > 0x7F)
    {
        uchar* new_octets = (uchar*)malloc(a->significant_octets + 1);
        memcpy(new_octets, a->octets, a->significant_octets);
        free(a->octets);
        
        a->octets = new_octets;
        a->significant_octets += 1;
        a->allocated_octets = a->significant_octets;
    }
    
    // Left shift octets by one, propagating the carry across octets.
    uchar carry = 0;
    for (uint64_t i = 0; i < original_octets; i++)
    {
        uchar cur_carry = carry;
        carry = a->octets[i] >> 7;
        LOG_DEBUG("Octet %llu (%02hhX) is shifted by one (%02hhX) and added "
            "to the carry (%hhu) resulting in %02hhX", i, a->octets[i],
            a->octets[i] << 1, cur_carry, cur_carry + (a->octets[i] << 1));
        a->octets[i] = cur_carry + (a->octets[i] << 1);
    }
    
    // Add carry to last octet if necessary
    if (carry > 0)
    {
        a->octets[original_octets] = carry;
        LOG_DEBUG("Carry (%hhu) added to octet %llu resulting in (%02hhX)",
            carry, original_octets + 1, a->octets[original_octets + 1]);
    }
}

void bigint_right_shift_inplace(BigInt* a)
{
    BIGINT_ASSERT_VALID(a);
    
    // Right shift octets by one, propagating the carry across octets.
    uchar carry = 0;
    for (uint64_t i = a->significant_octets; i > 0; i--)
    {
        uchar cur_carry = carry;
        carry = a->octets[i-1] << 7;
        LOG_DEBUG("Octet %llu (%02hhX) is shifted by one (%02hhX) and added "
            "to the carry (%hhu) resulting in %02hhX", i-1, a->octets[i-1],
            a->octets[i-1] << 1, cur_carry, cur_carry + (a->octets[i-1] << 1));
        a->octets[i-1] = cur_carry + (a->octets[i-1] >> 1);
    }
    
    // Check if the number of significant octets decreased
    if (a->octets[a->significant_octets-1] == 0 && a->significant_octets > 1)
        a->significant_octets--;
}

void bigint_add_inplace(BigInt* a, BigInt* b)
{
	BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);

	uint32_t carry = 0;
	uint32_t a_bytes = a->significant_octets;
	
	// Extends a if b is larger
	if(a->significant_octets < b->significant_octets)
	{
		a->significant_octets = b->significant_octets;
		a->allocated_octets = b->significant_octets;
		uchar* new_octets = realloc(a->octets, sizeof(uchar) * a->significant_octets);
		if (new_octets) 
		{
			a->octets = new_octets;
			for(uint32_t n = a_bytes; n < a->significant_octets; n++)
			{
				a->octets[n] = 0;
			}
		}			
	}
	a_bytes = a->significant_octets;
	uint64_t i = 0;
	// Execute adding and propagate carry
	for (; i < a_bytes; i++)
    {	
		uint32_t atemp;
		uint32_t btemp;
		if(i <= b->significant_octets-1)
		{
			atemp = (uint32_t)a->octets[i];
			btemp = (uint32_t)b->octets[i];
			carry = (carry + atemp + btemp);
		}
		else
		{
			atemp = (uint32_t)a->octets[i];
			carry = (carry + atemp);
		}

		a->octets[i] = carry & 0xFF;	
		carry = carry>>8;		
    }
	// If needed, allocate 1 more byte for the carry
	if(carry > 0)
	{
		a->significant_octets += 1;
		a->allocated_octets += 1;
		uchar* newOctets = realloc(a->octets, sizeof(uchar) * a->significant_octets);
		if (newOctets) 
		{
			a->octets = newOctets;
			a->octets[i] = carry;
		}	
	}	
}


void bigint_sub_inplace(BigInt* a, BigInt* b)
{
	// Negative representation is not implemented
	if(bigint_is_greater(b,a))
	{
		printf("! a < b ");
	} 
	else 
	{
	BIGINT_ASSERT_VALID(a);
    BIGINT_ASSERT_VALID(b);

	// count stores the minimum number of digits between a and b
	uint64_t count = (a->significant_octets > b->significant_octets) ? b->significant_octets : a->significant_octets;	
	uint64_t i = 0;
	uint8_t back_carry;
	uint8_t next_back_carry;
   	// next_back_carry is created to handle cases where back_carry is needed for i,  yet the both i+1 and i+2 bytes are zeros
	// Execute the sub from the lowest digits to the digits of count
	for (; i < count; i++)
    {
		uint32_t atemp = (uint32_t)a->octets[i];
		uint32_t btemp = (uint32_t)b->octets[i];
		back_carry = 0;
		back_carry = (atemp < btemp);

		// Two-complement is stored in btemp
		btemp = ~((uint32_t)b->octets[i])+1;
		
		if(back_carry || next_back_carry)
		{
			
			// If possible get a unit from the byte above
			if ((uint32_t)a->octets[i+1]!=0) 
			{
				a->octets[i+1] -= 1;
			}	
			// Else we need to look further up
			else
			{
				a->octets[i+1] = 0xFF;
				next_back_carry = 1;
			}				
		}
		atemp = atemp + btemp;
		a->octets[i] = atemp;	
    }
	
	// We might need to keep retrieving a unit until we reach a non-zero byte 
	int stopFlag = 0;
	i=i+1;
	if(back_carry || next_back_carry)
	{
	for (; (i < a->significant_octets)&&(!stopFlag); i++)
    {
		if ((uint32_t)a->octets[i] == 0)
		{
			a->octets[i] = 0xFF;
		}
		else 
		{
			a->octets[i] -= 1;
			stopFlag = 1; 
		}
    }
    }
	// Empty higher significant bytes that are zeros 
	uint64_t emptyBytes = 0;
	stopFlag = 0;
	for (uint64_t i = a->significant_octets-1; (i>0)&&(!stopFlag); i--)
	{
		if((uint32_t)a->octets[i]==0)
		{
			emptyBytes +=1;
		}
		else
		{
			stopFlag = 1;
		}
	}
	// Deallocate most significant bytes that are zero 
	if(emptyBytes > 0)
	{
		a->significant_octets -= emptyBytes;
		a->allocated_octets -= emptyBytes;
		uchar* newOctets = realloc(a->octets, sizeof(uchar) * a->significant_octets);
		if (newOctets) 
		{
			a->octets = newOctets;
		}	
	}	
	}
}

int bigint_is_even(BigInt* a)
{
    BIGINT_ASSERT_VALID(a);
    if((a->octets[0] & 1) == 1)
    {
	return 0;
    }
    return 1;
}
