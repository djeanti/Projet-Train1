#ifndef __CARDS_RFID__H__
#define __CARDS_RFID__H__

#include "RFID.h"

inline void debugFile(RFID card);
inline void deleteFile(int idx);
inline void printErrorFile(LPCTSTR fname, LPCTSTR info);

class CCards{//classe metier

public://attributs
	RFID* rfid_cards;//tableau de cartes RFID
	size_t static NB_CONNECTED_CARDS;
	
	static HANDLE th_com;//thread pour ecouter les ports
	static HANDLE th_reads[SZ_CARDS];//tableau de maximum 8 threads, chacun servant a lire ce que la carte numéro idx lit comme TAG ou rien du tout si elle ne lit rien
	
	static CButtonHandler* b_h;
	static CMessageHandler* c_h;

public://methods

	CCards(): rfid_cards(0)//constructor
	{
		rfid_cards = new RFID[SZ_CARDS];
		initRFID();//on donne une valeur initial a tous les attributs de chaque carte pour éviter un quelconque probleme plus tard
	}

	//initialisation des handler (pour actualiser les variables de PIKODlg) avant utilisation :

	void setHandlerB(CButtonHandler* h)//appelee dans InitInstance pour que qd on appel updateButton on appelle la methode surchargée de PIKODlg
	{
		b_h = h;//on en touche plus apres cela
	}

	void setHandlerM(CMessageHandler* h)
	{
		c_h = h;//on en touche plus apres cela
	}

	//initialisation des cartes :
	void initRFID()
	{
		for(size_t i=0;i<SZ_CARDS;i++)
		{
			rfid_cards[i].idx=i;//normalement idx vaut maximum SZ_CARDS-1
			rfid_cards[i].COM = CString("NoEntry");
			rfid_cards[i].isConnected = false;
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
			if(!cards[i].isConnected)//trouvé
			{
				return i;
			}
		}
		return -1;//aucune carte trouvee de libre
	}

	//Multithreading :
	static DWORD WINAPI ThRead(void* arg) {//multithreading pour modifier les tags lu dans la carte RFID
		RFID* card = ((RFID*)arg);//<=> cards[j]
		//strcuture qui encapsule RFID* et le handler (CButtonHandler)
		try
		{
			read_rfid(card);
		}
		catch(std::exception e)
		{
			CString str; str.Format(_T("COM%d"),card->idx);
			CString fname = CString("error_thread2") + str + CString(".txt");
			printErrorFile(fname,str);
		}
		
		return 0;
	}

	static DWORD WINAPI ThCOM(void* arg) {//multithreading pour evaluer l'etat des cartes en continue
		RFID* cards = (RFID*)arg; 
		int idx=-2;
		TCHAR  lpTargetPath[5000]; // buffer to store the path port COM when doing a test
		
		//on est censé appelé la methode de b_h que quand doModal est appelé
		::Sleep(50);//le temps que doModal soit appelé dans le thread principal on met en pause ce thread
		
		c_h->updateMsg(_T("Recherche de cartes RFID ..."));

		int i=0; bool stop=false;
		while(1)//on lit tous les 20 ports COM en continue et on connecte/déconnecte les cartes en fonction de ça
		{
		
			if(i>255)
			{
				i=0;
				//celui qui appelle updateButton ci-dessous c'est b_h = CButtonHandler
			}

			CString str; str.Format(_T("%d"),i); CString COM = CString("COM") + CString(str);
			idx = searchComCards(cards,COM);

			if(idx!=-1)//Une des cartes est associée à COM
			{

				DWORD test = QueryDosDevice(COM, lpTargetPath, 5000);
				if(test==0)//Aucun device n'est physiquement connecté à COM
				{//on a probablement debranché la carte
					try
					{
						b_h->updateButton(idx, FALSE);//on desactive le bouton
					
						//On ferme d'abord le thread chargé de lire en continu les tags de cette carte
						::CloseHandle(th_reads[idx]);

						//on ferme le handle 
						::CloseHandle(cards[idx].h);
						cards[idx].COM = CString("NoEntry");
						cards[idx].isConnected = false;
						NB_CONNECTED_CARDS--;//censé être toujours positif*/
					}
					catch(std::exception e)
					{
						CString str; str.Format(_T("COM%d"),idx);
						printErrorFile(_T("error_thread1.txt"),str);
					}
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

							try
							{
								cards[j].COM = COM;
								cards[j].isConnected = true;
								//on créé un thread pour lire en continue les tags lu par la carte numéro j 
								th_reads[j] = ::CreateThread(0,0,ThRead,cards+j,0,0);
								NB_CONNECTED_CARDS++;

								
							}
							catch(std::exception e)
							{
								CString str; str.Format(_T("COM%d"),j);
								printErrorFile(_T("error_thread1.txt"),str);
							}

						}//enf if initCom
		
					}//end if test
				}//end if j

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

	~CCards()//destructor
	{
		NB_CONNECTED_CARDS = 0;
		delete b_h;
		delete[] rfid_cards; rfid_cards=0;
		if(th_com!=NULL) ::CloseHandle(th_com);	
		for(int i=0; i<SZ_CARDS; i++)
		{
			if(th_reads[i]!=NULL) ::CloseHandle(th_reads[i]);	
		}
	}

	//debugging for errors
	void getError(CString info)//purpose = debugging
	{
			DWORD lasterror = GetLastError();
			CString s; 
			s.Format(_T("Error in %s! %d\n"), info, lasterror);
			//MessageBox(m_hWnd,h,s,_T("Error"),MB_OK);
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
						buffTag.Format(_T("%c"),card.id_read[i]);
						tmp = (LPCTSTR)buffTag;
						pf.Write(tmp,sizeof(tmp)*lstrlen(tmp)/2);//format a respecter
				 }

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

inline void deleteFile(int idx)//supprime les fichiers créé par debugFile (ne fonctionne pas)
{
	char pf[10] = "Card0.txt";
	char tmp = idx+'0';
	pf[4] = tmp;
	const int res = remove(pf);
	if(res!=0)//failure
	{
		CString str; str.Format(_T("Card%c"),tmp);
		printErrorFile(str,str);
	}

}

inline void printErrorFile(LPCTSTR fname, LPCTSTR info)//print the output of an RFID struct inside a file for debugging purposes
{
		try
		{	
			CFile pf;
			if ( pf.Open( fname, CFile::modeCreate |   CFile::modeReadWrite ) )
			{
				pf.Write(info,sizeof(info)*lstrlen(info)/2);
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
#endif