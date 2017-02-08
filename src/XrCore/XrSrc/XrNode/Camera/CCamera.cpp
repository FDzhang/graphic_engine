#include "CCamera.h"
//#include "CAProperty.h"


CCamera::CCamera():
	//m_transitionDuration(DefaultTransitionDuration),
	//m_transitionStyle(AnimationStyle_EaseOut),
	m_transitionDuration(500),
	m_transitionStyle(AnimationStyle_EaseOut),
	m_lockLookAt(FALSE),
	m_2Dmode(FALSE),
	m_2DAVMmode(FALSE)
{
	xLookAt._Set(0);
	yLookAt._Set(0);
	zLookAt._Set(0);
	xPos._Set(0);
	yPos._Set(0);
	zPos._Set(2.0);
	xRot._Set(0);
	yRot._Set(0);
	zRot._Set(0);
}

CCamera::~CCamera()
{
}
void CCamera::Set2DCamera(bool camera_flag)
{
    //m_2Dmode = camera_flag;
    m_2DAVMmode = camera_flag;
}

xr_state CCamera::SetPosition(
    /* [in] */ Float32 x,
	/* [in] */ Float32 y,
    /* [in] */ Float32 z)
{
	this->xPos.Set(x, m_transitionStyle, m_transitionDuration);
	this->yPos.Set(y, m_transitionStyle, m_transitionDuration);
	this->zPos.Set(z, m_transitionStyle, m_transitionDuration);

	return XR_OK;
}

xr_state CCamera::MovePosition(
    /* [in] */ Float32 x,
    /* [in] */ Float32 y,
	/* [in] */ Float32 z)
{
	return XR_OK;
}

xr_state CCamera::SetOrientation(
    /* [in] */ Float32 head,
    /* [in] */ Float32 pitch,
	/* [in] */ Float32 roll)
{
	return XR_OK;
}

Void CCamera::SetPerspective(
	/* [in] */ Float32 fovx, 
	/* [in] */ Float32 aspect, 
	/* [in] */ Float32 znear, 
	/* [in] */ Float32 zfar)
{
	m_camera.perspective(fovx, aspect, znear, zfar);
	this->fov.Set(fovx, m_transitionStyle, m_transitionDuration);
}

Void CCamera::SetFOV(
	/* [in] */ Float32 fov)
{
	this->fov.Set(fov, m_transitionStyle, m_transitionDuration);
}

Void CCamera::SetFOVDelta(
	/* [in] */ Float32 fov)
{
	this->fov.Delta(fov, m_transitionStyle, m_transitionDuration);
	if (this->fov.Get()<1) this->fov.Set(1);
	if (this->fov.Get()>170) this->fov.Set(170);
}


Void CCamera::SetCustomProjectionMatrix(
	/* [in] */ Float32* pMatrix,
	/* [in] */ Boolean transpose)
{
	m_camera.setProjectionMatrix(pMatrix, transpose);
}

Void CCamera::SetOrthognal(
	/* [in] */ Float32 l, 
	/* [in] */ Float32 r, 
	/* [in] */ Float32 t, 
	/* [in] */ Float32 b, 
	/* [in] */ Float32 n, 
	/* [in] */ Float32 f)
{
	m_camera.orthognal(l, r, t, b, n, f);
	m_2Dmode = TRUE;
}

Void CCamera::LookAt(
	/* [in] */ Float32 x, 
	/* [in] */ Float32 y, 
	/* [in] */ Float32 z)
{
	this->xLookAt.Set(x, m_transitionStyle, m_transitionDuration);
	this->yLookAt.Set(y, m_transitionStyle, m_transitionDuration);
	this->zLookAt.Set(z, m_transitionStyle, m_transitionDuration);
}

Void CCamera::Flush()
{
	if (!m_2Dmode && m_needUpdate) {
		m_camera.lookAt(xPos.Get(), yPos.Get(), zPos.Get(), xLookAt.Get(), yLookAt.Get(), zLookAt.Get());
		m_camera.RotateAround(xRot.Get(), yRot.Get());
		m_camera.setFov(fov.Get());
		m_needUpdate = FALSE;
	}
}

const XRMat4& CCamera::GetViewMatrix()
{
    static XRMat4 view_matrix=XRMat4::Scale(1.0,1.0,1.0);
	
	if(m_2DAVMmode == 1)
	{
	    return view_matrix;
	}
	//m_camera.setPosition(x.Get(), y.Get(), z.Get());
	Flush();
	return m_camera.getViewMatrix();
}

const XRMat4& CCamera::GetProjectionMatrix()
{
    static XRMat4 view_matrix=XRMat4::Scale(1.0,1.0,1.0);
	if(m_2DAVMmode == 1)
	{
	    return view_matrix;
	}

	Flush();
	return m_camera.getProjectionMatrix();
}

Void CCamera::LockLookAt(
	/* [in] */ Boolean flag)
{
	m_lockLookAt = flag;
}

Void CCamera::RotateAround(
	/* [in] */ Float32 x, 
	/* [in] */ Float32 y)
{
	xRot.Set(x, m_transitionStyle, m_transitionDuration);
	yRot.Set(y, m_transitionStyle, m_transitionDuration);
}

Void CCamera::RotateAroundDelta(
	/* [in] */ Float32 dx, 
	/* [in] */ Float32 dy)
{
	xRot.Delta(dx, m_transitionStyle, m_transitionDuration);
	yRot.Delta(dy, m_transitionStyle, m_transitionDuration);
	if (yRot.Get()<-90) yRot.Set(-90);
	if (yRot.Get()>90) yRot.Set(90);
}

Void CCamera::MoveAround(
	/* [in] */ Float32 x, 
	/* [in] */ Float32 y)
{
	xRot.Set(x, m_transitionStyle, m_transitionDuration);
	yRot.Set(y, m_transitionStyle, m_transitionDuration);
}

Void CCamera::MoveAroundDelta(
	/* [in] */ Float32 dx, 
	/* [in] */ Float32 dy)
{
	Float32 x, y, z;
    m_camera.GetMoveAroundVal(dx, dy, 0, &x, &y,&z); 

	xLookAt.Delta(x);
	yLookAt.Delta(y);
	zLookAt.Delta(z);
	xPos.Delta(x);
	yPos.Delta(y);
	zPos.Delta(z);
}

Void CCamera::GetCAProperty(
	/* [in] */ APType type,
	/* [out] */ IAProperty** ppIAProperty)
{
	switch (type) {
		case AP_X:
			*ppIAProperty = &xPos;
			break;
		case AP_Y:
			*ppIAProperty = &yPos;
			break;
		case AP_Z:
			*ppIAProperty = &zPos;
			break;
		case AP_RX:
			*ppIAProperty = &xRot;
			break;
		case AP_RY:
			*ppIAProperty = &yRot;
			break;
		case AP_RZ:
			*ppIAProperty = &zRot;
			break;
		case AP_CamAtX:
			*ppIAProperty = &xLookAt;
			break;
		case AP_CamAtY:
			*ppIAProperty = &yLookAt;
			break;
		case AP_CamAtZ:
			*ppIAProperty = &zLookAt;
			break;
		case AP_CamFOV:
			*ppIAProperty = &fov;
			break;
	}
}

xr_state CCamera::GetPosition(
	/* [in] */ Float32 *x,
	/* [in] */ Float32 *y,
	/* [in] */ Float32 *z)
{
	*x = this->xPos.Get();
	*y = this->yPos.Get();
	*z = this->zPos.Get();
	return XR_OK;
}

xr_state CCamera::GetLookAt(		
	/* [in] */ Float32 *vx,
	/* [in] */ Float32 *vy,
	/* [in] */ Float32 *vz)
{
	*vx = this->xLookAt.Get();
	*vy = this->yLookAt.Get();
	*vz = this->zLookAt.Get();
	return XR_OK;
}
