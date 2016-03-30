#include <stdlib.h>

#include "../../src/ec_parameters.h"
#include "../../src/bigint.h"
#include "../../src/ec_point.h"

int main(void)
{
    EllipticCurveParameter params;
    BigInt p, a, b, n, h, x, y;
    bigint_from_hex_string(&p, "FFFFFFFFAAAAAAAAAAAA");
    bigint_from_hex_string(&a, "FFFFFFFFAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    bigint_from_hex_string(&b, "FFFFFFFFAAAAAAAAAAAACCCCD");
    bigint_from_hex_string(&n, "DDFFFFFFFFAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    bigint_from_hex_string(&h, "CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    bigint_from_hex_string(&x, "DDFFFFFFFFACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    bigint_from_hex_string(&y, "CCCCCCCCCCCCCCCCCCCCCCCCCCCCDDCCCC");
    Point point;
    create_point(&point, &x, &y);

    ec_create_parameters(&params, &p, &a, &b, &point, &n, &h);

    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    point_free(&point);
    bigint_free(&n);
    bigint_free(&h);
    bigint_free(&x);
    bigint_free(&y);
    ec_free(&params);
}
