#ifndef __ISCROLLPANEL_H__
#define __ISCROLLPANEL_H__
#include "ILayer.h"
 
class IScrollPanel : virtual public ILayer
{
public:
    // Common Layer API
    //
	virtual xr_state SetScrollMode(
		/* [in] */ ScrollMode mode)=0;

	virtual xr_state SetEnableBuffer(
		/* [in] */ Boolean flag)=0;

	//virtual Void ScrollContent(
 //       /* [in] */ Int32 x,
 //       /* [in] */ Int32 y);

    //virtual void ScrollByDistance(
    //    /* [in] */ Float32 dx,
    //    /* [in] */ Float32 dy)=0;

    //virtual void ScrollBySpeed(
    //    /* [in] */ Float32 sx,
    //    /* [in] */ Float32 sy)=0;
};

#endif  //__ISCROLLPANEL_H__
