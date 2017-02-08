#include "videoloader.h"
//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLES2/gl2ext.h>

//extern int currentIndex;
//extern GLuint *ptex_objs;
GLuint TextureBuffer[4];
extern int ConfirmImage10FileRegersted(void);
extern int ConfirmImage11FileRegersted(void);
extern int ConfirmImage12FileRegersted(void);
extern int ConfirmImage13FileRegersted(void);

int MapBufferVirtualAddress(void **vptr)
{
return 0;
			
}


#ifdef STATIC_CALIBRATION
#include"../gles_utility/PVRTTextureAPI.h"

GLuint	m_uiTexture[4];

const char c_szTextureFile13[]		= "Image13.pvr";  //bottom hmi
const char c_szTextureFile12[] 	=     "Image12.pvr";   //top hmi right
const char c_szTextureFile11[]		= "Image11.pvr";  //top hmii left
const char c_szTextureFile10[]		= "Image10.pvr";  //top hmi front

#endif


void Release()
{
	printf("release\n");

	//cache_fini(&cacheCtrl);
}

int InitVideoTexture(void* eglDisplay)
{
    int testTemp =0;

#ifdef STATIC_CALIBRATION
    testTemp =ConfirmImage10FileRegersted();
	printf("\r\n InitVideoTexture check number %d",testTemp);
    testTemp =ConfirmImage11FileRegersted();
	printf("\r\n InitVideoTexture check number %d",testTemp);
    testTemp =ConfirmImage12FileRegersted();
	printf("\r\n InitVideoTexture check number %d",testTemp);
    testTemp =ConfirmImage13FileRegersted();
	printf("\r\n InitVideoTexture check number %d",testTemp);

	if(PVRTTextureLoadFromPVR(c_szTextureFile10, &m_uiTexture[0]) != PVR_SUCCESS)
	{
		//PVRShellSet(prefExitMessage, "ERROR: Cannot load the texture10\n");
		
		printf("\r\n InitVideoTexture check number %d",testTemp);
		printf("\r\n InitVideoTexture could not load texture %s",c_szTextureFile10);
		return false;
	}	
	if(PVRTTextureLoadFromPVR(c_szTextureFile11, &m_uiTexture[1]) != PVR_SUCCESS)
	{
		//PVRShellSet(prefExitMessage, "ERROR: Cannot load the texture11\n");
		
		printf("\r\n InitVideoTexture check number %d",testTemp);
		printf("\r\n InitVideoTexture could not load texture %s",c_szTextureFile11);
		return false;
	}	
	if(PVRTTextureLoadFromPVR(c_szTextureFile12, &m_uiTexture[2]) != PVR_SUCCESS)
	{
		//PVRShellSet(prefExitMessage, "ERROR: Cannot load the texture12\n");
		
		printf("\r\n InitVideoTexture could not load texture %s",c_szTextureFile12);
		return false;
	}	
	if(PVRTTextureLoadFromPVR(c_szTextureFile13, &m_uiTexture[3]) != PVR_SUCCESS)
	{
		//PVRShellSet(prefExitMessage, "ERROR: Cannot load the texture13\n");
		
		printf("\r\n InitVideoTexture could not load texture %s",c_szTextureFile13);
		return false;
	}	
#endif


	return 0;
}


int GenVideoTexture(int id)
{
#if 0
	int i;
	glGenTextures(1, &tex[id]);

		//if(PVRTTextureLoadFromPVR(c_szImage[i], &m_uiTexture[i]) != PVR_SUCCESS) {
		//	return false;
		//}

		glBindTexture(GL_TEXTURE_2D, tex[id]);
		//SetCurrentTextureVideo(i);
		//UpdateCurrentTexture(i);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, video_width, video_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return tex[id];
#else
return 0;
#endif
}


void UpdateVideoTexture()
{	
	int i = 0;
}

void UpdateJ6VideoTexture(GLuint input[])
{	
	for(int i=0;i<4;i++)
	{
	   TextureBuffer[i]=input[i]; 
	  // printf("\r\n TexBuffer[%d] = %d",i,TextureBuffer[i]);
	}
}

int GetBufferIndex(int channelIndex)
{
	int bufIndex=0;

	return bufIndex;

	//return currentIndex[channelIndex];
}

void BindVideoTexture(int channelIndex)
{
    //printf("\r\n dynamic texture call channle [%d]",channelIndex);
    int real_chnl;
#ifdef STATIC_CALIBRATION
    glBindTexture(GL_TEXTURE_2D,m_uiTexture[channelIndex]);
   // printf("\r\n static texture");
#else
    if(channelIndex == 0)
    {
        real_chnl = 3;
    }
	else if(channelIndex == 1)
		{
			real_chnl = 2;
		}
	else
	{
	    real_chnl = channelIndex-2;
	}

	glBindTexture(GL_TEXTURE_EXTERNAL_OES,TextureBuffer[real_chnl]);
   // printf("\r\n dynamic texture call channle [%d]",channelIndex);

#endif
	//printf("\r\n BindVideoTexture[%d] = %d",channelIndex,TextureBuffer[channelIndex]);

      //  glBindTexture(GL_TEXTURE_STREAM_IMG, ptex_objs[channelIndex*6+currentIndex]);
//printf("bind idx=%d, chn=%d, texid=%d\n", currentIndex, channelIndex, ptex_objs[channelIndex*6+currentIndex]);
	//assert(currentIndex>=0 && currentIndex<=2);
	//glBindTexture(GL_TEXTURE_2D, videobufferTex[currentIndex[channelIndex]*NUM_VIDEO_CAP_CHN + channelIndex]);
}


