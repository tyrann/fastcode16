#ifndef __BIGINT_CONSTANTS_H_
#define __BIGINT_CONSTANTS_H_

// Size in bytes of the memory allocated for bigint objects
#ifndef BIGINT_SIZE
    #define BIGINT_SIZE 160
#endif

// Alignment of bigint buffers in bytes
#define BIGINT_ALIGNMENT 16

// Size of the header informations of a BigInt (one uint64_t field)
#define BIGINT_HEADER_SIZE 8
#define BIGINT_HEADER_PADDING (BIGINT_ALIGNMENT - (BIGINT_HEADER_SIZE % BIGINT_ALIGNMENT))
#define BIGINT_BLOCKS_COUNT (BIGINT_SIZE - BIGINT_HEADER_SIZE - BIGINT_HEADER_PADDING) / 8

#if (BIGINT_SIZE / BIGINT_ALIGNMENT) * BIGINT_ALIGNMENT != BIGINT_SIZE
    #error "Please specify BIGINT_SIZE as a multiple of BIGINT_ALIGNMENT"
#endif

// Define bigint tags here:
// ==========================
#define BI_COMMONS_ZERO_TAG 0
#define BI_COMMONS_ONE_TAG 1
#define BI_COMMONS_TWO_TAG 2
#define BI_COMMONS_THREE_TAG 3

#define BI_PARAMS_A_TAG 4
#define BI_PARAMS_B_TAG 5
#define BI_PARAMS_GX_TAG 6
#define BI_PARAMS_GY_TAG 7
#define BI_PARAMS_H_TAG 8
#define BI_PARAMS_N_TAG 9
#define BI_PARAMS_P_TAG 10

#define BI_MONTGOMERYMUL_XMONT_TAG 11
#define BI_MONTGOMERYMUL_YMONT_TAG 12
#define BI_DIVIDE_U_TAG 13
#define BI_DIVIDE_V_TAG 14
#define BI_DIVIDE_X1_TAG 15
#define BI_DIVIDE_X2_TAG 16

#define BI_POINTISONCURVE_XSQUARED_TAG 17
#define BI_POINTISONCURVE_XSQUAREDREV_TAG 18
#define BI_POINTISONCURVE_XRESULT_TAG 19
#define BI_POINTISONCURVE_XRESULTREV_TAG 20
#define BI_POINTISONCURVE_YRESULT_TAG 21
#define BI_POINTISONCURVE_YRESULTREV_TAG 22
#define BI_POINTISONCURVE_AX_TAG 23
#define BI_POINTISONCURVE_AXREV_TAG 24

#define BI_POINTADD_NUMERATOR_TAG 25
#define BI_POINTADD_TMP_TAG 26
#define BI_POINTADD_DENOMINATOR_TAG 27
#define BI_POINTADD_LAMBDA_TAG 28
#define BI_POINTADD_LAMBDASQUARED_TAG 29
#define BI_POINTADD_XTWICE_TAG 30
#define BI_POINTADD_Y1ADDINVERSE_TAG 31
#define BI_POINTADD_X1ADDINVERSE_TAG 32
#define BI_POINTADD_Y1_TAG 33
#define BI_POINTADD_X1MINUSX3_TAG 34
#define BI_POINTMUL_P2X_TAG 35
#define BI_POINTMUL_P2Y_TAG 36

#define BI_ECDH_DU_TAG 37
#define BI_ECDH_DV_TAG 38
#define BI_ECDH_SHAREDU_TAG 39
#define BI_ECDH_SHAREDV_TAG 40
#define BI_ECDH_PUBKEYUX_TAG 41
#define BI_ECDH_PUBKEYUY_TAG 42
#define BI_ECDH_PUBKEYVX_TAG 43
#define BI_ECDH_PUBKEYVY_TAG 44
#define BI_ECDH_SHAREDSECRETY_TAG 45

#define BI_POINT_CONVERT_TO_MONTGOMERY_SPACE_X_TAG 46
#define BI_POINT_CONVERT_TO_MONTGOMERY_SPACE_Y_TAG 47
#define BI_POINT_REVERT_FROM_MONTGOMERY_SPACE_X_TAG 48
#define BI_POINT_REVERT_FROM_MONTGOMERY_SPACE_Y_TAG 49

#define BI_EC_PARAMETER_CONVERT_TO_MONTGOMERY_SPACE_A_TAG 50
#define BI_EC_PARAMETER_CONVERT_TO_MONTGOMERY_SPACE_B_TAG 51
#define BI_EC_PARAMETER_REVERT_FROM_MONTGOMERY_SPACE_A_TAG 52
#define BI_EC_PARAMETER_REVERT_FROM_MONTGOMERY_SPACE_B_TAG 53

#define BI_EC_PARAMS_TWO_TAG 54
#define BI_EC_PARAMS_THREE_TAG 55

#define BI_MAIN_SHAREDINFOU_CONV_TAG 56
#define BI_MAIN_SHAREDINFOV_CONV_TAG 57

#define BI_MONTGOMERY_INIT_PRIME_TAG 58

#define BI_MONTGOMERY_MUL_TMP1_TAG 59
#define BI_MONTGOMERY_MUL_TMP2_TAG 60

#define BI_TESTS_A_TAG 61
#define BI_TESTS_AX_TAG 62
#define BI_TESTS_AY_TAG 63
#define BI_TESTS_BX_TAG 64
#define BI_TESTS_BY_TAG 65
#define BI_TESTS_B_TAG 66
#define BI_TESTS_C_TAG 67
#define BI_TESTS_D_TAG 68
#define BI_TESTS_DU_TAG 69
#define BI_TESTS_DV_TAG 70
#define BI_TESTS_P_TAG 71
#define BI_TESTS_PX_TAG 72
#define BI_TESTS_PY_TAG 73
#define BI_TESTS_QX_TAG 74
#define BI_TESTS_QY_TAG 75
#define BI_TESTS_X_TAG 76
#define BI_TESTS_X1_TAG 77
#define BI_TESTS_X2_TAG 78
#define BI_TESTS_Y_TAG 79
#define BI_TESTS_Y1_TAG 80
#define BI_TESTS_Y2_TAG 81
#define BI_TESTS_EXPECTED_TAG 82
#define BI_TESTS_EXPECTEDX_TAG 83
#define BI_TESTS_EXPECTEDY_TAG 84
#define BI_TESTS_RESULTX_TAG 85
#define BI_TESTS_RESULTY_TAG 86
#define BI_TESTS_PINFX_TAG 87
#define BI_TESTS_PINFY_TAG 88
#define BI_TESTS_PUBKEYUX_TAG 89
#define BI_TESTS_PUBKEYUY_TAG 90
#define BI_TESTS_PUBKEYVX_TAG 91
#define BI_TESTS_PUBKEYVY_TAG 92
#define BI_TESTS_SHAREDU_TAG 93
#define BI_TESTS_SHAREDV_TAG 94
#define BI_TESTS_X_CONV_TAG 95
#define BI_TESTS_Y_CONV_TAG 96

// Update the number of tags
// after defining a new one:
#define BI_TAGS_COUNT 97
// ==========================

#endif
