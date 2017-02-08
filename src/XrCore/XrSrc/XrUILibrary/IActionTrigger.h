#ifndef __IBUTTONACTION_H__
#define __IBUTTONACTION_H__

#include "../External/xrTypes.h"

class IActionTrigger
{ 
public:
	virtual Void OnPress(Int32 id)=0;
	virtual Void OnRelease(Int32 id, Boolean isIn)=0;
};

#endif  //__IBUTTONACTION_H__