#ifndef __RFID__H__
#define __RFID__H__

#include<iostream>
#include<stdio.h>

#include "CButtonHandler.h"
#include "CMessageHandler.h"

#define BUFSIZE    12  // Size of receive buffer (in bytes) (10-byte unique ID + null character)

#define RFID_START  0x0A  // RFID Reader Start and Stop bytes
#define RFID_STOP   0x0D

#define SZ_CARDS 8//Number of cards (maximum) used in this project
#define SZ_SUPPORTS_CARDS 3

struct RFID{//modelise une carte RFID
	HANDLE h;
	CString id_read;//id qu'on lit (a cause de l'encryption)
	CString COM;//le nom du port COM ou elle est connecte (chaine vide sinon)
	int support;//a quel  support (1, 2 ou 3) la carte est elle posée sur le circuit réel
	bool isConnected;
	int num;//numero du bouton sur l'interface GUI de CPIKDlg auquel le tag lu est associé (on le définit dans le thread rfid_read associé à chaque carte
};typedef struct RFID RFID;
//si la carte est deco elle contient CString("NoEntry") comme port, id_read et id_true sont vide et isConnected=false
//idx : on aura toujours le meme ordre : 0,1,2,3,4,5,6,7, si tag 4 est deconeecte l'idx ne changera pas, des qu'il sera reconnecté meme a un autre port com on l'affichera toujours sur le bouton tag4 associé

struct IMAGE{
public:
	CImage img;
	CBitmap b;
	void Load(LPCTSTR _name) {img.Load(_name);} 

}; typedef struct IMAGE IMAGE;



const CString BUTTONS_ID[SZ_CARDS] = {CString("0419EC51B8"), //id du TAG associé au bouton 1 de la fenetre GUI CPIKODlg
											CString(""), 
											CString(""),
											CString(""), 
											CString(""),
											CString(""), 
											CString(""),
											CString("")};

inline int from_id_get_button(CString id)
{
	/*fonction qui à partir de l'id fournit le numéro du bouton correspondant en cherchant dans le tableau BUTTONS_TAGS*/
	int res = -1;
	for(int i=0;i<SZ_CARDS;i++)
	{
		if(BUTTONS_ID[i]==id)	return i;
	}
	return res;//-11 : impossible a renvoyer normalement
}

#endif
