#include "CScrollPanel.h"

CScrollPanel::CScrollPanel(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, ScrollMode mode, CMaterial* pMtl, Float32 opacity):
	CLayer(x, y, z, width, height, pMtl, opacity),
	CScrollModule2D(mode)
{
	m_layerType = LayerType_ScrollPanel;
	m_moduleHost = this;
	m_self = (Void*)this;
}

CScrollPanel::~CScrollPanel()
{
}

xr_state CScrollPanel::SetScrollMode(ScrollMode mode)
{
    m_mode = mode;
	return XR_OK;
}

Boolean CScrollPanel::OnTouch(TouchPackage* package)
{
    Int32 m_currTime;
	if (!GetSub()) return FALSE;
	switch (package->touchEvent) {
        case TouchEvent_Down:
			ScrollReset(GetSub());
            m_dx = 0;
            m_dy = 0;
            m_lastPackage.x = package->x;
            m_lastPackage.y = package->y;
            break;

        case TouchEvent_Move:
            m_dx = package->x - m_lastPackage.x;
            m_dy = package->y - m_lastPackage.y;
            ScrollByDistance(m_dx, m_dy);

            m_lastPackage.x = package->x;
            m_lastPackage.y = package->y;
            m_lastTime = XrGetTime();
            break;

        case TouchEvent_Up:

            m_currTime = XrGetTime();
            if (m_currTime - m_lastTime > 200) {
                m_dx = 0;
                m_dy = 0;
            }

            ScrollBySpeed(m_dx, m_dy);

            m_lastPackage.x = package->x;
            m_lastPackage.y = package->y;
            break;

        default:
            break;

    }

    return TRUE;
}

xr_state CScrollPanel::SetEnableBuffer(
	/* [in] */ Boolean flag)
{
	return XR_OK;
}