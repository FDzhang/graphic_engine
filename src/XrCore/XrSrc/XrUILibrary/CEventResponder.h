#ifndef __CEVENTRESPONDER_H__
#define __CEVENTRESPONDER_H__

#include "../External/IEventResponder.h"

class CEventResponder
{
public:
	virtual xr_state AddToRenderNode(class CUINode* node);
	virtual xr_state SetEnable(Boolean enable);

private:
	
};

#endif  //__CEVENTRESPONDER_H__

