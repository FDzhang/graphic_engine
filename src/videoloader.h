#ifndef __GL_VIDEO_H__
#define __GL_VIDEO_H__
//#define STATIC_CALIBRATION
#ifdef __cplusplus
extern "C" {
#endif

class IVideoDelegate
{ 
public:
	virtual void OnFinish()=0; 
};

/****************************************************************************
**  
**	Function:				Init OpenGL Texture
**
**	Input:				vptr			-		twelve virtual address array
**
**	Output:				eglDisplay	-	Display context
**						
**
****************************************************************************/
int InitVideoTexture(void* eglDisplay);

void SetCurrentTextureVideo(int index);

int BindCurrentBuffer(unsigned int* Tex);

char* GetValidFilePath(char* path[], char* filename);
void SetCurrentTexturePA(int index);


void UpdateVideoTexture();

int GenVideoTexture(int id);


/****************************************************************************
**  
**	Function:				Get the new buffer/group index from the shared memory
**	
**	Input:				The channel Index to be get from
**
**   Return:				The buffer/group index (0 ~ 3) READY to be processed
**
****************************************************************************/
int GetBufferIndex(int channelIndex);


/****************************************************************************
**  
**	Function:				Bind Video Texture of the channel index
**
**   Input:				channel index, starting from 0
**
**
****************************************************************************/
void BindVideoTexture(int channelIndex);


/****************************************************************************
**  
**	Function:				Map the buffer's physical addresses to virtual addresses
**
**   Ouput:				The array holding 12 virtual addresses 
**
**	Return:				SUCCESS		0
**						FAILURE		-1
**
****************************************************************************/
int MapBufferVirtualAddress(void **vptr);



/****************************************************************************
**  
**	Function:				Copy data from source buffer to destination buffer, cache-coherence library is used 
**
**   Iuput:				src		-		Copy source buffer
**						dst		-		Copy destination buffer    [CAUTION]:   Address MUST be 64 bytes aligned !
**						length	-		The number of bytes to copy
**
**	Return:				A pointer to the destination buffer (that is, the value of dst).
**										
**
****************************************************************************/
void* memcpy_libcache(void* dst, const void* src, int length);


void Release();


#ifdef __cplusplus
}
#endif

#endif // __GL_VIDEO_H__
