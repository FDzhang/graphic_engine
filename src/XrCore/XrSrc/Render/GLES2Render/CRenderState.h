#ifndef __C_RENDER_STATE_H__
#define __C_RENDER_STATE_H__

#include "utilityGLES2.h"
#include "CVertexLayout.h"
#include "CShaderObject.h"
#include "CSampler.h"
#include "CTexture.h"
#include "CUniformBlock.h"

class CRenderState
{
public:
	CRenderState()
	{
		m_state = 0;
	}

	Void Set(UInt32 state) {
		m_state = state;
	}
	
	UInt32 Get() {
		return m_state;
	}
private:
	friend class CRenderDevice;
	friend class CRenderContext;
	//ID3D11DepthStencilState* m_pDX11depthStencilState;
	//ID3D11RasterizerState* m_pDX11RasterizerState;
	//ID3D11BlendState*	m_pDX11BlendState;
	UInt32 m_state;
	//UInt32 m_sref;
};

#endif  //__C_RENDER_STATE_H__
