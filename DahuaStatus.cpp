#include "DahuaStatus.hpp"

#include <cstring>
#include <unistd.h>

static BOOL g_bNetSDKInitFlag = FALSE;

static LLONG g_lLoginHandle = 0L;
static char g_szDevIp[32] = "pollok.dyndns.tv";
static WORD g_nPort = 37777;
static char g_szUserName[64] = "admin";
static char g_szPasswd[64] = "admin";


int init_test(DWORD* sdk_status)
{
    // SDK Init
    g_bNetSDKInitFlag = CLIENT_Init(DisConnectFunc, 0);
    if (FALSE == g_bNetSDKInitFlag)
    {
        std::cout << ("Init client SDK fail") << std::endl;
        return -1;
    }
    else
    {
        printf("Init client SDK done\n");
    }

    DWORD dwNetSdkVersion = CLIENT_GetSDKVersion();
    *sdk_status = CLIENT_GetSDKVersion();
    std::cout << "NetSDK version is " << dwNetSdkVersion << std::endl;

    // Set reconnection callback
    // optional
    CLIENT_SetAutoReconnect(&HaveReConnect, 0);

    // Set device connectio  timeout and trial times
    // optional
    int nWaitTime = 5000;
    int nTryTimes = 3;
    CLIENT_SetConnectTime(nWaitTime, nTryTimes);

    // Set more network parameters
    // optional
    NET_PARAM stuNetParm = {0};
    stuNetParm.nConnectTime = 3000; // The timeout of connection when login
    CLIENT_SetNetworkParam(&stuNetParm);


    // LOGIN setup
    NET_DEVICEINFO_Ex stDevInfo = {0};
    int nError = 0;

    while (0 == g_lLoginHandle)
    {
        // Login to device
        g_lLoginHandle = CLIENT_LoginEx2(g_szDevIp, g_nPort, g_szUserName,
                                         g_szPasswd, EM_LOGIN_SPEC_CAP_TCP, NULL, &stDevInfo, &nError);

        if (0 == g_lLoginHandle)
        {
            std::cout << "CLIENT_LoginEx " << g_szDevIp << g_nPort << "Failed!" << "Last Error: " << CLIENT_GetLastError() << std::endl;

        }
        else
        {
            std::cout << "CLIENT_LoginEx " << g_szDevIp << g_nPort << "Success" << std::endl;
            // for first login wait for some data to be initialised first
            sleep(500);
            std::cout << "ready..." << std::endl;
        }


    }



    return 0;
}


void run_test()
{
    if (FALSE == g_bNetSDKInitFlag)
    {
        return;
    }
    std::cout << "Running test..." << std::endl;
}

void end_test()
{
    std::cout << "Running end test..." << std::endl;
    // Logout operation
    if (TRUE == g_bNetSDKInitFlag)
    {
        CLIENT_Cleanup();
        g_bNetSDKInitFlag = FALSE;
    }
}

void CALLBACK DisConnectFunc(LLONG lLoginID, char* pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    std::cout << "Call DisConnectFunc" << std::endl;
    std::cout << "lLoginID: " << lLoginID << std::endl;;
    if (NULL != pchDVRIP)
    {
        std::cout << "pchDVRIP" <<  pchDVRIP << std::endl;;
    }
    std::cout << "nDVRPor: " << nDVRPort << std::endl;
    std::cout << "dwUser[%p]\n" << dwUser << std::endl;
}

void CALLBACK HaveReConnect(LLONG lLongID, char *pchDVRIP, int nDVRPort, LDWORD dwUser)
{
    std::cout << "Call HaveReConnecf" << std::endl;
    std::cout << "lLoginId: " << lLongID << std::endl;
    if (NULL != pchDVRIP)
    {
        std::cout << "pchDVRIP " << pchDVRIP << std::endl;
    }
    std::cout << "nDVRPort " << nDVRPort << std::endl;
    std::cout << "dwUser " << dwUser << std::endl;

}
