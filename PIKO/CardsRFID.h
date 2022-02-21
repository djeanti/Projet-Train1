#ifndef __CARDS_RFID__H__
#define __CARDS_RFID__H__

#include "RFID.h"

inline void printErrorFile(LPCTSTR fname, LPCTSTR info);
inline void getError(CString fname, CString info=CString(""));

class CCards{//classe Document

protected://attributs
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

	void initCommunications()//pour toutes les cartes
	{
		//on lance un thread qui ecoute sur les 20 premiers ports COM de l'ordinateur
		th_com = ::CreateThread(0,0,ThCOM,rfid_cards,0,0);
	}

	~CCards()//destructor
	{
		NB_CONNECTED_CARDS = 0;
		delete b_h; b_h= 0; delete c_h; c_h =0;

		//structure RFID :
		delete[] rfid_cards; rfid_cards=0;

		//on ferme tous les threads pas encore fermé :
		if(th_com!=NULL) ::CloseHandle(th_com);

		for(int i=0; i<SZ_CARDS; i++)
		{
			if(th_reads[i]!=NULL) ::CloseHandle(th_reads[i]);	
		}
	}

private : 
	//initialisation des cartes :
	void initRFID()
	{
		for(size_t i=0;i<SZ_CARDS;i++)
		{
			rfid_cards[i].num = rfid_cards[i].support = -1;//normalement idx vaut maximum SZ_CARDS-1
			rfid_cards[i].COM = rfid_cards[i].id_read = CString("");
			rfid_cards[i].isConnected = false;
		}
	}

	//demarrage de la communication :
	bool static initCom(RFID* card, CString COM, DWORD baudRate=CBR_2400, BYTE byParity = NOPARITY, BYTE byStopBits = ONESTOPBIT, BYTE byByteSize  = 8);//pour 1 seule carte

	bool static read_rfid(RFID* card);//pour lire le tag d'une carte RFID (tag qu'on affiche a l'ecran)

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
		//structure qui encapsule RFID* et le handler (CButtonHandler)
		bool result = false;
		try
		{
			result = read_rfid(card);
		}
		catch(std::exception e)
		{
				getError(_T("error_thread2.txt"));
		}

		//on désactive les boutons de la GUI :
		b_h->updateTagButton(card->num, FALSE);
		b_h->updateSupportButton(card->support, FALSE);//le bon support boutton (associé a cette carte) devient rouge 

		if(result)//erreur de la part de from_id_get_button (on est pas censé avoir cette erreur si on travaille avec les tags dont les identifiants sont tous notés dans BUTTONS_ID)
		{
				getError(_T("error_thread2.txt"));
		}

		return 0;
	}

	static DWORD WINAPI ThCOM(void* arg) {//multithreading pour evaluer l'etat des cartes en continue
		RFID* cards = (RFID*)arg; 
		int idx=-2;
		TCHAR  lpTargetPath[5000]; // buffer to store the path port COM when doing a test
		
		//on est censé appelé la methode de b_h que quand doModal est appelé
		::Sleep(5000);//le temps que doModal soit appelé dans le thread principal on met en pause ce thread

		int i=0;
		int nb=0, nb2=0;
		//b_h->newButtonPopup();

		while(1)//on lit tous les 20 ports COM en continue et on connecte/déconnecte les cartes en fonction de ça
		{
		
			if(i>50)
			{
				i=0;
				nb++;
			}
		
			CString str; str.Format(_T("%d"),i); CString COM = CString("COM") + CString(str);//nom du port COM (COM0, COM1, COM2 ...)
			idx = searchComCards(cards,COM);//on cherche si dans la structure, une des cartes est associée à ce port COM
			
			DWORD test = QueryDosDevice(COM, lpTargetPath, 5000);

			if(idx!=-1)//Une des cartes est associée au port COMi
			{

				if(test==0)//Aucun device n'est physiquement connecté à COM
				{//on a probablement debranché la carte
					try
					{
						//On ferme d'abord le thread chargé de lire en continu les tags de cette carte
						::CloseHandle(th_reads[idx]);

						//on ferme le handle 
						::CloseHandle(cards[idx].h);

						//on réinitialise la carte dans la structure :
						cards[idx].COM = cards[idx].id_read = CString("");
						cards[idx].support = cards[idx].num = -1;
						cards[idx].isConnected = false;

						//le nombre de carte connecté change en conséquence :
						NB_CONNECTED_CARDS--;//censé être toujours positif*/
					}
					catch(std::exception e)
					{
						getError(_T("error_thread1.txt"));
					}
				}

			}//fin du if
			else if(idx==-1 && NB_CONNECTED_CARDS<SZ_CARDS)//le port COM n'existe pas dans le tableau ET il reste des handle libre dans cards
			{

				if(test!=0)//1 device est connecte au port COM
				{
					//On modifie le tableau de structure RFID cards pour ajouter une carte connectee

					size_t j = getFreeIdx(cards);//on recupere un lecteur dans le tableau possédant un handle libre
					if( j!=-1 )//il faut qu'au moins 1 carte soit disponible (cette condition doit être toujours vraie si on arrive jusqu'ici ! Car on test avant NB_CONNECTED_CARDS<SZ_CARDS)
					{
						if( initCom(cards+j,COM) )//le device connecte au port COMi est finalement une carte RFID (et non pas une cle usb par exemple) car la connection s'est bien etablie
						{

							try
							{
								//on veut savoir sur le circuit réel sur quel support la carte est située : on demande à l'utilisateur vaec newButtonPopup
								int support_idx  = b_h->newButtonPopup();//on ne peut le faire que trois fois (car on ne peut mettre que 3 supports maximum dans le circuit réel, si on en met plus, il y aura interférences entre les lecteurs RFID)
								if( 1<= support_idx && support_idx<=3)
								{//on a trouvé un support : on modifie donc card[j] pour pouvoir l'utiliser
									cards[j].support = support_idx;
									cards[j].COM = COM;
									cards[j].isConnected = true;
									NB_CONNECTED_CARDS++;

									//on créé un thread pour lire en continue les tags lu par la carte numéro j 
									th_reads[j] = ::CreateThread(0,0,ThRead,cards+j,0,0);
								
								}
								else//on ferme la connection -> on ne peut pas travailler avec cette carte si aucun support sur la fenetre GUI ne lui est associé
								{//plus assez de suppport peuvent acceuillir de cartes sur le circuit réel
									::CloseHandle(cards[j].h);
									CString str; str.Format(_T("Une carte a tente de se connecte au port COM%d mais il n'y a plus assez de support pour la connecter"),j);
									getError(_T("NoMoreSupportAvailable.txt"),str);
								}

							}
							catch(std::exception e)
							{
								getError(_T("error_thread1.txt"));
							}

						}//enf if initCom
		
					}//end if test
				}//end if j

			}//fin du else if

			i++;
		}//fin du while

		return 0;
	}

	//debugging for errors

};

inline void getError(CString fname, CString info)//purpose = debugging
{
		DWORD lasterror = GetLastError();
		CString s; 
		if(info!=CString(""))	s.Format(_T("Error with : %s! %d\n"), info, lasterror);
		else s = CString("Erreur : %d",lasterror);
		//MessageBox(m_hWnd,h,s,_T("Error"),MB_OK);
		printErrorFile(fname,s);
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