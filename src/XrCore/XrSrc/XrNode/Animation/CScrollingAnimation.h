#ifndef __CSCROLLINGANIMATION_H__
#define __CSCROLLINGANIMATION_H__
#include "CBaseAnimation.h"
#include "../../External/IScrollingAnimation.h"

class CScrollingAnimation : public IScrollingAnimation, public CBaseAnimation
{
public:

#define STATE_NEED_REPOSITION 0
#define STATE_SCROLLING_FORWARD 1
#define STATE_SCROLLING_BACKWARD -1
#define STATE_REPOSITIONING 2

#define HARDNESS 0.3
#define epsilogn 0.0002f
#define FICTION 0.0003f

	CScrollingAnimation();
	virtual ~CScrollingAnimation() {};
	virtual Boolean Update(UInt32 timeStamp);
	
	virtual Void SetRange(Float32 from, Float32 to, Boolean flag);
	virtual Void SetInterval(Float32 intl);
	virtual Void DockToValue(Float32 val);
	virtual Void DockToDeltaValue(Float32 val);
	virtual Void GetCurPos(
		/* [out] */ Float32& pCurPos);
	virtual Void BindTarget(IAProperty* target)
	{
		m_target = target;
	}

	virtual Void Bind2ndTarget(IAProperty* target, Float32 offset, Float32 scale)
	{
		m_2ndTarget = target;
		m_2ndOffset = offset;
		m_2ndScale = scale;
	}

	virtual Void Scroll(Float32 x);

private:
	Float32 		m_value;
	Float32			m_upperBound;
	Float32			m_lowerBound;

	Float32			m_acc;
	Float32 		m_speed;
	Float32			m_deltaS;
    Float32			m_dist;
	Int32			m_state;
	Boolean 		m_bound;

	UInt32          m_rewardDuration;
	UInt32			m_lastTime;

	void*			m_host;
	IAProperty*		m_target;
	IAProperty*		m_2ndTarget;
	Float32			m_2ndOffset;
	Float32			m_2ndScale;

	Float32         m_curValue;
};

#endif  //__CSCROLLINGANIMATION_H__

