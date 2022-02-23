#pragma once
#include "afxwin.h"

#include "RFID.h"
// Boîte de dialogue CMsgRFID

class CMsgRFID : public CDialog
{
	DECLARE_DYNAMIC(CMsgRFID)

public:
	CMsgRFID(CWnd* pParent = NULL);   // constructeur standard
	virtual ~CMsgRFID();

// Données de boîte de dialogue
	enum { IDD = IDD_POPUP_RFID };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV
	virtual BOOL OnInitDialog();
	void blend_img(LPCTSTR img_name);
	
	DECLARE_MESSAGE_MAP()

private:
	CStatic m_static;
	IMAGE m_bg;
	CButton m_support1; BOOL support1Checked;
	CButton m_support2; BOOL support2Checked;
	CButton m_support3; BOOL support3Checked;
	int support_idx;//support choisi(indice)

	//static int number_available_support;
	static bool support1_selected, support2_selected, support3_selected;//if true  => on ne peut plus choisir le support 1 car il a déjà été sélectionné
protected : 
	afx_msg void OnSupport1Clicked();
	afx_msg void OnSupport2Clicked();
	afx_msg void OnSupport3Clicked();
	afx_msg void OnBnClickedOk();
	afx_msg void OnClose();
public:
	//bool isAvailableSupport();
	int GetAnswer();
	void static releaseSupport(int idx)
	{
		switch(idx)
		{
			case 0:
				support1_selected = false;
				break;
			case 1:
				support2_selected = false;
				break;
			case 2:
				support3_selected = false;
				break;
		}
	}
};
