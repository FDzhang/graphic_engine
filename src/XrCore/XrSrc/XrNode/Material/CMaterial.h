#ifndef __CMATERIAL_H__
#define __CMATERIAL_H__
#include "../../Common/XrInternal.h"
#include "../../External/IMaterial.h"
#include "../../Render/XrBatchRender.h"
#include "../Animation/CAProperty.h"
#include "../../XrResource/CResource.h"


class CMaterial : virtual public IMaterial, public CResource
{
public:
	CMaterial(MaterialType type);
	virtual ~CMaterial();

	virtual Int32 GetId();
	virtual UInt32 GetType() { return m_type; }

	virtual xr_state SetAmbientColor(Float32 r, Float32 g, Float32 b, Float32 a=1.0);
	virtual xr_state SetDiffuseColor(Float32 r, Float32 g, Float32 b, Float32 a=1.0);
	virtual xr_state SetSpecularColor(Float32 r, Float32 g, Float32 b, Float32 a=1.0);
	virtual xr_state SetEmissionColor(Float32 r, Float32 g, Float32 b, Float32 a=1.0);
    virtual xr_state SetMaterialShininess(Float32 val);

	virtual xr_state GetAmbientColor(Float32* r, Float32* g, Float32* b, Float32* a=0);
	virtual xr_state GetDiffuseColor(Float32* r, Float32* g, Float32* b, Float32* a=0);
	virtual xr_state GetSpecularColor(Float32* r, Float32* g, Float32* b, Float32* a=0);
	virtual xr_state GetEmissionColor(Float32* r, Float32* g, Float32* b, Float32* a=0);
	virtual xr_state GetMaterialShininess(Float32* val);

	virtual xr_state SetDiffuseMap(ConstString filename, UInt32 type = XR_TEXTURE_TYPE_DIFFUSE_SRGB);
	virtual xr_state SetSpecularMap(ConstString filename);
	virtual xr_state SetAmbientMap(ConstString filename);
	virtual xr_state SetNormalMap(ConstString filename);
	virtual xr_state SetRoughnessMap(ConstString filename);
	virtual xr_state SetEnvironmentMap(ConstString filename);
	virtual xr_state SetIrradianceMap(ConstString filename);
	virtual xr_state SetEmissionMap(ConstString filename);
	virtual xr_state SetTransparencyMap(ConstString filename);
	virtual xr_state SetCustomMap(ConstString filename, Int32 index);

	virtual CXrTextureEx* GetDiffuseMap();
	virtual CXrTextureEx* GetSpecularMap();
	virtual CXrTextureEx* GetAmbientMap();
	virtual CXrTextureEx* GetNormalMap();
	virtual CXrTextureEx* GetRoughnessMap();
	virtual CXrTextureEx* GetEnvironmentMap();
	virtual CXrTextureEx* GetIrradianceMap();
	virtual CXrTextureEx* GetEmissionMap();
	virtual CXrTextureEx* GetTransparencyMap();
	virtual CXrTextureEx* GetCustomMap(Int32 index);
	
	//CXrTextureEx* _GetDiffuseMap();

	virtual xr_state SetDiffuseMap(Int32 id);
	virtual xr_state SetSpecularMap(Int32 id);
	virtual xr_state SetEnvironmentMap(Int32 id);
	virtual xr_state SetIrradianceMap(Int32 id);
	virtual xr_state SetAmbientMap(Int32 id);
	virtual xr_state SetNormalMap(Int32 id);
	virtual xr_state SetRoughnessMap(Int32 id);
	virtual xr_state SetEmissionMap(Int32 id);
	virtual xr_state SetTransparencyMap(Int32 id);
	virtual xr_state SetCustomMap(Int32 id, Int32 index);

	virtual IRenderEffect* GetEffect() { return m_effect; }
	virtual xr_state CreateMaterialEffect(IRenderEffect** ppIRenderEffect);
	virtual xr_state UseDefaultMaterialEffect(MaterialType mtlType);

	virtual xr_state LoadTextureMapFromFile(ConstString fileName);
	virtual xr_state SetCustomMap(CXrTextureEx* tex, Int32 index);
	virtual xr_state SetDiffuseMap(CXrTextureEx* tex);
	virtual xr_state SetSpecularMap(CXrTextureEx* tex);
	virtual xr_state SetNormalMap(CXrTextureEx* tex);
	virtual xr_state SetEnvironmentMap(CXrTextureEx* tex);
	virtual xr_state SetIrradianceMap(CXrTextureEx* tex);
	virtual xr_state SetTransparencyMap(CXrTextureEx* tex);
	virtual xr_state SetDefaultLightDirection(Float32 x, Float32 y, Float32 z);
	virtual xr_state GetDefaultLightDirection(Float32* x, Float32* y, Float32* z);
	virtual xr_state SetOpacity(Float32 opacity);
	virtual Float32   GetOpacity();
	xr_state SetAmbientMap(CXrTextureEx* tex);

	virtual Int32 Release();

	virtual Void SetOpaque(Boolean opaque) {
		m_effect->SetOpaque(opaque);
	}

	virtual Boolean IsOpaque() {
		return m_effect->IsOpaque();
	}

    Void SetType(MaterialType type) {
		m_type = type;
	}

	virtual CShaderObject* GetRender(IRenderDelegate** ppDelegate) { if (m_effect) return m_effect->GetRenderDelegateContent(ppDelegate); else return 0; }

	//Material GetType() { return m_type; }
	Void GetSize(Float32* w, Float32* h)
	{
		if (diffuseMap) {
			*w=(Float32)diffuseMap->GetWidth();
			*h=(Float32)diffuseMap->GetHeight();
		}
		else {
			*w = 0;
			*h = 0;
		}
	}
	//CXrBiLinkList<CBatchRender>* GetRenderQuene() { return &m_renderQuene; }

private:
	CXrTextureEx*						diffuseMap;
	CXrTextureEx*						specularMap;
	CXrTextureEx*						ambientMap;
	CXrTextureEx*						normalMap;
	CXrTextureEx*						roughnessMap;
	CXrTextureEx*						emissionMap;
	CXrTextureEx*						environmentMap;
	CXrTextureEx*						irradianceMap;
	CXrTextureEx*						transparencyMap;
	CXrTextureEx*						customMap[8];
	MaterialType						m_type;
	CXrRenderEffect*					m_effect;

	//CAProperty						ar;
	//CAProperty						ag;
	//CAProperty						ab;
	//CAProperty						dr;
	//CAProperty						dg;
	//CAProperty						db;
	//CAProperty						sr;
	//CAProperty						sg;
	//CAProperty						sb;
	CAVector4*							m_diffuseColor;
	CAVector4*							m_ambientColor;
	CAVector4*							m_specularColor;
	CAVector4*							m_emissionColor;
	CAVector3*							m_defaultLightDir;
	CAProperty							m_shininessValue;
	Float32                             m_opacity;
//	CXrBiLinkList<CBatchRender>	    m_renderQuene;	//render quene for blending primitive
};


#endif  //__CMATERIAL_H__
