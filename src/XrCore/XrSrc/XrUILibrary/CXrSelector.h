#ifndef __CXR_SELECTOR_H__
#define __CXR_SELECTOR_H__
#include "CXrBaseView.h"


class CXrSelector : public CXrBaseView
{
public:
	CXrSelector(Int32 cornerSize) {
		m_selected = -1;
		m_cornerSize = cornerSize;
		m_textX = 0.0; m_textY = 0.0;
		m_HLOpacity = 0.6;
	}
	~CXrSelector();

	virtual xr_state Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Int32 dx, Int32 dy, Float32 opacity, String BGTex, String FGTex, Int32 row, Int32 colume);
	xr_state AddChinese(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Int32 dx, Int32 dy,  Float32 opacity, String BGTex, String FGTex, Int32 row, Int32 colume);
	Void SetChineseItemText(Int32 num, unsigned int  text, Int32 size=-1);

	Void Update();
	virtual Void* GetObject() { return (Void*)this; }
	virtual Void SetItemText(Int32 num, String text, Int32 size = -1);
	virtual Boolean OnTouchEvent(
		/* [in] */Int32 layerId,
		/* [in] */Int32 x,
		/* [in] */Int32 y,
		/* [in] */Int32 type);

	Void Select(Int32 num);
	Void ClearSelect();

	Void SetTextSize(Int32 size);
	Void SetTextPosition(Int32 x, Int32 y) { m_textX = x, m_textY = y; }
	//Void SetFGTexOpacity(Float32 opacity) { m_FGOpacity = opacity;}
	Void SetHighlightOpacity(Float32 opacity) { m_HLOpacity = opacity;}
private:
	Int32		m_mtl1;
	Int32		m_mtl2;
	Int32		m_textMtl;
	Float32		m_itemW;
	Float32		m_itemH;
	Float32		m_interval;
	Float32		m_opacity;
	Float32		m_HLOpacity;
	struct SelectorItem*		m_item;
	Int32		m_cornerSize;
	Int32		m_itemNum;
	Int32		m_rowNum;
	Int32		m_columeNum;
	Int32		m_selected;
	Int32		m_dx;
	Int32		m_dy;
	Int32		m_textX;
	Int32		m_textY;
};

#endif  //__CXR_SELECTOR_H__
