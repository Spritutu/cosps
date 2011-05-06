// DynamicToolBar.h : main header file for the DYNAMICTOOLBAR application
//

#if !defined(AFX_DYNAMICTOOLBAR_H__F9645A1A_FF09_4237_93B7_B9C43768E6DB__INCLUDED_)
#define AFX_DYNAMICTOOLBAR_H__F9645A1A_FF09_4237_93B7_B9C43768E6DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDynamicToolBarApp:
// See DynamicToolBar.cpp for the implementation of this class
//

class CDynamicToolBarApp : public CWinApp
{
public:
	CDynamicToolBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDynamicToolBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDynamicToolBarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYNAMICTOOLBAR_H__F9645A1A_FF09_4237_93B7_B9C43768E6DB__INCLUDED_)
