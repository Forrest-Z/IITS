//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: Engine_ECU_private.h
//
// Code generated for Simulink model 'Engine_ECU'.
//
// Model version                  : 1.361
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Thu Jul  9 18:45:48 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#ifndef RTW_HEADER_Engine_ECU_private_h_
#define RTW_HEADER_Engine_ECU_private_h_
#include "rtwtypes.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        (*((rtm)->errorStatus))
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   (*((rtm)->errorStatus) = (val))
#endif

#ifndef rtmGetErrorStatusPointer
# define rtmGetErrorStatusPointer(rtm) (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatusPointer
# define rtmSetErrorStatusPointer(rtm, val) ((rtm)->errorStatus = (val))
#endif

extern P_Engine_ECU_T Engine_ECU_rtP;

#endif                                 // RTW_HEADER_Engine_ECU_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
