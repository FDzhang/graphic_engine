#ifndef __CJ6_CAMERA_SOURCE_RENDER_H__
#define __CJ6_CAMERA_SOURCE_RENDER_H__

#include "../ICameraSourceRender.h"
#include "../DataStruct.h"
class CJ6CameraSourceRender: public ICameraSourceRender
{
public:

    virtual unsigned char GetShaderName(
        /* [out] */ char *pVertexShader,
        /* [in] */ int type);

    virtual void SetCameraSourceToMaterial(
        /* [in] */ IMaterial *pMaterial,int camera_index);
	
    virtual int GetCameraSourceTextureId(
        /* [in] */ int index);
	virtual void SetCameraSourceMask(int textureid,int camera_index);

    virtual void UpdateCameraSource(int index,unsigned int texBuffer);

	virtual Void UseCameraTexture(
               /*[in]*/int index);
	
	virtual Void UseCameraMaskTexture(
               /*[in]*/int index);


	virtual void Init(char *file_path);

private:
	char m_file_path[MAX_NAME_LENGTH];
	int m_texture_id[4];
	unsigned int m_texture_buffer[4];
	int m_texture_index[4];
	int m_masktexture_id[4];

};

#endif  

