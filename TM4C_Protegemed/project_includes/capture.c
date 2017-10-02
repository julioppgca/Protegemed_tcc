/*
 * capture.c
 *
 *  Created on: 4 de set de 2017
 *      Author: skelter_win
 */

#include "project_includes/capture.h"



int16_t ADCchannel[CHANNELS_COUNTER][SAMPLE_FRAME];
Outlet outlet[OUTLET_COUNTER];
Panel panel;

//uint8_t temp[6][15360];

uint32_t eventCount=0; // debug purpose
uint8_t eventOn=0;
uint32_t sendCount=0;
uint8_t setOn=0;
uint32_t packError=0;

uint8_t adcStop=0;

void serializeMsg(uint8_t outletNum);
void char2byte(uint8_t outletNum, uint8_t num);
void float2byte(uint8_t outletNum, float32_t *num);
static inline void copy_int16_f32( int16_t * pSrc, float32_t * pDst, uint32_t blockSize);
static inline void logOutlet(int16_t outletNum);
static inline void logPanel(void);

int8_t differencePack(int16_t *pSrc, uint8_t *pDst, uint32_t blockSize);


/*------------------------------------------------
 *              ADC0 Transfer Values
 *------------------------------------------------
 */
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
 *------------------------------------------------
 */
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
    // process first part of AIN8...AIN12
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
 *              Calculate RMS value
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
        for(i=CH0;i<OUTLET_COUNTER;i++)
        {
            // phase current
            // copy vector
            copy_int16_f32(ADCchannel[i],tempSamples, SAMPLE_FRAME);
            // Get mean value
            arm_mean_f32(tempSamples, SAMPLE_FRAME, &meanValue);
            // ADC offset
            arm_offset_f32(tempSamples, -meanValue ,tempSamples, SAMPLE_FRAME);
            // ADC scale
            arm_scale_f32(tempSamples, ptgmSettings.channel[i].channel_gain , tempSamples, SAMPLE_FRAME);
            // calculate RMS
            arm_rms_f32(tempSamples, SAMPLE_FRAME, &tempRms);
            // copy to outlet
            outlet[i].phaseRms = tempRms;

            // diff current
            // copy vector
            copy_int16_f32(ADCchannel[i+1],tempSamples, SAMPLE_FRAME);
            // Get mean value
            arm_mean_f32(tempSamples, SAMPLE_FRAME, &meanValue);
            // ADC offset
            arm_offset_f32(tempSamples, -meanValue , tempSamples, SAMPLE_FRAME);
            // ADC scale
            arm_scale_f32(tempSamples, ptgmSettings.channel[i+1].channel_gain , tempSamples, SAMPLE_FRAME);
            // calculate RMS
            arm_rms_f32(tempSamples, SAMPLE_FRAME, &tempRms);
            // copy to outlet
            outlet[i].diffRms = tempRms;
        }

        /* Process Panel  */
        for(i=CH12;i<CH15;i++) // 2 voltages and 1 earth leakage sensor
        {
            // copy vector
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

        // all done, do event analysis
        Semaphore_post(s_doEventAnalysis);

     GPIO_write(DEBUG_PIN_CAPTURE, 0); // hardware debug pin off
     Log_write1(UIABenchmark_stop,(xdc_IArg)"Process Data Task"); // Max: 4.2ms
    }

}

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
//        outlet[outletNum].logPutVoltage = &outlet[outletNum].logVoltage[0];
//        outlet[outletNum].logPutLeakage = &outlet[outletNum].logEarthLeakage[0];
        outlet[outletNum].logGetPhase = &outlet[outletNum].logPhase[0];
        outlet[outletNum].logGetDiff = &outlet[outletNum].logDiff[0];

        if (outletNum < OUTLET_COUNTER >> 2)
            outlet[outletNum].logGetVoltage = &panel.logVoltage1[0];
        else
            outlet[outletNum].logGetVoltage = &panel.logVoltage2[0];

        outlet[outletNum].logGetLeakage = &panel.logEarthLeakage[0];
//        outlet[outletNum].logGetVoltage = &outlet[outletNum].logVoltage[0];
//        outlet[outletNum].logGetLeakage = &outlet[outletNum].logEarthLeakage[0];
    }

    // Panel init
    panel.logPutVoltage1 = &panel.logVoltage1[0];
    panel.logPutVoltage2 = &panel.logVoltage2[0];
    panel.logPutLeakage = &panel.logEarthLeakage[0];

    while (1)
    {
        // wait until data is being processed
        Semaphore_pend(s_doEventAnalysis, BIOS_WAIT_FOREVER);
        Log_write1(UIABenchmark_start,(xdc_IArg)"Event Analisys Task");
        // scan all outlets
        for (outletNum = 0; outletNum < OUTLET_COUNTER; outletNum++)
        {
            // panel is always logging
            logPanel();

            switch (outlet[outletNum].event)
            {
            case OFF:   // Equipment is off, looking for turns on events
            {
                if (outlet[outletNum].phaseRms > outlet[outletNum].limitPhase) // turned on?
                {
                    outlet[outletNum].event = TURNS_ON;
                }
                break;
            }
            case ON:    // Equipment is on, looking for turns off events
            {
                if (outlet[outletNum].phaseRms < (outlet[outletNum].limitPhase)) // turned off?
                {
                    outlet[outletNum].event = TURNS_OFF;
                }
                else
                    //logOutlet(outletNum); // keep logging
                    break;
            }
            }

            // processes ON and OFF events
            if (setOn) //if (outlet[outletNum].event == TURNS_ON)//if(setOn) // if(outletNum==1) // if(setOn)//if (outlet[outletNum].event == TURNS_ON)
            {

                logOutlet(outletNum);
                // increment log counter
                outlet[outletNum].logCounter++;
            }
            else if (outlet[outletNum].event == TURNS_OFF)
            {
                //doSprintfPOST_OFF(outletNum);
                //Semaphore_post(s_doDataSendTcpIp);
                //sendCount++;
                //serializeMsg(outletNum);
                outlet[outletNum].logCounter++; // increment log counter
            }

            // finalize log process
            if (outlet[outletNum].logCounter > MAX_WAVE_LOG)
            {
                // if still on after 10 log events, send logged data, else discard.
                if (outlet[outletNum].phaseRms > outlet[outletNum].limitPhase)
                {
                    outlet[outletNum].event = ON;       // equipment is on
                    sendCount++;
                    Semaphore_post(s_doDataSendTcpIp);  // send data
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
 *          Write Outlet Circular buffers
 *
 */
static inline void logOutlet(int16_t outletNum)
{
    // write phase circular buffer
    arm_copy_q15(ADCchannel[outletNum * 2], outlet[outletNum].logPutPhase, SAMPLE_FRAME);
    // increment or reset circular phase buffer
    if (outlet[outletNum].logPutPhase >= &outlet[outletNum].logPhase[LOG_BUFFER_SIZE-SAMPLE_FRAME])
        outlet[outletNum].logPutPhase = &outlet[outletNum].logPhase[0];
    else
        outlet[outletNum].logPutPhase += SAMPLE_FRAME;

    // write diff circular buffer
    arm_copy_q15(ADCchannel[(outletNum * 2) + 1], outlet[outletNum].logPutDiff,SAMPLE_FRAME);
    // increment or reset circular diff buffer
    if (outlet[outletNum].logPutDiff >= &outlet[outletNum].logDiff[LOG_BUFFER_SIZE-SAMPLE_FRAME])
        outlet[outletNum].logPutDiff = &outlet[outletNum].logDiff[0];
    else
        outlet[outletNum].logPutDiff += SAMPLE_FRAME;

//    // write voltage circular buffer
//    if(outletNum < OUTLET_COUNTER/2)
//        arm_copy_q15(ADCchannel[CH12], outlet[outletNum].logPutVoltage, SAMPLE_FRAME);
//    else
//        arm_copy_q15(ADCchannel[CH13], outlet[outletNum].logPutVoltage, SAMPLE_FRAME);
//    // increment or reset circular voltage buffer
//    if (outlet[outletNum].logPutVoltage >= &outlet[outletNum].logVoltage[LOG_BUFFER_SIZE-SAMPLE_FRAME])
//        outlet[outletNum].logPutVoltage = &outlet[outletNum].logVoltage[0];
//    else
//        outlet[outletNum].logPutVoltage += SAMPLE_FRAME;
//
//    // write earth leakage circular buffer
//    arm_copy_q15(ADCchannel[CH14], outlet[outletNum].logPutLeakage, SAMPLE_FRAME);
//    // increment or reset circular earth leakage buffer
//    if (outlet[outletNum].logPutLeakage == &outlet[outletNum].logEarthLeakage[LOG_BUFFER_SIZE-SAMPLE_FRAME])
//        outlet[outletNum].logPutLeakage = &outlet[outletNum].logEarthLeakage[0];
//    else
//        outlet[outletNum].logPutLeakage += SAMPLE_FRAME;
}

/*
 *          Write Panel Circular buffers
 *
 */
static inline void logPanel(void)
{
    // write voltage1 circular buffer
    arm_copy_q15(ADCchannel[CH12], panel.logPutVoltage1, SAMPLE_FRAME);
    // increment or reset circular phase buffer
    if (panel.logPutVoltage1 >= &panel.logVoltage1[LOG_BUFFER_SIZE - SAMPLE_FRAME])
        panel.logPutVoltage1 = &panel.logVoltage1[0];
    else
        panel.logPutVoltage1 += SAMPLE_FRAME;

    // write voltage2 circular buffer
    arm_copy_q15(ADCchannel[CH13], panel.logPutVoltage2, SAMPLE_FRAME);
    // increment or reset circular phase buffer
    if (panel.logPutVoltage2 >= &panel.logVoltage2[LOG_BUFFER_SIZE - SAMPLE_FRAME])
        panel.logPutVoltage2 = &panel.logVoltage2[0];
    else
        panel.logPutVoltage2 += SAMPLE_FRAME;

    // write earth leakage circular buffer
    arm_copy_q15(ADCchannel[CH14], panel.logPutLeakage, SAMPLE_FRAME);
    // increment or reset circular phase buffer
    if (panel.logPutLeakage >= &panel.logEarthLeakage[LOG_BUFFER_SIZE - SAMPLE_FRAME])
        panel.logPutLeakage = &panel.logEarthLeakage[0];
    else
        panel.logPutLeakage += SAMPLE_FRAME;

}

int8_t differencePack(int16_t *pSrc, uint8_t *pDst, uint32_t blockSize)
{
    uint32_t blkCnt;
    //uint16_t in1, in2, in3, in4;

    *pDst++ = *(uint32_t *)pSrc>>8;
    *pDst++ = *(uint32_t *)pSrc++;

    for(blkCnt=0;blkCnt<blockSize;blkCnt++)
    {
        *pDst++ = *pSrc - *pSrc++;
        if(*pDst>127)
        {
            return -1;
        }
    }
    return 0;
}






void serializeMsg(uint8_t outletNum)
{

    //if (msgOutlet[outletNum].put < MAX_MSG_LOG_PER_OUTLET)
    {
        if (outlet[outletNum].logCounter < MAX_WAVE_LOG)
        {
//            char2byte(outletNum, outlet[outletNum].num);
//            char2byte(outletNum, outlet[outletNum].event);
//            char2byte(outletNum, outlet[outletNum].logCounter);
//            float2byte(outletNum, &outlet[outletNum].phaseRMS);
//            float2byte(outletNum, &outlet[outletNum].diffRMS);
//            float2byte(outletNum, outlet[outletNum].voltageRMS);


        }
        else
        {
            if (outlet[outletNum].phaseRms > outlet[outletNum].limitPhase)
                outlet[outletNum].event = ON;
            else
                outlet[outletNum].event = OFF;


           // msgOutlet[outletNum].put++;        //increment msg buffer

        }
    }
    //else
    {
        //msgOutlet error, no free resources
    }

    //uint16_t a, b, c;
    Log_write1(UIABenchmark_start,(xdc_IArg)"Serialize");
//    c = outletNum; //for (c=0;c<OUTLET_COUNTER;c++)
//    {
//        for (a = 0, b = 0; a < 240; a++)
//        {
//            temp[b] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 24;
//            temp[b + 1] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 16;
//            temp[b + 2] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 8;
//            temp[b + 3] = *(uint32_t *) &msgBuffer[c].phaseFFT[a];
//            temp[b + 4] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 24;
//            temp[b + 5] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 16;
//            temp[b + 6] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 8;
//            temp[b + 7] = *(uint32_t *) &msgBuffer[c].phaseFFT[a];
//            temp[b + 8] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 24;
//            temp[b + 9] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 16;
//            temp[b + 10] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 8;
//            temp[b + 11] = *(uint32_t *) &msgBuffer[c].phaseFFT[a];
//            temp[b + 12] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 24;
//            temp[b + 13] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 16;
//            temp[b + 14] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 8;
//            temp[b + 15] = *(uint32_t *) &msgBuffer[c].phaseFFT[a];
//            temp[b + 16] = *(uint32_t *) &msgBuffer[c].phaseFFT[a];
//            temp[b + 17] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 24;
//            temp[b + 18] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 16;
//            temp[b + 19] = *(uint32_t *) &msgBuffer[c].phaseFFT[a] >> 8;
//            temp[b + 20] = *(uint32_t *) &msgBuffer[c].phaseFFT[a];
//            b = b + 21;
//        } //Log_write1(UIABenchmark_stop,(xdc_IArg)"Serialize");
//    }
    Log_write1(UIABenchmark_stop,(xdc_IArg)"Serialize");
}


/**
 *
 *
 */
static inline void copy_int16_f32( int16_t * pSrc, float32_t * pDst, uint32_t blockSize)
{
  uint32_t blkCnt;                               /* loop counter */

  /* Run the below code for Cortex-M4 and Cortex-M3 */
  float32_t in1, in2, in3, in4;

  /*loop Unrolling */
  blkCnt = blockSize >> 2u;

  /* First part of the processing with loop unrolling.  Compute 4 outputs at a time.
   ** a second loop below computes the remaining 1 to 3 samples. */
  while(blkCnt > 0u)
  {
    /* C = A */
    /* Copy and then store the results in the destination buffer */
    in1 = (float32_t)*pSrc++;
    in2 = (float32_t)*pSrc++;
    in3 = (float32_t)*pSrc++;
    in4 = (float32_t)*pSrc++;

    *pDst++ = in1;
    *pDst++ = in2;
    *pDst++ = in3;
    *pDst++ = in4;

    /* Decrement the loop counter */
    blkCnt--;
  }

  /* If the blockSize is not a multiple of 4, compute any remaining output samples here.
   ** No loop unrolling is used. */
  blkCnt = blockSize % 0x4u;

  while(blkCnt > 0u)
  {
    /* C = A */
    /* Copy and then store the results in the destination buffer */
    *pDst++ = *pSrc++;

    /* Decrement the loop counter */
    blkCnt--;
  }
}
