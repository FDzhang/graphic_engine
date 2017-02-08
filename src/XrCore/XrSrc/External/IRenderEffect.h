#ifndef __I_RENDER_EFFECT_H__
#define __I_RENDER_EFFECT_H__
#include "xrIntrinsic.h"

class IRenderEffect
{
public:
	virtual xr_state InitShaderFromMemory(
		/* [in] */ ConstString name,
		/* [in] */ ConstString vs,
		/* [in] */ ConstString ps,
		/* [in] */ Int32 UBSize,
		/* [in] */ XRVertexLayout layout,
		/* [in] */ UInt32 renderState)=0;

	virtual xr_state InitShaderFromFile(
		/* [in] */ ConstString name,
		/* [in] */ ConstString vs,
		/* [in] */ ConstString ps,
		/* [in] */ Int32 UBSize,
		/* [in] */ XRVertexLayout layout,
		/* [in] */ UInt32 renderState)=0;

	//virtual xr_state InitShaderFromString(
	//	/* [in] */ String effectName, 
	//	/* [in] */ String vertexShader, 
	//	/* [in] */ String fragmentShader,
	//	/* [in] */ String* Attribs,
	//	/* [in] */ Int32 AttribsArraySize,
	//	/* [in] */ String* Uniforms,
	//	/* [in] */ Int32 UniformsArraySize,
	//	/* [in] */ String* Textures,
	//	/* [in] */ Int32 TextureArraySize)=0;

	//virtual xr_state InitShaderFromFile(
	//	/* [in] */ String effectName, 
	//	/* [in] */ String vtxName, 
	//	/* [in] */ String frgName,
	//	/* [in] */ String* Attribs,
	//	/* [in] */ Int32 AttribsArraySize,
	//	/* [in] */ String* Uniforms,
	//	/* [in] */ Int32 UniformsArraySize,
	//	/* [in] */ String* Textures,
	//	/* [in] */ Int32 TextureArraySize)=0;

	virtual xr_state GetEffectParam(
		/* [in] */ class CShaderObject** ppShader, 
		/* [in] */ class CUniformBlock** ppUB, 
		/* [in] */ class CRenderState** ppRS, 
		/* [in] */ class CVertexLayout** ppLayout)=0;

	//virtual xr_state GetEffectParamEx(
	//	/* [in] */ class CShaderObject** ppShader, 
	//	/* [in] */ class CUniformBlock** ppUB, 
	//	/* [in] */ class CUniformBlock** ppUB2, 
	//	/* [in] */ class CRenderState** ppRS, 
	//	/* [in] */ class CVertexLayout** ppLayout)=0;

	virtual xr_state SetRenderDelegate(class IRenderDelegate* pDelegate)=0;
	//virtual struct ShaderObject* GetShaderObject()=0;
	//virtual Int32 RenderDelegate(class IMaterial* pMtl, struct TransformInfo* pTrans, const Float32* pViewMatrix, const Float32* pProjMatrix, Float32 opacity)=0; 
};	

#endif  //__I_RENDER_EFFECT_H__
