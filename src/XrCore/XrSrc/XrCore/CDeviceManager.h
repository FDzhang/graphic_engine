#ifndef __CDEVICEMANGER_H__
#define __CDEVICEMANGER_H__
#include "../XrNode/Material/CMaterial.h"
#include "../External/IDeviceManager.h"
#include "../External/ITextureDelegate.h"
#include "../Render/XrRender.h"
#include "../External/IRenderTarget.h"

class IMaterialEx;
class CMaterialEx;
class CMaterial;
class IVertexProgram;
class CVertexProgram;
class IFragmentProgram;
class CFragmentProgram;


class CRenderTargetEx : public IRenderTarget
{
public:
	virtual Void GetSize(
		/* [out] */ Int32* width, 
		/* [out] */ Int32* height)
	{
		*width = m_rt.GetWidth();
		*height = m_rt.GetHeight();
	}

	Int32 GetWidth() {
		return m_rt.GetWidth();
	}

	Int32 GetHeight() {
		return m_rt.GetHeight();
	}

	virtual Int32 GetId() { return 0;}

	CTexture* GetRenderTexture()
	{
		return m_rt.GetRenderTexture();
	}

	virtual Int32 GetTextureId()
	{
		return m_rt.GetRenderTexture()->m_id;
	}
	unsigned int m_id;
	CRenderTarget m_rt;
};


class CDeviceManager : public IDeviceManager
{
public:
    CDeviceManager();
    ~CDeviceManager();

    //virtual xr_state Initialize();
	Int32 CreateTextureFromFile(ConstString fileName, UInt32 type);
	virtual Int32 CreateTexture(Void* pData, Int32 width, Int32 height, XRBufferFormat format, UInt32 mode = XR_SAMPLER_CLAMP | XR_SAMPLER_LINEAR, Int32 miplevel=6);
	virtual Int32 CreateStreamingTexture(Int32 width, Int32 height, XRBufferFormat format, ITextureDelegate* pDelegate);
	Int32 CreateSharedTexture(ConstString nameId, Int32 width, Int32 height, XRBufferFormat format, UInt32 mode = XR_SAMPLER_CLAMP | XR_SAMPLER_LINEAR, CXrTextureEx** ppTex=0, Boolean* isExist=0);
	CXrTextureEx* AquireTexture(Int32 id);
	xr_state UpdateTexture(Void* pData, CTexture* pTexture);
	virtual xr_state ReleaseTexture(Int32 id);

	Int32 QueryShaderProgram(ConstString name, CShaderObjectEx** ppShaderObject);
	xr_state ReleaseShaderProgram(Int32 id);
	xr_state RegisterShaderProgram(Int32 id, CShaderObjectEx* pShaderObject);
	CShaderObjectEx* GetShaderProgramById(Int32 id);

	void GetDeviceContextAndSwapChain(CRenderContext** ppCContext, CRenderDevice** ppCDevice, CSwapChain** ppCSwapChain)
	{
		*ppCContext = m_renderContext;
		*ppCDevice = m_renderDevice;
		*ppCSwapChain = m_swapChain;
	}
	Int32 CreateMaterial(
		/* [in] */ MaterialType materialType,
		/* [out] */ IMaterial** ppMtl);

	CMaterial* AquireMaterial(Int32 idx);


	 virtual Int32 CreateRenderTarget(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth,
     /* [out] */ IRenderTarget** ppIRenderTarget=0);


	CRenderContext* context() { return m_renderContext; }
	CRenderDevice* device() { return m_renderDevice; }
	
	void Init();
    CVertexLayout* GetVertexLayout(XRVertexLayout layout);
	CSampler* GetDefaultSampler(XRSamplerMode mode=XR_SAMPLER_CLAMP) { return &m_samplers[mode]; }
	CSampler* GetDefaultDepthSampler(XRSamplerMode mode=XRSamplerMode(XR_SAMPLER_BORDER+1)) { return &m_samplers[mode]; }
private:
	friend class CXrCore;
	Boolean QueryTexFileByString(ConstString wsName, Int32* slotId);
	Int32 GetTexAdjacentSlot(Int32 id);

	Boolean QueryShaderByString(ConstString wsName, Int32* slotId);
	Int32 GetShaderAdjacentSlot(Int32 id);

	CXrTextureEx			m_tex[TexHashTableNum];
	CShaderObjectEx			m_shader[ShaderHashTableNum];
	CVertexLayout			m_layout[8];
	CSampler				m_samplers[5];
	CLazySlot<CMaterial, DefaultNumMaterail> m_Mtls;
	CLazySlot<CMaterial, DefaultNumMesh> m_Meshes;
	CLazySlot<CRenderTargetEx, DefaultNumRenderTarget>			m_renderTarget;
	CSwapChain* m_swapChain;
	CRenderDevice* m_renderDevice;
	CRenderContext* m_renderContext;
};


#endif  //__CDEVICEMANGER_H__
