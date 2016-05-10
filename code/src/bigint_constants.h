#ifndef __BIGINT_CONSTANTS_H_
#define __BIGINT_CONSTANTS_H_

// Size in bytes of the memory allocated for bigint objects
#ifndef BIGINT_SIZE
    #define BIGINT_SIZE 1024
#endif

// Alignment of bigint buffers in bytes
#define BIGINT_ALIGNMENT 16

// Size of the header informations of a BigInt (one uint64_t field)
#define BIGINT_HEADER_SIZE 8
#define BIGINT_HEADER_PADDING (BIGINT_ALIGNMENT - (BIGINT_HEADER_SIZE % BIGINT_ALIGNMENT))
#define BIGINT_OCTETS_COUNT (BIGINT_SIZE - BIGINT_HEADER_SIZE - BIGINT_HEADER_PADDING)

#if (BIGINT_SIZE / BIGINT_ALIGNMENT) * BIGINT_ALIGNMENT != BIGINT_SIZE
    #error "Please specify BIGINT_SIZE as a multiple of BIGINT_ALIGNMENT"
#endif

// Define bigint tags here:
// ==========================
#define BI_COMMONS_ZERO_TAG 0
#define BI_COMMONS_ONE_TAG 1
#define BI_TESTS_A_TAG 2
#define BI_TESTS_B_TAG 3
#define BI_TESTS_C_TAG 4
#define BI_TESTS_P_TAG 6
#define BI_TESTS_X_TAG 7
#define BI_TESTS_Y_TAG 8
#define BI_TESTS_EXPECTED_TAG 9
#define BI_MONTGOMERYMUL_XMONT_TAG 10
#define BI_MONTGOMERYMUL_YMONT_TAG 11
#define BI_DIVIDE_U_TAG 12
#define BI_DIVIDE_V_TAG 13
#define BI_DIVIDE_X1_TAG 14
#define BI_DIVIDE_X2_TAG 15
#define BI_POINTISONCURVE_XSQUARED_TAG 16

// Update the number of tags
// after defining a new one:
#define BI_TAGS_COUNT 16
// ==========================

#endif