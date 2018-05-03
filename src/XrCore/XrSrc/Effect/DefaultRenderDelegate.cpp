#include "DefaultRenderDelegate.h"
#include "../Render/XrRender.h"
#include "../External/IMaterial.h"
#include "../XrNode/CNode.h"
#include "../XrNode/Scene/CSceneNode.h"
#include "RenderingUtility.h"
#include "../XrCore/CDeviceManager.h"

#define fRIR 4.0f

#define AMB  0.3f
#define DIF   0.5f
#define SPC   0.4f

//#define AMB  0.1f
//#define DIF   0.9f
//#define SPC   0.4f

float g_AmbientColor[3] = {AMB, AMB, AMB};
//float g_AmbientColor[3] = {0.0f, 0.0f, 0.0f};
float g_DiffuseColor[3] = {DIF, DIF, DIF};
float g_SpecularColor[3] = {SPC, SPC, SPC};
float g_MaterialColor[3]= {1.0,1.0,1.0}; 
float g_MaterialAlpha=0.5;
float g_TextureStep=0.2;

Int32 RenderDelegate_Basic::OnRender(
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
	//XRDM->context()->SetShaders(pShader);
	//XRDM->context()->SetRenderState(pRS);
	//XRDM->context()->SetVertexLayout(pLayout);
	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	if (pMtl->GetType() & Material_Mask) {
		XRDM->context()->PSSetTexture(1, pMtl->GetTransparencyMap(), XRDM->GetDefaultSampler());
	}

	if (pModelMatrix) {
		UI_Spirit_CB cb;
		cb.TransformMatrix = (*pProjMatrix)*(*pModelMatrix);
		XRDM->context()->UpdateUniformBlock(pUB, &cb);
		XRDM->context()->VSSetUniformBlock(0, pUB);
	}
	else {
		XRDM->context()->UpdateUniformBlock(pUB, (void*)pProjMatrix) ;
		XRDM->context()->VSSetUniformBlock(0, pUB);
	}
	return 1;
}

Int32 RenderDelegate_UI_Font::OnRender(
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

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 

	if (pModelMatrix) {
		UI_Spirit_CB cb;
		cb.TransformMatrix = (*pProjMatrix)* (*pModelMatrix);
		XRDM->context()->UpdateUniformBlock(pUB, &cb);
		XRDM->context()->VSSetUniformBlock(0, pUB);
	}
	else {
		XRDM->context()->UpdateUniformBlock(pUB, (void*)pProjMatrix);
		XRDM->context()->VSSetUniformBlock(0, pUB);
	}
	return 0;
}

Int32 RenderDelegate_Rigid_Texture::OnRender(
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
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 

	FR_RigidTexture_CB cb;
	cb.TransformMatrix = (*pProjMatrix)* (* pViewMatrix)*(*pModelMatrix);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}
Int32 RenderDelegate_RigidColor_Texture::OnRender(
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
	float Ambientcolor[4];
	pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	
	XRDM->context()->PSSetTexture(1, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 
	pMtl->GetAmbientColor(&Ambientcolor[0],&Ambientcolor[1],&Ambientcolor[2],&Ambientcolor[3]);

	FR_RigidColorTexture_CB cb;
	cb.TransformMatrix = (*pProjMatrix)* (* pViewMatrix)*(*pModelMatrix);
	cb.InTexColor.Set(Ambientcolor[0],Ambientcolor[1],Ambientcolor[2],Ambientcolor[3]);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}

Int32 RenderDelegate_Rigid_Blend::OnRender(
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
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 

	FR_RigidBlend_CB cb;
	cb.TransformMatrix = (*pProjMatrix)* (* pViewMatrix)*(*pModelMatrix);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}
Int32 RenderDelegate_Color_Plot::OnRender(
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
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();
	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 

	FR_ColorPlot_CB cb;
	cb.TransformMatrix = (*pProjMatrix)* (* pViewMatrix)*(*pModelMatrix);
	
	Float32 color[4]={1.0,1.0,1.0,1.0};
	pMtl->GetAmbientColor(&color[0],&color[1],&color[2],&color[3]);
	
	cb.WaveColor.Set(color[0],color[1],color[2]);	
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}
Int32 RenderDelegate_Dynamic_Blend::OnRender(
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
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 
	Float32 color[4]={1.0,1.0,1.0,1.0};
	pMtl->GetAmbientColor(&color[0],&color[1],&color[2],&color[3]);

	FR_DynamicBlend_CB cb;

	cb.WaveColor.Set(color[0],color[1],color[2]);	
	cb.TransformMatrix = (*pProjMatrix)* (* pViewMatrix)*(*pModelMatrix);
	
	cb.TextureStep = g_TextureStep;
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}
Int32 RenderDelegate_FlObject::OnRender(
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
	//XRDM->context()->SetShaders(pShader);
	//XRDM->context()->SetRenderState(pRS);
	//XRDM->context()->SetVertexLayout(pLayout);

	XRDM->context()->PSSetTexture(0, pMtl->GetCustomMap(0), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetCustomMap(1), XRDM->GetDefaultSampler()); 

	FR_FlObject_CB cb;
	cb.modelMatrix = (*pModelMatrix);
	cb.viewProjMatrix = (*pProjMatrix)* (* pViewMatrix);

    // calculate eye position in cubemap space
    XRVec4 eyePos_eye(0.0, 0.0, 0.0, 1.0), eyePos_model;
    XRMat4 viewInv = (*pViewMatrix).inverse();
	eyePos_model = viewInv * eyePos_eye;

	Float32 color[4];
	Float32 emission[4];
	pMtl->GetAmbientColor(&color[0],&color[1],&color[2],&color[3]);
	pMtl->GetEmissionColor(&emission[0],&emission[1],&emission[2],&emission[3]);
	cb.color.Set(color);
	cb.emission.Set(emission);
	cb.eyePos.Set(&eyePos_model.x);
	cb.modelMatrix = (*pModelMatrix);
	cb.viewProjMatrix = (*pProjMatrix) * (*pViewMatrix);

	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}

Int32 RenderDelegate_FrObject::OnRender(
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

	XRDM->context()->PSSetTexture(0, pMtl->GetCustomMap(0), XRDM->GetDefaultSampler()); 

	FR_FrObject_CB cb;

    // calculate eye position in cubemap space
    XRVec4 eyePos_eye(0.0, 0.0, 0.0, 1.0), eyePos_model;

	Float32 color[4]={1.0,1.0,1.0,1.0};
	Float32 emission[4]={0.0,0.0,0.0,0.0};
	pMtl->GetAmbientColor(&color[0],&color[1],&color[2],&color[3]);
	pMtl->GetEmissionColor(&emission[0],&emission[1],&emission[2],&emission[3]);
	cb.color.Set(color);
	cb.emission.Set(emission);
	cb.modelMatrix = (*pModelMatrix);
	cb.viewProjMatrix = (*pProjMatrix) * (*pViewMatrix);
    XRMat4 viewInv = (*pViewMatrix).inverse();
	eyePos_model = viewInv * eyePos_eye;
	cb.eyePos.Set(&eyePos_model.x);

	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	return 0;
}


Int32 RenderDelegate_Skinned_Texture::OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject)
{
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CUniformBlock* pUB2;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();
	BonePallete* pallete = node->GetMeshBonePallete();
	pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 

	FR_SkinnedTexture_CB cb;
	cb.TransformMatrix = (*pProjMatrix)* (* pViewMatrix) * (*pModelMatrix);
	cb.param.Set((Float32)pallete->maxInfNum,0,0,0);
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	XRDM->context()->UpdateUniformBlock(pUB, &pallete->bones[0]);
	XRDM->context()->VSSetUniformBlock(1, pUB);

	return 0;
}

Int32 RenderDelegate_SkyBox::OnRender(
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

	XRDM->context()->PSSetTexture(0, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 

	FR_SkyBox_CB cb;
	cb.ViewMatrix = (*pViewMatrix).inverse();
	cb.ProjMatrix = (* pProjMatrix);

	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}

	
XRMat4 biasMatrix = XRMat4(0.5f, 0.0f, 0.0f, 0.0f,
							0.0f, 0.5f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.5f, 0.0f,
							0.5f, 0.5f, 0.5f, 1.0f);

Int32 RenderDelegate_Rigid_Bump::OnRender(
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
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetNormalMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(2, pMtl->GetSpecularMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(3, pMtl->GetTransparencyMap(), XRDM->GetDefaultSampler()); 
	if (pLight) XRDM->context()->PSSetTexture(4, pLight->GetRenderTexture(), XRDM->GetDefaultDepthSampler()); 
	XRDM->context()->PSSetTexture(5, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(6, pMtl->GetIrradianceMap(), XRDM->GetDefaultSampler()); 

	FR_RigidBump_CB cb;
	XRVec4 eyePos_eye(0.0, 0.0, 0.0, 1.0), eyePos_model;
    XRMat4 viewInv = (*pViewMatrix).inverse();
    eyePos_model = viewInv * eyePos_eye;

	cb.ModelMatrix = (*pModelMatrix);
	cb.ViewProjMatrix = (*pProjMatrix) * (* pViewMatrix);
	cb.eyePos = eyePos_model;
	//cb.NormalMatrix = ((XRMat3)(cb.MVMatrix)).inverse().transpose();
	Float32 x=0,y=0,z=0;
	if (pLight) {
		pLight->GetPosition(&x,&y,&z);
		cb.LightPosition.Set(x,y,z,1);
		cb.BiasMatrix = biasMatrix * (*pLight->GetProj()) * (*pLight->GetView());// * (*pViewMatrix).inverse();
	}
	Float32 color[4]={1.0,1.0,1.0,1.0};
	pMtl->GetAmbientColor(&color[0],&color[1],&color[2],&color[3]);
	cb.ambientTerm.Set(color[0],color[1],color[2], color[3]);
	pMtl->GetDiffuseColor(&color[0],&color[1],&color[2],&color[3]);
	cb.diffuseTerm.Set(color[0],color[1],color[2], color[3]);
	pMtl->GetSpecularColor(&color[0],&color[1],&color[2],&color[3]);
	cb.SpecularTerm.Set(color[0],color[1],color[2], color[3]);
	pMtl->GetMaterialShininess(&color[0]);
	cb.ShininessTerm = color[0];

	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	return 0;
}

Int32 RenderDelegate_Skinned_Bump::OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject)
{
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CUniformBlock* pUB2;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();
	BonePallete* pallete = node->GetMeshBonePallete();
	pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	
	XRDM->context()->PSSetTexture(1, pMtl->GetNormalMap(), XRDM->GetDefaultSampler()); 

	XRDM->context()->PSSetTexture(2, pMtl->GetSpecularMap(), XRDM->GetDefaultSampler()); 

	if (pLight) XRDM->context()->PSSetTexture(3, pLight->GetRenderTexture(), XRDM->GetDefaultDepthSampler()); 
	XRDM->context()->PSSetTexture(4, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(5, pMtl->GetIrradianceMap(), XRDM->GetDefaultSampler()); 
	//XRDM->context()->PSSetTexture(3, pMtl->GetTransparencyMap(), XRDM->GetDefaultSampler()); 


	FR_SkinnedBump_CB cb;
	XRVec4 eyePos_eye(0.0, 0.0, 0.0, 1.0), eyePos_model;
    XRMat4 viewInv = (*pViewMatrix).inverse();
    eyePos_model = viewInv * eyePos_eye;

	cb.ModelMatrix = (*pModelMatrix);
	cb.ViewProjMatrix = (*pProjMatrix) * (* pViewMatrix);
	cb.eyePos = eyePos_model;
	Float32 x=0,y=0,z=0;
	if (pLight) {
		pLight->GetPosition(&x,&y,&z);
		cb.LightPosition.Set(x,y,z,1.0);
		cb.BiasMatrix = biasMatrix * (*pLight->GetProj()) * (*pLight->GetView());
	}

	cb.param.Set((Float32)pallete->maxInfNum,0,0,0);

	int offset = 3*sizeof(XRMat4)+3*sizeof(XRVec4);
	void * pt = XRDM->context()->LockUniformBlock(pUB);
	memcpy(pt, &cb, offset);
	memcpy((char*)pt+offset, &pallete->bones[0], MAX_BONE_NUM*sizeof(XRMat4));

	Float32 color[4]={1.0,1.0,1.0,1.0};
	pMtl->GetAmbientColor(&color[0],&color[1],&color[2],&color[3]);
	cb.ambientTerm.Set(color[0],color[1],color[2],color[3]);
	pMtl->GetDiffuseColor(&color[0],&color[1],&color[2],&color[3]);
	cb.diffuseTerm.Set(color[0],color[1],color[2],color[3]);
	pMtl->GetSpecularColor(&color[0],&color[1],&color[2],&color[3]);
	cb.SpecularTerm.Set(color[0],color[1],color[2],color[3]);

	pMtl->GetMaterialShininess(&color[0]);
	cb.ShininessTerm = color[0];
	offset+=MAX_BONE_NUM*sizeof(XRMat4);
	memcpy((char*)pt+offset, &cb.ambientTerm, sizeof(XRVec4)*3+4);
	XRDM->context()->UnlockUniformBlock(pUB);

	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	return 0;
}

Int32 RenderDelegate_Shadow::OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject)
{
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CUniformBlock* pUB2;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();
	pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	//XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 

	Pre_Shadow_CB cb;
	cb.TransformMatrix = (*pProjMatrix) * (* pViewMatrix) * (*pModelMatrix);

	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}

Int32 RenderDelegate_Shadow_Skinned::OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject)
{
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CUniformBlock* pUB2;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	CNode* node = (CNode*)pIObject->GetRealType();
	String name = node->GetName();
	BonePallete* pallete = node->GetMeshBonePallete();
	if (!pallete) return -1;
	pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	//XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 

	Pre_Shadow_Skinned_CB cb;
	cb.TransformMatrix = (*pProjMatrix)* (* pViewMatrix) * (*pModelMatrix);
	cb.param.Set((Float32)pallete->maxInfNum,0,0,0);

	void * pt = XRDM->context()->LockUniformBlock(pUB);

	memcpy(pt, &cb, sizeof(XRMat4)+sizeof(XRVec4));
	memcpy((char*)pt+sizeof(XRMat4)+sizeof(XRVec4), &pallete->bones[0], MAX_BONE_NUM*sizeof(XRMat4));
	//XRDM->context()->UpdateUniformBlock(pUB, &cb, 0, sizeof(XRMat4)+sizeof(XRVec4));
	//XRDM->context()->UpdateUniformBlock(pUB, &pallete->bones[0], sizeof(XRMat4)+sizeof(XRVec4), MAX_BONE_NUM*sizeof(XRMat4));
	XRDM->context()->UnlockUniformBlock(pUB);

	XRDM->context()->VSSetUniformBlock(0, pUB);
	//XRDM->context()->VSSetUniformBlock(1, pUB);

	return 0;
}
	
Int32 RenderDelegate_FrGlossy::OnRender(
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

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 

	FR_Glossy_CB cb;

	cb.MVMatrix = (*pViewMatrix)*(*pModelMatrix);
	cb.MVITMatrix =  XRMat3(cb.MVMatrix).inverse().transpose();
	cb.MVPMatrix = (*pProjMatrix)*cb.MVMatrix;
	cb.AmbientColor.Set(g_AmbientColor);
	cb.DiffuseColor.Set(g_DiffuseColor);
	cb.SpecularColor.Set(g_SpecularColor);

	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	return 0;
}
Int32 RenderDelegate_FrGlossyColor::OnRender(
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

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(2, pMtl->GetAmbientMap(), XRDM->GetDefaultSampler()); 

	FR_GlossyColor_CB cb;

	cb.MVMatrix = (*pViewMatrix)*(*pModelMatrix);
	cb.MVITMatrix =  XRMat3(cb.MVMatrix).inverse().transpose();
	cb.MVPMatrix = (*pProjMatrix)*cb.MVMatrix;
	cb.AmbientColor.Set(g_AmbientColor);
	cb.DiffuseColor.Set(g_DiffuseColor);
	cb.SpecularColor.Set(g_SpecularColor);
    cb.MaterialColor.Set(g_MaterialColor);
    cb.AlphaRate=g_MaterialAlpha;
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	return 0;
}
Int32 RenderDelegate_FrGlossyAlpha::OnRender(
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

	XRDM->context()->PSSetTexture(0, pMtl->GetDiffuseMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 

	FR_GlossyAlpha_CB cb;

	cb.MVMatrix = (*pViewMatrix)*(*pModelMatrix);
	cb.MVITMatrix =  XRMat3(cb.MVMatrix).inverse().transpose();
	cb.MVPMatrix = (*pProjMatrix)*cb.MVMatrix;
	cb.AmbientColor.Set(g_AmbientColor);
	cb.DiffuseColor.Set(g_DiffuseColor);
	cb.SpecularColor.Set(g_SpecularColor);
	cb.AlphaRate = pMtl->GetOpacity();
	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);
	XRDM->context()->PSSetUniformBlock(0, pUB);
	return 0;
}
Int32 RenderDelegate_FrGlass::OnRender(
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

	XRDM->context()->PSSetTexture(0, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 

	FR_Glass_CB cb;

	XRMat4 mv = (*pViewMatrix)*(*pModelMatrix);
	cb.MVPMatrix = (*pProjMatrix)*mv;
	// Set eye position in model space
	cb.EyePosition = mv.inverse() * XRVec4(0, 0, 0, 1);
	cb.RIRSquare = fRIR * fRIR;

	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}
Int32 RenderDelegate_FrGlassAlpha::OnRender(
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

	XRDM->context()->PSSetTexture(0, pMtl->GetEnvironmentMap(), XRDM->GetDefaultSampler()); 
	XRDM->context()->PSSetTexture(1, pMtl->GetAmbientMap(), XRDM->GetDefaultSampler()); 

	FR_Glass_Alpha_CB cb;

	XRMat4 mv = (*pViewMatrix)*(*pModelMatrix);
	cb.MVPMatrix = (*pProjMatrix)*mv;
	// Set eye position in model space
	cb.EyePosition = mv.inverse() * XRVec4(0, 0, 0, 1);
	cb.RIRSquare = fRIR * fRIR;

	XRDM->context()->UpdateUniformBlock(pUB, &cb);
	XRDM->context()->VSSetUniformBlock(0, pUB);

	return 0;
}

