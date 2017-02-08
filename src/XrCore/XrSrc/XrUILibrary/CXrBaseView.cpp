#include "CXrBaseView.h"
#include "../Common/XrInternal.h"

CXrBaseView::CXrBaseView()
{
	m_root = 0;
	m_rootId = -1;
	m_node = 0;
	m_trigger = 0;
}
String CXrBaseView::GetName()
{
	return m_name;
}

Void CXrBaseView::SetName(String name)
{
	if (!m_name) {m_name = new CHAR[MaxNameLen];
	}
	if (!m_name) return;
	strcpy(m_name, name);
}

xr_state CXrBaseView::InitView()
{
	return XR_OK;
}

Void CXrBaseView::SetPosition(Float32 x, Float32 y)
{
	if (m_root) {
		m_root->SetX(x);
		m_root->SetY(y);
	}
}
Void CXrBaseView::SetDX(Float32 x)
{
	if (m_root) {
		m_root->SetDX(x);
	}
}

Void CXrBaseView::SetDY(Float32 y)
{
	if (m_root) {
		m_root->SetDY(y);
	}
}

Void CXrBaseView::SetSize(Float32 w, Float32 h)
{
	if (m_root) {
		m_root->SetWidth(w);
		m_root->SetHeight(h);
	}
}

Void CXrBaseView::SetEnable(Boolean enable)
{
	if (m_root) m_root->SetEnable(enable);
}

Void CXrBaseView::SetOpacity(Float32 opacity)
{
	if (m_root) m_root->SetOpacity(opacity);
}

Void CXrBaseView::Show()
{
	if (m_root) m_root->SetOpacity(1);
}

Void CXrBaseView::Hide()
{
	if (m_root) m_root->SetOpacity(0);
}

Boolean CXrBaseView::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	if (type == TouchEvent_Down) {
		if (m_trigger) m_trigger->OnPress(layerId);
	}
	else if (type == TouchEvent_Up) {
		if (m_trigger) m_trigger->OnRelease(layerId, true);
	}
	return TRUE;
}


xr_state CXrBaseView::Add(class IUINode* node ,Int32 targetIndex, InsertFlag flag, Int32 x, Int32 y, Int32 w, Int32 h)
{
	return XR_OK;
}
Void CXrBaseView::SetOnClickDelegate(IActionTrigger* trigger)
{
	if (m_root) m_root->SetEventResponder(this);
	m_trigger = trigger;
}

Void CXrBaseView::SetAnchorPoint(
		/* [in] */Float32 x,
		/* [in] */Float32 y)
{
	if (m_root) m_root->SetAnchorPoint(x, y);
}
