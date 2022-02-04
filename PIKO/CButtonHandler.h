#ifndef __CBUTTON_HANDLER_H__
#define __CBUTTON_HANDLER_H__

class CButtonHandler
{
public:
	virtual void updateButton(int idx, BOOL val, LPCTSTR text=_T("NoTag")) = 0;
};

#endif