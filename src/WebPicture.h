// WebPicture.h : main header file for the WebPicture application
//

#if !defined(AFX_WebPicture_H__8D22CD62_1B28_4438_8F6D_A9A2FF84884F__INCLUDED_)
#define AFX_WebPicture_H__8D22CD62_1B28_4438_8F6D_A9A2FF84884F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWebPictureApp:
// See WebPicture.cpp for the implementation of this class
//

class CWebPictureApp : public CWinApp
{
public:
	CWebPictureApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebPictureApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWebPictureApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WebPicture_H__8D22CD62_1B28_4438_8F6D_A9A2FF84884F__INCLUDED_)
