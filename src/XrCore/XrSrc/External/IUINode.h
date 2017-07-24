#ifndef __IRENDER_NODE_UI_H__
#define __IRENDER_NODE_UI_H__
#include "IRenderNode.h"

class IUINode : virtual public IRenderNode
{
public:
    virtual Int32 CreateScrollPanel(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 width,
        /* [in] */ Float32 height,
		/* [in] */ ScrollMode mode,
		/* [in] */ Float32 z)=0;

    virtual Int32 CreateLayoutPanel(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 width,
        /* [in] */ Float32 height,
        /* [in] */ LayoutMode mode,
		/* [in] */ Float32 z)=0;

	virtual Int32 CreateSpirit(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Int32 materialId,
		/* [in] */ Float32 opacity,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ XrRect* roi=0,
        /* [in] */ Float32 width=0,
        /* [in] */ Float32 height=0,
		/* [in] */ Float32 z=0)=0;

	virtual Int32 CreateTextLayer(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Int32 materialId,
		/* [in] */ Float32 opacity,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ class ITextLayer** ppITextLayer=0,
        /* [in] */ Float32 width=0,
        /* [in] */ Float32 height=0,
		/* [in] */ Float32 z=0)=0;
//materialId could use to load the texture.
	virtual Int32 CreateChineseTextLayer(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Int32 materialId,
		/* [in] */ Float32 opacity,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ class ITextLayer** ppITextLayer=0,
        /* [in] */ Float32 width=0,
        /* [in] */ Float32 height=0,
		/* [in] */ Float32 z=0)=0;

	virtual Int32 CreateUIFontMaterial(
        /* [in] */ ConstString fileName,
		/* [in] */ class IMaterial** ppIMaterial)=0;
	virtual Int32 CreateUIChineseFontMaterial(
        /* [in] */ ConstString fileName,
		/* [in] */ class IMaterial** ppIMaterial)=0;

	virtual xr_state RemoveLayer(
		/* [in] */ Int32 index)=0;

	virtual class ILayer* GetLayer(Int32 id)=0;
	virtual class ISpirit* GetSpirit(Int32 id)=0;
	virtual	class ILayoutPanel* GetLayoutPanel(Int32 id)=0;

	virtual Int32 CreateUIMaterial(MaterialType materialType, String name, UInt32 texOption=0, class IMaterial** ppIMaterial=0)=0;

	//virtual xr_state SetLayerMaterial(
	//	/* [in] */ Int32 layerId,
	//	/* [in] */ Int32 mtlId,
	//	/* [in] */ Rect* roi=0);
};

#endif  //__IRENDER_NODE_UI_H__
