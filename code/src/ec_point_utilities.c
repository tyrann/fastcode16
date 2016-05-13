#include "ec_point_utilities.h"
#include "opcount/opcount.h"

extern uint64_t global_opcount;
extern uint64_t global_index_count;

void create_point(Point* p, const BigInt *a, const BigInt * b)
{
    bigint_copy(&(p->x), a);
    bigint_copy(&(p->y), b);
    p->is_at_infinity = 0;
}

void create_point_from_hex(Point* p, const char *x, const char *y)
{
    BigInt p_x, p_y;
    bigint_from_hex_string(&p_x,x);
    bigint_from_hex_string(&p_y,y);
    create_point(p, &p_x, &p_y);
    bigint_free(&p_x);
    bigint_free(&p_y);
}

void create_point_from_uint32(Point* p, uint32_t x, uint32_t y)
{
    BigInt p_x, p_y;
    bigint_from_uint32(&p_x,x);
    bigint_from_uint32(&p_y,y);
    create_point(p, &p_x, &p_y);
    bigint_free(&p_x);
    bigint_free(&p_y);
}

void create_point_from_uint64(Point* p, uint64_t x, uint64_t y)
{
    BigInt p_x, p_y;
    bigint_from_uint64(&p_x,x);
    bigint_from_uint64(&p_y,y);
    create_point(p, &p_x, &p_y);
    bigint_free(&p_x);
    bigint_free(&p_y);
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

char point_is_on_curve(const Point* p, const EllipticCurveParameter *params)
{
    char result;
    if(p->is_at_infinity)
    {
	result = 1;
    }
    else
    {
	BigInt x_result, x_squared, a_x, y_result, x_squared_rev, x_result_rev, y_result_rev, a_x_rev;
	montgomery_mul(&x_squared, &(p->x), &(p->x), &params->p);
	__montgomery_revert(&x_squared_rev, &x_squared, &params->p);
	
	montgomery_mul(&x_result, &x_squared_rev, &(p->x), &params->p);
	__montgomery_revert(&x_result_rev, &x_result, &params->p);


	montgomery_mul(&a_x, &(params->a), &(p->x), &(params->p));
	__montgomery_revert(&a_x_rev, &a_x, &params->p);

	bigint_add_inplace(&x_result_rev, &a_x_rev);

	bigint_add_inplace(&x_result_rev, &(params->b));
	bigint_modulo_inplace(&x_result_rev, &(params->p));

	montgomery_mul(&y_result, &(p->y), &(p->y), &(params->p));
	__montgomery_revert(&y_result_rev, &y_result, &params->p);
	bigint_modulo_inplace(&y_result_rev, &(params->p));

	result = bigint_are_equal(&x_result_rev, &y_result_rev);
	bigint_free(&x_result);
	bigint_free(&x_squared);
	bigint_free(&a_x);
	bigint_free(&y_result);
	bigint_free(&x_squared_rev);
	bigint_free(&x_result_rev);
	bigint_free(&y_result_rev);
	bigint_free(&a_x_rev);
    }
    return result;
}

void point_free(Point* p)
{
    bigint_free(&(p->x));
    bigint_free(&(p->y));
}

void point_copy(Point* dest, const Point *source)
{
    bigint_copy(&(dest->x), &(source->x));
    bigint_copy(&(dest->y), &(source->y));
    dest->is_at_infinity = source->is_at_infinity;
}

int point_are_equal(const Point *p, const Point *q)
{
    if(!bigint_are_equal(&(p->x), &q->x) || !bigint_are_equal(&(p->y), &q->y) || p->is_at_infinity != q->is_at_infinity)
	{
		__COUNT_OP(&global_opcount, 3);
		return 0;
    }
    return 1;
}
