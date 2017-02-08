#ifndef __CAPROPERTY_H__
#define __CAPROPERTY_H__
#include "../../Common/XrInternal.h"
#include "../../External/IAProperty.h"

struct TransitionInfo: public CBiLinkNode<TransitionInfo>
{
	Float32							fromValue;
	Float32							dstValue;
	AnimationStyle					style;
	UInt32							duration;
	class CATransition*				transition;
	class IAnimationDelegate*		apdelegate;
	class CAProperty*				host;
};

class CAProperty: public IAProperty
{
public:
	CAProperty() : m_tsInfo(0), m_curValue(0) {}
	~CAProperty();

	virtual Void OnTransitionFinish();
	virtual Void SetTransitionValue(Float32 val)  { m_curValue = (1.0 - val)*m_tsInfo->fromValue + m_tsInfo->dstValue* val; }

	virtual Void Set(Float32 val, UInt32 style, UInt32 duration);
	virtual Void Delta(Float32 dval, UInt32 style, UInt32 duration);

	virtual Void Set(
		/* [in] */ Float32 val);

	virtual Void Delta(
		/* [in] */ Float32 dval);

	virtual Void SetTransitionStyle(
		/* [in] */ UInt32 style, 
		/* [in] */ UInt32 duration);

	virtual Void SetAPDelegate(
		/* [in] */ class IAnimationDelegate* apdelegate);

	virtual Float32 Get() { return m_curValue; }

	Float32 GetDst()
	{
		if (m_tsInfo) return m_tsInfo->dstValue;
		else return m_curValue;
	}

	Void _Set(Float32 val) {
		m_curValue = val;
	} 
	Void _Delta(Float32 val) {
		m_curValue +=val;
	} 

	friend class CAQuaternion;
protected:
	Float32					m_curValue;
	TransitionInfo*			m_tsInfo;
};

struct CAVector2
{
	Void Set(Float32 x, Float32 y)
	{
		this->x.Set(x);
		this->y.Set(y);
	}

	CAProperty	x;
	CAProperty	y;
};

struct CAVector3 : public CAVector2
{

	Void Set(Float32 x, Float32 y, Float32 z)
	{
		this->x.Set(x);
		this->y.Set(y);
		this->z.Set(z);
	}

	CAProperty	z;
};

struct CAVector4 : public CAVector3
{
	Void Set(Float32 x, Float32 y, Float32 z, Float32 w)
	{
		this->x.Set(x);
		this->y.Set(y);
		this->z.Set(z);
		this->w.Set(w);
	}

	CAProperty	w;
};

#endif  //__CAPROPERTY_H__

