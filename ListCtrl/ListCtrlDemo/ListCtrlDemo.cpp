// ListCtrlDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ListCtrlDemo.h"
#include "MainDlg.h"
#include "Preferences.h"
#include <log4cplus/configurator.h>
#include <direct.h>
#include "LangGrammarMap.h"
#include "htmlhelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DECLARE_THE_LOGGER_NAME("ListCtrlDemo.cpp")

void InitLog4cplus();

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoApp

BEGIN_MESSAGE_MAP(CListCtrlDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CListCtrlDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, /*CWinApp::*/OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoApp construction

CListCtrlDemoApp::CListCtrlDemoApp()
{
	m_pSysBkBrush  = NULL;
}

CListCtrlDemoApp::~CListCtrlDemoApp()
{
	if(m_pSysBkBrush != NULL)
	{
		m_pSysBkBrush->DeleteObject();
		delete m_pSysBkBrush;
		m_pSysBkBrush = NULL;
	}

	free((void*)m_pszAppName);
	m_pszAppName = NULL;

	LOG4CPLUS_INFO_STR(THE_LOGGER, "CListCtrlDemoApp::~CListCtrlDemoApp() called.")
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CListCtrlDemoApp object

CListCtrlDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CListCtrlDemoApp initialization
void CListCtrlDemoApp::InitWorkDir()
{
	//The old way can't work if the current work dir is not the dir where exe is at
	/*
	_tgetcwd(m_szWorkDir.GetBuffer(MAX_PATH), MAX_PATH);
	m_szWorkDir.ReleaseBuffer();
	//Remove the last backslash if exist
	m_szWorkDir.TrimRight('\\');
	*/

	//Get the Full Path of the .exe file
	LPTSTR lpszFullPath = m_szWorkDir.GetBuffer(MAX_PATH);
	::GetModuleFileName(NULL, lpszFullPath, MAX_PATH);
	m_szWorkDir.ReleaseBuffer();

	TCHAR drive[MAX_PATH];
    TCHAR dir[MAX_PATH];
    TCHAR fname[MAX_PATH];
    TCHAR ext[MAX_PATH];
	
    _tsplitpath(m_szWorkDir, drive, dir, fname, ext);
	m_szWorkDir.Format("%s%s", drive, dir);
	//Remove the last backslash if exist
	m_szWorkDir.TrimRight('\\');

	//For Debug and Release version in VC++
	CString szCheckFilePath;
	szCheckFilePath.Format(_T("%s\\dat\\default\\filter_tree.xml"), m_szWorkDir);
	if(!::PathFileExists(szCheckFilePath))
	{
		int nLastBSPos = m_szWorkDir.ReverseFind(_T('\\'));
		if(nLastBSPos >= 0)
		{
			m_szWorkDir.GetBufferSetLength(nLastBSPos);
		}
	}
}
BOOL CListCtrlDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	InitWorkDir();

	InitLog4cplus();
	if(IS_LOG_ENABLED(THE_LOGGER, log4cplus::INFO_LOG_LEVEL))
	{
		TIME_ZONE_INFORMATION tzi;
		GetTimeZoneInformation(&tzi);	
		LOG4CPLUS_INFO(THE_LOGGER, "Application Initialized. TimeZone="<<(-(tzi.Bias)))
	}

	//Set App's name
	if(m_pszAppName != NULL)
	{
		free((void*)m_pszAppName);
		m_pszAppName = NULL;
	}
	m_pszAppName = _tcsdup(SZ_PRODUCT_NAME);

	m_szPrefIniFile.Format(_T("%s"), CommonUtils::GetConfFilePath(_T("preferences.ini"), GCFP_USER));

	SYS_PREF()->Init();

	//Call GetInstance() to make sure the LangGrammar to be initialized.
	CLangGrammarMap::GetInstance();

	m_pSysBkBrush = new CBrush();
	m_pSysBkBrush->CreateSolidBrush(RGB(251, 252, 249));

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CListCtrlDemoApp::OnHelp()
{
	LOG4CPLUS_DEBUG_STR(THE_LOGGER, "OnHelp Called.")
	CWnd* pMainWnd = AfxGetMainWnd();
	ASSERT(pMainWnd != NULL);
	pMainWnd->SendMessage(WM_COMMAND, IDM_HELP_HELP_CONTENT);
}

CString& SYS_PREF_INI_FILE() 
{
	return SYS_APP()->m_szPrefIniFile;
}

CListCtrlDemoApp* SYS_APP()
{
	CListCtrlDemoApp* pApp = (CListCtrlDemoApp*)AfxGetApp();
	ASSERT(pApp);
	return pApp;
}
void InitLog4cplus()
{
#ifdef ENABLE_LOG4CPLUS	
	const char* pLogFileSuffixName = "LOG_FILE_SUFFIX";
	CString szLogFileSuffix = getenv(pLogFileSuffixName);

	const char* pAppWorkDirName = "APP_WORK_DIR";
	CString szAppWorkDir = getenv(pAppWorkDirName);
	
	//Set the env to the current time str
	CString sTime = CTime::GetCurrentTime().Format("_%Y_%m_%d_%H_%M_%S");
	
	CString szValue;
	szValue.Format("%s=%s", pLogFileSuffixName, sTime);
	_putenv(szValue);

	szValue.Format("%s=%s", pAppWorkDirName, SYS_APP()->m_szWorkDir);
	_putenv(szValue);
	
	CString szConfigFile;
	szConfigFile.Format("%s\\dat\\config\\log4cplus.properties", SYS_APP()->m_szWorkDir);
	try
	{
		//This will take effect in the configure process
		log4cplus::PropertyConfigurator::doConfigure((LPCTSTR)szConfigFile);
	}
	catch(...) 
	{
		CString sLogInfo;
		sLogInfo.Format("Exception occured when configure log4cplus, config file = %s", szConfigFile);
		AfxTrace("%s\n", sLogInfo);
		LOG4CPLUS_FATAL(ROOT_LOGGER, (LPCTSTR)sLogInfo)
	}
	
	//After configuration, restore the environment variable.
	szValue.Format("%s=%s", pLogFileSuffixName, szLogFileSuffix);
	_putenv(szValue);

	szValue.Format("%s=%s", pAppWorkDirName, szAppWorkDir);
	_putenv(szValue);
#endif
}

int CListCtrlDemoApp::ExitInstance() 
{
	LOG4CPLUS_INFO(THE_LOGGER, "Application Exit.")
	return CWinApp::ExitInstance();
}

BOOL CListCtrlDemoApp::PreTranslateMessage(MSG* pMsg) 
{
	//The Key RETURN and ESCAPE will cause the system halted, remove the response of the 2 keys.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		{
			HWND hWndMsgParent = ::GetParent(pMsg->hwnd);
			HWND hWndWork = ((CMainDlg*)AfxGetMainWnd())->m_pCounterDlg->GetSafeHwnd();
			if(hWndWork == hWndMsgParent)
			{
				return TRUE;
			}
		}
	}
	
	return CWinApp::PreTranslateMessage(pMsg);
}
