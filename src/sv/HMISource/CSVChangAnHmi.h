#ifndef _CSV_CHANGAN_H_
#define _CSV_CHANGAN_H_

#include "ISVHmi.h"

typedef enum Changan_Basic_Elem_Params_Tag
{
	CCAG_ELEM_X = 0,
	CCAG_ELEM_Y,
	CCAG_ELEM_WIDTH,
	CCAG_ELEM_HEIGHT,
	CCAG_ELEM_NUMS,
}
Changan_Basic_Elem_Params_Tag;

typedef enum Changan_Main_Screen_Hmi_Tag
{
	CCAG_RED_TRACK,
    CCAG_RED_TRACK_CAMERA,
	CCAG_CAMERA_FRONT,
	CCAG_CAMERA_REAR,
	CCAG_CAMERA_LEFT,
	CCAG_CAMERA_RIGHT,
    CCAG_ICON_NUMS,
}
Changan_Main_Screen_Hmi_Tag;

typedef enum Changan_Track_Cam_Region_Index_Tag
{
    CCAG_TRACK_CAMERA_REGION_FRONT,
	CCAG_TRACK_CAMERA_REGION_REAR,
	CCAG_TRACK_CAMERA_REGION_LEFT,
	CCAG_TRACK_CAMERA_REGION_RIGHT,
	CCAG_TRACK_CAMERA_REGION_FRONT_LEFT,
	CCAG_TRACK_CAMERA_REGION_FRONT_RIGHT,
	CCAG_TRACK_CAMERA_REGION_REAR_LEFT,
	CCAG_TRACK_CAMERA_REGION_REAR_RIGHT,	
    CCAG_TRACK_CAMERA_REGION_NUMS,
}
Changan_Track_Cam_Region_Index_T;

enum
{
	CAR_RECT_X = 146,
	CAR_RECT_Y = 310,
	CAR_RECT_WIDTH = 100,
	CAR_RECT_HEIGHT = 100,
};

static int m_trackCamIconRegion[CCAG_TRACK_CAMERA_REGION_NUMS][CCAG_ELEM_NUMS] = {
	189,100,64,64,
	89,200,64,64,
	189,100,64,64,
	89,200,64,64,
	189,100,64,64,
	89,200,64,64,
	189,100,64,64,
	89,200,64,64,
};
static int m_trackCamRegion[CCAG_TRACK_CAMERA_REGION_NUMS][CCAG_ELEM_NUMS] = {
	189,100,64,64,
	89,200,64,64,
	189,100,64,64,
	89,200,64,64,
	189,100,64,64,
	89,200,64,64,
	189,100,64,64,
	89,200,64,64,
};

class CSVChanganHmi : public ISVHmi
{
public:

	CSVChanganHmi();
    virtual int Init(int window_width, int window_height);
    virtual int Update();
    virtual int ReturnHmiMsg(Hmi_Message_T* pHmiMsg);

private:
	int SetSurroundViewCamElem();
	int ProcessIconTouchEvent();
	int ProcessTrackCamRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action);
	int ProcessCarRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action);
	int SetElemProperty();

private:
	Hmi_Button_Data_T ccagIconData[CCAG_ICON_NUMS];
    HMIButton* ccagIcon[CCAG_ICON_NUMS];
	
	int m_stitchRegionWidth;
	int m_stitchRegionHeight;

public:	
	static unsigned char m_trackCamVisibility;
	static unsigned char m_trackVisibility;
	static unsigned char m_frontCamVisibility;
	static unsigned char m_rearCamVisibility;
	static unsigned char m_leftCamVisibility;
	static unsigned char m_rightCamVisibility;

	static unsigned char m_trackCamColor;
	static unsigned char m_trackColor;

	static unsigned char m_frontCamColor;
	static unsigned char m_rearCamColor;
	static unsigned char m_leftCamColor;
	static unsigned char m_rightCamColor;

	static float m_trackCamPosX;
	static float m_trackCamPosY;
	static unsigned int m_currentTrackCamRegionIndex;
	static unsigned int m_isTrackRegion;
	static unsigned int m_isCarRegion;
};


#endif //_CSV_CHANGAN_H_