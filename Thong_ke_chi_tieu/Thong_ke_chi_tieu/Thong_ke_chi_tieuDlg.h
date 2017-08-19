
// Thong_ke_chi_tieuDlg.h : header file
//

#pragma once
#include "Excell.h"

// CThong_ke_chi_tieuDlg dialog
class CThong_ke_chi_tieuDlg : public CDialogEx, CExcell
{
// Construction
public:
	CThong_ke_chi_tieuDlg(CWnd* pParent = NULL);	// standard constructor
	
// Dialog Data
	enum { IDD = IDD_THONG_KE_CHI_TIEU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPush();
private:

public:
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedPull();
};
