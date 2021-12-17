
// RFIDDoc.h : interface de la classe CRFIDDoc
//


#pragma once


class CRFIDDoc : public CDocument
{
protected: // création à partir de la sérialisation uniquement
	CRFIDDoc();
	DECLARE_DYNCREATE(CRFIDDoc)

// Attributs
public:

// Opérations
public:

// Substitutions
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implémentation
public:
	virtual ~CRFIDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};


