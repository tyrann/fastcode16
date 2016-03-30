#include "ec_point.h"

void create_point(Point* p, BigInt const* a, BigInt const* b)
{
    bigint_copy(&(p->x), a);
    bigint_copy(&(p->y), b);
    p->is_at_infinity = 0;
}

void point_free(Point* p)
{
    bigint_free(&(p->x));
    bigint_free(&(p->y));
}

void point_copy(Point* dest, const Point const *source)
{
    bigint_copy(&(dest->x), &(source->x));
    bigint_copy(&(dest->y), &(source->y));
    dest->is_at_infinity = source->is_at_infinity;
}
