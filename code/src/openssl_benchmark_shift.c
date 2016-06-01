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
extern uint64_t global_index_count; 
extern uint64_t mul_opcount;
extern uint64_t add_opcount;
extern uint64_t shift_opcount;
extern uint64_t avx_opcount;


/*
 * Test left shift 
*/
void test_Left_Shift()
{
    bigint_create_buffer();
	
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

    start = start_tsc();
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
	for(int i = 0; i < num_runs; i++)
    {
    bigint_left_shift_inplace(a);      	
    }
    cycles = stop_tsc(start);

    mul_opcount = mul_opcount/num_runs;
    add_opcount = add_opcount/num_runs; 
    shift_opcount = shift_opcount/num_runs;
    avx_opcount = avx_opcount/num_runs;
    global_index_count = global_index_count/num_runs;
    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6); 
    bigint_destroy_buffer();
}

void test_Left_Shift_open_ssl()
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;
    
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    BIGNUM *a = BN_new();
	BIGNUM *result = BN_new();

    BN_hex2bn(&a, "8cd2c5edd23d55f01c9007ffffffc006");
    start = start_tsc();
    for(int i = 0; i < num_runs; i++)
    {
		BN_lshift1(result, a);
    }
    cycles = stop_tsc(start);

    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
	
    BN_CTX_free(ctx);
    BN_free(a);
    BN_free(result);
}

void openssl_Benchmark_Shift(){
    	
	// Test left shift
	printf("============Test ShiftLeft============\n");

	printf("ECC ShiftLeft\n");
	test_Left_Shift();
	printf("OpenSSl ShiftLeft\n");
	test_Left_Shift_open_ssl();
}
