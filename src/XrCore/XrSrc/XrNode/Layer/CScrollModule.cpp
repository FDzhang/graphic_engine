#include "CScrollModule.h"
#include "CLayer.h"
#include "../../XrCore/CAnimationManager.h"

CScrollModule2D::CScrollModule2D(ScrollMode mode)
{
	 m_mode = mode;
	 m_xId = XRAM->AddAnimation(&m_xDir);
	 m_yId = XRAM->AddAnimation(&m_yDir);
}

CScrollModule2D::~CScrollModule2D()
{
	 XRAM->RemoveAnimation(m_xId);
	 XRAM->RemoveAnimation(m_yId);
}

Void CScrollModule2D::ScrollByDistance(
/* [in] */ Float32 dx,
/* [in] */ Float32 dy)
{
	if (m_mode & ScrollMode_X) m_xDir.DockToDeltaValue(dx);
	if (m_mode & ScrollMode_Y) m_yDir.DockToDeltaValue(dy);
}

Void CScrollModule2D::ScrollBySpeed(
/* [in] */ Float32 sx,
/* [in] */ Float32 sy)
{
	if (m_mode & ScrollMode_X) m_xDir.Scroll(sx);
	if (m_mode & ScrollMode_Y) m_yDir.Scroll(sy);
}

Void CScrollModule2D::ScrollReset(CLayer* layer)
{
	Int32 len;
	if (m_mode & ScrollMode_X) {
		len = layer->GetWidth() - m_moduleHost->GetWidth();
		if (len<0) len=0;
		m_xDir.Deactive();
		m_xDir.SetRange(-len, 0, TRUE);
		m_xDir.BindTarget(&layer->x);
	}
	if (m_mode & ScrollMode_Y) {
		len = layer->GetHeight() - m_moduleHost->GetHeight();
		if (len<0) len=0;
		m_yDir.Deactive();
		m_yDir.SetRange(-len, 0, TRUE);
		m_yDir.BindTarget(&layer->y);
	}
}