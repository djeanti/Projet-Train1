#ifndef __CMESSAGE_HANDLER_H__
#define __CMESSAGE_HANDLER_H__

class CMessageHandler
{
public:
	virtual void updateMsg(LPCTSTR text=_T("NoTag")) = 0;
};

#endif//end __CMESSAGE_HANDLER_H__