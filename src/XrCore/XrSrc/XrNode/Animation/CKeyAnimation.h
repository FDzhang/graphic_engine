#ifndef __CKEYANIMATION_H__
#define __CKEYANIMATION_H__
#include "CBaseAnimation.h"
#include "../../External/IKeyAnimation.h"

class CKeyAnimation : public IKeyAnimation, public CBaseAnimation
{
public:
	CKeyAnimation();
	virtual ~CKeyAnimation();
	virtual Boolean Update(UInt32 timeStamp);

	virtual Void Start();
	virtual Void Pause();
	virtual Void Stop();
	virtual Void Resume();
	virtual Boolean GetActiveState();

	virtual xr_state CreateTimeLines(
		/* [in] */ Float32 *key, 
		/* [in] */ Int32 keyNum, 
		/* [in] */ Int32 timeLineNum,
		/* [in] */ AnimationStyle style,
		/* [in] */ Boolean loop);

	virtual xr_state BindProperty(
		/* [in] */ Int32 timeLineId, 
		/* [in] */ class IAProperty* property);

	virtual xr_state SetDeltaUpdate(
		/* [in] */ Int32 timeLineId);

	virtual Void SetAnimationDelegate(
		/* [in] */ class IAnimationDelegate* apdelegate);

	Void DeInit();

protected:
	CLazySlot<IAProperty, 4>*		m_timelines;
	Int32							m_timelineNum;
	Float32*						m_keys;
	Float32*						m_frameData;
	Float32							m_progress;			//in seconds
	Float32							m_endTime;			//in seconds
	Boolean							m_receiveEvent;
	Boolean							m_loop;
	Int32							m_id;
	IAnimationDelegate*				m_delegate;
};

#endif  //__CKEYANIMATION_H__

