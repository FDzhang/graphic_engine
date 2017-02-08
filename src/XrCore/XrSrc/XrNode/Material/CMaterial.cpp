#include "CMaterial.h"
#include "../../XrCore/CDeviceManager.h"
#include "../../Render/CRenderManager.h"

CMaterial::CMaterial(MaterialType type)
{
	Xr_Self_Src
	diffuseMap = 0;
	specularMap = 0;
	ambientMap = 0;
	normalMap = 0;
	roughnessMap = 0;
	emissionMap = 0;
	environmentMap = 0;
	irradianceMap = 0;
	transparencyMap = 0;
	m_type = type;
	m_effect = 0;
	m_defaultLightDir = 0;
	m_diffuseColor = 0;
	m_ambientColor = 0;
	m_specularColor = 0;
	m_emissionColor = 0;
	m_shininessValue.Set(1.0,0,0);
}

CMaterial::~CMaterial()
{
	if (diffuseMap) {
		XRDM->ReleaseTexture(diffuseMap->m_id);
		diffuseMap=0;
	}
	if (specularMap) {
		XRDM->ReleaseTexture(specularMap->m_id);
		specularMap=0;
	}
	if (ambientMap) {
		XRDM->ReleaseTexture(ambientMap->m_id);
		ambientMap=0;
	}
	if (normalMap) {
		XRDM->ReleaseTexture(normalMap->m_id);
		normalMap=0;
	}
	if (roughnessMap) {
		XRDM->ReleaseTexture(roughnessMap->m_id);
		roughnessMap=0;
	}
	if (emissionMap) {
		XRDM->ReleaseTexture(emissionMap->m_id);
		emissionMap=0;
	}
	if (environmentMap) {
		XRDM->ReleaseTexture(environmentMap->m_id);
		environmentMap=0;
	}
	if (irradianceMap) {
		XRDM->ReleaseTexture(irradianceMap->m_id);
		irradianceMap=0;
	}
	if (transparencyMap) {
		XRDM->ReleaseTexture(transparencyMap->m_id);
		transparencyMap=0;
	}
	if (m_effect) {
		IRenderDelegate* dele = m_effect->GetRenderDelegate();
		if (!(Material_Custom & m_type) && dele) {
			delete dele;
		}
		delete m_effect;
	}
	if (m_defaultLightDir) delete m_defaultLightDir;
	if (m_diffuseColor) delete m_diffuseColor;
	if (m_ambientColor) delete m_ambientColor;
	if (m_specularColor) delete m_specularColor;
}

Int32 CMaterial::GetId()
{
	return CResource::GetID();
	//return XR_OK;
}

xr_state CMaterial::SetAmbientColor(Float32 r, Float32 g, Float32 b, Float32 a)
{
	if (!m_ambientColor ){ m_ambientColor  = new CAVector4;
	}
	if (!m_ambientColor ) return XR_FAILED;
	m_ambientColor->x.Set(r, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_ambientColor->y.Set(g, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_ambientColor->z.Set(b, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_ambientColor->w.Set(a, AnimationStyle_EaseOut, DefaultTransitionDuration);
	return XR_OK;
}

xr_state CMaterial::SetDiffuseColor(Float32 r, Float32 g, Float32 b, Float32 a)
{
	if (!m_diffuseColor ) {m_diffuseColor  = new CAVector4;
	}
	if (!m_diffuseColor ) return XR_FAILED;
	m_diffuseColor->x.Set(r, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_diffuseColor->y.Set(g, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_diffuseColor->z.Set(b, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_diffuseColor->w.Set(a, AnimationStyle_EaseOut, DefaultTransitionDuration);
	return XR_OK;
}

xr_state CMaterial::SetSpecularColor(Float32 r, Float32 g, Float32 b, Float32 a)
{
	if (!m_specularColor ) {m_specularColor  = new CAVector4;
		}
	if (!m_specularColor ) return XR_FAILED;
	m_specularColor->x.Set(r, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_specularColor->y.Set(g, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_specularColor->z.Set(b, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_specularColor->w.Set(a, AnimationStyle_EaseOut, DefaultTransitionDuration);
	return XR_OK;
}

xr_state CMaterial::SetEmissionColor(Float32 r, Float32 g, Float32 b, Float32 a)
{
	if (!m_emissionColor ) {m_emissionColor  = new CAVector4;
		}
	if (!m_emissionColor ) return XR_FAILED;
	m_emissionColor->x.Set(r, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_emissionColor->y.Set(g, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_emissionColor->z.Set(b, AnimationStyle_EaseOut, DefaultTransitionDuration);
	m_emissionColor->w.Set(a, AnimationStyle_EaseOut, DefaultTransitionDuration);
	return XR_OK;
}
xr_state CMaterial::SetMaterialShininess(Float32 val)
{
	m_shininessValue.Set(val, AnimationStyle_EaseOut, DefaultTransitionDuration);
	return XR_OK;
}

xr_state CMaterial::GetMaterialShininess(Float32* val)
{
	*val = m_shininessValue.Get();
	return XR_OK;
}

xr_state CMaterial::GetAmbientColor(Float32* r, Float32* g, Float32* b, Float32* a)
{
	if (!m_ambientColor ) return XR_FAILED;
	*r = m_ambientColor->x.Get();
	*g = m_ambientColor->y.Get();
	*b = m_ambientColor->z.Get();
	if(a) *a = m_ambientColor->w.Get();
	return XR_OK;
}

xr_state CMaterial::GetDiffuseColor(Float32* r, Float32* g, Float32* b, Float32* a)
{
	if (!m_diffuseColor ) return XR_FAILED;
	*r = m_diffuseColor->x.Get();
	*g = m_diffuseColor->y.Get();
	*b = m_diffuseColor->z.Get();
	if(a) *a = m_diffuseColor->w.Get();
	return XR_OK;
}

xr_state CMaterial::GetSpecularColor(Float32* r, Float32* g, Float32* b, Float32* a)
{
	if (!m_specularColor ) return XR_FAILED;
	*r = m_specularColor->x.Get();
	*g = m_specularColor->y.Get();
	*b = m_specularColor->z.Get();
	if(a) *a = m_specularColor->w.Get();
	return XR_OK;
}

xr_state CMaterial::GetEmissionColor(Float32* r, Float32* g, Float32* b, Float32* a)
{
	if (!m_emissionColor ) return XR_FAILED;
	*r = m_emissionColor->x.Get();
	*g = m_emissionColor->y.Get();
	*b = m_emissionColor->z.Get();
	if(a) *a = m_emissionColor->w.Get();
	return XR_OK;
}


xr_state CMaterial::SetDiffuseMap(ConstString filename, UInt32 type)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, type);
	//if (tid<0) return XR_FAILED;
	return SetDiffuseMap(tid);
}

xr_state CMaterial::SetSpecularMap(ConstString filename)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, XR_TEXTURE_TYPE_SPECULAR);
	//if (tid<0) return XR_FAILED;
	return SetSpecularMap(tid);
}

xr_state CMaterial::SetAmbientMap(ConstString filename)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, XR_TEXTURE_TYPE_AMBIENT);
	//if (tid<0) return XR_FAILED;
	return SetAmbientMap(tid);
}

xr_state CMaterial::SetNormalMap(ConstString filename)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, XR_TEXTURE_TYPE_NORMAL);
	//if (tid<0) return XR_FAILED;
	return SetNormalMap(tid);
}

xr_state CMaterial::SetRoughnessMap(ConstString filename)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, XR_TEXTURE_TYPE_ROUGHNESS);
	//if (tid<0) return XR_FAILED;
	return SetRoughnessMap(tid);
}

xr_state CMaterial::SetEnvironmentMap(ConstString filename)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, XR_TEXTURE_TYPE_AMBIENT);
	//if (tid<0) return XR_FAILED;XR_TEXTURE_TYPE_HDR
	return SetEnvironmentMap(tid);
}
xr_state CMaterial::SetIrradianceMap(ConstString filename)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, XR_TEXTURE_TYPE_HDR);
	//if (tid<0) return XR_FAILED;
	return SetIrradianceMap(tid);
}

xr_state CMaterial::SetEmissionMap(ConstString filename)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, XR_TEXTURE_TYPE_EMISSIVE);
	//if (tid<0) return XR_FAILED;
	return SetEmissionMap(tid);
}
xr_state CMaterial::SetTransparencyMap(ConstString filename)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, XR_TEXTURE_TYPE_TRANSPARENCY);
	//if (tid<0) return XR_FAILED;
	return SetTransparencyMap(tid);
}
xr_state CMaterial::SetCustomMap(ConstString filename, Int32 index)
{
	Int32 tid = XRDM->CreateTextureFromFile(filename, 0);
	if (tid<0) return XR_FAILED;
	return this->SetCustomMap(tid,index);
}

xr_state CMaterial::SetDiffuseMap(Int32 id)
{
	CXrTextureEx* tex = XRDM->AquireTexture(id);
	return SetDiffuseMap(tex);
}

xr_state CMaterial::SetSpecularMap(Int32 id)
{
	CXrTextureEx* tex = XRDM->AquireTexture(id);
	return SetSpecularMap(tex);
}

xr_state CMaterial::SetEnvironmentMap(Int32 id)
{
	CXrTextureEx* tex = XRDM->AquireTexture(id);
	return SetEnvironmentMap(tex);
}

xr_state CMaterial::SetIrradianceMap(Int32 id)
{
	CXrTextureEx* tex = XRDM->AquireTexture(id);
	return SetIrradianceMap(tex);
}


xr_state CMaterial::SetAmbientMap(Int32 id)
{
	CXrTextureEx* tex = XRDM->AquireTexture(id);
	

	return SetAmbientMap(tex);
}

xr_state CMaterial::SetNormalMap(Int32 id)
{
	CXrTextureEx* tex = XRDM->AquireTexture(id);
	return SetNormalMap(tex);
	return XR_OK;
}

xr_state CMaterial::SetRoughnessMap(Int32 id)
{
	return XR_OK;
}

xr_state CMaterial::SetEmissionMap(Int32 id)
{
	return XR_OK;
}

xr_state CMaterial::SetTransparencyMap(Int32 id)
{
	//m_isOpaque = FALSE;
	CXrTextureEx* tex = XRDM->AquireTexture(id);
	return SetTransparencyMap(tex);
}

xr_state CMaterial::SetNormalMap(CXrTextureEx* tex)
{
	//if (!tex) return XR_FAILED;
	//if (normalMap) {
	//	XRDM->ReleaseTexture(normalMap->m_id);
	//}

	normalMap = tex;
	return XR_OK;
}

xr_state CMaterial::SetSpecularMap(CXrTextureEx* tex)
{
	//if (!tex) return XR_FAILED;
	//if (specularMap) {
	//	XRDM->ReleaseTexture(specularMap->m_id);
	//}

	specularMap = tex;
	//if (!(diffuseMap->format&TexFormat_Alpha)) m_isOpaque = TRUE;
	return XR_OK;
}
xr_state CMaterial::SetAmbientMap(CXrTextureEx* tex)
{
	//if (!tex) return XR_FAILED;
	//if (specularMap) {
	//	XRDM->ReleaseTexture(specularMap->m_id);
	//}

	ambientMap= tex;
	//if (!(diffuseMap->format&TexFormat_Alpha)) m_isOpaque = TRUE;
	return XR_OK;
}

xr_state CMaterial::SetDiffuseMap(CXrTextureEx* tex)
{
	//if (!tex) return XR_FAILED;
	//if (diffuseMap) {
	//	XRDM->ReleaseTexture(diffuseMap->m_id);
	//}

	diffuseMap = tex;
	//if (!(diffuseMap->format&TexFormat_Alpha)) m_isOpaque = TRUE;
	return XR_OK;
}

xr_state CMaterial::SetEnvironmentMap(CXrTextureEx* tex)
{
	//if (!tex) return XR_FAILED;
	//if (environmentMap) {
	//	XRDM->ReleaseTexture(environmentMap->m_id);
	//}

	environmentMap = tex;
	return XR_OK;
}

xr_state CMaterial::SetIrradianceMap(CXrTextureEx* tex)
{
	//if (!tex) return XR_FAILED;
	//if (irradianceMap) {
	//	XRDM->ReleaseTexture(irradianceMap->m_id);
	//}

	irradianceMap = tex;
	return XR_OK;
}

xr_state CMaterial::SetTransparencyMap(CXrTextureEx* tex)
{
	//if (!tex) return XR_FAILED;
	//if (transparencyMap) {
	//	XRDM->ReleaseTexture(transparencyMap->m_id);
	//}

	transparencyMap = tex;
	return XR_OK;
}

xr_state CMaterial::SetCustomMap(CXrTextureEx* tex, Int32 index)
{
	//if (!tex) return XR_FAILED;
	customMap[index] = tex;
	return XR_OK;
}

//CTexture* CMaterial::_GetDiffuseMap()
//{
//	return diffuseMap;
//}

CXrTextureEx* CMaterial::GetDiffuseMap()
{
	return diffuseMap;
}

CXrTextureEx* CMaterial::GetSpecularMap()
{
	return specularMap;
}

CXrTextureEx* CMaterial::GetAmbientMap()
{
	return ambientMap;
}

CXrTextureEx* CMaterial::GetNormalMap()
{
	return normalMap;
}

CXrTextureEx* CMaterial::GetRoughnessMap()
{
	return roughnessMap;
}

CXrTextureEx* CMaterial::GetEnvironmentMap()
{
	return environmentMap;
}

CXrTextureEx* CMaterial::GetIrradianceMap()
{
	return irradianceMap;
}

CXrTextureEx* CMaterial::GetEmissionMap()
{
	return emissionMap;
}

CXrTextureEx* CMaterial::GetTransparencyMap()
{
	return transparencyMap;
}

CXrTextureEx* CMaterial::GetCustomMap(Int32 index)
{
	return customMap[index];
}

xr_state CMaterial::LoadTextureMapFromFile(ConstString fileName)
{
	return XR_OK;
}

xr_state CMaterial::SetCustomMap(Int32 id, Int32 index)
{
	CXrTextureEx* tex = XRDM->AquireTexture(id);
	return SetCustomMap(tex, index);
}

xr_state CMaterial::UseDefaultMaterialEffect(MaterialType mtlType)
{
	if (m_effect) {
		return XR_FAILED;
	}

	//m_effect = new CXrRenderEffect();
	//if (!m_effect) return XR_FAILED;

	m_effect = XRRM->CreateEffect(mtlType);

	if (!m_effect) {
		goto CleanUp;
	}
	return XR_OK;

CleanUp:
	delete m_effect;
	m_type = Material_Null;
	return XR_FAILED;
}

xr_state CMaterial::CreateMaterialEffect(IRenderEffect** ppIRenderEffect)
{
	CXrRenderEffect* effect = new CXrRenderEffect();
	if (!effect) return  XR_FAILED;
	m_effect = effect;
	if (ppIRenderEffect) *ppIRenderEffect = effect;
	return XR_OK;
}

xr_state CMaterial::SetDefaultLightDirection(Float32 x, Float32 y, Float32 z)
{
	if (!m_defaultLightDir) {m_defaultLightDir = new CAVector3;
		}
	if (!m_defaultLightDir) return XR_FAILED;
	m_defaultLightDir->x.Set(x, 0, 0);
	m_defaultLightDir->y.Set(y, 0, 0);
	m_defaultLightDir->z.Set(z, 0, 0);
	return XR_OK;
}

xr_state CMaterial::GetDefaultLightDirection(Float32* x, Float32* y, Float32* z)
{
	if (!m_defaultLightDir) return XR_FAILED;
	*x = m_defaultLightDir->x.Get();
	*y = m_defaultLightDir->y.Get();
	*z = m_defaultLightDir->z.Get();
	return XR_OK;
}

Int32 CMaterial::Release()
{
	Int32 refcnt = DecRef();
	if (refcnt == 0) {
		delete this;
    }
	return refcnt;
}
