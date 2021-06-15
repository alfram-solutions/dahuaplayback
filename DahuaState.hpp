#ifndef DAHUASTATE_H
#define DAHUASTATE_H

#include <dhnetsdk.h>

static BOOL g_bNetSDKInitFlag;
static LLONG g_lLoginHandle;
static LLONG g_lRealHandle;
static char g_szDevIp[32];
static WORD g_nPort;
static char g_szUserName[64];
static char g_szPasswd[64];

// callbacks
void CALLBACK DisConnectFunc(LLONG lLoginID, char* pchDVRIP, int nDVRPort, LDWORD dwUser);

void CALLBACK HaveReConnect(LLONG loginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

void CALLBACK RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, LDWORD dwUser);

struct DahuaState
{



    DWORD sdk_status;

    DahuaState();

    int init_test();

    void run_test();

    void end_test();

};

#endif // DAHUASTATE_H
