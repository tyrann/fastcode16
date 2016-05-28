
#ifndef __BIGINT_OPERATIONS_H_
#define __BIGINT_OPERATIONS_H_

#include "bigint.h"

/*
 * sets p_prime to -p^-1 (mod 2^64)
 */
void __montgomery_init(const BigInt p);

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

void bigint_mul_add_inplace_x2(BigInt res, const BigInt a, const uint64_t b, const BigInt c, const uint64_t d, const uint64_t mul_size);

// Compute res += a * b
void bigint_mul_add_inplace(BigInt res, const BigInt a, const uint64_t b, const uint64_t mul_size);

void bigint_multiply(BigInt res, const BigInt a, const uint64_t b);

void bigint_multiply_inplace(BigInt a, uint64_t b);

void bigint_left_shift_inplace(BigInt a);

void bigint_right_shift_inplace(BigInt a);

void bigint_right_shift_inplace_64(BigInt a);

void bigint_add_inplace(BigInt a, const BigInt b);

void bigint_sub_inplace(BigInt a, const BigInt b);

void bigint_add_inplace_mod(BigInt a, const BigInt b, const BigInt p);

/*
 * 0 <= a < p && 0 <= b < p is assumed
 */
void bigint_sub_inplace_mod(BigInt a, const BigInt b, const BigInt p);

void bigint_modulo_inplace(BigInt a, const BigInt mod);

// Compute b/a over Fp, storing the result in dest.
void bigint_divide(BigInt dest, const BigInt b, const BigInt a, const BigInt p);

extern uint64_t p_prime;
extern BigInt montgomery_inverse_two;

#endif
