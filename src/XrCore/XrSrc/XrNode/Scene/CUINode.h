#ifndef __CRENDERNODEUI_H__
#define __CRENDERNODEUI_H__
#include "../../Common/XrInternal.h"
#include "../../External/IUINode.h"
#include "CRenderNode.h"
#include "../Layer/CLayer.h"
#include "../../Render/XrBatchRender.h"

class CUINode:  public CRenderNode, public IUINode, public CXrTree<CLayer>
{
public:
	CUINode();
	virtual ~CUINode();

	virtual xr_state OnUpdate();
	virtual TouchPackage* OnEvent(TouchPackage* package);
	xr_state ProcessEventQueue();
	//virtual xr_state OnRender();
	virtual xr_state SetRenderTarget(class IRenderTarget* pIRenderTarget);

    virtual Int32 CreateScrollPanel(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 width,
        /* [in] */ Float32 height,
		/* [in] */ ScrollMode mode,
		/* [in] */ Float32 z=UI_SPIRITOFFSET);

    virtual Int32 CreateLayoutPanel(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 width,
        /* [in] */ Float32 height,
        /* [in] */ LayoutMode mode,
		/* [in] */ Float32 z=UI_SPIRITOFFSET);

	virtual Int32 CreateSpirit(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Int32 materialId,
		/* [in] */ Float32 opacity,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ Rect* roi=0,
        /* [in] */ Float32 width=0,
        /* [in] */ Float32 height=0,
		/* [in] */ Float32 z=0);

	virtual Int32 CreateTextLayer(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Int32 materialId,
		/* [in] */ Float32 opacity,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ ITextLayer** ppITextLayer=0,
        /* [in] */ Float32 width=0,
        /* [in] */ Float32 height=0,
		/* [in] */ Float32 z=0);
	virtual Int32 CreateChineseTextLayer(
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Int32 materialId,
		/* [in] */ Float32 opacity,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ ITextLayer** ppITextLayer=0,
        /* [in] */ Float32 width=0,
        /* [in] */ Float32 height=0,
		/* [in] */ Float32 z=0);

	virtual class ILayer* GetLayer(Int32 id);
	virtual	class ILayoutPanel* GetLayoutPanel(Int32 id);
	virtual	class IScrollPanel* GetScrollPanel(Int32 id);
	virtual class ISpirit* GetSpirit(Int32 id);

	virtual Int32 CreateMaterial(
		/* [in] */ MaterialType materialType,
		/* [out] */ IMaterial** ppMtl);

	virtual Int32 CreateUIFontMaterial(
        /* [in] */ ConstString fileName,
		/* [in] */ class IMaterial** ppIMaterial);
	
		virtual Int32 CreateUIChineseFontMaterial(
			/* [in] */ ConstString fileName,
			/* [in] */ class IMaterial** ppIMaterial);

	virtual Int32 CreateUIMaterial(MaterialType materialType, String name,  UInt32 texOption=0, IMaterial** ppIMaterial=0);
	Int32 CreateMaterialFromRenderTarget(MaterialType materialType, Int32 rtId, class IMaterial** ppIMaterial=0);

	//virtual xr_state SetLayerMaterial(
	///* [in] */ Int32 layerId,
	///* [in] */ Int32 mtlId,
	///* [in] */ Rect* roi=0);

	xr_state AddUIRender(LayerTraverseInfo* info);
	CLayer* GetLayerObject(Int32 id) { return m_layer.Get(id); }

	virtual xr_state RemoveLayer(
		/* [in] */ Int32 index);

private:
	
	Void TraverseNode(
    /* [in] */ LayerTraverseInfo* traverseInfo,
    /* [in] */ CNodeVisitor* visitor,
    /* [in] */ Boolean visitSibling);

	Int32 CreateLayer(
		/* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 width,
        /* [in] */ Float32 height);

	CLayer* TestLayerHit(TouchPackage* pPackage);

	inline Int32 _AddLayer(CLayer* layer, Int32 targetIndex, InsertFlag flag);
	
	CLazySlot<CLayer, DefaultNumLayer>		m_layer;
	CLayer*								m_hitedLayer;
	CStack<LayerTraverseInfo, MaxNumStack>   m_rs;				//layer rendering stack

	//CXrBiLinkList<CBatchRender>			m_renderQuene;		//render quene for blending primitive
};

#endif  //__CRENDERNODEUI_H__

