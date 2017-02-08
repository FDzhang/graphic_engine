#ifndef __IOBJECT_H__
#define __IOBJECT_H__
#include "xrIntrinsic.h"

class IObject
{ 
public:
	virtual String GetName()=0; 

	virtual Void SetName(
		/* [in] */ String name)=0; 

	virtual Void* GetRealType()=0; 
};

#endif  //__IOBJECT_H__
