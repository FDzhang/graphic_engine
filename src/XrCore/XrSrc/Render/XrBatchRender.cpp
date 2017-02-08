#include "XrBatchRender.h"
#include "../XrNode/Material/CMaterial.h"
#include "../XrNode/Layer/CLayer.h"
#include "../XrNode/Scene/CRenderNode.h"
#include "../XrNode/Mesh/CMesh.h"
#include "../External/IRenderDelegate.h"
//#include "CShaderObject.h"
//#include "ShaderLibrary.h"
//#include "GLUtility.h"
//#include "XrNode/Material/CMaterialex.h"
//#include "XrNode/Material/CMaterial.h"

float ProjId[16]={1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};

float VertexData[]={-1,1,0, 0,0,0, 0,1,   -1,-1,0, 0,0,0, 0,0,   1,-1,0, 0,0,0, 1,0,   1,1,0, 0,0,0, 1,1};

CBatchRender::CBatchRender():
	m_vertexCount(0),
	m_indexCount(0),
	m_useTransform(FALSE),
	m_objData(0),
	m_vertexDataInternal(0),
	m_indexDataInternal(0),
	m_useInternal(0),
	m_useIndex(FALSE),
	m_pVB(0),
	m_pIB(0),
	m_instancingCount(0),
	instancingTransformMatrix(0),
	m_pMesh(NULL)
{
	m_renderPass.Default();
	m_color.Set(0.0,0.0,0.0,1.0);
}

CBatchRender::~CBatchRender()
{
	if (m_useInternal) {
		m_VBInternal.Release();
		m_IBInternal.Release();
	}
}

Void CBatchRender::UseMaterial(CMaterial* pMtl)
{
	
}

Void CBatchRender::Test(CMaterial* pMtl)
{
}


Void CBatchRender::Draw(UInt32 mode)
{
	UInt32 indexCount;

	if (m_pIB) {
		XRDM->context()->SetIndexBuffer(m_pIB);
		if(m_pMesh)
		m_indexCount = m_pMesh->GetIndexCount();
		XRDM->context()->DrawIndexedPrimitive(m_indexCount,0,0);

	}
	else
	{
	    if(m_pMesh)
	    {
	        m_vertexCount=m_pMesh->GetVertexCount();
	    }
		XRDM->context()->DrawPrimitive(m_vertexCount, 0);
	}
}


Void CBatchRender::DrawPass(UInt32 mode)
{
}

XRMat4* CBatchRender::GetModelMatrix()
{
	if (m_useTransform) {
		return &transformMatrix;
	}
	else return 0;
}

XRMat4* CBatchRender::GetInstancingMatrix(Int32 batch)
{
	return &instancingTransformMatrix[batch];
}


Void CBatchRender::Render(CMaterial* pMtl)
{
	XrAssert(pMtl);
	static unsigned int cnt=0;
	unsigned int start, timestamp1,timestamp2,timestamp3,timestamp4,end,total=0;
    cnt++;
	IRenderDelegate* renderDelegate=0;
	pMtl->GetRender(&renderDelegate);
	if (!renderDelegate) return;
	//renderDelegate->SetBatchIndex(this->m_uBatchIdx);


	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	
	start = XrGetTime();
	pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);
	XRDM->context()->SetShaders(pShader);
	timestamp1 = XrGetTime();

	if (m_useInternal) {
		m_pVB = &m_VBInternal;
		m_pIB = &m_IBInternal;
		XRDM->context()->UpdateVertexBuffer(m_pVB, m_vertexDataInternal, m_vertexCount*8*4);
		XRDM->context()->UpdateIndexBuffer(m_pIB, m_indexDataInternal, m_indexCount*2);
	}
	XRDM->context()->SetVertexBuffer(0, m_pVB, pLayout);
	timestamp2 = XrGetTime();

	int ret = renderDelegate->OnRender(pMtl, GetModelMatrix(), &m_owner->GetCamera()->GetViewMatrix(), &m_owner->GetCamera()->GetProjectionMatrix(), m_owner->GetLight(), m_objData);
	timestamp3=XrGetTime();

	XRDM->context()->SetRenderState(pRS);
	timestamp4 = XrGetTime();

	if (!m_instancingCount) Draw(0);
	
	end = XrGetTime();
	for (Int32 i=0;i<m_instancingCount;i++) {
		XRMat4 trans = (*GetInstancingMatrix(i)) * (*GetModelMatrix());
		renderDelegate->OnRender(pMtl, &trans, &m_owner->GetCamera()->GetViewMatrix(), &m_owner->GetCamera()->GetProjectionMatrix(), m_owner->GetLight(), m_objData);
		Draw(0);
	}
	#if 0
	if(cnt%100 == 99&&1==pMtl->GetType())
    {
    xrprintf("\r\n SetShaders time=%d",timestamp1-start);
    xrprintf("\r\n UpdateVertexBuffer time=%d",timestamp2-timestamp1);	 
    xrprintf("\r\n OnRender time=%d",timestamp3-timestamp2);	 
    xrprintf("\r\n SetRenderState time=%d",timestamp4-timestamp3);	 
	
    xrprintf("\r\n Draw time=%d",end-timestamp4);
	xrprintf("\r\n m_instancingCount = %d",m_instancingCount);
	}	
	#endif
}

Void CBatchRender::PreRender(CMaterial* pMtl, const XRMat4* view, const XRMat4* proj)
{
	XrAssert(pMtl);

	IRenderDelegate* renderDelegate=0;
	pMtl->GetRender(&renderDelegate);
	if (!renderDelegate) return;
	//renderDelegate->SetBatchIndex(this->m_uBatchIdx);

	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);
	XRDM->context()->SetShaders(pShader);

	if (m_useInternal) {
		m_pVB = &m_VBInternal;
		m_pIB = &m_IBInternal;
		XRDM->context()->UpdateVertexBuffer(m_pVB, m_vertexDataInternal, m_vertexCount*8*4);
		XRDM->context()->UpdateIndexBuffer(m_pIB, m_indexDataInternal, m_indexCount*2);
	}
	XRDM->context()->SetVertexBuffer(0, m_pVB, pLayout);

	renderDelegate->OnRender(pMtl, GetModelMatrix(), view, proj, m_owner->GetLight(), m_objData);

	XRDM->context()->SetRenderState(pRS);

	if (!m_instancingCount) Draw(0);
	for (Int32 i=0;i<m_instancingCount;i++) {
		XRMat4 trans = (*GetInstancingMatrix(i)) * (*GetModelMatrix());
		if (renderDelegate->OnRender(pMtl, &trans, view, proj, m_owner->GetLight(), m_objData)>=0) Draw(0);
	}

}

inline void* GetGLDataPT(Boolean vbo, Float32* dataPT, Int32 offset)
{
	if (vbo) {
		return (void*)(4*offset);
	}
	else {
		return &dataPT[offset];
	}
}

inline void* GetGLDataSepPT(Boolean vbo, Float32* dataPT, Int32 offset)
{
	if (vbo) {
		return (void*)0;
	}
	else {
		return &dataPT[offset];
	}
}

Void CBatchRender::BindInterleavedVertexData(Int32 VertexSize,Int32 VertexIndex,Boolean UseVBO)
{

}

Void CBatchRender::BindElseVertexData(Int32 VertexSize,Int32 VertexIndex,Int32 VertexOffset,Boolean UseVBO)
{

}

Void CBatchRender::BindVertexData()
{
}

Void CBatchRender::UnBindVertexData()
{

}

Void CBatchRender::ApplyModelTransform(TransformInfo* pTrans)
{
	if (pTrans->sx != 1 || pTrans->sy != 1 || pTrans->sz != 1) {
		transformMatrix =  XRMat4::Scale(pTrans->sx, pTrans->sy, pTrans->sz);
	}
	else transformMatrix = XRMat4::Identity();
	
	transformMatrix *= XRMat4::Translation(pTrans->tx, pTrans->ty, pTrans->tz);

	if (pTrans->rx != 0) transformMatrix *= XRMat4::RotationX(pTrans->rx);
	if (pTrans->ry != 0) transformMatrix *= XRMat4::RotationY(pTrans->ry);
	if (pTrans->rz != 0) transformMatrix *= XRMat4::RotationZ(pTrans->rz);

	//transformMatrix = XRMat4::Translation(pTrans->tx, pTrans->ty, pTrans->tz) * XRMat4::RotationX(pTrans->rx) * XRMat4::RotationY(pTrans->ry) * XRMat4::RotationZ(pTrans->rz);
	//transformMatrix = XRMat4::Identity();
	
}

// 0----3
// |    |
// 1----2	
Boolean CBatchRender::TryAddQuad(LayerTraverseInfo* info)
{
	Region region;
	if (!InitInternalBuffer(UIVertexBlock, 8*sizeof(Float32))) return FALSE;
	Float32 x = info->x, y = info->y, z = info->z;
	CLayer* layer = info->layer;
	if (info->opacity == 0.0) return TRUE; //Need to Render
	if (layer->UseTransform()) {
		if (m_vertexCount==0) {
			m_useTransform = TRUE;
			TransformInfo trans;
			trans.tx = x;
			trans.ty = y;
			trans.tz = z;
			trans.rx = layer->rx.Get();
			trans.ry = layer->ry.Get();
			trans.rz = layer->rz.Get();
			ApplyModelTransform(&trans);
			x = 0;
			y = 0;
			z = 0;
		}
		else return FALSE;
	}
	else {
		if (m_useTransform) return FALSE;
	}
	region.left = x - layer->width.Get() * layer->GetAnchorX();
	region.top = y - layer->height.Get() * layer->GetAnchorY();
	region.right = region.left + layer->width.Get();
	region.bottom = region.top + layer->height.Get();

	Color color;
	color.Set(layer->r.Get(),layer->g.Get(),layer->b.Get(), info->opacity);

	if (m_vertexCount == 0) {
		m_pVB = 0;
		m_pIB =0;
		m_useIndex = TRUE;
		m_objData = layer;
		m_vertexLayout = XR_VERTEX_LAYOUT_PNT;
	}
	//else if (!(color==m_color)){
	//	return FALSE;
	//}
	Region* texCoord = layer->GetROI();
	
	if (!(layer->GetType() & LayerType_ComplexLayer)) {
		if (m_vertexCount+4>UIVertexBlock) return FALSE;
		AddQuad(&region, texCoord, z, &color);
	}
	else {
		Int32 vCount=0, iCount=0;
		if (m_vertexCount + layer->GetVertexCount()<UIVertexBlock) {
			layer->OnAddMesh(&m_vertexDataInternal[m_vertexCount*8], &m_indexDataInternal[m_indexCount], x, y, color.a,  &m_vertexCount, &m_indexCount);
		}
		else return FALSE;
	}
	return TRUE;
}

Void CBatchRender::AddQuad(Region* pPos, Region* pUV, Float32 z, Color* color)
{
	m_indexDataInternal[m_indexCount+0] = m_vertexCount + 0;
	m_indexDataInternal[m_indexCount+1] = m_vertexCount + 1;
	m_indexDataInternal[m_indexCount+2] = m_vertexCount + 2;
	m_indexDataInternal[m_indexCount+3] = m_vertexCount + 0;
	m_indexDataInternal[m_indexCount+4] = m_vertexCount + 2;
	m_indexDataInternal[m_indexCount+5] = m_vertexCount + 3;
	m_indexCount+=6;

	Int32 count = m_vertexCount;
	//0
	m_vertexDataInternal[count*8+0]=pPos->left;
	m_vertexDataInternal[count*8+1]=pPos->top;
	m_vertexDataInternal[count*8+2]=color->a;
	m_vertexDataInternal[count*8+3]=color->r;
	m_vertexDataInternal[count*8+4]=color->g;
	m_vertexDataInternal[count*8+5]=color->b;
	m_vertexDataInternal[count*8+6]=pUV->left;
	//m_vertexDataInternal[count*8+7]=1.0f - pUV->top;
	m_vertexDataInternal[count*8+7]=pUV->top;
	count+=1;

	//1
	m_vertexDataInternal[count*8+0]=pPos->left;
	m_vertexDataInternal[count*8+1]=pPos->bottom;
	m_vertexDataInternal[count*8+2]=color->a;
	m_vertexDataInternal[count*8+3]=color->r;
	m_vertexDataInternal[count*8+4]=color->g;
	m_vertexDataInternal[count*8+5]=color->b;
	m_vertexDataInternal[count*8+6]=pUV->left;
	//m_vertexDataInternal[count*8+7]=1.0f - pUV->bottom;
	m_vertexDataInternal[count*8+7]=pUV->bottom;
	count+=1;

	//2
	m_vertexDataInternal[count*8+0]=pPos->right;
	m_vertexDataInternal[count*8+1]=pPos->bottom;
	m_vertexDataInternal[count*8+2]=color->a;
	m_vertexDataInternal[count*8+3]=color->r;
	m_vertexDataInternal[count*8+4]=color->g;
	m_vertexDataInternal[count*8+5]=color->b;
	m_vertexDataInternal[count*8+6]=pUV->right;
	//m_vertexDataInternal[count*8+7]=1.0f - pUV->bottom;
	m_vertexDataInternal[count*8+7]=pUV->bottom;
	count+=1;

	//3
	m_vertexDataInternal[count*8+0]=pPos->right;
	m_vertexDataInternal[count*8+1]=pPos->top;
	m_vertexDataInternal[count*8+2]=color->a;
	m_vertexDataInternal[count*8+3]=color->r;
	m_vertexDataInternal[count*8+4]=color->g;
	m_vertexDataInternal[count*8+5]=color->b;
	m_vertexDataInternal[count*8+6]=pUV->right;
	//m_vertexDataInternal[count*8+7]=1.0f - pUV->top;
	m_vertexDataInternal[count*8+7]=pUV->top;
	count+=1;

	m_vertexCount+=4;

	//xrprint("Quad Append: vertex count = %d\n", m_vertexCount);
}

Boolean CBatchRender::InitInternalBuffer(Int32 vertexCount, Int32 vertexSize)
{
	if (m_useInternal) return TRUE;
	if (!m_vertexDataInternal) {
		m_vertexDataInternal = (Float32*)new char[(vertexCount+1)*vertexSize];
	}
	if (!m_vertexDataInternal) return FALSE;

	if (!m_indexDataInternal) {
		m_indexDataInternal = (UInt16*)new char[vertexCount*3];
	}
	if (!m_indexDataInternal) {
		delete[] m_vertexDataInternal;
		m_vertexDataInternal = 0;
		return FALSE;
	}
	XRDM->device()->CreateVertexBuffer(0, vertexSize, (vertexCount+1), &m_VBInternal, XR_BUFFER_DYNAMIC);
	XRDM->device()->CreateIndexBuffer(0, vertexCount*3, &m_IBInternal, XR_BUFFER_DYNAMIC);
	m_useInternal = TRUE;
	return TRUE;
}

xr_state CBatchRender::FetchMeshData(CMesh* mesh)
{
	if (m_useInternal) return XR_OK;

	m_vertexLayout = mesh->GetVertexLayout();

	m_pVB = mesh->GetVB();
	m_vertexCount = mesh->GetVertexCount();

	m_pIB = mesh->GetIB();
	m_indexCount = mesh->GetIndexCount();

	m_pMesh = mesh;
	return XR_OK;
}

xr_state CBatchRender::SetTransform2D(TransformInfo* transform)
{
	//trans = *transform;
	ApplyModelTransform(transform);
	m_useTransform = TRUE;
	return XR_OK;
}

xr_state CBatchRender::SetTransformMatrix(XRMat4* transform)
{
	m_useTransform = TRUE;
	transformMatrix = *transform;
	//transformMatrix.transpose();
	return XR_OK;
}

xr_state CBatchRender::SetInstancingMatrix(XRMat4* instancing, Int32 count)
{
	instancingTransformMatrix = instancing;
	m_instancingCount = count;
	return XR_OK;
}
