#ifndef __CRENDERNODE_H__
#define __CRENDERNODE_H__
#include "../../External/xrTypes.h"
#include "../../Common/XrInternal.h"
#include "../../External/IRenderNode.h"
//#include "../3rd/Camera.h"
#include "../Material/CMaterial.h"
#include "../Camera/CCamera.h"
#include "CRenderGroup.h"
#include "../../XrCore/CDeviceManager.h"
#include "../Lighting/CLight.h"

class CNodeVisitor
{
public:
    CNodeVisitor()
    {
        m_continue = TRUE;
    }

    virtual Boolean isContinue() { return m_continue; }

    virtual Int32 isNeedVisit(LayerTraverseInfo& traverseInfo) = 0;
    virtual Void visitNode(LayerTraverseInfo& traverseInfo) = 0;

protected:
    Boolean m_continue;
};

class CRenderVisitor : public CNodeVisitor
{
public:
    Int32 isNeedVisit(LayerTraverseInfo& traverseInfo);
    Void visitNode(LayerTraverseInfo& traverseInfo);

private:
};

class CEventVisitor : public CNodeVisitor
{
public:

    CEventVisitor(Int32 x, Int32 y, TouchEvent eventype)
    {
        eventX = peekX = x;
        eventY = peekY = y;
        touchEvent = eventype;
        lastPeekLayerId = -1;
        hitId = -1;
    }

    Int32 isNeedVisit(LayerTraverseInfo& traverseInfo);
    Void visitNode(LayerTraverseInfo& traverseInfo);

    Int32           hitId;
    Int32           lastPeekLayerId;
    Int32           eventX;
    Int32           eventY;
    TouchEvent		touchEvent;
	KeyEvent		keyEvent;
    Int32           peekX;
    Int32           peekY;
};

class CRenderNode: virtual public IRenderNode,  public CTreeNode<CRenderNode>
{
#ifdef _FILEVIEWER_
	friend class PODFileConverterToXR;
#endif
public:
	CRenderNode();
	virtual ~CRenderNode();

	virtual xr_state Init(RenderNodeType type, Int32 width, Int32 height);
	virtual xr_state Init(RenderNodeType type, class CRenderTargetEx* pRenderTarget);
	virtual xr_state OnUpdate();
	virtual TouchPackage* OnEvent(TouchPackage* package);
	virtual xr_state ProcessEventQueue();
	virtual xr_state OnRender(CRenderTargetEx* pRenderTarget);
	virtual xr_state SetRenderTarget(CRenderTargetEx* pRenderTarget);
	virtual xr_state SetRenderTarget(Int32 rtId);
	virtual CRenderTargetEx* GetRenderTarget();
	virtual xr_state AddTouchEvent(TouchPackage* pPackage);
	RenderNodeType GetType() {
		return m_type;
	}
	
	Int32 CreateMaterialFromRenderTarget(MaterialType materialType, Int32 rtId, class IMaterial** ppIMaterial=0);

	virtual Int32 CreateMaterial(
		/* [in] */ MaterialType materialType,
		/* [out] */ class IMaterial** ppMtl);

    virtual Int32 CreateMesh(
        /* [in] */ ModelType type,
		/* [in] */ Float32 dx,
		/* [in] */ Float32 dy,
		/* [in] */ Float32 dz,
		/* [in] */ String name,
		/* [out] */ class IMesh** ppIMesh);

	virtual Int32 LoadMesh(
		/* [out] */ IMesh** ppMesh,
		/* [in]  */ String meshName,
		/* [in]  */ Float32 scale);
	
	virtual xr_state ReleaseMaterial(Int32 index);
	virtual xr_state ReleaseMesh(Int32 index);
	virtual CCamera* GetCamera();
	virtual Void PostRender();

	CMaterial* GetMaterialObject(Int32 index) {
		if( index < 0 ) return NULL;
		else{
			return m_mtl.Get(index);
		}
	}

	CMaterial* UseMaterialObject(Int32 index) {
		if( index < 0 ) return NULL;
		else{
			m_mtl.Get(index)->AddRef();
			return m_mtl.Get(index);
		}
	}

	CMesh* GetMeshObject(Int32 index) { return m_mesh.Get(index); }

	virtual xr_state SetClear(
		/* [in] */ Boolean colorFlag,
		/* [in] */ Boolean depthFlag);

	virtual Boolean GetClearDepth();
	virtual Void OnRenderFinish();
	virtual Void PreRender();
	virtual xr_state SetEnable(
		/* [in] */ Boolean flag)
	{
		m_enable = flag;
		return XR_OK;
	}

	Boolean GetEnable() { return m_enable; }

	virtual xr_state SetRenderROI(
		/* [in] */ Region* reg);

	virtual Region* GetRenderROI();

	virtual Void* GetRealType() { return m_self; }

	Int32 AddMesh(CMesh* mesh) {
		return m_mesh.Add(mesh);
	}
    virtual xr_state SetClearColor(
		/* [in] */ Float32 r,
		/* [in] */ Float32 g,
		/* [in] */ Float32 b,
		/* [in] */ Float32 a)
	{
		m_clearColor.Set(r,g,b,a);
		return XR_OK;
	}

    xr_state GetClearColor(
		/* [in] */ Float32* r,
		/* [in] */ Float32* g,
		/* [in] */ Float32* b,
		/* [in] */ Float32* a)
	{
		*r = m_clearColor.x.Get();
		*g = m_clearColor.y.Get();
		*b = m_clearColor.z.Get();
		*a = m_clearColor.w.Get();
		return XR_OK;
	}

	Boolean isClearColor() {
		return m_bClearColor;
	}
	Boolean isClearDepth() {
		return m_bClearDepth;
	}

	CLight* GetLight(Int32 id=0)
	{
		return m_lights.Get(id);
	}

protected:

	CLazySlot<CMaterial, DefaultMaterialNum>	m_mtl;
	CLazySlot<CMesh, DefaultMeshNum>			m_mesh;
	CLazySlot<CLight, DefaultLightNum>		    m_lights;

	RenderNodeType								m_type;
	CRenderTargetEx*							    m_pRenderTarget;
	CCamera										defaultCamera;
	Boolean										m_bClearColor;
	Boolean										m_bClearDepth;
	Boolean										m_enable;
	CFlushQueue<TouchPackage, DefaultEventNum>	m_eventQueue;
	KeyPackage									m_keyPackage;
	Region*										m_renderROI;
	CAVector4*									m_ROIAP;
	CPool<CBatchRender>							m_renderPool;
	UInt32										m_LastTime;
	Void*										m_self;
	CAVector4									m_clearColor;
	CRenderGroupList							m_RenderGroupList;

};

#endif  //__CRENDERNODE_H__

