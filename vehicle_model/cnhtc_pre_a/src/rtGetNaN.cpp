//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: rtGetNaN.cpp
//
// Code generated for Simulink model 'Braking'.
//
// Model version                  : 1.20
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:19 2020
//
//
//  Abstract:
//       Function to initialize non-finite, NaN
#include "rtGetNaN.h"
#define NumBitsPerChar 8U

extern "C" {
//
// Initialize rtNaN needed by the generated code.
// NaN is initialized as non-signaling. Assumes IEEE.
//
real_T rtGetNaN(void) {
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;
    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }
  return nan;
}
//
// Initialize rtNaNF needed by the generated code.
// NaN is initialized as non-signaling. Assumes IEEE.
//
real32_T rtGetNaNF(void) {
  IEEESingle nanF = {{0}};
  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}
}
//

// File trailer for generated code.
//
// [EOF]
//
