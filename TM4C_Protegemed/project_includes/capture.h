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

/* TM4C tivaware lib */
#include <ti/drivers/GPIO.h>

/* Project Header files */
#include "project_includes/Board.h"

typedef struct{
    float32_t phaseWave[SAMPLE_FRAME];
    float32_t diffWave[SAMPLE_FRAME];
    uint32_t id;
    float32_t phaseRMS;
    float32_t diffRMS;
    float32_t voltageRMS;
    uint8_t limitCounterPhase;
    uint8_t limitCounterDiff;
    float32_t *phaseFFT;
    float32_t *diffFFT;
    float32_t *voltageFFT;
    float32_t limitPhase;
    float32_t limitDiff;
}Outlet;

extern float32_t harmonics[];

#endif /* PROJECT_INCLUDES_CAPTURE_H_ */
