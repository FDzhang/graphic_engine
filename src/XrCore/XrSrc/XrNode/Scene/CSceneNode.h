#ifndef __CRENDERNODESCENE_H__
#define __CRENDERNODESCENE_H__
#include "../../Common/XrInternal.h"
#include "../../External/ISceneNode.h"
#include "CSceneVisitor.h"
#include "../CNode.h"
#include "CRenderNode.h"
#include "CSkeletonManager.h"
#include "../../Render/XrBatchRender.h"

class CSceneNode:  public CRenderNode, public ISceneNode, public CXrTree<CNode>
{
public:
	CSceneNode() {
		m_type = RenderNodeType_3D;
		m_enableLight = FALSE;
		m_self = (Void*)this;
	}

	virtual ~CSceneNode();


    virtual Int32 CreateModel(
		/* [in] */ Int32 type,
		/* [in] */ Int32 materialId,
		/* [in] */ Int32 targetIndex,
		/* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
		/* [in] */ Float32 y,
		/* [in] */ Float32 z,
		/* [in] */ Float32 scale,
		/* [out] */ class INode** ppINode);

	virtual Int32 LoadNodeFromFile(
		/* [in] */ Int32 targetIndex,
		/* [in] */ InsertFlag flag,
		/* [in] */ ConstString fileName,
		/* [out] */INode** ppINode);

	virtual Int32 CreateNode(
		/* [in] */ Int32 targetIndex,
		/* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 z,
		/* [out] */ class INode** ppINode);

    virtual Int32 CreateMesh(
        /* [in] */ ModelType type,
		/* [in] */ Float32 dx,
		/* [in] */ Float32 dy,
		/* [in] */ Float32 dz,
		/* [in] */ String name,
		/* [out] */ class IMesh** ppIMesh);

	virtual Int32 CreateMaterial(
		/* [in] */ MaterialType materialType,
		/* [out] */ IMaterial** ppMtl=0);

	virtual Int32 CreateMaterialEx(
		/* [in] */ MaterialBlock* pDesc,
		/* [in] */ Int32 meshId,
		/* [out] */ IMaterial** ppMtl=0);

	virtual Int32 LoadModelFromFile(
        /* [in] */ String name,
		/* [in] */ Int32 materialId,
        /* [in] */ Int32 targetIndex,
        /* [in] */ InsertFlag flag,
		/* [in] */ Float32 x,
        /* [in] */ Float32 y,
        /* [in] */ Float32 z,
        /* [in] */ Float32 scale,
		/* [out] */ class INode** ppINode);

	virtual Int32 ReleaseModel(
		/* [in] */ Int32 modelId);

	virtual Int32 RemoveModel(
		/* [in] */ Int32 modelId);

    virtual Int32 CreateSubdivision(
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
		/* [out] */ class INode** ppINode);

	virtual Int32 CreateCamera(
	/* [in] */ Float32 fovx, 
	/* [in] */ Float32 aspect, 
	/* [in] */ Float32 znear, 
	/* [in] */ Float32 zfar,
	/* [out] */ ICamera** ppCamera);

	virtual xr_state SetCamera(
		/* [in] */ Int32 camId);	

	virtual CCamera* GetCamera();

	virtual Int32 CreateLight(
		/* [in] */ LightType type,
        /* [in] */ Int32 x,
		/* [in] */ Int32 y,
		/* [in] */ Int32 z,
	    /* [in] */ Int32 vx,
		/* [in] */ Int32 vy,
		/* [in] */ Int32 vz,
		/* [out] */ class ILight** ppILight);

    virtual xr_state EnableLighting(
		/* [in] */ Boolean flag);

	virtual xr_state EnableShadowVolume(
		/* [in] */ Boolean flag);

    virtual INode* FindNode(
	   /* [in] */ Int32 parentId,
	   /* [in] */ ConstString name);

	xr_state Init(Int32 width, Int32 height);
	xr_state Init(CRenderTargetEx* pRenderTarget);
	virtual xr_state OnUpdate();
	virtual TouchPackage* OnEvent(TouchPackage* package);
	virtual xr_state OnRender(CRenderTargetEx* pRenderTarget);
	virtual xr_state SetRenderTarget(class IRenderTarget* pIRenderTarget);
	virtual Void PostRender();

	virtual Int32 CreateMaterialFromRenderTarget(MaterialType materialType, Int32 rtId);

	/*CMaterial*  GetMaterial(Int32 index) {
		if (index<0) return 0;
		m_mtl.Get(index)->AddRef();
		return m_mtl.Get(index);
	}*/

	xr_state ReleaseMaterial(Int32 index);

	Int32 AddNode(CNode* model, Int32 targetIndex, InsertFlag flag);

	xr_state AddMeshRender(CNode* node, XRMat4* transform, XRMat4* instancing=0, Int32 count=0);
	
	xr_state OnCreateModelMesh(CNode* model);
	xr_state OnRemoveModelMesh(CNode* model);
	virtual Void OnRenderFinish();
	virtual Void PreRender();
	Int32 CreateBonePallete(BonePallete* pallete);
	BonePallete* GetBonePallete(Int32 id);

	Int32 AddNodeToSlot(CNode* node) {
		Int32 returnId = m_node.Add(node);
		node->SetSceneOwnerInfo(this, returnId);
		return returnId;
	}
private:

	Void UpdateHierarchy();
	Void UpdateNode(CNode* node, XRMat4* parentTransform, XRMat4* instancing=0, Int32 count=0);

	Void VisitNode(
    /* [in] */ SceneTraverseInfo* traverseInfo,
    /* [in] */ class CSceneVisitor* visitor,
    /* [in] */ Boolean visitSibling);

	CLayer* TestHit(TouchPackage* pPackage);
	
	CLazySlot<CNode, DefaultNumModel>		m_node;
	CStack<SceneTraverseInfo, MaxNumStack>  m_rs;				//layer rendering stack
	CLazySlot<CCamera, DefaultCameraNum>	m_cams;


	CSkeletonManager						m_skmgr;
	UInt32									m_camId;
	Boolean									m_enableLight;

	//CXrBiLinkList<CBatchRender>			m_renderQuene;		//render quene for blending primitive
};

#endif  //__CRENDERNODESCENE_H__

