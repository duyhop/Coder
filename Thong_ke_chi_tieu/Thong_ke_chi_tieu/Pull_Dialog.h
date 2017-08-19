#pragma once
#include "Action.h"

// CPull_Dialog dialog

class CPull_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPull_Dialog)

public:
	CPull_Dialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPull_Dialog();

// Dialog Data
	enum { IDD = IDD_PULL_DIALOG };
private:
	CEdit CEdit_User;
	CEdit CEdit_Pass;
	CEdit CEdit_Sum;
	CEdit CEdit_Remain;
	CButton CBtn_View;
	CButton CBtn_Status;
	CComboBox CCombobox;

	CAction Action;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	void Init_Frame();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSign();
	afx_msg void OnBnClickedBtnSum();
	afx_msg void OnBnClickedBtnView();
	afx_msg void OnBnClickedBtnStatus();
};
