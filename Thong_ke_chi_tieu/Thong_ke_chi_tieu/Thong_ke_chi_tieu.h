
// Thong_ke_chi_tieu.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CThong_ke_chi_tieuApp:
// See Thong_ke_chi_tieu.cpp for the implementation of this class
//

class CThong_ke_chi_tieuApp : public CWinApp
{
public:
	CThong_ke_chi_tieuApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CThong_ke_chi_tieuApp theApp;