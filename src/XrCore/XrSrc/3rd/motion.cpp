//----------------------------------------------------------------------------------
// File:        motion.cpp
// SDK Version: v10.10 
// Email:       tegradev@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2007-2012, NVIDIA CORPORATION.  All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA OR ITS SUPPLIERS
// BE  LIABLE  FOR  ANY  SPECIAL,  INCIDENTAL,  INDIRECT,  OR  CONSEQUENTIAL DAMAGES
// WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS OF BUSINESS PROFITS,
// BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
// ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
//
//----------------------------------------------------------------------------------

#include "motion.h"
#include "../Platform/XrOS.h"

#define STATE_NEED_REPOSITION 0
#define STATE_SCROLLING_FORWARD 1
#define STATE_SCROLLING_BACKWARD -1
#define STATE_REPOSITIONING 2
#define HARDNESS 1
#define epsilogn 0.0002f
#define FICTION 0.0004f



static signed char coefs[16] = {
    -1, 2,-1, 0,
     3,-5, 0, 2,
    -3, 4, 1, 0,
     1,-1, 0, 0 };

inline int sign(float x)
{
	if (x>=0.0000000f) return 1;
	else return -1;
}

GlMotion::GlMotion()
{
	m_deltaS = 0.0f;
	m_value = 0.0f;
	m_active = 0;
	m_rewardSpeed = 600;//in ms
	m_dockingSpeed = 30;
}

int GlMotion::Update(int param1, int param2)
{
    float  delta = 0, currTime = 0, deltaTime, time;
    float acc = m_acc, y , y2;

	if (!m_active) return 0;

    switch (m_state) {
        case STATE_SCROLLING_FORWARD:
            currTime = MotionGetTime() - m_startTime;
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
            m_active = true;
            break;

        case STATE_SCROLLING_BACKWARD:
            currTime = MotionGetTime() - m_startTime;
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
            m_active = true;
            break;

        case STATE_NEED_REPOSITION:
			if (!m_bound) {
				m_active = false;
                return 0;
			}
			if (m_value > m_upperBound ) {
				if (m_value>m_upperBoundLimit) m_value = m_upperBoundLimit;
				m_fromValue = m_value;
				m_toValue = m_upperBound;
			}
			else if (m_value < m_lowerBound) {
				if (m_value<m_lowerBoundLimit) m_value = m_lowerBoundLimit;
				m_fromValue = m_value;
				m_toValue = m_lowerBound;
			}
			else {
                m_active = false;
                return 0;
			}
			    
            m_dy = (m_toValue - m_fromValue);
            m_startTime = MotionGetTime();
            m_totalTime = m_rewardSpeed;
            m_state = STATE_REPOSITIONING;
            m_active = true;
            return 0;

        case STATE_REPOSITIONING:
            time = MotionGetTime() - m_startTime;

            if (time > m_totalTime) {
                m_value = m_toValue;
                m_active = false;
				return 0;
            }
            else {
                m_active = true;
            }

            delta = m_dy * ((m_totalTime<<1) - time)
                   * time / (m_totalTime * m_totalTime);

			m_value=m_fromValue+delta;
			m_lastTime = currTime;
			return 0;
    }

    m_value+=m_deltaS;
	if (!m_bound) {
	     if (m_value>m_upperBound) m_value = m_lowerBound;
	     if (m_value<m_lowerBound) m_value = m_upperBound;
	}
    m_lastTime = currTime;
	return 0;
}

void GlMotion::SetRange(float from, float to, int flag, float hardLimit)
{
	m_lowerBound = from;
	m_upperBound = to;
	m_lowerBoundLimit = m_lowerBound + (from - to)*hardLimit;
	m_upperBoundLimit = m_upperBound + (to - from)*hardLimit;
	
	m_bound = flag;
}

void GlMotion::SetInterval(float intl)
{
}

void GlMotion::ResetValue(float val)
{
	m_value = val;
	m_active = false;
}

void GlMotion::LockOnValue(float val)
{
    m_fromValue = m_value;
    m_toValue = val;
    m_dy = (m_toValue - m_fromValue);
    m_startTime = MotionGetTime();
    m_totalTime = m_dockingSpeed;
    m_state = STATE_REPOSITIONING;
    m_active = true;
}

void GlMotion::LockOnDeltaValue(float val)
{
	m_value += val;
    m_state = STATE_NEED_REPOSITION;
    m_active = true;
}

void GlMotion::Release(float x)
{
    m_speed = x;
    m_state = sign(x);
    m_acc = FICTION * m_state;
    m_dist = 0.0f;

    m_startTime = MotionGetTime();
    m_lastTime = 0;

    m_active = true;

    if (m_bound && (m_value > m_upperBound || m_value < m_lowerBound)) {
        m_state = STATE_NEED_REPOSITION;
    }
}

float GlMotion::Get()
{
	return m_value;
}

unsigned int GlMotion::MotionGetTime()
{
	return XrGetTime();
}


void GlMotion::SetKeyFrameData(float *key, int num, int dim)
{
	m_key = key;
	m_num = num;
	m_dim = dim;
}

bool GlMotion::GetSpline(float t, float* result)
{
    const int size = m_dim + 1;

    // find key
    int k = 0; while( m_key[k*size] < t ) k++;

    // interpolant
    const float h = (t-m_key[(k-1)*size])/(m_key[k*size]-m_key[(k-1)*size]);

    // init result
    for( int i=0; i < m_dim; i++ ) result[i] = 0.0f;

    // add basis functions
    for( int i=0; i<4; i++ )
    {
        int kn = k+i-2; if( kn<0 ) kn=0; else if( kn>(m_num-1) ) kn=m_num-1;

        const signed char *co = coefs + 4*i;

        const float b  = 0.5f*(((co[0]*h + co[1])*h + co[2])*h + co[3]);

        for( int j=0; j < m_dim; j++ ) result[j] += b * m_key[kn*size+j+1];
    }
	return true;
}

bool GlMotion::GetLinear(float t, float* result)
{
    const int size = m_dim + 1;

    // find key
    int k = 0; while( m_key[k*size] < t ) k++;

    // interpolant
	const float h = (t-m_key[(k-1)*size])/(m_key[k*size]-m_key[(k-1)*size]);

    // init result
    for( int i=0; i < m_dim; i++ ) {
		result[i] = m_key[(k-1)*size+i+1]*(1-h)+m_key[k*size+i+1]*h;
	}

	return true;
}