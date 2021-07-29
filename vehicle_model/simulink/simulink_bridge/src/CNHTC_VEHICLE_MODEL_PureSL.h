//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: CNHTC_VEHICLE_MODEL_PureSL.h
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
#ifndef RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_h_
#define RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_h_
#include <cstring>
#include <cmath>
#ifndef CNHTC_VEHICLE_MODEL_PureSL_COMMON_INCLUDES_
# define CNHTC_VEHICLE_MODEL_PureSL_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                           // CNHTC_VEHICLE_MODEL_PureSL_COMMON_INCLUDES_

#include "CNHTC_VEHICLE_MODEL_PureSL_types.h"

// Child system includes
#include "CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic.h"
#include "SteerWhlMdl.h"
#include "Braking.h"
#include "TCU.h"
#include "Engine_ECU.h"
#include "rt_zcfcn.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetErrorStatusPointer
# define rtmGetErrorStatusPointer(rtm) ((const char_T **)(&((rtm)->errorStatus)))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

// Block signals (default storage)
typedef struct {
  real_T Integrator1;                  // '<S5>/Integrator1'
  real_T EngSpdFdbk_rpm;               // '<S3>/Unit Delay3'
  real_T EngTrq;                       // '<S112>/EngTrq Table'
  real_T Saturation;                   // '<S3>/Saturation'
  real_T Add;                          // '<S3>/Add'
  real_T Abs;                          // '<S3>/Abs'
  real_T Add1;                         // '<S3>/Add1'
  real_T Divide;                       // '<S3>/Divide'
  real_T Abs1;                         // '<S3>/Abs1'
  real_T Divide1;                      // '<S3>/Divide1'
  real_T Constant1;                    // '<S2>/Constant1'
  real_T Integrator;                   // '<S2>/Integrator'
  real_T VxBody_mps;                   // '<S126>/Signal Conversion'
  real_T Constant4;                    // '<S2>/Constant4'
  real_T Integrator1_f;                // '<S2>/Integrator1'
  real_T SteerWhAngle_DZ_deg;          // '<S1>/SteerWhlMdl'
  real_T WhlAngF_deg;                  // '<S2>/Gain1'
  real_T WhlAngF_rad;                  // '<S2>/Gain'
  real_T Omega_w_rads;                 // '<S126>/Gain1'
  real_T UnitDelay;                    // '<S2>/Unit Delay'
  real_T Divide1_l;                    // '<S129>/Divide1'
  real_T Gain2;                        // '<S129>/Gain2'
  real_T FxfDr;                        // '<S129>/Gain'
  real_T UnitDelay1_g;                 // '<Root>/Unit Delay1'
  real_T bwdWhlPre_Mpa[4];             // '<S1>/Brake_System'
  real_T fwdWhlPre_Mpa[2];             // '<S1>/Brake_System'
  real_T TrailWhlPre_Mpa[6];           // '<S1>/Brake_System'
  real_T BraF;                         // '<S128>/Fcn'
  real_T Gain;                         // '<S128>/Gain'
  real_T BraF_g;                       // '<S128>/Switch'
  real_T Fxf_N;                        // '<S129>/Add'
  real_T uDLookupTable;                // '<S3>/1-D Lookup Table'
  real_T Product1;                     // '<S3>/Product1'
  real_T Tw_Nm;                        // '<S2>/Product'
  real_T Add2;                         // '<S129>/Add2'
  real_T Fxr;                          // '<S129>/Gain1'
  real_T Fxr_N;                        // '<S129>/Add1'
  real_T Gain3;                        // '<S127>/Gain3'
  real_T Fextx;                        // '<S127>/Switch'
  real_T Add1_h;                       // '<S127>/Add1'
  real_T Add_c;                        // '<S2>/Add'
  real_T Gain_g;                       // '<Root>/Gain'
  real_T Cos;                          // '<Root>/Cos'
  real_T Product;                      // '<Root>/Product'
  real_T Sin;                          // '<Root>/Sin'
  real_T Product1_f;                   // '<Root>/Product1'
  real_T Memory;                       // '<S118>/Memory'
  real_T domega_o;                     // '<S117>/domega_o'
  real_T Integrator_k;                 // '<S118>/Integrator'
  real_T Gain2_c;                      // '<S117>/Gain2'
  real_T Integrator_n;                 // '<S117>/Integrator'
  real_T Gain1;                        // '<S117>/Gain1'
  real_T Subtract1;                    // '<S117>/Subtract1'
  real_T UnaryMinus;                   // '<S117>/Unary Minus'
  real_T Integrator_i;                 // '<S31>/Integrator'
  real_T ClutchGain;                   // '<S13>/ClutchGain'
  real_T Saturation_o;                 // '<S32>/Saturation'
  real_T TorqueConversion;             // '<S32>/Torque Conversion'
  real_T UnitDelay_h;                  // '<Root>/Unit Delay'
  real_T GearSel;                      // '<S3>/TCU'
  real_T Memory3;                      // '<S35>/Memory3'
  real_T Memory_h;                     // '<S35>/Memory'
  real_T Add2_m;                       // '<S35>/Add2'
  real_T Memory1;                      // '<S35>/Memory1'
  real_T CmdGear;                      // '<S35>/Switch1'
  real_T Constant;                     // '<S38>/Constant'
  real_T Integrator1_o1;               // '<S38>/Integrator1'
  real_T Integrator1_o2;               // '<S38>/Integrator1'
  real_T NewGear;                      // '<S35>/Switch2'
  real_T b;                            // '<S15>/Gear2damping'
  real_T J;                            // '<S15>/Gear2inertias'
  real_T N;                            // '<S15>/Gear2Ratios'
  real_T IC;                           // '<S17>/IC'
  real_T Switch;                       // '<S17>/Switch'
  real_T IC_c;                         // '<S18>/IC'
  real_T Switch_f;                     // '<S18>/Switch'
  real_T IC_i;                         // '<S16>/IC'
  real_T Switch_i;                     // '<S16>/Switch'
  real_T Merge;                        // '<S10>/Merge'
  real_T Merge1;                       // '<S10>/Merge1'
  real_T Merge2;                       // '<S10>/Merge2'
  real_T Merge3;                       // '<S10>/Merge3'
  real_T PwrStoredTrans;               // '<S10>/Merge4'
  real_T PwrCltchLoss;                 // '<S10>/Merge4'
  real_T PwrDampLoss;                  // '<S10>/Merge4'
  real_T PwrEffLoss;                   // '<S10>/Merge4'
  real_T Product_l;                    // '<S13>/Product'
  real_T upi;                          // '<S13>/2*pi'
  real_T Switch_i0;                    // '<S13>/Switch'
  real_T Sum;                          // '<S31>/Sum'
  real_T Product_a;                    // '<S31>/Product'
  real_T Ratioofstatictokinetic;       // '<S32>/Ratio of static to kinetic'
  real_T Memory1_h;                    // '<S38>/Memory1'
  real_T UnaryMinus2;                  // '<S38>/Unary Minus2'
  real_T Memory1_k;                    // '<S39>/Memory1'
  real_T Switch1;                      // '<S39>/Switch1'
  real_T Memory2;                      // '<S38>/Memory2'
  real_T Switch1_d;                    // '<S38>/Switch1'
  real_T Gain1_m;                      // '<S38>/Gain1'
  real_T IC_o;                         // '<S40>/IC'
  real_T Integrator1_o1_e;             // '<S40>/Integrator1'
  real_T Integrator1_o2_i;             // '<S40>/Integrator1'
  real_T DataTypeConversion;           // '<S40>/Data Type Conversion'
  real_T Gain1_mt;                     // '<S40>/Gain1'
  real_T Abs_j;                        // '<S48>/Abs'
  real_T Product3;                     // '<S48>/Product3'
  real_T Add3;                         // '<S48>/Add3'
  real_T ApparentInertiaRatio;         // '<S48>/Product8'
  real_T Product2;                     // '<S13>/Product2'
  real_T Product1_e;                   // '<S48>/Product1'
  real_T InputClutchDamping;           // '<S48>/Input Clutch Damping'
  real_T ApparentTransDamping;         // '<S48>/Product2'
  real_T Sum2;                         // '<S48>/Sum2'
  real_T Product4;                     // '<S48>/Product4'
  real_T Sum3;                         // '<S48>/Sum3'
  real_T Abs_c;                        // '<S45>/Abs'
  real_T Abs_f;                        // '<S49>/Abs'
  real_T Product3_k;                   // '<S49>/Product3'
  real_T Add3_l;                       // '<S49>/Add3'
  real_T InputDamping;                 // '<S49>/Input Damping'
  real_T Product1_et;                  // '<S49>/Product1'
  real_T Product2_m;                   // '<S49>/Product2'
  real_T ApparentInertiaRatio_j;       // '<S49>/Product8'
  real_T Sum2_j;                       // '<S49>/Sum2'
  real_T Product4_b;                   // '<S49>/Product4'
  real_T Sum3_l;                       // '<S49>/Sum3'
  real_T Product1_p;                   // '<S13>/Product1'
  real_T Sum_g;                        // '<S46>/Sum'
  real_T Abs_e;                        // '<S50>/Abs'
  real_T TrqCmd;                       // '<S3>/Engine_ECU'
  real_T Sum_l;                        // '<S5>/Sum'
  real_T Divide_c;                     // '<S5>/Divide'
  real_T Memory_c;                     // '<S89>/Memory'
  real_T domega_o_o;                   // '<S88>/domega_o'
  real_T Integrator_m;                 // '<S89>/Integrator'
  real_T Gain2_g;                      // '<S88>/Gain2'
  real_T Integrator_if;                // '<S88>/Integrator'
  real_T Gain1_e;                      // '<S88>/Gain1'
  real_T Subtract1_b;                  // '<S88>/Subtract1'
  real_T Memory_l;                     // '<S81>/Memory'
  real_T domega_o_h;                   // '<S80>/domega_o'
  real_T Integrator_c;                 // '<S81>/Integrator'
  real_T Gain2_c4;                     // '<S80>/Gain2'
  real_T Integrator_mv;                // '<S80>/Integrator'
  real_T Gain1_mx;                     // '<S80>/Gain1'
  real_T Subtract1_p;                  // '<S80>/Subtract1'
  real_T Add_a;                        // '<S6>/Add'
  real_T Gain_a;                       // '<S6>/Gain'
  real_T a_sim;                        // '<S6>/Divide'
  real_T v;                            // '<S6>/Integrator'
  real_T diffDir;                      // '<S67>/Switch'
  real_T VectorConcatenate[2];         // '<S63>/Vector Concatenate'
  real_T Integrator_ng[2];             // '<S63>/Integrator'
  real_T Product_d[2];                 // '<S67>/Product'
  real_T Gain_l[2];                    // '<S67>/Gain'
  real_T SumofElements;                // '<S67>/Sum of Elements'
  real_T UnaryMinus1[2];               // '<S67>/Unary Minus1'
  real_T Gain1_l[2];                   // '<S67>/Gain1'
  real_T VectorConcatenate_n[4];       // '<S67>/Vector Concatenate'
  real_T Product1_g;                   // '<S77>/Product1'
  real_T Switch_j;                     // '<S77>/Switch'
  real_T Product4_j;                   // '<S77>/Product4'
  real_T UnaryMinus_f;                 // '<S88>/Unary Minus'
  real_T Product1_a;                   // '<S75>/Product1'
  real_T Switch_n;                     // '<S75>/Switch'
  real_T Product4_o;                   // '<S75>/Product4'
  real_T UnaryMinus_m;                 // '<S80>/Unary Minus'
  real_T Product1_l;                   // '<S76>/Product1'
  real_T Switch_jk;                    // '<S76>/Switch'
  real_T Product4_k;                   // '<S76>/Product4'
  real_T UnaryMinus2_g[2];             // '<S70>/Unary Minus2'
  real_T diffDir_l;                    // '<S70>/Switch1'
  real_T Product1_j[2];                // '<S70>/Product1'
  real_T Gain1_f[2];                   // '<S70>/Gain1'
  real_T omegadot[3];                  // '<S70>/Vector Concatenate'
  real_T Gain11;                       // '<S9>/Gain11'
  real_T Divide5;                      // '<S9>/Divide5'
  real_T Subtract;                     // '<S80>/Subtract'
  real_T Switch_o;                     // '<S81>/Switch'
  real_T Sum_i;                        // '<S81>/Sum'
  real_T Product_ab;                   // '<S81>/Product'
  real_T Subtract_b;                   // '<S88>/Subtract'
  real_T Switch_d;                     // '<S89>/Switch'
  real_T Sum_o;                        // '<S89>/Sum'
  real_T Product_dd;                   // '<S89>/Product'
  real_T VectorConcatenate_nl[4];      // '<S6>/Vector Concatenate'
  real_T EngSpdFdbk_rpm_g;             // '<S3>/Gain1'
  real_T Integrator_i4;                // '<S99>/Integrator'
  real_T RPMtodegs;                    // '<S99>/RPM to deg//s'
  real_T Subtract_i;                   // '<S117>/Subtract'
  real_T Switch_jp;                    // '<S118>/Switch'
  real_T Sum_k;                        // '<S118>/Sum'
  real_T Product_h;                    // '<S118>/Product'
  real_T Gain1_p;                      // '<S127>/Gain1'
  real_T Sin_e;                        // '<S127>/Sin'
  real_T Product_k;                    // '<S127>/Product'
  real_T Gain2_cz;                     // '<S127>/Gain2'
  real_T Sin1;                         // '<S127>/Sin1'
  real_T Product2_e;                   // '<S127>/Product2'
  real_T Gain5;                        // '<S127>/Gain5'
  real_T Gain4;                        // '<S127>/Gain4'
  real_T mu_total;                     // '<S127>/Sum1'
  real_T Rx;                           // '<S127>/Product3'
  real_T Gain_e;                       // '<S127>/Gain'
  real_T Add_j;                        // '<S127>/Add'
  real_T UnitDelay_f;                  // '<S131>/Unit Delay'
  real_T UnitDelay_c;                  // '<S132>/Unit Delay'
  real_T UnaryMinus_e;                 // '<S67>/Unary Minus'
  real_T TmpSignalConversionAtSFunctionInport1[3];// '<S63>/Open Differential'
  real_T xdot[2];                      // '<S63>/Open Differential'
  real_T UnaryMinus_d;                 // '<S70>/Unary Minus'
  real_T Product1_c;                   // '<S10>/Product1'
  real_T Eta1D;                        // '<S57>/Eta 1D'
  real_T PumpIntegrator;               // '<S14>/Pump Integrator'
  real_T Product1_lu;                  // '<S52>/Product1'
  real_T Switch_g;                     // '<S52>/Switch'
  real_T Product4_d;                   // '<S52>/Product4'
  real_T Subtract_d;                   // '<S52>/Subtract'
  real_T Product2_c;                   // '<S52>/Product2'
  real_T w_out;                        // '<S14>/Integrator'
  real_T Product1_d;                   // '<S53>/Product1'
  real_T Switch_h;                     // '<S53>/Switch'
  real_T Product4_g;                   // '<S53>/Product4'
  real_T Subtract_e;                   // '<S53>/Subtract'
  real_T Product2_mo;                  // '<S53>/Product2'
  real_T PwrEffLoss_p;                 // '<S14>/Add'
  real_T Product4_a;                   // '<S54>/Product4'
  real_T Add2_d;                       // '<S54>/Add2'
  real_T Gain_n;                       // '<S54>/Gain'
  real_T TrigonometricFunction;        // '<S54>/Trigonometric Function'
  real_T Product2_ej;                  // '<S54>/Product2'
  real_T Product1_pe;                  // '<S54>/Product1'
  real_T Product2_j;                   // '<S55>/Product2'
  real_T T_ext;                        // '<S55>/Add2'
  real_T Add1_d;                       // '<S14>/Add1'
  real_T InputClutchDamping_d;         // '<S14>/Input Clutch Damping'
  real_T InputSum;                     // '<S14>/Input Sum'
  real_T Product2_p;                   // '<S14>/Product2'
  real_T Product_ki;                   // '<S14>/Product'
  real_T PwrStoredTrans_n;             // '<S14>/Add2'
  real_T Product10;                    // '<S14>/Product10'
  real_T Product_b;                    // '<S55>/Product'
  real_T Add3_c;                       // '<S14>/Add3'
  real_T Product3_e;                   // '<S54>/Product3'
  real_T UnaryMinus_k;                 // '<S54>/Unary Minus'
  real_T InputClutchInertia;           // '<S14>/Input Clutch Inertia'
  real_T Product1_j2;                  // '<S14>/Product1'
  real_T Switch_k;                     // '<S56>/Switch'
  real_T Product3_m;                   // '<S14>/Product3'
  real_T PwrDampLoss_b;                // '<S14>/Unary Minus'
  real_T Fcn;                          // '<S56>/Fcn'
  real_T Abs_js;                       // '<S56>/Abs'
  real_T Eta1D_p;                      // '<S30>/Eta 1D'
  real_T Abs_ck;                       // '<S12>/Abs'
  real_T omega;                        // '<S12>/Locked Shaft Integrator'
  real_T Product1_o;                   // '<S28>/Product1'
  real_T Switch_nc;                    // '<S28>/Switch'
  real_T Product4_n;                   // '<S28>/Product4'
  real_T Subtract_d1;                  // '<S28>/Subtract'
  real_T Product2_f;                   // '<S28>/Product2'
  real_T Product5;                     // '<S12>/Product5'
  real_T Product1_gc;                  // '<S29>/Product1'
  real_T Switch_j0;                    // '<S29>/Switch'
  real_T Product4_nt;                  // '<S29>/Product4'
  real_T Subtract_a;                   // '<S29>/Subtract'
  real_T Product2_c2;                  // '<S29>/Product2'
  real_T PwrEffLoss_i;                 // '<S12>/Add'
  real_T Product1_f3;                  // '<S12>/Product1'
  real_T Product6;                     // '<S12>/Product6'
  real_T inputclutchDamping;           // '<S12>/input clutch Damping'
  real_T Add1_f;                       // '<S12>/Add1'
  real_T Add2_l;                       // '<S12>/Add2'
  real_T Product3_mq;                  // '<S12>/Product3'
  real_T Add3_o;                       // '<S12>/Add3'
  real_T Sum_k0;                       // '<S12>/Sum'
  real_T PwrStoredTrans_d;             // '<S12>/Product'
  real_T Product2_mi;                  // '<S12>/Product2'
  real_T UnaryMinus_b;                 // '<S12>/Unary Minus'
  real_T PwrDampLoss_f;                // '<S12>/Product7'
  real_T Product8;                     // '<S12>/Product8'
  int8_T Gain1_h;                      // '<S1>/Gain1'
  boolean_T UnitDelay2;                // '<S3>/Unit Delay2'
  boolean_T Compare;                   // '<S135>/Compare'
  boolean_T Compare_g;                 // '<S134>/Compare'
  boolean_T Memory_n;                  // '<S47>/Memory'
  boolean_T Compare_e;                 // '<S37>/Compare'
  boolean_T Compare_gz;                // '<S41>/Compare'
  boolean_T Memory2_c;                 // '<S40>/Memory2'
  boolean_T LogicalOperator3;          // '<S39>/Logical Operator3'
  boolean_T Compare_l;                 // '<S42>/Compare'
  boolean_T LogicalOperator2;          // '<S38>/Logical Operator2'
  boolean_T ClutchClosed;              // '<S39>/Logical Operator1'
  boolean_T ClutchClosedandready;      // '<S39>/Logical Operator5'
  boolean_T LogicalOperator7;          // '<S39>/Logical Operator7'
  boolean_T Newgearrequest;            // '<S39>/Relational Operator'
  boolean_T LogicalOperator2_e;        // '<S39>/Logical Operator2'
  boolean_T LogicalOperator3_k;        // '<S38>/Logical Operator3'
  boolean_T Begin;                     // '<S39>/Logical Operator4'
  boolean_T LogicalOperator6;          // '<S39>/Logical Operator6'
  boolean_T Compare_lp;                // '<S43>/Compare'
  boolean_T Memory_k;                  // '<S44>/Memory'
  boolean_T LogicalOperator;           // '<S44>/Logical Operator'
  boolean_T LogicalOperator2_ex;       // '<S44>/Logical Operator2'
  boolean_T LogicalOperator1;          // '<S44>/Logical Operator1'
  boolean_T RelationalOperator;        // '<S45>/Relational Operator'
  boolean_T VelocitiesMatch;           // '<S46>/Velocities Match'
  boolean_T RelationalOperator_n;      // '<S50>/Relational Operator'
  boolean_T Logic;                     // '<S46>/Logic'
  boolean_T CombinatorialLogic;        // '<S47>/Combinatorial  Logic'
  boolean_T Compare_d;                 // '<S133>/Compare'
  boolean_T Compare_h;                 // '<S58>/Compare'
  boolean_T Compare_gp;                // '<S59>/Compare'
  boolean_T LogicalOperator_k;         // '<S56>/Logical Operator'
  B_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T TwoDofDynamic;// '<S125>/TwoDofDynamic' 
} B_CNHTC_VEHICLE_MODEL_PureSL_T;

// Block states (default storage) for system '<Root>'
typedef struct {
  real_T UnitDelay1_DSTATE;            // '<S3>/Unit Delay1'
  real_T UnitDelay3_DSTATE;            // '<S3>/Unit Delay3'
  real_T UnitDelay4_DSTATE;            // '<S3>/Unit Delay4'
  real_T UnitDelay_DSTATE;             // '<S2>/Unit Delay'
  real_T UnitDelay1_DSTATE_h;          // '<Root>/Unit Delay1'
  real_T UnitDelay_DSTATE_i;           // '<Root>/Unit Delay'
  real_T Memory_PreviousInput;         // '<S118>/Memory'
  real_T Memory3_PreviousInput;        // '<S35>/Memory3'
  real_T Memory_PreviousInput_a;       // '<S35>/Memory'
  real_T Memory1_PreviousInput;        // '<S35>/Memory1'
  real_T Memory1_PreviousInput_b;      // '<S38>/Memory1'
  real_T Memory1_PreviousInput_p;      // '<S39>/Memory1'
  real_T Memory2_PreviousInput;        // '<S38>/Memory2'
  real_T Memory_PreviousInput_p;       // '<S89>/Memory'
  real_T Memory_PreviousInput_c;       // '<S81>/Memory'
  int_T Integrator_IWORK;              // '<S2>/Integrator'
  int_T Integrator1_IWORK;             // '<S2>/Integrator1'
  int_T Integrator_IWORK_j;            // '<S118>/Integrator'
  int_T Integrator1_IWORK_a;           // '<S38>/Integrator1'
  int_T Integrator1_IWORK_j;           // '<S40>/Integrator1'
  int_T Integrator_IWORK_i;            // '<S89>/Integrator'
  int_T Integrator_IWORK_c;            // '<S81>/Integrator'
  int_T Integrator_IWORK_l;            // '<S63>/Integrator'
  int_T PumpIntegrator_IWORK;          // '<S14>/Pump Integrator'
  int_T Integrator_IWORK_p;            // '<S14>/Integrator'
  int_T LockedShaftIntegrator_IWORK;   // '<S12>/Locked Shaft Integrator'
  int_T VelocitiesMatch_MODE;          // '<S46>/Velocities Match'
  boolean_T UnitDelay2_DSTATE;         // '<S3>/Unit Delay2'
  int8_T If_ActiveSubsystem;           // '<S10>/If'
  boolean_T Memory_PreviousInput_j;    // '<S47>/Memory'
  boolean_T Memory2_PreviousInput_d;   // '<S40>/Memory2'
  boolean_T IC_FirstOutputTime;        // '<S17>/IC'
  boolean_T IC_FirstOutputTime_p;      // '<S18>/IC'
  boolean_T IC_FirstOutputTime_c;      // '<S16>/IC'
  boolean_T IC_FirstOutputTime_d;      // '<S40>/IC'
  boolean_T Memory_PreviousInput_k;    // '<S44>/Memory'
  DW_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T TwoDofDynamic;// '<S125>/TwoDofDynamic' 
} DW_CNHTC_VEHICLE_MODEL_PureSL_T;

// Continuous states (default storage)
typedef struct {
  real_T Integrator1_CSTATE;           // '<S5>/Integrator1'
  real_T Integrator_CSTATE;            // '<S2>/Integrator'
  real_T Integrator1_CSTATE_h;         // '<S2>/Integrator1'
  real_T Integrator_CSTATE_l;          // '<Root>/Integrator'
  real_T Integrator1_CSTATE_o;         // '<Root>/Integrator1'
  real_T Integrator_CSTATE_m;          // '<S118>/Integrator'
  real_T Integrator_CSTATE_d;          // '<S117>/Integrator'
  real_T Integrator_CSTATE_df;         // '<S31>/Integrator'
  real_T Integrator1_CSTATE_d;         // '<S38>/Integrator1'
  real_T Integrator1_CSTATE_de;        // '<S40>/Integrator1'
  real_T Integrator_CSTATE_k;          // '<S89>/Integrator'
  real_T Integrator_CSTATE_b;          // '<S88>/Integrator'
  real_T Integrator_CSTATE_i;          // '<S81>/Integrator'
  real_T Integrator_CSTATE_d5;         // '<S80>/Integrator'
  real_T Integrator_CSTATE_o;          // '<S6>/Integrator'
  real_T Integrator_CSTATE_lv[2];      // '<S63>/Integrator'
  real_T Integrator_CSTATE_bf;         // '<S99>/Integrator'
  real_T PumpIntegrator_CSTATE;        // '<S14>/Pump Integrator'
  real_T Integrator_CSTATE_kg;         // '<S14>/Integrator'
  real_T LockedShaftIntegrator_CSTATE; // '<S12>/Locked Shaft Integrator'
} X_CNHTC_VEHICLE_MODEL_PureSL_T;

// Periodic continuous state vector (global)
typedef int_T PeriodicIndX_CNHTC_VEHICLE_MODEL_PureSL_T[1];
typedef real_T PeriodicRngX_CNHTC_VEHICLE_MODEL_PureSL_T[2];

// State derivatives (default storage)
typedef struct {
  real_T Integrator1_CSTATE;           // '<S5>/Integrator1'
  real_T Integrator_CSTATE;            // '<S2>/Integrator'
  real_T Integrator1_CSTATE_h;         // '<S2>/Integrator1'
  real_T Integrator_CSTATE_l;          // '<Root>/Integrator'
  real_T Integrator1_CSTATE_o;         // '<Root>/Integrator1'
  real_T Integrator_CSTATE_m;          // '<S118>/Integrator'
  real_T Integrator_CSTATE_d;          // '<S117>/Integrator'
  real_T Integrator_CSTATE_df;         // '<S31>/Integrator'
  real_T Integrator1_CSTATE_d;         // '<S38>/Integrator1'
  real_T Integrator1_CSTATE_de;        // '<S40>/Integrator1'
  real_T Integrator_CSTATE_k;          // '<S89>/Integrator'
  real_T Integrator_CSTATE_b;          // '<S88>/Integrator'
  real_T Integrator_CSTATE_i;          // '<S81>/Integrator'
  real_T Integrator_CSTATE_d5;         // '<S80>/Integrator'
  real_T Integrator_CSTATE_o;          // '<S6>/Integrator'
  real_T Integrator_CSTATE_lv[2];      // '<S63>/Integrator'
  real_T Integrator_CSTATE_bf;         // '<S99>/Integrator'
  real_T PumpIntegrator_CSTATE;        // '<S14>/Pump Integrator'
  real_T Integrator_CSTATE_kg;         // '<S14>/Integrator'
  real_T LockedShaftIntegrator_CSTATE; // '<S12>/Locked Shaft Integrator'
} XDot_CNHTC_VEHICLE_MODEL_PureSL_T;

// State disabled
typedef struct {
  boolean_T Integrator1_CSTATE;        // '<S5>/Integrator1'
  boolean_T Integrator_CSTATE;         // '<S2>/Integrator'
  boolean_T Integrator1_CSTATE_h;      // '<S2>/Integrator1'
  boolean_T Integrator_CSTATE_l;       // '<Root>/Integrator'
  boolean_T Integrator1_CSTATE_o;      // '<Root>/Integrator1'
  boolean_T Integrator_CSTATE_m;       // '<S118>/Integrator'
  boolean_T Integrator_CSTATE_d;       // '<S117>/Integrator'
  boolean_T Integrator_CSTATE_df;      // '<S31>/Integrator'
  boolean_T Integrator1_CSTATE_d;      // '<S38>/Integrator1'
  boolean_T Integrator1_CSTATE_de;     // '<S40>/Integrator1'
  boolean_T Integrator_CSTATE_k;       // '<S89>/Integrator'
  boolean_T Integrator_CSTATE_b;       // '<S88>/Integrator'
  boolean_T Integrator_CSTATE_i;       // '<S81>/Integrator'
  boolean_T Integrator_CSTATE_d5;      // '<S80>/Integrator'
  boolean_T Integrator_CSTATE_o;       // '<S6>/Integrator'
  boolean_T Integrator_CSTATE_lv[2];   // '<S63>/Integrator'
  boolean_T Integrator_CSTATE_bf;      // '<S99>/Integrator'
  boolean_T PumpIntegrator_CSTATE;     // '<S14>/Pump Integrator'
  boolean_T Integrator_CSTATE_kg;      // '<S14>/Integrator'
  boolean_T LockedShaftIntegrator_CSTATE;// '<S12>/Locked Shaft Integrator'
} XDis_CNHTC_VEHICLE_MODEL_PureSL_T;

// Zero-crossing (trigger) state
typedef struct {
  ZCSigState Integrator_Reset_ZCE;     // '<S118>/Integrator'
  ZCSigState Integrator1_Reset_ZCE;    // '<S40>/Integrator1'
  ZCSigState VelocitiesMatch_Input_ZCE;// '<S46>/Velocities Match'
  ZCSigState Integrator_Reset_ZCE_g;   // '<S89>/Integrator'
  ZCSigState Integrator_Reset_ZCE_a;   // '<S81>/Integrator'
} PrevZCX_CNHTC_VEHICLE_MODEL_PureSL_T;

#ifndef ODE3_INTG
#define ODE3_INTG

// ODE3 Integration Data
typedef struct {
  real_T *y;                           // output
  real_T *f[3];                        // derivatives
} ODE3_IntgData;

#endif

// External outputs (root outports fed by signals with default storage)
typedef struct {
  real_T GearPos;                      // '<Root>/GearPos'
  boolean_T foundation_brake_in_use;   // '<Root>/foundation_brake_in_use'
  real_T EngTrq_Nm;                    // '<Root>/EngTrq_Nm'
  real_T EngSpd_rpm;                   // '<Root>/EngSpd_rpm'
  real_T engine_torque_loss_percent;   // '<Root>/engine_torque_loss_percent'
  boolean_T shift_in_process;          // '<Root>/shift_in_process'
  real_T engine_torque_percent;        // '<Root>/engine_torque_percent'
  real_T Velong_kph_p;                 // '<Root>/Velong_kph'
  real_T Yaw_deg_n;                    // '<Root>/Yaw_deg'
  real_T Omega_w_rads;                 // '<Root>/Omega_w_rads'
  real_T ax_mps2_f;                    // '<Root>/ax_mps2'
  real_T Vx_kph_e;                     // '<Root>/Vx_kph'
  real_T Vy_kph_a;                     // '<Root>/Vy_kph'
  real_T X_p;                          // '<Root>/X'
  real_T Y_h;                          // '<Root>/Y'
} ExtY_CNHTC_VEHICLE_MODEL_PureSL_T;

// Parameters (default storage)
struct P_CNHTC_VEHICLE_MODEL_PureSL_T_ {
  real_T OpenDifferential_Jd;          // Mask Parameter: OpenDifferential_Jd
                                          //  Referenced by: '<S63>/Jd'

  real_T OpenDifferential_Jw1;         // Mask Parameter: OpenDifferential_Jw1
                                          //  Referenced by: '<S63>/Jw1'

  real_T OpenDifferential_Jw2;         // Mask Parameter: OpenDifferential_Jw2
                                          //  Referenced by: '<S63>/Jw3'

  real_T AutomatedManualTransmission_K_c;
                              // Mask Parameter: AutomatedManualTransmission_K_c
                                 //  Referenced by: '<S13>/ClutchGain'

  real_T AutomatedManualTransmission_R;
                                // Mask Parameter: AutomatedManualTransmission_R
                                   //  Referenced by: '<S32>/Torque Conversion'

  real_T PropShaft_b;                  // Mask Parameter: PropShaft_b
                                          //  Referenced by: '<S117>/Gain2'

  real_T TorsionalCompliance2_b;       // Mask Parameter: TorsionalCompliance2_b
                                          //  Referenced by: '<S88>/Gain2'

  real_T TorsionalCompliance1_b;       // Mask Parameter: TorsionalCompliance1_b
                                          //  Referenced by: '<S80>/Gain2'

  real_T OpenDifferential_bd;          // Mask Parameter: OpenDifferential_bd
                                          //  Referenced by: '<S63>/bd'

  real_T AutomatedManualTransmission_bin;
                              // Mask Parameter: AutomatedManualTransmission_bin
                                 //  Referenced by:
                                 //    '<S12>/input clutch Damping'
                                 //    '<S14>/Input Clutch Damping'
                                 //    '<S48>/Input Clutch Damping'
                                 //    '<S49>/Input Damping'

  real_T OpenDifferential_bw1;         // Mask Parameter: OpenDifferential_bw1
                                          //  Referenced by: '<S63>/bw1'

  real_T OpenDifferential_bw2;         // Mask Parameter: OpenDifferential_bw2
                                          //  Referenced by: '<S63>/bw2'

  real_T CompareToConstant_const;     // Mask Parameter: CompareToConstant_const
                                         //  Referenced by: '<S135>/Constant'

  real_T CompareToConstant_const_k; // Mask Parameter: CompareToConstant_const_k
                                       //  Referenced by: '<S134>/Constant'

  real_T CompareToConstant_const_d; // Mask Parameter: CompareToConstant_const_d
                                       //  Referenced by: '<S133>/Constant'

  real_T PropShaft_domega_o;           // Mask Parameter: PropShaft_domega_o
                                          //  Referenced by: '<S117>/domega_o'

  real_T TorsionalCompliance2_domega_o;
                                // Mask Parameter: TorsionalCompliance2_domega_o
                                   //  Referenced by: '<S88>/domega_o'

  real_T TorsionalCompliance1_domega_o;
                                // Mask Parameter: TorsionalCompliance1_domega_o
                                   //  Referenced by: '<S80>/domega_o'

  real_T OpenDifferential_eta;         // Mask Parameter: OpenDifferential_eta
                                          //  Referenced by: '<S79>/Constant'

  real_T MappedCIEngine_f_tbrake[320];// Mask Parameter: MappedCIEngine_f_tbrake
                                         //  Referenced by: '<S112>/EngTrq Table'

  real_T MappedCIEngine_f_tbrake_n_bpt[16];
                                // Mask Parameter: MappedCIEngine_f_tbrake_n_bpt
                                   //  Referenced by: '<S112>/EngTrq Table'

  real_T MappedCIEngine_f_tbrake_t_bpt[20];
                                // Mask Parameter: MappedCIEngine_f_tbrake_t_bpt
                                   //  Referenced by: '<S112>/EngTrq Table'

  real_T PropShaft_k;                  // Mask Parameter: PropShaft_k
                                          //  Referenced by: '<S117>/Gain1'

  real_T TorsionalCompliance2_k;       // Mask Parameter: TorsionalCompliance2_k
                                          //  Referenced by: '<S88>/Gain1'

  real_T TorsionalCompliance1_k;       // Mask Parameter: TorsionalCompliance1_k
                                          //  Referenced by: '<S80>/Gain1'

  real_T AutomatedManualTransmission_muk;
                              // Mask Parameter: AutomatedManualTransmission_muk
                                 //  Referenced by:
                                 //    '<S32>/Ratio of static to kinetic'
                                 //    '<S32>/Torque Conversion'

  real_T AutomatedManualTransmission_mus;
                              // Mask Parameter: AutomatedManualTransmission_mus
                                 //  Referenced by: '<S32>/Ratio of static to kinetic'

  real_T TorsionalCompliance1_omega_c;
                                 // Mask Parameter: TorsionalCompliance1_omega_c
                                    //  Referenced by: '<S80>/omega_c'

  real_T TorsionalCompliance2_omega_c;
                                 // Mask Parameter: TorsionalCompliance2_omega_c
                                    //  Referenced by: '<S88>/omega_c'

  real_T PropShaft_omega_c;            // Mask Parameter: PropShaft_omega_c
                                          //  Referenced by: '<S117>/omega_c'

  real_T AutomatedManualTransmission_omegain_o;
                        // Mask Parameter: AutomatedManualTransmission_omegain_o
                           //  Referenced by:
                           //    '<S16>/Constant'
                           //    '<S17>/Constant'

  real_T AutomatedManualTransmission_omegaout_o;
                       // Mask Parameter: AutomatedManualTransmission_omegaout_o
                          //  Referenced by: '<S18>/Constant'

  real_T OpenDifferential_omegaw1o; // Mask Parameter: OpenDifferential_omegaw1o
                                       //  Referenced by: '<S63>/Constant'

  real_T OpenDifferential_omegaw2o; // Mask Parameter: OpenDifferential_omegaw2o
                                       //  Referenced by: '<S63>/Constant1'

  real_T AutomatedManualTransmission_tauc;
                             // Mask Parameter: AutomatedManualTransmission_tauc
                                //  Referenced by: '<S13>/Constant1'

  real_T AutomatedManualTransmission_tc;
                               // Mask Parameter: AutomatedManualTransmission_tc
                                  //  Referenced by: '<S38>/Gain1'

  real_T PropShaft_theta_o;            // Mask Parameter: PropShaft_theta_o
                                          //  Referenced by: '<S117>/Integrator'

  real_T TorsionalCompliance2_theta_o;
                                 // Mask Parameter: TorsionalCompliance2_theta_o
                                    //  Referenced by: '<S88>/Integrator'

  real_T TorsionalCompliance1_theta_o;
                                 // Mask Parameter: TorsionalCompliance1_theta_o
                                    //  Referenced by: '<S80>/Integrator'

  real_T div0protectabspoly1_thresh;
                                   // Mask Parameter: div0protectabspoly1_thresh
                                      //  Referenced by:
                                      //    '<S58>/Constant'
                                      //    '<S59>/Constant'

  real_T AutomatedManualTransmission_ts;
                               // Mask Parameter: AutomatedManualTransmission_ts
                                  //  Referenced by: '<S40>/Gain1'

  real_T ElectronicThrottleActuatorDynamics1_wc;
                       // Mask Parameter: ElectronicThrottleActuatorDynamics1_wc
                          //  Referenced by: '<S5>/Constant'

  boolean_T AutomatedManualTransmission_SynchLocked;
                      // Mask Parameter: AutomatedManualTransmission_SynchLocked
                         //  Referenced by: '<S40>/Memory2'

  real_T LockedShaftIntegrator_UpperSat;// Expression: maxAbsSpd
                                           //  Referenced by: '<S12>/Locked Shaft Integrator'

  real_T LockedShaftIntegrator_LowerSat;// Expression: -maxAbsSpd
                                           //  Referenced by: '<S12>/Locked Shaft Integrator'

  real_T Constant_Value;               // Expression: 1
                                          //  Referenced by: '<S28>/Constant'

  real_T Switch_Threshold;             // Expression: 0
                                          //  Referenced by: '<S28>/Switch'

  real_T Constant_Value_b;             // Expression: 1
                                          //  Referenced by: '<S29>/Constant'

  real_T Switch_Threshold_l;           // Expression: 0
                                          //  Referenced by: '<S29>/Switch'

  real_T Constant1_Value;              // Expression: 0
                                          //  Referenced by: '<S12>/Constant1'

  real_T PumpIntegrator_UpperSat;      // Expression: maxAbsSpd
                                          //  Referenced by: '<S14>/Pump Integrator'

  real_T PumpIntegrator_LowerSat;      // Expression: -maxAbsSpd
                                          //  Referenced by: '<S14>/Pump Integrator'

  real_T Constant_Value_d;             // Expression: 1
                                          //  Referenced by: '<S52>/Constant'

  real_T Switch_Threshold_h;           // Expression: 0
                                          //  Referenced by: '<S52>/Switch'

  real_T Integrator_UpperSat;          // Expression: maxAbsSpd
                                          //  Referenced by: '<S14>/Integrator'

  real_T Integrator_LowerSat;          // Expression: -maxAbsSpd
                                          //  Referenced by: '<S14>/Integrator'

  real_T Constant_Value_n;             // Expression: 1
                                          //  Referenced by: '<S53>/Constant'

  real_T Switch_Threshold_p;           // Expression: 0
                                          //  Referenced by: '<S53>/Switch'

  real_T Gain_Gain;                    // Expression: 4
                                          //  Referenced by: '<S54>/Gain'

  real_T OpenDifferential_shaftSwitchMask;// Expression: shaftSwitchMask
                                             //  Referenced by: '<S63>/Open Differential'

  real_T Gain1_Gain;                   // Expression: 1/57.3
                                          //  Referenced by: '<S127>/Gain1'

  real_T Gain2_Gain;                   // Expression: -1
                                          //  Referenced by: '<S127>/Gain2'

  real_T Gain5_Gain;                   // Expression: 3.6
                                          //  Referenced by: '<S127>/Gain5'

  real_T Gain_Gain_g;                  // Expression: -1
                                          //  Referenced by: '<S127>/Gain'

  real_T Constant_Value_p;             // Expression: 0
                                          //  Referenced by: '<S37>/Constant'

  real_T Constant_Value_dg;            // Expression: 0
                                          //  Referenced by: '<S41>/Constant'

  real_T Constant_Value_pn;            // Expression: 0
                                          //  Referenced by: '<S42>/Constant'

  real_T Constant_Value_k;             // Expression: 0
                                          //  Referenced by: '<S43>/Constant'

  real_T UnitDelay1_InitialCondition;  // Expression: 0
                                          //  Referenced by: '<S3>/Unit Delay1'

  real_T Gain1_Gain_p;                 // Expression: 1
                                          //  Referenced by: '<S1>/Gain1'

  real_T Gain_Gain_b;                  // Expression: 1
                                          //  Referenced by: '<S1>/Gain'

  real_T Integrator1_IC;               // Expression: 0
                                          //  Referenced by: '<S5>/Integrator1'

  real_T UnitDelay3_InitialCondition;  // Expression: 0
                                          //  Referenced by: '<S3>/Unit Delay3'

  real_T Saturation_UpperSat;          // Expression: inf
                                          //  Referenced by: '<S3>/Saturation'

  real_T Saturation_LowerSat;          // Expression: 0
                                          //  Referenced by: '<S3>/Saturation'

  real_T UnitDelay4_InitialCondition;  // Expression: 0
                                          //  Referenced by: '<S3>/Unit Delay4'

  real_T Constant1_Value_i;            // Expression: eps
                                          //  Referenced by: '<S3>/Constant1'

  real_T Gain3_Gain;                   // Expression: 3.6
                                          //  Referenced by: '<Root>/Gain3'

  real_T Gain_Gain_m;                  // Expression: 57.3
                                          //  Referenced by: '<S126>/Gain'

  real_T Gain1_Gain_b;                 // Expression: 1/22
                                          //  Referenced by: '<S2>/Gain1'

  real_T Gain_Gain_f;                  // Expression: 1/57.3
                                          //  Referenced by: '<S2>/Gain'

  real_T Gain2_Gain_h;                 // Expression: 57.3
                                          //  Referenced by: '<S126>/Gain2'

  real_T Gain1_Gain_g;                 // Expression: 3.6
                                          //  Referenced by: '<Root>/Gain1'

  real_T UnitDelay_InitialCondition;   // Expression: 0
                                          //  Referenced by: '<S2>/Unit Delay'

  real_T Gain2_Gain_g;                 // Expression: -1
                                          //  Referenced by: '<S129>/Gain2'

  real_T Constant_Value_i;             // Expression: 0
                                          //  Referenced by: '<S128>/Constant'

  real_T UnitDelay1_InitialCondition_o;// Expression: 0
                                          //  Referenced by: '<Root>/Unit Delay1'

  real_T Gain_Gain_h;                  // Expression: -1
                                          //  Referenced by: '<S128>/Gain'

  real_T Constant3_Value;              // Expression: 0
                                          //  Referenced by: '<S127>/Constant3'

  real_T Gain3_Gain_m;                 // Expression: 9.801
                                          //  Referenced by: '<S127>/Gain3'

  real_T Constant_Value_pr;            // Expression: 0
                                          //  Referenced by: '<S127>/Constant'

  real_T Constant1_Value_h;            // Expression: 0
                                          //  Referenced by: '<S127>/Constant1'

  real_T Gain_Gain_h3;                 // Expression: 1/57.3
                                          //  Referenced by: '<Root>/Gain'

  real_T Gain2_Gain_n;                 // Expression: 3.6
                                          //  Referenced by: '<Root>/Gain2'

  real_T Gain4_Gain;                   // Expression: 3.6
                                          //  Referenced by: '<Root>/Gain4'

  real_T Integrator_IC;                // Expression: 0
                                          //  Referenced by: '<Root>/Integrator'

  real_T Integrator1_IC_d;             // Expression: 0
                                          //  Referenced by: '<Root>/Integrator1'

  real_T Memory_InitialCondition;      // Expression: 0
                                          //  Referenced by: '<S118>/Memory'

  real_T Integrator_IC_m;              // Expression: 0
                                          //  Referenced by: '<S31>/Integrator'

  real_T Saturation_UpperSat_p;        // Expression: inf
                                          //  Referenced by: '<S32>/Saturation'

  real_T Saturation_LowerSat_p;        // Expression: eps
                                          //  Referenced by: '<S32>/Saturation'

  real_T UnitDelay_InitialCondition_f; // Expression: 0
                                          //  Referenced by: '<Root>/Unit Delay'

  real_T Constant_Value_kv;            // Expression: ClutchLocked
                                          //  Referenced by: '<S38>/Constant'

  real_T Integrator1_UpperSat;         // Expression: 1
                                          //  Referenced by: '<S38>/Integrator1'

  real_T Integrator1_LowerSat;         // Expression: 0
                                          //  Referenced by: '<S38>/Integrator1'

  real_T Gear2inertias_tableData[13];  // Expression: Jout
                                          //  Referenced by: '<S15>/Gear2inertias'

  real_T Constant1_Value_k;            // Expression: 1
                                          //  Referenced by: '<S17>/Constant1'

  real_T IC_Value;                     // Expression: 0
                                          //  Referenced by: '<S17>/IC'

  real_T Switch_Threshold_f;           // Expression: 0
                                          //  Referenced by: '<S17>/Switch'

  real_T Constant1_Value_l;            // Expression: 1
                                          //  Referenced by: '<S18>/Constant1'

  real_T IC_Value_m;                   // Expression: 0
                                          //  Referenced by: '<S18>/IC'

  real_T Switch_Threshold_fk;          // Expression: 0
                                          //  Referenced by: '<S18>/Switch'

  real_T Constant1_Value_lc;           // Expression: 1
                                          //  Referenced by: '<S16>/Constant1'

  real_T IC_Value_mc;                  // Expression: 0
                                          //  Referenced by: '<S16>/IC'

  real_T Switch_Threshold_n;           // Expression: 0
                                          //  Referenced by: '<S16>/Switch'

  real_T Merge4_1_InitialOutput;   // Computed Parameter: Merge4_1_InitialOutput
                                      //  Referenced by: '<S10>/Merge4'

  real_T Merge4_2_InitialOutput;   // Computed Parameter: Merge4_2_InitialOutput
                                      //  Referenced by: '<S10>/Merge4'

  real_T Merge4_3_InitialOutput;   // Computed Parameter: Merge4_3_InitialOutput
                                      //  Referenced by: '<S10>/Merge4'

  real_T Merge4_4_InitialOutput;   // Computed Parameter: Merge4_4_InitialOutput
                                      //  Referenced by: '<S10>/Merge4'

  real_T upi_Gain;                     // Expression: 2*pi
                                          //  Referenced by: '<S13>/2*pi'

  real_T Constant_Value_ks;            // Expression: 0
                                          //  Referenced by: '<S13>/Constant'

  real_T Memory1_InitialCondition;     // Expression: 1
                                          //  Referenced by: '<S38>/Memory1'

  real_T Memory1_InitialCondition_d;   // Expression: 0
                                          //  Referenced by: '<S39>/Memory1'

  real_T Memory2_InitialCondition;     // Expression: -1
                                          //  Referenced by: '<S38>/Memory2'

  real_T Constant1_Value_n;            // Expression: 0
                                          //  Referenced by: '<S40>/Constant1'

  real_T IC_Value_a;                   // Expression: SynchLocked
                                          //  Referenced by: '<S40>/IC'

  real_T Integrator1_UpperSat_a;       // Expression: 1
                                          //  Referenced by: '<S40>/Integrator1'

  real_T Integrator1_LowerSat_l;       // Expression: -eps
                                          //  Referenced by: '<S40>/Integrator1'

  real_T VelocitiesMatch_Offset;       // Expression: 0
                                          //  Referenced by: '<S46>/Velocities Match'

  real_T Constant_Value_h;             // Expression: 0
                                          //  Referenced by: '<S3>/Constant'

  real_T Memory_InitialCondition_o;    // Expression: 0
                                          //  Referenced by: '<S89>/Memory'

  real_T Memory_InitialCondition_g;    // Expression: 0
                                          //  Referenced by: '<S81>/Memory'

  real_T Constant_Value_ir;            // Expression: 18000
                                          //  Referenced by: '<S6>/Constant'

  real_T Integrator_IC_j;              // Expression: 0
                                          //  Referenced by: '<S6>/Integrator'

  real_T Constant1_Value_p;            // Expression: 1
                                          //  Referenced by: '<S67>/Constant1'

  real_T Constant_Value_kz;            // Expression: shaftSwitchMask
                                          //  Referenced by: '<S67>/Constant'

  real_T Switch_Threshold_b;           // Expression: 1
                                          //  Referenced by: '<S67>/Switch'

  real_T Integrator_UpperSat_h;        // Expression: maxAbsSpd
                                          //  Referenced by: '<S63>/Integrator'

  real_T Integrator_LowerSat_e;        // Expression: -maxAbsSpd
                                          //  Referenced by: '<S63>/Integrator'

  real_T Gain1_Gain_o;                 // Expression: 1/2
                                          //  Referenced by: '<S67>/Gain1'

  real_T Constant_Value_m;             // Expression: 1
                                          //  Referenced by: '<S77>/Constant'

  real_T Switch_Threshold_d;           // Expression: 0
                                          //  Referenced by: '<S77>/Switch'

  real_T Constant_Value_f;             // Expression: 1
                                          //  Referenced by: '<S75>/Constant'

  real_T Switch_Threshold_lf;          // Expression: 0
                                          //  Referenced by: '<S75>/Switch'

  real_T Constant_Value_bq;            // Expression: 1
                                          //  Referenced by: '<S76>/Constant'

  real_T Switch_Threshold_l2;          // Expression: 0
                                          //  Referenced by: '<S76>/Switch'

  real_T Constant_Value_l;             // Expression: shaftSwitchMask
                                          //  Referenced by: '<S70>/Constant'

  real_T Constant6_Value;              // Expression: 1
                                          //  Referenced by: '<S70>/Constant6'

  real_T Switch1_Threshold;            // Expression: 1
                                          //  Referenced by: '<S70>/Switch1'

  real_T Gain11_Gain;                  // Expression: 1/3.6
                                          //  Referenced by: '<S9>/Gain11'

  real_T Reset_Value;                  // Expression: 1
                                          //  Referenced by: '<S81>/Reset'

  real_T Reset_Value_o;                // Expression: 1
                                          //  Referenced by: '<S89>/Reset'

  real_T Gain1_Gain_a;                 // Expression: 60/2/pi
                                          //  Referenced by: '<S3>/Gain1'

  real_T Integrator_IC_e;              // Expression: 0
                                          //  Referenced by: '<S99>/Integrator'

  real_T Integrator_WrappedStateUpperValue;// Expression: 360*Cps
                                              //  Referenced by: '<S99>/Integrator'

  real_T Integrator_WrappedStateLowerValue;// Expression: 0
                                              //  Referenced by: '<S99>/Integrator'

  real_T RPMtodegs_Gain;               // Expression: 180/30
                                          //  Referenced by: '<S99>/RPM to deg//s'

  real_T Reset_Value_o3;               // Expression: 1
                                          //  Referenced by: '<S118>/Reset'

  uint32_T EngTrqTable_maxIndex[2];  // Computed Parameter: EngTrqTable_maxIndex
                                        //  Referenced by: '<S112>/EngTrq Table'

  boolean_T UnitDelay2_InitialCondition;
                              // Computed Parameter: UnitDelay2_InitialCondition
                                 //  Referenced by: '<S3>/Unit Delay2'

  boolean_T Memory_InitialCondition_b; // Expression: ClutchLocked
                                          //  Referenced by: '<S47>/Memory'

  boolean_T Memory_InitialCondition_h;
                                // Computed Parameter: Memory_InitialCondition_h
                                   //  Referenced by: '<S44>/Memory'

  boolean_T CombinatorialLogic_table[8];
                                 // Computed Parameter: CombinatorialLogic_table
                                    //  Referenced by: '<S47>/Combinatorial  Logic'

  P_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T TwoDofDynamic;// '<S125>/TwoDofDynamic' 
};

// Real-time Model Data Structure
struct tag_RTM_CNHTC_VEHICLE_MODEL_PureSL_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_CNHTC_VEHICLE_MODEL_PureSL_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[21];
  real_T odeF[3][21];
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
extern struct_1Bydkh1pAHvKL6MKYnygkF rtP_Chas;// Variable: Chas
                                                 //  Referenced by:
                                                 //    '<S2>/Constant'
                                                 //    '<S3>/Constant2'
                                                 //    '<S3>/1-D Lookup Table'
                                                 //    '<S126>/Gain1'
                                                 //    '<S127>/Constant2'
                                                 //    '<S127>/Gain4'
                                                 //    '<S129>/Constant'
                                                 //    '<S129>/Constant3'
                                                 //    '<S129>/Gain'
                                                 //    '<S129>/Gain1'
                                                 //    '<S6>/Gain'
                                                 //    '<S9>/Constant12'
                                                 //    '<S12>/Constant'
                                                 //    '<S14>/Input Clutch Inertia'
                                                 //    '<S15>/Gear2Ratios'
                                                 //    '<S15>/Gear2damping'
                                                 //    '<S15>/Gear2inertias'
                                                 //    '<S63>/Ndiff2'
                                                 //    '<S67>/Gain'
                                                 //    '<S30>/Eta 1D'
                                                 //    '<S48>/Constant'
                                                 //    '<S57>/Eta 1D'
                                                 //    '<S49>/Constant'
                                                 //    '<S70>/Gain1'

extern struct_xuvldbp4qY393voN3kPmeB rtP_EBC;// Variable: EBC
                                                //  Referenced by: '<S1>/Brake_System'

extern struct_FRG4WHA92HxYEB6reTTd6E rtP_VEH;// Variable: VEH
                                                //  Referenced by:
                                                //    '<S1>/Constant'
                                                //    '<S2>/Constant1'
                                                //    '<S2>/Constant2'
                                                //    '<S2>/Constant3'
                                                //    '<S2>/Constant4'
                                                //    '<S127>/Mass_kg2'
                                                //    '<S130>/Cf'
                                                //    '<S130>/Cr'
                                                //    '<S130>/Lf'
                                                //    '<S130>/Lf_2'
                                                //    '<S130>/Lr'
                                                //    '<S130>/Lr_2'
                                                //    '<S130>/inv_Iz'
                                                //    '<S35>/Memory'
                                                //    '<S35>/Memory1'
                                                //    '<S35>/Memory3'

extern real_T rtP_DnShiftSpdTa[99];    // Variable: DnShiftSpdTa
                                          //  Referenced by: '<S3>/TCU'

extern real_T rtP_EngTorBp_ne[15];     // Variable: EngTorBp_ne
                                          //  Referenced by: '<S3>/Engine_ECU'

extern real_T rtP_EngTorBp_ped[16];    // Variable: EngTorBp_ped
                                          //  Referenced by: '<S3>/Engine_ECU'

extern real_T rtP_EngTorTable[240];    // Variable: EngTorTable
                                          //  Referenced by: '<S3>/Engine_ECU'

extern real_T rtP_ShiftDnTa_Bp_GearPos[11];// Variable: ShiftDnTa_Bp_GearPos
                                              //  Referenced by: '<S3>/TCU'

extern real_T rtP_ShiftDnTa_Bp_PedPos[9];// Variable: ShiftDnTa_Bp_PedPos
                                            //  Referenced by: '<S3>/TCU'

extern real_T rtP_ShiftUpTa_Bp_GearPos[11];// Variable: ShiftUpTa_Bp_GearPos
                                              //  Referenced by: '<S3>/TCU'

extern real_T rtP_ShiftUpTa_Bp_PedPos[10];// Variable: ShiftUpTa_Bp_PedPos
                                             //  Referenced by: '<S3>/TCU'

extern real_T rtP_UpshiftSpdTa[110];   // Variable: UpshiftSpdTa
                                          //  Referenced by: '<S3>/TCU'

extern real_T rtP_dt_ECU;              // Variable: dt_ECU
                                          //  Referenced by: '<S3>/Engine_ECU'

extern real_T rtP_dt_bra;              // Variable: dt_bra
                                          //  Referenced by: '<S1>/Brake_System'

extern real_T rtP_simTs;               // Variable: simTs
                                          //  Referenced by:
                                          //    '<S131>/Gain1'
                                          //    '<S132>/Gain1'


//
//  Exported Global Signals
//
//  Note: Exported global signals are block signals with an exported global
//  storage class designation.  Code generation will declare the memory for
//  these signals and export their symbols.
//

#ifdef __cplusplus

extern "C" {

#endif

  extern real_T pedalPos_pct;          // '<Root>/pedalPos_pct'
  extern real_T XBR1_ExternalAccele;   // '<Root>/XBR1_ExternalAccele'
  extern real_T SteerWhAngle_rad;      // '<Root>/SteerWhAngle_rad'
  extern real_T Grade_deg;             // '<Root>/Grade_deg'
  extern real_T XBR1_Ctrl_Mode;        // '<Root>/XBR1_Ctrl_Mode'
  extern real_T throttle_pct;          // '<S1>/Gain'
  extern real_T Velong_kph;            // '<Root>/Gain3'
  extern real_T Yaw_deg;               // '<S126>/Gain'
  extern real_T YawRate_dps;           // '<S126>/Gain2'
  extern real_T Velate_kph;            // '<Root>/Gain1'
  extern real_T ax_mps2;               // '<S2>/Divide'
  extern real_T Vx_kph;                // '<Root>/Gain2'
  extern real_T Vy_kph;                // '<Root>/Gain4'
  extern real_T X;                     // '<Root>/Integrator'
  extern real_T Y;                     // '<Root>/Integrator1'

#ifdef __cplusplus

}
#endif

// Class declaration for model CNHTC_VEHICLE_MODEL_PureSL
class CNHTC_VEHICLE_MODEL_PureSLModelClass {
  // public data and function members
 public:
  // Tunable parameters
  static P_CNHTC_VEHICLE_MODEL_PureSL_T CNHTC_VEHICLE_MODEL_PureSL_P;

  // External outputs
  ExtY_CNHTC_VEHICLE_MODEL_PureSL_T CNHTC_VEHICLE_MODEL_PureSL_Y;

  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  CNHTC_VEHICLE_MODEL_PureSLModelClass();

  // Destructor
  ~CNHTC_VEHICLE_MODEL_PureSLModelClass();

  // Real-Time Model get method
  RT_MODEL_CNHTC_VEHICLE_MODEL_PureSL_T * getRTM();

  // private data and function members
 private:
  // Block signals
  B_CNHTC_VEHICLE_MODEL_PureSL_T CNHTC_VEHICLE_MODEL_PureSL_B;

  // Block states
  DW_CNHTC_VEHICLE_MODEL_PureSL_T CNHTC_VEHICLE_MODEL_PureSL_DW;
  X_CNHTC_VEHICLE_MODEL_PureSL_T CNHTC_VEHICLE_MODEL_PureSL_X;// Block continuous states 
  PeriodicIndX_CNHTC_VEHICLE_MODEL_PureSL_T
    CNHTC_VEHICLE_MODEL_PureSL_PeriodicIndX;// Block periodic continuous states
  PeriodicRngX_CNHTC_VEHICLE_MODEL_PureSL_T
    CNHTC_VEHICLE_MODEL_PureSL_PeriodicRngX;
  PrevZCX_CNHTC_VEHICLE_MODEL_PureSL_T CNHTC_VEHICLE_MODEL_PureSL_PrevZCX;// Triggered events 

  // Real-Time Model
  RT_MODEL_CNHTC_VEHICLE_MODEL_PureSL_T CNHTC_VEHICLE_MODEL_PureSL_M;

  // private member function(s) for subsystem '<S125>/TwoDofDynamic'
  void CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_Init
    (DW_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localDW,
     P_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localP);
  void CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic_Update
    (B_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localB,
     DW_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localDW);
  void CNHTC_VEHICLE_MODEL_PureSL_TwoDofDynamic(real_T rtu_WhlAngF_rad, real_T
    rtu_vx_mps, real_T rtu_vehicle_mass_kg, real_T *rty_omega_radps, real_T
    *rty_vy_mps, B_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localB,
    DW_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localDW,
    P_TwoDofDynamic_CNHTC_VEHICLE_MODEL_PureSL_T *localP);

  // Continuous states update member function
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void CNHTC_VEHICLE_MODEL_PureSL_derivatives();

  // model instance variable for '<S1>/Brake_System'
  BrakingModelClass Brake_SystemMDLOBJ1;

  // model instance variable for '<S3>/Engine_ECU'
  Engine_ECUModelClass Engine_ECUMDLOBJ2;

  // model instance variable for '<S3>/TCU'
  TCUModelClass TCUMDLOBJ3;

  // model instance variable for '<S1>/SteerWhlMdl'
  SteerWhlMdlModelClass SteerWhlMdlMDLOBJ4;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<S19>/Abs1' : Unused code path elimination
//  Block '<S19>/Gain' : Unused code path elimination
//  Block '<S19>/Product' : Unused code path elimination
//  Block '<S19>/Product1' : Unused code path elimination
//  Block '<S19>/Product2' : Unused code path elimination
//  Block '<S19>/Saturation' : Unused code path elimination
//  Block '<S19>/Saturation1' : Unused code path elimination
//  Block '<S19>/Saturation2' : Unused code path elimination
//  Block '<S19>/Sum of Elements' : Unused code path elimination
//  Block '<S19>/Sum of Elements1' : Unused code path elimination
//  Block '<S21>/Abs' : Unused code path elimination
//  Block '<S22>/Compare' : Unused code path elimination
//  Block '<S22>/Constant' : Unused code path elimination
//  Block '<S23>/Compare' : Unused code path elimination
//  Block '<S23>/Constant' : Unused code path elimination
//  Block '<S21>/Fcn' : Unused code path elimination
//  Block '<S21>/Logical Operator' : Unused code path elimination
//  Block '<S21>/Switch' : Unused code path elimination
//  Block '<S11>/Product' : Unused code path elimination
//  Block '<S11>/Product1' : Unused code path elimination
//  Block '<S5>/FixPt Data Type Duplicate1' : Unused code path elimination
//  Block '<S69>/Abs' : Unused code path elimination
//  Block '<S69>/Constant6' : Unused code path elimination
//  Block '<S69>/Constant7' : Unused code path elimination
//  Block '<S69>/Constant8' : Unused code path elimination
//  Block '<S69>/Product1' : Unused code path elimination
//  Block '<S69>/Product4' : Unused code path elimination
//  Block '<S69>/Sum of Elements2' : Unused code path elimination
//  Block '<S69>/Unary Minus' : Unused code path elimination
//  Block '<S70>/Constant1' : Unused code path elimination
//  Block '<S70>/Constant4' : Unused code path elimination
//  Block '<S70>/Constant5' : Unused code path elimination
//  Block '<S70>/Product5' : Unused code path elimination
//  Block '<S70>/Sum of Elements1' : Unused code path elimination
//  Block '<S68>/Sum of Elements3' : Unused code path elimination
//  Block '<S68>/Transferred Power' : Unused code path elimination
//  Block '<S68>/Unary Minus' : Unused code path elimination
//  Block '<S75>/Product2' : Unused code path elimination
//  Block '<S75>/Subtract' : Unused code path elimination
//  Block '<S76>/Product2' : Unused code path elimination
//  Block '<S76>/Subtract' : Unused code path elimination
//  Block '<S77>/Product2' : Unused code path elimination
//  Block '<S77>/Subtract' : Unused code path elimination
//  Block '<S6>/Scope' : Unused code path elimination
//  Block '<S83>/Constant8' : Unused code path elimination
//  Block '<S83>/Product1' : Unused code path elimination
//  Block '<S83>/Product4' : Unused code path elimination
//  Block '<S83>/Unary Minus' : Unused code path elimination
//  Block '<S82>/Product' : Unused code path elimination
//  Block '<S82>/Transferred Power' : Unused code path elimination
//  Block '<S82>/Unary Minus1' : Unused code path elimination
//  Block '<S80>/Signal Copy' : Unused code path elimination
//  Block '<S80>/Signal Copy1' : Unused code path elimination
//  Block '<S80>/Unary Minus1' : Unused code path elimination
//  Block '<S91>/Constant8' : Unused code path elimination
//  Block '<S91>/Product1' : Unused code path elimination
//  Block '<S91>/Product4' : Unused code path elimination
//  Block '<S91>/Unary Minus' : Unused code path elimination
//  Block '<S90>/Product' : Unused code path elimination
//  Block '<S90>/Transferred Power' : Unused code path elimination
//  Block '<S90>/Unary Minus1' : Unused code path elimination
//  Block '<S88>/Signal Copy' : Unused code path elimination
//  Block '<S88>/Signal Copy1' : Unused code path elimination
//  Block '<S88>/Unary Minus1' : Unused code path elimination
//  Block '<S96>/Constant' : Unused code path elimination
//  Block '<S96>/Divide' : Unused code path elimination
//  Block '<S96>/MinMax' : Unused code path elimination
//  Block '<S107>/Compare' : Unused code path elimination
//  Block '<S107>/Constant' : Unused code path elimination
//  Block '<S108>/Compare' : Unused code path elimination
//  Block '<S108>/Constant' : Unused code path elimination
//  Block '<S105>/Constant' : Unused code path elimination
//  Block '<S105>/Fcn' : Unused code path elimination
//  Block '<S105>/Logical Operator' : Unused code path elimination
//  Block '<S105>/Product' : Unused code path elimination
//  Block '<S105>/Switch' : Unused code path elimination
//  Block '<S105>/Switch1' : Unused code path elimination
//  Block '<S105>/Unary Minus' : Unused code path elimination
//  Block '<S109>/Compare' : Unused code path elimination
//  Block '<S109>/Constant' : Unused code path elimination
//  Block '<S110>/Compare' : Unused code path elimination
//  Block '<S110>/Constant' : Unused code path elimination
//  Block '<S106>/Constant' : Unused code path elimination
//  Block '<S106>/Fcn' : Unused code path elimination
//  Block '<S106>/Logical Operator' : Unused code path elimination
//  Block '<S106>/Product' : Unused code path elimination
//  Block '<S106>/Switch' : Unused code path elimination
//  Block '<S106>/Switch1' : Unused code path elimination
//  Block '<S106>/Unary Minus' : Unused code path elimination
//  Block '<S97>/Air Flow Table' : Unused code path elimination
//  Block '<S100>/AFR calc1' : Unused code path elimination
//  Block '<S100>/Constant' : Unused code path elimination
//  Block '<S100>/Gain' : Unused code path elimination
//  Block '<S101>/Calc Load' : Unused code path elimination
//  Block '<S101>/Cylinders per sec' : Unused code path elimination
//  Block '<S101>/Engine Displacement' : Unused code path elimination
//  Block '<S101>/Ideal Gas Constant' : Unused code path elimination
//  Block '<S101>/Nominal Airflow At Current Speed and STP' : Unused code path elimination
//  Block '<S101>/Nominal Cylinder Air Mass g//cyl' : Unused code path elimination
//  Block '<S101>/Saturation3' : Unused code path elimination
//  Block '<S101>/Standard Air Temperature' : Unused code path elimination
//  Block '<S101>/Standard Pressure Sea Level' : Unused code path elimination
//  Block '<S101>/cyls per cycle' : Unused code path elimination
//  Block '<S101>/cyls per cycle ' : Unused code path elimination
//  Block '<S101>/rev per cycle' : Unused code path elimination
//  Block '<S101>/sec per min' : Unused code path elimination
//  Block '<S112>/Bsfc Table' : Unused code path elimination
//  Block '<S112>/EoCO2 Table' : Unused code path elimination
//  Block '<S112>/EoCo Table' : Unused code path elimination
//  Block '<S112>/EoHc Table' : Unused code path elimination
//  Block '<S112>/EoNOx Table' : Unused code path elimination
//  Block '<S112>/EoPm Table' : Unused code path elimination
//  Block '<S112>/ExhManGasTemp Table' : Unused code path elimination
//  Block '<S112>/FuelMassFlw Table' : Unused code path elimination
//  Block '<S103>/LHV' : Unused code path elimination
//  Block '<S114>/Constant' : Unused code path elimination
//  Block '<S103>/Product' : Unused code path elimination
//  Block '<S103>/Subtract' : Unused code path elimination
//  Block '<S103>/rpm to rad//s' : Unused code path elimination
//  Block '<S104>/Constant' : Unused code path elimination
//  Block '<S104>/Max' : Unused code path elimination
//  Block '<S120>/Constant8' : Unused code path elimination
//  Block '<S120>/Product1' : Unused code path elimination
//  Block '<S120>/Product4' : Unused code path elimination
//  Block '<S120>/Unary Minus' : Unused code path elimination
//  Block '<S119>/Product' : Unused code path elimination
//  Block '<S119>/Transferred Power' : Unused code path elimination
//  Block '<S119>/Unary Minus1' : Unused code path elimination
//  Block '<S117>/Signal Copy' : Unused code path elimination
//  Block '<S117>/Signal Copy1' : Unused code path elimination
//  Block '<S117>/Unary Minus1' : Unused code path elimination
//  Block '<S130>/Scope' : Unused code path elimination
//  Block '<S130>/Scope1' : Unused code path elimination
//  Block '<S130>/Scope2' : Unused code path elimination
//  Block '<S127>/Scope' : Unused code path elimination
//  Block '<S127>/Scope1' : Unused code path elimination
//  Block '<S126>/Signal Conversion1' : Eliminate redundant signal conversion block
//  Block '<S126>/Signal Conversion2' : Eliminate redundant signal conversion block
//  Block '<S126>/Signal Conversion3' : Eliminate redundant signal conversion block


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
//  '<Root>' : 'CNHTC_VEHICLE_MODEL_PureSL'
//  '<S1>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem'
//  '<S2>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body'
//  '<S3>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine'
//  '<S4>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission'
//  '<S5>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Electronic Throttle Actuator Dynamics1'
//  '<S6>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive'
//  '<S7>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine'
//  '<S8>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft'
//  '<S9>'   : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Subsystem1'
//  '<S10>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission'
//  '<S11>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation'
//  '<S12>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Locked'
//  '<S13>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response'
//  '<S14>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked'
//  '<S15>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/gear2props'
//  '<S16>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/omegain_o'
//  '<S17>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/omegain_o1'
//  '<S18>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/omegaout_o'
//  '<S19>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation/Mechanical Efficiency'
//  '<S20>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation/Power Accounting Bus Creator'
//  '<S21>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation/Mechanical Efficiency/div0protect - abs poly'
//  '<S22>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation/Mechanical Efficiency/div0protect - abs poly/Compare To Constant'
//  '<S23>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation/Mechanical Efficiency/div0protect - abs poly/Compare To Constant1'
//  '<S24>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation/Power Accounting Bus Creator/PwrNotTrnsfrd Input'
//  '<S25>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation/Power Accounting Bus Creator/PwrStored Input'
//  '<S26>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Bus Creation/Power Accounting Bus Creator/PwrTrnsfrd Input'
//  '<S27>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Locked/AMT Eta'
//  '<S28>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Locked/Apply Efficiency'
//  '<S29>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Locked/Apply Efficiency1'
//  '<S30>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Locked/AMT Eta/Eta 1D'
//  '<S31>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Cont LPF Dyn'
//  '<S32>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Friction Model'
//  '<S33>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing'
//  '<S34>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up Friction Mode Logic'
//  '<S35>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Gear Selection'
//  '<S36>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Syncronizer Timing'
//  '<S37>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Gear Selection/Compare To Zero3'
//  '<S38>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Syncronizer Timing/Internal Control Clutch Engagement'
//  '<S39>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Syncronizer Timing/Shift Interlock'
//  '<S40>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Syncronizer Timing/Synch Timing'
//  '<S41>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Syncronizer Timing/Internal Control Clutch Engagement/Compare To Zero1'
//  '<S42>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Syncronizer Timing/Internal Control Clutch Engagement/Compare To Zero2'
//  '<S43>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Syncronizer Timing/Synch Timing/Compare To Zero1'
//  '<S44>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Gear, Clutch and Syncro Timing/Syncronizer Timing/Synch Timing/LatchSwitchCont'
//  '<S45>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up Friction Mode Logic/Break Apart Detection'
//  '<S46>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up Friction Mode Logic/Lockup Detection'
//  '<S47>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up Friction Mode Logic/Lockup FSM'
//  '<S48>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up Friction Mode Logic/Requisite Friction'
//  '<S49>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up Friction Mode Logic/Lockup Detection/Friction Calc'
//  '<S50>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Simple Clutch Response/Lock-up Friction Mode Logic/Lockup Detection/Required Friction for Lockup'
//  '<S51>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/AMT Eta'
//  '<S52>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/Apply Efficiency'
//  '<S53>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/Apply Efficiency1'
//  '<S54>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/Clutch Torque'
//  '<S55>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/Losses'
//  '<S56>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/div0protect - abs poly1'
//  '<S57>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/AMT Eta/Eta 1D'
//  '<S58>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/div0protect - abs poly1/Compare To Constant'
//  '<S59>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Automated Manual Transmission/Automated Manual Transmission/Unlocked/div0protect - abs poly1/Compare To Constant1'
//  '<S60>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential'
//  '<S61>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1'
//  '<S62>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2'
//  '<S63>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential'
//  '<S64>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Bus Creation'
//  '<S65>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Efficiency'
//  '<S66>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Open Differential'
//  '<S67>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/y'
//  '<S68>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Bus Creation/Power'
//  '<S69>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Bus Creation/Power/Damping Power'
//  '<S70>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Bus Creation/Power/Kinetic Power'
//  '<S71>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Bus Creation/Power/Power Accounting Bus Creator'
//  '<S72>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Bus Creation/Power/Power Accounting Bus Creator/PwrNotTrnsfrd Input'
//  '<S73>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Bus Creation/Power/Power Accounting Bus Creator/PwrStored Input'
//  '<S74>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Bus Creation/Power/Power Accounting Bus Creator/PwrTrnsfrd Input'
//  '<S75>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Efficiency/Axle 1 Efficiency'
//  '<S76>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Efficiency/Axle 2 Efficiency'
//  '<S77>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Efficiency/Drive Efficiency'
//  '<S78>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Efficiency/Eta'
//  '<S79>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Open Differential/Open Differential/Efficiency/Eta/Constant Eta'
//  '<S80>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1/Torsional Compliance Linear'
//  '<S81>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1/Torsional Compliance Linear/Cont LPF IC Dyn'
//  '<S82>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1/Torsional Compliance Linear/Power'
//  '<S83>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1/Torsional Compliance Linear/Power/Damping Power'
//  '<S84>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1/Torsional Compliance Linear/Power/Power Accounting Bus Creator'
//  '<S85>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrNotTrnsfrd Input'
//  '<S86>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrStored Input'
//  '<S87>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance1/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrTrnsfrd Input'
//  '<S88>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2/Torsional Compliance Linear'
//  '<S89>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2/Torsional Compliance Linear/Cont LPF IC Dyn'
//  '<S90>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2/Torsional Compliance Linear/Power'
//  '<S91>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2/Torsional Compliance Linear/Power/Damping Power'
//  '<S92>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2/Torsional Compliance Linear/Power/Power Accounting Bus Creator'
//  '<S93>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrNotTrnsfrd Input'
//  '<S94>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrStored Input'
//  '<S95>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Front Wheel Drive/Torsional Compliance2/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrTrnsfrd Input'
//  '<S96>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Afr Calculation'
//  '<S97>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Air Flow'
//  '<S98>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/CI Engine Fuel Mass without Boost Lag'
//  '<S99>'  : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Engine Crank Angle Calculation'
//  '<S100>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Fuel Volume Flow'
//  '<S101>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Load Calculation'
//  '<S102>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Mapped Core Engine'
//  '<S103>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Mapped Engine Power Info'
//  '<S104>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Max Commanded Fuel-Torque'
//  '<S105>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Afr Calculation/div0protect - poly1'
//  '<S106>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Afr Calculation/div0protect - poly2'
//  '<S107>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Afr Calculation/div0protect - poly1/Compare To Constant'
//  '<S108>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Afr Calculation/div0protect - poly1/Compare To Constant1'
//  '<S109>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Afr Calculation/div0protect - poly2/Compare To Constant'
//  '<S110>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Afr Calculation/div0protect - poly2/Compare To Constant1'
//  '<S111>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Mapped Core Engine/Without Temperature Input and with Trq'
//  '<S112>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Mapped Core Engine/Without Temperature Input and with Trq/Mapped Core Engine'
//  '<S113>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Mapped Engine Power Info/Power Accounting Bus Creator'
//  '<S114>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Mapped Engine Power Info/Power Accounting Bus Creator/No PwrStored Input'
//  '<S115>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Mapped Engine Power Info/Power Accounting Bus Creator/PwrNotTrnsfrd Input'
//  '<S116>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Mapped CI Engine/Mapped Engine Power Info/Power Accounting Bus Creator/PwrTrnsfrd Input'
//  '<S117>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft/Torsional Compliance Linear'
//  '<S118>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft/Torsional Compliance Linear/Cont LPF IC Dyn'
//  '<S119>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft/Torsional Compliance Linear/Power'
//  '<S120>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft/Torsional Compliance Linear/Power/Damping Power'
//  '<S121>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft/Torsional Compliance Linear/Power/Power Accounting Bus Creator'
//  '<S122>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrNotTrnsfrd Input'
//  '<S123>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrStored Input'
//  '<S124>' : 'CNHTC_VEHICLE_MODEL_PureSL/Subsystem/DriveLine/Prop Shaft/Torsional Compliance Linear/Power/Power Accounting Bus Creator/PwrTrnsfrd Input'
//  '<S125>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/LateralDynamics'
//  '<S126>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/Output'
//  '<S127>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/Rolling friction'
//  '<S128>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/Subsystem'
//  '<S129>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/WheelForceCal'
//  '<S130>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/LateralDynamics/TwoDofDynamic'
//  '<S131>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/LateralDynamics/TwoDofDynamic/integration1'
//  '<S132>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/LateralDynamics/TwoDofDynamic/integration2'
//  '<S133>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/Output/Compare To Constant'
//  '<S134>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/Rolling friction/Compare To Constant'
//  '<S135>' : 'CNHTC_VEHICLE_MODEL_PureSL/Vehicle Body/Subsystem/Compare To Constant'

#endif                              // RTW_HEADER_CNHTC_VEHICLE_MODEL_PureSL_h_

//
// File trailer for generated code.
//
// [EOF]
//
