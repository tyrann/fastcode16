#ifndef __OPENSSL_BENCHMARK_H_
#define __OPENSSL_BENCHMARK_H_
#include <stdio.h>
#include "config/config.h"
#include "bigint.h"
#include "ec_point_structure.h"
#include "ec_point_operations.h"
#include "ec_parameters.h"
#include "ec_point_utilities.h"
#include "ec_dh.h"
#include "logging/logging.h"

void openssl_Benchmark_Add(void);
void openssl_Benchmark_Mult(void);
void openssl_Benchmark_Mont_Mult(void);
void openssl_Benchmark_Div(void);
void openssl_Benchmark_Shift(void);

#endif