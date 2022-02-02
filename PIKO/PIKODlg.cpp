
// PIKODlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "PIKO.h"
#include "PIKODlg.h"

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


// boîte de dialogue CPIKODlg




CPIKODlg::CPIKODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPIKODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPIKODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAG1, m_tag1);
	DDX_Control(pDX, IDC_TAG2, m_tag2);
	DDX_Control(pDX, IDC_TAG3, m_tag3);
	DDX_Control(pDX, IDC_TAG4, m_tag4);
	DDX_Control(pDX, IDC_TAG5, m_tag5);
	DDX_Control(pDX, IDC_TAG6, m_tag6);
	DDX_Control(pDX, IDC_TAG7, m_tag7);
	DDX_Control(pDX, IDC_TAG8, m_tag8);
	DDX_Control(pDX, IDC_CONNECT_TAGS, m_searchtags);
}

BEGIN_MESSAGE_MAP(CPIKODlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CONNECT_TAGS, &CPIKODlg::SearchTagsBtn)
END_MESSAGE_MAP()


// gestionnaires de messages pour CPIKODlg

BOOL CPIKODlg::OnInitDialog()
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
	//le code commenté ci-dessous empeche l'apparition de l'executable du programme 
	thgui_struct = new ThGui;
	
	thgui_struct->m1 = &m_tag1; thgui_struct->m2 = &m_tag2; thgui_struct->m3 = &m_tag3;
	thgui_struct->m4 = &m_tag4; thgui_struct->m5 = &m_tag5; thgui_struct->m6 = &m_tag6;
	thgui_struct->m7 = &m_tag7; thgui_struct->m8 = &m_tag8;
	thgui_struct->cards = card_manager.getRFID();

	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CPIKODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPIKODlg::OnPaint()
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
HCURSOR CPIKODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI CPIKODlg::ThGUI(void* arg)
{
	ThGui* struct_gui = (ThGui*)arg;//contient toute la structure
	//on actualise l'interface GUI ici (le texte des boutons et si ils sont activés ou désactivés)
	while(1)
	{
		
		for(size_t i=0;i<SZ_CARDS;i++)
		{
			if(struct_gui->cards[i].isConnected)
			{
				if(!struct_gui->cards[i].NoTag)//On ne lit aucun tag RFID
				{
					//On désactive le bouton
					struct_gui.switchState(FALSE,i);
					//setButtonState(i, FALSE, struct_gui, _T("No Tag"));
				}
				else
				{
					struct_gui.switchState(TRUE,i,(LPCTSTR)(struct_gui->cards->id_read));//faux
					//On active le bouton
				}
			}
		}//end for
	}
	return 0;
}

void CPIKODlg::SearchTagsBtn()
{
	/*Role de cette fonction:
	
	-Lancer les threads de CCards
	-créé un thread pour changer l'état des boutons de l'interface GUI régulièrement en fonction de la structure RFID* de cards.
	*/
	card_manager.initCommunications();
	th_gui = ::CreateThread(0,0,ThGUI,thgui_struct,0,0);
	m_searchtags.EnableWindow(FALSE);
	CString s("searching for tag...");
	m_searchtags.SetWindowTextW((LPCTSTR)s);
	//Griser les bouttons des tags RFID qui ne sont pas detectés
	
}
