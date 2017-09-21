/*
 * capture.c
 *
 *  Created on: 4 de set de 2017
 *      Author: skelter_win
 */

#include "project_includes/capture.h"


// debug waves option
//#define DEBUG_WAVES

uint32_t eventCount=0; // debug purpose
uint8_t eventOn=0;
uint32_t sendCount=0;
Outlet outlet[OUTLET_COUNTER];
float32_t ADCchannel[CHANNELS_COUNTER][SAMPLE_FRAME];

/* global variables */
float32_t debugOutlet1Phase[SAMPLE_FRAME];
float32_t debugOutlet1Diff[SAMPLE_FRAME];
float32_t debugOutlet1Voltage[SAMPLE_FRAME];



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
void capture_Task(void)
{

    uint16_t i, j;
    float32_t meanPhase, meanDiff;
    arm_rfft_fast_instance_f32 s;

    arm_rfft_fast_init_f32(&s, SAMPLE_FRAME);

    // set detect limits
    for(i=0,j=0;i<OUTLET_COUNTER;i++)
    {
        outlet[i].limitPhase = ptgmSettings.channel[j].channel_limit;
        outlet[i].limitDiff = ptgmSettings.channel[j+1].channel_limit;
        outlet[i].limitCounterPhase=0;
        outlet[i].limitCounterDiff=0;
        j+=2;
    }

    while (1)
    {
        // wait adc0 and adc1 data being transferred from DMA
        Event_pend(e_adcData_Ready,(Event_Id_00+Event_Id_01),0,BIOS_WAIT_FOREVER);
        GPIO_write(DEBUG_PIN_CAPTURE, 1);
        arm_copy_f32(ADCchannel[CH0], outlet[OUTLET_1].phaseWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH1], outlet[OUTLET_1].diffWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH2], outlet[OUTLET_2].phaseWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH3], outlet[OUTLET_2].diffWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH4], outlet[OUTLET_3].phaseWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH5], outlet[OUTLET_3].diffWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH6], outlet[OUTLET_4].phaseWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH7], outlet[OUTLET_4].diffWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH8], outlet[OUTLET_5].phaseWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH9], outlet[OUTLET_5].diffWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH10], outlet[OUTLET_6].phaseWave, SAMPLE_FRAME);
        arm_copy_f32(ADCchannel[CH11], outlet[OUTLET_6].diffWave, SAMPLE_FRAME);

        /* process all outlets */
        Log_write3(UIABenchmark_startInstanceWithStr, (IArg)"Benchmarck",1,(IArg)"Data processing");
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
        Log_write3(UIABenchmark_stopInstanceWithStr, (IArg)"Benchmarck",1,(IArg)"Data processing");

#ifdef DEBUG_WAVES       // debug waves
       arm_copy_f32(outlet[i].phaseWave, debugOutlet1Phase, SAMPLE_FRAME);
       arm_copy_f32(outlet[i].diffWave, debugOutlet1Diff, SAMPLE_FRAME);
       //arm_copy_f32(ADCchannel[2], debugOutlet1Voltage, SAMPLE_FRAME);
#endif

       //for(i=0;i<OUTLET_COUNTER;i++)
       for(i=0;i<1;i++)
       {
           if (outlet[i].phaseRMS > outlet[i].limitPhase)
           {
               eventOn=1;
               //(Outlet1PhaseRMS>0.5)
           }
           if(eventOn)
           {
                char g_str_PostSend[POST_DATA_SIZE];
                memset(g_str_PostSend, ' ', POST_DATA_SIZE);

                sprintf(g_str_PostSend,
                        "RMS_P=%08X&RMS_D=%08X&RMS_V=%08X&SIN_P=",
                        *(unsigned int*) &outlet[i].phaseRMS,
                        *(unsigned int*) &outlet[i].diffRMS,
                        *(unsigned int*) &outlet[i].phaseRMS);
                uint8_t j, k;
                char temp[9];

                for (k = 0, j = 0; k < ptgmSettings.maxHarmonics; k++)
                {
                    j += 2;
                    sprintf(temp, "%08X;",
                            *(unsigned int*) &outlet[i].phaseFFT[j]);
                    strcat(g_str_PostSend, temp);

                }
                strcat(g_str_PostSend, "&COS_P=");
                for (k = 0, j = 1; k < ptgmSettings.maxHarmonics; k++)
                {
                    j += 2;
                    sprintf(temp, "%08X;",
                            *(unsigned int*) &outlet[i].phaseFFT[j]);
                    strcat(g_str_PostSend, temp);
                }
                strcat(g_str_PostSend, "&SIN_D=");
                for (k = 0, j = 0; k < ptgmSettings.maxHarmonics; k++)
                {
                    j += 2;
                    sprintf(temp, "%08X;",
                            *(unsigned int*) &outlet[i].diffFFT[j]);
                    strcat(g_str_PostSend, temp);
                }
                strcat(g_str_PostSend, "&COS_D=");
                for (k = 0, j = 1; k < ptgmSettings.maxHarmonics; k++)
                {
                    j += 2;
                    sprintf(temp, "%08X;",
                            *(unsigned int*) &outlet[i].diffFFT[j]);
                    strcat(g_str_PostSend, temp);
                }
                strcat(g_str_PostSend, "&SIN_V=");
                for (k = 0, j = 0; k < ptgmSettings.maxHarmonics; k++)
                {
                    j += 2;
                    sprintf(temp, "%08X;",
                            *(unsigned int*) &outlet[i].phaseFFT[j]);
                    strcat(g_str_PostSend, temp);
                }
                strcat(g_str_PostSend, "&COS_V=");
                for (k = 0, j = 1; k < ptgmSettings.maxHarmonics; k++)
                {
                    j += 2;
                    sprintf(temp, "%08X;",
                            *(unsigned int*) &outlet[i].phaseFFT[j]);
                    strcat(g_str_PostSend, temp);
                }


                     static Task_Handle httpPOST_Handle;
                     Task_Params httpPOST_Params;
                     Error_Block httpPOST_eb;

                     Error_init(&httpPOST_eb);
                     Task_Params_init(&httpPOST_Params);
                     httpPOST_Params.stackSize = HTTPTASKSTACKSIZE;
                     httpPOST_Params.priority = 1;
                     httpPOST_Params.arg0 = (xdc_UArg)g_str_PostSend;
                     httpPOST_Handle = Task_create((Task_FuncPtr)httpPOST_Task, &httpPOST_Params, &httpPOST_eb);
                     if (httpPOST_Handle == NULL)
                         {
                             Log_info0("captureTask: Failed to create HTTP POST Task\n");
                         }
                     sendCount++;

                 if(++eventCount>10)
                 {
                     eventOn=0;
                     eventCount=0;
                 }
                 //Task_sleep(1000); // FIXME: remove this later

               }

       }
     GPIO_write(DEBUG_PIN_CAPTURE, 0);
    }
}
