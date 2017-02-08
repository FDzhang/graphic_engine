#ifndef __CLAYOUTPANEL_H__
#define __CLAYOUTPANEL_H__
#include "../../Common/XrInternal.h"
#include "CLayoutModule.h"
#include "CLayer.h"
#include "../../External/ILayoutPanel.h"

class CLayoutPanel: public ILayoutPanel,  public CLayer, public CLayoutModule2D
{
public:
	CLayoutPanel(Float32 x, Float32 y, Float32 z, Float32 width, Float32 height, LayoutMode mode, CMaterial* pMtl=0, Float32 opacity=1.0f);
	virtual ~CLayoutPanel();

    xr_state SetLayoutMode(LayoutMode mode); //stack, grid, dock, free, square
    virtual Void SetMargin(Float32 x, Float32 y);
    virtual Void SetInterval(Float32 x, Float32 y);
    virtual Void SetAlignMode(Int32 alignMode, Int32 vhMode);
    virtual Void SetRowColumnNum(Int32 rowNum, Int32 columnNum);

	virtual Void ReArrange();
    LayoutMode GetLayoutMode()				{ return m_mode; }
    Void SetAutoSize(Boolean autoSize)      { m_autoSize = autoSize; }

	LAYER_DEFAULT_IMPLEMENTATION
private:

};

#endif  //__CLAYOUTPANEL_H__

