#include "ec_point_utilities.h"
#include "ec_point_operations.h"
#include "opcount/opcount.h"
#include <stdio.h>
#include <stdlib.h>

extern uint64_t global_opcount;
extern uint64_t global_index_count;
extern block* __bigint__precomputation_buffer;

void point_convert_to_montgomery_space(Point* Q, const BigInt p);

void create_point(Point* p, const BigInt a, const BigInt b, const BigInt prime)
{
    p->x = a;
    p->y = b;
    p->is_at_infinity = 0;
    point_convert_to_montgomery_space(p, prime);
}

void create_point_no_conversion(Point* p, const BigInt a, const BigInt b)
{
    p->x = a;
    p->y = b;
    p->is_at_infinity = 0;
}

void create_point_from_hex(Point* p, uint32_t tag_x, uint32_t tag_y, const char *x, const char *y, const BigInt prime)
{
    create_point(p,
        bigint_from_hex_string(tag_x, x),
        bigint_from_hex_string(tag_y, y),
        prime);
}

void create_point_from_uint64(Point* p, uint32_t tag_x, uint32_t tag_y, uint64_t x, uint64_t y, const BigInt prime)
{
    create_point(p,
        bigint_from_uint64(tag_x, x),
        bigint_from_uint64(tag_y, y),
        prime);
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
        BigInt x_result = GET_BIGINT_PTR(BI_POINTISONCURVE_XRESULT_TAG);
        BigInt y_result = GET_BIGINT_PTR(BI_POINTISONCURVE_YRESULT_TAG);
        BigInt a_x = GET_BIGINT_PTR(BI_POINTISONCURVE_AX_TAG);
        
        montgomery_mul(x_squared, p->x, p->x, params->p);
	    montgomery_mul(x_result, x_squared, p->x, params->p);
	    montgomery_mul(a_x, params->a, p->x, params->p);

	    bigint_add_inplace(x_result, a_x);
	    bigint_add_inplace(x_result, params->b);
	    bigint_modulo_inplace(x_result, params->p);

	    montgomery_mul(y_result, p->y, p->y, params->p);
	    bigint_modulo_inplace(y_result, params->p);

	    result = bigint_are_equal(x_result, y_result);
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

void precompute_points(EllipticCurveParameter *parameter)
{
	assert(__bigint__precomputation_buffer != 0);
	BigInt x, y;
	Point tmp;
	Point tmp2;
	create_point_from_uint64(&tmp, BI_PRECOMPUTE_POINTS_TMP_X_TAG, BI_PRECOMPUTE_POINTS_TMP_Y_TAG, 0, 0, parameter->p);
	point_copy(&tmp, &(parameter->generator));
	for(unsigned int i = 0; i < parameter->p->significant_blocks * 64; i++)
	{
		Point G;
		x = get_precomputed_bigint(2*i);
		y = get_precomputed_bigint(2*i+1);
		create_point_no_conversion(&G, x, y);
		point_copy(&G, &tmp);
		ec_point_add_inplace(&tmp, &tmp, parameter);
		get_precomputed_point(&tmp2, 0);
	}
}

// Stores 2^i*G in P
void get_precomputed_point(Point *P, int i)
{
	BigInt x = get_precomputed_bigint(2*i);
	BigInt y = get_precomputed_bigint(2*i + 1);
	create_point_no_conversion(P, x, y);
}

void print_point(const Point *P, const BigInt prime)
{
	Point Q;
	create_point_from_uint64(&Q, BI_PRINT_POINT_X_TAG, BI_PRINT_POINT_Y_TAG, 0, 0, prime);
	point_copy(&Q, P);
	point_revert_from_montgomery_space(&Q, prime);
	char *x_str = bigint_to_hex_string(Q.x);
	char *y_str = bigint_to_hex_string(Q.y);
	printf("(%s,%s)\n", x_str, y_str);
	free(x_str);
	free(y_str);
}

