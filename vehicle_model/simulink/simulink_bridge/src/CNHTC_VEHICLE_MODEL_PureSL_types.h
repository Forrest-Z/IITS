//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: CNHTC_VEHICLE_MODEL_PureSL_types.h
//
// Code generated for Simulink model 'CNHTC_VEHICLE_MODEL_PureSL'.
//
// Model version                  : 1.92
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Thu Jul  9 18:47:09 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#ifndef RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_types_h_
#define RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_types_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#ifndef DEFINED_TYPEDEF_FOR_struct_xuvldbp4qY393voN3kPmeB_
#define DEFINED_TYPEDEF_FOR_struct_xuvldbp4qY393voN3kPmeB_

typedef struct {
  real_T bwdAxlePre_Table[52];
  real_T fwdAxlePre_Table[52];
  real_T braCmd_BP[26];
  real_T mass_BP[2];
  real_T Tc_ValLag;
  real_T TDelay;
  real_T PreUpRate;
  real_T PreDnRate;
} struct_xuvldbp4qY393voN3kPmeB;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_FRG4WHA92HxYEB6reTTd6E_
#define DEFINED_TYPEDEF_FOR_struct_FRG4WHA92HxYEB6reTTd6E_

typedef struct {
  real_T InitialLongPosition;
  real_T InitialLatPosition;
  real_T InitialYawAngle;
  real_T InitialLongVel;
  real_T InitialLatVel;
  real_T InitialYawRate;
  real_T InitGearPos;
  real_T Mass;
  real_T Iz;
  real_T a;
  real_T b;
  real_T WhlBase;
  real_T TrackWdth;
  real_T Cd;
  real_T FrtArea;
  real_T Rt;
  real_T BraCylinderArea;
  real_T Cf;
  real_T Cr;
  real_T Lf;
  real_T Lr;
} struct_FRG4WHA92HxYEB6reTTd6E;

#endif

#ifndef DEFINED_TYPEDEF_FOR_struct_1Bydkh1pAHvKL6MKYnygkF_
#define DEFINED_TYPEDEF_FOR_struct_1Bydkh1pAHvKL6MKYnygkF_

typedef struct {
  real_T mu_Sta;
  real_T mu_Dyn;
  real_T Rt;
  real_T DrLiEff;
  real_T GbRatioTable[13];
  real_T GbRatioBp[13];
  real_T Jn[13];
  real_T DampingCoeffs[13];
  real_T GearEta[13];
  real_T DifRatio;
  real_T Cyf;
  real_T Cyr;
  real_T EngTorMaxTable[12];
  real_T EngTorMaxBp[12];
  real_T Tau_TransTor;
  real_T Tau_TransOmega;
  real_T EngSpdMax;
  real_T EngSpdMin;
  real_T PedalTable[390];
  real_T PedalBp_ne[15];
  real_T PedalBp_tor[26];
  real_T Iw_kgm2;
  real_T Ie_kgm2;
  real_T EngReferTor_Nm;
} struct_1Bydkh1pAHvKL6MKYnygkF;

#endif

// Parameters for system: '<S125>/TwoDofDynamic'
typedef struct P_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T_
  P_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T;

// Parameters (default storage)
typedef struct P_CNHTC_VEHICLE_MODEL_PureSL_T_ P_CNHTC_VEHICLE_MODEL_PureSL_T;

// Forward declaration for rtModel
typedef struct tag_RTM_CNHTC_VEHICLE_MODEL_PureSL_T
  RT_MODEL_CNHTC_VEHICLE_MODEL_PureSL_T;

#endif                        // RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
