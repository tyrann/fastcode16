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

/*
 * Test left shift 
*/
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

/*
 * Test Addition
*/
void test_Add()
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
	BigInt b = bigint_from_hex_string(BI_TESTS_B_TAG, "9007ffffffc0068cd2c5edd23d55f01c");

    start = start_tsc();
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
	BN_free(b);
    BN_free(result);
}


/*
 * Test montgomery multiplication
*/
void test_Mult()
{
    myInt64 cycles;
    myInt64 start;
    int num_runs = NUM_RUNS;

	BigInt a = bigint_from_hex_string(BI_TESTS_A_TAG, "8cd2c5edd23d55f01c9007ffffffc006");
	BigInt b = bigint_from_hex_string(BI_TESTS_A_TAG, "9007ffffffc0068cd2c5edd23d55f01c");
	BigInt p = bigint_from_hex_string(BI_PARAMS_P_TAG, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37"); // P from SECP192K1
	BigInt res = GET_BIGINT_PTR(BI_POINTADD_NUMERATOR_TAG);

    start = start_tsc();
	for(int i = 0; i < num_runs; i++)
    {
    montgomery_mul(res, a, b, p);
    }
    cycles = stop_tsc(start);

    global_opcount = global_opcount/num_runs;
    global_index_count = global_index_count/num_runs;
    double r;  
    r = cycles / num_runs;
    printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);    
}

void test_Mult_open_ssl()
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

    BN_hex2bn(&a, "8cd2c5edd23d55f01c9007ffffffc006");
    BN_hex2bn(&b, "9007ffffffc0068cd2c5edd23d55f01c");


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

/*
 * Test division
*/

void test_Div()
{
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

void openssl_Benchmark(){
    
    bigint_create_buffer();
	
	// Test left shift
	printf("============Test ShiftLeft============\n");

	printf("ECC ShiftLeft\n");
	test_Left_Shift();
	printf("OpenSSl ShiftLeft\n");
	test_Left_Shift_open_ssl();
	
	// Test add 
	printf("============Test Add============\n");
	printf("ECC Addition\n");
	test_Add();
	printf("OpenSSl Addition\n");
	test_Add_open_ssl();
	
	// Test montgomery multiplication 
	printf("============Test Mult============\n");
	printf("ECC mont-multiplication\n");
	test_Mult();
	printf("OpenSSl mont-multiplication\n");
	test_Mult_open_ssl();
	
	// Test division
	printf("============Test Div============\n");
	printf("ECC Division\n");
	test_Div();
	printf("OpenSSl Division\n");
	test_Div_open_ssl();		

    bigint_destroy_buffer();
}
