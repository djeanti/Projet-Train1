
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
	m_tags[0] = &m_tag1; m_tags[1] = &m_tag2;
	m_tags[2] = &m_tag3; m_tags[3] = &m_tag4; 
	m_tags[4] = &m_tag5; m_tags[5] = &m_tag6;
	m_tags[6] = &m_tag7; m_tags[7] = &m_tag8;
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
	DDX_Control(pDX, ID_PIKO_STATIC1, m_static_img1);
	DDX_Control(pDX, ID_PIKO_STATIC2, m_static_img2);
	DDX_Control(pDX, ID_PIKO_STATIC3, m_static_img3);
	DDX_Control(pDX, ID_PIKO_STATIC4, m_static_img4);
	DDX_Control(pDX, ID_PIKO_STATIC5, m_static_img5);
	DDX_Control(pDX, IDC_LIST1, m_msg);
}

BEGIN_MESSAGE_MAP(CPIKODlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CPIKODlg::OnClearMsg)
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

	init_IMAGES();

	// TODO : ajoutez ici une initialisation supplémentaire
	for(int i=0;i<SZ_CARDS;i++)
	{
		m_tags[i]->EnableWindow(FALSE);
		m_tags[i]->SetWindowText(_T("NoTag"));
	}
		
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

//affichage des images sur l'interface GUI :

void CPIKODlg::blend_img(size_t idx, LPCTSTR img_name)
/*Role de cette fonction : Afficher une image à l'écran*/
{
	if(idx>=SZ_TAB_IMAGES)	 return;

	tab_img[idx].img.Load( img_name );//loading the image :
	int w = tab_img[idx].img.GetWidth();
	int h = tab_img[idx].img.GetHeight();
	
	COLORREF MFC_Dlg_Color = ::GetSysColor(COLOR_3DFACE);
	BYTE R_inherit = GetRValue(MFC_Dlg_Color), B_inherit = GetBValue(MFC_Dlg_Color), G_inherit = GetGValue(MFC_Dlg_Color);

	BYTE R, G, B;//pour recuperer la couleur du pixel a chaque iteration
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			R = GetRValue(tab_img[idx].img.GetPixel(i,j)); 
			G = GetGValue(tab_img[idx].img.GetPixel(i,j)); 
			B = GetBValue(tab_img[idx].img.GetPixel(i,j));
			if(R>SEUIL_BG_IMG && G >SEUIL_BG_IMG && B>SEUIL_BG_IMG)//on supprime le fond de l'image "transparent" qui apparaît comme noir en MFC
			{
				tab_img[idx].img.SetPixelRGB(i,j,R_inherit,G_inherit,B_inherit);
			}
		}
	}

}

void CPIKODlg::init_IMAGES()
{
	//Charger les images :
	size_t idx=0;
	blend_img(idx, _T("wagon1_60.png"));
	tab_img[idx].b.Attach(tab_img[idx].img);
	m_static_img1.SetBitmap( tab_img[idx].b );
	//m_static_img1.SetWindowPos(this,1000,1000,tab_img[0].img.GetWidth(),tab_img[0].img.GetHeight(),SS_BITMAP | SS_CENTERIMAGE);

	idx+=1;
	blend_img(idx, _T("wagon2_60.png"));
	tab_img[idx].b.Attach(tab_img[idx].img);
	m_static_img2.SetBitmap( tab_img[idx].b );

	idx+=1;
	blend_img(idx, _T("main_wagon_60.png"));
	tab_img[idx].b.Attach(tab_img[idx].img);
	m_static_img3.SetBitmap( tab_img[idx].b );

	idx+=1;
	blend_img(idx, _T("wagon3_60.png"));
	tab_img[idx].b.Attach(tab_img[idx].img);
	m_static_img4.SetBitmap( tab_img[idx].b );

	idx+=1;
	blend_img(idx, _T("wagon4_60.png"));
	tab_img[idx].b.Attach(tab_img[idx].img);
	m_static_img5.SetBitmap( tab_img[idx].b );
}


//handlers :
void CPIKODlg::updateButton(int idx, BOOL val, LPCTSTR text)
{
	//Problème : 
	/*
		ASSERT(::IsWindow(m_hWnd) || (m_pCtrlSite != NULL)); est appelé automatiquement par le système 
		quand EnableWindow et SetWindowText sont appelés et pour une raison inconnue
		il se trouve que cette assertion échoue, ce qui n'est pas normale car dans PIKO.cpp
		on a créé ce handle normalement (dans InitiInstance)
	*/

	//les deux if commentés ci-dessous ne créé pas d'erreur d'execution donc ::IsWindow(m_hWnd) est faux et m_pCtrlSite==NULL
	/*if(m_pCtrlSite != NULL)
	{
			m_tags[idx]->EnableWindow(val);
	}
	
	if(::IsWindow(m_hWnd) == TRUE)
	{
			m_tags[idx]->EnableWindow(val);
	}*/

	m_tags[idx]->EnableWindow(val);//ASSERT(::IsWindow(m_hWnd) || (m_pCtrlSite != NULL)); echoue 
	//m_tags[idx]->SetWindowText(text);
}

void CPIKODlg::OnClearMsg()
{
	//supprimer tous les messages de la listbox
	m_msg.ResetContent();
}
