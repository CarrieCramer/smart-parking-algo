
// smart_parking_gui.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Csmart_parking_guiApp:
// See smart_parking_gui.cpp for the implementation of this class
//

class Csmart_parking_guiApp : public CWinApp
{
public:
	Csmart_parking_guiApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Csmart_parking_guiApp theApp;