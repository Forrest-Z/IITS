//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: Engine_ECU.cpp
//
// Code generated for Simulink model 'Engine_ECU'.
//
// Model version                  : 1.361
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Thu Aug  6 11:42:49 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#include "Engine_ECU.h"
#include "Engine_ECU_private.h"
#include "look1_binlcpw.h"
#include "look2_binlcapw.h"

// Named constants for Chart: '<Root>/EngineControl'
const uint8_T Engine_ECU_IN_ClutchDisconect = 1U;
const uint8_T Engine_ECU_IN_ClutchLocked = 1U;
const uint8_T Engine_ECU_IN_Idle = 2U;
const uint8_T Engine_ECU_IN_NO_ACTIVE_CHILD = 0U;
const uint8_T Engine_ECU_IN_ReduceFuel = 2U;
const uint8_T Engine_ECU_IN_Syncronize = 3U;
P_Engine_ECU_T Engine_ECUModelClass::Engine_ECU_rtP = {
  // Mask Parameter: RevLimiterControl_EngRevLim
  //  Referenced by: '<S3>/Constant'

  4500.0,

  // Mask Parameter: Syncronizecontrolspeed_Ki_idle
  //  Referenced by: '<S16>/I Gain'

  0.2,

  // Mask Parameter: Syncronizecontrolspeed_Kp_idle
  //  Referenced by: '<S16>/P Gain'

  0.05,

  // Mask Parameter: Syncronizecontrolspeed_N_idle
  //  Referenced by: '<S16>/Base Idle Speed'

  900.0,

  // Mask Parameter: Syncronizecontrolspeed_Trq_idlecmd_max
  //  Referenced by:
  //    '<S16>/Saturation'
  //    '<S16>/Saturation1'

  1500.0,

  // Mask Parameter: CompareToConstant_const
  //  Referenced by: '<S17>/Constant'

  220.0,

  // Mask Parameter: CompareToConstant1_const
  //  Referenced by: '<S18>/Constant'

  150.0,

  // Mask Parameter: CompareToConstant1_const_g
  //  Referenced by: '<S14>/Constant'

  1,

  // Mask Parameter: CompareToConstant_const_b
  //  Referenced by: '<S15>/Constant'

  2,

  // Expression: 1
  //  Referenced by: '<S8>/TrqCmd'

  1.0,

  // Expression: 0
  //  Referenced by: '<S16>/Unit Delay'

  0.0,

  // Expression: 0
  //  Referenced by: '<S16>/Saturation'

  0.0,

  // Expression: 200
  //  Referenced by: '<S16>/Constant1'

  200.0,

  // Expression: 0
  //  Referenced by: '<S16>/Saturation1'

  0.0,

  // Expression: 2000
  //  Referenced by: '<S2>/Constant4'

  2000.0,

  // Expression: 300
  //  Referenced by: '<S2>/Constant2'

  300.0,

  // Expression: -3000
  //  Referenced by: '<S2>/Constant3'

  -3000.0,

  // Expression: -800
  //  Referenced by: '<S2>/Constant1'

  -800.0,

  // Expression: [1 0]
  //  Referenced by: '<S3>/1-D Lookup Table'

  { 1.0, 0.0 },

  // Expression: [1 1.01]
  //  Referenced by: '<S3>/1-D Lookup Table'

  { 1.0, 1.01 },

  // Expression: 0
  //  Referenced by: '<S19>/Delay Input2'

  0.0,

  // Computed Parameter: sampletime_WtEt
  //  Referenced by: '<S19>/sample time'

  0.002,

  // Computed Parameter: torque_map1_maxIndex
  //  Referenced by: '<Root>/torque_map1'

  { 15U, 14U },

  // Computed Parameter: ShiftDoneTrg_Y0
  //  Referenced by: '<S6>/ShiftDoneTrg'

  0,

  // Computed Parameter: GearShiftTrg_Y0
  //  Referenced by: '<S7>/GearShiftTrg'

  0,

  // Computed Parameter: UnitDelay1_InitialCondition
  //  Referenced by: '<S7>/Unit Delay1'

  0,

  // Start of '<S1>/IdleSpdCtrl'
  {
    // Mask Parameter: idlecontrolspeed_Ki_idle
    //  Referenced by: '<S9>/I Gain'

    0.2,

    // Mask Parameter: idlecontrolspeed_Kp_idle
    //  Referenced by: '<S9>/P Gain'

    0.05,

    // Mask Parameter: idlecontrolspeed_N_idle
    //  Referenced by: '<S9>/Base Idle Speed'

    600.0,

    // Mask Parameter: idlecontrolspeed_Trq_idlecmd_max
    //  Referenced by:
    //    '<S9>/Saturation'
    //    '<S9>/Saturation1'

    500.0,

    // Expression: 1
    //  Referenced by: '<S4>/TrqCmd'

    1.0,

    // Expression: 0
    //  Referenced by: '<S9>/Unit Delay'

    0.0,

    // Expression: 0
    //  Referenced by: '<S9>/Saturation'

    0.0,

    // Expression: 200
    //  Referenced by: '<S9>/Constant1'

    200.0,

    // Expression: 0
    //  Referenced by: '<S9>/Saturation1'

    0.0
  }
  ,

  // End of '<S1>/IdleSpdCtrl'

  // Start of '<S1>/IdleTrgCal'
  {
    // Mask Parameter: CompareToConstant4_const
    //  Referenced by: '<S13>/Constant'

    1.0,

    // Mask Parameter: CompareToConstant1_const
    //  Referenced by: '<S10>/Constant'

    1.0,

    // Mask Parameter: CompareToConstant2_const
    //  Referenced by: '<S11>/Constant'

    0.1,

    // Mask Parameter: CompareToConstant3_const
    //  Referenced by: '<S12>/Constant'

    0.0,

    // Computed Parameter: Idle_Trg_Y0
    //  Referenced by: '<S5>/Idle_Trg'

    0,

    // Computed Parameter: UnitDelay_InitialCondition
    //  Referenced by: '<S5>/Unit Delay'

    0
  }
  // End of '<S1>/IdleTrgCal'
};

// System initialize for function-call system: '<S1>/IdleTrgCal'
void Engine_ECUModelClass::Engine_ECU_IdleTrgCal_Init(boolean_T *rty_Idle_Trg,
  DW_IdleTrgCal_Engine_ECU_T *localDW, P_IdleTrgCal_Engine_ECU_T *localP)
{
  // InitializeConditions for UnitDelay: '<S5>/Unit Delay'
  localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

  // SystemInitialize for Outport: '<S5>/Idle_Trg'
  *rty_Idle_Trg = localP->Idle_Trg_Y0;
}

// Output and update for function-call system: '<S1>/IdleTrgCal'
void Engine_ECUModelClass::Engine_ECU_IdleTrgCal(real_T rtu_TrqCmd, real_T
  rtu_VehSpd, real_T rtu_PedalPos_pct, real_T rtu_BrkCmd, boolean_T
  *rty_Idle_Trg, B_IdleTrgCal_Engine_ECU_T *localB, DW_IdleTrgCal_Engine_ECU_T
  *localDW, P_IdleTrgCal_Engine_ECU_T *localP)
{
  // RelationalOperator: '<S13>/Compare' incorporates:
  //   Constant: '<S13>/Constant'

  localB->Compare = (rtu_TrqCmd <= localP->CompareToConstant4_const);

  // RelationalOperator: '<S10>/Compare' incorporates:
  //   Constant: '<S10>/Constant'

  localB->Compare_b = (rtu_PedalPos_pct <= localP->CompareToConstant1_const);

  // Logic: '<S5>/AND'
  localB->AND = (localB->Compare && localB->Compare_b);

  // RelationalOperator: '<S11>/Compare' incorporates:
  //   Constant: '<S11>/Constant'

  localB->Compare_i = (rtu_VehSpd <= localP->CompareToConstant2_const);

  // RelationalOperator: '<S12>/Compare' incorporates:
  //   Constant: '<S12>/Constant'

  localB->Compare_k = (rtu_BrkCmd >= localP->CompareToConstant3_const);

  // UnitDelay: '<S5>/Unit Delay'
  localB->UnitDelay = localDW->UnitDelay_DSTATE;

  // Logic: '<S5>/AND2'
  localB->AND2 = (localB->Compare_k || localB->UnitDelay);

  // Logic: '<S5>/AND1'
  localB->AND1 = (localB->Compare_b && localB->Compare_i && localB->AND2);

  // Logic: '<S5>/AND3'
  *rty_Idle_Trg = (localB->AND && localB->AND1);

  // Update for UnitDelay: '<S5>/Unit Delay'
  localDW->UnitDelay_DSTATE = localB->AND1;
}

// System initialize for function-call system: '<S1>/IdleSpdCtrl'
void Engine_ECUModelClass::Engine_ECU_IdleSpdCtrl_Init(real_T *rty_TrqCmd,
  DW_IdleSpdCtrl_Engine_ECU_T *localDW, P_IdleSpdCtrl_Engine_ECU_T *localP)
{
  // InitializeConditions for UnitDelay: '<S9>/Unit Delay'
  localDW->UnitDelay_DSTATE = localP->UnitDelay_InitialCondition;

  // SystemInitialize for Outport: '<S4>/TrqCmd'
  *rty_TrqCmd = localP->TrqCmd_Y0;
}

// Disable for function-call system: '<S1>/IdleSpdCtrl'
void Engine_ECUModelClass::Engine_ECU_IdleSpdCtrl_Disable(real_T *rty_TrqCmd,
  P_IdleSpdCtrl_Engine_ECU_T *localP)
{
  // Disable for Outport: '<S4>/TrqCmd'
  *rty_TrqCmd = localP->TrqCmd_Y0;
}

// Output and update for function-call system: '<S1>/IdleSpdCtrl'
void Engine_ECUModelClass::Engine_ECU_IdleSpdCtrl(real_T rtu_EngSpd, real_T
  *rty_TrqCmd, B_IdleSpdCtrl_Engine_ECU_T *localB, DW_IdleSpdCtrl_Engine_ECU_T
  *localDW, P_IdleSpdCtrl_Engine_ECU_T *localP)
{
  real_T u0;
  real_T u1;
  real_T u2;

  // Sum: '<S9>/Add' incorporates:
  //   Constant: '<S9>/Base Idle Speed'

  localB->Add = localP->idlecontrolspeed_N_idle - rtu_EngSpd;

  // Gain: '<S9>/I Gain'
  localB->IGain = localP->idlecontrolspeed_Ki_idle * localB->Add;

  // Product: '<S9>/Product' incorporates:
  //   Constant: '<S9>/Constant'

  localB->Product = rtP_dt_ECU * localB->IGain;

  // UnitDelay: '<S9>/Unit Delay'
  localB->UnitDelay = localDW->UnitDelay_DSTATE;

  // Saturate: '<S9>/Saturation'
  u0 = localB->UnitDelay;
  u1 = localP->Saturation_LowerSat;
  u2 = localP->idlecontrolspeed_Trq_idlecmd_max;
  if (u0 > u2) {
    localB->Saturation = u2;
  } else if (u0 < u1) {
    localB->Saturation = u1;
  } else {
    localB->Saturation = u0;
  }

  // End of Saturate: '<S9>/Saturation'

  // Sum: '<S9>/Add1'
  localB->Add1 = localB->Product + localB->Saturation;

  // Gain: '<S9>/P Gain'
  localB->PGain = localP->idlecontrolspeed_Kp_idle * localB->Add;

  // Sum: '<S9>/Add2' incorporates:
  //   Constant: '<S9>/Constant1'

  localB->Add2 = (localB->Saturation + localB->PGain) + localP->Constant1_Value;

  // Saturate: '<S9>/Saturation1'
  u0 = localB->Add2;
  u1 = localP->Saturation1_LowerSat;
  u2 = localP->idlecontrolspeed_Trq_idlecmd_max;
  if (u0 > u2) {
    u0 = u2;
  } else {
    if (u0 < u1) {
      u0 = u1;
    }
  }

  *rty_TrqCmd = u0;

  // End of Saturate: '<S9>/Saturation1'

  // Update for UnitDelay: '<S9>/Unit Delay'
  localDW->UnitDelay_DSTATE = localB->Add1;
}

// System initialize for referenced model: 'Engine_ECU'
void Engine_ECUModelClass::init(void)
{
  // InitializeConditions for UnitDelay: '<S19>/Delay Input2'
  //
  //  Block description for '<S19>/Delay Input2':
  //
  //   Store in Global RAM

  Engine_ECU_DW.DelayInput2_DSTATE = Engine_ECU_rtP.DelayInput2_InitialCondition;
  Engine_ECU_DW.is_Syncronize = Engine_ECU_IN_NO_ACTIVE_CHILD;
  Engine_ECU_DW.temporalCounter_i1 = 0U;
  Engine_ECU_DW.is_active_c3_Engine_ECU = 0U;
  Engine_ECU_DW.is_c3_Engine_ECU = Engine_ECU_IN_NO_ACTIVE_CHILD;

  // SystemInitialize for Chart: '<Root>/EngineControl' incorporates:
  //   SubSystem: '<S1>/ShiftDoneCal'

  // SystemInitialize for Outport: '<S6>/ShiftDoneTrg'
  Engine_ECU_B.AND_j = Engine_ECU_rtP.ShiftDoneTrg_Y0;

  // SystemInitialize for Chart: '<Root>/EngineControl' incorporates:
  //   SubSystem: '<S1>/ShiftUpCal'

  // InitializeConditions for UnitDelay: '<S7>/Unit Delay1'
  Engine_ECU_DW.UnitDelay1_DSTATE = Engine_ECU_rtP.UnitDelay1_InitialCondition;

  // SystemInitialize for Outport: '<S7>/GearShiftTrg'
  Engine_ECU_B.AND = Engine_ECU_rtP.GearShiftTrg_Y0;

  // SystemInitialize for Chart: '<Root>/EngineControl' incorporates:
  //   SubSystem: '<S1>/IdleTrgCal'

  Engine_ECU_IdleTrgCal_Init(&Engine_ECU_B.AND3, &Engine_ECU_DW.IdleTrgCal,
    &Engine_ECU_rtP.IdleTrgCal);

  // SystemInitialize for Chart: '<Root>/EngineControl' incorporates:
  //   SubSystem: '<S1>/IdleSpdCtrl'

  Engine_ECU_IdleSpdCtrl_Init(&Engine_ECU_B.Saturation1_g,
    &Engine_ECU_DW.IdleSpdCtrl, &Engine_ECU_rtP.IdleSpdCtrl);

  // SystemInitialize for Chart: '<Root>/EngineControl' incorporates:
  //   SubSystem: '<S1>/SyncSpdCtrl'

  // InitializeConditions for UnitDelay: '<S16>/Unit Delay'
  Engine_ECU_DW.UnitDelay_DSTATE = Engine_ECU_rtP.UnitDelay_InitialCondition;

  // SystemInitialize for Outport: '<S8>/TrqCmd'
  Engine_ECU_B.Saturation1 = Engine_ECU_rtP.TrqCmd_Y0;
}

// Disable for referenced model: 'Engine_ECU'
void Engine_ECUModelClass::disable(void)
{
  // Disable for Chart: '<Root>/EngineControl' incorporates:
  //   SubSystem: '<S1>/IdleSpdCtrl'

  Engine_ECU_IdleSpdCtrl_Disable(&Engine_ECU_B.Saturation1_g,
    &Engine_ECU_rtP.IdleSpdCtrl);

  // Disable for Chart: '<Root>/EngineControl' incorporates:
  //   SubSystem: '<S1>/SyncSpdCtrl'

  // Disable for Outport: '<S8>/TrqCmd'
  Engine_ECU_B.Saturation1 = Engine_ECU_rtP.TrqCmd_Y0;
}

// Output and update for referenced model: 'Engine_ECU'
void Engine_ECUModelClass::step(const real_T *rtu_EngSpd_rpm, const real_T
  *rtu_VehSpd_kmph, const real_T *rtu_BrkCmd, const real_T *rtu_PedalPos_pct,
  const boolean_T *rtu_ClutchLock, const real_T *rtu_GearSel, const real_T
  *rtu_GearPos, real_T *rty_TrqCmd)
{
  real_T u0;
  real_T u1;
  real_T u2;

  // DataTypeConversion: '<Root>/Data Type Conversion'
  u0 = std::floor(*rtu_GearSel);
  if (rtIsNaN(u0) || rtIsInf(u0)) {
    u0 = 0.0;
  } else {
    u0 = std::fmod(u0, 256.0);
  }

  Engine_ECU_B.DataTypeConversion = static_cast<int8_T>((u0 < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-u0)))) : static_cast<int32_T>(static_cast<int8_T>(
    static_cast<uint8_T>(u0)))));

  // End of DataTypeConversion: '<Root>/Data Type Conversion'

  // DataTypeConversion: '<Root>/Data Type Conversion1'
  u0 = std::floor(*rtu_GearPos);
  if (rtIsNaN(u0) || rtIsInf(u0)) {
    u0 = 0.0;
  } else {
    u0 = std::fmod(u0, 256.0);
  }

  Engine_ECU_B.DataTypeConversion1 = static_cast<int8_T>((u0 < 0.0 ?
    static_cast<int32_T>(static_cast<int8_T>(-static_cast<int8_T>
    (static_cast<uint8_T>(-u0)))) : static_cast<int32_T>(static_cast<int8_T>(
    static_cast<uint8_T>(u0)))));

  // End of DataTypeConversion: '<Root>/Data Type Conversion1'

  // Lookup_n-D: '<Root>/torque_map1'
  Engine_ECU_B.torque_map1 = look2_binlcapw(*rtu_PedalPos_pct, *rtu_EngSpd_rpm,
    rtP_EngTorBp_ped, rtP_EngTorBp_ne, rtP_EngTorTable,
    Engine_ECU_rtP.torque_map1_maxIndex, 16U);

  // Chart: '<Root>/EngineControl'
  if (Engine_ECU_DW.temporalCounter_i1 < 511U) {
    Engine_ECU_DW.temporalCounter_i1 = static_cast<uint16_T>
      ((Engine_ECU_DW.temporalCounter_i1 + 1U));
  }

  // Gateway: EngineControl
  // During: EngineControl
  if (Engine_ECU_DW.is_active_c3_Engine_ECU == 0U) {
    // Entry: EngineControl
    Engine_ECU_DW.is_active_c3_Engine_ECU = 1U;

    // Entry Internal: EngineControl
    // Transition: '<S1>:2'
    Engine_ECU_DW.is_c3_Engine_ECU = Engine_ECU_IN_ClutchLocked;

    // Entry 'ClutchLocked': '<S1>:3'
    // '<S1>:3:3' EngTor = TorCmd;
    Engine_ECU_B.EngTor = Engine_ECU_B.torque_map1;

    // '<S1>:3:4' GearShiftTrg = false;
    Engine_ECU_DW.GearShiftTrg = false;

    // '<S1>:3:5' Idle_Trg = false;
    Engine_ECU_DW.Idle_Trg = false;
  } else {
    switch (Engine_ECU_DW.is_c3_Engine_ECU) {
     case Engine_ECU_IN_ClutchLocked:
      // During 'ClutchLocked': '<S1>:3'
      // '<S1>:5:1' sf_internal_predicateOutput = GearShiftTrg;
      if (Engine_ECU_DW.GearShiftTrg) {
        // Transition: '<S1>:5'
        Engine_ECU_DW.is_c3_Engine_ECU = Engine_ECU_IN_Syncronize;

        // Entry 'Syncronize': '<S1>:1'
        // '<S1>:1:3' ShiftDoneTrg = false;
        Engine_ECU_DW.ShiftDoneTrg = false;

        // '<S1>:1:4' Idle_Trg = false;
        Engine_ECU_DW.Idle_Trg = false;

        // Entry Internal 'Syncronize': '<S1>:1'
        // Transition: '<S1>:52'
        Engine_ECU_DW.is_Syncronize = Engine_ECU_IN_ReduceFuel;
        Engine_ECU_DW.temporalCounter_i1 = 0U;

        // Entry 'ReduceFuel': '<S1>:51'
      } else {
        // '<S1>:32:1' sf_internal_predicateOutput = Idle_Trg;
        if (Engine_ECU_DW.Idle_Trg) {
          // Transition: '<S1>:32'
          Engine_ECU_DW.is_c3_Engine_ECU = Engine_ECU_IN_Idle;

          // Entry 'Idle': '<S1>:22'
          // '<S1>:22:3' EngTor = IdleSpdCtrl(EngSpd);
          // Simulink Function 'IdleSpdCtrl': '<S1>:23'
          Engine_ECU_B.EngSpd = *rtu_EngSpd_rpm;

          // Outputs for Function Call SubSystem: '<S1>/IdleSpdCtrl'
          Engine_ECU_IdleSpdCtrl(Engine_ECU_B.EngSpd,
            &Engine_ECU_B.Saturation1_g, &Engine_ECU_B.IdleSpdCtrl,
            &Engine_ECU_DW.IdleSpdCtrl, &Engine_ECU_rtP.IdleSpdCtrl);

          // End of Outputs for SubSystem: '<S1>/IdleSpdCtrl'
          Engine_ECU_B.EngTor = Engine_ECU_B.Saturation1_g;
        } else {
          // '<S1>:3:7' EngTor = TorCmd;
          Engine_ECU_B.EngTor = Engine_ECU_B.torque_map1;

          // '<S1>:3:8' GearShiftTrg = ShiftUpCal(GearSel);
          // Simulink Function 'ShiftUpCal': '<S1>:10'
          Engine_ECU_B.GearSel_d = Engine_ECU_B.DataTypeConversion;

          // Outputs for Function Call SubSystem: '<S1>/ShiftUpCal'
          // UnitDelay: '<S7>/Unit Delay1'
          Engine_ECU_B.UnitDelay1 = Engine_ECU_DW.UnitDelay1_DSTATE;

          // RelationalOperator: '<S7>/Relational Operator1'
          Engine_ECU_B.RelationalOperator1 = (Engine_ECU_B.GearSel_d !=
            Engine_ECU_B.UnitDelay1);

          // RelationalOperator: '<S15>/Compare' incorporates:
          //   Constant: '<S15>/Constant'

          Engine_ECU_B.Compare_o = (Engine_ECU_B.GearSel_d >
            Engine_ECU_rtP.CompareToConstant_const_b);

          // Logic: '<S7>/AND'
          Engine_ECU_B.AND = (Engine_ECU_B.RelationalOperator1 &&
                              Engine_ECU_B.Compare_o);

          // Update for UnitDelay: '<S7>/Unit Delay1'
          Engine_ECU_DW.UnitDelay1_DSTATE = Engine_ECU_B.GearSel_d;

          // End of Outputs for SubSystem: '<S1>/ShiftUpCal'
          Engine_ECU_DW.GearShiftTrg = Engine_ECU_B.AND;

          // '<S1>:3:9' Idle_Trg = IdleTrgCal(EngTor,VehSpd,BrkCmd,PedalPos_pct); 
          // Simulink Function 'IdleTrgCal': '<S1>:26'
          Engine_ECU_B.TrqCmd = Engine_ECU_B.EngTor;
          Engine_ECU_B.VehSpd = *rtu_VehSpd_kmph;
          Engine_ECU_B.PedalPos_pct = *rtu_BrkCmd;
          Engine_ECU_B.BrkCmd = *rtu_PedalPos_pct;

          // Outputs for Function Call SubSystem: '<S1>/IdleTrgCal'
          Engine_ECU_IdleTrgCal(Engine_ECU_B.TrqCmd, Engine_ECU_B.VehSpd,
                                Engine_ECU_B.PedalPos_pct, Engine_ECU_B.BrkCmd,
                                &Engine_ECU_B.AND3, &Engine_ECU_B.IdleTrgCal,
                                &Engine_ECU_DW.IdleTrgCal,
                                &Engine_ECU_rtP.IdleTrgCal);

          // End of Outputs for SubSystem: '<S1>/IdleTrgCal'
          Engine_ECU_DW.Idle_Trg = Engine_ECU_B.AND3;

          // '<S1>:3:10' EngStatus = 1;
          Engine_ECU_B.EngStatus = 1.0;
        }
      }
      break;

     case Engine_ECU_IN_Idle:
      // During 'Idle': '<S1>:22'
      // '<S1>:38:1' sf_internal_predicateOutput = Idle_Trg<1;
      if (!Engine_ECU_DW.Idle_Trg) {
        // Transition: '<S1>:38'
        Engine_ECU_DW.is_c3_Engine_ECU = Engine_ECU_IN_ClutchLocked;

        // Entry 'ClutchLocked': '<S1>:3'
        // '<S1>:3:3' EngTor = TorCmd;
        Engine_ECU_B.EngTor = Engine_ECU_B.torque_map1;

        // '<S1>:3:4' GearShiftTrg = false;
        Engine_ECU_DW.GearShiftTrg = false;

        // '<S1>:3:5' Idle_Trg = false;
        Engine_ECU_DW.Idle_Trg = false;
      } else {
        // '<S1>:48:1' sf_internal_predicateOutput = Idle_Trg<1;
        if (!Engine_ECU_DW.Idle_Trg) {
          // Transition: '<S1>:48'
          Engine_ECU_DW.is_c3_Engine_ECU = Engine_ECU_IN_Syncronize;

          // Entry 'Syncronize': '<S1>:1'
          // '<S1>:1:3' ShiftDoneTrg = false;
          Engine_ECU_DW.ShiftDoneTrg = false;

          // '<S1>:1:4' Idle_Trg = false;
          Engine_ECU_DW.Idle_Trg = false;

          // Entry Internal 'Syncronize': '<S1>:1'
          // Transition: '<S1>:52'
          Engine_ECU_DW.is_Syncronize = Engine_ECU_IN_ReduceFuel;
          Engine_ECU_DW.temporalCounter_i1 = 0U;

          // Entry 'ReduceFuel': '<S1>:51'
        } else {
          // '<S1>:22:5' EngTor = IdleSpdCtrl(EngSpd);
          // Simulink Function 'IdleSpdCtrl': '<S1>:23'
          Engine_ECU_B.EngSpd = *rtu_EngSpd_rpm;

          // Outputs for Function Call SubSystem: '<S1>/IdleSpdCtrl'
          Engine_ECU_IdleSpdCtrl(Engine_ECU_B.EngSpd,
            &Engine_ECU_B.Saturation1_g, &Engine_ECU_B.IdleSpdCtrl,
            &Engine_ECU_DW.IdleSpdCtrl, &Engine_ECU_rtP.IdleSpdCtrl);

          // End of Outputs for SubSystem: '<S1>/IdleSpdCtrl'
          Engine_ECU_B.EngTor = Engine_ECU_B.Saturation1_g;

          // '<S1>:22:6' Idle_Trg = IdleTrgCal(EngTor,VehSpd,BrkCmd,PedalPos_pct); 
          // Simulink Function 'IdleTrgCal': '<S1>:26'
          Engine_ECU_B.TrqCmd = Engine_ECU_B.EngTor;
          Engine_ECU_B.VehSpd = *rtu_VehSpd_kmph;
          Engine_ECU_B.PedalPos_pct = *rtu_BrkCmd;
          Engine_ECU_B.BrkCmd = *rtu_PedalPos_pct;

          // Outputs for Function Call SubSystem: '<S1>/IdleTrgCal'
          Engine_ECU_IdleTrgCal(Engine_ECU_B.TrqCmd, Engine_ECU_B.VehSpd,
                                Engine_ECU_B.PedalPos_pct, Engine_ECU_B.BrkCmd,
                                &Engine_ECU_B.AND3, &Engine_ECU_B.IdleTrgCal,
                                &Engine_ECU_DW.IdleTrgCal,
                                &Engine_ECU_rtP.IdleTrgCal);

          // End of Outputs for SubSystem: '<S1>/IdleTrgCal'
          Engine_ECU_DW.Idle_Trg = Engine_ECU_B.AND3;

          // '<S1>:22:7' EngStatus = 0;
          Engine_ECU_B.EngStatus = 0.0;
        }
      }
      break;

     default:
      // During 'Syncronize': '<S1>:1'
      // '<S1>:4:1' sf_internal_predicateOutput = ShiftDoneTrg;
      if (Engine_ECU_DW.ShiftDoneTrg) {
        // Transition: '<S1>:4'
        // Exit Internal 'Syncronize': '<S1>:1'
        Engine_ECU_DW.is_Syncronize = Engine_ECU_IN_NO_ACTIVE_CHILD;
        Engine_ECU_DW.is_c3_Engine_ECU = Engine_ECU_IN_ClutchLocked;

        // Entry 'ClutchLocked': '<S1>:3'
        // '<S1>:3:3' EngTor = TorCmd;
        Engine_ECU_B.EngTor = Engine_ECU_B.torque_map1;

        // '<S1>:3:4' GearShiftTrg = false;
        Engine_ECU_DW.GearShiftTrg = false;

        // '<S1>:3:5' Idle_Trg = false;
        Engine_ECU_DW.Idle_Trg = false;
      } else {
        // '<S1>:47:1' sf_internal_predicateOutput = Idle_Trg;
        if (Engine_ECU_DW.Idle_Trg) {
          // Transition: '<S1>:47'
          // Exit Internal 'Syncronize': '<S1>:1'
          Engine_ECU_DW.is_Syncronize = Engine_ECU_IN_NO_ACTIVE_CHILD;
          Engine_ECU_DW.is_c3_Engine_ECU = Engine_ECU_IN_Idle;

          // Entry 'Idle': '<S1>:22'
          // '<S1>:22:3' EngTor = IdleSpdCtrl(EngSpd);
          // Simulink Function 'IdleSpdCtrl': '<S1>:23'
          Engine_ECU_B.EngSpd = *rtu_EngSpd_rpm;

          // Outputs for Function Call SubSystem: '<S1>/IdleSpdCtrl'
          Engine_ECU_IdleSpdCtrl(Engine_ECU_B.EngSpd,
            &Engine_ECU_B.Saturation1_g, &Engine_ECU_B.IdleSpdCtrl,
            &Engine_ECU_DW.IdleSpdCtrl, &Engine_ECU_rtP.IdleSpdCtrl);

          // End of Outputs for SubSystem: '<S1>/IdleSpdCtrl'
          Engine_ECU_B.EngTor = Engine_ECU_B.Saturation1_g;
        } else {
          // '<S1>:1:6' ShiftDoneTrg = ShiftDoneCal(GearSel,GearPos,ClutchLock); 
          // Simulink Function 'ShiftDoneCal': '<S1>:35'
          Engine_ECU_B.GearSel = Engine_ECU_B.DataTypeConversion;
          Engine_ECU_B.GearPos = Engine_ECU_B.DataTypeConversion1;
          Engine_ECU_B.ClutchLock = *rtu_ClutchLock;

          // Outputs for Function Call SubSystem: '<S1>/ShiftDoneCal'
          // RelationalOperator: '<S6>/Relational Operator'
          Engine_ECU_B.RelationalOperator = (Engine_ECU_B.GearSel ==
            Engine_ECU_B.GearPos);

          // RelationalOperator: '<S14>/Compare' incorporates:
          //   Constant: '<S14>/Constant'

          Engine_ECU_B.Compare_g = (Engine_ECU_B.ClutchLock ==
            Engine_ECU_rtP.CompareToConstant1_const_g);

          // Logic: '<S6>/AND'
          Engine_ECU_B.AND_j = (Engine_ECU_B.RelationalOperator &&
                                Engine_ECU_B.Compare_g);

          // End of Outputs for SubSystem: '<S1>/ShiftDoneCal'
          Engine_ECU_DW.ShiftDoneTrg = Engine_ECU_B.AND_j;

          // '<S1>:1:7' Idle_Trg = IdleTrgCal(EngTor,VehSpd,BrkCmd,PedalPos_pct); 
          // Simulink Function 'IdleTrgCal': '<S1>:26'
          Engine_ECU_B.TrqCmd = Engine_ECU_B.EngTor;
          Engine_ECU_B.VehSpd = *rtu_VehSpd_kmph;
          Engine_ECU_B.PedalPos_pct = *rtu_BrkCmd;
          Engine_ECU_B.BrkCmd = *rtu_PedalPos_pct;

          // Outputs for Function Call SubSystem: '<S1>/IdleTrgCal'
          Engine_ECU_IdleTrgCal(Engine_ECU_B.TrqCmd, Engine_ECU_B.VehSpd,
                                Engine_ECU_B.PedalPos_pct, Engine_ECU_B.BrkCmd,
                                &Engine_ECU_B.AND3, &Engine_ECU_B.IdleTrgCal,
                                &Engine_ECU_DW.IdleTrgCal,
                                &Engine_ECU_rtP.IdleTrgCal);

          // End of Outputs for SubSystem: '<S1>/IdleTrgCal'
          Engine_ECU_DW.Idle_Trg = Engine_ECU_B.AND3;

          // '<S1>:1:8' EngStatus = 2;
          Engine_ECU_B.EngStatus = 2.0;
          if (Engine_ECU_DW.is_Syncronize == Engine_ECU_IN_ClutchDisconect) {
            // During 'ClutchDisconect': '<S1>:53'
            // '<S1>:53:2' EngTor = 0;
            Engine_ECU_B.EngTor = 0.0;
          } else {
            // During 'ReduceFuel': '<S1>:51'
            // '<S1>:59:1' sf_internal_predicateOutput = after(0.7,sec);
            if (Engine_ECU_DW.temporalCounter_i1 >= 350U) {
              // Transition: '<S1>:59'
              Engine_ECU_DW.is_Syncronize = Engine_ECU_IN_ClutchDisconect;

              // Entry 'ClutchDisconect': '<S1>:53'
            } else {
              // '<S1>:51:3' EngTor = SyncSpdCtrl(EngSpd,TorCmd);
              // Simulink Function 'SyncSpdCtrl': '<S1>:58'
              Engine_ECU_B.EngSpd_f = *rtu_EngSpd_rpm;
              Engine_ECU_B.EngTorCur_Nm = Engine_ECU_B.torque_map1;

              // Outputs for Function Call SubSystem: '<S1>/SyncSpdCtrl'
              // Sum: '<S16>/Add' incorporates:
              //   Constant: '<S16>/Base Idle Speed'

              Engine_ECU_B.Add = Engine_ECU_rtP.Syncronizecontrolspeed_N_idle -
                Engine_ECU_B.EngSpd_f;

              // Gain: '<S16>/I Gain'
              Engine_ECU_B.IGain = Engine_ECU_rtP.Syncronizecontrolspeed_Ki_idle
                * Engine_ECU_B.Add;

              // Product: '<S16>/Product' incorporates:
              //   Constant: '<S16>/Constant'

              Engine_ECU_B.Product_c = rtP_dt_ECU * Engine_ECU_B.IGain;

              // UnitDelay: '<S16>/Unit Delay'
              Engine_ECU_B.UnitDelay = Engine_ECU_DW.UnitDelay_DSTATE;

              // Saturate: '<S16>/Saturation'
              u0 = Engine_ECU_B.UnitDelay;
              u1 = Engine_ECU_rtP.Saturation_LowerSat;
              u2 = Engine_ECU_rtP.Syncronizecontrolspeed_Trq_idlecmd_max;
              if (u0 > u2) {
                Engine_ECU_B.Saturation = u2;
              } else if (u0 < u1) {
                Engine_ECU_B.Saturation = u1;
              } else {
                Engine_ECU_B.Saturation = u0;
              }

              // End of Saturate: '<S16>/Saturation'

              // Sum: '<S16>/Add1'
              Engine_ECU_B.Add1 = Engine_ECU_B.Product_c +
                Engine_ECU_B.Saturation;

              // Gain: '<S16>/P Gain'
              Engine_ECU_B.PGain = Engine_ECU_rtP.Syncronizecontrolspeed_Kp_idle
                * Engine_ECU_B.Add;

              // Sum: '<S16>/Add2' incorporates:
              //   Constant: '<S16>/Constant1'

              Engine_ECU_B.Add2 = (Engine_ECU_B.Saturation + Engine_ECU_B.PGain)
                + Engine_ECU_rtP.Constant1_Value;

              // Saturate: '<S16>/Saturation1'
              u0 = Engine_ECU_B.Add2;
              u1 = Engine_ECU_rtP.Saturation1_LowerSat;
              u2 = Engine_ECU_rtP.Syncronizecontrolspeed_Trq_idlecmd_max;
              if (u0 > u2) {
                Engine_ECU_B.Saturation1 = u2;
              } else if (u0 < u1) {
                Engine_ECU_B.Saturation1 = u1;
              } else {
                Engine_ECU_B.Saturation1 = u0;
              }

              // End of Saturate: '<S16>/Saturation1'

              // Update for UnitDelay: '<S16>/Unit Delay'
              Engine_ECU_DW.UnitDelay_DSTATE = Engine_ECU_B.Add1;

              // End of Outputs for SubSystem: '<S1>/SyncSpdCtrl'
              Engine_ECU_B.EngTor = Engine_ECU_B.Saturation1;
            }
          }
        }
      }
      break;
    }
  }

  // End of Chart: '<Root>/EngineControl'

  // Product: '<S3>/Product1' incorporates:
  //   Constant: '<S3>/Constant'

  Engine_ECU_B.Product1 = *rtu_EngSpd_rpm /
    Engine_ECU_rtP.RevLimiterControl_EngRevLim;

  // Lookup_n-D: '<S3>/1-D Lookup Table'
  Engine_ECU_B.uDLookupTable = look1_binlcpw(Engine_ECU_B.Product1,
    Engine_ECU_rtP.uDLookupTable_bp01Data,
    Engine_ECU_rtP.uDLookupTable_tableData, 1U);

  // Product: '<S3>/Product'
  Engine_ECU_B.Product = Engine_ECU_B.EngTor * Engine_ECU_B.uDLookupTable;

  // RelationalOperator: '<S17>/Compare' incorporates:
  //   Constant: '<S17>/Constant'

  Engine_ECU_B.Compare = (Engine_ECU_B.Product >=
    Engine_ECU_rtP.CompareToConstant_const);

  // UnitDelay: '<S19>/Delay Input2'
  //
  //  Block description for '<S19>/Delay Input2':
  //
  //   Store in Global RAM

  Engine_ECU_B.Yk1 = Engine_ECU_DW.DelayInput2_DSTATE;

  // Sum: '<S19>/Difference Inputs1'
  //
  //  Block description for '<S19>/Difference Inputs1':
  //
  //   Add in CPU

  Engine_ECU_B.UkYk1 = Engine_ECU_B.Product - Engine_ECU_B.Yk1;

  // Switch: '<S2>/Switch2' incorporates:
  //   Constant: '<S2>/Constant2'
  //   Constant: '<S2>/Constant4'

  if (Engine_ECU_B.Compare) {
    Engine_ECU_B.Switch2 = Engine_ECU_rtP.Constant2_Value;
  } else {
    Engine_ECU_B.Switch2 = Engine_ECU_rtP.Constant4_Value;
  }

  // End of Switch: '<S2>/Switch2'

  // SampleTimeMath: '<S19>/sample time'
  //
  //  About '<S19>/sample time':
  //   y = K where K = ( w * Ts )

  Engine_ECU_B.sampletime = Engine_ECU_rtP.sampletime_WtEt;

  // Product: '<S19>/delta rise limit'
  Engine_ECU_B.deltariselimit = Engine_ECU_B.Switch2 * Engine_ECU_B.sampletime;

  // RelationalOperator: '<S20>/LowerRelop1'
  Engine_ECU_B.LowerRelop1 = (Engine_ECU_B.UkYk1 > Engine_ECU_B.deltariselimit);

  // Switch: '<S20>/Switch2'
  if (Engine_ECU_B.LowerRelop1) {
    Engine_ECU_B.Switch2_d = Engine_ECU_B.deltariselimit;
  } else {
    // RelationalOperator: '<S18>/Compare' incorporates:
    //   Constant: '<S18>/Constant'

    Engine_ECU_B.Compare_f = (Engine_ECU_B.Product >=
      Engine_ECU_rtP.CompareToConstant1_const);

    // Switch: '<S2>/Switch1' incorporates:
    //   Constant: '<S2>/Constant1'
    //   Constant: '<S2>/Constant3'

    if (Engine_ECU_B.Compare_f) {
      Engine_ECU_B.Switch1 = Engine_ECU_rtP.Constant1_Value_b;
    } else {
      Engine_ECU_B.Switch1 = Engine_ECU_rtP.Constant3_Value;
    }

    // End of Switch: '<S2>/Switch1'

    // Product: '<S19>/delta fall limit'
    Engine_ECU_B.deltafalllimit = Engine_ECU_B.Switch1 * Engine_ECU_B.sampletime;

    // RelationalOperator: '<S20>/UpperRelop'
    Engine_ECU_B.UpperRelop = (Engine_ECU_B.UkYk1 < Engine_ECU_B.deltafalllimit);

    // Switch: '<S20>/Switch'
    if (Engine_ECU_B.UpperRelop) {
      Engine_ECU_B.Switch = Engine_ECU_B.deltafalllimit;
    } else {
      Engine_ECU_B.Switch = Engine_ECU_B.UkYk1;
    }

    // End of Switch: '<S20>/Switch'
    Engine_ECU_B.Switch2_d = Engine_ECU_B.Switch;
  }

  // End of Switch: '<S20>/Switch2'

  // Sum: '<S19>/Difference Inputs2'
  //
  //  Block description for '<S19>/Difference Inputs2':
  //
  //   Add in CPU

  *rty_TrqCmd = Engine_ECU_B.Switch2_d + Engine_ECU_B.Yk1;

  // Update for UnitDelay: '<S19>/Delay Input2'
  //
  //  Block description for '<S19>/Delay Input2':
  //
  //   Store in Global RAM

  Engine_ECU_DW.DelayInput2_DSTATE = *rty_TrqCmd;
}

// Model initialize function
void Engine_ECUModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // block I/O
  (void) std::memset((static_cast<void *>(&Engine_ECU_B)), 0,
                     sizeof(B_Engine_ECU_T));

  {
    Engine_ECU_B.torque_map1 = 0.0;
    Engine_ECU_B.Product1 = 0.0;
    Engine_ECU_B.uDLookupTable = 0.0;
    Engine_ECU_B.Product = 0.0;
    Engine_ECU_B.Yk1 = 0.0;
    Engine_ECU_B.UkYk1 = 0.0;
    Engine_ECU_B.Switch2 = 0.0;
    Engine_ECU_B.sampletime = 0.0;
    Engine_ECU_B.deltariselimit = 0.0;
    Engine_ECU_B.Switch2_d = 0.0;
    Engine_ECU_B.Switch1 = 0.0;
    Engine_ECU_B.deltafalllimit = 0.0;
    Engine_ECU_B.Switch = 0.0;
    Engine_ECU_B.EngTor = 0.0;
    Engine_ECU_B.EngStatus = 0.0;
    Engine_ECU_B.TrqCmd = 0.0;
    Engine_ECU_B.VehSpd = 0.0;
    Engine_ECU_B.PedalPos_pct = 0.0;
    Engine_ECU_B.BrkCmd = 0.0;
    Engine_ECU_B.EngSpd = 0.0;
    Engine_ECU_B.EngSpd_f = 0.0;
    Engine_ECU_B.EngTorCur_Nm = 0.0;
    Engine_ECU_B.Add = 0.0;
    Engine_ECU_B.IGain = 0.0;
    Engine_ECU_B.Product_c = 0.0;
    Engine_ECU_B.UnitDelay = 0.0;
    Engine_ECU_B.Saturation = 0.0;
    Engine_ECU_B.Add1 = 0.0;
    Engine_ECU_B.PGain = 0.0;
    Engine_ECU_B.Add2 = 0.0;
    Engine_ECU_B.Saturation1 = 0.0;
    Engine_ECU_B.Saturation1_g = 0.0;
    Engine_ECU_B.IdleSpdCtrl.Add = 0.0;
    Engine_ECU_B.IdleSpdCtrl.IGain = 0.0;
    Engine_ECU_B.IdleSpdCtrl.Product = 0.0;
    Engine_ECU_B.IdleSpdCtrl.UnitDelay = 0.0;
    Engine_ECU_B.IdleSpdCtrl.Saturation = 0.0;
    Engine_ECU_B.IdleSpdCtrl.Add1 = 0.0;
    Engine_ECU_B.IdleSpdCtrl.PGain = 0.0;
    Engine_ECU_B.IdleSpdCtrl.Add2 = 0.0;
  }

  // states (dwork)
  (void) std::memset(static_cast<void *>(&Engine_ECU_DW), 0,
                     sizeof(DW_Engine_ECU_T));
  Engine_ECU_DW.DelayInput2_DSTATE = 0.0;
  Engine_ECU_DW.UnitDelay_DSTATE = 0.0;
  Engine_ECU_DW.IdleSpdCtrl.UnitDelay_DSTATE = 0.0;
}

// Constructor
Engine_ECUModelClass::Engine_ECUModelClass()
{
  // Currently there is no constructor body generated.
}

// Destructor
Engine_ECUModelClass::~Engine_ECUModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
RT_MODEL_Engine_ECU_T * Engine_ECUModelClass::getRTM()
{
  return (&Engine_ECU_M);
}

// member function to setup error status pointer
void Engine_ECUModelClass::setErrorStatusPointer(const char_T **rt_errorStatus)
{
  rtmSetErrorStatusPointer((&Engine_ECU_M), rt_errorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
