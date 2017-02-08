#include "CLight.h"
#include "../CNode.h"
#include "../Camera/CCamera.h"
#include "../../XrCore/CDeviceManager.h"

CLight::CLight():	
	m_transitionDuration(DefaultTransitionDuration),
	m_transitionStyle(AnimationStyle_EaseOut)
{
	x._Set(0);
	y._Set(0);
	z._Set(0);
	vx._Set(1);
	vy._Set(1);
	vz._Set(1);
	m_renderTargetSize = 2048;
}

CLight::~CLight()
{
}
xr_state CLight::Init(LightType type)
{
	m_type = type;
	switch (type) {
	case LightType_Point:
		InitPointLight();
		break;
	case LightType_Spot:
		InitSpotLight();
		break;
	default:
		goto END;
	}
	InitRender();
	m_renderCamera.SetPerspective(70, 1.0, 100.0f, 1000.0f);
END:
	return XR_OK;
}
xr_state CLight::InitSpotLight()
{
	m_renderTarget = new CRenderTarget;
	//XRDM->device()->CreateRenderTarget(m_renderTargetSize, m_renderTargetSize, XR_R8G8B8A8, XR_D24, m_renderTarget);
	XRDM->device()->CreateRenderTarget(m_renderTargetSize, m_renderTargetSize, XR_R32F, XR_D24, m_renderTarget);
	return XR_OK;
}
xr_state CLight::InitPointLight()
{
	Int32 i;
	m_renderTarget = new CRenderTarget;
	for (i=0;i<6;i++) {
		//XRDM->device()->CreateRenderTargetCube(m_renderTargetSize, m_renderTargetSize, XR_NONE, XR_D24, m_renderTarget);
	}
	return XR_OK;
}

xr_state CLight::InitRender()
{
	m_rigidRender = new CMaterial(Material_Shadow);
	
	m_skinnedRender = new CMaterial(Material_Shadow_Skinned);
	m_rigidRender->UseDefaultMaterialEffect(Material_Shadow);
	m_skinnedRender->UseDefaultMaterialEffect(Material_Shadow_Skinned);
	return XR_OK;
}


xr_state CLight::SetRenderTarget()
{
	XRDM->context()->SetRenderTarget(m_renderTarget);
	XRDM->context()->ClearDepthStencil(1.0,0.0);
	//XRDM->context()->SetColorMask(0,0,0,0);
	//XRDM->context()->ClearRenderTarget(1.0,1.0,1.0,1.0);
	return XR_OK;
}

xr_state CLight::RestoreRenderTarget()
{
	//XRDM->context()->SetColorMask(1,1,1,1);
	//XRDM->context()->ClearRenderTarget(1.0,1.0,1.0,1.0);
	return XR_OK;
}

xr_state CLight::SetPosition(
    /* [in] */ Float32 x,
	/* [in] */ Float32 y,
    /* [in] */ Float32 z)
{
	//this->x.Set(x, m_transitionStyle, m_transitionDuration);
	//this->y.Set(y, m_transitionStyle, m_transitionDuration);
	//this->z.Set(z, m_transitionStyle, m_transitionDuration);

	m_renderCamera.SetPosition(x, y,z);
	return XR_OK;
}

xr_state CLight::SetOrientation(
    /* [in] */ Float32 vx,
    /* [in] */ Float32 vy,
	/* [in] */ Float32 vz)
{
	//this->vx.Set(vx, m_transitionStyle, m_transitionDuration);
	//this->vy.Set(vy, m_transitionStyle, m_transitionDuration);
	//this->vz.Set(vz, m_transitionStyle, m_transitionDuration);
	m_renderCamera.LookAt(vx, vy, vz);
	return XR_OK;
}

xr_state CLight::SetColor(
		/* [in] */ Float32 r,
		/* [in] */ Float32 g,
		/* [in] */ Float32 b)
{
	this->r.Set(r, m_transitionStyle, m_transitionDuration);
	this->g.Set(g, m_transitionStyle, m_transitionDuration);
	this->b.Set(b, m_transitionStyle, m_transitionDuration);
	return XR_OK;
}

xr_state CLight::GetPosition(
	/* [in] */ Float32 *x,
	/* [in] */ Float32 *y,
	/* [in] */ Float32 *z)
{
	m_renderCamera.GetPosition(x,y,z);
	return XR_OK;
}

xr_state CLight::GetOrientation(		
	/* [in] */ Float32 *vx,
	/* [in] */ Float32 *vy,
	/* [in] */ Float32 *vz)
{
	m_renderCamera.GetLookAt(vx,vy,vz);
	return XR_OK;
}

Void CLight::GetCAProperty(
	/* [in] */ APType type,
	/* [out] */ IAProperty** ppIAProperty)
{
	switch (type) {
		case AP_X:
			*ppIAProperty = &x;
			break;
		case AP_Y:
			*ppIAProperty = &y;
			break;
		case AP_Z:
			*ppIAProperty = &z;
			break;
		case AP_VX:
			*ppIAProperty = &vx;
			break;
		case AP_VY:
			*ppIAProperty = &vy;
			break;
		case AP_VZ:
			*ppIAProperty = &vz;
			break;
	}
}

xr_state CLight::OnCreateModel(CNode* model)
{
	return XR_OK;
}

xr_state CLight::OnUpdateModel(class CNode* model, class XRMat4& world)
{
	Float32 dir[3]={vx.Get(),vy.Get(),vz.Get()};
	return XR_OK;
}

xr_state CLight::OnRemoveModel(CNode* model)
{
	return XR_OK;
}

xr_state CLight::Render(XRMat4& mView, XRMat4& mProj)
{
	XRVec4 LightPos(vx.Get(),vy.Get(),vz.Get(),0);
	return XR_OK;
}

CMaterial* CLight::GetMaterialRender(CMaterial* mtl)
{
	if (mtl->GetType()&Material_Skinned) return m_skinnedRender;
	return m_rigidRender;
}
