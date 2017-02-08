#ifndef __CAQUATERNION_H__
#define __CAQUATERNION_H__
#include "CAProperty.h"

class CAQuaternion: public CAProperty
{
public:
	CAQuaternion():xyz(0) {}
	~CAQuaternion();

	Void Init(CAVector3* vec3) { xyz = vec3; }
	virtual Void OnTransitionFinish();
	virtual Void SetTransitionValue(Float32 val);

	virtual Void Set(Float32* val, UInt32 style, UInt32 duration);	//x,y,z,w
	virtual Void Delta(Float32* dval, UInt32 style, UInt32 duration);

	virtual Void Set(
		/* [in] */ Float32* val);

	virtual Void Delta(
		/* [in] */ Float32* dval);

	virtual Void SetTransitionStyle(
		/* [in] */ UInt32 style, 
		/* [in] */ UInt32 duration);

	Void Get(Float32* result)
	{
		result[0] =  xyz->x.m_curValue;
		result[1] =  xyz->y.m_curValue;
		result[2] =  xyz->z.m_curValue;
		result[3] =  m_curValue;
	}

	Void GetDst(Float32* result)
	{
		if (m_tsInfo) {
			result[0] = xyz->x.m_tsInfo->dstValue;
			result[1] = xyz->y.m_tsInfo->dstValue;
			result[2] = xyz->z.m_tsInfo->dstValue;
			result[3] = m_tsInfo->dstValue;
		}
		else {
			result[0] =  xyz->x.m_curValue;
			result[1] =  xyz->y.m_curValue;
			result[2] =  xyz->z.m_curValue;
			result[3] =  m_curValue;
		}
	}

	Void _Set(Float32* val)
	{
		xyz->x._Set(val[0]);
		xyz->y._Set(val[1]);
		xyz->z._Set(val[2]);
		m_curValue = val[3];
	} 

	Boolean IsEquall(Float32* vec)
	{
		return m_tsInfo->dstValue == vec[3] && xyz->x.m_tsInfo->dstValue == vec[0] && xyz->y.m_tsInfo->dstValue == vec[1] && xyz->z.m_tsInfo->dstValue == vec[2];
	}

	Void InitTransitionValue(Float32* vec)
	{
		m_tsInfo->fromValue = m_curValue;
		m_tsInfo->dstValue = vec[3];

		xyz->x.m_tsInfo->fromValue = xyz->x.m_curValue;
		xyz->y.m_tsInfo->fromValue = xyz->y.m_curValue;
		xyz->z.m_tsInfo->fromValue = xyz->z.m_curValue;
		xyz->x.m_tsInfo->dstValue = vec[0];
		xyz->y.m_tsInfo->dstValue = vec[1];
		xyz->z.m_tsInfo->dstValue = vec[2];
	}
	Void InitTransitionDeltaValue(Float32* vec)
	{
		m_tsInfo->fromValue = m_curValue;
		m_tsInfo->dstValue += vec[3];

		xyz->x.m_tsInfo->fromValue = xyz->x.m_curValue;
		xyz->y.m_tsInfo->fromValue = xyz->y.m_curValue;
		xyz->z.m_tsInfo->fromValue = xyz->z.m_curValue;
		xyz->x.m_tsInfo->dstValue += vec[0];
		xyz->y.m_tsInfo->dstValue += vec[1];
		xyz->z.m_tsInfo->dstValue += vec[2];
	}
protected:
	CAVector3*		xyz;
	//w component is held by itself;
};


#endif  //__CAQUATERNION_H__

