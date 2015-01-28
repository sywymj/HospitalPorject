// ScTest.cpp : 定义控制台应用程序的入口点。
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
		int i;
		cout<<"load siinterface";
		cin>>i;
		HMODULE hinst_Si=LoadLibrary(_T("SiInterface.dll"));
		if (!hinst_Si)
		{
			throw new exception("load siinterface.dll error");
		}
		PFUNINIT funInit=(PFUNINIT)GetProcAddress(hinst_Si,_T("INIT"));
		PFUNBUSHANDLE funBusHandle=(PFUNBUSHANDLE)GetProcAddress(hinst_Si,_T("BUSINESS_HANDLE"));

		/*char * pathBuf=new char[1024];
		memset(pathBuf,0,1024);
		GetCurrentDirectory(1020,pathBuf);
		printf(pathBuf);
		printf("\r\n");


		memset(pathBuf,0,1024);
		GetModuleFileName(hinst_Si,pathBuf,1020);
		GetCurrentDirectory(1020,pathBuf);
		printf(pathBuf);
		printf("\r\n");*/


		if (!(funInit && funBusHandle))
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


		memset(outBuf,0,2048);
		memset(inBuf,0,2048);
		//构造传入参数
		//strcpy_s(inBuf,2047,_T("9120^11003^admin^^20150127192930-11003-0001^0000^^"));
		sprintf_s(inBuf,2047,"9120^11003^admin^^20150127192930-11003-%04d^0000^^",i);
		//////////////////////////////////////////////////////////////////////////
		
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

	cout<<"finish\r\n";
	int i;
	cin>>i;
	delete[] outBuf;
	delete[] inBuf;
	return 0;
}

