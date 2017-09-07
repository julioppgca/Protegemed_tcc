/*
 * File: SignalGen_rx.h
 *
 * Code generated for Simulink model 'SignalGen_rx'.
 *
 * Model version                  : 1.185
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Tue Sep 05 18:15:23 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SignalGen_rx_h_
#define RTW_HEADER_SignalGen_rx_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef SignalGen_rx_COMMON_INCLUDES_
# define SignalGen_rx_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "F2806x_Device.h"
#include "DSP28xx_SciUtil.h"
#include "F2806x_Examples.h"
#include "IQmathLib.h"
#endif                                 /* SignalGen_rx_COMMON_INCLUDES_ */

#include "SignalGen_rx_types.h"
#include "MW_target_hardware_resources.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

extern void enable_interrupts(void);
extern void init_SCI(void);
extern void init_SCI_GPIO(void);
extern void config_ePWM_GPIO (void);

/* Block signals (auto storage) */
typedef struct {
  uint16_T Gain[4];                    /* '<S1>/Gain' */
  uint16_T SCIReceive[4];              /* '<S1>/SCI Receive' */
} B_SignalGen_rx_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T Output_DSTATE;              /* '<S2>/Output' */
} DW_SignalGen_rx_T;

/* Parameters (auto storage) */
struct P_SignalGen_rx_T_ {
  real_T DAC1[512];                    /* Variable: DAC1
                                        * Referenced by: '<Root>/Direct Lookup Table (n-D)1'
                                        */
  real_T DAC2[512];                    /* Variable: DAC2
                                        * Referenced by: '<Root>/Direct Lookup Table (n-D)2'
                                        */
  real_T DAC3[512];                    /* Variable: DAC3
                                        * Referenced by: '<Root>/Direct Lookup Table (n-D)3'
                                        */
  real_T DAC4[512];                    /* Variable: DAC4
                                        * Referenced by: '<Root>/Direct Lookup Table (n-D)4'
                                        */
  real_T PWM_Offset;                   /* Variable: PWM_Offset
                                        * Referenced by:
                                        *   '<Root>/Constant'
                                        *   '<Root>/Direct Lookup Table (n-D)1'
                                        *   '<Root>/Direct Lookup Table (n-D)2'
                                        *   '<Root>/Direct Lookup Table (n-D)3'
                                        *   '<Root>/Direct Lookup Table (n-D)4'
                                        */
  uint16_T CounterLimited_uplimit;     /* Mask Parameter: CounterLimited_uplimit
                                        * Referenced by: '<S5>/FixPt Switch'
                                        */
  real_T Constant_Value;               /* Expression: 127/255
                                        * Referenced by: '<S1>/Constant'
                                        */
  uint16_T Constant_Value_o;           /* Computed Parameter: Constant_Value_o
                                        * Referenced by: '<S5>/Constant'
                                        */
  uint16_T Output_InitialCondition;    /* Computed Parameter: Output_InitialCondition
                                        * Referenced by: '<S2>/Output'
                                        */
  uint16_T FixPtConstant_Value;        /* Computed Parameter: FixPtConstant_Value
                                        * Referenced by: '<S4>/FixPt Constant'
                                        */
  uint16_T Gain_Gain;                  /* Computed Parameter: Gain_Gain
                                        * Referenced by: '<S1>/Gain'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_SignalGen_rx_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint16_T TID[3];
    } TaskCounters;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_SignalGen_rx_T SignalGen_rx_P;

/* Block signals (auto storage) */
extern B_SignalGen_rx_T SignalGen_rx_B;

/* Block states (auto storage) */
extern DW_SignalGen_rx_T SignalGen_rx_DW;

/* External function called from main */
extern void SignalGen_rx_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void SignalGen_rx_SetEventsForThisBaseStep(boolean_T *eventFlags);
extern void SignalGen_rx_initialize(void);
extern void SignalGen_rx_step(int_T tid);
extern void SignalGen_rx_terminate(void);

/* Real-time Model object */
extern RT_MODEL_SignalGen_rx_T *const SignalGen_rx_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Data Type Propagation' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S5>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S3>/DAC1 Vrms' : Unused code path elimination
 * Block '<S3>/DAC2 Vrms' : Unused code path elimination
 * Block '<S3>/DAC3 Vrms' : Unused code path elimination
 * Block '<S3>/DAC4 Vrms' : Unused code path elimination
 * Block '<S3>/Osciloscoppe view' : Unused code path elimination
 * Block '<S3>/RMS' : Unused code path elimination
 * Block '<S3>/RMS1' : Unused code path elimination
 * Block '<S3>/RMS2' : Unused code path elimination
 * Block '<S3>/RMS3' : Unused code path elimination
 * Block '<S6>/Bias offset' : Unused code path elimination
 * Block '<S6>/Gain to volts' : Unused code path elimination
 * Block '<S7>/Rate Transition' : Unused code path elimination
 * Block '<S7>/To Workspace' : Unused code path elimination
 * Block '<S7>/ZOH ADC simulation' : Unused code path elimination
 * Block '<S1>/Rate Transition3' : Eliminated since input and output rates are identical
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SignalGen_rx'
 * '<S1>'   : 'SignalGen_rx/Comunication'
 * '<S2>'   : 'SignalGen_rx/Counter Limited'
 * '<S3>'   : 'SignalGen_rx/Simulation view'
 * '<S4>'   : 'SignalGen_rx/Counter Limited/Increment Real World'
 * '<S5>'   : 'SignalGen_rx/Counter Limited/Wrap To Zero'
 * '<S6>'   : 'SignalGen_rx/Simulation view/Scale to 3.3 Volts'
 * '<S7>'   : 'SignalGen_rx/Simulation view/Subsystem'
 */
#endif                                 /* RTW_HEADER_SignalGen_rx_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
