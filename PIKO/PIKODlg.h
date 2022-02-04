
// PIKODlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"
#include "CButtonHandler.h"

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

// Implémentation
protected:
	HICON m_hIcon;
	
	// Fonctions générées de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void SearchTagsBtn();

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
	CButton m_searchtags;
};
