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

#define MAX_WAVE_LOG 10
#define MAX_HARMONIC 12
#define MSG_BUFFER 4800
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
    uint8_t logCounter;
    float32_t *phaseWave;
    float32_t *diffWave;
    float32_t *voltageWave;
    //float32_t phaseFFT[SAMPLE_FRAME];
    //float32_t diffFFT[SAMPLE_FRAME];
    float32_t phaseRMS;
    float32_t diffRMS;
    float32_t *voltageFFT;
    float32_t *voltageRMS;
    float32_t limitPhase;
    float32_t limitDiff;
    float32_t limitVoltage;
}Outlet;

typedef struct{
    float32_t *voltageWave1;
    float32_t *voltageWave2;
    float32_t *earthLeakageWave;
    //float32_t voltageFFT1[SAMPLE_FRAME];
    //float32_t voltageFFT2[SAMPLE_FRAME];
    //float32_t earthLeakageFFT[SAMPLE_FRAME];
    float32_t voltage1RMS;
    float32_t voltage2RMS;
    float32_t eathLeakageRMS;
}Panel;

typedef struct{
    uint8_t put;
    uint8_t get;
    uint16_t index;
    char buffer[MSG_BUFFER];
}Msg;

//typedef struct{
//    uint8_t outletNum;
//    uint8_t outletEvent;
//    uint8_t sendFlag;
//    float32_t phaseRMS[MAX_WAVE_LOG];
//    float32_t diffRMS[MAX_WAVE_LOG];
//    float32_t voltageRMS[MAX_WAVE_LOG];
//    float32_t phaseFFT[2*MAX_HARMONIC*MAX_WAVE_LOG];
//    float32_t diffFFT[2*MAX_HARMONIC*MAX_WAVE_LOG];
//    float32_t voltageFFT[2*MAX_HARMONIC*MAX_WAVE_LOG];
//}OutletMsg;
//
//
//typedef struct{
//    uint16_t put;
//    uint16_t get;
//    OutletMsg buffer[MAX_MSG_BUFFER];
//}MsgBuffer;

extern char g_str_PostSend[];

extern char temp[4800];
#endif /* PROJECT_INCLUDES_CAPTURE_H_ */
