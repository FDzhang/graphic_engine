#ifndef __CASERIES_GENERATOR_H__
#define __CASERIES_GENERATOR_H__
#include "../../Common/XrInternal.h"
//#include "..\External\ILayer.h"

class CSeriesGenerator
{
public:
	CSeriesGenerator() : m_active(0), m_totalTime(0), m_style(AnimationStyle_EaseOut) {}
	Void Generate(Float32 fromVal, Float32 toVal, Int32 duration, AnimationStyle style = AnimationStyle_EaseOut);
	Void SetKeyFrameData(Float32 *key, Int32 num, Int32 dim, AnimationStyle style);

protected:
	Boolean	GetStyle(Int32 timeStamp, Float32* result);
	Boolean GetSpline(Float32 t, Float32* result);
	Boolean GetLinear(Float32 t, Float32* result);
	Boolean GetSimpleLinear(Float32 t, Float32* result);

	Boolean GetSpline(Float32 t, Float32* result, Float32* key, Int32 num, Int32 dim, Int32* pos=0);
	Boolean GetLinear(Float32 t, Float32* result, Float32* key, Int32 num, Int32 dim, Int32* pos=0);

	AnimationStyle			m_style;
	Float32					m_from;
	Float32					m_dx;
	Float32					m_interValue;
	Int32					m_active;
	Int32					m_totalTime;
	Int32					m_startTime;

	Float32* m_key;
	Int32 m_num;
	Int32 m_dim;
};

#endif  //__CASERIES_GENERATOR_H__

