/*
 * settings.c
 *
 *  Created on: 4 de set de 2017
 *      Author: skelter_win
 */
#include "project_includes/settings.h"

// uncoment line bellow to reset all settings
//#define STANDARD_SETTINGS

#define EEPROM_START_ADR 0x0000


struct PtgmSettings ptgmSettingsWrite =
{
    NUM_OF_ADC_CHANNELS,    // channels=6
    256,                    // samples=256
    "192.168.2.106",        // networkServer=192.168.1.10
    "192.168.2.110",        // networkAddress=192.168.1.241
    "255.255.255.0",        // networkMask=255.255.255.0
    "192.168.2.1",          // networkGateway=192.168.1.1
    0,                      // networkDhcp=false
    0,                      // syncTimeZone=false
    -3,                     // networkTimeZone=-3
    1,//rfidRead=true
    8,//moduleNumber=8
    12,//maxHarmonics=12
    10,//eventLimit=10
    10,//mboxLenght=10
    500,//delayTry=500
    50,//delaySend=50
    1,//logEnabled=true
    1,//logMarks=true
    600,//logMarksInterval=600
    90,//logLevel=90
    (3.3/4095), //channel0_gain=123.9107
    2048,       //channel0_offset=2085
    0.5,        //channel0_limit=0.1
    'p',        //channel0_purpose=p
    (3.3/4095), //channel1_gain=1154.7621
    2048,       //channel1_offset=2063
    0.25,        //channel1_limit=0.1
    'd',        //channel1_purpose=d
    (3.3/4095), //channel2_gain=123.9107
    2048,       //channel2_offset=2085
    0.7,        //channel2_limit=0.1
    'p',        //channel2_purpose=p
    (3.3/4095), //channel3_gain=1154.7621
    2048,       //channel3_offset=2063
    0.71,        //channel3_limit=0.1
    'd',        //channel3_purpose=d
    (3.3/4095), //channel4_gain=123.9107
    2048,       //channel4_offset=2085
    1.5,        //channel4_limit=0.1
    'p',        //channel4_purpose=p
    (3.3/4095), //channel5_gain=1154.7621
    2048,       //channel5_offset=2063
    1.5,        //channel5_limit=0.1
    'd',        //channel5_purpose=d
    (3.3/4095), //channel6_gain=123.9107
    2048,       //channel6_offset=2085
    1.5,        //channel6_limit=0.1
    'p',        //channel6_purpose=p
    (3.3/4095), //channel7_gain=1154.7621
    2048,       //channel7_offset=2063
    1.5,        //channel7_limit=0.1
    'd',        //channel7_purpose=d
    (3.3/4095), //channel8_gain=123.9107
    2048,       //channel8_offset=2085
    1.5,        //channel8_limit=0.1
    'p',        //channel8_purpose=p
    (3.3/4095), //channel9_gain=1154.7621
    2048,       //channel9_offset=2063
    1.5,        //channel9_limit=0.1
    'd',        //channel9_purpose=d
    (3.3/4095), //channel10_gain=123.9107
    2048,       //channel10_offset=2085
    1.5,        //channel10_limit=0.1
    'p',        //channel10_purpose=p
    (3.3/4095), //channel11_gain=1154.7621
    2048,       //channel11_offset=2063
    1.5,        //channel11_limit=0.1
    'd',        //channel11_purpose=d
    (3.3/4095), //channel12_gain=123.9107
    2048,       //channel12_offset=2085
    1.5,        //channel12_limit=0.1
    'p',        //channel12_purpose=p
    (3.3/4095), //channel13_gain=1154.7621
    2048,       //channel13_offset=2063
    1.5,        //channel13_limit=0.1
    'd',        //channel13_purpose=d
    (3.3/4095), //channel14_gain=123.9107
    2048,       //channel14_offset=2085
    1.5,        //channel14_limit=0.1
    'p',        //channel14_purpose=p
    (3.3/4095), //channel15_gain=1154.7621
    2048,       //channel15_offset=2063
    1.5,        //channel15_limit=0.1
    'd',        //channel15_purpose=d
    1,//outlet0=7
    2,//outlet1=8
    3,//outlet2=9
    4,//
    5,//
    6 //
}; /* Write struct */

struct PtgmSettings ptgmSettings =
{
    0,   //channels=6
    0,//samples=256
    "",//networkServer=192.168.1.10
    "",//networkAddress=192.168.1.241
    "",//networkMask=255.255.255.0
    "",//networkGateway=192.168.1.1
    0,//networkDhcp=false
    0,//syncTimeZone=false
    0,//networkTimeZone=-3
    0,//rfidRead=true
    0,//moduleNumber=8
    0,//maxHarmonics=12
    0,//eventLimit=10
    0,//mboxLenght=10
    0,//delayTry=500
    0,//delaySend=50
    0,//logEnabled=true
    0,//logMarks=true
    0,//logMarksInterval=600
    0,//logLevel=90
    0,//channel0_gain=123.9107
    0,//channel0_offset=2085
    0,//channel0_limit=0.1
    0,//channel0_purpose=p
    0,//channel1_gain=1154.7621
    0,//channel1_offset=2063
    0,//channel1_limit=0.1
    0,//channel1_purpose=d
    0,//channel0_gain=123.9107
    0,//channel0_offset=2085
    0,//channel0_limit=0.1
    0,//channel0_purpose=p
    0,//channel1_gain=1154.7621
    0,//channel1_offset=2063
    0,//channel1_limit=0.1
    0,//channel1_purpose=d
    0,//channel0_gain=123.9107
    0,//channel0_offset=2085
    0,//channel0_limit=0.1
    0,//channel0_purpose=p
    0,//channel1_gain=1154.7621
    0,//channel1_offset=2063
    0,//channel1_limit=0.1
    0,//channel1_purpose=d
    0,//channel0_gain=123.9107
    0,//channel0_offset=2085
    0,//channel0_limit=0.1
    0,//channel0_purpose=p
    0,//channel1_gain=1154.7621
    0,//channel1_offset=2063
    0,//channel1_limit=0.1
    0,//channel1_purpose=d
    0,//channel0_gain=123.9107
    0,//channel0_offset=2085
    0,//channel0_limit=0.1
    0,//channel0_purpose=p
    0,//channel1_gain=1154.7621
    0,//channel1_offset=2063
    0,//channel1_limit=0.1
    0,//channel1_purpose=d
    0,//channel0_gain=123.9107
    0,//channel0_offset=2085
    0,//channel0_limit=0.1
    0,//channel0_purpose=p
    0,//channel1_gain=1154.7621
    0,//channel1_offset=2063
    0,//channel1_limit=0.1
    0,//channel1_purpose=d
    0,//channel0_gain=123.9107
    0,//channel0_offset=2085
    0,//channel0_limit=0.1
    0,//channel0_purpose=p
    0,//channel1_gain=1154.7621
    0,//channel1_offset=2063
    0,//channel1_limit=0.1
    0,//channel1_purpose=d
    0,//channel0_gain=123.9107
    0,//channel0_offset=2085
    0,//channel0_limit=0.1
    0,//channel0_purpose=p
    0,//channel1_gain=1154.7621
    0,//channel1_offset=2063
    0,//channel1_limit=0.1
    0,//channel1_purpose=d
    0,//outlet0=7
    0,//outlet1=8
    0,//outlet2=9
    0,//
    0,//
    0//
}; /* Read struct */

void readPtgmSettings(void)
{

    /* EEPROM SETTINGS */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0); // EEPROM activate
    while(EEPROMInit()!=EEPROM_INIT_OK); // EEPROM start TODO: Verify return code

#ifdef STANDARD_SETTINGS
    //Write struct to EEPROM start from 0x0000
    EEPROMProgram((uint32_t *) &ptgmSettingsWrite, EEPROM_START_ADR,
                  sizeof(ptgmSettingsWrite));
#endif

    //Read from struct at EEPROM start from 0x0000
    EEPROMRead((uint32_t *) &ptgmSettings, EEPROM_START_ADR,
               sizeof(ptgmSettings));

    Log_info0("ptgmSettings loaded.");
}
