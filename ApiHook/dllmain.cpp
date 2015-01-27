// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#pragma comment(lib,"detours.lib")
#import "../WyScInterfaceLib/bin/Debug/WyScInterfaceLib.tlb"
typedef int(WINAPI * PFUNBUSHANDLE)(char *,char *);
static PFUNBUSHANDLE pFunBusHandle_True=NULL;

__declspec(dllexport) int WINAPI  FunBusHandle_Mine(char *inputData,char *outputData)
{
	WyScInterfaceLib::IWyScHookPtr comObj(__uuidof(WyScInterfaceLib::WyScInterFaceComLib));
	long hr=-1;
	BSTR bstrIndata=_bstr_t(inputData);
	BSTR bstrOutData=SysAllocStringByteLen("\0",2048);
	if (bstrOutData == NULL)
		return E_OUTOFMEMORY;

	VARIANT_BOOL bBeforeSend;
	if (comObj)
	{
		bBeforeSend=comObj->beforeSend(&hr,&bstrIndata,&bstrOutData);

		if (!bBeforeSend)
		{
			hr=pFunBusHandle_True(_bstr_t(bstrIndata),outputData);
			bstrOutData=_bstr_t(outputData);
			comObj->afterSend(&hr,&bstrOutData);
		}

		strcpy_s(outputData,2048,_bstr_t(bstrOutData));
		comObj->Release();
	}
	//int hr=0;
	SysFreeString(bstrOutData);
	return hr;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	if (DetourIsHelperProcess()) {
		return TRUE;
	}
	//pFunBusHandle_True=(PFUNBUSHANDLE)DetourFindFunction(_T("SiInterface.dll"),_T("BUSINESS_HANDLE"));
	
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {

		CoInitializeEx(NULL,COINIT_MULTITHREADED);

		HMODULE hinst_Si=LoadLibrary(_T("SiInterface.dll"));
		if (hinst_Si)
		{
			pFunBusHandle_True=(PFUNBUSHANDLE)GetProcAddress(hinst_Si,_T("BUSINESS_HANDLE"));
		}

		if (pFunBusHandle_True)
		{
			DetourRestoreAfterWith();

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach(&(PVOID&)pFunBusHandle_True, FunBusHandle_Mine);
			DetourTransactionCommit();
		}
		
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		CoUninitialize();

		if (pFunBusHandle_True)
		{
			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourDetach(&(PVOID&)pFunBusHandle_True, FunBusHandle_Mine);
			DetourTransactionCommit();
		}
		
	}
	return TRUE;

}

