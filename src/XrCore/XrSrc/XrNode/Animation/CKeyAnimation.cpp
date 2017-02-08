#include "CKeyAnimation.h"
#include "CAProperty.h" 

CKeyAnimation::CKeyAnimation():
	m_receiveEvent(FALSE)
{
	m_timelines = 0;
	m_timelineNum = 0;
	m_frameData = 0;
	m_keys = 0;
	m_delegate = 0;
	m_loop = TRUE;
	m_active = FALSE;
}
CKeyAnimation::~CKeyAnimation()
{
	DeInit();
}

Void CKeyAnimation::DeInit()
{
	if (m_frameData) delete	m_frameData;
	if (m_timelines) delete m_timelines;
	if (m_keys) delete m_keys;
}

xr_state CKeyAnimation::SetDeltaUpdate(
	/* [in] */ Int32 timeLineId)
{
	m_frameData[m_timelineNum+timeLineId] = 1.0;
	for(int i=0;i<m_timelineNum;i++)
	{
	    m_frameData[i]=0;
	}
	return XR_OK;
}

Boolean CKeyAnimation::Update(UInt32 timeStamp)
{
	IAProperty* property;

	m_progress = Float32(timeStamp-m_startTime)/1000.0+0.001;
	if (!m_active) return FALSE;

	if (m_progress>=m_endTime||m_progress<0) {
		if (m_loop) {
			Start();
			SetDeltaUpdate(0);
			printf("\r\n start m_loop");
			return FALSE;
		}
		else {
			Stop();
			printf("\r\n end m_loop");
			if (m_delegate) m_delegate->OnFinish(0);
			return FALSE;
		}
	}
	if (m_style== AnimationStyle_KeyLinear) GetLinear(m_progress,m_frameData);
	else if (m_style== AnimationStyle_KeySpline) GetSpline(m_progress,m_frameData);
	else if (m_style == AnimationStyle_KeySimpleLinear) GetSimpleLinear(m_progress,m_frameData);
	else return TRUE;

	for (Int32 i=0;i<m_timelineNum;i++) {
		for (m_timelines[i].First();!m_timelines[i].IsDone();m_timelines[i].Next()) {
			property = m_timelines[i].GetCurrent();
			//printf("\r\n m_progress = %f,timestamp = %d,m_style = %x ",m_progress,timeStamp,m_style);
		    if(m_style == AnimationStyle_KeySimpleLinear)
		    {
				property->Set(m_frameData[i], 0,0);
		    
		    }
			else
			{
    			if (m_frameData[m_timelineNum+i]==1.0)
    			{	property->Delta(m_frameData[i], 0,0);
    			    //    printf("frame_data = 1");
    			}
    			else 
    			{
    			property->Set(m_frameData[i], 0,0);
    				//printf("frame_data = set");
    			}
			}
		}
	}
	return FALSE;
}

xr_state CKeyAnimation::CreateTimeLines(
	/* [in] */ Float32 *key, 
	/* [in] */ Int32 keyNum, 
	/* [in] */ Int32 timeLineNum,
	/* [in] */ AnimationStyle style,
	/* [in] */ Boolean loop)
{
	m_frameData = new Float32[timeLineNum*2];
	if (!m_frameData) goto FAILED; 
	for(Int32 i=0;i<timeLineNum*2;i++) {
		m_frameData[i]=0;
	}
	m_timelines = new CLazySlot<IAProperty, 4>[timeLineNum];
	if (!m_timelines) goto FAILED; 
	m_keys = new Float32[keyNum*(timeLineNum+1)];
	if (!m_keys) goto FAILED; 
	memcpy(m_keys, key, keyNum*(timeLineNum+1)*sizeof(Float32));
	m_style = style;
	m_loop = loop;
	m_endTime = key[(keyNum-1)*(timeLineNum+1)];
	SetKeyFrameData(m_keys, keyNum, timeLineNum, style);
	m_timelineNum = timeLineNum;
	return XR_OK;

FAILED:
	DeInit();
	return XR_FAILED;
}

xr_state CKeyAnimation::BindProperty(
	/* [in] */ Int32 timeLineId, 
	/* [in] */ class IAProperty* property)
{
	m_timelines[timeLineId].Add(property);
	return XR_OK;
}

	
Void CKeyAnimation::Start()
{
	m_startTime = XrGetTime();
	m_progress = 0;
	m_active = TRUE;
}
Void CKeyAnimation::Stop()
{
	m_active = FALSE;
}

Void CKeyAnimation::Pause()
{
	m_active = TRUE;
}
Void CKeyAnimation::Resume()
{
	m_active = FALSE;
}

Boolean CKeyAnimation::GetActiveState()
{
	return m_active;
}

Void CKeyAnimation::SetAnimationDelegate(
		/* [in] */ class IAnimationDelegate* apdelegate)
{
	m_delegate = apdelegate;
}
