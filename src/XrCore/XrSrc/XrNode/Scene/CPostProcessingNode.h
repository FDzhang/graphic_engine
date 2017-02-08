#ifndef __CRENDER_NODE_EFFECT_H__
#define __CRENDER_NODE_EFFECT_H__
#include "../../Common/XrInternal.h"
#include "../../External/IPostProcessingNode.h"
#include "../../Effect/PostProcessing.h"
#include "CRenderNode.h"

class CPostProcessingNode: public CRenderNode, public IPostProcessingNode
{
public:
	CPostProcessingNode() { m_type = RenderNodeType_PostProcessing; }
	virtual xr_state SetEnable(
		/* [in] */ Boolean flag);

	virtual ~CPostProcessingNode();
	xr_state Init();
	//xr_state SetEffect(RenderNodeType type);
	virtual xr_state OnUpdate();
	virtual TouchPackage* OnEvent(TouchPackage* package);
	virtual xr_state OnRender(CRenderTargetEx* pRenderTarget);
	//virtual xr_state SetRenderTarget(class IRenderTarget* pIRenderTarget);
	CRenderTargetEx* GetRenderTarget();

private:
	CHDRPostProcessing		m_effect;
	Void*					m_self;
};

#endif  //__CRENDER_NODE_EFFECT_H__

