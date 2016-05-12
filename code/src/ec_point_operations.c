#include "ec_point.h"
#include "bigint.h"

void ec_point_add(Point *result, const Point *a, const Point *b, const EllipticCurveParameter *params)
{	
    assert(point_is_on_curve(a, params));
    assert(point_is_on_curve(b, params));
	
    // SEC 1: Elliptic Curve Cryptography Certicom Research Version 2.0 page 7
    
    // Rule 1
    if(a->is_at_infinity && b->is_at_infinity)
    {
		result->is_at_infinity = 1;
    }
    // Rule 2
    else if(a->is_at_infinity)
    {
		point_copy(result, b);
    }
    else if(b->is_at_infinity)
    {
		point_copy(result, a);
    }
    // Rule 5
    else if(bigint_are_equal(a->x, b->x) && bigint_are_equal(a->y, b->y)
		&& !bigint_are_equal(a->y, bigint_zero))
    {
		// Get BigInt objects
		BigInt numerator = GET_BIGINT_PTR(BI_POINTADD_NUMERATOR_TAG);
		BigInt numerator_rev = GET_BIGINT_PTR(BI_POINTADD_NUMERATORREV_TAG);
		BigInt denominator = GET_BIGINT_PTR(BI_POINTADD_DENOMINATOR_TAG);
		BigInt denominator_rev = GET_BIGINT_PTR(BI_POINTADD_DENOMINATORREV_TAG);
		BigInt lambda = GET_BIGINT_PTR(BI_POINTADD_LAMBDA_TAG);
		BigInt lambda_squared = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUARED_TAG);
		BigInt lambda_squared_rev = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUAREDREV_TAG);
		BigInt x_twice = GET_BIGINT_PTR(BI_POINTADD_XTWICE_TAG);
		BigInt x_twice_rev = GET_BIGINT_PTR(BI_POINTADD_XTWICEREV_TAG);
		BigInt dummy = GET_BIGINT_PTR(BI_POINTADD_DUMMY_TAG);
		BigInt x_3 = GET_BIGINT_PTR(BI_POINTADD_X3_TAG);
		BigInt x_add_inverse = GET_BIGINT_PTR(BI_POINTADD_XADDINVERSE_TAG);
		BigInt y_3 = GET_BIGINT_PTR(BI_POINTADD_Y3_TAG);
		BigInt y_3_rev = GET_BIGINT_PTR(BI_POINTADD_Y3REV_TAG);
		BigInt x_1_minus_x_3 = GET_BIGINT_PTR(BI_POINTADD_X1MINUSX3_TAG);
		BigInt y_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_Y1ADDINVERSE_TAG);

		// numerator
		montgomery_mul(numerator, a->x, a->x, params->p);
		__montgomery_revert(numerator_rev, numerator, params->p);

		montgomery_mul(numerator, numerator_rev, bigint_three, params->p);
		__montgomery_revert(numerator_rev, numerator, params->p);

		bigint_add_inplace(numerator_rev, params->a);
		bigint_modulo_inplace(numerator_rev, params->p);
	
		// denominator
		montgomery_mul(denominator, a->y, bigint_two, params->p);
		__montgomery_revert(denominator_rev, denominator, params->p);

		// calculate lambda
		bigint_divide(lambda, numerator_rev, denominator_rev, params->p);

		//calculate x
		montgomery_mul(lambda_squared, lambda, lambda, params->p);
		__montgomery_revert(lambda_squared_rev, lambda_squared, params->p);

		montgomery_mul(x_twice, a->x, bigint_two, params->p);
		__montgomery_revert(x_twice_rev, x_twice, params->p);
	
		bigint_copy(dummy, params->p);
		bigint_sub_inplace(dummy, x_twice_rev);

		bigint_copy(x_3, lambda_squared_rev);
		bigint_add_inplace(x_3, dummy);
		bigint_modulo_inplace(x_3, params->p);
	
		// calculate y
		bigint_copy(x_1_minus_x_3, a->x);
		bigint_copy(x_add_inverse, params->p);
		bigint_sub_inplace(x_add_inverse, x_3);

		// x_1 - x_3
		bigint_add_inplace(x_1_minus_x_3, x_add_inverse);

		// calculate lambda(x_1 - x_3)
		montgomery_mul(y_3, lambda, x_1_minus_x_3, params->p);
		__montgomery_revert(y_3_rev, y_3, params->p);

		bigint_copy(y_1_add_inverse, params->p);
		bigint_sub_inplace(y_1_add_inverse, a->y);

		bigint_add_inplace(y_3_rev, y_1_add_inverse);
		bigint_modulo_inplace(y_3_rev, params->p);

		bigint_copy(result->x, x_3);
		bigint_copy(result->y, y_3_rev);
		result->is_at_infinity = 0;
    } 
    // Rule 3
    else if(bigint_are_equal(a->x, b->x))
    {
		result->is_at_infinity = 1;
    }
    // Rule 4
    else if(!bigint_are_equal(a->x, b->x))
    {	
		// Get BigInt objects
		BigInt numerator = GET_BIGINT_PTR(BI_POINTADD_NUMERATOR_TAG);
		BigInt denominator = GET_BIGINT_PTR(BI_POINTADD_DENOMINATOR_TAG);
		BigInt lambda = GET_BIGINT_PTR(BI_POINTADD_LAMBDA_TAG);
		BigInt lambda_squared = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUARED_TAG);
		BigInt lambda_squared_rev = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUAREDREV_TAG);
		
		BigInt x_1 = GET_BIGINT_PTR(BI_POINTADD_X1_TAG);
		BigInt x_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_X1ADDINVERSE_TAG);
		BigInt y_1 = GET_BIGINT_PTR(BI_POINTADD_Y1_TAG);
		BigInt y_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_Y1ADDINVERSE_TAG);
		BigInt x_2 = GET_BIGINT_PTR(BI_POINTADD_X2_TAG);
		BigInt x_2_add_inverse = GET_BIGINT_PTR(BI_POINTADD_X2ADDINVERSE_TAG);
		BigInt x_3 = GET_BIGINT_PTR(BI_POINTADD_X3_TAG);
		BigInt x_3_add_inverse = GET_BIGINT_PTR(BI_POINTADD_X3ADDINVERSE_TAG);
		BigInt y_3 = GET_BIGINT_PTR(BI_POINTADD_Y3_TAG);
		BigInt y_3_rev = GET_BIGINT_PTR(BI_POINTADD_Y3REV_TAG);
		BigInt x_1_minus_x_3 = GET_BIGINT_PTR(BI_POINTADD_X1MINUSX3_TAG);
	
		//Calculate y_2 - y_1
		bigint_copy(y_1, a->y);
		bigint_modulo_inplace(y_1, params->p);

		bigint_copy(y_1_add_inverse, params->p);
		bigint_sub_inplace(y_1_add_inverse, y_1);
		bigint_copy(numerator, b->y);

		bigint_add_inplace(numerator, y_1_add_inverse);
		bigint_modulo_inplace(numerator, params->p);
	
		//Calculate x_2 - x_1
		bigint_copy(x_1, a->x);
		bigint_modulo_inplace(x_1, params->p);

		bigint_copy(x_1_add_inverse, params->p);
		bigint_sub_inplace(x_1_add_inverse, x_1);
		bigint_copy(denominator, b->x);

		bigint_add_inplace(denominator, x_1_add_inverse);
		bigint_modulo_inplace(denominator, params->p);
	
		//Calculate lambda
		bigint_divide(lambda, numerator, denominator, params->p);

		//Calculate lambda^2
		montgomery_mul(lambda_squared, lambda, lambda, params->p);
		__montgomery_revert(lambda_squared_rev, lambda_squared, params->p);

		bigint_copy(x_2, b->x);
		bigint_modulo_inplace(x_2, params->p);
		bigint_copy(x_2_add_inverse, params->p);
		bigint_sub_inplace(x_2_add_inverse, x_2);
	
		bigint_copy(x_3, lambda_squared_rev);
		bigint_add_inplace(x_3, x_1_add_inverse);
		bigint_modulo_inplace(x_3, params->p);
		bigint_add_inplace(x_3, x_2_add_inverse);
		bigint_modulo_inplace(x_3, params->p);

		// Calculate y_3
		bigint_copy(x_3_add_inverse, params->p);
		bigint_sub_inplace(x_3_add_inverse, x_3);

		bigint_copy(x_1_minus_x_3, x_1);
		bigint_add_inplace(x_1_minus_x_3, x_3_add_inverse);

		montgomery_mul(y_3, lambda, x_1_minus_x_3, params->p);
		__montgomery_revert(y_3_rev, y_3, params->p);
		bigint_add_inplace(y_3_rev, y_1_add_inverse);
		bigint_modulo_inplace(y_3_rev, params->p);
	
		bigint_copy(result->x, x_3);
		bigint_copy(result->y, y_3_rev);
		result->is_at_infinity = 0;
    }
    else
    {
		assert("ec_point_add - this code should not be reached");
    }
}

void ec_point_mul(Point *result, const BigInt d, const Point *P, const EllipticCurveParameter *params)
{
	Point p1, p2;
    Point q1, q2;
	
	create_point_from_uint32(&p1, BI_POINTMUL_P1X_TAG, BI_POINTMUL_P1Y_TAG, 0, 0);
	create_point_from_uint32(&p2, BI_POINTMUL_P2X_TAG, BI_POINTMUL_P2Y_TAG, 0, 0);
	create_point_from_uint32(&q1, BI_POINTMUL_Q1X_TAG, BI_POINTMUL_Q1Y_TAG, 0, 0);
	create_point_from_uint32(&q2, BI_POINTMUL_Q2X_TAG, BI_POINTMUL_Q2Y_TAG, 0, 0);
	q1.is_at_infinity = 1;
	q2.is_at_infinity = 1;
	
    point_copy(&p2, P);

    for(uint64_t i = 0; i < d->significant_octets; i++)
    {
		for(int j = 0; j < 8; j++) 
		{
	    	if(d->octets[i] & (1 << j)) 
	    	{
				ec_point_add(&q1, &q2, &p2, params);
				point_copy(&q2, &q1);	
	   		}
	    	ec_point_add(&p1, &p2, &p2, params);
	    	point_copy(&p2, &p1);
		}
    }
    point_copy(result, &q1);
}
