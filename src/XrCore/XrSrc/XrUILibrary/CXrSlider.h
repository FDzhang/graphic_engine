#ifndef __CXRSLIDER_H__
#define __CXRSLIDER_H__

#include "CXrBaseView.h"

class CXrSlider : public CXrBaseView
{
public:
	CXrSlider();
	~CXrSlider();

	Void Add(class IUINode* node, Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y,Int32 w, Int32 h, ScrollMode mode, Int32 low, Int32 high, Int32 div, Int32 mul);
	Void SetMode(ScrollMode mode);
	Void SetRange(Int32 low, Int32 high);
	Void SetDivider(Int32 div);
	Void SetDividerMul(Int32 multiple);
	Void InitRes(class IUINode* node, Int32 w, Int32 h);
	Void GetSilderAP(IAProperty** ppIAPX, IAProperty** ppIAPY);
	virtual Void* GetRealType() { return (Void*)this; }
private:
	Int32		m_low;
	Int32		m_high;
	Int32		m_div;
	Int32		m_mul;

	ScrollMode	m_mode;
	Int32	textMtlId;
	Int32   lineMtlId;
	Int32   RTMtlId;
	Int32   RTId;
	Int32	RTNodeId;

	Int32	line16Tex;
	class	IUINode* rtNode;
	class	IMaterial* pRTMtl;
	class	ILayoutPanel* pPanel;

	Int32			baseLayerId;
	Int32			scrollPanelId;
	Int32			layoutPanelId;
	
	Int32			divCount;
	Int32*			divIds;		
	ILayer*			glow;
};

#endif  //__CXRGRID_H__

