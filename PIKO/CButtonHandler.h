#ifndef __CBUTTON_HANDLER_H__
#define __CBUTTON_HANDLER_H__

class CButtonHandler
{
public:
	virtual void updateTagButton(int idx, BOOL val) = 0;
	virtual void updateSupportButton(int idx, BOOL val) = 0;
	virtual int newButtonPopup(CString COM, int num_card) = 0 ;
	//un message popup demande lorsqu'une nouvelle carte rfid est connectee 
	//a quel support elle est associee, on renvoit l'index du support choisi
	virtual void releaseSupportButton(int idx) = 0;//pour libérer une carte
};

#endif