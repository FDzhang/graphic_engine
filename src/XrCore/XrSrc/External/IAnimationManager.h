#ifndef __IANIMATION_MANAGER_H__
#define __IANIMATION_MANAGER_H__
#include "xrIntrinsic.h"
 
class IAnimationManager
{
public:

	virtual Int32 CreateAnimation(            
		/* [in] */ Int32 from,
        /* [in] */ Int32 to,
        /* [in] */ Int32 beginFrame,
        /* [in] */ Int32 repeatCount,
        /* [in] */ Boolean autoReverse,
        /* [in] */ Int32 style,
        /* [in] */ Int32 duration,
        /* [in] */ Int32 animeType) = 0;

	virtual Int32 CreateScrollingAnimation(
        /* [out] */ class IScrollingAnimation**  ppIScrollingAnimation) = 0;

	virtual Int32 CreateKeyAnimation(            
		/* [in] */ Float32 *key, 
		/* [in] */ Int32 keyNum, 
		/* [in] */ Int32 timeLineNum,
		/* [out] */ class IKeyAnimation** ppIKeyAnimation,
        /* [in] */ AnimationStyle style=AnimationStyle_KeyLinear,
		/* [in] */ Boolean loop=TRUE)=0;

};

#endif  //__IANIMATION_MANAGER_H__
