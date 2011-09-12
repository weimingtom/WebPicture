// WebPictureDlg.h : header file
//

#if !defined(AFX_WebPictureDLG_H__2C00BB23_0A90_4992_B001_9295B90F3D6B__INCLUDED_)
#define AFX_WebPictureDLG_H__2C00BB23_0A90_4992_B001_9295B90F3D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWebPictureDlg dialog

class CWebPictureDlg : public CDialog
{
public:
	CString szLogName;
	void OnRemove();
// Construction
public:
	CWebPictureDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWebPictureDlg)
	enum { IDD = IDD_WebPicture_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWebPictureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWebPictureDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnView();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnCheck3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WebPictureDLG_H__2C00BB23_0A90_4992_B001_9295B90F3D6B__INCLUDED_)
