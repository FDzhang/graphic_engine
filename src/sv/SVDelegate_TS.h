#ifndef __SV_DELEGATE_TS_H__
#define __SV_DELEGATE_TS_H__

#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../XrCore/XrSrc/XrCore/CDeviceManager.h"

extern CRenderContext* g_pXrRenderContext;

struct SV2D_PARAM_TS
{
	XRMat4 myPMVMatrix;
};

class RenderDelegateSV2D_TS : public IRenderDelegate
{
public:
	RenderDelegateSV2D_TS() {}
	virtual ~RenderDelegateSV2D_TS() {}

	virtual Int32 OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject)
	{
		CShaderObject* pShader;
		CUniformBlock* pUB;
		CRenderState* pRS;
		CVertexLayout* pLayout;

		pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);
		pRS->Set(XR_BLEND_DEFAULT | XR_CULLMODE_NONE | XR_FRONTFACE_CCW);

		XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler());
		XRDM->context()->PSSetTexture(1, pMtl->GetSpecularMap(), XRDM->GetDefaultSampler());
		XRDM->context()->PSSetTexture(2, pMtl->GetAmbientMap(), XRDM->GetDefaultSampler());
		XRDM->context()->PSSetTexture(3, pMtl->GetNormalMap(), XRDM->GetDefaultSampler());
		XRDM->context()->PSSetTexture(4, pMtl->GetIrradianceMap(), XRDM->GetDefaultSampler());

		SV2D_PARAM_TS sv2D_param;
		g_pXrRenderContext->UpdateUniformBlock(pUB, &sv2D_param);
		g_pXrRenderContext->VSSetUniformBlock(0, pUB);

		return 0;
	}
};
#endif //__SV_DELEGATE_TS_H__
