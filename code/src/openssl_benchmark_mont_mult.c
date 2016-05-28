#ifndef WIN32
#include <sys/time.h>
#include <inttypes.h>
#include "main.h"
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
 * Test montgomery multiplication
*/
void test_Mont_Mult()
{
	bigint_create_buffer();

    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

	BigInt b = GET_BIGINT_PTR(BI_TESTS_B_TAG);
	BigInt c = GET_BIGINT_PTR(BI_TESTS_C_TAG);
	BigInt p = bigint_from_hex_string(BI_TESTS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
	BigInt x = bigint_from_hex_string(BI_TESTS_X_TAG, "c1d420185df71b4d6473d45a552a4de2c476d2653ec8c699");
	BigInt y = bigint_from_hex_string(BI_TESTS_Y_TAG, "118427b3b4a05bc8a8a4de8459867fffffffffff");
	BigInt x_conv = GET_BIGINT_PTR(BI_TESTS_X_CONV_TAG);
	BigInt y_conv = GET_BIGINT_PTR(BI_TESTS_Y_CONV_TAG);
	__montgomery_init(p);
	__montgomery_convert(x_conv, x, p);
	__montgomery_convert(y_conv, y, p);
    start = start_tsc();
	for(int i = 0; i < num_runs; i++)
    {

	montgomery_mul(c, x_conv, y_conv, p); // ??Only repeat mult or should we include revert too?
    }
	__montgomery_revert(b, c, p);

    cycles = stop_tsc(start);

    global_opcount = global_opcount/num_runs;
    global_index_count = global_index_count/num_runs;
    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);    
    bigint_destroy_buffer();
}

void test_Mont_Mult_open_ssl()
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;
    
    BN_CTX *ctx;
    ctx = BN_CTX_new();
	BN_MONT_CTX *mont;
	mont = BN_MONT_CTX_new();
	BIGNUM *p = BN_new();
    BN_hex2bn(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");

	BN_MONT_CTX_set(mont, p, ctx);
	
    BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *result = BN_new();

    BN_hex2bn(&a, "c1d420185df71b4d6473d45a552a4de2c476d2653ec8c699");
    BN_hex2bn(&b, "118427b3b4a05bc8a8a4de8459867fffffffffff");


    start = start_tsc();
    for(int i = 0; i < num_runs; i++)
    {
	BN_mod_mul_montgomery(result, a, b, mont, ctx);	
	}
    cycles = stop_tsc(start);

    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
	
    BN_CTX_free(ctx);
	BN_MONT_CTX_free(mont);
    BN_free(a);
    BN_free(b);
    BN_free(result);
}

void openssl_Benchmark_Mont_Mult()
{

	// Test montgomery multiplication 
	printf("============Test montgomery Mult============\n");
	printf("ECC mont-multiplication\n");
	test_Mont_Mult();
	printf("OpenSSl mont-multiplication\n");
	test_Mont_Mult_open_ssl();
}
