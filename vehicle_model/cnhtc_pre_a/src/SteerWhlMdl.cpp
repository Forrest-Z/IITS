//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: SteerWhlMdl.cpp
//
// Code generated for Simulink model 'SteerWhlMdl'.
//
// Model version                  : 1.27
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:38 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#include "SteerWhlMdl.h"

#include "SteerWhlMdl_private.h"
#include "look1_binlxpw.h"
P_SteerWhlMdl_T SteerWhlMdlModelClass::SteerWhlMdl_rtP = {
    // Expression: 180/3.14
    //  Referenced by: '<Root>/Gain2'
    57.324840764331206};
// Output and update for referenced model: 'SteerWhlMdl'
void SteerWhlMdlModelClass::step(const real_T *rtu_SteerWhAngle_rad,
                                 real_T *rty_SteerWhAngle_DZ_deg) {
  // Gain: '<Root>/Gain2'
  SteerWhlMdl_B.SteerWhAngle_in =
      SteerWhlMdl_rtP.Gain2_Gain * *rtu_SteerWhAngle_rad;
  // Lookup_n-D: '<Root>/DeadZone'
  *rty_SteerWhAngle_DZ_deg = look1_binlxpw(
      SteerWhlMdl_B.SteerWhAngle_in, rtP_steer_input, rtP_steer_output, 6U);
}
// Model initialize function
void SteerWhlMdlModelClass::initialize() {
  // Registration code
  // block I/O
  { SteerWhlMdl_B.SteerWhAngle_in = 0.0; }
}
// Constructor
SteerWhlMdlModelClass::SteerWhlMdlModelClass() {
  // Currently there is no constructor body generated.
}
// Destructor
SteerWhlMdlModelClass::~SteerWhlMdlModelClass() {
  // Currently there is no destructor body generated.
}
// Real-Time Model get method
RT_MODEL_SteerWhlMdl_T *SteerWhlMdlModelClass::getRTM() {
  return (&SteerWhlMdl_M);
}
// member function to setup error status pointer
void SteerWhlMdlModelClass::setErrorStatusPointer(
    const char_T **rt_errorStatus) {
  rtmSetErrorStatusPointer((&SteerWhlMdl_M), rt_errorStatus);
}
//
// File trailer for generated code.
//
// [EOF]
//
