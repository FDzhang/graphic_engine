//----------------------------------------------------------------------------------
// File:        motion.h
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

#ifndef __GL_MOTION_H__
#define __GL_MOTION_H__

class GlMotion
{
public:
	GlMotion();
	int Update(int param1, int param2);
	void SetRange(float from, float to, int flag, float hardLimit = 0.5);
	void SetInterval(float intl);
	void LockOnValue(float val);
	void LockOnDeltaValue(float val);
	void ResetValue(float val);
	void Release(float x);
	void SetKeyFrameData(float *key, int num, int dim);
	bool GetSpline(float t, float* result);
	bool GetLinear(float t, float* result);
	float Get();
	unsigned int MotionGetTime();
	int			m_rewardSpeed;
	int			m_dockingSpeed;

private:
	float m_value;
	float m_upperBound;
	float m_lowerBound;
	float m_upperBoundLimit;
	float m_lowerBoundLimit;
	float m_fromValue;
	float m_toValue;
	float m_acc;
	float m_speed;
	float m_deltaS;
    float m_dist;
	float m_dy;
	int m_state;
	bool m_active;
	int m_bound;
	int m_startTime;
    int m_lastTime;
    int	m_totalTime;
	float* m_key;
	int m_num;
	int	m_dim;
};
#endif //__GL_MOTION_H__
