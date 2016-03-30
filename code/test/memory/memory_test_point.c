#include <stdlib.h>
#include "../../src/bigint.h"
#include "../../src/ec_point.h"

int main(void)
{
    BigInt a, b;
    bigint_from_hex_string(&a, "FFFFFFFFAAAAAAAAAAAA");
    bigint_from_hex_string(&b, "FFFFFFFFAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    Point p;
    create_point(&p, &a, &b);
    point_free(&p);
    bigint_free(&a);
    bigint_free(&b);
}
