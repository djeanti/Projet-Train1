
// ChildView.cpp : implémentation de la classe CChildView
//

#include "stdafx.h"
#include "winbase.h"
#include "CardReader.h"

/******************************************CardReader class********************************************************/
CardReader::CardReader()
{
}

CardReader::~CardReader()
{
	closeCommunication();
}


//CardReader methods

void CardReader::Msg(CString info)//purpose = debugging
{
		CString s; 
		s.Format(_T("%s\n"), info);
		MessageBox(s,_T("Msg"),MB_OK);
}

bool CardReader::getError(CString info)//purpose = debugging
{
		DWORD lasterror = GetLastError();
		CString s; 
		s.Format(_T("Error in %s! %d\n"), info, lasterror);
		//MessageBox(s,_T("Error"),MB_OK);
		return false;
}

void CardReader::closeCommunication()
{
	if(hFile!=NULL)
	{
		CloseHandle(hFile);
	}
}

bool CardReader::initCommunication(LPCWSTR nomPort, DWORD baudRate, BYTE byParity, BYTE byStopBits, BYTE byByteSize)
{
	COMport = (CString) nomPort;
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
	//Initialisation du buffer a 0x00 :
	BYTE szBuff[BUFSIZE] = {0};
	for(int i=0;i<BUFSIZE;i++){
		szBuff[i] = 0x00;
	}
	DWORD dwBytesRead = 0;

	bool val=false;//condition de sortie de la boucle while
	do{

		if(ReadFile(hFile, szBuff, BUFSIZE, &dwBytesRead, NULL)!=FALSE)//on abien lu
		{
			if(dwBytesRead==12)
			{
				if(szBuff[0]==RFID_START && szBuff[BUFSIZE-1]==RFID_STOP)
				{
					storeBuff(szBuff);
					val = true;
				}
			}
		}

	}while(!val);

	return true;

}

bool CardReader::write_rfid()
{
	return true;
}

//END of CardReader methods


/********************************************************RFID class*********************************************************************/

RFID::RFID(): PORTS_TAB(0), SZ_PORTS_TAB(50), SZ_CARDS(8)//constructor
{
	PORTS_TAB = new CString[SZ_PORTS_TAB];
	cards = new CardReader[SZ_CARDS];
}

RFID::~RFID()//destructor
{
	delete[] PORTS_TAB;
}

//RFID methods

bool RFID::searchAvailablePorts()//regarde quels ports sont connecté et les stocke dans un tableau PORTS_TAB
{
    TCHAR  lpTargetPath[5000]; // buffer to store the path of the COMPORTS
    bool gotPort = false; // in case the port is not found
		
		NB_ELEMS_PORTS_TAB = 0;
		for(size_t i=0;i<SZ_PORTS_TAB;i++)
		{
			PORTS_TAB[i]=CString("");
		}

    for (int i = 0; i < 50; i++) // checking ports from COM0 to COM50
    {
        CString str;
        str.Format(_T("%d"),i);
        CString ComName=CString("COM") + CString(str); // converting to COM0, COM1, COM2

        DWORD test = QueryDosDevice(ComName, lpTargetPath, 5000);

        // Test the return value and error if any
        if (test != 0) //QueryDosDevice returns zero if it didn't find an object
        {
						PORTS_TAB[NB_ELEMS_PORTS_TAB] = ComName;
						NB_ELEMS_PORTS_TAB++;
            gotPort = true;
        }

    }

		return gotPort;//true => on a detecte au moins un port
}

bool RFID::isAvailable(CString nomPort){

}

void RFID::closeAllCards()
{
	for(size_t i=0;i<NB_ELEMS_PORTS_TAB && i<SZ_CARDS;i++)
	{
		cards[i].closeCommunication();
	}

	NB_ELEMS_PORTS_TAB=0;
	for(size_t i=0;i<SZ_PORTS_TAB;i++)
	{
		PORTS_TAB[i]=CString("");
	}
}
//end of RFID methods