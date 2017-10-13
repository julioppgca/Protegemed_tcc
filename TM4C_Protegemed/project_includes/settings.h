/*
 * settings.h
 *
 *  Created on: 4 de set de 2017
 *      Author: skelter_win
 */

#ifndef PROJECT_INCLUDES_SETTINGS_H_
#define PROJECT_INCLUDES_SETTINGS_H_

#include <stdint.h>
#include <stdbool.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>   // to use Log_Info
#include <xdc/cfg/global.h> // to get static definitions from RTOS.cfg file

/* Driverlib Header files */
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/eeprom.h"

/* Project Header files */
#include "project_includes/eth_network.h"

#define NUM_OF_ADC_CHANNELS     16

typedef struct
{
    float       channel_gain;
    uint16_t    channel_offset;
    float       channel_limit;
    uint8_t     channel_purpose;
} channelSettings;

struct PtgmSettings
{
    uint8_t channels;
    uint16_t samples;
    uint8_t networkServer[15];
    uint8_t networkAddress[15];
    uint8_t networkMask[15];
    uint8_t networkGateway[15];
    uint8_t networkDhcp;
    uint8_t syncTimeZone;
    int8_t networkTimeZone;
    uint8_t rfidRead;
    uint16_t moduleNumber;
    uint8_t maxHarmonics;
    uint8_t eventLimit;
    uint8_t mboxLenght;
    uint16_t delayTry;
    uint16_t delaySend;
    uint8_t logEnabled;
    uint8_t logMarks;
    uint16_t logMarksInterval;
    uint16_t logLevel;
    channelSettings channel[NUM_OF_ADC_CHANNELS];
    uint16_t outlet[6];
};

extern struct PtgmSettings ptgmSettingsWrite;
extern struct PtgmSettings ptgmSettings;

void readPtgmSettings(void);

#endif /* PROJECT_INCLUDES_SETTINGS_H_ */
