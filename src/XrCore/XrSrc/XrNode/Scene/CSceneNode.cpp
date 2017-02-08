#include "CSceneNode.h"
#include "../../Common/xrDataStruct.cpp"
#include "../../XrCore/CDeviceManager.h"
#include "../../XrCore/CXrCore.h"
#include "CSceneVisitor.h"
#include "../../Render/XrRender.h"
#include "../CNode.h"
#include "../../3rd/XrFileLoader.h"
#include "../../XrResource/CNodeSerializer.h"

CSceneNode::~CSceneNode()
{
	for (m_cams.First();!m_cams.IsDone();m_cams.Next()) {
		delete m_cams.GetCurrent();
	}
	for (m_lights.First();!m_lights.IsDone();m_lights.Next()) {
		delete m_lights.GetCurrent();
	}
	for (m_node.First();!m_node.IsDone();m_node.Next()) {
		CNode* node = m_node.GetCurrent();
		//CLayer* realType = (CLayer*)layer->GetRealType();
		delete node;
	}
	for (m_mesh.First();!m_mesh.IsDone();m_mesh.Next()) {
		CMesh* mesh = m_mesh.GetCurrent();
		//CLayer* realType = (CLayer*)layer->GetRealType();
		delete mesh;
	}
}
Int32 CSceneNode::CreateMaterialEx(
	/* [in] */ MaterialBlock* pDesc,
	/* [in] */ Int32 meshId,
	/* [out] */ IMaterial** ppMtl)

{
	CMaterial* pMtl;
	CMesh* pMesh = m_mesh.Get(meshId);
	Int32 tid;
	Int32 mid;
	Int32 type = pDesc->type;

	if (pMesh) {
		if (pMesh->HasBone()) {
			type |= Material_Skinned;
		}
	}
	pMtl = new CMaterial((MaterialType)type);
	if (!pMtl) {
		return -1;
	}

	pMtl->UseDefaultMaterialEffect((MaterialType)type);
	if (ppMtl) *ppMtl = pMtl;
	mid = m_mtl.Add(pMtl);
	pMtl->SetID(mid);

	if (pDesc->diffuseTex) pMtl->SetDiffuseMap(pDesc->diffuseTex);
	if (pDesc->normalTex) pMtl->SetNormalMap(pDesc->normalTex);
	if (pDesc->ambientTex) pMtl->SetAmbientMap(pDesc->ambientTex);
	if (pDesc->emissiveTex) pMtl->SetEmissionMap(pDesc->emissiveTex);
	if (pDesc->roughnessTex) pMtl->SetRoughnessMap(pDesc->roughnessTex);
	if (pDesc->specularTex) pMtl->SetSpecularMap(pDesc->specularTex);

	return mid;
}


INode* CSceneNode::FindNode(
	   /* [in] */ Int32 parentId,
	   /* [in] */ ConstString name)
{
    SceneTraverseInfo rs;
	rs.Reset();

	CNode* result = 0;
	CNode* root = m_node.Get(parentId);
	if (!root) return 0;
    CNodeFinder visitor(this);
	visitor.SetTargetName(name);
    rs.node = root;
    VisitNode(&rs, &visitor, FALSE);
	result = visitor.GetResult();
	return result;
}
 
//LPBOUNDINGSPHERE calcSphere(BYTE *vects,DWORD count,DWORD stride,LPBOUNDINGSPHERE sphere)
//{
//    // find center
//    sphere->center=D3DXVECTOR3(0.0f,0.0f,0.0f);
//    BYTE *ptr=vects;
//
//    for (int i=0;i<count;i++) {
//        sphere->center+=*((LPD3DXVECTOR3) ptr);
//        ptr+=stride;
//    }
//    sphere->center/=(float)count;
//    // find farthest point in set
//    sphere->radius=0.0f;
//    ptr=vects;
//
//    for (int i=0;i<count;i++) {
//        D3DXVECTOR3 v;
//          v=*((LPD3DXVECTOR3) ptr)-sphere->center;
//        float distSq=D3DXVec3LengthSq(&v);
//        if (distSq>sphere->radius)
//            sphere->radius=distSq;
//        ptr+=stride;
//    }
//    sphere->radius=sqrtf(sphere->radius);
//}

xr_state CSceneNode::Init(Int32 width, Int32 height)
{
	defaultCamera.SetPerspective(90.0f, Float32(width)/height, CAM_NEAR, CAM_FAR);
	m_camId = m_cams.Add(&defaultCamera);
	SetCamera(m_camId);
	return XR_OK;
}

xr_state CSceneNode::Init(CRenderTargetEx* pRenderTarget)
{
	Int32 width, height;
	pRenderTarget->GetSize(&width, &height);
	m_pRenderTarget = pRenderTarget;
	return Init(width, height);
}


void iqFrustumF_CreatePerspective( float *frus, float fovy, float aspect, float znear, float zfar )
{
    const float an = fovy * (3.141592653589f/180.0f);
    const float si = sinf(an);
    const float co = cosf(an);
    frus[ 0] =  0.0f; frus[ 1] = -co;      frus[ 2] =  si;        frus[ 3] =  0.0f;
    frus[ 4] =  0.0f; frus[ 5] =  co;      frus[ 6] =  si;        frus[ 7] =  0.0f;
    frus[ 8] =  co;   frus[ 9] =  0.0f;    frus[10] =  si*aspect; frus[11] =  0.0f;
    frus[12] = -co;   frus[13] =  0.0f;    frus[14] =  si*aspect; frus[15] =  0.0f;
    frus[16] =  0.0f; frus[17] =  0.0f;    frus[18] =  1.0f;      frus[19] =  zfar;
    frus[20] =  0.0f; frus[21] =  0.0f;    frus[22] = -1.0f;      frus[23] = -znear;
}

Int32 CSceneNode::CreateMaterialFromRenderTarget(MaterialType materialType, Int32 rtId)
{
	return CRenderNode::CreateMaterialFromRenderTarget(materialType, rtId);
}

Int32 CSceneNode::CreateMaterial(
	/* [in] */ MaterialType materialType,
	/* [out] */ IMaterial** ppMtl)
{
	return CRenderNode::CreateMaterial(materialType, ppMtl);
}


xr_state CSceneNode::ReleaseMaterial(Int32 index)
{
	//CMaterial* mtl;
    if (index < 0 ) {
		XrASSERT(0);
        return E_NOT_EXIST;
    }

	m_mtl.Release(index);

    return NOERROR;
}

xr_state CSceneNode::SetRenderTarget(class IRenderTarget* pIRenderTarget)
{
	return XR_OK;
}

Int32 CSceneNode::CreateMesh(
    /* [in] */ ModelType type,
	/* [in] */ Float32 dx,
	/* [in] */ Float32 dy,
	/* [in] */ Float32 dz,
	/* [in] */ String name,
	/* [out] */ class IMesh** ppIMesh)
{
	return CRenderNode::CreateMesh(type, dx, dy, dz, name, ppIMesh);
}

Int32 CSceneNode::AddNode(CNode* node, Int32 targetIndex, InsertFlag flag)
{
	Int32 returnId = AddNodeToSlot(node);
	if (flag) CXrTree::AddNode(m_node.Get(targetIndex), m_node.Get(returnId), flag);
	return returnId;
}

xr_state CSceneNode::OnCreateModelMesh(CNode* node)
{
	CLight* light;
	for (m_lights.First();!m_lights.IsDone();m_lights.Next()) {
		 light = m_lights.GetCurrent();
		 light->OnCreateModel(node);
	}
	return XR_OK;
}

xr_state CSceneNode::OnRemoveModelMesh(CNode* node)
{
	CLight* light;
	for (m_lights.First();!m_lights.IsDone();m_lights.Next()) {
		 light = m_lights.GetCurrent();
		 light->OnRemoveModel(node);
	}
	return XR_OK;
}

Int32 CSceneNode::CreateNode(
	/* [in] */ Int32 targetIndex,
	/* [in] */ InsertFlag flag,
	/* [in] */ Float32 x,
    /* [in] */ Float32 y,
    /* [in] */ Float32 z,
	/* [out] */ class INode** ppINode)
{
	CNode* node = new CNode(this);
	node->position.x.Set(x, 0, 0);
	node->position.y.Set(y, 0, 0);
	node->position.z.Set(z, 0, 0);
	node->rotation.x.Set(0, 0, 0);
	node->rotation.y.Set(0, 0, 0);
	node->rotation.z.Set(0, 0, 0);
	node->scale.x.Set(1.0, 0, 0);
	node->scale.y.Set(1.0, 0, 0);
	node->scale.z.Set(1.0, 0, 0);

	if (ppINode) *ppINode = node;
	Int32 id = AddNode(node, targetIndex, flag);
	//OnCreateModelMesh(node);
	return id;
}

Int32 CSceneNode::CreateModel(
/* [in] */ Int32 type,
/* [in] */ Int32 materialId,
/* [in] */ Int32 targetIndex,
/* [in] */ InsertFlag flag,
/* [in] */ Float32 x,
/* [in] */ Float32 y,
/* [in] */ Float32 z,
/* [in] */ Float32 scale,
/* [out] */INode** ppINode)
{
	Region texCoord;

	CMaterial* pMtl = GetMaterialObject(materialId);
	CNode* node = new CNode(this);
	if (!node) return -1;
	if (type & ModelType_Internal) {
		//node->GenPrimitive(scale, scale, scale, ModelType_Cube, 0);

		node->GenPrimitive(scale, scale, scale, (ModelType)type, 0);
		scale = 1.0;
	}
	else if (type == ModelType_Null) {
	}

	node->position.x.Set(x, 0, 0);
	node->position.y.Set(y, 0, 0);
	node->position.z.Set(z, 0, 0);
	node->rotation.x.Set(0, 0, 0);
	node->rotation.y.Set(0, 0, 0);
	node->rotation.z.Set(0, 0, 0);
	node->scale.x.Set(1.0, 0, 0);
	node->scale.y.Set(1.0, 0, 0);
	node->scale.z.Set(1.0, 0, 0);

	node->SetMaterial(materialId);

	if (ppINode) *ppINode = node;
	Int32 id = AddNode(node, targetIndex, flag);
	OnCreateModelMesh(node);
	return id;
}

Int32 CSceneNode::LoadNodeFromFile(
	/* [in] */ Int32 targetIndex,
	/* [in] */ InsertFlag flag,
	/* [in] */ ConstString fileName,
	/* [out] */INode** ppINode)
{
	CNodeSerializer serializer;

	CNode* node = serializer.LoadFromFile(fileName, this, false);
	if (!node) return -1;
	Int32 id = AddNode(node, targetIndex, flag);
	if (ppINode) *ppINode = node;
	return id;
}

Int32 CSceneNode::LoadModelFromFile(
    /* [in] */ String name,
	/* [in] */ Int32 materialId,
    /* [in] */ Int32 targetIndex,
    /* [in] */ InsertFlag flag,
	/* [in] */ Float32 x,
    /* [in] */ Float32 y,
    /* [in] */ Float32 z,
    /* [in] */ Float32 scale,
	/* [out] */ class INode** ppINode)
{
	Region texCoord;

	//CMaterial* pMtl = GetMaterialObject(materialId);
	CNode* model = new CNode(this);
	if (!model) return -1;
	CMesh* pMesh = new CMesh();
	if (!pMesh) {
		delete model;
		return -1;
	}

	model->SetMesh(AddMesh(pMesh));
	pMesh->SetName(name);

	_LoadModelFromFile(name, pMesh, scale, TRUE);
	//MathLib::computeAABBox(pMesh->GetBound(),pMesh->useVBO() ? pMesh->GetVBOSource():pMesh->GetVertexBuffer(), pMesh->GetnVtxStride()/sizeof(Float32),pMesh->GetVertexCount() );


	model->SetPosition(x, y, z);
	model->SetScale(1, 1, 1);
	model->SetMaterial(materialId);
	if (ppINode) *ppINode = model;

	Int32 id = AddNode(model, targetIndex, flag);
	OnCreateModelMesh(model);
	return id;

	return -1;
}

Int32 CSceneNode::ReleaseModel(
	/* [in] */ Int32 modelId)
{
	CNode* node = m_node.Get(modelId);
	IsolateNode(node);
	m_node.Delete(modelId);
	return XR_OK;
}

Int32 CSceneNode::RemoveModel(
	/* [in] */ Int32 modelId)
{
	CNode* model = m_node.Get(modelId);
	IsolateNode(model);
	return XR_OK;
}

Int32 CSceneNode::CreateSubdivision(
    /* [in] */ ModelType type,
	/* [in] */ Int32 materialId,
    /* [in] */ Int32 targetIndex,
    /* [in] */ InsertFlag flag,
	/* [in] */ Float32 sx,
    /* [in] */ Float32 sy,
    /* [in] */ Float32 sz,
    /* [in] */ Int32 dx,
	/* [in] */ Int32 dy,
	/* [in] */ Int32 dz,
	/* [out] */ class INode** ppINode)
{
	Region texCoord;

	CMaterial* pMtl = GetMaterialObject(materialId);
	CNode* model = new CNode(this);

	if (!model) return -1;
	if (type & ModelType_Internal) {
		model->GenSubdivision(sx, sy, sz, dx, dy, dz, ModelType_Plane, materialId);
	}

	if (ppINode) *ppINode = model;
	Int32 id = AddNode(model, targetIndex, flag);
	OnCreateModelMesh(model);
	return id;
}

xr_state CSceneNode::OnUpdate()
{
	UInt32 time = XrGetTime();
	UInt32 deltaTime = time - m_LastTime;
	m_LastTime = time;

	m_RenderGroupList.Clear();

	UpdateHierarchy();

 //   SceneTraverseInfo rs;
	//rs.Reset();
 //   CSceneVisitor visitor(this);
	//if (!m_pHead) return XR_OK;
 //   rs.node = m_pHead;
 //   VisitNode(&rs, &visitor, TRUE);

	m_skmgr.Update();

	return XR_OK;
}

Void CSceneNode::UpdateHierarchy()
{
	XRMat4 transform, rotation, translation;
	CNode* node = m_pHead;
	if (!node) return;
	
	while (node) {
		if (node->GetEnable()) {
			node->GetScalingMatrix(&transform);
			node->GetRotationMatrix(&rotation);
			node->GetTranslationMatrix(&translation);
			transform = translation * rotation * transform;
			if (node->isBone()) {
				node->m_globalTransform = transform;
			}
			AddMeshRender(node, &transform, node->GetInstancing(), node->GetInstancingCount());
			UpdateNode(node->GetSub(), &transform, node->GetInstancing(), node->GetInstancingCount());
		}
		node = node->GetNext();
	}
	

}
Void CSceneNode::UpdateNode(CNode* node, XRMat4* parentTransform, XRMat4* instancing, Int32 count)
{
	XRMat4 transform, rotation, translation;
	Float32 x,y,z;
	XRMat4* _instancing;
	Int32 _count;

	if (!node) return;
	
	while (node) {
		if (node->GetEnable()) {
			node->GetScalingMatrix(&transform);
			node->GetRotationMatrix(&rotation);
			node->GetTranslationMatrix(&translation);
			transform = (*parentTransform) * translation * rotation * transform;
			
			if (node->isBone()) {
				node->m_globalTransform = transform;
			}
			if (node->GetInstancingCount()) {
				_instancing = node->GetInstancing();
				_count = node->GetInstancingCount();
			}
			else {
				_instancing = instancing;
				_count = count;
			}

			AddMeshRender(node, &transform, _instancing, _count);
			UpdateNode(node->GetSub(), &transform, _instancing, _count);
		}
		node = node->GetNext();
	}
}

Void CSceneNode::VisitNode(
    /* [in] */ SceneTraverseInfo* traverseInfo,
    /* [in] */ CSceneVisitor* visitor,
    /* [in] */ Boolean visitSibling)
{
   SceneTraverseInfo rs = *traverseInfo;

    m_rs.Clean();

    if (visitSibling) {
        m_rs.Push(rs);
    }
    else {
        if (visitor->isNeedVisit(rs)) {
            visitor->visitNode(rs);
            if (visitor->isContinue()) {
                rs.node = rs.node->GetSub();
                if (rs.node) {
                    m_rs.Push(rs);
                }
            }
            else return;
        }
    }

    while (!m_rs.IsEmpty()) {
        m_rs.Pop(rs);

        if (rs.node->GetNext()) {
            CNode* currentModel = rs.node;
            rs.node = currentModel->GetNext();
            m_rs.Push(rs);
            rs.node = currentModel;
        }

        if (visitor->isNeedVisit(rs)) {
            visitor->visitNode(rs);
            if (visitor->isContinue()) {
                rs.node = rs.node->GetSub();
                if (rs.node) {
                    m_rs.Push(rs);
                }
            }
        }
    }

    return;
}

xr_state CSceneNode::AddMeshRender(CNode* node, XRMat4* transform, XRMat4* instancing, Int32 count)
{
	CBatchRender* pBatchRender;
	//CMesh* mesh = node->GetMesh();
	//if (!mesh) return XR_OK;
	//CMaterial* mtl = node->GetMaterial();
	//if (!mtl) return XR_OK;

	//if (node->selfScale) ApplyScalingMatrix(node->selfScale->x.Get(), node->selfScale->y.Get(),node->selfScale->z.Get(), &transform);
	//if (node->selfRotation) ApplyRotationMatrix(node->selfRotation->x.Get(), node->selfRotation->y.Get(),node->selfRotation->z.Get(), &transform);
	//transform = (*transformMatrix) * transform;

	//UInt32 num = 1;
	CDrawable* drawable=0;
	for(node->FirstDrawable(); !node->DrawableEnds(); node->NextDrawable())
	{
		drawable = node->GetCurrentDrawable();
		pBatchRender = m_renderPool.Get();
		pBatchRender->Reset();
		pBatchRender->SetOwner(this);
		pBatchRender->SetObjectInfo(node);
		pBatchRender->FetchMeshData(drawable->mesh);
		pBatchRender->SetDrawMode(node->GetDrawModeBits());
		pBatchRender->SetTransformMatrix(transform);
		pBatchRender->SetInstancingMatrix(instancing, count);
		m_RenderGroupList.AddBatchRender(drawable->mtl,pBatchRender);
	}
	return XR_OK;
	//ff
}

Int32 CSceneNode::CreateCamera(
	/* [in] */ Float32 fovx, 
	/* [in] */ Float32 aspect, 
	/* [in] */ Float32 znear, 
	/* [in] */ Float32 zfar,
	/* [out] */ ICamera** ppCamera)
{
	CCamera* camera = new CCamera();
	if (!camera) return -1;
	if (ppCamera) *ppCamera = camera;
	camera->SetPerspective(fovx, aspect, znear, zfar);
	return m_cams.Add(camera);
}

CCamera* CSceneNode::GetCamera()
{
	return m_cams.Get(m_camId);
}

xr_state CSceneNode::SetCamera(
	/* [in] */ Int32 camId)
{
	m_camId = camId;
	return XR_OK;
}

xr_state CSceneNode::OnRender(CRenderTargetEx* pRenderTarget)
{
	return CRenderNode::OnRender(pRenderTarget);
}

TouchPackage* CSceneNode::OnEvent(TouchPackage* package)
{
	return package;
}

Void CSceneNode::PreRender()
{
	CLight* light;
	for (m_lights.First();!m_lights.IsDone();m_lights.Next()) {
		light = m_lights.GetCurrent();
		light->SetRenderTarget();
		m_RenderGroupList.PreRender(m_renderPool, light, light->GetView(), light->GetProj());
		//light->RestoreRenderTarget();
	}
}

Int32 CSceneNode::CreateLight(
	/* [in] */ LightType type,
    /* [in] */ Int32 x,
	/* [in] */ Int32 y,
	/* [in] */ Int32 z,
    /* [in] */ Int32 vx,
	/* [in] */ Int32 vy,
	/* [in] */ Int32 vz,
	/* [out] */ class ILight** ppILight)
{
	CLight* light = new CLight();
	if (!light) return -1;
	light->Init(type);
	if (ppILight) *ppILight = light;
	light->SetPosition(x, y, z);
	light->SetOrientation(vx, vy, vz);
	return m_lights.Add(light);
}

xr_state CSceneNode::EnableLighting(
	/* [in] */ Boolean flag)
{
	m_enableLight = flag;
	return XR_OK;
}

xr_state CSceneNode::EnableShadowVolume(
	/* [in] */ Boolean flag)
{
	return XR_OK;
}

Void CSceneNode::PostRender()
{
	CLight* light;
	CCamera* cam = GetCamera();
	XRMat4 view = cam->GetViewMatrix();
	XRMat4 proj = cam->GetProjectionMatrix();
	for (m_lights.First();!m_lights.IsDone();m_lights.Next()) {
		light = m_lights.GetCurrent();
		light->Render(view, proj);
	}
}

Void CSceneNode::OnRenderFinish()
{
	CLight* light;
	m_cams.Get(m_camId)->SetNeedUpdate();
	for (m_lights.First();!m_lights.IsDone();m_lights.Next()) {
		light = m_lights.GetCurrent();
		light->SetNeedUpdate();
	}
}

Int32 CSceneNode::CreateBonePallete(BonePallete* pallete)
{
	return m_skmgr.AddBonePallete(pallete);
}

BonePallete* CSceneNode::GetBonePallete(Int32 id)
{
	return m_skmgr.GetBonePallete(id);
}
