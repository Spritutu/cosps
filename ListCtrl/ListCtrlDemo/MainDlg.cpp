// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ListCtrlDemo.h"
#include "MainDlg.h"
#include "AboutDlg.h"
#include "Preferences.h"
#include "PreferencesDlg.h"
#include "CustomLangDlg.h"
#include "ShowLangRuleDlg.h"
#include "RegisterDlg.h"
#include "LicenseMgr.h"
#include "htmlhelp.h"
#include "EvaluationLimitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainDlg dialog


CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CResizableDialog(CMainDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//{{AFX_DATA_INIT(CMainDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCounterDlg = new CListCtrlDemoDlg();
	m_pMainToolBarCtrl = new CMainToolBarCtrl();
}

CMainDlg::~CMainDlg()
{
	delete m_pMainToolBarCtrl;
	delete m_pCounterDlg;
}


void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CResizableDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainDlg, CResizableDialog)
	//{{AFX_MSG_MAP(CMainDlg)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers
void CMainDlg::OnOK()
{
	return;
}
void CMainDlg::OnCancel()
{
	CResizableDialog::OnCancel();
}
BOOL CMainDlg::OnInitDialog() 
{
	CResizableDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	SetMenuBarBkg();

	InitGUI();

	if(!CLicenseMgr::GetInstance()->IsRegistered(TRUE))
	{
		CString szText;
		szText.Format("%s%s", AfxGetApp()->m_pszAppName, _T("(Evaluation Version)"));
		SetWindowText(szText);
	}
	else
	{
		SetWindowText(AfxGetApp()->m_pszAppName);
	}

	EnableSaveRestore("MainDlg");
	m_pCounterDlg->UpdateFilterTreeBkgnd();

	return TRUE;
}

void CMainDlg::SetMenuBarBkg()
{
	MENUINFO MenuInfo = {0};
	MenuInfo.cbSize = sizeof(MenuInfo);
	MenuInfo.hbrBack = *(SYS_APP()->m_pSysBkBrush); // Brush you want to draw
	MenuInfo.fMask = MIM_BACKGROUND;
	MenuInfo.dwStyle = MNS_AUTODISMISS;
	
	CMenu* pMenu = GetMenu();
	
	if(IsMenu(pMenu->m_hMenu))
	{
		SetMenuInfo(pMenu->m_hMenu, &MenuInfo);
	}
}

void CMainDlg::InitGUI()
{
	CWnd* pWndToolBar = m_pMainToolBarCtrl;
	if (m_pMainToolBarCtrl->Create(WS_VISIBLE | WS_CHILD | CCS_TOP | CCS_NODIVIDER | TBSTYLE_TOOLTIPS 
		| TBSTYLE_FLAT | TBSTYLE_TRANSPARENT | TBSTYLE_LIST, CRect(0,0,0,0), this, IDC_TOOLBAR))
	{
// 		if(IsUseReBar())
// 		{
			m_pMainToolBarCtrl->ModifyStyle(0, CCS_NORESIZE);
			m_pMainToolBarCtrl->SetExtendedStyle(m_pMainToolBarCtrl->GetExtendedStyle() | TBSTYLE_EX_HIDECLIPPEDBUTTONS);
// 		}
		m_pMainToolBarCtrl->Init();
		pWndToolBar = InitReBar();
	}
	m_pCounterDlg->Create(IDD_LISTCTRLDEMO_DIALOG);
	
	// adjust all main window sizes for toolbar height and maximize the child windows
	CRect rcClient, rcToolbar;
	GetClientRect(&rcClient);
	pWndToolBar->GetWindowRect(&rcToolbar);
	rcClient.top += rcToolbar.Height();

	m_pCounterDlg->SetWindowPos(NULL, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), SWP_NOZORDER);

	// anchors
	AddAnchor(pWndToolBar->m_hWnd,	TOP_LEFT, TOP_RIGHT);
	AddAnchor(m_pCounterDlg->m_hWnd, TOP_LEFT, BOTTOM_RIGHT);

	SetSizeGripVisibility(FALSE);
	UpdateSizeGrip();
}

CWnd* CMainDlg::InitReBar()
{
	CMainToolBarCtrl* pToolBarCtrl = m_pMainToolBarCtrl;
	if (m_MainReBarCtrl.Create(WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | RBS_BANDBORDERS 
		| RBS_AUTOSIZE | CCS_NODIVIDER, CRect(0, 0, 0, 0), this, AFX_IDW_REBAR))
	{
		CSize sizeBar;
		VERIFY( pToolBarCtrl->GetMaxSize(&sizeBar) );
		REBARBANDINFO rbbi = {0};
		rbbi.cbSize = sizeof(rbbi);
		rbbi.fMask = RBBIM_STYLE | RBBIM_SIZE | RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_IDEALSIZE | RBBIM_ID;
		rbbi.fStyle = RBBS_NOGRIPPER | RBBS_BREAK | RBBS_USECHEVRON;
		rbbi.hwndChild = pToolBarCtrl->m_hWnd;
		rbbi.cxMinChild = sizeBar.cy;
		rbbi.cyMinChild = sizeBar.cy;
		rbbi.cxIdeal = sizeBar.cx;
		rbbi.cx = rbbi.cxIdeal;
		rbbi.wID = 0;
		VERIFY( m_MainReBarCtrl.InsertBand((UINT)-1, &rbbi) );
		
		pToolBarCtrl->SetParentReBarWnd(m_MainReBarCtrl.m_hWnd);
		
		return &m_MainReBarCtrl;
	}
	return pToolBarCtrl;
}

BOOL CMainDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	switch(wParam)
	{
	case IDM_FILE_ADD:
	case ID_TBBTN_ADD_SOURCE_DIR:
		{
			m_pCounterDlg->OnButtonAdd();
		}
		break;
	case IDM_FILE_DEL:
		{
			m_pCounterDlg->OnButtonDel();
		}
		break;
	case IDM_FILE_START:
	case ID_TBBTN_START_TO_COUNT:
		{
			m_pCounterDlg->OnButtonStart();
		}
		break;
	case IDM_FILE_CLEAR:
	case ID_TBBTN_CLEAR_RESULT:
		{
			m_pCounterDlg->OnButtonClear();
		}
		break;
	case IDM_REPORT_EXPORT:
	case ID_TBBTN_EXPORT:
		{
			m_pCounterDlg->OnExport();
		}
		break;
	case IDM_REPORT_EXPORT_CSV:
		{
			m_pCounterDlg->OnExport(EXPORT_TYPE_CSV);
		}
		break;
	case IDM_REPORT_EXPORT_XLS:
		{
			m_pCounterDlg->OnExport(EXPORT_TYPE_EXCEL);
		}
		break;
	case IDM_REPORT_EXPORT_XML:
		{
			m_pCounterDlg->OnExport(EXPORT_TYPE_XML);
		}
		break;
	case IDM_REPORT_EXPORT_HTML:
		{
			m_pCounterDlg->OnExport(EXPORT_TYPE_HTML);
		}
		break;
	case IDM_TOOLS_OPTIONS:
	case ID_TBBTN_SETTING:
		{
			CPreferencesDlg prefsDlg;
			prefsDlg.DoModal();
		}
		break;
	case IDM_TOOLS_LANG_RULES:
		{
			CShowLangRuleDlg showLangRuleDlg;
			showLangRuleDlg.DoModal();
		}
		break;
	case IDM_FILE_EXIT:
	case ID_TBBTN_EXIT:
		{
			ASSERT(AfxGetMainWnd());
			AfxGetMainWnd()->SendMessage(WM_CLOSE);
		}
		break;
	case IDM_HELP_HELP_CONTENT:
		{
			CString szHelpFilePath;
			szHelpFilePath.Format(_T("%s\\help\\help_en.chm"), SYS_APP()->m_szWorkDir);
			HtmlHelp(m_hWnd, szHelpFilePath, HH_DISPLAY_TOPIC, NULL);
		}
		break;
	case IDM_HELP_SOFTWARE_WEBSITE:
		{
			CHyperLink::GotoURL(SZ_PRODUCT_WEBSITE, SW_SHOW);
		}
		break;
	case IDM_HELP_CHECK_UPGRADES:
		{
			CHyperLink::GotoURL(SZ_PRODUCT_UPGRADE, SW_SHOW);
		}
		break;
	case IDM_HELP_ORDER:
		{
			CHyperLink::GotoURL(SZ_PRODUCT_WEBSITE_ORDER, SW_SHOW);
		}
		break;
	case IDM_HELP_REGISTER:
		{
			if(CLicenseMgr::GetInstance()->IsRegistered(TRUE))
			{
				CString szText;
				szText.Format(_T("You have REGISTERED this software already. Thanks for your supporting!"));
				AfxMessageBox(szText, MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				CRegisterDlg regDlg;
				regDlg.DoModal();
			}
		}
		break;
	case IDM_HELP_ABOUT:
		{
			CAboutDlg dlg;
			dlg.DoModal();
		}
		break;
	}
	
	return CResizableDialog::OnCommand(wParam, lParam);
}

BOOL CMainDlg::OnEraseBkgnd(CDC* pDC)
{	
	return TRUE;
}

void CMainDlg::OnClose() 
{
	CResizableDialog::OnClose();
}

void CMainDlg::OnDestroy() 
{
	SYS_PREF()->Save();
	CResizableDialog::OnDestroy();
}
