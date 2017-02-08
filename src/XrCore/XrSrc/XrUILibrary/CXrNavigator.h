#ifndef __CXR_NAVIGATOR_H__
#define __CXR_NAVIGATOR_H__
#include "CXrBaseView.h"

struct NavigatorItem {
	Int32		m_baseId;
	Int32		m_fontLayerId;
	ITextLayer*		text;
	Int32		m_layerId1;
	Int32		m_layerId2;
	String		m_text;
};


#define PULSE_TYPE_BUTTON   0
#define	SWITCH_TYPE_BUTTON  1

#define NONE_INIT_SELECT  -1

class CXrNavigator : public CXrBaseView
{
public:
	CXrNavigator(Boolean isHorizontal=0) { m_selected = 0; m_isHorizontal = isHorizontal; }
	~CXrNavigator();

	virtual xr_state Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Int32 interval, Float32 opacity, String tex1, String tex2, String tex3, Int32 count,bool tex_same_flag=1);
	Void Update();
	virtual Void* GetObject() { return (Void*)this; }
	virtual Void SetItemText(Int32 num, String text);
	
	xr_state SetInitSelect(Int32 count,unsigned char button_type=PULSE_TYPE_BUTTON);
	virtual xr_state SetButtonTexture(class IUINode* node ,Int32 count,String tex1, String tex2, String tex3);
	virtual Boolean OnTouchEvent(
		/* [in] */Int32 layerId,
		/* [in] */Int32 x,
		/* [in] */Int32 y,
		/* [in] */Int32 type);
	Void Select(Int32 id);
private:
	Int32		m_mtl1[10];
	Int32		m_mtl2[10];
	Int32		m_mtl3[10];
	Int32		m_textMtl;
	Float32		m_itemW;
	Float32		m_itemH;
	Float32		m_interval;
	NavigatorItem*		m_item;
	Int32		m_itemNum;
	Int32		m_selected;	
	Int32		m_pre_selected;
	Boolean		m_isHorizontal;
	unsigned char m_button_type;
	
	Boolean		m_isSelected[10];
};

#endif  //__CXR_NAVIGATOR_H__
