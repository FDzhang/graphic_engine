#ifndef __CANIMATIONMANAGER_H__
#define __CANIMATIONMANAGER_H__
#include "../External/IAnimationManager.h"
#include "../External/IKeyAnimation.h"
#include "../XrNode/Animation/CATransition.h"
#include "../XrNode/Animation/CBaseAnimation.h"
#include "../XrNode/Animation/CAnimationStack.h"

class CAnimationManager : public IAnimationManager
{
public:
    CAnimationManager();
    ~CAnimationManager();
	Void Update();
	CATransition* AquireTransition(AnimationStyle style, UInt32 duration, TransitionInfo* updater);
	Void ReleaseTransition(CATransition* tran);
	Void FlushTransition();
	virtual Int32 CreateAnimation(            
		/* [in] */ Int32 from,
        /* [in] */ Int32 to,
        /* [in] */ Int32 beginFrame,
        /* [in] */ Int32 repeatCount,
        /* [in] */ Boolean autoReverse,
        /* [in] */ Int32 style,
        /* [in] */ Int32 duration,
		/* [in] */ Int32 animeType);

	virtual Int32 CreateKeyAnimation(            
		/* [in] */ Float32 *key, 
		/* [in] */ Int32 keyNum, 
		/* [in] */ Int32 timeLineNum,
		/* [out] */ IKeyAnimation** ppIKeyAnimation,
        /* [in] */ AnimationStyle style=AnimationStyle_KeySpline,
		/* [in] */ Boolean loop=TRUE);

	virtual Int32 CreateScrollingAnimation(
        /* [out] */ class IScrollingAnimation**  ppIScrollingAnimation);

	Int32 CreateAnimationStack(class CAnimationStack** ppStack);

	xr_state DeleteAnimation();
	Int32 AddAnimation(CBaseAnimation* animation);
	Void RemoveAnimation(Int32 animeId);

	Int32 AddUpdate(class IUpdateDelegate* update);
	Void RemoveUpdate(Int32 updateId);

private:
	CATransition* QueueHeader;
	CATransition* ActiveHeader;
    CATransition* FreeHeader;
	CATransition* Iterator;

	//CTransitionPool												m_transitionPool;
	CLazySlot<CBaseAnimation, DefaultNumAnime>		m_animation;
	CLazySlot<IUpdateDelegate, DefaultNumUpdate>    m_update;

	UInt32 m_PrevTime;
};

#endif  //__CANIMATIONMANAGER_H__
