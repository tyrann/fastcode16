
#ifndef __BIGINT_OPERATIONS_H_
#define __BIGINT_OPERATIONS_H_

#include "bigint.h"

/* Checks if GCD of a and b is equal to 1*/
//void __extended_gcd(BigInt* a, BigInt* b, BigInt* u, BigInt* v);

//void __montgomery_convert(BigInt* x, BigInt* p, BigInt* res);

//void __montgomery_revert(BigInt* x, BigInt* p, BigInt* rev);

/* Computes the fast Montgomery mutliplication
 * Input:
 *		3 large integer x and y and p
 * Output:
 *		Stores the result of x*y mod p in res
 */
//void montgomery_mul(BigInt* x, BigInt* y, BigInt* p, BigInt* res);

void bigint_left_shift_inplace(BigInt* a);

void bigint_right_shift_inplace(BigInt* a);

void bigint_add_inplace(BigInt* a, BigInt* b);

void bigint_sub_inplace(BigInt* a, BigInt* b);

//void bigint_mul_inplace(BigInt* a, BigInt* b);

void bigint_modulo_inplace(BigInt* a, BigInt* mod);

// Compute b/a over Fp, storing the result in dest.
void bigint_divide(BigInt* dest, BigInt* b, BigInt* a, BigInt* p);

#endif
