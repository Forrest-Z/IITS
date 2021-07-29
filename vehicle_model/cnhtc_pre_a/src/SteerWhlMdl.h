//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: SteerWhlMdl.h
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
#ifndef SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_STEERWHLMDL_H_
#define SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_STEERWHLMDL_H_
#include <stddef.h>

#include <cstring>
#ifndef SteerWhlMdl_COMMON_INCLUDES_
#define SteerWhlMdl_COMMON_INCLUDES_
#include "rtwtypes.h" // NOLINT
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif  // SteerWhlMdl_COMMON_INCLUDES_
#include "SteerWhlMdl_types.h"

// Block signals for model 'SteerWhlMdl'
typedef struct {
  real_T SteerWhAngle_in;  // '<Root>/Gain2'
} B_SteerWhlMdl_T;
// Parameters (default storage)
struct P_SteerWhlMdl_T_ {
  real_T Gain2_Gain;  // Expression: 180/3.14
                      //  Referenced by: '<Root>/Gain2'
};
// Real-time Model Data Structure
struct tag_RTM_SteerWhlMdl_T {
  const char_T **errorStatus;
};
// Model block global parameters (default storage)
extern real_T rtP_steer_input[7];   // Variable: steer_input
                                    //  Referenced by: '<Root>/DeadZone'
extern real_T rtP_steer_output[7];  // Variable: steer_output
                                    //  Referenced by: '<Root>/DeadZone'
// Class declaration for model SteerWhlMdl
class SteerWhlMdlModelClass {
  // public data and function members
 public:
  // Tunable parameters
  static P_SteerWhlMdl_T SteerWhlMdl_rtP;
  // model initialize function
  void initialize();
  // model step function
  void step(const real_T *rtu_SteerWhAngle_rad,
            real_T *rty_SteerWhAngle_DZ_deg);
  // Constructor
  SteerWhlMdlModelClass();
  // Destructor
  ~SteerWhlMdlModelClass();
  // Real-Time Model get method
  RT_MODEL_SteerWhlMdl_T *getRTM();
  // member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);
  // private data and function members
 private:
  // Block signals
  B_SteerWhlMdl_T SteerWhlMdl_B;
  // Real-Time Model
  RT_MODEL_SteerWhlMdl_T SteerWhlMdl_M;
};
//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'SteerWhlMdl'
#endif  // SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_STEERWHLMDL_H_
//
// File trailer for generated code.
//
// [EOF]
//
