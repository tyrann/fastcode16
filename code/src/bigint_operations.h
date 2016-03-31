#include "bigint.h"

/* Checks if GCD of a and b is equal to 1*/
//void __extended_gcd(BigInt* a, BigInt* b, BigInt* u, BigInt* v);

void __montgomery_convert(BigInt* x, BigInt* p, BigInt* res);

void __montgomery_revert(BigInt* x, BigInt* p, BigInt* rev);

/* Computes the fast Montgomery mutliplication
 * Input:
 *		3 large integer x and y and p
 * Output:
 *		Stores the result of x*y mod p in res
 */
void montgomery_mul(BigInt* x, BigInt* y, BigInt* p, BigInt* res);

int bigint_is_even(BigInt* a);

void bigint_left_shift_inplace(BigInt* a);

void bigint_right_shift_inplace(BigInt* a);

//void bigint_add_inplace(BigInt* a, BigInt* b);

//void bigint_mul_inplace(BigInt* a, BigInt* b);

int bigint_is_greater(const BigInt* const a, const BigInt* const b);

//int bigint_is_equal(BigInt* a,BigInt* b);

//void bigint_sub_inplace(BigInt* a, BigInt* b);
