#include "CScrollingAnimation.h"
#include "CAProperty.h"

CScrollingAnimation::CScrollingAnimation():
	m_target(0),
	m_2ndTarget(0),
	m_2ndOffset(0),
	m_2ndScale(1.0)
{
	m_deltaS = 0.0f;
	m_value = 0.0f;
	m_active = 0;
	m_dx = 0;
	m_from = 0;
	m_rewardDuration = 2000;//ms
}

Boolean CScrollingAnimation::Update(UInt32 timeStamp)
{
    Int32 currTime = 0, deltaTime, time;
    Float32 acc = m_acc, y , y2, delta=0;
	
	if (!m_active) return FALSE;

    switch (m_state) {
        case STATE_SCROLLING_FORWARD:     //case of scolling forward
			//print("scroll fw, ");
            currTime = timeStamp - m_startTime;
            deltaTime = currTime - m_lastTime;
			if (m_bound) {
				y = m_value - m_upperBound;
				if (y > 0) {
					acc = acc * (y) * HARDNESS;
				}
			}

            m_speed -= deltaTime*acc;
            m_deltaS = deltaTime*m_speed;

            if (m_speed<= epsilogn) {
                m_state = STATE_NEED_REPOSITION;
            }
            m_active = TRUE;
            break;

        case STATE_SCROLLING_BACKWARD:    //case of scolling backward
			//print("scroll bw, ");
            currTime = timeStamp - m_startTime;
            deltaTime = currTime - m_lastTime;
			if (m_bound) {
				y2 = m_value - m_lowerBound;
				if (y2 < 0) {
					acc = acc * ((-y2)) * HARDNESS;
				}
			}
            m_speed -= deltaTime*acc;
            m_deltaS = deltaTime*m_speed;

            if (m_speed >= -epsilogn) {
                m_state = STATE_NEED_REPOSITION;
            }
            m_active = TRUE;
            break;

        case STATE_NEED_REPOSITION:     //check to see if finished, if was out of bound, need reposition
			//print("need rep, ");
            // y = m_upperBound;
            // y2 = m_lowerBound;
			if (!m_bound) {
				m_active = FALSE;
                return m_active;
			}
            if (m_value > m_upperBound ) {
                m_from = m_value;
                m_dx = (m_upperBound - m_from);
                m_startTime = timeStamp;
                m_totalTime = m_rewardDuration;
                m_state = STATE_REPOSITIONING;
                m_active = TRUE;
                return m_active;
            }
            else if (m_value < m_lowerBound) {
				m_from = m_value;
				m_dx = (m_lowerBound - m_from);
                m_startTime = timeStamp;
                m_totalTime = m_rewardDuration;
                m_state = STATE_REPOSITIONING;
                m_active = TRUE;
                return m_active;
            }
            else {
				m_from = m_value;
				m_dx = 0;
                m_active = FALSE;
                return 0;
            }
            break;

        case STATE_REPOSITIONING:     //auto docking for reposition
			//xrprint("reposing: Pos = %f, m_from = %f, m_to = %f!!! !!!\n", m_value, m_from, m_from+m_dx);
            time = timeStamp - m_startTime;

            if (time > m_totalTime) {

                m_value = m_from+m_dx;
				m_target->Set(m_value, 0, 0);
				if (m_2ndTarget) m_2ndTarget->Set(m_2ndOffset+m_2ndScale*m_value, 0, 0);
				m_dx = 0;
				m_from = m_value;
                m_active = FALSE;
				//xrprint("Update: Pos = %f, m_from = %f, m_to = %f ReposEnd!!! !!!\n", m_value, m_from, m_from+m_dx);
				return m_active;
            }
            else {
                m_active = TRUE;
            }

            delta = m_dx * ((m_totalTime<<1) - time)
                   * time / (m_totalTime * m_totalTime);

			m_value=m_from+delta;
			m_target->Set(m_value, 0, 0);
			if (m_2ndTarget) m_2ndTarget->Set(m_2ndOffset+m_2ndScale*m_value, 0, 0);
			//print("value = %f, m_from = %f, m_to = %f!!!\n", m_value, m_from, m_to);
			m_lastTime = currTime;
			return m_active;
    }

    m_value+=m_deltaS;
	if (!m_bound) {
	     if (m_value>m_upperBound) m_value = m_lowerBound;
	     if (m_value<m_lowerBound) m_value = m_upperBound;
	}
	m_target->Set(m_value, 0, 0);
	if (m_2ndTarget) m_2ndTarget->Set(m_2ndOffset+m_2ndScale*m_value, 0, 0);
	//xrprint("Update: Pos = %f, m_speed = %f!!!!\n", m_value, m_speed);
    m_lastTime = currTime;

	return m_active;
}


Void CScrollingAnimation::SetRange(Float32 from, Float32 to, Boolean flag)
{
	m_lowerBound = from;
	m_upperBound = to;
	m_bound = flag;
}

Void CScrollingAnimation::SetInterval(Float32 intl)
{
}

Void CScrollingAnimation::DockToValue(Float32 val)
{
    m_from = m_value;
    m_dx = (val - m_from);
    m_startTime = XrGetTime();
    m_totalTime = m_rewardDuration;
    m_state = STATE_REPOSITIONING;
    m_active = TRUE;
	//xrprint("DockToValue = %f!\n", val);
}

Void CScrollingAnimation::DockToDeltaValue(Float32 val)
{
    m_from = m_target->Get();
	m_value = m_from+val;

	if (!m_bound) {
	     if (m_value>m_upperBound) m_value = m_lowerBound + (m_value - m_upperBound);
	     if (m_value<m_lowerBound) m_value = m_upperBound + (m_value - m_lowerBound);
	    // if (m_value>m_upperBound) m_value = m_upperBound;
	    // if (m_value<m_lowerBound) m_value = m_lowerBound;
	}
    else
    {
	    if (m_value>m_upperBound) m_value = m_upperBound;
	    if (m_value<m_lowerBound) m_value = m_lowerBound;
    
    }
	m_target->Set(m_value, 0, 0);
	if (m_2ndTarget) m_2ndTarget->Set(m_2ndOffset+m_2ndScale*m_value, 0, 0);
    m_dx = val;
	m_active = FALSE;
	//xrprint("SetVal: layerPos = %f!\n",m_value);
	return;

    m_startTime = XrGetTime();
    m_totalTime = 10;
    m_state = STATE_REPOSITIONING;
    m_active = TRUE;
	//xrprint("SetVal: layerPos = %f!\n",m_value);
}

Void CScrollingAnimation::Scroll(Float32 x)
{
//	if (-0.0==x) return;
    m_speed = x*0.05;
    m_state = getSign(x);
    m_acc = FICTION * m_state;
    m_dist = 0.0f;

    m_startTime = XrGetTime();
    m_lastTime = 0;

    m_active = TRUE;

	//xrprint("Init m_acc = %f, m_speed = %f, m_state = %d!!!!\n", m_acc, m_speed, m_state);

    if (m_bound && (m_value > m_upperBound || m_value < m_lowerBound)) {
        m_state = STATE_NEED_REPOSITION;
    }
}
