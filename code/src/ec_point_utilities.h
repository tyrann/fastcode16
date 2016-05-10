
#ifndef __EC_POINT_UTILITIES_H_
#define __EC_POINT_UTILITIES_H_

#include "ec_point_structure.h"
#include "ec_parameters.h"

void create_point(Point* p, const BigInt a, const BigInt b);

void create_point_from_hex(Point* p, uint32_t tag_x, uint32_t tag_y, const char *x, const char *y);

void create_point_from_uint32(Point* p, uint32_t tag_x, uint32_t tag_y, uint32_t x, uint32_t y);

void create_point_from_uint64(Point* p, uint32_t tag_x, uint32_t tag_y, uint64_t x, uint64_t y);

void create_point_inf(Point* p, uint32_t tag_x, uint32_t tag_y);

char point_is_on_curve(const Point* p, const EllipticCurveParameter *params);

void point_copy(Point* dest, Point const *source);

int point_are_equal(const Point *x, const Point *y);

#endif
