
#pragma once

#define BUFSIZE    12  // Size of receive buffer (in bytes) (10-byte unique ID + null character)

#define RFID_START  0x0A  // RFID Reader Start and Stop bytes
#define RFID_STOP   0x0D

class CardReader : public CWnd//encapsule 1 seule carte
{

public: // création à partir de la sérialisation uniquement
	CardReader();
	~CardReader();

// Attributs
public:
	HANDLE hFile; 
	int Data_thread1;
	CString COMport;

//Methodes
public:
	bool initCommunication(LPCWSTR nomPort=_T("\\\\.\\COM3"), DWORD baudRate=CBR_2400, BYTE byParity = NOPARITY, BYTE byStopBits = ONESTOPBIT, BYTE byByteSize  = 8);
	bool read_rfid();
	bool write_rfid();
	void storeBuff(BYTE szBuff[BUFSIZE]);
	bool getError(CString info);
	void Msg(CString info);//afficher un message quelquonque
	void closeCommunication();//close handle
	CString getPort() const{return COMport;}
};

class RFID
{
public:
	RFID();
	~RFID();

public://attributs
	//pour gerer plusieurs cartes :
	const size_t SZ_PORTS_TAB;//nb max d'elements de PORTS_TAB
	size_t NB_ELEMS_PORTS_TAB;//nb elements actuel de NB_ELEMS_PORTS_TAB
	CString* PORTS_TAB;

	CardReader* cards;
	size_t SZ_CARDS;//Number of cards (maximum) used in this project

public://methods
	bool searchAvailablePorts();
	bool isAvailable(CString nomPort);//verifie si la carte associee au port nomPort est disponible ou non
	void closeAllCards();//close handle for all cards
};