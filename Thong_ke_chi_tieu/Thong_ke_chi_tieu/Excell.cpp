#include "stdafx.h"
#include "Excell.h"


CExcell::CExcell(void): m_hr(NULL), m_pEApp(NULL), m_pBooks(NULL), m_pActiveBook(NULL), m_Sheets(NULL)
{
	//m_hr = S_OK;
	//m_pEApp = NULL;
	//m_pBooks = NULL;
	//m_pActiveBook = NULL;
	//m_Sheets = NULL;
}


CExcell::~CExcell(void)
{
	//Quit();
//	CoUninitialize();
}

HRESULT CExcell::Initialize(bool bVisible)
{
	CoInitialize(NULL);
	CLSID clsid;
	m_hr = CLSIDFromProgID(L"Excel.Application", &clsid);
	if(SUCCEEDED(m_hr))
	{
		m_hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, 
							  IID_IDispatch, (void **)&m_pEApp);
		if(FAILED(m_hr)) m_pEApp=NULL;
	}
	SetVisible(bVisible);
	return m_hr;
}

HRESULT CExcell::Create_File(bool bVisible)
{
	if(m_pEApp==NULL) 
	{
		if(FAILED(m_hr=Initialize(bVisible)))
			return m_hr;
	}

	// Check file exist
	{
		CString Path_File;
		Path_File = Get_PathFile();

		if(PathFileExists(Path_File))
		{
			Open(Path_File, false);
			return m_hr;
		}
	}

	{
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_pEApp, L"Workbooks", 0);
		m_pBooks = result.pdispVal;
	}

	{	
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_METHOD, &result, m_pBooks, L"Add", 0);
		m_pActiveBook = result.pdispVal;
	}

	{	
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_pActiveBook, L"Sheets", 0);
		m_Sheets = result.pdispVal;
	}

	IDispatch *pSheet;
	{
		VARIANT result, param1;
		VariantInit(&result);
		result.pdispVal = NULL;
		param1.vt = VT_I4;
		param1.lVal = 3;
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, param1);
		pSheet = result.pdispVal;
	}

	{
		VARIANT var1, var2;
		var1.pdispVal = NULL;
		var1.vt = VT_NULL;
 
		var2.pdispVal = pSheet;
		var2.vt = VT_DISPATCH;

		for(int i = 9; i--;)
		{
			m_hr=OLEMethod(DISPATCH_METHOD, NULL, m_Sheets, L"Add", 2, var2, var1);
		}
	}

	// init number sheets, sheet name, boder, color
	{
		LPCTSTR Month[12] = {L"January", L"February", L"March", L"April", L"May", L"June", L"July", L"August", L"September", L"October", L"Novemer", L"December"};
	
		for(int i = 12; i--;)
		{
			Set_SheetName(i+1, Month[i]);
		}
	}

	//Save file
	{
		COleVariant varFilename((LPCTSTR)PathFile);
		VARIANT varAs;
		varAs.vt=VT_I4;
		varAs.intVal=-4143;
		m_hr=OLEMethod(DISPATCH_METHOD,NULL,m_pActiveBook,L"SaveAs",2,varAs,varFilename.Detach());
	}

	pSheet->Release();

	return m_hr;
}

HRESULT CExcell::Create_Format(int nSheetNo)
{
	// init number sheets, sheet name, boder, color
	Set_Data(nSheetNo, L"CURRENT", 1, 1);
	SetExcelBackgroundColor(nSheetNo, L"A1", 255);
	Set_Data(nSheetNo, L"SUM", 2, 1);
	SetExcelBackgroundColor(nSheetNo, L"A2", 255);
	SetExcelBackgroundColor(nSheetNo, L"A3:H3", 16776960);
	Set_Data(nSheetNo, L"DAY", 3, 1);
	Set_Data(nSheetNo, L"MONEY", 3, 2);
	MergeExcelCells(nSheetNo, L"C3:H3");
	Set_Data(nSheetNo, L"NOTE", 3, 3);
	SetExcelBorder(nSheetNo, L"A3", 1);
	SetExcelBorder(nSheetNo, L"B3", 1);
	SetExcelBorder(nSheetNo, L"C3:H3", 1);
	Set_FormatCell(nSheetNo, L"General", 1, 2);

	return m_hr;
}

HRESULT CExcell::Open(LPCTSTR szFilename, bool bVisible)
{
	if(m_pEApp==NULL) 
	{
		if(FAILED(m_hr=Initialize(bVisible)))
			return m_hr;
	}

	{
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_pEApp, L"Workbooks", 0);
		m_pBooks = result.pdispVal;
	}

	{
		COleVariant sFname(szFilename);
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_pBooks, L"Open", 1,sFname.Detach());
		m_pActiveBook = result.pdispVal;
	}

	{	
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_pActiveBook, L"Sheets", 0);
		m_Sheets = result.pdispVal;
	}

	return m_hr;
}

HRESULT CExcell::Set_SheetName(int nSheetNo, LPCTSTR szSheetName)
{
	if(!m_pEApp) return E_FAIL;
	if(!m_pActiveBook) return E_FAIL;

	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = nSheetNo;
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);
		pSheet = result.pdispVal;
	}

	{
		COleVariant oleName(szSheetName);
		m_hr=OLEMethod(DISPATCH_PROPERTYPUT, NULL, pSheet, L"Name", 1, oleName.Detach());
	}

	pSheet->Release();
	return m_hr;
}
HRESULT CExcell::Quit()
{
	if(m_pEApp==NULL) return E_FAIL;
	DISPID dispID;
	LPOLESTR ptName=_T("Quit");
	m_hr = m_pEApp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
	
	if(SUCCEEDED(m_hr))
	{
		DISPPARAMS dp = { NULL, NULL, 0, 0 };
		m_hr = m_pEApp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD, 
									&dp, NULL, NULL, NULL);
	}
	m_pEApp->Release();
	CoUninitialize();
	m_pEApp=NULL;
	return m_hr;
}

HRESULT CExcell::Set_Data(int sheet_num, LPCTSTR szText, int nRow, int nCol)
{
	static int number = 0;
	number++;

	if(!m_pEApp || !m_pActiveBook) return E_FAIL;

	IDispatch *pActiveCell;
	{
		VARIANT result;
		VariantInit(&result);

		m_hr = OLEMethod(DISPATCH_PROPERTYGET, &result, m_pEApp, L"ActiveCell", 0);
		pActiveCell=result.pdispVal;
	}

	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = sheet_num;

		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);
		pSheet = result.pdispVal;
	}

	IDispatch *pCells;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT row, col;
		row.vt =VT_I4;
		row.lVal =nRow;
		col.vt =VT_I4;
		col.lVal =nCol;

		m_hr = OLEMethod(DISPATCH_PROPERTYGET, &result, pSheet, L"Cells", 2,col,row);
		pCells=result.pdispVal;
	}
	/*if(number == 1)
	{
		COleVariant val(L"Date");
		m_hr = OLEMethod(DISPATCH_PROPERTYPUT, NULL, pCells, L"NumberFormat", 1,val.Detach());
	}*/

	if(number == 2 || number == 4)
	{
		COleVariant val(L"General");
		m_hr = OLEMethod(DISPATCH_PROPERTYPUT, NULL, pCells, L"NumberFormat", 1,val.Detach());
		if(number == 4)
			number = 0;
	}
	else
	{
		CString temp = NULL;
		CString Range = NULL;
		
		temp.Format(_T("%d"), nRow);
		if (temp.Compare(L"1") && temp.Compare(L"2"))
		{
			Range = (CString)"C" + temp + (CString)":" + (CString)"H" + temp;

			IDispatch* pRange;
			{
				COleVariant oleParam(Range);
				VARIANT result;
				VariantInit(&result);
				m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pSheet, L"Range", 1, oleParam.Detach());
				pRange = result.pdispVal;
			}

				m_hr=OLEMethod(DISPATCH_METHOD, NULL, pRange, L"Merge", 0);
		}
	}
	COleVariant val(szText);
	m_hr = OLEMethod(DISPATCH_PROPERTYPUT, NULL, pCells, L"Value", 1,val.Detach());

	pCells->Release();
	pSheet->Release();
	pActiveCell ->Release();

	return m_hr;
}

HRESULT CExcell::SaveAs(LPCTSTR szFilename, int nSaveAs)
{
	COleVariant varFilename(szFilename);
	VARIANT varAs;
	varAs.vt=VT_I4;
	varAs.intVal=1;

	m_hr=OLEMethod(DISPATCH_METHOD,NULL,m_pActiveBook,L"SaveAs",2,varAs,varFilename.Detach());

	return m_hr;
}

HRESULT CExcell::Save()
{
	COleVariant varFilename(PathFile);
	VARIANT varAs;
	varAs.vt=VT_I4;
	varAs.intVal=-1200;
	m_hr=OLEMethod(DISPATCH_METHOD,NULL,m_pActiveBook,L"Save",2,varAs, varFilename.Detach());
	{
          VARIANT x;
          x.vt = VT_I4;
          x.lVal = 1;
          m_hr = OLEMethod(DISPATCH_PROPERTYPUT, NULL, m_pActiveBook, L"Save", 1, x);
    }
	//m_hr = OLEMethod(DISPATCH_METHOD, NULL, m_pEApp, L"Quit", 0);
	return m_hr;
}

HRESULT CExcell::SetVisible(bool bVisible)
{
	if(!m_pEApp) return E_FAIL;
	VARIANT x;
	x.vt = VT_I4;
	x.lVal = bVisible;
	m_hr=OLEMethod(DISPATCH_PROPERTYPUT, NULL, m_pEApp, L"Visible", 1, x);

	return m_hr;
}

HRESULT CExcell::OLEMethod(int nType, VARIANT *pvResult, IDispatch *pDisp,LPOLESTR ptName, int cArgs...)
{
	if(!pDisp) return E_FAIL;

	va_list marker;
	va_start(marker, cArgs);

	DISPPARAMS dp = { NULL, NULL, 0, 0 };
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPID dispID;
	char szName[200];


	// Convert down to ANSI
	WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);

	// Get DISPID for name passed...
	HRESULT hr= pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
	if(FAILED(hr)) {
		return hr;
	}
	// Allocate memory for arguments...
	VARIANT *pArgs = new VARIANT[cArgs+1];
	// Extract arguments...
	for(int i=0; i<cArgs; i++) {
		pArgs[i] = va_arg(marker, VARIANT);
	}

	// Build DISPPARAMS
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs;

	// Handle special-case for property-puts!
	if(nType & DISPATCH_PROPERTYPUT) {
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}

	// Make the call!
	hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, nType, &dp, pvResult, NULL, NULL);
	if(FAILED(hr)) {
		return hr;
	}
	// End variable-argument section...
	va_end(marker);

	delete [] pArgs;
	return hr;
}

HRESULT CExcell::Get_Data(int sheet_num, int nrow, int ncol, CString &sValue)
{
	if(!m_pEApp) return E_FAIL;
	if(!m_pActiveBook) return E_FAIL;

	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = sheet_num;

		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);

		pSheet = result.pdispVal;
	}

	IDispatch *pCells;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT row, col;
		row.vt =VT_I4;
		row.lVal = nrow;
		col.vt =VT_I4;
		col.lVal = ncol;

		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pSheet, L"Cells", 2,col,row);

		pCells=result.pdispVal;
	}

	{
		VARIANT result;
		VariantInit(&result);

		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pCells, L"Value", 0);

		sValue = BSTR(result.pbstrVal);
		if(!sValue.Compare(L""))
		{
			sValue.Format(_T("%g"), result.dblVal);
		}
		
	}

	pCells->Release();
	pSheet->Release();
	return m_hr;
}
HRESULT CExcell::Get_Datas(int sheet_num, int index, CString &sValue)
{
	if(!m_pEApp) return E_FAIL;
	if(!m_pActiveBook) return E_FAIL;

	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = sheet_num;

		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);

		pSheet = result.pdispVal;
	}
	IDispatch *pCells;
	VARIANT result;
	VARIANT row, col;
	double Datas = 0;
	for (int i = 4; i <= index; i++)
	{
		VariantInit(&result);
		
		row.vt =VT_I4;
		row.lVal = i;
		col.vt =VT_I4;
		col.lVal = 2;

		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pSheet, L"Cells", 2,col,row);

		pCells=result.pdispVal;

		VariantInit(&result);

		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pCells, L"Value", 0);

		//sValue = BSTR(result.pbstrVal);
		Datas += result.dblVal;
	}
	sValue.Format(_T("%g"), result.dblVal);

	//pCells->Release();
	pSheet->Release();
	return m_hr;
}

HRESULT CExcell::MergeExcelCells(int sheet_num, LPCTSTR szRange)
{
	if(!m_pEApp) return E_FAIL;
	if(!m_pActiveBook) return E_FAIL;

	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = sheet_num;
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);
		pSheet = result.pdispVal;
	}

	IDispatch* pRange;
	{
		COleVariant oleParam(szRange);
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pSheet, L"Range", 1, oleParam.Detach());
		pRange = result.pdispVal;
	}

	{
		m_hr=OLEMethod(DISPATCH_METHOD, NULL, pRange, L"Merge", 0);
	}

	pRange->Release();
	pSheet->Release();
	return m_hr;
}

HRESULT CExcell::SetExcelBackgroundColor(int sheet_num, LPCTSTR szRange, COLORREF crColor)
{
	if(!m_pEApp) return E_FAIL;
	if(!m_pActiveBook) return E_FAIL;

	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = sheet_num;
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);
		pSheet = result.pdispVal;
	}

	IDispatch* pRange;
	{
		COleVariant oleRange(szRange);
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pSheet, L"Range", 1, oleRange.Detach());
		pRange = result.pdispVal;
	}

	IDispatch *pInterior;
	{
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pRange, L"Interior",0);
		pInterior=result.pdispVal;
	}

	{
		VARIANT x;
		x.vt = VT_I4;
		x.lVal = crColor;
		m_hr=OLEMethod(DISPATCH_PROPERTYPUT, NULL, pInterior, L"Color", 1, x);
	}

	pInterior->Release();
	pRange->Release();
	pSheet->Release();
	//pSheets->Release();
	return m_hr;
}

HRESULT CExcell::SetExcelBorder(int sheet_num, LPCTSTR szRange, int nStyle)
{
	if(!m_pEApp) return E_FAIL;
	if(!m_pActiveBook) return E_FAIL;

	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = sheet_num;
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);
		pSheet = result.pdispVal;
	}

	IDispatch* pRange;
	{
		COleVariant oleParam(szRange);
		VARIANT result;
		VariantInit(&result);
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, pSheet, L"Range", 1, oleParam.Detach());
		pRange = result.pdispVal;
	}

	{
		VARIANT x;
		x.vt = VT_I4;
		x.lVal = nStyle;
		m_hr=OLEMethod(DISPATCH_METHOD, NULL, pRange, L"BorderAround", 1, x);
	}

	pRange->Release();
	pSheet->Release();
	//pSheets->Release();
	return m_hr;
}

HRESULT CExcell::Password_Excel(LPCTSTR szPassword)
{
	if(!m_pEApp) return E_FAIL;
	if(!m_pActiveBook) return E_FAIL;

	COleVariant olePassword(szPassword);

	return m_hr=OLEMethod(DISPATCH_METHOD, NULL, m_pActiveBook, L"Protect", 0, olePassword.Detach());
}

HRESULT CExcell::ProtectExcelSheet(int nSheetNo, LPCTSTR szPassword)
{
	if(!m_pEApp) return E_FAIL;
	if(!m_pActiveBook) return E_FAIL;

	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = nSheetNo;
		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);
		pSheet = result.pdispVal;
	}

	{
		COleVariant olePassword(szPassword);
		m_hr=OLEMethod(DISPATCH_METHOD, NULL, pSheet, L"Protect", 1, olePassword.Detach());
	}
	pSheet->Release();
	return m_hr;
}

CString CExcell::Get_PathFile()
{
	// Check exist path && file
	GetCurrentDirectory( MAX_PATH, PathFile);
	wsprintf(PathFile, L"%s%s", PathFile, L"\\OutPut_Data");

	if(!PathFileExists(PathFile))
	{
		CreateDirectory(PathFile,NULL);
	}
	wsprintf(PathFile, L"%s%s", PathFile, L"\\Data.xls");

	return PathFile;
}

HRESULT CExcell::Set_FormatCell(int sheet_num, LPCTSTR szText, int nRow, int nCol)
{
	if(!m_pEApp || !m_pActiveBook) return E_FAIL;

	IDispatch *pActiveCell;
	{
		VARIANT result;
		VariantInit(&result);

		m_hr = OLEMethod(DISPATCH_PROPERTYGET, &result, m_pEApp, L"ActiveCell", 0);
		pActiveCell=result.pdispVal;
	}
	
	IDispatch *pSheet;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT itemn;
		itemn.vt = VT_I4;
		itemn.lVal = sheet_num;

		m_hr=OLEMethod(DISPATCH_PROPERTYGET, &result, m_Sheets, L"Item", 1, itemn);
		pSheet = result.pdispVal;
	}

	IDispatch *pCells;
	{
		VARIANT result;
		VariantInit(&result);
		VARIANT row, col;
		row.vt =VT_I4;
		row.lVal =nRow;
		col.vt =VT_I4;
		col.lVal =nCol;

		m_hr = OLEMethod(DISPATCH_PROPERTYGET, &result, pSheet, L"Cells", 2,col,row);
		pCells=result.pdispVal;
	}

	COleVariant val(szText);
	m_hr = OLEMethod(DISPATCH_PROPERTYPUT, NULL, pCells, L"NumberFormat", 1,val.Detach());
	/*COleVariant olePassword(L"12345");
	m_hr=OLEMethod(DISPATCH_METHOD, NULL, m_pActiveBook, L"Unprotect", 1, olePassword.Detach());
*/
	

	pCells->Release();
	pSheet->Release();
	pActiveCell ->Release();

	return m_hr;
}