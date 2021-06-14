#ifndef DAHUASTATUS_HPP
#define DAHUASTATUS_HPP

#include <iostream>

#include <dhnetsdk.h>

static BOOL g_bNetSDKInitFlag = FALSE;

static LLONG g_lLoginHandle = 0L;
static LLONG g_lRealHandle = 0;
static char g_szDevIp[32] = "pollok.dyndns.tv";
static WORD g_nPort = 37777;
static char g_szUserName[64] = "admin";
static char g_szPasswd[64] = "admin";

BYTE *pVideoBuff;
DWORD *pDwBuffSize;

// callbacks
void CALLBACK DisConnectFunc(LLONG lLoginID, char* pchDVRIP, int nDVRPort, LDWORD dwUser);

void CALLBACK HaveReConnect(LLONG loginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);

void CALLBACK RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LONG param, LDWORD dwUser);




int init_test(DWORD* sdk_status);


void run_test();

void end_test();

#endif // DAHUASTATUS_HPP
