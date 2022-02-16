
// PIKO.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux
#include "CardsRFID.h"
#include "PIKODlg.h"

// CPIKOApp:
// Consultez PIKO.cpp pour l'implémentation de cette classe
//

class CPIKOApp : public CWinAppEx
{
public:
	CCards* manager;

public:
	CPIKOApp();

	//cardmanager + threads (tous)

// Substitutions
	public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CPIKOApp theApp;