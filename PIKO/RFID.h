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
	CString id_read;//id du tag qu'on lit
	CString COM;//le nom du port COM ou elle est connectee (chaine vide sinon)
	int support;//a quel  support (1, 2 ou 3) la carte est elle pos�e sur le circuit r�el
	bool isConnected;//pour savoir si le lecteur est connect�e ou non
	int num;//numero du bouton sur l'interface GUI de CPIKDlg auquel le tag lu est associ�
};typedef struct RFID RFID;

struct IMAGE{
public:
	CImage img;
	CBitmap b;
	void Load(LPCTSTR _name) {img.Load(_name);} 

}; typedef struct IMAGE IMAGE;



const CString BUTTONS_ID[SZ_CARDS] = {CString("0419EC51B8"), //arriere wagon principal
																			CString("0419AE51CA"),  //avant wagon principal
																			CString("0419AE560B"), //tag situ� sur le wagon 2 
																			CString("0419EC4450"),  //tag situ� a l'arriere du wagon 1
																			CString("0419EC4662"), //tag situ� a l'avant du wagon 1
																			CString("0419EC4200"),  //arriere wagon 3
																			CString("0419EC5A8D"), //avant wagon 3
																			CString("0419EC5ECB")};//tag situ� sur le wagon 4

inline int from_id_get_button(CString id)
{
	/*fonction qui � partir de l'id fournit le num�ro du bouton correspondant en cherchant dans le tableau BUTTONS_TAGS*/
	int res = -1;
	for(int i=0;i<SZ_CARDS;i++)
	{
		if(BUTTONS_ID[i]==id)	return i;
	}

	return res;//-11 : impossible a renvoyer normalement
}

#endif
