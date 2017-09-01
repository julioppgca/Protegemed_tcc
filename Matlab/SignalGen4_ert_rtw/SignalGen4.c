/*
 * File: SignalGen4.c
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

#include "SignalGen4.h"
#include "SignalGen4_private.h"

/* Block states (auto storage) */
DW_SignalGen4_T SignalGen4_DW;

/* Real-time model */
RT_MODEL_SignalGen4_T SignalGen4_M_;
RT_MODEL_SignalGen4_T *const SignalGen4_M = &SignalGen4_M_;
static void rate_monotonic_scheduler(void);

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to "remember" which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void SignalGen4_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(SignalGen4_M, 1));
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (SignalGen4_M->Timing.TaskCounters.TID[1])++;
  if ((SignalGen4_M->Timing.TaskCounters.TID[1]) > 1) {/* Sample time: [6.5104166666666666E-5s, 0.0s] */
    SignalGen4_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function for TID0 */
void SignalGen4_step0(void)            /* Sample time: [3.2552083333333333E-5s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_DirectLookupTablenD4;
  real_T rtb_DirectLookupTablenD3;
  uint16_T rtb_FixPtSum1;

  {                                    /* Sample time: [3.2552083333333333E-5s, 0.0s] */
    rate_monotonic_scheduler();
  }

  /* LookupNDDirect: '<Root>/Direct Lookup Table (n-D)1' incorporates:
   *  UnitDelay: '<S1>/Output'
   *
   * About '<Root>/Direct Lookup Table (n-D)1':
   *  1-dimensional Direct Look-Up returning a Scalar
   */
  if (SignalGen4_DW.Output_DSTATE <= 511U) {
    rtb_FixPtSum1 = SignalGen4_DW.Output_DSTATE;
  } else {
    rtb_FixPtSum1 = 511U;
  }

  rtb_DirectLookupTablenD4 = SignalGen4_P.DAC1[(int16_T)rtb_FixPtSum1];

  /* End of LookupNDDirect: '<Root>/Direct Lookup Table (n-D)1' */

  /* LookupNDDirect: '<Root>/Direct Lookup Table (n-D)2' incorporates:
   *  UnitDelay: '<S1>/Output'
   *
   * About '<Root>/Direct Lookup Table (n-D)2':
   *  1-dimensional Direct Look-Up returning a Scalar
   */
  if (SignalGen4_DW.Output_DSTATE <= 511U) {
    rtb_FixPtSum1 = SignalGen4_DW.Output_DSTATE;
  } else {
    rtb_FixPtSum1 = 511U;
  }

  rtb_DirectLookupTablenD3 = SignalGen4_P.DAC2[(int16_T)rtb_FixPtSum1];

  /* End of LookupNDDirect: '<Root>/Direct Lookup Table (n-D)2' */

  /* S-Function (c2802xpwm): '<Root>/ePWM7 DAC1 and DAC2' */

  /*-- Update CMPA value for ePWM7 --*/
  {
    EPwm7Regs.CMPA.half.CMPA = (uint16_T)(rtb_DirectLookupTablenD4);
  }

  /*-- Update CMPB value for ePWM7 --*/
  {
    EPwm7Regs.CMPB = (uint16_T)(rtb_DirectLookupTablenD3);
  }

  /* LookupNDDirect: '<Root>/Direct Lookup Table (n-D)3' incorporates:
   *  UnitDelay: '<S1>/Output'
   *
   * About '<Root>/Direct Lookup Table (n-D)3':
   *  1-dimensional Direct Look-Up returning a Scalar
   */
  if (SignalGen4_DW.Output_DSTATE <= 511U) {
    rtb_FixPtSum1 = SignalGen4_DW.Output_DSTATE;
  } else {
    rtb_FixPtSum1 = 511U;
  }

  rtb_DirectLookupTablenD3 = SignalGen4_P.DAC3[(int16_T)rtb_FixPtSum1];

  /* End of LookupNDDirect: '<Root>/Direct Lookup Table (n-D)3' */

  /* LookupNDDirect: '<Root>/Direct Lookup Table (n-D)4' incorporates:
   *  UnitDelay: '<S1>/Output'
   *
   * About '<Root>/Direct Lookup Table (n-D)4':
   *  1-dimensional Direct Look-Up returning a Scalar
   */
  if (SignalGen4_DW.Output_DSTATE <= 511U) {
    rtb_FixPtSum1 = SignalGen4_DW.Output_DSTATE;
  } else {
    rtb_FixPtSum1 = 511U;
  }

  rtb_DirectLookupTablenD4 = SignalGen4_P.DAC4[(int16_T)rtb_FixPtSum1];

  /* End of LookupNDDirect: '<Root>/Direct Lookup Table (n-D)4' */

  /* S-Function (c2802xpwm): '<Root>/ePWM8 DAC3 and DAC4' */

  /*-- Update CMPA value for ePWM8 --*/
  {
    EPwm8Regs.CMPA.half.CMPA = (uint16_T)(rtb_DirectLookupTablenD3);
  }

  /*-- Update CMPB value for ePWM8 --*/
  {
    EPwm8Regs.CMPB = (uint16_T)(rtb_DirectLookupTablenD4);
  }

  /* Sum: '<S3>/FixPt Sum1' incorporates:
   *  Constant: '<S3>/FixPt Constant'
   *  UnitDelay: '<S1>/Output'
   */
  rtb_FixPtSum1 = SignalGen4_DW.Output_DSTATE + SignalGen4_P.FixPtConstant_Value;

  /* Switch: '<S4>/FixPt Switch' */
  if (rtb_FixPtSum1 > SignalGen4_P.CounterLimited_uplimit) {
    /* Update for UnitDelay: '<S1>/Output' incorporates:
     *  Constant: '<S4>/Constant'
     */
    SignalGen4_DW.Output_DSTATE = SignalGen4_P.Constant_Value;
  } else {
    /* Update for UnitDelay: '<S1>/Output' */
    SignalGen4_DW.Output_DSTATE = rtb_FixPtSum1;
  }

  /* End of Switch: '<S4>/FixPt Switch' */
}

/* Model step function for TID1 */
void SignalGen4_step1(void)            /* Sample time: [6.5104166666666666E-5s, 0.0s] */
{
  /* (no output/update code required) */
}

/* Model step wrapper function for compatibility with a static main program */
void SignalGen4_step(int_T tid)
{
  switch (tid) {
   case 0 :
    SignalGen4_step0();
    break;

   case 1 :
    SignalGen4_step1();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void SignalGen4_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)SignalGen4_M, 0,
                sizeof(RT_MODEL_SignalGen4_T));

  /* states (dwork) */
  (void) memset((void *)&SignalGen4_DW, 0,
                sizeof(DW_SignalGen4_T));

  /* Start for S-Function (c2802xpwm): '<Root>/ePWM7 DAC1 and DAC2' */

  /*** Initialize ePWM7 modules ***/
  {
    /*-- Setup Time-Base (TB) Submodule --*/
    EPwm7Regs.TBPRD = 360;             // Time Base Period Register

    /*  // Time Base Control Register
       EPwm7Regs.TBCTL.bit.CTRMODE              = 0;          // Counter Mode
       EPwm7Regs.TBCTL.bit.SYNCOSEL             = 3;          // Sync Output Select
       EPwm7Regs.TBCTL.bit.PRDLD                = 0;          // Shadow select
       EPwm7Regs.TBCTL.bit.PHSEN                = 0;          // Phase Load Enable
       EPwm7Regs.TBCTL.bit.PHSDIR               = 0;          // Phase Direction Bit
       EPwm7Regs.TBCTL.bit.HSPCLKDIV            = 0;          // High Speed TBCLK Pre-scaler
       EPwm7Regs.TBCTL.bit.CLKDIV               = 0;          // Time Base Clock Pre-scaler
       EPwm7Regs.TBCTL.bit.SWFSYNC              = 0;          // Software Force Sync Pulse
     */
    EPwm7Regs.TBCTL.all = (EPwm7Regs.TBCTL.all & ~0x3FFF) | 0x30;

    /* // Time-Base Phase Register
       EPwm7Regs.TBPHS.half.TBPHS               = 0;          // Phase offset register
     */
    EPwm7Regs.TBPHS.all = (EPwm7Regs.TBPHS.all & ~0xFFFF0000) | 0x0;

    // Time Base Counter Register
    EPwm7Regs.TBCTR = 0x0000;          /* Clear counter*/

    /*-- Setup Counter_Compare (CC) Submodule --*/
    /*	// Counter Compare Control Register
       EPwm7Regs.CMPCTL.bit.SHDWAMODE           = 0;  // Compare A Register Block Operating Mode
       EPwm7Regs.CMPCTL.bit.SHDWBMODE           = 0;  // Compare B Register Block Operating Mode
       EPwm7Regs.CMPCTL.bit.LOADAMODE           = 0;          // Active Compare A Load
       EPwm7Regs.CMPCTL.bit.LOADBMODE           = 0;          // Active Compare B Load
     */
    EPwm7Regs.CMPCTL.all = (EPwm7Regs.CMPCTL.all & ~0x5F) | 0x0;
    EPwm7Regs.CMPA.half.CMPA = 180;    // Counter Compare A Register
    EPwm7Regs.CMPB = 180;              // Counter Compare B Register

    /*-- Setup Action-Qualifier (AQ) Submodule --*/
    EPwm7Regs.AQCTLA.all = 150;        // Action Qualifier Control Register For Output A
    EPwm7Regs.AQCTLB.all = 2310;       // Action Qualifier Control Register For Output B

    /*	// Action Qualifier Software Force Register
       EPwm7Regs.AQSFRC.bit.RLDCSF              = 0;          // Reload from Shadow Options
     */
    EPwm7Regs.AQSFRC.all = (EPwm7Regs.AQSFRC.all & ~0xC0) | 0x0;

    /*	// Action Qualifier Continuous S/W Force Register
       EPwm7Regs.AQCSFRC.bit.CSFA               = 0;          // Continuous Software Force on output A
       EPwm7Regs.AQCSFRC.bit.CSFB               = 0;          // Continuous Software Force on output B
     */
    EPwm7Regs.AQCSFRC.all = (EPwm7Regs.AQCSFRC.all & ~0xF) | 0x0;

    /*-- Setup Dead-Band Generator (DB) Submodule --*/
    /*	// Dead-Band Generator Control Register
       EPwm7Regs.DBCTL.bit.OUT_MODE             = 0;          // Dead Band Output Mode Control
       EPwm7Regs.DBCTL.bit.IN_MODE              = 0;          // Dead Band Input Select Mode Control
       EPwm7Regs.DBCTL.bit.POLSEL               = 0;          // Polarity Select Control
       EPwm7Regs.DBCTL.bit.HALFCYCLE            = 0;          // Half Cycle Clocking Enable
     */
    EPwm7Regs.DBCTL.all = (EPwm7Regs.DBCTL.all & ~0x803F) | 0x0;
    EPwm7Regs.DBRED = 0;               // Dead-Band Generator Rising Edge Delay Count Register
    EPwm7Regs.DBFED = 0;               // Dead-Band Generator Falling Edge Delay Count Register

    /*-- Setup Event-Trigger (ET) Submodule --*/
    /*	// Event Trigger Selection and Pre-Scale Register
       EPwm7Regs.ETSEL.bit.SOCAEN               = 0;          // Start of Conversion A Enable
       EPwm7Regs.ETSEL.bit.SOCASEL              = 0;          // Start of Conversion A Select
       EPwm7Regs.ETPS.bit.SOCAPRD               = 1;          // EPWM7SOCA Period Select

       EPwm7Regs.ETSEL.bit.SOCBEN               = 0;          // Start of Conversion B Enable

       EPwm7Regs.ETSEL.bit.SOCBSEL              = 1;          // Start of Conversion B Select
       EPwm7Regs.ETPS.bit.SOCBPRD               = 1;          // EPWM7SOCB Period Select
       EPwm7Regs.ETSEL.bit.INTEN                = 0;          // EPWM7INTn Enable
       EPwm7Regs.ETSEL.bit.INTSEL               = 1;          // EPWM7INTn Select

       EPwm7Regs.ETPS.bit.INTPRD                = 1;          // EPWM7INTn Period Select
     */
    EPwm7Regs.ETSEL.all = (EPwm7Regs.ETSEL.all & ~0xFF0F) | 0x1001;
    EPwm7Regs.ETPS.all = (EPwm7Regs.ETPS.all & ~0x3303) | 0x1101;

    /*-- Setup PWM-Chopper (PC) Submodule --*/
    /*	// PWM Chopper Control Register
       EPwm7Regs.PCCTL.bit.CHPEN                = 0;          // PWM chopping enable
       EPwm7Regs.PCCTL.bit.CHPFREQ              = 0;          // Chopping clock frequency
       EPwm7Regs.PCCTL.bit.OSHTWTH              = 0;          // One-shot pulse width
       EPwm7Regs.PCCTL.bit.CHPDUTY              = 0;          // Chopping clock Duty cycle
     */
    EPwm7Regs.PCCTL.all = (EPwm7Regs.PCCTL.all & ~0x7FF) | 0x0;

    /*-- Set up Trip-Zone (TZ) Submodule --*/
    EALLOW;
    EPwm7Regs.TZSEL.all = 0;           // Trip Zone Select Register

    /*	// Trip Zone Control Register
       EPwm7Regs.TZCTL.bit.TZA                  = 3;          // TZ1 to TZ6 Trip Action On EPWM7A
       EPwm7Regs.TZCTL.bit.TZB                  = 3;          // TZ1 to TZ6 Trip Action On EPWM7B
       EPwm7Regs.TZCTL.bit.DCAEVT1              = 3;          // EPWM7A action on DCAEVT1
       EPwm7Regs.TZCTL.bit.DCAEVT2              = 3;          // EPWM7A action on DCAEVT2
       EPwm7Regs.TZCTL.bit.DCBEVT1              = 3;          // EPWM7B action on DCBEVT1
       EPwm7Regs.TZCTL.bit.DCBEVT2              = 3;          // EPWM7B action on DCBEVT2
     */
    EPwm7Regs.TZCTL.all = (EPwm7Regs.TZCTL.all & ~0xFFF) | 0xFFF;

    /*	// Trip Zone Enable Interrupt Register
       EPwm7Regs.TZEINT.bit.OST                 = 0;          // Trip Zones One Shot Int Enable
       EPwm7Regs.TZEINT.bit.CBC                 = 0;          // Trip Zones Cycle By Cycle Int Enable
       EPwm7Regs.TZEINT.bit.DCAEVT1             = 0;          // Digital Compare A Event 1 Int Enable
       EPwm7Regs.TZEINT.bit.DCAEVT2             = 0;          // Digital Compare A Event 2 Int Enable
       EPwm7Regs.TZEINT.bit.DCBEVT1             = 0;          // Digital Compare B Event 1 Int Enable
       EPwm7Regs.TZEINT.bit.DCBEVT2             = 0;          // Digital Compare B Event 2 Int Enable
     */
    EPwm7Regs.TZEINT.all = (EPwm7Regs.TZEINT.all & ~0x7E) | 0x0;

    /*	// Digital Compare A Control Register
       EPwm7Regs.DCACTL.bit.EVT1SYNCE           = 0;          // DCAEVT1 SYNC Enable
       EPwm7Regs.DCACTL.bit.EVT1SOCE            = 1;          // DCAEVT1 SOC Enable
       EPwm7Regs.DCACTL.bit.EVT1FRCSYNCSEL      = 0;          // DCAEVT1 Force Sync Signal
       EPwm7Regs.DCACTL.bit.EVT1SRCSEL          = 0;          // DCAEVT1 Source Signal
       EPwm7Regs.DCACTL.bit.EVT2FRCSYNCSEL      = 0;          // DCAEVT2 Force Sync Signal
       EPwm7Regs.DCACTL.bit.EVT2SRCSEL          = 0;          // DCAEVT2 Source Signal
     */
    EPwm7Regs.DCACTL.all = (EPwm7Regs.DCACTL.all & ~0x30F) | 0x4;

    /*	// Digital Compare B Control Register
       EPwm7Regs.DCBCTL.bit.EVT1SYNCE           = 0;          // DCBEVT1 SYNC Enable
       EPwm7Regs.DCBCTL.bit.EVT1SOCE            = 0;          // DCBEVT1 SOC Enable
       EPwm7Regs.DCBCTL.bit.EVT1FRCSYNCSEL      = 0;          // DCBEVT1 Force Sync Signal
       EPwm7Regs.DCBCTL.bit.EVT1SRCSEL          = 0;          // DCBEVT1 Source Signal
       EPwm7Regs.DCBCTL.bit.EVT2FRCSYNCSEL      = 0;          // DCBEVT2 Force Sync Signal
       EPwm7Regs.DCBCTL.bit.EVT2SRCSEL          = 0;          // DCBEVT2 Source Signal
     */
    EPwm7Regs.DCBCTL.all = (EPwm7Regs.DCBCTL.all & ~0x30F) | 0x0;

    /*	// Digital Compare Trip Select Register
       EPwm7Regs.DCTRIPSEL.bit.DCAHCOMPSEL      = 0;          // Digital Compare A High COMP Input Select

       EPwm7Regs.DCTRIPSEL.bit.DCALCOMPSEL      = 1;          // Digital Compare A Low COMP Input Select
       EPwm7Regs.DCTRIPSEL.bit.DCBHCOMPSEL      = 0;          // Digital Compare B High COMP Input Select
       EPwm7Regs.DCTRIPSEL.bit.DCBLCOMPSEL      = 1;          // Digital Compare B Low COMP Input Select
     */
    EPwm7Regs.DCTRIPSEL.all = (EPwm7Regs.DCTRIPSEL.all & ~ 0xFFFF) | 0x1010;

    /*	// Trip Zone Digital Comparator Select Register
       EPwm7Regs.TZDCSEL.bit.DCAEVT1            = 0;          // Digital Compare Output A Event 1
       EPwm7Regs.TZDCSEL.bit.DCAEVT2            = 0;          // Digital Compare Output A Event 2
       EPwm7Regs.TZDCSEL.bit.DCBEVT1            = 0;          // Digital Compare Output B Event 1
       EPwm7Regs.TZDCSEL.bit.DCBEVT2            = 0;          // Digital Compare Output B Event 2
     */
    EPwm7Regs.TZDCSEL.all = (EPwm7Regs.TZDCSEL.all & ~0xFFF) | 0x0;

    /*	// Digital Compare Filter Control Register
       EPwm7Regs.DCFCTL.bit.BLANKE              = 0;          // Blanking Enable/Disable
       EPwm7Regs.DCFCTL.bit.PULSESEL            = 1;          // Pulse Select for Blanking & Capture Alignment
       EPwm7Regs.DCFCTL.bit.BLANKINV            = 0;          // Blanking Window Inversion
       EPwm7Regs.DCFCTL.bit.SRCSEL              = 0;          // Filter Block Signal Source Select
     */
    EPwm7Regs.DCFCTL.all = (EPwm7Regs.DCFCTL.all & ~0x3F) | 0x10;
    EPwm7Regs.DCFOFFSET = 0;           // Digital Compare Filter Offset Register
    EPwm7Regs.DCFWINDOW = 0;           // Digital Compare Filter Window Register

    /*	// Digital Compare Capture Control Register
       EPwm7Regs.DCCAPCTL.bit.CAPE              = 0;          // Counter Capture Enable
     */
    EPwm7Regs.DCCAPCTL.all = (EPwm7Regs.DCCAPCTL.all & ~0x1) | 0x0;

    /*	// HRPWM Configuration Register
       EPwm7Regs.HRCNFG.bit.SWAPAB              = 0;          // Swap EPWMA and EPWMB Outputs Bit
       EPwm7Regs.HRCNFG.bit.SELOUTB             = 0;          // EPWMB Output Selection Bit
     */
    EPwm7Regs.HRCNFG.all = (EPwm7Regs.HRCNFG.all & ~0xA0) | 0x0;
    EDIS;
  }

  /* Start for S-Function (c2802xpwm): '<Root>/ePWM8 DAC3 and DAC4' */

  /*** Initialize ePWM8 modules ***/
  {
    /*-- Setup Time-Base (TB) Submodule --*/
    EPwm8Regs.TBPRD = 360;             // Time Base Period Register

    /*  // Time Base Control Register
       EPwm8Regs.TBCTL.bit.CTRMODE              = 0;          // Counter Mode
       EPwm8Regs.TBCTL.bit.SYNCOSEL             = 3;          // Sync Output Select
       EPwm8Regs.TBCTL.bit.PRDLD                = 0;          // Shadow select
       EPwm8Regs.TBCTL.bit.PHSEN                = 0;          // Phase Load Enable
       EPwm8Regs.TBCTL.bit.PHSDIR               = 0;          // Phase Direction Bit
       EPwm8Regs.TBCTL.bit.HSPCLKDIV            = 0;          // High Speed TBCLK Pre-scaler
       EPwm8Regs.TBCTL.bit.CLKDIV               = 0;          // Time Base Clock Pre-scaler
       EPwm8Regs.TBCTL.bit.SWFSYNC              = 0;          // Software Force Sync Pulse
     */
    EPwm8Regs.TBCTL.all = (EPwm8Regs.TBCTL.all & ~0x3FFF) | 0x30;

    /* // Time-Base Phase Register
       EPwm8Regs.TBPHS.half.TBPHS               = 0;          // Phase offset register
     */
    EPwm8Regs.TBPHS.all = (EPwm8Regs.TBPHS.all & ~0xFFFF0000) | 0x0;

    // Time Base Counter Register
    EPwm8Regs.TBCTR = 0x0000;          /* Clear counter*/

    /*-- Setup Counter_Compare (CC) Submodule --*/
    /*	// Counter Compare Control Register
       EPwm8Regs.CMPCTL.bit.SHDWAMODE           = 0;  // Compare A Register Block Operating Mode
       EPwm8Regs.CMPCTL.bit.SHDWBMODE           = 0;  // Compare B Register Block Operating Mode
       EPwm8Regs.CMPCTL.bit.LOADAMODE           = 0;          // Active Compare A Load
       EPwm8Regs.CMPCTL.bit.LOADBMODE           = 0;          // Active Compare B Load
     */
    EPwm8Regs.CMPCTL.all = (EPwm8Regs.CMPCTL.all & ~0x5F) | 0x0;
    EPwm8Regs.CMPA.half.CMPA = 180;    // Counter Compare A Register
    EPwm8Regs.CMPB = 180;              // Counter Compare B Register

    /*-- Setup Action-Qualifier (AQ) Submodule --*/
    EPwm8Regs.AQCTLA.all = 150;        // Action Qualifier Control Register For Output A
    EPwm8Regs.AQCTLB.all = 2310;       // Action Qualifier Control Register For Output B

    /*	// Action Qualifier Software Force Register
       EPwm8Regs.AQSFRC.bit.RLDCSF              = 0;          // Reload from Shadow Options
     */
    EPwm8Regs.AQSFRC.all = (EPwm8Regs.AQSFRC.all & ~0xC0) | 0x0;

    /*	// Action Qualifier Continuous S/W Force Register
       EPwm8Regs.AQCSFRC.bit.CSFA               = 0;          // Continuous Software Force on output A
       EPwm8Regs.AQCSFRC.bit.CSFB               = 0;          // Continuous Software Force on output B
     */
    EPwm8Regs.AQCSFRC.all = (EPwm8Regs.AQCSFRC.all & ~0xF) | 0x0;

    /*-- Setup Dead-Band Generator (DB) Submodule --*/
    /*	// Dead-Band Generator Control Register
       EPwm8Regs.DBCTL.bit.OUT_MODE             = 0;          // Dead Band Output Mode Control
       EPwm8Regs.DBCTL.bit.IN_MODE              = 0;          // Dead Band Input Select Mode Control
       EPwm8Regs.DBCTL.bit.POLSEL               = 0;          // Polarity Select Control
       EPwm8Regs.DBCTL.bit.HALFCYCLE            = 0;          // Half Cycle Clocking Enable
     */
    EPwm8Regs.DBCTL.all = (EPwm8Regs.DBCTL.all & ~0x803F) | 0x0;
    EPwm8Regs.DBRED = 0;               // Dead-Band Generator Rising Edge Delay Count Register
    EPwm8Regs.DBFED = 0;               // Dead-Band Generator Falling Edge Delay Count Register

    /*-- Setup Event-Trigger (ET) Submodule --*/
    /*	// Event Trigger Selection and Pre-Scale Register
       EPwm8Regs.ETSEL.bit.SOCAEN               = 0;          // Start of Conversion A Enable
       EPwm8Regs.ETSEL.bit.SOCASEL              = 0;          // Start of Conversion A Select
       EPwm8Regs.ETPS.bit.SOCAPRD               = 1;          // EPWM8SOCA Period Select

       EPwm8Regs.ETSEL.bit.SOCBEN               = 0;          // Start of Conversion B Enable

       EPwm8Regs.ETSEL.bit.SOCBSEL              = 1;          // Start of Conversion B Select
       EPwm8Regs.ETPS.bit.SOCBPRD               = 1;          // EPWM8SOCB Period Select
       EPwm8Regs.ETSEL.bit.INTEN                = 0;          // EPWM8INTn Enable
       EPwm8Regs.ETSEL.bit.INTSEL               = 1;          // EPWM8INTn Select

       EPwm8Regs.ETPS.bit.INTPRD                = 1;          // EPWM8INTn Period Select
     */
    EPwm8Regs.ETSEL.all = (EPwm8Regs.ETSEL.all & ~0xFF0F) | 0x1001;
    EPwm8Regs.ETPS.all = (EPwm8Regs.ETPS.all & ~0x3303) | 0x1101;

    /*-- Setup PWM-Chopper (PC) Submodule --*/
    /*	// PWM Chopper Control Register
       EPwm8Regs.PCCTL.bit.CHPEN                = 0;          // PWM chopping enable
       EPwm8Regs.PCCTL.bit.CHPFREQ              = 0;          // Chopping clock frequency
       EPwm8Regs.PCCTL.bit.OSHTWTH              = 0;          // One-shot pulse width
       EPwm8Regs.PCCTL.bit.CHPDUTY              = 0;          // Chopping clock Duty cycle
     */
    EPwm8Regs.PCCTL.all = (EPwm8Regs.PCCTL.all & ~0x7FF) | 0x0;

    /*-- Set up Trip-Zone (TZ) Submodule --*/
    EALLOW;
    EPwm8Regs.TZSEL.all = 0;           // Trip Zone Select Register

    /*	// Trip Zone Control Register
       EPwm8Regs.TZCTL.bit.TZA                  = 3;          // TZ1 to TZ6 Trip Action On EPWM8A
       EPwm8Regs.TZCTL.bit.TZB                  = 3;          // TZ1 to TZ6 Trip Action On EPWM8B
       EPwm8Regs.TZCTL.bit.DCAEVT1              = 3;          // EPWM8A action on DCAEVT1
       EPwm8Regs.TZCTL.bit.DCAEVT2              = 3;          // EPWM8A action on DCAEVT2
       EPwm8Regs.TZCTL.bit.DCBEVT1              = 3;          // EPWM8B action on DCBEVT1
       EPwm8Regs.TZCTL.bit.DCBEVT2              = 3;          // EPWM8B action on DCBEVT2
     */
    EPwm8Regs.TZCTL.all = (EPwm8Regs.TZCTL.all & ~0xFFF) | 0xFFF;

    /*	// Trip Zone Enable Interrupt Register
       EPwm8Regs.TZEINT.bit.OST                 = 0;          // Trip Zones One Shot Int Enable
       EPwm8Regs.TZEINT.bit.CBC                 = 0;          // Trip Zones Cycle By Cycle Int Enable
       EPwm8Regs.TZEINT.bit.DCAEVT1             = 0;          // Digital Compare A Event 1 Int Enable
       EPwm8Regs.TZEINT.bit.DCAEVT2             = 0;          // Digital Compare A Event 2 Int Enable
       EPwm8Regs.TZEINT.bit.DCBEVT1             = 0;          // Digital Compare B Event 1 Int Enable
       EPwm8Regs.TZEINT.bit.DCBEVT2             = 0;          // Digital Compare B Event 2 Int Enable
     */
    EPwm8Regs.TZEINT.all = (EPwm8Regs.TZEINT.all & ~0x7E) | 0x0;

    /*	// Digital Compare A Control Register
       EPwm8Regs.DCACTL.bit.EVT1SYNCE           = 0;          // DCAEVT1 SYNC Enable
       EPwm8Regs.DCACTL.bit.EVT1SOCE            = 1;          // DCAEVT1 SOC Enable
       EPwm8Regs.DCACTL.bit.EVT1FRCSYNCSEL      = 0;          // DCAEVT1 Force Sync Signal
       EPwm8Regs.DCACTL.bit.EVT1SRCSEL          = 0;          // DCAEVT1 Source Signal
       EPwm8Regs.DCACTL.bit.EVT2FRCSYNCSEL      = 0;          // DCAEVT2 Force Sync Signal
       EPwm8Regs.DCACTL.bit.EVT2SRCSEL          = 0;          // DCAEVT2 Source Signal
     */
    EPwm8Regs.DCACTL.all = (EPwm8Regs.DCACTL.all & ~0x30F) | 0x4;

    /*	// Digital Compare B Control Register
       EPwm8Regs.DCBCTL.bit.EVT1SYNCE           = 0;          // DCBEVT1 SYNC Enable
       EPwm8Regs.DCBCTL.bit.EVT1SOCE            = 0;          // DCBEVT1 SOC Enable
       EPwm8Regs.DCBCTL.bit.EVT1FRCSYNCSEL      = 0;          // DCBEVT1 Force Sync Signal
       EPwm8Regs.DCBCTL.bit.EVT1SRCSEL          = 0;          // DCBEVT1 Source Signal
       EPwm8Regs.DCBCTL.bit.EVT2FRCSYNCSEL      = 0;          // DCBEVT2 Force Sync Signal
       EPwm8Regs.DCBCTL.bit.EVT2SRCSEL          = 0;          // DCBEVT2 Source Signal
     */
    EPwm8Regs.DCBCTL.all = (EPwm8Regs.DCBCTL.all & ~0x30F) | 0x0;

    /*	// Digital Compare Trip Select Register
       EPwm8Regs.DCTRIPSEL.bit.DCAHCOMPSEL      = 0;          // Digital Compare A High COMP Input Select

       EPwm8Regs.DCTRIPSEL.bit.DCALCOMPSEL      = 1;          // Digital Compare A Low COMP Input Select
       EPwm8Regs.DCTRIPSEL.bit.DCBHCOMPSEL      = 0;          // Digital Compare B High COMP Input Select
       EPwm8Regs.DCTRIPSEL.bit.DCBLCOMPSEL      = 1;          // Digital Compare B Low COMP Input Select
     */
    EPwm8Regs.DCTRIPSEL.all = (EPwm8Regs.DCTRIPSEL.all & ~ 0xFFFF) | 0x1010;

    /*	// Trip Zone Digital Comparator Select Register
       EPwm8Regs.TZDCSEL.bit.DCAEVT1            = 0;          // Digital Compare Output A Event 1
       EPwm8Regs.TZDCSEL.bit.DCAEVT2            = 0;          // Digital Compare Output A Event 2
       EPwm8Regs.TZDCSEL.bit.DCBEVT1            = 0;          // Digital Compare Output B Event 1
       EPwm8Regs.TZDCSEL.bit.DCBEVT2            = 0;          // Digital Compare Output B Event 2
     */
    EPwm8Regs.TZDCSEL.all = (EPwm8Regs.TZDCSEL.all & ~0xFFF) | 0x0;

    /*	// Digital Compare Filter Control Register
       EPwm8Regs.DCFCTL.bit.BLANKE              = 0;          // Blanking Enable/Disable
       EPwm8Regs.DCFCTL.bit.PULSESEL            = 1;          // Pulse Select for Blanking & Capture Alignment
       EPwm8Regs.DCFCTL.bit.BLANKINV            = 0;          // Blanking Window Inversion
       EPwm8Regs.DCFCTL.bit.SRCSEL              = 0;          // Filter Block Signal Source Select
     */
    EPwm8Regs.DCFCTL.all = (EPwm8Regs.DCFCTL.all & ~0x3F) | 0x10;
    EPwm8Regs.DCFOFFSET = 0;           // Digital Compare Filter Offset Register
    EPwm8Regs.DCFWINDOW = 0;           // Digital Compare Filter Window Register

    /*	// Digital Compare Capture Control Register
       EPwm8Regs.DCCAPCTL.bit.CAPE              = 0;          // Counter Capture Enable
     */
    EPwm8Regs.DCCAPCTL.all = (EPwm8Regs.DCCAPCTL.all & ~0x1) | 0x0;

    /*	// HRPWM Configuration Register
       EPwm8Regs.HRCNFG.bit.SWAPAB              = 0;          // Swap EPWMA and EPWMB Outputs Bit
       EPwm8Regs.HRCNFG.bit.SELOUTB             = 0;          // EPWMB Output Selection Bit
     */
    EPwm8Regs.HRCNFG.all = (EPwm8Regs.HRCNFG.all & ~0xA0) | 0x0;
    EDIS;
  }

  /* InitializeConditions for UnitDelay: '<S1>/Output' */
  SignalGen4_DW.Output_DSTATE = SignalGen4_P.Output_InitialCondition;
}

/* Model terminate function */
void SignalGen4_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
