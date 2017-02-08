#ifndef __IANIMATIONDELEGATE_H__
#define __IANIMATIONDELEGATE_H__
#include "xrIntrinsic.h"
 

class IAnimationDelegate
{ 
public:
	// return value : FALSE means delegate will only call once

	//virtual Boolean OnCreate(class IAProperty* caller)=0; 

	//virtual Boolean OnUpdate(class IAProperty* caller)=0; 

	virtual Boolean OnFinish(class IAProperty* caller)=0; 
};

#endif  //__IANIMATIONDELEGATE_H__
