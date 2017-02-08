#ifndef __CLIGHT_H__
#define __CLIGHT_H__
#include "../../Common/XrInternal.h"
#include "../../External/ILight.h"
#include "../Animation/CAProperty.h"
#include "../Camera/CCamera.h"

class CLight: public ILight
{
public:
	CLight();
	//CNode(Float32 x, Float32 y, Float32 z, Float32 scale, ModelType type, CMaterial* mtl=0);
	virtual ~CLight();

	virtual xr_state SetPosition(
		/* [in] */ Float32 x,
		/* [in] */ Float32 y,
		/* [in] */ Float32 z);

	virtual xr_state SetOrientation(		
		/* [in] */ Float32 vx,
		/* [in] */ Float32 vy,
		/* [in] */ Float32 vz);

	virtual xr_state GetPosition(
		/* [in] */ Float32 *x,
		/* [in] */ Float32 *y,
		/* [in] */ Float32 *z);

	virtual xr_state GetOrientation(		
		/* [in] */ Float32 *vx,
		/* [in] */ Float32 *vy,
		/* [in] */ Float32 *vz);

	virtual xr_state SetColor(
		/* [in] */ Float32 r,
		/* [in] */ Float32 g,
		/* [in] */ Float32 b);

	virtual Void GetCAProperty(
		/* [in] */ APType type,
		/* [out] */ class IAProperty** ppIAProperty);
	
	xr_state OnCreateModel(class CNode* model);
	xr_state OnUpdateModel(class CNode* model, struct XRMat4& world);
	xr_state OnRemoveModel(CNode* model);
	xr_state Render(XRMat4& mView, XRMat4& mProj);
	class CMaterial* GetMaterialRender(CMaterial* mtl);
	class CRenderTarget* GetRenderTarget();
	xr_state SetRenderTarget();
	xr_state RestoreRenderTarget();
	virtual xr_state Init(LightType type);
	xr_state InitSpotLight();
	xr_state InitPointLight();
	xr_state InitRender();
	XRMat4* GetView(){
		return (XRMat4*)&m_renderCamera.GetViewMatrix();
	}
	XRMat4* GetProj(){
		return (XRMat4*)&m_renderCamera.GetProjectionMatrix();
	}
	CTexture* GetRenderTexture()
	{
		return m_renderTarget->GetRenderTexture();
		//return m_renderTarget->GetDepthStencilTexture();
	}
	Void SetNeedUpdate() {
		m_renderCamera.SetNeedUpdate();
	}
	CAProperty						x;
	CAProperty						y;
	CAProperty						z;
	CAProperty						vx;
	CAProperty						vy;
	CAProperty						vz;
	CAProperty						r;
	CAProperty						g;
	CAProperty						b;
protected:
	CCamera							m_renderCamera;
	CMaterial*						m_skinnedRender;
	CMaterial*						m_rigidRender;
	LightType						m_type;
	AnimationStyle					m_transitionStyle;
	UInt32							m_transitionDuration;
	CRenderTarget*					m_renderTarget;
	Int32							m_renderTargetSize;
};

#endif  //__CLIGHT_H__

