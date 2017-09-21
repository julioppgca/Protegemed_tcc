/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B06
 */

#include <xdc/std.h>

#include <ti/sysbios/family/arm/m3/Hwi.h>
extern const ti_sysbios_family_arm_m3_Hwi_Handle ADC_Seq0_ISR_Handle;

#include <ti/sysbios/family/arm/m3/Hwi.h>
extern const ti_sysbios_family_arm_m3_Hwi_Handle ADC_Seq1_ISR_Handle;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle initSamplesTask_Handle;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle capture_Task_Handle;

#include <ti/sysbios/knl/Event.h>
extern const ti_sysbios_knl_Event_Handle e_adcData_Ready;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle heartBeat_Task_Handle;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle s_critical_section;

#include <ti/sysbios/knl/Swi.h>
extern const ti_sysbios_knl_Swi_Handle adc0Ping_Swi_Handle;

#include <ti/sysbios/knl/Swi.h>
extern const ti_sysbios_knl_Swi_Handle adc0Pong_Swi_Handle;

#include <ti/sysbios/knl/Swi.h>
extern const ti_sysbios_knl_Swi_Handle adc1Ping_Swi_Handle;

#include <ti/sysbios/knl/Swi.h>
extern const ti_sysbios_knl_Swi_Handle adc1Pong_Swi_Handle;

extern int xdc_runtime_Startup__EXECFXN__C;

extern int xdc_runtime_Startup__RESETFXN__C;

