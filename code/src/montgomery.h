#include "bigint.h"

/* Checks if GCD of a and b is equal to 1*/
void __extended_gcd(BigInt* a, BigInt* b, BigInt* u, BigInt* v);

void __montgomery_convert(BigInt* x, BigInt* p, BigInt* res);

void __montgomery_revert(BigInt* x, BigInt* p, BigInt* rev);

/* Computes the fast Montgomery mutliplication
 * Input:
 *		3 large integer x and y and p
 * Output:
 *		Stores the result of x*y mod p in res
 */
void montgomery_mul(BigInt* x, BigInt* y, BigInt* p, BigInt* res);
