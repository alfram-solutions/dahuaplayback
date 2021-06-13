#ifndef DAHUASTATUS_HPP
#define DAHUASTATUS_HPP

#include <stdio.h>

#include <dhnetsdk.h>

// callbacks
void CALLBACK DisConnectFunc(LLONG lLoginID, char* pchDVRIP, int nDVRPort, LDWORD dwUser);

void CALLBACK HaveReConnect(LLONG loginID, char *pchDVRIP, LLONG nDVRPort, LDWORD dwUser);

int sdk_init(DWORD* sdk_status);

#endif // DAHUASTATUS_HPP
