
// PIKO.cpp : D�finit les comportements de classe pour l'application.
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
	// TODO�: ajoutez ici du code de construction,
	// Placez toutes les initialisations significatives dans InitInstance
}


// Seul et unique objet CPIKOApp

CPIKOApp theApp;


// initialisation de CPIKOApp

BOOL CPIKOApp::InitInstance()
{
	CWinAppEx::InitInstance();

	// Initialisation standard
	// Si vous n'utilisez pas ces fonctionnalit�s et que vous souhaitez r�duire la taille
	// de votre ex�cutable final, vous devez supprimer ci-dessous
	// les routines d'initialisation sp�cifiques dont vous n'avez pas besoin.
	// Changez la cl� de Registre sous laquelle nos param�tres sont enregistr�s
	// TODO : modifiez cette cha�ne avec des informations appropri�es,
	// telles que le nom de votre soci�t� ou organisation
	SetRegistryKey(_T("Applications locales g�n�r�es par AppWizard"));

	dlg = new CPIKODlg();

	m_pMainWnd = dlg;

	manager = new CCards();

	manager->setHandlerB(dlg);
	manager->setHandlerM(dlg);
	manager->initCommunications();//appeler cette methode une fois que DoModal a ete appel�e (dans CPIKODlg)

	INT_PTR nResponse = dlg->DoModal();
	
	if (nResponse == IDOK)
	{
		
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO : placez ici le code d�finissant le comportement lorsque la bo�te de dialogue est
		//  ferm�e avec Annuler
	}

	// Lorsque la bo�te de dialogue est ferm�e, retourner FALSE afin de quitter
	//  l'application, plut�t que de d�marrer la pompe de messages de l'application.
	return FALSE;
}