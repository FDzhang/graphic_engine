#ifndef _CXR_RESOURCE_H
#define _CXR_RESOURCE_H
#include "../Common/XrInternal.h"
#include "../External/IResource.h"

class CResource : public CXrRef,virtual public IResource
{
public:
	virtual ~CResource(){}

	Void Release();

	Void SetName(String name)	{}
	String GetName() { return NULL; }
	virtual Int32 GetID() const { return m_id; }
	virtual Void SetID(Int32 id) { m_id = id; }

	Xr_Self_H

protected:
	Int32	m_id;

};

#endif