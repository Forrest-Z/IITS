//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: TCU.cpp
//
// Code generated for Simulink model 'TCU'.
//
// Model version                  : 1.228
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:44 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#include "TCU.h"

#include "TCU_private.h"
#include "look2_binlcapw.h"

// Named constants for Chart: '<Root>/TCM Shift Controller'
const int32_T TCU_CALL_EVENT = -1;
const uint8_T TCU_IN_DownShifting = 1U;
const uint8_T TCU_IN_G10 = 1U;
const uint8_T TCU_IN_G11 = 2U;
const uint8_T TCU_IN_G12 = 3U;
const uint8_T TCU_IN_G2 = 4U;
const uint8_T TCU_IN_G3 = 5U;
const uint8_T TCU_IN_G4 = 6U;
const uint8_T TCU_IN_G5 = 7U;
const uint8_T TCU_IN_G6 = 8U;
const uint8_T TCU_IN_G7 = 9U;
const uint8_T TCU_IN_G8 = 10U;
const uint8_T TCU_IN_G9 = 11U;
const uint8_T TCU_IN_NO_ACTIVE_CHILD = 0U;
const uint8_T TCU_IN_Neutral = 12U;
const uint8_T TCU_IN_SteadyState = 2U;
const uint8_T TCU_IN_UpShifting = 3U;
const uint8_T TCU_IN_preDownShifting = 4U;
const uint8_T TCU_IN_preUpShifting = 5U;
const int32_T TCU_event_Down = 0;
const int32_T TCU_event_Up = 1;
const int32_T TCU_event_Up2 = 2;
P_TCU_T TCUModelClass::TCU_rtP = {
    // Computed Parameter: up_th_Y0
    //  Referenced by: '<S5>/up_th'
    0.0,
    // Computed Parameter: down_th_Y0
    //  Referenced by: '<S4>/down_th'
    0.0,
    // Expression: 1/100
    //  Referenced by: '<Root>/Gain'
    0.01,
    // Expression: 1200
    //  Referenced by: '<S1>/Constant'
    1200.0,
    // Expression: 1e-6
    //  Referenced by: '<S1>/Constant1'
    1.0E-6,
    // Computed Parameter: CalculateUpshiftThreshold_maxIndex
    //  Referenced by: '<S5>/Calculate Upshift Threshold'
    {9U, 10U},
    // Computed Parameter: CalculateDownshiftThreshold_maxIndex
    //  Referenced by: '<S4>/Calculate  Downshift Threshold'
    {8U, 10U},
    // Start of '<S2>/calc'
    {// Computed Parameter: SpdThr_Y0
     //  Referenced by: '<S3>/SpdThr'
     0.0,
     // Computed Parameter: CalculateUpshiftThreshold1_maxIndex
     //  Referenced by: '<S3>/Calculate Upshift Threshold1'
     {9U, 10U},
     // Computed Parameter: CalculateDownshiftThreshold_maxIndex
     //  Referenced by: '<S3>/Calculate  Downshift Threshold'
     {8U, 10U}}
    // End of '<S2>/calc'
};
// System initialize for function-call system: '<S2>/calc'
void TCUModelClass::TCU_calc_Init(real_T *rty_SpdThr, P_calc_TCU_T *localP) {
  // SystemInitialize for Outport: '<S3>/SpdThr'
  *rty_SpdThr = localP->SpdThr_Y0;
}
// Output and update for function-call system: '<S2>/calc'
void TCUModelClass::TCU_calc(real_T rtu_gear, real_T rtu_pedal,
                             real_T rtu_speed, real_T *rty_SpdThr,
                             B_calc_TCU_T *localB, P_calc_TCU_T *localP) {
  // Lookup_n-D: '<S3>/Calculate Upshift Threshold1'
  localB->CalculateUpshiftThreshold1 = look2_binlcapw(
      rtu_pedal, rtu_gear, rtP_ShiftUpTa_Bp_PedPos, rtP_ShiftUpTa_Bp_GearPos,
      rtP_UpshiftSpdTa, localP->CalculateUpshiftThreshold1_maxIndex, 10U);
  // Sum: '<S3>/Add1'
  localB->Add1 = localB->CalculateUpshiftThreshold1 - rtu_speed;
  // Lookup_n-D: '<S3>/Calculate  Downshift Threshold'
  localB->CalculateDownshiftThreshold = look2_binlcapw(
      rtu_pedal, rtu_gear, rtP_ShiftDnTa_Bp_PedPos, rtP_ShiftDnTa_Bp_GearPos,
      rtP_DnShiftSpdTa, localP->CalculateDownshiftThreshold_maxIndex, 9U);
  // Sum: '<S3>/Add3'
  localB->Add3 = rtu_speed - localB->CalculateDownshiftThreshold;
  // Sum: '<S3>/Add4'
  *rty_SpdThr = localB->Add1 - localB->Add3;
}
// Function for Chart: '<Root>/TCM Shift Controller'
void TCUModelClass::TCU_GearState(const real_T *rtu_VehSpdFdbk,
                                  real_T *rty_TransmissionCmd) {
  // During 'GearState': '<S2>:17'
  switch (TCU_DW.is_GearState) {
    case TCU_IN_G10:
      // During 'G10': '<S2>:356'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Down:
          // Transition: '<S2>:358'
          TCU_DW.is_GearState = TCU_IN_G9;
          // Entry 'G9': '<S2>:353'
          *rty_TransmissionCmd = 9.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:361'
          TCU_DW.is_GearState = TCU_IN_G11;
          // Entry 'G11': '<S2>:359'
          *rty_TransmissionCmd = 11.0;
          break;
      }
      break;
    case TCU_IN_G11:
      // During 'G11': '<S2>:359'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Down:
          // Transition: '<S2>:360'
          TCU_DW.is_GearState = TCU_IN_G10;
          // Entry 'G10': '<S2>:356'
          *rty_TransmissionCmd = 10.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:364'
          TCU_DW.is_GearState = TCU_IN_G12;
          // Entry 'G12': '<S2>:362'
          *rty_TransmissionCmd = 12.0;
          break;
      }
      break;
    case TCU_IN_G12:
      // During 'G12': '<S2>:362'
      if (TCU_DW.sfEvent == TCU_event_Down) {
        // Transition: '<S2>:363'
        TCU_DW.is_GearState = TCU_IN_G11;
        // Entry 'G11': '<S2>:359'
        *rty_TransmissionCmd = 11.0;
      }
      break;
    case TCU_IN_G2:
      // During 'G2': '<S2>:6'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Up2:
          // Transition: '<S2>:368'
          TCU_DW.is_GearState = TCU_IN_G4;
          // Entry 'G4': '<S2>:42'
          *rty_TransmissionCmd = 4.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:43'
          TCU_DW.is_GearState = TCU_IN_G3;
          // Entry 'G3': '<S2>:41'
          *rty_TransmissionCmd = 3.0;
          break;
        default:
          if (TCU_B.LogicalOperator) {
            // Transition: '<S2>:88'
            TCU_DW.is_GearState = TCU_IN_Neutral;
            // Entry 'Neutral': '<S2>:1'
            *rty_TransmissionCmd = 0.0;
          } else {
            // Simulink Function 'calc': '<S2>:197'
            TCU_B.gear_a = 2.0;
            TCU_B.pedal_b = TCU_B.Gain;
            TCU_B.speed = *rtu_VehSpdFdbk;
            // Outputs for Function Call SubSystem: '<S2>/calc'
            TCU_calc(TCU_B.gear_a, TCU_B.pedal_b, TCU_B.speed, &TCU_B.Add4,
                     &TCU_B.calc, &TCU_rtP.calc);
            // End of Outputs for SubSystem: '<S2>/calc'
          }
          break;
      }
      break;
    case TCU_IN_G3:
      // During 'G3': '<S2>:41'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Up:
          // Transition: '<S2>:44'
          TCU_DW.is_GearState = TCU_IN_G4;
          // Entry 'G4': '<S2>:42'
          *rty_TransmissionCmd = 4.0;
          break;
        case TCU_event_Up2:
          // Transition: '<S2>:401'
          TCU_DW.is_GearState = TCU_IN_G5;
          // Entry 'G5': '<S2>:324'
          *rty_TransmissionCmd = 5.0;
          break;
        case TCU_event_Down:
          // Transition: '<S2>:69'
          TCU_DW.is_GearState = TCU_IN_G2;
          // Entry 'G2': '<S2>:6'
          *rty_TransmissionCmd = 2.0;
          break;
        default:
          // Simulink Function 'calc': '<S2>:197'
          TCU_B.gear_a = 3.0;
          TCU_B.pedal_b = TCU_B.Gain;
          TCU_B.speed = *rtu_VehSpdFdbk;
          // Outputs for Function Call SubSystem: '<S2>/calc'
          TCU_calc(TCU_B.gear_a, TCU_B.pedal_b, TCU_B.speed, &TCU_B.Add4,
                   &TCU_B.calc, &TCU_rtP.calc);
          // End of Outputs for SubSystem: '<S2>/calc'
          break;
      }
      break;
    case TCU_IN_G4:
      // During 'G4': '<S2>:42'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Up2:
          // Transition: '<S2>:402'
          TCU_DW.is_GearState = TCU_IN_G6;
          // Entry 'G6': '<S2>:85'
          *rty_TransmissionCmd = 6.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:327'
          TCU_DW.is_GearState = TCU_IN_G5;
          // Entry 'G5': '<S2>:324'
          *rty_TransmissionCmd = 5.0;
          break;
        case TCU_event_Down:
          // Transition: '<S2>:68'
          TCU_DW.is_GearState = TCU_IN_G3;
          // Entry 'G3': '<S2>:41'
          *rty_TransmissionCmd = 3.0;
          break;
        default:
          // Simulink Function 'calc': '<S2>:197'
          TCU_B.gear_a = 4.0;
          TCU_B.pedal_b = TCU_B.Gain;
          TCU_B.speed = *rtu_VehSpdFdbk;
          // Outputs for Function Call SubSystem: '<S2>/calc'
          TCU_calc(TCU_B.gear_a, TCU_B.pedal_b, TCU_B.speed, &TCU_B.Add4,
                   &TCU_B.calc, &TCU_rtP.calc);
          // End of Outputs for SubSystem: '<S2>/calc'
          break;
      }
      break;
    case TCU_IN_G5:
      // During 'G5': '<S2>:324'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Up2:
          // Transition: '<S2>:403'
          TCU_DW.is_GearState = TCU_IN_G7;
          // Entry 'G7': '<S2>:344'
          *rty_TransmissionCmd = 7.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:86'
          TCU_DW.is_GearState = TCU_IN_G6;
          // Entry 'G6': '<S2>:85'
          *rty_TransmissionCmd = 6.0;
          break;
        case TCU_event_Down:
          // Transition: '<S2>:328'
          TCU_DW.is_GearState = TCU_IN_G4;
          // Entry 'G4': '<S2>:42'
          *rty_TransmissionCmd = 4.0;
          break;
        default:
          // Simulink Function 'calc': '<S2>:197'
          TCU_B.gear_a = 5.0;
          TCU_B.pedal_b = TCU_B.Gain;
          TCU_B.speed = *rtu_VehSpdFdbk;
          // Outputs for Function Call SubSystem: '<S2>/calc'
          TCU_calc(TCU_B.gear_a, TCU_B.pedal_b, TCU_B.speed, &TCU_B.Add4,
                   &TCU_B.calc, &TCU_rtP.calc);
          // End of Outputs for SubSystem: '<S2>/calc'
          break;
      }
      break;
    case TCU_IN_G6:
      // During 'G6': '<S2>:85'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Up2:
          // Transition: '<S2>:404'
          TCU_DW.is_GearState = TCU_IN_G8;
          // Entry 'G8': '<S2>:347'
          *rty_TransmissionCmd = 8.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:345'
          TCU_DW.is_GearState = TCU_IN_G7;
          // Entry 'G7': '<S2>:344'
          *rty_TransmissionCmd = 7.0;
          break;
        case TCU_event_Down:
          // Transition: '<S2>:87'
          TCU_DW.is_GearState = TCU_IN_G5;
          // Entry 'G5': '<S2>:324'
          *rty_TransmissionCmd = 5.0;
          break;
      }
      break;
    case TCU_IN_G7:
      // During 'G7': '<S2>:344'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Up2:
          // Transition: '<S2>:405'
          TCU_DW.is_GearState = TCU_IN_G9;
          // Entry 'G9': '<S2>:353'
          *rty_TransmissionCmd = 9.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:348'
          TCU_DW.is_GearState = TCU_IN_G8;
          // Entry 'G8': '<S2>:347'
          *rty_TransmissionCmd = 8.0;
          break;
        case TCU_event_Down:
          // Transition: '<S2>:346'
          TCU_DW.is_GearState = TCU_IN_G6;
          // Entry 'G6': '<S2>:85'
          *rty_TransmissionCmd = 6.0;
          break;
      }
      break;
    case TCU_IN_G8:
      // During 'G8': '<S2>:347'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Up2:
          // Transition: '<S2>:406'
          TCU_DW.is_GearState = TCU_IN_G10;
          // Entry 'G10': '<S2>:356'
          *rty_TransmissionCmd = 10.0;
          break;
        case TCU_event_Down:
          // Transition: '<S2>:349'
          TCU_DW.is_GearState = TCU_IN_G7;
          // Entry 'G7': '<S2>:344'
          *rty_TransmissionCmd = 7.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:354'
          TCU_DW.is_GearState = TCU_IN_G9;
          // Entry 'G9': '<S2>:353'
          *rty_TransmissionCmd = 9.0;
          break;
      }
      break;
    case TCU_IN_G9:
      // During 'G9': '<S2>:353'
      switch (TCU_DW.sfEvent) {
        case TCU_event_Down:
          // Transition: '<S2>:355'
          TCU_DW.is_GearState = TCU_IN_G8;
          // Entry 'G8': '<S2>:347'
          *rty_TransmissionCmd = 8.0;
          break;
        case TCU_event_Up:
          // Transition: '<S2>:357'
          TCU_DW.is_GearState = TCU_IN_G10;
          // Entry 'G10': '<S2>:356'
          *rty_TransmissionCmd = 10.0;
          break;
      }
      break;
    case TCU_IN_Neutral:
      // During 'Neutral': '<S2>:1'
      if (!TCU_B.LogicalOperator) {
        // Transition: '<S2>:32'
        TCU_DW.is_GearState = TCU_IN_G2;
        // Entry 'G2': '<S2>:6'
        *rty_TransmissionCmd = 2.0;
      }
      break;
  }
}
// Function for Chart: '<Root>/TCM Shift Controller'
void TCUModelClass::TCU_c1_TCU(const real_T *rtu_VehSpdFdbk,
                               real_T *rty_TransmissionCmd) {
  int32_T b_previousEvent;
  real_T up_th;
  // Chart: '<Root>/TCM Shift Controller'
  // During: TCM Shift Controller
  if (TCU_DW.is_active_c1_TCU == 0U) {
    // Entry: TCM Shift Controller
    TCU_DW.is_active_c1_TCU = 1U;
    // Entry Internal: TCM Shift Controller
    TCU_DW.is_active_GearState = 1U;
    // Entry Internal 'GearState': '<S2>:17'
    // Transition: '<S2>:409'
    TCU_DW.is_GearState = TCU_IN_G2;
    // Entry 'G2': '<S2>:6'
    *rty_TransmissionCmd = 2.0;
    TCU_DW.is_active_SelectionState = 1U;
    // Entry Internal 'SelectionState': '<S2>:18'
    // Transition: '<S2>:19'
    TCU_DW.is_SelectionState = TCU_IN_SteadyState;
    // Entry 'SteadyState': '<S2>:11'
  } else {
    if (TCU_DW.is_active_GearState != 0U) {
      TCU_GearState(rtu_VehSpdFdbk, rty_TransmissionCmd);
    }
    if (TCU_DW.is_active_SelectionState != 0U) {
      // During 'SelectionState': '<S2>:18'
      // Simulink Function 'calc_up': '<S2>:40'
      TCU_B.gear = *rty_TransmissionCmd;
      TCU_B.pedal = TCU_B.Gain;
      // Outputs for Function Call SubSystem: '<S2>/calc_up'
      // Lookup_n-D: '<S5>/Calculate Upshift Threshold'
      TCU_B.CalculateUpshiftThreshold =
          look2_binlcapw(TCU_B.pedal, TCU_B.gear, rtP_ShiftUpTa_Bp_PedPos,
                         rtP_ShiftUpTa_Bp_GearPos, rtP_UpshiftSpdTa,
                         TCU_rtP.CalculateUpshiftThreshold_maxIndex, 10U);
      // End of Outputs for SubSystem: '<S2>/calc_up'
      up_th = TCU_B.CalculateUpshiftThreshold;
      // Simulink Function 'calc_down': '<S2>:75'
      TCU_B.gear_i = *rty_TransmissionCmd;
      TCU_B.pedal_h = TCU_B.Gain;
      // Outputs for Function Call SubSystem: '<S2>/calc_down'
      // Lookup_n-D: '<S4>/Calculate  Downshift Threshold'
      TCU_B.CalculateDownshiftThreshold =
          look2_binlcapw(TCU_B.pedal_h, TCU_B.gear_i, rtP_ShiftDnTa_Bp_PedPos,
                         rtP_ShiftDnTa_Bp_GearPos, rtP_DnShiftSpdTa,
                         TCU_rtP.CalculateDownshiftThreshold_maxIndex, 9U);
      // End of Outputs for SubSystem: '<S2>/calc_down'
      switch (TCU_DW.is_SelectionState) {
        case TCU_IN_DownShifting:
          // During 'DownShifting': '<S2>:56'
          // Transition: '<S2>:60'
          // Event: '<S2>:71'
          b_previousEvent = TCU_DW.sfEvent;
          TCU_DW.sfEvent = TCU_event_Down;
          if (TCU_DW.is_active_GearState != 0U) {
            TCU_GearState(rtu_VehSpdFdbk, rty_TransmissionCmd);
          }
          TCU_DW.sfEvent = b_previousEvent;
          // Transition: '<S2>:25'
          TCU_DW.is_SelectionState = TCU_IN_SteadyState;
          // Entry 'SteadyState': '<S2>:11'
          break;
        case TCU_IN_SteadyState:
          // During 'SteadyState': '<S2>:11'
          if ((*rtu_VehSpdFdbk < TCU_B.CalculateDownshiftThreshold) &&
              (*rty_TransmissionCmd > 1.0)) {
            // Transition: '<S2>:63'
            // Transition: '<S2>:158'
            TCU_DW.is_SelectionState = TCU_IN_preDownShifting;
            TCU_DW.temporalCounter_i1 = 0U;
          } else {
            if ((*rtu_VehSpdFdbk > up_th) && (*rty_TransmissionCmd <= 11.0) &&
                (std::floor(*rty_TransmissionCmd) == *rty_TransmissionCmd)) {
              // Transition: '<S2>:21'
              // Transition: '<S2>:154'
              TCU_DW.is_SelectionState = TCU_IN_preUpShifting;
              TCU_DW.temporalCounter_i1 = 0U;
            }
          }
          break;
        case TCU_IN_UpShifting:
          // During 'UpShifting': '<S2>:13'
          // Transition: '<S2>:24'
          // Event: '<S2>:48'
          b_previousEvent = TCU_DW.sfEvent;
          TCU_DW.sfEvent = TCU_event_Up;
          if (TCU_DW.is_active_GearState != 0U) {
            TCU_GearState(rtu_VehSpdFdbk, rty_TransmissionCmd);
          }
          TCU_DW.sfEvent = b_previousEvent;
          // Transition: '<S2>:25'
          TCU_DW.is_SelectionState = TCU_IN_SteadyState;
          // Entry 'SteadyState': '<S2>:11'
          break;
        case TCU_IN_preDownShifting:
          // During 'preDownShifting': '<S2>:157'
          if ((TCU_DW.temporalCounter_i1 >= 500U) &&
              (*rtu_VehSpdFdbk < TCU_B.CalculateDownshiftThreshold - 2.0)) {
            // Transition: '<S2>:159'
            TCU_DW.is_SelectionState = TCU_IN_DownShifting;
            // Entry 'DownShifting': '<S2>:56'
          } else {
            if (*rtu_VehSpdFdbk >= TCU_B.CalculateDownshiftThreshold) {
              // Transition: '<S2>:160'
              // Transition: '<S2>:170'
              TCU_DW.is_SelectionState = TCU_IN_SteadyState;
              // Entry 'SteadyState': '<S2>:11'
            }
          }
          break;
        case TCU_IN_preUpShifting:
          // During 'preUpShifting': '<S2>:149'
          if ((TCU_DW.temporalCounter_i1 >= 1U) &&
              ((*rtu_VehSpdFdbk > up_th) && (TCU_B.Gain >= 0.6) &&
               (*rty_TransmissionCmd <= 8.0))) {
            // Transition: '<S2>:395'
            // Event: '<S2>:391'
            b_previousEvent = TCU_DW.sfEvent;
            TCU_DW.sfEvent = TCU_event_Up2;
            TCU_c1_TCU(rtu_VehSpdFdbk, rty_TransmissionCmd);
            TCU_DW.sfEvent = b_previousEvent;
            if (TCU_DW.is_SelectionState == TCU_IN_preUpShifting) {
              // Transition: '<S2>:25'
              TCU_DW.is_SelectionState = TCU_IN_SteadyState;
              // Entry 'SteadyState': '<S2>:11'
            }
          } else if ((TCU_DW.temporalCounter_i1 >= 1U) &&
                     ((*rtu_VehSpdFdbk > up_th) && (TCU_B.Gain < 0.6))) {
            // Transition: '<S2>:155'
            TCU_DW.is_SelectionState = TCU_IN_UpShifting;
            // Entry 'UpShifting': '<S2>:13'
          } else {
            if (*rtu_VehSpdFdbk <= up_th) {
              // Transition: '<S2>:164'
              // Transition: '<S2>:156'
              TCU_DW.is_SelectionState = TCU_IN_SteadyState;
              // Entry 'SteadyState': '<S2>:11'
            }
          }
          break;
      }
    }
  }
  // End of Chart: '<Root>/TCM Shift Controller'
}
// System initialize for referenced model: 'TCU'
void TCUModelClass::init(real_T *rty_TransmissionCmd) {
  TCU_DW.sfEvent = TCU_CALL_EVENT;
  TCU_DW.is_active_GearState = 0U;
  TCU_DW.is_GearState = TCU_IN_NO_ACTIVE_CHILD;
  TCU_DW.is_active_SelectionState = 0U;
  TCU_DW.is_SelectionState = TCU_IN_NO_ACTIVE_CHILD;
  TCU_DW.temporalCounter_i1 = 0U;
  TCU_DW.is_active_c1_TCU = 0U;
  *rty_TransmissionCmd = 0.0;
  // SystemInitialize for Chart: '<Root>/TCM Shift Controller' incorporates:
  //   SubSystem: '<S2>/calc_up'
  // SystemInitialize for Outport: '<S5>/up_th'
  TCU_B.CalculateUpshiftThreshold = TCU_rtP.up_th_Y0;
  // SystemInitialize for Chart: '<Root>/TCM Shift Controller' incorporates:
  //   SubSystem: '<S2>/calc_down'
  // SystemInitialize for Outport: '<S4>/down_th'
  TCU_B.CalculateDownshiftThreshold = TCU_rtP.down_th_Y0;
  // SystemInitialize for Chart: '<Root>/TCM Shift Controller' incorporates:
  //   SubSystem: '<S2>/calc'
  TCU_calc_Init(&TCU_B.Add4, &TCU_rtP.calc);
}
// Output and update for referenced model: 'TCU'
void TCUModelClass::step(const real_T *rtu_pedalPos_pct,
                         const real_T *rtu_VehSpdFdbk,
                         const real_T *rtu_EngSpdFdbk_rpm,
                         real_T *rty_TransmissionCmd) {
  // Gain: '<Root>/Gain'
  TCU_B.Gain = TCU_rtP.Gain_Gain * *rtu_pedalPos_pct;
  // RelationalOperator: '<S1>/Relational Operator1' incorporates:
  //   Constant: '<S1>/Constant1'
  TCU_B.RelationalOperator1 = (TCU_B.Gain <= TCU_rtP.Constant1_Value);
  // RelationalOperator: '<S1>/Relational Operator' incorporates:
  //   Constant: '<S1>/Constant'
  TCU_B.RelationalOperator = (*rtu_EngSpdFdbk_rpm <= TCU_rtP.Constant_Value);
  // Logic: '<S1>/Logical Operator'
  TCU_B.LogicalOperator =
      (TCU_B.RelationalOperator1 && TCU_B.RelationalOperator);
  // Chart: '<Root>/TCM Shift Controller'
  if (TCU_DW.temporalCounter_i1 < 511U) {
    TCU_DW.temporalCounter_i1 =
        static_cast<uint16_T>((TCU_DW.temporalCounter_i1 + 1U));
  }
  // Gateway: TCM Shift Controller
  TCU_DW.sfEvent = TCU_CALL_EVENT;
  TCU_c1_TCU(rtu_VehSpdFdbk, rty_TransmissionCmd);
  // End of Chart: '<Root>/TCM Shift Controller'
}
// Model initialize function
void TCUModelClass::initialize() {
  // Registration code
  // block I/O
  (void)std::memset((static_cast<void *>(&TCU_B)), 0, sizeof(B_TCU_T));
  {
    TCU_B.Gain = 0.0;
    TCU_B.gear = 0.0;
    TCU_B.pedal = 0.0;
    TCU_B.gear_i = 0.0;
    TCU_B.pedal_h = 0.0;
    TCU_B.gear_a = 0.0;
    TCU_B.pedal_b = 0.0;
    TCU_B.speed = 0.0;
    TCU_B.Add4 = 0.0;
    TCU_B.CalculateDownshiftThreshold = 0.0;
    TCU_B.CalculateUpshiftThreshold = 0.0;
    TCU_B.calc.CalculateUpshiftThreshold1 = 0.0;
    TCU_B.calc.Add1 = 0.0;
    TCU_B.calc.CalculateDownshiftThreshold = 0.0;
    TCU_B.calc.Add3 = 0.0;
  }
  // states (dwork)
  (void)std::memset(static_cast<void *>(&TCU_DW), 0, sizeof(DW_TCU_T));
}
// Constructor
TCUModelClass::TCUModelClass() {
  // Currently there is no constructor body generated.
}
// Destructor
TCUModelClass::~TCUModelClass() {
  // Currently there is no destructor body generated.
}
// Real-Time Model get method
RT_MODEL_TCU_T *TCUModelClass::getRTM() { return (&TCU_M); }
// member function to setup error status pointer
void TCUModelClass::setErrorStatusPointer(const char_T **rt_errorStatus) {
  rtmSetErrorStatusPointer((&TCU_M), rt_errorStatus);
}
//
// File trailer for generated code.
//
// [EOF]
//
