// MsgRFID.cpp�: fichier d'impl�mentation
//

#include "stdafx.h"
#include "PIKO.h"
#include "MsgRFID.h"


// Bo�te de dialogue CMsgRFID

IMPLEMENT_DYNAMIC(CMsgRFID, CDialog)

//static :
int CMsgRFID::number_available_support = 3;
bool CMsgRFID::support1_selected = false;
bool CMsgRFID::support2_selected = false;
bool CMsgRFID::support3_selected = false;

CMsgRFID::CMsgRFID(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgRFID::IDD, pParent), support1Checked(FALSE), support2Checked(FALSE), support3Checked(FALSE), support_idx(-1)
{
	
}

CMsgRFID::~CMsgRFID()
{
}

void CMsgRFID::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_PIKO_STATIC7, m_static);
	DDX_Control(pDX, IDC_CHECK_SUPPORT1, m_support1);
	DDX_Control(pDX, IDC_CHECK_SUPPORT2, m_support2);
	DDX_Control(pDX, IDC_CHECK_SUPPORT3, m_support3);
}

BOOL CMsgRFID::OnInitDialog()
{
	CDialog::OnInitDialog();

	//show circuit image 
	blend_img(_T("circuit.png"));
	m_bg.b.Attach(m_bg.img);
	m_static.SetBitmap( m_bg.b );

	//hidde support buttons already selected :
	if (support1_selected)
	{
		m_support1.ShowWindow(SW_HIDE);
	}
	if (support2_selected)
	{
		m_support2.ShowWindow(SW_HIDE);
	}
	if (support3_selected)
	{
		m_support3.ShowWindow(SW_HIDE);
	}
	
	return TRUE;
}
void CMsgRFID::blend_img(LPCTSTR img_name)
/*Role de cette fonction : Afficher une image � l'�cran*/
{
	m_bg.img.Load( img_name );//loading the image :
	int w = m_bg.img.GetWidth();
	int h = m_bg.img.GetHeight();
	
	COLORREF MFC_Dlg_Color = ::GetSysColor(COLOR_3DFACE);
	BYTE R_inherit = GetRValue(MFC_Dlg_Color), B_inherit = GetBValue(MFC_Dlg_Color), G_inherit = GetGValue(MFC_Dlg_Color);

	BYTE R, G, B;//pour recuperer la couleur du pixel a chaque iteration
	for(int i=0;i<w;i++)
	{
		for(int j=0;j<h;j++)
		{
			R = GetRValue(m_bg.img.GetPixel(i,j)); 
			G = GetGValue(m_bg.img.GetPixel(i,j)); 
			B = GetBValue(m_bg.img.GetPixel(i,j));
			if(R>SEUIL_BG_IMG && G >SEUIL_BG_IMG && B>SEUIL_BG_IMG)//on supprime le fond de l'image "transparent" qui appara�t comme noir en MFC
			{
				m_bg.img.SetPixelRGB(i,j,R_inherit,G_inherit,B_inherit);
			}
		}
	}

}

BEGIN_MESSAGE_MAP(CMsgRFID, CDialog)
	ON_BN_CLICKED(IDC_CHECK_SUPPORT1, &CMsgRFID::OnSupport1Clicked)
	ON_BN_CLICKED(IDC_CHECK_SUPPORT2, &CMsgRFID::OnSupport2Clicked)
	ON_BN_CLICKED(IDC_CHECK_SUPPORT3, &CMsgRFID::OnSupport3Clicked)
	ON_BN_CLICKED(IDOK, &CMsgRFID::OnBnClickedOk)
END_MESSAGE_MAP()

// Gestionnaires de messages de CMsgRFID
void CMsgRFID::OnSupport1Clicked()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contr�le
	support1Checked = !support1Checked;

	m_support2.EnableWindow(!support1Checked);
	m_support3.EnableWindow(!support1Checked);

	support_idx = 1;
}

void CMsgRFID::OnSupport2Clicked()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contr�le
	support2Checked = !support2Checked;

	m_support1.EnableWindow(!support2Checked);
	m_support3.EnableWindow(!support2Checked);

	support_idx = 2;
}

void CMsgRFID::OnSupport3Clicked()
{
	// TODO : ajoutez ici le code de votre gestionnaire de notification de contr�le
	support3Checked = !support3Checked;

	m_support1.EnableWindow(!support3Checked);
	m_support2.EnableWindow(!support3Checked);

	support_idx = 3;
}

void CMsgRFID::OnBnClickedOk()
{

	// TODO : ajoutez ici le code de votre gestionnaire de notification de contr�le
	if(support1Checked==TRUE || support2Checked==TRUE || support3Checked==TRUE)
	{
		if(!support1_selected)	support1_selected = (support1Checked==TRUE);
		if(!support2_selected)	support2_selected = (support2Checked==TRUE);
		if(!support3_selected)	support3_selected = (support3Checked==TRUE);
		
		number_available_support--;
		OnOK();
	}
	else
	{
		::MessageBox(m_hWnd,_T("Vous devez choisir l'un des supports avant de valider !"),_T("Choix incorrect"),MB_OK);
	}

}

int CMsgRFID::GetAnswer()
{
	return support_idx;
}

bool CMsgRFID::isAvailableSupport()
{
	return number_available_support>0;
}