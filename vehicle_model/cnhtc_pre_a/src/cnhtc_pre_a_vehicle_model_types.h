//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: cnhtc_pre_a_vehicle_model_types.h
//
// Code generated for Simulink model 'cnhtc_pre_a_vehicle_model'.
//
// Model version                  : 1.71
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:56 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#ifndef SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_TYPES_H_
#define SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_TYPES_H_
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
#ifndef DEFINED_TYPEDEF_FOR_struct_o4hYTbLTHRHZgQXM4jB8FD_
#define DEFINED_TYPEDEF_FOR_struct_o4hYTbLTHRHZgQXM4jB8FD_
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
  real_T g;
  real_T Cf;
  real_T Cr;
  real_T Lf;
  real_T Lr;
} struct_o4hYTbLTHRHZgQXM4jB8FD;
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
// Parameters (default storage)
typedef struct P_cnhtc_pre_a_vehicle_model_T_ P_cnhtc_pre_a_vehicle_model_T;
// Forward declaration for rtModel
typedef struct tag_RTM_cnhtc_pre_a_vehicle_model_T
    RT_MODEL_cnhtc_pre_a_vehicle_model_T;
//

#endif  // SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_TYPES_H_
// File trailer for generated code.
//
// [EOF]
//
