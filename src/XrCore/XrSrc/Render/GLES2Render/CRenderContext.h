#ifndef __C_RENDER_CONTEXT_H__
#define __C_RENDER_CONTEXT_H__

#include "CVertexLayout.h"
#include "CShaderObject.h"
#include "CRenderState.h"
#include "CSampler.h"
#include "CTexture.h"
#include "CUniformBlock.h"

class CRenderContext
{
public:
	CRenderContext();
	xr_state SetRenderTarget(class CRenderTarget* pRenderTarget, Region* reg=0);
	xr_state SetRenderState(CRenderState* pRenderState);
	Void SetShaders(class CShaderObject* pShaders);
	Void SetViewport(Int32 x, Int32 y, Int32 width, Int32 height);
	Void SetViewport(Region* reg);
	Void SetVertexLayout(CVertexLayout* layout);
	Void DisableVertexLayout(CVertexLayout* layout);
	xr_state SetPrimitiveType(XRPrimitiveType type);
	xr_state SetDepthRange(Float32 zNear, Float32 zFar);
	xr_state SetVertexBuffer(Int32 index, class CVertexBuffer* pVertexBuffer, CVertexLayout* layout);
	xr_state SetIndexBuffer(class CIndexBuffer* pIndexBuffer);
	xr_state UpdateVertexBuffer(CVertexBuffer* pVertexBuffer, Void* pData, Int32 size);
	xr_state UpdateIndexBuffer(CIndexBuffer* pIndexBuffer, Void* pData, Int32 size);
	Void ClearRenderTarget(Float32 r, Float32 g, Float32 b, Float32 a);
	Void ClearDepthStencil(Float32 depth, UInt8 stencil);
	Void ClearDepthStencil();
	Void SetColorMask(Boolean r, Boolean g, Boolean b, Boolean a);
	xr_state PSSetTexture(Int32 index, class CTexture* pTexture, CSampler* pSampler);
	xr_state VSSetTexture(Int32 index, class CTexture* pTexture, CSampler* pSampler);
	xr_state VSSetUniformBlock(Int32 index, CUniformBlock* pBlock);
	xr_state PSSetUniformBlock(Int32 index, CUniformBlock* pBlock);
	xr_state UpdateUniformBlock(CUniformBlock* pBlock, Void* pData, Int32 offset=0, Int32 size=0);
	xr_state PSDisableUniformBlock(Int32 index);
	xr_state LockRenderedData(class CRenderTarget* pRenderTarget, void** pData, int* rowPitch=0, int* colPitch=0);
	xr_state UnlockRenderedData(class CRenderTarget* pRenderTarget);
	Void DrawPrimitive(Int32 count, Int32 offset);
	Void DrawIndexedPrimitive(Int32 count, Int32 indexOffset, Int32 vertexOffset);
	Void* LockUniformBlock(CUniformBlock* pBlock);
	Void UnlockUniformBlock(CUniformBlock* pBlock);

	friend bool XrCreateDeviceContextAndSwapChain(int width, int height, int context, class CRenderContext** ppCContext, class CRenderDevice** ppCDevice, class CSwapChain** ppCSwapChain, int type);

private:
	Void SetDefaultSampler();
	//CVertexLayout*				    m_pVertexLayout;
	CRenderTarget*					m_pRenderTarget;
	Float32							m_zNear;
	Float32							m_zFar;
	//ID3D11DeviceContext*			m_pImmediateContext;
	UInt32							m_primitiveTopology;
	CSampler*						m_pDefaultSampler;
};

CShaderObject* GetCurrentShader();

#endif  //__C_RENDER_CONTEXT_H__
