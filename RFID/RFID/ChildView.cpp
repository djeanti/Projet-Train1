
// ChildView.cpp : implémentation de la classe CChildView
//

#include "stdafx.h"
#include "RFID.h"

#include "RFIDDoc.h"
#include "ChildView.h"
#include "winbase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

IMPLEMENT_DYNCREATE(CChildView, CView)

BEGIN_MESSAGE_MAP(CChildView, CView)
END_MESSAGE_MAP()

// construction ou destruction de CChildView

//CChildView

CChildView::CChildView()
{
	m_card.read_rfid();
}

CChildView::~CChildView()
{

}

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO : changez ici la classe ou les styles Window en modifiant
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// dessin de CChildView

void CChildView::OnDraw(CDC* /*pDC*/)
{
	CRFIDDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO : ajoutez ici le code de dessin pour les données natives
	
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// diagnostics pour CChildView

#ifdef _DEBUG
void CChildView::AssertValid() const
{
	CView::AssertValid();
}

void CChildView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRFIDDoc* CChildView::GetDocument() const // la version non Debug est inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRFIDDoc)));
	return (CRFIDDoc*)m_pDocument;
}
#endif //_DEBUG


// gestionnaires de messages pour CChildView

