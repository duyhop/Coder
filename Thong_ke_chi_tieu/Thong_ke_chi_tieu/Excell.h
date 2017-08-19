#pragma once
#include "stdafx.h"
class CExcell
{
public:
	CExcell(void);
	~CExcell(void);
	
private:
	// Variable
	IDispatch *m_pEApp;
	IDispatch *m_pBooks;
	IDispatch *m_Sheets;
	IDispatch *m_pActiveBook;
	TCHAR PathFile[MAX_PATH];
	HRESULT m_hr;

protected:

	// function
	HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...);
	HRESULT Initialize(bool bVisible);
	HRESULT OLEMethod(int nType, VARIANT *pvResult, IDispatch *pDisp,LPOLESTR ptName, int cArgs...);
	HRESULT SetVisible(bool bVisible);
	HRESULT Set_Data(int sheet_num, LPCTSTR szText, int nRow, int nCol, int status);
	HRESULT Set_SheetName(int nSheetNo, LPCTSTR szSheetName);
	HRESULT Get_Data(int num_sheet, int nrow, int ncol, CString &sValue);
	HRESULT Get_Datas(int sheet_num, int index, CString &sValue);
	HRESULT SaveAs(LPCTSTR szFilename, int nSaveAs);
	HRESULT Save();
	HRESULT MergeExcelCells(int sheet_num, LPCTSTR szRange);
	HRESULT SetExcelBackgroundColor(int sheet_num, LPCTSTR szRange, COLORREF crColor);
	HRESULT SetExcelBorder(int sheet_num, LPCTSTR szRange, int nStyle);
	HRESULT Password_Excel(LPCTSTR szPassword);
	HRESULT Quit();
	HRESULT ProtectExcelSheet(int nSheetNo, LPCTSTR szPassword);
	HRESULT Create_Format(int nSheetNo);
	HRESULT Create_OWE_Format(int nSheetNo);

public:
	HRESULT Create_File(bool bVisible);
	CString Get_PathFile();
	HRESULT Set_FormatCell(int sheet_num, LPCTSTR szText, int nRow, int nCol);
	HRESULT Open(LPCTSTR szFilename, bool bVisible);
	
};

