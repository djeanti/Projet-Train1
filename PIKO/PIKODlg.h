
// PIKODlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"
#include "CButtonHandler.h"

#define SZ_TAB_IMAGES 5
#define SEUIL_BG_IMG 240 //seuil pour le format RGB d'un pixel au dela duquel le pixel en question hérite de la couleur de la fenetre MFC
struct IMAGE{
public:
	CImage img;
	CBitmap b;
	void Load(LPCTSTR _name) {img.Load(_name);} 

}; typedef struct IMAGE IMAGE;

// boîte de dialogue CPIKODlg
class CPIKODlg : public CDialog, public CButtonHandler
{
// Construction
public:
	CPIKODlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
	enum { IDD = IDD_PIKO_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV
	virtual void updateButton(int idx, BOOL val, LPCTSTR text);

protected:
	void blend_img(size_t idx, LPCTSTR img_name);//change the color of some pixel in the image to blend it perfectly to the mfc window
	void init_IMAGES();//initialise le tableau de struct IMAGE
	
public:
	CButton* m_tags[SZ_CARDS];

	CButton m_tag1;
	CButton m_tag2;
	CButton m_tag3;
	CButton m_tag4;
	CButton m_tag5;
	CButton m_tag6;
	CButton m_tag7;
	CButton m_tag8;

	CStatic m_static_img1;
	CStatic m_static_img2;
	CStatic m_static_img3;
	CStatic m_static_img4;
	CStatic m_static_img5;

	IMAGE tab_img[SZ_TAB_IMAGES];//indice 0 -> m_static_img1 ... 4 -> m_static_img5
	CListBox m_msg;

// Implémentation
protected:
	HICON m_hIcon;
	
	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClearMsg();

	DECLARE_MESSAGE_MAP()
	
};
