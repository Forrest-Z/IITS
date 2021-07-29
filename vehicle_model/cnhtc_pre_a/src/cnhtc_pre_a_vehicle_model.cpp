//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: cnhtc_pre_a_vehicle_model.cpp
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
#include "cnhtc_pre_a_vehicle_model.h"

#include "automldiffopen_m841FDlI.h"
#include "cnhtc_pre_a_vehicle_model_private.h"
#include "look1_binlcpw.h"
#include "look1_binlxpw.h"
#include "look2_binlcapw.h"
#include "look2_binlcpw.h"
#include "rt_powd_snf.h"

// State reduction function
void local_stateReduction(real_T *x, int_T *p, int_T n, real_T *r) {
  int_T i, j;
  for (i = 0, j = 0; i < n; ++i, ++j) {
    int_T k = p[i];
    real_T lb = r[j++];
    real_T xk = x[k] - lb;
    real_T rk = r[j] - lb;
    int_T q = (int_T)std::floor(xk / rk);
    if (q) {
      x[k] = xk - q * rk + lb;
    }
  }
}
//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
void CNHTC_VEHICLE_MODEL_codeModelClass::rt_ertODEUpdateContinuousStates(
    RTWSolverInfo *si) {
  // Solver Matrices
  static const real_T rt_ODE3_A[3] = {1.0 / 2.0, 3.0 / 4.0, 1.0};
  static const real_T rt_ODE3_B[3][3] = {{1.0 / 2.0, 0.0, 0.0},
                                         {0.0, 3.0 / 4.0, 0.0},
                                         {2.0 / 9.0, 1.0 / 3.0, 4.0 / 9.0}};
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 18;
  rtsiSetSimTimeStep(si, MINOR_TIME_STEP);
  // Save the state values at time t in y, we'll use x as ynew.
  (void)std::memcpy(y, x, static_cast<uint_T>(nXc) * sizeof(real_T));
  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  cnhtc_pre_a_vehicle_model_derivatives();
  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i] * hB[0]);
  }
  rtsiSetT(si, t + h * rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  cnhtc_pre_a_vehicle_model_derivatives();
  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i] * hB[0] + f1[i] * hB[1]);
  }
  rtsiSetT(si, t + h * rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  cnhtc_pre_a_vehicle_model_derivatives();
  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i] * hB[0] + f1[i] * hB[1] + f2[i] * hB[2]);
  }
  rtsiSetT(si, tnew);
  local_stateReduction(x, rtsiGetPeriodicContStateIndices(si), 1,
                       rtsiGetPeriodicContStateRanges(si));
  rtsiSetSimTimeStep(si, MAJOR_TIME_STEP);
}
// Model step function
void CNHTC_VEHICLE_MODEL_codeModelClass::step() {
  boolean_T zcEvent;
  ZCEventType zcEvent_0;
  uint32_T rowIdx;
  real_T unusedU1[3];
  int8_T rtPrevAction;
  int8_T rtAction;
  real_T tmp;
  int32_T i;
  boolean_T tmp_0[3];
  real_T u1;
  real_T u2;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // set solver stop time
    rtsiSetSolverStopTime(
        &(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
        (((&cnhtc_pre_a_vehicle_model_M)->Timing.clockTick0 + 1) *
         (&cnhtc_pre_a_vehicle_model_M)->Timing.stepSize0));
  }  // end MajorTimeStep
  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    (&cnhtc_pre_a_vehicle_model_M)->Timing.t[0] =
        rtsiGetT(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo);
  }
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Outport: '<Root>/GearPos' incorporates:
    //   UnitDelay: '<S1>/Unit Delay1'
    cnhtc_pre_a_vehicle_model_Y.GearPos =
        cnhtc_pre_a_vehicle_model_DW.UnitDelay1_DSTATE;
    // Outport: '<Root>/foundation_brake_in_use' incorporates:
    //   DataTypeConversion: '<Root>/Data Type Conversion'
    //   Inport: '<Root>/XBR1_Ctrl_Mode'
    cnhtc_pre_a_vehicle_model_Y.foundation_brake_in_use =
        (cnhtc_pre_a_vehicle_model_U.XBR1_Ctrl_Mode != 0.0);
    // Outport: '<Root>/throttle_pct' incorporates:
    //   Gain: '<Root>/Gain'
    //   Inport: '<Root>/pedalPos_pct'
    cnhtc_pre_a_vehicle_model_Y.throttle_pct =
        cnhtc_pre_a_vehicle_model_P.Gain_Gain_f *
        cnhtc_pre_a_vehicle_model_U.pedalPos_pct;
    // UnitDelay: '<S1>/Unit Delay3'
    cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm =
        cnhtc_pre_a_vehicle_model_DW.UnitDelay3_DSTATE;
  }
  // Integrator: '<S3>/Integrator1'
  cnhtc_pre_a_vehicle_model_B.Integrator1 =
      cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE;
  // Lookup_n-D: '<S111>/EngTrq Table'
  cnhtc_pre_a_vehicle_model_B.EngTrq =
      look2_binlcpw(cnhtc_pre_a_vehicle_model_B.Integrator1,
                    cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm,
                    cnhtc_pre_a_vehicle_model_P.MappedCIEngine_f_tbrake_t_bpt,
                    cnhtc_pre_a_vehicle_model_P.MappedCIEngine_f_tbrake_n_bpt,
                    cnhtc_pre_a_vehicle_model_P.MappedCIEngine_f_tbrake,
                    cnhtc_pre_a_vehicle_model_P.EngTrqTable_maxIndex, 20U);
  // Saturate: '<S1>/Saturation'
  tmp = cnhtc_pre_a_vehicle_model_B.EngTrq;
  u1 = cnhtc_pre_a_vehicle_model_P.Saturation_LowerSat;
  u2 = cnhtc_pre_a_vehicle_model_P.Saturation_UpperSat;
  if (tmp > u2) {
    cnhtc_pre_a_vehicle_model_B.Saturation = u2;
  } else if (tmp < u1) {
    cnhtc_pre_a_vehicle_model_B.Saturation = u1;
  } else {
    cnhtc_pre_a_vehicle_model_B.Saturation = tmp;
  }
  // End of Saturate: '<S1>/Saturation'
  // Outport: '<Root>/EngTrq_Nm'
  cnhtc_pre_a_vehicle_model_Y.EngTrq_Nm =
      cnhtc_pre_a_vehicle_model_B.Saturation;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Outport: '<Root>/EngSpd_rpm' incorporates:
    //   UnitDelay: '<S1>/Unit Delay4'
    cnhtc_pre_a_vehicle_model_Y.EngSpd_rpm =
        cnhtc_pre_a_vehicle_model_DW.UnitDelay4_DSTATE;
    // UnitDelay: '<S1>/Unit Delay2'
    cnhtc_pre_a_vehicle_model_B.UnitDelay2 =
        cnhtc_pre_a_vehicle_model_DW.UnitDelay2_DSTATE;
    // Outport: '<Root>/shift_in_process' incorporates:
    //   Logic: '<S1>/NOT'
    cnhtc_pre_a_vehicle_model_Y.shift_in_process =
        !cnhtc_pre_a_vehicle_model_B.UnitDelay2;
  }
  // Sum: '<S1>/Add'
  cnhtc_pre_a_vehicle_model_B.Add = cnhtc_pre_a_vehicle_model_B.Integrator1 -
                                    cnhtc_pre_a_vehicle_model_B.Saturation;
  // Abs: '<S1>/Abs'
  cnhtc_pre_a_vehicle_model_B.Abs = std::abs(cnhtc_pre_a_vehicle_model_B.Add);
  // Sum: '<S1>/Add1' incorporates:
  //   Constant: '<S1>/Constant1'
  cnhtc_pre_a_vehicle_model_B.Add1 =
      cnhtc_pre_a_vehicle_model_B.Integrator1 +
      cnhtc_pre_a_vehicle_model_P.Constant1_Value_d;
  // Product: '<S1>/Divide'
  cnhtc_pre_a_vehicle_model_B.Divide =
      cnhtc_pre_a_vehicle_model_B.Abs / cnhtc_pre_a_vehicle_model_B.Add1;
  // Outport: '<Root>/engine_torque_loss_percent'
  cnhtc_pre_a_vehicle_model_Y.engine_torque_loss_percent =
      cnhtc_pre_a_vehicle_model_B.Divide;
  // Abs: '<S1>/Abs1'
  cnhtc_pre_a_vehicle_model_B.Abs1 =
      std::abs(cnhtc_pre_a_vehicle_model_B.Saturation);
  // Product: '<S1>/Divide1' incorporates:
  //   Constant: '<S1>/Constant2'
  cnhtc_pre_a_vehicle_model_B.Divide1 =
      cnhtc_pre_a_vehicle_model_B.Abs1 / rtP_Chas.EngReferTor_Nm;
  // Outport: '<Root>/engine_torque_percent'
  cnhtc_pre_a_vehicle_model_Y.engine_torque_percent =
      cnhtc_pre_a_vehicle_model_B.Divide1;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Lookup_n-D: '<S1>/1-D Lookup Table' incorporates:
    //   Outport: '<Root>/GearPos'
    cnhtc_pre_a_vehicle_model_B.uDLookupTable =
        look1_binlxpw(cnhtc_pre_a_vehicle_model_Y.GearPos, rtP_Chas.GbRatioBp,
                      rtP_Chas.GbRatioTable, 12U);
  }
  // Product: '<S1>/Product1'
  cnhtc_pre_a_vehicle_model_B.Product1 =
      cnhtc_pre_a_vehicle_model_B.uDLookupTable *
      cnhtc_pre_a_vehicle_model_B.Saturation;
  // Outport: '<Root>/TransTorOut_Nm'
  cnhtc_pre_a_vehicle_model_Y.TransTorOut_Nm =
      cnhtc_pre_a_vehicle_model_B.Product1;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // UnitDelay: '<Root>/Unit Delay1'
    cnhtc_pre_a_vehicle_model_B.UnitDelay1_k =
        cnhtc_pre_a_vehicle_model_DW.UnitDelay1_DSTATE_j;
    // ModelReference: '<Root>/Brake_System' incorporates:
    //   Inport: '<Root>/Mass_kg'
    //   Inport: '<Root>/XBR1_Ctrl_Mode'
    //   Inport: '<Root>/XBR1_ExternalAccele'
    //   Outport: '<Root>/TrailWhlPre_Mpa'
    //   Outport: '<Root>/bwdWhlPre_Mpa'
    //   Outport: '<Root>/fwdWhlPre_Mpa'
    Brake_SystemMDLOBJ1.step(&cnhtc_pre_a_vehicle_model_U.XBR1_ExternalAccele,
                             &cnhtc_pre_a_vehicle_model_B.UnitDelay1_k,
                             &cnhtc_pre_a_vehicle_model_U.XBR1_Ctrl_Mode,
                             &cnhtc_pre_a_vehicle_model_U.Mass_kg,
                             &cnhtc_pre_a_vehicle_model_Y.bwdWhlPre_Mpa[0],
                             &cnhtc_pre_a_vehicle_model_Y.fwdWhlPre_Mpa[0],
                             &cnhtc_pre_a_vehicle_model_Y.TrailWhlPre_Mpa[0]);
    // Memory: '<S46>/Memory'
    cnhtc_pre_a_vehicle_model_B.Memory_c =
        cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_j;
    // Memory: '<S117>/Memory'
    cnhtc_pre_a_vehicle_model_B.Memory =
        cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput;
    // Constant: '<S116>/domega_o'
    cnhtc_pre_a_vehicle_model_B.domega_o =
        cnhtc_pre_a_vehicle_model_P.PropShaft_domega_o;
  }
  // Integrator: '<S5>/Integrator'
  cnhtc_pre_a_vehicle_model_B.Integrator =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE;
  // Outport: '<Root>/fuel_consumption'
  cnhtc_pre_a_vehicle_model_Y.fuel_consumption =
      cnhtc_pre_a_vehicle_model_B.Integrator;
  // Integrator: '<S117>/Integrator'
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    zcEvent_0 =
        rt_ZCFcn(RISING_ZERO_CROSSING,
                 &cnhtc_pre_a_vehicle_model_PrevZCX.Integrator_Reset_ZCE,
                 (cnhtc_pre_a_vehicle_model_B.Memory));
    zcEvent = (zcEvent_0 != NO_ZCEVENT);
    // evaluate zero-crossings
    if (zcEvent || (cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK != 0)) {
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_p =
          cnhtc_pre_a_vehicle_model_B.domega_o;
    }
  }
  cnhtc_pre_a_vehicle_model_B.Integrator_e =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_p;
  // End of Integrator: '<S117>/Integrator'
  // Gain: '<S116>/Gain2'
  cnhtc_pre_a_vehicle_model_B.Gain2 = cnhtc_pre_a_vehicle_model_P.PropShaft_b *
                                      cnhtc_pre_a_vehicle_model_B.Integrator_e;
  // Integrator: '<S116>/Integrator'
  cnhtc_pre_a_vehicle_model_B.Integrator_h =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_f;
  // Gain: '<S116>/Gain1'
  cnhtc_pre_a_vehicle_model_B.Gain1 = cnhtc_pre_a_vehicle_model_P.PropShaft_k *
                                      cnhtc_pre_a_vehicle_model_B.Integrator_h;
  // Sum: '<S116>/Subtract1'
  cnhtc_pre_a_vehicle_model_B.Subtract1 =
      cnhtc_pre_a_vehicle_model_B.Gain2 + cnhtc_pre_a_vehicle_model_B.Gain1;
  // UnaryMinus: '<S116>/Unary Minus'
  cnhtc_pre_a_vehicle_model_B.UnaryMinus =
      -cnhtc_pre_a_vehicle_model_B.Subtract1;
  // Integrator: '<S30>/Integrator'
  cnhtc_pre_a_vehicle_model_B.Integrator_es =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_g;
  // Gain: '<S12>/ClutchGain'
  cnhtc_pre_a_vehicle_model_B.ClutchGain =
      cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_K_c *
      cnhtc_pre_a_vehicle_model_B.Integrator_es;
  // Saturate: '<S31>/Saturation'
  tmp = cnhtc_pre_a_vehicle_model_B.ClutchGain;
  u1 = cnhtc_pre_a_vehicle_model_P.Saturation_LowerSat_f;
  u2 = cnhtc_pre_a_vehicle_model_P.Saturation_UpperSat_a;
  if (tmp > u2) {
    cnhtc_pre_a_vehicle_model_B.Saturation_e = u2;
  } else if (tmp < u1) {
    cnhtc_pre_a_vehicle_model_B.Saturation_e = u1;
  } else {
    cnhtc_pre_a_vehicle_model_B.Saturation_e = tmp;
  }
  // End of Saturate: '<S31>/Saturation'
  // Gain: '<S31>/Torque Conversion'
  tmp = cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_R *
        cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_muk;
  cnhtc_pre_a_vehicle_model_B.TorqueConversion =
      tmp * cnhtc_pre_a_vehicle_model_B.Saturation_e;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // UnitDelay: '<Root>/Unit Delay'
    cnhtc_pre_a_vehicle_model_B.UnitDelay =
        cnhtc_pre_a_vehicle_model_DW.UnitDelay_DSTATE;
    // ModelReference: '<S1>/TCU' incorporates:
    //   Inport: '<Root>/pedalPos_pct'
    TCUMDLOBJ3.step(&cnhtc_pre_a_vehicle_model_U.pedalPos_pct,
                    &cnhtc_pre_a_vehicle_model_B.UnitDelay,
                    &cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm,
                    &cnhtc_pre_a_vehicle_model_B.GearSel);
    // Memory: '<S34>/Memory3'
    cnhtc_pre_a_vehicle_model_B.Memory3 =
        cnhtc_pre_a_vehicle_model_DW.Memory3_PreviousInput;
    // Memory: '<S34>/Memory'
    cnhtc_pre_a_vehicle_model_B.Memory_e =
        cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_p;
    // Sum: '<S34>/Add2'
    cnhtc_pre_a_vehicle_model_B.Add2 = cnhtc_pre_a_vehicle_model_B.Memory3 -
                                       cnhtc_pre_a_vehicle_model_B.Memory_e;
    // RelationalOperator: '<S36>/Compare' incorporates:
    //   Constant: '<S36>/Constant'
    cnhtc_pre_a_vehicle_model_B.Compare =
        (cnhtc_pre_a_vehicle_model_B.Add2 !=
         cnhtc_pre_a_vehicle_model_P.Constant_Value_n);
    // Memory: '<S34>/Memory1'
    cnhtc_pre_a_vehicle_model_B.Memory1 =
        cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput;
    // Switch: '<S34>/Switch1'
    if (cnhtc_pre_a_vehicle_model_B.Compare) {
      cnhtc_pre_a_vehicle_model_B.CmdGear = cnhtc_pre_a_vehicle_model_B.GearSel;
    } else {
      cnhtc_pre_a_vehicle_model_B.CmdGear = cnhtc_pre_a_vehicle_model_B.Memory1;
    }
    // End of Switch: '<S34>/Switch1'
    // Constant: '<S37>/Constant'
    cnhtc_pre_a_vehicle_model_B.Constant =
        cnhtc_pre_a_vehicle_model_P.Constant_Value_hd;
  }
  // Integrator: '<S37>/Integrator1'
  // Limited  Integrator  (w/ Saturation Port)
  if (cnhtc_pre_a_vehicle_model_DW.Integrator1_IWORK != 0) {
    cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g =
        cnhtc_pre_a_vehicle_model_B.Constant;
  }
  if (cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g >=
      cnhtc_pre_a_vehicle_model_P.Integrator1_UpperSat) {
    cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g =
        cnhtc_pre_a_vehicle_model_P.Integrator1_UpperSat;
    cnhtc_pre_a_vehicle_model_B.Integrator1_o2 = 1.0;
  } else if (cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g <=
             cnhtc_pre_a_vehicle_model_P.Integrator1_LowerSat) {
    cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g =
        cnhtc_pre_a_vehicle_model_P.Integrator1_LowerSat;
    cnhtc_pre_a_vehicle_model_B.Integrator1_o2 = -1.0;
  } else {
    cnhtc_pre_a_vehicle_model_B.Integrator1_o2 = 0.0;
  }
  cnhtc_pre_a_vehicle_model_B.Integrator1_o1 =
      cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g;
  // End of Integrator: '<S37>/Integrator1'
  // RelationalOperator: '<S40>/Compare' incorporates:
  //   Constant: '<S40>/Constant'
  cnhtc_pre_a_vehicle_model_B.Compare_n =
      (cnhtc_pre_a_vehicle_model_B.Integrator1_o2 !=
       cnhtc_pre_a_vehicle_model_P.Constant_Value_m);
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Memory: '<S39>/Memory2'
    cnhtc_pre_a_vehicle_model_B.Memory2_g =
        cnhtc_pre_a_vehicle_model_DW.Memory2_PreviousInput_e;
  }
  // Logic: '<S38>/Logical Operator3'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator3 =
      (cnhtc_pre_a_vehicle_model_B.Compare_n &&
       cnhtc_pre_a_vehicle_model_B.Memory2_g);
  // Switch: '<S34>/Switch2'
  if (cnhtc_pre_a_vehicle_model_B.LogicalOperator3) {
    cnhtc_pre_a_vehicle_model_B.NewGear = cnhtc_pre_a_vehicle_model_B.CmdGear;
  } else {
    cnhtc_pre_a_vehicle_model_B.NewGear = cnhtc_pre_a_vehicle_model_B.Memory3;
  }
  // End of Switch: '<S34>/Switch2'
  // Lookup_n-D: '<S14>/Gear2damping'
  cnhtc_pre_a_vehicle_model_B.b =
      look1_binlxpw(cnhtc_pre_a_vehicle_model_B.NewGear, rtP_Chas.GbRatioBp,
                    rtP_Chas.DampingCoeffs, 12U);
  // Lookup_n-D: '<S14>/Gear2inertias'
  cnhtc_pre_a_vehicle_model_B.J =
      look1_binlxpw(cnhtc_pre_a_vehicle_model_B.NewGear, rtP_Chas.GbRatioBp,
                    cnhtc_pre_a_vehicle_model_P.Gear2inertias_tableData, 12U);
  // Lookup_n-D: '<S14>/Gear2Ratios'
  cnhtc_pre_a_vehicle_model_B.N =
      look1_binlxpw(cnhtc_pre_a_vehicle_model_B.NewGear, rtP_Chas.GbRatioBp,
                    rtP_Chas.GbRatioTable, 12U);
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // InitialCondition: '<S16>/IC' incorporates:
    //   Constant: '<S16>/Constant1'
    if (cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime) {
      cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime = false;
      cnhtc_pre_a_vehicle_model_B.IC = cnhtc_pre_a_vehicle_model_P.IC_Value;
    } else {
      cnhtc_pre_a_vehicle_model_B.IC =
          cnhtc_pre_a_vehicle_model_P.Constant1_Value_f;
    }
    // End of InitialCondition: '<S16>/IC'
    // InitialCondition: '<S17>/IC' incorporates:
    //   Constant: '<S17>/Constant1'
    if (cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_e) {
      cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_e = false;
      cnhtc_pre_a_vehicle_model_B.IC_a = cnhtc_pre_a_vehicle_model_P.IC_Value_c;
    } else {
      cnhtc_pre_a_vehicle_model_B.IC_a =
          cnhtc_pre_a_vehicle_model_P.Constant1_Value_c;
    }
    // End of InitialCondition: '<S17>/IC'
  }
  // Switch: '<S16>/Switch' incorporates:
  //   Constant: '<S16>/Constant'
  if (cnhtc_pre_a_vehicle_model_B.IC >
      cnhtc_pre_a_vehicle_model_P.Switch_Threshold_n) {
    cnhtc_pre_a_vehicle_model_B.Switch =
        cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch =
        cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_omegain_o;
  }
  // End of Switch: '<S16>/Switch'
  // Switch: '<S17>/Switch' incorporates:
  //   Constant: '<S17>/Constant'
  if (cnhtc_pre_a_vehicle_model_B.IC_a >
      cnhtc_pre_a_vehicle_model_P.Switch_Threshold_e) {
    // Product: '<S9>/Product1'
    cnhtc_pre_a_vehicle_model_B.Product1_bw =
        cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE /
        cnhtc_pre_a_vehicle_model_B.N;
    cnhtc_pre_a_vehicle_model_B.Switch_a =
        cnhtc_pre_a_vehicle_model_B.Product1_bw;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_a =
        cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_omegaout_o;
  }
  // End of Switch: '<S17>/Switch'
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // InitialCondition: '<S15>/IC' incorporates:
    //   Constant: '<S15>/Constant1'
    if (cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_f) {
      cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_f = false;
      cnhtc_pre_a_vehicle_model_B.IC_d = cnhtc_pre_a_vehicle_model_P.IC_Value_o;
    } else {
      cnhtc_pre_a_vehicle_model_B.IC_d =
          cnhtc_pre_a_vehicle_model_P.Constant1_Value_o;
    }
    // End of InitialCondition: '<S15>/IC'
  }
  // Switch: '<S15>/Switch' incorporates:
  //   Constant: '<S15>/Constant'
  if (cnhtc_pre_a_vehicle_model_B.IC_d >
      cnhtc_pre_a_vehicle_model_P.Switch_Threshold_l) {
    cnhtc_pre_a_vehicle_model_B.Switch_f =
        cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_f =
        cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_omegain_o;
  }
  // End of Switch: '<S15>/Switch'
  // If: '<S9>/If'
  rtPrevAction = cnhtc_pre_a_vehicle_model_DW.If_ActiveSubsystem;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    rtAction = static_cast<int8_T>(!cnhtc_pre_a_vehicle_model_B.Memory_c);
    cnhtc_pre_a_vehicle_model_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = cnhtc_pre_a_vehicle_model_DW.If_ActiveSubsystem;
  }
  switch (rtAction) {
    case 0:
      if (rtAction != rtPrevAction) {
        // InitializeConditions for IfAction SubSystem: '<S9>/Locked'
        // incorporates:
        //   ActionPort: '<S11>/Action'
        // InitializeConditions for If: '<S9>/If' incorporates:
        //   Integrator: '<S11>/Locked Shaft Integrator'
        if (rtmIsFirstInitCond((&cnhtc_pre_a_vehicle_model_M))) {
          cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE = 0.0;
        }
        cnhtc_pre_a_vehicle_model_DW.LockedShaftIntegrator_IWORK = 1;
        // End of InitializeConditions for SubSystem: '<S9>/Locked'
      }
      // Outputs for IfAction SubSystem: '<S9>/Locked' incorporates:
      //   ActionPort: '<S11>/Action'
      // Lookup_n-D: '<S29>/Eta 1D'
      cnhtc_pre_a_vehicle_model_B.Eta1D_b =
          look1_binlcpw(cnhtc_pre_a_vehicle_model_B.NewGear, rtP_Chas.GbRatioBp,
                        rtP_Chas.GearEta, 12U);
      // Abs: '<S11>/Abs'
      cnhtc_pre_a_vehicle_model_B.Abs_k =
          std::abs(cnhtc_pre_a_vehicle_model_B.N);
      // Integrator: '<S11>/Locked Shaft Integrator'
      // Limited  Integrator
      if (cnhtc_pre_a_vehicle_model_DW.LockedShaftIntegrator_IWORK != 0) {
        cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE =
            cnhtc_pre_a_vehicle_model_B.Switch_f;
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
            &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
      }
      if (cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE >=
          cnhtc_pre_a_vehicle_model_P.LockedShaftIntegrator_UpperSat) {
        if (cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE !=
            cnhtc_pre_a_vehicle_model_P.LockedShaftIntegrator_UpperSat) {
          cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE =
              cnhtc_pre_a_vehicle_model_P.LockedShaftIntegrator_UpperSat;
          rtsiSetBlockStateForSolverChangedAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
          rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
        }
      } else {
        if ((cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE <=
             cnhtc_pre_a_vehicle_model_P.LockedShaftIntegrator_LowerSat) &&
            (cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE !=
             cnhtc_pre_a_vehicle_model_P.LockedShaftIntegrator_LowerSat)) {
          cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE =
              cnhtc_pre_a_vehicle_model_P.LockedShaftIntegrator_LowerSat;
          rtsiSetBlockStateForSolverChangedAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
          rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
        }
      }
      cnhtc_pre_a_vehicle_model_B.omega =
          cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE;
      // End of Integrator: '<S11>/Locked Shaft Integrator'
      // Product: '<S27>/Product1'
      cnhtc_pre_a_vehicle_model_B.Product1_ei =
          cnhtc_pre_a_vehicle_model_B.Saturation *
          cnhtc_pre_a_vehicle_model_B.omega;
      // Switch: '<S27>/Switch' incorporates:
      //   Constant: '<S27>/Constant'
      if (cnhtc_pre_a_vehicle_model_B.Product1_ei >
          cnhtc_pre_a_vehicle_model_P.Switch_Threshold) {
        cnhtc_pre_a_vehicle_model_B.Switch_aq =
            cnhtc_pre_a_vehicle_model_B.Eta1D_b;
      } else {
        cnhtc_pre_a_vehicle_model_B.Switch_aq =
            cnhtc_pre_a_vehicle_model_P.Constant_Value;
      }
      // End of Switch: '<S27>/Switch'
      // Product: '<S27>/Product4'
      cnhtc_pre_a_vehicle_model_B.Product4_a =
          cnhtc_pre_a_vehicle_model_B.Switch_aq *
          cnhtc_pre_a_vehicle_model_B.Saturation;
      // Sum: '<S27>/Subtract'
      cnhtc_pre_a_vehicle_model_B.Subtract_l =
          cnhtc_pre_a_vehicle_model_B.Product4_a -
          cnhtc_pre_a_vehicle_model_B.Saturation;
      // Product: '<S27>/Product2'
      cnhtc_pre_a_vehicle_model_B.Product2_h =
          cnhtc_pre_a_vehicle_model_B.Subtract_l *
          cnhtc_pre_a_vehicle_model_B.omega;
      // Product: '<S11>/Product5'
      cnhtc_pre_a_vehicle_model_B.Product5 =
          cnhtc_pre_a_vehicle_model_B.UnaryMinus /
          cnhtc_pre_a_vehicle_model_B.N;
      // Product: '<S28>/Product1'
      cnhtc_pre_a_vehicle_model_B.Product1_fr =
          cnhtc_pre_a_vehicle_model_B.Product5 *
          cnhtc_pre_a_vehicle_model_B.omega;
      // Switch: '<S28>/Switch' incorporates:
      //   Constant: '<S28>/Constant'
      if (cnhtc_pre_a_vehicle_model_B.Product1_fr >
          cnhtc_pre_a_vehicle_model_P.Switch_Threshold_j) {
        cnhtc_pre_a_vehicle_model_B.Switch_k4 =
            cnhtc_pre_a_vehicle_model_B.Eta1D_b;
      } else {
        cnhtc_pre_a_vehicle_model_B.Switch_k4 =
            cnhtc_pre_a_vehicle_model_P.Constant_Value_b;
      }
      // End of Switch: '<S28>/Switch'
      // Product: '<S28>/Product4'
      cnhtc_pre_a_vehicle_model_B.Product4_pm =
          cnhtc_pre_a_vehicle_model_B.Switch_k4 *
          cnhtc_pre_a_vehicle_model_B.Product5;
      // Sum: '<S28>/Subtract'
      cnhtc_pre_a_vehicle_model_B.Subtract_c =
          cnhtc_pre_a_vehicle_model_B.Product4_pm -
          cnhtc_pre_a_vehicle_model_B.Product5;
      // Product: '<S28>/Product2'
      cnhtc_pre_a_vehicle_model_B.Product2_e =
          cnhtc_pre_a_vehicle_model_B.Subtract_c *
          cnhtc_pre_a_vehicle_model_B.omega;
      // Sum: '<S11>/Add'
      cnhtc_pre_a_vehicle_model_B.PwrEffLoss_i =
          cnhtc_pre_a_vehicle_model_B.Product2_h +
          cnhtc_pre_a_vehicle_model_B.Product2_e;
      // Product: '<S11>/Product1'
      cnhtc_pre_a_vehicle_model_B.Product1_l =
          1.0 / cnhtc_pre_a_vehicle_model_B.Abs_k /
          cnhtc_pre_a_vehicle_model_B.Abs_k * cnhtc_pre_a_vehicle_model_B.b;
      // Product: '<S11>/Product6'
      cnhtc_pre_a_vehicle_model_B.Product6 =
          cnhtc_pre_a_vehicle_model_B.Product1_l *
          cnhtc_pre_a_vehicle_model_B.omega;
      // Gain: '<S11>/input clutch Damping'
      cnhtc_pre_a_vehicle_model_B.inputclutchDamping =
          cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_bin *
          cnhtc_pre_a_vehicle_model_B.omega;
      // Sum: '<S11>/Add1'
      cnhtc_pre_a_vehicle_model_B.Add1_a =
          cnhtc_pre_a_vehicle_model_B.Product6 +
          cnhtc_pre_a_vehicle_model_B.inputclutchDamping;
      // Sum: '<S11>/Add2'
      cnhtc_pre_a_vehicle_model_B.Add2_n =
          cnhtc_pre_a_vehicle_model_B.Product4_a +
          cnhtc_pre_a_vehicle_model_B.Product4_pm;
      // Product: '<S11>/Product3'
      cnhtc_pre_a_vehicle_model_B.Product3_c =
          cnhtc_pre_a_vehicle_model_B.J / cnhtc_pre_a_vehicle_model_B.Abs_k /
          cnhtc_pre_a_vehicle_model_B.Abs_k;
      // Sum: '<S11>/Add3' incorporates:
      //   Constant: '<S11>/Constant'
      tmp = rtP_Chas.Ie_kgm2 * 3.0;
      cnhtc_pre_a_vehicle_model_B.Add3_ff =
          tmp + cnhtc_pre_a_vehicle_model_B.Product3_c;
      // Sum: '<S11>/Sum'
      cnhtc_pre_a_vehicle_model_B.Sum_a = cnhtc_pre_a_vehicle_model_B.Add2_n -
                                          cnhtc_pre_a_vehicle_model_B.Add1_a;
      // Product: '<S11>/Product'
      cnhtc_pre_a_vehicle_model_B.PwrStoredTrans_e =
          cnhtc_pre_a_vehicle_model_B.Sum_a * cnhtc_pre_a_vehicle_model_B.omega;
      // Product: '<S11>/Product2'
      cnhtc_pre_a_vehicle_model_B.Product2_fr =
          cnhtc_pre_a_vehicle_model_B.omega / cnhtc_pre_a_vehicle_model_B.N;
      // UnaryMinus: '<S11>/Unary Minus'
      cnhtc_pre_a_vehicle_model_B.UnaryMinus_p =
          -cnhtc_pre_a_vehicle_model_B.Add1_a;
      // Product: '<S11>/Product7'
      cnhtc_pre_a_vehicle_model_B.PwrDampLoss_d =
          cnhtc_pre_a_vehicle_model_B.omega *
          cnhtc_pre_a_vehicle_model_B.UnaryMinus_p;
      // Product: '<S11>/Product8'
      cnhtc_pre_a_vehicle_model_B.Product8 =
          1.0 / cnhtc_pre_a_vehicle_model_B.Add3_ff *
          cnhtc_pre_a_vehicle_model_B.Sum_a;
      // SignalConversion: '<S11>/Signal Conversion1'
      cnhtc_pre_a_vehicle_model_B.Merge2 = cnhtc_pre_a_vehicle_model_B.N;
      // SignalConversion: '<S11>/Signal Conversion2'
      cnhtc_pre_a_vehicle_model_B.Merge3 = cnhtc_pre_a_vehicle_model_B.omega;
      // SignalConversion: '<S11>/Signal Conversion3'
      cnhtc_pre_a_vehicle_model_B.Merge =
          cnhtc_pre_a_vehicle_model_B.Product2_fr;
      // SignalConversion: '<S11>/Signal Conversion4'
      cnhtc_pre_a_vehicle_model_B.Merge1 =
          cnhtc_pre_a_vehicle_model_B.PwrStoredTrans_e;
      // SignalConversion generated from: '<S11>/Signal Conversion5'
      cnhtc_pre_a_vehicle_model_B.PwrStoredTrans =
          cnhtc_pre_a_vehicle_model_B.PwrStoredTrans_e;
      // SignalConversion generated from: '<S11>/Signal Conversion5'
      // incorporates:
      //   Constant: '<S11>/Constant1'
      cnhtc_pre_a_vehicle_model_B.PwrCltchLoss =
          cnhtc_pre_a_vehicle_model_P.Constant1_Value;
      // SignalConversion generated from: '<S11>/Signal Conversion5'
      cnhtc_pre_a_vehicle_model_B.PwrDampLoss =
          cnhtc_pre_a_vehicle_model_B.PwrDampLoss_d;
      // SignalConversion generated from: '<S11>/Signal Conversion5'
      cnhtc_pre_a_vehicle_model_B.PwrEffLoss =
          cnhtc_pre_a_vehicle_model_B.PwrEffLoss_i;
      // End of Outputs for SubSystem: '<S9>/Locked'
      break;
    case 1:
      if (rtAction != rtPrevAction) {
        // InitializeConditions for IfAction SubSystem: '<S9>/Unlocked'
        // incorporates:
        //   ActionPort: '<S13>/Action'
        // InitializeConditions for If: '<S9>/If' incorporates:
        //   Integrator: '<S13>/Integrator'
        //   Integrator: '<S13>/Pump Integrator'
        if (rtmIsFirstInitCond((&cnhtc_pre_a_vehicle_model_M))) {
          cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE = 0.0;
          cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d = 0.0;
        }
        cnhtc_pre_a_vehicle_model_DW.PumpIntegrator_IWORK = 1;
        cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_e = 1;
        // End of InitializeConditions for SubSystem: '<S9>/Unlocked'
      }
      // Outputs for IfAction SubSystem: '<S9>/Unlocked' incorporates:
      //   ActionPort: '<S13>/Action'
      // Lookup_n-D: '<S56>/Eta 1D'
      cnhtc_pre_a_vehicle_model_B.Eta1D =
          look1_binlcpw(cnhtc_pre_a_vehicle_model_B.NewGear, rtP_Chas.GbRatioBp,
                        rtP_Chas.GearEta, 12U);
      // Integrator: '<S13>/Pump Integrator'
      // Limited  Integrator
      if (cnhtc_pre_a_vehicle_model_DW.PumpIntegrator_IWORK != 0) {
        cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE =
            cnhtc_pre_a_vehicle_model_B.Switch;
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
            &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
      }
      if (cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE >=
          cnhtc_pre_a_vehicle_model_P.PumpIntegrator_UpperSat) {
        if (cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE !=
            cnhtc_pre_a_vehicle_model_P.PumpIntegrator_UpperSat) {
          cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE =
              cnhtc_pre_a_vehicle_model_P.PumpIntegrator_UpperSat;
          rtsiSetBlockStateForSolverChangedAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
          rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
        }
      } else {
        if ((cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE <=
             cnhtc_pre_a_vehicle_model_P.PumpIntegrator_LowerSat) &&
            (cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE !=
             cnhtc_pre_a_vehicle_model_P.PumpIntegrator_LowerSat)) {
          cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE =
              cnhtc_pre_a_vehicle_model_P.PumpIntegrator_LowerSat;
          rtsiSetBlockStateForSolverChangedAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
          rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
        }
      }
      cnhtc_pre_a_vehicle_model_B.PumpIntegrator =
          cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE;
      // End of Integrator: '<S13>/Pump Integrator'
      // Product: '<S51>/Product1'
      cnhtc_pre_a_vehicle_model_B.Product1_n =
          cnhtc_pre_a_vehicle_model_B.Saturation *
          cnhtc_pre_a_vehicle_model_B.PumpIntegrator;
      // Switch: '<S51>/Switch' incorporates:
      //   Constant: '<S51>/Constant'
      if (cnhtc_pre_a_vehicle_model_B.Product1_n >
          cnhtc_pre_a_vehicle_model_P.Switch_Threshold_k) {
        cnhtc_pre_a_vehicle_model_B.Switch_o =
            cnhtc_pre_a_vehicle_model_B.Eta1D;
      } else {
        cnhtc_pre_a_vehicle_model_B.Switch_o =
            cnhtc_pre_a_vehicle_model_P.Constant_Value_j;
      }
      // End of Switch: '<S51>/Switch'
      // Product: '<S51>/Product4'
      cnhtc_pre_a_vehicle_model_B.Product4_cv =
          cnhtc_pre_a_vehicle_model_B.Switch_o *
          cnhtc_pre_a_vehicle_model_B.Saturation;
      // Sum: '<S51>/Subtract'
      cnhtc_pre_a_vehicle_model_B.Subtract_mb =
          cnhtc_pre_a_vehicle_model_B.Product4_cv -
          cnhtc_pre_a_vehicle_model_B.Saturation;
      // Product: '<S51>/Product2'
      cnhtc_pre_a_vehicle_model_B.Product2_o =
          cnhtc_pre_a_vehicle_model_B.Subtract_mb *
          cnhtc_pre_a_vehicle_model_B.PumpIntegrator;
      // Integrator: '<S13>/Integrator'
      // Limited  Integrator
      if (cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_e != 0) {
        cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d =
            cnhtc_pre_a_vehicle_model_B.Switch_a;
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
            &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
      }
      if (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d >=
          cnhtc_pre_a_vehicle_model_P.Integrator_UpperSat) {
        if (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d !=
            cnhtc_pre_a_vehicle_model_P.Integrator_UpperSat) {
          cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d =
              cnhtc_pre_a_vehicle_model_P.Integrator_UpperSat;
          rtsiSetBlockStateForSolverChangedAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
          rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
        }
      } else {
        if ((cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d <=
             cnhtc_pre_a_vehicle_model_P.Integrator_LowerSat) &&
            (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d !=
             cnhtc_pre_a_vehicle_model_P.Integrator_LowerSat)) {
          cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d =
              cnhtc_pre_a_vehicle_model_P.Integrator_LowerSat;
          rtsiSetBlockStateForSolverChangedAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
          rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, true);
        }
      }
      cnhtc_pre_a_vehicle_model_B.w_out =
          cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d;
      // End of Integrator: '<S13>/Integrator'
      // Product: '<S52>/Product1'
      cnhtc_pre_a_vehicle_model_B.Product1_ex =
          cnhtc_pre_a_vehicle_model_B.UnaryMinus *
          cnhtc_pre_a_vehicle_model_B.w_out;
      // Switch: '<S52>/Switch' incorporates:
      //   Constant: '<S52>/Constant'
      if (cnhtc_pre_a_vehicle_model_B.Product1_ex >
          cnhtc_pre_a_vehicle_model_P.Switch_Threshold_g) {
        cnhtc_pre_a_vehicle_model_B.Switch_b =
            cnhtc_pre_a_vehicle_model_B.Eta1D;
      } else {
        cnhtc_pre_a_vehicle_model_B.Switch_b =
            cnhtc_pre_a_vehicle_model_P.Constant_Value_a;
      }
      // End of Switch: '<S52>/Switch'
      // Product: '<S52>/Product4'
      cnhtc_pre_a_vehicle_model_B.Product4_e =
          cnhtc_pre_a_vehicle_model_B.Switch_b *
          cnhtc_pre_a_vehicle_model_B.UnaryMinus;
      // Sum: '<S52>/Subtract'
      cnhtc_pre_a_vehicle_model_B.Subtract_g =
          cnhtc_pre_a_vehicle_model_B.Product4_e -
          cnhtc_pre_a_vehicle_model_B.UnaryMinus;
      // Product: '<S52>/Product2'
      cnhtc_pre_a_vehicle_model_B.Product2_d =
          cnhtc_pre_a_vehicle_model_B.Subtract_g *
          cnhtc_pre_a_vehicle_model_B.w_out;
      // Sum: '<S13>/Add'
      cnhtc_pre_a_vehicle_model_B.PwrEffLoss_f =
          cnhtc_pre_a_vehicle_model_B.Product2_o +
          cnhtc_pre_a_vehicle_model_B.Product2_d;
      // Product: '<S53>/Product4'
      cnhtc_pre_a_vehicle_model_B.Product4_eu =
          cnhtc_pre_a_vehicle_model_B.w_out * cnhtc_pre_a_vehicle_model_B.N;
      // Sum: '<S53>/Add2'
      cnhtc_pre_a_vehicle_model_B.Add2_o =
          cnhtc_pre_a_vehicle_model_B.PumpIntegrator -
          cnhtc_pre_a_vehicle_model_B.Product4_eu;
      // Gain: '<S53>/Gain'
      cnhtc_pre_a_vehicle_model_B.Gain_nb =
          cnhtc_pre_a_vehicle_model_P.Gain_Gain *
          cnhtc_pre_a_vehicle_model_B.Add2_o;
      // Trigonometry: '<S53>/Trigonometric Function'
      cnhtc_pre_a_vehicle_model_B.TrigonometricFunction =
          std::tanh(cnhtc_pre_a_vehicle_model_B.Gain_nb);
      // Product: '<S53>/Product2'
      cnhtc_pre_a_vehicle_model_B.Product2_a =
          cnhtc_pre_a_vehicle_model_B.TorqueConversion *
          cnhtc_pre_a_vehicle_model_B.TrigonometricFunction;
      // Product: '<S53>/Product1'
      cnhtc_pre_a_vehicle_model_B.Product1_fs =
          cnhtc_pre_a_vehicle_model_B.Product2_a *
          cnhtc_pre_a_vehicle_model_B.N;
      // Product: '<S54>/Product2'
      cnhtc_pre_a_vehicle_model_B.Product2_g =
          cnhtc_pre_a_vehicle_model_B.w_out * cnhtc_pre_a_vehicle_model_B.b;
      // Sum: '<S54>/Add2'
      cnhtc_pre_a_vehicle_model_B.T_ext =
          cnhtc_pre_a_vehicle_model_B.Product4_e -
          cnhtc_pre_a_vehicle_model_B.Product2_g;
      // Sum: '<S13>/Add1'
      cnhtc_pre_a_vehicle_model_B.Add1_m =
          cnhtc_pre_a_vehicle_model_B.Product1_fs +
          cnhtc_pre_a_vehicle_model_B.T_ext;
      // Gain: '<S13>/Input Clutch Damping'
      cnhtc_pre_a_vehicle_model_B.InputClutchDamping_m =
          cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_bin *
          cnhtc_pre_a_vehicle_model_B.PumpIntegrator;
      // Sum: '<S13>/Input Sum'
      cnhtc_pre_a_vehicle_model_B.InputSum =
          (cnhtc_pre_a_vehicle_model_B.Product4_cv -
           cnhtc_pre_a_vehicle_model_B.Product2_a) -
          cnhtc_pre_a_vehicle_model_B.InputClutchDamping_m;
      // Product: '<S13>/Product2'
      cnhtc_pre_a_vehicle_model_B.Product2_f =
          cnhtc_pre_a_vehicle_model_B.PumpIntegrator *
          cnhtc_pre_a_vehicle_model_B.InputSum;
      // Product: '<S13>/Product'
      cnhtc_pre_a_vehicle_model_B.Product_i =
          cnhtc_pre_a_vehicle_model_B.w_out *
          cnhtc_pre_a_vehicle_model_B.Add1_m;
      // Sum: '<S13>/Add2'
      cnhtc_pre_a_vehicle_model_B.PwrStoredTrans_b =
          cnhtc_pre_a_vehicle_model_B.Product2_f +
          cnhtc_pre_a_vehicle_model_B.Product_i;
      // Product: '<S13>/Product10'
      cnhtc_pre_a_vehicle_model_B.Product10 =
          cnhtc_pre_a_vehicle_model_B.PumpIntegrator *
          cnhtc_pre_a_vehicle_model_B.InputClutchDamping_m;
      // Product: '<S54>/Product'
      cnhtc_pre_a_vehicle_model_B.Product_j =
          cnhtc_pre_a_vehicle_model_B.Product2_g *
          cnhtc_pre_a_vehicle_model_B.w_out;
      // Sum: '<S13>/Add3'
      cnhtc_pre_a_vehicle_model_B.Add3_f =
          cnhtc_pre_a_vehicle_model_B.Product10 +
          cnhtc_pre_a_vehicle_model_B.Product_j;
      // Product: '<S53>/Product3'
      cnhtc_pre_a_vehicle_model_B.Product3_j =
          cnhtc_pre_a_vehicle_model_B.Add2_o *
          cnhtc_pre_a_vehicle_model_B.Product2_a;
      // UnaryMinus: '<S53>/Unary Minus'
      cnhtc_pre_a_vehicle_model_B.UnaryMinus_f =
          -cnhtc_pre_a_vehicle_model_B.Product3_j;
      // Gain: '<S13>/Input Clutch Inertia'
      tmp = 1.0 / (rtP_Chas.Ie_kgm2 * 3.0);
      cnhtc_pre_a_vehicle_model_B.InputClutchInertia =
          tmp * cnhtc_pre_a_vehicle_model_B.InputSum;
      // Product: '<S13>/Product1'
      cnhtc_pre_a_vehicle_model_B.Product1_ai =
          cnhtc_pre_a_vehicle_model_B.Add1_m / cnhtc_pre_a_vehicle_model_B.J;
      // RelationalOperator: '<S57>/Compare' incorporates:
      //   Constant: '<S57>/Constant'
      tmp = -cnhtc_pre_a_vehicle_model_P.div0protectabspoly1_thresh;
      cnhtc_pre_a_vehicle_model_B.Compare_e =
          (cnhtc_pre_a_vehicle_model_B.w_out >= tmp);
      // RelationalOperator: '<S58>/Compare' incorporates:
      //   Constant: '<S58>/Constant'
      cnhtc_pre_a_vehicle_model_B.Compare_i =
          (cnhtc_pre_a_vehicle_model_B.w_out <=
           cnhtc_pre_a_vehicle_model_P.div0protectabspoly1_thresh);
      // Logic: '<S55>/Logical Operator'
      cnhtc_pre_a_vehicle_model_B.LogicalOperator_a =
          (cnhtc_pre_a_vehicle_model_B.Compare_e &&
           cnhtc_pre_a_vehicle_model_B.Compare_i);
      // Switch: '<S55>/Switch'
      if (cnhtc_pre_a_vehicle_model_B.LogicalOperator_a) {
        // Fcn: '<S55>/Fcn'
        tmp = cnhtc_pre_a_vehicle_model_B.w_out / 1.0e-6;
        tmp = rt_powd_snf(tmp, 2.0);
        cnhtc_pre_a_vehicle_model_B.Fcn = 2.0E-6 / (3.0 - tmp);
        cnhtc_pre_a_vehicle_model_B.Switch_l = cnhtc_pre_a_vehicle_model_B.Fcn;
      } else {
        // Abs: '<S55>/Abs'
        cnhtc_pre_a_vehicle_model_B.Abs_n =
            std::abs(cnhtc_pre_a_vehicle_model_B.w_out);
        cnhtc_pre_a_vehicle_model_B.Switch_l =
            cnhtc_pre_a_vehicle_model_B.Abs_n;
      }
      // End of Switch: '<S55>/Switch'
      // Product: '<S13>/Product3'
      cnhtc_pre_a_vehicle_model_B.Product3_p =
          cnhtc_pre_a_vehicle_model_B.PumpIntegrator /
          cnhtc_pre_a_vehicle_model_B.Switch_l;
      // SignalConversion: '<S13>/Signal Conversion1'
      cnhtc_pre_a_vehicle_model_B.Merge = cnhtc_pre_a_vehicle_model_B.w_out;
      // SignalConversion: '<S13>/Signal Conversion2'
      cnhtc_pre_a_vehicle_model_B.Merge3 =
          cnhtc_pre_a_vehicle_model_B.PumpIntegrator;
      // SignalConversion: '<S13>/Signal Conversion3'
      cnhtc_pre_a_vehicle_model_B.Merge2 =
          cnhtc_pre_a_vehicle_model_B.Product3_p;
      // SignalConversion: '<S13>/Signal Conversion4'
      cnhtc_pre_a_vehicle_model_B.Merge1 =
          cnhtc_pre_a_vehicle_model_B.PwrStoredTrans_b;
      // SignalConversion generated from: '<S13>/Signal Conversion5'
      cnhtc_pre_a_vehicle_model_B.PwrStoredTrans =
          cnhtc_pre_a_vehicle_model_B.PwrStoredTrans_b;
      // SignalConversion generated from: '<S13>/Signal Conversion5'
      cnhtc_pre_a_vehicle_model_B.PwrCltchLoss =
          cnhtc_pre_a_vehicle_model_B.UnaryMinus_f;
      // UnaryMinus: '<S13>/Unary Minus'
      cnhtc_pre_a_vehicle_model_B.PwrDampLoss_g =
          -cnhtc_pre_a_vehicle_model_B.Add3_f;
      // SignalConversion generated from: '<S13>/Signal Conversion5'
      cnhtc_pre_a_vehicle_model_B.PwrDampLoss =
          cnhtc_pre_a_vehicle_model_B.PwrDampLoss_g;
      // SignalConversion generated from: '<S13>/Signal Conversion5'
      cnhtc_pre_a_vehicle_model_B.PwrEffLoss =
          cnhtc_pre_a_vehicle_model_B.PwrEffLoss_f;
      // End of Outputs for SubSystem: '<S9>/Unlocked'
      break;
  }
  // End of If: '<S9>/If'
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Product: '<S12>/Product' incorporates:
    //   Constant: '<S12>/Constant1'
    cnhtc_pre_a_vehicle_model_B.Product =
        1.0 / cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_tauc;
    // Gain: '<S12>/2*pi'
    cnhtc_pre_a_vehicle_model_B.upi = cnhtc_pre_a_vehicle_model_P.upi_Gain *
                                      cnhtc_pre_a_vehicle_model_B.Product;
  }
  // Switch: '<S12>/Switch' incorporates:
  //   Constant: '<S12>/Constant'
  if (cnhtc_pre_a_vehicle_model_B.NewGear != 0.0) {
    cnhtc_pre_a_vehicle_model_B.Switch_i =
        cnhtc_pre_a_vehicle_model_B.Integrator1_o1;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_i =
        cnhtc_pre_a_vehicle_model_P.Constant_Value_c;
  }
  // End of Switch: '<S12>/Switch'
  // Sum: '<S30>/Sum'
  cnhtc_pre_a_vehicle_model_B.Sum = cnhtc_pre_a_vehicle_model_B.Switch_i -
                                    cnhtc_pre_a_vehicle_model_B.Integrator_es;
  // Product: '<S30>/Product'
  cnhtc_pre_a_vehicle_model_B.Product_e =
      cnhtc_pre_a_vehicle_model_B.upi * cnhtc_pre_a_vehicle_model_B.Sum;
  // Gain: '<S31>/Ratio of static to kinetic'
  tmp = cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_mus /
        cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_muk;
  cnhtc_pre_a_vehicle_model_B.Ratioofstatictokinetic =
      tmp * cnhtc_pre_a_vehicle_model_B.TorqueConversion;
  // RelationalOperator: '<S41>/Compare' incorporates:
  //   Constant: '<S41>/Constant'
  cnhtc_pre_a_vehicle_model_B.Compare_l =
      (cnhtc_pre_a_vehicle_model_B.Integrator1_o1 ==
       cnhtc_pre_a_vehicle_model_P.Constant_Value_d);
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Memory: '<S37>/Memory1'
    cnhtc_pre_a_vehicle_model_B.Memory1_c =
        cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput_m;
    // UnaryMinus: '<S37>/Unary Minus2'
    cnhtc_pre_a_vehicle_model_B.UnaryMinus2 =
        -cnhtc_pre_a_vehicle_model_B.Memory1_c;
    // Memory: '<S38>/Memory1'
    cnhtc_pre_a_vehicle_model_B.Memory1_j =
        cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput_c;
  }
  // Logic: '<S37>/Logical Operator2'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator2 =
      (cnhtc_pre_a_vehicle_model_B.Compare_l &&
       cnhtc_pre_a_vehicle_model_B.Compare_n);
  // Logic: '<S38>/Logical Operator1'
  cnhtc_pre_a_vehicle_model_B.ClutchClosed =
      !cnhtc_pre_a_vehicle_model_B.LogicalOperator2;
  // Logic: '<S38>/Logical Operator5'
  cnhtc_pre_a_vehicle_model_B.ClutchClosedandready =
      (cnhtc_pre_a_vehicle_model_B.Compare_n &&
       cnhtc_pre_a_vehicle_model_B.ClutchClosed);
  // Logic: '<S38>/Logical Operator7'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator7 =
      (cnhtc_pre_a_vehicle_model_B.LogicalOperator3 ||
       cnhtc_pre_a_vehicle_model_B.ClutchClosedandready);
  // Switch: '<S38>/Switch1'
  if (cnhtc_pre_a_vehicle_model_B.ClutchClosedandready) {
    cnhtc_pre_a_vehicle_model_B.Switch1 = cnhtc_pre_a_vehicle_model_B.NewGear;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch1 = cnhtc_pre_a_vehicle_model_B.Memory1_j;
  }
  // End of Switch: '<S38>/Switch1'
  // RelationalOperator: '<S38>/Relational Operator'
  cnhtc_pre_a_vehicle_model_B.Newgearrequest =
      (cnhtc_pre_a_vehicle_model_B.GearSel !=
       cnhtc_pre_a_vehicle_model_B.Switch1);
  // Logic: '<S38>/Logical Operator2'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator2_f =
      (cnhtc_pre_a_vehicle_model_B.LogicalOperator7 &&
       cnhtc_pre_a_vehicle_model_B.Newgearrequest);
  // Logic: '<S37>/Logical Operator3'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator3_l =
      (cnhtc_pre_a_vehicle_model_B.LogicalOperator2_f &&
       cnhtc_pre_a_vehicle_model_B.Compare_n);
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Memory: '<S37>/Memory2'
    cnhtc_pre_a_vehicle_model_B.Memory2 =
        cnhtc_pre_a_vehicle_model_DW.Memory2_PreviousInput;
  }
  // Switch: '<S37>/Switch1'
  if (cnhtc_pre_a_vehicle_model_B.LogicalOperator3_l) {
    cnhtc_pre_a_vehicle_model_B.Switch1_m =
        cnhtc_pre_a_vehicle_model_B.UnaryMinus2;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch1_m = cnhtc_pre_a_vehicle_model_B.Memory2;
  }
  // End of Switch: '<S37>/Switch1'
  // Gain: '<S37>/Gain1'
  tmp = 1.0 / cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_tc;
  cnhtc_pre_a_vehicle_model_B.Gain1_m =
      tmp * cnhtc_pre_a_vehicle_model_B.Switch1_m;
  // Logic: '<S38>/Logical Operator4'
  cnhtc_pre_a_vehicle_model_B.Begin =
      (cnhtc_pre_a_vehicle_model_B.Newgearrequest &&
       cnhtc_pre_a_vehicle_model_B.LogicalOperator2);
  // Logic: '<S38>/Logical Operator6'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator6 =
      !cnhtc_pre_a_vehicle_model_B.Newgearrequest;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // InitialCondition: '<S39>/IC' incorporates:
    //   Constant: '<S39>/Constant1'
    if (cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_fi) {
      cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_fi = false;
      cnhtc_pre_a_vehicle_model_B.IC_o = cnhtc_pre_a_vehicle_model_P.IC_Value_m;
    } else {
      cnhtc_pre_a_vehicle_model_B.IC_o =
          cnhtc_pre_a_vehicle_model_P.Constant1_Value_i;
    }
    // End of InitialCondition: '<S39>/IC'
  }
  // Integrator: '<S39>/Integrator1'
  // Limited  Integrator  (w/ Saturation Port)
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    zcEvent = (cnhtc_pre_a_vehicle_model_B.LogicalOperator6 &&
               (cnhtc_pre_a_vehicle_model_PrevZCX.Integrator1_Reset_ZCE !=
                POS_ZCSIG));
    cnhtc_pre_a_vehicle_model_PrevZCX.Integrator1_Reset_ZCE =
        cnhtc_pre_a_vehicle_model_B.LogicalOperator6;
    // evaluate zero-crossings
    if (zcEvent || (cnhtc_pre_a_vehicle_model_DW.Integrator1_IWORK_l != 0)) {
      cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h =
          cnhtc_pre_a_vehicle_model_B.IC_o;
    }
  }
  if (cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h >=
      cnhtc_pre_a_vehicle_model_P.Integrator1_UpperSat_j) {
    cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h =
        cnhtc_pre_a_vehicle_model_P.Integrator1_UpperSat_j;
    cnhtc_pre_a_vehicle_model_B.Integrator1_o2_j = 1.0;
  } else if (cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h <=
             cnhtc_pre_a_vehicle_model_P.Integrator1_LowerSat_a) {
    cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h =
        cnhtc_pre_a_vehicle_model_P.Integrator1_LowerSat_a;
    cnhtc_pre_a_vehicle_model_B.Integrator1_o2_j = -1.0;
  } else {
    cnhtc_pre_a_vehicle_model_B.Integrator1_o2_j = 0.0;
  }
  cnhtc_pre_a_vehicle_model_B.Integrator1_o1_c =
      cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h;
  // End of Integrator: '<S39>/Integrator1'
  // RelationalOperator: '<S42>/Compare' incorporates:
  //   Constant: '<S42>/Constant'
  cnhtc_pre_a_vehicle_model_B.Compare_j =
      (cnhtc_pre_a_vehicle_model_B.Integrator1_o2_j !=
       cnhtc_pre_a_vehicle_model_P.Constant_Value_h);
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Memory: '<S43>/Memory'
    cnhtc_pre_a_vehicle_model_B.Memory_j =
        cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_o;
  }
  // Logic: '<S43>/Logical Operator'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator =
      (cnhtc_pre_a_vehicle_model_B.Memory_j ||
       cnhtc_pre_a_vehicle_model_B.Begin);
  // Logic: '<S43>/Logical Operator2'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator2_k =
      !cnhtc_pre_a_vehicle_model_B.LogicalOperator6;
  // Logic: '<S43>/Logical Operator1'
  cnhtc_pre_a_vehicle_model_B.LogicalOperator1 =
      (cnhtc_pre_a_vehicle_model_B.LogicalOperator &&
       cnhtc_pre_a_vehicle_model_B.LogicalOperator2_k);
  // DataTypeConversion: '<S39>/Data Type Conversion'
  cnhtc_pre_a_vehicle_model_B.DataTypeConversion =
      cnhtc_pre_a_vehicle_model_B.LogicalOperator1;
  // Gain: '<S39>/Gain1'
  tmp = 1.0 / cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_ts;
  cnhtc_pre_a_vehicle_model_B.Gain1_f =
      tmp * cnhtc_pre_a_vehicle_model_B.DataTypeConversion;
  // Abs: '<S47>/Abs'
  cnhtc_pre_a_vehicle_model_B.Abs_j = std::abs(cnhtc_pre_a_vehicle_model_B.N);
  // Product: '<S47>/Product3'
  cnhtc_pre_a_vehicle_model_B.Product3 =
      cnhtc_pre_a_vehicle_model_B.J / cnhtc_pre_a_vehicle_model_B.Abs_j;
  // Sum: '<S47>/Add3' incorporates:
  //   Constant: '<S47>/Constant'
  tmp = rtP_Chas.Ie_kgm2 * 3.0;
  cnhtc_pre_a_vehicle_model_B.Add3 = tmp + cnhtc_pre_a_vehicle_model_B.Product3;
  // Product: '<S47>/Product8'
  cnhtc_pre_a_vehicle_model_B.ApparentInertiaRatio =
      1.0 / cnhtc_pre_a_vehicle_model_B.Add3 *
      cnhtc_pre_a_vehicle_model_B.Product3;
  // Product: '<S12>/Product2'
  cnhtc_pre_a_vehicle_model_B.Product2 =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus / cnhtc_pre_a_vehicle_model_B.N;
  // Product: '<S47>/Product1'
  cnhtc_pre_a_vehicle_model_B.Product1_j =
      cnhtc_pre_a_vehicle_model_B.Product2 / cnhtc_pre_a_vehicle_model_B.N;
  // Gain: '<S47>/Input Clutch Damping'
  cnhtc_pre_a_vehicle_model_B.InputClutchDamping =
      cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_bin *
      cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE;
  // Product: '<S47>/Product2'
  cnhtc_pre_a_vehicle_model_B.ApparentTransDamping =
      cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE *
      cnhtc_pre_a_vehicle_model_B.b;
  // Sum: '<S47>/Sum2'
  cnhtc_pre_a_vehicle_model_B.Sum2 =
      ((cnhtc_pre_a_vehicle_model_B.Saturation +
        cnhtc_pre_a_vehicle_model_B.Product1_j) -
       cnhtc_pre_a_vehicle_model_B.InputClutchDamping) -
      cnhtc_pre_a_vehicle_model_B.ApparentTransDamping;
  // Product: '<S47>/Product4'
  cnhtc_pre_a_vehicle_model_B.Product4 =
      cnhtc_pre_a_vehicle_model_B.ApparentInertiaRatio *
      cnhtc_pre_a_vehicle_model_B.Sum2;
  // Sum: '<S47>/Sum3'
  cnhtc_pre_a_vehicle_model_B.Sum3 =
      cnhtc_pre_a_vehicle_model_B.Product4 +
      cnhtc_pre_a_vehicle_model_B.ApparentTransDamping;
  // Abs: '<S44>/Abs'
  cnhtc_pre_a_vehicle_model_B.Abs_a =
      std::abs(cnhtc_pre_a_vehicle_model_B.Sum3);
  // RelationalOperator: '<S44>/Relational Operator'
  cnhtc_pre_a_vehicle_model_B.RelationalOperator =
      (cnhtc_pre_a_vehicle_model_B.Abs_a >=
       cnhtc_pre_a_vehicle_model_B.Ratioofstatictokinetic);
  // Abs: '<S48>/Abs'
  cnhtc_pre_a_vehicle_model_B.Abs_jd = std::abs(cnhtc_pre_a_vehicle_model_B.N);
  // Product: '<S48>/Product3'
  cnhtc_pre_a_vehicle_model_B.Product3_g =
      cnhtc_pre_a_vehicle_model_B.J / cnhtc_pre_a_vehicle_model_B.Abs_jd;
  // Sum: '<S48>/Add3' incorporates:
  //   Constant: '<S48>/Constant'
  tmp = rtP_Chas.Ie_kgm2 * 3.0;
  cnhtc_pre_a_vehicle_model_B.Add3_o =
      tmp + cnhtc_pre_a_vehicle_model_B.Product3_g;
  // Gain: '<S48>/Input Damping'
  cnhtc_pre_a_vehicle_model_B.InputDamping =
      cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_bin *
      cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE;
  // Product: '<S48>/Product1'
  cnhtc_pre_a_vehicle_model_B.Product1_e =
      cnhtc_pre_a_vehicle_model_B.Product2 / cnhtc_pre_a_vehicle_model_B.N;
  // Product: '<S48>/Product2'
  cnhtc_pre_a_vehicle_model_B.Product2_n =
      cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE *
      cnhtc_pre_a_vehicle_model_B.b;
  // Product: '<S48>/Product8'
  cnhtc_pre_a_vehicle_model_B.ApparentInertiaRatio_o =
      1.0 / cnhtc_pre_a_vehicle_model_B.Add3_o *
      cnhtc_pre_a_vehicle_model_B.Product3_g;
  // Sum: '<S48>/Sum2'
  cnhtc_pre_a_vehicle_model_B.Sum2_j =
      ((cnhtc_pre_a_vehicle_model_B.Saturation +
        cnhtc_pre_a_vehicle_model_B.Product1_e) -
       cnhtc_pre_a_vehicle_model_B.InputDamping) -
      cnhtc_pre_a_vehicle_model_B.Product2_n;
  // Product: '<S48>/Product4'
  cnhtc_pre_a_vehicle_model_B.Product4_c =
      cnhtc_pre_a_vehicle_model_B.ApparentInertiaRatio_o *
      cnhtc_pre_a_vehicle_model_B.Sum2_j;
  // Sum: '<S48>/Sum3'
  cnhtc_pre_a_vehicle_model_B.Sum3_m = cnhtc_pre_a_vehicle_model_B.Product4_c +
                                       cnhtc_pre_a_vehicle_model_B.Product2_n;
  // Product: '<S12>/Product1'
  cnhtc_pre_a_vehicle_model_B.Product1_a =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d *
      cnhtc_pre_a_vehicle_model_B.N;
  // Sum: '<S45>/Sum'
  cnhtc_pre_a_vehicle_model_B.Sum_o =
      cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE -
      cnhtc_pre_a_vehicle_model_B.Product1_a;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // HitCross: '<S45>/Velocities Match'
    zcEvent_0 =
        rt_ZCFcn(ANY_ZERO_CROSSING,
                 &cnhtc_pre_a_vehicle_model_PrevZCX.VelocitiesMatch_Input_ZCE,
                 (cnhtc_pre_a_vehicle_model_B.Sum_o -
                  cnhtc_pre_a_vehicle_model_P.VelocitiesMatch_Offset));
    if (cnhtc_pre_a_vehicle_model_DW.VelocitiesMatch_MODE == 0) {
      if (zcEvent_0 != NO_ZCEVENT) {
        cnhtc_pre_a_vehicle_model_B.VelocitiesMatch =
            !cnhtc_pre_a_vehicle_model_B.VelocitiesMatch;
        cnhtc_pre_a_vehicle_model_DW.VelocitiesMatch_MODE = 1;
      } else if (cnhtc_pre_a_vehicle_model_B.VelocitiesMatch) {
        cnhtc_pre_a_vehicle_model_B.VelocitiesMatch =
            ((!(cnhtc_pre_a_vehicle_model_B.Sum_o !=
                cnhtc_pre_a_vehicle_model_P.VelocitiesMatch_Offset)) &&
             cnhtc_pre_a_vehicle_model_B.VelocitiesMatch);
      } else {
        cnhtc_pre_a_vehicle_model_B.VelocitiesMatch =
            ((cnhtc_pre_a_vehicle_model_B.Sum_o ==
              cnhtc_pre_a_vehicle_model_P.VelocitiesMatch_Offset) ||
             cnhtc_pre_a_vehicle_model_B.VelocitiesMatch);
      }
    } else {
      cnhtc_pre_a_vehicle_model_B.VelocitiesMatch =
          ((!(cnhtc_pre_a_vehicle_model_B.Sum_o !=
              cnhtc_pre_a_vehicle_model_P.VelocitiesMatch_Offset)) &&
           cnhtc_pre_a_vehicle_model_B.VelocitiesMatch);
      cnhtc_pre_a_vehicle_model_DW.VelocitiesMatch_MODE = 0;
    }
    // End of HitCross: '<S45>/Velocities Match'
  }
  // Abs: '<S49>/Abs'
  cnhtc_pre_a_vehicle_model_B.Abs_o =
      std::abs(cnhtc_pre_a_vehicle_model_B.Sum3_m);
  // RelationalOperator: '<S49>/Relational Operator'
  cnhtc_pre_a_vehicle_model_B.RelationalOperator_p =
      (cnhtc_pre_a_vehicle_model_B.Abs_o <=
       cnhtc_pre_a_vehicle_model_B.Ratioofstatictokinetic);
  // Logic: '<S45>/Logic'
  cnhtc_pre_a_vehicle_model_B.Logic =
      (cnhtc_pre_a_vehicle_model_B.VelocitiesMatch &&
       cnhtc_pre_a_vehicle_model_B.RelationalOperator_p);
  // CombinatorialLogic: '<S46>/Combinatorial  Logic'
  rowIdx = 0U;
  tmp_0[0] = cnhtc_pre_a_vehicle_model_B.Logic;
  tmp_0[1] = cnhtc_pre_a_vehicle_model_B.RelationalOperator;
  tmp_0[2] = cnhtc_pre_a_vehicle_model_B.Memory_c;
  for (i = 0; i < 3; i++) {
    rowIdx = (rowIdx << 1) + tmp_0[static_cast<uint32_T>(i)];
  }
  cnhtc_pre_a_vehicle_model_B.CombinatorialLogic =
      cnhtc_pre_a_vehicle_model_P.CombinatorialLogic_table[rowIdx];
  // End of CombinatorialLogic: '<S46>/Combinatorial  Logic'
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // ModelReference: '<S1>/Engine_ECU' incorporates:
    //   Constant: '<S1>/Constant'
    //   Inport: '<Root>/pedalPos_pct'
    //   Outport: '<Root>/GearPos'
    Engine_ECUMDLOBJ2.step(&cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm,
                           &cnhtc_pre_a_vehicle_model_B.UnitDelay,
                           &cnhtc_pre_a_vehicle_model_P.Constant_Value_dt,
                           &cnhtc_pre_a_vehicle_model_U.pedalPos_pct,
                           &cnhtc_pre_a_vehicle_model_B.UnitDelay2,
                           &cnhtc_pre_a_vehicle_model_B.GearSel,
                           &cnhtc_pre_a_vehicle_model_Y.GearPos,
                           &cnhtc_pre_a_vehicle_model_B.TrqCmd);
    // Memory: '<S88>/Memory'
    cnhtc_pre_a_vehicle_model_B.Memory_i =
        cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_n;
    // Constant: '<S87>/domega_o'
    cnhtc_pre_a_vehicle_model_B.domega_o_e =
        cnhtc_pre_a_vehicle_model_P.TorsionalCompliance2_domega_o;
  }
  // Sum: '<S3>/Sum'
  cnhtc_pre_a_vehicle_model_B.Sum_l = cnhtc_pre_a_vehicle_model_B.TrqCmd -
                                      cnhtc_pre_a_vehicle_model_B.Integrator1;
  // Product: '<S3>/Divide' incorporates:
  //   Constant: '<S3>/Constant'
  cnhtc_pre_a_vehicle_model_B.Divide_p =
      cnhtc_pre_a_vehicle_model_B.Sum_l *
      cnhtc_pre_a_vehicle_model_P.ElectronicThrottleActuatorDynamics1_wc;
  // Integrator: '<S88>/Integrator'
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    zcEvent_0 =
        rt_ZCFcn(RISING_ZERO_CROSSING,
                 &cnhtc_pre_a_vehicle_model_PrevZCX.Integrator_Reset_ZCE_a,
                 (cnhtc_pre_a_vehicle_model_B.Memory_i));
    zcEvent = (zcEvent_0 != NO_ZCEVENT);
    // evaluate zero-crossings
    if (zcEvent || (cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_n != 0)) {
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_l =
          cnhtc_pre_a_vehicle_model_B.domega_o_e;
    }
  }
  cnhtc_pre_a_vehicle_model_B.Integrator_o =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_l;
  // End of Integrator: '<S88>/Integrator'
  // Gain: '<S87>/Gain2'
  cnhtc_pre_a_vehicle_model_B.Gain2_m =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance2_b *
      cnhtc_pre_a_vehicle_model_B.Integrator_o;
  // Integrator: '<S87>/Integrator'
  cnhtc_pre_a_vehicle_model_B.Integrator_f =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_o;
  // Gain: '<S87>/Gain1'
  cnhtc_pre_a_vehicle_model_B.Gain1_l =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance2_k *
      cnhtc_pre_a_vehicle_model_B.Integrator_f;
  // Sum: '<S87>/Subtract1'
  cnhtc_pre_a_vehicle_model_B.Subtract1_n =
      cnhtc_pre_a_vehicle_model_B.Gain2_m + cnhtc_pre_a_vehicle_model_B.Gain1_l;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Memory: '<S80>/Memory'
    cnhtc_pre_a_vehicle_model_B.Memory_k =
        cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_c;
    // Constant: '<S79>/domega_o'
    cnhtc_pre_a_vehicle_model_B.domega_o_p =
        cnhtc_pre_a_vehicle_model_P.TorsionalCompliance1_domega_o;
  }
  // Integrator: '<S80>/Integrator'
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    zcEvent_0 =
        rt_ZCFcn(RISING_ZERO_CROSSING,
                 &cnhtc_pre_a_vehicle_model_PrevZCX.Integrator_Reset_ZCE_av,
                 (cnhtc_pre_a_vehicle_model_B.Memory_k));
    zcEvent = (zcEvent_0 != NO_ZCEVENT);
    // evaluate zero-crossings
    if (zcEvent || (cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_l != 0)) {
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_c =
          cnhtc_pre_a_vehicle_model_B.domega_o_p;
    }
  }
  cnhtc_pre_a_vehicle_model_B.Integrator_i =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_c;
  // End of Integrator: '<S80>/Integrator'
  // Gain: '<S79>/Gain2'
  cnhtc_pre_a_vehicle_model_B.Gain2_f =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance1_b *
      cnhtc_pre_a_vehicle_model_B.Integrator_i;
  // Integrator: '<S79>/Integrator'
  cnhtc_pre_a_vehicle_model_B.Integrator_op =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_e;
  // Gain: '<S79>/Gain1'
  cnhtc_pre_a_vehicle_model_B.Gain1_mz =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance1_k *
      cnhtc_pre_a_vehicle_model_B.Integrator_op;
  // Sum: '<S79>/Subtract1'
  cnhtc_pre_a_vehicle_model_B.Subtract1_d =
      cnhtc_pre_a_vehicle_model_B.Gain2_f +
      cnhtc_pre_a_vehicle_model_B.Gain1_mz;
  // Sum: '<S4>/Add'
  cnhtc_pre_a_vehicle_model_B.Add_m = cnhtc_pre_a_vehicle_model_B.Subtract1_n +
                                      cnhtc_pre_a_vehicle_model_B.Subtract1_d;
  // SignalConversion generated from: '<S4>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.VectorConcatenate_p[0] =
      cnhtc_pre_a_vehicle_model_B.Subtract1_n;
  // SignalConversion generated from: '<S4>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.VectorConcatenate_p[1] =
      cnhtc_pre_a_vehicle_model_B.Subtract1_d;
  // SignalConversion generated from: '<S4>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.VectorConcatenate_p[2] = 0.0;
  // SignalConversion generated from: '<S4>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.VectorConcatenate_p[3] = 0.0;
  // Gain: '<S4>/Gain'
  tmp = 1.0 / rtP_Chas.Rt;
  cnhtc_pre_a_vehicle_model_B.Gain = tmp * cnhtc_pre_a_vehicle_model_B.Add_m;
  // Product: '<S4>/Divide' incorporates:
  //   Constant: '<S4>/Constant'
  cnhtc_pre_a_vehicle_model_B.a_sim =
      cnhtc_pre_a_vehicle_model_B.Gain /
      cnhtc_pre_a_vehicle_model_P.Constant_Value_e;
  // Integrator: '<S4>/Integrator'
  cnhtc_pre_a_vehicle_model_B.v =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_k;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Switch: '<S66>/Switch' incorporates:
    //   Constant: '<S66>/Constant'
    //   Constant: '<S66>/Constant1'
    if (cnhtc_pre_a_vehicle_model_P.Constant_Value_nr >
        cnhtc_pre_a_vehicle_model_P.Switch_Threshold_p) {
      cnhtc_pre_a_vehicle_model_B.diffDir =
          cnhtc_pre_a_vehicle_model_P.Constant1_Value_p;
    } else {
      // UnaryMinus: '<S66>/Unary Minus' incorporates:
      //   Constant: '<S66>/Constant1'
      cnhtc_pre_a_vehicle_model_B.UnaryMinus_m =
          -cnhtc_pre_a_vehicle_model_P.Constant1_Value_p;
      cnhtc_pre_a_vehicle_model_B.diffDir =
          cnhtc_pre_a_vehicle_model_B.UnaryMinus_m;
    }
    // End of Switch: '<S66>/Switch'
    // Constant: '<S62>/Constant'
    cnhtc_pre_a_vehicle_model_B.VectorConcatenate[0] =
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_omegaw1o;
    // Constant: '<S62>/Constant1'
    cnhtc_pre_a_vehicle_model_B.VectorConcatenate[1] =
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_omegaw2o;
  }
  // Gain: '<S66>/Gain'
  // Limited  Integrator
  tmp = rtP_Chas.DifRatio / 2.0;
  for (i = 0; i < 2; i++) {
    // Integrator: '<S62>/Integrator'
    if (cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_l5 != 0) {
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[i] =
          cnhtc_pre_a_vehicle_model_B.VectorConcatenate[i];
    }
    if (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[i] >=
        cnhtc_pre_a_vehicle_model_P.Integrator_UpperSat_h) {
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[i] =
          cnhtc_pre_a_vehicle_model_P.Integrator_UpperSat_h;
    } else {
      if (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[i] <=
          cnhtc_pre_a_vehicle_model_P.Integrator_LowerSat_l) {
        cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[i] =
            cnhtc_pre_a_vehicle_model_P.Integrator_LowerSat_l;
      }
    }
    cnhtc_pre_a_vehicle_model_B.Integrator_f1[i] =
        cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[i];
    // End of Integrator: '<S62>/Integrator'
    // Product: '<S66>/Product'
    cnhtc_pre_a_vehicle_model_B.Product_m[i] =
        cnhtc_pre_a_vehicle_model_B.diffDir *
        cnhtc_pre_a_vehicle_model_B.Integrator_f1[i];
    // Gain: '<S66>/Gain'
    cnhtc_pre_a_vehicle_model_B.Gain_i[i] =
        tmp * cnhtc_pre_a_vehicle_model_B.Product_m[i];
  }
  // Sum: '<S66>/Sum of Elements'
  tmp = -0.0;
  for (i = 0; i < 2; i++) {
    tmp += cnhtc_pre_a_vehicle_model_B.Gain_i[i];
    // UnaryMinus: '<S66>/Unary Minus1'
    cnhtc_pre_a_vehicle_model_B.UnaryMinus1[i] =
        -cnhtc_pre_a_vehicle_model_B.Integrator_f1[i];
    // Gain: '<S66>/Gain1'
    cnhtc_pre_a_vehicle_model_B.Gain1_p[i] =
        cnhtc_pre_a_vehicle_model_P.Gain1_Gain *
        cnhtc_pre_a_vehicle_model_B.Integrator_f1[i];
  }
  cnhtc_pre_a_vehicle_model_B.SumofElements = tmp;
  // End of Sum: '<S66>/Sum of Elements'
  // SignalConversion generated from: '<S66>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.VectorConcatenate_e[0] =
      cnhtc_pre_a_vehicle_model_B.SumofElements;
  // SignalConversion generated from: '<S66>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.VectorConcatenate_e[1] =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus1[0];
  // SignalConversion generated from: '<S66>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.VectorConcatenate_e[2] =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus1[1];
  // Sum: '<S66>/Add'
  cnhtc_pre_a_vehicle_model_B.VectorConcatenate_e[3] =
      cnhtc_pre_a_vehicle_model_B.Gain1_p[0] -
      cnhtc_pre_a_vehicle_model_B.Gain1_p[1];
  // Product: '<S76>/Product1'
  cnhtc_pre_a_vehicle_model_B.Product1_b =
      cnhtc_pre_a_vehicle_model_B.Subtract1 *
      cnhtc_pre_a_vehicle_model_B.VectorConcatenate_e[0];
  // Switch: '<S76>/Switch' incorporates:
  //   Constant: '<S76>/Constant'
  //   Constant: '<S78>/Constant'
  if (cnhtc_pre_a_vehicle_model_B.Product1_b >
      cnhtc_pre_a_vehicle_model_P.Switch_Threshold_g3) {
    cnhtc_pre_a_vehicle_model_B.Switch_n =
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_eta;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_n =
        cnhtc_pre_a_vehicle_model_P.Constant_Value_g;
  }
  // End of Switch: '<S76>/Switch'
  // Product: '<S76>/Product4'
  cnhtc_pre_a_vehicle_model_B.Product4_h =
      cnhtc_pre_a_vehicle_model_B.Switch_n *
      cnhtc_pre_a_vehicle_model_B.Subtract1;
  // UnaryMinus: '<S87>/Unary Minus'
  cnhtc_pre_a_vehicle_model_B.UnaryMinus_d =
      -cnhtc_pre_a_vehicle_model_B.Subtract1_n;
  // Product: '<S74>/Product1'
  cnhtc_pre_a_vehicle_model_B.Product1_h =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus_d *
      cnhtc_pre_a_vehicle_model_B.VectorConcatenate_e[1];
  // Switch: '<S74>/Switch' incorporates:
  //   Constant: '<S74>/Constant'
  //   Constant: '<S78>/Constant'
  if (cnhtc_pre_a_vehicle_model_B.Product1_h >
      cnhtc_pre_a_vehicle_model_P.Switch_Threshold_o) {
    cnhtc_pre_a_vehicle_model_B.Switch_k =
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_eta;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_k =
        cnhtc_pre_a_vehicle_model_P.Constant_Value_gj;
  }
  // End of Switch: '<S74>/Switch'
  // Product: '<S74>/Product4'
  cnhtc_pre_a_vehicle_model_B.Product4_p =
      cnhtc_pre_a_vehicle_model_B.Switch_k *
      cnhtc_pre_a_vehicle_model_B.UnaryMinus_d;
  // UnaryMinus: '<S79>/Unary Minus'
  cnhtc_pre_a_vehicle_model_B.UnaryMinus_e =
      -cnhtc_pre_a_vehicle_model_B.Subtract1_d;
  // Product: '<S75>/Product1'
  cnhtc_pre_a_vehicle_model_B.Product1_f =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus_e *
      cnhtc_pre_a_vehicle_model_B.VectorConcatenate_e[2];
  // Switch: '<S75>/Switch' incorporates:
  //   Constant: '<S75>/Constant'
  //   Constant: '<S78>/Constant'
  if (cnhtc_pre_a_vehicle_model_B.Product1_f >
      cnhtc_pre_a_vehicle_model_P.Switch_Threshold_ob) {
    cnhtc_pre_a_vehicle_model_B.Switch_e =
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_eta;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_e =
        cnhtc_pre_a_vehicle_model_P.Constant_Value_k;
  }
  // End of Switch: '<S75>/Switch'
  // Product: '<S75>/Product4'
  cnhtc_pre_a_vehicle_model_B.Product4_j =
      cnhtc_pre_a_vehicle_model_B.Switch_e *
      cnhtc_pre_a_vehicle_model_B.UnaryMinus_e;
  // SignalConversion generated from: '<S65>/ SFunction ' incorporates:
  //   MATLAB Function: '<S62>/Open Differential'
  cnhtc_pre_a_vehicle_model_B.TmpSignalConversionAtSFunctionInport1[0] =
      cnhtc_pre_a_vehicle_model_B.Product4_h;
  cnhtc_pre_a_vehicle_model_B.TmpSignalConversionAtSFunctionInport1[1] =
      cnhtc_pre_a_vehicle_model_B.Product4_p;
  cnhtc_pre_a_vehicle_model_B.TmpSignalConversionAtSFunctionInport1[2] =
      cnhtc_pre_a_vehicle_model_B.Product4_j;
  // MATLAB Function: '<S62>/Open Differential' incorporates:
  //   Constant: '<S62>/Jd'
  //   Constant: '<S62>/Jw1'
  //   Constant: '<S62>/Jw3'
  //   Constant: '<S62>/Ndiff2'
  //   Constant: '<S62>/bd'
  //   Constant: '<S62>/bw1'
  //   Constant: '<S62>/bw2'
  // MATLAB Function 'Open Differential/Open Differential': '<S65>:1'
  // '<S65>:1:2' coder.allowpcode('plain')
  // '<S65>:1:3' if shaftSwitchMask==1
  if (cnhtc_pre_a_vehicle_model_P.OpenDifferential_shaftSwitchMask == 1.0) {
    // '<S65>:1:4' [~,xdot] = automldiffopen(u,bw1,bd,bw2,Ndiff,1,Jd,Jw1,Jw2,x);
    automldiffopen_m841FDlI(
        cnhtc_pre_a_vehicle_model_B.TmpSignalConversionAtSFunctionInport1,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_bw1,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_bd,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_bw2, rtP_Chas.DifRatio,
        1.0, cnhtc_pre_a_vehicle_model_P.OpenDifferential_Jd,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_Jw1,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_Jw2,
        cnhtc_pre_a_vehicle_model_B.Integrator_f1, unusedU1,
        cnhtc_pre_a_vehicle_model_B.xdot);
    // '<S65>:1:4' ~
  } else {
    // '<S65>:1:5' else
    // '<S65>:1:6' [~,xdot] = automldiffopen(u,bw1,bd,bw2,Ndiff,0,Jd,Jw1,Jw2,x);
    automldiffopen_m841FDlI(
        cnhtc_pre_a_vehicle_model_B.TmpSignalConversionAtSFunctionInport1,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_bw1,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_bd,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_bw2, rtP_Chas.DifRatio,
        0.0, cnhtc_pre_a_vehicle_model_P.OpenDifferential_Jd,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_Jw1,
        cnhtc_pre_a_vehicle_model_P.OpenDifferential_Jw2,
        cnhtc_pre_a_vehicle_model_B.Integrator_f1, unusedU1,
        cnhtc_pre_a_vehicle_model_B.xdot);
    // '<S65>:1:6' ~
  }
  // UnaryMinus: '<S69>/Unary Minus2'
  for (i = 0; i < 2; i++) {
    cnhtc_pre_a_vehicle_model_B.UnaryMinus2_g[i] =
        -cnhtc_pre_a_vehicle_model_B.xdot[i];
  }
  // End of UnaryMinus: '<S69>/Unary Minus2'
  // SignalConversion generated from: '<S69>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.omegadot[1] =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus2_g[0];
  // SignalConversion generated from: '<S69>/Vector Concatenate'
  cnhtc_pre_a_vehicle_model_B.omegadot[2] =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus2_g[1];
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Switch: '<S69>/Switch1' incorporates:
    //   Constant: '<S69>/Constant'
    //   Constant: '<S69>/Constant6'
    if (cnhtc_pre_a_vehicle_model_P.Constant_Value_np >
        cnhtc_pre_a_vehicle_model_P.Switch1_Threshold) {
      cnhtc_pre_a_vehicle_model_B.diffDir_d =
          cnhtc_pre_a_vehicle_model_P.Constant6_Value;
    } else {
      // UnaryMinus: '<S69>/Unary Minus' incorporates:
      //   Constant: '<S69>/Constant6'
      cnhtc_pre_a_vehicle_model_B.UnaryMinus_o =
          -cnhtc_pre_a_vehicle_model_P.Constant6_Value;
      cnhtc_pre_a_vehicle_model_B.diffDir_d =
          cnhtc_pre_a_vehicle_model_B.UnaryMinus_o;
    }
    // End of Switch: '<S69>/Switch1'
  }
  // Gain: '<S69>/Gain1'
  tmp = rtP_Chas.DifRatio / 2.0;
  for (i = 0; i < 2; i++) {
    // Product: '<S69>/Product1'
    cnhtc_pre_a_vehicle_model_B.Product1_eh[i] =
        cnhtc_pre_a_vehicle_model_B.diffDir_d *
        cnhtc_pre_a_vehicle_model_B.xdot[i];
    // Gain: '<S69>/Gain1'
    cnhtc_pre_a_vehicle_model_B.Gain1_f0[i] =
        tmp * cnhtc_pre_a_vehicle_model_B.Product1_eh[i];
  }
  // Sum: '<S69>/Sum of Elements2'
  tmp = -0.0;
  for (i = 0; i < 2; i++) {
    tmp += cnhtc_pre_a_vehicle_model_B.Gain1_f0[i];
  }
  cnhtc_pre_a_vehicle_model_B.omegadot[0] = tmp;
  // End of Sum: '<S69>/Sum of Elements2'
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Gain: '<S8>/Gain11'
    cnhtc_pre_a_vehicle_model_B.Gain11 =
        cnhtc_pre_a_vehicle_model_P.Gain11_Gain *
        cnhtc_pre_a_vehicle_model_B.UnitDelay;
    // Product: '<S8>/Divide5' incorporates:
    //   Constant: '<S8>/Constant12'
    cnhtc_pre_a_vehicle_model_B.Divide5 =
        cnhtc_pre_a_vehicle_model_B.Gain11 / rtP_Chas.Rt;
  }
  // Sum: '<S79>/Subtract'
  cnhtc_pre_a_vehicle_model_B.Subtract =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus1[1] -
      cnhtc_pre_a_vehicle_model_B.Divide5;
  // Switch: '<S80>/Switch'
  if (cnhtc_pre_a_vehicle_model_B.Memory_k != 0.0) {
    cnhtc_pre_a_vehicle_model_B.Switch_nm =
        cnhtc_pre_a_vehicle_model_B.Integrator_i;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_nm =
        cnhtc_pre_a_vehicle_model_B.domega_o_p;
  }
  // End of Switch: '<S80>/Switch'
  // Sum: '<S80>/Sum'
  cnhtc_pre_a_vehicle_model_B.Sum_h = cnhtc_pre_a_vehicle_model_B.Subtract -
                                      cnhtc_pre_a_vehicle_model_B.Switch_nm;
  // Product: '<S80>/Product' incorporates:
  //   Constant: '<S79>/omega_c'
  cnhtc_pre_a_vehicle_model_B.Product_h =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance1_omega_c *
      cnhtc_pre_a_vehicle_model_B.Sum_h;
  // Sum: '<S87>/Subtract'
  cnhtc_pre_a_vehicle_model_B.Subtract_m =
      cnhtc_pre_a_vehicle_model_B.UnaryMinus1[0] -
      cnhtc_pre_a_vehicle_model_B.Divide5;
  // Switch: '<S88>/Switch'
  if (cnhtc_pre_a_vehicle_model_B.Memory_i != 0.0) {
    cnhtc_pre_a_vehicle_model_B.Switch_h =
        cnhtc_pre_a_vehicle_model_B.Integrator_o;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_h =
        cnhtc_pre_a_vehicle_model_B.domega_o_e;
  }
  // End of Switch: '<S88>/Switch'
  // Sum: '<S88>/Sum'
  cnhtc_pre_a_vehicle_model_B.Sum_b = cnhtc_pre_a_vehicle_model_B.Subtract_m -
                                      cnhtc_pre_a_vehicle_model_B.Switch_h;
  // Product: '<S88>/Product' incorporates:
  //   Constant: '<S87>/omega_c'
  cnhtc_pre_a_vehicle_model_B.Product_et =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance2_omega_c *
      cnhtc_pre_a_vehicle_model_B.Sum_b;
  // Product: '<S5>/Product'
  cnhtc_pre_a_vehicle_model_B.Product_p =
      cnhtc_pre_a_vehicle_model_B.EngTrq *
      cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm;
  // Gain: '<S5>/Gain'
  cnhtc_pre_a_vehicle_model_B.Gain_n = cnhtc_pre_a_vehicle_model_P.Gain_Gain_j *
                                       cnhtc_pre_a_vehicle_model_B.Product_p;
  // Lookup_n-D: '<S5>/fuel_map'
  cnhtc_pre_a_vehicle_model_B.fuel_map = look2_binlcapw(
      cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm,
      cnhtc_pre_a_vehicle_model_B.EngTrq, rtP_fuel_engspeed, rtP_fuel_engtor,
      rtP_fuel_bsfc, cnhtc_pre_a_vehicle_model_P.fuel_map_maxIndex, 12U);
  // Product: '<S5>/Product2'
  cnhtc_pre_a_vehicle_model_B.Product2_p =
      cnhtc_pre_a_vehicle_model_B.fuel_map * cnhtc_pre_a_vehicle_model_B.Gain_n;
  // Gain: '<S5>/Gain2'
  cnhtc_pre_a_vehicle_model_B.Gain2_a = cnhtc_pre_a_vehicle_model_P.Gain2_Gain *
                                        cnhtc_pre_a_vehicle_model_B.Product2_p;
  // Saturate: '<S5>/Saturation'
  tmp = cnhtc_pre_a_vehicle_model_B.Gain2_a;
  u1 = cnhtc_pre_a_vehicle_model_P.Saturation_LowerSat_p;
  u2 = cnhtc_pre_a_vehicle_model_P.Saturation_UpperSat_i;
  if (tmp > u2) {
    cnhtc_pre_a_vehicle_model_B.Saturation_b = u2;
  } else if (tmp < u1) {
    cnhtc_pre_a_vehicle_model_B.Saturation_b = u1;
  } else {
    cnhtc_pre_a_vehicle_model_B.Saturation_b = tmp;
  }
  // End of Saturate: '<S5>/Saturation'
  // Gain: '<S1>/Gain1'
  cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm_j =
      cnhtc_pre_a_vehicle_model_P.Gain1_Gain_k *
      cnhtc_pre_a_vehicle_model_B.Merge3;
  // Integrator: '<S98>/Integrator'
  cnhtc_pre_a_vehicle_model_B.Integrator_od =
      cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_j;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // Gain: '<S98>/RPM to deg//s'
    cnhtc_pre_a_vehicle_model_B.RPMtodegs =
        cnhtc_pre_a_vehicle_model_P.RPMtodegs_Gain *
        cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm;
  }
  // Sum: '<S116>/Subtract'
  cnhtc_pre_a_vehicle_model_B.Subtract_j =
      cnhtc_pre_a_vehicle_model_B.Merge -
      cnhtc_pre_a_vehicle_model_B.SumofElements;
  // Switch: '<S117>/Switch'
  if (cnhtc_pre_a_vehicle_model_B.Memory != 0.0) {
    cnhtc_pre_a_vehicle_model_B.Switch_hd =
        cnhtc_pre_a_vehicle_model_B.Integrator_e;
  } else {
    cnhtc_pre_a_vehicle_model_B.Switch_hd =
        cnhtc_pre_a_vehicle_model_B.domega_o;
  }
  // End of Switch: '<S117>/Switch'
  // Sum: '<S117>/Sum'
  cnhtc_pre_a_vehicle_model_B.Sum_f = cnhtc_pre_a_vehicle_model_B.Subtract_j -
                                      cnhtc_pre_a_vehicle_model_B.Switch_hd;
  // Product: '<S117>/Product' incorporates:
  //   Constant: '<S116>/omega_c'
  cnhtc_pre_a_vehicle_model_B.Product_f =
      cnhtc_pre_a_vehicle_model_P.PropShaft_omega_c *
      cnhtc_pre_a_vehicle_model_B.Sum_f;
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    // ModelReference: '<Root>/SteerWhlMdl' incorporates:
    //   Inport: '<Root>/SteerWhAngle_rad'
    //   Outport: '<Root>/SteerWhAngle_DZ_deg'
    SteerWhlMdlMDLOBJ4.step(&cnhtc_pre_a_vehicle_model_U.SteerWhAngle_rad,
                            &cnhtc_pre_a_vehicle_model_Y.SteerWhAngle_DZ_deg);
  }
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
      // Update for UnitDelay: '<S1>/Unit Delay1'
      cnhtc_pre_a_vehicle_model_DW.UnitDelay1_DSTATE =
          cnhtc_pre_a_vehicle_model_B.NewGear;
      // Update for UnitDelay: '<S1>/Unit Delay3' incorporates:
      //   Outport: '<Root>/EngSpd_rpm'
      cnhtc_pre_a_vehicle_model_DW.UnitDelay3_DSTATE =
          cnhtc_pre_a_vehicle_model_Y.EngSpd_rpm;
      // Update for UnitDelay: '<S1>/Unit Delay4'
      cnhtc_pre_a_vehicle_model_DW.UnitDelay4_DSTATE =
          cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm_j;
      // Update for UnitDelay: '<S1>/Unit Delay2'
      cnhtc_pre_a_vehicle_model_DW.UnitDelay2_DSTATE =
          cnhtc_pre_a_vehicle_model_B.Memory_c;
      // Update for UnitDelay: '<Root>/Unit Delay1' incorporates:
      //   Inport: '<Root>/ax_g'
      cnhtc_pre_a_vehicle_model_DW.UnitDelay1_DSTATE_j =
          cnhtc_pre_a_vehicle_model_U.ax_g;
      // Update for Memory: '<S46>/Memory'
      cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_j =
          cnhtc_pre_a_vehicle_model_B.CombinatorialLogic;
      // Update for Memory: '<S117>/Memory' incorporates:
      //   Constant: '<S117>/Reset'
      cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput =
          cnhtc_pre_a_vehicle_model_P.Reset_Value_j;
      // Update for UnitDelay: '<Root>/Unit Delay' incorporates:
      //   Inport: '<Root>/Vx_kmph'
      cnhtc_pre_a_vehicle_model_DW.UnitDelay_DSTATE =
          cnhtc_pre_a_vehicle_model_U.Vx_kmph;
      // Update for Memory: '<S34>/Memory3'
      cnhtc_pre_a_vehicle_model_DW.Memory3_PreviousInput =
          cnhtc_pre_a_vehicle_model_B.NewGear;
      // Update for Memory: '<S34>/Memory'
      cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_p =
          cnhtc_pre_a_vehicle_model_B.GearSel;
      // Update for Memory: '<S34>/Memory1'
      cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput =
          cnhtc_pre_a_vehicle_model_B.CmdGear;
    }
    // Update for Integrator: '<S117>/Integrator'
    cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK = 0;
    // Update for Integrator: '<S37>/Integrator1'
    cnhtc_pre_a_vehicle_model_DW.Integrator1_IWORK = 0;
    if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
      // Update for Memory: '<S39>/Memory2'
      cnhtc_pre_a_vehicle_model_DW.Memory2_PreviousInput_e =
          cnhtc_pre_a_vehicle_model_B.Compare_j;
      // Update for Memory: '<S37>/Memory1'
      cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput_m =
          cnhtc_pre_a_vehicle_model_B.Memory2;
      // Update for Memory: '<S38>/Memory1'
      cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput_c =
          cnhtc_pre_a_vehicle_model_B.Switch1;
      // Update for Memory: '<S37>/Memory2'
      cnhtc_pre_a_vehicle_model_DW.Memory2_PreviousInput =
          cnhtc_pre_a_vehicle_model_B.Switch1_m;
    }
    // Update for If: '<S9>/If'
    switch (cnhtc_pre_a_vehicle_model_DW.If_ActiveSubsystem) {
      case 0:
        // Update for IfAction SubSystem: '<S9>/Locked' incorporates:
        //   ActionPort: '<S11>/Action'
        // Update for Integrator: '<S11>/Locked Shaft Integrator'
        cnhtc_pre_a_vehicle_model_DW.LockedShaftIntegrator_IWORK = 0;
        // End of Update for SubSystem: '<S9>/Locked'
        break;
      case 1:
        // Update for IfAction SubSystem: '<S9>/Unlocked' incorporates:
        //   ActionPort: '<S13>/Action'
        // Update for Integrator: '<S13>/Pump Integrator'
        cnhtc_pre_a_vehicle_model_DW.PumpIntegrator_IWORK = 0;
        // Update for Integrator: '<S13>/Integrator'
        cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_e = 0;
        // End of Update for SubSystem: '<S9>/Unlocked'
        break;
    }
    // End of Update for If: '<S9>/If'
    // Update for Integrator: '<S39>/Integrator1'
    cnhtc_pre_a_vehicle_model_DW.Integrator1_IWORK_l = 0;
    if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
      // Update for Memory: '<S43>/Memory'
      cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_o =
          cnhtc_pre_a_vehicle_model_B.LogicalOperator1;
      // Update for Memory: '<S88>/Memory' incorporates:
      //   Constant: '<S88>/Reset'
      cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_n =
          cnhtc_pre_a_vehicle_model_P.Reset_Value_g;
      // Update for Memory: '<S80>/Memory' incorporates:
      //   Constant: '<S80>/Reset'
      cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_c =
          cnhtc_pre_a_vehicle_model_P.Reset_Value;
    }
    // Update for Integrator: '<S88>/Integrator'
    cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_n = 0;
    // Update for Integrator: '<S80>/Integrator'
    cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_l = 0;
    // Update for Integrator: '<S62>/Integrator'
    cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_l5 = 0;
    // ContTimeOutputInconsistentWithStateAtMajorOutputFlag is set, need to run
    // a minor output
    if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
      if (rtsiGetContTimeOutputInconsistentWithStateAtMajorStep(
              &(&cnhtc_pre_a_vehicle_model_M)->solverInfo)) {
        rtsiSetSimTimeStep(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                           MINOR_TIME_STEP);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep(
            &(&cnhtc_pre_a_vehicle_model_M)->solverInfo, false);
        CNHTC_VEHICLE_MODEL_codeModelClass::step();
        rtsiSetSimTimeStep(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                           MAJOR_TIME_STEP);
      }
    }
  }  // end MajorTimeStep
  if (rtmIsMajorTimeStep((&cnhtc_pre_a_vehicle_model_M))) {
    rt_ertODEUpdateContinuousStates(
        &(&cnhtc_pre_a_vehicle_model_M)->solverInfo);
    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.
    ++(&cnhtc_pre_a_vehicle_model_M)->Timing.clockTick0;
    (&cnhtc_pre_a_vehicle_model_M)->Timing.t[0] =
        rtsiGetSolverStopTime(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo);
    {
      // Update absolute timer for sample time: [0.001s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.001, which is
      //  the step size of the task. Size of "clockTick1" ensures timer will not
      //  overflow during the application lifespan selected.
      (&cnhtc_pre_a_vehicle_model_M)->Timing.clockTick1++;
    }
  }  // end MajorTimeStep
}  // NOLINT
// Derivatives for root system: '<Root>'
void CNHTC_VEHICLE_MODEL_codeModelClass::
    cnhtc_pre_a_vehicle_model_derivatives() {
  int_T iS;
  boolean_T lsat;
  boolean_T usat;
  XDot_cnhtc_pre_a_vehicle_model_T *_rtXdot;
  _rtXdot = ((XDot_cnhtc_pre_a_vehicle_model_T      // NOLINT
                  *)(&cnhtc_pre_a_vehicle_model_M)  // NOLINT
                 ->derivs);                         // NOLINT
  // Derivatives for Integrator: '<S3>/Integrator1'
  _rtXdot->Integrator1_CSTATE = cnhtc_pre_a_vehicle_model_B.Divide_p;
  // Derivatives for Integrator: '<S5>/Integrator'
  _rtXdot->Integrator_CSTATE = cnhtc_pre_a_vehicle_model_B.Saturation_b;
  // Derivatives for Integrator: '<S117>/Integrator'
  _rtXdot->Integrator_CSTATE_p = cnhtc_pre_a_vehicle_model_B.Product_f;
  // Derivatives for Integrator: '<S116>/Integrator'
  _rtXdot->Integrator_CSTATE_f = cnhtc_pre_a_vehicle_model_B.Subtract_j;
  // Derivatives for Integrator: '<S30>/Integrator'
  _rtXdot->Integrator_CSTATE_g = cnhtc_pre_a_vehicle_model_B.Product_e;
  // Derivatives for Integrator: '<S37>/Integrator1'
  lsat = (cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g <=
          cnhtc_pre_a_vehicle_model_P.Integrator1_LowerSat);
  usat = (cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g >=
          cnhtc_pre_a_vehicle_model_P.Integrator1_UpperSat);
  if (((!lsat) && (!usat)) ||
      (lsat && (cnhtc_pre_a_vehicle_model_B.Gain1_m > 0.0)) ||
      (usat && (cnhtc_pre_a_vehicle_model_B.Gain1_m < 0.0))) {
    _rtXdot->Integrator1_CSTATE_g = cnhtc_pre_a_vehicle_model_B.Gain1_m;
  } else {
    // in saturation
    _rtXdot->Integrator1_CSTATE_g = 0.0;
  }
  // End of Derivatives for Integrator: '<S37>/Integrator1'
  // Derivatives for If: '<S9>/If'
  ((XDot_cnhtc_pre_a_vehicle_model_T *)(&cnhtc_pre_a_vehicle_model_M)  // NOLINT
       ->derivs)                                                       // NOLINT
      ->LockedShaftIntegrator_CSTATE = 0.0;                            // NOLINT
  {
    real_T *dx;
    int_T i;
    dx = &(((XDot_cnhtc_pre_a_vehicle_model_T      // NOLINT
                 *)(&cnhtc_pre_a_vehicle_model_M)  // NOLINT
                ->derivs)                          // NOLINT
               ->PumpIntegrator_CSTATE);           // NOLINT
    for (i = 0; i < 2; i++) {
      dx[i] = 0.0;
    }
  }
  switch (cnhtc_pre_a_vehicle_model_DW.If_ActiveSubsystem) {
    case 0:
      // Derivatives for IfAction SubSystem: '<S9>/Locked' incorporates:
      //   ActionPort: '<S11>/Action'
      // Derivatives for Integrator: '<S11>/Locked Shaft Integrator'
      lsat = (cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE <=
              cnhtc_pre_a_vehicle_model_P.LockedShaftIntegrator_LowerSat);
      usat = (cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE >=
              cnhtc_pre_a_vehicle_model_P.LockedShaftIntegrator_UpperSat);
      if (((!lsat) && (!usat)) ||
          (lsat && (cnhtc_pre_a_vehicle_model_B.Product8 > 0.0)) ||
          (usat && (cnhtc_pre_a_vehicle_model_B.Product8 < 0.0))) {
        _rtXdot->LockedShaftIntegrator_CSTATE =
            cnhtc_pre_a_vehicle_model_B.Product8;
      } else {
        // in saturation
        _rtXdot->LockedShaftIntegrator_CSTATE = 0.0;
      }
      // End of Derivatives for Integrator: '<S11>/Locked Shaft Integrator'
      // End of Derivatives for SubSystem: '<S9>/Locked'
      break;
    case 1:
      // Derivatives for IfAction SubSystem: '<S9>/Unlocked' incorporates:
      //   ActionPort: '<S13>/Action'
      // Derivatives for Integrator: '<S13>/Pump Integrator'
      lsat = (cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE <=
              cnhtc_pre_a_vehicle_model_P.PumpIntegrator_LowerSat);
      usat = (cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE >=
              cnhtc_pre_a_vehicle_model_P.PumpIntegrator_UpperSat);
      if (((!lsat) && (!usat)) ||
          (lsat && (cnhtc_pre_a_vehicle_model_B.InputClutchInertia > 0.0)) ||
          (usat && (cnhtc_pre_a_vehicle_model_B.InputClutchInertia < 0.0))) {
        _rtXdot->PumpIntegrator_CSTATE =
            cnhtc_pre_a_vehicle_model_B.InputClutchInertia;
      } else {
        // in saturation
        _rtXdot->PumpIntegrator_CSTATE = 0.0;
      }
      // End of Derivatives for Integrator: '<S13>/Pump Integrator'
      // Derivatives for Integrator: '<S13>/Integrator'
      lsat = (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d <=
              cnhtc_pre_a_vehicle_model_P.Integrator_LowerSat);
      usat = (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d >=
              cnhtc_pre_a_vehicle_model_P.Integrator_UpperSat);
      if (((!lsat) && (!usat)) ||
          (lsat && (cnhtc_pre_a_vehicle_model_B.Product1_ai > 0.0)) ||
          (usat && (cnhtc_pre_a_vehicle_model_B.Product1_ai < 0.0))) {
        _rtXdot->Integrator_CSTATE_d = cnhtc_pre_a_vehicle_model_B.Product1_ai;
      } else {
        // in saturation
        _rtXdot->Integrator_CSTATE_d = 0.0;
      }
      // End of Derivatives for Integrator: '<S13>/Integrator'
      // End of Derivatives for SubSystem: '<S9>/Unlocked'
      break;
  }
  // End of Derivatives for If: '<S9>/If'
  // Derivatives for Integrator: '<S39>/Integrator1'
  lsat = (cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h <=
          cnhtc_pre_a_vehicle_model_P.Integrator1_LowerSat_a);
  usat = (cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h >=
          cnhtc_pre_a_vehicle_model_P.Integrator1_UpperSat_j);
  if (((!lsat) && (!usat)) ||
      (lsat && (cnhtc_pre_a_vehicle_model_B.Gain1_f > 0.0)) ||
      (usat && (cnhtc_pre_a_vehicle_model_B.Gain1_f < 0.0))) {
    _rtXdot->Integrator1_CSTATE_h = cnhtc_pre_a_vehicle_model_B.Gain1_f;
  } else {
    // in saturation
    _rtXdot->Integrator1_CSTATE_h = 0.0;
  }
  // End of Derivatives for Integrator: '<S39>/Integrator1'
  // Derivatives for Integrator: '<S88>/Integrator'
  _rtXdot->Integrator_CSTATE_l = cnhtc_pre_a_vehicle_model_B.Product_et;
  // Derivatives for Integrator: '<S87>/Integrator'
  _rtXdot->Integrator_CSTATE_o = cnhtc_pre_a_vehicle_model_B.Subtract_m;
  // Derivatives for Integrator: '<S80>/Integrator'
  _rtXdot->Integrator_CSTATE_c = cnhtc_pre_a_vehicle_model_B.Product_h;
  // Derivatives for Integrator: '<S79>/Integrator'
  _rtXdot->Integrator_CSTATE_e = cnhtc_pre_a_vehicle_model_B.Subtract;
  // Derivatives for Integrator: '<S4>/Integrator'
  _rtXdot->Integrator_CSTATE_k = cnhtc_pre_a_vehicle_model_B.a_sim;
  // Derivatives for Integrator: '<S62>/Integrator'
  for (iS = 0; iS < 2; iS++) {
    lsat = (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[iS] <=
            cnhtc_pre_a_vehicle_model_P.Integrator_LowerSat_l);
    usat = (cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[iS] >=
            cnhtc_pre_a_vehicle_model_P.Integrator_UpperSat_h);
    if (((!lsat) && (!usat)) ||
        (lsat && (cnhtc_pre_a_vehicle_model_B.xdot[iS] > 0.0)) ||
        (usat && (cnhtc_pre_a_vehicle_model_B.xdot[iS] < 0.0))) {
      _rtXdot->Integrator_CSTATE_ks[iS] = cnhtc_pre_a_vehicle_model_B.xdot[iS];
    } else {
      // in saturation
      _rtXdot->Integrator_CSTATE_ks[iS] = 0.0;
    }
  }
  // End of Derivatives for Integrator: '<S62>/Integrator'
  // Derivatives for Integrator: '<S98>/Integrator'
  _rtXdot->Integrator_CSTATE_j = cnhtc_pre_a_vehicle_model_B.RPMtodegs;
}
// Model initialize function
void CNHTC_VEHICLE_MODEL_codeModelClass::initialize() {
  // Registration code
  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  // non-finite (run-time) assignments
  cnhtc_pre_a_vehicle_model_P.Saturation_UpperSat = rtInf;
  cnhtc_pre_a_vehicle_model_P.Saturation_UpperSat_a = rtInf;
  cnhtc_pre_a_vehicle_model_P.Saturation_UpperSat_i = rtInf;
  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                          &(&cnhtc_pre_a_vehicle_model_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                &rtmGetTPtr((&cnhtc_pre_a_vehicle_model_M)));
    rtsiSetStepSizePtr(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                       &(&cnhtc_pre_a_vehicle_model_M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                 &(&cnhtc_pre_a_vehicle_model_M)->derivs);
    rtsiSetContStatesPtr(
        &(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
        (real_T **)&(&cnhtc_pre_a_vehicle_model_M)->contStates);  // NOLINT
    rtsiSetNumContStatesPtr(
        &(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
        &(&cnhtc_pre_a_vehicle_model_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(
        &(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
        &(&cnhtc_pre_a_vehicle_model_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(
        &(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
        &(&cnhtc_pre_a_vehicle_model_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(
        &(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
        &(&cnhtc_pre_a_vehicle_model_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                          (&rtmGetErrorStatus((&cnhtc_pre_a_vehicle_model_M))));
    rtsiSetRTModelPtr(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                      (&cnhtc_pre_a_vehicle_model_M));
  }
  rtsiSetSimTimeStep(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
                     MAJOR_TIME_STEP);
  (&cnhtc_pre_a_vehicle_model_M)->intgData.y =
      (&cnhtc_pre_a_vehicle_model_M)->odeY;
  (&cnhtc_pre_a_vehicle_model_M)->intgData.f[0] =
      (&cnhtc_pre_a_vehicle_model_M)->odeF[0];
  (&cnhtc_pre_a_vehicle_model_M)->intgData.f[1] =
      (&cnhtc_pre_a_vehicle_model_M)->odeF[1];
  (&cnhtc_pre_a_vehicle_model_M)->intgData.f[2] =
      (&cnhtc_pre_a_vehicle_model_M)->odeF[2];
  (&cnhtc_pre_a_vehicle_model_M)->contStates = ((
      X_cnhtc_pre_a_vehicle_model_T *)&cnhtc_pre_a_vehicle_model_X);  // NOLINT
  (&cnhtc_pre_a_vehicle_model_M)->periodicContStateIndices =
      ((int_T *)cnhtc_pre_a_vehicle_model_PeriodicIndX);  // NOLINT
  (&cnhtc_pre_a_vehicle_model_M)->periodicContStateRanges =
      ((real_T *)cnhtc_pre_a_vehicle_model_PeriodicRngX);  // NOLINT
  rtsiSetSolverData(
      &(&cnhtc_pre_a_vehicle_model_M)->solverInfo,
      static_cast<void *>(&(&cnhtc_pre_a_vehicle_model_M)->intgData));
  rtsiSetSolverName(&(&cnhtc_pre_a_vehicle_model_M)->solverInfo, "ode3");
  rtmSetTPtr((&cnhtc_pre_a_vehicle_model_M),
             &(&cnhtc_pre_a_vehicle_model_M)->Timing.tArray[0]);
  (&cnhtc_pre_a_vehicle_model_M)->Timing.stepSize0 = 0.001;
  rtmSetFirstInitCond((&cnhtc_pre_a_vehicle_model_M), 1);
  // block I/O
  (void)std::memset((static_cast<void *>(&cnhtc_pre_a_vehicle_model_B)), 0,
                    sizeof(B_cnhtc_pre_a_vehicle_model_T));
  {
    int32_T i;
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.VectorConcatenate[i] = 0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.Integrator_f1[i] = 0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.Product_m[i] = 0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.Gain_i[i] = 0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.UnaryMinus1[i] = 0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.Gain1_p[i] = 0.0;
    }
    for (i = 0; i < 4; i++) {
      cnhtc_pre_a_vehicle_model_B.VectorConcatenate_e[i] = 0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.UnaryMinus2_g[i] = 0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.Product1_eh[i] = 0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.Gain1_f0[i] = 0.0;
    }
    for (i = 0; i < 3; i++) {
      cnhtc_pre_a_vehicle_model_B.omegadot[i] = 0.0;
    }
    for (i = 0; i < 4; i++) {
      cnhtc_pre_a_vehicle_model_B.VectorConcatenate_p[i] = 0.0;
    }
    for (i = 0; i < 3; i++) {
      cnhtc_pre_a_vehicle_model_B.TmpSignalConversionAtSFunctionInport1[i] =
          0.0;
    }
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_B.xdot[i] = 0.0;
    }
    cnhtc_pre_a_vehicle_model_B.Integrator1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm = 0.0;
    cnhtc_pre_a_vehicle_model_B.EngTrq = 0.0;
    cnhtc_pre_a_vehicle_model_B.Saturation = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add = 0.0;
    cnhtc_pre_a_vehicle_model_B.Abs = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Divide = 0.0;
    cnhtc_pre_a_vehicle_model_B.Abs1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Divide1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.uDLookupTable = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnitDelay1_k = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory = 0.0;
    cnhtc_pre_a_vehicle_model_B.domega_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain2 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator_h = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnaryMinus = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator_es = 0.0;
    cnhtc_pre_a_vehicle_model_B.ClutchGain = 0.0;
    cnhtc_pre_a_vehicle_model_B.Saturation_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.TorqueConversion = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnitDelay = 0.0;
    cnhtc_pre_a_vehicle_model_B.GearSel = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory3 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add2 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.CmdGear = 0.0;
    cnhtc_pre_a_vehicle_model_B.Constant = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator1_o1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator1_o2 = 0.0;
    cnhtc_pre_a_vehicle_model_B.NewGear = 0.0;
    cnhtc_pre_a_vehicle_model_B.b = 0.0;
    cnhtc_pre_a_vehicle_model_B.J = 0.0;
    cnhtc_pre_a_vehicle_model_B.N = 0.0;
    cnhtc_pre_a_vehicle_model_B.IC = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch = 0.0;
    cnhtc_pre_a_vehicle_model_B.IC_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.IC_d = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Merge = 0.0;
    cnhtc_pre_a_vehicle_model_B.Merge1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Merge2 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Merge3 = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrStoredTrans = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrCltchLoss = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrDampLoss = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrEffLoss = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product = 0.0;
    cnhtc_pre_a_vehicle_model_B.upi = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_i = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Ratioofstatictokinetic = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory1_c = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnaryMinus2 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory1_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch1 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory2 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch1_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain1_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.IC_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator1_o1_c = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator1_o2_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.DataTypeConversion = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain1_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Abs_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product3 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add3 = 0.0;
    cnhtc_pre_a_vehicle_model_B.ApparentInertiaRatio = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.InputClutchDamping = 0.0;
    cnhtc_pre_a_vehicle_model_B.ApparentTransDamping = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum2 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum3 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Abs_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.Abs_jd = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product3_g = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add3_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.InputDamping = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_n = 0.0;
    cnhtc_pre_a_vehicle_model_B.ApparentInertiaRatio_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum2_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_c = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum3_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.Abs_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.TrqCmd = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum_l = 0.0;
    cnhtc_pre_a_vehicle_model_B.Divide_p = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory_i = 0.0;
    cnhtc_pre_a_vehicle_model_B.domega_o_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain2_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain1_l = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract1_n = 0.0;
    cnhtc_pre_a_vehicle_model_B.Memory_k = 0.0;
    cnhtc_pre_a_vehicle_model_B.domega_o_p = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator_i = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain2_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator_op = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain1_mz = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract1_d = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain = 0.0;
    cnhtc_pre_a_vehicle_model_B.a_sim = 0.0;
    cnhtc_pre_a_vehicle_model_B.v = 0.0;
    cnhtc_pre_a_vehicle_model_B.diffDir = 0.0;
    cnhtc_pre_a_vehicle_model_B.SumofElements = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_b = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_n = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_h = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnaryMinus_d = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_h = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_k = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_p = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnaryMinus_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.diffDir_d = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain11 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Divide5 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_nm = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum_h = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product_h = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_h = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum_b = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product_et = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product_p = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain_n = 0.0;
    cnhtc_pre_a_vehicle_model_B.fuel_map = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_p = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain2_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.Saturation_b = 0.0;
    cnhtc_pre_a_vehicle_model_B.EngSpdFdbk_rpm_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.Integrator_od = 0.0;
    cnhtc_pre_a_vehicle_model_B.RPMtodegs = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_hd = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnaryMinus_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnaryMinus_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_bw = 0.0;
    cnhtc_pre_a_vehicle_model_B.Eta1D = 0.0;
    cnhtc_pre_a_vehicle_model_B.PumpIntegrator = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_n = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_cv = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract_mb = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.w_out = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_ex = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_b = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract_g = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_d = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrEffLoss_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_eu = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add2_o = 0.0;
    cnhtc_pre_a_vehicle_model_B.Gain_nb = 0.0;
    cnhtc_pre_a_vehicle_model_B.TrigonometricFunction = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_fs = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_g = 0.0;
    cnhtc_pre_a_vehicle_model_B.T_ext = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add1_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.InputClutchDamping_m = 0.0;
    cnhtc_pre_a_vehicle_model_B.InputSum = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product_i = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrStoredTrans_b = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product10 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add3_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product3_j = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnaryMinus_f = 0.0;
    cnhtc_pre_a_vehicle_model_B.InputClutchInertia = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_ai = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_l = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product3_p = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrDampLoss_g = 0.0;
    cnhtc_pre_a_vehicle_model_B.Fcn = 0.0;
    cnhtc_pre_a_vehicle_model_B.Abs_n = 0.0;
    cnhtc_pre_a_vehicle_model_B.Eta1D_b = 0.0;
    cnhtc_pre_a_vehicle_model_B.Abs_k = 0.0;
    cnhtc_pre_a_vehicle_model_B.omega = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_ei = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_aq = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract_l = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_h = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product5 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_fr = 0.0;
    cnhtc_pre_a_vehicle_model_B.Switch_k4 = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product4_pm = 0.0;
    cnhtc_pre_a_vehicle_model_B.Subtract_c = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrEffLoss_i = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product1_l = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product6 = 0.0;
    cnhtc_pre_a_vehicle_model_B.inputclutchDamping = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add1_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add2_n = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product3_c = 0.0;
    cnhtc_pre_a_vehicle_model_B.Add3_ff = 0.0;
    cnhtc_pre_a_vehicle_model_B.Sum_a = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrStoredTrans_e = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product2_fr = 0.0;
    cnhtc_pre_a_vehicle_model_B.UnaryMinus_p = 0.0;
    cnhtc_pre_a_vehicle_model_B.PwrDampLoss_d = 0.0;
    cnhtc_pre_a_vehicle_model_B.Product8 = 0.0;
  }
  // states (continuous)
  {
    (void)std::memset(static_cast<void *>(&cnhtc_pre_a_vehicle_model_X), 0,
                      sizeof(X_cnhtc_pre_a_vehicle_model_T));
  }
  // Periodic continuous states
  {
    (void)std::memset(
        static_cast<void *>(cnhtc_pre_a_vehicle_model_PeriodicIndX), 0,
        1 * sizeof(int_T));
    (void)std::memset(
        static_cast<void *>(cnhtc_pre_a_vehicle_model_PeriodicRngX), 0,
        2 * sizeof(real_T));
  }
  // states (dwork)
  (void)std::memset(static_cast<void *>(&cnhtc_pre_a_vehicle_model_DW), 0,
                    sizeof(DW_cnhtc_pre_a_vehicle_model_T));
  cnhtc_pre_a_vehicle_model_DW.UnitDelay1_DSTATE = 0.0;
  cnhtc_pre_a_vehicle_model_DW.UnitDelay3_DSTATE = 0.0;
  cnhtc_pre_a_vehicle_model_DW.UnitDelay4_DSTATE = 0.0;
  cnhtc_pre_a_vehicle_model_DW.UnitDelay1_DSTATE_j = 0.0;
  cnhtc_pre_a_vehicle_model_DW.UnitDelay_DSTATE = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory3_PreviousInput = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_p = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput_m = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput_c = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory2_PreviousInput = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_n = 0.0;
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_c = 0.0;
  // external inputs
  cnhtc_pre_a_vehicle_model_U.pedalPos_pct = 0.0;
  cnhtc_pre_a_vehicle_model_U.XBR1_ExternalAccele = 0.0;
  cnhtc_pre_a_vehicle_model_U.XBR1_Ctrl_Mode = 0.0;
  cnhtc_pre_a_vehicle_model_U.SteerWhAngle_rad = 0.0;
  cnhtc_pre_a_vehicle_model_U.Vx_kmph = 0.0;
  cnhtc_pre_a_vehicle_model_U.ax_g = 0.0;
  cnhtc_pre_a_vehicle_model_U.Mass_kg = 0.0;
  // external outputs
  (void)std::memset(static_cast<void *>(&cnhtc_pre_a_vehicle_model_Y), 0,
                    sizeof(ExtY_cnhtc_pre_a_vehicle_model_T));
  cnhtc_pre_a_vehicle_model_Y.GearPos = 0.0;
  cnhtc_pre_a_vehicle_model_Y.throttle_pct = 0.0;
  cnhtc_pre_a_vehicle_model_Y.EngTrq_Nm = 0.0;
  cnhtc_pre_a_vehicle_model_Y.EngSpd_rpm = 0.0;
  cnhtc_pre_a_vehicle_model_Y.engine_torque_loss_percent = 0.0;
  cnhtc_pre_a_vehicle_model_Y.engine_torque_percent = 0.0;
  cnhtc_pre_a_vehicle_model_Y.TransTorOut_Nm = 0.0;
  {
    int32_T i;
    for (i = 0; i < 4; i++) {
      cnhtc_pre_a_vehicle_model_Y.bwdWhlPre_Mpa[i] = 0.0;
    }
  }
  {
    int32_T i;
    for (i = 0; i < 2; i++) {
      cnhtc_pre_a_vehicle_model_Y.fwdWhlPre_Mpa[i] = 0.0;
    }
  }
  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      cnhtc_pre_a_vehicle_model_Y.TrailWhlPre_Mpa[i] = 0.0;
    }
  }
  cnhtc_pre_a_vehicle_model_Y.SteerWhAngle_DZ_deg = 0.0;
  cnhtc_pre_a_vehicle_model_Y.fuel_consumption = 0.0;
  // Model Initialize function for ModelReference Block: '<Root>/Brake_System'
  // Set error status pointer for ModelReference Block: '<Root>/Brake_System'
  Brake_SystemMDLOBJ1.setErrorStatusPointer(
      rtmGetErrorStatusPointer((&cnhtc_pre_a_vehicle_model_M)));
  Brake_SystemMDLOBJ1.initialize();
  // Model Initialize function for ModelReference Block: '<S1>/Engine_ECU'
  // Set error status pointer for ModelReference Block: '<S1>/Engine_ECU'
  Engine_ECUMDLOBJ2.setErrorStatusPointer(
      rtmGetErrorStatusPointer((&cnhtc_pre_a_vehicle_model_M)));
  Engine_ECUMDLOBJ2.initialize();
  // Model Initialize function for ModelReference Block: '<S1>/TCU'
  // Set error status pointer for ModelReference Block: '<S1>/TCU'
  TCUMDLOBJ3.setErrorStatusPointer(
      rtmGetErrorStatusPointer((&cnhtc_pre_a_vehicle_model_M)));
  TCUMDLOBJ3.initialize();
  // Model Initialize function for ModelReference Block: '<Root>/SteerWhlMdl'
  // Set error status pointer for ModelReference Block: '<Root>/SteerWhlMdl'
  SteerWhlMdlMDLOBJ4.setErrorStatusPointer(
      rtmGetErrorStatusPointer((&cnhtc_pre_a_vehicle_model_M)));
  SteerWhlMdlMDLOBJ4.initialize();
  // Start for Constant: '<S116>/domega_o'
  cnhtc_pre_a_vehicle_model_B.domega_o =
      cnhtc_pre_a_vehicle_model_P.PropShaft_domega_o;
  // Start for Constant: '<S37>/Constant'
  cnhtc_pre_a_vehicle_model_B.Constant =
      cnhtc_pre_a_vehicle_model_P.Constant_Value_hd;
  // Start for InitialCondition: '<S16>/IC'
  cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime = true;
  // Start for InitialCondition: '<S17>/IC'
  cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_e = true;
  // Start for InitialCondition: '<S15>/IC'
  cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_f = true;
  // Start for If: '<S9>/If'
  cnhtc_pre_a_vehicle_model_DW.If_ActiveSubsystem = -1;
  // Start for InitialCondition: '<S39>/IC'
  cnhtc_pre_a_vehicle_model_B.IC_o = cnhtc_pre_a_vehicle_model_P.IC_Value_m;
  cnhtc_pre_a_vehicle_model_DW.IC_FirstOutputTime_fi = true;
  // Start for Constant: '<S87>/domega_o'
  cnhtc_pre_a_vehicle_model_B.domega_o_e =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance2_domega_o;
  // Start for Constant: '<S79>/domega_o'
  cnhtc_pre_a_vehicle_model_B.domega_o_p =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance1_domega_o;
  cnhtc_pre_a_vehicle_model_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  cnhtc_pre_a_vehicle_model_PrevZCX.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  cnhtc_pre_a_vehicle_model_PrevZCX.VelocitiesMatch_Input_ZCE =
      UNINITIALIZED_ZCSIG;
  cnhtc_pre_a_vehicle_model_PrevZCX.Integrator_Reset_ZCE_a =
      UNINITIALIZED_ZCSIG;
  cnhtc_pre_a_vehicle_model_PrevZCX.Integrator_Reset_ZCE_av =
      UNINITIALIZED_ZCSIG;
  // InitializeConditions for UnitDelay: '<S1>/Unit Delay1'
  cnhtc_pre_a_vehicle_model_DW.UnitDelay1_DSTATE =
      cnhtc_pre_a_vehicle_model_P.UnitDelay1_InitialCondition;
  // InitializeConditions for Integrator: '<S3>/Integrator1'
  cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE =
      cnhtc_pre_a_vehicle_model_P.Integrator1_IC;
  // InitializeConditions for UnitDelay: '<S1>/Unit Delay3'
  cnhtc_pre_a_vehicle_model_DW.UnitDelay3_DSTATE =
      cnhtc_pre_a_vehicle_model_P.UnitDelay3_InitialCondition;
  // InitializeConditions for UnitDelay: '<S1>/Unit Delay4'
  cnhtc_pre_a_vehicle_model_DW.UnitDelay4_DSTATE =
      cnhtc_pre_a_vehicle_model_P.UnitDelay4_InitialCondition;
  // InitializeConditions for UnitDelay: '<S1>/Unit Delay2'
  cnhtc_pre_a_vehicle_model_DW.UnitDelay2_DSTATE =
      cnhtc_pre_a_vehicle_model_P.UnitDelay2_InitialCondition;
  // InitializeConditions for UnitDelay: '<Root>/Unit Delay1'
  cnhtc_pre_a_vehicle_model_DW.UnitDelay1_DSTATE_j =
      cnhtc_pre_a_vehicle_model_P.UnitDelay1_InitialCondition_a;
  // InitializeConditions for Integrator: '<S5>/Integrator'
  cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE =
      cnhtc_pre_a_vehicle_model_P.Integrator_IC;
  // InitializeConditions for Memory: '<S46>/Memory'
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_j =
      cnhtc_pre_a_vehicle_model_P.Memory_InitialCondition_pv;
  // InitializeConditions for Memory: '<S117>/Memory'
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput =
      cnhtc_pre_a_vehicle_model_P.Memory_InitialCondition;
  // InitializeConditions for Integrator: '<S117>/Integrator' incorporates:
  //   Integrator: '<S37>/Integrator1'
  if (rtmIsFirstInitCond((&cnhtc_pre_a_vehicle_model_M))) {
    cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_p = 0.0;
    cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_g = 0.0;
  }
  cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK = 1;
  // End of InitializeConditions for Integrator: '<S117>/Integrator'
  // InitializeConditions for Integrator: '<S116>/Integrator'
  cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_f =
      cnhtc_pre_a_vehicle_model_P.PropShaft_theta_o;
  // InitializeConditions for Integrator: '<S30>/Integrator'
  cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_g =
      cnhtc_pre_a_vehicle_model_P.Integrator_IC_h;
  // InitializeConditions for UnitDelay: '<Root>/Unit Delay'
  cnhtc_pre_a_vehicle_model_DW.UnitDelay_DSTATE =
      cnhtc_pre_a_vehicle_model_P.UnitDelay_InitialCondition;
  // InitializeConditions for Memory: '<S34>/Memory3'
  cnhtc_pre_a_vehicle_model_DW.Memory3_PreviousInput = rtP_VEH.InitGearPos;
  // InitializeConditions for Memory: '<S34>/Memory'
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_p = rtP_VEH.InitGearPos;
  // InitializeConditions for Memory: '<S34>/Memory1'
  cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput = rtP_VEH.InitGearPos;
  // InitializeConditions for Integrator: '<S37>/Integrator1'
  cnhtc_pre_a_vehicle_model_DW.Integrator1_IWORK = 1;
  // InitializeConditions for Memory: '<S39>/Memory2'
  cnhtc_pre_a_vehicle_model_DW.Memory2_PreviousInput_e =
      cnhtc_pre_a_vehicle_model_P.AutomatedManualTransmission_SynchLocked;
  // InitializeConditions for Memory: '<S37>/Memory1'
  cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput_m =
      cnhtc_pre_a_vehicle_model_P.Memory1_InitialCondition;
  // InitializeConditions for Memory: '<S38>/Memory1'
  cnhtc_pre_a_vehicle_model_DW.Memory1_PreviousInput_c =
      cnhtc_pre_a_vehicle_model_P.Memory1_InitialCondition_k;
  // InitializeConditions for Memory: '<S37>/Memory2'
  cnhtc_pre_a_vehicle_model_DW.Memory2_PreviousInput =
      cnhtc_pre_a_vehicle_model_P.Memory2_InitialCondition;
  // InitializeConditions for Integrator: '<S39>/Integrator1' incorporates:
  //   Integrator: '<S88>/Integrator'
  if (rtmIsFirstInitCond((&cnhtc_pre_a_vehicle_model_M))) {
    cnhtc_pre_a_vehicle_model_X.Integrator1_CSTATE_h = 0.0;
    cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_l = 0.0;
  }
  cnhtc_pre_a_vehicle_model_DW.Integrator1_IWORK_l = 1;
  // End of InitializeConditions for Integrator: '<S39>/Integrator1'
  // InitializeConditions for Memory: '<S43>/Memory'
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_o =
      cnhtc_pre_a_vehicle_model_P.Memory_InitialCondition_b;
  // InitializeConditions for Memory: '<S88>/Memory'
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_n =
      cnhtc_pre_a_vehicle_model_P.Memory_InitialCondition_g;
  // InitializeConditions for Integrator: '<S88>/Integrator'
  cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_n = 1;
  // InitializeConditions for Integrator: '<S87>/Integrator'
  cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_o =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance2_theta_o;
  // InitializeConditions for Memory: '<S80>/Memory'
  cnhtc_pre_a_vehicle_model_DW.Memory_PreviousInput_c =
      cnhtc_pre_a_vehicle_model_P.Memory_InitialCondition_p;
  // InitializeConditions for Integrator: '<S80>/Integrator' incorporates:
  //   Integrator: '<S62>/Integrator'
  if (rtmIsFirstInitCond((&cnhtc_pre_a_vehicle_model_M))) {
    cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_c = 0.0;
    cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[0] = 0.0;
    cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_ks[1] = 0.0;
  }
  cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_l = 1;
  // End of InitializeConditions for Integrator: '<S80>/Integrator'
  // InitializeConditions for Integrator: '<S79>/Integrator'
  cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_e =
      cnhtc_pre_a_vehicle_model_P.TorsionalCompliance1_theta_o;
  // InitializeConditions for Integrator: '<S4>/Integrator'
  cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_k =
      cnhtc_pre_a_vehicle_model_P.Integrator_IC_g;
  // InitializeConditions for Integrator: '<S62>/Integrator'
  cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_l5 = 1;
  // InitializeConditions for Integrator: '<S98>/Integrator'
  cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_j =
      cnhtc_pre_a_vehicle_model_P.Integrator_IC_i;
  // SystemInitialize for ModelReference: '<Root>/Brake_System' incorporates:
  //   Inport: '<Root>/Mass_kg'
  //   Inport: '<Root>/XBR1_Ctrl_Mode'
  //   Inport: '<Root>/XBR1_ExternalAccele'
  //   Outport: '<Root>/TrailWhlPre_Mpa'
  //   Outport: '<Root>/bwdWhlPre_Mpa'
  //   Outport: '<Root>/fwdWhlPre_Mpa'
  Brake_SystemMDLOBJ1.init();
  // SystemInitialize for ModelReference: '<S1>/TCU' incorporates:
  //   Inport: '<Root>/pedalPos_pct'
  TCUMDLOBJ3.init(&cnhtc_pre_a_vehicle_model_B.GearSel);
  // SystemInitialize for IfAction SubSystem: '<S9>/Unlocked'
  // SystemInitialize for IfAction SubSystem: '<S9>/Locked'
  // InitializeConditions for Integrator: '<S11>/Locked Shaft Integrator'
  // incorporates:
  //   Integrator: '<S13>/Pump Integrator'
  if (rtmIsFirstInitCond((&cnhtc_pre_a_vehicle_model_M))) {
    cnhtc_pre_a_vehicle_model_X.LockedShaftIntegrator_CSTATE = 0.0;
    cnhtc_pre_a_vehicle_model_X.PumpIntegrator_CSTATE = 0.0;
  }
  // End of SystemInitialize for SubSystem: '<S9>/Unlocked'
  cnhtc_pre_a_vehicle_model_DW.LockedShaftIntegrator_IWORK = 1;
  // End of InitializeConditions for Integrator: '<S11>/Locked Shaft Integrator'
  // End of SystemInitialize for SubSystem: '<S9>/Locked'
  // SystemInitialize for IfAction SubSystem: '<S9>/Unlocked'
  // InitializeConditions for Integrator: '<S13>/Pump Integrator'
  cnhtc_pre_a_vehicle_model_DW.PumpIntegrator_IWORK = 1;
  // InitializeConditions for Integrator: '<S13>/Integrator'
  if (rtmIsFirstInitCond((&cnhtc_pre_a_vehicle_model_M))) {
    cnhtc_pre_a_vehicle_model_X.Integrator_CSTATE_d = 0.0;
  }
  cnhtc_pre_a_vehicle_model_DW.Integrator_IWORK_e = 1;
  // End of InitializeConditions for Integrator: '<S13>/Integrator'
  // End of SystemInitialize for SubSystem: '<S9>/Unlocked'
  // SystemInitialize for Merge generated from: '<S9>/Merge4'
  cnhtc_pre_a_vehicle_model_B.PwrStoredTrans =
      cnhtc_pre_a_vehicle_model_P.Merge4_1_InitialOutput;
  // SystemInitialize for Merge generated from: '<S9>/Merge4'
  cnhtc_pre_a_vehicle_model_B.PwrCltchLoss =
      cnhtc_pre_a_vehicle_model_P.Merge4_2_InitialOutput;
  // SystemInitialize for Merge generated from: '<S9>/Merge4'
  cnhtc_pre_a_vehicle_model_B.PwrDampLoss =
      cnhtc_pre_a_vehicle_model_P.Merge4_3_InitialOutput;
  // SystemInitialize for Merge generated from: '<S9>/Merge4'
  cnhtc_pre_a_vehicle_model_B.PwrEffLoss =
      cnhtc_pre_a_vehicle_model_P.Merge4_4_InitialOutput;
  // SystemInitialize for ModelReference: '<S1>/Engine_ECU' incorporates:
  //   Constant: '<S1>/Constant'
  //   Inport: '<Root>/pedalPos_pct'
  //   Outport: '<Root>/GearPos'
  Engine_ECUMDLOBJ2.init();
  // InitializeConditions for root-level periodic continuous states
  {
    int_T rootPeriodicContStateIndices[1] = {14};
    real_T rootPeriodicContStateRanges[2] = {0.0, 720.0};
    (void)std::memcpy((void *)cnhtc_pre_a_vehicle_model_PeriodicIndX,  // NOLINT
                      rootPeriodicContStateIndices, 1 * sizeof(int_T));
    (void)std::memcpy((void *)cnhtc_pre_a_vehicle_model_PeriodicRngX,  // NOLINT
                      rootPeriodicContStateRanges, 2 * sizeof(real_T));
  }
  // set "at time zero" to false
  if (rtmIsFirstInitCond((&cnhtc_pre_a_vehicle_model_M))) {
    rtmSetFirstInitCond((&cnhtc_pre_a_vehicle_model_M), 0);
  }
}  // NOLINT
// Model terminate function
void CNHTC_VEHICLE_MODEL_codeModelClass::terminate() {
  // (no terminate code required)
}
// Constructor
CNHTC_VEHICLE_MODEL_codeModelClass::CNHTC_VEHICLE_MODEL_codeModelClass()
    : cnhtc_pre_a_vehicle_model_M() {
  // Currently there is no constructor body generated.
}
// Destructor
CNHTC_VEHICLE_MODEL_codeModelClass::~CNHTC_VEHICLE_MODEL_codeModelClass() {
  // Currently there is no destructor body generated.
}
// Real-Time Model get method
RT_MODEL_cnhtc_pre_a_vehicle_model_T *
CNHTC_VEHICLE_MODEL_codeModelClass::getRTM() {
  return (&cnhtc_pre_a_vehicle_model_M);
}
//

// File trailer for generated code.
//
// [EOF]
//
