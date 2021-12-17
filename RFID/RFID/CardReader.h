
#pragma once

#define BUFSIZE    12  // Size of receive buffer (in bytes) (10-byte unique ID + null character)

#define RFID_START  0x0A  // RFID Reader Start and Stop bytes
#define RFID_STOP   0x0D

class CardReader : public CWnd
{

public: // création à partir de la sérialisation uniquement
	CardReader();
	~CardReader();

// Attributs
public:
	HANDLE hFile; 
	int Data_thread1;

//Methodes
public:
	bool initCommunication(LPCWSTR nomPort=_T("\\\\.\\COM3"), DWORD baudRate=CBR_2400, BYTE byParity = NOPARITY, BYTE byStopBits = ONESTOPBIT, BYTE byByteSize  = 8);
	bool read_rfid();
	bool write_rfid();
	void storeBuff(BYTE szBuff[BUFSIZE]);
	bool getError(CString info);
};

