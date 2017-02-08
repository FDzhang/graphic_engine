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
#include "CImageCameraSourceRender.h"
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../fileloader.h"
#include "../DataStruct.h"
/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/


/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * External Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/
static char *m_CamIMGName[4]={"front.bmp","rear.bmp","left.bmp","right.bmp"};	
static char *m_ShaderName[6]={"OVVertShaderNew.vtx","OVFragShader.frg","OVVertShaderSV2D.vtx","OVFragShaderSV2D.frg","OVVertShaderEmirror.vtx","OVFragEmirrorImg.frg"};

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/

void CImageCameraSourceRender::Init(char *file_path)
{
    memcpy(m_file_path,file_path,MAX_NAME_LENGTH*sizeof(char));
   
    return;

}

void CImageCameraSourceRender::SetCameraSourceToMaterial(IMaterial *pMaterial,int camera_index)
{
    char TempName[MAX_NAME_LENGTH];
	sprintf(&(TempName[0]),"%s%s",m_file_path,m_CamIMGName[camera_index]);
	pMaterial->SetDiffuseMap(TempName);
	m_texture_id[camera_index] = pMaterial->GetDiffuseMap()->texid;
	return;

}
void CImageCameraSourceRender::SetCameraSourceMask(int textureid,int camera_index)
{

	m_masktexture_id[camera_index]=textureid;
	return;

}

int CImageCameraSourceRender::GetCameraSourceTextureId(int index)
{
    return m_texture_id[index];

}

void CImageCameraSourceRender::UpdateCameraSource(int index,unsigned int texBuffer)
{
    return;
}

void CImageCameraSourceRender::UseCameraTexture(int index)
{
    if(index>=4)
    {
        index = 3;
    }
   	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture_id[index]); 
}
  
void CImageCameraSourceRender::UseCameraMaskTexture(int index)
{
    if(index>=4)
    {
        index = 3;
    }

	 glActiveTexture(GL_TEXTURE1);
	 glBindTexture(GL_TEXTURE_2D, m_masktexture_id[index]);
}


unsigned char CImageCameraSourceRender::GetShaderName(char *pVertexShader,int type)
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

