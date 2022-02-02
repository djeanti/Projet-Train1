#include "stdafx.h"
#include "CardsRFID.h"

size_t CCards::NB_CONNECTED_CARDS=0;

//sans initialiser les HANDLE on a une erreur d'édition des liens
HANDLE CCards::th_com=0;
HANDLE CCards::th_reads[SZ_CARDS] = {0};

bool CCards::initCom(RFID* card, CString COM, DWORD baudRate, BYTE byParity, BYTE byStopBits, BYTE byByteSize)//carte numero i
{
	// Open serial port
	card->h = CreateFile(COM, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (card->h == INVALID_HANDLE_VALUE) 
	{ 
		return false;
	}

	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);

	if (!GetCommState(card->h, &serialParams))
	{
		return false;
	}

	serialParams.BaudRate = baudRate;
	serialParams.ByteSize = byByteSize;
	serialParams.StopBits = byStopBits;
	serialParams.Parity = byParity;


	if (!SetCommState(card->h, &serialParams))
	{
		return false;
	}

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 10;
	timeout.ReadTotalTimeoutConstant = 10;
	timeout.ReadTotalTimeoutMultiplier = 10;
	timeout.WriteTotalTimeoutConstant = 10;
	timeout.WriteTotalTimeoutMultiplier = 20;

	if (!SetCommTimeouts(card->h, &timeout))
	{
		return false;
	}

	//connection established correctly 

	return true;
}

void CCards::read_rfid(RFID* card)//idx = numero de la carte etudiee
{
	//fonction statique utilisée uniquement pour lire un tag RFID
	BYTE szBuff[BUFSIZE];//buffer temporaire
	for(int i=0;i<BUFSIZE;i++)
	{
		szBuff[i]=0x00;
	}
	DWORD dwBytesRead = 0;
	do{
		if(card->h!=NULL)//on ne lit rien si le handle a été supprimé et on sors de la boucle infinie de force
		{

					if(ReadFile(card->h, szBuff, BUFSIZE, &dwBytesRead, NULL)!=FALSE)//on a bien lu
					{
						if(dwBytesRead==12 && szBuff[0]==RFID_START && szBuff[BUFSIZE-1]==RFID_STOP)//on a tout lu correctement
						{
							//on stocke le nouveau tag lu dans id_read de la carte RFID
							for(size_t i=0;i<BUFSIZE;i++)
							{
								card->id_read[i]=szBuff[i];
							}
							card->NoTag=false;//le buffer id_read n'est plus "vide"
						}
						else//on a pas lu de tag correctement
						{
							card->NoTag=true;//on ne réinitialise pas le buffer mais ce n'est pas grave car c'est cette attribut qu'on analysera dans PIKODlg pour modifier l'état des boutons
						}

				}//end ReadFile
		}
	}while(1);//boucle infinie

}