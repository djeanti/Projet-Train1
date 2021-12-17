
// RFIDDoc.cpp : implémentation de la classe CRFIDDoc
//

#include "stdafx.h"
#include "RFID.h"

#include "RFIDDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRFIDDoc

IMPLEMENT_DYNCREATE(CRFIDDoc, CDocument)

BEGIN_MESSAGE_MAP(CRFIDDoc, CDocument)
END_MESSAGE_MAP()


// construction ou destruction de CRFIDDoc

CRFIDDoc::CRFIDDoc()
{
	// TODO : ajoutez ici le code d'une construction unique

}

CRFIDDoc::~CRFIDDoc()
{
}

BOOL CRFIDDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO : ajoutez ici le code de réinitialisation
	// (les documents SDI réutiliseront ce document)

	return TRUE;
}




// sérialisation de CRFIDDoc

void CRFIDDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO : ajoutez ici le code de stockage
	}
	else
	{
		// TODO : ajoutez ici le code de chargement
	}
}


// diagnostics pour CRFIDDoc

#ifdef _DEBUG
void CRFIDDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CRFIDDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// commandes pour CRFIDDoc
