
#ifndef __EC_STRUCTURE_H_
#define __EC_STRUCTURE_H_

#include "bigint.h"

/* Describes a point on the elliptic curve. 
 * We represent the point at infinity by
 * byte-long flag */
typedef struct
{
	BigInt x;
	BigInt y;
	char is_at_infinity;

} Point;

#endif
