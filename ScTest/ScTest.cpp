// ScTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
typedef  int (WINAPI * PFUNINIT)(char *);
typedef  int(WINAPI * PFUNBUSHANDLE)(char *,char *);
int _tmain(int argc, _TCHAR* argv[])
{
	printf("hello world");
	HMODULE hinst_Si=LoadLibrary(_T("Siinterface.dll"));
	if (!hinst_Si)
	{
		return -1;
	}
	PFUNINIT funInit=(PFUNINIT)GetProcAddress(hinst_Si,_T("INIT"));
	PFUNBUSHANDLE funBusHandle=(PFUNBUSHANDLE)GetProcAddress(hinst_Si,_T("BUSINESS_HANDLE"));
	if (funInit || funBusHandle)
	{
		return -2;
	}
	char * ErrorBuf=new char[2048];
	
	CString strError;
	int hr=funInit(ErrorBuf);
	if (hr)
	{
		printf(ErrorBuf);
		delete[] ErrorBuf;
		return -3;
	}
	

	delete[] ErrorBuf;
	return 0;
}

