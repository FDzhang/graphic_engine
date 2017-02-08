#ifndef _IXR_RESOURCE_H
#define _IXR_RESOURCE_H
#include "IObject.h"

class IResource : public IObject
{
public:
	virtual Int32 GetID() const = 0;
	virtual Void SetID(Int32 id) = 0;
};

#endif