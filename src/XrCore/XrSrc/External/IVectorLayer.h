#ifndef __IVECTORLAYER_H__
#define __IVECTORLAYER_H__
#include "ILayer.h"
 
class IVectorLayer : virtual public ILayer
{
public:
    // Common Layer API
    //
	virtual xr_state GenPath(
		/* [in] */ Float32* inputData,
		/* [in] */ Int32 dataNum,
		/* [in] */ Int32	elemNum,
		/* [in] */ Float32 width,
		/* [in] */ Float32 midRoundRatio,
		/* [in] */ Float32 endRoundRatio,
		/* [in] */ Float32 deltaRad,
		/* [in] */ Float32 texScale,
		/* [in] */ Boolean bLoop)=0;

	virtual xr_state RoundRect(
		/* [in] */ Float32 roundRatio,
		/* [in] */ Float32 deltaRad)=0;

};

#endif  //__IVECTORLAYER_H__
