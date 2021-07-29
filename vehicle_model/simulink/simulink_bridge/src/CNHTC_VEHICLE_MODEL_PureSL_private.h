//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: CNHTC_VEHICLE_MODEL_PureSL_private.h
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
#ifndef RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_private_h_
#define RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_private_h_
#include "rtwtypes.h"
#include "zero_crossing_types.h"

// Private macros used by the generated code to access rtModel
#ifndef rtmSetFirstInitCond
# define rtmSetFirstInitCond(rtm, val) ((rtm)->Timing.firstInitCondFlag = (val))
#endif

#ifndef rtmIsFirstInitCond
# define rtmIsFirstInitCond(rtm)       ((rtm)->Timing.firstInitCondFlag)
#endif

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm)       (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

// private model entry point functions
extern void CNHTC_VEHICLE_MODEL_PureSL_derivatives();

#endif                      // RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_private_h_

//
// File trailer for generated code.
//
// [EOF]
//
