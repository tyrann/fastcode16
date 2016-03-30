#include "ec_point.h"
#include "bigint.h"

void create_point(Point* p, BigInt const* a, BigInt const* b)
{
    bigint_copy(&(p->x), a);
    bigint_copy(&(p->y), b);
    p->is_at_infinity = 0;
}

void create_point_inf(Point* p)
{
    BigInt zero;
    bigint_from_uint32(&zero, 0);
    bigint_copy(&(p->x), &zero);
    bigint_copy(&(p->y), &zero);
    p->is_at_infinity = 1;
    bigint_free(&zero);
}

void point_free(Point* p)
{
    bigint_free(&(p->x));
    bigint_free(&(p->y));
}

void point_copy(Point* dest, Point const *source)
{
    bigint_copy(&(dest->x), &(source->x));
    bigint_copy(&(dest->y), &(source->y));
    dest->is_at_infinity = source->is_at_infinity;
}

int point_are_equal(Point const *p, Point const *q)
{
    if(!bigint_are_equal(&(p->x), &q->x) || !bigint_are_equal(&(p->y), &q->y) || p->is_at_infinity != q->is_at_infinity) {
	return 0;
    }
    return 1;
}
