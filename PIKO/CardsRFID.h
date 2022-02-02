#ifndef __CARDS_RFID__H__
#define __CARDS_RFID__H__

#include "RFID.h"

inline void debugFile(RFID card);
inline void deleteFile(int idx);

class CCards{

public://attributs
	RFID* rfid_cards;//tableau de cartes RFID
	size_t static NB_CONNECTED_CARDS;
	
	static HANDLE th_com;//thread pour ecouter les ports
	static HANDLE th_reads[SZ_CARDS];//tableau de maximum 8 threads, chacun servant a lire ce que la carte numéro idx lit comme TAG ou rien du tout si elle ne lit rien

public://methods

	CCards(): rfid_cards(0)//constructor
	{
		//init_HANDLE();
		rfid_cards = new RFID[SZ_CARDS];
		initRFID();//on donne une valeur initial a tous les attributs de chaque carte pour éviter un quelconque probleme plus tard
	}

	//initialisation des cartes avant utilisation :
	void initBuffs(int i)//idx = numero de la carte rfid etudie
	{
		for(size_t j=0;j<BUFSIZE;j++)
		{
			rfid_cards[i].id_read[j] = rfid_cards[i].id_true[j] = 0x00;
		}
	}

	void initRFID()
	{
		for(size_t i=0;i<SZ_CARDS;i++)
		{
			rfid_cards[i].idx=i;//normalement idx vaut maximum SZ_CARDS-1
			rfid_cards[i].COM = CString("NoEntry");
			rfid_cards[i].isConnected = false;
			rfid_cards[i].NoTag = true;
			initBuffs(i);
		}
	}

	//demarrage de la communication :
	bool static initCom(RFID* card, CString COM, DWORD baudRate=CBR_2400, BYTE byParity = NOPARITY, BYTE byStopBits = ONESTOPBIT, BYTE byByteSize  = 8);//pour 1 seule carte

	void static read_rfid(RFID* card);//pour lire le tag d'une carte RFID (tag qu'on affiche a l'ecran)

	int static searchComCards(RFID* cards, CString COM)//parcours a la recherche du port com en argument, on renvoit -1 si on ne trouve rien
	{
		for(size_t i=0;i<SZ_CARDS;i++)
		{
			if(cards[i].COM==COM)//trouvé
			{
				return i;
			}
		}
		return -1;
	}

	static int getFreeIdx(RFID* cards)//parcours le tableau et renvoit le premier index associe a une carte non connectee
	{
		for(size_t i=0;i<SZ_CARDS;i++)
		{
			if(cards[i].isConnected==false)//trouvé
			{
				return i;
			}
		}
		return -1;//aucune carte trouvee de libre
	}

	//Multithreading :
	static DWORD WINAPI ThRead(void* arg) {//multithreading pour modifier les tags lu dans la carte RFID
		RFID* card = ((RFID*)arg);//<=> cards[j]
		read_rfid(card);
		return 0;
	}

	static DWORD WINAPI ThCOM(void* arg) {//multithreading pour evaluer l'etat des cartes en continue
		RFID* cards = (RFID*)arg; int idx=-1;
		TCHAR  lpTargetPath[5000]; // buffer to store the path port COM when doing a test

		char pf[10] = "Card5.txt";//pour créé le fichier de chaque carte
		int i=0;
		while(1)//on lit tous les 20 ports COM en continue et on connecte/déconnecte les cartes en fonction de ça
		{

			if(i>20)
			{
				i=0;
			}

			CString str; str.Format(_T("%d"),i); CString COM = CString("COM") + CString(str);
			idx = searchComCards(cards,COM);

			if(idx!=-1)//Une des cartes est associée à COM
			{

				DWORD test = QueryDosDevice(COM, lpTargetPath, 5000);
				if(test==0)//Aucun device n'est physiquement connecté à COM
				{
					deleteFile(idx);

					//on a probablement debranché la carte
					
					//On ferme d'abord le thread chargé de lire en continu les tags de cette carte
					::CloseHandle(th_reads[idx]);

					//on ferme le handle 
					::CloseHandle(cards[idx].h);
					cards[idx].COM = CString("NoEntry");
					cards[idx].isConnected = false;
					cards[idx].NoTag = false;//Pour éviter de reinitialiser le buffer pour id_read a chaque fois
					NB_CONNECTED_CARDS--;//censé être toujours positif
				}

			}//fin du if
			else if(idx==-1 && NB_CONNECTED_CARDS<SZ_CARDS)//le port COM n'existe pas dans le tableau ET il reste des handle libre dans cards
			{

				DWORD test = QueryDosDevice(COM, lpTargetPath, 5000);
				if(test!=0)//1 device est connecte au port COM
				{
					//On ajoute au tableau des cartes
					size_t j = getFreeIdx(cards);//on recupere un indice du tableau avec un handle libre
					if( j!=-1 )//il faut qu'au moins 1 carte soit disponible (cette condition doit être toujours vraie si on arrive jusqu'ici !
					{
						if( initCom(cards+j,COM) )//une nouvelle carte RFID a ete connectee correctement
						{
							cards[j].COM = COM;
							cards[j].isConnected = true;
							cards[j].NoTag = true;
							//on créé un thread pour lire en continue les tags lu par la carte numéro j et on actualise ainsi les tags id_read de la structure cards (utile après pour PIKODlg)
							th_reads[j] = ::CreateThread(0,0,ThRead,cards+j,0,0);
							NB_CONNECTED_CARDS++;

							debugFile(cards[j]);//on créé le fichier associée pour debug
						}
						else
						{
							//afficher un message d'erreur (on est pas censé ne pas réussir à connecter la carte si elle est bien connectée à COM)
						}

					}
				}

			}//fin du else if

			i++;
		}//fin du while

		return 0;
	}

	void initCommunications()//pour toutes les cartes
	{
		//on lance un thread qui ecoute sur les 20 premiers ports COM de l'ordinateur
		th_com = ::CreateThread(0,0,ThCOM,rfid_cards,0,0);
	}

	//Fermeture de l'application :
	void closeCommunications()//Fermeture de tous les HANDLE
	{
		for(size_t i=0;i<SZ_CARDS;i++)
		{
			if(rfid_cards[i].h!=NULL)
			{
				CloseHandle(rfid_cards[i].h);
			}
		}
	}

	~CCards()//destructor
	{
		NB_CONNECTED_CARDS = 0;

		closeCommunications();
		delete[] rfid_cards;

		if(th_com!=NULL) ::CloseHandle(th_com);		
	}

	//debugging for errors
	void getError(CString info)//purpose = debugging
	{
			DWORD lasterror = GetLastError();
			CString s; 
			s.Format(_T("Error in %s! %d\n"), info, lasterror);
			//MessageBox(m_hWnd,h,s,_T("Error"),MB_OK);
	}

	RFID* getRFID()
	{
		return rfid_cards;
	}
};

/*
	On créé un fichier CardN.txt pour chaque carte appelée par cette fonction ou n = idx de la structure RFID.
	On détruit ce fichier dans ThCom qd une carte est deconnectee
*/
inline void debugFile(RFID card)//print the output of an RFID struct inside a file for debugging purposes
{
		try
		{
			 // try to open the file
			CFile pf; 
			int idx = card.idx; 
			CString nomFile; nomFile.Format(_T("Card%d.txt"),idx);
			if ( pf.Open( nomFile, CFile::modeCreate |   CFile::modeReadWrite ) )
			{
				 CString str; str.Format(_T("~ CARD%d ~\nFichier décrivant la carte numéro %d (attribut RFID* de CCards)\n\n"),idx, idx);
				 LPCTSTR tmp = (LPCTSTR)str;
				 pf.Write(tmp,sizeof(tmp)*lstrlen(tmp)/2);//format a respecter
				 
				 tmp = _T("TAG id_read :\n");
				 pf.Write(tmp,sizeof(tmp)*lstrlen(tmp)/2);//format a respecter
				 
				 //id_read :
				 for(int i=0;i<BUFSIZE;i++)//12 fois
				 {
						CString buffTag;
						buffTag.Format(_T("%x"),card.id_read[i]);
						tmp = (LPCTSTR)buffTag;
						pf.Write(tmp,sizeof(tmp)*lstrlen(tmp)/2);//format a respecter
				 }

				 //NoTag
				 if(card.NoTag)
				 {
						tmp = _T("\n\nNoTag = true");
				 }
				 else
				 {
						tmp = _T("\n\nNoTag = false");
				 }
				 pf.Write(tmp,sizeof(tmp)*lstrlen(tmp)/2);//format a respecter

				 //isConnected
				 if(card.isConnected)
				 {
						tmp = _T("\n\nisConnected = true\n");
				 }
				 else
				 {
						tmp = _T("\n\nisConnected = false\n");
				 }
				 pf.Write(tmp,sizeof(tmp)*lstrlen(tmp)/2);//format a respecter

				 pf.Close();
			 }
		}
		catch (CFileException* pEx)
		{
			 // if an error occurs, just make a message box
			 pEx->ReportError();
			 pEx->Delete();
		}
}

#include<iostream>
#include<stdio.h>

inline void deleteFile(int idx)//supprime les fichiers créé par debugFile
{
	char pf[10] = "Card5.txt";
	pf[4] = idx+'0';
	try {
		remove(pf);
	}
	catch(std::exception e) 
	{
		 //do nothing
	}
}

#endif