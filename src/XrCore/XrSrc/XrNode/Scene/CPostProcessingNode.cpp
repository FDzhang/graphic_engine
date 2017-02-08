#include "CPostProcessingNode.h"
#include "../../Common/xrDataStruct.cpp"
#include "../../XrCore/CDeviceManager.h"
#include "../../XrCore/CXrCore.h"
#include "../../Render/XrRender.h"
#include "../../3rd/XrFileLoader.h"
#include "../CNode.h"

CPostProcessingNode::~CPostProcessingNode()
{
}

xr_state CPostProcessingNode::Init()
{	
	m_effect.init(GetScreenWidth(),GetScreenHeight());
	return XR_OK;
}

xr_state CPostProcessingNode::SetEnable(
		/* [in] */ Boolean flag)
{
	m_enable = flag;
	return XR_OK;
}

CRenderTargetEx* CPostProcessingNode::GetRenderTarget()
{
	return m_effect.GetSceneBuffer();
}

xr_state CPostProcessingNode::OnRender(CRenderTargetEx* pRenderTarget)
{
	m_effect.render(&pRenderTarget->m_rt);
	//if (m_pRenderTarget) m_pRenderTarget->Bind();
	//m_render->Render(m_effectMtl);
	//m_renderPool.Release(m_render);
	return XR_OK;
}

xr_state CPostProcessingNode::OnUpdate()
{
	return XR_OK;
}

TouchPackage* CPostProcessingNode::OnEvent(TouchPackage* package)
{
	//m_delegate->OnEvent(package->x, package->y, package->touchEvent);
	return package;
}
