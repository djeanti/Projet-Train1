
// PIKODlg.cpp : fichier d'impl�mentation
//

#include "stdafx.h"
#include "PIKO.h"
#include "PIKODlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// bo�te de dialogue CPIKODlg

CPIKODlg::CPIKODlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPIKODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_tags[0] = &m_tag1; m_tags[1] = &m_tag2;
	m_tags[2] = &m_tag3; m_tags[3] = &m_tag4; 
	m_tags[4] = &m_tag5; m_tags[5] = &m_tag6;
	m_tags[6] = &m_tag7; m_tags[7] = &m_tag8;

	m_supports[0]= &m_support1; m_supports[1]= &m_support2;
	m_supports[2]= &m_support3;
	for(int i=3;i<SZ_CARDS;i++)
	{
		m_supports[i]=0;
	}
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
	DDX_Control(pDX, ID_PIKO_STATIC6, m_static_circuit);
	DDX_Control(pDX, IDC_SUPPORT3, m_support1);
	DDX_Control(pDX, IDC_SUPPORT2, m_support2);
	DDX_Control(pDX, IDC_SUPPORT1, m_support3);
}

BEGIN_MESSAGE_MAP(CPIKODlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// gestionnaires de messages pour CPIKODlg

BOOL CPIKODlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Ajouter l'�l�ment de menu "� propos de..." au menu Syst�me.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes syst�me.
	/*ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
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
	}*/

	// D�finir l'ic�ne de cette bo�te de dialogue. L'infrastructure effectue cela automatiquement
	//  lorsque la fen�tre principale de l'application n'est pas une bo�te de dialogue
	SetIcon(m_hIcon, TRUE);			// D�finir une grande ic�ne
	SetIcon(m_hIcon, FALSE);		// D�finir une petite ic�ne


	init_IMAGES();

	// TODO : ajoutez ici une initialisation suppl�mentaire
	CString str;
	for(int i=0;i<SZ_CARDS;i++)
	{
		//str.Format(_T("TAG %d"),i);
		str = BUTTONS_ID[i];
		m_tags[i]->EnableWindow(FALSE);//ASSERT(::IsWindow(m_hWnd) || (m_pCtrlSite != NULL)); echoue 
		m_tags[i]->SetWindowText(str);
	}
		
	return TRUE;  // retourne TRUE, sauf si vous avez d�fini le focus sur un contr�le
}

void CPIKODlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	/*if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		//CAboutDlg dlgAbout;
		//dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}*/
	CDialog::OnSysCommand(nID, lParam);
}

// Si vous ajoutez un bouton R�duire � votre bo�te de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'ic�ne. Pour les applications MFC utilisant le mod�le Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CPIKODlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de p�riph�rique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'ic�ne dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'ic�ne
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Le syst�me appelle cette fonction pour obtenir le curseur � afficher lorsque l'utilisateur fait glisser
//  la fen�tre r�duite.
HCURSOR CPIKODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//affichage des images sur l'interface GUI :

void CPIKODlg::blend_img(size_t idx, LPCTSTR img_name)
/*Role de cette fonction : Afficher une image � l'�cran*/
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
			if(R>SEUIL_BG_IMG && G >SEUIL_BG_IMG && B>SEUIL_BG_IMG)//on supprime le fond de l'image "transparent" qui appara�t comme noir en MFC
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
	blend_img(idx, _T("main_wagon_60.png"));
	tab_img[idx].b.Attach(tab_img[idx].img);
	m_static_img1.SetBitmap( tab_img[idx].b );

	idx+=1;
	blend_img(idx, _T("wagon2_60.png"));
	tab_img[idx].b.Attach(tab_img[idx].img);
	m_static_img2.SetBitmap( tab_img[idx].b );

	idx+=1;
	blend_img(idx, _T("wagon1_60.png"));
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

	//circuit :
	idx+=1;
	blend_img(idx, _T("circuit.png"));
	tab_img[idx].b.Attach(tab_img[idx].img);
	m_static_circuit.SetBitmap( tab_img[idx].b );

	//supports :
	for(int i=0; i<3; i++)
	{
		m_supports[i]->EnableWindow(FALSE);
	}
}


//handlers :
void CPIKODlg::updateTagButton(int idx, BOOL val)
{

		//CString str; str.Format(_T("tag = %d"),idx);
		//::MessageBox(m_hWnd,str,_T("msg"),MB_OK);

		if(idx>=SZ_CARDS || idx <0)	return;
	

		m_tags[idx]->EnableWindow(val);

		if(val==TRUE)//couleur du bouton change
		{
			m_tags[idx]->SetFaceColor(RGB(255,0,0),true);
			m_tags[idx]->SetTextColor(RGB(255,255,255));
			m_tags[idx]->SetWindowText(_T("Detected !"));
		}
		else
		{
			COLORREF MFC_Dlg_Color = ::GetSysColor(COLOR_3DFACE);
			int R, G, B;
			R = GetRValue(MFC_Dlg_Color); G = GetGValue(MFC_Dlg_Color); B = GetBValue(MFC_Dlg_Color);
			m_tags[idx]->SetFaceColor(RGB(R,G,B),true);
			m_tags[idx]->SetTextColor(RGB(0,0,0));	
			
			//CString c_str; c_str.Format(_T("TAG %d"),idx);
			m_tags[idx]->SetWindowText(BUTTONS_ID[idx]);
		}
		//CString str; str.Format(_T("TAG %d"),idx);
		//m_tags[idx]->SetWindowText(_T());
}


void CPIKODlg::updateSupportButton(int idx, BOOL val)
{

		if(idx>=SZ_SUPPORTS_CARDS || idx <0)	return;

		if(val==TRUE)
		{
				//CString str; str.Format(_T("support = %d"),idx);
	//::MessageBox(m_hWnd,str,_T("msg"),MB_OK);

			m_supports[idx]->SetFaceColor(RGB(255,0,0),true);
			m_supports[idx]->SetTextColor(RGB(255,255,255));
			m_supports[idx]->SetWindowText(_T("TAG !"));
		}
		else//couleur par d�faut
		{
			COLORREF MFC_Dlg_Color = ::GetSysColor(COLOR_3DFACE);
			int R, G, B;
			R = GetRValue(MFC_Dlg_Color); G = GetGValue(MFC_Dlg_Color); B = GetBValue(MFC_Dlg_Color);
			m_supports[idx]->SetFaceColor(RGB(R,G,B),true);
			m_supports[idx]->SetTextColor(RGB(0,0,0));
			m_supports[idx]->SetWindowText(_T(""));
		}
		
}

int CPIKODlg::newButtonPopup(CString COM, int num_card)
{
	/*
		Affiche une nouvelle fen�tre � chaque fois qu'une nouvelle carte est connect�e
		Quand on choisit le support sur cette nouvelle fen�tre, on r�cup�re cette information
		puis on renvoit l'index du support s�l�ctionn� ici (de 1 � 3 car on a 3 support en tout).
	*/
	int idx_support=-1;

	//CString str; str.Format(_T("num card = %d"),num_card);
	//::MessageBox(m_hWnd,str,_T("new card !"),MB_OK);

	CMsgRFID dlg;

	INT_PTR nResponse = dlg.DoModal();

	if(nResponse == IDOK)
	{
		idx_support = dlg.GetAnswer();
		//on recup�re les informations (Quel support a �t� s�lectionn�)
		//on supprime le support num�ro idx_support de la liste des supports dont il est possible d'associer une carte, 
		//cela signifie que la prochaine carte qu'on connectera, on aura un support de moins de disponible pour associe la carte
	}

	return idx_support;
}

void CPIKODlg::releaseSupportButton(int idx)
{
	//CString str; str.Format(_T("releasing support %d"),idx);
	//::MessageBox(m_hWnd,str,_T("msg"),MB_OK);

	if(idx>=SZ_SUPPORTS_CARDS || idx <0)	return;
	
	CMsgRFID::releaseSupport(idx);
}