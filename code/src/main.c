#ifndef WIN32
#include <sys/time.h>
#include "main.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define NUM_RUNS 2
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 1.8e9
#define CALIBRATE

unsigned short int n;
#define STR_LEN 20

/* 
 * Compute ECDH
 * 
 */
// secp192k1
void create_parameters_ECDHShort(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFEE37");
    bigint_from_uint32(&a, 0);
    bigint_from_uint32(&b, 3);
    create_point_from_hex(&G, "DB4FF10EC057E9AE26B07D0280B7F4341DA5D1B1EAE06C7D", "9B2F2F6D9C5628A7844163D015BE86344082AA88D95E2F9D");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D");
    bigint_from_uint32(&h, 1);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}

// secp521r1
void create_parameters_ECDHLong(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_hex_string(&p, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF");
    bigint_from_hex_string(&a, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC");
    bigint_from_hex_string(&b, "0051953EB9618E1C9A1F929A21A0B68540EEA2DA725B99B315F3B8B489918EF109E156193951EC7E937B1652C0BD3BB1BF073573DF883D2C34F1EF451FD46B503F00");
    create_point_from_hex(&G, "00C6858E06B70404E9CD9E3ECB662395B4429C648139053FB521F828AF606B4D3DBAA14B5E77EFE75928FE1DC127A2FFA8DE3348B3C1856A429BF97E7E31C2E5BD66", "011839296A789A3BC0045C8A5FB42C7D1BD998F54449579B446817AFBD17273E662C97EE72995EF42640C550B9013FAD0761353C7086A272C24088BE94769FD16650");
    bigint_from_hex_string(&n, "01FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409");
    bigint_from_uint32(&h, 1);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}

void computeECDH(char* dURand, char* dVRand) {
	EllipticCurveParameter params;
    create_parameters_ECDHShort(&params);
	BigInt dU;
	bigint_from_hex_string(&dU, dURand); // Randome number between 0 and n 
	
	BigInt dV;
	bigint_from_hex_string(&dV, dVRand); // Randome number between 0 and n 

	ECDH uECDH;
    Point pub_keyU;
    create_point_inf(&pub_keyU);
	BigInt sharedInfoU;
	bigint_from_uint32(&sharedInfoU, 0);
	ec_create_ECDH(&uECDH, &params, &pub_keyU, &dU, &sharedInfoU);	
	ECDH vECDH;
    Point pub_keyV;
    create_point_inf(&pub_keyV);
	BigInt sharedInfoV;
	bigint_from_uint32(&sharedInfoV, 1);
	ec_create_ECDH(&vECDH, &params, &pub_keyV, &dV, &sharedInfoV);
	
	ecdh_generate_public_key(&uECDH, &dU);
	ecdh_generate_public_key(&vECDH, &dV);
	ec_free(&params);
	bigint_free(&dU);
	bigint_free(&dV);

    point_free(&pub_keyU);
	bigint_free(&sharedInfoU);
	ec_ECDHfree(&uECDH);

	point_free(&pub_keyV);
	bigint_free(&sharedInfoV);
	ec_ECDHfree(&vECDH);	

}

/* 
 * Timing function based on the TimeStep Counter of the CPU.
 */

double rdtsc(char* dURand, char* dVRand) {
  int i, num_runs;
  myInt64 cycles;
  myInt64 start;
  num_runs = NUM_RUNS;

/* 
 * The CPUID instruction serializes the pipeline.
 * Using it, we can create execution barriers around the code we want to time.
 * The calibrate section is used to make the computation large enough so as to 
 * avoid measurements bias due to the timing overhead.
 */
#ifdef CALIBRATE
  while(num_runs < (1 << 14)) { // run 14 times 
      start = start_tsc();
      for (i = 0; i < num_runs; ++i) {
          computeECDH(dURand,dVRand);
      }
      cycles = stop_tsc(start);

      if(cycles >= CYCLES_REQUIRED) break;

      num_runs *= 2;  
  }
#endif

  start = start_tsc();
  for (i = 0; i < num_runs; ++i) { 
    computeECDH(dURand,dVRand);
  }

  cycles = stop_tsc(start)/num_runs;
  return cycles;
}

int main(){

  double r;  

// secp192k1
  printf("======EC secp192k1=====\n");
  printf("n = 10\n");
  r = rdtsc("FFFFFFFFFF","26F2FC170F"); // r = circles 
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 20\n");
  r = rdtsc("FFFFFFFFFFFFFFFFFFFF","26F2FC170F69466A74DE"); // r = circles 
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 30\n");
  r = rdtsc("FFFFFFFFFFFFFFFFFFFFFFFE26F2FC","FFFFFE26F2FC170F69466A74DEFD8D"); // r = circles 
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 40\n");
  r = rdtsc("FFFFFFFFFFFFFFFFFFFFFFFE26F2FCFFFFFFFFFF","FFFFFE26F2FC170F69466A74DEFD8D26F2FC170F"); // r = circles 
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  
  // secp521r1
  printf("======EC secp521r1=====\n");
  printf("n = 10\n");
  r = rdtsc("FFFFFFFFFF","26F2FC170F"); // r = circles 
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 20\n");
  r = rdtsc("FFFFFFFFFFFFFFFFFFFF","26F2FC170F69466A74DE"); 
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 30\n");
  r = rdtsc("FFFFFFFFFFFFFFFFFFFFFFFE26F2FC","FFFFFE26F2FC170F69466A74DEFD8D");  
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 40\n");
  r = rdtsc("FFFFFFFFFFFFFFFFFFFFFFFE26F2FCFFFFFFFFFF","FFFFFE26F2FC170F69466A74DEFD8D26F2FC170F");  
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 50\n");
  r = rdtsc("FFFFFFFFFFFFFFFFFFFFFFFE26F2FCFFFFFFFFFFFFFFFFFFFF","26F2FC170FFFFFFE26F2FC170F69466A74DEFD8D26F2FC170F");
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 80\n");
  r = rdtsc("FFFFFFFFFFFFFFFFFFFFFFFE26F2FCFFFFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D","26F2FC170FFFFFFE26F2FC170F69466A74DEFD8D26F2FC170FFFFFFFFFFFFFFFFFFFFFFFFE26F2FC");
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  
  printf("n = 100\n");
  r = rdtsc("FFFFFFFFFFFFFFFFF26F2FC170F69466A74DEFFFFFFE26F2FCFFFFFFFFFFFFFFFFFFFFFFFFFE26F2FC170F69466A74DEFD8D","26F2FC170FFFFFFE26F2FC170F69466A74DEFD8D26F2FCFFFFFFFFFFFFFFFFFFFF170FFFFFFFFFFFFFFFFFFFFFFFFE26F2FC");
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);
  return 0;
}


/*
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
	printf("elliptic curve cryptography expects one parameter\n");
	printf("example ./ecc configfile.txt\n");
    }
    else
    {
	EllipticCurveParameter parameter;
	int code = read_config_file(&parameter, argv[1]);
	if(code == CONFIG_COULD_NOT_OPEN_FILE)
	{
	    fprintf(stderr, "Could not open file \"%s\"\n", argv[1]);
	    return -1;
	}
	else if(code == CONFIG_INVALID_FORMAT)
	{
	    fprintf(stderr, "The config file \"%s\" is invalid\n", argv[1]);
	    return -1;
	}
	else
	{
	    BigInt d;
	    Point P, result, expected;

	    point_copy(&P, &(parameter.generator));
	    bigint_copy(&d, &(parameter.n));
	    create_point_inf(&expected);
	    ec_point_mul(&result, &d, &P, &parameter);
	    printf("%i", point_are_equal(&result, &expected));
	    bigint_free(&d);
	    point_free(&P);
	    point_free(&result);
	    point_free(&expected);
	    ec_free(&parameter);
	}
	
    }

    return 0;
}
*/
