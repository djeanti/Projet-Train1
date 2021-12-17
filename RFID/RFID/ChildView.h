
// ChildView.h : interface de la classe CChildView
//


#pragma once

#include "CardReader.h"

class CChildView : public CView
{

protected: // cr�ation � partir de la s�rialisation uniquement
	CChildView();
	~CChildView();
	DECLARE_DYNCREATE(CChildView)

// Attributs
public:
	CRFIDDoc* GetDocument() const;
	CardReader m_card;

// Op�rations
public:
	
// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitu� pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

// Impl�mentation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions g�n�r�es de la table des messages
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version de d�bogage dans ChildView.cpp
inline CRFIDDoc* CChildView::GetDocument() const
   { return reinterpret_cast<CRFIDDoc*>(m_pDocument); }
#endif

