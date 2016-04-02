
#ifndef __EC_POINT_UTILITIES_H_
#define __EC_POINT_UTILITIES_H_

#include "ec_point_structure.h"

void create_point(Point* p, BigInt const* a, BigInt const* b);

void create_point_inf(Point* p);

void point_free(Point* p);

void point_copy(Point* dest, Point const *source);

int point_are_equal(Point const *x, Point const *y);

#endif
