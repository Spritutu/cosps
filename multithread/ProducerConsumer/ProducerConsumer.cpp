// ProducerConsumer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ProducerConsumer.h"
#include "SyncQueue.h"
#include "ManualEventQueue.h"
#include "AutoEventQueue.h"

#if defined ENABLE_PTHREAD
#include "PosixCVQueue.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

long nProductID = 0;

const int nSleepTime = 2000;
const int nProducerCount = 2;
const int nConsumerCount = 7;
const int nQueueCapacity = 10;
const int nProductCount = 11;

DWORD WINAPI ThreadProcP(LPVOID lpParameter)
{
	CSyncQueue* pQueue = (CSyncQueue*)lpParameter;
	
	int nID;
	for(int i = 0; i < nProductCount; i++)
	{
//		Sleep(nSleepTime);
		nID = ::InterlockedIncrement(&nProductID);
		pQueue->Put((void*)nID);
		printf("Producer [%05d] produce [%02d]\n", GetCurrentThreadId(), nID);
	}
	
	return 0;
}

bool consume(CSyncQueue* pQueue, void* ptr)
{
	printf("Consumer [%05d] consume [%02d]\n", GetCurrentThreadId(), (int)ptr);
	if(!ptr)
	{
		pQueue->Put(NULL);
		return false;
	}
	int id = (int)ptr;
	if(id == nProducerCount * nProductCount)
	{
		pQueue->Put(NULL);
		return false;
	}
	return true;
}
DWORD WINAPI ThreadProcC(LPVOID lpParameter)
{
	CSyncQueue* pQueue = (CSyncQueue*)lpParameter;
	
	void* ptr = NULL;
	
	while(TRUE)
	{
		Sleep(nSleepTime);
		ptr = pQueue->Get();
		
		if(!consume(pQueue, ptr))
		{
			printf("Consumer [%05d] ended\n", GetCurrentThreadId());
			break;
		}
	}
	
	return 0;
}

void TestProducerConsumer(int nCountP, int nCountC, int nMax, int nType = 0);

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		CString strHello;
		strHello.LoadString(IDS_HELLO);
		cout << (LPCTSTR)strHello << endl;
	}

// 	printf("===test 1===\n");
// 	TestProducerConsumer(nProducerCount, nConsumerCount, nQueueCapacity, 0);
// 
// 	printf("\n\n===test 2===\n");
// 	TestProducerConsumer(nProducerCount, nConsumerCount, nQueueCapacity, 1);

	printf("\n\n===test 3===\n");
	TestProducerConsumer(nProducerCount, nConsumerCount, nQueueCapacity, 2);

	return nRetCode;
}

void TestProducerConsumer(int nCountP, int nCountC, int nMax, int nType)
{
	nProductID = 0;
	CSyncQueue* pSyncQueue = NULL;
	
	if(nType % 3 == 0)
	{
		pSyncQueue = new CManualEventQueue(nMax);
	}
	else if(nType % 3 == 1)
	{
		pSyncQueue = new CAutoEventQueue(nMax);
	}
	else
	{
#if defined ENABLE_PTHREAD
		pSyncQueue = new CPosixCVQueue(nMax);
#else
		pSyncQueue = new CAutoEventQueue(nMax);
#endif
	}
	
	HANDLE* hThreads = new HANDLE[nCountP + nCountC];
	
	int i, j;
	DWORD dwThreadId;
	for(i = 0; i < nCountC; i++)
	{
		hThreads[i] = ::CreateThread(NULL, 0, ThreadProcC, (LPVOID)pSyncQueue, 0, &dwThreadId);
		if(hThreads[i] == NULL)
		{
			printf("Failed to create thread [%02d], GetLastError() = %d\n", i, GetLastError());
			return;
		}
	}
	for(j = 0; j < nCountP; j++)
	{
		hThreads[nCountC + j] = ::CreateThread(NULL, 0, ThreadProcP, (LPVOID)pSyncQueue, 0, &dwThreadId);
		if(hThreads[nCountC + j] == NULL)
		{
			printf("Failed to create thread [%02d], GetLastError() = %d\n", nCountC + j, GetLastError());
			return;
		}
	}
	
	::WaitForMultipleObjects(nCountC + nCountP, hThreads, TRUE, INFINITE);
	printf("All Threads ended\n");
}


