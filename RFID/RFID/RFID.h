
// RFID.h : fichier d'en-tête principal pour l'application RFID
//
#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"       // symboles principaux


// CRFIDApp:
// Consultez RFID.cpp pour l'implémentation de cette classe
//

class CRFIDApp : public CWinAppEx
{
public:
	CRFIDApp();


// Substitutions
public:
	virtual BOOL InitInstance();

// Implémentation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRFIDApp theApp;
