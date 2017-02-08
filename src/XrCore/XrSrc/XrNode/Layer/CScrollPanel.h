#ifndef __CSCROLLPANEL_H__
#define __CSCROLLPANEL_H__
#include "../../Common/XrInternal.h"
#include "CScrollModule.h"
#include "CLayer.h"
#include "../../External/IScrollPanel.h"

class CScrollPanel: public IScrollPanel,  public CLayer, public CScrollModule2D
{
public:
	CScrollPanel(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, ScrollMode mode, CMaterial* pMtl=0, Float32 opacity=1.0f);
	virtual ~CScrollPanel();

	xr_state SetScrollMode(ScrollMode mode);

	virtual Boolean OnTouch(TouchPackage* package);

	virtual xr_state SetEnableBuffer(
		/* [in] */ Boolean flag);

	LAYER_DEFAULT_IMPLEMENTATION

private:
	Float32				m_dx;
	Float32				m_dy;
	TouchPackage		m_lastPackage;
	UInt32				m_lastTime;
};

#endif  //__CSCROLLPANEL_H__

