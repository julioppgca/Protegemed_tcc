/*
 * File: SignalGen4.h
 *
 * Code generated for Simulink model 'SignalGen4'.
 *
 * Model version                  : 1.160
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Thu Aug 31 20:26:42 2017
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_SignalGen4_h_
#define RTW_HEADER_SignalGen4_h_
#include <string.h>
#include <stddef.h>
#ifndef SignalGen4_COMMON_INCLUDES_
# define SignalGen4_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "F2806x_Device.h"
#include "F2806x_Examples.h"
#include "IQmathLib.h"
#endif                                 /* SignalGen4_COMMON_INCLUDES_ */

#include "SignalGen4_types.h"
#include "MW_target_hardware_resources.h"

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
extern void config_ePWM_GPIO (void);

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint16_T Output_DSTATE;              /* '<S1>/Output' */
} DW_SignalGen4_T;

/* Parameters (auto storage) */
struct P_SignalGen4_T_ {
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
  uint16_T CounterLimited_uplimit;     /* Mask Parameter: CounterLimited_uplimit
                                        * Referenced by: '<S4>/FixPt Switch'
                                        */
  uint16_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S4>/Constant'
                                        */
  uint16_T Output_InitialCondition;    /* Computed Parameter: Output_InitialCondition
                                        * Referenced by: '<S1>/Output'
                                        */
  uint16_T FixPtConstant_Value;        /* Computed Parameter: FixPtConstant_Value
                                        * Referenced by: '<S3>/FixPt Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_SignalGen4_T {
  const char_T *errorStatus;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

/* Block parameters (auto storage) */
extern P_SignalGen4_T SignalGen4_P;

/* Block states (auto storage) */
extern DW_SignalGen4_T SignalGen4_DW;

/* External function called from main */
extern void SignalGen4_SetEventsForThisBaseStep(boolean_T *eventFlags);

/* Model entry point functions */
extern void SignalGen4_SetEventsForThisBaseStep(boolean_T *eventFlags);
extern void SignalGen4_initialize(void);
extern void SignalGen4_step(int_T tid);
extern void SignalGen4_terminate(void);

/* Real-time Model object */
extern RT_MODEL_SignalGen4_T *const SignalGen4_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Data Type Propagation' : Unused code path elimination
 * Block '<S3>/FixPt Data Type Duplicate' : Unused code path elimination
 * Block '<S4>/FixPt Data Type Duplicate1' : Unused code path elimination
 * Block '<S2>/DAC1 Vrms' : Unused code path elimination
 * Block '<S2>/DAC2 Vrms' : Unused code path elimination
 * Block '<S2>/DAC3 Vrms' : Unused code path elimination
 * Block '<S2>/DAC4 Vrms' : Unused code path elimination
 * Block '<S2>/Osciloscoppe view' : Unused code path elimination
 * Block '<S2>/RMS' : Unused code path elimination
 * Block '<S2>/RMS1' : Unused code path elimination
 * Block '<S2>/RMS2' : Unused code path elimination
 * Block '<S2>/RMS3' : Unused code path elimination
 * Block '<S5>/Bias offset' : Unused code path elimination
 * Block '<S5>/Gain to volts' : Unused code path elimination
 * Block '<S6>/Rate Transition' : Unused code path elimination
 * Block '<S6>/To Workspace' : Unused code path elimination
 * Block '<S6>/ZOH ADC simulation' : Unused code path elimination
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
 * '<Root>' : 'SignalGen4'
 * '<S1>'   : 'SignalGen4/Counter Limited'
 * '<S2>'   : 'SignalGen4/Simulation view'
 * '<S3>'   : 'SignalGen4/Counter Limited/Increment Real World'
 * '<S4>'   : 'SignalGen4/Counter Limited/Wrap To Zero'
 * '<S5>'   : 'SignalGen4/Simulation view/Scale to 3.3 Volts'
 * '<S6>'   : 'SignalGen4/Simulation view/Subsystem'
 */
#endif                                 /* RTW_HEADER_SignalGen4_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
