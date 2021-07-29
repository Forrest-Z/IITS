//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: TCU_private.h
//
// Code generated for Simulink model 'TCU'.
//
// Model version                  : 1.228
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Thu Aug  6 11:43:00 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#ifndef RTW_HEADER_TCU_private_h_
#define RTW_HEADER_TCU_private_h_
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

extern P_TCU_T TCU_rtP;

#endif                                 // RTW_HEADER_TCU_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
