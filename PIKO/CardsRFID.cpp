#include "stdafx.h"
#include "CardsRFID.h"

size_t CCards::NB_CONNECTED_CARDS=0;

//sans initialiser les HANDLE on a une erreur d'édition des liens
HANDLE CCards::th_com=0;
HANDLE CCards::th_reads[SZ_CARDS] = {0};
CButtonHandler* CCards::b_h = 0;

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
	timeout.ReadIntervalTimeout = 100;
	timeout.ReadTotalTimeoutConstant = 100;// read constant (milliseconds)
	timeout.ReadTotalTimeoutMultiplier = 100;
	timeout.WriteTotalTimeoutConstant = 100;
	timeout.WriteTotalTimeoutMultiplier = 100;

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
		card->id_read[i]=' ';
	}
	DWORD dwBytesRead = 0;

	/*
		Problème : La carte RFID ne détecte pas le tag même lorsque ce dernier est à côté.
		A cause du timeout ? oui
	*/
	CString tag(""), tmp;
	//debugFile(*card);
	do{
		if(card->h!=NULL)//on ne lit rien si le handle a été supprimé et on sors de la boucle infinie de force
		{

					if(ReadFile(card->h, szBuff, BUFSIZE, &dwBytesRead, NULL)!=FALSE)//on a bien lu
					{
						if(dwBytesRead==12 && szBuff[0]==RFID_START && szBuff[BUFSIZE-1]==RFID_STOP)//on a tout lu correctement
						{
							//on stocke le nouveau tag lu dans id_read de la carte RFID (on le fait une seule fois)
							if(tag == CString(""))
							{
								for(size_t i=0;i<BUFSIZE;i++)
								{
									tmp.Format(_T("%c"),(char)szBuff[i]);
									if(i!=0 && i!=BUFSIZE-1)	tag+= (CString)tmp;
									card->id_read[i]=(char)szBuff[i];
								}
							}
							b_h->updateButton(card->idx, TRUE, tag);					
						}
						else
						{
							tag = CString("");
							for(size_t i=1;i<BUFSIZE-1;i++)
							{
								card->id_read[i]=' ';
							}
							b_h->updateButton(card->idx, FALSE);
						}
				}//end ReadFile
				else//ReadFile a échoué
				{
					tag = CString("");
					CString str; str.Format(_T("FICHIER%d.txt"),card->idx);
					printErrorFile(str,_T("ee"));
				}

		}
	}while(1);//boucle infinie
}