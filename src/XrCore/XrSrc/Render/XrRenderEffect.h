#ifndef __CSHADEREFFECT_H__
#define __CSHADEREFFECT_H__
#include "../External/IRenderEffect.h"
#include "../Common/XrInternal.h"

class CXrRenderEffect : public IRenderEffect
{
public:
	CXrRenderEffect() {}
	virtual ~CXrRenderEffect() {}

	virtual xr_state InitShaderFromMemory(ConstString name, ConstString vs, ConstString ps, Int32 UBSize, XRVertexLayout layout, UInt32 renderState);
	virtual xr_state InitShaderFromFile(ConstString name, ConstString vs, ConstString ps, Int32 UBSize, XRVertexLayout layout, UInt32 renderState);
	//virtual xr_state InitShaderEx(String name, String vs, String ps, Int32 UBSize, Int32 UBSize2, XRVertexLayout layout, UInt32 renderState);
	//virtual xr_state InitShaderFromString(
	//	/* [in] */ String effectName, 
	//	/* [in] */ String vertexShader, 
	//	/* [in] */ String fragmentShader,
	//	/* [in] */ String* Attribs,
	//	/* [in] */ Int32 AttribsArraySize,
	//	/* [in] */ String* Uniforms,
	//	/* [in] */ Int32 UniformsArraySize,
	//	/* [in] */ String* Textures,
	//	/* [in] */ Int32 TextureArraySize);

	//virtual xr_state InitShaderFromFile(
	//	/* [in] */ String effectName, 
	//	/* [in] */ String vtxName, 
	//	/* [in] */ String frgName,
	//	/* [in] */ String* Attribs,
	//	/* [in] */ Int32 AttribsArraySize,
	//	/* [in] */ String* Uniforms,
	//	/* [in] */ Int32 UniformsArraySize,
	//	/* [in] */ String* Textures,
	//	/* [in] */ Int32 TextureArraySize);

	virtual xr_state GetEffectParam(
		/* [in] */ class CShaderObject** ppShader, 
		/* [in] */ class CUniformBlock** ppUB, 
		/* [in] */ class CRenderState** ppRS, 
		/* [in] */ class CVertexLayout** ppLayout);

	//virtual xr_state GetEffectParamEx(
	//	/* [in] */ class CShaderObject** ppShader, 
	//	/* [in] */ class CUniformBlock** ppUB, 
	//	/* [in] */ class CUniformBlock** ppUB2, 
	//	/* [in] */ class CRenderState** ppRS, 
	//	/* [in] */ class CVertexLayout** ppLayout);

	virtual xr_state SetRenderDelegate(IRenderDelegate* pDelegate);
	virtual IRenderDelegate* GetRenderDelegate() { return m_delegate; }
	//ShaderObject* GetShaderObject() { return m_shader; }
	CShaderObject* GetRenderDelegateContent(IRenderDelegate** ppDelegate) { if (ppDelegate) *ppDelegate = m_delegate; return m_pShader; }

	Void SetOpaque(Boolean opaque) {
		m_isOpaque = opaque;
	}
	bool IsBlendState(void);

	Boolean IsOpaque() {
		//return m_isOpaque;
		return !IsBlendState();
	}

protected:
	Int32					m_shaderId;
	IRenderDelegate*		m_delegate;
	CShaderObjectEx*		m_pShader;
	CRenderState            m_renderState;
	CVertexLayout*          m_pVertexLayout;
	Boolean					m_isOpaque;
};

#endif  //__CSHADEREFFECT_H__

