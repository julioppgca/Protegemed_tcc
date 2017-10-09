/*
 *    ======== eth_network.c ========
 *    Contains non-BSD sockets code (NDK Network Open Hook)
 */

#include "project_includes/eth_network.h"
#include "project_includes/capture.h"


// debug global variables
uint32_t tcpCount=0;
uint32_t sendError=0;
uint32_t socketErro=0;

// transmit string
char g_str_PostSend[POST_DATA_SIZE];

// prototypes
static inline serializeMsg(void);


static inline serializeMsg(void)
{
    int8_t *pStrPost;   // pointer to g_str_PostSend
    int8_t i;           // block counter

    // initiate pointer
    pStrPost = (int8_t *)&g_str_PostSend[0];

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

///*
// *  ======== printError ========
// */
//void printError(char *errString, int code)
//{
//    System_printf("Error! code = %d, desc = %s\n", code, errString);
//    //System_flush();
//    BIOS_exit(code);
//}

///* TCP/IP client */
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

        do{ // TODO: error log...
            client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(client==-1) socketErro++;
        }while(client < 0);

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
            case 'g': // test
            {
                //send(clientfd, temp, sizeof(temp), 0);
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
