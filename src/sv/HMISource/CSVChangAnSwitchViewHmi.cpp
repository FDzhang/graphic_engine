/*===========================================================================*\
 * FILE: CSVChangAnSwitchViewHmi.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
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
#include "CSVChangAnSwitchViewHmi.h"
#include "gpu_log.h"

extern float car_rect[4];
unsigned int CSVChangAnSwitchViewHmi::m_startCountTime = 0;
unsigned char CSVChangAnSwitchViewHmi::m_hasBeenTouched = 0;

class CFrontCamActionTrigger : public IActionTrigger
{
public:
	CFrontCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(FRONT_SINGLE_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CRearCamActionTrigger : public IActionTrigger
{
public:
	CRearCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(REAR_SINGLE_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CLeftCamActionTrigger : public IActionTrigger
{
public:
	CLeftCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(LEFT_SINGLE_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CRightCamActionTrigger : public IActionTrigger
{
public:
	CRightCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(RIGHT_SINGLE_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CTrackFrontCamActionTrigger : public IActionTrigger
{
public:
	CTrackFrontCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_REAR_3D_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CTrackRearCamActionTrigger : public IActionTrigger
{
public:
	CTrackRearCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(FRONT_3D_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CTrackLeftCamActionTrigger : public IActionTrigger
{
public:
	CTrackLeftCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_LEFT_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CTrackRightCamActionTrigger : public IActionTrigger
{
public:
	CTrackRightCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_RIGHT_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CTrackFrontLeftCamActionTrigger : public IActionTrigger
{
public:
	CTrackFrontLeftCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_LEFT_FRONT_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CTrackFrontRightCamActionTrigger : public IActionTrigger
{
public:
	CTrackFrontRightCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_RIGHT_FRONT_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CTrackRearLeftCamActionTrigger : public IActionTrigger
{
public:
	CTrackRearLeftCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_LEFT_REAR_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};

class CTrackRearRightCamActionTrigger : public IActionTrigger
{
public:
	CTrackRearRightCamActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_RIGHT_REAR_VIEW);
		CSVChangAnSwitchViewHmi::m_startCountTime = XrGetTime();
		CSVChangAnSwitchViewHmi::m_hasBeenTouched = 1;
	}


private:
};


CSVChangAnSwitchViewHmi::CSVChangAnSwitchViewHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	memset(m_trigger, NULL, CHANGAN_ICON_NUMS * sizeof(IActionTrigger*));
	
	memset(m_buttonVisibility, 1, CHANGAN_ICON_NUMS * sizeof(unsigned char));

	memset(m_buttonImage, 0, CHANGAN_ICON_NUMS * sizeof(unsigned char));

	m_cameraIconsVisibility = 1;

}

CSVChangAnSwitchViewHmi::~CSVChangAnSwitchViewHmi()
{
	for(int i = 0; i < CHANGAN_ICON_NUMS; i++)
	{
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);		
	    SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);		
		SAFE_DELETE(m_trigger[i]);
	    
		SAFE_DELETE(m_baseButton[i]);
	}
}
	
int CSVChangAnSwitchViewHmi::SetHmiParams()
{
	m_baseButtonData[CHANGAN_RED_TRACK].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_RED_TRACK].show_flag = 1;
	m_baseButtonData[CHANGAN_RED_TRACK].show_icon_num = 0;
    m_baseButtonData[CHANGAN_RED_TRACK].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_RED_TRACK].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_RED_TRACK].icon_file_name[0],"%sCar/red_track.dds",XR_RES);  //white_track
    sprintf(m_baseButtonData[CHANGAN_RED_TRACK].icon_file_name[1],"%sCar/white_track.dds",XR_RES);
	
	m_baseButtonData[CHANGAN_CAMERA_FRONT].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_CAMERA_FRONT].show_flag = 1;
	m_baseButtonData[CHANGAN_CAMERA_FRONT].show_icon_num = 0;
    m_baseButtonData[CHANGAN_CAMERA_FRONT].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_CAMERA_FRONT].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_CAMERA_FRONT].icon_file_name[0],"%sCar/rear_white_camera.dds",XR_RES);  //white_track
    sprintf(m_baseButtonData[CHANGAN_CAMERA_FRONT].icon_file_name[1],"%sCar/rear_yellow_camera.dds",XR_RES);
	m_trigger[CHANGAN_CAMERA_FRONT] = new CFrontCamActionTrigger;

	m_baseButtonData[CHANGAN_CAMERA_LEFT].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_CAMERA_LEFT].show_flag = 1;
	m_baseButtonData[CHANGAN_CAMERA_LEFT].show_icon_num = 0;
    m_baseButtonData[CHANGAN_CAMERA_LEFT].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_CAMERA_LEFT].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_CAMERA_LEFT].icon_file_name[0],"%sCar/rear_white_camera.dds",XR_RES);  //white_track
    sprintf(m_baseButtonData[CHANGAN_CAMERA_LEFT].icon_file_name[1],"%sCar/rear_yellow_camera.dds",XR_RES);
	m_trigger[CHANGAN_CAMERA_LEFT] = new CLeftCamActionTrigger;

	m_baseButtonData[CHANGAN_CAMERA_RIGHT].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_CAMERA_RIGHT].show_flag = 1;
	m_baseButtonData[CHANGAN_CAMERA_RIGHT].show_icon_num = 0;
    m_baseButtonData[CHANGAN_CAMERA_RIGHT].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_CAMERA_RIGHT].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_CAMERA_RIGHT].icon_file_name[0],"%sCar/rear_white_camera.dds",XR_RES);  //white_track
    sprintf(m_baseButtonData[CHANGAN_CAMERA_RIGHT].icon_file_name[1],"%sCar/rear_yellow_camera.dds",XR_RES);
	m_trigger[CHANGAN_CAMERA_RIGHT] = new CRightCamActionTrigger;

	m_baseButtonData[CHANGAN_CAMERA_REAR].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_CAMERA_REAR].show_flag = 1;
	m_baseButtonData[CHANGAN_CAMERA_REAR].show_icon_num = 0;
    m_baseButtonData[CHANGAN_CAMERA_REAR].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_CAMERA_REAR].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_CAMERA_REAR].icon_file_name[0],"%sCar/front_white_camera.dds",XR_RES);  //white_track
    sprintf(m_baseButtonData[CHANGAN_CAMERA_REAR].icon_file_name[1],"%sCar/front_yellow_camera.dds",XR_RES);
	m_trigger[CHANGAN_CAMERA_REAR] = new CRearCamActionTrigger;

	m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].show_flag = 0;
	m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].show_icon_num = 1;
    m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].icon_file_name[0],"%sCar/front_white_camera.dds",XR_RES);  //white_track
    sprintf(m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].icon_file_name[1],"%sCar/front_yellow_camera.dds",XR_RES);
	m_buttonImage[CHANGAN_TRACK_FRONT_CAMERA] = 1;
	m_trigger[CHANGAN_TRACK_FRONT_CAMERA] = new CTrackFrontCamActionTrigger;

	m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].show_flag = 0;
	m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].show_icon_num = 1;
    m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].icon_file_name[0],"%sCar/rear_white_camera.dds",XR_RES);  //white_track
    sprintf(m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].icon_file_name[1],"%sCar/rear_yellow_camera.dds",XR_RES);
	m_buttonImage[CHANGAN_TRACK_REAR_CAMERA] = 1;
	m_trigger[CHANGAN_TRACK_REAR_CAMERA] = new CTrackRearCamActionTrigger;

	m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].show_flag = 0;
	m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].show_icon_num = 1;
    m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].icon_file_name[0],"%sCar/left_white_camera.dds",XR_RES);
    sprintf(m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].icon_file_name[1],"%sCar/left_yellow_camera.dds",XR_RES);
	m_buttonImage[CHANGAN_TRACK_LEFT_CAMERA] = 1;
	m_trigger[CHANGAN_TRACK_LEFT_CAMERA] = new CTrackLeftCamActionTrigger;

	m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].show_flag = 0;
	m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].show_icon_num = 1;
    m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].icon_file_name[0],"%sCar/right_white_camera.dds",XR_RES);  
    sprintf(m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].icon_file_name[1],"%sCar/right_yellow_camera.dds",XR_RES);
	m_buttonImage[CHANGAN_TRACK_RIGHT_CAMERA] = 1;
	m_trigger[CHANGAN_TRACK_RIGHT_CAMERA] = new CTrackRightCamActionTrigger;

	m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].show_flag = 0;
	m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].show_icon_num = 1;
    m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].icon_file_name[0],"%sCar/front_left_white_camera.dds",XR_RES);  
    sprintf(m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].icon_file_name[1],"%sCar/front_left_yellow_camera.dds",XR_RES);
	m_buttonImage[CHANGAN_TRACK_FRONT_LEFT_CAMERA] = 1;
	m_trigger[CHANGAN_TRACK_FRONT_LEFT_CAMERA] = new CTrackFrontLeftCamActionTrigger;

	m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].show_flag = 0;
	m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].show_icon_num = 1;
    m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].icon_file_name[0],"%sCar/front_right_white_camera.dds",XR_RES);  
    sprintf(m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].icon_file_name[1],"%sCar/front_right_yellow_camera.dds",XR_RES);
	m_buttonImage[CHANGAN_TRACK_FRONT_RIGHT_CAMERA] = 1;
	m_trigger[CHANGAN_TRACK_FRONT_RIGHT_CAMERA] = new CTrackFrontRightCamActionTrigger;

	m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].show_flag = 0;
	m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].show_icon_num = 1;
    m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].icon_file_name[0],"%sCar/rear_left_white_camera.dds",XR_RES);  
    sprintf(m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].icon_file_name[1],"%sCar/rear_left_yellow_camera.dds",XR_RES);
	m_buttonImage[CHANGAN_TRACK_REAR_LEFT_CAMERA] = 1;
	m_trigger[CHANGAN_TRACK_REAR_LEFT_CAMERA] = new CTrackRearLeftCamActionTrigger;

	m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].show_flag = 0;
	m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].show_icon_num = 1;
    m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].icon_file_name[0] = new char [50];
	m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].icon_file_name[1] = new char [50];
	sprintf(m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].icon_file_name[0],"%sCar/rear_right_white_camera.dds",XR_RES);  
    sprintf(m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].icon_file_name[1],"%sCar/rear_right_yellow_camera.dds",XR_RES);
	m_buttonImage[CHANGAN_TRACK_REAR_RIGHT_CAMERA] = 1;
	m_trigger[CHANGAN_TRACK_REAR_RIGHT_CAMERA] = new CTrackRearRightCamActionTrigger;

	for(int i = CHANGAN_RED_TRACK; i < CHANGAN_ICON_NUMS; i++)
	{
		m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
		m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
		m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
		m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
		m_baseButtonData[i].delegate_func = NULL;
		m_baseButtonData[i].trigger = m_trigger[i];

		m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
		m_baseButton[i]->SetVisibility(0);
	}



	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}
int CSVChangAnSwitchViewHmi::Init(int window_width, int window_height)
{
	m_screenWidth = window_width;
	m_screenHeight = window_height;
	float leftPanelWidth = 0.0;//100.0;
	float heightInterval = 80.0;
	float stitchRegionWidth = window_width * 0.35;
	float stitchRegionHeight = window_height - 2.0 * heightInterval;
	
	m_buttonSize[CHANGAN_RED_TRACK][BUTTON_SIZE_WIDTH] = 378.0;
	m_buttonSize[CHANGAN_RED_TRACK][BUTTON_SIZE_HEIGHT] = 487.0;
	m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] = (stitchRegionWidth - m_buttonSize[CHANGAN_RED_TRACK][BUTTON_SIZE_WIDTH])/2.0 + leftPanelWidth;
	m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] = (window_height - m_buttonSize[CHANGAN_RED_TRACK][BUTTON_SIZE_HEIGHT])/2.0 + 0.0;

	m_buttonSize[CHANGAN_TRACK_FRONT_CAMERA][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_TRACK_FRONT_CAMERA][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_TRACK_FRONT_CAMERA][BUTTON_POS_X] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] + (378.0 - 64.0)/2;
	m_buttonPos[CHANGAN_TRACK_FRONT_CAMERA][BUTTON_POS_Y] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] - 8;

	m_buttonSize[CHANGAN_TRACK_REAR_CAMERA][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_TRACK_REAR_CAMERA][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_TRACK_REAR_CAMERA][BUTTON_POS_X] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] + (378.0 - 64.0)/2;
	m_buttonPos[CHANGAN_TRACK_REAR_CAMERA][BUTTON_POS_Y] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] + 487.0 - 64.0 + 8;

	m_buttonSize[CHANGAN_TRACK_LEFT_CAMERA][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_TRACK_LEFT_CAMERA][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_TRACK_LEFT_CAMERA][BUTTON_POS_X] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] - 10;
	m_buttonPos[CHANGAN_TRACK_LEFT_CAMERA][BUTTON_POS_Y] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] + (487.0 - 64.0)/2 + 4;

	m_buttonSize[CHANGAN_TRACK_RIGHT_CAMERA][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_TRACK_RIGHT_CAMERA][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_TRACK_RIGHT_CAMERA][BUTTON_POS_X] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] + (378.0 - 64.0) + 10;
	m_buttonPos[CHANGAN_TRACK_RIGHT_CAMERA][BUTTON_POS_Y] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] + (487.0 - 64.0)/2 + 3;

	m_buttonSize[CHANGAN_TRACK_FRONT_LEFT_CAMERA][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_TRACK_FRONT_LEFT_CAMERA][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_TRACK_FRONT_LEFT_CAMERA][BUTTON_POS_X] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] + 20.0;
	m_buttonPos[CHANGAN_TRACK_FRONT_LEFT_CAMERA][BUTTON_POS_Y] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] + 76.0;

	m_buttonSize[CHANGAN_TRACK_FRONT_RIGHT_CAMERA][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_TRACK_FRONT_RIGHT_CAMERA][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_TRACK_FRONT_RIGHT_CAMERA][BUTTON_POS_X] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] + 298.0;
	m_buttonPos[CHANGAN_TRACK_FRONT_RIGHT_CAMERA][BUTTON_POS_Y] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] + 76.0;

	m_buttonSize[CHANGAN_TRACK_REAR_LEFT_CAMERA][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_TRACK_REAR_LEFT_CAMERA][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_TRACK_REAR_LEFT_CAMERA][BUTTON_POS_X] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] + 21.0;
	m_buttonPos[CHANGAN_TRACK_REAR_LEFT_CAMERA][BUTTON_POS_Y] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] + 353.0;

	m_buttonSize[CHANGAN_TRACK_REAR_RIGHT_CAMERA][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_TRACK_REAR_RIGHT_CAMERA][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_TRACK_REAR_RIGHT_CAMERA][BUTTON_POS_X] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_X] + 292.0;
	m_buttonPos[CHANGAN_TRACK_REAR_RIGHT_CAMERA][BUTTON_POS_Y] = m_buttonPos[CHANGAN_RED_TRACK][BUTTON_POS_Y] + 350.0;

	m_buttonSize[CHANGAN_CAMERA_FRONT][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_CAMERA_FRONT][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_CAMERA_FRONT][BUTTON_POS_X] = (stitchRegionWidth - m_buttonSize[CHANGAN_CAMERA_FRONT][BUTTON_SIZE_WIDTH]) * 0.5 + leftPanelWidth;
	m_buttonPos[CHANGAN_CAMERA_FRONT][BUTTON_POS_Y] = (1.0 - car_rect[1]) * stitchRegionHeight/2.0 + heightInterval;

	m_buttonSize[CHANGAN_CAMERA_LEFT][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_CAMERA_LEFT][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_CAMERA_LEFT][BUTTON_POS_X] = (1.0 + car_rect[0]) * (stitchRegionWidth)/2.0 + leftPanelWidth - m_buttonSize[CHANGAN_CAMERA_LEFT][BUTTON_SIZE_WIDTH] + 18;
	m_buttonPos[CHANGAN_CAMERA_LEFT][BUTTON_POS_Y] = (1.0 - car_rect[3]) * (stitchRegionHeight)/2.0 + heightInterval - 2.0 * m_buttonSize[CHANGAN_CAMERA_LEFT][BUTTON_SIZE_HEIGHT];

	m_buttonSize[CHANGAN_CAMERA_RIGHT][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_CAMERA_RIGHT][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_CAMERA_RIGHT][BUTTON_POS_X] = (1.0 + car_rect[2]) * (stitchRegionWidth)/2.0 + leftPanelWidth - 18;
	m_buttonPos[CHANGAN_CAMERA_RIGHT][BUTTON_POS_Y] = (1.0 - car_rect[3]) * (stitchRegionHeight)/2.0 + heightInterval - 2.0 * m_buttonSize[CHANGAN_CAMERA_RIGHT][BUTTON_SIZE_HEIGHT];
	
	m_buttonSize[CHANGAN_CAMERA_REAR][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[CHANGAN_CAMERA_REAR][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[CHANGAN_CAMERA_REAR][BUTTON_POS_X] = (stitchRegionWidth - m_buttonSize[CHANGAN_CAMERA_REAR][BUTTON_SIZE_WIDTH]) * 0.5 + leftPanelWidth;
	m_buttonPos[CHANGAN_CAMERA_REAR][BUTTON_POS_Y] = (1.0 - car_rect[3]) * stitchRegionHeight/2.0 + heightInterval- m_buttonSize[CHANGAN_CAMERA_REAR][BUTTON_SIZE_HEIGHT];

    float carRectWidth = stitchRegionWidth*(car_rect[2]-car_rect[0])*0.8;
	float carRectHeight = stitchRegionWidth*(car_rect[1]-car_rect[3])*0.5;
	m_carRectSize[BUTTON_SIZE_WIDTH] = carRectWidth;
	m_carRectSize[BUTTON_SIZE_HEIGHT] = carRectHeight;
	m_carRectPos[BUTTON_POS_X] = (stitchRegionWidth - carRectWidth) * 0.5 + leftPanelWidth;
	m_carRectPos[BUTTON_POS_Y] = (1.0 - car_rect[1]) * stitchRegionHeight/2.0 + heightInterval + stitchRegionWidth*(car_rect[1]-car_rect[3])*0.35;

	SetHmiParams();
	
	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}
int CSVChangAnSwitchViewHmi::Update(Hmi_Message_T& hmiMsg)
{
    static unsigned int initStartCountTime = 0;
	if(initStartCountTime == 0)
	{
	    m_startCountTime = XrGetTime();
		initStartCountTime = 1;
	}

	unsigned char viewCmd;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(viewCmd);
	static unsigned char lastViewCmd = 200;

    if(m_hasBeenTouched == 0 && viewCmd != lastViewCmd)
	{
	    m_startCountTime = XrGetTime();
	}

	m_buttonImage[CHANGAN_CAMERA_FRONT] = 0;
	m_buttonImage[CHANGAN_CAMERA_REAR] = 0;
	m_buttonImage[CHANGAN_CAMERA_LEFT] = 0;
	m_buttonImage[CHANGAN_CAMERA_RIGHT] = 0;
	/*m_buttonImage[CHANGAN_TRACK_FRONT_CAMERA] = 0;
	m_buttonImage[CHANGAN_TRACK_REAR_CAMERA] = 0;
	m_buttonImage[CHANGAN_TRACK_LEFT_CAMERA] = 0;
	m_buttonImage[CHANGAN_TRACK_RIGHT_CAMERA] = 0;
	m_buttonImage[CHANGAN_TRACK_FRONT_LEFT_CAMERA] = 0;
	m_buttonImage[CHANGAN_TRACK_FRONT_RIGHT_CAMERA] = 0;
	m_buttonImage[CHANGAN_TRACK_REAR_LEFT_CAMERA] = 0;
	m_buttonImage[CHANGAN_TRACK_REAR_RIGHT_CAMERA] = 0;*/
	m_buttonVisibility[CHANGAN_TRACK_FRONT_CAMERA] = 0;
	m_buttonVisibility[CHANGAN_TRACK_REAR_CAMERA] = 0;
	m_buttonVisibility[CHANGAN_TRACK_LEFT_CAMERA] = 0;
	m_buttonVisibility[CHANGAN_TRACK_RIGHT_CAMERA] = 0;
	m_buttonVisibility[CHANGAN_TRACK_FRONT_LEFT_CAMERA] = 0;
	m_buttonVisibility[CHANGAN_TRACK_FRONT_RIGHT_CAMERA] = 0;
	m_buttonVisibility[CHANGAN_TRACK_REAR_LEFT_CAMERA] = 0;
	m_buttonVisibility[CHANGAN_TRACK_REAR_RIGHT_CAMERA] = 0;

	if(viewCmd == FRONT_SINGLE_VIEW)
	{
		m_buttonImage[CHANGAN_CAMERA_FRONT] = 1;
	}
	else if(viewCmd == REAR_SINGLE_VIEW)
	{
	    m_buttonImage[CHANGAN_CAMERA_REAR] = 1;
	}
	else if(viewCmd == LEFT_SINGLE_VIEW)
	{
	    m_buttonImage[CHANGAN_CAMERA_LEFT] = 1;
	}
	else if(viewCmd == RIGHT_SINGLE_VIEW)
	{
	    m_buttonImage[CHANGAN_CAMERA_RIGHT] = 1;
	}
	else if(viewCmd == BMW_REAR_3D_VIEW)
	{
	    m_buttonVisibility[CHANGAN_TRACK_FRONT_CAMERA] = 1;
	}
	else if(viewCmd == FRONT_3D_VIEW)
	{
	    m_buttonVisibility[CHANGAN_TRACK_REAR_CAMERA] = 1;
	}
	else if(viewCmd == BMW_LEFT_VIEW)
	{
	    m_buttonVisibility[CHANGAN_TRACK_LEFT_CAMERA] = 1;
	}
	else if(viewCmd == BMW_RIGHT_VIEW)
	{
	    m_buttonVisibility[CHANGAN_TRACK_RIGHT_CAMERA] = 1;
	}
	else if(viewCmd == BMW_LEFT_FRONT_VIEW)
	{
	    m_buttonVisibility[CHANGAN_TRACK_FRONT_LEFT_CAMERA] = 1;
	}
	else if(viewCmd == BMW_RIGHT_FRONT_VIEW)
	{
	    m_buttonVisibility[CHANGAN_TRACK_FRONT_RIGHT_CAMERA] = 1;
	}
	else if(viewCmd == BMW_LEFT_REAR_VIEW)
	{
	    m_buttonVisibility[CHANGAN_TRACK_REAR_LEFT_CAMERA] = 1;
	}
	else if(viewCmd == BMW_RIGHT_REAR_VIEW)
	{
	    m_buttonVisibility[CHANGAN_TRACK_REAR_RIGHT_CAMERA] = 1;
	}

	int x = 0;
	int y = 0;
	int touchType = 0;
	if(GetTouchEventInfo(x,y,touchType))
	{
		ProcessCarRegionTouchEvent(x,y,touchType);
		if(m_cameraIconsVisibility == 1)
		{
		    ProcessTrackCamRegionTouchEvent(x,y,touchType);
		}
	}

    m_currentTime = XrGetTime();
    if(m_hasBeenTouched == 1)
    {
		if(m_currentTime - m_startCountTime > 10000)
	    {
	        m_cameraIconsVisibility = 0;
			m_hasBeenTouched = 0;
	    }
		else
		{
		    m_cameraIconsVisibility = 1;
		}
    }
	else if(m_hasBeenTouched == 0)
	{
		if(m_currentTime - m_startCountTime > 2000)
		{
		    m_cameraIconsVisibility = 0;
		}
		else
		{
		    m_cameraIconsVisibility = 1;
		}
	}
	RefreshHmi();

	lastViewCmd = viewCmd;
		
	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}
int CSVChangAnSwitchViewHmi::RefreshHmi()
{
	for(int i = CHANGAN_RED_TRACK; i < CHANGAN_ICON_NUMS; i++)
	{
	    m_baseButton[i]->SetShowIconNum(m_buttonImage[i]);
		if(m_cameraIconsVisibility == 0)
		{
		    m_baseButton[i]->SetVisibility(0);
		}
		else if(m_cameraIconsVisibility == 1)
		{
		    m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		}
		m_baseButton[i]->Update();
	}

	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}
int CSVChangAnSwitchViewHmi::ProcessCarRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action)
{
	static int  touch_action = action;
	static int  touch_pos_x = 0;
	static int  touch_pos_y = 0;
	

	if(SCREEN_TOUCHED == touch_action)
	{
		touch_pos_x = pos_x;
		touch_pos_y = pos_y;
	}
	else
	{
		return CHANGAN_SWITCH_VIEW_HMI_NORMAL; 
	}


    if(touch_pos_x > m_carRectPos[BUTTON_POS_X]
        && touch_pos_x < m_carRectPos[BUTTON_POS_X] + m_carRectSize[BUTTON_SIZE_WIDTH]
        && touch_pos_y > m_carRectPos[BUTTON_POS_Y]
        && touch_pos_y < m_carRectPos[BUTTON_POS_Y] + m_carRectSize[BUTTON_SIZE_HEIGHT])
    {
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}

int CSVChangAnSwitchViewHmi::ProcessTrackCamRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action)
{
    static int  touch_action = action;
	static int  touch_pos_x = 0;
	static int  touch_pos_y = 0;
	

	if(SCREEN_TOUCHED == touch_action)
	{
		touch_pos_x = pos_x;
		touch_pos_y = pos_y;
	}
	else
	{
		return CHANGAN_SWITCH_VIEW_HMI_NORMAL; 
	}


    if(touch_pos_x > m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].pos[0]
        && touch_pos_x < m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].pos[0] + m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].width
        && touch_pos_y > m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].pos[1]
        && touch_pos_y < m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].pos[1] + m_baseButtonData[CHANGAN_TRACK_FRONT_CAMERA].height)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_REAR_3D_VIEW);
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	if(touch_pos_x > m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].pos[0]
        && touch_pos_x < m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].pos[0] + m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].width
        && touch_pos_y > m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].pos[1]
        && touch_pos_y < m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].pos[1] + m_baseButtonData[CHANGAN_TRACK_REAR_CAMERA].height)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(FRONT_3D_VIEW);
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	if(touch_pos_x > m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].pos[0]
        && touch_pos_x < m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].pos[0] + m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].width
        && touch_pos_y > m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].pos[1]
        && touch_pos_y < m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].pos[1] + m_baseButtonData[CHANGAN_TRACK_LEFT_CAMERA].height)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_LEFT_VIEW);
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	if(touch_pos_x > m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].pos[0]
        && touch_pos_x < m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].pos[0] + m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].width
        && touch_pos_y > m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].pos[1]
        && touch_pos_y < m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].pos[1] + m_baseButtonData[CHANGAN_TRACK_RIGHT_CAMERA].height)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_RIGHT_VIEW);
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	if(touch_pos_x > m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].pos[0]
        && touch_pos_x < m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].pos[0] + m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].width
        && touch_pos_y > m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].pos[1]
        && touch_pos_y < m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].pos[1] + m_baseButtonData[CHANGAN_TRACK_FRONT_LEFT_CAMERA].height)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_LEFT_FRONT_VIEW);
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	if(touch_pos_x > m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].pos[0]
        && touch_pos_x < m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].pos[0] + m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].width
        && touch_pos_y > m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].pos[1]
        && touch_pos_y < m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].pos[1] + m_baseButtonData[CHANGAN_TRACK_FRONT_RIGHT_CAMERA].height)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_RIGHT_FRONT_VIEW);
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	if(touch_pos_x > m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].pos[0]
        && touch_pos_x < m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].pos[0] + m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].width
        && touch_pos_y > m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].pos[1]
        && touch_pos_y < m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].pos[1] + m_baseButtonData[CHANGAN_TRACK_REAR_LEFT_CAMERA].height)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_LEFT_REAR_VIEW);
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	if(touch_pos_x > m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].pos[0]
        && touch_pos_x < m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].pos[0] + m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].width
        && touch_pos_y > m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].pos[1]
        && touch_pos_y < m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].pos[1] + m_baseButtonData[CHANGAN_TRACK_REAR_RIGHT_CAMERA].height)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(BMW_RIGHT_REAR_VIEW);
		m_cameraIconsVisibility = 1;
		m_startCountTime = XrGetTime();
        m_hasBeenTouched = 1;
    }

	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}

int CSVChangAnSwitchViewHmi::SetElementsVisibility(unsigned char pFlag)
{
	for(int i = CHANGAN_RED_TRACK; i < CHANGAN_ICON_NUMS; i++)
	{
        if(m_cameraIconsVisibility == 0 || pFlag == 0)
		{
		    m_baseButton[i]->SetVisibility(0);
		}
		else if(m_cameraIconsVisibility == 1)
		{
		    m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		}
	}

	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}

int CSVChangAnSwitchViewHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}
int CSVChangAnSwitchViewHmi::DestroyHmiElems()
{
	return CHANGAN_SWITCH_VIEW_HMI_NORMAL;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVChangAnSwitchViewHmi class.
\*===========================================================================*/
