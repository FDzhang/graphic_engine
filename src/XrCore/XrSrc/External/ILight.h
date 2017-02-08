#ifndef __ILIGHT_H__
#define __ILIGHT_H__
#include "xrIntrinsic.h"
 
class ILight
{
public:
    // Common Layer API
    //
	virtual xr_state SetPosition(
		/* [in] */ Float32 x,
		/* [in] */ Float32 y,
		/* [in] */ Float32 z)=0;

	virtual xr_state SetOrientation(		
		/* [in] */ Float32 vx,
		/* [in] */ Float32 vy,
		/* [in] */ Float32 vz)=0;

	virtual xr_state SetColor(
		/* [in] */ Float32 r,
		/* [in] */ Float32 g,
		/* [in] */ Float32 b)=0;

	virtual xr_state GetPosition(
		/* [in] */ Float32 *x,
		/* [in] */ Float32 *y,
		/* [in] */ Float32 *z)=0;

	virtual xr_state GetOrientation(		
		/* [in] */ Float32 *vx,
		/* [in] */ Float32 *vy,
		/* [in] */ Float32 *vz)=0;

};

#endif  //__ILIGHT_H__
