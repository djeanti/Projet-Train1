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

struct RFID{//modelise une carte RFID
	HANDLE h;
	char id_read[BUFSIZE];//id qu'on lit (a cause de l'encryption)
	size_t idx;//identifie le numéro de la carte (en fonction de l'ordre de détection...) -> idx=1 signifie qu'on affichera la carte sur le bouton tag1 du GUI
	CString COM;//le nom du port COM ou elle est connecte (chaine vide sinon)
	bool isConnected;
};typedef struct RFID RFID;
//si la carte est deco elle contient CString("NoEntry") comme port, id_read et id_true sont vide et isConnected=false
//idx : on aura toujours le meme ordre : 0,1,2,3,4,5,6,7, si tag 4 est deconeecte l'idx ne changera pas, des qu'il sera reconnecté meme a un autre port com on l'affichera toujours sur le bouton tag4 associé


//structure utilisée dans la lecture des cartes (thread de lecture) :
struct RFID_button{//RFID associee a un bouton handler
	RFID* card;
	CButtonHandler* h;
};typedef struct RFID_button RFID_button;
#endif
