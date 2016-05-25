#include "ec_point.h"
#include "bigint.h"
#include "opcount/opcount.h"
#include <stdio.h>
#include <stdlib.h>

extern uint64_t global_opcount;
extern uint64_t global_index_count;

void ec_point_add_inplace(Point *a, const Point *b, const EllipticCurveParameter *params)
{	
	//print_point(a, params->p);
    assert(point_is_on_curve(a, params));
    assert(point_is_on_curve(b, params));
	
    // SEC 1: Elliptic Curve Cryptography Certicom Research Version 2.0 page 7
    
    // Rule 1
    if(a->is_at_infinity && b->is_at_infinity)
    {
		// Nothing to do here
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
		BigInt tmp = GET_BIGINT_PTR(BI_POINTADD_TMP_TAG);
		BigInt numerator = GET_BIGINT_PTR(BI_POINTADD_NUMERATOR_TAG);
		BigInt denominator = GET_BIGINT_PTR(BI_POINTADD_DENOMINATOR_TAG);
		BigInt lambda = GET_BIGINT_PTR(BI_POINTADD_LAMBDA_TAG);
		BigInt lambda_squared = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUARED_TAG);
		BigInt x_twice = GET_BIGINT_PTR(BI_POINTADD_XTWICE_TAG);
		BigInt y_1 = GET_BIGINT_PTR(BI_POINTADD_Y1_TAG);
		BigInt x_1_minus_x_3 = GET_BIGINT_PTR(BI_POINTADD_X1MINUSX3_TAG);

		// numerator
		montgomery_mul(tmp, a->x, a->x, params->p);

		bigint_copy(y_1, a->y);
		montgomery_mul(numerator, tmp, params->three, params->p);

		bigint_add_inplace(numerator, params->a);
		bigint_modulo_inplace(numerator, params->p);

		// denominator
		montgomery_mul(denominator, a->y, params->two, params->p);

		// calculate lambda
		bigint_divide(lambda, numerator, denominator, params->p);
		__montgomery_convert(tmp, lambda, params->p);
		
		//calculate x
		bigint_copy(x_1_minus_x_3, a->x);
		montgomery_mul(lambda_squared, tmp, tmp, params->p);
		montgomery_mul(x_twice, a->x, params->two, params->p);
		bigint_copy(a->x, lambda_squared);		

		bigint_add_inplace(a->x, params->p);
		bigint_sub_inplace(a->x, x_twice);
		bigint_modulo_inplace(a->x, params->p);
	
		// calculate y
		
		// x_1 - x_3
		bigint_add_inplace(x_1_minus_x_3, params->p);
		bigint_sub_inplace(x_1_minus_x_3, a->x);
				
		// calculate lambda(x_1 - x_3)
		montgomery_mul(a->y, tmp, x_1_minus_x_3, params->p);

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
		BigInt tmp = GET_BIGINT_PTR(BI_POINTADD_TMP_TAG);
		BigInt numerator = GET_BIGINT_PTR(BI_POINTADD_NUMERATOR_TAG);
		BigInt denominator = GET_BIGINT_PTR(BI_POINTADD_DENOMINATOR_TAG);
		BigInt lambda = GET_BIGINT_PTR(BI_POINTADD_LAMBDA_TAG);
		BigInt lambda_squared = GET_BIGINT_PTR(BI_POINTADD_LAMBDASQUARED_TAG);
		BigInt x_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_X1ADDINVERSE_TAG);
		BigInt y_1_add_inverse = GET_BIGINT_PTR(BI_POINTADD_Y1ADDINVERSE_TAG);
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
		__montgomery_convert(tmp, lambda, params->p);

		//Calculate lambda^2
		bigint_copy(x_1_minus_x_3, a->x);
		montgomery_mul(lambda_squared, tmp, tmp, params->p);
		bigint_copy(a->x, lambda_squared);
	
		bigint_add_inplace(a->x, x_1_add_inverse);
		bigint_add_inplace(a->x, params->p);
		bigint_sub_inplace(a->x, b->x);
		bigint_modulo_inplace(a->x, params->p);

		// Calculate y_3
		bigint_add_inplace(x_1_minus_x_3, params->p);
		bigint_sub_inplace(x_1_minus_x_3, a->x);

		montgomery_mul(a->y, tmp, x_1_minus_x_3, params->p);
		
		bigint_add_inplace(a->y, y_1_add_inverse);
		bigint_modulo_inplace(a->y, params->p);
	
		a->is_at_infinity = 0;
    }
    else
    {
		assert("ec_point_add - this code should not be reached");
    }
}

void ec_point_double_inplace(Point *a, const EllipticCurveParameter *params)
{
	BigInt lambda1 = GET_BIGINT_PTR(BI_EC_POINT_DOUBLE_INPLACE_LAMBDA1_TAG);
	BigInt lambda2 = GET_BIGINT_PTR(BI_EC_POINT_DOUBLE_INPLACE_LAMBDA2_TAG);
	BigInt lambda3 = GET_BIGINT_PTR(BI_EC_POINT_DOUBLE_INPLACE_LAMBDA3_TAG);
	BigInt x_1 = GET_BIGINT_PTR(BI_EC_POINT_DOUBLE_INPLACE_X1_TAG);
	BigInt y_1 = GET_BIGINT_PTR(BI_EC_POINT_DOUBLE_INPLACE_Y1_TAG);
	BigInt z_1 = GET_BIGINT_PTR(BI_EC_POINT_DOUBLE_INPLACE_Z1_TAG);

	bigint_copy(x_1, a->x);
	bigint_copy(y_1, a->y);
	bigint_copy(z_1, a->z);
	bigint_copy(lambda2, a->x);

	// calculate lambda1
	montgomery_mul(x_1, x_1, x_1, params->p);
	bigint_copy(a->x, x_1);
	bigint_left_shift_inplace(x_1);
	bigint_modulo_inplace(x_1, params->p);
	bigint_add_inplace_mod(x_1, a->x, params->p);

	bigint_copy(lambda1, z_1);
	montgomery_mul(lambda1, lambda1, lambda1, params->p);
	montgomery_mul(lambda1, lambda1, lambda1, params->p);
	montgomery_mul(lambda1, lambda1, params->a, params->p);
	bigint_add_inplace_mod(lambda1, x_1, params->p);

	montgomery_mul(a->z, y_1, z_1, params->p);
	bigint_left_shift_inplace(a->z);
	bigint_modulo_inplace(a->z, params->p);

	// calculate lambda 2
	//4*x-1
	bigint_left_shift_inplace(lambda2);
	bigint_modulo_inplace(lambda2, params->p);
	bigint_left_shift_inplace(lambda2);
	bigint_modulo_inplace(lambda2, params->p);
	montgomery_mul(y_1, y_1, y_1, params->p);
	montgomery_mul(lambda2, lambda2, y_1, params->p);

	// calculate x_3
	montgomery_mul(a->x, lambda1, lambda1, params->p);
	bigint_copy(a->y, lambda2);
	bigint_left_shift_inplace(a->y);
	bigint_modulo_inplace(a->y, params->p);
	bigint_sub_inplace_mod(a->x, a->y, params->p);

	// calculate lambda3
	montgomery_mul(y_1, y_1, y_1, params->p);
	bigint_copy(lambda3, y_1);
	bigint_left_shift_inplace(lambda3);
	bigint_modulo_inplace(lambda3, params->p);
	bigint_left_shift_inplace(lambda3);
	bigint_modulo_inplace(lambda3, params->p);
	bigint_left_shift_inplace(lambda3);
	bigint_modulo_inplace(lambda3, params->p);
	bigint_copy(a->y, lambda2);
	bigint_sub_inplace_mod(a->y, a->x, params->p);
	montgomery_mul(a->y, a->y, lambda1, params->p);
	bigint_sub_inplace_mod(a->y, lambda3, params->p);
}


void ec_point_mul(Point *result, const BigInt d, const Point *P, const EllipticCurveParameter *params)
{
	Point p2;

	create_point_from_uint64(&p2, BI_POINTMUL_P2X_TAG, BI_POINTMUL_P2Y_TAG,  BI_POINTMUL_P2Z_TAG, 0, 0, params->p);
	bigint_copy(result->x, bigint_zero);
	bigint_copy(result->y, bigint_zero);
	result->is_at_infinity = 1;
	
    point_copy(&p2, P);
	for(uint64_t i = 0; i < d->significant_blocks; i++)
    {
		for(uint64_t j = 0; j < 64; j++) 
		{
			__COUNT_OP(&global_opcount,2);
	    	if(d->blocks[i] & (((uint64_t)1) << j)) 
	    	{
				ec_point_add_inplace(result, &p2, params);	
	   		}
			
			ec_point_add_inplace(&p2, &p2, params);
			__COUNT_OP(&global_index_count,1);
		}

		__COUNT_OP(&global_index_count,1);
    }

}

void ec_point_mul_generator(Point *result, const BigInt d, const EllipticCurveParameter *params)
{
	assert(__bigint__precomputation_buffer != 0);
	Point p2;

	create_point_from_uint64(&p2, BI_POINTMUL_P2X_TAG, BI_POINTMUL_P2Y_TAG,  BI_POINTMUL_P2Z_TAG, 0, 0, params->p);
	bigint_copy(result->x, bigint_zero);
	bigint_copy(result->y, bigint_zero);
	result->is_at_infinity = 1;

    point_copy(&p2, &(params->generator));
	for(uint64_t i = 0; i < d->significant_blocks; i++)
    {
		for(uint64_t j = 0; j < 64; j++)
		{
			__COUNT_OP(&global_opcount,2);
	    	if(d->blocks[i] & (((uint64_t)1) << j))
	    	{
	    		BigInt x = get_precomputed_bigint(3*(i*64 + j));
	    		BigInt y = get_precomputed_bigint(3*(i*64 + j) + 1);
	    		BigInt z = get_precomputed_bigint(3*(i*64 + j) + 2);
	    		create_point_no_conversion(&p2, x, y, z);
				ec_point_add_inplace(result, &p2, params);
	   		}
			__COUNT_OP(&global_index_count,1);
		}

		__COUNT_OP(&global_index_count,1);
    }

}
