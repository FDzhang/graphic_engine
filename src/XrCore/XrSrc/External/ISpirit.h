#ifndef __ISPIRIT_H__
#define __ISPIRIT_H__
#include "ILayer.h"
 
class ISpirit : virtual public ILayer
{
public:
    // Common Layer API
    //
	virtual xr_state GenPlaneMesh(
		/* [in] */ Int32 x,
		/* [in] */ Int32 y,
		/* [in] */ Int32 dx,
        /* [in] */ Int32 dy,
        /* [in] */ Float32 texScaleX,
		/* [in] */ Float32 texScaleY)=0;

};

#endif  //__ISPIRIT_H__
