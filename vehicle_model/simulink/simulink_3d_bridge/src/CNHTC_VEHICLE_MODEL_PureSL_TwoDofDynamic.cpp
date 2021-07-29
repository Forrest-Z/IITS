//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic.cpp
//
// Code generated for Simulink model 'CNHTC_VEHICLE_MODEL_PureSL'.
//
// Model version                  : 1.97
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Thu Aug  6 11:43:12 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#include "CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic.h"

// Include model header file for global data
#include "CNHTC_VEHICLE_MODEL_PureSL.h"
#include "CNHTC_VEHICLE_MODEL_PureSL_private.h"

// System initialize for atomic system: '<S125>/TwoDofDynamic'
void CNHTC_VEHICLE_MODEL_PureSLModelClass::
  CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_Init
  (DW_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localDW,
   P_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localP)
{
  // InitializeConditions for UnitDelay: '<S131>/Unit Delay'
  localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

  // InitializeConditions for UnitDelay: '<S132>/Unit Delay'
  localDW->UnitDelay_DSTATE_j = localP->UnitDelay_InitialCondition_b;
}

// Outputs for atomic system: '<S125>/TwoDofDynamic'
void CNHTC_VEHICLE_MODEL_PureSLModelClass::
  CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic(real_T rtu_WhlAngF_rad, real_T
  rtu_vx_mps, real_T rtu_vehicle_mass_kg, real_T *rty_omega_radps, real_T
  *rty_vy_mps, B_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localB,
  DW_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localDW,
  P_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localP)
{
  real_T u1;
  real_T u2;
  real_T u0;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // UnitDelay: '<S131>/Unit Delay'
    *rty_vy_mps = localDW->UnitDelay_DSTATE;

    // UnitDelay: '<S132>/Unit Delay'
    *rty_omega_radps = localDW->UnitDelay_DSTATE_j;

    // Gain: '<S130>/Lf'
    localB->Lf = rtP_VEH.Lf * *rty_omega_radps;

    // Sum: '<S130>/sum'
    localB->sum = *rty_vy_mps + localB->Lf;
  }

  // Saturate: '<S130>/Saturation'
  u1 = localP->Saturation_LowerSat;
  u2 = localP->Saturation_UpperSat;
  if (rtu_vx_mps > u2) {
    localB->Saturation = u2;
  } else if (rtu_vx_mps < u1) {
    localB->Saturation = u1;
  } else {
    localB->Saturation = rtu_vx_mps;
  }

  // End of Saturate: '<S130>/Saturation'

  // Product: '<S130>/Divide'
  localB->Divide = localB->sum / localB->Saturation;

  // Gain: '<S130>/Gain3'
  localB->Gain3 = localP->Gain3_Gain * localB->Divide;

  // Sum: '<S130>/sum2'
  localB->th_f = rtu_WhlAngF_rad + localB->Gain3;

  // Gain: '<S130>/Cf'
  localB->Ff = rtP_VEH.Cf * localB->th_f;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Trigonometry: '<S130>/Cos'
    localB->Cos = std::cos(rtu_WhlAngF_rad);

    // Gain: '<S130>/Lr'
    localB->Lr = rtP_VEH.Lr * *rty_omega_radps;

    // Sum: '<S130>/sum1'
    localB->sum1 = *rty_vy_mps - localB->Lr;
  }

  // Product: '<S130>/Divide1'
  localB->th_r = localB->sum1 / localB->Saturation;

  // Gain: '<S130>/Gain1'
  localB->Gain1 = localP->Gain1_Gain * localB->th_r;

  // Gain: '<S130>/Cr'
  localB->Fr = rtP_VEH.Cr * localB->Gain1;

  // Product: '<S130>/Divide2'
  localB->Divide2 = localB->Cos * localB->Ff;

  // Product: '<S130>/Divide3'
  localB->Divide3 = localB->Saturation * *rty_omega_radps;

  // Sum: '<S130>/sum4'
  localB->sum4 = localB->Divide2 + localB->Fr;

  // Product: '<S130>/Divide4'
  localB->Divide4 = localB->sum4 / rtu_vehicle_mass_kg;

  // Gain: '<S130>/Lf_2'
  localB->Lf_2 = rtP_VEH.Lf * localB->Divide2;

  // Gain: '<S130>/Lr_2'
  localB->Lr_2 = rtP_VEH.Lr * localB->Fr;

  // Sum: '<S130>/sum5'
  localB->sum5 = localB->Divide4 - localB->Divide3;

  // Gain: '<S131>/Gain1'
  localB->Gain1_l = rtP_simTs * localB->sum5;

  // Sum: '<S131>/Sum'
  localB->Sum = localB->Gain1_l + *rty_vy_mps;

  // Saturate: '<S131>/Saturation'
  u0 = localB->Sum;
  u1 = localP->Saturation_LowerSat_o;
  u2 = localP->Saturation_UpperSat_c;
  if (u0 > u2) {
    localB->Saturation_a = u2;
  } else if (u0 < u1) {
    localB->Saturation_a = u1;
  } else {
    localB->Saturation_a = u0;
  }

  // End of Saturate: '<S131>/Saturation'

  // Sum: '<S130>/sum3'
  localB->sum3 = localB->Lf_2 - localB->Lr_2;

  // Gain: '<S130>/inv_Iz'
  u1 = 1.0 / rtP_VEH.Iz;
  localB->inv_Iz = u1 * localB->sum3;

  // Gain: '<S132>/Gain1'
  localB->Gain1_k = rtP_simTs * localB->inv_Iz;

  // Sum: '<S132>/Sum'
  localB->Sum_c = localB->Gain1_k + *rty_omega_radps;

  // Saturate: '<S132>/Saturation'
  u0 = localB->Sum_c;
  u1 = localP->Saturation_LowerSat_c;
  u2 = localP->Saturation_UpperSat_p;
  if (u0 > u2) {
    localB->Saturation_p = u2;
  } else if (u0 < u1) {
    localB->Saturation_p = u1;
  } else {
    localB->Saturation_p = u0;
  }

  // End of Saturate: '<S132>/Saturation'
}

// Update for atomic system: '<S125>/TwoDofDynamic'
void CNHTC_VEHICLE_MODEL_PureSLModelClass::
  CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_Update
  (B_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localB,
   DW_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localDW)
{
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Update for UnitDelay: '<S131>/Unit Delay'
    localDW->UnitDelay_DSTATE = localB->Saturation_a;

    // Update for UnitDelay: '<S132>/Unit Delay'
    localDW->UnitDelay_DSTATE_j = localB->Saturation_p;
  }
}

//
// File trailer for generated code.
//
// [EOF]
//
