
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
	if(initCommunication())
	{
		read_rfid();
	}
	else{
		getError(_T("can't initialize connection"));
	}
}

CChildView::~CChildView()
{
	CloseHandle(hFile);
}


//RFID methods

bool CChildView::getError(CString info)//purpose = debugging
{
		DWORD lasterror = GetLastError();
		CString s; 
		s.Format(_T("Error in %s! %d\n"), info, lasterror);
		MessageBox(s,_T("Error"),MB_OK);
		return false;
}

bool CChildView::initCommunication(LPCWSTR nomPort, DWORD baudRate, BYTE byParity, BYTE byStopBits, BYTE byByteSize)
{
	// Open serial port
	hFile = CreateFile(nomPort, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE) 
	{ 
		return getError(_T("createfile"));
	}

	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);

	if (!GetCommState(hFile, &serialParams))
	{
		return getError(_T("getcomstate"));
	}

	serialParams.BaudRate = baudRate;
	serialParams.ByteSize = byByteSize;
	serialParams.StopBits = byStopBits;
	serialParams.Parity = byParity;


	if (!SetCommState(hFile, &serialParams))
	{
		return getError(_T("setcommstate"));
	}

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 10;
	timeout.ReadTotalTimeoutConstant = 10;
	timeout.ReadTotalTimeoutMultiplier = 10;
	timeout.WriteTotalTimeoutConstant = 10;
	timeout.WriteTotalTimeoutMultiplier = 20;

	if (!SetCommTimeouts(hFile, &timeout))
	{
		return getError(_T("setcommtimeout"));
	}
	//connection established correctly 

	return true;
}

void CChildView::storeBuff(BYTE szBuff[BUFSIZE])
{
	FILE* pf = fopen("fichier.txt","w+");
	if(pf!=NULL){
		for(int i=0;i<BUFSIZE;i++){
			fprintf(pf,"%x",szBuff[i]);
		}
	}
	else{
		getError(_T("fichier cannot be opened"));
	}
	::fclose(pf);
}

bool CChildView::read_rfid()//a terminer
{
	BYTE szBuff[BUFSIZE] = {0};
	for(int i=0;i<BUFSIZE;i++){
		szBuff[i] = 0x00;
	}
	DWORD dwBytesRead = 0;

	int cpt=0;
	CString s(_T("")); 
	BOOL val=FALSE;
	do{
		val = ReadFile(hFile, szBuff, BUFSIZE, &dwBytesRead, NULL);
		if(val!=FALSE)
		{
			if(dwBytesRead==12)
			{
				if(szBuff[0]==RFID_START && szBuff[BUFSIZE-1]==RFID_STOP)
				{
					storeBuff(szBuff);
					cpt++;
				}
			}
		}
	}while(cpt<5);

	s.Format(_T("%s"),szBuff);
	MessageBox(s,_T("Tag RFID"),MB_OK);
	return true;

}

bool CChildView::write_rfid()
{
	return true;
}

//END of RFID methods





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
	CButton b;
	//b.Create(_T("Button"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(10,10,100,30),NULL,1);//ne marche pas
	
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

