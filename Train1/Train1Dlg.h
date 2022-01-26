
// Train1Dlg.h : fichier d'en-tête
//

#pragma once
#include "afxwin.h"
#include "CardReader.h"

#define	IDT_TIMER_0	WM_USER + 200

// boîte de dialogue CTrain1Dlg
class CTrain1Dlg : public CDialog
{
// Construction
public:
	CTrain1Dlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
	enum { IDD = IDD_TRAIN1_DIALOG };

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
	DECLARE_MESSAGE_MAP();
	void printMsg(LPCTSTR msg);//affiche un message dans la list
	void clearList();//supprime le contenu de la listbox
	void OnTimer(UINT TimerVal);

public:
	afx_msg void OnCardsConnect();
	afx_msg void SearchTagsBtn();
	CListBox m_list;
	size_t NB_LIST_IDX;//nb de lignes affiche sur la list a l'instant t
	RFID cards_rfid;

private : 
	UINT timerID;//event listener pour checker quels cartes sont connectées
	size_t cpt_timer;
};
