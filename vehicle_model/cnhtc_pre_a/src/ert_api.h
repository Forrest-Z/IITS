#ifndef ERT_INTERFACE_H
#define ERT_INTERFACE_H

#include "rtwtypes.h"

typedef struct _ert_input_data {
  real_T pedalPos_pct;        /* '<Root>/pedalPos_pct' */
  real_T XBR1_ExternalAccele; /* '<Root>/XBR1_ExternalAccele' */
  int8_T XBR1_Ctrl_Mode;      /* '<Root>/XBR1_Ctrl_Mode' */
  real_T SteerWhAngle_rad;    /* '<Root>/SteerWhAngle_rad' */
} ert_input_data;

typedef ert_input_data ert_simulink_input_data;

typedef struct _ert_simulink_output_data {
  real_T _GearPos;        /* '<S1>/Unit Delay1‘,档位 */
  real_T _EngSpd_rpm;     /* '<S1>/DriveLine' ，发动机转速*/
  real_T _TransTorOut_Nm; /* '<S1>/DriveLine' 变速箱输出轴扭矩*/
  real_T _EngTrq_Nm;      /* '<S1>/DriveLine' ， 发动机扭矩*/
  real_T
      _engine_torque_loss_percent; /* '<S1>/DriveLine'， 发动机损失扭矩百分比*/
  real_T _engine_torque_percent; /* '<S1>/DriveLine' ，  发动机扭矩百分比*/
  real_T _bwdWhlPre_Mpa[4]; /* '<Root>/Brake_System' 牵引车后驱动轴制动压力*/
  real_T _fwdWhlPre_Mpa[2]; /* '<Root>/Brake_System' 牵引车前轴制动压力*/
  real_T _TrailWhlPre_Mpa[6];  /* '<Root>/Brake_System' 挂车自动压力*/
  real_T _SteerWhAngle_DZ_deg; /* '<Root>/SteerWhlMdl' ，方向盘转角*/
  real_T _throttle_pct;        /* '<Root>/Gain' 油门开度百分比*/
  boolean_T _shift_in_process; /* '<S1>/NOT' ，挂当中状态*/
  boolean_T _foundation_brake_in_use; /* '<Root>/Data Type
                                         Conversion'，制动系统状态 */
  real_T fuel_consumption;
} ert_simulink_output_data;

// remove guache
typedef union _ert_trucksim_input_data {
  struct {
    real_T _TransTorOut_Nm;
    real_T _bwdWhlPre_Mpa[4];
    real_T _fwdWhlPre_Mpa[2];
    real_T _TrailWhlPre_Mpa[6];  // '<Root>/TrailWhlPre_Mpa'
    real_T _SteerWhAngle_DZ_deg;
  } simulink;

  struct _trucksim {
    real_T IMP_M_OUT_TR;
    real_T IMP_PBK_L2;
    real_T IMP_PBK_R2;
    real_T IMP_PBK_L3;
    real_T IMP_PBK_R3;
    real_T IMP_PBK_L1;
    real_T IMP_PBK_R1;
    real_T IMP_PBK_L4;
    real_T IMP_PBK_R4;
    real_T IMP_PBK_L5;
    real_T IMP_PBK_R5;
    real_T IMP_PBK_L6;
    real_T IMP_PBK_R6;
    real_T IMP_STEER_SW;
  } trucksim;

  // import data
  real_T import_data[sizeof(struct _trucksim)];
} ert_trucksim_input_data;

typedef struct _ert_trucksim_output_data {
  real_T AVz;
  real_T Vx;
  real_T Vy;
  real_T Vz;
  real_T Ax;
  real_T Ay;
  real_T Xo;
  real_T Yo;
  real_T Steer_L1;
  real_T Steer_R1;
  real_T Yaw;
  real_T Pitch;
  real_T Roll;
  real_T Station;
  real_T T_Stamp;
  real_T Zo;
  real_T Mass;
} ert_trucksim_output_data;

typedef struct _ert_output_data {
  ert_simulink_output_data simulink;
  ert_trucksim_output_data trucksim;
  uint32_T frame_id;
} ert_output_data;

void ert_init(int use_trucksim, const char* sim_file_path);
ert_output_data ert_run_one_step(ert_input_data input);
void ert_terminate();

// #ifdef __cplusplus
// } // extern "C"
// #endif

#endif  //  ERT_INTERFACE_H
