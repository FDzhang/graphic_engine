#ifndef __C_BASE_NODE_H__
#define __C_BASE_NODE_H__
#include "../Common/XrInternal.h"
#include "Animation/CAProperty.h"

template <typename T> 
class CBaseNode: public CTreeNode<T>
{
public:

	Int32 GetId()
	{
		return m_id;
	}
	
	Void SetId(Int32 id)
	{
		m_id = id;
	}

	CAVector3						position;
	CAVector3						rotation;
	CAVector3						scale;

protected:
	Boolean							m_enable;
	Boolean							m_visible;
	Int32							m_id;
};

#endif  //__C_BASE_NODE_H__

