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



//void UpdateVideoTexture();

//int GenVideoTexture(int id);


int GenVideoBufferTexture(int id);
int UpdateVideoBufferTexture(int id);



#ifdef __cplusplus
}
#endif

#endif // __GL_VIDEO_H__
