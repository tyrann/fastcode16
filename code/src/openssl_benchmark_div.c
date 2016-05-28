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
#define NUM_RUNS 1024 // Change number of runs 
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 1.8e9
#define CALIBRATE
#define OP_COUNT 1

unsigned short int n;
extern uint64_t global_opcount; 
extern uint64_t global_index_count; 

/*
 * Test division
*/

void test_Div()
{
	bigint_create_buffer();
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

	BigInt x = GET_BIGINT_PTR(BI_TESTS_X_TAG);

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "7cd73b6fc007dfee34a23caf363ae67e8bb8782600000000032accceb");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "c69d8b898f0e43b4643a018e7b0569de6f8cf328e0bf6d59ace4e3bc2ca28d10");
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "ffffffff00000001000000000000000000000000ffffffffffffffffffffffff");
	
    start = start_tsc();
	for(int i = 0; i < num_runs; i++)
    {
	bigint_divide(x, b, a, p);
    }
    cycles = stop_tsc(start);

    global_opcount = global_opcount/num_runs;
    global_index_count = global_index_count/num_runs;
    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);     
    bigint_destroy_buffer();
}

void test_Div_open_ssl()
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;
    
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *result = BN_new();
	BIGNUM *rem = BN_new();

    BN_hex2bn(&a, "7cd73b6fc007dfee34a23caf363ae67e8bb8782600000000032accceb");
    BN_hex2bn(&b, "c69d8b898f0e43b4643a018e7b0569de6f8cf328e0bf6d59ace4e3bc2ca28d10");


    start = start_tsc();
    for(int i = 0; i < num_runs; i++)
    {
		BN_div(result, rem, b, a, ctx);
	}
    cycles = stop_tsc(start);

    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
	
    BN_CTX_free(ctx);
    BN_free(a);
	BN_free(b);
    BN_free(result);
	BN_free(rem);
}

void openssl_Benchmark_Div()
{ 	
	// Test division
	printf("============Test Div============\n");
	printf("ECC Division\n");
	test_Div();
	printf("OpenSSl Division\n");
	test_Div_open_ssl();		

}
