#include "CRenderNode.h"
#include "../../Common/xrDataStruct.cpp"
#include "../Layer/CSpirit.h"
#include "../../Render/XrRender.h"
#include "../../XrCore/CDeviceManager.h"
#include "../../XrCore/CXrCore.h"
#include "../../3rd/XrFileLoader.h"
CRenderNode::CRenderNode():
	m_pRenderTarget(0),
	m_enable(TRUE),
	m_bClearDepth(0),
	m_bClearColor(0),
	m_renderROI(0),
	m_ROIAP(0),
	m_LastTime(0)
{
}

CRenderNode::~CRenderNode()
{
	for (m_mtl.First();!m_mtl.IsDone();m_mtl.Next()) {
		CMaterial* mat = m_mtl.GetCurrent();
		mat->Release();
	}
}

xr_state CRenderNode::SetRenderROI(
	/* [in] */ Region* reg)
{
	if (!m_renderROI){ m_renderROI = new Region;
		};
	if (!m_renderROI) goto FAILED;
	if (!m_ROIAP) {
		m_ROIAP = new CAVector4;
		if (!m_ROIAP) goto FAILED;
		m_ROIAP->x.Set(reg->left,0,0);
		m_ROIAP->y.Set(reg->right,0,0);
		m_ROIAP->z.Set(reg->top,0,0);
		m_ROIAP->w.Set(reg->bottom,0,0);
		m_ROIAP->x.SetTransitionStyle(AnimationStyle_EaseOut, 500);
		m_ROIAP->y.SetTransitionStyle(AnimationStyle_EaseOut, 500);
		m_ROIAP->z.SetTransitionStyle(AnimationStyle_EaseOut, 500);
		m_ROIAP->w.SetTransitionStyle(AnimationStyle_EaseOut, 500);
	}

	//if (m_renderROI) *m_renderROI = *reg;
	m_ROIAP->x.Set(reg->left);
	m_ROIAP->y.Set(reg->right);
	m_ROIAP->z.Set(reg->top);
	m_ROIAP->w.Set(reg->bottom);
	return XR_OK;
FAILED:
	if (m_renderROI) delete m_renderROI;
	if (m_ROIAP) delete m_ROIAP;
	return XR_FAILED;
}

Region* CRenderNode::GetRenderROI()
{
	if (m_renderROI) {
		m_renderROI->Set(m_ROIAP->x.Get(), m_ROIAP->y.Get(),m_ROIAP->z.Get(),m_ROIAP->w.Get());
		return m_renderROI;
	}
	else return 0;
}

xr_state CRenderNode::Init(RenderNodeType type, Int32 width, Int32 height)
{
	m_type = type;
	if (type == RenderNodeType_UI2D) defaultCamera.SetOrthognal(0, width, 0, height, CAM_NEAR, CAM_FAR);
	else if (type == RenderNodeType_UI3D) defaultCamera.SetPerspective(90.0f, Float32(width)/height, CAM_NEAR, CAM_FAR);
	return XR_OK;
}

xr_state CRenderNode::Init(RenderNodeType type, CRenderTargetEx* pRenderTarget)
{
	Int32 width, height;
	pRenderTarget->GetSize(&width, &height);
	m_pRenderTarget = pRenderTarget;
	return Init(type, width, height);
}



Int32 CRenderNode::CreateMaterialFromRenderTarget(MaterialType materialType, Int32 rtId, class IMaterial** ppIMaterial)
{
	CMaterial* pMtl;
	CRenderTargetEx* pRT;
	Int32 mid=-1;
	//switch (materialType) {
	//	case Material_UI_Spirit:
	//	case Material_UI_Spirit_With_Mask:
	//		pRT = XrCore->GetRenderTarget(rtId);
	//		if (!pRT) return -1;
	//		pMtl = new CMaterial(materialType);
	//		if (!pMtl)return -1;
	//		pMtl->SetDiffuseMap(pRT->GetRenderTexture());
	//		pMtl->UseDefaultMaterialEffect(materialType);
	//		//pMtl->RefInit();
	//		mid = m_mtl.Add(pMtl);
	//		break;
	//	default:
	//	break;
	//}
	//if (ppIMaterial) *ppIMaterial = pMtl;
	//pMtl->SetID(mid);
	return mid;
}

CCamera* CRenderNode::GetCamera()
{
	return &defaultCamera;
}

Int32 CRenderNode::CreateMaterial(
	/* [in] */ MaterialType materialType,
	/* [out] */ IMaterial** ppMtl)
{
	CMaterial* pMtl;
	Int32 tid;
	Int32 mid;
	pMtl = new CMaterial(materialType);
	if (!pMtl) {
		return -1;
	}
	if (materialType && (materialType != Material_Custom)) pMtl->UseDefaultMaterialEffect(materialType);
	//pMtl->RefInit();
	if (ppMtl) *ppMtl = pMtl;
	mid = m_mtl.Add(pMtl);
	pMtl->SetID(mid);
	return mid;
}

Int32 CRenderNode:: CreateMesh(
        /* [in] */ ModelType type,
		/* [in] */ Float32 dx,
		/* [in] */ Float32 dy,
		/* [in] */ Float32 dz,
		/* [in] */ String name,
		/* [out] */ class IMesh** ppIMesh)
{
	CMesh* pMesh;
	Int32 tid;
	Int32 mid;
	pMesh = new CMesh();
	if (!pMesh) {
		return -1;
	}

	if (ppIMesh) *ppIMesh = pMesh;
	mid = AddMesh(pMesh);
	if (type & ModelType_Internal) {
		pMesh->GenPrimitive(dx, dy, dz, type, 0);
	}
	else if (type == ModelType_Null) {

	}

	return mid;
}
Int32 CRenderNode::LoadMesh(
		/* [out] */ IMesh** ppMesh,
		/* [in]  */ String meshName,
		/* [in]  */ Float32 scale)
{
	XrAssert(ppMesh);
	Int32 mid = 0;
	//CMesh* mesh = new CMesh();
	//LoadModelFromFile(meshName, mesh, scale, TRUE);
	////MathLib::computeAABBox(mesh->GetBound(),mesh->useVBO() ? mesh->GetVBOSource():mesh->GetVertexBuffer(),
	////	mesh->GetnVtxStride()/sizeof(Float32),mesh->GetVertexCount() );
	//*ppMesh = mesh;
	//mid = m_mesh.Add(mesh);
	return mid;
}

xr_state CRenderNode::OnUpdate()
{
	return XR_OK;
}

xr_state CRenderNode::OnRender(CRenderTargetEx* pRenderTarget)
{
	CMaterial* pMtl;
	CBatchRender* pRender;
	//XrASSERT(!m_renderQuene.GetHead());
	Float32 r,g,b,a;

	if (m_pRenderTarget) {
		GetClearColor(&r,&g,&b,&a);
		XRDM->context()->SetRenderTarget(&m_pRenderTarget->m_rt ,GetRenderROI());
		if (m_bClearColor) XRDM->context()->ClearRenderTarget(r,g,b,a);
		if (m_bClearDepth) XRDM->context()->ClearDepthStencil();
	}

	this->m_RenderGroupList.Render(this->m_renderPool);

	OnRenderFinish();
	//PostRender();
	return XR_OK;

}

xr_state CRenderNode::SetRenderTarget(Int32 rtId)
{
	return 0;
}
Void CRenderNode::PreRender()
{
}

Void CRenderNode::PostRender()
{
}

TouchPackage* CRenderNode::OnEvent(TouchPackage* package)
{
	return package;
}


xr_state CRenderNode::ProcessEventQueue()
{
	return XR_OK;
}

xr_state CRenderNode::SetRenderTarget(CRenderTargetEx* pRenderTarget)
{
	m_pRenderTarget = pRenderTarget;
	return XR_OK;
}

xr_state CRenderNode::AddTouchEvent(TouchPackage* pPackage)
{
	m_eventQueue.Add(pPackage);
	return XR_OK;
}

xr_state CRenderNode::ReleaseMaterial(Int32 index)
{
	//CMaterial* mtl;
    if (index < 0 ) {
		XrASSERT(0);
        return E_NOT_EXIST;
    }
	
	m_mtl.Release(index);

    return NOERROR;
}

xr_state CRenderNode::ReleaseMesh(Int32 index)
{
    if (index < 0 ) {
		XrASSERT(0);
        return E_NOT_EXIST;
    }
	
	m_mesh.Release(index);

    return NOERROR;
}


CRenderTargetEx* CRenderNode::GetRenderTarget()
{
	return m_pRenderTarget;
}

xr_state CRenderNode::SetClear(
	/* [in] */ Boolean colorFlag,
	/* [in] */ Boolean depthFlag)
{
	m_bClearColor = colorFlag;
	m_bClearDepth = depthFlag;
	return XR_OK;
}

Boolean CRenderNode::GetClearDepth()
{
	return m_bClearDepth;
}

Void CRenderNode::OnRenderFinish()
{
}
