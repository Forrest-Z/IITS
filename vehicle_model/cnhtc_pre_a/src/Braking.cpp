//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: Braking.cpp
//
// Code generated for Simulink model 'Braking'.
//
// Model version                  : 1.20
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:19 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#include "Braking.h"

#include "Braking_private.h"
#include "look1_binlcapw.h"
#include "look2_binlcapw.h"

P_Braking_T BrakingModelClass::Braking_rtP = {
    // Mask Parameter: CompareToConstant_const
    //  Referenced by: '<S4>/Constant'
    0.0,
    // Mask Parameter: CompareToConstant_const_n
    //  Referenced by: '<S16>/Constant'
    0.01,
    // Mask Parameter: CompareToConstant1_const
    //  Referenced by: '<S8>/Constant'
    0.001,
    // Mask Parameter: CompareToConstant2_const
    //  Referenced by: '<S9>/Constant'
    -0.001,
    // Mask Parameter: CompareToConstant1_const_l
    //  Referenced by: '<S10>/Constant'
    0.001,
    // Mask Parameter: CompareToConstant2_const_f
    //  Referenced by: '<S11>/Constant'
    -0.001,
    // Mask Parameter: CompareToConstant1_const_o
    //  Referenced by: '<S12>/Constant'
    0.001,
    // Mask Parameter: CompareToConstant2_const_h
    //  Referenced by: '<S13>/Constant'
    -0.001,
    // Mask Parameter: CompareToConstant_const_n5
    //  Referenced by: '<S19>/Constant'
    0.001,
    // Mask Parameter: CompareToConstant1_const_ld
    //  Referenced by: '<S20>/Constant'
    -0.001,
    // Mask Parameter: CompareToConstant2_const_j
    //  Referenced by: '<S21>/Constant'
    0.001,
    // Mask Parameter: CompareToConstant3_const
    //  Referenced by: '<S22>/Constant'
    -0.001,
    // Mask Parameter: CompareToConstant4_const
    //  Referenced by: '<S23>/Constant'
    0.001,
    // Mask Parameter: CompareToConstant5_const
    //  Referenced by: '<S24>/Constant'
    -0.001,
    // Expression: 0
    //  Referenced by: '<S1>/Constant3'
    0.0,
    // Expression: 1
    //  Referenced by: '<S1>/Constant'
    1.0,
    // Expression: 0
    //  Referenced by: '<S2>/Constant3'
    0.0,
    // Expression: 1
    //  Referenced by: '<S2>/Constant'
    1.0,
    // Expression: 0
    //  Referenced by: '<S3>/Constant3'
    0.0,
    // Expression: 1000
    //  Referenced by: '<S3>/Gain'
    1000.0,
    // Expression: 1
    //  Referenced by: '<S3>/Constant'
    1.0,
    // Expression: 0
    //  Referenced by: '<S14>/Constant1'
    0.0,
    // Expression: 0
    //  Referenced by: '<S14>/Constant2'
    0.0,
    // Expression: 1
    //  Referenced by: '<S14>/Kf'
    1.0,
    // Expression: 1
    //  Referenced by: '<S14>/Gain1'
    1.0,
    // Expression: 0
    //  Referenced by: '<S14>/Saturation'
    0.0,
    // Expression: -inf
    //  Referenced by: '<S14>/Saturation'
    0.0,
    // Expression: 1
    //  Referenced by: '<S14>/Gain6'
    1.0,
    // Expression: 0
    //  Referenced by: '<S14>/Constant3'
    0.0,
    // Expression: 0
    //  Referenced by: '<S14>/Constant6'
    0.0,
    // Expression: 1500
    //  Referenced by: '<S6>/Constant13'
    1500.0,
    // Expression: 1500
    //  Referenced by: '<S6>/Constant11'
    1500.0,
    // Expression: 1500
    //  Referenced by: '<S6>/Constant'
    1500.0,
    // Expression: 0.01
    //  Referenced by: '<S6>/Constant3'
    0.01,
    // Expression: 0
    //  Referenced by: '<S6>/Constant2'
    0.0,
    // Expression: 0
    //  Referenced by: '<S6>/Constant1'
    0.0,
    // Expression: 0.01
    //  Referenced by: '<S6>/Constant7'
    0.01,
    // Expression: 0
    //  Referenced by: '<S6>/Constant6'
    0.0,
    // Expression: 0
    //  Referenced by: '<S6>/Constant12'
    0.0,
    // Expression: 0.01
    //  Referenced by: '<S6>/Constant10'
    0.01,
    // Expression: 0
    //  Referenced by: '<S6>/Constant9'
    0.0,
    // Expression: 0
    //  Referenced by: '<S6>/Constant14'
    0.0,
    // Expression: 1.5
    //  Referenced by: '<S14>/Constant5'
    1.5,
    // Expression: 0
    //  Referenced by: '<S14>/Saturation1'
    0.0,
    // Expression: -inf
    //  Referenced by: '<S14>/Saturation1'
    0.0,
    // Expression: 0
    //  Referenced by: '<S17>/Unit Delay'
    0.0,
    // Expression: -1
    //  Referenced by: '<S14>/Gain'
    -1.0,
    // Expression: 0.7
    //  Referenced by: '<S15>/Gain1'
    0.7,
    // Expression: 0
    //  Referenced by: '<Root>/Unit Delay'
    0.0,
    // Expression: [1.1 1.4]
    //  Referenced by: '<S15>/TrailPreGain'
    {1.1, 1.4},
    // Expression: [1 1.5]
    //  Referenced by: '<S15>/TrailPreGain'
    {1.0, 1.5},
    // Expression: 0
    //  Referenced by: '<Root>/Unit Delay'
    0.0,
    // Expression: 0.3
    //  Referenced by: '<S15>/Gain'
    0.3,
    // Expression: 0
    //  Referenced by: '<Root>/Unit Delay'
    0.0,
    // Expression: 0
    //  Referenced by: '<S25>/Unit Delay'
    0.0,
    // Expression: 0.001
    //  Referenced by: '<S6>/Gain1'
    0.001,
    // Expression: 0
    //  Referenced by: '<S27>/Unit Delay'
    0.0,
    // Expression: 0.001
    //  Referenced by: '<S6>/Gain2'
    0.001,
    // Expression: 0
    //  Referenced by: '<S26>/Unit Delay'
    0.0,
    // Expression: 0.001
    //  Referenced by: '<S6>/Gain3'
    0.001,
    // Computed Parameter: BackAxleBrakePressure_maxIndex
    //  Referenced by: '<S15>/Back Axle Brake Pressure'
    {25U, 1U},
    // Computed Parameter: forwardAxleBrakePressure1_maxIndex
    //  Referenced by: '<S15>/forward Axle Brake Pressure1'
    {25U, 1U},
    // Computed Parameter: UnitDelay1_InitialCondition
    //  Referenced by: '<S17>/Unit Delay1'
    1,
    // Computed Parameter: UnitDelay1_InitialCondition_g
    //  Referenced by: '<S25>/Unit Delay1'
    1,
    // Computed Parameter: UnitDelay1_InitialCondition_o
    //  Referenced by: '<S27>/Unit Delay1'
    1,
    // Computed Parameter: UnitDelay1_InitialCondition_f
    //  Referenced by: '<S26>/Unit Delay1'
    1,
    // Computed Parameter: ManualSwitch_CurrentSetting
    //  Referenced by: '<S1>/Manual Switch'
    1U,
    // Computed Parameter: ManualSwitch_CurrentSetting_m
    //  Referenced by: '<S2>/Manual Switch'
    1U,
    // Computed Parameter: ManualSwitch_CurrentSetting_g
    //  Referenced by: '<S3>/Manual Switch'
    1U};
// System initialize for referenced model: 'Braking'
void BrakingModelClass::init(void) {
  // InitializeConditions for UnitDelay: '<S17>/Unit Delay1'
  Braking_DW.UnitDelay1_DSTATE = Braking_rtP.UnitDelay1_InitialCondition;
  // InitializeConditions for UnitDelay: '<S17>/Unit Delay'
  Braking_DW.UnitDelay_DSTATE = Braking_rtP.UnitDelay_InitialCondition;
  // InitializeConditions for UnitDelay generated from: '<Root>/Unit Delay'
  Braking_DW.UnitDelay_2_DSTATE = Braking_rtP.UnitDelay_2_InitialCondition;
  // InitializeConditions for UnitDelay generated from: '<Root>/Unit Delay'
  Braking_DW.UnitDelay_3_DSTATE = Braking_rtP.UnitDelay_3_InitialCondition;
  // InitializeConditions for UnitDelay generated from: '<Root>/Unit Delay'
  Braking_DW.UnitDelay_1_DSTATE = Braking_rtP.UnitDelay_1_InitialCondition;
  // InitializeConditions for UnitDelay: '<S25>/Unit Delay1'
  Braking_DW.UnitDelay1_DSTATE_k = Braking_rtP.UnitDelay1_InitialCondition_g;
  // InitializeConditions for UnitDelay: '<S25>/Unit Delay'
  Braking_DW.UnitDelay_DSTATE_a = Braking_rtP.UnitDelay_InitialCondition_e;
  // InitializeConditions for UnitDelay: '<S27>/Unit Delay1'
  Braking_DW.UnitDelay1_DSTATE_p = Braking_rtP.UnitDelay1_InitialCondition_o;
  // InitializeConditions for UnitDelay: '<S27>/Unit Delay'
  Braking_DW.UnitDelay_DSTATE_n = Braking_rtP.UnitDelay_InitialCondition_k;
  // InitializeConditions for UnitDelay: '<S26>/Unit Delay1'
  Braking_DW.UnitDelay1_DSTATE_m = Braking_rtP.UnitDelay1_InitialCondition_f;
  // InitializeConditions for UnitDelay: '<S26>/Unit Delay'
  Braking_DW.UnitDelay_DSTATE_h = Braking_rtP.UnitDelay_InitialCondition_b;
}
// Output and update for referenced model: 'Braking'
void BrakingModelClass::step(const real_T *rtu_XBR1_ExternalAccele,
                             const real_T *rtu_ax_g,
                             const real_T *rtu_XBR1_Ctrl_Mode,
                             const real_T *rtu_Mass_kg,
                             real_T rty_bwdWhlPre_Mpa[4],
                             real_T rty_fwdWhlPre_Mpa[2],
                             real_T rty_TrailWhlPre_Mpa[6]) {
  real_T u0;
  real_T u1;
  real_T u2;
  // UnitDelay: '<S17>/Unit Delay1'
  Braking_B.UnitDelay1 = Braking_DW.UnitDelay1_DSTATE;
  // RelationalOperator: '<S4>/Compare' incorporates:
  //   Constant: '<S4>/Constant'
  Braking_B.Compare =
      (*rtu_XBR1_Ctrl_Mode == Braking_rtP.CompareToConstant_const);
  // Switch: '<S14>/Switch1' incorporates:
  //   Constant: '<S14>/Constant1'
  if (Braking_B.Compare) {
    Braking_B.Switch1 = Braking_rtP.Constant1_Value;
  } else {
    Braking_B.Switch1 = *rtu_XBR1_ExternalAccele;
  }
  // End of Switch: '<S14>/Switch1'
  // Saturate: '<S14>/Saturation1'
  u0 = Braking_B.Switch1;
  u1 = Braking_rtP.Saturation1_LowerSat;
  u2 = Braking_rtP.Saturation1_UpperSat;
  if (u0 > u2) {
    Braking_B.Saturation1 = u2;
  } else if (u0 < u1) {
    Braking_B.Saturation1 = u1;
  } else {
    Braking_B.Saturation1 = u0;
  }
  // End of Saturate: '<S14>/Saturation1'
  // Abs: '<S14>/Abs1'
  Braking_B.Abs1 = std::abs(Braking_B.Saturation1);
  // UnitDelay: '<S17>/Unit Delay'
  Braking_B.UnitDelay = Braking_DW.UnitDelay_DSTATE;
  // Switch: '<S17>/Switch' incorporates:
  //   Constant: '<S14>/Constant3'
  if (Braking_B.UnitDelay1) {
    Braking_B.Switch = Braking_rtP.Constant3_Value_l;
  } else {
    // Gain: '<S5>/Gain2'
    Braking_B.Gain2 = rtP_VEH.g * *rtu_ax_g;
    // Saturate: '<S14>/Saturation'
    u0 = Braking_B.Gain2;
    u1 = Braking_rtP.Saturation_LowerSat;
    u2 = Braking_rtP.Saturation_UpperSat;
    if (u0 > u2) {
      Braking_B.Saturation = u2;
    } else if (u0 < u1) {
      Braking_B.Saturation = u1;
    } else {
      Braking_B.Saturation = u0;
    }
    // End of Saturate: '<S14>/Saturation'
    // Abs: '<S14>/Abs'
    Braking_B.Abs = std::abs(Braking_B.Saturation);
    // Sum: '<S14>/Subtract1'
    Braking_B.aErr = Braking_B.Abs1 - Braking_B.Abs;
    // Gain: '<S14>/Gain6'
    Braking_B.Gain6 = Braking_rtP.Gain6_Gain * Braking_B.aErr;
    // Product: '<S17>/Product' incorporates:
    //   Constant: '<S14>/Constant4'
    Braking_B.Product_l = Braking_B.Gain6 * rtP_dt_bra;
    // Sum: '<S17>/Add1'
    Braking_B.Add1_j = Braking_B.Product_l + Braking_B.UnitDelay;
    Braking_B.Switch = Braking_B.Add1_j;
  }
  // End of Switch: '<S17>/Switch'
  // RelationalOperator: '<S18>/LowerRelop1' incorporates:
  //   Constant: '<S14>/Constant5'
  Braking_B.LowerRelop1 = (Braking_B.Switch > Braking_rtP.Constant5_Value);
  // Switch: '<S18>/Switch2' incorporates:
  //   Constant: '<S14>/Constant5'
  if (Braking_B.LowerRelop1) {
    Braking_B.Switch2 = Braking_rtP.Constant5_Value;
  } else {
    // RelationalOperator: '<S18>/UpperRelop' incorporates:
    //   Constant: '<S14>/Constant6'
    Braking_B.UpperRelop_b = (Braking_B.Switch < Braking_rtP.Constant6_Value);
    // Switch: '<S18>/Switch' incorporates:
    //   Constant: '<S14>/Constant6'
    if (Braking_B.UpperRelop_b) {
      Braking_B.Switch_a = Braking_rtP.Constant6_Value;
    } else {
      Braking_B.Switch_a = Braking_B.Switch;
    }
    // End of Switch: '<S18>/Switch'
    Braking_B.Switch2 = Braking_B.Switch_a;
  }
  // End of Switch: '<S18>/Switch2'
  // RelationalOperator: '<S16>/Compare' incorporates:
  //   Constant: '<S16>/Constant'
  Braking_B.Compare_j =
      (Braking_B.Abs1 > Braking_rtP.CompareToConstant_const_n);
  // Switch: '<S14>/Switch' incorporates:
  //   Constant: '<S14>/Constant2'
  if (Braking_B.Compare_j) {
    // Gain: '<S14>/Kf'
    Braking_B.Kf = Braking_rtP.Kf_Gain * Braking_B.Abs1;
    // Gain: '<S14>/Gain1'
    Braking_B.Gain1 = Braking_rtP.Gain1_Gain * Braking_B.Switch2;
    // Sum: '<S14>/Add3'
    Braking_B.Add3 = Braking_B.Gain1 + Braking_B.Kf;
    Braking_B.Switch_b = Braking_B.Add3;
  } else {
    Braking_B.Switch_b = Braking_rtP.Constant2_Value;
  }
  // End of Switch: '<S14>/Switch'
  // Gain: '<S14>/Gain'
  Braking_B.BraCmdCtrl_mps2 = Braking_rtP.Gain_Gain_g * Braking_B.Switch_b;
  // Lookup_n-D: '<S15>/Back Axle Brake Pressure'
  Braking_B.BackAxleBrakePressure =
      look2_binlcapw(Braking_B.BraCmdCtrl_mps2, *rtu_Mass_kg, rtP_EBC.braCmd_BP,
                     rtP_EBC.mass_BP, rtP_EBC.bwdAxlePre_Table,
                     Braking_rtP.BackAxleBrakePressure_maxIndex, 26U);
  // Gain: '<S15>/Gain1'
  Braking_B.bwdWhlPreCmd_Kpa =
      Braking_rtP.Gain1_Gain_h * Braking_B.BackAxleBrakePressure;
  // UnitDelay generated from: '<Root>/Unit Delay'
  Braking_B.bwdWhlPre_Mpa = Braking_DW.UnitDelay_2_DSTATE;
  // ManualSwitch: '<S1>/Manual Switch' incorporates:
  //   Constant: '<S1>/Constant'
  if (Braking_rtP.ManualSwitch_CurrentSetting == 1) {
    Braking_B.ManualSwitch = Braking_rtP.Constant_Value;
  } else {
    Braking_B.ManualSwitch = 0.0;
  }
  // End of ManualSwitch: '<S1>/Manual Switch'
  // Switch: '<S1>/Switch'
  if (Braking_B.ManualSwitch != 0.0) {
    // Sum: '<S1>/Subtract'
    Braking_B.Subtract = Braking_B.bwdWhlPreCmd_Kpa - Braking_B.bwdWhlPre_Mpa;
    // RelationalOperator: '<S8>/Compare' incorporates:
    //   Constant: '<S8>/Constant'
    Braking_B.Compare_ae =
        (Braking_B.Subtract > Braking_rtP.CompareToConstant1_const);
    // Switch: '<S1>/Switch1' incorporates:
    //   Constant: '<S1>/Constant1'
    if (Braking_B.Compare_ae) {
      Braking_B.BwdWhlBraPreRate_Kpas_k = rtP_EBC.PreUpRate;
    } else {
      // RelationalOperator: '<S9>/Compare' incorporates:
      //   Constant: '<S9>/Constant'
      Braking_B.Compare_km =
          (Braking_B.Subtract < Braking_rtP.CompareToConstant2_const);
      // Switch: '<S1>/Switch2' incorporates:
      //   Constant: '<S1>/Constant2'
      //   Constant: '<S1>/Constant3'
      if (Braking_B.Compare_km) {
        Braking_B.BwdWhlBraPreRate_Kpas_l = rtP_EBC.PreDnRate;
      } else {
        Braking_B.BwdWhlBraPreRate_Kpas_l = Braking_rtP.Constant3_Value;
      }
      // End of Switch: '<S1>/Switch2'
      Braking_B.BwdWhlBraPreRate_Kpas_k = Braking_B.BwdWhlBraPreRate_Kpas_l;
    }
    // End of Switch: '<S1>/Switch1'
    Braking_B.BwdWhlBraPreRate_Kpas = Braking_B.BwdWhlBraPreRate_Kpas_k;
  } else {
    Braking_B.BwdWhlBraPreRate_Kpas = 0.0;
  }
  // End of Switch: '<S1>/Switch'
  // Lookup_n-D: '<S15>/TrailPreGain'
  Braking_B.TrailPreGain = look1_binlcapw(
      Braking_B.BraCmdCtrl_mps2, Braking_rtP.TrailPreGain_bp01Data,
      Braking_rtP.TrailPreGain_tableData, 1U);
  // Product: '<S15>/Product'
  Braking_B.TrailWhlPreCmd_Kpa =
      Braking_B.BackAxleBrakePressure * Braking_B.TrailPreGain;
  // UnitDelay generated from: '<Root>/Unit Delay'
  Braking_B.TrailAllWhlPre_Mpa = Braking_DW.UnitDelay_3_DSTATE;
  // ManualSwitch: '<S2>/Manual Switch' incorporates:
  //   Constant: '<S2>/Constant'
  if (Braking_rtP.ManualSwitch_CurrentSetting_m == 1) {
    Braking_B.ManualSwitch_b = Braking_rtP.Constant_Value_i;
  } else {
    Braking_B.ManualSwitch_b = 0.0;
  }
  // End of ManualSwitch: '<S2>/Manual Switch'
  // Switch: '<S2>/Switch'
  if (Braking_B.ManualSwitch_b != 0.0) {
    // Sum: '<S2>/Subtract'
    Braking_B.TrailPreErr_Kpa =
        Braking_B.TrailWhlPreCmd_Kpa - Braking_B.TrailAllWhlPre_Mpa;
    // RelationalOperator: '<S10>/Compare' incorporates:
    //   Constant: '<S10>/Constant'
    Braking_B.Compare_o =
        (Braking_B.TrailPreErr_Kpa > Braking_rtP.CompareToConstant1_const_l);
    // Switch: '<S2>/Switch1' incorporates:
    //   Constant: '<S2>/Constant1'
    if (Braking_B.Compare_o) {
      Braking_B.TrailWhlBraPreRate_Kpas_f = rtP_EBC.PreUpRate;
    } else {
      // RelationalOperator: '<S11>/Compare' incorporates:
      //   Constant: '<S11>/Constant'
      Braking_B.Compare_as =
          (Braking_B.TrailPreErr_Kpa < Braking_rtP.CompareToConstant2_const_f);
      // Switch: '<S2>/Switch2' incorporates:
      //   Constant: '<S2>/Constant2'
      //   Constant: '<S2>/Constant3'
      if (Braking_B.Compare_as) {
        Braking_B.BwdWhlBraPreRate_Kpas_b = rtP_EBC.PreDnRate;
      } else {
        Braking_B.BwdWhlBraPreRate_Kpas_b = Braking_rtP.Constant3_Value_n;
      }
      // End of Switch: '<S2>/Switch2'
      Braking_B.TrailWhlBraPreRate_Kpas_f = Braking_B.BwdWhlBraPreRate_Kpas_b;
    }
    // End of Switch: '<S2>/Switch1'
    Braking_B.TrailWhlBraPreRate_Kpas = Braking_B.TrailWhlBraPreRate_Kpas_f;
  } else {
    Braking_B.TrailWhlBraPreRate_Kpas = 0.0;
  }
  // End of Switch: '<S2>/Switch'
  // Lookup_n-D: '<S15>/forward Axle Brake Pressure1'
  Braking_B.forwardAxleBrakePressure1 =
      look2_binlcapw(Braking_B.BraCmdCtrl_mps2, *rtu_Mass_kg, rtP_EBC.braCmd_BP,
                     rtP_EBC.mass_BP, rtP_EBC.fwdAxlePre_Table,
                     Braking_rtP.forwardAxleBrakePressure1_maxIndex, 26U);
  // Gain: '<S15>/Gain'
  Braking_B.fwdWhlPreCmd_Kpa =
      Braking_rtP.Gain_Gain_j * Braking_B.forwardAxleBrakePressure1;
  // UnitDelay generated from: '<Root>/Unit Delay'
  Braking_B.fwdAllWhlPre_Mpa = Braking_DW.UnitDelay_1_DSTATE;
  // ManualSwitch: '<S3>/Manual Switch' incorporates:
  //   Constant: '<S3>/Constant'
  if (Braking_rtP.ManualSwitch_CurrentSetting_g == 1) {
    Braking_B.ManualSwitch_p = Braking_rtP.Constant_Value_b;
  } else {
    Braking_B.ManualSwitch_p = 0.0;
  }
  // End of ManualSwitch: '<S3>/Manual Switch'
  // Switch: '<S3>/Switch'
  if (Braking_B.ManualSwitch_p != 0.0) {
    // Gain: '<S3>/Gain'
    Braking_B.Gain = Braking_rtP.Gain_Gain * Braking_B.fwdAllWhlPre_Mpa;
    // Sum: '<S3>/Subtract'
    Braking_B.FwdPreErr_Kpa = Braking_B.fwdWhlPreCmd_Kpa - Braking_B.Gain;
    // RelationalOperator: '<S12>/Compare' incorporates:
    //   Constant: '<S12>/Constant'
    Braking_B.Compare_au =
        (Braking_B.FwdPreErr_Kpa > Braking_rtP.CompareToConstant1_const_o);
    // Switch: '<S3>/Switch1' incorporates:
    //   Constant: '<S3>/Constant1'
    if (Braking_B.Compare_au) {
      Braking_B.FwdWhlBraPreRate_Kpas_m = rtP_EBC.PreUpRate;
    } else {
      // RelationalOperator: '<S13>/Compare' incorporates:
      //   Constant: '<S13>/Constant'
      Braking_B.Compare_k =
          (Braking_B.FwdPreErr_Kpa < Braking_rtP.CompareToConstant2_const_h);
      // Switch: '<S3>/Switch2' incorporates:
      //   Constant: '<S3>/Constant2'
      //   Constant: '<S3>/Constant3'
      if (Braking_B.Compare_k) {
        Braking_B.BwdWhlBraPreRate_Kpas_j = rtP_EBC.PreDnRate;
      } else {
        Braking_B.BwdWhlBraPreRate_Kpas_j = Braking_rtP.Constant3_Value_o;
      }
      // End of Switch: '<S3>/Switch2'
      Braking_B.FwdWhlBraPreRate_Kpas_m = Braking_B.BwdWhlBraPreRate_Kpas_j;
    }
    // End of Switch: '<S3>/Switch1'
    Braking_B.FwdWhlBraPreRate_Kpas = Braking_B.FwdWhlBraPreRate_Kpas_m;
  } else {
    Braking_B.FwdWhlBraPreRate_Kpas = 0.0;
  }
  // End of Switch: '<S3>/Switch'
  // RelationalOperator: '<S19>/Compare' incorporates:
  //   Constant: '<S19>/Constant'
  Braking_B.Compare_c = (Braking_B.BwdWhlBraPreRate_Kpas >
                         Braking_rtP.CompareToConstant_const_n5);
  // RelationalOperator: '<S21>/Compare' incorporates:
  //   Constant: '<S21>/Constant'
  Braking_B.Compare_n = (Braking_B.FwdWhlBraPreRate_Kpas >
                         Braking_rtP.CompareToConstant2_const_j);
  // RelationalOperator: '<S23>/Compare' incorporates:
  //   Constant: '<S23>/Constant'
  Braking_B.Compare_i = (Braking_B.TrailWhlBraPreRate_Kpas >
                         Braking_rtP.CompareToConstant4_const);
  // Switch: '<S6>/Switch' incorporates:
  //   Constant: '<S6>/Constant'
  if (Braking_B.Compare_c) {
    Braking_B.UpLimit_bwd = Braking_B.bwdWhlPreCmd_Kpa;
  } else {
    Braking_B.UpLimit_bwd = Braking_rtP.Constant_Value_p;
  }
  // End of Switch: '<S6>/Switch'
  // UnitDelay: '<S25>/Unit Delay1'
  Braking_B.UnitDelay1_a = Braking_DW.UnitDelay1_DSTATE_k;
  // UnitDelay: '<S25>/Unit Delay'
  Braking_B.UnitDelay_d = Braking_DW.UnitDelay_DSTATE_a;
  // Switch: '<S25>/Switch' incorporates:
  //   Constant: '<S6>/Constant2'
  if (Braking_B.UnitDelay1_a) {
    Braking_B.Switch_e = Braking_rtP.Constant2_Value_m;
  } else {
    // Product: '<S25>/Product' incorporates:
    //   Constant: '<S6>/Constant3'
    Braking_B.Product_k =
        Braking_B.BwdWhlBraPreRate_Kpas * Braking_rtP.Constant3_Value_b;
    // Sum: '<S25>/Add1'
    Braking_B.Add1_m = Braking_B.Product_k + Braking_B.UnitDelay_d;
    Braking_B.Switch_e = Braking_B.Add1_m;
  }
  // End of Switch: '<S25>/Switch'
  // RelationalOperator: '<S28>/LowerRelop1'
  Braking_B.LowerRelop1_c = (Braking_B.Switch_e > Braking_B.UpLimit_bwd);
  // Switch: '<S28>/Switch2'
  if (Braking_B.LowerRelop1_c) {
    Braking_B.Switch2_c = Braking_B.UpLimit_bwd;
  } else {
    // RelationalOperator: '<S20>/Compare' incorporates:
    //   Constant: '<S20>/Constant'
    Braking_B.Compare_h = (Braking_B.BwdWhlBraPreRate_Kpas <
                           Braking_rtP.CompareToConstant1_const_ld);
    // Switch: '<S6>/Switch1' incorporates:
    //   Constant: '<S6>/Constant1'
    if (Braking_B.Compare_h) {
      Braking_B.LowLimit_bwd_i = Braking_B.bwdWhlPreCmd_Kpa;
    } else {
      Braking_B.LowLimit_bwd_i = Braking_rtP.Constant1_Value_c;
    }
    // End of Switch: '<S6>/Switch1'
    // RelationalOperator: '<S28>/UpperRelop'
    Braking_B.UpperRelop_o = (Braking_B.Switch_e < Braking_B.LowLimit_bwd_i);
    // Switch: '<S28>/Switch'
    if (Braking_B.UpperRelop_o) {
      Braking_B.Switch_cu = Braking_B.LowLimit_bwd_i;
    } else {
      Braking_B.Switch_cu = Braking_B.Switch_e;
    }
    // End of Switch: '<S28>/Switch'
    Braking_B.Switch2_c = Braking_B.Switch_cu;
  }
  // End of Switch: '<S28>/Switch2'
  // Gain: '<S6>/Gain1'
  Braking_B.bwdWhlPre_Mpa_m = Braking_rtP.Gain1_Gain_hn * Braking_B.Switch2_c;
  // Switch: '<S6>/Switch4' incorporates:
  //   Constant: '<S6>/Constant13'
  if (Braking_B.Compare_i) {
    Braking_B.UpLimit_bwd_d = Braking_B.TrailWhlPreCmd_Kpa;
  } else {
    Braking_B.UpLimit_bwd_d = Braking_rtP.Constant13_Value;
  }
  // End of Switch: '<S6>/Switch4'
  // UnitDelay: '<S27>/Unit Delay1'
  Braking_B.UnitDelay1_ah = Braking_DW.UnitDelay1_DSTATE_p;
  // UnitDelay: '<S27>/Unit Delay'
  Braking_B.UnitDelay_c = Braking_DW.UnitDelay_DSTATE_n;
  // Switch: '<S27>/Switch' incorporates:
  //   Constant: '<S6>/Constant9'
  if (Braking_B.UnitDelay1_ah) {
    Braking_B.Switch_n = Braking_rtP.Constant9_Value;
  } else {
    // Product: '<S27>/Product' incorporates:
    //   Constant: '<S6>/Constant10'
    Braking_B.Product =
        Braking_B.TrailWhlBraPreRate_Kpas * Braking_rtP.Constant10_Value;
    // Sum: '<S27>/Add1'
    Braking_B.Add1 = Braking_B.Product + Braking_B.UnitDelay_c;
    Braking_B.Switch_n = Braking_B.Add1;
  }
  // End of Switch: '<S27>/Switch'
  // RelationalOperator: '<S30>/LowerRelop1'
  Braking_B.LowerRelop1_o = (Braking_B.Switch_n > Braking_B.UpLimit_bwd_d);
  // Switch: '<S30>/Switch2'
  if (Braking_B.LowerRelop1_o) {
    Braking_B.Switch2_o = Braking_B.UpLimit_bwd_d;
  } else {
    // RelationalOperator: '<S24>/Compare' incorporates:
    //   Constant: '<S24>/Constant'
    Braking_B.Compare_d = (Braking_B.TrailWhlBraPreRate_Kpas <
                           Braking_rtP.CompareToConstant5_const);
    // Switch: '<S6>/Switch5' incorporates:
    //   Constant: '<S6>/Constant14'
    if (Braking_B.Compare_d) {
      Braking_B.LowLimit_bwd = Braking_B.TrailWhlPreCmd_Kpa;
    } else {
      Braking_B.LowLimit_bwd = Braking_rtP.Constant14_Value;
    }
    // End of Switch: '<S6>/Switch5'
    // RelationalOperator: '<S30>/UpperRelop'
    Braking_B.UpperRelop = (Braking_B.Switch_n < Braking_B.LowLimit_bwd);
    // Switch: '<S30>/Switch'
    if (Braking_B.UpperRelop) {
      Braking_B.Switch_d = Braking_B.LowLimit_bwd;
    } else {
      Braking_B.Switch_d = Braking_B.Switch_n;
    }
    // End of Switch: '<S30>/Switch'
    Braking_B.Switch2_o = Braking_B.Switch_d;
  }
  // End of Switch: '<S30>/Switch2'
  // Gain: '<S6>/Gain2'
  Braking_B.TrailAllWhlPre_Mpa_d = Braking_rtP.Gain2_Gain * Braking_B.Switch2_o;
  // Switch: '<S6>/Switch2' incorporates:
  //   Constant: '<S6>/Constant11'
  if (Braking_B.Compare_n) {
    Braking_B.UpLimit_bwd_n = Braking_B.fwdWhlPreCmd_Kpa;
  } else {
    Braking_B.UpLimit_bwd_n = Braking_rtP.Constant11_Value;
  }
  // End of Switch: '<S6>/Switch2'
  // UnitDelay: '<S26>/Unit Delay1'
  Braking_B.UnitDelay1_m = Braking_DW.UnitDelay1_DSTATE_m;
  // UnitDelay: '<S26>/Unit Delay'
  Braking_B.UnitDelay_e = Braking_DW.UnitDelay_DSTATE_h;
  // Switch: '<S26>/Switch' incorporates:
  //   Constant: '<S6>/Constant6'
  if (Braking_B.UnitDelay1_m) {
    Braking_B.Switch_e5 = Braking_rtP.Constant6_Value_l;
  } else {
    // Product: '<S26>/Product' incorporates:
    //   Constant: '<S6>/Constant7'
    Braking_B.Product_p =
        Braking_B.FwdWhlBraPreRate_Kpas * Braking_rtP.Constant7_Value;
    // Sum: '<S26>/Add1'
    Braking_B.Add1_a = Braking_B.Product_p + Braking_B.UnitDelay_e;
    Braking_B.Switch_e5 = Braking_B.Add1_a;
  }
  // End of Switch: '<S26>/Switch'
  // RelationalOperator: '<S29>/LowerRelop1'
  Braking_B.LowerRelop1_g = (Braking_B.Switch_e5 > Braking_B.UpLimit_bwd_n);
  // Switch: '<S29>/Switch2'
  if (Braking_B.LowerRelop1_g) {
    Braking_B.Switch2_k = Braking_B.UpLimit_bwd_n;
  } else {
    // RelationalOperator: '<S22>/Compare' incorporates:
    //   Constant: '<S22>/Constant'
    Braking_B.Compare_a = (Braking_B.FwdWhlBraPreRate_Kpas <
                           Braking_rtP.CompareToConstant3_const);
    // Switch: '<S6>/Switch3' incorporates:
    //   Constant: '<S6>/Constant12'
    if (Braking_B.Compare_a) {
      Braking_B.LowLimit_bwd_k = Braking_B.fwdWhlPreCmd_Kpa;
    } else {
      Braking_B.LowLimit_bwd_k = Braking_rtP.Constant12_Value;
    }
    // End of Switch: '<S6>/Switch3'
    // RelationalOperator: '<S29>/UpperRelop'
    Braking_B.UpperRelop_h = (Braking_B.Switch_e5 < Braking_B.LowLimit_bwd_k);
    // Switch: '<S29>/Switch'
    if (Braking_B.UpperRelop_h) {
      Braking_B.Switch_c = Braking_B.LowLimit_bwd_k;
    } else {
      Braking_B.Switch_c = Braking_B.Switch_e5;
    }
    // End of Switch: '<S29>/Switch'
    Braking_B.Switch2_k = Braking_B.Switch_c;
  }
  // End of Switch: '<S29>/Switch2'
  // Gain: '<S6>/Gain3'
  Braking_B.fwdAllWhlPre_Mpa_b = Braking_rtP.Gain3_Gain * Braking_B.Switch2_k;
  // SignalConversion generated from: '<Root>/TrailWhlPre_Mpa'
  rty_TrailWhlPre_Mpa[0] = Braking_B.TrailAllWhlPre_Mpa_d;
  rty_TrailWhlPre_Mpa[1] = Braking_B.TrailAllWhlPre_Mpa_d;
  rty_TrailWhlPre_Mpa[2] = Braking_B.TrailAllWhlPre_Mpa_d;
  rty_TrailWhlPre_Mpa[3] = Braking_B.TrailAllWhlPre_Mpa_d;
  rty_TrailWhlPre_Mpa[4] = Braking_B.TrailAllWhlPre_Mpa_d;
  rty_TrailWhlPre_Mpa[5] = Braking_B.TrailAllWhlPre_Mpa_d;
  // SignalConversion generated from: '<Root>/bwdWhlPre_Mpa'
  rty_bwdWhlPre_Mpa[0] = Braking_B.bwdWhlPre_Mpa_m;
  rty_bwdWhlPre_Mpa[1] = Braking_B.bwdWhlPre_Mpa_m;
  rty_bwdWhlPre_Mpa[2] = Braking_B.bwdWhlPre_Mpa_m;
  rty_bwdWhlPre_Mpa[3] = Braking_B.bwdWhlPre_Mpa_m;
  // SignalConversion generated from: '<Root>/fwdWhlPre_Mpa'
  rty_fwdWhlPre_Mpa[0] = Braking_B.fwdAllWhlPre_Mpa_b;
  rty_fwdWhlPre_Mpa[1] = Braking_B.fwdAllWhlPre_Mpa_b;
  // Update for UnitDelay: '<S17>/Unit Delay1'
  Braking_DW.UnitDelay1_DSTATE = Braking_B.Compare;
  // Update for UnitDelay: '<S17>/Unit Delay'
  Braking_DW.UnitDelay_DSTATE = Braking_B.Switch2;
  // Update for UnitDelay generated from: '<Root>/Unit Delay'
  Braking_DW.UnitDelay_2_DSTATE = Braking_B.bwdWhlPre_Mpa_m;
  // Update for UnitDelay generated from: '<Root>/Unit Delay'
  Braking_DW.UnitDelay_3_DSTATE = Braking_B.TrailAllWhlPre_Mpa_d;
  // Update for UnitDelay generated from: '<Root>/Unit Delay'
  Braking_DW.UnitDelay_1_DSTATE = Braking_B.fwdAllWhlPre_Mpa_b;
  // Update for UnitDelay: '<S25>/Unit Delay1'
  Braking_DW.UnitDelay1_DSTATE_k = Braking_B.Compare;
  // Update for UnitDelay: '<S25>/Unit Delay'
  Braking_DW.UnitDelay_DSTATE_a = Braking_B.Switch2_c;
  // Update for UnitDelay: '<S27>/Unit Delay1'
  Braking_DW.UnitDelay1_DSTATE_p = Braking_B.Compare;
  // Update for UnitDelay: '<S27>/Unit Delay'
  Braking_DW.UnitDelay_DSTATE_n = Braking_B.Switch2_o;
  // Update for UnitDelay: '<S26>/Unit Delay1'
  Braking_DW.UnitDelay1_DSTATE_m = Braking_B.Compare;
  // Update for UnitDelay: '<S26>/Unit Delay'
  Braking_DW.UnitDelay_DSTATE_h = Braking_B.Switch2_k;
}
// Model initialize function
void BrakingModelClass::initialize() {
  // Registration code
  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));
  // block I/O
  (void)std::memset((static_cast<void *>(&Braking_B)), 0, sizeof(B_Braking_T));
  {
    Braking_B.Switch1 = 0.0;
    Braking_B.Saturation1 = 0.0;
    Braking_B.Abs1 = 0.0;
    Braking_B.UnitDelay = 0.0;
    Braking_B.Switch = 0.0;
    Braking_B.Switch2 = 0.0;
    Braking_B.Switch_b = 0.0;
    Braking_B.BraCmdCtrl_mps2 = 0.0;
    Braking_B.BackAxleBrakePressure = 0.0;
    Braking_B.bwdWhlPreCmd_Kpa = 0.0;
    Braking_B.bwdWhlPre_Mpa = 0.0;
    Braking_B.ManualSwitch = 0.0;
    Braking_B.BwdWhlBraPreRate_Kpas = 0.0;
    Braking_B.TrailPreGain = 0.0;
    Braking_B.TrailWhlPreCmd_Kpa = 0.0;
    Braking_B.TrailAllWhlPre_Mpa = 0.0;
    Braking_B.ManualSwitch_b = 0.0;
    Braking_B.TrailWhlBraPreRate_Kpas = 0.0;
    Braking_B.forwardAxleBrakePressure1 = 0.0;
    Braking_B.fwdWhlPreCmd_Kpa = 0.0;
    Braking_B.fwdAllWhlPre_Mpa = 0.0;
    Braking_B.ManualSwitch_p = 0.0;
    Braking_B.FwdWhlBraPreRate_Kpas = 0.0;
    Braking_B.UpLimit_bwd = 0.0;
    Braking_B.UnitDelay_d = 0.0;
    Braking_B.Switch_e = 0.0;
    Braking_B.Switch2_c = 0.0;
    Braking_B.bwdWhlPre_Mpa_m = 0.0;
    Braking_B.UpLimit_bwd_d = 0.0;
    Braking_B.UnitDelay_c = 0.0;
    Braking_B.Switch_n = 0.0;
    Braking_B.Switch2_o = 0.0;
    Braking_B.TrailAllWhlPre_Mpa_d = 0.0;
    Braking_B.UpLimit_bwd_n = 0.0;
    Braking_B.UnitDelay_e = 0.0;
    Braking_B.Switch_e5 = 0.0;
    Braking_B.Switch2_k = 0.0;
    Braking_B.fwdAllWhlPre_Mpa_b = 0.0;
    Braking_B.LowLimit_bwd = 0.0;
    Braking_B.Switch_d = 0.0;
    Braking_B.Product = 0.0;
    Braking_B.Add1 = 0.0;
    Braking_B.LowLimit_bwd_k = 0.0;
    Braking_B.Switch_c = 0.0;
    Braking_B.Product_p = 0.0;
    Braking_B.Add1_a = 0.0;
    Braking_B.LowLimit_bwd_i = 0.0;
    Braking_B.Switch_cu = 0.0;
    Braking_B.Product_k = 0.0;
    Braking_B.Add1_m = 0.0;
    Braking_B.Switch_a = 0.0;
    Braking_B.Gain2 = 0.0;
    Braking_B.Saturation = 0.0;
    Braking_B.Abs = 0.0;
    Braking_B.aErr = 0.0;
    Braking_B.Gain6 = 0.0;
    Braking_B.Product_l = 0.0;
    Braking_B.Add1_j = 0.0;
    Braking_B.Kf = 0.0;
    Braking_B.Gain1 = 0.0;
    Braking_B.Add3 = 0.0;
    Braking_B.Gain = 0.0;
    Braking_B.FwdPreErr_Kpa = 0.0;
    Braking_B.FwdWhlBraPreRate_Kpas_m = 0.0;
    Braking_B.BwdWhlBraPreRate_Kpas_j = 0.0;
    Braking_B.TrailPreErr_Kpa = 0.0;
    Braking_B.TrailWhlBraPreRate_Kpas_f = 0.0;
    Braking_B.BwdWhlBraPreRate_Kpas_b = 0.0;
    Braking_B.Subtract = 0.0;
    Braking_B.BwdWhlBraPreRate_Kpas_k = 0.0;
    Braking_B.BwdWhlBraPreRate_Kpas_l = 0.0;
  }
  // states (dwork)
  (void)std::memset(static_cast<void *>(&Braking_DW), 0, sizeof(DW_Braking_T));
  Braking_DW.UnitDelay_DSTATE = 0.0;
  Braking_DW.UnitDelay_2_DSTATE = 0.0;
  Braking_DW.UnitDelay_3_DSTATE = 0.0;
  Braking_DW.UnitDelay_1_DSTATE = 0.0;
  Braking_DW.UnitDelay_DSTATE_a = 0.0;
  Braking_DW.UnitDelay_DSTATE_n = 0.0;
  Braking_DW.UnitDelay_DSTATE_h = 0.0;
  // non-finite (run-time) assignments
  Braking_rtP.Saturation_LowerSat = rtMinusInf;
  Braking_rtP.Saturation1_LowerSat = rtMinusInf;
}
// Constructor
BrakingModelClass::BrakingModelClass() {
  // Currently there is no constructor body generated.
}
// Destructor
BrakingModelClass::~BrakingModelClass() {
  // Currently there is no destructor body generated.
}
// Real-Time Model get method
RT_MODEL_Braking_T *BrakingModelClass::getRTM() { return (&Braking_M); }
// member function to setup error status pointer
void BrakingModelClass::setErrorStatusPointer(const char_T **rt_errorStatus) {
  rtmSetErrorStatusPointer((&Braking_M), rt_errorStatus);
}
//

// File trailer for generated code.
//
// [EOF]
//
