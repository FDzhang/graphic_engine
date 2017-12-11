#ifndef __IMATERIAL_H__
#define __IMATERIAL_H__
#include "xrIntrinsic.h"
#include "IRenderEffect.h"
#include "IResource.h"

class IMaterial : virtual public IResource
{
public:
	virtual Int32 GetId()=0;
	virtual UInt32 GetType()=0;

	virtual xr_state SetAmbientColor(Float32 r, Float32 g, Float32 b, Float32 a=1.0)=0;
	virtual xr_state SetDiffuseColor(Float32 r, Float32 g, Float32 b, Float32 a=1.0)=0;
	virtual xr_state SetSpecularColor(Float32 r, Float32 g, Float32 b, Float32 a=1.0)=0;
	virtual xr_state SetEmissionColor(Float32 r, Float32 g, Float32 b, Float32 a=1.0)=0;
	virtual xr_state SetMaterialShininess(Float32 val)=0;

	virtual xr_state GetAmbientColor(Float32* r, Float32* g, Float32* b, Float32* a=0)=0;
	virtual xr_state GetDiffuseColor(Float32* r, Float32* g, Float32* b, Float32* a=0)=0;
	virtual xr_state GetSpecularColor(Float32* r, Float32* g, Float32* b, Float32* a=0)=0;
	virtual xr_state GetEmissionColor(Float32* r, Float32* g, Float32* b, Float32* a=0)=0;
	virtual xr_state GetMaterialShininess(Float32* val)=0
		;
	virtual xr_state SetDiffuseMap(ConstString filename, UInt32 type = XR_TEXTURE_TYPE_DIFFUSE_SRGB)=0;
	virtual xr_state SetSpecularMap(ConstString filename)=0;
	virtual xr_state SetAmbientMap(ConstString filename)=0;
	virtual xr_state SetNormalMap(ConstString filename)=0;
	virtual xr_state SetRoughnessMap(ConstString filename)=0;
	virtual xr_state SetEnvironmentMap(ConstString filename)=0;
	virtual xr_state SetIrradianceMap(ConstString filename)=0;
	virtual xr_state SetEmissionMap(ConstString filename)=0;
	virtual xr_state SetTransparencyMap(ConstString filename)=0;
	virtual xr_state SetCustomMap(ConstString filename, Int32 index)=0;   //index should be from 0~8

	virtual xr_state SetDiffuseMap(Int32 id)=0;
	virtual xr_state SetSpecularMap(Int32 id)=0;
	virtual xr_state SetEnvironmentMap(Int32 id)=0;
	virtual xr_state SetAmbientMap(Int32 id)=0;
	virtual xr_state SetNormalMap(Int32 id)=0;
	virtual xr_state SetRoughnessMap(Int32 id)=0;
	virtual xr_state SetEmissionMap(Int32 id)=0;
	virtual xr_state SetIrradianceMap(Int32 id)=0;
	virtual xr_state SetTransparencyMap(Int32 id)=0;

	virtual class CTexture* GetDiffuseMap()=0;
	virtual class CTexture* GetSpecularMap()=0;
	virtual class CTexture* GetAmbientMap()=0;
	virtual class CTexture* GetNormalMap()=0;
	virtual class CTexture* GetRoughnessMap()=0;
	virtual class CTexture* GetEnvironmentMap()=0;
	virtual class CTexture* GetIrradianceMap()=0;
	virtual class CTexture* GetEmissionMap()=0;
	virtual class CTexture* GetTransparencyMap()=0;
	virtual class CTexture* GetCustomMap(Int32 index)=0;

	virtual IRenderEffect* GetEffect()=0;
	virtual xr_state CreateMaterialEffect(IRenderEffect** ppIRenderEffect)=0;
	virtual xr_state SetDefaultLightDirection(Float32 x, Float32 y, Float32 z)=0;
	virtual xr_state GetDefaultLightDirection(Float32* x, Float32* y, Float32* z)=0;
	virtual Boolean IsOpaque()=0;

	virtual Int32 Release() = 0;
};

#endif  //__IMATERIAL_H__
