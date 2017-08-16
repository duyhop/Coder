#pragma once
#include "Action.h"

// CPush_Dialog dialog

class CPush_Dialog : public CDialogEx
{
	DECLARE_DYNAMIC(CPush_Dialog)

public:
	CPush_Dialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPush_Dialog();

// Dialog Data
	enum { IDD = IDD_PUSH_DIALOG };
private:
	CAction Action;
	CEdit CEdit_Money;
	CEdit CEdit_Note;
	CEdit CEdit_DateTime;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPush();
};
