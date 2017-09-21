/*
 * capture.h
 *
 *  Created on: 4 de set de 2017
 *      Author: skelter_win
 */

#ifndef PROJECT_INCLUDES_CAPTURE_H_
#define PROJECT_INCLUDES_CAPTURE_H_

/* Standard variables definitions */
#include <stdint.h>
#include <stdbool.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>   // to use Log_Info
#include <xdc/cfg/global.h> // to get static definitions from RTOS.cfg file


/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/uia/events/UIABenchmark.h>

/* Project Header files */
#include "project_includes/Board.h"
#include "project_includes/settings.h"
#include "project_includes/adc_sample.h"
#include "project_includes/eth_network.h"

/* ARM Math CMSIS DSP */
#include <arm_math.h>

/* Strings functions */
#include <string.h>
#include <stdio.h>

/* TM4C tivaware RTOS lib */
#include <ti/drivers/GPIO.h>

/* Project Header files */
#include "project_includes/Board.h"

enum analogInputsADC0
{
    AIN0, AIN1, AIN2, AIN3, AIN4, AIN5, AIN6, AIN7, AIN_OFFSET
};

enum analogInputsADC1
{
    AIN8, AIN9, AIN10, AIN11, AIN12, AIN13, AIN14, AIN15
};

enum analogChannels
{
    CH0, CH1, CH2,  CH3,  CH4,  CH5,  CH6,  CH7,
    CH8, CH9, CH10, CH11, CH12, CH13, CH14, CH15,
    CHANNELS_COUNTER
};

enum outletNumber
{
    OUTLET_1, OUTLET_2, OUTLET_3, OUTLET_4, OUTLET_5, OUTLET_6, OUTLET_COUNTER
};

typedef struct{
    float32_t phaseWave[SAMPLE_FRAME];
    float32_t diffWave[SAMPLE_FRAME];
    uint32_t id;
    float32_t phaseRMS;
    float32_t diffRMS;
    float32_t voltageRMS;
    uint8_t limitCounterPhase;
    uint8_t limitCounterDiff;
    float32_t phaseFFT[SAMPLE_FRAME];
    float32_t diffFFT[SAMPLE_FRAME];
    float32_t voltageFFT[SAMPLE_FRAME];
    float32_t limitPhase;
    float32_t limitDiff;
}Outlet;

extern float32_t harmonics[];

#endif /* PROJECT_INCLUDES_CAPTURE_H_ */
