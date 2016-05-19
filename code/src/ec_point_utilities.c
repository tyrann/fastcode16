#include "ec_point_utilities.h"
#include "opcount/opcount.h"

extern uint64_t global_opcount;
extern uint64_t global_index_count;

void create_point(Point* p, const BigInt a, const BigInt b)
{
    p->x = a;
    p->y = b;
    p->is_at_infinity = 0;
}

void create_point_from_hex(Point* p, uint32_t tag_x, uint32_t tag_y, const char *x, const char *y)
{
    create_point(p,
        bigint_from_hex_string(tag_x, x),
        bigint_from_hex_string(tag_y, y));
}

void create_point_from_uint64(Point* p, uint32_t tag_x, uint32_t tag_y, uint64_t x, uint64_t y)
{
    create_point(p,
        bigint_from_uint64(tag_x, x),
        bigint_from_uint64(tag_y, y));
}

void point_convert_to_montgomery_space(Point* Q, const BigInt p)
{
	BigInt x = GET_BIGINT_PTR(BI_POINT_CONVERT_TO_MONTGOMERY_SPACE_X_TAG);
	BigInt y = GET_BIGINT_PTR(BI_POINT_CONVERT_TO_MONTGOMERY_SPACE_Y_TAG);
	bigint_copy(x, Q->x);
	bigint_copy(y, Q->y);
	__montgomery_convert(Q->x, x, p);
	__montgomery_convert(Q->y, y, p);
}

void point_revert_from_montgomery_space(Point* Q, const BigInt p)
{
	BigInt x = GET_BIGINT_PTR(BI_POINT_REVERT_FROM_MONTGOMERY_SPACE_X_TAG);
	BigInt y = GET_BIGINT_PTR(BI_POINT_REVERT_FROM_MONTGOMERY_SPACE_Y_TAG);
	bigint_copy(x, Q->x);
	bigint_copy(y, Q->y);
	__montgomery_revert(Q->x, x, p);
	__montgomery_revert(Q->y, y, p);
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
        BigInt x_squared = GET_BIGINT_PTR(BI_POINTISONCURVE_XSQUARED_TAG);
        BigInt x_squared_rev = GET_BIGINT_PTR(BI_POINTISONCURVE_XSQUAREDREV_TAG);
        BigInt x_result = GET_BIGINT_PTR(BI_POINTISONCURVE_XRESULT_TAG);
        BigInt x_result_rev = GET_BIGINT_PTR(BI_POINTISONCURVE_XRESULTREV_TAG);
        BigInt y_result = GET_BIGINT_PTR(BI_POINTISONCURVE_YRESULT_TAG);
        BigInt y_result_rev = GET_BIGINT_PTR(BI_POINTISONCURVE_YRESULTREV_TAG);
        BigInt a_x = GET_BIGINT_PTR(BI_POINTISONCURVE_AX_TAG);
        BigInt a_x_rev = GET_BIGINT_PTR(BI_POINTISONCURVE_AXREV_TAG);
        
        montgomery_mul(x_squared, p->x, p->x, params->p);
        __montgomery_revert(x_squared_rev, x_squared, params->p);
    
	    montgomery_mul(x_result, x_squared_rev, p->x, params->p);
	    __montgomery_revert(x_result_rev, x_result, params->p);

	    montgomery_mul(a_x, params->a, p->x, params->p);
	    __montgomery_revert(a_x_rev, a_x, params->p);

	    bigint_add_inplace(x_result_rev, a_x_rev);
	    bigint_add_inplace(x_result_rev, params->b);
	    bigint_modulo_inplace(x_result_rev, params->p);

	    montgomery_mul(y_result, p->y, p->y, params->p);
	    __montgomery_revert(y_result_rev, y_result, params->p);
	    bigint_modulo_inplace(y_result_rev, params->p);

	    result = bigint_are_equal(x_result_rev, y_result_rev);
    }
    return result;
}

void point_copy(Point* dest, const Point *source)
{
    bigint_copy(dest->x, source->x);
    bigint_copy(dest->y, source->y);
    dest->is_at_infinity = source->is_at_infinity;
}

int point_are_equal(const Point *p, const Point *q)
{
    if(p->is_at_infinity == q->is_at_infinity)
	{
        if (q->is_at_infinity == 1)
		{
            return 1;
		}
        else if(!bigint_are_equal(p->x, q->x) || !bigint_are_equal(p->y, q->y))
		{ 
			__COUNT_OP(&global_opcount,1);
            return 0;
		}
		else
		{
            return 1;
		}
    }
    else
    {
        return 0;
    }
}
