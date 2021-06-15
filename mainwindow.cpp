#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QByteArray>

#include <iostream>
using namespace std;

#ifndef NEW
#define NEW new(std::nothrow)
#endif

void * RoutineLoginThread(LPVOID lpPara);

DEVICE_LIST 	g_DeviceList;

DHMutex        	g_csDevice;
bool	        g_bExit = false;


void ConvertLoginError2String(int nErrorCode , QString &strErrorCode)
{
    switch(nErrorCode)
    {
    case 0:
        strErrorCode = "Login Success";
        break;

    case 1:
        strErrorCode = "Account or Password Incorrect";
        break;

    case 2:
        strErrorCode = "User Is Not Exist";
        break;

    case 3:
        strErrorCode = "Login Timeout";
        break;

    case 4:
        strErrorCode = "Repeat Login";
        break;

    case 5:
        strErrorCode = "User Account is Locked";
        break;

    case 6:
        strErrorCode = "User In Blacklist";
        break;

    case 7:
        strErrorCode = "Device Busy";
        break;

    case 8:
        strErrorCode = "Sub Connect Failed";
        break;

    case 9:
        strErrorCode = "Host Connect Failed";
        break;

    case 10 :
        strErrorCode = "Max Connect";
        break;

    case 11:
        strErrorCode = "Support Protocol3 Only";
        break;

    case 12:
        strErrorCode = "UKey Info Error";
        break;

    case 13:
        strErrorCode = "No Authorized";
        break;

    case 18:
        strErrorCode = "Device Account isn't Initialized";
        break;

    default:
        strErrorCode = "Unknown Error";
        break;
    }

}

void InitDeviceInfo(DH_Device_Info &stDeviceInfo)
{
    stDeviceInfo.lLoginHandle = 0UL;
    stDeviceInfo.nChannelCount = 0;
    stDeviceInfo.bOnline = FALSE;
    stDeviceInfo.strErrorCode = "";
    stDeviceInfo.nPort = 0;
    stDeviceInfo.nBelongThread = 0;
    stDeviceInfo.nIndex = 0;
    stDeviceInfo.nTimeCount = 0L;
    memset(&stDeviceInfo.szDevIp , 0 , sizeof(stDeviceInfo.szDevIp));
    memset(&stDeviceInfo.szUserName , 0 , sizeof(stDeviceInfo.szUserName));
    memset(&stDeviceInfo.szPassWord , 0 , sizeof(stDeviceInfo.szPassWord));
    memset(&stDeviceInfo.channel , 0 , sizeof(stDeviceInfo.channel));
}

void CALLBACK RealDataCallBackEx(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LLONG param, LDWORD dwUser)
{
    DH_Channel_Info* pChannelInfo = (DH_Channel_Info*)dwUser;
    if(NULL == pChannelInfo)
    {
        return;
    }

    pChannelInfo->dwStatistic = dwBufSize;
}

void CALLBACK DisConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    MainWindow * pThis = (MainWindow *)dwUser;
    if(NULL == pThis)
    {
        return;
    }

    g_csDevice.Lock();

    DEVICE_LIST::iterator it = g_DeviceList.begin();
    while (it != g_DeviceList.end())
    {
        DH_Device_Info *pDeviceInfo = (*it);
        if (pDeviceInfo != NULL)
        {
            if (pDeviceInfo->lLoginHandle == lLoginID)
            {
                pDeviceInfo->bOnline = FALSE;
                pDeviceInfo->strErrorCode = "Device Disconnected";
                int nMinCount = pDeviceInfo->nChannelCount > 16?16:pDeviceInfo->nChannelCount;
                for(int i = 0; i < nMinCount; i++)
                {
                    pDeviceInfo->channel[i].dwStatistic = 0;
                }
                break;
            }
        }

        it++;
    }
    g_csDevice.UnLock();

    return;
}

void CALLBACK  HaveReConnectFunc(LLONG lLoginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser)
{
    if( pchDVRIP == NULL)
        return ;
    g_csDevice.Lock();
    NET_DEVICEINFO deviceInfo = {0};
    DEVICE_LIST::iterator it = g_DeviceList.begin();
    while (it != g_DeviceList.end())
    {
        DH_Device_Info *pDeviceInfo = (*it);
        if (pDeviceInfo == NULL)
        {
            it++;
            continue;
        }

        if (lLoginID == pDeviceInfo->lLoginHandle)
        {
            pDeviceInfo->bOnline = TRUE;
            pDeviceInfo->strErrorCode = "Login Success";
            break;
        }

        it++;
    }
    g_csDevice.UnLock();
    return;
}


void * RoutineLoginThread(LPVOID lpPara)
{
    //  return 0;
    long nThreadID = (long)lpPara;
    if(nThreadID < 0)
    {
        return 0;
    }
    g_csDevice.Lock();

    DEVICE_LIST::iterator it = g_DeviceList.begin();
    while (it != g_DeviceList.end())
    {
        if(g_bExit == true)
        {
            break;
        }

        DH_Device_Info *pDeviceInfo = (*it);

        if (pDeviceInfo == NULL)
        {
            it++;
            continue;
        }

        if (pDeviceInfo->nBelongThread == nThreadID)
        {
            NET_IN_LOGIN_WITH_HIGHLEVEL_SECURITY stInparam;
            memset(&stInparam, 0, sizeof(stInparam));
            stInparam.dwSize = sizeof(stInparam);
            strncpy(stInparam.szIP, pDeviceInfo->szDevIp, sizeof(stInparam.szIP) - 1);
            strncpy(stInparam.szPassword, pDeviceInfo->szPassWord, sizeof(stInparam.szPassword) - 1);
            strncpy(stInparam.szUserName, pDeviceInfo->szUserName, sizeof(stInparam.szUserName) - 1);
            stInparam.nPort = pDeviceInfo->nPort;
            stInparam.emSpecCap = EM_LOGIN_SPEC_CAP_TCP;

            NET_OUT_LOGIN_WITH_HIGHLEVEL_SECURITY stOutparam;
            memset(&stOutparam, 0, sizeof(stOutparam));
            stOutparam.dwSize = sizeof(stOutparam);
            pDeviceInfo->lLoginHandle = CLIENT_LoginWithHighLevelSecurity(&stInparam, &stOutparam);

            ConvertLoginError2String(stOutparam.nError , pDeviceInfo->strErrorCode);
            if (pDeviceInfo->lLoginHandle == 0)
            {
                if(stOutparam.nError != 255)
                {
                  printf("Login failed! error = %d", stOutparam.nError);
                }
                else
                {
                    stOutparam.nError = CLIENT_GetLastError();
                    if(stOutparam.nError ==NET_ERROR_MAC_VALIDATE_FAILED )
                    {
                        printf("Login failed! bad mac address");
                    }
                    else if(stOutparam.nError ==NET_ERROR_SENIOR_VALIDATE_FAILED)
                    {
                        printf("Login failed! senior validate failed");
                    }
                }

                pDeviceInfo->bOnline = FALSE;
                it++;
                continue;
            }
            else
            {
                int nRetLen = 0;
                NET_DEV_CHN_COUNT_INFO stuChn = {sizeof(NET_DEV_CHN_COUNT_INFO)};
                stuChn.stuVideoIn.dwSize = sizeof(stuChn.stuVideoIn);
                stuChn.stuVideoOut.dwSize = sizeof(stuChn.stuVideoOut);
                if(CLIENT_QueryDevState(pDeviceInfo->lLoginHandle, DH_DEVSTATE_DEV_CHN_COUNT, (char*)&stuChn, stuChn.dwSize, &nRetLen))
                {
                    pDeviceInfo->nChannelCount = stuChn.stuVideoIn.nMaxTotal;
                }
                else
                {
                    pDeviceInfo->nChannelCount = stOutparam.stuDeviceInfo.nChanNum;
                }
            }

            pDeviceInfo->bOnline = TRUE;
//           pDeviceInfo->nChannelCount = deviceInfo.nChanNum;
            int nLoopCount = pDeviceInfo->nChannelCount;
            if(nLoopCount > 16)
            {
                nLoopCount = 16;
            }
            for (int i = 0; i < nLoopCount; i++)
            {

                pDeviceInfo->channel[i].lRealPlayHandle = CLIENT_RealPlay(pDeviceInfo->lLoginHandle,i, NULL);
                if (pDeviceInfo->channel[i].lRealPlayHandle != 0)
                {
                    CLIENT_SetRealDataCallBackEx2(pDeviceInfo->channel[i].lRealPlayHandle, RealDataCallBackEx, (LDWORD)&(pDeviceInfo->channel[i]), 0x0f);
                }
                else
                {
                    printf("loginid = %ld;real play failed!\n", pDeviceInfo->lLoginHandle);
                }
            }
        }

        it++;
    }
    g_csDevice.UnLock();
    return 0;
}



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
