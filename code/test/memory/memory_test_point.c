#include <stdlib.h>

#include "../../src/ec_parameters.h"
#include "../../src/bigint.h"
#include "../../src/ec_point.h"

int main(void)
{
    BigInt *a, *b;
    a = malloc(sizeof(BigInt));
    b = malloc(sizeof(BigInt));
    bigint_from_hex_string(a, "FFFFFFFFAAAAAAAAAAAA");
    bigint_from_hex_string(b, "FFFFFFFFAAAAAAAAAAAACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC");
    Point *p = malloc(sizeof(Point));
    create_point(p, a, b);
    point_free(p);
    bigint_free(a);
    bigint_free(b);
}
