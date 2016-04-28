
#ifndef __BIGINT_OPERATIONS_H_
#define __BIGINT_OPERATIONS_H_

#include "bigint.h"

/* Checks if GCD of a and b is equal to 1*/
//void __extended_gcd(BigInt* a, BigInt* b, BigInt* u, BigInt* v);

void __montgomery_convert(BigInt* res, const BigInt* x, const BigInt* p);

void __montgomery_revert(BigInt* rev, const BigInt* x, const BigInt* p);

/* Computes the fast Montgomery mutliplication
 * Input:
 *		3 large integer x and y and p
 * Output:
 *		Stores the result of x*y mod p in res
 */
void montgomery_mul(BigInt* res, const BigInt* x, const BigInt* y, const BigInt* p);

void bigint_left_shift_inplace(BigInt* a);

void bigint_right_shift_inplace(BigInt* a);

void bigint_add_inplace(BigInt* a, const BigInt* b);

void bigint_sub_inplace(BigInt* a, const BigInt* b);

//void bigint_mul_inplace(BigInt* a, BigInt* b);

void bigint_modulo_inplace(BigInt* a, const BigInt* mod);

// Compute b/a over Fp, storing the result in dest.
void bigint_divide(BigInt* dest, const BigInt* b, const BigInt* a, const BigInt* p);

#endif
