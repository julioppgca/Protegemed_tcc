/*
 *    ======== eth_network.c ========
 *    Contains non-BSD sockets code (NDK Network Open Hook)
 */

#include "project_includes/eth_network.h"
#include "project_includes/capture.h"

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
    char data[POST_DATA_SIZE];
    int ret;
    int len;
    char CONTENT_LENGTH[3];
    struct sockaddr_in addr;

    /* copy task param to a local variable */
    Semaphore_pend(s_critical_section, BIOS_WAIT_FOREVER);
        strcpy(data,(char*)arg0);//strcpy(data, g_str_PostSend);
    Semaphore_post(s_critical_section);

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

    ret = HTTPCli_sendRequestBody(&cli, data, strlen(data));
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
}

/*
 *  ======== tcpWorker ========
 *  Task to handle TCP connection. Can be multiple Tasks running
 *  this function.
 */
void tcpWorker(UArg arg0, UArg arg1)
{
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
            case 'g': // Create HTML POST
            {
                static Task_Handle taskHandle;
                Task_Params taskParams;
                Error_Block eb;

                    Error_init(&eb);
                    Task_Params_init(&taskParams);
                    taskParams.stackSize = HTTPTASKSTACKSIZE;
                    taskParams.priority = 1;
                    taskHandle = Task_create((Task_FuncPtr)httpPOST_Task, &taskParams, &eb);
                    if (taskHandle == NULL)
                        {
                            printError("netIPAddrHook: Failed to create HTTP Task\n", -1);
                        }

                send(clientfd, "http Post", 9, 0);
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

    while ((clientfd =
            accept(server, (struct sockaddr *)&clientAddr, &addrlen)) != -1) {

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
