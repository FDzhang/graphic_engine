#ifndef _IPICKERMANAGER_H
#define _IPICKERMANAGER_H
#include "xrIntrinsic.h"
class IPicker;

class IPickerManager
{
public:
	virtual Void CreatePicker(UInt32 type,IPicker** pPicker) = 0;
	virtual Void RemovePicker(IPicker* pPicker) = 0;
};

#endif