#ifndef __ISCROLLING_ANIMATION_H__
#define __ISCROLLING_ANIMATION_H__
#include "xrIntrinsic.h"
class IScrollingAnimation
{
public:

	virtual Void SetRange(
		/* [in] */ Float32 from, 
		/* [in] */ Float32 to, 
		/* [in] */ Boolean hasBound)=0;

	virtual Void SetInterval(
		/* [in] */ Float32 intl)=0;
	
	virtual Void GetCurPos(
			/* [out] */ Float32& pCurPos) = 0;

	virtual Void DockToValue(
		/* [in] */ Float32 val)=0;

	virtual Void DockToDeltaValue(
		/* [in] */ Float32 val)=0;

	virtual Void BindTarget(
		/* [in] */ class IAProperty* target)=0;

	virtual Void Scroll(
		/* [in] */ Float32 x)=0;

	virtual Void Bind2ndTarget(
		/* [in] */ class IAProperty* target,
		/* [in] */ Float32 offset,
		/* [in] */ Float32 scale)=0;

};

#endif  //__ISCROLLING_ANIMATION_H__
