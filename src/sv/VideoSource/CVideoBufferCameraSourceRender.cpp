/*===========================================================================*\
 * FILE: template.c
 *===========================================================================
 * Copyright 2008 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *
 * ABBREVIATIONS:
 *   TODO: List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     TODO: Update list of design document(s)
 *
 *   Requirements Document(s):
 *     TODO: Update list of requirements document(s)
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "CVideoBufferCameraSourceRender.h"
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../fileloader.h"
#include "../DataStruct.h"
#include "../videoloader.h"
/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/
extern IDeviceManager* rm;

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/
class VideoBufferTextureDelegate : public ITextureDelegate
{
public:
	VideoBufferTextureDelegate(Int32 id) { m_id = id; }
	virtual xr_state OnCreate(
		/* [in] */ Int32 width,
		/* [in] */ Int32 height,
		/* [in] */ UInt32 format,
		/* [in/out] */ CTexture* pTexture)
	{
		pTexture->format = format;
		pTexture->width = width;
		pTexture->height = height;
		pTexture->texid = GenVideoBufferTexture(m_id);

		return XR_OK;
	}

	virtual xr_state OnUpdate()
	{
		GLint Tmpe = 8;
		#ifdef WIN32
		UpdateVideoBufferTexture(m_id);
         #endif
		return XR_OK;
	}
	virtual xr_state OnRelease()
	{
		return XR_OK;
	}

	virtual Boolean NeedUpdate()
	{
		return TRUE;
	}

	Int32 m_id;

};
	


/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * External Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/
static char *m_ShaderName[6]={"OVVertShaderNew.vtx","OVFragShaderbg.frg","OVVertShaderSV2D.vtx","OVFragShaderSV2D.frg","OVVertShaderNew.vtx","OVFragShaderbg.frg"};

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/

void CVideoBufferCameraSourceRender::Init(char *file_path)
{
    memcpy(m_file_path,file_path,MAX_NAME_LENGTH*sizeof(char));
	char video_path[80] = "./svres/";
	#ifdef WIN_32
	//InitVideo(video_path);
    #endif
	ITextureDelegate* tdelegate[4];

	for (int i=0;i<4;i++) {
		tdelegate[i] = new VideoBufferTextureDelegate(i);
		
		m_texture_index[i] = rm->CreateStreamingTexture(640, 480, XR_R8G8B8, tdelegate[i]);
	}   

	
    return;

}

void CVideoBufferCameraSourceRender::SetCameraSourceToMaterial(IMaterial *pMaterial,int camera_index)
{

	pMaterial->SetDiffuseMap(m_texture_index[camera_index]);
	m_texture_id[camera_index]= pMaterial->GetDiffuseMap()->texid;
	return;

}
void CVideoBufferCameraSourceRender::SetCameraSourceMask(int textureid,int camera_index)
{

	m_masktexture_id[camera_index]=textureid;
	return;

}

int CVideoBufferCameraSourceRender::GetCameraSourceTextureId(int index)
{
    return m_texture_id[index];

}

void CVideoBufferCameraSourceRender::UpdateCameraSource(int index,unsigned int texBuffer)
{
    return;
}

void CVideoBufferCameraSourceRender::UseCameraTexture(int index)
{
    if(index>=4)
    {
        index = 3;
    }
   	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_id[index]); 
}
  
void CVideoBufferCameraSourceRender::UseCameraMaskTexture(int index)
{
    if(index>=4)
    {
        index = 3;
    }

	 glActiveTexture(GL_TEXTURE1);
	 glBindTexture(GL_TEXTURE_2D, m_masktexture_id[index]);
}


unsigned char CVideoBufferCameraSourceRender::GetShaderName(char *pVertexShader,int type)
{
   // char *TempName[MAX_NAME_LENGTH];
	sprintf(pVertexShader,"%s%s",m_file_path,m_ShaderName[type]);

	return 0;
}

/*===========================================================================*\
 * External Function Definitions
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------

\*===========================================================================*/

