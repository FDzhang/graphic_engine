#include "videoloader.h"
//#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>





unsigned int tex[4];
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

int GenVideoBufferTexture(int id)
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
		glTexImage2D(GL_TEXTURE_2D, 0, video_type, video_width, video_height, 0, video_type, GL_UNSIGNED_BYTE, NULL);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return tex[id];
	#endif
	return 0;
}

int UpdateVideoBufferTexture(int id)
{
#if 0
	currTime = GetTickCount();
	videoTime += currTime - lastTime;

	lastTime = currTime;


	GrabVideoBufferFrame(id);
#endif	
	return 0;
}





