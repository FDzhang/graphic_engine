#ifndef __IKEY_ANIMATION_H__
#define __IKEY_ANIMATION_H__
#include "IAnimationDelegate.h"

class IKeyAnimation
{
public:

	virtual xr_state CreateTimeLines(
		/* [in] */ Float32 *key, 
		/* [in] */ Int32 keyNum, 
		/* [in] */ Int32 timeLineNum,
		/* [in] */ AnimationStyle style=AnimationStyle_KeyLinear,
		/* [in] */ Boolean loop=TRUE)=0;

	virtual xr_state BindProperty(
		/* [in] */ Int32 timeLineId, 
		/* [in] */ class IAProperty* property)=0;

	virtual Void SetAnimationDelegate(
		/* [in] */ class IAnimationDelegate* apdelegate)=0;

	virtual xr_state SetDeltaUpdate(
		/* [in] */ Int32 timeLineId)=0;

	virtual Void Start()=0;
	virtual Void Pause()=0;
	virtual Void Stop()=0;
	virtual Void Resume()=0;
	virtual Boolean GetActiveState()=0;

};

#endif  //__IKEY_ANIMATION_H__
