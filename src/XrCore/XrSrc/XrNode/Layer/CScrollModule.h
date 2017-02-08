#ifndef __CSCROLLMODULE_H__
#define __CSCROLLMODULE_H__
#include "../../Common/XrInternal.h"
#include "../Animation/CScrollingAnimation.h"

class CScrollModule2D
{
public:
	CScrollModule2D(ScrollMode mode);
    ~CScrollModule2D();

	Void ScrollReset(CLayer* layer);

    virtual Void ScrollByDistance(
    /* [in] */ Float32 dx,
    /* [in] */ Float32 dy);

	virtual Void ScrollBySpeed(
    /* [in] */ Float32 sx,
    /* [in] */ Float32 sy);

protected:

	CLayer*					m_moduleHost;
	ScrollMode				m_mode;
	CScrollingAnimation		m_xDir;
	CScrollingAnimation		m_yDir;
	Int32					m_xId;
	Int32					m_yId;
};

#endif  //__CSCROLLMODULE_H__
