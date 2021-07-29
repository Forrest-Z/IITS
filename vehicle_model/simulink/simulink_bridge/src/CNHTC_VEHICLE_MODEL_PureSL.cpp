//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: CNHTC_VEHICLE_MODEL_PureSL.cpp
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

#include <iostream>

#include "CNHTC_VEHICLE_MODEL_PureSL.h"
#include "CNHTC_VEHICLE_MODEL_PureSL_private.h"
#include "automldiffopen_m841FDlI.h"
#include "look1_binlcpw.h"
#include "look1_binlxpw.h"
#include "look2_binlcpw.h"
#include "rt_powd_snf.h"

// Exported block signals
real_T pedalPos_pct;                   // '<Root>/pedalPos_pct'
real_T XBR1_ExternalAccele;            // '<Root>/XBR1_ExternalAccele'
real_T SteerWhAngle_rad;               // '<Root>/SteerWhAngle_rad'
real_T Grade_deg;                      // '<Root>/Grade_deg'
real_T XBR1_Ctrl_Mode;                 // '<Root>/XBR1_Ctrl_Mode'

real_T throttle_pct;                   // '<S1>/Gain'
real_T Velong_kph;                     // '<Root>/Gain3'
real_T Yaw_deg;                        // '<S126>/Gain'
real_T YawRate_dps;                    // '<S126>/Gain2'
real_T Velate_kph;                     // '<Root>/Gain1'

real_T ax_mps2;                        // '<S2>/Divide'
real_T Vx_kph;                         // '<Root>/Gain2'

real_T Vy_kph;                         // '<Root>/Gain4'
real_T X;                              // '<Root>/Integrator'
real_T Y;                              // '<Root>/Integrator1'


// State reduction function
void local_stateReduction(real_T* x, int_T* p, int_T n, real_T* r)
{
  int_T i, j;
  for (i = 0, j = 0; i < n; ++i, ++j) {
    int_T k = p[i];
    real_T lb = r[j++];
    real_T xk = x[k]-lb;
    real_T rk = r[j]-lb;
    int_T q = (int_T) std::floor(xk/rk);
    if (q) {
      x[k] = xk-q*rk+lb;
    }
  }
}

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
void CNHTC_VEHICLE_MODEL_PureSLModelClass::rt_ertODEUpdateContinuousStates
  (RTWSolverInfo *si )
{
  // Solver Matrices
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

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
  int_T nXc = 21;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  // Save the state values at time t in y, we'll use x as ynew.
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  CNHTC_VEHICLE_MODEL_PureSL_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  CNHTC_VEHICLE_MODEL_PureSL_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  CNHTC_VEHICLE_MODEL_PureSL_derivatives();

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  local_stateReduction(x, rtsiGetPeriodicContStateIndices(si), 1,
                       rtsiGetPeriodicContStateRanges(si));
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void CNHTC_VEHICLE_MODEL_PureSLModelClass::step()
{
  boolean_T zcEvent;
  ZCEventType zcEvent_0;
  uint32_T rowIdx;
  real_T unusedU1[3];
  int8_T rtPrevAction;
  int8_T rtAction;
  int32_T i;
  boolean_T tmp[3];
  real_T u0;
  real_T u1;
  real_T u2;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                          (((&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.clockTick0+1)*
      (&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    (&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.t[0] = rtsiGetT
      (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo);
  }

  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Outport: '<Root>/GearPos' incorporates:
    //   UnitDelay: '<S3>/Unit Delay1'

    CNHTC_VEHICLE_MODEL_PureSL_Y.GearPos =
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay1_DSTATE;

    // Gain: '<S1>/Gain1' incorporates:
    //   Inport: '<Root>/XBR1_Ctrl_Mode'

    u0 = std::floor(CNHTC_VEHICLE_MODEL_PureSL_P.Gain1_Gain_p * XBR1_Ctrl_Mode);
    if (rtIsNaN(u0) || rtIsInf(u0)) {
      u0 = 0.0;
    } else {
      u0 = std::fmod(u0, 256.0);
    }

    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_h = static_cast<int8_T>((u0 < 0.0 ?
      static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
      (static_cast<uint8_T>(-u0)))) : static_cast<int32_T>(static_cast<int8_T>(
      static_cast<uint8_T>(u0)))));

    // End of Gain: '<S1>/Gain1'

    // Outport: '<Root>/foundation_brake_in_use' incorporates:
    //   DataTypeConversion: '<S1>/Data Type Conversion'

    CNHTC_VEHICLE_MODEL_PureSL_Y.foundation_brake_in_use =
      (CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_h != 0);

    // Gain: '<S1>/Gain' incorporates:
    //   Inport: '<Root>/pedalPos_pct'

    throttle_pct = CNHTC_VEHICLE_MODEL_PureSL_P.Gain_Gain_b * pedalPos_pct;

    // UnitDelay: '<S3>/Unit Delay3'
    CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm =
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay3_DSTATE;
  }

  // Integrator: '<S5>/Integrator1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1 =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE;

  // Lookup_n-D: '<S112>/EngTrq Table'
  CNHTC_VEHICLE_MODEL_PureSL_B.EngTrq = look2_binlcpw
    (CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1,
     CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm,
     CNHTC_VEHICLE_MODEL_PureSL_P.MappedCIEngine_f_tbrake_t_bpt,
     CNHTC_VEHICLE_MODEL_PureSL_P.MappedCIEngine_f_tbrake_n_bpt,
     CNHTC_VEHICLE_MODEL_PureSL_P.MappedCIEngine_f_tbrake,
     CNHTC_VEHICLE_MODEL_PureSL_P.EngTrqTable_maxIndex, 20U);

  // Saturate: '<S3>/Saturation'
  u0 = CNHTC_VEHICLE_MODEL_PureSL_B.EngTrq;
  u1 = CNHTC_VEHICLE_MODEL_PureSL_P.Saturation_LowerSat;
  u2 = CNHTC_VEHICLE_MODEL_PureSL_P.Saturation_UpperSat;
  if (u0 > u2) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation = u2;
  } else if (u0 < u1) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation = u1;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation = u0;
  }

  // End of Saturate: '<S3>/Saturation'

  // Outport: '<Root>/EngTrq_Nm'
  CNHTC_VEHICLE_MODEL_PureSL_Y.EngTrq_Nm =
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Outport: '<Root>/EngSpd_rpm' incorporates:
    //   UnitDelay: '<S3>/Unit Delay4'

    CNHTC_VEHICLE_MODEL_PureSL_Y.EngSpd_rpm =
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay4_DSTATE;

    // UnitDelay: '<S3>/Unit Delay2'
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay2 =
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay2_DSTATE;

    // Outport: '<Root>/shift_in_process' incorporates:
    //   Logic: '<S3>/NOT'

    CNHTC_VEHICLE_MODEL_PureSL_Y.shift_in_process =
      !CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay2;
  }

  // Sum: '<S3>/Add'
  CNHTC_VEHICLE_MODEL_PureSL_B.Add = CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1 -
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation;

  // Abs: '<S3>/Abs'
  CNHTC_VEHICLE_MODEL_PureSL_B.Abs = std::abs(CNHTC_VEHICLE_MODEL_PureSL_B.Add);

  // Sum: '<S3>/Add1' incorporates:
  //   Constant: '<S3>/Constant1'

  CNHTC_VEHICLE_MODEL_PureSL_B.Add1 = CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1 +
    CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value_i;

  // Product: '<S3>/Divide'
  CNHTC_VEHICLE_MODEL_PureSL_B.Divide = CNHTC_VEHICLE_MODEL_PureSL_B.Abs /
    CNHTC_VEHICLE_MODEL_PureSL_B.Add1;

  // Outport: '<Root>/engine_torque_loss_percent'
  CNHTC_VEHICLE_MODEL_PureSL_Y.engine_torque_loss_percent =
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide;

  // Abs: '<S3>/Abs1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Abs1 = std::abs
    (CNHTC_VEHICLE_MODEL_PureSL_B.Saturation);

  // Product: '<S3>/Divide1' incorporates:
  //   Constant: '<S3>/Constant2'

  CNHTC_VEHICLE_MODEL_PureSL_B.Divide1 = CNHTC_VEHICLE_MODEL_PureSL_B.Abs1 /
    rtP_Chas.EngReferTor_Nm;

  // Outport: '<Root>/engine_torque_percent'
  CNHTC_VEHICLE_MODEL_PureSL_Y.engine_torque_percent =
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide1;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Constant: '<S2>/Constant1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Constant1 = rtP_VEH.InitialLongVel;
  }

  // Integrator: '<S2>/Integrator'
  if (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK != 0) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE =
      CNHTC_VEHICLE_MODEL_PureSL_B.Constant1;
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE;

  // End of Integrator: '<S2>/Integrator'

  // SignalConversion: '<S126>/Signal Conversion'
  CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps =
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator;

  // Gain: '<Root>/Gain3'
  Velong_kph = CNHTC_VEHICLE_MODEL_PureSL_P.Gain3_Gain *
    CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps;

  // Outport: '<Root>/Velong_kph'
  CNHTC_VEHICLE_MODEL_PureSL_Y.Velong_kph_p = Velong_kph;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Constant: '<S2>/Constant4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Constant4 = rtP_VEH.InitialYawAngle;
  }

  // Integrator: '<S2>/Integrator1'
  if (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK != 0) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_h =
      CNHTC_VEHICLE_MODEL_PureSL_B.Constant4;
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_f =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_h;

  // End of Integrator: '<S2>/Integrator1'

  // Gain: '<S126>/Gain'
  Yaw_deg = CNHTC_VEHICLE_MODEL_PureSL_P.Gain_Gain_m *
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_f;

  // Outport: '<Root>/Yaw_deg'
  CNHTC_VEHICLE_MODEL_PureSL_Y.Yaw_deg_n = Yaw_deg;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // ModelReference: '<S1>/SteerWhlMdl' incorporates:
    //   Inport: '<Root>/SteerWhAngle_rad'

    SteerWhlMdlMDLOBJ4.step(&SteerWhAngle_rad,
      &CNHTC_VEHICLE_MODEL_PureSL_B.SteerWhAngle_DZ_deg);

    // Gain: '<S2>/Gain1'
    CNHTC_VEHICLE_MODEL_PureSL_B.WhlAngF_deg =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain1_Gain_b *
      CNHTC_VEHICLE_MODEL_PureSL_B.SteerWhAngle_DZ_deg;

    // Gain: '<S2>/Gain'
    CNHTC_VEHICLE_MODEL_PureSL_B.WhlAngF_rad =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain_Gain_f *
      CNHTC_VEHICLE_MODEL_PureSL_B.WhlAngF_deg;
  }

  // Outputs for Atomic SubSystem: '<S125>/TwoDofDynamic'
  // Constant: '<S2>/Constant3'
  CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic
    (CNHTC_VEHICLE_MODEL_PureSL_B.WhlAngF_rad,
     CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps, rtP_VEH.Mass,
     &CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_c,
     &CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_f,
     &CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic,
     &CNHTC_VEHICLE_MODEL_PureSL_DW.TwoDofDynamic,
     &CNHTC_VEHICLE_MODEL_PureSL_P.TwoDofDynamic);

  // End of Outputs for SubSystem: '<S125>/TwoDofDynamic'

  // Gain: '<S126>/Gain1'
  u0 = 1.0 / rtP_Chas.Rt;
  CNHTC_VEHICLE_MODEL_PureSL_B.Omega_w_rads = u0 *
    CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps;

  // Outport: '<Root>/Omega_w_rads'
  CNHTC_VEHICLE_MODEL_PureSL_Y.Omega_w_rads =
    CNHTC_VEHICLE_MODEL_PureSL_B.Omega_w_rads;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Gain: '<S126>/Gain2'
    YawRate_dps = CNHTC_VEHICLE_MODEL_PureSL_P.Gain2_Gain_h *
      CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_c;
  }

  // RelationalOperator: '<S135>/Compare' incorporates:
  //   Constant: '<S135>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.Compare =
    (CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps <=
     CNHTC_VEHICLE_MODEL_PureSL_P.CompareToConstant_const);
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Gain: '<Root>/Gain1'
    Velate_kph = CNHTC_VEHICLE_MODEL_PureSL_P.Gain1_Gain_g *
      CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_f;

    // UnitDelay: '<S2>/Unit Delay'
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay =
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay_DSTATE;

    // Product: '<S129>/Divide1' incorporates:
    //   Constant: '<S129>/Constant'
    //   Constant: '<S129>/Constant3'

    CNHTC_VEHICLE_MODEL_PureSL_B.Divide1_l =
      CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay * rtP_Chas.Iw_kgm2 / rtP_Chas.Rt;

    // Gain: '<S129>/Gain2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2 =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain2_Gain_g *
      CNHTC_VEHICLE_MODEL_PureSL_B.Divide1_l;

    // Gain: '<S129>/Gain'
    u0 = 1.0 / rtP_Chas.Rt;
    CNHTC_VEHICLE_MODEL_PureSL_B.FxfDr = u0 * CNHTC_VEHICLE_MODEL_PureSL_B.Gain2;

    // UnitDelay: '<Root>/Unit Delay1'
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay1_g =
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay1_DSTATE_h;

    // ModelReference: '<S1>/Brake_System' incorporates:
    //   Constant: '<S1>/Constant'
    //   Inport: '<Root>/XBR1_Ctrl_Mode'
    //   Inport: '<Root>/XBR1_ExternalAccele'

    Brake_SystemMDLOBJ1.step(&XBR1_ExternalAccele,
      &CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay1_g, &XBR1_Ctrl_Mode, &rtP_VEH.Mass,
      &CNHTC_VEHICLE_MODEL_PureSL_B.bwdWhlPre_Mpa[0],
      &CNHTC_VEHICLE_MODEL_PureSL_B.fwdWhlPre_Mpa[0],
      &CNHTC_VEHICLE_MODEL_PureSL_B.TrailWhlPre_Mpa[0]);

    // Fcn: '<S128>/Fcn'
    CNHTC_VEHICLE_MODEL_PureSL_B.BraF =
      ((CNHTC_VEHICLE_MODEL_PureSL_B.bwdWhlPre_Mpa[0] * 2.0 +
        CNHTC_VEHICLE_MODEL_PureSL_B.bwdWhlPre_Mpa[1] * 2.0) +
       CNHTC_VEHICLE_MODEL_PureSL_B.bwdWhlPre_Mpa[2] * 6.0) * 26750.0;

    // Gain: '<S128>/Gain'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain = CNHTC_VEHICLE_MODEL_PureSL_P.Gain_Gain_h
      * CNHTC_VEHICLE_MODEL_PureSL_B.BraF;
  }

  // Switch: '<S128>/Switch' incorporates:
  //   Constant: '<S128>/Constant'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.Compare) {
    CNHTC_VEHICLE_MODEL_PureSL_B.BraF_g =
      CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_i;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.BraF_g = CNHTC_VEHICLE_MODEL_PureSL_B.Gain;
  }

  // End of Switch: '<S128>/Switch'

  // Sum: '<S129>/Add'
  CNHTC_VEHICLE_MODEL_PureSL_B.Fxf_N = CNHTC_VEHICLE_MODEL_PureSL_B.FxfDr +
    CNHTC_VEHICLE_MODEL_PureSL_B.BraF_g;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Lookup_n-D: '<S3>/1-D Lookup Table' incorporates:
    //   Outport: '<Root>/GearPos'

    CNHTC_VEHICLE_MODEL_PureSL_B.uDLookupTable = look1_binlxpw
      (CNHTC_VEHICLE_MODEL_PureSL_Y.GearPos, rtP_Chas.GbRatioBp,
       rtP_Chas.GbRatioTable, 12U);

    // Gain: '<S127>/Gain3' incorporates:
    //   Constant: '<S127>/Mass_kg2'

    CNHTC_VEHICLE_MODEL_PureSL_B.Gain3 =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain3_Gain_m * rtP_VEH.Mass;
  }

  // Product: '<S3>/Product1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product1 =
    CNHTC_VEHICLE_MODEL_PureSL_B.uDLookupTable *
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation;

  // Product: '<S2>/Product' incorporates:
  //   Constant: '<S2>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.Tw_Nm = CNHTC_VEHICLE_MODEL_PureSL_B.Product1 *
    rtP_Chas.DifRatio;

  // Sum: '<S129>/Add2'
  CNHTC_VEHICLE_MODEL_PureSL_B.Add2 = CNHTC_VEHICLE_MODEL_PureSL_B.Tw_Nm -
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide1_l;

  // Gain: '<S129>/Gain1'
  u0 = 1.0 / rtP_Chas.Rt;
  CNHTC_VEHICLE_MODEL_PureSL_B.Fxr = u0 * CNHTC_VEHICLE_MODEL_PureSL_B.Add2;

  // Sum: '<S129>/Add1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Fxr_N = CNHTC_VEHICLE_MODEL_PureSL_B.Fxr +
    CNHTC_VEHICLE_MODEL_PureSL_B.BraF_g;

  // RelationalOperator: '<S134>/Compare' incorporates:
  //   Constant: '<S134>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.Compare_g =
    (CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps <
     CNHTC_VEHICLE_MODEL_PureSL_P.CompareToConstant_const_k);

  // Switch: '<S127>/Switch' incorporates:
  //   Constant: '<S127>/Constant3'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.Compare_g) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Fextx =
      CNHTC_VEHICLE_MODEL_PureSL_P.Constant3_Value;
  } else {
    // Gain: '<S127>/Gain1' incorporates:
    //   Inport: '<Root>/Grade_deg'

    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_p =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain1_Gain * Grade_deg;

    // Trigonometry: '<S127>/Sin'
    CNHTC_VEHICLE_MODEL_PureSL_B.Sin_e = std::sin
      (CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_p);

    // Product: '<S127>/Product'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_k = CNHTC_VEHICLE_MODEL_PureSL_B.Gain3 *
      CNHTC_VEHICLE_MODEL_PureSL_B.Sin_e;

    // Gain: '<S127>/Gain2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_cz =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain2_Gain *
      CNHTC_VEHICLE_MODEL_PureSL_B.Product_k;

    // Trigonometry: '<S127>/Sin1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Sin1 = std::cos
      (CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_p);

    // Product: '<S127>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_e = CNHTC_VEHICLE_MODEL_PureSL_B.Sin1 *
      CNHTC_VEHICLE_MODEL_PureSL_B.Gain3;

    // Gain: '<S127>/Gain5'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain5 = CNHTC_VEHICLE_MODEL_PureSL_P.Gain5_Gain
      * CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps;

    // Gain: '<S127>/Gain4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain4 = rtP_Chas.mu_Dyn *
      CNHTC_VEHICLE_MODEL_PureSL_B.Gain5;

    // Sum: '<S127>/Sum1' incorporates:
    //   Constant: '<S127>/Constant2'

    CNHTC_VEHICLE_MODEL_PureSL_B.mu_total = rtP_Chas.mu_Sta +
      CNHTC_VEHICLE_MODEL_PureSL_B.Gain4;

    // Product: '<S127>/Product3'
    CNHTC_VEHICLE_MODEL_PureSL_B.Rx = CNHTC_VEHICLE_MODEL_PureSL_B.mu_total *
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_e;

    // Gain: '<S127>/Gain'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain_e =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain_Gain_g * CNHTC_VEHICLE_MODEL_PureSL_B.Rx;

    // Sum: '<S127>/Add'
    CNHTC_VEHICLE_MODEL_PureSL_B.Add_j = CNHTC_VEHICLE_MODEL_PureSL_B.Gain_e +
      CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_cz;
    CNHTC_VEHICLE_MODEL_PureSL_B.Fextx = CNHTC_VEHICLE_MODEL_PureSL_B.Add_j;
  }

  // End of Switch: '<S127>/Switch'

  // Sum: '<S127>/Add1' incorporates:
  //   Constant: '<S127>/Constant'
  //   Constant: '<S127>/Constant1'

  CNHTC_VEHICLE_MODEL_PureSL_B.Add1_h = (CNHTC_VEHICLE_MODEL_PureSL_B.Fextx +
    CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_pr) +
    CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value_h;

  // Sum: '<S2>/Add'
  CNHTC_VEHICLE_MODEL_PureSL_B.Add_c = (CNHTC_VEHICLE_MODEL_PureSL_B.Fxf_N +
    CNHTC_VEHICLE_MODEL_PureSL_B.Fxr_N) + CNHTC_VEHICLE_MODEL_PureSL_B.Add1_h;

  // Product: '<S2>/Divide' incorporates:
  //   Constant: '<S2>/Constant2'

  ax_mps2 = CNHTC_VEHICLE_MODEL_PureSL_B.Add_c / rtP_VEH.Mass;

  // Outport: '<Root>/ax_mps2'
  CNHTC_VEHICLE_MODEL_PureSL_Y.ax_mps2_f = ax_mps2;

  // Gain: '<Root>/Gain'
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain_g =
    CNHTC_VEHICLE_MODEL_PureSL_P.Gain_Gain_h3 * Yaw_deg;

  // Trigonometry: '<Root>/Cos'
  CNHTC_VEHICLE_MODEL_PureSL_B.Cos = std::cos
    (CNHTC_VEHICLE_MODEL_PureSL_B.Gain_g);

  // Product: '<Root>/Product'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product = CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps
    * CNHTC_VEHICLE_MODEL_PureSL_B.Cos;

  // Gain: '<Root>/Gain2'
  Vx_kph = CNHTC_VEHICLE_MODEL_PureSL_P.Gain2_Gain_n *
    CNHTC_VEHICLE_MODEL_PureSL_B.Product;

  // Outport: '<Root>/Vx_kph'
  CNHTC_VEHICLE_MODEL_PureSL_Y.Vx_kph_e = Vx_kph;

  // Trigonometry: '<Root>/Sin'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sin = std::sin
    (CNHTC_VEHICLE_MODEL_PureSL_B.Gain_g);

  // Product: '<Root>/Product1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product1_f =
    CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps * CNHTC_VEHICLE_MODEL_PureSL_B.Sin;

  // Gain: '<Root>/Gain4'
  Vy_kph = CNHTC_VEHICLE_MODEL_PureSL_P.Gain4_Gain *
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_f;

  // Outport: '<Root>/Vy_kph'
  CNHTC_VEHICLE_MODEL_PureSL_Y.Vy_kph_a = Vy_kph;

  // Integrator: '<Root>/Integrator'
  X = CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_l;

  // Outport: '<Root>/X'
  CNHTC_VEHICLE_MODEL_PureSL_Y.X_p = X;

  // Integrator: '<Root>/Integrator1'
  Y = CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_o;

  // Outport: '<Root>/Y'
  CNHTC_VEHICLE_MODEL_PureSL_Y.Y_h = Y;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Memory: '<S47>/Memory'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory_n =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_j;

    // Memory: '<S118>/Memory'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput;

    // Constant: '<S117>/domega_o'
    CNHTC_VEHICLE_MODEL_PureSL_B.domega_o =
      CNHTC_VEHICLE_MODEL_PureSL_P.PropShaft_domega_o;
  }

  // Integrator: '<S118>/Integrator'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    zcEvent_0 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator_Reset_ZCE,
                         (CNHTC_VEHICLE_MODEL_PureSL_B.Memory));
    zcEvent = (zcEvent_0 != NO_ZCEVENT);

    // evaluate zero-crossings
    if (zcEvent || (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_j != 0)) {
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_m =
        CNHTC_VEHICLE_MODEL_PureSL_B.domega_o;
    }
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_k =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_m;

  // End of Integrator: '<S118>/Integrator'

  // Gain: '<S117>/Gain2'
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_c =
    CNHTC_VEHICLE_MODEL_PureSL_P.PropShaft_b *
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_k;

  // Integrator: '<S117>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_n =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_d;

  // Gain: '<S117>/Gain1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain1 = CNHTC_VEHICLE_MODEL_PureSL_P.PropShaft_k *
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_n;

  // Sum: '<S117>/Subtract1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1 = CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_c
    + CNHTC_VEHICLE_MODEL_PureSL_B.Gain1;

  // UnaryMinus: '<S117>/Unary Minus'
  CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus =
    -CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1;

  // Integrator: '<S31>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_i =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_df;

  // Gain: '<S13>/ClutchGain'
  CNHTC_VEHICLE_MODEL_PureSL_B.ClutchGain =
    CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_K_c *
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_i;

  // Saturate: '<S32>/Saturation'
  u0 = CNHTC_VEHICLE_MODEL_PureSL_B.ClutchGain;
  u1 = CNHTC_VEHICLE_MODEL_PureSL_P.Saturation_LowerSat_p;
  u2 = CNHTC_VEHICLE_MODEL_PureSL_P.Saturation_UpperSat_p;
  if (u0 > u2) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation_o = u2;
  } else if (u0 < u1) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation_o = u1;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation_o = u0;
  }

  // End of Saturate: '<S32>/Saturation'

  // Gain: '<S32>/Torque Conversion'
  u0 = CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_R *
    CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_muk;
  CNHTC_VEHICLE_MODEL_PureSL_B.TorqueConversion = u0 *
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation_o;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // UnitDelay: '<Root>/Unit Delay'
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_h =
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay_DSTATE_i;

    // ModelReference: '<S3>/TCU' incorporates:
    //   Inport: '<Root>/pedalPos_pct'

    TCUMDLOBJ3.step(&pedalPos_pct, &CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_h,
                    &CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm,
                    &CNHTC_VEHICLE_MODEL_PureSL_B.GearSel);

    // Memory: '<S35>/Memory3'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory3 =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory3_PreviousInput;

    // Memory: '<S35>/Memory'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory_h =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_a;

    // Sum: '<S35>/Add2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Add2_m = CNHTC_VEHICLE_MODEL_PureSL_B.Memory3 -
      CNHTC_VEHICLE_MODEL_PureSL_B.Memory_h;

    // RelationalOperator: '<S37>/Compare' incorporates:
    //   Constant: '<S37>/Constant'

    CNHTC_VEHICLE_MODEL_PureSL_B.Compare_e =
      (CNHTC_VEHICLE_MODEL_PureSL_B.Add2_m !=
       CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_p);

    // Memory: '<S35>/Memory1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory1 =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput;

    // Switch: '<S35>/Switch1'
    if (CNHTC_VEHICLE_MODEL_PureSL_B.Compare_e) {
      CNHTC_VEHICLE_MODEL_PureSL_B.CmdGear =
        CNHTC_VEHICLE_MODEL_PureSL_B.GearSel;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.CmdGear =
        CNHTC_VEHICLE_MODEL_PureSL_B.Memory1;
    }

    // End of Switch: '<S35>/Switch1'

    // Constant: '<S38>/Constant'
    CNHTC_VEHICLE_MODEL_PureSL_B.Constant =
      CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_kv;
  }

  // Integrator: '<S38>/Integrator1'
  // Limited  Integrator  (w/ Saturation Port)
  if (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK_a != 0) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.Constant;
  }

  if (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d >=
      CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_UpperSat) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d =
      CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_UpperSat;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2 = 1.0;
  } else if (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d <=
             CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_LowerSat) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d =
      CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_LowerSat;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2 = -1.0;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2 = 0.0;
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o1 =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d;

  // End of Integrator: '<S38>/Integrator1'

  // RelationalOperator: '<S41>/Compare' incorporates:
  //   Constant: '<S41>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.Compare_gz =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2 !=
     CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_dg);
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Memory: '<S40>/Memory2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory2_c =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory2_PreviousInput_d;
  }

  // Logic: '<S39>/Logical Operator3'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator3 =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Compare_gz &&
     CNHTC_VEHICLE_MODEL_PureSL_B.Memory2_c);

  // Switch: '<S35>/Switch2'
  if (CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator3) {
    CNHTC_VEHICLE_MODEL_PureSL_B.NewGear = CNHTC_VEHICLE_MODEL_PureSL_B.CmdGear;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.NewGear = CNHTC_VEHICLE_MODEL_PureSL_B.Memory3;
  }

  // End of Switch: '<S35>/Switch2'

  // Lookup_n-D: '<S15>/Gear2damping'
  CNHTC_VEHICLE_MODEL_PureSL_B.b = look1_binlxpw
    (CNHTC_VEHICLE_MODEL_PureSL_B.NewGear, rtP_Chas.GbRatioBp,
     rtP_Chas.DampingCoeffs, 12U);

  // Lookup_n-D: '<S15>/Gear2inertias'
  CNHTC_VEHICLE_MODEL_PureSL_B.J = look1_binlxpw
    (CNHTC_VEHICLE_MODEL_PureSL_B.NewGear, rtP_Chas.GbRatioBp,
     CNHTC_VEHICLE_MODEL_PureSL_P.Gear2inertias_tableData, 12U);

  // Lookup_n-D: '<S15>/Gear2Ratios'
  CNHTC_VEHICLE_MODEL_PureSL_B.N = look1_binlxpw
    (CNHTC_VEHICLE_MODEL_PureSL_B.NewGear, rtP_Chas.GbRatioBp,
     rtP_Chas.GbRatioTable, 12U);
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // InitialCondition: '<S17>/IC' incorporates:
    //   Constant: '<S17>/Constant1'

    if (CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime) {
      CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime = false;
      CNHTC_VEHICLE_MODEL_PureSL_B.IC = CNHTC_VEHICLE_MODEL_PureSL_P.IC_Value;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.IC =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value_k;
    }

    // End of InitialCondition: '<S17>/IC'

    // InitialCondition: '<S18>/IC' incorporates:
    //   Constant: '<S18>/Constant1'

    if (CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_p) {
      CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_p = false;
      CNHTC_VEHICLE_MODEL_PureSL_B.IC_c =
        CNHTC_VEHICLE_MODEL_PureSL_P.IC_Value_m;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.IC_c =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value_l;
    }

    // End of InitialCondition: '<S18>/IC'
  }

  // Switch: '<S17>/Switch' incorporates:
  //   Constant: '<S17>/Constant'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.IC >
      CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_f) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch =
      CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch =
      CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_omegain_o;
  }

  // End of Switch: '<S17>/Switch'

  // Switch: '<S18>/Switch' incorporates:
  //   Constant: '<S18>/Constant'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.IC_c >
      CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_fk) {
    // Product: '<S10>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_c =
      CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE /
      CNHTC_VEHICLE_MODEL_PureSL_B.N;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_f =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product1_c;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_f =
      CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_omegaout_o;
  }

  // End of Switch: '<S18>/Switch'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // InitialCondition: '<S16>/IC' incorporates:
    //   Constant: '<S16>/Constant1'

    if (CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_c) {
      CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_c = false;
      CNHTC_VEHICLE_MODEL_PureSL_B.IC_i =
        CNHTC_VEHICLE_MODEL_PureSL_P.IC_Value_mc;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.IC_i =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value_lc;
    }

    // End of InitialCondition: '<S16>/IC'
  }

  // Switch: '<S16>/Switch' incorporates:
  //   Constant: '<S16>/Constant'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.IC_i >
      CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_n) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_i =
      CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_i =
      CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_omegain_o;
  }

  // End of Switch: '<S16>/Switch'

  // If: '<S10>/If'
  rtPrevAction = CNHTC_VEHICLE_MODEL_PureSL_DW.If_ActiveSubsystem;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    rtAction = static_cast<int8_T>(!CNHTC_VEHICLE_MODEL_PureSL_B.Memory_n);
    CNHTC_VEHICLE_MODEL_PureSL_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = CNHTC_VEHICLE_MODEL_PureSL_DW.If_ActiveSubsystem;
  }

  switch (rtAction) {
   case 0:
    if (rtAction != rtPrevAction) {
      // InitializeConditions for IfAction SubSystem: '<S10>/Locked' incorporates:
      //   ActionPort: '<S12>/Action'

      // InitializeConditions for If: '<S10>/If' incorporates:
      //   Integrator: '<S12>/Locked Shaft Integrator'

      if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
        CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE = 0.0;
      }

      CNHTC_VEHICLE_MODEL_PureSL_DW.LockedShaftIntegrator_IWORK = 1;

      // End of InitializeConditions for SubSystem: '<S10>/Locked'
    }

    // Outputs for IfAction SubSystem: '<S10>/Locked' incorporates:
    //   ActionPort: '<S12>/Action'

    // Lookup_n-D: '<S30>/Eta 1D'
    CNHTC_VEHICLE_MODEL_PureSL_B.Eta1D_p = look1_binlcpw
      (CNHTC_VEHICLE_MODEL_PureSL_B.NewGear, rtP_Chas.GbRatioBp,
       rtP_Chas.GearEta, 12U);

    // Abs: '<S12>/Abs'
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_ck = std::abs
      (CNHTC_VEHICLE_MODEL_PureSL_B.N);

    // Integrator: '<S12>/Locked Shaft Integrator'
    // Limited  Integrator
    if (CNHTC_VEHICLE_MODEL_PureSL_DW.LockedShaftIntegrator_IWORK != 0) {
      CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE =
        CNHTC_VEHICLE_MODEL_PureSL_B.Switch_i;
      rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
        (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
    }

    if (CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE >=
        CNHTC_VEHICLE_MODEL_PureSL_P.LockedShaftIntegrator_UpperSat) {
      if (CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE !=
          CNHTC_VEHICLE_MODEL_PureSL_P.LockedShaftIntegrator_UpperSat) {
        CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE =
          CNHTC_VEHICLE_MODEL_PureSL_P.LockedShaftIntegrator_UpperSat;
        rtsiSetBlockStateForSolverChangedAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
      }
    } else {
      if ((CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE <=
           CNHTC_VEHICLE_MODEL_PureSL_P.LockedShaftIntegrator_LowerSat) &&
          (CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE !=
           CNHTC_VEHICLE_MODEL_PureSL_P.LockedShaftIntegrator_LowerSat)) {
        CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE =
          CNHTC_VEHICLE_MODEL_PureSL_P.LockedShaftIntegrator_LowerSat;
        rtsiSetBlockStateForSolverChangedAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
      }
    }

    CNHTC_VEHICLE_MODEL_PureSL_B.omega =
      CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE;

    // End of Integrator: '<S12>/Locked Shaft Integrator'

    // Product: '<S28>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_o =
      CNHTC_VEHICLE_MODEL_PureSL_B.Saturation *
      CNHTC_VEHICLE_MODEL_PureSL_B.omega;

    // Switch: '<S28>/Switch' incorporates:
    //   Constant: '<S28>/Constant'

    if (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_o >
        CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_nc =
        CNHTC_VEHICLE_MODEL_PureSL_B.Eta1D_p;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_nc =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value;
    }

    // End of Switch: '<S28>/Switch'

    // Product: '<S28>/Product4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_n =
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_nc *
      CNHTC_VEHICLE_MODEL_PureSL_B.Saturation;

    // Sum: '<S28>/Subtract'
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_d1 =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product4_n -
      CNHTC_VEHICLE_MODEL_PureSL_B.Saturation;

    // Product: '<S28>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_f =
      CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_d1 *
      CNHTC_VEHICLE_MODEL_PureSL_B.omega;

    // Product: '<S12>/Product5'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product5 =
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus / CNHTC_VEHICLE_MODEL_PureSL_B.N;

    // Product: '<S29>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_gc =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product5 * CNHTC_VEHICLE_MODEL_PureSL_B.omega;

    // Switch: '<S29>/Switch' incorporates:
    //   Constant: '<S29>/Constant'

    if (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_gc >
        CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_l) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_j0 =
        CNHTC_VEHICLE_MODEL_PureSL_B.Eta1D_p;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_j0 =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_b;
    }

    // End of Switch: '<S29>/Switch'

    // Product: '<S29>/Product4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_nt =
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_j0 *
      CNHTC_VEHICLE_MODEL_PureSL_B.Product5;

    // Sum: '<S29>/Subtract'
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_a =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product4_nt -
      CNHTC_VEHICLE_MODEL_PureSL_B.Product5;

    // Product: '<S29>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_c2 =
      CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_a *
      CNHTC_VEHICLE_MODEL_PureSL_B.omega;

    // Sum: '<S12>/Add'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss_i =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_f +
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_c2;

    // Product: '<S12>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_f3 = 1.0 /
      CNHTC_VEHICLE_MODEL_PureSL_B.Abs_ck / CNHTC_VEHICLE_MODEL_PureSL_B.Abs_ck *
      CNHTC_VEHICLE_MODEL_PureSL_B.b;

    // Product: '<S12>/Product6'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product6 =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product1_f3 *
      CNHTC_VEHICLE_MODEL_PureSL_B.omega;

    // Gain: '<S12>/input clutch Damping'
    CNHTC_VEHICLE_MODEL_PureSL_B.inputclutchDamping =
      CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_bin *
      CNHTC_VEHICLE_MODEL_PureSL_B.omega;

    // Sum: '<S12>/Add1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Add1_f = CNHTC_VEHICLE_MODEL_PureSL_B.Product6
      + CNHTC_VEHICLE_MODEL_PureSL_B.inputclutchDamping;

    // Sum: '<S12>/Add2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Add2_l =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product4_n +
      CNHTC_VEHICLE_MODEL_PureSL_B.Product4_nt;

    // Product: '<S12>/Product3'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_mq = CNHTC_VEHICLE_MODEL_PureSL_B.J /
      CNHTC_VEHICLE_MODEL_PureSL_B.Abs_ck / CNHTC_VEHICLE_MODEL_PureSL_B.Abs_ck;

    // Sum: '<S12>/Add3' incorporates:
    //   Constant: '<S12>/Constant'

    u0 = rtP_Chas.Ie_kgm2 * 3.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add3_o = u0 +
      CNHTC_VEHICLE_MODEL_PureSL_B.Product3_mq;

    // Sum: '<S12>/Sum'
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_k0 = CNHTC_VEHICLE_MODEL_PureSL_B.Add2_l -
      CNHTC_VEHICLE_MODEL_PureSL_B.Add1_f;

    // Product: '<S12>/Product'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.Sum_k0 * CNHTC_VEHICLE_MODEL_PureSL_B.omega;

    // Product: '<S12>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_mi =
      CNHTC_VEHICLE_MODEL_PureSL_B.omega / CNHTC_VEHICLE_MODEL_PureSL_B.N;

    // UnaryMinus: '<S12>/Unary Minus'
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_b =
      -CNHTC_VEHICLE_MODEL_PureSL_B.Add1_f;

    // Product: '<S12>/Product7'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss_f =
      CNHTC_VEHICLE_MODEL_PureSL_B.omega *
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_b;

    // Product: '<S12>/Product8'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product8 = 1.0 /
      CNHTC_VEHICLE_MODEL_PureSL_B.Add3_o * CNHTC_VEHICLE_MODEL_PureSL_B.Sum_k0;

    // SignalConversion: '<S12>/Signal Conversion1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge2 = CNHTC_VEHICLE_MODEL_PureSL_B.N;

    // SignalConversion: '<S12>/Signal Conversion2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge3 = CNHTC_VEHICLE_MODEL_PureSL_B.omega;

    // SignalConversion: '<S12>/Signal Conversion3'
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_mi;

    // SignalConversion: '<S12>/Signal Conversion4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge1 =
      CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans_d;

    // SignalConversion generated from: '<S12>/Signal Conversion5'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans =
      CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans_d;

    // SignalConversion generated from: '<S12>/Signal Conversion5' incorporates:
    //   Constant: '<S12>/Constant1'

    CNHTC_VEHICLE_MODEL_PureSL_B.PwrCltchLoss =
      CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value;

    // SignalConversion generated from: '<S12>/Signal Conversion5'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss =
      CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss_f;

    // SignalConversion generated from: '<S12>/Signal Conversion5'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss =
      CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss_i;

    // End of Outputs for SubSystem: '<S10>/Locked'
    break;

   case 1:
    if (rtAction != rtPrevAction) {
      // InitializeConditions for IfAction SubSystem: '<S10>/Unlocked' incorporates:
      //   ActionPort: '<S14>/Action'

      // InitializeConditions for If: '<S10>/If' incorporates:
      //   Integrator: '<S14>/Integrator'
      //   Integrator: '<S14>/Pump Integrator'

      if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
        CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE = 0.0;
        CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg = 0.0;
      }

      CNHTC_VEHICLE_MODEL_PureSL_DW.PumpIntegrator_IWORK = 1;
      CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_p = 1;

      // End of InitializeConditions for SubSystem: '<S10>/Unlocked'
    }

    // Outputs for IfAction SubSystem: '<S10>/Unlocked' incorporates:
    //   ActionPort: '<S14>/Action'

    // Lookup_n-D: '<S57>/Eta 1D'
    CNHTC_VEHICLE_MODEL_PureSL_B.Eta1D = look1_binlcpw
      (CNHTC_VEHICLE_MODEL_PureSL_B.NewGear, rtP_Chas.GbRatioBp,
       rtP_Chas.GearEta, 12U);

    // Integrator: '<S14>/Pump Integrator'
    // Limited  Integrator
    if (CNHTC_VEHICLE_MODEL_PureSL_DW.PumpIntegrator_IWORK != 0) {
      CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE =
        CNHTC_VEHICLE_MODEL_PureSL_B.Switch;
      rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
        (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
    }

    if (CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE >=
        CNHTC_VEHICLE_MODEL_PureSL_P.PumpIntegrator_UpperSat) {
      if (CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE !=
          CNHTC_VEHICLE_MODEL_PureSL_P.PumpIntegrator_UpperSat) {
        CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE =
          CNHTC_VEHICLE_MODEL_PureSL_P.PumpIntegrator_UpperSat;
        rtsiSetBlockStateForSolverChangedAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
      }
    } else {
      if ((CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE <=
           CNHTC_VEHICLE_MODEL_PureSL_P.PumpIntegrator_LowerSat) &&
          (CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE !=
           CNHTC_VEHICLE_MODEL_PureSL_P.PumpIntegrator_LowerSat)) {
        CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE =
          CNHTC_VEHICLE_MODEL_PureSL_P.PumpIntegrator_LowerSat;
        rtsiSetBlockStateForSolverChangedAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
      }
    }

    CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator =
      CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE;

    // End of Integrator: '<S14>/Pump Integrator'

    // Product: '<S52>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_lu =
      CNHTC_VEHICLE_MODEL_PureSL_B.Saturation *
      CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator;

    // Switch: '<S52>/Switch' incorporates:
    //   Constant: '<S52>/Constant'

    if (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_lu >
        CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_h) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_g = CNHTC_VEHICLE_MODEL_PureSL_B.Eta1D;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_g =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_d;
    }

    // End of Switch: '<S52>/Switch'

    // Product: '<S52>/Product4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_g *
      CNHTC_VEHICLE_MODEL_PureSL_B.Saturation;

    // Sum: '<S52>/Subtract'
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product4_d -
      CNHTC_VEHICLE_MODEL_PureSL_B.Saturation;

    // Product: '<S52>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_c =
      CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_d *
      CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator;

    // Integrator: '<S14>/Integrator'
    // Limited  Integrator
    if (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_p != 0) {
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg =
        CNHTC_VEHICLE_MODEL_PureSL_B.Switch_f;
      rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
        (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
    }

    if (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg >=
        CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_UpperSat) {
      if (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg !=
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_UpperSat) {
        CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg =
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_UpperSat;
        rtsiSetBlockStateForSolverChangedAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
      }
    } else {
      if ((CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg <=
           CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_LowerSat) &&
          (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg !=
           CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_LowerSat)) {
        CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg =
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_LowerSat;
        rtsiSetBlockStateForSolverChangedAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, true);
      }
    }

    CNHTC_VEHICLE_MODEL_PureSL_B.w_out =
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg;

    // End of Integrator: '<S14>/Integrator'

    // Product: '<S53>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus *
      CNHTC_VEHICLE_MODEL_PureSL_B.w_out;

    // Switch: '<S53>/Switch' incorporates:
    //   Constant: '<S53>/Constant'

    if (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_d >
        CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_p) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_h = CNHTC_VEHICLE_MODEL_PureSL_B.Eta1D;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_h =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_n;
    }

    // End of Switch: '<S53>/Switch'

    // Product: '<S53>/Product4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_g =
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_h *
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus;

    // Sum: '<S53>/Subtract'
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_e =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product4_g -
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus;

    // Product: '<S53>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_mo =
      CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_e *
      CNHTC_VEHICLE_MODEL_PureSL_B.w_out;

    // Sum: '<S14>/Add'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss_p =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_c +
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_mo;

    // Product: '<S54>/Product4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_a = CNHTC_VEHICLE_MODEL_PureSL_B.w_out
      * CNHTC_VEHICLE_MODEL_PureSL_B.N;

    // Sum: '<S54>/Add2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Add2_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator -
      CNHTC_VEHICLE_MODEL_PureSL_B.Product4_a;

    // Gain: '<S54>/Gain'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain_n = CNHTC_VEHICLE_MODEL_PureSL_P.Gain_Gain
      * CNHTC_VEHICLE_MODEL_PureSL_B.Add2_d;

    // Trigonometry: '<S54>/Trigonometric Function'
    CNHTC_VEHICLE_MODEL_PureSL_B.TrigonometricFunction = std::tanh
      (CNHTC_VEHICLE_MODEL_PureSL_B.Gain_n);

    // Product: '<S54>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_ej =
      CNHTC_VEHICLE_MODEL_PureSL_B.TorqueConversion *
      CNHTC_VEHICLE_MODEL_PureSL_B.TrigonometricFunction;

    // Product: '<S54>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_pe =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_ej * CNHTC_VEHICLE_MODEL_PureSL_B.N;

    // Product: '<S55>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_j = CNHTC_VEHICLE_MODEL_PureSL_B.w_out
      * CNHTC_VEHICLE_MODEL_PureSL_B.b;

    // Sum: '<S55>/Add2'
    CNHTC_VEHICLE_MODEL_PureSL_B.T_ext = CNHTC_VEHICLE_MODEL_PureSL_B.Product4_g
      - CNHTC_VEHICLE_MODEL_PureSL_B.Product2_j;

    // Sum: '<S14>/Add1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Add1_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product1_pe +
      CNHTC_VEHICLE_MODEL_PureSL_B.T_ext;

    // Gain: '<S14>/Input Clutch Damping'
    CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchDamping_d =
      CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_bin *
      CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator;

    // Sum: '<S14>/Input Sum'
    CNHTC_VEHICLE_MODEL_PureSL_B.InputSum =
      (CNHTC_VEHICLE_MODEL_PureSL_B.Product4_d -
       CNHTC_VEHICLE_MODEL_PureSL_B.Product2_ej) -
      CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchDamping_d;

    // Product: '<S14>/Product2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_p =
      CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator *
      CNHTC_VEHICLE_MODEL_PureSL_B.InputSum;

    // Product: '<S14>/Product'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_ki = CNHTC_VEHICLE_MODEL_PureSL_B.w_out
      * CNHTC_VEHICLE_MODEL_PureSL_B.Add1_d;

    // Sum: '<S14>/Add2'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans_n =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_p +
      CNHTC_VEHICLE_MODEL_PureSL_B.Product_ki;

    // Product: '<S14>/Product10'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product10 =
      CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator *
      CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchDamping_d;

    // Product: '<S55>/Product'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_b =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_j *
      CNHTC_VEHICLE_MODEL_PureSL_B.w_out;

    // Sum: '<S14>/Add3'
    CNHTC_VEHICLE_MODEL_PureSL_B.Add3_c = CNHTC_VEHICLE_MODEL_PureSL_B.Product10
      + CNHTC_VEHICLE_MODEL_PureSL_B.Product_b;

    // Product: '<S54>/Product3'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_e =
      CNHTC_VEHICLE_MODEL_PureSL_B.Add2_d *
      CNHTC_VEHICLE_MODEL_PureSL_B.Product2_ej;

    // UnaryMinus: '<S54>/Unary Minus'
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_k =
      -CNHTC_VEHICLE_MODEL_PureSL_B.Product3_e;

    // Gain: '<S14>/Input Clutch Inertia'
    u0 = 1.0 / (rtP_Chas.Ie_kgm2 * 3.0);
    CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchInertia = u0 *
      CNHTC_VEHICLE_MODEL_PureSL_B.InputSum;

    // Product: '<S14>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_j2 =
      CNHTC_VEHICLE_MODEL_PureSL_B.Add1_d / CNHTC_VEHICLE_MODEL_PureSL_B.J;

    // RelationalOperator: '<S58>/Compare' incorporates:
    //   Constant: '<S58>/Constant'

    u0 = -CNHTC_VEHICLE_MODEL_PureSL_P.div0protectabspoly1_thresh;
    CNHTC_VEHICLE_MODEL_PureSL_B.Compare_h = (CNHTC_VEHICLE_MODEL_PureSL_B.w_out
      >= u0);

    // RelationalOperator: '<S59>/Compare' incorporates:
    //   Constant: '<S59>/Constant'

    CNHTC_VEHICLE_MODEL_PureSL_B.Compare_gp =
      (CNHTC_VEHICLE_MODEL_PureSL_B.w_out <=
       CNHTC_VEHICLE_MODEL_PureSL_P.div0protectabspoly1_thresh);

    // Logic: '<S56>/Logical Operator'
    CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator_k =
      (CNHTC_VEHICLE_MODEL_PureSL_B.Compare_h &&
       CNHTC_VEHICLE_MODEL_PureSL_B.Compare_gp);

    // Switch: '<S56>/Switch'
    if (CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator_k) {
      // Fcn: '<S56>/Fcn'
      u0 = CNHTC_VEHICLE_MODEL_PureSL_B.w_out / 1.0e-6;
      u0 = rt_powd_snf(u0, 2.0);
      CNHTC_VEHICLE_MODEL_PureSL_B.Fcn = 2.0E-6 / (3.0 - u0);
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_k = CNHTC_VEHICLE_MODEL_PureSL_B.Fcn;
    } else {
      // Abs: '<S56>/Abs'
      CNHTC_VEHICLE_MODEL_PureSL_B.Abs_js = std::abs
        (CNHTC_VEHICLE_MODEL_PureSL_B.w_out);
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_k =
        CNHTC_VEHICLE_MODEL_PureSL_B.Abs_js;
    }

    // End of Switch: '<S56>/Switch'

    // Product: '<S14>/Product3'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_m =
      CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator /
      CNHTC_VEHICLE_MODEL_PureSL_B.Switch_k;

    // SignalConversion: '<S14>/Signal Conversion1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge = CNHTC_VEHICLE_MODEL_PureSL_B.w_out;

    // SignalConversion: '<S14>/Signal Conversion2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge3 =
      CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator;

    // SignalConversion: '<S14>/Signal Conversion3'
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge2 =
      CNHTC_VEHICLE_MODEL_PureSL_B.Product3_m;

    // SignalConversion: '<S14>/Signal Conversion4'
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge1 =
      CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans_n;

    // SignalConversion generated from: '<S14>/Signal Conversion5'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans =
      CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans_n;

    // SignalConversion generated from: '<S14>/Signal Conversion5'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrCltchLoss =
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_k;

    // UnaryMinus: '<S14>/Unary Minus'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss_b =
      -CNHTC_VEHICLE_MODEL_PureSL_B.Add3_c;

    // SignalConversion generated from: '<S14>/Signal Conversion5'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss =
      CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss_b;

    // SignalConversion generated from: '<S14>/Signal Conversion5'
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss =
      CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss_p;

    // End of Outputs for SubSystem: '<S10>/Unlocked'
    break;
  }

  // End of If: '<S10>/If'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Product: '<S13>/Product' incorporates:
    //   Constant: '<S13>/Constant1'

    CNHTC_VEHICLE_MODEL_PureSL_B.Product_l = 1.0 /
      CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_tauc;

    // Gain: '<S13>/2*pi'
    CNHTC_VEHICLE_MODEL_PureSL_B.upi = CNHTC_VEHICLE_MODEL_PureSL_P.upi_Gain *
      CNHTC_VEHICLE_MODEL_PureSL_B.Product_l;
  }

  // Switch: '<S13>/Switch' incorporates:
  //   Constant: '<S13>/Constant'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.NewGear != 0.0) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_i0 =
      CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o1;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_i0 =
      CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_ks;
  }

  // End of Switch: '<S13>/Switch'

  // Sum: '<S31>/Sum'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum = CNHTC_VEHICLE_MODEL_PureSL_B.Switch_i0 -
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_i;

  // Product: '<S31>/Product'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product_a = CNHTC_VEHICLE_MODEL_PureSL_B.upi *
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum;

  // Gain: '<S32>/Ratio of static to kinetic'
  u0 = CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_mus /
    CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_muk;
  CNHTC_VEHICLE_MODEL_PureSL_B.Ratioofstatictokinetic = u0 *
    CNHTC_VEHICLE_MODEL_PureSL_B.TorqueConversion;

  // RelationalOperator: '<S42>/Compare' incorporates:
  //   Constant: '<S42>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.Compare_l =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o1 ==
     CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_pn);
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Memory: '<S38>/Memory1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory1_h =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput_b;

    // UnaryMinus: '<S38>/Unary Minus2'
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus2 =
      -CNHTC_VEHICLE_MODEL_PureSL_B.Memory1_h;

    // Memory: '<S39>/Memory1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory1_k =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput_p;
  }

  // Logic: '<S38>/Logical Operator2'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator2 =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Compare_l &&
     CNHTC_VEHICLE_MODEL_PureSL_B.Compare_gz);

  // Logic: '<S39>/Logical Operator1'
  CNHTC_VEHICLE_MODEL_PureSL_B.ClutchClosed =
    !CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator2;

  // Logic: '<S39>/Logical Operator5'
  CNHTC_VEHICLE_MODEL_PureSL_B.ClutchClosedandready =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Compare_gz &&
     CNHTC_VEHICLE_MODEL_PureSL_B.ClutchClosed);

  // Logic: '<S39>/Logical Operator7'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator7 =
    (CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator3 ||
     CNHTC_VEHICLE_MODEL_PureSL_B.ClutchClosedandready);

  // Switch: '<S39>/Switch1'
  if (CNHTC_VEHICLE_MODEL_PureSL_B.ClutchClosedandready) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch1 = CNHTC_VEHICLE_MODEL_PureSL_B.NewGear;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch1 =
      CNHTC_VEHICLE_MODEL_PureSL_B.Memory1_k;
  }

  // End of Switch: '<S39>/Switch1'

  // RelationalOperator: '<S39>/Relational Operator'
  CNHTC_VEHICLE_MODEL_PureSL_B.Newgearrequest =
    (CNHTC_VEHICLE_MODEL_PureSL_B.GearSel !=
     CNHTC_VEHICLE_MODEL_PureSL_B.Switch1);

  // Logic: '<S39>/Logical Operator2'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator2_e =
    (CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator7 &&
     CNHTC_VEHICLE_MODEL_PureSL_B.Newgearrequest);

  // Logic: '<S38>/Logical Operator3'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator3_k =
    (CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator2_e &&
     CNHTC_VEHICLE_MODEL_PureSL_B.Compare_gz);
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Memory: '<S38>/Memory2'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory2 =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory2_PreviousInput;
  }

  // Switch: '<S38>/Switch1'
  if (CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator3_k) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch1_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus2;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch1_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.Memory2;
  }

  // End of Switch: '<S38>/Switch1'

  // Gain: '<S38>/Gain1'
  u0 = 1.0 / CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_tc;
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_m = u0 *
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch1_d;

  // Logic: '<S39>/Logical Operator4'
  CNHTC_VEHICLE_MODEL_PureSL_B.Begin =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Newgearrequest &&
     CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator2);

  // Logic: '<S39>/Logical Operator6'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator6 =
    !CNHTC_VEHICLE_MODEL_PureSL_B.Newgearrequest;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // InitialCondition: '<S40>/IC' incorporates:
    //   Constant: '<S40>/Constant1'

    if (CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_d) {
      CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_d = false;
      CNHTC_VEHICLE_MODEL_PureSL_B.IC_o =
        CNHTC_VEHICLE_MODEL_PureSL_P.IC_Value_a;
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.IC_o =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value_n;
    }

    // End of InitialCondition: '<S40>/IC'
  }

  // Integrator: '<S40>/Integrator1'
  // Limited  Integrator  (w/ Saturation Port)
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    zcEvent = (CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator6 &&
               (CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator1_Reset_ZCE !=
                POS_ZCSIG));
    CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator1_Reset_ZCE =
      CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator6;

    // evaluate zero-crossings
    if (zcEvent || (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK_j != 0)) {
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de =
        CNHTC_VEHICLE_MODEL_PureSL_B.IC_o;
    }
  }

  if (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de >=
      CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_UpperSat_a) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de =
      CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_UpperSat_a;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2_i = 1.0;
  } else if (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de <=
             CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_LowerSat_l) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de =
      CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_LowerSat_l;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2_i = -1.0;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2_i = 0.0;
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o1_e =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de;

  // End of Integrator: '<S40>/Integrator1'

  // RelationalOperator: '<S43>/Compare' incorporates:
  //   Constant: '<S43>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.Compare_lp =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2_i !=
     CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_k);
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Memory: '<S44>/Memory'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory_k =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_k;
  }

  // Logic: '<S44>/Logical Operator'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Memory_k || CNHTC_VEHICLE_MODEL_PureSL_B.Begin);

  // Logic: '<S44>/Logical Operator2'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator2_ex =
    !CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator6;

  // Logic: '<S44>/Logical Operator1'
  CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator1 =
    (CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator &&
     CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator2_ex);

  // DataTypeConversion: '<S40>/Data Type Conversion'
  CNHTC_VEHICLE_MODEL_PureSL_B.DataTypeConversion =
    CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator1;

  // Gain: '<S40>/Gain1'
  u0 = 1.0 / CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_ts;
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_mt = u0 *
    CNHTC_VEHICLE_MODEL_PureSL_B.DataTypeConversion;

  // Abs: '<S48>/Abs'
  CNHTC_VEHICLE_MODEL_PureSL_B.Abs_j = std::abs(CNHTC_VEHICLE_MODEL_PureSL_B.N);

  // Product: '<S48>/Product3'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product3 = CNHTC_VEHICLE_MODEL_PureSL_B.J /
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_j;

  // Sum: '<S48>/Add3' incorporates:
  //   Constant: '<S48>/Constant'

  u0 = rtP_Chas.Ie_kgm2 * 3.0;
  CNHTC_VEHICLE_MODEL_PureSL_B.Add3 = u0 + CNHTC_VEHICLE_MODEL_PureSL_B.Product3;

  // Product: '<S48>/Product8'
  CNHTC_VEHICLE_MODEL_PureSL_B.ApparentInertiaRatio = 1.0 /
    CNHTC_VEHICLE_MODEL_PureSL_B.Add3 * CNHTC_VEHICLE_MODEL_PureSL_B.Product3;

  // Product: '<S13>/Product2'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product2 =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus / CNHTC_VEHICLE_MODEL_PureSL_B.N;

  // Product: '<S48>/Product1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product1_e =
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2 / CNHTC_VEHICLE_MODEL_PureSL_B.N;

  // Gain: '<S48>/Input Clutch Damping'
  CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchDamping =
    CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_bin *
    CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE;

  // Product: '<S48>/Product2'
  CNHTC_VEHICLE_MODEL_PureSL_B.ApparentTransDamping =
    CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE *
    CNHTC_VEHICLE_MODEL_PureSL_B.b;

  // Sum: '<S48>/Sum2'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum2 = ((CNHTC_VEHICLE_MODEL_PureSL_B.Saturation
    + CNHTC_VEHICLE_MODEL_PureSL_B.Product1_e) -
    CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchDamping) -
    CNHTC_VEHICLE_MODEL_PureSL_B.ApparentTransDamping;

  // Product: '<S48>/Product4'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product4 =
    CNHTC_VEHICLE_MODEL_PureSL_B.ApparentInertiaRatio *
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum2;

  // Sum: '<S48>/Sum3'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum3 = CNHTC_VEHICLE_MODEL_PureSL_B.Product4 +
    CNHTC_VEHICLE_MODEL_PureSL_B.ApparentTransDamping;

  // Abs: '<S45>/Abs'
  CNHTC_VEHICLE_MODEL_PureSL_B.Abs_c = std::abs
    (CNHTC_VEHICLE_MODEL_PureSL_B.Sum3);

  // RelationalOperator: '<S45>/Relational Operator'
  CNHTC_VEHICLE_MODEL_PureSL_B.RelationalOperator =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Abs_c >=
     CNHTC_VEHICLE_MODEL_PureSL_B.Ratioofstatictokinetic);

  // Abs: '<S49>/Abs'
  CNHTC_VEHICLE_MODEL_PureSL_B.Abs_f = std::abs(CNHTC_VEHICLE_MODEL_PureSL_B.N);

  // Product: '<S49>/Product3'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product3_k = CNHTC_VEHICLE_MODEL_PureSL_B.J /
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_f;

  // Sum: '<S49>/Add3' incorporates:
  //   Constant: '<S49>/Constant'

  u0 = rtP_Chas.Ie_kgm2 * 3.0;
  CNHTC_VEHICLE_MODEL_PureSL_B.Add3_l = u0 +
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_k;

  // Gain: '<S49>/Input Damping'
  CNHTC_VEHICLE_MODEL_PureSL_B.InputDamping =
    CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_bin *
    CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE;

  // Product: '<S49>/Product1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product1_et =
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2 / CNHTC_VEHICLE_MODEL_PureSL_B.N;

  // Product: '<S49>/Product2'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product2_m =
    CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE *
    CNHTC_VEHICLE_MODEL_PureSL_B.b;

  // Product: '<S49>/Product8'
  CNHTC_VEHICLE_MODEL_PureSL_B.ApparentInertiaRatio_j = 1.0 /
    CNHTC_VEHICLE_MODEL_PureSL_B.Add3_l *
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_k;

  // Sum: '<S49>/Sum2'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum2_j =
    ((CNHTC_VEHICLE_MODEL_PureSL_B.Saturation +
      CNHTC_VEHICLE_MODEL_PureSL_B.Product1_et) -
     CNHTC_VEHICLE_MODEL_PureSL_B.InputDamping) -
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_m;

  // Product: '<S49>/Product4'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product4_b =
    CNHTC_VEHICLE_MODEL_PureSL_B.ApparentInertiaRatio_j *
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum2_j;

  // Sum: '<S49>/Sum3'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum3_l = CNHTC_VEHICLE_MODEL_PureSL_B.Product4_b
    + CNHTC_VEHICLE_MODEL_PureSL_B.Product2_m;

  // Product: '<S13>/Product1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product1_p =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg *
    CNHTC_VEHICLE_MODEL_PureSL_B.N;

  // Sum: '<S46>/Sum'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum_g =
    CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE -
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_p;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // HitCross: '<S46>/Velocities Match'
    zcEvent_0 = rt_ZCFcn(ANY_ZERO_CROSSING,
                         &CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.VelocitiesMatch_Input_ZCE,
                         (CNHTC_VEHICLE_MODEL_PureSL_B.Sum_g -
                          CNHTC_VEHICLE_MODEL_PureSL_P.VelocitiesMatch_Offset));
    if (CNHTC_VEHICLE_MODEL_PureSL_DW.VelocitiesMatch_MODE == 0) {
      if (zcEvent_0 != NO_ZCEVENT) {
        CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch =
          !CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch;
        CNHTC_VEHICLE_MODEL_PureSL_DW.VelocitiesMatch_MODE = 1;
      } else if (CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch) {
        CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch =
          ((!(CNHTC_VEHICLE_MODEL_PureSL_B.Sum_g !=
              CNHTC_VEHICLE_MODEL_PureSL_P.VelocitiesMatch_Offset)) &&
           CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch);
      } else {
        CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch =
          ((CNHTC_VEHICLE_MODEL_PureSL_B.Sum_g ==
            CNHTC_VEHICLE_MODEL_PureSL_P.VelocitiesMatch_Offset) ||
           CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch);
      }
    } else {
      CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch =
        ((!(CNHTC_VEHICLE_MODEL_PureSL_B.Sum_g !=
            CNHTC_VEHICLE_MODEL_PureSL_P.VelocitiesMatch_Offset)) &&
         CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch);
      CNHTC_VEHICLE_MODEL_PureSL_DW.VelocitiesMatch_MODE = 0;
    }

    // End of HitCross: '<S46>/Velocities Match'
  }

  // Abs: '<S50>/Abs'
  CNHTC_VEHICLE_MODEL_PureSL_B.Abs_e = std::abs
    (CNHTC_VEHICLE_MODEL_PureSL_B.Sum3_l);

  // RelationalOperator: '<S50>/Relational Operator'
  CNHTC_VEHICLE_MODEL_PureSL_B.RelationalOperator_n =
    (CNHTC_VEHICLE_MODEL_PureSL_B.Abs_e <=
     CNHTC_VEHICLE_MODEL_PureSL_B.Ratioofstatictokinetic);

  // Logic: '<S46>/Logic'
  CNHTC_VEHICLE_MODEL_PureSL_B.Logic =
    (CNHTC_VEHICLE_MODEL_PureSL_B.VelocitiesMatch &&
     CNHTC_VEHICLE_MODEL_PureSL_B.RelationalOperator_n);

  // CombinatorialLogic: '<S47>/Combinatorial  Logic'
  rowIdx = 0U;
  tmp[0] = CNHTC_VEHICLE_MODEL_PureSL_B.Logic;
  tmp[1] = CNHTC_VEHICLE_MODEL_PureSL_B.RelationalOperator;
  tmp[2] = CNHTC_VEHICLE_MODEL_PureSL_B.Memory_n;
  for (i = 0; i < 3; i++) {
    rowIdx = (rowIdx << 1) + tmp[static_cast<uint32_T>(i)];
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.CombinatorialLogic =
    CNHTC_VEHICLE_MODEL_PureSL_P.CombinatorialLogic_table[rowIdx];

  // End of CombinatorialLogic: '<S47>/Combinatorial  Logic'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // ModelReference: '<S3>/Engine_ECU' incorporates:
    //   Constant: '<S3>/Constant'
    //   Inport: '<Root>/pedalPos_pct'
    //   Outport: '<Root>/GearPos'

    Engine_ECUMDLOBJ2.step(&CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm,
      &CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_h,
      &CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_h, &pedalPos_pct,
      &CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay2,
      &CNHTC_VEHICLE_MODEL_PureSL_B.GearSel,
      &CNHTC_VEHICLE_MODEL_PureSL_Y.GearPos,
      &CNHTC_VEHICLE_MODEL_PureSL_B.TrqCmd);

    // Memory: '<S89>/Memory'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory_c =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_p;

    // Constant: '<S88>/domega_o'
    CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_o =
      CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance2_domega_o;
  }

  // Sum: '<S5>/Sum'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum_l = CNHTC_VEHICLE_MODEL_PureSL_B.TrqCmd -
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1;

  // Product: '<S5>/Divide' incorporates:
  //   Constant: '<S5>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.Divide_c = CNHTC_VEHICLE_MODEL_PureSL_B.Sum_l *
    CNHTC_VEHICLE_MODEL_PureSL_P.ElectronicThrottleActuatorDynamics1_wc;

  // Integrator: '<S89>/Integrator'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    zcEvent_0 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator_Reset_ZCE_g,
                         (CNHTC_VEHICLE_MODEL_PureSL_B.Memory_c));
    zcEvent = (zcEvent_0 != NO_ZCEVENT);

    // evaluate zero-crossings
    if (zcEvent || (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_i != 0)) {
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_k =
        CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_o;
    }
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_m =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_k;

  // End of Integrator: '<S89>/Integrator'

  // Gain: '<S88>/Gain2'
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_g =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance2_b *
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_m;

  // Integrator: '<S88>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_if =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_b;

  // Gain: '<S88>/Gain1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_e =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance2_k *
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_if;

  // Sum: '<S88>/Subtract1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_b =
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_g + CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_e;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Memory: '<S81>/Memory'
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory_l =
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_c;

    // Constant: '<S80>/domega_o'
    CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_h =
      CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance1_domega_o;
  }

  // Integrator: '<S81>/Integrator'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    zcEvent_0 = rt_ZCFcn(RISING_ZERO_CROSSING,
                         &CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator_Reset_ZCE_a,
                         (CNHTC_VEHICLE_MODEL_PureSL_B.Memory_l));
    zcEvent = (zcEvent_0 != NO_ZCEVENT);

    // evaluate zero-crossings
    if (zcEvent || (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_c != 0)) {
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_i =
        CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_h;
    }
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_c =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_i;

  // End of Integrator: '<S81>/Integrator'

  // Gain: '<S80>/Gain2'
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_c4 =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance1_b *
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_c;

  // Integrator: '<S80>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_mv =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_d5;

  // Gain: '<S80>/Gain1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_mx =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance1_k *
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_mv;

  // Sum: '<S80>/Subtract1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_p =
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_c4 +
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_mx;

  // Sum: '<S6>/Add'
  CNHTC_VEHICLE_MODEL_PureSL_B.Add_a = CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_b
    + CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_p;

  // SignalConversion generated from: '<S6>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_nl[0] =
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_b;

  // SignalConversion generated from: '<S6>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_nl[1] =
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_p;

  // SignalConversion generated from: '<S6>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_nl[2] = 0.0;

  // SignalConversion generated from: '<S6>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_nl[3] = 0.0;

  // Gain: '<S6>/Gain'
  u0 = 1.0 / rtP_Chas.Rt;
  CNHTC_VEHICLE_MODEL_PureSL_B.Gain_a = u0 * CNHTC_VEHICLE_MODEL_PureSL_B.Add_a;

  // Product: '<S6>/Divide' incorporates:
  //   Constant: '<S6>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.a_sim = CNHTC_VEHICLE_MODEL_PureSL_B.Gain_a /
    CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_ir;

  // Integrator: '<S6>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_B.v =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_o;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Switch: '<S67>/Switch' incorporates:
    //   Constant: '<S67>/Constant'
    //   Constant: '<S67>/Constant1'

    if (CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_kz >
        CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_b) {
      CNHTC_VEHICLE_MODEL_PureSL_B.diffDir =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value_p;
    } else {
      // UnaryMinus: '<S67>/Unary Minus' incorporates:
      //   Constant: '<S67>/Constant1'

      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_e =
        -CNHTC_VEHICLE_MODEL_PureSL_P.Constant1_Value_p;
      CNHTC_VEHICLE_MODEL_PureSL_B.diffDir =
        CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_e;
    }

    // End of Switch: '<S67>/Switch'

    // Constant: '<S63>/Constant'
    CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate[0] =
      CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_omegaw1o;

    // Constant: '<S63>/Constant1'
    CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate[1] =
      CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_omegaw2o;
  }

  // Gain: '<S67>/Gain'
  // Limited  Integrator
  u0 = rtP_Chas.DifRatio / 2.0;
  for (i = 0; i < 2; i++) {
    // Integrator: '<S63>/Integrator'
    if (CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_l != 0) {
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[i] =
        CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate[i];
    }

    if (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[i] >=
        CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_UpperSat_h) {
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[i] =
        CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_UpperSat_h;
    } else {
      if (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[i] <=
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_LowerSat_e) {
        CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[i] =
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_LowerSat_e;
      }
    }

    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_ng[i] =
      CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[i];

    // End of Integrator: '<S63>/Integrator'

    // Product: '<S67>/Product'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_d[i] =
      CNHTC_VEHICLE_MODEL_PureSL_B.diffDir *
      CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_ng[i];

    // Gain: '<S67>/Gain'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain_l[i] = u0 *
      CNHTC_VEHICLE_MODEL_PureSL_B.Product_d[i];
  }

  // Sum: '<S67>/Sum of Elements'
  u0 = -0.0;
  for (i = 0; i < 2; i++) {
    u0 += CNHTC_VEHICLE_MODEL_PureSL_B.Gain_l[i];

    // UnaryMinus: '<S67>/Unary Minus1'
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus1[i] =
      -CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_ng[i];

    // Gain: '<S67>/Gain1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_l[i] =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain1_Gain_o *
      CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_ng[i];
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.SumofElements = u0;

  // End of Sum: '<S67>/Sum of Elements'

  // SignalConversion generated from: '<S67>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_n[0] =
    CNHTC_VEHICLE_MODEL_PureSL_B.SumofElements;

  // SignalConversion generated from: '<S67>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_n[1] =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus1[0];

  // SignalConversion generated from: '<S67>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_n[2] =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus1[1];

  // Sum: '<S67>/Add'
  CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_n[3] =
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_l[0] -
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_l[1];

  // Product: '<S77>/Product1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product1_g =
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1 *
    CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_n[0];

  // Switch: '<S77>/Switch' incorporates:
  //   Constant: '<S77>/Constant'
  //   Constant: '<S79>/Constant'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_g >
      CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_d) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_j =
      CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_eta;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_j =
      CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_m;
  }

  // End of Switch: '<S77>/Switch'

  // Product: '<S77>/Product4'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product4_j =
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_j *
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1;

  // UnaryMinus: '<S88>/Unary Minus'
  CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_f =
    -CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_b;

  // Product: '<S75>/Product1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product1_a =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_f *
    CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_n[1];

  // Switch: '<S75>/Switch' incorporates:
  //   Constant: '<S75>/Constant'
  //   Constant: '<S79>/Constant'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_a >
      CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_lf) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_n =
      CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_eta;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_n =
      CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_f;
  }

  // End of Switch: '<S75>/Switch'

  // Product: '<S75>/Product4'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product4_o =
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_n *
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_f;

  // UnaryMinus: '<S80>/Unary Minus'
  CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_m =
    -CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_p;

  // Product: '<S76>/Product1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product1_l =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_m *
    CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_n[2];

  // Switch: '<S76>/Switch' incorporates:
  //   Constant: '<S76>/Constant'
  //   Constant: '<S79>/Constant'

  if (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_l >
      CNHTC_VEHICLE_MODEL_PureSL_P.Switch_Threshold_l2) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_jk =
      CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_eta;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_jk =
      CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_bq;
  }

  // End of Switch: '<S76>/Switch'

  // Product: '<S76>/Product4'
  CNHTC_VEHICLE_MODEL_PureSL_B.Product4_k =
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_jk *
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_m;

  // SignalConversion generated from: '<S66>/ SFunction ' incorporates:
  //   MATLAB Function: '<S63>/Open Differential'

  CNHTC_VEHICLE_MODEL_PureSL_B.TmpSignalConversionAtSFunctionInport1[0] =
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_j;
  CNHTC_VEHICLE_MODEL_PureSL_B.TmpSignalConversionAtSFunctionInport1[1] =
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_o;
  CNHTC_VEHICLE_MODEL_PureSL_B.TmpSignalConversionAtSFunctionInport1[2] =
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_k;

  // MATLAB Function: '<S63>/Open Differential' incorporates:
  //   Constant: '<S63>/Jd'
  //   Constant: '<S63>/Jw1'
  //   Constant: '<S63>/Jw3'
  //   Constant: '<S63>/Ndiff2'
  //   Constant: '<S63>/bd'
  //   Constant: '<S63>/bw1'
  //   Constant: '<S63>/bw2'

  // MATLAB Function 'Open Differential/Open Differential': '<S66>:1'
  // '<S66>:1:2' coder.allowpcode('plain')
  // '<S66>:1:3' if shaftSwitchMask==1
  if (CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_shaftSwitchMask == 1.0) {
    // '<S66>:1:4' [~,xdot] = automldiffopen(u,bw1,bd,bw2,Ndiff,1,Jd,Jw1,Jw2,x); 
    automldiffopen_m841FDlI
      (CNHTC_VEHICLE_MODEL_PureSL_B.TmpSignalConversionAtSFunctionInport1,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_bw1,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_bd,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_bw2, rtP_Chas.DifRatio, 1.0,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_Jd,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_Jw1,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_Jw2,
       CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_ng, unusedU1,
       CNHTC_VEHICLE_MODEL_PureSL_B.xdot);

    // '<S66>:1:4' ~
  } else {
    // '<S66>:1:5' else
    // '<S66>:1:6' [~,xdot] = automldiffopen(u,bw1,bd,bw2,Ndiff,0,Jd,Jw1,Jw2,x); 
    automldiffopen_m841FDlI
      (CNHTC_VEHICLE_MODEL_PureSL_B.TmpSignalConversionAtSFunctionInport1,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_bw1,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_bd,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_bw2, rtP_Chas.DifRatio, 0.0,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_Jd,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_Jw1,
       CNHTC_VEHICLE_MODEL_PureSL_P.OpenDifferential_Jw2,
       CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_ng, unusedU1,
       CNHTC_VEHICLE_MODEL_PureSL_B.xdot);

    // '<S66>:1:6' ~
  }

  // UnaryMinus: '<S70>/Unary Minus2'
  for (i = 0; i < 2; i++) {
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus2_g[i] =
      -CNHTC_VEHICLE_MODEL_PureSL_B.xdot[i];
  }

  // End of UnaryMinus: '<S70>/Unary Minus2'

  // SignalConversion generated from: '<S70>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.omegadot[1] =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus2_g[0];

  // SignalConversion generated from: '<S70>/Vector Concatenate'
  CNHTC_VEHICLE_MODEL_PureSL_B.omegadot[2] =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus2_g[1];
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Switch: '<S70>/Switch1' incorporates:
    //   Constant: '<S70>/Constant'
    //   Constant: '<S70>/Constant6'

    if (CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_l >
        CNHTC_VEHICLE_MODEL_PureSL_P.Switch1_Threshold) {
      CNHTC_VEHICLE_MODEL_PureSL_B.diffDir_l =
        CNHTC_VEHICLE_MODEL_PureSL_P.Constant6_Value;
    } else {
      // UnaryMinus: '<S70>/Unary Minus' incorporates:
      //   Constant: '<S70>/Constant6'

      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_d =
        -CNHTC_VEHICLE_MODEL_PureSL_P.Constant6_Value;
      CNHTC_VEHICLE_MODEL_PureSL_B.diffDir_l =
        CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_d;
    }

    // End of Switch: '<S70>/Switch1'
  }

  // Gain: '<S70>/Gain1'
  u0 = rtP_Chas.DifRatio / 2.0;
  for (i = 0; i < 2; i++) {
    // Product: '<S70>/Product1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_j[i] =
      CNHTC_VEHICLE_MODEL_PureSL_B.diffDir_l *
      CNHTC_VEHICLE_MODEL_PureSL_B.xdot[i];

    // Gain: '<S70>/Gain1'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_f[i] = u0 *
      CNHTC_VEHICLE_MODEL_PureSL_B.Product1_j[i];
  }

  // Sum: '<S70>/Sum of Elements2'
  u0 = -0.0;
  for (i = 0; i < 2; i++) {
    u0 += CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_f[i];
  }

  CNHTC_VEHICLE_MODEL_PureSL_B.omegadot[0] = u0;

  // End of Sum: '<S70>/Sum of Elements2'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Gain: '<S9>/Gain11'
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain11 =
      CNHTC_VEHICLE_MODEL_PureSL_P.Gain11_Gain *
      CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_h;

    // Product: '<S9>/Divide5' incorporates:
    //   Constant: '<S9>/Constant12'

    CNHTC_VEHICLE_MODEL_PureSL_B.Divide5 = CNHTC_VEHICLE_MODEL_PureSL_B.Gain11 /
      rtP_Chas.Rt;
  }

  // Sum: '<S80>/Subtract'
  CNHTC_VEHICLE_MODEL_PureSL_B.Subtract =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus1[1] -
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide5;

  // Switch: '<S81>/Switch'
  if (CNHTC_VEHICLE_MODEL_PureSL_B.Memory_l != 0.0) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_o =
      CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_c;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_o =
      CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_h;
  }

  // End of Switch: '<S81>/Switch'

  // Sum: '<S81>/Sum'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum_i = CNHTC_VEHICLE_MODEL_PureSL_B.Subtract -
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_o;

  // Product: '<S81>/Product' incorporates:
  //   Constant: '<S80>/omega_c'

  CNHTC_VEHICLE_MODEL_PureSL_B.Product_ab =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance1_omega_c *
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_i;

  // Sum: '<S88>/Subtract'
  CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_b =
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus1[0] -
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide5;

  // Switch: '<S89>/Switch'
  if (CNHTC_VEHICLE_MODEL_PureSL_B.Memory_c != 0.0) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_m;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_d =
      CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_o;
  }

  // End of Switch: '<S89>/Switch'

  // Sum: '<S89>/Sum'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum_o = CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_b -
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_d;

  // Product: '<S89>/Product' incorporates:
  //   Constant: '<S88>/omega_c'

  CNHTC_VEHICLE_MODEL_PureSL_B.Product_dd =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance2_omega_c *
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_o;

  // Gain: '<S3>/Gain1'
  CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm_g =
    CNHTC_VEHICLE_MODEL_PureSL_P.Gain1_Gain_a *
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge3;

  // Integrator: '<S99>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_i4 =
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_bf;
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    // Gain: '<S99>/RPM to deg//s'
    CNHTC_VEHICLE_MODEL_PureSL_B.RPMtodegs =
      CNHTC_VEHICLE_MODEL_PureSL_P.RPMtodegs_Gain *
      CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm;
  }

  // Sum: '<S117>/Subtract'
  CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_i = CNHTC_VEHICLE_MODEL_PureSL_B.Merge -
    CNHTC_VEHICLE_MODEL_PureSL_B.SumofElements;

  // Switch: '<S118>/Switch'
  if (CNHTC_VEHICLE_MODEL_PureSL_B.Memory != 0.0) {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_jp =
      CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_k;
  } else {
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_jp =
      CNHTC_VEHICLE_MODEL_PureSL_B.domega_o;
  }

  // End of Switch: '<S118>/Switch'

  // Sum: '<S118>/Sum'
  CNHTC_VEHICLE_MODEL_PureSL_B.Sum_k = CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_i -
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_jp;

  // Product: '<S118>/Product' incorporates:
  //   Constant: '<S117>/omega_c'

  CNHTC_VEHICLE_MODEL_PureSL_B.Product_h =
    CNHTC_VEHICLE_MODEL_PureSL_P.PropShaft_omega_c *
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_k;

  // RelationalOperator: '<S133>/Compare' incorporates:
  //   Constant: '<S133>/Constant'

  CNHTC_VEHICLE_MODEL_PureSL_B.Compare_d =
    (CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps <
     CNHTC_VEHICLE_MODEL_PureSL_P.CompareToConstant_const_d);

  // Stop: '<S126>/Stop Simulation'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M)) &&
      CNHTC_VEHICLE_MODEL_PureSL_B.Compare_d) {
    rtmSetStopRequested((&CNHTC_VEHICLE_MODEL_PureSL_M), 1);
  }

  // End of Stop: '<S126>/Stop Simulation'
  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
      // Update for UnitDelay: '<S3>/Unit Delay1'
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay1_DSTATE =
        CNHTC_VEHICLE_MODEL_PureSL_B.NewGear;

      // Update for UnitDelay: '<S3>/Unit Delay3' incorporates:
      //   Outport: '<Root>/EngSpd_rpm'

      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay3_DSTATE =
        CNHTC_VEHICLE_MODEL_PureSL_Y.EngSpd_rpm;

      // Update for UnitDelay: '<S3>/Unit Delay4'
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay4_DSTATE =
        CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm_g;

      // Update for UnitDelay: '<S3>/Unit Delay2'
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay2_DSTATE =
        CNHTC_VEHICLE_MODEL_PureSL_B.Memory_n;
    }

    // Update for Integrator: '<S2>/Integrator'
    CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK = 0;

    // Update for Integrator: '<S2>/Integrator1'
    CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK = 0;

    // Update for Atomic SubSystem: '<S125>/TwoDofDynamic'
    CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_Update
      (&CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic,
       &CNHTC_VEHICLE_MODEL_PureSL_DW.TwoDofDynamic);

    // End of Update for SubSystem: '<S125>/TwoDofDynamic'
    if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
      // Update for UnitDelay: '<S2>/Unit Delay'
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay_DSTATE = ax_mps2;

      // Update for UnitDelay: '<Root>/Unit Delay1'
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay1_DSTATE_h = ax_mps2;

      // Update for Memory: '<S47>/Memory'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_j =
        CNHTC_VEHICLE_MODEL_PureSL_B.CombinatorialLogic;

      // Update for Memory: '<S118>/Memory' incorporates:
      //   Constant: '<S118>/Reset'

      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput =
        CNHTC_VEHICLE_MODEL_PureSL_P.Reset_Value_o3;

      // Update for UnitDelay: '<Root>/Unit Delay'
      CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay_DSTATE_i = Velong_kph;

      // Update for Memory: '<S35>/Memory3'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory3_PreviousInput =
        CNHTC_VEHICLE_MODEL_PureSL_B.NewGear;

      // Update for Memory: '<S35>/Memory'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_a =
        CNHTC_VEHICLE_MODEL_PureSL_B.GearSel;

      // Update for Memory: '<S35>/Memory1'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput =
        CNHTC_VEHICLE_MODEL_PureSL_B.CmdGear;
    }

    // Update for Integrator: '<S118>/Integrator'
    CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_j = 0;

    // Update for Integrator: '<S38>/Integrator1'
    CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK_a = 0;
    if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
      // Update for Memory: '<S40>/Memory2'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory2_PreviousInput_d =
        CNHTC_VEHICLE_MODEL_PureSL_B.Compare_lp;

      // Update for Memory: '<S38>/Memory1'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput_b =
        CNHTC_VEHICLE_MODEL_PureSL_B.Memory2;

      // Update for Memory: '<S39>/Memory1'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput_p =
        CNHTC_VEHICLE_MODEL_PureSL_B.Switch1;

      // Update for Memory: '<S38>/Memory2'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory2_PreviousInput =
        CNHTC_VEHICLE_MODEL_PureSL_B.Switch1_d;
    }

    // Update for If: '<S10>/If'
    switch (CNHTC_VEHICLE_MODEL_PureSL_DW.If_ActiveSubsystem) {
     case 0:
      // Update for IfAction SubSystem: '<S10>/Locked' incorporates:
      //   ActionPort: '<S12>/Action'

      // Update for Integrator: '<S12>/Locked Shaft Integrator'
      CNHTC_VEHICLE_MODEL_PureSL_DW.LockedShaftIntegrator_IWORK = 0;

      // End of Update for SubSystem: '<S10>/Locked'
      break;

     case 1:
      // Update for IfAction SubSystem: '<S10>/Unlocked' incorporates:
      //   ActionPort: '<S14>/Action'

      // Update for Integrator: '<S14>/Pump Integrator'
      CNHTC_VEHICLE_MODEL_PureSL_DW.PumpIntegrator_IWORK = 0;

      // Update for Integrator: '<S14>/Integrator'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_p = 0;

      // End of Update for SubSystem: '<S10>/Unlocked'
      break;
    }

    // End of Update for If: '<S10>/If'

    // Update for Integrator: '<S40>/Integrator1'
    CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK_j = 0;
    if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
      // Update for Memory: '<S44>/Memory'
      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_k =
        CNHTC_VEHICLE_MODEL_PureSL_B.LogicalOperator1;

      // Update for Memory: '<S89>/Memory' incorporates:
      //   Constant: '<S89>/Reset'

      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_p =
        CNHTC_VEHICLE_MODEL_PureSL_P.Reset_Value_o;

      // Update for Memory: '<S81>/Memory' incorporates:
      //   Constant: '<S81>/Reset'

      CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_c =
        CNHTC_VEHICLE_MODEL_PureSL_P.Reset_Value;
    }

    // Update for Integrator: '<S89>/Integrator'
    CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_i = 0;

    // Update for Integrator: '<S81>/Integrator'
    CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_c = 0;

    // Update for Integrator: '<S63>/Integrator'
    CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_l = 0;

    // ContTimeOutputInconsistentWithStateAtMajorOutputFlag is set, need to run a minor output 
    if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
      if (rtsiGetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo)) {
        rtsiSetSimTimeStep(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                           MINOR_TIME_STEP);
        rtsiSetContTimeOutputInconsistentWithStateAtMajorStep
          (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, false);
        CNHTC_VEHICLE_MODEL_PureSLModelClass::step();
        rtsiSetSimTimeStep(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                           MAJOR_TIME_STEP);
      }
    }
  }                                    // end MajorTimeStep

  if (rtmIsMajorTimeStep((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    rt_ertODEUpdateContinuousStates(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++(&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.clockTick0;
    (&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.t[0] = rtsiGetSolverStopTime
      (&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo);

    {
      // Update absolute timer for sample time: [0.002s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.002, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      (&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void CNHTC_VEHICLE_MODEL_PureSLModelClass::
  CNHTC_VEHICLE_MODEL_PureSL_derivatives()
{
  int_T iS;
  boolean_T lsat;
  boolean_T usat;
  XDot_CNHTC_VEHICLE_MODEL_PureSL_T *_rtXdot;
  _rtXdot = ((XDot_CNHTC_VEHICLE_MODEL_PureSL_T *)
             (&CNHTC_VEHICLE_MODEL_PureSL_M)->derivs);

  // Derivatives for Integrator: '<S5>/Integrator1'
  _rtXdot->Integrator1_CSTATE = CNHTC_VEHICLE_MODEL_PureSL_B.Divide_c;

  // Derivatives for Integrator: '<S2>/Integrator'
  _rtXdot->Integrator_CSTATE = ax_mps2;

  // Derivatives for Integrator: '<S2>/Integrator1'
  _rtXdot->Integrator1_CSTATE_h = CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_c;

  // Derivatives for Integrator: '<Root>/Integrator'
  _rtXdot->Integrator_CSTATE_l = CNHTC_VEHICLE_MODEL_PureSL_B.Product;

  // Derivatives for Integrator: '<Root>/Integrator1'
  _rtXdot->Integrator1_CSTATE_o = CNHTC_VEHICLE_MODEL_PureSL_B.Product1_f;

  // Derivatives for Integrator: '<S118>/Integrator'
  _rtXdot->Integrator_CSTATE_m = CNHTC_VEHICLE_MODEL_PureSL_B.Product_h;

  // Derivatives for Integrator: '<S117>/Integrator'
  _rtXdot->Integrator_CSTATE_d = CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_i;

  // Derivatives for Integrator: '<S31>/Integrator'
  _rtXdot->Integrator_CSTATE_df = CNHTC_VEHICLE_MODEL_PureSL_B.Product_a;

  // Derivatives for Integrator: '<S38>/Integrator1'
  lsat = (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d <=
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_LowerSat);
  usat = (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d >=
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_m >
        0.0)) || (usat && (CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_m < 0.0))) {
    _rtXdot->Integrator1_CSTATE_d = CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_m;
  } else {
    // in saturation
    _rtXdot->Integrator1_CSTATE_d = 0.0;
  }

  // End of Derivatives for Integrator: '<S38>/Integrator1'

  // Derivatives for If: '<S10>/If'
  ((XDot_CNHTC_VEHICLE_MODEL_PureSL_T *) (&CNHTC_VEHICLE_MODEL_PureSL_M)->derivs)
    ->LockedShaftIntegrator_CSTATE = 0.0;

  {
    real_T *dx;
    int_T i;
    dx = &(((XDot_CNHTC_VEHICLE_MODEL_PureSL_T *) (&CNHTC_VEHICLE_MODEL_PureSL_M)
            ->derivs)->PumpIntegrator_CSTATE);
    for (i=0; i < 2; i++) {
      dx[i] = 0.0;
    }
  }

  switch (CNHTC_VEHICLE_MODEL_PureSL_DW.If_ActiveSubsystem) {
   case 0:
    // Derivatives for IfAction SubSystem: '<S10>/Locked' incorporates:
    //   ActionPort: '<S12>/Action'

    // Derivatives for Integrator: '<S12>/Locked Shaft Integrator'
    lsat = (CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE <=
            CNHTC_VEHICLE_MODEL_PureSL_P.LockedShaftIntegrator_LowerSat);
    usat = (CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE >=
            CNHTC_VEHICLE_MODEL_PureSL_P.LockedShaftIntegrator_UpperSat);
    if (((!lsat) && (!usat)) || (lsat && (CNHTC_VEHICLE_MODEL_PureSL_B.Product8 >
          0.0)) || (usat && (CNHTC_VEHICLE_MODEL_PureSL_B.Product8 < 0.0))) {
      _rtXdot->LockedShaftIntegrator_CSTATE =
        CNHTC_VEHICLE_MODEL_PureSL_B.Product8;
    } else {
      // in saturation
      _rtXdot->LockedShaftIntegrator_CSTATE = 0.0;
    }

    // End of Derivatives for Integrator: '<S12>/Locked Shaft Integrator'
    // End of Derivatives for SubSystem: '<S10>/Locked'
    break;

   case 1:
    // Derivatives for IfAction SubSystem: '<S10>/Unlocked' incorporates:
    //   ActionPort: '<S14>/Action'

    // Derivatives for Integrator: '<S14>/Pump Integrator'
    lsat = (CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE <=
            CNHTC_VEHICLE_MODEL_PureSL_P.PumpIntegrator_LowerSat);
    usat = (CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE >=
            CNHTC_VEHICLE_MODEL_PureSL_P.PumpIntegrator_UpperSat);
    if (((!lsat) && (!usat)) || (lsat &&
         (CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchInertia > 0.0)) || (usat &&
         (CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchInertia < 0.0))) {
      _rtXdot->PumpIntegrator_CSTATE =
        CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchInertia;
    } else {
      // in saturation
      _rtXdot->PumpIntegrator_CSTATE = 0.0;
    }

    // End of Derivatives for Integrator: '<S14>/Pump Integrator'

    // Derivatives for Integrator: '<S14>/Integrator'
    lsat = (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg <=
            CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_LowerSat);
    usat = (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg >=
            CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_UpperSat);
    if (((!lsat) && (!usat)) || (lsat &&
         (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_j2 > 0.0)) || (usat &&
         (CNHTC_VEHICLE_MODEL_PureSL_B.Product1_j2 < 0.0))) {
      _rtXdot->Integrator_CSTATE_kg = CNHTC_VEHICLE_MODEL_PureSL_B.Product1_j2;
    } else {
      // in saturation
      _rtXdot->Integrator_CSTATE_kg = 0.0;
    }

    // End of Derivatives for Integrator: '<S14>/Integrator'
    // End of Derivatives for SubSystem: '<S10>/Unlocked'
    break;
  }

  // End of Derivatives for If: '<S10>/If'

  // Derivatives for Integrator: '<S40>/Integrator1'
  lsat = (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de <=
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_LowerSat_l);
  usat = (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de >=
          CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_UpperSat_a);
  if (((!lsat) && (!usat)) || (lsat && (CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_mt >
        0.0)) || (usat && (CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_mt < 0.0))) {
    _rtXdot->Integrator1_CSTATE_de = CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_mt;
  } else {
    // in saturation
    _rtXdot->Integrator1_CSTATE_de = 0.0;
  }

  // End of Derivatives for Integrator: '<S40>/Integrator1'

  // Derivatives for Integrator: '<S89>/Integrator'
  _rtXdot->Integrator_CSTATE_k = CNHTC_VEHICLE_MODEL_PureSL_B.Product_dd;

  // Derivatives for Integrator: '<S88>/Integrator'
  _rtXdot->Integrator_CSTATE_b = CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_b;

  // Derivatives for Integrator: '<S81>/Integrator'
  _rtXdot->Integrator_CSTATE_i = CNHTC_VEHICLE_MODEL_PureSL_B.Product_ab;

  // Derivatives for Integrator: '<S80>/Integrator'
  _rtXdot->Integrator_CSTATE_d5 = CNHTC_VEHICLE_MODEL_PureSL_B.Subtract;

  // Derivatives for Integrator: '<S6>/Integrator'
  _rtXdot->Integrator_CSTATE_o = CNHTC_VEHICLE_MODEL_PureSL_B.a_sim;

  // Derivatives for Integrator: '<S63>/Integrator'
  for (iS = 0; iS < 2; iS++) {
    lsat = (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[iS] <=
            CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_LowerSat_e);
    usat = (CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[iS] >=
            CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_UpperSat_h);
    if (((!lsat) && (!usat)) || (lsat && (CNHTC_VEHICLE_MODEL_PureSL_B.xdot[iS] >
          0.0)) || (usat && (CNHTC_VEHICLE_MODEL_PureSL_B.xdot[iS] < 0.0))) {
      _rtXdot->Integrator_CSTATE_lv[iS] = CNHTC_VEHICLE_MODEL_PureSL_B.xdot[iS];
    } else {
      // in saturation
      _rtXdot->Integrator_CSTATE_lv[iS] = 0.0;
    }
  }

  // End of Derivatives for Integrator: '<S63>/Integrator'

  // Derivatives for Integrator: '<S99>/Integrator'
  _rtXdot->Integrator_CSTATE_bf = CNHTC_VEHICLE_MODEL_PureSL_B.RPMtodegs;
}

// Model initialize function
void CNHTC_VEHICLE_MODEL_PureSLModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // non-finite (run-time) assignments
  CNHTC_VEHICLE_MODEL_PureSL_P.Saturation_UpperSat = rtInf;
  CNHTC_VEHICLE_MODEL_PureSL_P.Saturation_UpperSat_p = rtInf;
  CNHTC_VEHICLE_MODEL_PureSL_P.TwoDofDynamic.Saturation_UpperSat = rtInf;

  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                          &(&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.simTimeStep);
    rtsiSetTPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, &rtmGetTPtr
                ((&CNHTC_VEHICLE_MODEL_PureSL_M)));
    rtsiSetStepSizePtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                       &(&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.stepSize0);
    rtsiSetdXPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                 &(&CNHTC_VEHICLE_MODEL_PureSL_M)->derivs);
    rtsiSetContStatesPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, (real_T **)
                         &(&CNHTC_VEHICLE_MODEL_PureSL_M)->contStates);
    rtsiSetNumContStatesPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
      &(&CNHTC_VEHICLE_MODEL_PureSL_M)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
      &(&CNHTC_VEHICLE_MODEL_PureSL_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)
      ->solverInfo, &(&CNHTC_VEHICLE_MODEL_PureSL_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)
      ->solverInfo, &(&CNHTC_VEHICLE_MODEL_PureSL_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                          (&rtmGetErrorStatus((&CNHTC_VEHICLE_MODEL_PureSL_M))));
    rtsiSetRTModelPtr(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                      (&CNHTC_VEHICLE_MODEL_PureSL_M));
  }

  rtsiSetSimTimeStep(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,
                     MAJOR_TIME_STEP);
  (&CNHTC_VEHICLE_MODEL_PureSL_M)->intgData.y = (&CNHTC_VEHICLE_MODEL_PureSL_M
    )->odeY;
  (&CNHTC_VEHICLE_MODEL_PureSL_M)->intgData.f[0] =
    (&CNHTC_VEHICLE_MODEL_PureSL_M)->odeF[0];
  (&CNHTC_VEHICLE_MODEL_PureSL_M)->intgData.f[1] =
    (&CNHTC_VEHICLE_MODEL_PureSL_M)->odeF[1];
  (&CNHTC_VEHICLE_MODEL_PureSL_M)->intgData.f[2] =
    (&CNHTC_VEHICLE_MODEL_PureSL_M)->odeF[2];
  (&CNHTC_VEHICLE_MODEL_PureSL_M)->contStates = ((X_CNHTC_VEHICLE_MODEL_PureSL_T
    *) &CNHTC_VEHICLE_MODEL_PureSL_X);
  (&CNHTC_VEHICLE_MODEL_PureSL_M)->periodicContStateIndices = ((int_T*)
    CNHTC_VEHICLE_MODEL_PureSL_PeriodicIndX);
  (&CNHTC_VEHICLE_MODEL_PureSL_M)->periodicContStateRanges = ((real_T*)
    CNHTC_VEHICLE_MODEL_PureSL_PeriodicRngX);
  rtsiSetSolverData(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo, static_cast<
                    void *>(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->intgData));
  rtsiSetSolverName(&(&CNHTC_VEHICLE_MODEL_PureSL_M)->solverInfo,"ode3");
  rtmSetTPtr((&CNHTC_VEHICLE_MODEL_PureSL_M), &(&CNHTC_VEHICLE_MODEL_PureSL_M)
             ->Timing.tArray[0]);
  (&CNHTC_VEHICLE_MODEL_PureSL_M)->Timing.stepSize0 = 0.002;
  rtmSetFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M), 1);

  // block I/O
  (void) std::memset((static_cast<void *>(&CNHTC_VEHICLE_MODEL_PureSL_B)), 0,
                     sizeof(B_CNHTC_VEHICLE_MODEL_PureSL_T));

  {
    int32_T i;
    for (i = 0; i < 4; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.bwdWhlPre_Mpa[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.fwdWhlPre_Mpa[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.TrailWhlPre_Mpa[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_ng[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Product_d[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Gain_l[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus1[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_l[i] = 0.0;
    }

    for (i = 0; i < 4; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_n[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus2_g[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Product1_j[i] = 0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_f[i] = 0.0;
    }

    for (i = 0; i < 3; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.omegadot[i] = 0.0;
    }

    for (i = 0; i < 4; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.VectorConcatenate_nl[i] = 0.0;
    }

    for (i = 0; i < 3; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.TmpSignalConversionAtSFunctionInport1[i] =
        0.0;
    }

    for (i = 0; i < 2; i++) {
      CNHTC_VEHICLE_MODEL_PureSL_B.xdot[i] = 0.0;
    }

    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.EngTrq = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Constant1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.VxBody_mps = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Constant4 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.SteerWhAngle_DZ_deg = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.WhlAngF_deg = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.WhlAngF_rad = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Omega_w_rads = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide1_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.FxfDr = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay1_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.BraF = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.BraF_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Fxf_N = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.uDLookupTable = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Tw_Nm = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Fxr = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Fxr_N = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Fextx = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add1_h = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Cos = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sin = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.domega_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_n = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_i = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.ClutchGain = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Saturation_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TorqueConversion = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_h = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.GearSel = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory_h = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add2_m = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.CmdGear = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Constant = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.NewGear = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.b = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.J = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.N = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.IC = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.IC_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.IC_i = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_i = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Merge3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrCltchLoss = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.upi = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_i0 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_a = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Ratioofstatictokinetic = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory1_h = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory1_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch1_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_m = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.IC_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o1_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator1_o2_i = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.DataTypeConversion = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_mt = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_j = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.ApparentInertiaRatio = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchDamping = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.ApparentTransDamping = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add3_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.InputDamping = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_et = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_m = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.ApparentInertiaRatio_j = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum2_j = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_b = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum3_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_p = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TrqCmd = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_m = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_if = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_b = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Memory_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_h = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_c4 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_mv = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_mx = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract1_p = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add_a = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain_a = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.a_sim = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.v = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.diffDir = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.SumofElements = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_j = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_j = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_a = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_n = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_m = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_jk = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.diffDir_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain11 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Divide5 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_i = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_ab = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_b = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_dd = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.EngSpdFdbk_rpm_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Integrator_i4 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.RPMtodegs = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_i = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_jp = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_h = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain1_p = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sin_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain2_cz = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sin1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain5 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain4 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.mu_total = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Rx = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add_j = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnitDelay_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Eta1D = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PumpIntegrator = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_lu = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.w_out = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_h = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_g = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_mo = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss_p = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_a = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add2_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Gain_n = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TrigonometricFunction = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_ej = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_pe = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_j = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.T_ext = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add1_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchDamping_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.InputSum = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_p = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_ki = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans_n = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product10 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product_b = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add3_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_e = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.InputClutchInertia = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_j2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_m = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss_b = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Fcn = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_js = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Eta1D_p = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Abs_ck = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.omega = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_nc = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_n = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_d1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product5 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_gc = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Switch_j0 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product4_nt = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Subtract_a = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_c2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss_i = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product1_f3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product6 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.inputclutchDamping = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add1_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add2_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product3_mq = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Add3_o = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Sum_k0 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans_d = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product2_mi = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.UnaryMinus_b = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.Product8 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Lf = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.sum = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Saturation = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Divide = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Gain3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.th_f = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Ff = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Cos = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Lr = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.sum1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.th_r = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Gain1 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Fr = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Divide2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Divide3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.sum4 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Divide4 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Lf_2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Lr_2 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.sum5 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Gain1_l = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Sum = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Saturation_a = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.sum3 = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.inv_Iz = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Gain1_k = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Sum_c = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_B.TwoDofDynamic.Saturation_p = 0.0;
  }

  // exported global signals
  throttle_pct = 0.0;
  Velong_kph = 0.0;
  Yaw_deg = 0.0;
  YawRate_dps = 0.0;
  Velate_kph = 0.0;
  ax_mps2 = 0.0;
  Vx_kph = 0.0;
  Vy_kph = 0.0;
  X = 0.0;
  Y = 0.0;

  // states (continuous)
  {
    (void) std::memset(static_cast<void *>(&CNHTC_VEHICLE_MODEL_PureSL_X), 0,
                       sizeof(X_CNHTC_VEHICLE_MODEL_PureSL_T));
  }

  // Periodic continuous states
  {
    (void) std::memset(static_cast<void*>
                       (CNHTC_VEHICLE_MODEL_PureSL_PeriodicIndX), 0,
                       1*sizeof(int_T));
    (void) std::memset(static_cast<void*>
                       (CNHTC_VEHICLE_MODEL_PureSL_PeriodicRngX), 0,
                       2*sizeof(real_T));
  }

  // states (dwork)
  (void) std::memset(static_cast<void *>(&CNHTC_VEHICLE_MODEL_PureSL_DW), 0,
                     sizeof(DW_CNHTC_VEHICLE_MODEL_PureSL_T));
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay1_DSTATE = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay3_DSTATE = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay4_DSTATE = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay_DSTATE = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay1_DSTATE_h = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay_DSTATE_i = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory3_PreviousInput = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_a = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput_b = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput_p = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory2_PreviousInput = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_p = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_c = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.TwoDofDynamic.UnitDelay_DSTATE = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_DW.TwoDofDynamic.UnitDelay_DSTATE_j = 0.0;

  // external inputs
  pedalPos_pct = 0.0;
  XBR1_ExternalAccele = 0.0;
  SteerWhAngle_rad = 0.0;
  Grade_deg = 0.0;
  XBR1_Ctrl_Mode = 0.0;

  // external outputs
  (void) std::memset(static_cast<void *>(&CNHTC_VEHICLE_MODEL_PureSL_Y), 0,
                     sizeof(ExtY_CNHTC_VEHICLE_MODEL_PureSL_T));
  CNHTC_VEHICLE_MODEL_PureSL_Y.GearPos = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.EngTrq_Nm = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.EngSpd_rpm = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.engine_torque_loss_percent = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.engine_torque_percent = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.Velong_kph_p = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.Yaw_deg_n = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.Omega_w_rads = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.ax_mps2_f = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.Vx_kph_e = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.Vy_kph_a = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.X_p = 0.0;
  CNHTC_VEHICLE_MODEL_PureSL_Y.Y_h = 0.0;

  // Model Initialize function for ModelReference Block: '<S1>/Brake_System'

  // Set error status pointer for ModelReference Block: '<S1>/Brake_System'
  Brake_SystemMDLOBJ1.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&CNHTC_VEHICLE_MODEL_PureSL_M)));
  Brake_SystemMDLOBJ1.initialize();

  // Model Initialize function for ModelReference Block: '<S3>/Engine_ECU'

  // Set error status pointer for ModelReference Block: '<S3>/Engine_ECU'
  Engine_ECUMDLOBJ2.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&CNHTC_VEHICLE_MODEL_PureSL_M)));
  Engine_ECUMDLOBJ2.initialize();

  // Model Initialize function for ModelReference Block: '<S3>/TCU'

  // Set error status pointer for ModelReference Block: '<S3>/TCU'
  TCUMDLOBJ3.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&CNHTC_VEHICLE_MODEL_PureSL_M)));
  TCUMDLOBJ3.initialize();

  // Model Initialize function for ModelReference Block: '<S1>/SteerWhlMdl'

  // Set error status pointer for ModelReference Block: '<S1>/SteerWhlMdl'
  SteerWhlMdlMDLOBJ4.setErrorStatusPointer(rtmGetErrorStatusPointer
    ((&CNHTC_VEHICLE_MODEL_PureSL_M)));
  SteerWhlMdlMDLOBJ4.initialize();

  // Start for Constant: '<S2>/Constant1'
  CNHTC_VEHICLE_MODEL_PureSL_B.Constant1 = rtP_VEH.InitialLongVel;

  // Start for Constant: '<S2>/Constant4'
  CNHTC_VEHICLE_MODEL_PureSL_B.Constant4 = rtP_VEH.InitialYawAngle;

  // Start for Constant: '<S117>/domega_o'
  CNHTC_VEHICLE_MODEL_PureSL_B.domega_o =
    CNHTC_VEHICLE_MODEL_PureSL_P.PropShaft_domega_o;

  // Start for Constant: '<S38>/Constant'
  CNHTC_VEHICLE_MODEL_PureSL_B.Constant =
    CNHTC_VEHICLE_MODEL_PureSL_P.Constant_Value_kv;

  // Start for InitialCondition: '<S17>/IC'
  CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime = true;

  // Start for InitialCondition: '<S18>/IC'
  CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_p = true;

  // Start for InitialCondition: '<S16>/IC'
  CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_c = true;

  // Start for If: '<S10>/If'
  CNHTC_VEHICLE_MODEL_PureSL_DW.If_ActiveSubsystem = -1;

  // Start for InitialCondition: '<S40>/IC'
  CNHTC_VEHICLE_MODEL_PureSL_B.IC_o = CNHTC_VEHICLE_MODEL_PureSL_P.IC_Value_a;
  CNHTC_VEHICLE_MODEL_PureSL_DW.IC_FirstOutputTime_d = true;

  // Start for Constant: '<S88>/domega_o'
  CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_o =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance2_domega_o;

  // Start for Constant: '<S80>/domega_o'
  CNHTC_VEHICLE_MODEL_PureSL_B.domega_o_h =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance1_domega_o;
  CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;
  CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator1_Reset_ZCE = UNINITIALIZED_ZCSIG;
  CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.VelocitiesMatch_Input_ZCE =
    UNINITIALIZED_ZCSIG;
  CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator_Reset_ZCE_g =
    UNINITIALIZED_ZCSIG;
  CNHTC_VEHICLE_MODEL_PureSL_PrevZCX.Integrator_Reset_ZCE_a =
    UNINITIALIZED_ZCSIG;

  // InitializeConditions for UnitDelay: '<S3>/Unit Delay1'
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay1_DSTATE =
    CNHTC_VEHICLE_MODEL_PureSL_P.UnitDelay1_InitialCondition;

  // InitializeConditions for Integrator: '<S5>/Integrator1'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE =
    CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_IC;

  // InitializeConditions for UnitDelay: '<S3>/Unit Delay3'
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay3_DSTATE =
    CNHTC_VEHICLE_MODEL_PureSL_P.UnitDelay3_InitialCondition;

  // InitializeConditions for UnitDelay: '<S3>/Unit Delay4'
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay4_DSTATE =
    CNHTC_VEHICLE_MODEL_PureSL_P.UnitDelay4_InitialCondition;

  // InitializeConditions for UnitDelay: '<S3>/Unit Delay2'
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay2_DSTATE =
    CNHTC_VEHICLE_MODEL_PureSL_P.UnitDelay2_InitialCondition;

  // InitializeConditions for Integrator: '<S2>/Integrator' incorporates:
  //   Integrator: '<S2>/Integrator1'

  if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_h = 0.0;
  }

  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK = 1;

  // End of InitializeConditions for Integrator: '<S2>/Integrator'

  // InitializeConditions for Integrator: '<S2>/Integrator1'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK = 1;

  // InitializeConditions for UnitDelay: '<S2>/Unit Delay'
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay_DSTATE =
    CNHTC_VEHICLE_MODEL_PureSL_P.UnitDelay_InitialCondition;

  // InitializeConditions for UnitDelay: '<Root>/Unit Delay1'
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay1_DSTATE_h =
    CNHTC_VEHICLE_MODEL_PureSL_P.UnitDelay1_InitialCondition_o;

  // InitializeConditions for Integrator: '<Root>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_l =
    CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_IC;

  // InitializeConditions for Integrator: '<Root>/Integrator1'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_o =
    CNHTC_VEHICLE_MODEL_PureSL_P.Integrator1_IC_d;

  // InitializeConditions for Memory: '<S47>/Memory'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_j =
    CNHTC_VEHICLE_MODEL_PureSL_P.Memory_InitialCondition_b;

  // InitializeConditions for Memory: '<S118>/Memory'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput =
    CNHTC_VEHICLE_MODEL_PureSL_P.Memory_InitialCondition;

  // InitializeConditions for Integrator: '<S118>/Integrator' incorporates:
  //   Integrator: '<S38>/Integrator1'

  if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_m = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_d = 0.0;
  }

  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_j = 1;

  // End of InitializeConditions for Integrator: '<S118>/Integrator'

  // InitializeConditions for Integrator: '<S117>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_d =
    CNHTC_VEHICLE_MODEL_PureSL_P.PropShaft_theta_o;

  // InitializeConditions for Integrator: '<S31>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_df =
    CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_IC_m;

  // InitializeConditions for UnitDelay: '<Root>/Unit Delay'
  CNHTC_VEHICLE_MODEL_PureSL_DW.UnitDelay_DSTATE_i =
    CNHTC_VEHICLE_MODEL_PureSL_P.UnitDelay_InitialCondition_f;

  // InitializeConditions for Memory: '<S35>/Memory3'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory3_PreviousInput = rtP_VEH.InitGearPos;

  // InitializeConditions for Memory: '<S35>/Memory'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_a = rtP_VEH.InitGearPos;

  // InitializeConditions for Memory: '<S35>/Memory1'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput = rtP_VEH.InitGearPos;

  // InitializeConditions for Integrator: '<S38>/Integrator1'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK_a = 1;

  // InitializeConditions for Memory: '<S40>/Memory2'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory2_PreviousInput_d =
    CNHTC_VEHICLE_MODEL_PureSL_P.AutomatedManualTransmission_SynchLocked;

  // InitializeConditions for Memory: '<S38>/Memory1'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput_b =
    CNHTC_VEHICLE_MODEL_PureSL_P.Memory1_InitialCondition;

  // InitializeConditions for Memory: '<S39>/Memory1'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory1_PreviousInput_p =
    CNHTC_VEHICLE_MODEL_PureSL_P.Memory1_InitialCondition_d;

  // InitializeConditions for Memory: '<S38>/Memory2'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory2_PreviousInput =
    CNHTC_VEHICLE_MODEL_PureSL_P.Memory2_InitialCondition;

  // InitializeConditions for Integrator: '<S40>/Integrator1' incorporates:
  //   Integrator: '<S89>/Integrator'

  if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator1_CSTATE_de = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_k = 0.0;
  }

  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator1_IWORK_j = 1;

  // End of InitializeConditions for Integrator: '<S40>/Integrator1'

  // InitializeConditions for Memory: '<S44>/Memory'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_k =
    CNHTC_VEHICLE_MODEL_PureSL_P.Memory_InitialCondition_h;

  // InitializeConditions for Memory: '<S89>/Memory'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_p =
    CNHTC_VEHICLE_MODEL_PureSL_P.Memory_InitialCondition_o;

  // InitializeConditions for Integrator: '<S89>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_i = 1;

  // InitializeConditions for Integrator: '<S88>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_b =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance2_theta_o;

  // InitializeConditions for Memory: '<S81>/Memory'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Memory_PreviousInput_c =
    CNHTC_VEHICLE_MODEL_PureSL_P.Memory_InitialCondition_g;

  // InitializeConditions for Integrator: '<S81>/Integrator' incorporates:
  //   Integrator: '<S63>/Integrator'

  if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_i = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[0] = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_lv[1] = 0.0;
  }

  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_c = 1;

  // End of InitializeConditions for Integrator: '<S81>/Integrator'

  // InitializeConditions for Integrator: '<S80>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_d5 =
    CNHTC_VEHICLE_MODEL_PureSL_P.TorsionalCompliance1_theta_o;

  // InitializeConditions for Integrator: '<S6>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_o =
    CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_IC_j;

  // InitializeConditions for Integrator: '<S63>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_l = 1;

  // InitializeConditions for Integrator: '<S99>/Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_bf =
    CNHTC_VEHICLE_MODEL_PureSL_P.Integrator_IC_e;

  // SystemInitialize for Atomic SubSystem: '<S125>/TwoDofDynamic'
  CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_Init
    (&CNHTC_VEHICLE_MODEL_PureSL_DW.TwoDofDynamic,
     &CNHTC_VEHICLE_MODEL_PureSL_P.TwoDofDynamic);

  // End of SystemInitialize for SubSystem: '<S125>/TwoDofDynamic'

  // SystemInitialize for ModelReference: '<S1>/Brake_System' incorporates:
  //   Constant: '<S1>/Constant'
  //   Inport: '<Root>/XBR1_Ctrl_Mode'
  //   Inport: '<Root>/XBR1_ExternalAccele'

  Brake_SystemMDLOBJ1.init();

  // SystemInitialize for ModelReference: '<S3>/TCU' incorporates:
  //   Inport: '<Root>/pedalPos_pct'

  TCUMDLOBJ3.init(&CNHTC_VEHICLE_MODEL_PureSL_B.GearSel);

  // SystemInitialize for IfAction SubSystem: '<S10>/Unlocked'
  // SystemInitialize for IfAction SubSystem: '<S10>/Locked'
  // InitializeConditions for Integrator: '<S12>/Locked Shaft Integrator' incorporates:
  //   Integrator: '<S14>/Pump Integrator'

  if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    CNHTC_VEHICLE_MODEL_PureSL_X.LockedShaftIntegrator_CSTATE = 0.0;
    CNHTC_VEHICLE_MODEL_PureSL_X.PumpIntegrator_CSTATE = 0.0;
  }

  // End of SystemInitialize for SubSystem: '<S10>/Unlocked'
  CNHTC_VEHICLE_MODEL_PureSL_DW.LockedShaftIntegrator_IWORK = 1;

  // End of InitializeConditions for Integrator: '<S12>/Locked Shaft Integrator' 
  // End of SystemInitialize for SubSystem: '<S10>/Locked'

  // SystemInitialize for IfAction SubSystem: '<S10>/Unlocked'
  // InitializeConditions for Integrator: '<S14>/Pump Integrator'
  CNHTC_VEHICLE_MODEL_PureSL_DW.PumpIntegrator_IWORK = 1;

  // InitializeConditions for Integrator: '<S14>/Integrator'
  if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    CNHTC_VEHICLE_MODEL_PureSL_X.Integrator_CSTATE_kg = 0.0;
  }

  CNHTC_VEHICLE_MODEL_PureSL_DW.Integrator_IWORK_p = 1;

  // End of InitializeConditions for Integrator: '<S14>/Integrator'
  // End of SystemInitialize for SubSystem: '<S10>/Unlocked'

  // SystemInitialize for Merge generated from: '<S10>/Merge4'
  CNHTC_VEHICLE_MODEL_PureSL_B.PwrStoredTrans =
    CNHTC_VEHICLE_MODEL_PureSL_P.Merge4_1_InitialOutput;

  // SystemInitialize for Merge generated from: '<S10>/Merge4'
  CNHTC_VEHICLE_MODEL_PureSL_B.PwrCltchLoss =
    CNHTC_VEHICLE_MODEL_PureSL_P.Merge4_2_InitialOutput;

  // SystemInitialize for Merge generated from: '<S10>/Merge4'
  CNHTC_VEHICLE_MODEL_PureSL_B.PwrDampLoss =
    CNHTC_VEHICLE_MODEL_PureSL_P.Merge4_3_InitialOutput;

  // SystemInitialize for Merge generated from: '<S10>/Merge4'
  CNHTC_VEHICLE_MODEL_PureSL_B.PwrEffLoss =
    CNHTC_VEHICLE_MODEL_PureSL_P.Merge4_4_InitialOutput;

  // SystemInitialize for ModelReference: '<S3>/Engine_ECU' incorporates:
  //   Constant: '<S3>/Constant'
  //   Inport: '<Root>/pedalPos_pct'
  //   Outport: '<Root>/GearPos'

  Engine_ECUMDLOBJ2.init();

  // InitializeConditions for root-level periodic continuous states
  {
    int_T rootPeriodicContStateIndices[1] = { 17 };

    real_T rootPeriodicContStateRanges[2] = { 0.0, 720.0 };

    (void) std::memcpy((void*)CNHTC_VEHICLE_MODEL_PureSL_PeriodicIndX,
                       rootPeriodicContStateIndices,
                       1*sizeof(int_T));
    (void) std::memcpy((void*)CNHTC_VEHICLE_MODEL_PureSL_PeriodicRngX,
                       rootPeriodicContStateRanges,
                       2*sizeof(real_T));
  }

  // set "at time zero" to false
  if (rtmIsFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M))) {
    rtmSetFirstInitCond((&CNHTC_VEHICLE_MODEL_PureSL_M), 0);
  }
}

// Model terminate function
void CNHTC_VEHICLE_MODEL_PureSLModelClass::terminate()
{
  // (no terminate code required)
}

// Constructor
CNHTC_VEHICLE_MODEL_PureSLModelClass::CNHTC_VEHICLE_MODEL_PureSLModelClass() :
  CNHTC_VEHICLE_MODEL_PureSL_M()
{
  // Currently there is no constructor body generated.
}

// Destructor
CNHTC_VEHICLE_MODEL_PureSLModelClass::~CNHTC_VEHICLE_MODEL_PureSLModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
RT_MODEL_CNHTC_VEHICLE_MODEL_PureSL_T * CNHTC_VEHICLE_MODEL_PureSLModelClass::
  getRTM()
{
  return (&CNHTC_VEHICLE_MODEL_PureSL_M);
}

//
// File trailer for generated code.
//
// [EOF]
//
