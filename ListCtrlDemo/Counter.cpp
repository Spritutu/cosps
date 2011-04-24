#include "StdAfx.h"
#include "Counter.h"

UINT CCounter::CountThreadProc(LPVOID lpvData)
{
	LPCountThreadParam lpThreadParam = (LPCountThreadParam)lpvData;
	ASSERT(lpThreadParam && lpThreadParam->hwndMain);

	//Start to work
	LRESULT lresult = ::SendMessage(lpThreadParam->hwndMain, WM_START_COUNT, 0, 0);
	HWND hProgWnd = (HWND)lresult;
	ASSERT(hProgWnd);

	//Set current progress status
	LPUpdateProgressParam lpProgressParam = new UpdateProgressParam;
	lpProgressParam->nPos = 0;
	_stprintf(lpProgressParam->sFile, "%s", _T("Calculating the files count..."));
	::SendMessage(hProgWnd, WM_PROGRESS_UPDATE, (WPARAM)lpProgressParam, 0);
	delete lpProgressParam;
	lpProgressParam = NULL;

	//Calculate the files count
	CFileVisitor* pVisitor = new CFileCountVisitor(hProgWnd);

	UINT cAllFiles = 0;
	int i, count = lpThreadParam->dirList.GetSize();
	int result = 0, prev = 0;
	for(i = 0; i < count; i++)
	{
		result = EnumDirectory(lpThreadParam->dirList.GetAt(i), TRUE, pVisitor);
		if(result == -1)
		{
			break;
		}
		AfxTrace("dir=%s, count=%d\n", lpThreadParam->dirList.GetAt(i), pVisitor->GetResult() - prev);
		prev = pVisitor->GetResult();
	}
	cAllFiles = pVisitor->GetResult();
	delete pVisitor;
	pVisitor = NULL;

	if(result == -1)
	{
		//End the works
		::SendMessage(lpThreadParam->hwndMain, WM_END_COUNT, 0, 0);

		delete lpThreadParam;
		lpThreadParam = NULL;

		return -1;
	}

	//Update the progress range
	::SendMessage(hProgWnd, WM_PROGRESS_SET_RANGE, 0, cAllFiles);
	
	//Do the works
	pVisitor = new CFilePrintVisitor(hProgWnd);
	prev = 0;
	for(i = 0; i < count; i++)
	{
		if(EnumDirectoryFileFirst(lpThreadParam->dirList.GetAt(i), TRUE, pVisitor) == -1)
		{
			break;
		}
		AfxTrace("print dir=%s, count=%d\n", lpThreadParam->dirList.GetAt(i), pVisitor->GetResult() - prev);
		prev = pVisitor->GetResult();
	}
	delete pVisitor;
	pVisitor = NULL;

	//Show the last status
	Sleep(1000);

	//End the works
	::SendMessage(lpThreadParam->hwndMain, WM_END_COUNT, 0, 0);

	delete lpThreadParam;
	lpThreadParam = NULL;

	return 0;
}

int CCounter::EnumDirectory(LPCTSTR lpszDirName, BOOL bRecursive, CFileVisitor* pVisitor)
{
	ASSERT(lpszDirName);
	ASSERT(pVisitor);
	
	//Find Dir
	CString sCurDir;
	sCurDir.Format("%s\\*", lpszDirName);
	
	//Init
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(sCurDir, &FindFileData);
	
	DWORD dwError;
	if (hFind == INVALID_HANDLE_VALUE)
    {
		dwError = GetLastError();
		AfxTrace("FindFirstFile Error: %d, %s\n", dwError, sCurDir);
        return dwError;
    }
	
	CString sCurFile;
	BOOL hasMore;
	for(hasMore = (hFind != INVALID_HANDLE_VALUE); hasMore; hasMore = FindNextFile(hFind, &FindFileData))
	{
		//Ignore hidden files, current, and parent directory
		if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN != 0)
			|| _tcscmp(FindFileData.cFileName, ".") == 0
			|| _tcscmp(FindFileData.cFileName, "..") == 0)
		{
			continue;
		}
		//1. File
		if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
        {
			sCurFile.Format("%s\\%s", lpszDirName, FindFileData.cFileName);
            if(pVisitor->VisitFile(sCurFile) == -1)
			{
				AfxTrace ("VisitFile request to quit\n");
				FindClose(hFind);
				return -1;
			}
        }
		//2. Directory
		else if( bRecursive && ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) )
		{
			sCurFile.Format("%s\\%s", lpszDirName, FindFileData.cFileName);		
            if(EnumDirectory(sCurFile, bRecursive, pVisitor) == -1)
			{
				AfxTrace ("VisitFile request to quit\n");
				FindClose(hFind);
				return -1;
			}
		}
	}
	dwError = GetLastError();
	FindClose(hFind);
    if (dwError != ERROR_NO_MORE_FILES)
    {
		AfxTrace ("FindNextFile Error: %d, %s\n", dwError, sCurFile);
        return dwError;
    }
	dwError = 0;
	return dwError;
}

int CCounter::EnumDirectoryFileFirst(LPCTSTR lpszDirName, BOOL bRecursive, CFileVisitor* pVisitor)
{
	ASSERT(lpszDirName);
	ASSERT(pVisitor);

	//Find Dir
	CString sCurDir;
	sCurDir.Format("%s\\*", lpszDirName);
	
	//Init
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(sCurDir, &FindFileData);
	
	DWORD dwError;
	if (hFind == INVALID_HANDLE_VALUE)
    {
		dwError = GetLastError();
		AfxTrace("FindFirstFile Error: %d\n", dwError);
        return dwError;
    }
	
	CString sCurFile;
	BOOL hasMore;
	for(hasMore = (hFind != INVALID_HANDLE_VALUE); hasMore; hasMore = FindNextFile(hFind, &FindFileData))
	{
		//Ignore hidden files
		//1. File
		if( (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0 
			&& (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == 0)
        {
			sCurFile.Format("%s\\%s", lpszDirName, FindFileData.cFileName);
            if(pVisitor->VisitFile(sCurFile) == -1)
			{
				AfxTrace ("VisitFile request to quit\n");
				FindClose(hFind);
				return -1;
			}
        }
	}
	dwError = GetLastError();
	FindClose(hFind);
    if (dwError != ERROR_NO_MORE_FILES)
    {
		AfxTrace ("FindNextFile Error: %d\n", dwError);
        return dwError;
    }

	//No need to recursive find more
	if(!bRecursive)
	{
		dwError = 0;
		return dwError;
	}
	
	
	//Find directories
	hFind = FindFirstFile(sCurDir, &FindFileData);	
	if (hFind == INVALID_HANDLE_VALUE)
    {
		dwError = GetLastError();
		AfxTrace("Directory FindFirstFile Error: %d\n", dwError);
        return dwError;
    }
	
	for(hasMore = (hFind != INVALID_HANDLE_VALUE); hasMore; hasMore = FindNextFile(hFind, &FindFileData))
	{
		if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 
			&& (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) == 0
            && _tcscmp(FindFileData.cFileName, ".") != 0
            && _tcscmp(FindFileData.cFileName, "..") != 0)
		{
			sCurFile.Format("%s\\%s", lpszDirName, FindFileData.cFileName);		
            if(EnumDirectoryFileFirst(sCurFile, bRecursive, pVisitor) == -1)
			{
				AfxTrace ("VisitFile request to quit\n");
				FindClose(hFind);
				return -1;
			}
		}
	}
	dwError = GetLastError();
	FindClose(hFind);
	if (dwError != ERROR_NO_MORE_FILES)
    {
		AfxTrace ("Directory FindNextFile Error: %d\n", dwError);
        return dwError;
    }
    dwError = 0;
	return dwError;
}

CFileCountVisitor::CFileCountVisitor(HWND hWnd) : m_hProgWnd(hWnd), m_nCount(0), m_timeCost(10)
{
}

int CFileCountVisitor::VisitFile(LPCTSTR lpszFileName)
{
	m_nCount++;
	m_timeCost.UpdateCurrClock();
	if(m_timeCost.IsTimeOut())
	{
		//Do the check works
		BOOL isCancelled = ::SendMessage(m_hProgWnd, WM_PROGRESS_IS_CANCELLED, 0, 0);
		if(isCancelled)
		{
			return -1;
		}
		m_timeCost.UpdateLastClock();
	}
	return m_nCount;
}

CFilePrintVisitor::CFilePrintVisitor(HWND hWnd) : m_hProgWnd(hWnd), m_nCount(0)
{
}
int CFilePrintVisitor::VisitFile(LPCTSTR lpszFileName)
{
	m_nCount++;

	UpdateProgressParam param;
	param.nPos = m_nCount;
	_stprintf(param.sFile, "%s", lpszFileName);

	LRESULT lr = ::SendMessage(m_hProgWnd, WM_PROGRESS_UPDATE, (WPARAM)(&param), 0);
	if(lr == 0)
	{
		return -1;
	}

	return m_nCount;
}