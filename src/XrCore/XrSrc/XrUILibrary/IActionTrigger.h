#ifndef __IBUTTONACTION_H__
#define __IBUTTONACTION_H__

#include "../External/xrTypes.h"

class IActionTrigger
{ 
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)=0;
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)=0;
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0) = 0;
};

#endif  //__IBUTTONACTION_H__