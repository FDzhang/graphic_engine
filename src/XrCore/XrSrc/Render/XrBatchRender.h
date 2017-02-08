#ifndef __C_BATCH_RENDER_H__
#define __C_BATCH_RENDER_H__
#include "../Common/XrInternal.h"
#include "../Common/XRVector.h"
#include "XrRenderEffect.h"
class CMaterial;
//class CUIRenderList;


inline Void stateOverride(UInt32* dstPass, UInt32 srcPass)
{
	UInt32 drawStyle = srcPass & DrawMode_DrawStyle;
	*dstPass |= srcPass;
	if (drawStyle) {
		*dstPass &= ~DrawMode_DrawStyle;
		*dstPass |= drawStyle;
	}
}

class CBatchRender : public CBiLinkNode<CBatchRender>
{
public:
	CBatchRender();
	~CBatchRender();
	//Void SetProjInfo(const Float32* pProjInfo) { m_pProjInfo = pProjInfo; }
	Void SetDrawMode(UInt32 mode)
	{
		m_renderPass.drawModeOverride = mode;
	}
	virtual Void Render(CMaterial* pMtl);
	virtual Void PreRender(CMaterial* pMtl, const XRMat4* view, const XRMat4* proj);
	virtual Void Test(CMaterial* pMtl);
	Void DrawPass(UInt32 mode);
	Void Draw(UInt32 mode);
	Void ApplyModelTransform(TransformInfo* pTrans);
	virtual Boolean TryAddQuad(LayerTraverseInfo* info);
	virtual	Void UseMaterial(CMaterial* pMtl);
	Void AddQuad(Region* pPos, Region* pUV, Float32 z, Color* color);
	xr_state SetVertexStream(Float32* stream, Int32 size);
	xr_state SetIndexStream(Float32* stream, Int32 size);
	
	//xr_state SetVBO(Int32 vbo) { m_vbo = vbo; }
	//xr_state SetIBO(Int32 ibo) { m_ibo = ibo; }

	xr_state FetchMeshData(class CMesh* mesh);
	xr_state SetTransform2D(TransformInfo* transform);
	xr_state SetTransformMatrix(XRMat4* transform);
	xr_state SetInstancingMatrix(XRMat4* transform, Int32 count);
	Boolean InitInternalBuffer(Int32 vertexCount, Int32 vertexSize);

	XRMat4* GetModelMatrix();
	XRMat4* GetInstancingMatrix(Int32 batch);

	Void Reset() {
		m_vertexCount = 0;
		m_indexCount = 0;
		m_useTransform = FALSE;
		m_owner = 0;
		m_pVB = 0;
		m_pIB = 0;
		m_objData = 0;
		m_renderPass.Default();
		instancingTransformMatrix = 0;
		m_instancingCount = 0;
		//m_interleaved = 1;
	}

	Boolean NeedBlend() {
		return m_color.a<1.0;
	}

	class CRenderNode* GetOwner() { return m_owner; }
	Void SetOwner(class CRenderNode* owner) { m_owner = owner; }
	Void SetObjectInfo(class IObject* obj) { m_objData = obj; }
	Void BindVertexData();
	Void UnBindVertexData();

	//UInt32 GetuBatchIdx() const { return m_uBatchIdx; }
	IObject* GetObjData() { return m_objData; }

protected:
	Void BindInterleavedVertexData(Int32 VertexSize,Int32 VertexIndex,Boolean);
	Void BindElseVertexData(Int32 VertexSize,Int32 VertexIndex,Int32 VertexOffset,Boolean);

protected:

	Int32				m_vertexCount;
	Int32				m_indexCount;
	Color				m_color;
	//Float32			m_opacity;
	IObject* 			m_objData;
	Int32				m_currPos;
	Boolean				m_useTransform;
	Float32*			m_vertexDataInternal;
	UInt16*				m_indexDataInternal;
	Boolean				m_useInternal;
	Boolean				m_interleaved;
	Boolean				m_useIndex;
	class CVertexBuffer*		m_pVB;
	class CIndexBuffer*			m_pIB;
	class CVertexBuffer		    m_VBInternal;
	class CIndexBuffer			m_IBInternal;

	XRMat4				transformMatrix;
	XRMat4*				instancingTransformMatrix;
	XRVertexLayout		m_vertexLayout;
	RenderPass 		    m_renderPass;
	class CRenderNode*	m_owner;
	UInt32				m_instancingCount;
	CMesh*				m_pMesh;
};

#endif  //__C_BATCH_RENDER_H__

