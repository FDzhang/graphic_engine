#ifndef __IRENDER_NODE_EFFECT_H__
#define __IRENDER_NODE_EFFECT_H__
#include "IRenderNode.h"

class IPostProcessingNode
{
public:
 
	virtual xr_state SetEnable(
		/* [in] */ Boolean flag)=0;

};

#endif  //__IRENDER_NODE_EFFECT_H__

