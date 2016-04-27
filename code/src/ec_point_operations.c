#include "ec_point.h"
#include "bigint.h"

void ec_point_add(Point *result, const Point *a, const Point *b, const EllipticCurveParameter *params)
{
    assert(point_is_on_curve(a, params));
    assert(point_is_on_curve(b, params));

    BigInt zero;
    bigint_from_uint32(&zero, 0);
    BigInt two;
    bigint_from_uint32(&two, 2);
    BigInt three;
    bigint_from_uint32(&three, 3);

    // SEC 1: Elliptic Curve Cryptography Certicom Research Version 2.0 page 7
    
    // Rule 1
    if(a->is_at_infinity && b->is_at_infinity)
    {
	create_point_inf(result);
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
    else if(bigint_are_equal(&(a->x), &(b->x))  && bigint_are_equal(&(a->y), &(b->y)) && !bigint_are_equal(&(a->y), &zero))
    {
	BigInt numerator, numerator_rev, denominator, denominator_rev, lambda, lambda_squared, lambda_squared_rev, x_twice, x_twice_rev, dummy, x_3, x_add_inverse, y_3, y_3_rev, x_1_minus_x_3;
	BigInt y_1_add_inverse;

	// numerator
	montgomery_mul(&numerator, &(a->x), &(a->x), &(params->p));
	__montgomery_revert(&numerator_rev, &numerator, &(params->p));
	bigint_free(&numerator);

	montgomery_mul(&numerator, &numerator_rev, &three, &(params->p));
	bigint_free(&numerator_rev);
	__montgomery_revert(&numerator_rev, &numerator, &(params->p));

	bigint_add_inplace(&numerator_rev, &(params->a));
	bigint_modulo_inplace(&numerator_rev, &(params->p));
	
	// denominator
	montgomery_mul(&denominator, &(a->y), &two, &(params->p));
	__montgomery_revert(&denominator_rev, &denominator, &(params->p));

	// calculate lambda
	bigint_divide(&lambda, &numerator_rev, &denominator_rev, &(params->p));

	//calculate x
	montgomery_mul(&lambda_squared, &lambda, &lambda, &(params->p));
	__montgomery_revert(&lambda_squared_rev, &lambda_squared, &(params->p));

	montgomery_mul(&x_twice, &(a->x), &two, &(params->p));
	__montgomery_revert(&x_twice_rev, &x_twice, &(params->p));
	
	bigint_copy(&dummy, &(params->p));
	bigint_sub_inplace(&dummy, &x_twice_rev);

	bigint_copy(&x_3, &lambda_squared_rev);
	bigint_add_inplace(&x_3, &dummy);
	bigint_modulo_inplace(&x_3, &(params->p));
	
	// calculate y
	bigint_copy(&x_1_minus_x_3, &(a->x));
	bigint_copy(&x_add_inverse, &(params->p));
	bigint_sub_inplace(&x_add_inverse, &x_3);

	// x_1 - x_3
	bigint_add_inplace(&x_1_minus_x_3, &x_add_inverse);

	// calculate lambda(x_1 - x_3)
	montgomery_mul(&y_3, &lambda, &x_1_minus_x_3, &(params->p));
	__montgomery_revert(&y_3_rev, &y_3, &(params->p));

	bigint_copy(&y_1_add_inverse, &(params->p));
	bigint_sub_inplace(&y_1_add_inverse, &(a->y));

	bigint_add_inplace(&y_3_rev, &y_1_add_inverse);
	bigint_modulo_inplace(&y_3_rev, &(params->p));

	create_point(result, &x_3, &y_3_rev);

	bigint_free(&numerator);
	bigint_free(&numerator_rev);
	bigint_free(&denominator);
	bigint_free(&denominator_rev);
	bigint_free(&lambda);
	bigint_free(&lambda_squared);
	bigint_free(&lambda_squared_rev);
	bigint_free(&x_twice);
	bigint_free(&x_twice_rev);
	bigint_free(&dummy);
	bigint_free(&x_3);
	bigint_free(&x_add_inverse);
	bigint_free(&y_3);
	bigint_free(&y_3_rev);
	bigint_free(&x_1_minus_x_3);
	bigint_free(&y_1_add_inverse);
    } 
    // Rule 3
    else if(bigint_are_equal(&(a->x), &(b->x)))
    {
	create_point_inf(result);
    }
    // Rule 4
    else if(!bigint_are_equal(&(a->x), &(b->x)))
    {
	BigInt y_1, y_1_add_inverse, numerator;
	BigInt x_1, x_1_add_inverse, denominator;
	BigInt lambda;
	BigInt lambda_squared, lambda_squared_rev;
	BigInt x_2, x_2_add_inverse;
	BigInt x_3, x_3_add_inverse;
	BigInt x_1_minus_x3;
	BigInt y_3, y_3_rev;
	
	//Calculate y_2 - y_1
	bigint_copy(&y_1, &(a->y));
	bigint_modulo_inplace(&y_1, &(params->p));

	bigint_copy(&y_1_add_inverse, &(params->p));
	bigint_sub_inplace(&y_1_add_inverse, &y_1);
	bigint_copy(&numerator, &(b->y));

	bigint_add_inplace(&numerator, &(y_1_add_inverse));
	bigint_modulo_inplace(&numerator, &(params->p));
	
	//Calculate x_2 - x_1
	bigint_copy(&x_1, &(a->x));
	bigint_modulo_inplace(&x_1, &(params->p));

	bigint_copy(&x_1_add_inverse, &(params->p));
	bigint_sub_inplace(&x_1_add_inverse, &x_1);
	bigint_copy(&denominator, &(b->x));

	bigint_add_inplace(&denominator, &(x_1_add_inverse));
	bigint_modulo_inplace(&denominator, &(params->p));
	
	//Calculate lambda
	bigint_divide(&lambda, &numerator, &denominator, &(params->p));

	//Calculate lambda^2
	montgomery_mul(&lambda_squared, &lambda, &lambda, &(params->p));
	__montgomery_revert(&lambda_squared_rev, &lambda_squared, &(params->p));

	bigint_copy(&x_2, &(b->x));
	bigint_modulo_inplace(&x_2, &(params->p));
	bigint_copy(&x_2_add_inverse, &(params->p));
	bigint_sub_inplace(&x_2_add_inverse, &x_2);
	
	bigint_copy(&x_3, &lambda_squared_rev);
	bigint_add_inplace(&x_3, &(x_1_add_inverse));
	bigint_modulo_inplace(&x_3, &(params->p));
	bigint_add_inplace(&x_3, &(x_2_add_inverse));
	bigint_modulo_inplace(&x_3, &(params->p));

	// Calculate y_3
	bigint_copy(&x_3_add_inverse, &(params->p));
	bigint_sub_inplace(&x_3_add_inverse, &x_3);

	bigint_copy(&x_1_minus_x3, &x_1);
	bigint_add_inplace(&x_1_minus_x3, &x_3_add_inverse);

	montgomery_mul(&y_3, &lambda, &x_1_minus_x3, &(params->p));
	__montgomery_revert(&y_3_rev, &y_3, &(params->p));
	bigint_add_inplace(&y_3_rev, &y_1_add_inverse);
	bigint_modulo_inplace(&y_3_rev, &(params->p));
	
	create_point(result, &x_3, &y_3_rev);
	
	bigint_free(&y_1);
	bigint_free(&y_1_add_inverse);
	bigint_free(&numerator);
	bigint_free(&x_1);
	bigint_free(&x_1_add_inverse);
	bigint_free(&denominator);
	bigint_free(&lambda);
	bigint_free(&lambda_squared);
	bigint_free(&lambda_squared_rev);
	bigint_free(&x_2);
	bigint_free(&x_2_add_inverse);
	bigint_free(&x_3);
	bigint_free(&x_3_add_inverse);
	bigint_free(&x_1_minus_x3);
	bigint_free(&y_3);
	bigint_free(&y_3_rev);
    }
    else
    {
	assert("ec_point_add - this code should not be reached");
    }

    bigint_free(&zero);
    bigint_free(&two);
    bigint_free(&three);
}

void ec_point_mul(Point *result, const BigInt *d, const Point *P, const EllipticCurveParameter *params)
{
    Point q1, q2;
    Point p1, p2;
    create_point_inf(&q1);
    create_point_inf(&q2);
    point_copy(&p2, P);

    for(uint64_t i = 0; i < d->significant_octets; i++)
    {
	for(int j = 0; j < 8; j++) 
	{
	    if(d->octets[i] & (1 << j)) 
	    {
		point_free(&q1);
		ec_point_add(&q1, &q2, &p2, params);
		point_free(&q2);
		point_copy(&q2, &q1);	
	    }
	    ec_point_add(&p1, &p2, &p2, params);
	    point_free(&p2);
	    point_copy(&p2, &p1);
	    point_free(&p1);
	}
    }
    point_copy(result, &q1);
    point_free(&q1);
    point_free(&p2);
    point_free(&q2);
}
