//-----------------------------------------------------------------------------
// Copyright (c) 2006-2008 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#if !defined(CAMERA_H)
#define CAMERA_H

#include "../Common/XRVector.h"

//-----------------------------------------------------------------------------
// A general purpose 6DoF (six degrees of freedom) XRQuaternion based camera.
//
// This camera class supports 2 different behaviors:
// first person mode, and flight mode.
//
// First person mode only allows 5DOF (x axis movement, y axis movement, z axis
// movement, yaw, and pitch) and movement is always parallel to the world x-z
// (ground) plane.
//
// Flight mode supports 6DoF. This is the camera class' default behavior.
//
// This camera class allows the camera to be moved in 2 ways: using fixed
// step world units, and using a supplied velocity and acceleration. The former
// simply moves the camera by the specified amount. To move the camera in this
// way call one of the move() methods. The other way to move the camera
// calculates the camera's displacement based on the supplied velocity,
// acceleration, and elapsed time. To move the camera in this way call the
// updatePosition() method.
//-----------------------------------------------------------------------------

class Camera
{
public:

    Camera();
    ~Camera();

    void lookAt(float ex, float ey, float ez, float tx, float ty, float tz);
	void lookAt(XRVec3 &eye, XRVec3 &target, XRVec3 &up);
	void setPos(float x, float y, float z);


    void perspective(float fovx, float aspect, float znear, float zfar);
	void orthognal(float l, float r, float t, float b, float n, float f);

	Void Move(float x, float y, float z);
	Void GetMoveAroundVal(float x, float y, float z, float* ox, float* oy, float* oz);

    void RotateAround(float headingDegrees, float pitchDegrees);
	void setFov(float fov) { m_fovx = fov; updateProjectionMatrix(); }
    // Getter methods.
	void SetRightHanded(bool rhs) { m_rh = rhs; }
    const XRQuaternion &getOrientation() const;
    const XRVec3 &getPosition() const;
    const XRMat4 &getProjectionMatrix() const;
    const XRVec3 &getViewDirection() const;
    const XRMat4 &getViewMatrix() const;
    const XRVec3 &getXAxis() const;
    const XRVec3 &getYAxis() const;
    const XRVec3 &getZAxis() const;
    
    // Setter methods.

    void setOrientation(const XRQuaternion &orientation);
    void setPosition(float x, float y, float z);
    void setPosition(const XRVec3 &position);
	void setProjectionMatrix(float* pMatrix, bool transpose);
private:
	void rotateView(float headingDegrees, float pitchDegrees, float rollDegrees);

    void updateViewMatrix();
    void updateViewMatrix(XRQuaternion& orientation);
	void updateProjectionMatrix();

    static const float DEFAULT_FOVX;
    static const float DEFAULT_ZFAR;
    static const float DEFAULT_ZNEAR;
    static const XRVec3 WORLD_XAXIS;
    static const XRVec3 WORLD_YAXIS;
    static const XRVec3 WORLD_ZAXIS;

    float m_fovx;
    float m_znear;
    float m_zfar;
    float m_aspectRatio;
    float m_accumPitchDegrees;

	Boolean		m_rh;
	XRVec3 m_PosAt;
	XRVec3 m_LookAt;
    XRVec3 m_xAxis;
    XRVec3 m_yAxis;
    XRVec3 m_zAxis;
    XRVec3 m_viewDir;
    XRQuaternion m_orientation;
    XRMat4 m_viewMatrix;
    XRMat4 m_projMatrix;
};

//-----------------------------------------------------------------------------


inline const XRQuaternion &Camera::getOrientation() const
{ return m_orientation; }

inline const XRVec3 &Camera::getPosition() const
{ return m_PosAt; }

inline const XRMat4 &Camera::getProjectionMatrix() const
{ return m_projMatrix; }

inline const XRVec3 &Camera::getViewDirection() const
{ return m_viewDir; }

inline const XRMat4 &Camera::getViewMatrix() const
{ return m_viewMatrix; }

inline const XRVec3 &Camera::getXAxis() const
{ return m_xAxis; }

inline const XRVec3 &Camera::getYAxis() const
{ return m_yAxis; }

inline const XRVec3 &Camera::getZAxis() const
{ return m_zAxis; }

#endif