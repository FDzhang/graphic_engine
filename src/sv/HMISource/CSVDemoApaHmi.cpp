/*===========================================================================*\
 * FILE: CSVDemoApaHmi.cpp
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
#include "CSVDemoApaHmi.h"
#include "gpu_log.h"

typedef enum DemoApaParkingPlotDirctTag
{
	DEMO_APA_RIGHT_PARKING_PLOT = 0,
	DEMO_APA_LEFT_PARKING_PLOT,	
}
DemoApaParkingPlotDirctT;

typedef enum DemoApaParkingPlotColorTag
{
	DEMO_APA_PARKING_PLOT_DEFAULT_COLOR = 0,
	DEMO_APA_PARKING_PLOT_COLOR_RED = 2,	
	DEMO_APA_PARKING_PLOT_COLOR_GREEN = 4,
}
DemoApaParkingPlotColorT;



CSVDemoApaHmi::CSVDemoApaHmi(IUINode *pUiNode, int pUiNodeId) : ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	for(int i = DEMO_APA_STATUS_BAR_BKG; i < DEMO_APA_ICON_NUMS; i++)
    {
    	m_trigger[i] = NULL;
		m_baseButton[i] = NULL;
	}
	
    memset(m_buttonVisibility, 1, DEMO_APA_ICON_NUMS * sizeof(unsigned char));

    memset(m_buttonImage, 0, DEMO_APA_ICON_NUMS * sizeof(unsigned char));

	m_processBar = NULL;
	m_bevParkingLot[0] = NULL;

	m_bevParkingLotTexture[0] = 0;
	m_bevParkingLotVisibility[0] = 0;

}

CSVDemoApaHmi::~CSVDemoApaHmi()
{
/*	for(int i = 1; i< DEMO_APA_GEAR_STATE_NUMS; i++)
	{
		SAFE_DELETE(m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[i])
	}
	for(int i = 1; i< DEMO_APA_DIRECTION_NUMS; i++)
	{
		SAFE_DELETE(m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[i])
	}
	for(int i = 1; i< DEMO_APA_STATUS_NUMS; i++)
	{
		SAFE_DELETE(m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[i])
	}
	for(int i = 1; i< DEMO_APA_ASSISTANT_ALGO_NUMS; i++)
	{
		SAFE_DELETE(m_baseButtonData[DEMO_APA_ALGO_PROMPT].icon_file_name[i])
	}
	SAFE_DELETE(m_baseButtonData[DEMO_APA_ANIMATION_AREA_CAR].icon_file_name[1])
	for(int i = 1; i< DEMO_APA_ANIMATION_LEFT_STATUS_NUMS; i++)
	{
		SAFE_DELETE(m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[i])
	}
	for(int i = 1; i< DEMO_APA_ANIMATION_RIGHT_STATUS_NUMS; i++)
	{
		SAFE_DELETE(m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[i])
	}
	for(int i = 1; i< DEMO_APA_ANIMATION_GUIDELINE_NUMS; i++)
	{
		SAFE_DELETE(m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[i])
	}
	for(int i = 0; i < DEMO_APA_BEV_PARKING_PLOT_NUM; i++)
	{
		for(int j=0;j<6;j++)
		{
			SAFE_DELETE(m_bevParkingLotData[i].fillTextureName[j])
		}
	}
	
	SAFE_DELETE(m_processBarData.iconFileName[PROCESS_BAR])
	SAFE_DELETE(m_processBarData.iconFileName[PROCESS_BAR_BACKGROUND])
*/	
    for (int i = DEMO_APA_STATUS_BAR_BKG; i < DEMO_APA_ICON_NUMS; i++)
    {
        SAFE_DELETE(m_baseButton[i])
		//SAFE_DELETE(m_baseButtonData[i].icon_file_name[0])
		//SAFE_DELETE(m_trigger[i])
    }

	SAFE_DELETE(m_bevParkingLot[0])

	SAFE_DELETE(m_processBar)
	

	Log_Error("---------~CSVDemoApaHmi");
}

void CSVDemoApaHmi::SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight)
{
    m_buttonSize[pIconIndex][BUTTON_SIZE_WIDTH] = pIconWidth;
    m_buttonSize[pIconIndex][BUTTON_SIZE_HEIGHT] = pIconHeight;
    m_buttonPos[pIconIndex][BUTTON_POS_X] = pIconPosX;
    m_buttonPos[pIconIndex][BUTTON_POS_Y] = pIconPosY;
}

int CSVDemoApaHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;

    float heightInterval = 80.0;
    float stitchRegionWidth = window_width * 0.35;
    float stitchRegionHeight = window_height - 2.0 * heightInterval;
    float iconHInterval = 30.0;
    float iconVInterval = 20.0;
    float left_panel_width = 100.0;

    SetHmiElementProperty(DEMO_APA_STATUS_BAR_BKG, stitchRegionWidth + left_panel_width, heightInterval, window_width - stitchRegionWidth - left_panel_width, 138.0);

    m_buttonSize[DEMO_APA_GEAR_PROMPT][BUTTON_SIZE_WIDTH] = 34;
    m_buttonSize[DEMO_APA_GEAR_PROMPT][BUTTON_SIZE_HEIGHT] = 35;
    m_buttonPos[DEMO_APA_GEAR_PROMPT][BUTTON_POS_X] = m_buttonPos[DEMO_APA_STATUS_BAR_BKG][BUTTON_POS_X] + 80;
    m_buttonPos[DEMO_APA_GEAR_PROMPT][BUTTON_POS_Y] = m_buttonPos[DEMO_APA_STATUS_BAR_BKG][BUTTON_POS_Y] + (m_buttonSize[DEMO_APA_STATUS_BAR_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DEMO_APA_GEAR_PROMPT][BUTTON_SIZE_HEIGHT]) * 0.5;
	
    m_buttonSize[DEMO_APA_DIRECTION_PROMPT][BUTTON_SIZE_WIDTH] = 27;
    m_buttonSize[DEMO_APA_DIRECTION_PROMPT][BUTTON_SIZE_HEIGHT] = 46;
	m_buttonPos[DEMO_APA_DIRECTION_PROMPT][BUTTON_POS_X] = m_buttonPos[DEMO_APA_GEAR_PROMPT][BUTTON_POS_X] + m_buttonSize[DEMO_APA_GEAR_PROMPT][BUTTON_SIZE_WIDTH] + 60;
	m_buttonPos[DEMO_APA_DIRECTION_PROMPT][BUTTON_POS_Y] = m_buttonPos[DEMO_APA_STATUS_BAR_BKG][BUTTON_POS_Y] + (m_buttonSize[DEMO_APA_STATUS_BAR_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DEMO_APA_DIRECTION_PROMPT][BUTTON_SIZE_HEIGHT]) * 0.5;

	float animation_width = 286;
	float animation_height = 132;
	float animation_pos_x = stitchRegionWidth + left_panel_width + (window_width - stitchRegionWidth - left_panel_width - animation_width)*0.5;
	float animation_pos_y = heightInterval;
	for(int i = DEMO_APA_ANIMATION_AREA; i <= DEMO_APA_ANIMATION_AREA_GUIDELINE; i++)
	{
	    SetHmiElementProperty(i, animation_pos_x, animation_pos_y, animation_width, animation_height);
	}

	m_processBarData.width = 135.0;
	m_processBarData.height = 14.0;
	m_processBarData.pos[0] = stitchRegionWidth + left_panel_width + (window_width - stitchRegionWidth - left_panel_width - m_processBarData.width)*0.5;
	m_processBarData.pos[1] = m_buttonPos[DEMO_APA_ANIMATION_AREA][BUTTON_POS_Y] + m_buttonSize[DEMO_APA_ANIMATION_AREA][BUTTON_SIZE_HEIGHT] - m_processBarData.height + 2.0;
	m_processBarData.withBkgFlag = 1;
	m_processBarData.withBarIconFlag = 0;

	m_buttonSize[DEMO_APA_ALGO_PROMPT][BUTTON_SIZE_WIDTH] = 42;
	m_buttonSize[DEMO_APA_ALGO_PROMPT][BUTTON_SIZE_HEIGHT] = 36;
	m_buttonPos[DEMO_APA_ALGO_PROMPT][BUTTON_POS_X] = m_screenWidth - m_buttonSize[DEMO_APA_ALGO_PROMPT][BUTTON_SIZE_WIDTH] - 80;
	m_buttonPos[DEMO_APA_ALGO_PROMPT][BUTTON_POS_Y] = m_buttonPos[DEMO_APA_STATUS_BAR_BKG][BUTTON_POS_Y] + (m_buttonSize[DEMO_APA_STATUS_BAR_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DEMO_APA_ALGO_PROMPT][BUTTON_SIZE_HEIGHT]) * 0.5;

	m_buttonSize[DEMO_APA_STATUS_PROMPT][BUTTON_SIZE_WIDTH] = 47;
	m_buttonSize[DEMO_APA_STATUS_PROMPT][BUTTON_SIZE_HEIGHT] = 44;
	m_buttonPos[DEMO_APA_STATUS_PROMPT][BUTTON_POS_X] = m_buttonPos[DEMO_APA_ALGO_PROMPT][BUTTON_POS_X] - m_buttonSize[DEMO_APA_STATUS_PROMPT][BUTTON_SIZE_WIDTH] - 60;
	m_buttonPos[DEMO_APA_STATUS_PROMPT][BUTTON_POS_Y] = m_buttonPos[DEMO_APA_STATUS_BAR_BKG][BUTTON_POS_Y] + (m_buttonSize[DEMO_APA_STATUS_BAR_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DEMO_APA_STATUS_PROMPT][BUTTON_SIZE_HEIGHT]) * 0.5;

	for(int i = 0; i < DEMO_APA_BEV_PARKING_PLOT_NUM; i++)
	{
		m_bevParkingLotData[i].renderRegion = REGION_BEV_APA_PARKING_LOT;
		CAvmRenderDataBase::GetInstance()->GetStitchViewNode(&(m_bevParkingLotData[i].renderNode));
		m_bevParkingLotData[i].polygonVertexNum = 8;
		m_bevParkingLotData[i].fillTextureName[0] = new char[100];
		sprintf(m_bevParkingLotData[i].fillTextureName[DEMO_APA_PARKING_PLOT_DEFAULT_COLOR],"%sCar/APA/apa_right_parking_lot_normal.dds",XR_RES);
		m_bevParkingLotData[i].fillTextureName[1] = new char[100];
		sprintf(m_bevParkingLotData[i].fillTextureName[DEMO_APA_PARKING_PLOT_DEFAULT_COLOR + 1],"%sCar/APA/apa_left_parking_lot_normal.dds",XR_RES);	
		m_bevParkingLotData[i].fillTextureName[2] = new char[100];
		sprintf(m_bevParkingLotData[i].fillTextureName[DEMO_APA_PARKING_PLOT_COLOR_RED],"%sCar/APA/apa_right_parking_lot_red.dds",XR_RES);
		m_bevParkingLotData[i].fillTextureName[3] = new char[100];
		sprintf(m_bevParkingLotData[i].fillTextureName[DEMO_APA_PARKING_PLOT_COLOR_RED + 1],"%sCar/APA/apa_left_parking_lot_red.dds",XR_RES);	
		m_bevParkingLotData[i].fillTextureName[4] = new char[100];
		sprintf(m_bevParkingLotData[i].fillTextureName[DEMO_APA_PARKING_PLOT_COLOR_GREEN],"%sCar/APA/apa_right_parking_lot_green.dds",XR_RES);
		m_bevParkingLotData[i].fillTextureName[5] = new char[100];
		sprintf(m_bevParkingLotData[i].fillTextureName[DEMO_APA_PARKING_PLOT_COLOR_GREEN + 1],"%sCar/APA/apa_left_parking_lot_green.dds",XR_RES);	


		m_bevParkingLotData[i].fillTextureIndex = 0;
		m_bevParkingLotData[i].materialType = Material_Rigid_Blend;
	}
	

    SetHmiParams();
}

int CSVDemoApaHmi::SetHmiParams()
{
    m_baseButtonData[DEMO_APA_STATUS_BAR_BKG].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_STATUS_BAR_BKG].show_flag = 1;
    m_baseButtonData[DEMO_APA_STATUS_BAR_BKG].show_icon_num = 0;
    m_baseButtonData[DEMO_APA_STATUS_BAR_BKG].icon_file_name[0] = new char [50];
    sprintf(m_baseButtonData[DEMO_APA_STATUS_BAR_BKG].icon_file_name[0],"%sCar/APA/apa_status_bar_bkg.dds",XR_RES);
	m_buttonVisibility[DEMO_APA_STATUS_BAR_BKG] = 1;
	m_buttonImage[DEMO_APA_STATUS_BAR_BKG] = 0;

	m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_GEAR_PROMPT].show_flag = 1;
    m_baseButtonData[DEMO_APA_GEAR_PROMPT].show_icon_num = 0;
    m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[DEMO_APA_GEAR_P] = new char [50];
	m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[DEMO_APA_GEAR_R] = new char [50];
	m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[DEMO_APA_GEAR_N] = new char [50];
	m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[DEMO_APA_GEAR_D] = new char [50];
    sprintf(m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[DEMO_APA_GEAR_P],"%sCar/APA/apa_gear_p.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[DEMO_APA_GEAR_R],"%sCar/APA/apa_gear_r.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[DEMO_APA_GEAR_N],"%sCar/APA/apa_gear_n.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_GEAR_PROMPT].icon_file_name[DEMO_APA_GEAR_D],"%sCar/APA/apa_gear_d.dds",XR_RES);

	m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].show_flag = 1;
    m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].show_icon_num = 0;
    m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_FRONT] = new char [50];
	m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_FRONT_LEFT] = new char [50];
	m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_FRONT_RIGHT] = new char [50];
	m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_REAR] = new char [50];
	m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_REAR_LEFT] = new char [50];
	m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_REAR_RIGHT] = new char [50];	
	sprintf(m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_FRONT],"%sCar/APA/apa_toward_front.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_FRONT_LEFT],"%sCar/APA/apa_toward_front_left.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_FRONT_RIGHT],"%sCar/APA/apa_toward_front_right.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_REAR],"%sCar/APA/apa_toward_rear.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_REAR_LEFT],"%sCar/APA/apa_toward_rear_left.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_DIRECTION_PROMPT].icon_file_name[DEMO_APA_REAR_RIGHT],"%sCar/APA/apa_toward_rear_right.dds",XR_RES);

	m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_STATUS_PROMPT].show_flag = 1;
    m_baseButtonData[DEMO_APA_STATUS_PROMPT].show_icon_num = 0;
    m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_SEARCHING_PARKING_PLACE] = new char [100];
	m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_PARKING] = new char [100];
	m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_SUCCEEDED] = new char [100];
	m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_FAILED] = new char [100];
	m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_PLEASE_BRAKE] = new char [100];
	m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_HITCH] = new char [100];
	sprintf(m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_SEARCHING_PARKING_PLACE],"%sCar/APA/apa_searching_parking_place.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_PARKING],"%sCar/APA/apa_parking.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_SUCCEEDED],"%sCar/APA/apa_parking_succeeded.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_FAILED],"%sCar/APA/apa_parking_failed.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_PLEASE_BRAKE],"%sCar/APA/apa_please_brake.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_STATUS_PROMPT].icon_file_name[DEMO_APA_HITCH],"%sCar/APA/apa_hitch.dds",XR_RES);

	m_baseButtonData[DEMO_APA_ALGO_PROMPT].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_ALGO_PROMPT].show_flag = 0;
    m_baseButtonData[DEMO_APA_ALGO_PROMPT].show_icon_num = 0;
    m_baseButtonData[DEMO_APA_ALGO_PROMPT].icon_file_name[DEMO_APA_OBSTACLE_PEDESTRIAN] = new char [100];
	m_baseButtonData[DEMO_APA_ALGO_PROMPT].icon_file_name[DEMO_APA_OBSTACLE_BICYCLE] = new char [100];
	sprintf(m_baseButtonData[DEMO_APA_ALGO_PROMPT].icon_file_name[DEMO_APA_OBSTACLE_PEDESTRIAN],"%sCar/APA/apa_obstacle_pedestrian.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ALGO_PROMPT].icon_file_name[DEMO_APA_OBSTACLE_BICYCLE],"%sCar/APA/apa_obstacle_bicycle.dds",XR_RES);
	m_buttonVisibility[DEMO_APA_ALGO_PROMPT] = 0;
	m_buttonImage[DEMO_APA_ALGO_PROMPT] = 0;

	m_baseButtonData[DEMO_APA_ANIMATION_AREA].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA].show_flag = 1;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA].show_icon_num = 0;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA].icon_file_name[0] = new char [50];
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA].icon_file_name[0],"%sCar/APA/apa_animation_area.dds",XR_RES);
	m_buttonVisibility[DEMO_APA_ANIMATION_AREA] = 1;
	m_buttonImage[DEMO_APA_ANIMATION_AREA] = 0;

	m_baseButtonData[DEMO_APA_ANIMATION_AREA_CAR].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA_CAR].show_flag = 1;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA_CAR].show_icon_num = 0;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA_CAR].icon_file_name[0] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_CAR].icon_file_name[1] = new char [100];
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_CAR].icon_file_name[0],"%sCar/APA/apa_forward_car.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_CAR].icon_file_name[1],"%sCar/APA/apa_backward_car.dds",XR_RES);
	m_buttonVisibility[DEMO_APA_ANIMATION_AREA_CAR] = 1;
	m_buttonImage[DEMO_APA_ANIMATION_AREA_CAR] = 0;

	m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_type = STATIC_ICON;
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].show_flag = 0;
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].show_icon_num = 0;
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[DEMO_APA_FORWARD_SEARCHING_LEFT_PLACE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[DEMO_APA_BACKWARD_SEARCHING_LEFT_PLACE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[DEMO_APA_FORWARD_LEFT_PLACE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[DEMO_APA_BACKWARD_LEFT_PLACE] = new char [100];
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[DEMO_APA_FORWARD_SEARCHING_LEFT_PLACE],"%sCar/APA/apa_forward_searching_left_place.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[DEMO_APA_BACKWARD_SEARCHING_LEFT_PLACE],"%sCar/APA/apa_backward_searching_left_place.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[DEMO_APA_FORWARD_LEFT_PLACE],"%sCar/APA/apa_forward_left_place.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS].icon_file_name[DEMO_APA_BACKWARD_LEFT_PLACE],"%sCar/APA/apa_backward_left_place.dds",XR_RES);
	m_buttonVisibility[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS] = 1;
	m_buttonImage[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS] = 0;

	m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].show_flag = 0;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].show_icon_num = 0;
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[DEMO_APA_FORWARD_SEARCHING_RIGHT_PLACE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[DEMO_APA_BACKWARD_SEARCHING_RIGHT_PLACE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[DEMO_APA_FORWARD_RIGHT_PLACE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[DEMO_APA_BACKWARD_RIGHT_PLACE] = new char [100];
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[DEMO_APA_FORWARD_SEARCHING_RIGHT_PLACE],"%sCar/APA/apa_forward_searching_right_place.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[DEMO_APA_BACKWARD_SEARCHING_RIGHT_PLACE],"%sCar/APA/apa_backward_searching_right_place.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[DEMO_APA_FORWARD_RIGHT_PLACE],"%sCar/APA/apa_forward_right_place.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS].icon_file_name[DEMO_APA_BACKWARD_RIGHT_PLACE],"%sCar/APA/apa_backward_right_place.dds",XR_RES);
	m_buttonVisibility[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS] = 1;
	m_buttonImage[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS] = 0;

	m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_type = STATIC_ICON;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].show_flag = 0;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].show_icon_num = 0;
    m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[DEMO_APA_ANIMATION_FORWARD_LEFT_GUIDELINE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[DEMO_APA_ANIMATION_FORWARD_RIGHT_GUIDELINE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[DEMO_APA_ANIMATION_BACKWARD_LEFT_GUIDELINE] = new char [100];
	m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[DEMO_APA_ANIMATION_BACKWARD_RIGHT_GUIDELINE] = new char [100];
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[DEMO_APA_ANIMATION_FORWARD_LEFT_GUIDELINE],"%sCar/APA/apa_forward_left_guideline.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[DEMO_APA_ANIMATION_FORWARD_RIGHT_GUIDELINE],"%sCar/APA/apa_forward_right_guideline.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[DEMO_APA_ANIMATION_BACKWARD_LEFT_GUIDELINE],"%sCar/APA/apa_backward_left_guideline.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_APA_ANIMATION_AREA_GUIDELINE].icon_file_name[DEMO_APA_ANIMATION_BACKWARD_RIGHT_GUIDELINE],"%sCar/APA/apa_backward_right_guideline.dds",XR_RES);
	m_buttonVisibility[DEMO_APA_ANIMATION_AREA_GUIDELINE] = 0;
	m_buttonImage[DEMO_APA_ANIMATION_AREA_GUIDELINE] = 0;
	
	m_processBarData.iconFileName[PROCESS_BAR] = new char[100];
	sprintf(m_processBarData.iconFileName[PROCESS_BAR],"%sCar/APA/apa_processbar_blue.dds",XR_RES); 
	m_processBarData.iconFileName[PROCESS_BAR_BACKGROUND] = new char[100];
	sprintf(m_processBarData.iconFileName[PROCESS_BAR_BACKGROUND],"%sCar/APA/apa_processbar_gray.dds",XR_RES);
	m_processBarVisibility = 1;

    for(int i = DEMO_APA_STATUS_BAR_BKG; i < DEMO_APA_ICON_NUMS; i++)
    {
        m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
        m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
        m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
        m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
        m_baseButtonData[i].delegate_func = NULL;
        m_baseButtonData[i].trigger = m_trigger[i];
		if(m_baseButton[i] == NULL)
        	m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
        m_baseButton[i]->SetVisibility(0);
    }

	if(m_processBar == NULL)
		m_processBar = new HmiProcessBar(&m_processBarData, m_uiNode);
	m_processBar->SetVisibility(0);

	if(m_bevParkingLot[0] == NULL)
 		m_bevParkingLot[0] = new HMIPolygonBox(&m_bevParkingLotData[0]);
	m_bevParkingLot[0]->SetVisibility(m_bevParkingLotVisibility[0]);	

	
    return DEMO_APA_HMI_NORMAL;
}

int CSVDemoApaHmi::Update(Hmi_Message_T &hmiMsg)
{
	if(m_bevParkingLot[0])
	{
		ProcessApa();
		m_bevParkingLot[0]->SetPolygonBoxImage(m_bevParkingLotTexture[0]);
		m_bevParkingLot[0]->SetVisibility(m_bevParkingLotVisibility[0]);
	}
	
	for(int i = DEMO_APA_STATUS_BAR_BKG; i < DEMO_APA_ICON_NUMS; i++)
	{
		if(m_baseButton[i])
		{
			m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
			m_baseButton[i]->SetShowIconNum(m_buttonImage[i]);
			m_baseButton[i]->Update();
		}
	}

	if(m_processBar)
	{
		m_processBar->SetVisibility(m_processBarVisibility);
		m_processBar->Update();
	}	
    return DEMO_APA_HMI_NORMAL;
}

int CSVDemoApaHmi::ProcessApa()
{
    unsigned char gear_state;
    AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
	if(gear_state == GEAR_P)
    {
        m_buttonImage[DEMO_APA_GEAR_PROMPT] = DEMO_APA_GEAR_P;
    }
	if(gear_state == GEAR_R)
    {
        m_buttonImage[DEMO_APA_GEAR_PROMPT] = DEMO_APA_GEAR_R;
    }
	if(gear_state == GEAR_N)
    {
        m_buttonImage[DEMO_APA_GEAR_PROMPT] = DEMO_APA_GEAR_N;
    }
	if(gear_state == GEAR_D)
    {
        m_buttonImage[DEMO_APA_GEAR_PROMPT] = DEMO_APA_GEAR_D;
    }

	APAOverlayStruct apaResult;
	CAvmRenderDataBase::GetInstance()->GetApaResult(&apaResult);

	static unsigned char enterParkingStatus = 0;
	
	if(apaResult.drive_dirction_indicat == DEMO_APA_DRIVE_BACKWARD)
	{
		m_buttonImage[DEMO_APA_DIRECTION_PROMPT] = DEMO_APA_REAR;
		m_buttonVisibility[DEMO_APA_DIRECTION_PROMPT] = 1;
		enterParkingStatus = 1;
	}
	else if(apaResult.drive_dirction_indicat == DEMO_APA_DRIVE_FOWARD)
	{
		m_buttonImage[DEMO_APA_DIRECTION_PROMPT] = DEMO_APA_FRONT;
		m_buttonVisibility[DEMO_APA_DIRECTION_PROMPT] = 1;
		enterParkingStatus = 1;
	}
	else
	{
		m_buttonVisibility[DEMO_APA_DIRECTION_PROMPT] = 0;
	}	

	//Log_Error("----------apaResult.drive_dirction_indicat = %d", apaResult.drive_dirction_indicat)
	if(apaResult.drive_dirction_indicat == DEMO_APA_DRIVE_NONE_DIRECT)
	{
		m_processBarVisibility = 0;
	}
	else
	{
		m_processBarVisibility = 1;
		m_processBar->Move(apaResult.scroll_rate, PROCESS_BAR_FORWARD);
	}

	float plotVertex[8] = {-3000,0,-100, 0,-3000,2000,-100,2000};

	//  2 - 3
	//  |   |
	//  0 - 1

	plotVertex[0] = apaResult.pParkLotPos[1] * 1000.0;	
	plotVertex[1] = apaResult.pParkLotPos[0] * 1000.0;
	plotVertex[2] = apaResult.pParkLotPos[3] * 1000.0;	
	plotVertex[3] = apaResult.pParkLotPos[2] * 1000.0;
	plotVertex[4] = apaResult.pParkLotPos[5] * 1000.0;	
	plotVertex[5] = apaResult.pParkLotPos[4] * 1000.0;
	plotVertex[6] = apaResult.pParkLotPos[7] * 1000.0;	
	plotVertex[7] = apaResult.pParkLotPos[6] * 1000.0;	

	/*for(int i = 0; i < 8; i++)
	{
		Log_Error("----plotVertex[%d]: %0.5f", i, plotVertex[i]);
	}*/

	static unsigned char parkingPlotDirect = DEMO_APA_RIGHT_PARKING_PLOT;
	float swapValue[2] = {0.0, 0.0};
	if(enterParkingStatus == 0)
	{
		if(plotVertex[0] < 0.0)
		{
			parkingPlotDirect = DEMO_APA_LEFT_PARKING_PLOT;
			//Log_Error("--------------DEMO_APA_LEFT_PARKING_PLOT");
		}
		else
		{
			parkingPlotDirect = DEMO_APA_RIGHT_PARKING_PLOT;
			//Log_Error("--------------DEMO_APA_RIGHT_PARKING_PLOT");
		}
	}

	//Log_Error("parking_lot_detect_flag: %d",apaResult.parking_lot_detect_flag);

	if(apaResult.stop_sign_flag == 1)
	{
		m_buttonImage[DEMO_APA_STATUS_PROMPT] = DEMO_APA_PLEASE_BRAKE;
	}
	else
	{
		m_buttonImage[DEMO_APA_STATUS_PROMPT] = DEMO_APA_PARKING;
	}

	if(apaResult.parking_lot_detect_flag == 1)
	{
		m_buttonImage[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS] = DEMO_APA_FORWARD_SEARCHING_LEFT_PLACE;
		m_buttonVisibility[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS] = 1;
		m_buttonImage[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS] = DEMO_APA_FORWARD_SEARCHING_RIGHT_PLACE;
		m_buttonVisibility[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS] = 1;
		m_buttonImage[DEMO_APA_STATUS_PROMPT] = DEMO_APA_SEARCHING_PARKING_PLACE;
		//m_buttonVisibility[DEMO_APA_ANIMATION_AREA_GUIDELINE] = 0;
		
	}
	else if(apaResult.parking_lot_detect_flag == 0)
	{
		m_buttonVisibility[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS] = 0;
		m_buttonVisibility[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS] = 0;
	}

	if(apaResult.end_parking_sign_flag == 1)
	{
		m_buttonImage[DEMO_APA_STATUS_PROMPT] = DEMO_APA_SUCCEEDED;
	}

	
	if(apaResult.park_lot_flag == DEMO_APA_NO_PARKING_PLOT)
	{
		m_bevParkingLotVisibility[0] = 0;
	}
	else 
	{
		m_bevParkingLotVisibility[0] = 1;
		if(apaResult.park_lot_flag == DEMO_APA_PARKABLE_PARK_LOT)
		{
			if(parkingPlotDirect == DEMO_APA_RIGHT_PARKING_PLOT)
			{
				m_bevParkingLotTexture[0] = DEMO_APA_PARKING_PLOT_DEFAULT_COLOR;
				//m_buttonImage[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS] = DEMO_APA_FORWARD_RIGHT_PLACE;
				//m_buttonVisibility[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS] = 1;
				//m_buttonVisibility[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS] = 0;
				//m_buttonVisibility[DEMO_APA_ANIMATION_AREA_GUIDELINE] = 1;
				//m_buttonImage[DEMO_APA_ANIMATION_AREA_GUIDELINE] = DEMO_APA_ANIMATION_FORWARD_LEFT_GUIDELINE;
			}
			else
			{
				m_bevParkingLotTexture[0] = DEMO_APA_PARKING_PLOT_DEFAULT_COLOR + 1;
				//m_buttonImage[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS] = DEMO_APA_FORWARD_LEFT_PLACE;
				//m_buttonVisibility[DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS] = 1;
				//m_buttonVisibility[DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS] = 0;
				//m_buttonVisibility[DEMO_APA_ANIMATION_AREA_GUIDELINE] = 1;
				//m_buttonImage[DEMO_APA_ANIMATION_AREA_GUIDELINE] = DEMO_APA_ANIMATION_FORWARD_RIGHT_GUIDELINE;
			}
		}
		else if(apaResult.park_lot_flag == DEMO_APA_UNPARKABLE_PARK_LOT)
		{
			if(parkingPlotDirect == DEMO_APA_RIGHT_PARKING_PLOT)
			{
				m_bevParkingLotTexture[0] = DEMO_APA_PARKING_PLOT_COLOR_RED;
			}
			else
			{
				m_bevParkingLotTexture[0] = DEMO_APA_PARKING_PLOT_COLOR_RED + 1;	
			}

		}
		else
		{
			if(parkingPlotDirect == DEMO_APA_RIGHT_PARKING_PLOT)
			{
				m_bevParkingLotTexture[0] = DEMO_APA_PARKING_PLOT_COLOR_GREEN;
			}
			else
			{
				m_bevParkingLotTexture[0] = DEMO_APA_PARKING_PLOT_COLOR_GREEN + 1;	
			}	
		}
		if(parkingPlotDirect == DEMO_APA_LEFT_PARKING_PLOT)
		{
			swapValue[0] = plotVertex[0];
			swapValue[1] = plotVertex[1];
			plotVertex[0] = plotVertex[2];
			plotVertex[1] = plotVertex[3];
			plotVertex[2] = swapValue[0];
			plotVertex[3] = swapValue[1];

			swapValue[0] = plotVertex[4];
			swapValue[1] = plotVertex[5];
			plotVertex[4] = plotVertex[6];
			plotVertex[5] = plotVertex[7];
			plotVertex[6] = swapValue[0];
			plotVertex[7] = swapValue[1];
		}
		//Log_Error("--------parkingPlotDirect: %d, m_bevParkingLotTexture: %d", parkingPlotDirect, m_bevParkingLotTexture[0]);
		m_bevParkingLot[0]->Update(plotVertex);
	}
	
    return DEMO_APA_HMI_NORMAL;
}

int CSVDemoApaHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return DEMO_APA_HMI_NORMAL;
}

int CSVDemoApaHmi::SetElementsVisibility(unsigned char pFlag)
{
    return DEMO_APA_HMI_NORMAL;
}

int CSVDemoApaHmi::DestroyHmiElems()
{
    return DEMO_APA_HMI_NORMAL;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  1/4/18   Hangman Zhu   Create the CSVDemoApaHmi class.
\*===========================================================================*/
