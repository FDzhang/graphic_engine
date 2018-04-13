#ifndef __SV_NODE_2D_STICH_NEW_H__
#define __SV_NODE_2D_STICH_NEW_H__

//#include "fileloader.h"
#include "DataStruct.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "vehicle_motion_model.h"
#include "TS_config.h"
#include "SVNode2DStich.h"
#include "SVTimeStitcher.h"


#define LEFT_BOTTOM_POINT_INDEX 2
#define RIGHT_BOTTOM_POINT_INDEX 3
#define LEFT_TOP_POINT_INDEX  0
#define RIGHT_TOP_POINT_INDEX 1

#define CAR_LENGTH 4.667f
#define CAR_WIDTH 1.839f



class SVNode2DStichNew : public SVNode2DStich
{
public:
	SVNode2DStichNew();

	virtual int Init();
	virtual int Update(float steering_wheel_angle,float vehicle_speed,float left_wheel_speed,float right_wheel_speed,unsigned char gear_state,int time_offset,float yaw_rate);
	int GetKeyFrameTextureId();
	int GetGroundTextureId();
	virtual int GetStichFrameTextureId();
	virtual void InitStichKeyFrameNodeRT(int j);

	virtual void Init2DGroundNodeRT(int j);
	
	int ProcessGroundCoord(float steering_wheel_angle,float vehicle_speed,float left_wheel_speed, float right_wheel_speed,unsigned char gear_state,int time_offset,float yaw_rate);
	virtual void UpdateGoundTextureCoord(GpuCvPoint2D32f *pTextureIndex);
	//Update(unsigned char update_key_flag)
	virtual int SetEnable(unsigned char flag);
	
	void UpdateStich2DReslt(int index);
	virtual void InitStichAreaRT(void);
	void CalcShadowTextureCoord(float *car_rect,float *shadow_rect,float *pshadow_texture);
	void Update2DStichRslt(void);
    
protected:
    void Cvt4Point2Rect(float *pPoint,GpuCvPoint2D32f *pRect);

    class SVTimeStitcher* m_svTimeStitcher;
	 
};

#endif //#ifndef __SV_NODE_2D_STICH_NEW_H__