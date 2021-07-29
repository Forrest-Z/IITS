//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic.h
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
#ifndef RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_h_
#define RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_h_
#include <cmath>
#ifndef CNHTC_VEHICLE_MODEL_PureSL_COMMON_INCLUDES_
# define CNHTC_VEHICLE_MODEL_PureSL_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                           // CNHTC_VEHICLE_MODEL_PureSL_COMMON_INCLUDES_

#include "CNHTC_VEHICLE_MODEL_PureSL_types.h"

// Block signals for system '<S125>/TwoDofDynamic'
typedef struct {
  real_T Lf;                           // '<S130>/Lf'
  real_T sum;                          // '<S130>/sum'
  real_T Saturation;                   // '<S130>/Saturation'
  real_T Divide;                       // '<S130>/Divide'
  real_T Gain3;                        // '<S130>/Gain3'
  real_T th_f;                         // '<S130>/sum2'
  real_T Ff;                           // '<S130>/Cf'
  real_T Cos;                          // '<S130>/Cos'
  real_T Lr;                           // '<S130>/Lr'
  real_T sum1;                         // '<S130>/sum1'
  real_T th_r;                         // '<S130>/Divide1'
  real_T Gain1;                        // '<S130>/Gain1'
  real_T Fr;                           // '<S130>/Cr'
  real_T Divide2;                      // '<S130>/Divide2'
  real_T Divide3;                      // '<S130>/Divide3'
  real_T sum4;                         // '<S130>/sum4'
  real_T Divide4;                      // '<S130>/Divide4'
  real_T Lf_2;                         // '<S130>/Lf_2'
  real_T Lr_2;                         // '<S130>/Lr_2'
  real_T sum5;                         // '<S130>/sum5'
  real_T Gain1_l;                      // '<S131>/Gain1'
  real_T Sum;                          // '<S131>/Sum'
  real_T Saturation_a;                 // '<S131>/Saturation'
  real_T sum3;                         // '<S130>/sum3'
  real_T inv_Iz;                       // '<S130>/inv_Iz'
  real_T Gain1_k;                      // '<S132>/Gain1'
  real_T Sum_c;                        // '<S132>/Sum'
  real_T Saturation_p;                 // '<S132>/Saturation'
} B_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T;

// Block states (default storage) for system '<S125>/TwoDofDynamic'
typedef struct {
  real_T UnitDelay_DSTATE;             // '<S131>/Unit Delay'
  real_T UnitDelay_DSTATE_j;           // '<S132>/Unit Delay'
} DW_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T;

// Parameters for system: '<S125>/TwoDofDynamic'
struct P_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T_ {
  real_T UnitDelay_InitialCondition;   // Expression: 0
                                          //  Referenced by: '<S131>/Unit Delay'

  real_T UnitDelay_InitialCondition_b; // Expression: 0
                                          //  Referenced by: '<S132>/Unit Delay'

  real_T Saturation_UpperSat;          // Expression: inf
                                          //  Referenced by: '<S130>/Saturation'

  real_T Saturation_LowerSat;          // Expression: 5
                                          //  Referenced by: '<S130>/Saturation'

  real_T Gain3_Gain;                   // Expression: -1
                                          //  Referenced by: '<S130>/Gain3'

  real_T Gain1_Gain;                   // Expression: -1
                                          //  Referenced by: '<S130>/Gain1'

  real_T Saturation_UpperSat_c;        // Expression: 1
                                          //  Referenced by: '<S131>/Saturation'

  real_T Saturation_LowerSat_o;        // Expression: -1
                                          //  Referenced by: '<S131>/Saturation'

  real_T Saturation_UpperSat_p;        // Expression: 1
                                          //  Referenced by: '<S132>/Saturation'

  real_T Saturation_LowerSat_c;        // Expression: -1
                                          //  Referenced by: '<S132>/Saturation'

};

#endif                // RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_h_

//
// File trailer for generated code.
//
// [EOF]
//
