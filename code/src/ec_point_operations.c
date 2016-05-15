#include "ec_point.h"
#include "bigint.h"
#include "opcount/opcount.h"

extern uint64_t global_opcount;
extern uint64_t global_index_count;

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
		BigInt lambda = GET_BIGINT_PTR(BI_POINTADD_LAMBDA_TAG);
		BigInt lambda_squared = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUARED_TAG);
		BigInt x_twice = GET_BIGINT_PTR(BI_POINTADD_XTWICE_TAG);
		BigInt y_3 = GET_BIGINT_PTR(BI_POINTADD_Y3_TAG);
		BigInt x_1_minus_x_3 = GET_BIGINT_PTR(BI_POINTADD_X1MINUSX3_TAG);

		// numerator
		montgomery_mul(numerator, a->x, a->x, params->p);
		__montgomery_revert(numerator_rev, numerator, params->p);

		bigint_copy(numerator, numerator_rev);
		bigint_left_shift_inplace(numerator);
		bigint_add_inplace(numerator, numerator_rev);
		bigint_add_inplace(numerator, params->a);
		bigint_modulo_inplace(numerator, params->p);
	
		// denominator
		bigint_copy(denominator, a->y);
		bigint_left_shift_inplace(denominator);
		bigint_modulo_inplace(denominator, params->p);

		// calculate lambda
		bigint_divide(lambda, numerator, denominator, params->p);

		//calculate x
		montgomery_mul(lambda_squared, lambda, lambda, params->p);
		__montgomery_revert(result->x, lambda_squared, params->p);

		bigint_copy(x_twice, a->x);
		bigint_left_shift_inplace(x_twice);
		bigint_modulo_inplace(x_twice, params->p);
		
		bigint_add_inplace(result->x, params->p);
		bigint_sub_inplace(result->x, x_twice);
		bigint_modulo_inplace(result->x, params->p);
	
		// calculate y
		
		// x_1 - x_3
		bigint_copy(x_1_minus_x_3, a->x);
		bigint_add_inplace(x_1_minus_x_3, params->p);
		bigint_sub_inplace(x_1_minus_x_3, result->x);

		// calculate lambda(x_1 - x_3)
		montgomery_mul(y_3, lambda, x_1_minus_x_3, params->p);
		__montgomery_revert(result->y, y_3, params->p);

		bigint_add_inplace(result->y, params->p);
		bigint_sub_inplace(result->y, a->y);
		bigint_modulo_inplace(result->y, params->p);

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
		BigInt x_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_X1ADDINVERSE_TAG);
		BigInt y_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_Y1ADDINVERSE_TAG);
		BigInt y_3 = GET_BIGINT_PTR(BI_POINTADD_Y3_TAG);
		BigInt x_1_minus_x_3 = GET_BIGINT_PTR(BI_POINTADD_X1MINUSX3_TAG);
	
		// Compute inverses
		bigint_copy(x_1_add_inverse, params->p);
		bigint_sub_inplace(x_1_add_inverse, a->x);
		
		bigint_copy(y_1_add_inverse, params->p);
		bigint_sub_inplace(y_1_add_inverse, a->y);
	
		//Calculate y_2 - y_1
		bigint_copy(numerator, b->y);
		bigint_add_inplace(numerator, y_1_add_inverse);
		bigint_modulo_inplace(numerator, params->p);
	
		//Calculate x_2 - x_1		
		bigint_copy(denominator, b->x);
		bigint_add_inplace(denominator, x_1_add_inverse);
		bigint_modulo_inplace(denominator, params->p);
	
		//Calculate lambda
		bigint_divide(lambda, numerator, denominator, params->p);

		//Calculate lambda^2
		montgomery_mul(lambda_squared, lambda, lambda, params->p);
		__montgomery_revert(result->x, lambda_squared, params->p);
	
		bigint_add_inplace(result->x, x_1_add_inverse);
		bigint_add_inplace(result->x, params->p);
		bigint_sub_inplace(result->x, b->x);
		bigint_modulo_inplace(result->x, params->p);

		// Calculate y_3
		bigint_copy(x_1_minus_x_3, a->x);
		bigint_add_inplace(x_1_minus_x_3, params->p);
		bigint_sub_inplace(x_1_minus_x_3, result->x);

		montgomery_mul(y_3, lambda, x_1_minus_x_3, params->p);
		__montgomery_revert(result->y, y_3, params->p);
		
		bigint_add_inplace(result->y, y_1_add_inverse);
		bigint_modulo_inplace(result->y, params->p);
	
		result->is_at_infinity = 0;
    }
    else
    {
		assert("ec_point_add - this code should not be reached");
    }
}

void ec_point_add_inplace(Point *a, const Point *b, const EllipticCurveParameter *params)
{	
    assert(point_is_on_curve(a, params));
    assert(point_is_on_curve(b, params));
	
    // SEC 1: Elliptic Curve Cryptography Certicom Research Version 2.0 page 7
    
    // Rule 1
    if(a->is_at_infinity && b->is_at_infinity)
    {
		a->is_at_infinity = 1;
    }
    // Rule 2
    else if(a->is_at_infinity)
    {
		point_copy(a, b);
    }
    else if(b->is_at_infinity)
    {
		// Nothing to do here
    }
    // Rule 5
    else if(bigint_are_equal(a->x, b->x) && bigint_are_equal(a->y, b->y)
		&& !bigint_are_equal(a->y, bigint_zero))
    {
		// Get BigInt objects
		BigInt numerator = GET_BIGINT_PTR(BI_POINTADD_NUMERATOR_TAG);
		BigInt numerator_rev = GET_BIGINT_PTR(BI_POINTADD_NUMERATORREV_TAG);
		BigInt denominator = GET_BIGINT_PTR(BI_POINTADD_DENOMINATOR_TAG);
		BigInt lambda = GET_BIGINT_PTR(BI_POINTADD_LAMBDA_TAG);
		BigInt lambda_squared = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUARED_TAG);
		BigInt x_twice = GET_BIGINT_PTR(BI_POINTADD_XTWICE_TAG);
		BigInt y_1 = GET_BIGINT_PTR(BI_POINTADD_Y1_TAG);
		BigInt y_3 = GET_BIGINT_PTR(BI_POINTADD_Y3_TAG);
		BigInt x_1_minus_x_3 = GET_BIGINT_PTR(BI_POINTADD_X1MINUSX3_TAG);

		// numerator
		montgomery_mul(numerator, a->x, a->x, params->p);
		__montgomery_revert(numerator_rev, numerator, params->p);

		bigint_copy(numerator, numerator_rev);
		bigint_left_shift_inplace(numerator);
		bigint_add_inplace(numerator, numerator_rev);
		bigint_add_inplace(numerator, params->a);
		bigint_modulo_inplace(numerator, params->p);
	
		// denominator
		bigint_copy(denominator, a->y);
		bigint_copy(y_1, a->y);
		bigint_left_shift_inplace(denominator);
		bigint_modulo_inplace(denominator, params->p);

		// calculate lambda
		bigint_divide(lambda, numerator, denominator, params->p);

		//calculate x
		bigint_copy(x_1_minus_x_3, a->x);
		bigint_copy(x_twice, a->x);
		
		montgomery_mul(lambda_squared, lambda, lambda, params->p);
		__montgomery_revert(a->x, lambda_squared, params->p);

		bigint_left_shift_inplace(x_twice);
		bigint_modulo_inplace(x_twice, params->p);
		
		bigint_add_inplace(a->x, params->p);
		bigint_sub_inplace(a->x, x_twice);
		bigint_modulo_inplace(a->x, params->p);
	
		// calculate y
		
		// x_1 - x_3
		bigint_add_inplace(x_1_minus_x_3, params->p);
		bigint_sub_inplace(x_1_minus_x_3, a->x);

		// calculate lambda(x_1 - x_3)
		montgomery_mul(y_3, lambda, x_1_minus_x_3, params->p);
		__montgomery_revert(a->y, y_3, params->p);

		bigint_add_inplace(a->y, params->p);
		bigint_sub_inplace(a->y, y_1);
		bigint_modulo_inplace(a->y, params->p);

		a->is_at_infinity = 0;
    } 
    // Rule 3
    else if(bigint_are_equal(a->x, b->x))
    {
		a->is_at_infinity = 1;
    }
    // Rule 4
    else if(!bigint_are_equal(a->x, b->x))
    {	
		// Get BigInt objects
		BigInt numerator = GET_BIGINT_PTR(BI_POINTADD_NUMERATOR_TAG);
		BigInt denominator = GET_BIGINT_PTR(BI_POINTADD_DENOMINATOR_TAG);
		BigInt lambda = GET_BIGINT_PTR(BI_POINTADD_LAMBDA_TAG);
		BigInt lambda_squared = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUARED_TAG);
		BigInt x_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_X1ADDINVERSE_TAG);
		BigInt y_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_Y1ADDINVERSE_TAG);
		BigInt y_3 = GET_BIGINT_PTR(BI_POINTADD_Y3_TAG);
		BigInt x_1_minus_x_3 = GET_BIGINT_PTR(BI_POINTADD_X1MINUSX3_TAG);
	
		// Compute inverses
		bigint_copy(x_1_add_inverse, params->p);
		bigint_sub_inplace(x_1_add_inverse, a->x);
		
		bigint_copy(y_1_add_inverse, params->p);
		bigint_sub_inplace(y_1_add_inverse, a->y);
	
		//Calculate y_2 - y_1
		bigint_copy(numerator, b->y);
		bigint_add_inplace(numerator, y_1_add_inverse);
		bigint_modulo_inplace(numerator, params->p);
	
		//Calculate x_2 - x_1		
		bigint_copy(denominator, b->x);
		bigint_add_inplace(denominator, x_1_add_inverse);
		bigint_modulo_inplace(denominator, params->p);
	
		//Calculate lambda
		bigint_divide(lambda, numerator, denominator, params->p);

		//Calculate lambda^2
		bigint_copy(x_1_minus_x_3, a->x);
		montgomery_mul(lambda_squared, lambda, lambda, params->p);
		__montgomery_revert(a->x, lambda_squared, params->p);
	
		bigint_add_inplace(a->x, x_1_add_inverse);
		bigint_add_inplace(a->x, params->p);
		bigint_sub_inplace(a->x, b->x);
		bigint_modulo_inplace(a->x, params->p);

		// Calculate y_3
		bigint_add_inplace(x_1_minus_x_3, params->p);
		bigint_sub_inplace(x_1_minus_x_3, a->x);

		montgomery_mul(y_3, lambda, x_1_minus_x_3, params->p);
		__montgomery_revert(a->y, y_3, params->p);
		
		bigint_add_inplace(a->y, y_1_add_inverse);
		bigint_modulo_inplace(a->y, params->p);
	
		a->is_at_infinity = 0;
    }
    else
    {
		assert("ec_point_add - this code should not be reached");
    }
}

void ec_point_mul(Point *result, const BigInt d, const Point *P, const EllipticCurveParameter *params)
{
	Point p2;

	create_point_from_uint32(&p2, BI_POINTMUL_P2X_TAG, BI_POINTMUL_P2Y_TAG, 0, 0);
	bigint_copy(result->x, bigint_zero);
	bigint_copy(result->y, bigint_zero);
	result->is_at_infinity = 1;
	
    point_copy(&p2, P);

    for(uint64_t i = 0; i < d->significant_octets; i++)
    {
		for(int j = 0; j < 8; j++) 
		{
			__COUNT_OP(&global_opcount,2);
	    	if(d->octets[i] & (1 << j)) 
	    	{
				ec_point_add_inplace(result, &p2, params);	
	   		}
	    	ec_point_add_inplace(&p2, &p2, params);
			__COUNT_OP(&global_index_count,1);
		}

		__COUNT_OP(&global_index_count,1);
    }
}
