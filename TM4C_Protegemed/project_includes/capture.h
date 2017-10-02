/*
 * capture.h
 *
 *  Created on: 4 de set de 2017
 *      Author: skelter_win
 */

#ifndef PROJECT_INCLUDES_CAPTURE_H_
#define PROJECT_INCLUDES_CAPTURE_H_

/* Inline force functions */
#pragma FUNC_ALWAYS_INLINE(copy_int16_f32)
#pragma FUNC_ALWAYS_INLINE(logOutlet)

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

#define MAX_WAVE_LOG 10
#define MAX_HARMONIC 12
#define MSG_BUFFER 4800
#define LOG_BUFFER_SIZE 2560 //10*256 or to bytes: 3840 with merge, 5120 without merge
#define MAX_MSG_LOG_PER_OUTLET  2

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

enum events
{
   OFF, TURNS_ON, TURNS_OFF, ON, STAND_BY, OVER_VOLTAGE, UNDER_VOLTAGE, START_DIFF_LEAKAGE, STOP_DIFF_LEAKAGE, EVENT_COUNT
};

enum outletNumber
{
    OUTLET_1, OUTLET_2, OUTLET_3, OUTLET_4, OUTLET_5, OUTLET_6, OUTLET_COUNTER
};

typedef struct{
    uint8_t num;
    uint8_t event;
    float32_t phaseRms;
    float32_t diffRms;
    float32_t limitPhase;
    float32_t limitDiff;
    int16_t logPhase[LOG_BUFFER_SIZE];
    int16_t logDiff[LOG_BUFFER_SIZE];
//    int16_t logVoltage[LOG_BUFFER_SIZE];
//    int16_t logEarthLeakage[LOG_BUFFER_SIZE];
    uint8_t logCounter;
    int16_t *logPutPhase;
    int16_t *logPutDiff;
//    int16_t *logPutVoltage;
//    int16_t *logPutLeakage;
    int16_t *logGetPhase;
    int16_t *logGetDiff;
    int16_t *logGetVoltage;
    int16_t *logGetLeakage;
}Outlet;

typedef struct{
    float32_t voltage1Rms;
    float32_t voltage2Rms;
    float32_t eathLeakageRms;
    int16_t logVoltage1[LOG_BUFFER_SIZE];
    int16_t logVoltage2[LOG_BUFFER_SIZE];
    int16_t logEarthLeakage[LOG_BUFFER_SIZE];
    int16_t *logPutVoltage1;
    int16_t *logPutVoltage2;
    int16_t *logPutLeakage;
}Panel;

static inline void copy_int16_f32( int16_t * pSrc, float32_t * pDst, uint32_t blockSize);
static inline void logOutlet(int16_t outletNum);

#endif /* PROJECT_INCLUDES_CAPTURE_H_ */
