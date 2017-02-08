#include "CAProperty.h"
#include "CATransition.h"
#include "../../XrCore/CAnimationManager.h"
#include "../Layer/CLayer.h"
#include "../../External/IAnimationDelegate.h"

CAProperty::~CAProperty()
{
	if (m_tsInfo) delete m_tsInfo;
}

Void CAProperty::SetTransitionStyle(
	/* [in] */ UInt32 style, 
	/* [in] */ UInt32 duration)
{
		if (!m_tsInfo) m_tsInfo = new TransitionInfo();
		m_tsInfo->host = this;
		m_tsInfo->fromValue = m_curValue;
		m_tsInfo->dstValue = m_curValue;
		m_tsInfo->style = (AnimationStyle)style;
		m_tsInfo->duration = duration;
		m_tsInfo->transition = 0;
		m_tsInfo->apdelegate = 0;
}

Void CAProperty::Set(Float32 val, UInt32 style, UInt32 duration)
{
	if (style && duration) {
		if (m_tsInfo && m_tsInfo->transition) {
			if (m_tsInfo->dstValue == val) return;
			m_tsInfo->fromValue = m_curValue;
			m_tsInfo->dstValue = val;
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
			m_tsInfo->fromValue = m_curValue;
			m_tsInfo->dstValue = val;
			m_tsInfo->style = (AnimationStyle)style;
			m_tsInfo->duration = duration;
			m_tsInfo->apdelegate = 0;
			m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)style, duration, m_tsInfo);
			return;
		}
	}
	m_curValue = val;
}

Void CAProperty::Set(
	/* [in] */ Float32 val)
{
	if (!m_tsInfo)  goto end;
	if (m_tsInfo->style && m_tsInfo->duration) {
		if (m_tsInfo->transition) {
			if (m_tsInfo->dstValue == val) return;
			m_tsInfo->fromValue = m_curValue;
			m_tsInfo->dstValue = val;
			if (m_tsInfo->transition->ExcludeSharing(m_tsInfo)) {
				m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			}
			else {
				m_tsInfo->transition->SetNew(m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			}
			return;
		}
		else {
			if (m_tsInfo->dstValue == val) return;
			m_tsInfo->fromValue = m_curValue;
			m_tsInfo->dstValue = val;
			m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			return;
		}
	}
end:
	m_curValue = val;
}

Void CAProperty::Delta(
	/* [in] */ Float32 dval)
{
	if (!m_tsInfo || dval==0)  goto end;
	if (m_tsInfo->style && m_tsInfo->duration) {
		if (m_tsInfo->transition) {
			m_tsInfo->fromValue = m_curValue;
			m_tsInfo->dstValue = dval+m_tsInfo->dstValue;
			if (m_tsInfo->transition->ExcludeSharing(m_tsInfo)) {
				m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			}
			else {
				m_tsInfo->transition->SetNew(m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			}
			return;
		}
		else {
			m_tsInfo->fromValue = m_curValue;
			m_tsInfo->dstValue = dval+m_tsInfo->dstValue;
			m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)m_tsInfo->style, m_tsInfo->duration, m_tsInfo);
			return;
		}
	}
end:
	m_curValue += dval;
}

Void CAProperty::Delta(Float32 dval, UInt32 style, UInt32 duration)
{
	if (dval == 0) return;
	if (style && duration) {
		if (m_tsInfo && m_tsInfo->transition) {
			m_tsInfo->fromValue = m_curValue;
			m_tsInfo->dstValue = dval+m_tsInfo->dstValue;
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
			m_tsInfo->fromValue = m_curValue;
			m_tsInfo->dstValue = dval+m_tsInfo->dstValue;
			m_tsInfo->style = (AnimationStyle)style;
			m_tsInfo->duration = duration;
			m_tsInfo->apdelegate = 0;
			m_tsInfo->transition = XRAM->AquireTransition((AnimationStyle)style, duration, m_tsInfo);
			return;
		}
	}
	m_curValue += dval;
}

Void CAProperty::OnTransitionFinish()
{
	m_curValue = m_tsInfo->dstValue;
	//xrprint("host %p returned transition %p\n", this, transition);
	if (m_tsInfo->apdelegate && !m_tsInfo->apdelegate->OnFinish(this)) m_tsInfo->apdelegate = 0;
	m_tsInfo->transition = 0;
}

Void CAProperty::SetAPDelegate(
	/* [in] */ class IAnimationDelegate* apdelegate)
{
	if (m_tsInfo) {
		m_tsInfo->apdelegate = apdelegate;
	}
}
