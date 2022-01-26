
// Train1Dlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "Train1.h"
#include "Train1Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Données de boîte de dialogue
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// boîte de dialogue CTrain1Dlg




CTrain1Dlg::CTrain1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTrain1Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrain1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG, m_list);
}

BEGIN_MESSAGE_MAP(CTrain1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CARDS_AVAILABLE, &CTrain1Dlg::OnCardsConnect)
	ON_BN_CLICKED(IDC_SEARCH_TAGS, &CTrain1Dlg::SearchTagsBtn)
END_MESSAGE_MAP()


// gestionnaires de messages pour CTrain1Dlg

BOOL CTrain1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Définir l'icône de cette boîte de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO : ajoutez ici une initialisation supplémentaire
	NB_LIST_IDX=0;
	timerID=1; cpt_timer=0;
	SetTimer(timerID, 1000, 0);

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}


void CTrain1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône. Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CTrain1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CTrain1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTrain1Dlg::OnCardsConnect()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
		/*CString s; 
		s.Format(_T("Bonjour\n"));
		MessageBox(s,_T("Connect"),MB_OK);*/

		//on ajoute un messagea la console ici
		//printMsg(_T("Aucune cartes de connectés"));


		//on regarde quelles cartes sont disponibles
	if(cards_rfid.searchAvailablePorts())
	{
			for(size_t i=0;i<cards_rfid.NB_ELEMS_PORTS_TAB;i++)
			{
				printMsg(CString("A device was detected at ") + cards_rfid.PORTS_TAB[i]);
			}
			//on vérifie si on peut les utiliser ou non :


			for(size_t i=0;i<cards_rfid.NB_ELEMS_PORTS_TAB;i++)
			{
				CString nomPort("\\\\.\\"); nomPort+= cards_rfid.PORTS_TAB[i];
				if(cards_rfid.isAvailable(nomPort))
				{
					printMsg(CString("The RFID card connected to ") + cards_rfid.PORTS_TAB[i] + " is ready to be used !");
				}
			}

			cards_rfid.closeAllCards();
	}
	else
	{
			CString s; 
			s.Format(_T("No\n"));
			MessageBox(s,_T("No card"),MB_OK);
	}

}

void CTrain1Dlg::SearchTagsBtn()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contrôle
		/*CString s; 
		s.Format(_T("%d\n"),(int)m_list.GetCount());
		MessageBox(s,_T("Search for tags"),MB_OK);*/

	clearList();
}

void CTrain1Dlg::printMsg(LPCTSTR msg)
{
	m_list.AddString(msg); NB_LIST_IDX++;
}

void CTrain1Dlg::clearList()
{
	m_list.ResetContent();
}

void CTrain1Dlg::OnTimer(UINT TimerVal)
{
	cpt_timer++;
	CString s; s.Format(_T("Timer count %d sec"),cpt_timer);
	printMsg(_T("truc"));
}