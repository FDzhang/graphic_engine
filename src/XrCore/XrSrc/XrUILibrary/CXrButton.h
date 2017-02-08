#ifndef __XR_BUTTON_H__
#define __XR_BUTTON_H__
#include "CXrPanel.h"


class CXrButton : public CXrBaseView
{
public:
	CXrButton(Int32 cornerSize, class IActionTrigger* action=0, Boolean reserveState=0);
	~CXrButton();
	virtual xr_state Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Float32 opacity, String texBase, String texHit);
	virtual Void* GetObject() { return (Void*)this; }
	xr_state SetText(String text);
	xr_state SetTextSize(Float32 size);
	virtual Void SetOpacity(Float32 opacity);
	virtual Void SetActionDelegate(IActionTrigger* action) { buttonAction = action; }
	virtual Boolean OnTouchEvent(
		/* [in] */Int32 layerId,
		/* [in] */Int32 x,
		/* [in] */Int32 y,
		/* [in] */Int32 type);
	
	Void ReleaseUp();

private:
	CXrPanel		m_base;
	CXrPanel		m_hit;
	IActionTrigger	*buttonAction;
	ITextLayer*		m_text;
	Int32			m_textMtl;
	Float32			m_opacity;
	Float32			m_textSize;
	Boolean			m_isPressed;
	Boolean			m_reserveState;
};

#endif  //__XR_BUTTON_H__
