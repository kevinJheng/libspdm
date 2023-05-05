/**
 *  Copyright Notice:
 *  Copyright 2023 DMTF. All rights reserved.
 *  License: BSD 3-Clause License. For full text see link: https://github.com/DMTF/libspdm/blob/main/LICENSE.md
 **/

#include "internal/libspdm_crypt_lib.h"
#include "internal/libspdm_common_lib.h"
#include "internal/libspdm_fips_lib.h"

#if LIBSPDM_FIPS_MODE

/**
 * RSA_SSA(RSASSA-PKCS1 v1.5) self_test
 **/
bool libspdm_fips_selftest_rsa_ssa(void *fips_selftest_context)
{
    bool result = true;

#if LIBSPDM_RSA_SSA_SUPPORT
    libspdm_fips_selftest_context *context = fips_selftest_context;
    LIBSPDM_ASSERT(fips_selftest_context != NULL);

    /* any test fail cause the FIPS fail*/
    if (context->tested_algo != context->self_test_result) {
        return false;
    }

    /* check if run before.*/
    if ((context->tested_algo & LIBSPDM_FIPS_SELF_TEST_RSA_SSA) != 0) {
        return true;
    }

    uint8_t signature[1024];
    size_t sig_size;
    void *rsa;

    sig_size = sizeof(signature);
    libspdm_zero_mem(signature, sig_size);

    const uint8_t public_n[] = {
        0xd2, 0x24, 0xb6, 0x24, 0x58, 0x15, 0x1f, 0xef,
        0x7c, 0x93, 0x50, 0x10, 0xe9, 0x3f, 0x01, 0x1a,
        0xd9, 0x2a, 0x2d, 0x16, 0x28, 0xfc, 0x27, 0xc1,
        0x66, 0x33, 0x12, 0xcc, 0x0e, 0x61, 0xf5, 0x90,
        0x46, 0x3a, 0x8f, 0x5d, 0x82, 0xdb, 0x99, 0x7f,
        0x41, 0xa1, 0x68, 0xaf, 0xb0, 0x15, 0xc4, 0xa5,
        0x2a, 0xf4, 0xd9, 0x49, 0x7f, 0x55, 0x57, 0x28,
        0xe5, 0xf8, 0xbe, 0xcf, 0xfd, 0x7e, 0x5c, 0x7e,
        0x5a, 0x6f, 0xcb, 0x8c, 0xe1, 0x3d, 0x7e, 0x9e,
        0x5d, 0x0f, 0x51, 0x97, 0x19, 0x37, 0x81, 0x39,
        0x11, 0xcb, 0xf9, 0x8c, 0x2f, 0x9a, 0x83, 0xb1,
        0xc9, 0x13, 0x08, 0x5e, 0x38, 0xc4, 0xef, 0x99,
        0xbd, 0xc9, 0xe4, 0x05, 0x04, 0xab, 0xfd, 0x9e,
        0xc2, 0x95, 0x29, 0xe9, 0x42, 0x8d, 0x3b, 0x06,
        0x63, 0x6e, 0xcb, 0x01, 0x7f, 0x9d, 0x10, 0x69,
        0xf8, 0x53, 0x64, 0x9a, 0x43, 0x54, 0x62, 0x0f,
        0x9a, 0x50, 0xcc, 0x2d, 0x32, 0xfb, 0x5c, 0x22,
        0x10, 0x98, 0xa7, 0x52, 0xdb, 0xf2, 0x3a, 0x43,
        0x68, 0x28, 0xce, 0x3d, 0x58, 0xc4, 0x8b, 0xd4,
        0x94, 0xd7, 0x85, 0xea, 0x4b, 0x01, 0xab, 0x12,
        0x7e, 0xc3, 0x04, 0x97, 0xfb, 0xf8, 0x73, 0x79,
        0x89, 0x49, 0xf4, 0x06, 0x67, 0x8e, 0x07, 0x4e,
        0x0d, 0x91, 0x19, 0x53, 0x55, 0x46, 0xd1, 0xf7,
        0x76, 0x18, 0xf7, 0x64, 0x36, 0x10, 0xdd, 0xa7,
        0xac, 0x00, 0xca, 0x10, 0x3d, 0x4e, 0x05, 0x6a,
        0x7d, 0x42, 0x89, 0xc4, 0x74, 0xf4, 0x93, 0x67,
        0x51, 0xe0, 0xc9, 0x76, 0x21, 0x2f, 0xc3, 0xb9,
        0x30, 0x28, 0x91, 0x76, 0x56, 0xbf, 0xd8, 0x2d,
        0xcf, 0x5b, 0xdc, 0x42, 0xf9, 0x1f, 0xf1, 0xa8,
        0xc9, 0x3a, 0x4b, 0x0f, 0xff, 0x7a, 0xa0, 0xf9,
        0xe8, 0x87, 0x98, 0x38, 0x30, 0xa8, 0x96, 0x45,
        0x28, 0x3a, 0x86, 0x28, 0x02, 0xa2, 0x96, 0xcf
    };

    const uint8_t e[] = {
        0x00, 0x01, 0x00, 0x01,
    };

    const uint8_t private_d[] = {
        0x57, 0x87, 0x04, 0xfa, 0x94, 0x59, 0x90, 0x28,
        0xaf, 0x09, 0xa8, 0xc2, 0xb2, 0x74, 0x14, 0xa0,
        0xbb, 0x2d, 0x4f, 0x04, 0x38, 0xe3, 0xf6, 0x27,
        0x1e, 0xcb, 0x4d, 0x1c, 0x03, 0x2d, 0x98, 0x1b,
        0x94, 0xb4, 0xd5, 0x7c, 0x0c, 0x82, 0x2d, 0x28,
        0x0d, 0x0d, 0x0e, 0xce, 0x86, 0x98, 0x3a, 0x84,
        0xd5, 0x24, 0x90, 0xd0, 0x85, 0x21, 0xe5, 0xa0,
        0xda, 0x50, 0xc6, 0x21, 0x59, 0xa3, 0x65, 0x21,
        0x17, 0xc8, 0x12, 0xcf, 0x46, 0x0d, 0xd8, 0x0c,
        0x5c, 0x14, 0x82, 0x56, 0x5e, 0x21, 0x79, 0x48,
        0x6c, 0xfa, 0x39, 0xa1, 0xc3, 0x3e, 0x27, 0x76,
        0x48, 0x9b, 0x0d, 0xd4, 0x38, 0xef, 0x06, 0x21,
        0x52, 0x24, 0xa2, 0x3d, 0xd8, 0xd9, 0x4e, 0x54,
        0xef, 0x15, 0x34, 0x14, 0xbd, 0x2c, 0x98, 0x16,
        0x2c, 0x1a, 0x3c, 0xa2, 0x0e, 0x26, 0x3c, 0x6c,
        0xf7, 0x0a, 0xbd, 0x0f, 0x67, 0xd5, 0xe0, 0xd5,
        0x7f, 0x90, 0x82, 0x49, 0xa7, 0x0f, 0xe8, 0x77,
        0xe3, 0x67, 0x39, 0xfe, 0x1f, 0x5f, 0x70, 0xa8,
        0x47, 0x77, 0x3a, 0x9a, 0xda, 0xc1, 0x63, 0x7a,
        0x5f, 0x98, 0xbc, 0x2a, 0x55, 0xee, 0xfc, 0x7c,
        0xe0, 0xf6, 0x0b, 0xe0, 0xe5, 0x77, 0x8c, 0x1f,
        0x8e, 0x60, 0xc5, 0xc5, 0x24, 0xb7, 0x95, 0xff,
        0x5f, 0xb2, 0xda, 0xf8, 0xb8, 0x3a, 0xc2, 0x9e,
        0xe1, 0x68, 0x4f, 0x27, 0xde, 0x24, 0xbb, 0x92,
        0xb0, 0x6c, 0xf3, 0x4c, 0xbf, 0x6c, 0x74, 0x05,
        0x6f, 0xe9, 0x6c, 0x7a, 0x11, 0x3d, 0xb7, 0xe6,
        0xbc, 0xc9, 0x35, 0x4a, 0x5c, 0xc2, 0xd3, 0xf7,
        0x54, 0x94, 0xb2, 0x7c, 0x17, 0x01, 0xfa, 0x08,
        0xfc, 0xb3, 0xf5, 0x5b, 0xb2, 0xc0, 0x07, 0xdb,
        0x23, 0x6b, 0xac, 0xf9, 0x29, 0x8b, 0xe7, 0xa9,
        0x0f, 0x48, 0x7f, 0x1d, 0x6e, 0x76, 0x3c, 0x3b,
        0x62, 0xe9, 0xc1, 0xfd, 0xd4, 0xc0, 0x9d, 0xf9
    };

    const uint8_t input_data[] = {
        0x19, 0x90, 0x2d, 0x02, 0x34, 0x6e, 0xd5, 0x90,
        0x0e, 0x69, 0x51, 0x2f, 0xf2, 0xbd, 0x9d, 0x33,
        0x26, 0x71, 0x8f, 0x62, 0xa0, 0x01, 0xbd, 0xfd,
        0x94, 0xe2, 0x98, 0x17, 0x24, 0xfd, 0xca, 0xf0
    };

    const uint8_t expected_sig[] = {
        0x7b, 0x5c, 0x58, 0xd7, 0x81, 0xfc, 0xbb, 0x82,
        0x65, 0x1f, 0x17, 0xe2, 0x29, 0x75, 0x2a, 0x20,
        0xe3, 0xa0, 0x46, 0x3b, 0xd0, 0xd2, 0x10, 0x9a,
        0x09, 0x85, 0xe1, 0x4b, 0x68, 0x11, 0x64, 0xc9,
        0x44, 0xf4, 0x42, 0x11, 0x31, 0xbe, 0x02, 0xd4,
        0x2e, 0xe2, 0x8c, 0xb7, 0x33, 0xb9, 0xec, 0x0f,
        0xac, 0xad, 0x07, 0x74, 0xd7, 0xc4, 0xe7, 0x32,
        0xae, 0xd0, 0x01, 0xbe, 0x14, 0x5f, 0x40, 0x54,
        0x48, 0x4c, 0x24, 0x69, 0x39, 0x6b, 0x43, 0x3d,
        0xe3, 0xde, 0x06, 0x57, 0x13, 0xa9, 0x43, 0xef,
        0x4e, 0x75, 0x95, 0x5c, 0x77, 0x3e, 0xe1, 0x76,
        0x0c, 0xff, 0x51, 0x49, 0xa6, 0x62, 0x2a, 0x82,
        0x01, 0x76, 0xec, 0x2c, 0xcd, 0x48, 0x0d, 0x2e,
        0x6b, 0xdd, 0x8a, 0xd0, 0x2d, 0xaf, 0x3d, 0x5a,
        0xee, 0xc4, 0x6a, 0xdd, 0x04, 0x47, 0xb1, 0x5e,
        0xd0, 0x90, 0xee, 0xa6, 0xe7, 0x0f, 0x99, 0xb2,
        0x4e, 0xe4, 0xee, 0x30, 0x9e, 0xb2, 0x5e, 0xb9,
        0x7c, 0x75, 0xe1, 0xba, 0x60, 0x49, 0x94, 0x9b,
        0xd6, 0xa7, 0xe1, 0x9e, 0x24, 0xbc, 0x9e, 0x37,
        0xcf, 0x07, 0xea, 0xa8, 0xaf, 0xcc, 0xee, 0xf1,
        0x22, 0x2a, 0xdb, 0x3d, 0x4f, 0x29, 0xf4, 0x48,
        0x49, 0x56, 0xb4, 0xc6, 0x89, 0x3b, 0x7e, 0xd7,
        0x08, 0x7c, 0x2a, 0xb4, 0xcc, 0x6e, 0x4c, 0x12,
        0x6f, 0xbc, 0xac, 0xfb, 0xb0, 0xe5, 0xf7, 0xc7,
        0x57, 0xb3, 0x84, 0xa6, 0xb9, 0x2f, 0x59, 0xea,
        0xaa, 0xf0, 0x9a, 0xe7, 0xff, 0xbc, 0xf8, 0x12,
        0x09, 0x6e, 0x2b, 0xf8, 0x24, 0xc0, 0x45, 0xb4,
        0x0c, 0x23, 0x05, 0x7d, 0xf5, 0xc6, 0x8a, 0x19,
        0x30, 0x8a, 0x40, 0x5a, 0xc6, 0xbd, 0x66, 0xd5,
        0xdf, 0xc1, 0xbb, 0x8f, 0x26, 0x2d, 0xd1, 0xaf,
        0x46, 0x47, 0xef, 0x2b, 0x3d, 0x73, 0xd5, 0xcb,
        0x4a, 0xda, 0xf8, 0x0e, 0xf6, 0xdf, 0x5e, 0x7b
    };

    rsa = libspdm_rsa_new();
    if (rsa == NULL) {
        LIBSPDM_DEBUG((LIBSPDM_DEBUG_INFO, "RSA_PSS rsa new failed \n"));
        result = false;
        goto update;
    }

    result = libspdm_rsa_set_key(rsa, LIBSPDM_RSA_KEY_N, public_n, sizeof(public_n));
    if (!result) {
        LIBSPDM_DEBUG((LIBSPDM_DEBUG_INFO, "RSA_PSS rsa set key failed \n"));
        libspdm_rsa_free(rsa);
        result = false;
        goto update;
    }

    result = libspdm_rsa_set_key(rsa, LIBSPDM_RSA_KEY_E, e, sizeof(e));
    if (!result) {
        LIBSPDM_DEBUG((LIBSPDM_DEBUG_INFO, "RSA_PSS rsa set key failed \n"));
        libspdm_rsa_free(rsa);
        result = false;
        goto update;
    }

    result = libspdm_rsa_set_key(rsa, LIBSPDM_RSA_KEY_D, private_d, sizeof(private_d));
    if (!result) {
        LIBSPDM_DEBUG((LIBSPDM_DEBUG_INFO, "RSA_PSS rsa set key failed \n"));
        libspdm_rsa_free(rsa);
        result = false;
        goto update;
    }

    result = libspdm_rsa_pkcs1_sign_with_nid(rsa, LIBSPDM_CRYPTO_NID_SHA256,
                                             input_data, sizeof(input_data),
                                             signature, &sig_size);
    if (!result) {
        LIBSPDM_DEBUG((LIBSPDM_DEBUG_INFO, "RSA_PSS rsa sign failed \n"));
        libspdm_rsa_free(rsa);
        result = false;
        goto update;
    }

    /*KAT test*/
    if (sig_size != sizeof(expected_sig)) {
        LIBSPDM_DEBUG((LIBSPDM_DEBUG_INFO, "RSA_PSS KAT failed \n"));
        libspdm_rsa_free(rsa);
        result = false;
        goto update;
    }

    if (!libspdm_consttime_is_mem_equal(signature, expected_sig,
                                        sizeof(expected_sig))) {
        LIBSPDM_DEBUG((LIBSPDM_DEBUG_INFO, "RSA_PSS KAT failed \n"));
        libspdm_rsa_free(rsa);
        result = false;
        goto update;
    }

    result = libspdm_rsa_pkcs1_verify_with_nid(rsa, LIBSPDM_CRYPTO_NID_SHA256,
                                               input_data, sizeof(input_data),
                                               signature, sig_size);
    if (!result) {
        LIBSPDM_DEBUG((LIBSPDM_DEBUG_INFO, "RSA_PSS selftest failed \n"));
        libspdm_rsa_free(rsa);
        result = false;
        goto update;
    }

    libspdm_rsa_free(rsa);

update:
    /* mark it as tested*/
    context->tested_algo |= LIBSPDM_FIPS_SELF_TEST_RSA_SSA;

    /* record test result*/
    if (result) {
        context->self_test_result |= LIBSPDM_FIPS_SELF_TEST_RSA_SSA;
    } else {
        context->self_test_result &= ~LIBSPDM_FIPS_SELF_TEST_RSA_SSA;
    }

#endif/*LIBSPDM_RSA_SSA_SUPPORT*/

    return result;
}

#endif