#ifndef __C_RENDER_DEVICE_H__
#define __C_RENDER_DEVICE_H__
#include "CRenderTarget.h"
#include "CRenderState.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CUniformBlock.h"
#include "CShaderObject.h"
#include "CTexture.h"
#include "CSampler.h"

class CRenderDevice
{
public:
	CRenderDevice();
	xr_state Init();
	xr_state CreateRenderTargetFromSwapChain(class CSwapChain* pSwapChain, CRenderTarget* pRenderTarget);
	xr_state CreateRenderTarget(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth, CRenderTarget* pRenderTarget);
	xr_state CreateRenderTargetCube(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth, CRenderTarget* pRenderTarget);
	xr_state CreateAccessibleRenderTarget(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth, CRenderTarget* pRenderTarget);
	xr_state CreateRenderState(UInt32 state, CRenderState* pRenderState);
	xr_state CreateShaderFromFile(ConstString vtxName, ConstString frgName, CShaderObject* pShaderObject, XR_VERTEX_LAYOUT* desc=0, Int32 num=0, CVertexLayout* pLayout=0);
	xr_state CreateShaderFromMemory(ConstString vs, ConstString fs,  CShaderObject* pShaderObject, XR_VERTEX_LAYOUT* desc=0, Int32 num=0, CVertexLayout* pLayout=0);
	xr_state CreateTextureFromFile(ConstString fileName, CTexture* pTexture);
	xr_state CreateTexture(Void* pData, Int32 width, Int32 height, XRBufferFormat format, UInt32 mode, CTexture* pTexture, Int32 miplevel=1);
	xr_state UpdateTexture(Void* pData, CTexture* pTexture);
	xr_state CreateTextureCube(Void** pData, Int32 width, Int32 height, XRBufferFormat format, CTexture* pTexture);
	xr_state CreateVertexBuffer(Void* pBuffer, Int32 vertexSize, Int32 vertexNum, CVertexBuffer* ppVertexBuffer, XRBufferUsage usage = XR_BUFFER_STATIC);
	xr_state CreateIndexBuffer(Void* pBuffer, Int32 size, CIndexBuffer* ppIndexBuffer, XRBufferUsage usage = XR_BUFFER_STATIC);
	xr_state UpdateVertexBuffer(Void* pBuffer, CVertexBuffer* pVertexBuffer);
	xr_state UpdateIndexBuffer(Void* pBuffer, CIndexBuffer* pIndexBuffer);
	xr_state CreateUniformBlock(Int32 size, CUniformBlock* pUniformBlock);
    xr_state CreateVertexLayout(XR_VERTEX_LAYOUT* desc, Int32 num, CVertexLayout* pLayout, ConstString vs);
	xr_state CreateSampler(UInt32 mode, CSampler* pSampler);

private:
	friend bool XrCreateDeviceContextAndSwapChain(int width, int height, int context, class CRenderContext** ppCContext, class CRenderDevice** ppCDevice, class CSwapChain** ppCSwapChain, int type);

	//ID3D11Device*           m_pd3dDevice;
};

#endif  //__C_RENDER_DEVICE_H__
