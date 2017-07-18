#include "CXrSlideBar.h"
#include "../XrNode/Scene/CUINode.h"

#define LENGTH 8
#define INTVAL 2

static int HDashId=-1;
static int VDashId=-1;
static int HLineId=-1;
static int VLineId=-1;

CXrSlideBar::CXrSlideBar(Boolean isHorizontal)
{
	m_isHorizontal = isHorizontal;
	m_sliderW = 8;
	m_sliderH = 16;
	m_val = 0.0;

}


xr_state CXrSlideBar::Add(class IUINode* node,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 width, Int32 height, Int32 mtl, XrRect* barROI, XrRect* sliderROI)
{

	//Int32 mtl1, mtl2;
	//GetMaterial(node, &mtl1, &mtl2);
	m_barW = width;
	m_barH = height;


	m_baseLayerId = node->CreateSpirit(targetIndex, flag, -1, 1.0, x, y, 0, m_barW, m_sliderH); 
	ILayer* layer = node->GetLayer(m_baseLayerId);
	layer->SetEventResponder(this);

	m_barLayerId = node->CreateSpirit(m_baseLayerId, InsertFlag_Child, mtl, 1.0, 0, m_sliderH/2-1, barROI, m_barW, m_barH); 
	m_root = node->GetLayer(m_barLayerId);

	m_sliderLayerId = node->CreateSpirit(m_baseLayerId, InsertFlag_Child, mtl, 1.0, 0, 0, sliderROI, m_sliderW, m_sliderH); 
	m_pSlider = node->GetLayer(m_sliderLayerId);

	return XR_OK;
}

Boolean CXrSlideBar::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{

	if (type == TouchEvent_Down) {

	}
	if (type == TouchEvent_Move) {

	}
	else if (type == TouchEvent_Up) {

	}
	Int32 PosX = x<0?0:x;
	PosX = PosX>m_barW?m_barW:PosX;
	m_pSlider->SetX(PosX);
	m_val = Float32(PosX)/m_barW;
	return TRUE;

}


Void CXrSlideBar::SetValue(Float32 val)
{
	Float32 value = val<0?0:val;
	value = value>1.0?1.0:value;
	m_pSlider->SetX(m_barW*value);
	m_val = value;
}