#ifndef WIN32
#include <sys/time.h>
#include <inttypes.h>
#include "main.h"
#endif
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define NUM_RUNS 2
#define CYCLES_REQUIRED 1e8
#define FREQUENCY 1.8e9
#define CALIBRATE
#define OP_COUNT 1

unsigned short int n;
extern uint64_t global_opcount; 
extern uint64_t global_index_count; 
/* 
 * Compute ECDH
 * 
 */
 
// secp192k1, 24 bytes 
void create_parameters_ECDH192(EllipticCurveParameter *params)
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

// secp224r1, 28 bytes
void create_parameters_ECDH224(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF000000000000000000000001");
    bigint_from_hex_string(&a, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFE");
    bigint_from_hex_string(&b, "B4050A850C04B3ABF54132565044B0B7D7BFD8BA270B39432355FFB4");
    create_point_from_hex(&G, "B70E0CBD6BB4BF7F321390B94A03C1D356C21122343280D6115C1D21", "BD376388B5F723FB4C22DFE6CD4375A05A07476444D5819985007E34");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29455C5C2A3D");
    bigint_from_uint32(&h, 1);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}

// secp256k1, 32 bytes
void create_parameters_ECDH256(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFC2F");
    bigint_from_uint32(&a, 0);
    bigint_from_uint32(&b, 7);
    create_point_from_hex(&G, "79BE667EF9DCBBAC55A06295CE870B07029BFCDB2DCE28D959F2815B16F81798", "483ADA7726A3C4655DA4FBFC0E1108A8FD17B448A68554199C47D08FFB10D4B8");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0364141");
    bigint_from_uint32(&h, 1);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}


// secp384r1, 48 bytes
void create_parameters_ECDH384(EllipticCurveParameter *params)
{
    BigInt p, a, b, n, h;
    Point G;
    bigint_from_hex_string(&p, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFF");
    bigint_from_hex_string(&a, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFF0000000000000000FFFFFFFC");
    bigint_from_hex_string(&b, "B3312FA7E23EE7E4988E056BE3F82D19181D9C6EFE8141120314088F5013875AC656398D8A2ED19D2A85C8EDD3EC2AEF");
    create_point_from_hex(&G, "AA87CA22BE8B05378EB1C71EF320AD746E1D3B628BA79B9859F741E082542A385502F25DBF55296C3A545E3872760AB7", "3617DE4A96262C6F5D9E98BF9292DC29F8F41DBD289A147CE9DA3113B5F0B8C00A60B1CE1D7E819D7A431D7C90EA0E5F");
    bigint_from_hex_string(&n, "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF581A0DB248B0A77AECEC196ACCC52973");
    bigint_from_uint32(&h, 1);
    ec_create_parameters(params, &p, &a, &b, &G, &n, &h);
    bigint_free(&p);
    bigint_free(&a);
    bigint_free(&b);
    bigint_free(&n);
    bigint_free(&h);
    point_free(&G);
}


// secp521r1, 66 bytes
void create_parameters_ECDH521(EllipticCurveParameter *params)
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

void computeECDH(char* dURand, char* dVRand,int keyLength) {

	EllipticCurveParameter params;
    switch(keyLength) {
	  case 192 :
		create_parameters_ECDH192(&params);
        break;
      case 224 :
	  	create_parameters_ECDH224(&params);
        break;
      case 256 :
		create_parameters_ECDH256(&params);
        break;
      case 384 :
		create_parameters_ECDH384(&params);
        break;
      case 521 :
		create_parameters_ECDH521(&params);
        break;
      default :
  		create_parameters_ECDH192(&params);
   }
   
    BigInt dU;
    bigint_from_hex_string(&dU, dURand); // Random number between 0 and n 
	
    BigInt dV;
    bigint_from_hex_string(&dV, dVRand); // Random number between 0 and n 

    ECDH uECDH;
    Point pub_keyU;
    BigInt sharedInfoU;
   
    ECDH vECDH;
    Point pub_keyV;
    BigInt sharedInfoV;
	
    ecdh_generate_public_key(&pub_keyU, &dU, &params);
    ecdh_generate_public_key(&pub_keyV, &dV, &params);

	ecdh_compute_shared_secret(&sharedInfoU, &dU, &pub_keyV, &params);
	ecdh_compute_shared_secret(&sharedInfoV, &dV, &pub_keyU, &params);
	
    ec_create_ECDH(&uECDH, &params, &pub_keyU, &dU, &sharedInfoU);
    ec_create_ECDH(&vECDH, &params, &pub_keyV, &dV, &sharedInfoV);

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

double rdtsc(char* dURand, char* dVRand, int keyLength) {
  printf("======EC keyLength: %d =====\n", keyLength);
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
  while(num_runs < (1 << 1)) { // Changed, only run 1 time now. Originally 14 times
      start = start_tsc();
      for (i = 0; i < num_runs; ++i) {		  
          computeECDH(dURand,dVRand,keyLength);
   }
      cycles = stop_tsc(start);

      if(cycles >= CYCLES_REQUIRED) break;

      num_runs *= 2;  
  }
#endif

  start = start_tsc();
  for (i = 0; i < num_runs; ++i) { 
	computeECDH(dURand,dVRand,keyLength);
  }

  cycles = stop_tsc(start)/num_runs;
  global_opcount = global_opcount/num_runs;
  global_index_count = global_index_count/num_runs;
  double r;  
  r = cycles;
  printf("RDTSC instruction:\n %lf cycles measured => %lf seconds, assuming frequency is %lf MHz. (change in source file if different)\n\n", r, r/(FREQUENCY), (FREQUENCY)/1e6);  
  printf("global_opcount = %" PRIu64 "\n", global_opcount);
  printf("global_index_count = %" PRIu64 "\n", global_index_count);
  return cycles;
}

int main(){
  global_opcount = 0;
  global_index_count = 0; 
 /* */
// secp192
  rdtsc("FEFFFFFFFFFFFFFFFFFFFFFE62F2FC170F69466A74DEFD8D","FEFFFFFFFFFFFFFFFFFFFFFE26F2FC710F69466A74DEFD8D",192); 
  global_opcount = 0;
  global_index_count = 0;   
 
// secp224
  rdtsc("FEFFFFFFFFFFFFFFFFFFFFFFFFFF61A2E0B8F03E13DD29455C5C2A3D","FEFFFFFFFFFFFFFFFFFFFFFFFFFF16A2E0B8F03E13DD29545C5C2A3D",224); 
  global_opcount = 0;
  global_index_count = 0;    
  
  // secp256
  rdtsc("FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF84A03BBFD25E8CD0364141","FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEBAAEDCE6AF48A03BBFD25E8CD0361441",256); 
  global_opcount = 0;
  global_index_count = 0;  
 
  // secp384
  rdtsc("FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F4372DDF851A0DB248B0A77AECEC196ACCC52973","FEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC7634D81F3472DDF581A0DB248B0A77AECEC196ACCC52973",384);  
  global_opcount = 0;
  global_index_count = 0;
  
  // secp521
  rdtsc("01EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA15868783BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409","01EFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA51868738BF2F966B7FCC0148F709A5D03BB5C9B8899C47AEBB6FB71E91386409",521);
  global_opcount = 0;
  global_index_count = 0;  
  return 0;
}
