#include "ec_point.h"
#include "bigint.h"
#include "opcount/opcount.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

extern uint64_t global_opcount;
extern uint64_t global_index_count;
extern BigInt montgomery_inverse_two;

void ec_point_add_inplace(Point *a, const Point *b, const EllipticCurveParameter *params)
{	
	//print_point(a, params->p);
    assert(point_is_on_curve(a, params));
    assert(point_is_on_curve(b, params));
	
    // SEC 1: Elliptic Curve Cryptography Certicom Research Version 2.0 page 7
    
    if(a->is_at_infinity && b->is_at_infinity)
    {
		// Nothing to do here
    }
    else if(a->is_at_infinity)
    {
		point_copy(a, b);
    }
    else if(b->is_at_infinity)
    {
		// Nothing to do here
    }
    else {
		// Get BigInt objects
		BigInt lambda1 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA1_TAG);
		BigInt lambda2 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA2_TAG);
		BigInt lambda3 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA3_TAG);
		BigInt lambda4 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA4_TAG);
		BigInt lambda5 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA5_TAG);
		BigInt lambda6 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA6_TAG);
		BigInt lambda7 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA7_TAG);
		BigInt lambda8 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA8_TAG);
		BigInt lambda9 = GET_BIGINT_PTR(BI_POINTADD_LAMBDA9_TAG);
		BigInt z1_squared = GET_BIGINT_PTR(BI_POINTADD_Z1_SQUARED_TAG);
		BigInt z2_squared = GET_BIGINT_PTR(BI_POINTADD_Z2_SQUARED_TAG);

		BigInt tmp1 = GET_BIGINT_PTR(BI_POINTADD_TMP1_TAG);
		BigInt tmp2 = GET_BIGINT_PTR(BI_POINTADD_TMP2_TAG);
		
		// calculate lambda1 and lambda2
				
		// TODO: merge
		montgomery_mul(z2_squared, b->z, b->z, params->p);
		montgomery_mul(z1_squared, a->z, a->z, params->p);
		
		// TODO: merge
		montgomery_mul(lambda1, a->x, z2_squared, params->p);
		montgomery_mul(lambda2, b->x, z1_squared, params->p);

		//calculate lambda3
		bigint_copy(lambda3, lambda1);
		bigint_sub_inplace_mod(lambda3, lambda2, params->p);

		//calculate lambda4 and lambda5		
		// TODO: merge
		montgomery_mul(tmp1, b->z, z2_squared, params->p);
		montgomery_mul(tmp2, a->z, z1_squared, params->p);
		
		// TODO: merge
		montgomery_mul(lambda4, tmp1, a->y, params->p);
		montgomery_mul(lambda5, tmp2, b->y, params->p);

		//calculate lambda6
		bigint_copy(lambda6, lambda4);
		bigint_sub_inplace_mod(lambda6, lambda5, params->p);

		if(bigint_are_equal(lambda3, bigint_zero))
		{
			if(bigint_are_equal(lambda6, bigint_zero))
			{
				ec_point_double_inplace(a, params);
				return;
			}
			else
			{
				a->is_at_infinity = 1;
				return;
			}
		}

		//calculate lambda7
		bigint_copy(lambda7, lambda1);
		bigint_add_inplace_mod(lambda7, lambda2, params->p);

		//calculate lambda8
		bigint_copy(lambda8, lambda4);
		bigint_add_inplace_mod(lambda8, lambda5, params->p);

		//calculate z3
		// TODO: merge
		montgomery_mul(tmp1, a->z, b->z, params->p);
		montgomery_mul(lambda1, lambda3, lambda3, params->p);

		//calculate x3
		// TODO: merge	
		montgomery_mul(a->x, lambda6, lambda6, params->p);
		montgomery_mul(a->z, tmp1, lambda3, params->p);
		
		montgomery_mul(lambda9, lambda1, lambda7, params->p);
		bigint_sub_inplace_mod(a->x, lambda9, params->p);

		//calculate lambda9
		bigint_copy(lambda1, a->x);
		bigint_left_shift_inplace(lambda1);
		bigint_modulo_inplace(lambda1, params->p);
		bigint_sub_inplace_mod(lambda9, lambda1, params->p);

		//calculate y_3
		// TODO: merge
		montgomery_mul(tmp2, lambda9, lambda6, params->p);
		montgomery_mul(lambda1, lambda3, lambda3, params->p);
		
		montgomery_mul(tmp1, lambda1, lambda3, params->p);
		montgomery_mul(lambda1, tmp1, lambda8, params->p);
		bigint_sub_inplace_mod(tmp2, lambda1, params->p);
		
		montgomery_mul(a->y, tmp2, montgomery_inverse_two, params->p);

		a->is_at_infinity = 0;
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

	BigInt tmp1 = GET_BIGINT_PTR(BI_POINTADD_TMP1_TAG);
		
	bigint_copy(z_1, a->z);
	bigint_copy(lambda2, a->x);
	
	// TODO: merge
	montgomery_mul(lambda1, a->z, a->z, params->p);
	montgomery_mul(x_1, a->x, a->x, params->p);
	
	bigint_copy(a->x, x_1);
	bigint_left_shift_inplace(x_1);
	bigint_modulo_inplace(x_1, params->p);
	bigint_add_inplace_mod(x_1, a->x, params->p);
	
	// TODO: merge
	montgomery_mul(tmp1, lambda1, lambda1, params->p);
	montgomery_mul(a->z, a->y, z_1, params->p);

	// TODO: merge
	montgomery_mul(lambda1, tmp1, params->a, params->p);
	montgomery_mul(y_1, a->y, a->y, params->p);
	
	bigint_add_inplace_mod(lambda1, x_1, params->p);

	bigint_left_shift_inplace(a->z);
	bigint_modulo_inplace(a->z, params->p);

	// calculate lambda 2
	//4*x-1
	bigint_left_shift_inplace(lambda2);
	bigint_modulo_inplace(lambda2, params->p);
	bigint_left_shift_inplace(lambda2);
	bigint_modulo_inplace(lambda2, params->p);
	
	// TODO: merge
	montgomery_mul(a->x, lambda1, lambda1, params->p);
	montgomery_mul(tmp1, lambda2, y_1, params->p);

	// calculate x_3
	bigint_copy(a->y, tmp1);
	bigint_left_shift_inplace(a->y);
	bigint_modulo_inplace(a->y, params->p);
	bigint_sub_inplace_mod(a->x, a->y, params->p);

	// calculate lambda3
	montgomery_mul(lambda3, y_1, y_1, params->p);
	
	bigint_left_shift_inplace(lambda3);
	bigint_modulo_inplace(lambda3, params->p);
	bigint_left_shift_inplace(lambda3);
	bigint_modulo_inplace(lambda3, params->p);
	bigint_left_shift_inplace(lambda3);
	bigint_modulo_inplace(lambda3, params->p);
	
	bigint_sub_inplace_mod(tmp1, a->x, params->p);
	
	montgomery_mul(a->y, tmp1, lambda1, params->p);
	bigint_sub_inplace_mod(a->y, lambda3, params->p);
}


void ec_point_mul(Point *result, const BigInt d, const Point *P, const EllipticCurveParameter *params)
{
	Point p2;

	create_point_from_uint64(&p2, BI_POINTMUL_P2X_TAG, BI_POINTMUL_P2Y_TAG,  BI_POINTMUL_P2Z_TAG, 0, 0, params->p);
	bigint_copy(result->x, bigint_zero);
	bigint_copy(result->y, bigint_zero);
	result->is_at_infinity = 1;
	
	uint64_t i = 0;
    point_copy(&p2, P);
	for(; i < d->significant_blocks - 1; i++)
    {
		for(uint64_t j = 0; j < 64; j++) 
		{
			__COUNT_OP(&global_opcount,2);
	    	if(d->blocks[i] & (((uint64_t)1) << j)) 
	    	{
				ec_point_add_inplace(result, &p2, params);	
	   		}
			
			ec_point_double_inplace(&p2, params);
			__COUNT_OP(&global_index_count,1);
		}

		__COUNT_OP(&global_index_count,1);
    }

	//__builtin_clz Returns the number of leading 0-bits in x, starting at the most significant bit position.
	const unsigned char max = 64 - __builtin_clz(d->blocks[i]);

	for(uint64_t j = 0; j < max; j++)
	{
		__COUNT_OP(&global_opcount,2);
		if(d->blocks[i] & (((uint64_t)1) << j))
		{
			ec_point_add_inplace(result, &p2, params);
		}

		ec_point_double_inplace(&p2, params);
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
