// SignIn_Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "Thong_ke_chi_tieu.h"
#include "Pull_Dialog.h"
#include "afxdialogex.h"


// CPull_Dialog dialog

IMPLEMENT_DYNAMIC(CPull_Dialog, CDialog)

CPull_Dialog::CPull_Dialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPull_Dialog::IDD, pParent)
{

}

CPull_Dialog::~CPull_Dialog()
{
}

void CPull_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_USER, CEdit_User);
	DDX_Control(pDX, IDC_EDIT_PASS, CEdit_Pass);
	DDX_Control(pDX, IDC_BTN_STATUS, CBtn_Status);
	DDX_Control(pDX, IDC_BTN_VIEW, CBtn_View);
	DDX_Control(pDX, IDC_COMBO1, CCombobox);
	DDX_Control(pDX, IDC_EDIT_SUM, CEdit_Sum);
	DDX_Control(pDX, IDC_EDIT_REMAIN, CEdit_Remain);
}


BEGIN_MESSAGE_MAP(CPull_Dialog, CDialog)
	ON_BN_CLICKED(ID_SIGN, &CPull_Dialog::OnBnClickedSign)
	ON_BN_CLICKED(IDC_BTN_VIEW, &CPull_Dialog::OnBnClickedBtnView)
	ON_BN_CLICKED(IDC_BTN_STATUS, &CPull_Dialog::OnBnClickedBtnStatus)
END_MESSAGE_MAP()

BOOL CPull_Dialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	 CenterWindow();
	 
	 return true;
}
// CPull_Dialog message handlers


void CPull_Dialog::OnBnClickedSign()
{
	CString strUser = NULL;
	CString strPass = NULL;

	CEdit_User.GetWindowTextW(strUser);
	if (!strUser.Compare(L""))
	{
		MessageBoxA(NULL, "Please enter Account!!!", "Error!!!", MB_OK|MB_ICONERROR);
		return;
	}

	CEdit_Pass.GetWindowTextW(strPass);
	if (!strPass.Compare(L""))
	{
		MessageBoxA(NULL, "Please enter Pass!!!", "Error!!!", MB_OK|MB_ICONERROR);
		return;
	}

	if (!strPass.Compare(L"Vietnam2018") && !strUser.Compare(L"bostney"))
	{
		MessageBoxA(NULL, "SingIn Success!!!", "INFOR!!!", MB_OK|MB_ICONINFORMATION);
		Init_Frame();
	}
	else
	{
		MessageBoxA(NULL, "SingIn Failed!!!", "Error!!!", MB_OK|MB_ICONERROR);
	}
}

void CPull_Dialog::Init_Frame()
{
	CString strMonth = NULL;
	//LPCTSTR Month[12] = {L"January", L"February", L"March", L"April", L"May", L"June", L"July", L"August", L"September", L"October", L"Novemer", L"December"};
	CBtn_Status.EnableWindow(true);
	CBtn_View.EnableWindow(true);
	CCombobox.EnableWindow(true);
	for(int i = 1; i < 13; i++)
	{
		strMonth.Format(_T("%d"), i);
		CCombobox.AddString(strMonth);
	}
}


void CPull_Dialog::OnBnClickedBtnStatus()
{
	int sheetno = 0;
	CString strMonth = NULL;
	CString strSum = NULL;
	CString strRemain = NULL;

	CCombobox.GetWindowTextW(strMonth);
	if (!strMonth.Compare(L""))
	{
		MessageBoxA(NULL, "Please choose month to get SUM!!!", "Error!!!", MB_OK|MB_ICONERROR);
		return;
	}
	{
		CString strPathFile = NULL;
		strPathFile = Action.Get_PathFile();
		Action.Open(strPathFile, false);
	}

	Action.Pull_action(strMonth, strSum, strRemain);
	CEdit_Sum.SetWindowTextW(strSum);
	CEdit_Remain.SetWindowTextW(strRemain);
	// TODO: Add your control notification handler code here
}


void CPull_Dialog::OnBnClickedBtnView()
{
	Action.View_action();
	// TODO: Add your control notification handler code here
}