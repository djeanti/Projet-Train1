
// ChildView.h : interface de la classe CChildView
//


#pragma once

#define BUFSIZE    12  // Size of receive buffer (in bytes) (10-byte unique ID + null character)

#define RFID_START  0x0A  // RFID Reader Start and Stop bytes
#define RFID_STOP   0x0D

class CChildView : public CView
{

protected: // création à partir de la sérialisation uniquement
	CChildView();
	~CChildView();
	DECLARE_DYNCREATE(CChildView)

// Attributs
public:
	CRFIDDoc* GetDocument() const;
	HANDLE hFile; 
	int Data_thread1;

// Opérations
public:
	
// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	bool initCommunication(LPCWSTR nomPort=_T("\\\\.\\COM3"), DWORD baudRate=CBR_2400, BYTE byParity = NOPARITY, BYTE byStopBits = ONESTOPBIT, BYTE byByteSize  = 8);
	bool read_rfid();
	bool write_rfid();
	void storeBuff(BYTE szBuff[BUFSIZE]);
	bool getError(CString info);

// Implémentation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version de débogage dans ChildView.cpp
inline CRFIDDoc* CChildView::GetDocument() const
   { return reinterpret_cast<CRFIDDoc*>(m_pDocument); }
#endif

