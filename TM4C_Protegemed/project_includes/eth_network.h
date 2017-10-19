/*
 * eth_network.h
 *
 *  Created on: 24 de ago de 2017
 *      Author: juliosantos
 */

#ifndef PROJECT_INCLUDES_ETH_NETWORK_H_
#define PROJECT_INCLUDES_ETH_NETWORK_H_

/* Inline force functions */
#pragma FUNC_ALWAYS_INLINE(serializeMsg)


/* Standard variables definitions */
#include <stdint.h>
#include <stdbool.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Log.h>   // to use Log_Info
#include <xdc/cfg/global.h>

/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/net/http/httpcli.h> // http protocol


/* TM4C tivaware lib */
#include <ti/drivers/GPIO.h>

/* NDK BSD support */
#include <sys/socket.h>

/* Strings functions */
#include <string.h>
#include <stdio.h>

/* Tivaware Lib. */
#include "inc/hw_nvic.h"
#include "driverlib/systick.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

/* Project Header files */
#include "project_includes/settings.h"
#include "project_includes/capture.h"

/* ARM Math CMSIS DSP */
#include <arm_math.h>

/**
 *
 *      Network parameters
 *
 */

//#define USE_HTTP

// http protocol
#define PTGM_URI            "/"//"/Ptgm-Scripts/capture.php"         // Protegemed request URI
#define PTGM_HOSTNAME       "192.168.2.151"                     // Protegemed Server IP
#define PTGM_CONTENT_TYPE   "application/octet-stream" //"application/x-www-form-urlencoded" // Protegemed content type
#define USER_AGENT          "Ptgmed-TM4C"//"HTTPCli (ARM; TI-RTOS)"
#define HTTPTASKSTACKSIZE   4096
#define HEADER_SIZE         40      // FIXME: adjust manually in capture.h Msg struct
#define POST_DATA_SIZE      15400
#define CONTENT_LENGTH      "15400"
#define MAX_TRIES_CREATE_SOCKET 10
// TCP/IP server
#define TCPPORT             1000
#define TCPHANDLERSTACK     1024
#define TCPPACKETSIZE       256
#define NUMTCPWORKERS       3

// communications commands
#define COMMAND_ACK                 "OK"
#define READ_OUTLET_ID              0X11
#define WRITE_OUTLET_ID             0X12
#define READ_CHANNEL_OFFSET         0X13
#define WRITE_CHANNEL_OFFSET        0X14
#define READ_CHANNEL_GAIN           0X15
#define WRITE_CHANNEL_GAIN          0X16
#define READ_OUTLET_PHASE_LIMIT     0X17
#define WRITE_OUTLET_PHASE_LIMIT    0X18    // volatile memory, format <0x18> <outletNum:0..5> <IEEE754 hex MSB> <IEEE754 hex> <IEEE754 hex> <IEEE754 hex LSB>
#define READ_OUTLET_DIFF_LIMIT      0X19
#define WRITE_OUTLET_DIFF_LIMIT     0X20
#define REQUEST_FIRMWARE_UPDATE     0X55


#define FIRMWARE_DEBUG
#ifdef FIRMWARE_DEBUG
#define FIRMWARE_VERSION    "FW V1.01 - USB_Debug"
#else
#define FIRMWARE_VERSION    "FW V1.01 - ETH Bootloader"
#endif

#define ALIVE_MSG           "System Connected..."
#define FIRMWARE_UPDATED_REQUEST    "Firmware Update. Reseting MCU..."
#define OK_MSG "Ok"


extern char g_str_PostSend[];

static inline serializeMsg(void);

#endif /* PROJECT_INCLUDES_ETH_NETWORK_H_ */
