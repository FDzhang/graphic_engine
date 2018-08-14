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

#include "Camera.h"
#include "../Render/XrRender.h"
//#include "GLUtility.h"

const float Camera::DEFAULT_FOVX = 90.0f;
const float Camera::DEFAULT_ZFAR = 1000.0f;
const float Camera::DEFAULT_ZNEAR = 0.1f;

const XRVec3 Camera::WORLD_XAXIS(1.0f, 0.0f, 0.0f);
const XRVec3 Camera::WORLD_YAXIS(0.0f, 1.0f, 0.0f);
const XRVec3 Camera::WORLD_ZAXIS(0.0f, 0.0f, 1.0f);

static float degreesToRadians(float degrees)
{
    return (degrees * 3.14159265f) / 180.0f;
}

static float radiansToDegrees(float radians)
{
    return (radians * 180.0f) / 3.14159265f;
}

Camera::Camera()
{
    m_fovx = DEFAULT_FOVX;
    m_znear = DEFAULT_ZNEAR;
    m_zfar = DEFAULT_ZFAR;
    m_aspectRatio = 0.0f;
    m_rh = 1;
    m_accumPitchDegrees = 0.0f;
    
    m_PosAt.Set(0.0f, 0.0f, 0.0f);
	m_PosAt.Set(0.0f, 0.0f, 0.0f);
	m_LookAt.Set(0.0f, 0.0f, 0.0f);
    m_xAxis.Set(1.0f, 0.0f, 0.0f);
    m_yAxis.Set(0.0f, 1.0f, 0.0f);
    m_zAxis.Set(0.0f, 0.0f, 1.0f);
    m_viewDir.Set(0.0f, 0.0f, -1.0f);
    
	XRQuaternionIdentity(m_orientation);

    m_viewMatrix.MakeIdentity();
    m_projMatrix.MakeIdentity();
}

Camera::~Camera()
{
}

void Camera::lookAt(float ex, float ey, float ez, float tx, float ty, float tz)
{
	XRVec3 eye(ex, ey, ez);
	XRVec3 target(tx, ty, tz);
	XRVec3 y(0, 1, 0);
	lookAt(eye, target, y);
}

void Camera::GetMoveAroundVal(float x, float y, float z, float* ox, float* oy, float* oz)
{
	XRVec4 move(x,y,z,1);
	XRVec4 out = move * m_viewMatrix;
	*ox = out.x; *oy = out.y; *oz = out.z; 
}

void Camera::lookAt(XRVec3 &eye, XRVec3 &target, XRVec3 &up)
{
	if (m_rh) {
		m_zAxis = eye - target;
	}
	else {
		m_zAxis = target - eye;
	}
    m_PosAt = eye;
	m_LookAt = target;
    
    m_zAxis.normalize();

    m_viewDir = -m_zAxis;

	m_xAxis = up.cross(m_zAxis);
    m_xAxis.normalize();

    m_yAxis = m_zAxis.cross(m_xAxis);
    m_yAxis.normalize();
    m_xAxis.normalize();

    m_viewMatrix[0][0] = m_xAxis.x;
    m_viewMatrix[1][0] = m_xAxis.y;
    m_viewMatrix[2][0] = m_xAxis.z;
    m_viewMatrix[3][0] = -m_xAxis.dot(eye);

    m_viewMatrix[0][1] = m_yAxis.x;
    m_viewMatrix[1][1] = m_yAxis.y;
    m_viewMatrix[2][1] = m_yAxis.z;
    m_viewMatrix[3][1] = -m_yAxis.dot(eye);

    m_viewMatrix[0][2] = m_zAxis.x;
    m_viewMatrix[1][2] = m_zAxis.y;
    m_viewMatrix[2][2] = m_zAxis.z;    
    m_viewMatrix[3][2] = -m_zAxis.dot(eye);



    // Extract the pitch angle from the view matrix.
    m_accumPitchDegrees = radiansToDegrees(asinf(m_viewMatrix[1][2]));

    XRMatrixToQuaternion(m_orientation, m_viewMatrix);

	updateViewMatrix();
}

void Camera::orthognal(float l, float r, float t, float b, float n, float f)
{
    m_projMatrix[0][0] = 2.0 / (r - l);
    m_projMatrix[0][1] = 0.0f;
    m_projMatrix[0][2] = 0.0f;
    m_projMatrix[0][3] = 0.0f;

    m_projMatrix[1][0] = 0.0f;
    m_projMatrix[1][1] = 2.0 / (t - b);
    m_projMatrix[1][2] = 0.0f;
    m_projMatrix[1][3] = 0.0f;

    m_projMatrix[2][0] = 0.0f;
    m_projMatrix[2][1] = 0.0f;

    m_projMatrix[2][3] = 0.0f;

    m_projMatrix[3][0] = -(r + l) / (r - l);
    m_projMatrix[3][1] = -(t + b) / (t - b);
   
    m_projMatrix[3][3] = 1.0f;

#ifdef USE_DX11
		m_projMatrix[2][2] = 1.0 / (f - n);
		m_projMatrix[3][2] =  -n / (f - n);
#else
		m_projMatrix[2][2] = 2.0 / (f - n);
		m_projMatrix[3][2] =  -(f + n) / (f - n);
#endif
}


void Camera::perspective(float fovx, float aspect, float znear, float zfar)
{
    // Construct a projection matrix based on the horizontal field of view
    // 'fovx' rather than the more traditional vertical field of view 'fovy'.

    m_fovx = fovx;
    m_aspectRatio = aspect;
    m_znear = znear;
    m_zfar = zfar;

	updateProjectionMatrix();
}
#if 1
void Camera::updateProjectionMatrix()
{
    float e = 1.0f / tanf(degreesToRadians(m_fovx) / 2.0f);
    float aspectInv = 1.0f / m_aspectRatio;
    float fovy = 2.0f * atanf(aspectInv / e);
    float xScale = 1.0f / tanf(0.5f * fovy);
    float yScale = xScale / aspectInv;

    m_projMatrix[0][0] = xScale;
    m_projMatrix[0][1] = 0.0f;
    m_projMatrix[0][2] = 0.0f;
    m_projMatrix[0][3] = 0.0f;

    m_projMatrix[1][0] = 0.0f;
    m_projMatrix[1][1] = yScale;
    m_projMatrix[1][2] = 0.0f;
    m_projMatrix[1][3] = 0.0f;

    m_projMatrix[2][0] = 0.0f;
    m_projMatrix[2][1] = 0.0f;
    
    m_projMatrix[2][3] = -1.0f;

    m_projMatrix[3][0] = 0.0f;
    m_projMatrix[3][1] = 0.0f;
    
    m_projMatrix[3][3] = 0.0f;

#ifdef USE_DX11
		m_projMatrix[2][2] = (m_zfar) / (m_znear - m_zfar);
		m_projMatrix[3][2] = (m_zfar * m_znear) / (m_znear - m_zfar);
#else
		m_projMatrix[2][2] = (m_zfar + m_znear) / (m_znear - m_zfar);
		m_projMatrix[3][2] = (2.0f * m_zfar * m_znear) / (m_znear - m_zfar);
#endif

	if (!m_rh)
	{
		m_projMatrix[2][2] = m_projMatrix[2][2]*(-1);
		m_projMatrix[2][3] = f2vt(1);
	}

}
#else

void Camera::updateProjectionMatrix()
{
    float e = 1.0f / tanf(degreesToRadians(m_fovx) / 2.0f);
    float aspectInv = 1.0f / m_aspectRatio;
    float fovy = 2.0f * atanf(aspectInv / e);
    float xScale = 1.0f / tanf(0.5f * fovy);
    float yScale = xScale / aspectInv;
#if 0
    m_projMatrix[0][0] = xScale;
    m_projMatrix[0][1] = 0.0f;
    m_projMatrix[0][2] = 0.0f;
    m_projMatrix[0][3] = 0.0f;

    m_projMatrix[1][0] = 0.0f;
    m_projMatrix[1][1] = yScale;
    m_projMatrix[1][2] = 0.0f;
    m_projMatrix[1][3] = 0.0f;

    m_projMatrix[2][0] = 0.0f;
    m_projMatrix[2][1] = 0.0f;
    
    m_projMatrix[2][3] = -1.0f;

    m_projMatrix[3][0] = 0.0f;
    m_projMatrix[3][1] = 0.0f;
    
    m_projMatrix[3][3] = 0.0f;

#ifdef USE_DX11
		m_projMatrix[2][2] = (m_zfar) / (m_znear - m_zfar);
		m_projMatrix[3][2] = (m_zfar * m_znear) / (m_znear - m_zfar);
#else
		m_projMatrix[2][2] = (m_zfar + m_znear) / (m_znear - m_zfar);
		m_projMatrix[3][2] = (2.0f * m_zfar * m_znear) / (m_znear - m_zfar);
#endif

	if (!m_rh)
	{
		m_projMatrix[2][2] = m_projMatrix[2][2]*(-1);
		m_projMatrix[2][3] = f2vt(1);
	}
#endif

   float n= m_znear;
   float f = m_zfar;
   float r = n*tanf(degreesToRadians(m_fovx) / 2.0f);
   float t = r*m_aspectRatio;

m_projMatrix[0][0] = n/r;
m_projMatrix[0][1] = 0.0f;
m_projMatrix[0][2] = 0.0f;
m_projMatrix[0][3] = 0.0f;

m_projMatrix[1][0] = 0.0f;
m_projMatrix[1][1] = n/t;
m_projMatrix[1][2] = 0.0f;
m_projMatrix[1][3] = 0.0f;

m_projMatrix[2][0] = 0.0f;
m_projMatrix[2][1] = 0.0f;
m_projMatrix[2][2] = -(f+n)/(f-n);

m_projMatrix[2][3] = -2*f*n/(f-n);

m_projMatrix[3][0] = 0.0f;
m_projMatrix[3][1] = 0.0f;
m_projMatrix[3][2] = -1.0f;
m_projMatrix[3][3] = 0.0f;
   
}
#endif

void Camera::RotateAround(float headingDegrees, float pitchDegrees)
{
    // Implements the rotation logic for the first person style and
    // spectator style camera behaviors. Roll is ignored.

    XRQuaternion rot;

    // Rotate camera about the world y axis.
    // Note the order the XRQuaternions are multiplied. That is important!

    //m_orientation.fromAxisAngle(WORLD_YAXIS, headingDegrees);
	
	float head, pitch, roll;
	XrQuaterniontoHeadPitchRoll(m_orientation, head, pitch, roll);
	head += degreesToRadians(headingDegrees);
	pitch += degreesToRadians(pitchDegrees);
	XrQuaternionFromHeadPitchRoll(rot, head, pitch, roll);
    // Rotate camera about its local x axis.
    // Note the order the XRQuaternions are multiplied. That is important!
    //rot.fromAxisAngle(WORLD_XAXIS, pitchDegrees);
   // m_orientation = m_orientation * rot;
	
	XRVec3 mag = m_LookAt - m_PosAt;

	float magnitude = mag.length();
	//float head,pitch,roll;
	//print("head=%f,pitch=%f,roll=%f\n",head,pitch,roll);
	m_PosAt.x = m_LookAt.x-cos(pitch) * sin(head) * magnitude;
    m_PosAt.y = m_LookAt.y+sin(pitch) * magnitude;
    m_PosAt.z = m_LookAt.z+cos(pitch) * cos(head) * magnitude;

	updateViewMatrix(rot);
}

void Camera::setPosition(float x, float y, float z)
{
    m_PosAt.Set(x, y, z);
    updateViewMatrix();
}

void Camera::setPosition(const XRVec3 &position)
{
    m_PosAt = position;
    updateViewMatrix();
}


void Camera::updateViewMatrix()
{
    // Reconstruct the view matrix.

	XRQuaternionToMatrix(m_viewMatrix, m_orientation);

    m_xAxis.Set(m_viewMatrix[0][0], m_viewMatrix[1][0], m_viewMatrix[2][0]);
    m_yAxis.Set(m_viewMatrix[0][1], m_viewMatrix[1][1], m_viewMatrix[2][1]);
    m_zAxis.Set(m_viewMatrix[0][2], m_viewMatrix[1][2], m_viewMatrix[2][2]);
    m_viewDir = -m_zAxis;

    m_viewMatrix[3][0] = -m_xAxis.dot(m_PosAt);
    m_viewMatrix[3][1] = -m_yAxis.dot(m_PosAt);
    m_viewMatrix[3][2] = -m_zAxis.dot(m_PosAt);
}

void Camera::updateViewMatrix(XRQuaternion& orientation)
{
    // Reconstruct the view matrix.
	XRQuaternionToMatrix(m_viewMatrix, orientation);

    m_xAxis.Set(m_viewMatrix[0][0], m_viewMatrix[1][0], m_viewMatrix[2][0]);
    m_yAxis.Set(m_viewMatrix[0][1], m_viewMatrix[1][1], m_viewMatrix[2][1]);
    m_zAxis.Set(m_viewMatrix[0][2], m_viewMatrix[1][2], m_viewMatrix[2][2]);
    m_viewDir = -m_zAxis;

    m_viewMatrix[3][0] = -m_xAxis.dot(m_PosAt);
    m_viewMatrix[3][1] = -m_yAxis.dot(m_PosAt);
    m_viewMatrix[3][2] = -m_zAxis.dot(m_PosAt);
}

void Camera::setProjectionMatrix(float* pMatrix, bool transpose)
{
	int x, y, i=0;
	for (x=0;x<4;x++) {
		for (y=0;y<4;y++) {
			if (transpose) m_projMatrix[y][x] = pMatrix[i];
			else m_projMatrix[x][y] = pMatrix[i];
			i++;
		}
	}
}