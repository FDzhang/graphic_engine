#include "CATransition.h"
#include "CAProperty.h"
#include "../../Common/xrDataStruct.cpp"

Boolean CATransition::TryAdd(AnimationStyle style, UInt32 duration, TransitionInfo* updater)
{
	TransitionInfo* temp = m_updateLinkHeader;
	Boolean addFlag = FALSE;
	while (temp) {
		if (style == temp->style && duration == temp->duration) {
			if (m_updateLinkHeader)  m_updateLinkHeader->InsertBefore(updater);
			m_updateLinkHeader = updater;
			addFlag = TRUE;
			break;
		}
		temp = temp->GetNext();
	}

	//xrprint("fromVal = %f, toVal = %f!!!\n", fromVal, toVal);
	return addFlag;
}

Void CATransition::SetNew(AnimationStyle style, UInt32 duration, TransitionInfo* updater)
{
	m_from = 0.0;
    m_dx = 1.0;
    m_startTime = XrGetTime();
    m_active = TRUE;

	m_style = style;
	m_totalTime = duration;
	m_updateLinkHeader = updater;
}

Boolean CATransition::ExcludeSharing(TransitionInfo* updater)
{
	if (!updater->GetNext() && !updater->GetPrev()) return FALSE;
	if (updater == m_updateLinkHeader) m_updateLinkHeader = updater->GetNext();
	updater->Remove();
	return TRUE;
}

Boolean CATransition::Update(UInt32 timeStamp)
{
	Float32 result;
	TransitionInfo* iter = m_updateLinkHeader, *temp;
	if (GetStyle(timeStamp, &result)) {
		while (iter) {
			iter->host->SetTransitionValue(result);
			iter = iter->GetNext();
		}
		return TRUE;
	}
	else {
		while (iter) {
			temp = iter;
			iter->host->OnTransitionFinish();
			iter = iter->GetNext();
			temp->SetNext(0);
			temp->SetPrev(0);
		}
		m_updateLinkHeader = 0;
		return FALSE;
	}
}
