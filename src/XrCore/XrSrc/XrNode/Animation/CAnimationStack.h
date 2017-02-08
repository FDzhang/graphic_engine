#ifndef __CANIMATION_STACK_H__
#define __CANIMATION_STACK_H__
#include "CBaseAnimation.h"

class CAnimationStack : public CBaseAnimation
{
public:
	CAnimationStack():m_receiveEvent(FALSE) {
		m_animationLayer = 0;
		m_layerCount = 0;
		m_activeLayer = -1;
		//m_active = FALSE;
	} 
	virtual ~CAnimationStack() {};
	virtual Boolean Update(UInt32 timeStamp);
	Boolean IsActive() { return m_active; }
	Void Deactive() { m_active = FALSE; }
	Int32	GetId() { return m_id; }
	Void SetId(Int32 id) { m_id = id; }
	xr_state SetLayerCount(Int32 count);
	Int32 GetLayerCount() { return m_layerCount; }
	CAnimationLayer* GetLayer(Int32 id) { return &m_animationLayer[id]; }
	xr_state SetActiveLayer(Int32 id) { m_activeLayer = id; }
	xr_state UpdateNodeAnimation(CAnimationNode* node, Float32 currentSec);

	xr_state Start();
	xr_state Stop() { m_activeLayer = -1; }
	xr_state Pause() { m_activeLayer = -1; }
	xr_state Resume() { m_activeLayer = -1; }

protected:
	UInt32			m_startTime;
	Float32			m_duration;
	UInt32			m_currentTime;
	CAnimationLayer* m_animationLayer;
	Boolean			m_receiveEvent;
	Int32			m_id;
	Int32			m_layerCount;
	Int32			m_activeLayer;
};

#endif  //__CANIMATION_STACK_H__

