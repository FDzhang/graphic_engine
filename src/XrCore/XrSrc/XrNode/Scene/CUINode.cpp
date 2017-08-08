#include "CUINode.h"
#include "../../Common/xrDataStruct.cpp"
#include "../../XrCore/CDeviceManager.h"
#include "../../XrCore/CXrCore.h"
#include "CUIVisitor.h"
#include "../Layer/CSpirit.h"
#include "../../3rd/Font.h"
#include "../Layer/CTextLayer.h"
#include "../Layer/CLayoutPanel.h"
#include "../Layer/CScrollPanel.h"
#include "../Layer/CChineseTextLayer.h"


CUINode::CUINode()
{
	m_hitedLayer = 0;
}

CUINode::~CUINode()
{
	for (m_layer.First();!m_layer.IsDone();m_layer.Next()) {
		CLayer* layer = m_layer.GetCurrent();
		//CLayer* realType = (CLayer*)layer->GetRealType();
		delete layer;
	}
}


Int32 CUINode::CreateUIFontMaterial(
    /* [in] */ ConstString fileName,
	/* [in] */ IMaterial** ppMtl)
{
	CMaterial* pMtl;
	CXrTextureEx* tex;
	Boolean exist=0;

	Int32 texId = XRDM->CreateSharedTexture(fileName, XrFont::GetTexSize(), XrFont::GetTexSize(), XR_A8, XR_SAMPLER_LINEAR | XR_SAMPLER_CLAMP, &tex, &exist);

	pMtl = new CMaterial(Material_UI_Font);
	if (!pMtl) return -1;
	pMtl->UseDefaultMaterialEffect(Material_UI_Font);
	if (ppMtl) *ppMtl = pMtl;
	Int32 mid = m_mtl.Add(pMtl);

	if (!exist) {
		XrFont* font = new XrFont();
		if (!font) return -1;
		if (XRFAILED(font->Init(fileName))) {
			return -1;
		}
		font->FillTexture(tex);
		font->DeInit();
		tex->extraInfo = (Void*)font;
	}

	pMtl->SetDiffuseMap(texId);
	pMtl->SetID(mid);

	return mid;
}
Int32 CUINode::CreateUIChineseFontMaterial(
    /* [in] */ ConstString fileName,
	/* [in] */ IMaterial** ppMtl)
{
	CMaterial* pMtl;
	CXrTextureEx* tex;
	Boolean exist=0;

	Int32 texId = XRDM->CreateTextureFromFile(fileName, XR_TEXTURE_TYPE_NORMAL);//483, 141, XR_A8, XR_SAMPLER_LINEAR | XR_SAMPLER_CLAMP, &tex, &exist);

	pMtl = new CMaterial(Material_UI_Font);
	if (!pMtl) return -1;
	pMtl->UseDefaultMaterialEffect(Material_UI_Font);
	if (ppMtl) *ppMtl = pMtl;
	Int32 mid = m_mtl.Add(pMtl);
#if 0
	if (!exist) {
		XrFont* font = new XrFont();
		if (!font) return -1;
		if (XRFAILED(font->Init(fileName))) {
			return -1;
		}
		font->FillTexture(tex);
		font->DeInit();
		tex->extraInfo = (Void*)font;
	}
#endif
	pMtl->SetDiffuseMap(texId);
	pMtl->SetID(mid);

	return mid;
}

Void CUINode::TraverseNode(
    /* [in] */ LayerTraverseInfo* traverseInfo,
    /* [in] */ CNodeVisitor* visitor,
    /* [in] */ Boolean visitSibling)
{
    LayerTraverseInfo rs = *traverseInfo;

    m_rs.Clean();

    if (visitSibling) {
        m_rs.Push(rs);
    }
    else {
        if (visitor->isNeedVisit(rs)) {
            visitor->visitNode(rs);
            if (visitor->isContinue()) {
                rs.layer = rs.layer->GetSub();
                if (rs.layer) {
                    m_rs.Push(rs);
                }
            }
            else return;
        }
    }

    while (!m_rs.IsEmpty()) {
        m_rs.Pop(rs);

        if (rs.layer->GetNext()) {
            CLayer* currentLayer = rs.layer;
            rs.layer = currentLayer->GetNext();
            m_rs.Push(rs);
            rs.layer = currentLayer;
        }

        if (visitor->isNeedVisit(rs)) {
            visitor->visitNode(rs);
            if (visitor->isContinue()) {
                rs.layer = rs.layer->GetSub();
                if (rs.layer) {
                    m_rs.Push(rs);
                }
            }
        }
    }

    return;
}


xr_state CUINode::OnUpdate()
{
    m_RenderGroupList.Clear();
    LayerTraverseInfo rs;
    rs.z = 2.1;
    CUIUpdateVisitor visitor(this);
    if (!m_pHead) return XR_OK;
    rs.layer = m_pHead;
    rs.clipRect.Set(0,0, XrCore->GetScreenWidth(), XrCore->GetScreenHeight());
    TraverseNode(&rs, &visitor, TRUE);
	return XR_OK;
}

TouchPackage* CUINode::OnEvent(TouchPackage* package)
{
	CLayer* layer;
    if (m_enable && m_type == RenderNodeType_UI2D)
    {
        if (package->touchEvent == TouchEvent_Down)
        {
            layer = m_hitedLayer = TestLayerHit(package);
            if (m_hitedLayer)
            {
                while (!layer->OnTouch(package))
                {
                    layer = layer->GetSuper();
                    if (!layer)
                    {
                        layer = m_hitedLayer;
                        break;
                    }
                }
                m_hitedLayer = layer;
            }
        }
        else if (package->touchEvent == TouchEvent_Move)
        {
            if (m_hitedLayer) m_hitedLayer->OnTouch(package);
        }
        else if (package->touchEvent == TouchEvent_Up)
        {
            if (m_hitedLayer) m_hitedLayer->OnTouch(package);
            //m_hitedLayer = 0;
        }
    }
    return package;
}

xr_state CUINode::ProcessEventQueue()
{
	TouchPackage* pPackage;
	CLayer* layer;
	for (m_eventQueue.First(); !m_eventQueue.IsDone(); m_eventQueue.Next()) {
		pPackage = m_eventQueue.GetCurrent();
		if (m_type == RenderNodeType_UI2D) {
			if (pPackage->touchEvent == TouchEvent_Down) {
				m_hitedLayer = TestLayerHit(pPackage);
				if (layer = m_hitedLayer) {
					while (!layer->OnTouch(pPackage)) {
						layer = layer->GetSuper();
						if (!layer) {
							break;
						}
					}
					m_hitedLayer = layer;
				}
			}
			else if (pPackage->touchEvent == TouchEvent_Move) {
				if (m_hitedLayer) m_hitedLayer->OnTouch(pPackage);
			}
			else if (pPackage->touchEvent == TouchEvent_Up) {
				if (m_hitedLayer) m_hitedLayer->OnTouch(pPackage);
				m_hitedLayer = 0;
			}
		}
	}
	
	m_eventQueue.Reset();

	return XR_OK;
}

CLayer* CUINode::TestLayerHit(TouchPackage* pPackage)
{
	LayerTraverseInfo rs;
	CUIEventVisitor visitor(this);
	visitor.InitVisit(pPackage);
	if (!m_pHead) return XR_OK;
	rs.layer = m_pHead;
	TraverseNode(&rs, &visitor, TRUE);
	return visitor.GetLastHitLayer();
}

inline Int32 CUINode::_AddLayer(CLayer* layer, Int32 targetIndex, InsertFlag flag)
{
	Int32 returnId = m_layer.Add(layer);
	layer->SetOwnerInfo(this, returnId);
	if (flag) AddNode(m_layer.Get(targetIndex), m_layer.Get(returnId), flag);
	return returnId;
}

//xr_state CUINode::SetLayerMaterial(
//	/* [in] */ Int32 layerId,
//	/* [in] */ Int32 mtlId,
//	/* [in] */ Rect* roi)
//{
//	CMaterial* pMtl = GetMaterialObject(mtlId);
//	CLayer* pLayer = m_layer.Get(layerId);
//	return pLayer->SetMaterial(pMtl, roi);
//}

Int32 CUINode::CreateSpirit(
    /* [in] */ Int32 targetIndex,
    /* [in] */ InsertFlag flag,
	/* [in] */ Int32 materialId,
	/* [in] */ Float32 opacity,
	/* [in] */ Float32 x,
    /* [in] */ Float32 y,
	/* [in] */ Rect* roi,
    /* [in] */ Float32 width,
    /* [in] */ Float32 height,
	/* [in] */ Float32 z)
{

	Region texCoord;
	
	CMaterial* pMtl = GetMaterialObject(materialId);

	CLayer::GetAdaptiveLayerSize(pMtl, roi, width, height, texCoord);
	
	if (z==0) z=UI_SPIRITOFFSET;

	CSpirit* spirit = new CSpirit(x, y, z, width, height, pMtl, opacity);
	if (!spirit) return -1;

	spirit->SetMaterialROI(&texCoord); 

	return _AddLayer(spirit, targetIndex, flag);

}

Int32 CUINode::CreateLayoutPanel(
    /* [in] */ Int32 targetIndex,
    /* [in] */ InsertFlag flag,
	/* [in] */ Float32 x,
    /* [in] */ Float32 y,
    /* [in] */ Float32 width,
    /* [in] */ Float32 height,
    /* [in] */ LayoutMode mode,
	/* [in] */ Float32 z)
{
	Region texCoord;

	CLayer::GetAdaptiveLayerSize(0, 0, width, height, texCoord);

	CLayoutPanel* panel = new CLayoutPanel(x, y, z, width, height, mode);
	if (!panel) return -1;

	CLayer* layer = (CLayer*)panel;
	return _AddLayer(layer, targetIndex, flag);
}

Int32 CUINode::CreateScrollPanel(
    /* [in] */ Int32 targetIndex,
    /* [in] */ InsertFlag flag,
	/* [in] */ Float32 x,
    /* [in] */ Float32 y,
    /* [in] */ Float32 width,
    /* [in] */ Float32 height,
	/* [in] */ ScrollMode mode,
	/* [in] */ Float32 z)
{
	Region texCoord;

	CLayer::GetAdaptiveLayerSize(0, 0, width, height, texCoord);

	CScrollPanel* panel = new CScrollPanel(x, y, z, width, height, mode);
	if (!panel) return -1;

	CLayer* layer = (CLayer*)panel;
	return _AddLayer(layer, targetIndex, flag);
}

Int32 CUINode::CreateLayer(
	/* [in] */ Int32 targetIndex,
	/* [in] */ InsertFlag flag,
	/* [in] */ Float32 x,
	/* [in] */ Float32 y,
	/* [in] */ Float32 width,
	/* [in] */ Float32 height)
{
	return XR_OK;
}

Int32 CUINode::CreateTextLayer(
    /* [in] */ Int32 targetIndex,
    /* [in] */ InsertFlag flag,
	/* [in] */ Int32 materialId,
	/* [in] */ Float32 opacity,
	/* [in] */ Float32 x,
    /* [in] */ Float32 y,
	/* [in] */ ITextLayer** ppITextLayer,
    /* [in] */ Float32 width,
    /* [in] */ Float32 height,
	/* [in] */ Float32 z)
{
	if (z==0) z=UI_SPIRITOFFSET;
	CMaterial* pMtl = GetMaterialObject(materialId);

	CTextLayer* text = new CTextLayer(x, y, z, width, width/*height is same as width*/, pMtl, opacity);
	if (!text) return -1;
	if (ppITextLayer) *ppITextLayer = text;
	return _AddLayer(text, targetIndex, flag);
}
Int32 CUINode::CreateChineseTextLayer(
    /* [in] */ Int32 targetIndex,
    /* [in] */ InsertFlag flag,
	/* [in] */ Int32 materialId,
	/* [in] */ Float32 opacity,
	/* [in] */ Float32 x,
    /* [in] */ Float32 y,
	/* [in] */ ITextLayer** ppITextLayer,
    /* [in] */ Float32 width,
    /* [in] */ Float32 height,
	/* [in] */ Float32 z)
{
	if (z==0) z=UI_SPIRITOFFSET;
	CMaterial* pMtl = GetMaterialObject(materialId);

	CChineseTextLayer* text = new CChineseTextLayer(x, y, z, width, width/*height is same as width*/, pMtl, opacity);
	if (!text) return -1;
	if (ppITextLayer) *ppITextLayer = text;
	return _AddLayer(text, targetIndex, flag);
}

xr_state CUINode::RemoveLayer(
	/* [in] */ Int32 index)
{
	CLayer* layer = m_layer.Get(index);
	IsolateNode(layer);
	m_layer.Delete(index);
	return XR_OK;
}


Int32 CUINode::CreateUIMaterial(MaterialType materialType, String name, UInt32 texOption, IMaterial** ppIMaterial)
{
	CMaterial* pMtl;
	Int32 tid=-1;
	Int32 mid=-1;
	
	pMtl = new CMaterial(materialType);
	if (!pMtl) return -1;
	pMtl->UseDefaultMaterialEffect(materialType);
	if (name) {
		tid = XRDM->CreateTextureFromFile(name, XR_TEXTURE_TYPE_DIFFUSE_SRGB);
		pMtl->SetDiffuseMap(tid);
	}

	//pMtl->RefInit();
	mid = m_mtl.Add(pMtl);

	if (ppIMaterial) *ppIMaterial = pMtl;
	pMtl->SetID(mid);
	return mid;
}

Int32 CUINode::CreateMaterial(
	/* [in] */ MaterialType materialType,
	/* [out] */ IMaterial** ppMtl)
{
	return CRenderNode::CreateMaterial(materialType, ppMtl);
}

Int32 CUINode::CreateMaterialFromRenderTarget(MaterialType materialType, Int32 rtId, class IMaterial** ppIMaterial)
{
	return CRenderNode::CreateMaterialFromRenderTarget(materialType, rtId, ppIMaterial);
}

xr_state CUINode::AddUIRender(LayerTraverseInfo* info)
{
	//CBiLinkIterator<CBatchRender>* pIter;
	CBatchRender* pBatchRender;
	CMaterial* mtl = info->layer->GetMaterial();
	xr_state xstate = XR_FAILED;
	Boolean addFlag = FALSE;
	CLayer* layer = info->layer;
	if (mtl) {

		CRenderGroup* pRenderGroup = m_RenderGroupList.Find(mtl);//mtl->GetBiLinkListIterator();
		if( pRenderGroup ){
			CLazySlot<CBatchRender,BatchRenderNumOneGroup>& group = pRenderGroup->m_group;
			for (group.First(); !group.IsDone(); group.Next()) {
				pBatchRender = group.GetCurrent();
				if (layer->hasMesh()) break;
				if (pBatchRender->TryAddQuad(info)) {
					addFlag = TRUE;
					xstate = XR_OK;
					break;
				}
			}
		}
		if (!addFlag) {
			pBatchRender = m_renderPool.Get(); 
			//pBatchRender->Reset();
			pBatchRender->SetOwner(this);
 			if (layer->hasMesh()) {
				pBatchRender->FetchMeshData(layer->GetMesh());
				TransformInfo trans;
				trans.tx = info->x;trans.ty = info->y;trans.tz = info->z;
				pBatchRender->SetTransform2D(&trans);
			}
			else pBatchRender->TryAddQuad(info);
			m_RenderGroupList.AddBatchRender(mtl,pBatchRender);
			//mtl->AddNode(NULL, pBatchRender, InsertFlag_Default);
			xstate = XR_OK;
		}
	}
	else {
		return XR_FAILED;
	}

	return xstate;
}

xr_state CUINode::SetRenderTarget(class IRenderTarget* pIRenderTarget)
{
	return XR_OK;
}

ILayer* CUINode::GetLayer(Int32 id)
{
	return (ILayer*)m_layer.Get(id);
}

ILayoutPanel* CUINode::GetLayoutPanel(Int32 id)
{
	CLayer* layer = m_layer.Get(id);
	if (layer->GetType() == LayerType_LayoutPanel) return (ILayoutPanel*)layer->GetRealType();
	else return NULL;
}

IScrollPanel* CUINode::GetScrollPanel(Int32 id)
{
	CLayer* layer = m_layer.Get(id);
	if (layer->GetType() == LayerType_ScrollPanel) return (IScrollPanel*)layer->GetRealType();
	else return NULL;
}

ISpirit* CUINode::GetSpirit(Int32 id)
{
	CLayer* layer = m_layer.Get(id);
	if (layer->GetType() == LayerType_Spirit) return (ISpirit*)layer->GetRealType();
	else return NULL;
}
