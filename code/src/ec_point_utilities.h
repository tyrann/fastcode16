
#ifndef __EC_POINT_UTILITIES_H_
#define __EC_POINT_UTILITIES_H_

#include "ec_point_structure.h"

void create_point(Point* p, const BigInt * a, const BigInt * b);

void create_point_from_hex(Point* p, const char *x, const char *y);

void create_point_inf(Point* p);

void point_free(Point* p);

void point_copy(Point* dest, Point const *source);

int point_are_equal(const Point *x, const Point *y);

#endif
