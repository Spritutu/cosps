#if !defined(AFX_DLG2_H__5A05E4A6_38C3_4D54_BE32_DAE26E8D5243__INCLUDED_)
#define AFX_DLG2_H__5A05E4A6_38C3_4D54_BE32_DAE26E8D5243__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg2.h : header file
//
#include "ResizableDialog.h"
/////////////////////////////////////////////////////////////////////////////
// CDlg2 dialog

class CDlg2 : public CResizableDialog
{
// Construction
public:
	CDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlg2)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlg2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG2_H__5A05E4A6_38C3_4D54_BE32_DAE26E8D5243__INCLUDED_)
