//
// Copyright 2020 Inceptio Technology. All Rights Reserved.
//
// File: automldiffopen_m841FDlI.cpp
//
// Code generated for Simulink model 'CNHTC_VEHICLE_MODEL_code'.
//
// Model version                  : 1.71
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Fri Oct  9 15:46:56 2020
//
#include "automldiffopen_m841FDlI.h"

#include "rtwtypes.h"

// Function for MATLAB Function: '<S62>/Open Differential'
void automldiffopen_m841FDlI(const real_T u[3], real_T bw1, real_T bd,
                             real_T bw2, real_T Ndiff, real_T shaftSwitch,
                             real_T Jd, real_T Jw1, real_T Jw2,
                             const real_T x[2], real_T y[3], real_T xdot[2]) {
  int32_T diffDir;
  real_T term1;
  real_T term2;
  real_T invJ[4];
  real_T diffDir_0[6];
  real_T invJ_0[6];
  real_T bw1_0[4];
  real_T invJ_1[4];
  real_T invJ_2[2];
  real_T invJ_3[2];
  real_T diffDir_1[6];
  real_T diffDir_2[3];
  real_T tmp[3];
  int32_T i;
  int32_T i_0;
  if (shaftSwitch != 0.0) {
    diffDir = -1;
  } else {
    diffDir = 1;
  }
  term1 = Ndiff * Ndiff * Jd;
  term2 = (4.0 * Jw1 * Jw2 + term1 * Jw1) + Jw2 * term1;
  invJ[0] = (Jw2 * 4.0 + term1) / term2;
  invJ[2] = -term1 / term2;
  invJ[1] = -term1 / term2;
  invJ[3] = (Jw1 * 4.0 + term1) / term2;
  diffDir_0[0] = static_cast<real_T>(diffDir) / 2.0 * Ndiff;
  diffDir_0[2] = -1.0;
  diffDir_0[4] = 0.0;
  diffDir_0[1] = static_cast<real_T>(diffDir) / 2.0 * Ndiff;
  diffDir_0[3] = 0.0;
  diffDir_0[5] = -1.0;
  bw1_0[0] = -(Ndiff * bd + bw1);
  bw1_0[2] = -(Ndiff * bd);
  bw1_0[1] = -(Ndiff * bd);
  bw1_0[3] = -(Ndiff * bd + bw2);
  diffDir_1[0] = static_cast<real_T>(diffDir) / 2.0 * Ndiff;
  diffDir_1[3] = static_cast<real_T>(diffDir) / 2.0 * Ndiff;
  for (diffDir = 0; diffDir < 2; diffDir++) {
    for (i = 0; i < 3; i++) {
      invJ_0[diffDir + (i << 1)] = 0.0;
      for (i_0 = 0; i_0 < 2; i_0++) {
        term1 = invJ_0[(i << 1) + diffDir];
        term1 += invJ[(i_0 << 1) + diffDir] * diffDir_0[(i << 1) + i_0];
        invJ_0[diffDir + (i << 1)] = term1;
      }
    }
    for (i = 0; i < 2; i++) {
      invJ_1[diffDir + (i << 1)] = 0.0;
      for (i_0 = 0; i_0 < 2; i_0++) {
        term1 = invJ_1[(i << 1) + diffDir];
        term1 += invJ[(i_0 << 1) + diffDir] * bw1_0[(i << 1) + i_0];
        invJ_1[diffDir + (i << 1)] = term1;
      }
    }
    invJ_2[diffDir] = 0.0;
    for (i = 0; i < 3; i++) {
      term1 = invJ_2[diffDir];
      term1 += invJ_0[(i << 1) + diffDir] * u[i];
      invJ_2[diffDir] = term1;
    }
    invJ_3[diffDir] = 0.0;
    for (i = 0; i < 2; i++) {
      term1 = invJ_3[diffDir];
      term1 += invJ_1[(i << 1) + diffDir] * x[i];
      invJ_3[diffDir] = term1;
    }
    xdot[diffDir] = invJ_2[diffDir] + invJ_3[diffDir];
    diffDir_1[3 * diffDir + 1] = static_cast<real_T>(diffDir) + -1.0;
    diffDir_1[3 * diffDir + 2] = 0.0 - static_cast<real_T>(diffDir);
  }
  for (diffDir = 0; diffDir < 3; diffDir++) {
    diffDir_2[diffDir] = 0.0;
    for (i = 0; i < 2; i++) {
      term1 = diffDir_2[diffDir];
      term1 += diffDir_1[3 * i + diffDir] * x[i];
      diffDir_2[diffDir] = term1;
    }
    tmp[diffDir] = 0.0;
    for (i = 0; i < 3; i++) {
      term1 = tmp[diffDir];
      term1 += 0.0 * u[i];
      tmp[diffDir] = term1;
    }
    y[diffDir] = diffDir_2[diffDir] + tmp[diffDir];
  }
}
//

// File trailer for generated code.
//
// [EOF]
//
