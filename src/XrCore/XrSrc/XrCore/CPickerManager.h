#ifndef _CPICKERMANAGER_H
#define _CPICKERMANAGER_H
#include "../External/IPickerManager.h"
#include "../Common/XrInternal.h"


class IPicker;
class CPicker;
class CPickerManager : public IPickerManager
{
public:
	CPickerManager();
	~CPickerManager();

public:
	virtual Void CreatePicker(UInt32 type,IPicker** pPicker);
	virtual Void RemovePicker(IPicker* pPicker);
	xr_state OnTouchEvent(
		/* [in] */ Int32 x,
        /* [in] */ Int32 y,
		/* [in] */ UInt32 type);

protected:
	Boolean Calculate(Int32 x,Int32 y,UInt32 type);

protected:
	CArray<CPicker*>	m_Pickers;
	//Ray					m_CurScreenPtToWorldRay;
};
#endif
