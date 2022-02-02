
// PIKODlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"





#include "CardsRFID.h"

struct ThGui//structure pour ThGUI
{
	RFID* cards;//tableau des cartes
	//CButton *m1, *m2, *m3, *m4, *m5, *m6, *m7, *m8;
	CButton** m_tab;
	void switchState(BOOL val, int idx, LPCTSTR text=_T("Not connected"))
	{
		m_tab[i]->EnableWindow(val);
		m_tab[i]->SetWindowText(text);
	}

	public THGui(CButton *m1, CButton *m2, CButton *m3, CButton *m4, CButton *m5, CButton *m6, CButton *m7, CButton *m8)//constructor
	{
		m_tab = new CButton*[SZ_CARDS];
		for(size_t i=0;i<SZ_CARDS;i++)
		{	
			m_tab[i] = new CButton(); 
		}
		m_tab[0] = m1; m_tab[1] = m2; m_tab[2] = m3; m_tab[3] = m4; m_tab[4] = m5; m_tab[5] = m6; m_tab[6] = m7; m_tab[7] = m8;
	}

	~ThGui()
	{
		for(size_t i=0;i<SZ_CARDS;i++)
		{	
			delete m_tab[i]; 
		}
		delete[] m_tab;
	}
};typedef struct ThGui ThGui;

// boîte de dialogue CPIKODlg
class CPIKODlg : public CDialog
{
// Construction
public:
	CPIKODlg(CWnd* pParent = NULL);	// constructeur standard
	~CPIKODlg()
	{
		if(th_gui!=NULL)	CloseHandle(th_gui);
		delete thgui_struct;
	}

// Données de boîte de dialogue
	enum { IDD = IDD_PIKO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


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

protected://attributs:
	HANDLE th_gui;//thread actualisant l'interface GUI
	CCards card_manager;
	ThGui* thgui_struct;

protected://methods
	static DWORD WINAPI ThGUI(void* arg);

public:
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
