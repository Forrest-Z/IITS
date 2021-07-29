/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'CNHTC_VEHICLE_MODEL_code'.
 *
 * Model version                  : 1.33
 * Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
 * C/C++ source code generated on : Wed Jun 17 10:13:38 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "ert_api.h"

#include <stddef.h>
#include <stdio.h> /* This ert_main.c example uses printf/fflush */

#include "cnhtc_pre_a_vehicle_model.h"  // Model's header file
#include "rtwtypes.h"
#include "vs_api.h"  // NOLINT
#include "zero_crossing_types.h"

static CNHTC_VEHICLE_MODEL_codeModelClass
    CNHTC_VEHICLE_MODEL_code_Obj;  // Instance of model class
#define FILENAME_MAX 4096
#define GRAVITY_ACC 9.81
// static HMODULE vsDLL = NULL;
static char pathDLL_[FILENAME_MAX];
static double vs_t_;
static int use_trucksim = true;

void ert_init(int _use_trucksim, const char* sim_file_path) {
  use_trucksim = _use_trucksim;
  int test_case_id = 1;  // 1=empty, 2=full load, 3=half load
  // if (use_trucksim == true)
  {
    if (vs_get_dll_path(sim_file_path, pathDLL_) == -1) {
      printf("[Trucksim model] vs solver failed at getting dll!");
      return;
    }

    auto vsDLL = vs_load_library(pathDLL_);

    if (vs_get_api(vsDLL, pathDLL_) == -1) {
      printf("[Trucksim model] vs solver failed at getting api!");
      return;
    }

    // use hpc license
    // vs_set_hpc_licensing_address("127.0.0.1");

    vs_t_ = vs_setdef_and_read(sim_file_path, NULL, NULL);
    vs_initialize(vs_t_, NULL, NULL);
    switch (test_case_id) {
      case '1': {
        if (vs_statement("M_PL", "0", 1)) {
          printf("Trucksim model initialize empty payload failed!");
        }
        break;
      }
      case '2': {
        if (vs_statement("M_PL", "31000", 1)) {
          printf("Trucksim model initialize full payload failed!");
        }
        break;
      }
      case '3': {
        if (vs_statement("M_PL", "15500", 1)) {
          printf("Trucksim model initialize half payload failed!");
        }
        break;
      }
      default: {
        printf("Trucksim model invalid test case id for payload!");
      }
    }
  }

  CNHTC_VEHICLE_MODEL_code_Obj.initialize();
}

ert_simulink_output_data simlink_one_step(ert_simulink_input_data input) {
  ert_simulink_output_data output;

  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(CNHTC_VEHICLE_MODEL_code_Obj.getRTM(), "Overrun");
    return output;
  }

  OverrunFlag = true;

  auto sim_input = &CNHTC_VEHICLE_MODEL_code_Obj.cnhtc_pre_a_vehicle_model_U;
  sim_input->pedalPos_pct = input.pedalPos_pct;
  sim_input->XBR1_ExternalAccele = input.XBR1_ExternalAccele;
  sim_input->XBR1_Ctrl_Mode = input.XBR1_Ctrl_Mode;
  sim_input->SteerWhAngle_rad = input.SteerWhAngle_rad;

  /* Step the model for base rate */
  CNHTC_VEHICLE_MODEL_code_Obj.step();

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */

  auto sim_output = &CNHTC_VEHICLE_MODEL_code_Obj.cnhtc_pre_a_vehicle_model_Y;

  output._GearPos = sim_output->GearPos;
  output._EngSpd_rpm = sim_output->EngSpd_rpm;
  output._TransTorOut_Nm = sim_output->TransTorOut_Nm;
  output._EngTrq_Nm = sim_output->EngTrq_Nm;
  output._engine_torque_loss_percent = sim_output->engine_torque_loss_percent;
  output._engine_torque_percent = sim_output->engine_torque_percent;
  output._SteerWhAngle_DZ_deg = sim_output->SteerWhAngle_DZ_deg;
  output._throttle_pct = sim_output->throttle_pct;
  output._shift_in_process = sim_output->shift_in_process;
  output._foundation_brake_in_use = sim_output->foundation_brake_in_use;
  output.fuel_consumption = sim_output->fuel_consumption;
  memcpy(&output._bwdWhlPre_Mpa[0], &(sim_output->bwdWhlPre_Mpa[0]),
         sizeof(sim_output->bwdWhlPre_Mpa));
  memcpy(&output._fwdWhlPre_Mpa[0], &(sim_output->fwdWhlPre_Mpa[0]),
         sizeof(sim_output->fwdWhlPre_Mpa));
  memcpy(&output._TrailWhlPre_Mpa[0], &(sim_output->TrailWhlPre_Mpa[0]),
         sizeof(sim_output->TrailWhlPre_Mpa));

  // printf("\r\n data size : %d", sizeof(sim_output->bwdWhlPre_Mpa));

  // printf("%lf %lf %lf %lf %lf %lf %lf\n", XBR1_ExternalAccele,
  // bwdWhlPre_Mpa[0],bwdWhlPre_Mpa[1],fwdWhlPre_Mpa[0],fwdWhlPre_Mpa[1],fwdWhlPre_Mpa[2],fwdWhlPre_Mpa[3]);
  // coeffic(output._bwdWhlPre_Mpa, 0.2);
  // coeffic(output._fwdWhlPre_Mpa, 0.2);

  return output;
}

ert_output_data ert_run_one_step(ert_input_data input) {
  ert_output_data output;

  output.simulink = simlink_one_step(input);

  if (use_trucksim == true) {
    // prepare for trucksim
    ert_trucksim_input_data trucksim_input;
    trucksim_input.simulink._TransTorOut_Nm = output.simulink._TransTorOut_Nm;
    trucksim_input.simulink._SteerWhAngle_DZ_deg =
        output.simulink._SteerWhAngle_DZ_deg;

    memcpy(&trucksim_input.simulink._bwdWhlPre_Mpa[0],
           &output.simulink._bwdWhlPre_Mpa[0],
           sizeof(output.simulink._bwdWhlPre_Mpa));

    memcpy(&trucksim_input.simulink._fwdWhlPre_Mpa[0],
           &output.simulink._fwdWhlPre_Mpa[0],
           sizeof(output.simulink._fwdWhlPre_Mpa));

    memcpy(&trucksim_input.simulink._TrailWhlPre_Mpa[0],
           &output.simulink._TrailWhlPre_Mpa[0],
           sizeof(output.simulink._TrailWhlPre_Mpa));

    real_T* imports_ = (real_T*)&trucksim_input.import_data[0];
    real_T* exports_ = (real_T*)&output.trucksim;

    // printf("\r\n import data size : %d",
    // sizeof(imports_)/sizeof(imports_[0]));

    vs_t_ += vs_get_tstep();
    vs_integrate_io(vs_t_, imports_, exports_);
    // printf("simstatus %d time %f", &sim_status, &vs_t_);
    // printf("\r\n%lf - %lf : %lf , %lf , %.8lf, %lf", vs_t_,
    // output.simulink._GearPos, input.pedalPos_pct, imports_[0] ,exports_[2],
    // exports_[4]);

    auto sim_input = &CNHTC_VEHICLE_MODEL_code_Obj.cnhtc_pre_a_vehicle_model_U;

    sim_input->Vx_kmph = output.trucksim.Vx;
    sim_input->ax_g = output.trucksim.Ax;
    sim_input->Mass_kg = output.trucksim.Mass;
    // sim_input->ax_mps2 = output.trucksim.Ax * GRAVITY_ACC;
  }

  return output;
}

#if 0
/*******************************************/
//         global variable 
/*******************************************/
real_T pedalPos_pct = 0;       /* '<Root>/pedalPos_pct' */
real_T XBR1_ExternalAccele = 0; /* '<Root>/XBR1_ExternalAccele' */
int8_T XBR1_Ctrl_Mode = 0;      /* '<Root>/XBR1_Ctrl_Mode' */
real_T SteerWhAngle_rad = 0;    /* '<Root>/SteerWhAngle_rad' */
real_T Vx_kmph = 0;             /* '<Root>/Vx_kmph' */
real_T ax_mps2 = 0;             /* '<Root>/ax_mps2' */

/*******************************************/
// truck sim

#define FILENAME_MAX 4096
#define GRAVITY_ACC 9.81

//static char simfile[FILENAME_MAX] = "/home/dawei/Desktop/fead_ws/src/vehicle_model/trucksim/trucksim_bridge/resource/simfile.sim";
// static int kStepsNum = 1;


static HMODULE vsDLL = NULL;
static char pathDLL_[FILENAME_MAX];
static double vs_t_;
static int use_trucksim = true;

/*******************************************/
//         
/*******************************************/

void ert_init(int _use_trucksim, const char* sim_file_path)
{
    use_trucksim = _use_trucksim;

    Vx_kmph = 0.0;
    ax_mps2 = 0.0;

    /* Initialize model */
    CNHTC_VEHICLE_MODEL_code_initialize();

    if (use_trucksim == true)
    {
        if (vs_get_dll_path(sim_file_path, pathDLL_) == -1) {
            printf("[Trucksim model] vs solver failed at getting dll!");
            return;
        }

        vsDLL = vs_load_library(pathDLL_);
        
        if (vs_get_api(vsDLL, pathDLL_) == -1) {
            printf("[Trucksim model] vs solver failed at getting api!");
            return;
        }

        vs_t_ = vs_setdef_and_read(sim_file_path, NULL, NULL);
        vs_initialize(vs_t_, NULL, NULL);
    }
}

void ert_terminate()
{
    /* Terminate model */
    CNHTC_VEHICLE_MODEL_code_terminate();
}

void coeffic(real_T *buf,real_T coff){
    int buff_len = 0;
    int index = 0;
    buff_len = sizeof(buf)/sizeof(real_T);
    
    for(;index<buff_len ; index++){
        buf[index] = buf[index]*coff;
    }
}

ert_simulink_output_data simlink_one_step(ert_simulink_input_data input)
{
    ert_simulink_output_data output;

    static boolean_T OverrunFlag = false;

    /* Disable interrupts here */

    /* Check for overrun */
    if (OverrunFlag)
    {
        rtmSetErrorStatus(CNHTC_VEHICLE_MODEL_code_M, "Overrun");
        return output;
    }

    OverrunFlag = true;

    /* Save FPU context here (if necessary) */
    /* Re-enable timer or interrupt here */
    /* Set model inputs here */
    pedalPos_pct        = input.pedalPos_pct;
    XBR1_ExternalAccele = input.XBR1_ExternalAccele;
    XBR1_Ctrl_Mode      = input.XBR1_Ctrl_Mode;
    SteerWhAngle_rad    = input.SteerWhAngle_rad;
    
    
    /* Step the model for base rate */
    CNHTC_VEHICLE_MODEL_code_step();

    /* Get model outputs here */

    /* Indicate task complete */
    OverrunFlag = false;

    /* Disable interrupts here */
    /* Restore FPU context here (if necessary) */
    /* Enable interrupts here */
    
    output._GearPos                     = GearPos;                                       
    output._EngSpd_rpm                  = EngSpd_rpm;                                 
    output._TransTorOut_Nm              = TransTorOut_Nm;                         
    output._EngTrq_Nm                   = EngTrq_Nm;                                   
    output._engine_torque_loss_percent  = engine_torque_loss_percent; 
    output._engine_torque_percent       = engine_torque_percent;           
    output._SteerWhAngle_DZ_deg         = SteerWhAngle_DZ_deg;
    output._throttle_pct                = throttle_pct;
    output._shift_in_process            = shift_in_process;
    output._foundation_brake_in_use     = foundation_brake_in_use;
    memcpy(&output._bwdWhlPre_Mpa[0], &bwdWhlPre_Mpa[0], sizeof(bwdWhlPre_Mpa));
    memcpy(&output._fwdWhlPre_Mpa[0], &fwdWhlPre_Mpa[0], sizeof(fwdWhlPre_Mpa));
    // printf("%lf %lf %lf %lf %lf %lf %lf\n", XBR1_ExternalAccele, bwdWhlPre_Mpa[0],bwdWhlPre_Mpa[1],fwdWhlPre_Mpa[0],fwdWhlPre_Mpa[1],fwdWhlPre_Mpa[2],fwdWhlPre_Mpa[3]);
    coeffic(output._bwdWhlPre_Mpa, 0.2);
    coeffic(output._fwdWhlPre_Mpa, 0.2);
    return output;
}

ert_output_data ert_run_one_step(ert_input_data input)
{
    ert_output_data output;
    
    output.simulink = simlink_one_step(input);

    if (use_trucksim == true) {
        // prepare for trucksim     
        ert_trucksim_input_data trucksim_input;
        trucksim_input.simulink._TransTorOut_Nm = output.simulink._TransTorOut_Nm;
        trucksim_input.simulink._SteerWhAngle_DZ_deg = output.simulink._SteerWhAngle_DZ_deg;
        
        memcpy(&trucksim_input.simulink._bwdWhlPre_Mpa[0], &output.simulink._bwdWhlPre_Mpa[0],
            sizeof(output.simulink._bwdWhlPre_Mpa));

        memcpy(&trucksim_input.simulink._fwdWhlPre_Mpa[0], &output.simulink._fwdWhlPre_Mpa[0],
            sizeof(output.simulink._fwdWhlPre_Mpa));

        real_T* imports_ = (real_T*)&trucksim_input.import_data[0];
        real_T* exports_ = (real_T*)&output.trucksim;

        vs_t_ += vs_get_tstep();
        vs_integrate_io(vs_t_, imports_, exports_);
        // printf("simstatus %d time %f", &sim_status, &vs_t_);
        //printf("\r\n%lf - %lf : %lf , %lf , %.8lf, %lf", vs_t_, output.simulink._GearPos, input.pedalPos_pct, imports_[0] ,exports_[2], exports_[4]);

        Vx_kmph = output.trucksim.Vx;
        ax_mps2 = output.trucksim.Ax * GRAVITY_ACC;
    }
    
    return output;
}

#endif
