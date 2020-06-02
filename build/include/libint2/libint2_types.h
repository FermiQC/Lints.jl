/*
 *  Copyright (C) 2004-2020 Edward F. Valeev
 *
 *  This file is part of Libint.
 *
 *  Libint is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Libint is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with Libint.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _libint2_libint2types_h_
#define _libint2_libint2types_h_

#include <libint2/util/vector.h>
#include <libint2/util/intrinsic_operations.h>
#include <libint2/util/timer.h>
typedef struct {
#define LIBINT2_DEFINED_PO2 1
LIBINT2_REALTYPE PO2[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_0 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_0[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_1 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_1[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_2 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_2[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_3 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_3[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_4 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_4[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_5 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_5[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_6 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_6[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_7 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_7[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_8 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_8[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_9 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_9[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_10 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_10[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_11 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_11[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0___ElecPot_s___0___Ab__up_12 1
LIBINT2_REALTYPE _aB_s___0___ElecPot_s___0___Ab__up_12[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_0 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_0[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_1 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_1[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_2 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_2[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_3 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_3[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_4 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_4[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_5 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_5[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_6 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_6[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_7 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_7[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_8 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_8[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_9 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_9[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_10 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_10[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_11 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_11[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_12 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_12[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_13 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_13[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_14 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_14[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_15 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_15[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_16 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_16[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_17 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_17[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_18 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_18[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_19 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_19[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_20 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_20[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_21 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_21[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_22 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_22[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_23 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_23[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_24 1
LIBINT2_REALTYPE _aB_s___0__s___1___TwoPRep_s___0__s___1___Ab__up_24[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_AB_x 1
LIBINT2_REALTYPE AB_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_AB_y 1
LIBINT2_REALTYPE AB_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_AB_z 1
LIBINT2_REALTYPE AB_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_BA_x 1
LIBINT2_REALTYPE BA_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_BA_y 1
LIBINT2_REALTYPE BA_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_BA_z 1
LIBINT2_REALTYPE BA_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_BO_x 1
LIBINT2_REALTYPE BO_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_BO_y 1
LIBINT2_REALTYPE BO_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_BO_z 1
LIBINT2_REALTYPE BO_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_CD_x 1
LIBINT2_REALTYPE CD_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_CD_y 1
LIBINT2_REALTYPE CD_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_CD_z 1
LIBINT2_REALTYPE CD_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PA_x 1
LIBINT2_REALTYPE PA_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PA_y 1
LIBINT2_REALTYPE PA_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PA_z 1
LIBINT2_REALTYPE PA_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PB_x 1
LIBINT2_REALTYPE PB_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PB_y 1
LIBINT2_REALTYPE PB_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PB_z 1
LIBINT2_REALTYPE PB_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PC_x 1
LIBINT2_REALTYPE PC_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PC_y 1
LIBINT2_REALTYPE PC_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PC_z 1
LIBINT2_REALTYPE PC_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PO_x 1
LIBINT2_REALTYPE PO_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PO_y 1
LIBINT2_REALTYPE PO_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_PO_z 1
LIBINT2_REALTYPE PO_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_QC_x 1
LIBINT2_REALTYPE QC_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_QC_y 1
LIBINT2_REALTYPE QC_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_QC_z 1
LIBINT2_REALTYPE QC_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_WP_x 1
LIBINT2_REALTYPE WP_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_WP_y 1
LIBINT2_REALTYPE WP_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_WP_z 1
LIBINT2_REALTYPE WP_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_WQ_x 1
LIBINT2_REALTYPE WQ_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_WQ_y 1
LIBINT2_REALTYPE WQ_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_WQ_z 1
LIBINT2_REALTYPE WQ_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__0_Overlap_0_x 1
LIBINT2_REALTYPE _0_Overlap_0_x[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__0_Overlap_0_y 1
LIBINT2_REALTYPE _0_Overlap_0_y[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED__0_Overlap_0_z 1
LIBINT2_REALTYPE _0_Overlap_0_z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_oo2e 1
LIBINT2_REALTYPE oo2e[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_oo2z 1
LIBINT2_REALTYPE oo2z[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_oo2ze 1
LIBINT2_REALTYPE oo2ze[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_roe 1
LIBINT2_REALTYPE roe[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_roz 1
LIBINT2_REALTYPE roz[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_two_alpha0_bra 1
LIBINT2_REALTYPE two_alpha0_bra[LIBINT2_MAX_VECLEN];
#define LIBINT2_DEFINED_two_alpha0_ket 1
LIBINT2_REALTYPE two_alpha0_ket[LIBINT2_MAX_VECLEN];
/** Scratch buffer to hold intermediates */
#ifdef __cplusplus
mutable 
#endif
LIBINT2_REALTYPE* stack;
/** Buffer to hold vector intermediates. Only used by set-level RR code if it is vectorized linewise */
#ifdef __cplusplus
mutable 
#endif
LIBINT2_REALTYPE* vstack;
/** On completion, this contains pointers to computed targets */
#ifdef __cplusplus
mutable 
#endif
LIBINT2_REALTYPE* targets[25];
/** Actual vector length. Not to exceed MAX_VECLEN! If MAX_VECLEN is 1 then veclen is not used */
int veclen;
#if LIBINT2_FLOP_COUNT
/** FLOP counter. Libint must be configured with --enable-flop-counter to allow FLOP counting. It is user's reponsibility to set zero nflops before computing integrals. */
#ifdef __cplusplus
mutable 
#endif
LIBINT2_UINT_LEAST64* nflops;
#endif
#if LIBINT2_PROFILE
#if LIBINT2_CPLUSPLUS_STD >= 2011
/** profiling timers. Libint must be configured with --enable-profile to allow profiling. */
#ifdef __cplusplus
#ifdef __cplusplus
mutable 
#endif
libint2::Timers<2>* timers;
#else // timers are not accessible from C
  void* timers;
#endif
#endif
#endif
#if LIBINT2_ACCUM_INTS
/** If libint was configured with --enable-accum-ints then the target integrals are accumulated. To zero out the targets automatically before the computation, set this to nonzero. */
int zero_out_targets;
#endif
#if LIBINT2_CONTRACTED_INTS
/** If libint was configured with --enable-contracted-ints then contracted integrals are supported. Set this parameter to the total number of primitive combinations. */
int contrdepth;
#endif
} Libint_t;
typedef Libint_t Libint_default_t;
typedef Libint_t Libint_overlap_t;
typedef Libint_t Libint_kinetic_t;
typedef Libint_t Libint_elecpot_t;
typedef Libint_t Libint_1emultipole_t;
typedef Libint_t Libint_2emultipole_t;
typedef Libint_t Libint_3emultipole_t;
typedef Libint_t Libint_sphemultipole_t;
typedef Libint_t Libint_eri_t;
typedef Libint_t Libint_3eri_t;
typedef Libint_t Libint_2eri_t;
#endif

