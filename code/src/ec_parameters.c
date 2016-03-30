#include "ec_parameters.h"
#include "bigint.h"

void ec_free(EllipticCurveParameter *ec)
{
    bigint_free(&(ec->p));
    bigint_free(&(ec->a));
    bigint_free(&(ec->b));
    point_free(&(ec->generator));
    bigint_free(&(ec->n));
    bigint_free(&(ec->h));
}

void ec_create_parameters(EllipticCurveParameter *ec, const BigInt const *p, const BigInt const *a, const BigInt const *b, const Point const *generator, const BigInt const *n, const BigInt const *h)
{
    bigint_copy(&(ec->p), p);
    bigint_copy(&(ec->a), a);
    bigint_copy(&(ec->b), b);
    point_copy(&(ec->generator), generator);
    bigint_copy(&(ec->n), n);
    bigint_copy(&(ec->h), h);
}


