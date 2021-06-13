#include "DahuaStatus.hpp"

static BOOL g_bNetSDKInitFlag = FALSE;

int sdk_init(DWORD* sdk_status)
{
    // SDK Init
    g_bNetSDKInitFlag = CLIENT_Init(DisConnectFunc, 0);
    if (FALSE == g_bNetSDKInitFlag)
    {
        printf("Init client SDK fail\n");
        return -1;
    }
    else
    {
        printf("Init client SDK done\n");
    }

    DWORD dwNetSdkVersion = CLIENT_GetSDKVersion();
    *sdk_status = CLIENT_GetSDKVersion();
    printf("NetSDK version is {%d}", dwNetSdkVersion);

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
