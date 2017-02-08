#ifndef __IUPDATEDELEGATE_H__
#define __IUPDATEDELEGATE_H__
#include "xrTypes.h"

class IUpdateDelegate
{ 
public:

	virtual xr_state OnUpdate()=0; 
	virtual xr_state OnRelease()=0;
};

#endif  //__IUPDATEDELEGATE_H__
