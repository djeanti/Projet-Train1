
// Train1Dlg.h : fichier d'en-t�te
//

#pragma once
#include "afxwin.h"
#include "CardReader.h"

#define	IDT_TIMER_0	WM_USER + 200

// bo�te de dialogue CTrain1Dlg
class CTrain1Dlg : public CDialog
{
// Construction
public:
	CTrain1Dlg(CWnd* pParent = NULL);	// constructeur standard

// Donn�es de bo�te de dialogue
	enum { IDD = IDD_TRAIN1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Impl�mentation
protected:
	HICON m_hIcon;

	// Fonctions g�n�r�es de la table des messages
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
	UINT timerID;//event listener pour checker quels cartes sont connect�es
	size_t cpt_timer;
};
