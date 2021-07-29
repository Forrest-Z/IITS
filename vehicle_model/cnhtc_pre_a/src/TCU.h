//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: TCU.h
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
#ifndef SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_TCU_H_
#define SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_TCU_H_
#include <stddef.h>

#include <cmath>
#include <cstring>
#ifndef TCU_COMMON_INCLUDES_
#define TCU_COMMON_INCLUDES_
#include "rtwtypes.h"  // NOLINT
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif  // TCU_COMMON_INCLUDES_
#include "TCU_types.h"

// Block signals for system '<S2>/calc'
typedef struct {
  real_T CalculateUpshiftThreshold1;   // '<S3>/Calculate Upshift Threshold1'
  real_T Add1;                         // '<S3>/Add1'
  real_T CalculateDownshiftThreshold;  // '<S3>/Calculate  Downshift Threshold'
  real_T Add3;                         // '<S3>/Add3'
} B_calc_TCU_T;
// Block signals for model 'TCU'
typedef struct {
  real_T Gain;                         // '<Root>/Gain'
  real_T gear;                         // '<Root>/TCM Shift Controller'
  real_T pedal;                        // '<Root>/TCM Shift Controller'
  real_T gear_i;                       // '<Root>/TCM Shift Controller'
  real_T pedal_h;                      // '<Root>/TCM Shift Controller'
  real_T gear_a;                       // '<Root>/TCM Shift Controller'
  real_T pedal_b;                      // '<Root>/TCM Shift Controller'
  real_T speed;                        // '<Root>/TCM Shift Controller'
  real_T Add4;                         // '<S3>/Add4'
  real_T CalculateDownshiftThreshold;  // '<S4>/Calculate  Downshift Threshold'
  real_T CalculateUpshiftThreshold;    // '<S5>/Calculate Upshift Threshold'
  boolean_T RelationalOperator1;       // '<S1>/Relational Operator1'
  boolean_T RelationalOperator;        // '<S1>/Relational Operator'
  boolean_T LogicalOperator;           // '<S1>/Logical Operator'
  B_calc_TCU_T calc;                   // '<S2>/calc'
} B_TCU_T;
// Block states (default storage) for model 'TCU'
typedef struct {
  int32_T sfEvent;                   // '<Root>/TCM Shift Controller'
  uint16_T temporalCounter_i1;       // '<Root>/TCM Shift Controller'
  uint8_T is_active_c1_TCU;          // '<Root>/TCM Shift Controller'
  uint8_T is_GearState;              // '<Root>/TCM Shift Controller'
  uint8_T is_active_GearState;       // '<Root>/TCM Shift Controller'
  uint8_T is_SelectionState;         // '<Root>/TCM Shift Controller'
  uint8_T is_active_SelectionState;  // '<Root>/TCM Shift Controller'
} DW_TCU_T;
// Parameters for system: '<S2>/calc'
struct P_calc_TCU_T_ {
  real_T SpdThr_Y0;  // Computed Parameter: SpdThr_Y0
                     //  Referenced by: '<S3>/SpdThr'
  uint32_T CalculateUpshiftThreshold1_maxIndex[2];
  // Computed Parameter: CalculateUpshiftThreshold1_maxIndex
  //  Referenced by: '<S3>/Calculate Upshift Threshold1'
  uint32_T CalculateDownshiftThreshold_maxIndex[2];
  // Computed Parameter: CalculateDownshiftThreshold_maxIndex
  //  Referenced by: '<S3>/Calculate  Downshift Threshold'
};
// Parameters (default storage)
struct P_TCU_T_ {
  real_T up_th_Y0;         // Computed Parameter: up_th_Y0
                           //  Referenced by: '<S5>/up_th'
  real_T down_th_Y0;       // Computed Parameter: down_th_Y0
                           //  Referenced by: '<S4>/down_th'
  real_T Gain_Gain;        // Expression: 1/100
                           //  Referenced by: '<Root>/Gain'
  real_T Constant_Value;   // Expression: 1200
                           //  Referenced by: '<S1>/Constant'
  real_T Constant1_Value;  // Expression: 1e-6
                           //  Referenced by: '<S1>/Constant1'
  uint32_T CalculateUpshiftThreshold_maxIndex[2];
  // Computed Parameter: CalculateUpshiftThreshold_maxIndex
  //  Referenced by: '<S5>/Calculate Upshift Threshold'
  uint32_T CalculateDownshiftThreshold_maxIndex[2];
  // Computed Parameter: CalculateDownshiftThreshold_maxIndex
  //  Referenced by: '<S4>/Calculate  Downshift Threshold'
  P_calc_TCU_T calc;  // '<S2>/calc'
};
// Real-time Model Data Structure
struct tag_RTM_TCU_T {
  const char_T **errorStatus;
};
// Model block global parameters (default storage)
extern real_T rtP_DnShiftSpdTa[99];  // Variable: DnShiftSpdTa
                                     //  Referenced by:
                                     //    '<S3>/Calculate  Downshift Threshold'
                                     //    '<S4>/Calculate  Downshift Threshold'
extern real_T
    rtP_ShiftDnTa_Bp_GearPos[11];  // Variable: ShiftDnTa_Bp_GearPos
                                   //  Referenced by:
                                   //    '<S3>/Calculate  Downshift Threshold'
                                   //    '<S4>/Calculate  Downshift Threshold'
extern real_T
    rtP_ShiftDnTa_Bp_PedPos[9];  // Variable: ShiftDnTa_Bp_PedPos
                                 //  Referenced by:
                                 //    '<S3>/Calculate  Downshift Threshold'
                                 //    '<S4>/Calculate  Downshift Threshold'
extern real_T
    rtP_ShiftUpTa_Bp_GearPos[11];  // Variable: ShiftUpTa_Bp_GearPos
                                   //  Referenced by:
                                   //    '<S3>/Calculate Upshift Threshold1'
                                   //    '<S5>/Calculate Upshift Threshold'
extern real_T
    rtP_ShiftUpTa_Bp_PedPos[10];      // Variable: ShiftUpTa_Bp_PedPos
                                      //  Referenced by:
                                      //    '<S3>/Calculate Upshift Threshold1'
                                      //    '<S5>/Calculate Upshift Threshold'
extern real_T rtP_UpshiftSpdTa[110];  // Variable: UpshiftSpdTa
                                      //  Referenced by:
                                      //    '<S3>/Calculate Upshift Threshold1'
                                      //    '<S5>/Calculate Upshift Threshold'
// Class declaration for model TCU
class TCUModelClass {
  // public data and function members
 public:
  // Tunable parameters
  static P_TCU_T TCU_rtP;
  // model initialize function
  void initialize();
  // model step function
  void step(const real_T *rtu_pedalPos_pct, const real_T *rtu_VehSpdFdbk,
            const real_T *rtu_EngSpdFdbk_rpm, real_T *rty_TransmissionCmd);
  // Initial conditions function
  void init(real_T *rty_TransmissionCmd);
  // Constructor
  TCUModelClass();
  // Destructor
  ~TCUModelClass();
  // Real-Time Model get method
  RT_MODEL_TCU_T *getRTM();
  // member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);
  // private data and function members
 private:
  // Block signals
  B_TCU_T TCU_B;
  // Block states
  DW_TCU_T TCU_DW;
  // Real-Time Model
  RT_MODEL_TCU_T TCU_M;
  // private member function(s) for subsystem '<S2>/calc'
  void TCU_calc_Init(real_T *rty_SpdThr, P_calc_TCU_T *localP);
  void TCU_calc(real_T rtu_gear, real_T rtu_pedal, real_T rtu_speed,
                real_T *rty_SpdThr, B_calc_TCU_T *localB, P_calc_TCU_T *localP);
  // private member function(s) for subsystem
  // '<Root>/TmpModelReferenceSubsystem'
  void TCU_GearState(const real_T *rtu_VehSpdFdbk, real_T *rty_TransmissionCmd);
  void TCU_c1_TCU(const real_T *rtu_VehSpdFdbk, real_T *rty_TransmissionCmd);
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
//  '<Root>' : 'TCU'
//  '<S1>'   : 'TCU/Neutral Select'
//  '<S2>'   : 'TCU/TCM Shift Controller'
//  '<S3>'   : 'TCU/TCM Shift Controller/calc'
//  '<S4>'   : 'TCU/TCM Shift Controller/calc_down'
//  '<S5>'   : 'TCU/TCM Shift Controller/calc_up'
#endif  // SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_TCU_H_
//
// File trailer for generated code.
//
// [EOF]
//
