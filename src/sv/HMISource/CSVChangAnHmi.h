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
	CCAG_CTA_WARNING_CAR,
	CCAG_CTA_SINGLEVIEW_LEFT_WARNING,
	CCAG_CTA_SINGLEVIEW_RIGHT_WARNING,
	CCAG_CTA_AVMVIEW_LEFT_WARNING,
	CCAG_CTA_AVMVIEW_RIGHT_WARNING,	
    CCAG_ICON_NUMS,
}
Changan_Main_Screen_Hmi_Tag;

typedef enum Cta_Warning_Flag_Tag
{
	CCAG_CTA_NO_WARNIING = 0,
	CCAG_CTA_LEFT_WARNIING,
	CCAG_CTA_RIGHT_WARNIING,
	CCAG_CTA_ALL_WARNIING,
}
Cta_Warning_Flag_T;

typedef enum Changan_Track_Cam_Region_Index_Tag
{
    CCAG_TRACK_CAMERA_REGION_FRONT = 0,
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


typedef enum Changan_Cam_Region_Index_Tag
{
    CCAG_CAMERA_REGION_FRONT = 9,
    CCAG_CAMERA_REGION_REAR,
    CCAG_CAMERA_REGION_LEFT,
    CCAG_CAMERA_REGION_RIGHT,

}
Changan_Cam_Region_Index_T;


enum
{
	CAR_RECT_X = 246,
	CAR_RECT_Y = 310,
	CAR_RECT_WIDTH = 130,
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
    virtual int Update(Hmi_Message_T& hmiMsg);
    virtual int ReturnHmiMsg(Hmi_Message_T* pHmiMsg);
	virtual int MockTouchEvent(Hmi_Message_T& hmiMsg);
private:
	int SetSurroundViewCamElem();
	int ProcessAvmStatus();
	int ProcessIconTouchEvent();
	int ProcessTrackCamRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action);
	int ProcessCarRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action);
	int SetElemProperty();
	bool SetCustomView(unsigned char viewIndex);
	unsigned char GetCustomView();
	int InitCtaElem(Hmi_Message_T* pHmiMsg);
	int UpdateCtaElem(Hmi_Message_T* pHmiMsg);

private:
	Hmi_Button_Data_T ccagIconData[CCAG_ICON_NUMS];
    HMIButton* ccagIcon[CCAG_ICON_NUMS];
	
	int m_stitchRegionWidth;
	int m_stitchRegionHeight;

	int m_window_width;
	int m_window_height;

	int m_touchPressIndex;
	int m_lastTouchPressIndex;

	unsigned char m_cta_warning_car_showFlag;
	unsigned char m_cta_warning_left_showFlag;
	unsigned char m_cta_warning_right_showFlag;

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

	static unsigned char m_currentViewState;
        static unsigned char m_storeTrackRegion;
    
};


#endif //_CSV_CHANGAN_H_
