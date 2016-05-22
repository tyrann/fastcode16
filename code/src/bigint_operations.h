
#ifndef __BIGINT_OPERATIONS_H_
#define __BIGINT_OPERATIONS_H_

#include "bigint.h"

void __montgomery_convert(BigInt res, const BigInt x, const BigInt p);

void __montgomery_revert(BigInt rev, const BigInt x, const BigInt p);

/* Computes the fast Montgomery mutliplication
 * Input:
 *		3 large integer x and y and p
 * Output:
 *		Stores the result of x*y mod p in res
 *
 * see 14.36 Algorithm Montgomery multiplication
 * Handbook of Applied Cryptography, by A. Menezes, P. van Oorschot, and S. Vanstone, CRC Press, 1996
 */
void montgomery_mul(BigInt res, const BigInt x, const BigInt y, const BigInt p);

void multiply_inplace(BigInt a, uint64_t b);

void bigint_left_shift_inplace(BigInt a);

void bigint_right_shift_inplace(BigInt a);

void bigint_right_shift_inplace_64(BigInt a);

void bigint_add_inplace(BigInt a, const BigInt b);

void bigint_sub_inplace(BigInt a, const BigInt b);

void bigint_modulo_inplace(BigInt a, const BigInt mod);

// Compute b/a over Fp, storing the result in dest.
void bigint_divide(BigInt dest, const BigInt b, const BigInt a, const BigInt p);

extern uint64_t p_prime;

#endif
