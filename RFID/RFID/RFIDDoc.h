
// RFIDDoc.h : interface de la classe CRFIDDoc
//


#pragma once


class CRFIDDoc : public CDocument
{
protected: // cr�ation � partir de la s�rialisation uniquement
	CRFIDDoc();
	DECLARE_DYNCREATE(CRFIDDoc)

// Attributs
public:

// Op�rations
public:

// Substitutions
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Impl�mentation
public:
	virtual ~CRFIDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions g�n�r�es de la table des messages
protected:
	DECLARE_MESSAGE_MAP()
};


