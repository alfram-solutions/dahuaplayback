#include "DahuaStatus.hpp"

static BOOL g_bNetSDKInitFlag = FALSE;

int sdk_init(DWORD* sdk_status)
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

    return 0;
}

void CALLBACK DisConnectFunc(LLONG lLoginID, char* pchDVRIP, int nDVRPort, LDWORD dwUser)
{
    printf("Call DisConnectFunc\n");
    printf("lLoginID[0x%x]", lLoginID);
    if (NULL != pchDVRIP)
    {
    printf("pchDVRIP[%s]\n", pchDVRIP);
    }
    printf("nDVRPort[%d]\n", nDVRPort);
    printf("dwUser[%p]\n", dwUser);
    printf("\n");
}
