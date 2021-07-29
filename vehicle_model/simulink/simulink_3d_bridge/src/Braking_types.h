//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: Braking_types.h
//
// Code generated for Simulink model 'Braking'.
//
// Model version                  : 1.20
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Thu Aug  6 11:42:34 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#ifndef RTW_HEADER_Braking_types_h_
#define RTW_HEADER_Braking_types_h_
#include "rtwtypes.h"
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

// Parameters (default storage)
typedef struct P_Braking_T_ P_Braking_T;

// Forward declaration for rtModel
typedef struct tag_RTM_Braking_T RT_MODEL_Braking_T;

#endif                                 // RTW_HEADER_Braking_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
