#ifndef __CXR_SLIDEBAR_H__
#define __CXR_SLIDEBAR_H__
#include "CXrBaseView.h"

class CXrSlideBar : public CXrBaseView
{
public:
	CXrSlideBar(Boolean isHorizontal);
	~CXrSlideBar() {};
	
	virtual xr_state Add(class IUINode* node,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 width, Int32 height, Int32 mtl, Rect* barROI=0, Rect* sliderROI=0);
	Void InitMaterial(class IUINode* node);
	virtual Void SetRange(Float32 low, Float32 high) { m_high = high, m_low = low; }
	virtual Void* GetObject() { return (Void*)this; }

	Boolean OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type);

	Float32 GetValue() {
		return m_val;
	}

	Void SetValue(Float32 val);
    
protected:	
	Boolean		    m_isHorizontal;
	Int32			m_barLayerId;
	Int32			m_sliderLayerId;
	Int32			m_baseLayerId;
	ILayer*         m_pSlider;
	Float32			m_high;
	Float32			m_low;
	Int32			m_barW;
	Int32			m_barH;
	Int32			m_sliderW;
	Int32			m_sliderH;
	Float32			m_val;
};

#endif  //__CXR_SLIDEBAR_H__
