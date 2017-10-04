/*
 * capture.c
 *
 *  Created on: 4 de set de 2017
 *      Author: skelter_win
 */
#include "project_includes/capture.h"

// Globals
int16_t ADCchannel[CHANNELS_COUNTER][SAMPLE_FRAME];     // ADC channels stored values
Outlet outlet[OUTLET_COUNTER];                          // Outlet structure values
Panel panel;                                            // Panel structure values
Msg msg[OUTLET_COUNTER];
//Msg *pMsg;
//Msg *gMsg;

// debug global variables
uint32_t eventCount=0;
uint32_t sendCount=0;

// Prototypes
static inline void copy_int16_f32(int16_t * pSrc, float32_t * pDst, uint32_t blockSize);
static inline void logOutlet(int16_t outletNum);
static inline void logPanel(void);


/*------------------------------------------------
 *              ADC0 Transfer Values
 *-----------------------------------------------*/
void adc0Ping_Swi(void)
{
    uint16_t i, j;
    // process first part of AIN0...AIN7
    for (i = 0, j = 0; i < SAMPLE_FRAME / 2; i++)
    {
        ADCchannel[CH0][i] = g_uint16_adc0_ping[j + AIN0];
        ADCchannel[CH1][i] = g_uint16_adc0_ping[j + AIN1];
        ADCchannel[CH2][i] = g_uint16_adc0_ping[j + AIN2];
        ADCchannel[CH3][i] = g_uint16_adc0_ping[j + AIN3];
        ADCchannel[CH4][i] = g_uint16_adc0_ping[j + AIN4];
        ADCchannel[CH5][i] = g_uint16_adc0_ping[j + AIN5];
        ADCchannel[CH6][i] = g_uint16_adc0_ping[j + AIN6];
        ADCchannel[CH7][i] = g_uint16_adc0_ping[j + AIN7];
        j += AIN_OFFSET;
    }
}

void adc0Pong_Swi(void)
{
    uint16_t i, j;
    // process last part of AIN0...AIN7
    for (i = 128, j = 0; i < SAMPLE_FRAME; i++)
    {
        ADCchannel[CH0][i] =  g_uint16_adc0_pong[j + AIN0];
        ADCchannel[CH1][i] =  g_uint16_adc0_pong[j + AIN1];
        ADCchannel[CH2][i] =  g_uint16_adc0_pong[j + AIN2];
        ADCchannel[CH3][i] =  g_uint16_adc0_pong[j + AIN3];
        ADCchannel[CH4][i] =  g_uint16_adc0_pong[j + AIN4];
        ADCchannel[CH5][i] =  g_uint16_adc0_pong[j + AIN5];
        ADCchannel[CH6][i] =  g_uint16_adc0_pong[j + AIN6];
        ADCchannel[CH7][i] =  g_uint16_adc0_pong[j + AIN7];
        j += AIN_OFFSET;
    }
    // post event ADC0 data ready
    Event_post(e_adcData_Ready, Event_Id_00);
}


/*------------------------------------------------
 *              ADC1 Transfer Values
 *----------------------------------------------*/
void adc1Ping_Swi(void)
{
    uint16_t i, j;
    // process first part of AIN8...AIN12
    for (i = 0, j = 0; i < SAMPLE_FRAME / 2; i++)
    {
        ADCchannel[CH8][i] = g_uint16_adc1_ping[j + AIN8];
        ADCchannel[CH9][i] = g_uint16_adc1_ping[j + AIN9];
        ADCchannel[CH10][i] = g_uint16_adc1_ping[j + AIN10];
        ADCchannel[CH11][i] = g_uint16_adc1_ping[j + AIN11];
        ADCchannel[CH12][i] = g_uint16_adc1_ping[j + AIN12];
        ADCchannel[CH13][i] = g_uint16_adc1_ping[j + AIN13];
        ADCchannel[CH14][i] = g_uint16_adc1_ping[j + AIN14];
        ADCchannel[CH15][i] = g_uint16_adc1_ping[j + AIN15];

        j += AIN_OFFSET;
    }
}

void adc1Pong_Swi(void)
{
    uint16_t i, j;
    // process last part of AIN8...AIN12
    for (i = 128, j = 0; i < SAMPLE_FRAME; i++)
    {
        ADCchannel[CH8][i] = g_uint16_adc1_pong[j + AIN8];
        ADCchannel[CH9][i] = g_uint16_adc1_pong[j + AIN9];
        ADCchannel[CH10][i] = g_uint16_adc1_pong[j + AIN10];
        ADCchannel[CH11][i] = g_uint16_adc1_pong[j + AIN11];
        ADCchannel[CH12][i] = g_uint16_adc1_pong[j + AIN12];
        ADCchannel[CH13][i] = g_uint16_adc1_pong[j + AIN13];
        ADCchannel[CH14][i] = g_uint16_adc1_pong[j + AIN14];
        ADCchannel[CH15][i] = g_uint16_adc1_pong[j + AIN15];

        j += AIN_OFFSET;
    }
    // post event ADC1 data ready
    Event_post(e_adcData_Ready, Event_Id_01);//Semaphore_post(s_adc1_data_ready);
}



/**
 *              Data Process Task
 * Task created static (see RTOS_config.cfg). Process data
 * from DMA buffers and calculate rms value for AIN0...AIN15
 *
 */
void dataProcess_Task(void)
{

    uint16_t i;
    float32_t tempSamples[SAMPLE_FRAME];
    float32_t meanValue;
    float32_t tempRms;

    while (1)
    {
        // wait adc0 and adc1 data being transferred from DMA
        Event_pend(e_adcData_Ready,(Event_Id_00+Event_Id_01),Event_Id_NONE,BIOS_WAIT_FOREVER);

        Log_write1(UIABenchmark_start,(xdc_IArg)"Process Data Task");
        GPIO_write(DEBUG_PIN_CAPTURE, 1); // hardware debug pin on

        /* process outlets */
        for(i=CH0;i<OUTLET_COUNTER;i++) // 12 channels: 6 phase current and 6 differential current
        {
            // phase current
            // copy specific analog channel vector
            copy_int16_f32(ADCchannel[i*2],tempSamples, SAMPLE_FRAME);
            // Get mean value
            arm_mean_f32(tempSamples, SAMPLE_FRAME, &meanValue);
            // ADC offset
            arm_offset_f32(tempSamples, -meanValue ,tempSamples, SAMPLE_FRAME);
            // ADC scale
            arm_scale_f32(tempSamples, ptgmSettings.channel[i*2].channel_gain , tempSamples, SAMPLE_FRAME);
            // calculate RMS
            arm_rms_f32(tempSamples, SAMPLE_FRAME, &tempRms);
            // copy to outlet
            outlet[i].phaseRms = tempRms;

            // diff current
            // copy specific analog channel vector
            copy_int16_f32(ADCchannel[(i*2)+1],tempSamples, SAMPLE_FRAME);
            // Get mean value
            arm_mean_f32(tempSamples, SAMPLE_FRAME, &meanValue);
            // ADC offset
            arm_offset_f32(tempSamples, -meanValue , tempSamples, SAMPLE_FRAME);
            // ADC scale
            arm_scale_f32(tempSamples, ptgmSettings.channel[(i*2)+1].channel_gain , tempSamples, SAMPLE_FRAME);
            // calculate RMS
            arm_rms_f32(tempSamples, SAMPLE_FRAME, &tempRms);
            // copy to outlet
            outlet[i].diffRms = tempRms;
        }

        /* Process Panel  */
        for(i=CH12;i<CH15;i++) // 3 channels: 2 voltages and 1 earth leakage sensor
        {
            // copy specific analog channel vector
            copy_int16_f32(ADCchannel[i],tempSamples, SAMPLE_FRAME);
            // Get mean value
            arm_mean_f32(tempSamples, SAMPLE_FRAME, &meanValue);
            // ADC offset
            arm_offset_f32(tempSamples, -meanValue , tempSamples, SAMPLE_FRAME);
            // ADC scale TODO: see correct value for channel gain
            arm_scale_f32(tempSamples, ptgmSettings.channel[i].channel_gain , tempSamples, SAMPLE_FRAME);
            // calculate RMS
            arm_rms_f32(tempSamples, SAMPLE_FRAME, &tempRms);
            // copy to specific outlet variable
            if(i==CH12)         // copy to panel voltage1
                panel.voltage1Rms = tempRms;
            else if(i==CH13)    // copy to panel voltage2
                panel.voltage2Rms = tempRms;
            else                // copy to panel earth leakage
                panel.eathLeakageRms = tempRms;

        }
     GPIO_write(DEBUG_PIN_CAPTURE, 0); // hardware debug pin off
     Log_write1(UIABenchmark_stop,(xdc_IArg)"Process Data Task");

     // all done, do event analysis
     Semaphore_post(s_doEventAnalysis);
    }

}

/**
 *            Event Analysis Task
 * Task created static (see RTOS_config.cfg).
 * Look for On, Off, Leakage begin and end.
 *
 */
void eventAnalysis_Task(void)
{
    uint16_t outletNum, j;

    // set detect limits
    for (outletNum = 0, j = 0; outletNum < OUTLET_COUNTER; outletNum++, j += 2)
    {
        outlet[outletNum].num = outletNum + 1;
        outlet[outletNum].limitPhase = ptgmSettings.channel[j].channel_limit;
        outlet[outletNum].limitDiff = ptgmSettings.channel[j + 1].channel_limit;
        outlet[outletNum].logCounter = 0;
        outlet[outletNum].event = OFF;
        outlet[outletNum].logPutPhase = &outlet[outletNum].logPhase[0];
        outlet[outletNum].logPutDiff = &outlet[outletNum].logDiff[0];
        outlet[outletNum].logGetPhase = &outlet[outletNum].logPhase[6*MERGE_LOG_BLOCK];
        outlet[outletNum].logGetDiff = &outlet[outletNum].logDiff[6*MERGE_LOG_BLOCK];
        outlet[outletNum].logGetVoltage1 = &panel.logVoltage1[11*MERGE_LOG_BLOCK];
        outlet[outletNum].logGetVoltage2 = &panel.logVoltage2[11*MERGE_LOG_BLOCK];
        outlet[outletNum].logGetLeakage = &panel.logEarthLeakage[11*MERGE_LOG_BLOCK];
    }

    // Panel init
    panel.logPutVoltage1 = &panel.logVoltage1[0];
    panel.logPutVoltage2 = &panel.logVoltage2[0];
    panel.logPutLeakage = &panel.logEarthLeakage[0];


    // message init
//    pMsg = &msg[0];
//    gMsg = pMsg;

    while (1)
    {
        // wait until data is being processed, unblocked by dataProcess_Task
        Semaphore_pend(s_doEventAnalysis, BIOS_WAIT_FOREVER);
        Log_write1(UIABenchmark_start,(xdc_IArg)"Event Analisys Task");
        //log panel values
        logPanel();
        // scan all outlets
        for (outletNum = 0; outletNum < OUTLET_COUNTER; outletNum++)
        {

            switch (outlet[outletNum].event)
            {
            case OFF:   // Equipment is off, looking for turns on events
            {
                if (outlet[outletNum].phaseRms > outlet[outletNum].limitPhase) // turned on?
                {
                    // change actual state to turns on
                    outlet[outletNum].event = TURNS_ON;
                }
                break;
            }
            case ON:    // Equipment is on, looking for turns off events
            {
                if (outlet[outletNum].phaseRms < (outlet[outletNum].limitPhase)) // turned off?
                {
                    // change actual state to turns off
                    outlet[outletNum].event = TURNS_OFF;
                }
                else
                    logOutlet(outletNum); // keep logging until turns off
                    break;
            }
            }

            // processes ON and OFF events
            if (outlet[outletNum].event == TURNS_ON)//if(setOn) // if(outletNum==1) // if(setOn)//if (outlet[outletNum].event == TURNS_ON)
            {
                // start to log
                logOutlet(outletNum);
                // increment log counter
                outlet[outletNum].logCounter++;
            }
            else if (outlet[outletNum].event == TURNS_OFF)
            {
                //Send data TURNS_OFF event

            }

            // finalize log process
            if (outlet[outletNum].logCounter > MAX_WAVE_LOG)
            {
                // if still on after 10 log events, send logged data, else discard.
                if (outlet[outletNum].phaseRms > outlet[outletNum].limitPhase)
                {
                    // change state to ON
                    outlet[outletNum].event = ON;
                    //Send data TURNS_OFF event
//                    msg[outletNum].header[0]=0x00;
//                    msg[outletNum].header[1]=outlet[outletNum].num;
//                    msg[outletNum].header[2]=outlet[outletNum].event;
//                    msg[outletNum].phase = outlet[outletNum].logGetPhase;
//                    msg[outletNum].diff = outlet[outletNum].logGetDiff;
//                    msg[outletNum].voltage = outlet[outletNum].logGetVoltage1;
//                    msg[outletNum].leakage = outlet[outletNum].logGetLeakage;
//                    pMsg->header[0]=0x00;
//                    pMsg->header[0]=outlet[outletNum].num;
//                    pMsg->header[2]=outlet[outletNum].event;
//                    pMsg->phase = outlet[outletNum].logGetPhase;
//                    pMsg->diff = outlet[outletNum].logGetDiff;
//                    pMsg->voltage = outlet[outletNum].logGetVoltage1;
//                    pMsg->leakage = outlet[outletNum].logGetLeakage;
//                    if(++pMsg > (void *)OUTLET_COUNTER)
//                        pMsg = &msg[0];
//                    Semaphore_post(s_doDataSendTcpIp);
                    sendCount++;
                }
                else
                {
                    outlet[outletNum].event = OFF;
                }
                //reset log counter
                outlet[outletNum].logCounter = 0;
            }

        }
        Log_write1(UIABenchmark_stop,(xdc_IArg)"Event Analisys Task");
    }

}

/*
 *    Outlet circular buffer write
 */
static inline void logOutlet(int16_t outletNum)
{
    int16_t j;

    // write phase circular buffer
    for(j=0;j<SAMPLE_FRAME;j+=2)
    {
        // phase current samples merge
        *outlet[outletNum].logPutPhase++ = ADCchannel[(outletNum * 2)][j] >> 4;
        *outlet[outletNum].logPutPhase = ADCchannel[(outletNum * 2)][j]<<4;
        *outlet[outletNum].logPutPhase++ |= ADCchannel[(outletNum * 2)][j+1]>>8;
        *outlet[outletNum].logPutPhase++ = ADCchannel[(outletNum * 2)][j+1];

        // diff current samples merge
        *outlet[outletNum].logPutDiff++ = ADCchannel[(outletNum * 2)+1][j] >> 4;
        *outlet[outletNum].logPutDiff = ADCchannel[(outletNum * 2)+1][j]<<4;
        *outlet[outletNum].logPutDiff++ |= ADCchannel[(outletNum * 2)+1][j+1]>>8;
        *outlet[outletNum].logPutDiff++ = ADCchannel[(outletNum * 2)+1][j+1];

    }
    // increment or reset circular phase buffer
    if (outlet[outletNum].logPutPhase >= &outlet[outletNum].logPhase[LOG_BUFFER_SIZE])
    {
        outlet[outletNum].logPutPhase = &outlet[outletNum].logPhase[0];
        outlet[outletNum].logGetPhase = &outlet[outletNum].logPhase[6*MERGE_LOG_BLOCK];
    }
    else
    {
        outlet[outletNum].logGetPhase += MERGE_LOG_BLOCK;
    }

    // increment or reset circular diff buffer
    if (outlet[outletNum].logPutDiff >= &outlet[outletNum].logDiff[LOG_BUFFER_SIZE])
    {
        outlet[outletNum].logPutDiff = &outlet[outletNum].logDiff[0];
        outlet[outletNum].logGetDiff = &outlet[outletNum].logDiff[6*MERGE_LOG_BLOCK];
    }
    else
    {
        //*outlet[outletNum].logPutDiff += MERGE_LOG_BLOCK;
        outlet[outletNum].logGetDiff += MERGE_LOG_BLOCK;
    }

    // increment or reset circular voltage 1 buffer
    if (panel.logPutVoltage1 >= &panel.logVoltage1[LOG_BUFFER_SIZE_PANEL ])
    {
       outlet[outletNum].logGetVoltage1 = &panel.logVoltage1[11*MERGE_LOG_BLOCK];
    }
    else
    {
       outlet[outletNum].logGetVoltage1 += MERGE_LOG_BLOCK;
    }

    // increment or reset circular voltage 2 buffer
    if (panel.logPutVoltage2 >= &panel.logVoltage2[LOG_BUFFER_SIZE_PANEL ])
    {
       outlet[outletNum].logGetVoltage2 = &panel.logVoltage2[11*MERGE_LOG_BLOCK];
    }
    else
    {
       outlet[outletNum].logGetVoltage2 += MERGE_LOG_BLOCK;
    }

    // increment or reset circular earth leakage buffer
    if (panel.logPutLeakage >= &panel.logEarthLeakage[LOG_BUFFER_SIZE_PANEL ])
    {
       outlet[outletNum].logGetLeakage = &panel.logEarthLeakage[11*MERGE_LOG_BLOCK];
    }
    else
    {
       outlet[outletNum].logGetLeakage += MERGE_LOG_BLOCK;
    }
}

/**
 *    Panel circular buffer write
 */
static inline void logPanel(void)
{
    int16_t j;

    // write phase circular buffer
    for(j=0;j<SAMPLE_FRAME;j+=2)
    {
        // voltage1 samples merge
        *panel.logPutVoltage1++ = ADCchannel[CH12][j] >> 4;
        *panel.logPutVoltage1 = ADCchannel[CH12][j]<<4;
        *panel.logPutVoltage1++ |= ADCchannel[CH12][j+1]>>8;
        *panel.logPutVoltage1++ = ADCchannel[CH12][j+1];

        // voltage2 samples merge
        *panel.logPutVoltage2++ = ADCchannel[CH13][j] >> 4;
        *panel.logPutVoltage2 = ADCchannel[CH13][j]<<4;
        *panel.logPutVoltage2++ |= ADCchannel[CH13][j+1]>>8;
        *panel.logPutVoltage2++ = ADCchannel[CH13][j+1];

        // earth leakage samples merge
        *panel.logPutLeakage++ = ADCchannel[CH14][j] >> 4;
        *panel.logPutLeakage = ADCchannel[CH14][j]<<4;
        *panel.logPutLeakage++ |= ADCchannel[CH14][j+1]>>8;
        *panel.logPutLeakage++ = ADCchannel[CH14][j+1];
    }

    // reset circular voltage 1 buffer
    if (panel.logPutVoltage1 >= &panel.logVoltage1[LOG_BUFFER_SIZE_PANEL ])
    {
       panel.logPutVoltage1 = &panel.logVoltage1[0];
    }

    // reset circular voltage 2 buffer
    if (panel.logPutVoltage2 >= &panel.logVoltage2[LOG_BUFFER_SIZE_PANEL ])
    {
       panel.logPutVoltage2 = &panel.logVoltage2[0];
    }

    // reset circular earth leakage buffer
    if (panel.logPutLeakage >= &panel.logEarthLeakage[LOG_BUFFER_SIZE_PANEL ])
    {
       panel.logPutLeakage = &panel.logEarthLeakage[0];
    }
}

/**
 *    Vector copy function
 */
static inline void copy_int16_f32( int16_t * pSrc, float32_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;
  float32_t in1, in2, in3, in4;

  // divide by four, each loop writes four blocks
  blkCnt = blockSize >> 2u;

  while(blkCnt > 0u)
  {
    in1 = (float32_t)*pSrc++;
    in2 = (float32_t)*pSrc++;
    in3 = (float32_t)*pSrc++;
    in4 = (float32_t)*pSrc++;

    *pDst++ = in1;
    *pDst++ = in2;
    *pDst++ = in3;
    *pDst++ = in4;

    blkCnt--;
  }

  // If the blockSize is not a multiple of 4, compute any remaining output samples here.
  blkCnt = blockSize % 0x4u;

  while(blkCnt > 0u)
  {
    *pDst++ = *pSrc++;

    blkCnt--;
  }
}
