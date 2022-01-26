
// Train1.h : fichier d'en-tête principal pour l'application PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "incluez 'stdafx.h' avant d'inclure ce fichier pour PCH"
#endif

#include "resource.h"		// symboles principaux


// CTrain1App:
// Consultez Train1.cpp pour l'implémentation de cette classe
//

class CTrain1App : public CWinAppEx
{
public:
	CTrain1App();

// Substitutions
	public:
	virtual BOOL InitInstance();

// Implémentation

	DECLARE_MESSAGE_MAP()
};

extern CTrain1App theApp;