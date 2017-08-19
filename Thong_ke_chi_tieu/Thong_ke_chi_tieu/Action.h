#pragma once
#include "Excell.h"
using namespace std;

class CAction: public CExcell
{
private:
	typedef struct {
		CString strDate;
		CString strMoney;
		CString strNote;
	} Data;
public:
	CAction(void);
	~CAction(void);

	vector<Data> vt_Data;
	
	void View_action();
	void Push_action(CString money, CString Note, CString Date);
	void Push_owe_action(CString money, CString Note, CString Date);
	void Pull_action(CString strSheetNo, CString &strSum, CString &strRemain);
	void Sum_action(CString Month);
	int get_number(CString strSource);
	int get_Month(CString strSource);
	CString get_Day(CString strSource);
	void Save_Data(CString Money, CString Note, CString Date);
	int Get_curr_index(int imonth, int type);
	HRESULT Set_Current_SUM_Money(int month, int row, int colunm, int iMoney);
};

