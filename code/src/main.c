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
void computeECDH(char* dURand, char* dVRand, int keyLength) {

    EllipticCurveParameter params;
    switch(keyLength) {
    case 192 :
	ec_generate_parameter(&params, SECP192K1);
        break;
    case 224 :
	ec_generate_parameter(&params, SECP224R1);
        break;
    case 256 :
	ec_generate_parameter(&params, SECP256K1);
        break;
    case 384 :
	ec_generate_parameter(&params, SECP384R1);
        break;
    case 521 :
	ec_generate_parameter(&params, SECP521R1);
        break;
    default :
	ec_generate_parameter(&params, SECP192K1);
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
