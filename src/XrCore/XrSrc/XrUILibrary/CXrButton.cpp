#include "CXrButton.h"
#include "../Common/XrInternal.h"

CXrButton::CXrButton(Int32 cornerSize, class IActionTrigger* action, Boolean reserveState):
	m_base(cornerSize),
	m_hit(cornerSize)
{
	m_isPressed = 0;
	buttonAction = action;
	m_textSize = 0.6666;
	m_reserveState = reserveState;
}

	CXrButton::~CXrButton()
{

}

xr_state CXrButton::Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h, Float32 opacity, String texBase, String texHit)
{
	Float32 tw,th;
	m_rootId = node->CreateSpirit(targetIndex, flag, -1, 1.0, x, y, 0 ,w,h); 
	m_root = node->GetLayer(m_rootId);
	m_root->SetEventResponder(this);
	
	m_base.Add(node, m_rootId, InsertFlag_Child, 0,0,w,h,opacity, texBase);
	m_hit.Add(node, m_rootId, InsertFlag_Child, 0,0,w,h,opacity, texHit);

	m_textMtl = node->CreateUIFontMaterial(XR_RES"mcg.ttf", 0);
	node->CreateTextLayer(m_rootId, InsertFlag_Child, m_textMtl, 0.8, 0, h, &m_text, h*m_textSize);

	m_opacity = opacity;
	m_hit.SetOpacity(0);

	return XR_OK;
}

xr_state CXrButton::SetTextSize(Float32 size)
{
	Float32 w,h,tw,th;
	w = m_root->GetWidth();
	h = m_root->GetHeight();
	m_textSize = size;
	m_text->SetFontSize(size);
	m_text->GetTextWH(&tw,&th);
	m_text->SetPosition((w-tw)/2,(th+h)/2-m_text->GetHeight());
	return XR_OK;
}

xr_state CXrButton::SetText(String text)
{
	Float32 w,h,tw,th;
	w = m_root->GetWidth();
	h = m_root->GetHeight();

	m_text->SetText(text);
	m_text->GetTextWH(&tw,&th);
	m_text->SetPosition((w-tw)/2, (th+h)/2-m_text->GetHeight());

	return XR_OK;
}


Void CXrButton::SetOpacity(Float32 opacity)
{
	m_opacity = opacity;
	m_base.SetOpacity(opacity);
}

Boolean CXrButton::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	if (type == TouchEvent_Down) {
		m_isPressed = 1;
		m_hit.SetOpacity(m_opacity);
		m_base.SetOpacity(0.0);
		m_text->SetOpacity(1.0);
		if (buttonAction) buttonAction->OnPress(layerId);
	}
	else if (type == TouchEvent_Up) {
		m_isPressed = 0;
		m_hit.SetOpacity(0.0);
		m_base.SetOpacity(m_opacity);
		m_text->SetOpacity(0.8);
		if (buttonAction) buttonAction->OnRelease(layerId, true);
	}
	return TRUE;
}
