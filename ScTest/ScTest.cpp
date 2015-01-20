// ScTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
typedef  int (WINAPI * PFUNINIT)(char *);
typedef  int(WINAPI * PFUNBUSHANDLE)(char *,char *);

using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	char * outBuf=new char[2048];
	char * inBuf=new char[2048];
	CString strErr;
	int hr;
	try
	{
		HMODULE hinst_Si=LoadLibrary(_T("Siinterface.dll"));
		if (!hinst_Si)
		{
			throw new exception("load siinterface.dll error");
		}
		PFUNINIT funInit=(PFUNINIT)GetProcAddress(hinst_Si,_T("INIT"));
		PFUNBUSHANDLE funBusHandle=(PFUNBUSHANDLE)GetProcAddress(hinst_Si,_T("BUSINESS_HANDLE"));
		if (funInit || funBusHandle)
		{
			throw new exception("Get  init or bus_hanle function address error");
		}
		hr=funInit(outBuf);
		if (hr)
		{
			strErr="init error:";
			strErr+=outBuf;
			throw new exception(strErr);
		}


		//���촫�����

		//////////////////////////////////////////////////////////////////////////
		*outBuf=0;
		hr=funBusHandle(inBuf,outBuf);
		if (hr)
		{
			strErr="buss_handle error:";
			strErr+=outBuf;
			throw new exception(strErr);
		}

		printf("buss_handle invoke success:\r\noutputData:\r\n");
		printf(outBuf);

	}
	catch (exception* e)
	{
		printf(e->what());
	}
	delete[] outBuf;
	delete[] inBuf;
	return 0;
}

