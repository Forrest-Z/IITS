//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: Braking.h
//
// Code generated for Simulink model 'Braking'.
//
// Model version                  : 1.19
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Thu Jul  9 18:39:10 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Windows64)
// Code generation objectives:
//    1. Traceability
//    2. Debugging
// Validation result: Not run
//
#ifndef RTW_HEADER_Braking_h_
#define RTW_HEADER_Braking_h_
#include <cmath>
#include <cstring>
#include <stddef.h>
#ifndef Braking_COMMON_INCLUDES_
# define Braking_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 // Braking_COMMON_INCLUDES_

#include "Braking_types.h"
#include <stddef.h>
#include "rtGetInf.h"
#include "rt_nonfinite.h"

// Block signals for model 'Braking'
typedef struct {
  real_T Switch1;                      // '<S14>/Switch1'
  real_T Saturation1;                  // '<S14>/Saturation1'
  real_T Abs1;                         // '<S14>/Abs1'
  real_T UnitDelay;                    // '<S17>/Unit Delay'
  real_T Switch;                       // '<S17>/Switch'
  real_T Switch2;                      // '<S18>/Switch2'
  real_T Switch_b;                     // '<S14>/Switch'
  real_T BraCmdCtrl_mps2;              // '<S14>/Gain'
  real_T BackAxleBrakePressure;        // '<S15>/Back Axle Brake Pressure'
  real_T bwdWhlPreCmd_Kpa;             // '<S15>/Gain1'
  real_T bwdWhlPre_Mpa;                // '<Root>/Unit Delay'
  real_T ManualSwitch;                 // '<S1>/Manual Switch'
  real_T BwdWhlBraPreRate_Kpas;        // '<S1>/Switch'
  real_T TrailPreGain;                 // '<S15>/TrailPreGain'
  real_T TrailWhlPreCmd_Kpa;           // '<S15>/Product'
  real_T TrailAllWhlPre_Mpa;           // '<Root>/Unit Delay'
  real_T ManualSwitch_b;               // '<S2>/Manual Switch'
  real_T TrailWhlBraPreRate_Kpas;      // '<S2>/Switch'
  real_T forwardAxleBrakePressure1;    // '<S15>/forward Axle Brake Pressure1'
  real_T fwdWhlPreCmd_Kpa;             // '<S15>/Gain'
  real_T fwdAllWhlPre_Mpa;             // '<Root>/Unit Delay'
  real_T ManualSwitch_p;               // '<S3>/Manual Switch'
  real_T FwdWhlBraPreRate_Kpas;        // '<S3>/Switch'
  real_T UpLimit_bwd;                  // '<S6>/Switch'
  real_T UnitDelay_d;                  // '<S25>/Unit Delay'
  real_T Switch_e;                     // '<S25>/Switch'
  real_T Switch2_c;                    // '<S28>/Switch2'
  real_T bwdWhlPre_Mpa_m;              // '<S6>/Gain1'
  real_T UpLimit_bwd_d;                // '<S6>/Switch4'
  real_T UnitDelay_c;                  // '<S27>/Unit Delay'
  real_T Switch_n;                     // '<S27>/Switch'
  real_T Switch2_o;                    // '<S30>/Switch2'
  real_T TrailAllWhlPre_Mpa_d;         // '<S6>/Gain2'
  real_T UpLimit_bwd_n;                // '<S6>/Switch2'
  real_T UnitDelay_e;                  // '<S26>/Unit Delay'
  real_T Switch_e5;                    // '<S26>/Switch'
  real_T Switch2_k;                    // '<S29>/Switch2'
  real_T fwdAllWhlPre_Mpa_b;           // '<S6>/Gain3'
  real_T LowLimit_bwd;                 // '<S6>/Switch5'
  real_T Switch_d;                     // '<S30>/Switch'
  real_T Product;                      // '<S27>/Product'
  real_T Add1;                         // '<S27>/Add1'
  real_T LowLimit_bwd_k;               // '<S6>/Switch3'
  real_T Switch_c;                     // '<S29>/Switch'
  real_T Product_p;                    // '<S26>/Product'
  real_T Add1_a;                       // '<S26>/Add1'
  real_T LowLimit_bwd_i;               // '<S6>/Switch1'
  real_T Switch_cu;                    // '<S28>/Switch'
  real_T Product_k;                    // '<S25>/Product'
  real_T Add1_m;                       // '<S25>/Add1'
  real_T Switch_a;                     // '<S18>/Switch'
  real_T Saturation;                   // '<S14>/Saturation'
  real_T Abs;                          // '<S14>/Abs'
  real_T aErr;                         // '<S14>/Subtract1'
  real_T Gain6;                        // '<S14>/Gain6'
  real_T Product_l;                    // '<S17>/Product'
  real_T Add1_j;                       // '<S17>/Add1'
  real_T Kf;                           // '<S14>/Kf'
  real_T Gain1;                        // '<S14>/Gain1'
  real_T Add3;                         // '<S14>/Add3'
  real_T Gain;                         // '<S3>/Gain'
  real_T FwdPreErr_Kpa;                // '<S3>/Subtract'
  real_T FwdWhlBraPreRate_Kpas_m;      // '<S3>/Switch1'
  real_T BwdWhlBraPreRate_Kpas_j;      // '<S3>/Switch2'
  real_T TrailPreErr_Kpa;              // '<S2>/Subtract'
  real_T TrailWhlBraPreRate_Kpas_f;    // '<S2>/Switch1'
  real_T BwdWhlBraPreRate_Kpas_b;      // '<S2>/Switch2'
  real_T Subtract;                     // '<S1>/Subtract'
  real_T BwdWhlBraPreRate_Kpas_k;      // '<S1>/Switch1'
  real_T BwdWhlBraPreRate_Kpas_l;      // '<S1>/Switch2'
  boolean_T UnitDelay1;                // '<S17>/Unit Delay1'
  boolean_T Compare;                   // '<S4>/Compare'
  boolean_T LowerRelop1;               // '<S18>/LowerRelop1'
  boolean_T Compare_j;                 // '<S16>/Compare'
  boolean_T Compare_c;                 // '<S19>/Compare'
  boolean_T Compare_n;                 // '<S21>/Compare'
  boolean_T Compare_i;                 // '<S23>/Compare'
  boolean_T UnitDelay1_a;              // '<S25>/Unit Delay1'
  boolean_T LowerRelop1_c;             // '<S28>/LowerRelop1'
  boolean_T UnitDelay1_ah;             // '<S27>/Unit Delay1'
  boolean_T LowerRelop1_o;             // '<S30>/LowerRelop1'
  boolean_T UnitDelay1_m;              // '<S26>/Unit Delay1'
  boolean_T LowerRelop1_g;             // '<S29>/LowerRelop1'
  boolean_T Compare_d;                 // '<S24>/Compare'
  boolean_T UpperRelop;                // '<S30>/UpperRelop'
  boolean_T Compare_a;                 // '<S22>/Compare'
  boolean_T UpperRelop_h;              // '<S29>/UpperRelop'
  boolean_T Compare_h;                 // '<S20>/Compare'
  boolean_T UpperRelop_o;              // '<S28>/UpperRelop'
  boolean_T UpperRelop_b;              // '<S18>/UpperRelop'
  boolean_T Compare_au;                // '<S12>/Compare'
  boolean_T Compare_k;                 // '<S13>/Compare'
  boolean_T Compare_o;                 // '<S10>/Compare'
  boolean_T Compare_as;                // '<S11>/Compare'
  boolean_T Compare_ae;                // '<S8>/Compare'
  boolean_T Compare_km;                // '<S9>/Compare'
} B_Braking_T;

// Block states (default storage) for model 'Braking'
typedef struct {
  real_T UnitDelay_DSTATE;             // '<S17>/Unit Delay'
  real_T UnitDelay_2_DSTATE;           // '<Root>/Unit Delay'
  real_T UnitDelay_3_DSTATE;           // '<Root>/Unit Delay'
  real_T UnitDelay_1_DSTATE;           // '<Root>/Unit Delay'
  real_T UnitDelay_DSTATE_a;           // '<S25>/Unit Delay'
  real_T UnitDelay_DSTATE_n;           // '<S27>/Unit Delay'
  real_T UnitDelay_DSTATE_h;           // '<S26>/Unit Delay'
  boolean_T UnitDelay1_DSTATE;         // '<S17>/Unit Delay1'
  boolean_T UnitDelay1_DSTATE_k;       // '<S25>/Unit Delay1'
  boolean_T UnitDelay1_DSTATE_p;       // '<S27>/Unit Delay1'
  boolean_T UnitDelay1_DSTATE_m;       // '<S26>/Unit Delay1'
} DW_Braking_T;

// Parameters (default storage)
struct P_Braking_T_ {
  real_T CompareToConstant_const;     // Mask Parameter: CompareToConstant_const
                                         //  Referenced by: '<S4>/Constant'

  real_T CompareToConstant_const_n; // Mask Parameter: CompareToConstant_const_n
                                       //  Referenced by: '<S16>/Constant'

  real_T CompareToConstant1_const;   // Mask Parameter: CompareToConstant1_const
                                        //  Referenced by: '<S8>/Constant'

  real_T CompareToConstant2_const;   // Mask Parameter: CompareToConstant2_const
                                        //  Referenced by: '<S9>/Constant'

  real_T CompareToConstant1_const_l;
                                   // Mask Parameter: CompareToConstant1_const_l
                                      //  Referenced by: '<S10>/Constant'

  real_T CompareToConstant2_const_f;
                                   // Mask Parameter: CompareToConstant2_const_f
                                      //  Referenced by: '<S11>/Constant'

  real_T CompareToConstant1_const_o;
                                   // Mask Parameter: CompareToConstant1_const_o
                                      //  Referenced by: '<S12>/Constant'

  real_T CompareToConstant2_const_h;
                                   // Mask Parameter: CompareToConstant2_const_h
                                      //  Referenced by: '<S13>/Constant'

  real_T CompareToConstant_const_n5;
                                   // Mask Parameter: CompareToConstant_const_n5
                                      //  Referenced by: '<S19>/Constant'

  real_T CompareToConstant1_const_ld;
                                  // Mask Parameter: CompareToConstant1_const_ld
                                     //  Referenced by: '<S20>/Constant'

  real_T CompareToConstant2_const_j;
                                   // Mask Parameter: CompareToConstant2_const_j
                                      //  Referenced by: '<S21>/Constant'

  real_T CompareToConstant3_const;   // Mask Parameter: CompareToConstant3_const
                                        //  Referenced by: '<S22>/Constant'

  real_T CompareToConstant4_const;   // Mask Parameter: CompareToConstant4_const
                                        //  Referenced by: '<S23>/Constant'

  real_T CompareToConstant5_const;   // Mask Parameter: CompareToConstant5_const
                                        //  Referenced by: '<S24>/Constant'

  real_T Constant3_Value;              // Expression: 0
                                          //  Referenced by: '<S1>/Constant3'

  real_T Constant_Value;               // Expression: 1
                                          //  Referenced by: '<S1>/Constant'

  real_T Constant3_Value_n;            // Expression: 0
                                          //  Referenced by: '<S2>/Constant3'

  real_T Constant_Value_i;             // Expression: 1
                                          //  Referenced by: '<S2>/Constant'

  real_T Constant3_Value_o;            // Expression: 0
                                          //  Referenced by: '<S3>/Constant3'

  real_T Gain_Gain;                    // Expression: 1000
                                          //  Referenced by: '<S3>/Gain'

  real_T Constant_Value_b;             // Expression: 1
                                          //  Referenced by: '<S3>/Constant'

  real_T Constant1_Value;              // Expression: 0
                                          //  Referenced by: '<S14>/Constant1'

  real_T Constant2_Value;              // Expression: 0
                                          //  Referenced by: '<S14>/Constant2'

  real_T Kf_Gain;                      // Expression: 1
                                          //  Referenced by: '<S14>/Kf'

  real_T Gain1_Gain;                   // Expression: 1
                                          //  Referenced by: '<S14>/Gain1'

  real_T Saturation_UpperSat;          // Expression: 0
                                          //  Referenced by: '<S14>/Saturation'

  real_T Saturation_LowerSat;          // Expression: -inf
                                          //  Referenced by: '<S14>/Saturation'

  real_T Gain6_Gain;                   // Expression: 1
                                          //  Referenced by: '<S14>/Gain6'

  real_T Constant3_Value_l;            // Expression: 0
                                          //  Referenced by: '<S14>/Constant3'

  real_T Constant6_Value;              // Expression: 0
                                          //  Referenced by: '<S14>/Constant6'

  real_T Constant13_Value;             // Expression: 1500
                                          //  Referenced by: '<S6>/Constant13'

  real_T Constant11_Value;             // Expression: 1500
                                          //  Referenced by: '<S6>/Constant11'

  real_T Constant_Value_p;             // Expression: 1500
                                          //  Referenced by: '<S6>/Constant'

  real_T Constant3_Value_b;            // Expression: 0.01
                                          //  Referenced by: '<S6>/Constant3'

  real_T Constant2_Value_m;            // Expression: 0
                                          //  Referenced by: '<S6>/Constant2'

  real_T Constant1_Value_c;            // Expression: 0
                                          //  Referenced by: '<S6>/Constant1'

  real_T Constant7_Value;              // Expression: 0.01
                                          //  Referenced by: '<S6>/Constant7'

  real_T Constant6_Value_l;            // Expression: 0
                                          //  Referenced by: '<S6>/Constant6'

  real_T Constant12_Value;             // Expression: 0
                                          //  Referenced by: '<S6>/Constant12'

  real_T Constant10_Value;             // Expression: 0.01
                                          //  Referenced by: '<S6>/Constant10'

  real_T Constant9_Value;              // Expression: 0
                                          //  Referenced by: '<S6>/Constant9'

  real_T Constant14_Value;             // Expression: 0
                                          //  Referenced by: '<S6>/Constant14'

  real_T Constant5_Value;              // Expression: 1.5
                                          //  Referenced by: '<S14>/Constant5'

  real_T Saturation1_UpperSat;         // Expression: 0
                                          //  Referenced by: '<S14>/Saturation1'

  real_T Saturation1_LowerSat;         // Expression: -inf
                                          //  Referenced by: '<S14>/Saturation1'

  real_T UnitDelay_InitialCondition;   // Expression: 0
                                          //  Referenced by: '<S17>/Unit Delay'

  real_T Gain_Gain_g;                  // Expression: -1
                                          //  Referenced by: '<S14>/Gain'

  real_T Gain1_Gain_h;                 // Expression: 0.7
                                          //  Referenced by: '<S15>/Gain1'

  real_T UnitDelay_2_InitialCondition; // Expression: 0
                                          //  Referenced by: '<Root>/Unit Delay'

  real_T TrailPreGain_tableData[2];    // Expression: [1.1 1.4]
                                          //  Referenced by: '<S15>/TrailPreGain'

  real_T TrailPreGain_bp01Data[2];     // Expression: [1 1.5]
                                          //  Referenced by: '<S15>/TrailPreGain'

  real_T UnitDelay_3_InitialCondition; // Expression: 0
                                          //  Referenced by: '<Root>/Unit Delay'

  real_T Gain_Gain_j;                  // Expression: 0.3
                                          //  Referenced by: '<S15>/Gain'

  real_T UnitDelay_1_InitialCondition; // Expression: 0
                                          //  Referenced by: '<Root>/Unit Delay'

  real_T UnitDelay_InitialCondition_e; // Expression: 0
                                          //  Referenced by: '<S25>/Unit Delay'

  real_T Gain1_Gain_hn;                // Expression: 0.001
                                          //  Referenced by: '<S6>/Gain1'

  real_T UnitDelay_InitialCondition_k; // Expression: 0
                                          //  Referenced by: '<S27>/Unit Delay'

  real_T Gain2_Gain;                   // Expression: 0.001
                                          //  Referenced by: '<S6>/Gain2'

  real_T UnitDelay_InitialCondition_b; // Expression: 0
                                          //  Referenced by: '<S26>/Unit Delay'

  real_T Gain3_Gain;                   // Expression: 0.001
                                          //  Referenced by: '<S6>/Gain3'

  uint32_T BackAxleBrakePressure_maxIndex[2];
                           // Computed Parameter: BackAxleBrakePressure_maxIndex
                              //  Referenced by: '<S15>/Back Axle Brake Pressure'

  uint32_T forwardAxleBrakePressure1_maxIndex[2];
                       // Computed Parameter: forwardAxleBrakePressure1_maxIndex
                          //  Referenced by: '<S15>/forward Axle Brake Pressure1'

  boolean_T UnitDelay1_InitialCondition;
                              // Computed Parameter: UnitDelay1_InitialCondition
                                 //  Referenced by: '<S17>/Unit Delay1'

  boolean_T UnitDelay1_InitialCondition_g;
                            // Computed Parameter: UnitDelay1_InitialCondition_g
                               //  Referenced by: '<S25>/Unit Delay1'

  boolean_T UnitDelay1_InitialCondition_o;
                            // Computed Parameter: UnitDelay1_InitialCondition_o
                               //  Referenced by: '<S27>/Unit Delay1'

  boolean_T UnitDelay1_InitialCondition_f;
                            // Computed Parameter: UnitDelay1_InitialCondition_f
                               //  Referenced by: '<S26>/Unit Delay1'

  uint8_T ManualSwitch_CurrentSetting;
                              // Computed Parameter: ManualSwitch_CurrentSetting
                                 //  Referenced by: '<S1>/Manual Switch'

  uint8_T ManualSwitch_CurrentSetting_m;
                            // Computed Parameter: ManualSwitch_CurrentSetting_m
                               //  Referenced by: '<S2>/Manual Switch'

  uint8_T ManualSwitch_CurrentSetting_g;
                            // Computed Parameter: ManualSwitch_CurrentSetting_g
                               //  Referenced by: '<S3>/Manual Switch'

};

// Real-time Model Data Structure
struct tag_RTM_Braking_T {
  const char_T **errorStatus;
};

// Model block global parameters (default storage)
extern struct_xuvldbp4qY393voN3kPmeB rtP_EBC;// Variable: EBC
                                                //  Referenced by:
                                                //    '<S1>/Constant1'
                                                //    '<S1>/Constant2'
                                                //    '<S2>/Constant1'
                                                //    '<S2>/Constant2'
                                                //    '<S3>/Constant1'
                                                //    '<S3>/Constant2'
                                                //    '<S15>/Back Axle Brake Pressure'
                                                //    '<S15>/forward Axle Brake Pressure1'

extern real_T rtP_dt_bra;              // Variable: dt_bra
                                          //  Referenced by: '<S14>/Constant4'


// Class declaration for model Braking
class BrakingModelClass {
  // public data and function members
 public:
  // Tunable parameters
  static P_Braking_T Braking_rtP;

  // model initialize function
  void initialize();

  // model step function
  void step(const real_T *rtu_XBR1_ExternalAccele, const real_T *rtu_ax_mps2,
            const real_T *rtu_XBR1_Ctrl_Mode, const real_T *rtu_Mass_kg, real_T
            rty_bwdWhlPre_Mpa[4], real_T rty_fwdWhlPre_Mpa[2], real_T
            rty_TrailWhlPre_Mpa[6]);

  // Initial conditions function
  void init();

  // Constructor
  BrakingModelClass();

  // Destructor
  ~BrakingModelClass();

  // Real-Time Model get method
  RT_MODEL_Braking_T * getRTM();

  //member function to setup error status pointer
  void setErrorStatusPointer(const char_T **rt_errorStatus);

  // private data and function members
 private:
  // Block signals
  B_Braking_T Braking_B;

  // Block states
  DW_Braking_T Braking_DW;

  // Real-Time Model
  RT_MODEL_Braking_T Braking_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S18>/Data Type Duplicate' : Unused code path elimination
//  Block '<S18>/Data Type Propagation' : Unused code path elimination
//  Block '<S14>/Scope' : Unused code path elimination
//  Block '<S28>/Data Type Duplicate' : Unused code path elimination
//  Block '<S28>/Data Type Propagation' : Unused code path elimination
//  Block '<S29>/Data Type Duplicate' : Unused code path elimination
//  Block '<S29>/Data Type Propagation' : Unused code path elimination
//  Block '<S30>/Data Type Duplicate' : Unused code path elimination
//  Block '<S30>/Data Type Propagation' : Unused code path elimination
//  Block '<S6>/Scope' : Unused code path elimination
//  Block '<S6>/Scope1' : Unused code path elimination
//  Block '<S7>/Constant1' : Unused code path elimination
//  Block '<S7>/Divide' : Unused code path elimination
//  Block '<S7>/Gain' : Unused code path elimination


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
//  '<Root>' : 'Braking'
//  '<S1>'   : 'Braking/ABS controller for Bwd Axle'
//  '<S2>'   : 'Braking/ABS controller for Trail Axle'
//  '<S3>'   : 'Braking/ABS controller for fwd Axle'
//  '<S4>'   : 'Braking/Compare To Constant'
//  '<S5>'   : 'Braking/EBS controller'
//  '<S6>'   : 'Braking/HydraulicBrakeSystem'
//  '<S7>'   : 'Braking/Subsystem'
//  '<S8>'   : 'Braking/ABS controller for Bwd Axle/Compare To Constant1'
//  '<S9>'   : 'Braking/ABS controller for Bwd Axle/Compare To Constant2'
//  '<S10>'  : 'Braking/ABS controller for Trail Axle/Compare To Constant1'
//  '<S11>'  : 'Braking/ABS controller for Trail Axle/Compare To Constant2'
//  '<S12>'  : 'Braking/ABS controller for fwd Axle/Compare To Constant1'
//  '<S13>'  : 'Braking/ABS controller for fwd Axle/Compare To Constant2'
//  '<S14>'  : 'Braking/EBS controller/BrakeController'
//  '<S15>'  : 'Braking/EBS controller/BrakeDistribution'
//  '<S16>'  : 'Braking/EBS controller/BrakeController/Compare To Constant'
//  '<S17>'  : 'Braking/EBS controller/BrakeController/IntergraterWiLimit'
//  '<S18>'  : 'Braking/EBS controller/BrakeController/IntergraterWiLimit/Saturation Dynamic'
//  '<S19>'  : 'Braking/HydraulicBrakeSystem/Compare To Constant'
//  '<S20>'  : 'Braking/HydraulicBrakeSystem/Compare To Constant1'
//  '<S21>'  : 'Braking/HydraulicBrakeSystem/Compare To Constant2'
//  '<S22>'  : 'Braking/HydraulicBrakeSystem/Compare To Constant3'
//  '<S23>'  : 'Braking/HydraulicBrakeSystem/Compare To Constant4'
//  '<S24>'  : 'Braking/HydraulicBrakeSystem/Compare To Constant5'
//  '<S25>'  : 'Braking/HydraulicBrakeSystem/IntergraterWiLimit'
//  '<S26>'  : 'Braking/HydraulicBrakeSystem/IntergraterWiLimit1'
//  '<S27>'  : 'Braking/HydraulicBrakeSystem/IntergraterWiLimit2'
//  '<S28>'  : 'Braking/HydraulicBrakeSystem/IntergraterWiLimit/Saturation Dynamic'
//  '<S29>'  : 'Braking/HydraulicBrakeSystem/IntergraterWiLimit1/Saturation Dynamic'
//  '<S30>'  : 'Braking/HydraulicBrakeSystem/IntergraterWiLimit2/Saturation Dynamic'

#endif                                 // RTW_HEADER_Braking_h_

//
// File trailer for generated code.
//
// [EOF]
//
