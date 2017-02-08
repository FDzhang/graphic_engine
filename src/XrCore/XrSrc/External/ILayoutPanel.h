#ifndef __ILAYOUTPANEL_H__
#define __ILAYOUTPANEL_H__
#include "ILayer.h"
 
class ILayoutPanel : virtual public ILayer
{
public:
    // Common Layer API
    //
	virtual xr_state SetLayoutMode(
    /* [in] */ LayoutMode mode)=0;

	virtual Void ReArrange()=0;

	virtual Void SetMargin(
		/* [in] */ Float32 x, 
		/* [in] */ Float32 y)=0;

    virtual Void SetInterval(
		/* [in] */ Float32 x, 
		/* [in] */ Float32 y)=0;

};

#endif  //__ILAYOUTPANEL_H__
