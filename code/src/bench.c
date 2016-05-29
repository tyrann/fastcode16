#ifndef WIN32
#include <sys/time.h>
#include <inttypes.h>
#include "benchmark/benchmark.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifdef SYS_OSSL
#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/crypto.h>
#else
#include "../lib/openssl/usr/include/openssl/ec.h"
#include "../lib/openssl/usr/include/openssl/bn.h"
#include "../lib/openssl/usr/include/openssl/crypto.h"
#endif
#include <stdlib.h>
#include <openssl_benchmark.h>
#define NUM_RUNS 1
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 3.4e9
#define CALIBRATE


int main(){
    
	openssl_Benchmark_Add();
	openssl_Benchmark_Mult();
	openssl_Benchmark_Mont_Mult();
	openssl_Benchmark_Div();
	openssl_Benchmark_Shift();
    return 0;	

}
