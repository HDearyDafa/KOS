// KOS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include <gdiplus.h>
#include "KOS.h"
#include <iostream>

using namespace::std;

typedef struct TaskStatus {
	int Status;
	int Input;
} TASKSTATUS, *PTASKSTATUS;

DWORD WINAPI KOS_Dispatcher_0(LPVOID lpParam)
{
	PTASKSTATUS Dispatcher_0__Status = (PTASKSTATUS)lpParam;
	Dispatcher_0__Status->Status = 0;
	return 0;
}


int KOS_Kernel(int KOSMode)
{
	int KOS__Status = 0;
	INT32 KOS__TaskRequestQueue = 0;
	bool KOS__InterruptRequest = false;
	HANDLE  hThreadArray[4];
	TASKSTATUS pDispatcherStatusArray[4];
	DWORD   dwThreadIdArray[4];
	while (true)
	{
		if (KOSMode > 3)
		{
			KOS__Status |= 0x00000001;
		}
		
		if (KOS__InterruptRequest)
		{
			hThreadArray[0] = CreateThread(NULL, 0, KOS_Dispatcher_0, &pDispatcherStatusArray[0], 0, &dwThreadIdArray[0]);
		}

		for (int i=0; i < 4; i++)
		{
			KOS__Status |= (pDispatcherStatusArray[i].Status) << i;
		}

		if (KOS__Status != 0)
		{
			break;
		}

	}
	return KOS__Status;
}

int main()
{
	int OSStatus = 0;
	while(true)
	{
		int OSMode = 0;

		cout << "Input OSMode";
		cin >> OSMode;

		OSStatus = KOS_Kernel(OSMode);

		if (OSStatus != 0)
		{
			printf("OS error : %d", OSStatus);
		}
	}
	return 0;
}

