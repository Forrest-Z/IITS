//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: cnhtc_pre_a_vehicle_model.h
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
#ifndef SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_H_
#define SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_H_
#include <cmath>
#include <cstring>
#ifndef cnhtc_pre_a_vehicle_model_COMMON_INCLUDES_
#define cnhtc_pre_a_vehicle_model_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "zero_crossing_types.h"
#endif  // cnhtc_pre_a_vehicle_model_COMMON_INCLUDES_
#include "cnhtc_pre_a_vehicle_model_types.h"
// Child system includes
#include "Braking.h"
#include "Engine_ECU.h"
#include "SteerWhlMdl.h"
#include "TCU.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rt_zcfcn.h"
// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm) ((rtm)->errorStatus)
#endif
#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val) ((rtm)->errorStatus = (val))
#endif
#ifndef rtmGetErrorStatusPointer
#define rtmGetErrorStatusPointer(rtm) ((const char_T **)(&((rtm)->errorStatus)))
#endif
#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm) ((rtm)->Timing.stopRequestedFlag)
#endif
#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif
#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm) (&((rtm)->Timing.stopRequestedFlag))
#endif
#ifndef rtmGetT
#define rtmGetT(rtm) (rtmGetTPtr((rtm))[0])
#endif
#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm) ((rtm)->Timing.t)
#endif

// Block signals (default storage)
typedef struct {
  real_T Integrator1;             // '<S3>/Integrator1'
  real_T EngSpdFdbk_rpm;          // '<S1>/Unit Delay3'
  real_T EngTrq;                  // '<S111>/EngTrq Table'
  real_T Saturation;              // '<S1>/Saturation'
  real_T Add;                     // '<S1>/Add'
  real_T Abs;                     // '<S1>/Abs'
  real_T Add1;                    // '<S1>/Add1'
  real_T Divide;                  // '<S1>/Divide'
  real_T Abs1;                    // '<S1>/Abs1'
  real_T Divide1;                 // '<S1>/Divide1'
  real_T uDLookupTable;           // '<S1>/1-D Lookup Table'
  real_T Product1;                // '<S1>/Product1'
  real_T UnitDelay1_k;            // '<Root>/Unit Delay1'
  real_T Integrator;              // '<S5>/Integrator'
  real_T Memory;                  // '<S117>/Memory'
  real_T domega_o;                // '<S116>/domega_o'
  real_T Integrator_e;            // '<S117>/Integrator'
  real_T Gain2;                   // '<S116>/Gain2'
  real_T Integrator_h;            // '<S116>/Integrator'
  real_T Gain1;                   // '<S116>/Gain1'
  real_T Subtract1;               // '<S116>/Subtract1'
  real_T UnaryMinus;              // '<S116>/Unary Minus'
  real_T Integrator_es;           // '<S30>/Integrator'
  real_T ClutchGain;              // '<S12>/ClutchGain'
  real_T Saturation_e;            // '<S31>/Saturation'
  real_T TorqueConversion;        // '<S31>/Torque Conversion'
  real_T UnitDelay;               // '<Root>/Unit Delay'
  real_T GearSel;                 // '<S1>/TCU'
  real_T Memory3;                 // '<S34>/Memory3'
  real_T Memory_e;                // '<S34>/Memory'
  real_T Add2;                    // '<S34>/Add2'
  real_T Memory1;                 // '<S34>/Memory1'
  real_T CmdGear;                 // '<S34>/Switch1'
  real_T Constant;                // '<S37>/Constant'
  real_T Integrator1_o1;          // '<S37>/Integrator1'
  real_T Integrator1_o2;          // '<S37>/Integrator1'
  real_T NewGear;                 // '<S34>/Switch2'
  real_T b;                       // '<S14>/Gear2damping'
  real_T J;                       // '<S14>/Gear2inertias'
  real_T N;                       // '<S14>/Gear2Ratios'
  real_T IC;                      // '<S16>/IC'
  real_T Switch;                  // '<S16>/Switch'
  real_T IC_a;                    // '<S17>/IC'
  real_T Switch_a;                // '<S17>/Switch'
  real_T IC_d;                    // '<S15>/IC'
  real_T Switch_f;                // '<S15>/Switch'
  real_T Merge;                   // '<S9>/Merge'
  real_T Merge1;                  // '<S9>/Merge1'
  real_T Merge2;                  // '<S9>/Merge2'
  real_T Merge3;                  // '<S9>/Merge3'
  real_T PwrStoredTrans;          // '<S9>/Merge4'
  real_T PwrCltchLoss;            // '<S9>/Merge4'
  real_T PwrDampLoss;             // '<S9>/Merge4'
  real_T PwrEffLoss;              // '<S9>/Merge4'
  real_T Product;                 // '<S12>/Product'
  real_T upi;                     // '<S12>/2*pi'
  real_T Switch_i;                // '<S12>/Switch'
  real_T Sum;                     // '<S30>/Sum'
  real_T Product_e;               // '<S30>/Product'
  real_T Ratioofstatictokinetic;  // '<S31>/Ratio of static to kinetic'
  real_T Memory1_c;               // '<S37>/Memory1'
  real_T UnaryMinus2;             // '<S37>/Unary Minus2'
  real_T Memory1_j;               // '<S38>/Memory1'
  real_T Switch1;                 // '<S38>/Switch1'
  real_T Memory2;                 // '<S37>/Memory2'
  real_T Switch1_m;               // '<S37>/Switch1'
  real_T Gain1_m;                 // '<S37>/Gain1'
  real_T IC_o;                    // '<S39>/IC'
  real_T Integrator1_o1_c;        // '<S39>/Integrator1'
  real_T Integrator1_o2_j;        // '<S39>/Integrator1'
  real_T DataTypeConversion;      // '<S39>/Data Type Conversion'
  real_T Gain1_f;                 // '<S39>/Gain1'
  real_T Abs_j;                   // '<S47>/Abs'
  real_T Product3;                // '<S47>/Product3'
  real_T Add3;                    // '<S47>/Add3'
  real_T ApparentInertiaRatio;    // '<S47>/Product8'
  real_T Product2;                // '<S12>/Product2'
  real_T Product1_j;              // '<S47>/Product1'
  real_T InputClutchDamping;      // '<S47>/Input Clutch Damping'
  real_T ApparentTransDamping;    // '<S47>/Product2'
  real_T Sum2;                    // '<S47>/Sum2'
  real_T Product4;                // '<S47>/Product4'
  real_T Sum3;                    // '<S47>/Sum3'
  real_T Abs_a;                   // '<S44>/Abs'
  real_T Abs_jd;                  // '<S48>/Abs'
  real_T Product3_g;              // '<S48>/Product3'
  real_T Add3_o;                  // '<S48>/Add3'
  real_T InputDamping;            // '<S48>/Input Damping'
  real_T Product1_e;              // '<S48>/Product1'
  real_T Product2_n;              // '<S48>/Product2'
  real_T ApparentInertiaRatio_o;  // '<S48>/Product8'
  real_T Sum2_j;                  // '<S48>/Sum2'
  real_T Product4_c;              // '<S48>/Product4'
  real_T Sum3_m;                  // '<S48>/Sum3'
  real_T Product1_a;              // '<S12>/Product1'
  real_T Sum_o;                   // '<S45>/Sum'
  real_T Abs_o;                   // '<S49>/Abs'
  real_T TrqCmd;                  // '<S1>/Engine_ECU'
  real_T Sum_l;                   // '<S3>/Sum'
  real_T Divide_p;                // '<S3>/Divide'
  real_T Memory_i;                // '<S88>/Memory'
  real_T domega_o_e;              // '<S87>/domega_o'
  real_T Integrator_o;            // '<S88>/Integrator'
  real_T Gain2_m;                 // '<S87>/Gain2'
  real_T Integrator_f;            // '<S87>/Integrator'
  real_T Gain1_l;                 // '<S87>/Gain1'
  real_T Subtract1_n;             // '<S87>/Subtract1'
  real_T Memory_k;                // '<S80>/Memory'
  real_T domega_o_p;              // '<S79>/domega_o'
  real_T Integrator_i;            // '<S80>/Integrator'
  real_T Gain2_f;                 // '<S79>/Gain2'
  real_T Integrator_op;           // '<S79>/Integrator'
  real_T Gain1_mz;                // '<S79>/Gain1'
  real_T Subtract1_d;             // '<S79>/Subtract1'
  real_T Add_m;                   // '<S4>/Add'
  real_T Gain;                    // '<S4>/Gain'
  real_T a_sim;                   // '<S4>/Divide'
  real_T v;                       // '<S4>/Integrator'
  real_T diffDir;                 // '<S66>/Switch'
  real_T VectorConcatenate[2];    // '<S62>/Vector Concatenate'
  real_T Integrator_f1[2];        // '<S62>/Integrator'
  real_T Product_m[2];            // '<S66>/Product'
  real_T Gain_i[2];               // '<S66>/Gain'
  real_T SumofElements;           // '<S66>/Sum of Elements'
  real_T UnaryMinus1[2];          // '<S66>/Unary Minus1'
  real_T Gain1_p[2];              // '<S66>/Gain1'
  real_T VectorConcatenate_e[4];  // '<S66>/Vector Concatenate'
  real_T Product1_b;              // '<S76>/Product1'
  real_T Switch_n;                // '<S76>/Switch'
  real_T Product4_h;              // '<S76>/Product4'
  real_T UnaryMinus_d;            // '<S87>/Unary Minus'
  real_T Product1_h;              // '<S74>/Product1'
  real_T Switch_k;                // '<S74>/Switch'
  real_T Product4_p;              // '<S74>/Product4'
  real_T UnaryMinus_e;            // '<S79>/Unary Minus'
  real_T Product1_f;              // '<S75>/Product1'
  real_T Switch_e;                // '<S75>/Switch'
  real_T Product4_j;              // '<S75>/Product4'
  real_T UnaryMinus2_g[2];        // '<S69>/Unary Minus2'
  real_T diffDir_d;               // '<S69>/Switch1'
  real_T Product1_eh[2];          // '<S69>/Product1'
  real_T Gain1_f0[2];             // '<S69>/Gain1'
  real_T omegadot[3];             // '<S69>/Vector Concatenate'
  real_T Gain11;                  // '<S8>/Gain11'
  real_T Divide5;                 // '<S8>/Divide5'
  real_T Subtract;                // '<S79>/Subtract'
  real_T Switch_nm;               // '<S80>/Switch'
  real_T Sum_h;                   // '<S80>/Sum'
  real_T Product_h;               // '<S80>/Product'
  real_T Subtract_m;              // '<S87>/Subtract'
  real_T Switch_h;                // '<S88>/Switch'
  real_T Sum_b;                   // '<S88>/Sum'
  real_T Product_et;              // '<S88>/Product'
  real_T VectorConcatenate_p[4];  // '<S4>/Vector Concatenate'
  real_T Product_p;               // '<S5>/Product'
  real_T Gain_n;                  // '<S5>/Gain'
  real_T fuel_map;                // '<S5>/fuel_map'
  real_T Product2_p;              // '<S5>/Product2'
  real_T Gain2_a;                 // '<S5>/Gain2'
  real_T Saturation_b;            // '<S5>/Saturation'
  real_T EngSpdFdbk_rpm_j;        // '<S1>/Gain1'
  real_T Integrator_od;           // '<S98>/Integrator'
  real_T RPMtodegs;               // '<S98>/RPM to deg//s'
  real_T Subtract_j;              // '<S116>/Subtract'
  real_T Switch_hd;               // '<S117>/Switch'
  real_T Sum_f;                   // '<S117>/Sum'
  real_T Product_f;               // '<S117>/Product'
  real_T UnaryMinus_m;            // '<S66>/Unary Minus'
  real_T TmpSignalConversionAtSFunctionInport1[3];  // '<S62>/Open Differential'
  real_T xdot[2];                                   // '<S62>/Open Differential'
  real_T UnaryMinus_o;                              // '<S69>/Unary Minus'
  real_T Product1_bw;                               // '<S9>/Product1'
  real_T Eta1D;                                     // '<S56>/Eta 1D'
  real_T PumpIntegrator;                            // '<S13>/Pump Integrator'
  real_T Product1_n;                                // '<S51>/Product1'
  real_T Switch_o;                                  // '<S51>/Switch'
  real_T Product4_cv;                               // '<S51>/Product4'
  real_T Subtract_mb;                               // '<S51>/Subtract'
  real_T Product2_o;                                // '<S51>/Product2'
  real_T w_out;                                     // '<S13>/Integrator'
  real_T Product1_ex;                               // '<S52>/Product1'
  real_T Switch_b;                                  // '<S52>/Switch'
  real_T Product4_e;                                // '<S52>/Product4'
  real_T Subtract_g;                                // '<S52>/Subtract'
  real_T Product2_d;                                // '<S52>/Product2'
  real_T PwrEffLoss_f;                              // '<S13>/Add'
  real_T Product4_eu;                               // '<S53>/Product4'
  real_T Add2_o;                                    // '<S53>/Add2'
  real_T Gain_nb;                                   // '<S53>/Gain'
  real_T TrigonometricFunction;    // '<S53>/Trigonometric Function'
  real_T Product2_a;               // '<S53>/Product2'
  real_T Product1_fs;              // '<S53>/Product1'
  real_T Product2_g;               // '<S54>/Product2'
  real_T T_ext;                    // '<S54>/Add2'
  real_T Add1_m;                   // '<S13>/Add1'
  real_T InputClutchDamping_m;     // '<S13>/Input Clutch Damping'
  real_T InputSum;                 // '<S13>/Input Sum'
  real_T Product2_f;               // '<S13>/Product2'
  real_T Product_i;                // '<S13>/Product'
  real_T PwrStoredTrans_b;         // '<S13>/Add2'
  real_T Product10;                // '<S13>/Product10'
  real_T Product_j;                // '<S54>/Product'
  real_T Add3_f;                   // '<S13>/Add3'
  real_T Product3_j;               // '<S53>/Product3'
  real_T UnaryMinus_f;             // '<S53>/Unary Minus'
  real_T InputClutchInertia;       // '<S13>/Input Clutch Inertia'
  real_T Product1_ai;              // '<S13>/Product1'
  real_T Switch_l;                 // '<S55>/Switch'
  real_T Product3_p;               // '<S13>/Product3'
  real_T PwrDampLoss_g;            // '<S13>/Unary Minus'
  real_T Fcn;                      // '<S55>/Fcn'
  real_T Abs_n;                    // '<S55>/Abs'
  real_T Eta1D_b;                  // '<S29>/Eta 1D'
  real_T Abs_k;                    // '<S11>/Abs'
  real_T omega;                    // '<S11>/Locked Shaft Integrator'
  real_T Product1_ei;              // '<S27>/Product1'
  real_T Switch_aq;                // '<S27>/Switch'
  real_T Product4_a;               // '<S27>/Product4'
  real_T Subtract_l;               // '<S27>/Subtract'
  real_T Product2_h;               // '<S27>/Product2'
  real_T Product5;                 // '<S11>/Product5'
  real_T Product1_fr;              // '<S28>/Product1'
  real_T Switch_k4;                // '<S28>/Switch'
  real_T Product4_pm;              // '<S28>/Product4'
  real_T Subtract_c;               // '<S28>/Subtract'
  real_T Product2_e;               // '<S28>/Product2'
  real_T PwrEffLoss_i;             // '<S11>/Add'
  real_T Product1_l;               // '<S11>/Product1'
  real_T Product6;                 // '<S11>/Product6'
  real_T inputclutchDamping;       // '<S11>/input clutch Damping'
  real_T Add1_a;                   // '<S11>/Add1'
  real_T Add2_n;                   // '<S11>/Add2'
  real_T Product3_c;               // '<S11>/Product3'
  real_T Add3_ff;                  // '<S11>/Add3'
  real_T Sum_a;                    // '<S11>/Sum'
  real_T PwrStoredTrans_e;         // '<S11>/Product'
  real_T Product2_fr;              // '<S11>/Product2'
  real_T UnaryMinus_p;             // '<S11>/Unary Minus'
  real_T PwrDampLoss_d;            // '<S11>/Product7'
  real_T Product8;                 // '<S11>/Product8'
  boolean_T UnitDelay2;            // '<S1>/Unit Delay2'
  boolean_T Memory_c;              // '<S46>/Memory'
  boolean_T Compare;               // '<S36>/Compare'
  boolean_T Compare_n;             // '<S40>/Compare'
  boolean_T Memory2_g;             // '<S39>/Memory2'
  boolean_T LogicalOperator3;      // '<S38>/Logical Operator3'
  boolean_T Compare_l;             // '<S41>/Compare'
  boolean_T LogicalOperator2;      // '<S37>/Logical Operator2'
  boolean_T ClutchClosed;          // '<S38>/Logical Operator1'
  boolean_T ClutchClosedandready;  // '<S38>/Logical Operator5'
  boolean_T LogicalOperator7;      // '<S38>/Logical Operator7'
  boolean_T Newgearrequest;        // '<S38>/Relational Operator'
  boolean_T LogicalOperator2_f;    // '<S38>/Logical Operator2'
  boolean_T LogicalOperator3_l;    // '<S37>/Logical Operator3'
  boolean_T Begin;                 // '<S38>/Logical Operator4'
  boolean_T LogicalOperator6;      // '<S38>/Logical Operator6'
  boolean_T Compare_j;             // '<S42>/Compare'
  boolean_T Memory_j;              // '<S43>/Memory'
  boolean_T LogicalOperator;       // '<S43>/Logical Operator'
  boolean_T LogicalOperator2_k;    // '<S43>/Logical Operator2'
  boolean_T LogicalOperator1;      // '<S43>/Logical Operator1'
  boolean_T RelationalOperator;    // '<S44>/Relational Operator'
  boolean_T VelocitiesMatch;       // '<S45>/Velocities Match'
  boolean_T RelationalOperator_p;  // '<S49>/Relational Operator'
  boolean_T Logic;                 // '<S45>/Logic'
  boolean_T CombinatorialLogic;    // '<S46>/Combinatorial  Logic'
  boolean_T Compare_e;             // '<S57>/Compare'
  boolean_T Compare_i;             // '<S58>/Compare'
  boolean_T LogicalOperator_a;     // '<S55>/Logical Operator'
} B_cnhtc_pre_a_vehicle_model_T;
// Block states (default storage) for system '<Root>'
typedef struct {
  real_T UnitDelay1_DSTATE;           // '<S1>/Unit Delay1'
  real_T UnitDelay3_DSTATE;           // '<S1>/Unit Delay3'
  real_T UnitDelay4_DSTATE;           // '<S1>/Unit Delay4'
  real_T UnitDelay1_DSTATE_j;         // '<Root>/Unit Delay1'
  real_T UnitDelay_DSTATE;            // '<Root>/Unit Delay'
  real_T Memory_PreviousInput;        // '<S117>/Memory'
  real_T Memory3_PreviousInput;       // '<S34>/Memory3'
  real_T Memory_PreviousInput_p;      // '<S34>/Memory'
  real_T Memory1_PreviousInput;       // '<S34>/Memory1'
  real_T Memory1_PreviousInput_m;     // '<S37>/Memory1'
  real_T Memory1_PreviousInput_c;     // '<S38>/Memory1'
  real_T Memory2_PreviousInput;       // '<S37>/Memory2'
  real_T Memory_PreviousInput_n;      // '<S88>/Memory'
  real_T Memory_PreviousInput_c;      // '<S80>/Memory'
  int_T Integrator_IWORK;             // '<S117>/Integrator'
  int_T Integrator1_IWORK;            // '<S37>/Integrator1'
  int_T Integrator1_IWORK_l;          // '<S39>/Integrator1'
  int_T Integrator_IWORK_n;           // '<S88>/Integrator'
  int_T Integrator_IWORK_l;           // '<S80>/Integrator'
  int_T Integrator_IWORK_l5;          // '<S62>/Integrator'
  int_T PumpIntegrator_IWORK;         // '<S13>/Pump Integrator'
  int_T Integrator_IWORK_e;           // '<S13>/Integrator'
  int_T LockedShaftIntegrator_IWORK;  // '<S11>/Locked Shaft Integrator'
  int_T VelocitiesMatch_MODE;         // '<S45>/Velocities Match'
  boolean_T UnitDelay2_DSTATE;        // '<S1>/Unit Delay2'
  int8_T If_ActiveSubsystem;          // '<S9>/If'
  boolean_T Memory_PreviousInput_j;   // '<S46>/Memory'
  boolean_T Memory2_PreviousInput_e;  // '<S39>/Memory2'
  boolean_T IC_FirstOutputTime;       // '<S16>/IC'
  boolean_T IC_FirstOutputTime_e;     // '<S17>/IC'
  boolean_T IC_FirstOutputTime_f;     // '<S15>/IC'
  boolean_T IC_FirstOutputTime_fi;    // '<S39>/IC'
  boolean_T Memory_PreviousInput_o;   // '<S43>/Memory'
} DW_cnhtc_pre_a_vehicle_model_T;
// Continuous states (default storage)
typedef struct {
  real_T Integrator1_CSTATE;            // '<S3>/Integrator1'
  real_T Integrator_CSTATE;             // '<S5>/Integrator'
  real_T Integrator_CSTATE_p;           // '<S117>/Integrator'
  real_T Integrator_CSTATE_f;           // '<S116>/Integrator'
  real_T Integrator_CSTATE_g;           // '<S30>/Integrator'
  real_T Integrator1_CSTATE_g;          // '<S37>/Integrator1'
  real_T Integrator1_CSTATE_h;          // '<S39>/Integrator1'
  real_T Integrator_CSTATE_l;           // '<S88>/Integrator'
  real_T Integrator_CSTATE_o;           // '<S87>/Integrator'
  real_T Integrator_CSTATE_c;           // '<S80>/Integrator'
  real_T Integrator_CSTATE_e;           // '<S79>/Integrator'
  real_T Integrator_CSTATE_k;           // '<S4>/Integrator'
  real_T Integrator_CSTATE_ks[2];       // '<S62>/Integrator'
  real_T Integrator_CSTATE_j;           // '<S98>/Integrator'
  real_T PumpIntegrator_CSTATE;         // '<S13>/Pump Integrator'
  real_T Integrator_CSTATE_d;           // '<S13>/Integrator'
  real_T LockedShaftIntegrator_CSTATE;  // '<S11>/Locked Shaft Integrator'
} X_cnhtc_pre_a_vehicle_model_T;
// Periodic continuous state vector (global)
typedef int_T PeriodicIndX_cnhtc_pre_a_vehicle_model_T[1];
typedef real_T PeriodicRngX_cnhtc_pre_a_vehicle_model_T[2];
// State derivatives (default storage)
typedef struct {
  real_T Integrator1_CSTATE;            // '<S3>/Integrator1'
  real_T Integrator_CSTATE;             // '<S5>/Integrator'
  real_T Integrator_CSTATE_p;           // '<S117>/Integrator'
  real_T Integrator_CSTATE_f;           // '<S116>/Integrator'
  real_T Integrator_CSTATE_g;           // '<S30>/Integrator'
  real_T Integrator1_CSTATE_g;          // '<S37>/Integrator1'
  real_T Integrator1_CSTATE_h;          // '<S39>/Integrator1'
  real_T Integrator_CSTATE_l;           // '<S88>/Integrator'
  real_T Integrator_CSTATE_o;           // '<S87>/Integrator'
  real_T Integrator_CSTATE_c;           // '<S80>/Integrator'
  real_T Integrator_CSTATE_e;           // '<S79>/Integrator'
  real_T Integrator_CSTATE_k;           // '<S4>/Integrator'
  real_T Integrator_CSTATE_ks[2];       // '<S62>/Integrator'
  real_T Integrator_CSTATE_j;           // '<S98>/Integrator'
  real_T PumpIntegrator_CSTATE;         // '<S13>/Pump Integrator'
  real_T Integrator_CSTATE_d;           // '<S13>/Integrator'
  real_T LockedShaftIntegrator_CSTATE;  // '<S11>/Locked Shaft Integrator'
} XDot_cnhtc_pre_a_vehicle_model_T;
// State disabled
typedef struct {
  boolean_T Integrator1_CSTATE;            // '<S3>/Integrator1'
  boolean_T Integrator_CSTATE;             // '<S5>/Integrator'
  boolean_T Integrator_CSTATE_p;           // '<S117>/Integrator'
  boolean_T Integrator_CSTATE_f;           // '<S116>/Integrator'
  boolean_T Integrator_CSTATE_g;           // '<S30>/Integrator'
  boolean_T Integrator1_CSTATE_g;          // '<S37>/Integrator1'
  boolean_T Integrator1_CSTATE_h;          // '<S39>/Integrator1'
  boolean_T Integrator_CSTATE_l;           // '<S88>/Integrator'
  boolean_T Integrator_CSTATE_o;           // '<S87>/Integrator'
  boolean_T Integrator_CSTATE_c;           // '<S80>/Integrator'
  boolean_T Integrator_CSTATE_e;           // '<S79>/Integrator'
  boolean_T Integrator_CSTATE_k;           // '<S4>/Integrator'
  boolean_T Integrator_CSTATE_ks[2];       // '<S62>/Integrator'
  boolean_T Integrator_CSTATE_j;           // '<S98>/Integrator'
  boolean_T PumpIntegrator_CSTATE;         // '<S13>/Pump Integrator'
  boolean_T Integrator_CSTATE_d;           // '<S13>/Integrator'
  boolean_T LockedShaftIntegrator_CSTATE;  // '<S11>/Locked Shaft Integrator'
} XDis_cnhtc_pre_a_vehicle_model_T;
// Zero-crossing (trigger) state
typedef struct {
  ZCSigState Integrator_Reset_ZCE;       // '<S117>/Integrator'
  ZCSigState Integrator1_Reset_ZCE;      // '<S39>/Integrator1'
  ZCSigState VelocitiesMatch_Input_ZCE;  // '<S45>/Velocities Match'
  ZCSigState Integrator_Reset_ZCE_a;     // '<S88>/Integrator'
  ZCSigState Integrator_Reset_ZCE_av;    // '<S80>/Integrator'
} PrevZCX_cnhtc_pre_a_vehicle_model_T;
#ifndef ODE3_INTG
#define ODE3_INTG
// ODE3 Integration Data
typedef struct {
  real_T *y;     // output
  real_T *f[3];  // derivatives
} ODE3_IntgData;
#endif
// External inputs (root inport signals with default storage)
typedef struct {
  real_T pedalPos_pct;         // '<Root>/pedalPos_pct'
  real_T XBR1_ExternalAccele;  // '<Root>/XBR1_ExternalAccele'
  real_T XBR1_Ctrl_Mode;       // '<Root>/XBR1_Ctrl_Mode'
  real_T SteerWhAngle_rad;     // '<Root>/SteerWhAngle_rad'
  real_T Vx_kmph;              // '<Root>/Vx_kmph'
  real_T ax_g;                 // '<Root>/ax_g'
  real_T Mass_kg;              // '<Root>/Mass_kg'
} ExtU_cnhtc_pre_a_vehicle_model_T;
// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T GearPos;                     // '<Root>/GearPos'
  boolean_T foundation_brake_in_use;  // '<Root>/foundation_brake_in_use'
  real_T throttle_pct;                // '<Root>/throttle_pct'
  real_T EngTrq_Nm;                   // '<Root>/EngTrq_Nm'
  real_T EngSpd_rpm;                  // '<Root>/EngSpd_rpm'
  real_T engine_torque_loss_percent;  // '<Root>/engine_torque_loss_percent'
  boolean_T shift_in_process;         // '<Root>/shift_in_process'
  real_T engine_torque_percent;       // '<Root>/engine_torque_percent'
  real_T TransTorOut_Nm;              // '<Root>/TransTorOut_Nm'
  real_T bwdWhlPre_Mpa[4];            // '<Root>/bwdWhlPre_Mpa'
  real_T fwdWhlPre_Mpa[2];            // '<Root>/fwdWhlPre_Mpa'
  real_T TrailWhlPre_Mpa[6];          // '<Root>/TrailWhlPre_Mpa'
  real_T SteerWhAngle_DZ_deg;         // '<Root>/SteerWhAngle_DZ_deg'
  real_T fuel_consumption;            // '<Root>/fuel_consumption'
} ExtY_cnhtc_pre_a_vehicle_model_T;
// Parameters (default storage)
struct P_cnhtc_pre_a_vehicle_model_T_ {
  real_T OpenDifferential_Jd;   // Mask Parameter: OpenDifferential_Jd
                                //  Referenced by: '<S62>/Jd'
  real_T OpenDifferential_Jw1;  // Mask Parameter: OpenDifferential_Jw1
                                //  Referenced by: '<S62>/Jw1'
  real_T OpenDifferential_Jw2;  // Mask Parameter: OpenDifferential_Jw2
                                //  Referenced by: '<S62>/Jw3'
  real_T AutomatedManualTransmission_K_c;
  // Mask Parameter: AutomatedManualTransmission_K_c
  //  Referenced by: '<S12>/ClutchGain'
  real_T AutomatedManualTransmission_R;
  // Mask Parameter: AutomatedManualTransmission_R
  //  Referenced by: '<S31>/Torque Conversion'
  real_T PropShaft_b;             // Mask Parameter: PropShaft_b
                                  //  Referenced by: '<S116>/Gain2'
  real_T TorsionalCompliance2_b;  // Mask Parameter: TorsionalCompliance2_b
                                  //  Referenced by: '<S87>/Gain2'
  real_T TorsionalCompliance1_b;  // Mask Parameter: TorsionalCompliance1_b
                                  //  Referenced by: '<S79>/Gain2'
  real_T OpenDifferential_bd;     // Mask Parameter: OpenDifferential_bd
                                  //  Referenced by: '<S62>/bd'
  real_T AutomatedManualTransmission_bin;
  // Mask Parameter: AutomatedManualTransmission_bin
  //  Referenced by:
  //    '<S11>/input clutch Damping'
  //    '<S13>/Input Clutch Damping'
  //    '<S47>/Input Clutch Damping'
  //    '<S48>/Input Damping'
  real_T OpenDifferential_bw1;  // Mask Parameter: OpenDifferential_bw1
                                //  Referenced by: '<S62>/bw1'
  real_T OpenDifferential_bw2;  // Mask Parameter: OpenDifferential_bw2
                                //  Referenced by: '<S62>/bw2'
  real_T PropShaft_domega_o;    // Mask Parameter: PropShaft_domega_o
                                //  Referenced by: '<S116>/domega_o'
  real_T TorsionalCompliance2_domega_o;
  // Mask Parameter: TorsionalCompliance2_domega_o
  //  Referenced by: '<S87>/domega_o'
  real_T TorsionalCompliance1_domega_o;
  // Mask Parameter: TorsionalCompliance1_domega_o
  //  Referenced by: '<S79>/domega_o'
  real_T OpenDifferential_eta;  // Mask Parameter: OpenDifferential_eta
                                //  Referenced by: '<S78>/Constant'
  real_T
      MappedCIEngine_f_tbrake[320];  // Mask Parameter: MappedCIEngine_f_tbrake
                                     //  Referenced by: '<S111>/EngTrq Table'
  real_T MappedCIEngine_f_tbrake_n_bpt[16];
  // Mask Parameter: MappedCIEngine_f_tbrake_n_bpt
  //  Referenced by: '<S111>/EngTrq Table'
  real_T MappedCIEngine_f_tbrake_t_bpt[20];
  // Mask Parameter: MappedCIEngine_f_tbrake_t_bpt
  //  Referenced by: '<S111>/EngTrq Table'
  real_T PropShaft_k;             // Mask Parameter: PropShaft_k
                                  //  Referenced by: '<S116>/Gain1'
  real_T TorsionalCompliance2_k;  // Mask Parameter: TorsionalCompliance2_k
                                  //  Referenced by: '<S87>/Gain1'
  real_T TorsionalCompliance1_k;  // Mask Parameter: TorsionalCompliance1_k
                                  //  Referenced by: '<S79>/Gain1'
  real_T AutomatedManualTransmission_muk;
  // Mask Parameter: AutomatedManualTransmission_muk
  //  Referenced by:
  //    '<S31>/Ratio of static to kinetic'
  //    '<S31>/Torque Conversion'
  real_T AutomatedManualTransmission_mus;
  // Mask Parameter: AutomatedManualTransmission_mus
  //  Referenced by: '<S31>/Ratio of static to kinetic'
  real_T TorsionalCompliance1_omega_c;
  // Mask Parameter: TorsionalCompliance1_omega_c
  //  Referenced by: '<S79>/omega_c'
  real_T TorsionalCompliance2_omega_c;
  // Mask Parameter: TorsionalCompliance2_omega_c
  //  Referenced by: '<S87>/omega_c'
  real_T PropShaft_omega_c;  // Mask Parameter: PropShaft_omega_c
                             //  Referenced by: '<S116>/omega_c'
  real_T AutomatedManualTransmission_omegain_o;
  // Mask Parameter: AutomatedManualTransmission_omegain_o
  //  Referenced by:
  //    '<S15>/Constant'
  //    '<S16>/Constant'
  real_T AutomatedManualTransmission_omegaout_o;
  // Mask Parameter: AutomatedManualTransmission_omegaout_o
  //  Referenced by: '<S17>/Constant'
  real_T
      OpenDifferential_omegaw1o;  // Mask Parameter: OpenDifferential_omegaw1o
                                  //  Referenced by: '<S62>/Constant'
  real_T
      OpenDifferential_omegaw2o;  // Mask Parameter: OpenDifferential_omegaw2o
                                  //  Referenced by: '<S62>/Constant1'
  real_T AutomatedManualTransmission_tauc;
  // Mask Parameter: AutomatedManualTransmission_tauc
  //  Referenced by: '<S12>/Constant1'
  real_T AutomatedManualTransmission_tc;
  // Mask Parameter: AutomatedManualTransmission_tc
  //  Referenced by: '<S37>/Gain1'
  real_T PropShaft_theta_o;  // Mask Parameter: PropShaft_theta_o
                             //  Referenced by: '<S116>/Integrator'
  real_T TorsionalCompliance2_theta_o;
  // Mask Parameter: TorsionalCompliance2_theta_o
  //  Referenced by: '<S87>/Integrator'
  real_T TorsionalCompliance1_theta_o;
  // Mask Parameter: TorsionalCompliance1_theta_o
  //  Referenced by: '<S79>/Integrator'
  real_T div0protectabspoly1_thresh;
  // Mask Parameter: div0protectabspoly1_thresh
  //  Referenced by:
  //    '<S57>/Constant'
  //    '<S58>/Constant'
  real_T AutomatedManualTransmission_ts;
  // Mask Parameter: AutomatedManualTransmission_ts
  //  Referenced by: '<S39>/Gain1'
  real_T ElectronicThrottleActuatorDynamics1_wc;
  // Mask Parameter: ElectronicThrottleActuatorDynamics1_wc
  //  Referenced by: '<S3>/Constant'
  boolean_T AutomatedManualTransmission_SynchLocked;
  // Mask Parameter: AutomatedManualTransmission_SynchLocked
  //  Referenced by: '<S39>/Memory2'
  real_T LockedShaftIntegrator_UpperSat;  // Expression: maxAbsSpd
                                          //  Referenced by: '<S11>/Locked Shaft
                                          //  Integrator'
  real_T LockedShaftIntegrator_LowerSat;  // Expression: -maxAbsSpd
                                          //  Referenced by: '<S11>/Locked Shaft
                                          //  Integrator'
  real_T Constant_Value;                  // Expression: 1
                                          //  Referenced by: '<S27>/Constant'
  real_T Switch_Threshold;                // Expression: 0
                                          //  Referenced by: '<S27>/Switch'
  real_T Constant_Value_b;                // Expression: 1
                                          //  Referenced by: '<S28>/Constant'
  real_T Switch_Threshold_j;              // Expression: 0
                                          //  Referenced by: '<S28>/Switch'
  real_T Constant1_Value;                 // Expression: 0
                                          //  Referenced by: '<S11>/Constant1'
  real_T PumpIntegrator_UpperSat;         // Expression: maxAbsSpd
                                   //  Referenced by: '<S13>/Pump Integrator'
  real_T PumpIntegrator_LowerSat;  // Expression: -maxAbsSpd
                                   //  Referenced by: '<S13>/Pump Integrator'
  real_T Constant_Value_j;         // Expression: 1
                                   //  Referenced by: '<S51>/Constant'
  real_T Switch_Threshold_k;       // Expression: 0
                                   //  Referenced by: '<S51>/Switch'
  real_T Integrator_UpperSat;      // Expression: maxAbsSpd
                                   //  Referenced by: '<S13>/Integrator'
  real_T Integrator_LowerSat;      // Expression: -maxAbsSpd
                                   //  Referenced by: '<S13>/Integrator'
  real_T Constant_Value_a;         // Expression: 1
                                   //  Referenced by: '<S52>/Constant'
  real_T Switch_Threshold_g;       // Expression: 0
                                   //  Referenced by: '<S52>/Switch'
  real_T Gain_Gain;                // Expression: 4
                                   //  Referenced by: '<S53>/Gain'
  real_T OpenDifferential_shaftSwitchMask;  // Expression: shaftSwitchMask
                                            //  Referenced by: '<S62>/Open
                                            //  Differential'
  real_T Constant_Value_n;                  // Expression: 0
                                            //  Referenced by: '<S36>/Constant'
  real_T Constant_Value_m;                  // Expression: 0
                                            //  Referenced by: '<S40>/Constant'
  real_T Constant_Value_d;                  // Expression: 0
                                            //  Referenced by: '<S41>/Constant'
  real_T Constant_Value_h;                  // Expression: 0
                                            //  Referenced by: '<S42>/Constant'
  real_T UnitDelay1_InitialCondition;       // Expression: 0
                                       //  Referenced by: '<S1>/Unit Delay1'
  real_T Gain_Gain_f;                    // Expression: 1
                                         //  Referenced by: '<Root>/Gain'
  real_T Integrator1_IC;                 // Expression: 0
                                         //  Referenced by: '<S3>/Integrator1'
  real_T UnitDelay3_InitialCondition;    // Expression: 0
                                         //  Referenced by: '<S1>/Unit Delay3'
  real_T Saturation_UpperSat;            // Expression: inf
                                         //  Referenced by: '<S1>/Saturation'
  real_T Saturation_LowerSat;            // Expression: 0
                                         //  Referenced by: '<S1>/Saturation'
  real_T UnitDelay4_InitialCondition;    // Expression: 0
                                         //  Referenced by: '<S1>/Unit Delay4'
  real_T Constant1_Value_d;              // Expression: eps
                                         //  Referenced by: '<S1>/Constant1'
  real_T UnitDelay1_InitialCondition_a;  // Expression: 0
                                         //  Referenced by: '<Root>/Unit Delay1'
  real_T Integrator_IC;                  // Expression: 0
                                         //  Referenced by: '<S5>/Integrator'
  real_T Memory_InitialCondition;        // Expression: 0
                                         //  Referenced by: '<S117>/Memory'
  real_T Integrator_IC_h;                // Expression: 0
                                         //  Referenced by: '<S30>/Integrator'
  real_T Saturation_UpperSat_a;          // Expression: inf
                                         //  Referenced by: '<S31>/Saturation'
  real_T Saturation_LowerSat_f;          // Expression: eps
                                         //  Referenced by: '<S31>/Saturation'
  real_T UnitDelay_InitialCondition;     // Expression: 0
                                         //  Referenced by: '<Root>/Unit Delay'
  real_T Constant_Value_hd;              // Expression: ClutchLocked
                                         //  Referenced by: '<S37>/Constant'
  real_T Integrator1_UpperSat;           // Expression: 1
                                         //  Referenced by: '<S37>/Integrator1'
  real_T Integrator1_LowerSat;           // Expression: 0
                                         //  Referenced by: '<S37>/Integrator1'
  real_T Gear2inertias_tableData[13];    // Expression: Jout
                                       //  Referenced by: '<S14>/Gear2inertias'
  real_T Constant1_Value_f;       // Expression: 1
                                  //  Referenced by: '<S16>/Constant1'
  real_T IC_Value;                // Expression: 0
                                  //  Referenced by: '<S16>/IC'
  real_T Switch_Threshold_n;      // Expression: 0
                                  //  Referenced by: '<S16>/Switch'
  real_T Constant1_Value_c;       // Expression: 1
                                  //  Referenced by: '<S17>/Constant1'
  real_T IC_Value_c;              // Expression: 0
                                  //  Referenced by: '<S17>/IC'
  real_T Switch_Threshold_e;      // Expression: 0
                                  //  Referenced by: '<S17>/Switch'
  real_T Constant1_Value_o;       // Expression: 1
                                  //  Referenced by: '<S15>/Constant1'
  real_T IC_Value_o;              // Expression: 0
                                  //  Referenced by: '<S15>/IC'
  real_T Switch_Threshold_l;      // Expression: 0
                                  //  Referenced by: '<S15>/Switch'
  real_T Merge4_1_InitialOutput;  // Computed Parameter: Merge4_1_InitialOutput
                                  //  Referenced by: '<S9>/Merge4'
  real_T Merge4_2_InitialOutput;  // Computed Parameter: Merge4_2_InitialOutput
                                  //  Referenced by: '<S9>/Merge4'
  real_T Merge4_3_InitialOutput;  // Computed Parameter: Merge4_3_InitialOutput
                                  //  Referenced by: '<S9>/Merge4'
  real_T Merge4_4_InitialOutput;  // Computed Parameter: Merge4_4_InitialOutput
                                  //  Referenced by: '<S9>/Merge4'
  real_T upi_Gain;                // Expression: 2*pi
                                  //  Referenced by: '<S12>/2*pi'
  real_T Constant_Value_c;        // Expression: 0
                                  //  Referenced by: '<S12>/Constant'
  real_T Memory1_InitialCondition;    // Expression: 1
                                      //  Referenced by: '<S37>/Memory1'
  real_T Memory1_InitialCondition_k;  // Expression: 0
                                      //  Referenced by: '<S38>/Memory1'
  real_T Memory2_InitialCondition;    // Expression: -1
                                      //  Referenced by: '<S37>/Memory2'
  real_T Constant1_Value_i;           // Expression: 0
                                      //  Referenced by: '<S39>/Constant1'
  real_T IC_Value_m;                  // Expression: SynchLocked
                                      //  Referenced by: '<S39>/IC'
  real_T Integrator1_UpperSat_j;      // Expression: 1
                                      //  Referenced by: '<S39>/Integrator1'
  real_T Integrator1_LowerSat_a;      // Expression: -eps
                                      //  Referenced by: '<S39>/Integrator1'
  real_T VelocitiesMatch_Offset;      // Expression: 0
                                  //  Referenced by: '<S45>/Velocities Match'
  real_T Constant_Value_dt;          // Expression: 0
                                     //  Referenced by: '<S1>/Constant'
  real_T Memory_InitialCondition_g;  // Expression: 0
                                     //  Referenced by: '<S88>/Memory'
  real_T Memory_InitialCondition_p;  // Expression: 0
                                     //  Referenced by: '<S80>/Memory'
  real_T Constant_Value_e;           // Expression: 18000
                                     //  Referenced by: '<S4>/Constant'
  real_T Integrator_IC_g;            // Expression: 0
                                     //  Referenced by: '<S4>/Integrator'
  real_T Constant1_Value_p;          // Expression: 1
                                     //  Referenced by: '<S66>/Constant1'
  real_T Constant_Value_nr;          // Expression: shaftSwitchMask
                                     //  Referenced by: '<S66>/Constant'
  real_T Switch_Threshold_p;         // Expression: 1
                                     //  Referenced by: '<S66>/Switch'
  real_T Integrator_UpperSat_h;      // Expression: maxAbsSpd
                                     //  Referenced by: '<S62>/Integrator'
  real_T Integrator_LowerSat_l;      // Expression: -maxAbsSpd
                                     //  Referenced by: '<S62>/Integrator'
  real_T Gain1_Gain;                 // Expression: 1/2
                                     //  Referenced by: '<S66>/Gain1'
  real_T Constant_Value_g;           // Expression: 1
                                     //  Referenced by: '<S76>/Constant'
  real_T Switch_Threshold_g3;        // Expression: 0
                                     //  Referenced by: '<S76>/Switch'
  real_T Constant_Value_gj;          // Expression: 1
                                     //  Referenced by: '<S74>/Constant'
  real_T Switch_Threshold_o;         // Expression: 0
                                     //  Referenced by: '<S74>/Switch'
  real_T Constant_Value_k;           // Expression: 1
                                     //  Referenced by: '<S75>/Constant'
  real_T Switch_Threshold_ob;        // Expression: 0
                                     //  Referenced by: '<S75>/Switch'
  real_T Constant_Value_np;          // Expression: shaftSwitchMask
                                     //  Referenced by: '<S69>/Constant'
  real_T Constant6_Value;            // Expression: 1
                                     //  Referenced by: '<S69>/Constant6'
  real_T Switch1_Threshold;          // Expression: 1
                                     //  Referenced by: '<S69>/Switch1'
  real_T Gain11_Gain;                // Expression: 1/3.6
                                     //  Referenced by: '<S8>/Gain11'
  real_T Reset_Value;                // Expression: 1
                                     //  Referenced by: '<S80>/Reset'
  real_T Reset_Value_g;              // Expression: 1
                                     //  Referenced by: '<S88>/Reset'
  real_T Gain_Gain_j;                // Expression: 1/9550
                                     //  Referenced by: '<S5>/Gain'
  real_T Gain2_Gain;                 // Expression: 1/3600
                                     //  Referenced by: '<S5>/Gain2'
  real_T Saturation_UpperSat_i;      // Expression: inf
                                     //  Referenced by: '<S5>/Saturation'
  real_T Saturation_LowerSat_p;      // Expression: 0
                                     //  Referenced by: '<S5>/Saturation'
  real_T Gain1_Gain_k;               // Expression: 60/2/pi
                                     //  Referenced by: '<S1>/Gain1'
  real_T Integrator_IC_i;            // Expression: 0
                                     //  Referenced by: '<S98>/Integrator'
  real_T
      Integrator_WrappedStateUpperValue;  // Expression: 360*Cps
                                          //  Referenced by: '<S98>/Integrator'
  real_T
      Integrator_WrappedStateLowerValue;  // Expression: 0
                                          //  Referenced by: '<S98>/Integrator'
  real_T RPMtodegs_Gain;                  // Expression: 180/30
                          //  Referenced by: '<S98>/RPM to deg//s'
  real_T Reset_Value_j;              // Expression: 1
                                     //  Referenced by: '<S117>/Reset'
  uint32_T EngTrqTable_maxIndex[2];  // Computed Parameter: EngTrqTable_maxIndex
                                     //  Referenced by: '<S111>/EngTrq Table'
  uint32_T fuel_map_maxIndex[2];     // Computed Parameter: fuel_map_maxIndex
                                     //  Referenced by: '<S5>/fuel_map'
  boolean_T UnitDelay2_InitialCondition;
  // Computed Parameter: UnitDelay2_InitialCondition
  //  Referenced by: '<S1>/Unit Delay2'
  boolean_T Memory_InitialCondition_pv;  // Expression: ClutchLocked
                                         //  Referenced by: '<S46>/Memory'
  boolean_T Memory_InitialCondition_b;
  // Computed Parameter: Memory_InitialCondition_b
  //  Referenced by: '<S43>/Memory'
  boolean_T CombinatorialLogic_table[8];
  // Computed Parameter: CombinatorialLogic_table
  //  Referenced by: '<S46>/Combinatorial  Logic'
};
// Real-time Model Data Structure
struct tag_RTM_cnhtc_pre_a_vehicle_model_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_cnhtc_pre_a_vehicle_model_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[18];
  real_T odeF[3][18];
  ODE3_IntgData intgData;
  //
  //  Sizes:
  //  The following substructure contains sizes information
  //  for many of the model attributes such as inputs, outputs,
  //  dwork, sample times, etc.
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;
  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    boolean_T firstInitCondFlag;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};
// Model block global parameters (default storage)
extern struct_1Bydkh1pAHvKL6MKYnygkF
    rtP_Chas;  // Variable: Chas
               //  Referenced by:
               //    '<S1>/Constant2'
               //    '<S1>/1-D Lookup Table'
               //    '<S4>/Gain'
               //    '<S8>/Constant12'
               //    '<S11>/Constant'
               //    '<S13>/Input Clutch Inertia'
               //    '<S14>/Gear2Ratios'
               //    '<S14>/Gear2damping'
               //    '<S14>/Gear2inertias'
               //    '<S62>/Ndiff2'
               //    '<S66>/Gain'
               //    '<S29>/Eta 1D'
               //    '<S47>/Constant'
               //    '<S56>/Eta 1D'
               //    '<S48>/Constant'
               //    '<S69>/Gain1'
extern struct_xuvldbp4qY393voN3kPmeB
    rtP_EBC;  // Variable: EBC
              //  Referenced by: '<Root>/Brake_System'
extern struct_o4hYTbLTHRHZgQXM4jB8FD rtP_VEH;  // Variable: VEH
                                               //  Referenced by:
                                               //    '<Root>/Brake_System'
                                               //    '<S34>/Memory'
                                               //    '<S34>/Memory1'
                                               //    '<S34>/Memory3'
extern real_T rtP_DnShiftSpdTa[99];            // Variable: DnShiftSpdTa
                                               //  Referenced by: '<S1>/TCU'
extern real_T rtP_EngTorBp_ne[15];             // Variable: EngTorBp_ne
                                    //  Referenced by: '<S1>/Engine_ECU'
extern real_T rtP_EngTorBp_ped[16];  // Variable: EngTorBp_ped
                                     //  Referenced by: '<S1>/Engine_ECU'
extern real_T rtP_EngTorTable[240];  // Variable: EngTorTable
                                     //  Referenced by: '<S1>/Engine_ECU'
extern real_T rtP_ShiftDnTa_Bp_GearPos[11];  // Variable: ShiftDnTa_Bp_GearPos
                                             //  Referenced by: '<S1>/TCU'
extern real_T rtP_ShiftDnTa_Bp_PedPos[9];    // Variable: ShiftDnTa_Bp_PedPos
                                             //  Referenced by: '<S1>/TCU'
extern real_T rtP_ShiftUpTa_Bp_GearPos[11];  // Variable: ShiftUpTa_Bp_GearPos
                                             //  Referenced by: '<S1>/TCU'
extern real_T rtP_ShiftUpTa_Bp_PedPos[10];   // Variable: ShiftUpTa_Bp_PedPos
                                             //  Referenced by: '<S1>/TCU'
extern real_T rtP_UpshiftSpdTa[110];         // Variable: UpshiftSpdTa
                                             //  Referenced by: '<S1>/TCU'
extern real_T rtP_dt_ECU;                    // Variable: dt_ECU
                           //  Referenced by: '<S1>/Engine_ECU'
extern real_T rtP_dt_bra;             // Variable: dt_bra
                                      //  Referenced by: '<Root>/Brake_System'
extern real_T rtP_fuel_bsfc[132];     // Variable: fuel_bsfc
                                      //  Referenced by: '<S5>/fuel_map'
extern real_T rtP_fuel_engspeed[12];  // Variable: fuel_engspeed
                                      //  Referenced by: '<S5>/fuel_map'
extern real_T rtP_fuel_engtor[11];    // Variable: fuel_engtor
                                      //  Referenced by: '<S5>/fuel_map'
extern real_T rtP_steer_input[7];     // Variable: steer_input
                                      //  Referenced by: '<Root>/SteerWhlMdl'
extern real_T rtP_steer_output[7];    // Variable: steer_output
                                      //  Referenced by: '<Root>/SteerWhlMdl'
// Class declaration for model cnhtc_pre_a_vehicle_model
class CNHTC_VEHICLE_MODEL_codeModelClass {
  // public data and function members
 public:
  // Tunable parameters
  static P_cnhtc_pre_a_vehicle_model_T cnhtc_pre_a_vehicle_model_P;
  // External inputs
  ExtU_cnhtc_pre_a_vehicle_model_T cnhtc_pre_a_vehicle_model_U;
  // External outputs
  ExtY_cnhtc_pre_a_vehicle_model_T cnhtc_pre_a_vehicle_model_Y;
  // model initialize function
  void initialize();
  // model step function
  void step();
  // model terminate function
  void terminate();
  // Constructor
  CNHTC_VEHICLE_MODEL_codeModelClass();
  // Destructor
  ~CNHTC_VEHICLE_MODEL_codeModelClass();
  // Real-Time Model get method
  RT_MODEL_cnhtc_pre_a_vehicle_model_T *getRTM();
  // private data and function members
 private:
  // Block signals
  B_cnhtc_pre_a_vehicle_model_T cnhtc_pre_a_vehicle_model_B;
  // Block states
  DW_cnhtc_pre_a_vehicle_model_T cnhtc_pre_a_vehicle_model_DW;
  X_cnhtc_pre_a_vehicle_model_T
      cnhtc_pre_a_vehicle_model_X;  // Block continuous states
  PeriodicIndX_cnhtc_pre_a_vehicle_model_T
      cnhtc_pre_a_vehicle_model_PeriodicIndX;  // Block periodic continuous
                                               // states
  PeriodicRngX_cnhtc_pre_a_vehicle_model_T
      cnhtc_pre_a_vehicle_model_PeriodicRngX;
  PrevZCX_cnhtc_pre_a_vehicle_model_T
      cnhtc_pre_a_vehicle_model_PrevZCX;  // Triggered events
  // Real-Time Model
  RT_MODEL_cnhtc_pre_a_vehicle_model_T cnhtc_pre_a_vehicle_model_M;
  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si);
  // Derivatives member function
  void cnhtc_pre_a_vehicle_model_derivatives();
  // model instance variable for '<Root>/Brake_System'
  BrakingModelClass Brake_SystemMDLOBJ1;
  // model instance variable for '<S1>/Engine_ECU'
  Engine_ECUModelClass Engine_ECUMDLOBJ2;
  // model instance variable for '<S1>/TCU'
  TCUModelClass TCUMDLOBJ3;
  // model instance variable for '<Root>/SteerWhlMdl'
  SteerWhlMdlModelClass SteerWhlMdlMDLOBJ4;
};
//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S18>/Abs1' : Unused code path elimination
//  Block '<S18>/Gain' : Unused code path elimination
//  Block '<S18>/Product' : Unused code path elimination
//  Block '<S18>/Product1' : Unused code path elimination
//  Block '<S18>/Product2' : Unused code path elimination
//  Block '<S18>/Saturation' : Unused code path elimination
//  Block '<S18>/Saturation1' : Unused code path elimination
//  Block '<S18>/Saturation2' : Unused code path elimination
//  Block '<S18>/Sum of Elements' : Unused code path elimination
//  Block '<S18>/Sum of Elements1' : Unused code path elimination
//  Block '<S20>/Abs' : Unused code path elimination
//  Block '<S21>/Compare' : Unused code path elimination
//  Block '<S21>/Constant' : Unused code path elimination
//  Block '<S22>/Compare' : Unused code path elimination
//  Block '<S22>/Constant' : Unused code path elimination
//  Block '<S20>/Fcn' : Unused code path elimination
//  Block '<S20>/Logical Operator' : Unused code path elimination
//  Block '<S20>/Switch' : Unused code path elimination
//  Block '<S10>/Product' : Unused code path elimination
//  Block '<S10>/Product1' : Unused code path elimination
//  Block '<S3>/FixPt Data Type Duplicate1' : Unused code path elimination
//  Block '<S68>/Abs' : Unused code path elimination
//  Block '<S68>/Constant6' : Unused code path elimination
//  Block '<S68>/Constant7' : Unused code path elimination
//  Block '<S68>/Constant8' : Unused code path elimination
//  Block '<S68>/Product1' : Unused code path elimination
//  Block '<S68>/Product4' : Unused code path elimination
//  Block '<S68>/Sum of Elements2' : Unused code path elimination
//  Block '<S68>/Unary Minus' : Unused code path elimination
//  Block '<S69>/Constant1' : Unused code path elimination
//  Block '<S69>/Constant4' : Unused code path elimination
//  Block '<S69>/Constant5' : Unused code path elimination
//  Block '<S69>/Product5' : Unused code path elimination
//  Block '<S69>/Sum of Elements1' : Unused code path elimination
//  Block '<S67>/Sum of Elements3' : Unused code path elimination
//  Block '<S67>/Transferred Power' : Unused code path elimination
//  Block '<S67>/Unary Minus' : Unused code path elimination
//  Block '<S74>/Product2' : Unused code path elimination
//  Block '<S74>/Subtract' : Unused code path elimination
//  Block '<S75>/Product2' : Unused code path elimination
//  Block '<S75>/Subtract' : Unused code path elimination
//  Block '<S76>/Product2' : Unused code path elimination
//  Block '<S76>/Subtract' : Unused code path elimination
//  Block '<S4>/Scope' : Unused code path elimination
//  Block '<S82>/Constant8' : Unused code path elimination
//  Block '<S82>/Product1' : Unused code path elimination
//  Block '<S82>/Product4' : Unused code path elimination
//  Block '<S82>/Unary Minus' : Unused code path elimination
//  Block '<S81>/Product' : Unused code path elimination
//  Block '<S81>/Transferred Power' : Unused code path elimination
//  Block '<S81>/Unary Minus1' : Unused code path elimination
//  Block '<S79>/Signal Copy' : Unused code path elimination
//  Block '<S79>/Signal Copy1' : Unused code path elimination
//  Block '<S79>/Unary Minus1' : Unused code path elimination
//  Block '<S90>/Constant8' : Unused code path elimination
//  Block '<S90>/Product1' : Unused code path elimination
//  Block '<S90>/Product4' : Unused code path elimination
//  Block '<S90>/Unary Minus' : Unused code path elimination
//  Block '<S89>/Product' : Unused code path elimination
//  Block '<S89>/Transferred Power' : Unused code path elimination
//  Block '<S89>/Unary Minus1' : Unused code path elimination
//  Block '<S87>/Signal Copy' : Unused code path elimination
//  Block '<S87>/Signal Copy1' : Unused code path elimination
//  Block '<S87>/Unary Minus1' : Unused code path elimination
//  Block '<S95>/Constant' : Unused code path elimination
//  Block '<S95>/Divide' : Unused code path elimination
//  Block '<S95>/MinMax' : Unused code path elimination
//  Block '<S106>/Compare' : Unused code path elimination
//  Block '<S106>/Constant' : Unused code path elimination
//  Block '<S107>/Compare' : Unused code path elimination
//  Block '<S107>/Constant' : Unused code path elimination
//  Block '<S104>/Constant' : Unused code path elimination
//  Block '<S104>/Fcn' : Unused code path elimination
//  Block '<S104>/Logical Operator' : Unused code path elimination
//  Block '<S104>/Product' : Unused code path elimination
//  Block '<S104>/Switch' : Unused code path elimination
//  Block '<S104>/Switch1' : Unused code path elimination
//  Block '<S104>/Unary Minus' : Unused code path elimination
//  Block '<S108>/Compare' : Unused code path elimination
//  Block '<S108>/Constant' : Unused code path elimination
//  Block '<S109>/Compare' : Unused code path elimination
//  Block '<S109>/Constant' : Unused code path elimination
//  Block '<S105>/Constant' : Unused code path elimination
//  Block '<S105>/Fcn' : Unused code path elimination
//  Block '<S105>/Logical Operator' : Unused code path elimination
//  Block '<S105>/Product' : Unused code path elimination
//  Block '<S105>/Switch' : Unused code path elimination
//  Block '<S105>/Switch1' : Unused code path elimination
//  Block '<S105>/Unary Minus' : Unused code path elimination
//  Block '<S96>/Air Flow Table' : Unused code path elimination
//  Block '<S99>/AFR calc1' : Unused code path elimination
//  Block '<S99>/Constant' : Unused code path elimination
//  Block '<S99>/Gain' : Unused code path elimination
//  Block '<S100>/Calc Load' : Unused code path elimination
//  Block '<S100>/Cylinders per sec' : Unused code path elimination
//  Block '<S100>/Engine Displacement' : Unused code path elimination
//  Block '<S100>/Ideal Gas Constant' : Unused code path elimination
//  Block '<S100>/Nominal Airflow At Current Speed and STP' : Unused code path
//  elimination Block '<S100>/Nominal Cylinder Air Mass g//cyl' : Unused code
//  path elimination Block '<S100>/Saturation3' : Unused code path elimination
//  Block '<S100>/Standard Air Temperature' : Unused code path elimination
//  Block '<S100>/Standard Pressure Sea Level' : Unused code path elimination
//  Block '<S100>/cyls per cycle' : Unused code path elimination
//  Block '<S100>/cyls per cycle ' : Unused code path elimination
//  Block '<S100>/rev per cycle' : Unused code path elimination
//  Block '<S100>/sec per min' : Unused code path elimination
//  Block '<S111>/Bsfc Table' : Unused code path elimination
//  Block '<S111>/EoCO2 Table' : Unused code path elimination
//  Block '<S111>/EoCo Table' : Unused code path elimination
//  Block '<S111>/EoHc Table' : Unused code path elimination
//  Block '<S111>/EoNOx Table' : Unused code path elimination
//  Block '<S111>/EoPm Table' : Unused code path elimination
//  Block '<S111>/ExhManGasTemp Table' : Unused code path elimination
//  Block '<S111>/FuelMassFlw Table' : Unused code path elimination
//  Block '<S102>/LHV' : Unused code path elimination
//  Block '<S113>/Constant' : Unused code path elimination
//  Block '<S102>/Product' : Unused code path elimination
//  Block '<S102>/Subtract' : Unused code path elimination
//  Block '<S102>/rpm to rad//s' : Unused code path elimination
//  Block '<S103>/Constant' : Unused code path elimination
//  Block '<S103>/Max' : Unused code path elimination
//  Block '<S119>/Constant8' : Unused code path elimination
//  Block '<S119>/Product1' : Unused code path elimination
//  Block '<S119>/Product4' : Unused code path elimination
//  Block '<S119>/Unary Minus' : Unused code path elimination
//  Block '<S118>/Product' : Unused code path elimination
//  Block '<S118>/Transferred Power' : Unused code path elimination
//  Block '<S118>/Unary Minus1' : Unused code path elimination
//  Block '<S116>/Signal Copy' : Unused code path elimination
//  Block '<S116>/Signal Copy1' : Unused code path elimination
//  Block '<S116>/Unary Minus1' : Unused code path elimination
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
//  '<Root>' : 'cnhtc_pre_a_vehicle_model'
//  '<S1>'   : 'cnhtc_pre_a_vehicle_model/DriveLine'
//  '<S2>'   : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission'
//  '<S3>'   : 'cnhtc_pre_a_vehicle_model/DriveLine/Electronic Throttle Actuator
//  Dynamics1'
//  '<S4>'   : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive'
//  '<S5>'   : 'cnhtc_pre_a_vehicle_model/DriveLine/Fuel Consumption1'
//  '<S6>'   : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine'
//  '<S7>'   : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft'
//  '<S8>'   : 'cnhtc_pre_a_vehicle_model/DriveLine/Subsystem1'
//  '<S9>'   : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission'
//  '<S10>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation'
//  '<S11>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Locked'
//  '<S12>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response'
//  '<S13>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked'
//  '<S14>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/gear2props'
//  '<S15>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/omegain_o'
//  '<S16>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/omegain_o1'
//  '<S17>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/omegaout_o'
//  '<S18>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation/Mechanical
//  Efficiency'
//  '<S19>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation/Power Accounting Bus
//  Creator'
//  '<S20>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation/Mechanical
//  Efficiency/div0protect - abs poly'
//  '<S21>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation/Mechanical
//  Efficiency/div0protect - abs poly/Compare To Constant'
//  '<S22>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation/Mechanical
//  Efficiency/div0protect - abs poly/Compare To Constant1'
//  '<S23>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation/Power Accounting Bus
//  Creator/PwrNotTrnsfrd Input'
//  '<S24>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation/Power Accounting Bus
//  Creator/PwrStored Input'
//  '<S25>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Bus Creation/Power Accounting Bus
//  Creator/PwrTrnsfrd Input'
//  '<S26>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Locked/AMT Eta'
//  '<S27>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Locked/Apply Efficiency'
//  '<S28>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Locked/Apply Efficiency1'
//  '<S29>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Locked/AMT Eta/Eta 1D'
//  '<S30>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Cont LPF
//  Dyn'
//  '<S31>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Friction
//  Model'
//  '<S32>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing'
//  '<S33>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up
//  Friction Mode Logic'
//  '<S34>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Gear Selection'
//  '<S35>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Syncronizer Timing'
//  '<S36>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Gear Selection/Compare To Zero3'
//  '<S37>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Syncronizer Timing/Internal Control Clutch
//  Engagement'
//  '<S38>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Syncronizer Timing/Shift Interlock'
//  '<S39>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Syncronizer Timing/Synch Timing'
//  '<S40>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Syncronizer Timing/Internal Control Clutch
//  Engagement/Compare To Zero1'
//  '<S41>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Syncronizer Timing/Internal Control Clutch
//  Engagement/Compare To Zero2'
//  '<S42>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Syncronizer Timing/Synch Timing/Compare To Zero1'
//  '<S43>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Gear,
//  Clutch and Syncro Timing/Syncronizer Timing/Synch Timing/LatchSwitchCont'
//  '<S44>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up
//  Friction Mode Logic/Break Apart Detection'
//  '<S45>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up
//  Friction Mode Logic/Lockup Detection'
//  '<S46>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up
//  Friction Mode Logic/Lockup FSM'
//  '<S47>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up
//  Friction Mode Logic/Requisite Friction'
//  '<S48>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up
//  Friction Mode Logic/Lockup Detection/Friction Calc'
//  '<S49>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up
//  Friction Mode Logic/Lockup Detection/Required Friction for Lockup'
//  '<S50>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/AMT Eta'
//  '<S51>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/Apply Efficiency'
//  '<S52>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/Apply Efficiency1'
//  '<S53>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/Clutch Torque'
//  '<S54>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/Losses'
//  '<S55>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/div0protect - abs poly1'
//  '<S56>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/AMT Eta/Eta 1D'
//  '<S57>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/div0protect - abs
//  poly1/Compare To Constant'
//  '<S58>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Automated Manual
//  Transmission/Automated Manual Transmission/Unlocked/div0protect - abs
//  poly1/Compare To Constant1'
//  '<S59>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential'
//  '<S60>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1'
//  '<S61>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2'
//  '<S62>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential'
//  '<S63>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Bus Creation'
//  '<S64>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Efficiency'
//  '<S65>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Open Differential'
//  '<S66>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/y'
//  '<S67>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Bus Creation/Power'
//  '<S68>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Bus Creation/Power/Damping Power'
//  '<S69>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Bus Creation/Power/Kinetic Power'
//  '<S70>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Bus Creation/Power/Power Accounting Bus
//  Creator'
//  '<S71>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Bus Creation/Power/Power Accounting Bus
//  Creator/PwrNotTrnsfrd Input'
//  '<S72>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Bus Creation/Power/Power Accounting Bus
//  Creator/PwrStored Input'
//  '<S73>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Bus Creation/Power/Power Accounting Bus
//  Creator/PwrTrnsfrd Input'
//  '<S74>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Efficiency/Axle 1 Efficiency'
//  '<S75>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Efficiency/Axle 2 Efficiency'
//  '<S76>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Efficiency/Drive Efficiency'
//  '<S77>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Efficiency/Eta'
//  '<S78>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Open
//  Differential/Open Differential/Efficiency/Eta/Constant Eta'
//  '<S79>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1/Torsional Compliance Linear'
//  '<S80>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1/Torsional Compliance Linear/Cont LPF IC Dyn'
//  '<S81>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1/Torsional Compliance Linear/Power'
//  '<S82>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1/Torsional Compliance Linear/Power/Damping Power'
//  '<S83>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1/Torsional Compliance Linear/Power/Power Accounting Bus Creator'
//  '<S84>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1/Torsional Compliance Linear/Power/Power Accounting Bus
//  Creator/PwrNotTrnsfrd Input'
//  '<S85>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1/Torsional Compliance Linear/Power/Power Accounting Bus
//  Creator/PwrStored Input'
//  '<S86>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance1/Torsional Compliance Linear/Power/Power Accounting Bus
//  Creator/PwrTrnsfrd Input'
//  '<S87>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2/Torsional Compliance Linear'
//  '<S88>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2/Torsional Compliance Linear/Cont LPF IC Dyn'
//  '<S89>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2/Torsional Compliance Linear/Power'
//  '<S90>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2/Torsional Compliance Linear/Power/Damping Power'
//  '<S91>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2/Torsional Compliance Linear/Power/Power Accounting Bus Creator'
//  '<S92>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2/Torsional Compliance Linear/Power/Power Accounting Bus
//  Creator/PwrNotTrnsfrd Input'
//  '<S93>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2/Torsional Compliance Linear/Power/Power Accounting Bus
//  Creator/PwrStored Input'
//  '<S94>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Front Wheel Drive/Torsional
//  Compliance2/Torsional Compliance Linear/Power/Power Accounting Bus
//  Creator/PwrTrnsfrd Input'
//  '<S95>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Afr
//  Calculation'
//  '<S96>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Air Flow'
//  '<S97>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/CI Engine
//  Fuel Mass without Boost Lag'
//  '<S98>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Engine
//  Crank Angle Calculation'
//  '<S99>'  : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Fuel Volume
//  Flow'
//  '<S100>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Load
//  Calculation'
//  '<S101>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Mapped Core
//  Engine'
//  '<S102>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Mapped
//  Engine Power Info'
//  '<S103>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Max
//  Commanded Fuel-Torque'
//  '<S104>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Afr
//  Calculation/div0protect - poly1'
//  '<S105>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Afr
//  Calculation/div0protect - poly2'
//  '<S106>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Afr
//  Calculation/div0protect - poly1/Compare To Constant'
//  '<S107>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Afr
//  Calculation/div0protect - poly1/Compare To Constant1'
//  '<S108>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Afr
//  Calculation/div0protect - poly2/Compare To Constant'
//  '<S109>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Afr
//  Calculation/div0protect - poly2/Compare To Constant1'
//  '<S110>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Mapped Core
//  Engine/Without Temperature Input and with Trq'
//  '<S111>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Mapped Core
//  Engine/Without Temperature Input and with Trq/Mapped Core Engine'
//  '<S112>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Mapped
//  Engine Power Info/Power Accounting Bus Creator'
//  '<S113>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Mapped
//  Engine Power Info/Power Accounting Bus Creator/No PwrStored Input'
//  '<S114>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Mapped
//  Engine Power Info/Power Accounting Bus Creator/PwrNotTrnsfrd Input'
//  '<S115>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Mapped CI Engine/Mapped
//  Engine Power Info/Power Accounting Bus Creator/PwrTrnsfrd Input'
//  '<S116>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft/Torsional
//  Compliance Linear'
//  '<S117>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft/Torsional
//  Compliance Linear/Cont LPF IC Dyn'
//  '<S118>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft/Torsional
//  Compliance Linear/Power'
//  '<S119>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft/Torsional
//  Compliance Linear/Power/Damping Power'
//  '<S120>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft/Torsional
//  Compliance Linear/Power/Power Accounting Bus Creator'
//  '<S121>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft/Torsional
//  Compliance Linear/Power/Power Accounting Bus Creator/PwrNotTrnsfrd Input'
//  '<S122>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft/Torsional
//  Compliance Linear/Power/Power Accounting Bus Creator/PwrStored Input'
//  '<S123>' : 'cnhtc_pre_a_vehicle_model/DriveLine/Prop Shaft/Torsional
//  Compliance Linear/Power/Power Accounting Bus Creator/PwrTrnsfrd Input'
//

#endif  // SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_CNHTC_PRE_A_VEHICLE_MODEL_H_
// File trailer for generated code.
//
// [EOF]
//
