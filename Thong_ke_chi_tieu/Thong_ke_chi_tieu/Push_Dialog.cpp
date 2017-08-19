// Push_Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "Thong_ke_chi_tieu.h"
#include "Push_Dialog.h"
#include "afxdialogex.h"


// CPush_Dialog dialog

IMPLEMENT_DYNAMIC(CPush_Dialog, CDialog)

CPush_Dialog::CPush_Dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPush_Dialog::IDD, pParent)
{

}

CPush_Dialog::~CPush_Dialog()
{
}

void CPush_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MONEY, CEdit_Money);
	DDX_Control(pDX, IDC_NOTE, CEdit_Note);
	DDX_Control(pDX, IDC_DATE, CEdit_DateTime);
	DDX_Control(pDX, IDC_OWE, CCheckBox);
}


BEGIN_MESSAGE_MAP(CPush_Dialog, CDialog)
	ON_BN_CLICKED(IDC_PUSH, &CPush_Dialog::OnBnClickedPush)
END_MESSAGE_MAP()


// CPush_Dialog message handlers
BOOL CPush_Dialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	 CenterWindow();

	 Action.Create_File(false);
	 
	 return true;
}

void CPush_Dialog::OnBnClickedPush()
{
	CString strMoney = NULL;
	CString strNote = NULL;
	CString strDate = NULL;
	CEdit_Money.GetWindowTextW(strMoney);
	if (!strMoney.Compare(L""))
	{
		MessageBoxA(NULL, "Please enter money!!!", "Error!!!", MB_OK|MB_ICONERROR);
		return;
	}

	CEdit_Note.GetWindowTextW(strNote);
	if (!strNote.Compare(L""))
	{
		MessageBoxA(NULL, "Please enter Note!!!", "Error!!!", MB_OK|MB_ICONERROR);
		return;
	}

	CEdit_DateTime.GetWindowTextW(strDate);
	UINT Cbox_status = CCheckBox.GetState();
	if(BST_CHECKED == Cbox_status)
	{
		Action.Push_owe_action(strMoney, strNote, strDate);
	}
	else
	{
		Action.Push_action(strMoney, strNote, strDate);
	}
	

	// TODO: Add your control notification handler code here
}
