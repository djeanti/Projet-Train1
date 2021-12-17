
// ChildView.cpp : implémentation de la classe CChildView
//

#include "stdafx.h"
#include "winbase.h"
#include "CardReader.h"

CardReader::CardReader()
{
	initCommunication(_T("\\\\.\\COM4"));
}

CardReader::~CardReader()
{
	CloseHandle(hFile);
}


//RFID methods

bool CardReader::getError(CString info)//purpose = debugging
{
		DWORD lasterror = GetLastError();
		CString s; 
		s.Format(_T("Error in %s! %d\n"), info, lasterror);
		MessageBox(s,_T("Error"),MB_OK);
		return false;
}

bool CardReader::initCommunication(LPCWSTR nomPort, DWORD baudRate, BYTE byParity, BYTE byStopBits, BYTE byByteSize)
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

void CardReader::storeBuff(BYTE szBuff[BUFSIZE])
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

bool CardReader::read_rfid()//a terminer
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

	return true;

}

bool CardReader::write_rfid()
{
	return true;
}

//END of RFID methods
