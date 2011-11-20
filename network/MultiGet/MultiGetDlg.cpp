// MultiGetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiGet.h"
#include "MultiGetDlg.h"
#include "TestDownloader.h"
#include "CommonUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiGetDlg dialog

CMultiGetDlg::CMultiGetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiGetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiGetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bTaskCleaned = FALSE;
}

void CMultiGetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiGetDlg)
	DDX_Control(pDX, IDC_EDIT_URL, m_editUrl);
	DDX_Control(pDX, IDC_LIST_TASK, m_taskListCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMultiGetDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiGetDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DOWNLOAD_PROGRESS, OnUpdateProgress)
	ON_MESSAGE(WM_DOWNLOAD_COMPLETE, OnEnd)
	ON_MESSAGE(WM_DOWNLOAD_STATUS, OnStatusUpdate)
	ON_BN_CLICKED(IDC_ADD1, OnAdd1)
	ON_BN_CLICKED(IDC_BUTTON_START1, OnButtonStart1)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE, OnButtonRemove)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TASK, OnItemchangedListTask)
	ON_BN_CLICKED(IDC_BUTTON_REDOWNLOAD, OnButtonRedownload)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiGetDlg message handlers

BOOL CMultiGetDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_taskListCtrl.Init();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMultiGetDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMultiGetDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMultiGetDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CMultiGetDlg::OnStatusUpdate(WPARAM wParam, LPARAM lParam)
{
	int nTaskID = (int)wParam;
	CDownloadState* pStatusInfo = (CDownloadState*)lParam;
	
	int nIndex = 0;
	CTaskInfo* pTaskInfo = NULL;
	if(!GetTaskInfo(nTaskID, nIndex, pTaskInfo))
	{
		CString szLog;
		szLog.Format("[OnStatusUpdate]: The task [%02d] is in destroying. Status=0x%08X, detail = %s", 
			nTaskID, pStatusInfo->m_nState, (LPCTSTR)pStatusInfo->m_szDetail);
		LOG4CPLUS_INFO_STR(ROOT_LOGGER, (LPCTSTR)szLog)
	}
	else
	{
		pTaskInfo->m_dlState = *pStatusInfo;

		CheckState(nIndex, pStatusInfo->m_nState);

		CString szStatusMsg;
		CCommonUtils::StatusCodeToStr(pStatusInfo->m_nState, pStatusInfo->m_szDetail, szStatusMsg);
		
		m_taskListCtrl.SetItemText(nIndex, 4, (LPCTSTR)szStatusMsg);
		m_taskListCtrl.InvalidateSubItem(nIndex, 4);
	}
	
	ListCtrlSelectionChanged();
	
	return 1L;
}
LRESULT CMultiGetDlg::OnEnd(WPARAM wParam, LPARAM lParam)
{
	/*
	int nTaskID = (int)wParam;
	DWORD dwResult = (DWORD)lParam;
	
	int nIndex = 0;
	CTaskInfo* pTaskInfo = NULL;
	if(!GetTaskInfo(nTaskID, nIndex, pTaskInfo))
	{
		WORD nMajor = LOWORD(dwResult);

		CString szLog;
		szLog.Format("[OnEnd]: The task [%d] is in destroying. Result=0x%08X", nTaskID, dwResult);
		LOG4CPLUS_INFO_STR(ROOT_LOGGER, (LPCTSTR)szLog)
	}
	else
	{
		CString szStatusMsg;
		CCommonUtils::ResultCode2StatusStr(dwResult, szStatusMsg);
		
		m_taskListCtrl.SetItemText(nIndex, 4, (LPCTSTR)szStatusMsg);
		m_taskListCtrl.InvalidateSubItem(nIndex, 4);
	}

	ListCtrlSelectionChanged();
	*/

	//Same process with OnStatusUpdate
	int nTaskID = (int)wParam;
	CDownloadState* pStatusInfo = (CDownloadState*)lParam;
	
	int nIndex = 0;
	CTaskInfo* pTaskInfo = NULL;
	if(!GetTaskInfo(nTaskID, nIndex, pTaskInfo))
	{
		CString szLog;
		szLog.Format("[OnEnd]: The task [%02d] is in destroying. Status=0x%08X, detail = %s", 
			nTaskID, pStatusInfo->m_nState, (LPCTSTR)pStatusInfo->m_szDetail);
		LOG4CPLUS_INFO_STR(ROOT_LOGGER, (LPCTSTR)szLog)
	}
	else
	{
		pTaskInfo->m_dlState = *pStatusInfo;
		CheckState(nIndex, pStatusInfo->m_nState);

		CString szStatusMsg;
		CCommonUtils::StatusCodeToStr(pStatusInfo->m_nState, pStatusInfo->m_szDetail, szStatusMsg);
		
		m_taskListCtrl.SetItemText(nIndex, 4, (LPCTSTR)szStatusMsg);
		m_taskListCtrl.InvalidateSubItem(nIndex, 4);
	}
	
	ListCtrlSelectionChanged();

	return 1L;
}
void CMultiGetDlg::OnOK() 
{
}

LRESULT CMultiGetDlg::OnUpdateProgress(WPARAM wParam, LPARAM lParam)
{
	CProgressInfo* pProgressInfo = (CProgressInfo*)wParam;
	int index = GetTaskIndex(pProgressInfo->m_nTaskID);

	if(index < 0)
	{
		CString szLog;
		szLog.Format("[OnUpdateProgress]: The task [%02d] has been destroyed already.", pProgressInfo->m_nTaskID);
		LOG4CPLUS_INFO_STR(ROOT_LOGGER, (LPCTSTR)szLog)

		return (LRESULT)0;
	}
	
	ASSERT(index >= 0 && index < m_taskListCtrl.GetItemCount());
	CheckState(index);

	CTaskInfo* pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(index);
	ASSERT(pTaskInfo != NULL);


	CString szProgress;

	DWORD64 percent = 0;
	if(pProgressInfo->dltotal > 0)
	{
		percent = pProgressInfo->dlnow * 100 / pProgressInfo->dltotal;
		szProgress.Format("%c%I64d - %I64d of %I64d", '%', percent, pProgressInfo->dlnow, pProgressInfo->dltotal);
	}
	else
	{
		szProgress.Format("N/A - %I64d of N/A", pProgressInfo->dlnow);
	}

	CString szResult;
	if(pProgressInfo->retCode >= 0)
	{
		szResult.Format("%d - %s", pProgressInfo->retCode, pProgressInfo->szReason);
	}

	
	pTaskInfo->m_progress = szProgress;

	m_taskListCtrl.SetItemText(index, 3, szProgress);
	m_taskListCtrl.InvalidateSubItem(index, 3);

	return 1L;
}


void CMultiGetDlg::OnAdd1() 
{
	
	CString sUrl;
	m_editUrl.GetWindowText(sUrl);
	
	if(sUrl.IsEmpty())
	{
		AfxMessageBox("Empty Url");
		return;
	}
	CTaskInfo* pTaskInfo = new CTaskInfo();
	pTaskInfo->m_url = sUrl;
	pTaskInfo->m_progress = "Ready";
	pTaskInfo->m_nTaskID = CCommonUtils::GetUniqueID();
	
	m_taskListCtrl.AddRow(*pTaskInfo);
	
	m_editUrl.SetWindowText("");	
}

void CMultiGetDlg::OnButtonStart1() 
{
	CTaskInfo* pTaskInfo = NULL;
	//Get all selected items
	POSITION pos = m_taskListCtrl.GetFirstSelectedItemPosition();
	
	int nItem = -1;
	while (pos != NULL)
	{
		nItem = m_taskListCtrl.GetNextSelectedItem(pos);
		
		pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(nItem);
		ASSERT(pTaskInfo != NULL);
		
		if(pTaskInfo == NULL)
		{
			continue;
		}
		
		CDownloadParam param;
		param.m_hWnd = GetSafeHwnd();
		param.m_nTaskID = pTaskInfo->m_nTaskID;
		param.m_szUrl = pTaskInfo->m_url;
		param.m_nFileSize = 0;
		
		if(pTaskInfo->m_lpDownloaderMgr == NULL)
		{
			pTaskInfo->m_lpDownloaderMgr = new CDownloaderMgr();
		}
		pTaskInfo->m_lpDownloaderMgr->Init(param);
		
		pTaskInfo->m_lpDownloaderMgr->Start();
	}
}

void CMultiGetDlg::OnButtonPause() 
{
	CTaskInfo* pTaskInfo = NULL;
	//Get all selected items
	POSITION pos = m_taskListCtrl.GetFirstSelectedItemPosition();
	
	int nItem = -1;
	while (pos != NULL)
	{
		nItem = m_taskListCtrl.GetNextSelectedItem(pos);
		
		pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(nItem);
		ASSERT(pTaskInfo != NULL);
		
		if(pTaskInfo == NULL)
		{
			continue;
		}
		
		pTaskInfo->m_lpDownloaderMgr->Pause();
	}
}

void CMultiGetDlg::OnButtonRedownload() 
{
	CTaskInfo* pTaskInfo = NULL;
	//Get all selected items
	POSITION pos = m_taskListCtrl.GetFirstSelectedItemPosition();
	
	int nItem = -1;
	while (pos != NULL)
	{
		nItem = m_taskListCtrl.GetNextSelectedItem(pos);
		
		pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(nItem);
		ASSERT(pTaskInfo != NULL);
		
		if(pTaskInfo == NULL)
		{
			continue;
		}
		
		pTaskInfo->m_lpDownloaderMgr->ReStart();
	}
}
void CMultiGetDlg::OnButtonRemove() 
{
	CTaskInfo* pTaskInfo = NULL;

	POSITION pos = m_taskListCtrl.GetFirstSelectedItemPosition();
	int nItem = -1;
	while (pos != NULL)
	{
		nItem = m_taskListCtrl.GetNextSelectedItem(pos);

		pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(nItem);
		ASSERT(pTaskInfo != NULL);

		if(pTaskInfo->m_lpDownloaderMgr != NULL)
		{
			if(pTaskInfo->m_lpDownloaderMgr->Destroy() == CPostAction::DELETE_BY_EXTERNAL)
			{
				delete pTaskInfo->m_lpDownloaderMgr;
			}
		}
	}
	m_taskListCtrl.RemoveSelectedItems();
}

int CMultiGetDlg::GetTaskIndex(int nTaskID)
{
	int i, nRowCount;
	CTaskInfo* pTaskInfo = NULL;
	for(i = 0, nRowCount = m_taskListCtrl.GetItemCount(); i < nRowCount; i++)
	{
		pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(i);
		ASSERT(pTaskInfo != NULL);

		if(pTaskInfo->m_nTaskID == nTaskID)
		{
			return i;
		}
	}

	return -1;
}

CTaskInfo* CMultiGetDlg::GetTaskInfo(int nTaskID)
{
	int i, nRowCount;
	CTaskInfo* pTaskInfo = NULL;
	for(i = 0, nRowCount = m_taskListCtrl.GetItemCount(); i < nRowCount; i++)
	{
		pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(i);
		ASSERT(pTaskInfo != NULL);
		
		if(pTaskInfo->m_nTaskID == nTaskID)
		{
			return pTaskInfo;
		}
	}
	
	return NULL;
}

BOOL CMultiGetDlg::GetTaskInfo(int nTaskID, int& nIndex, CTaskInfo*& pTaskInfo)
{
	int i, nRowCount;
	CTaskInfo* ptr = NULL;
	for(i = 0, nRowCount = m_taskListCtrl.GetItemCount(); i < nRowCount; i++)
	{
		ptr = (CTaskInfo*)m_taskListCtrl.GetItemData(i);
		ASSERT(ptr != NULL);
		
		if(ptr->m_nTaskID == nTaskID)
		{
			nIndex = i;
			pTaskInfo = ptr;

			return TRUE;
		}
	}
	
	return FALSE;
}

void CMultiGetDlg::OnButtonAdd() 
{
	static const TCHAR* lpszUrlList[] = {
	"http://download.httpwatch.com/httpwatch.exe",
	"http://cn2.php.net/distributions/manual/php_enhanced_en.chm",
	"http://wiresharkdownloads.riverbed.com/wireshark/win32/wireshark-win32-1.6.2.exe",
	"http://download.wondershare.com/cbs_down/pdf-converter-pro_full839.exe",
	"http://70.duote.org:8080/rmdemo.zip",
	"http://desktop.youku.com/iku2/iku2.1_setup.exe",
	"http://sc.down.chinaz.com/201108/Mp3ABCut_2.1.0.zip",
	"http://63.duote.org/winmpgvideoconvert.exe",
	"http://download.skype.com/SkypeSetupFull.exe",
	"http://ncu.dl.sourceforge.net/project/aresgalaxy/aresgalaxy/AresRegular217_10272010/aresregular217_installer.exe",
	"http://labs.renren.com/apache-mirror//httpd/httpd-2.2.20-win32-src.zip",
	"http://www.youtubeget.com/down/yg.exe",
	"http://www.any-code-counter.com",
	"fasfasdfafffffffffffffffffffwefwef",
	"f43fifasdkfiefkds"};
	
	int nCount = sizeof(lpszUrlList)/sizeof(lpszUrlList[0]);
	for(int i = 0; i < nCount; i++)
	{
		CTaskInfo* pTaskInfo = new CTaskInfo();
		pTaskInfo->m_url = lpszUrlList[i];
		pTaskInfo->m_progress = "Ready";
		pTaskInfo->m_nTaskID = CCommonUtils::GetUniqueID();
		m_taskListCtrl.AddRow(*pTaskInfo);
	}
}

void CMultiGetDlg::OnItemchangedListTask(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	CString szLog;
	if(IS_LOG_ENABLED(ROOT_LOGGER, log4cplus::TRACE_LOG_LEVEL))
	{
		szLog.Format("uChanged = %04x, uNewState = %04x, uOldState = %04x, iItem = %d. ",
			pNMListView->uChanged, pNMListView->uNewState, pNMListView->uOldState, pNMListView->iItem);
		LOG4CPLUS_TRACE_STR(ROOT_LOGGER, (LPCTSTR)szLog)
	}
	if(pNMListView->uChanged == LVIF_STATE)
    {
		//1. uNewState & LVIS_SELECTED, there's new items selected
		//2. uOldState & LVIS_SELECTED, there's old items deselected
		//we care about both events
		if((pNMListView->uNewState & LVIS_SELECTED) || (pNMListView->uOldState & LVIS_SELECTED))
		{
			ListCtrlSelectionChanged();
		}
    }
	*pResult = 0;
}

void CMultiGetDlg::ListCtrlSelectionChanged()
{
	DWORD dwStatus = DL_OPER_FLAG_NONE;

	POSITION pos = m_taskListCtrl.GetFirstSelectedItemPosition();

	int nItem = -1;
	CTaskInfo* pTaskInfo = NULL;
	while (pos != NULL)
	{
		nItem = m_taskListCtrl.GetNextSelectedItem(pos);
		
		pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(nItem);
		ASSERT(pTaskInfo != NULL);

		dwStatus |= pTaskInfo->m_dlState.GetAccess();
	}

	EnableButtons(dwStatus);
}

void CMultiGetDlg::EnableButtons(DWORD dwStatus)
{
	GetDlgItem(IDC_BUTTON_START1)->EnableWindow(dwStatus & DL_OPER_FLAG_START);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(dwStatus & DL_OPER_FLAG_PAUSE);
	GetDlgItem(IDC_BUTTON_REMOVE)->EnableWindow(dwStatus & DL_OPER_FLAG_REMOVE);
	GetDlgItem(IDC_BUTTON_REDOWNLOAD)->EnableWindow(dwStatus & DL_OPER_FLAG_REDOWNLOAD);
}

void CMultiGetDlg::OnClose() 
{
	StopAllTasks();
	
	CDialog::OnClose();
}

void CMultiGetDlg::CheckState(int nIndex, int nState)
{
	CTaskInfo* pTaskInfo = (CTaskInfo*)m_taskListCtrl.GetItemData(nIndex);
	ASSERT(pTaskInfo != NULL);

	DWORD dwState1, dwState2;

	dwState1 = pTaskInfo->m_dlState.GetState();

	if(pTaskInfo->m_lpDownloaderMgr != NULL)
	{
		if(nState >= 0)
		{
			dwState2 = nState;
			ASSERT(dwState1 == dwState2);
		}

		dwState2 = pTaskInfo->m_lpDownloaderMgr->GetState();
		if(dwState2 <= TSE_DESTROYED)
		{
			ASSERT(dwState1 == dwState2);
		}
	}
	else
	{
		AfxTrace("========================CheckState: m_lpDownloaderMgr = NULL==============\n");
	}
}

void CMultiGetDlg::OnCancel() 
{
	StopAllTasks();

	CDialog::OnCancel();
}

void CMultiGetDlg::StopAllTasks(BOOL bHideWindow)
{
	if(m_bTaskCleaned)
	{
		return;
	}
	CString szLog;
	if(bHideWindow)
	{
		//1. Hide main window
		ASSERT(AfxGetMainWnd());
		AfxGetMainWnd()->ShowWindow(SW_HIDE);

		szLog.Format("[StopAllTasks]: Main window hide");
		LOG4CPLUS_INFO_STR(ROOT_LOGGER, (LPCTSTR)szLog)
	}

	//Send Remove command
	OnButtonRemove();
		
	//2. Wait thread monitor thread ends
	//TODO: switch off the message receive of HWND
	SYS_THREAD_MONITOR()->StopMonitor(TRUE);
	
	szLog.Format("[StopAllTasks]: Thread monitor stopped");
	LOG4CPLUS_INFO_STR(ROOT_LOGGER, (LPCTSTR)szLog)

	m_bTaskCleaned = TRUE;
}
