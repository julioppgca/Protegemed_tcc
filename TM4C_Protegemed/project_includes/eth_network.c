/*
 *    ======== eth_network.c ========
 *    Contains non-BSD sockets code (NDK Network Open Hook)
 */

#include "project_includes/eth_network.h"
#include "project_includes/capture.h"


// debug global variables
uint32_t tcpCount=0;
uint32_t sendError=0;
uint32_t socketError=0; //TODO: transfer to local in release

// transmit string
char g_str_PostSend[POST_DATA_SIZE];

// post header
//const char postHeader[]=\
//        "POST / HTTP/1.1\r\n"
//        "Host: 192.168.2.151\r\n"
//        "Content-Type: application/octet-stream\r\n"
//        "Content-Length: 15400\r\n"
//        "\r\n";

// prototypes
static inline serializeMsg(void);


static inline serializeMsg(void)
{
    int8_t *pStrPost;   // pointer to g_str_PostSend
    int8_t i;           // block counter

    // initiate pointer
    pStrPost = (int8_t *)&g_str_PostSend[0];

//    // get a message header
//    arm_copy_q7((int8_t*)postHeader, pStrPost, 101);
//    pStrPost += 102;

    // get a message header
    arm_copy_q7((int8_t*)gMsg->header, pStrPost, HEADER_SIZE);
    pStrPost += HEADER_SIZE;

    // get message raw data
    for(i=0;i<MAX_WAVE_LOG;i++) // phase raw data
    {
       arm_copy_q7(gMsg->phase, pStrPost, MERGE_LOG_BLOCK);
       pStrPost += MERGE_LOG_BLOCK;
       gMsg->phase += MERGE_LOG_BLOCK;
       if(gMsg->phase >= &outlet[gMsg->outletNum].logPhase[LOG_BUFFER_SIZE])
           gMsg->phase = &outlet[gMsg->outletNum].logPhase[0];

    }
    for(i=0;i<MAX_WAVE_LOG;i++) // diff raw data
    {
       arm_copy_q7(gMsg->diff, pStrPost, MERGE_LOG_BLOCK);
       pStrPost += MERGE_LOG_BLOCK;
       gMsg->diff += MERGE_LOG_BLOCK;
       if(gMsg->diff >= &outlet[gMsg->outletNum].logDiff[LOG_BUFFER_SIZE])
           gMsg->diff = &outlet[gMsg->outletNum].logDiff[0];
    }
    for(i=0;i<MAX_WAVE_LOG;i++) // voltage raw data
    {
       arm_copy_q7(gMsg->voltage, pStrPost, MERGE_LOG_BLOCK);
       pStrPost += MERGE_LOG_BLOCK;
       gMsg->voltage += MERGE_LOG_BLOCK;
       if(gMsg->outletNum < OUTLET_COUNTER>>1) // voltage 1 or 2
       {
       if(gMsg->voltage >= &panel.logVoltage1[LOG_BUFFER_SIZE_PANEL])
           gMsg->voltage = &panel.logVoltage1[0];
       }
       else
       {
       if(gMsg->voltage >= &panel.logVoltage2[LOG_BUFFER_SIZE_PANEL])
           gMsg->voltage = &panel.logVoltage2[0];
       }
    }
    for(i=0;i<MAX_WAVE_LOG;i++) // leakage raw data
    {
       arm_copy_q7(gMsg->leakage, pStrPost, MERGE_LOG_BLOCK);
       pStrPost += MERGE_LOG_BLOCK;
       gMsg->leakage += MERGE_LOG_BLOCK;
       if(gMsg->leakage >= &panel.logEarthLeakage[LOG_BUFFER_SIZE_PANEL])
           gMsg->leakage = &panel.logEarthLeakage[0];
    }

    // increment to the next queued message or reset circular buffer
    if(++gMsg > &msg[OUTLET_COUNTER])
       gMsg=&msg[0];

}


#ifndef USE_HTTP
/* TCP/IP client send data */
void dataSendTcpIp(void)
{
    int client;
    int status;
    struct sockaddr_in serverAddr;

//    int8_t i;           // index increment
//    int8_t *pStrPost;   // pointer to g_str_PostSend

    Semaphore_pend(s_networkIsUp, BIOS_WAIT_FOREVER);

    while (1)
    {
        Semaphore_pend(s_doDataSendTcpIp, BIOS_WAIT_FOREVER);
        Log_write1(UIABenchmark_start,(xdc_IArg)"TCP Send");
        GPIO_write(DEBUG_PIN_SEND, 1); // hardware debug pin on

        fdOpenSession(dataSendTcpIp_Handle);

        // serialize message to send
        serializeMsg();

        do{
            client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(client==-1)
            {
                if( ++socketError > MAX_TRIES_CREATE_SOCKET )
                {
                    Log_info1("Maximum tries to create the socket has been reached. Tries: %d", socketError);
                    goto shutdown;
                }
            }
        }while(client < 0);
        socketError=0;

        if (client == -1)
        {
            Log_info0("Error: client socket not created.");
            goto shutdown;
        }

        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = htonl(3232236183); //TODO: use like this: inet_addr(PTGM_HOSTNAME);
        serverAddr.sin_port = htons(7891); // TcpIp server listen Port = 7891
        memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

        status = connect(client, (struct sockaddr *) &serverAddr,sizeof(serverAddr));
        if (status == -1)
        {
            Log_info0("connection refused");
            sendError++;
            goto shutdown;
        }

        send(client, g_str_PostSend, POST_DATA_SIZE, 0);
        tcpCount++;

        //TODO: confirm receive?
        //recv(client, lixo, _LEN, 0);

        close(client);

        shutdown:
            if (client > 0) {
                close(client);
            }

        fdCloseSession(dataSendTcpIp_Handle);

        GPIO_write(DEBUG_PIN_SEND, 0); // hardware debug pin off
    Log_write1(UIABenchmark_stop,(xdc_IArg)"TCP Send");
    }

}
void httpPOST_Task(UArg arg0, UArg arg1) // dummy function to avoid static configuration error, missing symbols
{
    //dummy
}
#else
void dataSendTcpIp(void) // dummy function to avoid static configuration error
{
    //dummy
}
/*
 *
 *          HTTP Task - POST to the server
 *  This Task is created dynamically, it sends the captured data through
 *  a POST method to Protegmed server
 *  whenever is needed.
 *
 *  TODO: Treat errors on connections
 */
void httpPOST_Task(UArg arg0, UArg arg1)
{
    bool moreFlag = false;
    int ret;
    int len;
//    char CONTENT_LENGTH[4]=;
    struct sockaddr_in addr;

    char data[100]={};

    while(1)
    {
        Semaphore_pend(s_doDataSendTcpIp, BIOS_WAIT_FOREVER);
        Log_write1(UIABenchmark_start,(xdc_IArg)"HTTP Send");
        GPIO_write(DEBUG_PIN_SEND, 1); // hardware debug pin on

        fdOpenSession(httpPOST_Task_Handle);

        // serialize message to send
        serializeMsg();


        HTTPCli_Struct cli;
        HTTPCli_Field fields[3] = {
                                  { HTTPStd_FIELD_NAME_HOST, PTGM_HOSTNAME },
                                  { HTTPStd_FIELD_NAME_USER_AGENT, USER_AGENT },
                                  { NULL, NULL }
                                  };

        /* construct client */
        HTTPCli_construct(&cli);

        /* set fields to http POST */
        HTTPCli_setRequestFields(&cli, fields);

        /* */
        ret = HTTPCli_initSockAddr((struct sockaddr *)&addr, PTGM_HOSTNAME, 0);
        if (ret < 0) {
            Log_info1("httpPOST_Task: address resolution failed", ret);
        }


        ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, NULL);
        if (ret < 0) {
            Log_info1("%d: httpPOST_Task: connect failed", ret);
        }

        ret = HTTPCli_sendRequest(&cli, HTTPStd_POST, PTGM_URI, true);
        if (ret < 0) {
            Log_info1("%d: httpPOST_Task: send failed", ret);
        }

        ret = HTTPCli_sendField(&cli, HTTPStd_FIELD_NAME_CONTENT_LENGTH, CONTENT_LENGTH, false);
        ret = HTTPCli_sendField(&cli, HTTPStd_FIELD_NAME_CONTENT_TYPE, PTGM_CONTENT_TYPE, true);

        if (ret < 0) {
            Log_info1("%d: httpPOST_Task: send failed", ret);
        }

        ret = HTTPCli_sendRequestBody(&cli, g_str_PostSend, POST_DATA_SIZE);
        if (ret < 0) {
            Log_info1("%d: httpPOST_Task: Variable data couldn't be sent", ret);
        }

        ret = HTTPCli_getResponseStatus(&cli);
        if (ret != HTTPStd_OK) {
            Log_info1("%d httpPOST_Task: cannot get status", ret);
        }

        ret = HTTPCli_getResponseField(&cli, data, sizeof(data), &moreFlag);

        if (ret != HTTPCli_FIELD_ID_END) {
            Log_info1("%d: httpPOST_Task: response field processing failed", ret);
        }

        len = 0;
        do {
            ret = HTTPCli_readResponseBody(&cli, data, sizeof(data), &moreFlag);
            if (ret < 0) {
                Log_info1("%d: httpPOST_Task: response body processing failed", ret);
            }

            len += ret;
        } while (moreFlag);

        Log_info1("Received: %d characters", strlen(data));

        HTTPCli_disconnect(&cli);
        HTTPCli_destruct(&cli);

        fdCloseSession(httpPOST_Task_Handle);

        GPIO_write(DEBUG_PIN_SEND, 0); // hardware debug pin off
        Log_write1(UIABenchmark_stop,(xdc_IArg)"HTTP Send");
    }
}
#endif


/*
 *  ======== tcpWorker ========
 *  Task to handle TCP connection. Can be multiple Tasks running
 *  this function.
 */
void tcpWorker(UArg arg0, UArg arg1)
{
Log_write1(UIABenchmark_start,(xdc_IArg)"TCP Worker");
    int  clientfd = (int)arg0;
    //int  bytesRcvd;
    //int  bytesSent;
    char buffer[TCPPACKETSIZE];

    System_printf("tcpWorker: start clientfd = 0x%x\n", clientfd);

    recv(clientfd, buffer, TCPPACKETSIZE, 0);

    switch (buffer[0])
        {
            case '?':
            {
                send(clientfd, "brave new world!", 16, 0);

                break;
            }
            case READ_OUTLET_ID:
            {
                char temp[2];
                temp[0] = ptgmSettings.outlet[buffer[1]]>>8;
                temp[1] = ptgmSettings.outlet[buffer[1]];
                send(clientfd, temp, sizeof(temp), 0);
                break;
            }
            case WRITE_OUTLET_ID:
            {
                ptgmSettings.outlet[buffer[1]] = (buffer[2]<<8 | buffer[3]);
                send(clientfd, COMMAND_ACK, sizeof(COMMAND_ACK), 0);
                break;
            }
            case READ_OUTLET_PHASE_LIMIT:
            {
                char temp[4];
//                temp[0] = *(uint32_t *)&ptgmSettings.channel[buffer[1]*2].channel_limit>>24;
//                temp[1] = *(uint32_t *)&ptgmSettings.channel[buffer[1]*2].channel_limit>>16;
//                temp[2] = *(uint32_t *)&ptgmSettings.channel[buffer[1]*2].channel_limit>>8;
//                temp[3] = *(uint32_t *)&ptgmSettings.channel[buffer[1]*2].channel_limit;
                temp[0] =  *(uint32_t *)&outlet[buffer[1]].limitPhase >> 24;
                temp[1] =  *(uint32_t *)&outlet[buffer[1]].limitPhase >> 16;
                temp[2] =  *(uint32_t *)&outlet[buffer[1]].limitPhase >> 8;
                temp[3] =  *(uint32_t *)&outlet[buffer[1]].limitPhase ;
                send(clientfd, temp, sizeof(temp), 0);
                break;
            }
            case WRITE_OUTLET_PHASE_LIMIT:
            {
                // from hex to float
                *(uint32_t *)&outlet[buffer[1]].limitPhase = ((int32_t)buffer[2] << 24) |
                                                             ((int32_t)buffer[3] << 16) |
                                                             ((int32_t)buffer[4] << 8)  |
                                                             buffer[5];
                send(clientfd, COMMAND_ACK, sizeof(COMMAND_ACK), 0);
                break;
            }
            case REQUEST_FIRMWARE_UPDATE:
            {
                //
                // Firmware Update Request -> 'U' + MAC address (U=0x55 in ascii)
                // eg.:  0x55 0x08 0x00 0x28 0x5a 0x8c 0x56
                //
                if ((buffer[0] == 'U') && (buffer[1] == 0x08) && (buffer[2] == 0x00)
                        && (buffer[3] == 0x28) && (buffer[4] == 0x5a)
                        && (buffer[5] == 0x8c) && (buffer[6] == 0x56))
                {
                    //const char UpdateRequest[] = "Firmware Update. Reseting...";
                    send(clientfd, FIRMWARE_UPDATED_REQUEST, sizeof(FIRMWARE_UPDATED_REQUEST), 0);

                    //
                    // Disable all processor interrupts.  Instead of disabling them
                    // one at a time (and possibly missing an interrupt if new sources
                    // are added), a direct write to NVIC is done to disable all
                    // peripheral interrupts.
                    //
                    HWREG(NVIC_DIS0) = 0xffffffff;
                    HWREG(NVIC_DIS1) = 0xffffffff;
                    HWREG(NVIC_DIS2) = 0xffffffff;
                    HWREG(NVIC_DIS3) = 0xffffffff;
                    HWREG(NVIC_DIS4) = 0xffffffff;

                    //
                    // Also disable the SysTick interrupt.
                    //
                    SysTickIntDisable();
                    SysTickDisable();

                    //
                    // Return control to the boot loader.
                    // This is a call to the ROM bootloader.
                    //
                    ROM_UpdateEMAC(120000000);
                }
        break;
            }
            default:
            {
                send(clientfd, "Unknown Command", 15, 0);
                break;
            }

        }

    System_printf("tcpWorker stop clientfd = 0x%x\n", clientfd);

    close(clientfd);
Log_write1(UIABenchmark_stop,(xdc_IArg)"TCP Worker");
}

/*
 *  ======== tcpHandler ========
 *  Creates new Task to handle new TCP connections.
 */
void tcpHandler(UArg arg0, UArg arg1)
{
    int                status;
    int                clientfd;
    int                server;
    struct sockaddr_in localAddr;
    struct sockaddr_in clientAddr;
    int                optval;
    int                optlen = sizeof(optval);
    socklen_t          addrlen = sizeof(clientAddr);
    Task_Handle        taskHandle;
    Task_Params        taskParams;
    Error_Block        eb;

    server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server == -1) {
        System_printf("Error: socket not created.\n");
        goto shutdown;
    }


    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(arg0);

    status = bind(server, (struct sockaddr *)&localAddr, sizeof(localAddr));
    if (status == -1) {
        System_printf("Error: bind failed.\n");
        goto shutdown;
    }

    status = listen(server, NUMTCPWORKERS);
    if (status == -1) {
        System_printf("Error: listen failed.\n");
        goto shutdown;
    }

    optval = 1;
    if (setsockopt(server, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
        System_printf("Error: setsockopt failed\n");
        goto shutdown;
    }

    while ((clientfd = accept(server, (struct sockaddr *)&clientAddr, &addrlen)) != -1)
    {
        System_printf("tcpHandler: Creating thread clientfd = %d\n", clientfd);

        /* Init the Error_Block */
        Error_init(&eb);

        /* Initialize the defaults and set the parameters. */
        Task_Params_init(&taskParams);
        taskParams.arg0 = (UArg)clientfd;
        taskParams.stackSize = 1280;
        taskHandle = Task_create((Task_FuncPtr)tcpWorker, &taskParams, &eb);
        if (taskHandle == NULL) {
            System_printf("Error: Failed to create new Task\n");
            close(clientfd);
        }

        /* addrlen is a value-result param, must reset for next accept call */
        addrlen = sizeof(clientAddr);
    }

    System_printf("Error: accept failed.\n");

shutdown:
    if (server > 0) {
        close(server);
    }
}


/*
 *  ======== netIPAddrHook ========
 *  This function is called when IP Addr is added/deleted
 */
void netIPAddrHook(unsigned int IPAddr, unsigned int IfIdx, unsigned int fAdd)
{
    Semaphore_post(s_networkIsUp);
}

/*
 *  ======== netOpenHook ========
 *  NDK network open hook used to initialize IPv6
 */
void netOpenHook()
{
    Task_Handle taskHandle;
    Task_Params taskParams;
    Error_Block eb;

    /* Make sure Error_Block is initialized */
    Error_init(&eb);

    /*
     *  Create the Task that farms out incoming TCP connections.
     *  arg0 will be the port that this task listens to.
     */
    Task_Params_init(&taskParams);
    taskParams.stackSize = TCPHANDLERSTACK;
    taskParams.priority = 1;
    taskParams.arg0 = TCPPORT;
    taskHandle = Task_create((Task_FuncPtr)tcpHandler, &taskParams, &eb);
    if (taskHandle == NULL) {
        System_printf("netOpenHook: Failed to create tcpHandler Task\n");
    }

    System_flush();
}
