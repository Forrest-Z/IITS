//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: rt_zcfcn.h
//
// Code generated for Simulink model 'CNHTC_VEHICLE_MODEL_code'.
//
// Model version                  : 1.71
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:56 2020
//
#ifndef SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_RT_ZCFCN_H_
#define SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_RT_ZCFCN_H_
#include "rtwtypes.h"
#include "solver_zc.h"
#include "zero_crossing_types.h"
#ifndef slZcHadEvent
#define slZcHadEvent(ev, zcsDir) (((ev) & (zcsDir)) != 0x00)
#endif
#ifndef slZcUnAliasEvents
#define slZcUnAliasEvents(evL, evR)               \
  ((((slZcHadEvent((evL), (SL_ZCS_EVENT_N2Z)) &&  \
      slZcHadEvent((evR), (SL_ZCS_EVENT_Z2P))) || \
     (slZcHadEvent((evL), (SL_ZCS_EVENT_P2Z)) &&  \
      slZcHadEvent((evR), (SL_ZCS_EVENT_Z2N))))   \
        ? (SL_ZCS_EVENT_NUL)                      \
        : (evR)))
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern ZCEventType rt_ZCFcn(ZCDirection zcDir, ZCSigState *prevZc,
                            real_T currValue);
#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_RT_ZCFCN_H_
//
// File trailer for generated code.
//
// [EOF]
//
