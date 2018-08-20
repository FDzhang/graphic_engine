#ifndef __CXRPANEL_H__
#define __CXRPANEL_H__
#include "CXrBaseView.h"

class CXrPanel : public CXrBaseView
{
public:
	CXrPanel(Int32 cornerSize, Int32 BorderWidth=-1, Boolean hollow=FALSE);
	CXrPanel();
	virtual xr_state Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Float32 opacity,const char* texName);
	virtual xr_state Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Float32 opacity, Int32 mtlId);
	//virtual Void SetOpacity(Float32 opacity);
	//virtual Void SetPosition(Int32 x, Int32 y);
	//virtual Void SetSize(Int32 x, Int32 y);
	Void ArrangeSquareUp();
	Void SetCornerSize(Int32 cornerSize);
	Void SetTextureSrc(String name);
	virtual Void SetOpacity(Float32 opacity);
	virtual Void SetSize(Float32 w, Float32 h);
	~CXrPanel() {}
	virtual Void* GetObject() { return (Void*)this; }

private:
	Int32			m_subLayerId[9];
	Int32			m_panelId;
	Int32			m_subLayerMtl;
	Int32			m_borderWidth;
	Int32			m_cornerSize;
	Boolean			m_hollow;
};

#endif  //__CXRPANEL_H__
