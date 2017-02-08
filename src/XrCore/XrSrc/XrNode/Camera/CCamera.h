#ifndef __CCAMERA_H__
#define __CCAMERA_H__
#include "../../Common/XrInternal.h"
#include "../../External/ICamera.h"
#include "../../3rd/Camera.h"
#include "../Animation/CAProperty.h"
#include "../CBaseNode.h"

class CCamera: public ICamera, public CBaseNode<CCamera>
{
public:
	CCamera();
	//CNode(Float32 x, Float32 y, Float32 z, Float32 scale, ModelType type, CMaterial* mtl=0);
	~CCamera();
	
	virtual void Set2DCamera(bool camera_flag);
    virtual xr_state SetPosition(
        /* [in] */ Float32 x,
		/* [in] */ Float32 y,
        /* [in] */ Float32 z);

    virtual xr_state MovePosition(
        /* [in] */ Float32 x,
        /* [in] */ Float32 y,
		/* [in] */ Float32 z);
	
    virtual xr_state SetOrientation(
        /* [in] */ Float32 head,
        /* [in] */ Float32 pitch,
		/* [in] */ Float32 roll);

	virtual void SetPerspective(
		/* [in] */ Float32 fovx, 
		/* [in] */ Float32 aspect, 
		/* [in] */ Float32 znear, 
		/* [in] */ Float32 zfar);

	virtual Void SetFOV(
		/* [in] */ Float32 fov);

	virtual Void SetFOVDelta(
		/* [in] */ Float32 fov);

	virtual Void SetCustomProjectionMatrix(
		/* [in] */ Float32* pMatrix,
		/* [in] */ Boolean transpose);

	virtual void SetOrthognal(
		/* [in] */ Float32 l, 
		/* [in] */ Float32 r, 
		/* [in] */ Float32 t, 
		/* [in] */ Float32 b, 
		/* [in] */ Float32 n, 
		/* [in] */ Float32 f);

	virtual Void LookAt(
		/* [in] */ Float32 x, 
		/* [in] */ Float32 y, 
		/* [in] */ Float32 z);

	virtual Void LockLookAt(
		/* [in] */ Boolean flag);

	virtual Void RotateAround(
		/* [in] */ Float32 x, 
		/* [in] */ Float32 y);

	virtual Void RotateAroundDelta(
		/* [in] */ Float32 dx, 
		/* [in] */ Float32 dy);

	virtual Void MoveAround(
		/* [in] */ Float32 x, 
		/* [in] */ Float32 y);

	virtual Void MoveAroundDelta(
		/* [in] */ Float32 dx, 
		/* [in] */ Float32 dy);

	virtual Void GetCAProperty(
		/* [in] */ APType type,
		/* [out] */ IAProperty** ppIAProperty);

	virtual xr_state GetPosition(
		/* [in] */ Float32 *x,
		/* [in] */ Float32 *y,
		/* [in] */ Float32 *z);

	virtual xr_state GetLookAt(		
		/* [in] */ Float32 *vx,
		/* [in] */ Float32 *vy,
		/* [in] */ Float32 *vz);

	const XRMat4& GetViewMatrix();
	const XRMat4& GetProjectionMatrix();

	Void Flush();
	Void SetNeedUpdate() { m_needUpdate = TRUE; }

	CAProperty						xLookAt;
	CAProperty						yLookAt;
	CAProperty						zLookAt;
	CAProperty						xPos;
	CAProperty						yPos;
	CAProperty						zPos;
	CAProperty						xRot;	//for lookAround
	CAProperty						yRot;
	CAProperty						zRot;

	CAProperty						fov;

private:
	Camera					m_camera;
	AnimationStyle			m_transitionStyle;
	UInt32					m_transitionDuration;
	Boolean					m_lockLookAt;
	Boolean					m_2Dmode;
	Boolean                  m_2DAVMmode;
	Boolean					m_needUpdate;
};

#endif  //__CCAMERA_H__

