#ifndef DAHUASTATUS_HPP
#define DAHUASTATUS_HPP

#include <iostream>

#include <dhnetsdk.h>

// callbacks
void CALLBACK DisConnectFunc(LLONG lLoginID, char* pchDVRIP, int nDVRPort, LDWORD dwUser);

void CALLBACK HaveReConnect(LLONG loginID, char *pchDVRIP, LONG nDVRPort, LDWORD dwUser);



int init_test(DWORD* sdk_status);


void run_test();

void end_test();

#endif // DAHUASTATUS_HPP
