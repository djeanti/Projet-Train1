
// PIKO.cpp : Définit les comportements de classe pour l'application.
//

#include "stdafx.h"
#include "PIKO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPIKOApp

BEGIN_MESSAGE_MAP(CPIKOApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// construction CPIKOApp

CPIKOApp::CPIKOApp()
{
	// TODO : ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CPIKOApp

CPIKOApp theApp;


// initialisation de CPIKOApp

BOOL CPIKOApp::InitInstance()
{
	CWinAppEx::InitInstance();

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalités et que vous souhaitez réduire la taille
	// de votre exécutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation spécifiques dont vous n'avez pas besoin.
	// Changez la clé de Registre sous laquelle nos paramètres sont enregistrés
	// TODO : modifiez cette chaîne avec des informations appropriées,
	// telles que le nom de votre société ou organisation
	SetRegistryKey(_T("Applications locales générées par AppWizard"));

	dlg = new CPIKODlg();

	m_pMainWnd = dlg;

	manager = new CCards();

	manager->setHandlerB(dlg);
	manager->setHandlerM(dlg);
	manager->initCommunications();//appeler cette methode une fois que DoModal a ete appelée (dans CPIKODlg)

	INT_PTR nResponse = dlg->DoModal();
	
	if (nResponse == IDOK)
	{
		
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO : placez ici le code définissant le comportement lorsque la boîte de dialogue est
		//  fermée avec Annuler
	}

	// Lorsque la boîte de dialogue est fermée, retourner FALSE afin de quitter
	//  l'application, plutôt que de démarrer la pompe de messages de l'application.
	return FALSE;
}