#include "CAQuaternion.h"
#include "CATransition.h"
#include "../../XrCore/CAnimationManager.h"
#include "../Layer/CLayer.h"
#include "../../External/IAnimationDelegate.h"
#include "../../Common/XrMathEx.h"

CAQuaternion::~CAQuaternion()
{
}

Void CAQuaternion::SetTransitionStyle(
	/* [in] */ UInt32 style, 
	/* [in] */ UInt32 duration)
{
	CAProperty::SetTransitionStyle(style, duration);	//for w component
	xyz->x.SetTransitionStyle(style, duration);
	xyz->y.SetTransitionStyle(style, duration);
	xyz->z.SetTransitionStyle(style, duration);
}

Void CAQuaternion::SetTransitionValue(Float32 val)
{
	//XRQUATERNIONf from={xyz->x.m_tsInfo->fromValue, xyz->y.m_tsInfo->fromValue, xyz->z.m_tsInfo->fromValue, m_tsInfo->fromValue};
	//XRQUATERNIONf to={xyz->x.m_tsInfo->dstValue, xyz->y.m_tsInfo->dstValue, xyz->z.m_tsInfo->dstValue, m_tsInfo->dstValue};
	//XRQUATERNIONf out;
	//XRMatrixQuaternionSlerpF(out, from, to, val);
	//xyz->x.m_curValue = out.x;
	//xyz->y.m_curValue = out.y;
	//xyz->z.m_curValue = out.z;
	//m_curValue = out.w;
}

Void CAQuaternion::Set(Float32* val, UInt32 style, UInt32 duration)
{
	if (style && duration) {
		if (m_tsInfo && m_tsInfo->transition) {
			if (IsEquall(val)) return;
			InitTransitionValue(val);
			if (m_tsInfo->transition->ExcludeSharing(m_tsInfo)) {
				m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)style, duration, m_tsInfo);
			}
			else {
				m_tsInfo->transition->SetNew((AnimationStyle)style, duration, m_tsInfo);
			}
			return;
		}
		else {
			if (!m_tsInfo) m_tsInfo = new TransitionInfo();
			m_tsInfo->host = this;
			InitTransitionValue(val);
			m_tsInfo->style = (AnimationStyle)style;
			m_tsInfo->duration = duration;
			m_tsInfo->apdelegate = 0;
			m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)style, duration, m_tsInfo);
			return;
		}
	}
	m_curValue = val[3];
	xyz->x.m_curValue = val[0];
	xyz->y.m_curValue = val[1];
	xyz->z.m_curValue = val[2];
}

Void CAQuaternion::Set(
	/* [in] */ Float32* val)
{
	if (!m_tsInfo)  goto end;
	if (m_tsInfo->style && m_tsInfo->duration) {
		if (m_tsInfo->transition) {
			if (IsEquall(val)) return;
			InitTransitionValue(val);
			if (m_tsInfo->transition->ExcludeSharing(m_tsInfo)) {
				m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			}
			else {
				m_tsInfo->transition->SetNew(m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			}
			return;
		}
		else {
			if (IsEquall(val)) return;
			InitTransitionValue(val);
			m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			return;
		}
	}
end:
	m_curValue = val[3];
	xyz->x.m_curValue = val[0];
	xyz->y.m_curValue = val[1];
	xyz->z.m_curValue = val[2];
}

Void CAQuaternion::Delta(
	/* [in] */ Float32* dval)
{
	if (!m_tsInfo || dval==0)  goto end;
	if (m_tsInfo->style && m_tsInfo->duration) {
		if (m_tsInfo->transition) {
			InitTransitionDeltaValue(dval);
			if (m_tsInfo->transition->ExcludeSharing(m_tsInfo)) {
				m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			}
			else {
				m_tsInfo->transition->SetNew(m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			}
			return;
		}
		else {
			InitTransitionDeltaValue(dval);
			m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			return;
		}
	}
end:
	m_curValue += dval[3];
	xyz->x.m_curValue += dval[0];
	xyz->y.m_curValue += dval[1];
	xyz->z.m_curValue += dval[2];
}

Void CAQuaternion::Delta(Float32* dval, UInt32 style, UInt32 duration)
{
	if (dval == 0) return;
	if (style && duration) {
		if (m_tsInfo && m_tsInfo->transition) {
			InitTransitionDeltaValue(dval);
			if (m_tsInfo->transition->ExcludeSharing(m_tsInfo)) {
				m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)style, duration, m_tsInfo);
			}
			else {
				m_tsInfo->transition->SetNew((AnimationStyle)style, duration, m_tsInfo);
			}
			return;
		}
		else {
			if (!m_tsInfo) m_tsInfo = new TransitionInfo();
			m_tsInfo->host = this;
			InitTransitionDeltaValue(dval);
			m_tsInfo->style = (AnimationStyle)style;
			m_tsInfo->duration = duration;
			m_tsInfo->apdelegate = 0;
			m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)style, duration, m_tsInfo);
			return;
		}
	}
	m_curValue += dval[3];
	xyz->x.m_curValue += dval[0];
	xyz->y.m_curValue += dval[1];
	xyz->z.m_curValue += dval[2];
}

Void CAQuaternion::OnTransitionFinish()
{
	m_curValue = m_tsInfo->dstValue;
	xyz->x.m_curValue = xyz->x.m_tsInfo->dstValue;
	xyz->y.m_curValue = xyz->y.m_tsInfo->dstValue;
	xyz->z.m_curValue = xyz->z.m_tsInfo->dstValue;
	//xrprint("host %p returned transition %p\n", this, transition);
	if (m_tsInfo->apdelegate && !m_tsInfo->apdelegate->OnFinish(this)) m_tsInfo->apdelegate = 0;
	m_tsInfo->transition = 0;
}
