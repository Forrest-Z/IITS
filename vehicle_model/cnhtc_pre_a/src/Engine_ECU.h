//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: Engine_ECU.h
//
// Code generated for Simulink model 'Engine_ECU'.
//
// Model version                  : 1.361
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:31 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#ifndef SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_ENGINE_ECU_H_
#define SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_ENGINE_ECU_H_
#include <stddef.h>

#include <cmath>
#include <cstring>
#ifndef Engine_ECU_COMMON_INCLUDES_
#define Engine_ECU_COMMON_INCLUDES_
#include "rtwtypes.h"  // NOLINT
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif  // Engine_ECU_COMMON_INCLUDES_
#include "Engine_ECU_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

// Block signals for system '<S1>/IdleTrgCal'
typedef struct {
  boolean_T Compare;    // '<S13>/Compare'
  boolean_T Compare_b;  // '<S10>/Compare'
  boolean_T AND;        // '<S5>/AND'
  boolean_T Compare_i;  // '<S11>/Compare'
  boolean_T Compare_k;  // '<S12>/Compare'
  boolean_T UnitDelay;  // '<S5>/Unit Delay'
  boolean_T AND2;       // '<S5>/AND2'
  boolean_T AND1;       // '<S5>/AND1'
} B_IdleTrgCal_Engine_ECU_T;
// Block states (default storage) for system '<S1>/IdleTrgCal'
typedef struct {
  boolean_T UnitDelay_DSTATE;  // '<S5>/Unit Delay'
} DW_IdleTrgCal_Engine_ECU_T;
// Block signals for system '<S1>/IdleSpdCtrl'
typedef struct {
  real_T Add;         // '<S9>/Add'
  real_T IGain;       // '<S9>/I Gain'
  real_T Product;     // '<S9>/Product'
  real_T UnitDelay;   // '<S9>/Unit Delay'
  real_T Saturation;  // '<S9>/Saturation'
  real_T Add1;        // '<S9>/Add1'
  real_T PGain;       // '<S9>/P Gain'
  real_T Add2;        // '<S9>/Add2'
} B_IdleSpdCtrl_Engine_ECU_T;
// Block states (default storage) for system '<S1>/IdleSpdCtrl'
typedef struct {
  real_T UnitDelay_DSTATE;  // '<S9>/Unit Delay'
} DW_IdleSpdCtrl_Engine_ECU_T;
// Block signals for model 'Engine_ECU'
typedef struct {
  real_T torque_map1;                      // '<Root>/torque_map1'
  real_T Product1;                         // '<S3>/Product1'
  real_T uDLookupTable;                    // '<S3>/1-D Lookup Table'
  real_T Product;                          // '<S3>/Product'
  real_T Yk1;                              // '<S19>/Delay Input2'
  real_T UkYk1;                            // '<S19>/Difference Inputs1'
  real_T Switch2;                          // '<S2>/Switch2'
  real_T sampletime;                       // '<S19>/sample time'
  real_T deltariselimit;                   // '<S19>/delta rise limit'
  real_T Switch2_d;                        // '<S20>/Switch2'
  real_T Switch1;                          // '<S2>/Switch1'
  real_T deltafalllimit;                   // '<S19>/delta fall limit'
  real_T Switch;                           // '<S20>/Switch'
  real_T EngTor;                           // '<Root>/EngineControl'
  real_T EngStatus;                        // '<Root>/EngineControl'
  real_T TrqCmd;                           // '<Root>/EngineControl'
  real_T VehSpd;                           // '<Root>/EngineControl'
  real_T PedalPos_pct;                     // '<Root>/EngineControl'
  real_T BrkCmd;                           // '<Root>/EngineControl'
  real_T EngSpd;                           // '<Root>/EngineControl'
  real_T EngSpd_f;                         // '<Root>/EngineControl'
  real_T EngTorCur_Nm;                     // '<Root>/EngineControl'
  real_T Add;                              // '<S16>/Add'
  real_T IGain;                            // '<S16>/I Gain'
  real_T Product_c;                        // '<S16>/Product'
  real_T UnitDelay;                        // '<S16>/Unit Delay'
  real_T Saturation;                       // '<S16>/Saturation'
  real_T Add1;                             // '<S16>/Add1'
  real_T PGain;                            // '<S16>/P Gain'
  real_T Add2;                             // '<S16>/Add2'
  real_T Saturation1;                      // '<S16>/Saturation1'
  real_T Saturation1_g;                    // '<S9>/Saturation1'
  int8_T DataTypeConversion;               // '<Root>/Data Type Conversion'
  int8_T DataTypeConversion1;              // '<Root>/Data Type Conversion1'
  int8_T GearSel;                          // '<Root>/EngineControl'
  int8_T GearPos;                          // '<Root>/EngineControl'
  int8_T GearSel_d;                        // '<Root>/EngineControl'
  int8_T UnitDelay1;                       // '<S7>/Unit Delay1'
  boolean_T Compare;                       // '<S17>/Compare'
  boolean_T LowerRelop1;                   // '<S20>/LowerRelop1'
  boolean_T Compare_f;                     // '<S18>/Compare'
  boolean_T UpperRelop;                    // '<S20>/UpperRelop'
  boolean_T ClutchLock;                    // '<Root>/EngineControl'
  boolean_T AND3;                          // '<S5>/AND3'
  boolean_T RelationalOperator1;           // '<S7>/Relational Operator1'
  boolean_T Compare_o;                     // '<S15>/Compare'
  boolean_T AND;                           // '<S7>/AND'
  boolean_T RelationalOperator;            // '<S6>/Relational Operator'
  boolean_T Compare_g;                     // '<S14>/Compare'
  boolean_T AND_j;                         // '<S6>/AND'
  B_IdleSpdCtrl_Engine_ECU_T IdleSpdCtrl;  // '<S1>/IdleSpdCtrl'
  B_IdleTrgCal_Engine_ECU_T IdleTrgCal;    // '<S1>/IdleTrgCal'
} B_Engine_ECU_T;
// Block states (default storage) for model 'Engine_ECU'
typedef struct {
  real_T DelayInput2_DSTATE;                // '<S19>/Delay Input2'
  real_T UnitDelay_DSTATE;                  // '<S16>/Unit Delay'
  uint16_T temporalCounter_i1;              // '<Root>/EngineControl'
  int8_T UnitDelay1_DSTATE;                 // '<S7>/Unit Delay1'
  uint8_T is_active_c3_Engine_ECU;          // '<Root>/EngineControl'
  uint8_T is_c3_Engine_ECU;                 // '<Root>/EngineControl'
  uint8_T is_Syncronize;                    // '<Root>/EngineControl'
  boolean_T ShiftDoneTrg;                   // '<Root>/EngineControl'
  boolean_T Idle_Trg;                       // '<Root>/EngineControl'
  boolean_T GearShiftTrg;                   // '<Root>/EngineControl'
  DW_IdleSpdCtrl_Engine_ECU_T IdleSpdCtrl;  // '<S1>/IdleSpdCtrl'
  DW_IdleTrgCal_Engine_ECU_T IdleTrgCal;    // '<S1>/IdleTrgCal'
} DW_Engine_ECU_T;
// Parameters for system: '<S1>/IdleTrgCal'
struct P_IdleTrgCal_Engine_ECU_T_ {
  real_T CompareToConstant4_const;  // Mask Parameter: CompareToConstant4_const
                                    //  Referenced by: '<S13>/Constant'
  real_T CompareToConstant1_const;  // Mask Parameter: CompareToConstant1_const
                                    //  Referenced by: '<S10>/Constant'
  real_T CompareToConstant2_const;  // Mask Parameter: CompareToConstant2_const
                                    //  Referenced by: '<S11>/Constant'
  real_T CompareToConstant3_const;  // Mask Parameter: CompareToConstant3_const
                                    //  Referenced by: '<S12>/Constant'
  boolean_T Idle_Trg_Y0;            // Computed Parameter: Idle_Trg_Y0
                                    //  Referenced by: '<S5>/Idle_Trg'
  boolean_T UnitDelay_InitialCondition;
  // Computed Parameter: UnitDelay_InitialCondition
  //  Referenced by: '<S5>/Unit Delay'
};
// Parameters for system: '<S1>/IdleSpdCtrl'
struct P_IdleSpdCtrl_Engine_ECU_T_ {
  real_T idlecontrolspeed_Ki_idle;  // Mask Parameter: idlecontrolspeed_Ki_idle
                                    //  Referenced by: '<S9>/I Gain'
  real_T idlecontrolspeed_Kp_idle;  // Mask Parameter: idlecontrolspeed_Kp_idle
                                    //  Referenced by: '<S9>/P Gain'
  real_T idlecontrolspeed_N_idle;   // Mask Parameter: idlecontrolspeed_N_idle
                                    //  Referenced by: '<S9>/Base Idle Speed'
  real_T idlecontrolspeed_Trq_idlecmd_max;
  // Mask Parameter: idlecontrolspeed_Trq_idlecmd_max
  //  Referenced by:
  //    '<S9>/Saturation'
  //    '<S9>/Saturation1'
  real_T TrqCmd_Y0;                   // Expression: 1
                                      //  Referenced by: '<S4>/TrqCmd'
  real_T UnitDelay_InitialCondition;  // Expression: 0
                                      //  Referenced by: '<S9>/Unit Delay'
  real_T Saturation_LowerSat;         // Expression: 0
                                      //  Referenced by: '<S9>/Saturation'
  real_T Constant1_Value;             // Expression: 200
                                      //  Referenced by: '<S9>/Constant1'
  real_T Saturation1_LowerSat;        // Expression: 0
                                      //  Referenced by: '<S9>/Saturation1'
};
// Parameters (default storage)
struct P_Engine_ECU_T_ {
  real_T RevLimiterControl_EngRevLim;
  // Mask Parameter: RevLimiterControl_EngRevLim
  //  Referenced by: '<S3>/Constant'
  real_T Syncronizecontrolspeed_Ki_idle;
  // Mask Parameter: Syncronizecontrolspeed_Ki_idle
  //  Referenced by: '<S16>/I Gain'
  real_T Syncronizecontrolspeed_Kp_idle;
  // Mask Parameter: Syncronizecontrolspeed_Kp_idle
  //  Referenced by: '<S16>/P Gain'
  real_T Syncronizecontrolspeed_N_idle;
  // Mask Parameter: Syncronizecontrolspeed_N_idle
  //  Referenced by: '<S16>/Base Idle Speed'
  real_T Syncronizecontrolspeed_Trq_idlecmd_max;
  // Mask Parameter: Syncronizecontrolspeed_Trq_idlecmd_max
  //  Referenced by:
  //    '<S16>/Saturation'
  //    '<S16>/Saturation1'
  real_T CompareToConstant_const;   // Mask Parameter: CompareToConstant_const
                                    //  Referenced by: '<S17>/Constant'
  real_T CompareToConstant1_const;  // Mask Parameter: CompareToConstant1_const
                                    //  Referenced by: '<S18>/Constant'
  boolean_T CompareToConstant1_const_g;
  // Mask Parameter: CompareToConstant1_const_g
  //  Referenced by: '<S14>/Constant'
  int8_T
      CompareToConstant_const_b;  // Mask Parameter: CompareToConstant_const_b
                                  //  Referenced by: '<S15>/Constant'
  real_T TrqCmd_Y0;               // Expression: 1
                                  //  Referenced by: '<S8>/TrqCmd'
  real_T UnitDelay_InitialCondition;  // Expression: 0
                                      //  Referenced by: '<S16>/Unit Delay'
  real_T Saturation_LowerSat;         // Expression: 0
                                      //  Referenced by: '<S16>/Saturation'
  real_T Constant1_Value;             // Expression: 200
                                      //  Referenced by: '<S16>/Constant1'
  real_T Saturation1_LowerSat;        // Expression: 0
                                      //  Referenced by: '<S16>/Saturation1'
  real_T Constant4_Value;             // Expression: 2000
                                      //  Referenced by: '<S2>/Constant4'
  real_T Constant2_Value;             // Expression: 300
                                      //  Referenced by: '<S2>/Constant2'
  real_T Constant3_Value;             // Expression: -3000
                                      //  Referenced by: '<S2>/Constant3'
  real_T Constant1_Value_b;           // Expression: -800
                                      //  Referenced by: '<S2>/Constant1'
  real_T uDLookupTable_tableData[2];  // Expression: [1 0]
                                      //  Referenced by: '<S3>/1-D Lookup Table'
  real_T uDLookupTable_bp01Data[2];   // Expression: [1 1.01]
                                      //  Referenced by: '<S3>/1-D Lookup Table'
  real_T DelayInput2_InitialCondition;  // Expression: 0
                                        //  Referenced by: '<S19>/Delay Input2'
  real_T sampletime_WtEt;               // Computed Parameter: sampletime_WtEt
                                        //  Referenced by: '<S19>/sample time'
  uint32_T torque_map1_maxIndex[2];  // Computed Parameter: torque_map1_maxIndex
                                     //  Referenced by: '<Root>/torque_map1'
  boolean_T ShiftDoneTrg_Y0;         // Computed Parameter: ShiftDoneTrg_Y0
                                     //  Referenced by: '<S6>/ShiftDoneTrg'
  boolean_T GearShiftTrg_Y0;         // Computed Parameter: GearShiftTrg_Y0
                                     //  Referenced by: '<S7>/GearShiftTrg'
  int8_T UnitDelay1_InitialCondition;
  // Computed Parameter: UnitDelay1_InitialCondition
  //  Referenced by: '<S7>/Unit Delay1'
  P_IdleSpdCtrl_Engine_ECU_T IdleSpdCtrl;  // '<S1>/IdleSpdCtrl'
  P_IdleTrgCal_Engine_ECU_T IdleTrgCal;    // '<S1>/IdleTrgCal'
};
// Real-time Model Data Structure
struct tag_RTM_Engine_ECU_T {
  const char_T **errorStatus;
};
// Model block global parameters (default storage)
extern real_T rtP_EngTorBp_ne[15];   // Variable: EngTorBp_ne
                                     //  Referenced by: '<Root>/torque_map1'
extern real_T rtP_EngTorBp_ped[16];  // Variable: EngTorBp_ped
                                     //  Referenced by: '<Root>/torque_map1'
extern real_T rtP_EngTorTable[240];  // Variable: EngTorTable
                                     //  Referenced by: '<Root>/torque_map1'
extern real_T rtP_dt_ECU;            // Variable: dt_ECU
                                     //  Referenced by:
                                     //    '<S9>/Constant'
                                     //    '<S16>/Constant'
// Class declaration for model Engine_ECU
class Engine_ECUModelClass {
  // public data and function members
 public:
  // Tunable parameters
  static P_Engine_ECU_T Engine_ECU_rtP;
  // model initialize function
  void initialize();
  // model step function
  void step(const real_T *rtu_EngSpd_rpm, const real_T *rtu_VehSpd_kmph,
            const real_T *rtu_BrkCmd, const real_T *rtu_PedalPos_pct,
            const boolean_T *rtu_ClutchLock, const real_T *rtu_GearSel,
            const real_T *rtu_GearPos, real_T *rty_TrqCmd);
  // Initial conditions function
  void init();
  // model disable function
  void disable();
  // Constructor
  Engine_ECUModelClass();
  // Destructor
  ~Engine_ECUModelClass();
  // Real-Time Model get method
  RT_MODEL_Engine_ECU_T *getRTM();
  // member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);
  // private data and function members
 private:
  // Block signals
  B_Engine_ECU_T Engine_ECU_B;
  // Block states
  DW_Engine_ECU_T Engine_ECU_DW;
  // Real-Time Model
  RT_MODEL_Engine_ECU_T Engine_ECU_M;
  // private member function(s) for subsystem '<S1>/IdleTrgCal'
  void Engine_ECU_IdleTrgCal_Init(boolean_T *rty_Idle_Trg,
                                  DW_IdleTrgCal_Engine_ECU_T *localDW,
                                  P_IdleTrgCal_Engine_ECU_T *localP);
  void Engine_ECU_IdleTrgCal(real_T rtu_TrqCmd, real_T rtu_VehSpd,
                             real_T rtu_PedalPos_pct, real_T rtu_BrkCmd,
                             boolean_T *rty_Idle_Trg,
                             B_IdleTrgCal_Engine_ECU_T *localB,
                             DW_IdleTrgCal_Engine_ECU_T *localDW,
                             P_IdleTrgCal_Engine_ECU_T *localP);
  // private member function(s) for subsystem '<S1>/IdleSpdCtrl'
  void Engine_ECU_IdleSpdCtrl_Init(real_T *rty_TrqCmd,
                                   DW_IdleSpdCtrl_Engine_ECU_T *localDW,
                                   P_IdleSpdCtrl_Engine_ECU_T *localP);
  void Engine_ECU_IdleSpdCtrl_Disable(real_T *rty_TrqCmd,
                                      P_IdleSpdCtrl_Engine_ECU_T *localP);
  void Engine_ECU_IdleSpdCtrl(real_T rtu_EngSpd, real_T *rty_TrqCmd,
                              B_IdleSpdCtrl_Engine_ECU_T *localB,
                              DW_IdleSpdCtrl_Engine_ECU_T *localDW,
                              P_IdleSpdCtrl_Engine_ECU_T *localP);
};
//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S4>/Scope' : Unused code path elimination
//  Block '<S8>/Scope' : Unused code path elimination
//  Block '<S19>/FixPt Data Type Duplicate' : Unused code path elimination
//  Block '<S20>/Data Type Duplicate' : Unused code path elimination
//  Block '<S20>/Data Type Propagation' : Unused code path elimination
//  Block '<S3>/Constant1' : Unused code path elimination
//  Block '<S3>/Relational Operator' : Unused code path elimination
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
//  '<Root>' : 'Engine_ECU'
//  '<S1>'   : 'Engine_ECU/EngineControl'
//  '<S2>'   : 'Engine_ECU/RateLimit'
//  '<S3>'   : 'Engine_ECU/Rev Limiter Control'
//  '<S4>'   : 'Engine_ECU/EngineControl/IdleSpdCtrl'
//  '<S5>'   : 'Engine_ECU/EngineControl/IdleTrgCal'
//  '<S6>'   : 'Engine_ECU/EngineControl/ShiftDoneCal'
//  '<S7>'   : 'Engine_ECU/EngineControl/ShiftUpCal'
//  '<S8>'   : 'Engine_ECU/EngineControl/SyncSpdCtrl'
//  '<S9>'   : 'Engine_ECU/EngineControl/IdleSpdCtrl/idle control speed'
//  '<S10>'  : 'Engine_ECU/EngineControl/IdleTrgCal/Compare To Constant1'
//  '<S11>'  : 'Engine_ECU/EngineControl/IdleTrgCal/Compare To Constant2'
//  '<S12>'  : 'Engine_ECU/EngineControl/IdleTrgCal/Compare To Constant3'
//  '<S13>'  : 'Engine_ECU/EngineControl/IdleTrgCal/Compare To Constant4'
//  '<S14>'  : 'Engine_ECU/EngineControl/ShiftDoneCal/Compare To Constant1'
//  '<S15>'  : 'Engine_ECU/EngineControl/ShiftUpCal/Compare To Constant'
//  '<S16>'  : 'Engine_ECU/EngineControl/SyncSpdCtrl/Syncronize control speed'
//  '<S17>'  : 'Engine_ECU/RateLimit/Compare To Constant'
//  '<S18>'  : 'Engine_ECU/RateLimit/Compare To Constant1'
//  '<S19>'  : 'Engine_ECU/RateLimit/Rate Limiter Dynamic'
//  '<S20>'  : 'Engine_ECU/RateLimit/Rate Limiter Dynamic/Saturation Dynamic'

#endif  // SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_ENGINE_ECU_H_
//
// File trailer for generated code.
//
// [EOF]
//
