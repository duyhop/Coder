#include "stdafx.h"
#include "Action.h"
using namespace std;

CAction::CAction(void)
{
}

CAction::~CAction(void)
{
	Quit();
}
void CAction::Push_action(CString Money, CString Note, CString Date)
{
	int imonth = 0;
	int current_indx = 0;
	CString strDay = NULL;
	
	imonth = get_Month(Date);
	{
		CString strFormat = NULL;

		Get_Data(imonth, 1, 1, strFormat);
		if (!strFormat.Compare(L"0"))
		{
			Create_Format(imonth);
		}
	}
	if (current_indx == 0)
	{
		current_indx = Get_curr_index(imonth);
	}

	strDay = get_Day(Date);
	HRESULT hr = Set_Data(imonth, (LPCTSTR)strDay, current_indx, 1);

	if(FAILED(hr))
	{
		MessageBoxA(NULL, "Push DAY is Failed!!!", "ERROR", MB_OK|MB_ICONERROR);
		return;
	}
	
	hr = Set_Data(imonth, Money + L"K", current_indx, 2);
	if(FAILED(hr))
	{
		MessageBoxA(NULL, "Push MONEY is Failed!!!", "ERROR", MB_OK|MB_ICONERROR);
		return;
	}

	if(FAILED(hr))
	{
		
		return;
	}

	hr = Set_Data(imonth, Note, current_indx, 3);
	if(FAILED(hr))
	{
		MessageBoxA(NULL, "Push NOTE is Failed!!!", "ERROR", MB_OK|MB_ICONERROR);
		return;
	}

	Set_Current_SUM_Money(imonth, 1, 2, Money);
	Set_Current_SUM_Money(imonth, 2, 2, Money);
	// Set current money avaiable
	//{
		/*CString strCurrent_Money = NULL;
		double Current_Moneys = 0;
		Get_Data(imonth, 1, 2, strCurrent_Money);
		Current_Moneys = get_number(strCurrent_Money);
		Current_Moneys += get_number(Money);
		strCurrent_Money.Format(_T("%g"), Current_Moneys);

		hr = Set_Data(imonth, strCurrent_Money + L"K", 1, 2);
		if(FAILED(hr))
		{
			MessageBoxA(NULL, "Push CURRENT MONEY is Failed!!!", "ERROR", MB_OK|MB_ICONERROR);
			return;
		}*/
	//}

	/*{
		CString strSUM_Money = NULL;
		double SUM_Moneys = 0;
		double money = 0;

		Get_Data(imonth, 2, 2, strSUM_Money);
		SUM_Moneys = get_number(strSUM_Money);
		money = get_number(Money);
		if (money < 0)
		{
			SUM_Moneys += money;
			strSUM_Money.Format(_T("%g"), SUM_Moneys);

			hr = Set_Data(imonth, strSUM_Money + L"K", 2, 2);
			if(FAILED(hr))
			{
				MessageBoxA(NULL, "Push SUM MONEY is Failed!!!", "ERROR", MB_OK|MB_ICONERROR);
				return;
			}
			else
			{
				MessageBoxA(NULL, "Push SUM MONEY is Success!!!", "OK", MB_OK|MB_ICONINFORMATION);
			}
		}
	}*/
	//Set_Format(imonth, L"General", 1, 2);
	//Password_Excel(L"12345");
	//ProtectExcelSheet(7, L"12345");
	Save();
	current_indx++;
	
	MessageBoxA(NULL, "Push is completed!!!", "Info", MB_OK|MB_ICONINFORMATION);
	
}

int CAction::get_number(CString strSource)
{
	int result = 0;
	bool bflag = false;
	int length = strSource.GetLength();
	for(int i= 0; i< length; i++){
		if (strSource[i] - '0' == -3)
		{
			bflag = true;
			continue;
		}
		if (strSource[i] - '0' >= 0 && strSource[i] - '0'!= 27)
		{
			result = result * 10 + (strSource[i] - '0');
		}
	}
	if(bflag)
	{
		result = ~result + 1;
	}
	return result;
}

int CAction::get_Month(CString strSource)
{
	int result = 0;
	for(int i= 0; i< 2; i++){
		if (strSource[i] - '0' >= 0)
			result = result * 10 + (strSource[i] - '0');
	}
	return result;
}

CString CAction::get_Day(CString strSource)
{
	CString result = NULL;
	int length = 0;
	length = strSource.GetLength();

	for(int i= length - 7; i<= length-5; i++){
		if (strSource[i] - '0' >= 0)
		{
			result += strSource[i];
		}
	}
	return result;
}

void CAction::Save_Data(CString Money, CString Note, CString Date)
{
	Data temp;
	temp.strDate = Money;
	temp.strDate = Note;
	temp.strDate = Date;

	vt_Data.push_back(temp);
}
/*
Purpose: Get current line is filled to continue fill

@author _Robert Bostney_
@Date 22/06/2017 
*/
int CAction::Get_curr_index(int imonth)
{
	CString strMoney = NULL;
	CString strNote = NULL;
	CString strDate = NULL;

	for (int i = 3; i < MAX_PATH; i ++)
	{
		Get_Data(imonth, i, 1, strDate);
		if(!strDate.Compare(L"0"))
		{
			return i;
		}

		Get_Data(imonth, i, 2, strMoney);
		if(!strMoney.Compare(L"0"))
		{
			return i;
		}

		Get_Data(imonth, i, 3, strNote);
		if(!strNote.Compare(L"0"))
		{
			return i;
		}
		
	}
}
HRESULT CAction::Set_Current_SUM_Money(int imonth, int row, int colunm, CString strMoney)
{
	CString strCurrent_Money = NULL;
	double Current_Money = 0;
	double db_money = 0;

	Get_Data(imonth, row, colunm, strCurrent_Money);
	Current_Money = get_number(strCurrent_Money);
	
	db_money = get_number(strMoney);

	if (db_money > 0 && row == 2)
	{
		return S_OK;
	}

	Current_Money += db_money;
	strCurrent_Money.Format(_T("%g"), Current_Money);
		
	HRESULT hr = Set_Data(imonth, strCurrent_Money + L"K", row, colunm);
	if(FAILED(hr))
	{
		MessageBoxA(NULL, "Push CURRENT/SUM is Failed!!!", "ERROR", MB_OK|MB_ICONERROR);
		return hr;
	}

	return S_OK;
}

void CAction::View_action()
{
	CString Path_File = NULL;
	Path_File = Get_PathFile();

	HRESULT hr = Open(Path_File, true);
}

void CAction::Pull_action(CString strSheetNo, CString &strSum, CString &strRemain)
{
	int sheetno = 0, index = 0;
	sheetno = get_number(strSheetNo);
	index = Get_curr_index(sheetno);
	Get_Data(sheetno, 2, 2, strSum);

	if(!strSum.Compare(L"0"))
	{
		Get_Datas(sheetno, index, strSum);
	}
	Get_Data(sheetno, 1, 2, strRemain);
}

