#ifndef WIN32
#include <sys/time.h>
#include <inttypes.h>
#include "main.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <openssl/ec.h>
#include <openssl/bn.h>
#include <openssl/crypto.h>
#include <stdlib.h>
#define NUM_RUNS 1024 // Change number of runs 
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 1.8e9
#define CALIBRATE
#define OP_COUNT 1

unsigned short int n;
extern uint64_t global_opcount; 
extern uint64_t global_index_count; 

void test_Left_Shift()
{
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

    global_opcount = global_opcount/num_runs;
    global_index_count = global_index_count/num_runs;
    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6); 
    
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


void test_Add()
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

    start = start_tsc();
	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
	BigInt b = bigint_from_hex_string(BI_TESTS_A_TAG, "9007ffffffc0068cd2c5edd23d55f01c");

	for(int i = 0; i < num_runs; i++)
    {
    bigint_add_inplace(a, b);
    }
    cycles = stop_tsc(start);

    global_opcount = global_opcount/num_runs;
    global_index_count = global_index_count/num_runs;
    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6); 
    
}

void test_Add_open_ssl()
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;
    
    BN_CTX *ctx;
    ctx = BN_CTX_new();
    BIGNUM *a = BN_new();
	BIGNUM *b = BN_new();
	BIGNUM *result = BN_new();

    BN_hex2bn(&a, "8cd2c5edd23d55f01c9007ffffffc006");
    BN_hex2bn(&b, "9007ffffffc0068cd2c5edd23d55f01c");


    start = start_tsc();
    for(int i = 0; i < num_runs; i++)
    {
		BN_add(result, a, b);
	}
    cycles = stop_tsc(start);

    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
	
    BN_CTX_free(ctx);
    BN_free(a);
    BN_free(result);
}

void openssl_Benchmark(){
    
    bigint_create_buffer();
	
	// Test left shift
	printf("Test ShiftLeft\n");
	test_Left_Shift();
	printf("Test ShiftLeft of OpenSSl\n");
	test_Left_Shift_open_ssl();
	
	// Test add 
	printf("Test Addition\n");
	test_Add();
	printf("Test Addition of OpenSSl\n");
	test_Add_open_ssl();

    bigint_destroy_buffer();
}
