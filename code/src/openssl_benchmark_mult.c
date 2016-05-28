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

unsigned short int n;
extern uint64_t global_opcount; 
extern uint64_t global_index_count; 


/*
 * Test multiplication
*/

void test_Mul()
{
	bigint_create_buffer();
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

	uint64_t b = 123123123;
    BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "37900b3819a5d49e0a355fb44e75b48372b7ac48e88af780ba692c47681fd3246a87e6456b9eb9d9effa1eb798ee7e5adfb40bf41b3a45930cb949e8330eef8edfee7b7df9b020bd3fedac73c552b6acc9d494ef52c3b570097747fd7969cdb4677e5ad6daec42bb5ffcfaadee09e63e1a36a2016ab6715286928660d3b8a63d0990249defb076dc82a7ac3e550aa662888b2eb3e");

    start = start_tsc();
	for(int i = 0; i < num_runs; i++)
    {
	bigint_multiply_inplace(a, b);
    }
    cycles = stop_tsc(start);

    global_opcount = global_opcount/num_runs;
    global_index_count = global_index_count/num_runs;
    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);     
    bigint_destroy_buffer();
}

void test_Mul_open_ssl()
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;
    
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *result = BN_new();

    BN_hex2bn(&a, "37900b3819a5d49e0a355fb44e75b48372b7ac48e88af780ba692c47681fd3246a87e6456b9eb9d9effa1eb798ee7e5adfb40bf41b3a45930cb949e8330eef8edfee7b7df9b020bd3fedac73c552b6acc9d494ef52c3b570097747fd7969cdb4677e5ad6daec42bb5ffcfaadee09e63e1a36a2016ab6715286928660d3b8a63d0990249defb076dc82a7ac3e550aa662888b2eb3e");
    BN_hex2bn(&b, "756B5B3");


    start = start_tsc();
    for(int i = 0; i < num_runs; i++)
    {
		BN_mul(result, b, a, ctx);
	}
    cycles = stop_tsc(start);

    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
	
    BN_CTX_free(ctx);
    BN_free(a);
	BN_free(b);
    BN_free(result);
}


void openssl_Benchmark_Mult()
{
    // Test multiplication 
	printf("============Test Mult============\n");
	printf("ECC multiplication\n");
	test_Mul();
	printf("OpenSSl multiplication\n");
	test_Mul_open_ssl();
}
