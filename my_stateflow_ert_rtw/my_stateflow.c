/*
 * File: my_stateflow.c
 *
 * Code generated for Simulink model 'my_stateflow'.
 *
 * Model version                  : 1.15
 * Simulink Coder version         : 9.3 (R2020a) 18-Nov-2019
 * C/C++ source code generated on : Tue Jan 19 20:38:00 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "my_stateflow.h"
#include "my_stateflow_private.h"

/* Named constants for Chart: '<Root>/Chart' */
#define my_stateflow_IN_High_speed     ((uint8_T)1U)
#define my_stateflow_IN_Low_speed      ((uint8_T)2U)
#define my_stateflow_IN_Mid_speed      ((uint8_T)3U)
#define my_stateflow_IN_P              ((uint8_T)4U)
#define my_stateflow_IN_R              ((uint8_T)5U)

/* Block states (default storage) */
DW_my_stateflow_T my_stateflow_DW;

/* Real-time model */
RT_MODEL_my_stateflow_T my_stateflow_M_;
RT_MODEL_my_stateflow_T *const my_stateflow_M = &my_stateflow_M_;

/* Model step function */
void my_stateflow_step(void)
{
  /* Chart: '<Root>/Chart' */
  if (my_stateflow_DW.is_active_c3_my_stateflow == 0U) {
    my_stateflow_DW.is_active_c3_my_stateflow = 1U;
    my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_P;
    g_msg_out.CurState = state_P;
  } else {
    switch (my_stateflow_DW.is_c3_my_stateflow) {
     case my_stateflow_IN_High_speed:
      if (g_msg_in.speed < 45.0F) {
        g_msg_out.BrakeState = UnLock;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_Mid_speed;
        g_msg_out.CurState = state_D_mid;
      } else if (g_msg_in.CarEvent == shift_down) {
        g_msg_out.BrakeState = BrakeHigh;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_P;
        g_msg_out.CurState = state_P;
      } else {
        g_msg_out.acc = acc_update(state_D_high);
      }
      break;

     case my_stateflow_IN_Low_speed:
      if (g_msg_in.speed > 30.0F) {
        g_msg_out.BrakeState = UnLock;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_Mid_speed;
        g_msg_out.CurState = state_D_mid;
      } else if (g_msg_in.CarEvent == shift_down) {
        g_msg_out.BrakeState = BrakeLow;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_P;
        g_msg_out.CurState = state_P;
      } else {
        g_msg_out.acc = acc_update(state_D_low);
      }
      break;

     case my_stateflow_IN_Mid_speed:
      if (g_msg_in.speed > 50.0F) {
        g_msg_out.BrakeState = UnLock;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_High_speed;
        g_msg_out.CurState = state_D_high;
      } else if (g_msg_in.speed < 25.0F) {
        g_msg_out.BrakeState = UnLock;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_Low_speed;
        g_msg_out.CurState = state_D_low;
      } else if (g_msg_in.CarEvent == shift_down) {
        g_msg_out.BrakeState = BrakeMid;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_P;
        g_msg_out.CurState = state_P;
      } else {
        g_msg_out.acc = acc_update(state_D_mid);
      }
      break;

     case my_stateflow_IN_P:
      if (g_msg_in.CarEvent == shift_up) {
        g_msg_out.BrakeState = UnLock;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_Low_speed;
        g_msg_out.CurState = state_D_low;
      } else if (g_msg_in.CarEvent == shift_down) {
        g_msg_out.BrakeState = UnLock;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_R;
        g_msg_out.CurState = state_R;
      } else {
        g_msg_out.acc = acc_update(state_P);
      }
      break;

     default:
      /* case IN_R: */
      if (g_msg_in.CarEvent == shift_up) {
        g_msg_out.BrakeState = BreakReverse;
        my_stateflow_DW.is_c3_my_stateflow = my_stateflow_IN_P;
        g_msg_out.CurState = state_P;
      } else {
        g_msg_out.acc = acc_update(state_R);
      }
      break;
    }
  }

  /* End of Chart: '<Root>/Chart' */
}

/* Model initialize function */
void my_stateflow_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void my_stateflow_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
