#include "DahuaStatus.hpp"

#include <cstring>
#include <unistd.h>



//static BOOL g_bNetSDKInitFlag = FALSE;

//static LLONG g_lLoginHandle = 0L;
//static LLONG g_lRealHandle = 0;
//static char g_szDevIp[32] = "pollok.dyndns.tv";
//static WORD g_nPort = 37777;
//static char g_szUserName[64] = "admin";
//static char g_szPasswd[64] = "admin";

//static BYTE *pVideoBuff;


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
            sleep(10);
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

    if (0 == g_lLoginHandle)
    {
        return;
    }

    // realize real-time monitoring




    // start real-time monitoring
    int nChannelID = 0; // preview channel
    DH_RealPlayType emRealPlayType = DH_RType_Realplay;
    g_lRealHandle = CLIENT_RealPlayEx(g_lLoginHandle, nChannelID, NULL, emRealPlayType);

    if (0 == g_lRealHandle)
    {
        std::cout << "CLIENT_RealPlayEx: failed! Error code: " << CLIENT_GetLastError() << std::endl;
        return;
    }
    else {
        DWORD dwFlag = 0x00000001;
        if (FALSE == CLIENT_SetRealDataCallBackEx(g_lRealHandle,
                                                  &RealDataCallBackEx, NULL, dwFlag))
        {
            std::cout << "CLIENT_SetRealDataCallBackEx: failed! Error code: " << CLIENT_GetLastError() << std::endl;
            return;
        }
    }
    std::cout << "Running test..." << std::endl;
    sleep(10);
}

void end_test()
{
    std::cout << "Running end test..." << std::endl;

    std::cout << "input any key to quit" << std::endl;
    getchar();

    // Close preview
    if ( 0 != g_lRealHandle)
    {
        if (FALSE == CLIENT_StopRealPlayEx(g_lRealHandle))
        {
            std::cout << "CLIENT_StopRealPlayEx failed, g_lRealHandle " << g_lRealHandle << " Last Error " << CLIENT_GetLastError() << std::endl;

        }
        else
        {
            g_lRealHandle = 0;
        }
    }
    // exit device
    // Logout operation
    if (0 == g_lLoginHandle)
    {
        if (FALSE == CLIENT_Logout(g_lLoginHandle))
        {
            std::cout << "CLIENT_Logout Failed. Last error: " << CLIENT_GetLastError() << std::endl;
        }
        else
        {
            g_lLoginHandle = 0;
        }
    }
    // clean up resource
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

void CALLBACK RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer,
                                 DWORD dwBufSize, LONG param, LDWORD dwUser)
{
    if (lRealHandle == g_lRealHandle)
    {
        switch(dwDataType)
        {
        case 0:
            // original A/V hybrid data
            //std::cout << "Receive real data, param: lRealHandle " << lRealHandle << " dwDataType " << dwDataType << " pBuffer " << pBuffer << " dwBufSize " << dwBufSize << " param " << param << " dwUser " << dwUser << std::endl;
            pVideoBuff = pBuffer;
            pDwBuffSize = &dwBufSize;
        }
    }
}


