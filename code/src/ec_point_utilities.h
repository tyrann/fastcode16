
#ifndef __EC_POINT_UTILITIES_H_
#define __EC_POINT_UTILITIES_H_

#include "ec_point_structure.h"
#include "ec_parameters.h"

void create_point(Point* p, const BigInt a, const BigInt b, const BigInt c, const BigInt prime);

void create_point_no_conversion(Point* p, const BigInt a, const BigInt b, const BigInt c);

void create_point_from_hex(Point* p, uint32_t tag_x, uint32_t tag_y,  uint32_t tag_z, const char *x, const char *y, const BigInt prime);

void create_point_from_uint64(Point* p, uint32_t tag_x, uint32_t tag_y,  uint32_t tag_z, uint64_t x, uint64_t y, const BigInt prime);

void point_revert_from_montgomery_space(Point* Q, const BigInt p);

char point_is_on_curve(const Point* p, const EllipticCurveParameter *params);

void point_convert_to_affine_coordinates(Point* p, const EllipticCurveParameter *params);

void point_copy(Point* dest, Point const *source);

int point_are_equal(const Point *x, const Point *y);

void precompute_points(EllipticCurveParameter *parameter);

// Stores 2^i*G in P
void get_precomputed_point(Point *P, int i);

void print_point(const Point *P, const BigInt prime);

#endif
