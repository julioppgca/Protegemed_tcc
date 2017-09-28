/*
 * capture.c
 *
 *  Created on: 4 de set de 2017
 *      Author: skelter_win
 */

#include "project_includes/capture.h"


// debug waves option
//#define DEBUG_WAVES

#ifdef DEBUG_WAVES
/* global variables */
float32_t debugOutlet1Phase[SAMPLE_FRAME];
float32_t debugOutlet1Diff[SAMPLE_FRAME];
float32_t debugOutlet1Voltage[SAMPLE_FRAME];
#endif

uint32_t eventCount=0; // debug purpose
uint8_t eventOn=0;
uint32_t sendCount=0, httpTaskCreatFailed=0;
Outlet outlet[OUTLET_COUNTER];
Panel panel;
//Msg msgOutlet[OUTLET_COUNTER];

char g_str_PostSend[POST_DATA_SIZE];

char g_str_LogOff[MAX_WAVE_LOG][POST_DATA_SIZE];
char count=0;

char temp[4800];

char setOn=0;

float32_t ADCchannel[CHANNELS_COUNTER][SAMPLE_FRAME]__attribute__((aligned(CHANNELS_COUNTER*SAMPLE_FRAME)));

void doSprintfPOST_ON(uint8_t outletNum);
uint8_t doLogOffEvent(uint8_t outletNum);
void doSprintfPOST_OFF(uint8_t outletNum);
void serializeMsg(uint8_t outletNum);
void char2byte(uint8_t outletNum, uint8_t num);
void float2byte(uint8_t outletNum, float32_t *num);
/**
 *              ADC0 Transfer Values
 *
 */
void adc0Ping_Swi(void)
{
    uint16_t i, j;
    // process first part of AIN0...AIN7
    for (i = 0, j = 0; i < SAMPLE_FRAME / 2; i++)
    {
        ADCchannel[CH0][i] = (float) g_uint16_adc0_ping[j + AIN0];
        ADCchannel[CH1][i] = (float) g_uint16_adc0_ping[j + AIN1];
        ADCchannel[CH2][i] = (float) g_uint16_adc0_ping[j + AIN2];
        ADCchannel[CH3][i] = (float) g_uint16_adc0_ping[j + AIN3];
        ADCchannel[CH4][i] = (float) g_uint16_adc0_ping[j + AIN4];
        ADCchannel[CH5][i] = (float) g_uint16_adc0_ping[j + AIN5];
        ADCchannel[CH6][i] = (float) g_uint16_adc0_ping[j + AIN6];
        ADCchannel[CH7][i] = (float) g_uint16_adc0_ping[j + AIN7];
        j += AIN_OFFSET;
    }
}

void adc0Pong_Swi(void)
{
    uint16_t i, j;
    // process last part of AIN0...AIN7
    for (i = 128, j = 0; i < SAMPLE_FRAME; i++)
    {
        ADCchannel[CH0][i] = (float) g_uint16_adc0_pong[j + AIN0];
        ADCchannel[CH1][i] = (float) g_uint16_adc0_pong[j + AIN1];
        ADCchannel[CH2][i] = (float) g_uint16_adc0_pong[j + AIN2];
        ADCchannel[CH3][i] = (float) g_uint16_adc0_pong[j + AIN3];
        ADCchannel[CH4][i] = (float) g_uint16_adc0_pong[j + AIN4];
        ADCchannel[CH5][i] = (float) g_uint16_adc0_pong[j + AIN5];
        ADCchannel[CH6][i] = (float) g_uint16_adc0_pong[j + AIN6];
        ADCchannel[CH7][i] = (float) g_uint16_adc0_pong[j + AIN7];
        j += AIN_OFFSET;
    }
    // post event ADC0 data ready
    Event_post(e_adcData_Ready, Event_Id_00);
}


/**
 *              ADC1 Transfer Values
 *
 */
void adc1Ping_Swi(void)
{
    uint16_t i, j;
    // process first part of AIN8...AIN12
    for (i = 0, j = 0; i < SAMPLE_FRAME / 2; i++)
    {
        ADCchannel[CH8][i] = (float) g_uint16_adc1_ping[j + AIN8];
        ADCchannel[CH9][i] = (float) g_uint16_adc1_ping[j + AIN9];
        ADCchannel[CH10][i] = (float) g_uint16_adc1_ping[j + AIN10];
        ADCchannel[CH11][i] = (float) g_uint16_adc1_ping[j + AIN11];
        ADCchannel[CH12][i] = (float) g_uint16_adc1_ping[j + AIN12];
        ADCchannel[CH13][i] = (float) g_uint16_adc1_ping[j + AIN13];
        ADCchannel[CH14][i] = (float) g_uint16_adc1_ping[j + AIN14];
        ADCchannel[CH15][i] = (float) g_uint16_adc1_ping[j + AIN15];

        j += AIN_OFFSET;
    }
}

void adc1Pong_Swi(void)
{
    uint16_t i, j;
    // process first part of AIN8...AIN12
    for (i = 128, j = 0; i < SAMPLE_FRAME; i++)
    {
        ADCchannel[CH8][i] = (float) g_uint16_adc1_pong[j + AIN8];
        ADCchannel[CH9][i] = (float) g_uint16_adc1_pong[j + AIN9];
        ADCchannel[CH10][i] = (float) g_uint16_adc1_pong[j + AIN10];
        ADCchannel[CH11][i] = (float) g_uint16_adc1_pong[j + AIN11];
        ADCchannel[CH12][i] = (float) g_uint16_adc1_pong[j + AIN12];
        ADCchannel[CH13][i] = (float) g_uint16_adc1_pong[j + AIN13];
        ADCchannel[CH14][i] = (float) g_uint16_adc1_pong[j + AIN14];
        ADCchannel[CH15][i] = (float) g_uint16_adc1_pong[j + AIN15];

        j += AIN_OFFSET;
    }
    // post event ADC1 data ready
    Event_post(e_adcData_Ready, Event_Id_01);//Semaphore_post(s_adc1_data_ready);
}



/**
 *              Calculate RMS value
 * Task created static (see RTOS_config.cfg). Process data
 * from DMA buffers and calculate rms value for AIN0...AIN15
 * If need, calculate fft for a specified channel.
 *
 */
void dataProcess_Task(void)
{

    uint16_t i, j;
    float32_t meanPhase;
    float32_t meanDiff;
    float32_t meanVoltage1;
    float32_t meanVoltage2;
    float32_t meanEarthLeakage;
    arm_rfft_fast_instance_f32 s;

    arm_rfft_fast_init_f32(&s, SAMPLE_FRAME);

    while (1)
    {
        // wait adc0 and adc1 data being transferred from DMA
        Event_pend(e_adcData_Ready,(Event_Id_00+Event_Id_01),0,BIOS_WAIT_FOREVER);
        Log_write1(UIABenchmark_start,(xdc_IArg)"Process Data Task");
        GPIO_write(DEBUG_PIN_CAPTURE, 1); // hardware debug pin on

        // set Outlet pointers to its respective analog channel, CH0=Phase CH1=Diff, CH2=Phase CH3=Diff ....
        for (i = 0, j = 0; i < OUTLET_COUNTER; i++, j += 2)
        {
            outlet[i].phaseWave =  ADCchannel[j];
            outlet[i].diffWave =  ADCchannel[j+1];
        }
        // set panel pointers to its respective analog channel
        panel.voltageWave1 = ADCchannel[CH12];
        panel.voltageWave2 = ADCchannel[CH13];
        panel.earthLeakageWave = ADCchannel[CH14];

        /* process all outlets */
        for(i=0;i<OUTLET_COUNTER;i++)
        {
            // Get mean value
            arm_mean_f32(outlet[i].phaseWave, SAMPLE_FRAME, &meanPhase);
            arm_mean_f32(outlet[i].diffWave, SAMPLE_FRAME, &meanDiff);
            // ADC offset
            arm_offset_f32(outlet[i].phaseWave, -meanPhase , outlet[i].phaseWave, SAMPLE_FRAME);
            arm_offset_f32(outlet[i].diffWave, -meanDiff , outlet[i].diffWave, SAMPLE_FRAME);
            // ADC scale
            arm_scale_f32(outlet[i].phaseWave, ptgmSettings.channel[i].channel_gain , outlet[i].phaseWave, SAMPLE_FRAME);
            arm_scale_f32(outlet[i].diffWave, ptgmSettings.channel[i+1].channel_gain , outlet[i].diffWave, SAMPLE_FRAME);
            // calculate RMS
            arm_rms_f32(outlet[i].phaseWave, SAMPLE_FRAME, &outlet[i].phaseRMS);
            arm_rms_f32(outlet[i].diffWave, SAMPLE_FRAME, &outlet[i].diffRMS);

            // Calculate fft - Benchmark result: 3.209ms, 12 fft calculation
            arm_rfft_fast_f32(&s, outlet[i].phaseWave, outlet[i].phaseFFT, 0);
            arm_rfft_fast_f32(&s, outlet[i].diffWave, outlet[i].diffFFT, 0);
        }

        /* process Panel  */
        // Get mean value
        arm_mean_f32(panel.voltageWave1, SAMPLE_FRAME, &meanVoltage1);
        arm_mean_f32(panel.voltageWave2, SAMPLE_FRAME, &meanVoltage2);
        arm_mean_f32(panel.earthLeakageWave, SAMPLE_FRAME, &meanEarthLeakage);
        // ADC offset
        arm_offset_f32(panel.voltageWave1, -meanVoltage1 , panel.voltageWave1, SAMPLE_FRAME);
        arm_offset_f32(panel.voltageWave2, -meanVoltage2 , panel.voltageWave2, SAMPLE_FRAME);
        arm_offset_f32(panel.earthLeakageWave, -meanEarthLeakage , panel.earthLeakageWave, SAMPLE_FRAME);
        // ADC scale
        arm_scale_f32(panel.voltageWave1, (3.3/4095) , panel.voltageWave1, SAMPLE_FRAME); // FIXME: Adjust Gain value
        arm_scale_f32(panel.voltageWave2, (3.3/4095) , panel.voltageWave2, SAMPLE_FRAME);
        arm_scale_f32(panel.earthLeakageWave, (3.3/4095) , panel.earthLeakageWave, SAMPLE_FRAME);
        // calculate RMS
        arm_rms_f32(panel.voltageWave1, SAMPLE_FRAME, &panel.voltage1RMS);
        arm_rms_f32(panel.voltageWave2, SAMPLE_FRAME, &panel.voltage2RMS);
        arm_rms_f32(panel.earthLeakageWave, SAMPLE_FRAME, &panel.eathLeakageRMS);
        // Calculate fft
        arm_rfft_fast_f32(&s,panel.voltageWave1, panel.voltageFFT1,0);
        arm_rfft_fast_f32(&s,panel.voltageWave2, panel.voltageFFT2,0);
        arm_rfft_fast_f32(&s,panel.earthLeakageWave, panel.earthLeakageFFT,0);
        // Assign Voltage FFT and RMS values to their respective outlets
        outlet[OUTLET_1].voltageFFT = panel.voltageFFT1;
        outlet[OUTLET_2].voltageFFT = panel.voltageFFT1;
        outlet[OUTLET_3].voltageFFT = panel.voltageFFT1;
        outlet[OUTLET_4].voltageFFT = panel.voltageFFT2;
        outlet[OUTLET_5].voltageFFT = panel.voltageFFT2;
        outlet[OUTLET_6].voltageFFT = panel.voltageFFT2;
        outlet[OUTLET_1].voltageRMS = &panel.voltage1RMS;
        outlet[OUTLET_2].voltageRMS = &panel.voltage1RMS;
        outlet[OUTLET_3].voltageRMS = &panel.voltage1RMS;
        outlet[OUTLET_4].voltageRMS = &panel.voltage2RMS;
        outlet[OUTLET_5].voltageRMS = &panel.voltage2RMS;
        outlet[OUTLET_6].voltageRMS = &panel.voltage2RMS;

        // all done, do event analysis
        Semaphore_post(s_doEventAnalysis);

#ifdef DEBUG_WAVES       // debug waves
       arm_copy_f32(outlet[OUTLET_1].phaseWave, debugOutlet1Phase, SAMPLE_FRAME);
       arm_copy_f32(outlet[OUTLET_1].diffWave, debugOutlet1Diff, SAMPLE_FRAME);
       arm_copy_f32(panel.voltageFFTOutlets1, debugOutlet1Voltage, SAMPLE_FRAME);
#endif

     Log_write1(UIABenchmark_stop,(xdc_IArg)"Process Data Task"); // Max: 4.2ms
     GPIO_write(DEBUG_PIN_CAPTURE, 0); // hardware debug pin off
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
        outlet[outletNum].limitDiff = ptgmSettings.channel[j+1].channel_limit;
        outlet[outletNum].logCounter = 0;
        outlet[outletNum].event = OFF;

        // initialize msg buffer
        //msgOutlet[outletNum].put=0;
        //msgOutlet[outletNum].get=0;
    }






    while(1)
    {
        // wait until data is being processed
        Semaphore_pend(s_doEventAnalysis, BIOS_WAIT_FOREVER);
        Log_write1(UIABenchmark_start,(xdc_IArg)"Event Analisys Task");
        // scan all outlets
        for (outletNum = 0; outletNum < OUTLET_COUNTER; outletNum++)
        {

            switch (outlet[outletNum].event)
            {
                case OFF:   // Equipment is off, looking for turns on events
                {
                    if (outlet[outletNum].phaseRMS > outlet[outletNum].limitPhase)  // turned on?
                    {
                        outlet[outletNum].event = TURNS_ON;
                    }
                    break;
                }
                case ON:    // Equipment is on, looking for turns off events
                {
                    if (outlet[outletNum].phaseRMS < (outlet[outletNum].limitPhase))  // turned off?
                    {
                        outlet[outletNum].event = TURNS_OFF;
                        count = doLogOffEvent(outletNum);//doSprintfPOST_OFF(outletNum); // log off events
                    }
                    else
                        count = doLogOffEvent(outletNum);//doSprintfPOST_OFF(outletNum); // log off events
                    break;
                }
              }

            // processes ON and OFF events
            if(setOn)//if (outlet[outletNum].event == TURNS_ON)
            {
                //doSprintfPOST_ON(outletNum);
                Semaphore_post(s_doDataSendTcpIp);
                sendCount++;
                //serializeMsg(outletNum);
                outlet[outletNum].logCounter++; // increment log counter
            }
            /*else if (outlet[outletNum].event == TURNS_OFF)
            {
                //doSprintfPOST_OFF(outletNum);
                Semaphore_post(s_doDataSendTcpIp);
                sendCount++;
                //serializeMsg(outletNum);
                outlet[outletNum].logCounter++; // increment log counter
            }*/

            // finalize log process
            if (outlet[outletNum].logCounter >= MAX_WAVE_LOG)
            {
                if (outlet[outletNum].phaseRMS > outlet[outletNum].limitPhase)
                                outlet[outletNum].event = ON;
                            else
                                outlet[outletNum].event = OFF;
                outlet[outletNum].logCounter = 0;   //reset log counter

                //sendCount++;
                //Semaphore_post(s_doDataSendTcpIp);

            }

          }

            Log_write1(UIABenchmark_stop,(xdc_IArg)"Event Analisys Task");
        }

 }


void doSprintfPOST_ON(uint8_t outletNum)
{
    uint8_t i,j,k;

    memset(g_str_PostSend, ' ', POST_DATA_SIZE);
    i=outletNum;

    sprintf(g_str_PostSend,
            "O=%d&EV_ID=%d&SP_ID=%d&RMS_P=%08X&RMS_D=%08X&RMS_V=%08X&FFT=",
            outlet[i].num, outlet[i].event,
            outlet[i].logCounter,
            *(unsigned int*) &outlet[i].phaseRMS,
            *(unsigned int*) &outlet[i].diffRMS,
            *(unsigned int*) &outlet[i].voltageRMS);

    for (k = 0, j = 0; k < ptgmSettings.maxHarmonics; k++)
    {
        j += 2;
        sprintf(g_str_PostSend + strlen(g_str_PostSend),
                "%08X;%08X;%08X;%08X;%08X;%08X;",
                *(unsigned int*) &outlet[i].phaseFFT[j],
                *(unsigned int*) &outlet[i].phaseFFT[j + 1],
                *(unsigned int*) &outlet[i].diffFFT[j],
                *(unsigned int*) &outlet[i].diffFFT[j + 1],
                *(unsigned int*) &outlet[i].voltageFFT[j],
                *(unsigned int*) &outlet[i].voltageFFT[j + 1]);
    }


    /* create http task dynamically */
    static Task_Handle httpPOST_Handle;
    Task_Params httpPOST_Params;
    Error_Block httpPOST_eb;

    Error_init(&httpPOST_eb);
    Task_Params_init(&httpPOST_Params);
    httpPOST_Params.stackSize = HTTPTASKSTACKSIZE;
    httpPOST_Params.priority = 1;
    //httpPOST_Params.arg0 = (xdc_UArg) g_str_PostSend;
    httpPOST_Handle = Task_create((Task_FuncPtr) httpPOST_Task,
                                  &httpPOST_Params, &httpPOST_eb);
    if (httpPOST_Handle == NULL)
    {
        Log_info0("captureTask: Failed to create HTTP POST Task");
        httpPOST_Handle = Task_create((Task_FuncPtr) httpPOST_Task,
                                      &httpPOST_Params,
                                      &httpPOST_eb);
        if (httpPOST_Handle == NULL)
        {
            Log_info1("captureTask: Failed to create HTTP POST Task %d Times.", ++httpTaskCreatFailed);
        }
    }

}

uint8_t doLogOffEvent(uint8_t outletNum)
{
    static uint8_t c=0;
    uint8_t i,j,k;

    memset(g_str_PostSend, ' ', POST_DATA_SIZE);
    i=outletNum;

    sprintf(g_str_PostSend,
            "O=%d&EV_ID=%d&SP_ID=%d&RMS_P=%08X&RMS_D=%08X&RMS_V=%08X&FFT=",
            outlet[i].num, TURNS_OFF,//outlet[i].event,
            count,//outlet[i].logCounter,
            *(unsigned int*) &outlet[i].phaseRMS,
            *(unsigned int*) &outlet[i].diffRMS,
            *(unsigned int*) &outlet[i].voltageRMS);

    for (k = 0, j = 0; k < ptgmSettings.maxHarmonics; k++)
    {
        j += 2;
        sprintf(g_str_PostSend + strlen(g_str_PostSend),
                "%08X;%08X;%08X;%08X;%08X;%08X;",
                *(unsigned int*) &outlet[i].phaseFFT[j],
                *(unsigned int*) &outlet[i].phaseFFT[j + 1],
                *(unsigned int*) &outlet[i].diffFFT[j],
                *(unsigned int*) &outlet[i].diffFFT[j + 1],
                *(unsigned int*) &outlet[i].voltageFFT[j],
                *(unsigned int*) &outlet[i].voltageFFT[j + 1]);
    }



    strcpy(g_str_LogOff[c],g_str_PostSend);
    c++;
    if(c>=MAX_WAVE_LOG)
        c=0;

    return c;
}

void doSprintfPOST_OFF(uint8_t outletNum)
{

    strcpy(g_str_PostSend, g_str_LogOff[count]);

    if(++count>=MAX_WAVE_LOG)
        count = 0;

    /* create http task dynamically */
    static Task_Handle httpPOST_Handle;
    Task_Params httpPOST_Params;
    Error_Block httpPOST_eb;

    Error_init(&httpPOST_eb);
    Task_Params_init(&httpPOST_Params);
    httpPOST_Params.stackSize = HTTPTASKSTACKSIZE;
    httpPOST_Params.priority = 1;
    //httpPOST_Params.arg0 = (xdc_UArg) g_str_PostSend;
    httpPOST_Handle = Task_create((Task_FuncPtr) httpPOST_Task,
                                  &httpPOST_Params, &httpPOST_eb);
    if (httpPOST_Handle == NULL)
    {
        Log_info0("captureTask: Failed to create HTTP POST Task");
        httpPOST_Handle = Task_create((Task_FuncPtr) httpPOST_Task,
                                      &httpPOST_Params,
                                      &httpPOST_eb);
        if (httpPOST_Handle == NULL)
        {
            Log_info1("captureTask: Failed to create HTTP POST Task %d Times.", ++httpTaskCreatFailed);
        }
    }

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
            if (outlet[outletNum].phaseRMS > outlet[outletNum].limitPhase)
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

void char2byte(uint8_t outletNum, uint8_t num)
{
//    msgOutlet[outletNum].buffer[msgOutlet[outletNum].put][msgOutlet[outletNum].index++]=num;
}

void float2byte(uint8_t outletNum, float32_t *num)
{
//    msgOutlet[outletNum].buffer[msgOutlet[outletNum].put][msgOutlet[outletNum].index++]= *(uint32_t *) num >> 24;
//    msgOutlet[outletNum].buffer[msgOutlet[outletNum].put][msgOutlet[outletNum].index++]= *(uint32_t *) num >> 16;
//    msgOutlet[outletNum].buffer[msgOutlet[outletNum].put][msgOutlet[outletNum].index++]= *(uint32_t *) num >> 8;
//    msgOutlet[outletNum].buffer[msgOutlet[outletNum].put][msgOutlet[outletNum].index++]= *(uint32_t *) num;
}
