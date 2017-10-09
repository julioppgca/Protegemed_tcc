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


/* TM4C tivaware lib */
#include <ti/drivers/GPIO.h>

/* NDK BSD support */
#include <sys/socket.h>
//#include <ti/ndk/inc/socketndk.h>

//#include <ti/ndk/inc/_stack.h>  // test

/* Strings functions */
#include <string.h>
#include <stdio.h>

/* Project Header files */
#include "project_includes/settings.h"
#include "project_includes/capture.h"


/**
 *
 *      Network parameters
 *
 */
// http protocol
#define PTGM_URI            "/"//"/Ptgm-Scripts/capture.php"         // Protegemed request URI
#define PTGM_HOSTNAME       "192.168.2.151"                     // Protegemed Server IP
#define PTGM_CONTENT_TYPE   "application/octet-stream" //"application/x-www-form-urlencoded" // Protegemed content type
#define USER_AGENT          "Ptgmed-TM4C"//"HTTPCli (ARM; TI-RTOS)"
#define HTTPTASKSTACKSIZE   4096
#define HEADER_SIZE         40      // FIXME: adjust manually in capture.h Msg struct
#define POST_DATA_SIZE      15400
// TCP/IP server
#define TCPPORT             1000
#define TCPHANDLERSTACK     1024
#define TCPPACKETSIZE       256
#define NUMTCPWORKERS       3

extern char g_str_PostSend[];

static inline serializeMsg(void);

#endif /* PROJECT_INCLUDES_ETH_NETWORK_H_ */
