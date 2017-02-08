#ifndef __CXR_CELLULAR_H__
#define __CXR_CELLULAR_H__
#include "CXrBaseView.h"

struct CellularItem {
	Int32		m_baseId;
	Int32		m_fontLayerId;
	ITextLayer*	text;
	Int32		m_layerId1;
	Int32		m_layerId2;
	String		m_text;
};

class CXrCellular : public CXrBaseView
{
public:
	CXrCellular() { m_selected = 0; }
	~CXrCellular();

	virtual xr_state Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Float32 dsX, Float32 dsY, Float32 opacity, String tex1, String tex2, String tex3, Int32 count);
	Void Update();
	virtual Void* GetObject() { return (Void*)this; }
	virtual Void SetItemText(Int32 num, String text);
	virtual Boolean OnTouchEvent(
		/* [in] */Int32 layerId,
		/* [in] */Int32 x,
		/* [in] */Int32 y,
		/* [in] */Int32 type);

private:
	Int32		m_mtl1;
	Int32		m_mtl2;
	Int32		m_mtl3;
	Int32		m_textMtl;
	Float32		m_itemW;
	Float32		m_itemH;
	Float32		m_interval;
	CellularItem*		m_item;
	Int32		m_itemNum;
	Int32		m_selected;
	Float32		m_dsX;
	Float32		m_dsY;
};

#endif  //__CXR_CELLULAR_H__
