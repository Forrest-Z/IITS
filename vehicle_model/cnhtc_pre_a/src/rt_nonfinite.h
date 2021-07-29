//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: rt_nonfinite.h
//
// Code generated for Simulink model 'Braking'.
//
// Model version                  : 1.20
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:19 2020
//
#ifndef SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_RT_NONFINITE_H_
#define SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_RT_NONFINITE_H_
#include <stddef.h>

#include "rtwtypes.h"
#ifdef __cplusplus

extern "C" {
#endif
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
extern void rt_InitInfAndNaN(size_t realSize);
extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;
typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;
typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;
#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // SIMULATION_VEHICLE_MODEL_CNHTC_PRE_A_V1P1_RT_NONFINITE_H_
//
// File trailer for generated code.
//
// [EOF]
//
