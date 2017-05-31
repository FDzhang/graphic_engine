#include "CRenderManager.h"
#include "../XrNode/Material/CMaterial.h"
#include "../XrNode/Layer/CLayer.h"
#include "../XrNode/Scene/CRenderNode.h"
#include "../XrNode/Mesh/CMesh.h"
#include "../External/IRenderDelegate.h"
#include "../Effect/DefaultRenderDelegate.h"

CRenderManager::CRenderManager():
	m_useDeferredRendering(0),
	m_gbuffer(0),
	m_lightbuffer(0)
{

}

CXrRenderEffect* CRenderManager::CreateEffect(MaterialType mtlType)
{
	IRenderDelegate* renderDelegate;

	CXrRenderEffect* pEffect= new CXrRenderEffect;
	if (!pEffect) return 0;
	switch (mtlType) {
		case Material_UI_Spirit:
		case Material_UI_Glow:
		case Material_UI_Shadow:
			pEffect->SetOpaque(FALSE);
			renderDelegate = new RenderDelegate_Basic();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(UI_Spirit));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_UI_Font:
			pEffect->SetOpaque(FALSE);
			renderDelegate = new RenderDelegate_UI_Font();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(UI_Font));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		//case Material_UI_Spirit_With_Mask:
		//	pEffect->SetOpaque(FALSE);
		//	renderDelegate = new RenderDelegate_Basic();
		//	if (!renderDelegate) return 0;
		//	pEffect->InitShaderFromMemory(ShaderSource2Param(UI_Spirit_With_Mask));
		//	pEffect->SetRenderDelegate(renderDelegate);
		//	break;
		//case Material_Video:
		//	pEffect->SetOpaque(TRUE);
		//	renderDelegate = new RenderDelegate_Basic();
		//	if (!renderDelegate) return 0;
		//	pEffect->InitShaderFromMemory(UI_Video_FX, UI_Video_FX, UI_Video_CB);
		//	pEffect->SetRenderDelegate(renderDelegate);
		//	break;
		//case Material_DynMsk:
		//	pEffect->SetOpaque(FALSE);
		//	renderDelegate = new RenderDelegate_DynMsk();
		//	if (!renderDelegate) return 0;
		//	pEffect->InitShaderFromMemory(Shader_UI_DYN_Mask);
		//	pEffect->SetRenderDelegate(renderDelegate);
		//	break;
		case Material_Glossy:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_FrGlossy();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_Glossy));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Glossy_Color:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_FrGlossyColor();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_GlossyColor));
			pEffect->SetRenderDelegate(renderDelegate);
			break;			
		case Material_Glass:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_FrGlass();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_Glass));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Glass_Alpha:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_FrGlassAlpha();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_Glass_Alpha));
			pEffect->SetRenderDelegate(renderDelegate);
			break;			
		case Material_Refract:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_FrObject();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_FrObject));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Reflect:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_FlObject();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_FlObject));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_SkyBox:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_SkyBox();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_SkyBox));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Rigid_Texture:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Rigid_Texture();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_RigidTexture));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_RigidColor_Texture:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_RigidColor_Texture();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_RigidColorTexture));
			pEffect->SetRenderDelegate(renderDelegate);
		break;
		case Material_RigidVideo_Texture:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Rigid_Texture();
			
			// buffer file %s,line %d",__FILE__,__LINE__);
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_RigidVideoTexture));
			pEffect->SetRenderDelegate(renderDelegate);
			break;			
		case Material_Rigid_Blend:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Rigid_Blend();
			
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_RigidBlend));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Color_Plot:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Color_Plot();
			
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_ColorPlot));
			pEffect->SetRenderDelegate(renderDelegate);
			break;			
		case Material_Dynamic_Blend:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Dynamic_Blend();
			
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_DynamicBlend));
			pEffect->SetRenderDelegate(renderDelegate);
			break;			
		case Material_Skinned_Texture:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Skinned_Texture();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_SkinnedTexture));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Rigid_Bump:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Rigid_Bump();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_RigidBump));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Skinned_Bump:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Skinned_Bump();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(FR_SkinnedBump));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Shadow:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Shadow();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(Pre_Shadow));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		case Material_Shadow_Skinned:
			pEffect->SetOpaque(TRUE);
			renderDelegate = new RenderDelegate_Shadow_Skinned();
			if (!renderDelegate) return 0;
			pEffect->InitShaderFromMemory(ShaderSource2Param(Pre_Shadow_Skinned));
			pEffect->SetRenderDelegate(renderDelegate);
			break;
		//case Material_Simple_Video:
		//	pEffect->SetOpaque(TRUE);
		//	renderDelegate = new RenderDelegate_Simple_Texture();
		//	if (!renderDelegate) return 0;
		//	pEffect->InitShaderFromMemory(Shader_Simple_Video);
		//	pEffect->SetRenderDelegate(renderDelegate);
		//	break;
		//case Material_Simple_Video_Mask:
		//	pEffect->SetOpaque(FALSE);
		//	renderDelegate = new RenderDelegate_Simple_Texture();
		//	if (!renderDelegate) return 0;
		//	pEffect->InitShaderFromMemory(Shader_Simple_Video_Mask);
		//	pEffect->SetRenderDelegate(renderDelegate);
		//	break;
		default:
			break;
	}
	return pEffect;
}

xr_state CRenderManager::InitDeferredRender()
{
	SAFE_DELETE(m_gbuffer);
	SAFE_DELETE(m_lightbuffer);

	//XRDM->device()->CreateRenderTarget(XrGetScreenWidth(),
	return XR_OK;
}

xr_state CRenderManager::InitForwardRender()
{
	SAFE_DELETE(m_gbuffer);
	SAFE_DELETE(m_lightbuffer);

	return XR_OK;
}
