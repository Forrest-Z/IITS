//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: cnhtc_pre_a_vehicle_model_private.h
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
#ifndef SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_PRIVATE_H_
#define SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_PRIVATE_H_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
// Private macros used by the generated code to access rtModel
#ifndef rtmSetFirstInitCond
#define rtmSetFirstInitCond(rtm, val) ((rtm)->Timing.firstInitCondFlag = (val))
#endif
#ifndef rtmIsFirstInitCond
#define rtmIsFirstInitCond(rtm) ((rtm)->Timing.firstInitCondFlag)
#endif
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm) (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif
#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm) (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif
#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val) ((rtm)->Timing.t = (val))
#endif

// private model entry point functions
extern void cnhtc_pre_a_vehicle_model_derivatives();

#endif  // SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_PRIVATE_H_
//
// File trailer for generated code.
//
// [EOF]
//
