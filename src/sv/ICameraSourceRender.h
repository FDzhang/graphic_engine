#ifndef __ICAMERA_SOURCE_RENDER_H__
#define __ICAMERA_SOURCE_RENDER_H__
 #include "../XrCore/XrSrc/External/XrHeaders.h"

class ICameraSourceRender
{
public:

    virtual unsigned char GetShaderName(
        /* [out] */ char *pVertexShader,
        /* [in] 0---3d vertex shader  1---3d fragment shader  2---2d vertex shader  3---2d fragment shader*/ int type)=0;

    virtual void SetCameraSourceToMaterial(
        /* [in] */ IMaterial *pMaterial,int index)=0;


    virtual int GetCameraSourceTextureId(
        /* [in] */ int index)=0;

    virtual void UpdateCameraSource(int index,unsigned int texBuffer)=0;

	virtual Void UseCameraTexture(
               /*[in]*/int index)=0;
	
	virtual Void UseCameraMaskTexture(
               /*[in]*/int index)=0;

	virtual void SetCameraSourceMask(int textureid,int camera_index)=0;

	virtual void Init(char *file_path) = 0;
};

#endif  //__ICAMERA_H__

