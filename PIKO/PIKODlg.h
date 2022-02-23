
// PIKODlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"
#include "CButtonHandler.h"
#include "CMessageHandler.h"
#include "afxcmn.h"
#include "MsgRFID.h"

#define SZ_TAB_IMAGES 6

#define SEUIL_BG_IMG 240 //seuil pour le format RGB d'un pixel au dela duquel le pixel en question hérite de la couleur de la fenetre MFC

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
	//methodes surchargées de CButtonHandler :
	virtual void updateTagButton(int idx, BOOL val);	
	virtual void updateSupportButton(int idx, BOOL val);
	virtual int newButtonPopup(CString COM, int num_card);
	virtual void releaseSupportButton(int idx);

	//autres méthodes :
	void blend_img(size_t idx, LPCTSTR img_name);//change the color of some pixel in the image to blend it perfectly to the mfc window
	void init_IMAGES();//initialise le tableau de struct IMAGE

protected://attributs encapsulés de la fenêtre

	CMFCButton m_tag1;
	CMFCButton m_tag2;
	CMFCButton m_tag3;
	CMFCButton m_tag4;
	CMFCButton m_tag5;
	CMFCButton m_tag6;
	CMFCButton m_tag7;
	CMFCButton m_tag8;

	CStatic m_static_img1;
	CStatic m_static_img2;
	CStatic m_static_img3;
	CStatic m_static_img4;
	CStatic m_static_img5;
	CStatic m_static_circuit;

	CMFCButton m_support1;
	CMFCButton m_support2;
	CMFCButton m_support3;

	//tableaux :
	CMFCButton* m_tags[SZ_CARDS];
	CMFCButton* m_supports[SZ_SUPPORTS_CARDS];
	IMAGE tab_img[SZ_TAB_IMAGES];//indice 0 -> m_static_img1 ... 4 -> m_static_img5

// Implémentation
protected:
	HICON m_hIcon;
		
	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
};
