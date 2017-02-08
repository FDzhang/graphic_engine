#ifndef __C_RENDER_MANAGER_H__
#define __C_RENDER_MANAGER_H__
#include "../Common/XrInternal.h"
#include "../Common/XRVector.h"
#include "XrRenderEffect.h"
#include "../XrCore/CDeviceManager.h"

class CMaterial;
//class CUIRenderList;

class CRenderManager
{
public:
	CRenderManager();
	~CRenderManager() {}

	Void Reset() {

	}

	Boolean isDeferredRendering()
	{
		return m_useDeferredRendering;
	}

	Void SetUseDeferredRendering(Boolean flag) {
		m_useDeferredRendering = flag;
		if (flag) InitDeferredRender();
		else InitForwardRender();
	}

	CXrRenderEffect* CreateEffect(MaterialType mtlType);

	CRenderTargetEx* GetFrameBuffer() { return &m_framebuffer; }

	xr_state InitDeferredRender();
	xr_state InitForwardRender();

protected:
	CRenderTargetEx		m_framebuffer;
	CRenderTargetEx*	m_gbuffer;
	CRenderTargetEx*	m_lightbuffer;
	Boolean				m_useDeferredRendering;
	//CLazySlot
};

#endif  //__C_BATCH_RENDER_H__

