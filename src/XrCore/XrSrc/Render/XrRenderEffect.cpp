
#include "XrRenderEffect.h"
#include "../Common/XrInternal.h"
#include "../XrCore/CDeviceManager.h"
xr_state CXrRenderEffect::InitShaderFromMemory(ConstString name, ConstString vs, ConstString ps, Int32 UBSize, XRVertexLayout layout, UInt32 renderState)
{
	XRDM->QueryShaderProgram(name, &m_pShader);

	if (!m_pShader->isInitialized) {
		XRDM->device()->CreateShaderFromMemory(vs, ps, m_pShader);
		XRDM->device()->CreateUniformBlock(UBSize, &m_pShader->ub);
	}
	XRDM->device()->CreateRenderState(renderState, &m_renderState);
	m_pVertexLayout = XRDM->GetVertexLayout(layout);
	return XR_OK;
}

xr_state CXrRenderEffect::InitShaderFromFile(ConstString name, ConstString vs, ConstString ps, Int32 UBSize, XRVertexLayout layout, UInt32 renderState)
{
	XRDM->QueryShaderProgram(name, &m_pShader);

	if (!m_pShader->isInitialized) {
		XRDM->device()->CreateShaderFromFile(vs, ps, m_pShader);
		XRDM->device()->CreateUniformBlock(UBSize, &m_pShader->ub);
	}
	XRDM->device()->CreateRenderState(renderState, &m_renderState);
	m_pVertexLayout = XRDM->GetVertexLayout(layout);
	return XR_OK;
}

bool CXrRenderEffect::IsBlendState(void)
{
    //printf("\r\n blend flag called ,m_renderState.Get()=0x%x",m_renderState.Get()&XR_BLEND_BITS);
	return m_renderState.Get()&XR_BLEND_BITS;
}
//xr_state CXrRenderEffect::InitShaderEx(String name, String vs, String ps, Int32 UBSize, Int32 UBSize2, XRVertexLayout layout, UInt32 renderState)
//{
//	XRDM->QueryShaderProgram(name, &m_pShader);
//
//	if (!m_pShader->isInitialized) {
//		XRDM->device()->CreateShaderFromMemory(vs, ps, m_pShader);
//		XRDM->device()->CreateRenderState(renderState, &m_pShader->renderState);
//		XRDM->device()->CreateUniformBlock(UBSize, &m_pShader->ub);
//		XRDM->device()->CreateUniformBlock(UBSize2, &m_pShader->ub2);
//	}
//	m_pVertexLayout = XRDM->GetVertexLayout(layout);
//	return XR_OK;
//}

xr_state CXrRenderEffect::SetRenderDelegate(IRenderDelegate* pDelegate)
{
	m_delegate = pDelegate;
	return XR_OK;
}

xr_state CXrRenderEffect::GetEffectParam(
	/* [in] */ class CShaderObject** ppShader, 
	/* [in] */ class CUniformBlock** ppUB, 
	/* [in] */ class CRenderState** ppRS, 
	/* [in] */ class CVertexLayout** ppLayout)
{
	*ppShader = m_pShader;
	*ppUB = &m_pShader->ub;
	*ppRS = &m_renderState;
	*ppLayout = m_pVertexLayout;
	return XR_OK;
}
//	xr_state CXrRenderEffect::GetEffectParamEx(
//	/* [in] */ class CShaderObject** ppShader, 
//	/* [in] */ class CUniformBlock** ppUB, 
//	/* [in] */ class CUniformBlock** ppUB2, 
//	/* [in] */ class CRenderState** ppRS, 
//	/* [in] */ class CVertexLayout** ppLayout)
//{
//	*ppShader = m_pShader;
//	*ppUB = &m_pShader->ub;
//	*ppUB2 = &m_pShader->ub2;
//	*ppRS = &m_pShader->renderState;
//	*ppLayout = m_pVertexLayout;
//	return XR_OK;
//}