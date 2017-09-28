/*
 *    ======== eth_network.c ========
 *    Contains non-BSD sockets code (NDK Network Open Hook)
 */

#include "project_includes/eth_network.h"
#include "project_includes/capture.h"

#define _LEN 4200
     char lixo[_LEN];

//void client(void);

     uint32_t tcpCount=0;

uint32_t sendError=0, socketErro=0;
//char j,temp[2500];
//char g_str_PostSend[POST_DATA_SIZE];

/*
 *  ======== printError ========
 */
void printError(char *errString, int code)
{
    System_printf("Error! code = %d, desc = %s\n", code, errString);
    //System_flush();
    BIOS_exit(code);
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
    char *data;//data[POST_DATA_SIZE];
    int ret;
    int len;
    char CONTENT_LENGTH[3];
    struct sockaddr_in addr;

    //while(1)
    {
      //Semaphore_pend(s_doHttpPost, BIOS_WAIT_FOREVER);
        Log_write1(UIABenchmark_start,(xdc_IArg)"http POST Task");
    /* copy task param to a local variable */
    //Semaphore_pend(s_critical_section, BIOS_WAIT_FOREVER);
        data=g_str_PostSend;//strcpy(data, g_str_PostSend);//strcpy(data,(char*)arg0);//strcpy(data, g_str_PostSend);
    //Semaphore_post(s_critical_section);

    /* Debug connection with a standard data string, uncomment below */
    //strcpy(data, PTGM_TEST_DATA);
    len = strlen(data);//len = sizeof(PTGM_TEST_DATA);
    sprintf(CONTENT_LENGTH, "%d", len);

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
        Log_info1("%d: httpPOST_Task: connect failed, retrying..", ret);
        ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, NULL);
        if (ret < 0) {
                //sendError++;
                Log_info1("%d: httpPOST_Task: connect failed, retrying..2", ret);
                ret = HTTPCli_connect(&cli, (struct sockaddr *)&addr, 0, NULL);
        }
    }

    ret = HTTPCli_sendRequest(&cli, HTTPStd_POST, PTGM_URI, true);
    if (ret < 0) {
        //sendError++;
        Log_info1("%d: httpPOST_Task: send failed", ret);
    }

    ret = HTTPCli_sendField(&cli, HTTPStd_FIELD_NAME_CONTENT_LENGTH, CONTENT_LENGTH, false);
    ret = HTTPCli_sendField(&cli, HTTPStd_FIELD_NAME_CONTENT_TYPE, PTGM_CONTENT_TYPE, true);

    if (ret < 0) {
        sendError++;
        Log_info1("%d: httpPOST_Task: send failed", ret);
    }

    ret = HTTPCli_sendRequestBody(&cli, data, strlen(data));
    if (ret < 0) {
        //sendError++;
        Log_info1("%d: httpPOST_Task: Variable data couldn't be sent", ret);
    }

    ret = HTTPCli_getResponseStatus(&cli);
    if (ret != HTTPStd_OK) {
        //sendError++;
        Log_info1("%d httpPOST_Task: cannot get status", ret);
    }

    ret = HTTPCli_getResponseField(&cli, data, sizeof(data), &moreFlag);

    if (ret != HTTPCli_FIELD_ID_END) {
        //sendError++;
        Log_info1("%d: httpPOST_Task: response field processing failed", ret);
    }

    len = 0;
    do {
        ret = HTTPCli_readResponseBody(&cli, data, sizeof(data), &moreFlag);
        if (ret < 0) {
            //sendError++;
            Log_info1("%d: httpPOST_Task: response body processing failed", ret);
        }

        len += ret;
    } while (moreFlag);

    Log_info1("Received: %d characters", strlen(data));

    HTTPCli_disconnect(&cli);
    HTTPCli_destruct(&cli);

    Log_write1(UIABenchmark_stop,(xdc_IArg)"http POST Task");
    }
    moreFlag=0;
}


/* TCP/IP client */
void dataSendTcpIp(void)
{

    memset(lixo, 'A', _LEN);
    int client;
    int status;
    struct sockaddr_in serverAddr;


    Semaphore_pend(s_networkIsUp, BIOS_WAIT_FOREVER);

    while (1)
    {
        Semaphore_pend(s_doDataSendTcpIp, BIOS_WAIT_FOREVER);
        Log_write1(UIABenchmark_start,(xdc_IArg)"TCP Send");

        fdOpenSession(dataSendTcpIp_Handle);

        /*---- Create the socket. The three arguments are: ----*/
        /* 1) Internet domain 2) Stream socket 3) Default protocol (TCP in this case) */
        //clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        do{
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
        serverAddr.sin_addr.s_addr = htonl(3232236183); //inet_addr(PTGM_HOSTNAME);
        serverAddr.sin_port = htons(7891); // TcpIp server listen Port = 7891
        memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

        /*---- Connect the socket to the server using the address struct ----*/
        status = connect(client, (struct sockaddr *) &serverAddr,sizeof(serverAddr));
        if (status == -1)
        {
            Log_info0("connection refused");
            sendError++;
            goto shutdown;
        }

        send(client, lixo, _LEN, 0);
        tcpCount++;
        //recv(client, lixo, _LEN, 0);

        close(client);


        shutdown:
            if (client > 0) {
                close(client);
            }

        fdCloseSession(dataSendTcpIp_Handle);
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
                //char temp[115]="POST / HTTP/1.1\nHost: 192.168.2.151\nContent-Length: 7\nContent-Type: application/x-www-form-urlencoded\nTYPE=04";
                //float32_t value = 3.2;

//                char i;
//                Log_write1(UIABenchmark_start,(xdc_IArg)"Serialize");
//                for (i = 0, j=0; i < 240; i++)
//                {
//                    temp[j] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 24;
//                    temp[j + 1] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 16;
//                    temp[j + 2] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 8;
//                    temp[j + 3] = *(uint32_t *) &msgBuffer[0].phaseFFT[i];
//                    temp[j + 4] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 24;
//                    temp[j + 5] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 16;
//                    temp[j + 6] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 8;
//                    temp[j + 7] = *(uint32_t *) &msgBuffer[0].phaseFFT[i];
//                    temp[j + 8] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 24;
//                    temp[j + 9] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 16;
//                    temp[j + 10] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 8;
//                    temp[j + 11] = *(uint32_t *) &msgBuffer[0].phaseFFT[i];
//                    temp[j + 12] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 24;
//                    temp[j + 13] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 16;
//                    temp[j + 14] = *(uint32_t *) &msgBuffer[0].phaseFFT[i] >> 8;
//                    temp[j + 15] = *(uint32_t *) &msgBuffer[0].phaseFFT[i];
//                    j=j+16;
//                }
//                Log_write1(UIABenchmark_stop,(xdc_IArg)"Serialize");
                send(clientfd, temp, sizeof(temp), 0);
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
    buffer[0]=0;
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
//    static Task_Handle httpPOST_Handle;
//    Task_Params httpPOST_Params;
//    Error_Block httpPOST_eb;
//
//    Error_init(&httpPOST_eb);
//    Task_Params_init(&httpPOST_Params);
//    httpPOST_Params.stackSize = HTTPTASKSTACKSIZE;
//    httpPOST_Params.priority = 1;
//    httpPOST_Handle = Task_create((Task_FuncPtr) httpPOST_Task,
//                                  &httpPOST_Params, &httpPOST_eb);
//    if (httpPOST_Handle == NULL)
//    {
//        Log_info0("captureTask: Failed to create HTTP POST Task");
//    }
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
