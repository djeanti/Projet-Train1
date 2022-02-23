#include "stdafx.h"
#include "CardsRFID.h"

size_t CCards::NB_CONNECTED_CARDS=0;

//sans initialiser les HANDLE on a une erreur d'édition des liens
HANDLE CCards::th_com=0;
HANDLE CCards::th_reads[SZ_CARDS] = {0};
CButtonHandler* CCards::b_h = 0;
CMessageHandler* CCards::c_h = 0;

bool CCards::initCom(RFID* card, CString COM, DWORD baudRate, BYTE byParity, BYTE byStopBits, BYTE byByteSize)//carte numero i
{
	// Open serial port
	card->h = CreateFile(COM, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (card->h == INVALID_HANDLE_VALUE) 
	{ 
		getError(_T("initComErreur.txt"),_T("CreateFile"));
		return false;
	}

	// Do some basic settings
	DCB serialParams = { 0 };
	serialParams.DCBlength = sizeof(serialParams);

	if (!GetCommState(card->h, &serialParams))
	{
		getError(_T("initComErreur.txt"),_T("GetCommState"));
		return false;
	}

	serialParams.BaudRate = baudRate;
	serialParams.ByteSize = byByteSize;
	serialParams.StopBits = byStopBits;
	serialParams.Parity = byParity;


	if (!SetCommState(card->h, &serialParams))
	{
		getError(_T("initComErreur.txt"),_T("SetCommState"));
		return false;
	}

	// Set timeouts
	COMMTIMEOUTS timeout = { 0 };
	timeout.ReadIntervalTimeout = 50;
	timeout.ReadTotalTimeoutConstant = 50;// read constant (milliseconds)
	timeout.ReadTotalTimeoutMultiplier = 50;
	timeout.WriteTotalTimeoutConstant = 100;
	timeout.WriteTotalTimeoutMultiplier = 100;

	if (!SetCommTimeouts(card->h, &timeout))
	{
		getError(_T("initComErreur.txt"),_T("SetCommTimeouts"));
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

	/*
		Problème : La carte RFID ne détecte pas le tag même lorsque ce dernier est à côté.
		A cause du timeout ? oui
	*/
	CString tmp, tag("");
	bool error = false;
	do{
		if(card->h!=NULL)
		{

					if(ReadFile(card->h, szBuff, BUFSIZE, &dwBytesRead, NULL)!=FALSE)//on a bien lu
					{
						if(dwBytesRead==12 && szBuff[0]==RFID_START && szBuff[BUFSIZE-1]==RFID_STOP)//on a tout lu correctement
						{
							tag = CString("");
							//on stocke le nouveau tag lu dans id_read de la carte RFID (on le fait une seule fois)
							for(size_t i=0;i<BUFSIZE;i++)
							{
								tmp.Format(_T("%c"),(char)szBuff[i]);
								if(i!=0 && i!=BUFSIZE-1)	tag+= (CString)tmp;
							}
							//on a fini de récupérer le tag, maintenant on souhaite savoir quel bouton grisé
							//chaque bouton est associé à un tag, on appelle la méthode statique associée à ce travail
						
							//getError(_T("ReadFile_failure.txt"), tag);
							int num = from_id_get_button(tag);
							
							
							card->id_read=tag;
							card->num = num;

							b_h->updateTagButton(num, TRUE);	//le bouton associé au tag BUTTONS_ID[num] devient rouge
							b_h->updateSupportButton(card->support, TRUE);
							

						}
						else
						{

							b_h->updateTagButton(card->num, FALSE);
							b_h->updateSupportButton(card->support, FALSE);
						}

				}//end ReadFile
				else//ReadFile a échoué
				{
					getError(_T("ReadFile_failure.txt"), card->COM);
				}

		}
		else
		{
			return;
		}
		
	}while(1);//boucle infinie

}