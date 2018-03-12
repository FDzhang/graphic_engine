/*===========================================================================*\
 * FILE: CSVDemoApaHmi.h
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

#ifndef _CSV_DEMO_APA_HMI_H_
#define _CSV_DEMO_APA_HMI_H_

#include "ISVHmi.h"

typedef enum DemoApaHmiElementTag {
    DEMO_APA_STATUS_BAR_BKG = 0,
	DEMO_APA_GEAR_PROMPT,
    DEMO_APA_DIRECTION_PROMPT,
    DEMO_APA_STATUS_PROMPT,
    //DEMO_APA_FAULT_PROMPT,
    DEMO_APA_ALGO_PROMPT,
    //DEMO_APA_PROCESS_PROMPT,
    DEMO_APA_ANIMATION_AREA,
    DEMO_APA_ANIMATION_AREA_CAR,
    DEMO_APA_ANIMATION_AREA_LEFT_APA_STATUS,
    DEMO_APA_ANIMATION_AREA_RIGHT_APA_STATUS,
    DEMO_APA_ANIMATION_AREA_GUIDELINE,
    DEMO_APA_ICON_NUMS,
} DemoApaHmiElementT;

typedef enum DemoApaHmiGearStateTag {
    DEMO_APA_GEAR_P,
    DEMO_APA_GEAR_R,
    DEMO_APA_GEAR_N,
    DEMO_APA_GEAR_D,
    DEMO_APA_GEAR_STATE_NUMS,
} DemoApaHmiGearStateT;

typedef enum DemoApaHmiDriveStateTag 
{
	DEMO_APA_DRIVE_BACKWARD = -1,
    DEMO_APA_DRIVE_NONE_DIRECT,
    DEMO_APA_DRIVE_FOWARD,
    DEMO_APA_DRIVE_STATE_NUMS,
} 
DemoApaHmiDriveStateT;


typedef enum DemoApaHmiDirectionTag {
    DEMO_APA_FRONT = 0,
    DEMO_APA_FRONT_LEFT,
    DEMO_APA_FRONT_RIGHT,
    DEMO_APA_REAR,
    DEMO_APA_REAR_LEFT,
    DEMO_APA_REAR_RIGHT,
    DEMO_APA_DIRECTION_NUMS,
} DemoApaHmiDirectionT;

typedef enum DemoApaHmiApaStatusTag {
    DEMO_APA_SEARCHING_PARKING_PLACE = 0,
    DEMO_APA_PARKING,
    DEMO_APA_SUCCEEDED,
    DEMO_APA_FAILED,
    DEMO_APA_PLEASE_BRAKE,
    DEMO_APA_HITCH,
    DEMO_APA_STATUS_NUMS,
} DemoApaHmiApaStatusT;

typedef enum DemoApaHmiAssistantAlgoTag {
    DEMO_APA_OBSTACLE_PEDESTRIAN = 0,
    DEMO_APA_OBSTACLE_BICYCLE,
    DEMO_APA_ASSISTANT_ALGO_NUMS,
} DemoApaHmiAssistantAlgoT;

typedef enum DemoApaParkingPlotTypeTag
{
	DEMO_APA_BEV_PARKING_PLOT = 0,
	DEMO_APA_PARKING_PLOT_TYPE_NUMS,
}
DemoApaParkingPlotTypeT;

typedef enum DemoApaPlotNumTag
{
	DEMO_APA_BEV_PARKING_PLOT_NUM = 1,
}
DemoApaParkingPlotNumT;

typedef enum DemoApaParkingPlotStatusTag
{
	DEMO_APA_NO_PARKING_PLOT = 0,
	DEMO_APA_PARKABLE_PARK_LOT,
	DEMO_APA_UNPARKABLE_PARK_LOT,
	DEMO_APA_UNLOCK_PARK_LOT,
	DEMO_APA_PARKING_PLOT_STATUS_NUM,	
}
DemoApaParkingPlotStatusT;

typedef enum DemoApaHmiAnimationLeftStatusTag {
    DEMO_APA_FORWARD_SEARCHING_LEFT_PLACE = 0,
    DEMO_APA_BACKWARD_SEARCHING_LEFT_PLACE,
    DEMO_APA_FORWARD_LEFT_PLACE,
    DEMO_APA_BACKWARD_LEFT_PLACE,
    DEMO_APA_ANIMATION_LEFT_STATUS_NUMS,
} DemoApaHmiAnimationLeftStatusT;

typedef enum DemoApaHmiAnimationRightStatusTag {
    DEMO_APA_FORWARD_SEARCHING_RIGHT_PLACE = 0,
    DEMO_APA_BACKWARD_SEARCHING_RIGHT_PLACE,
    DEMO_APA_FORWARD_RIGHT_PLACE,
    DEMO_APA_BACKWARD_RIGHT_PLACE,
    DEMO_APA_ANIMATION_RIGHT_STATUS_NUMS,
} DemoApaHmiAnimationRightStatusT;

typedef enum DemoApaHmiAnimationGuidelineTag {
    DEMO_APA_ANIMATION_FORWARD_LEFT_GUIDELINE = 0,
    DEMO_APA_ANIMATION_FORWARD_RIGHT_GUIDELINE,
    DEMO_APA_ANIMATION_BACKWARD_LEFT_GUIDELINE,
    DEMO_APA_ANIMATION_BACKWARD_RIGHT_GUIDELINE,
    DEMO_APA_ANIMATION_GUIDELINE_NUMS,
}
DemoApaHmiAnimationGuidelineT;

class CSVDemoApaHmi : public ISVHmi
{
  public:
    CSVDemoApaHmi(IUINode *pUiNode = NULL, int pUiNodeId = -1);
    virtual ~CSVDemoApaHmi();
    virtual int SetElementsVisibility(unsigned char pFlag);
    HMI_BASE_INHERITANCE_FUNC()

  private:
    int SetHmiParams();
    int RefreshHmi();
    void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);

    int ProcessApa();

  private:
    Hmi_Button_Data_T m_baseButtonData[DEMO_APA_ICON_NUMS];
    HMIButton *m_baseButton[DEMO_APA_ICON_NUMS];

    float m_buttonPos[DEMO_APA_ICON_NUMS][BUTTON_POS];
    float m_buttonSize[DEMO_APA_ICON_NUMS][BUTTON_SIZE];

    unsigned char m_buttonVisibility[DEMO_APA_ICON_NUMS];
    unsigned char m_buttonImage[DEMO_APA_ICON_NUMS];

    HmiProcessBarDataT m_processBarData;
	HmiProcessBar*     m_processBar;
	unsigned char      m_processBarVisibility;
	float			   m_processBarForwardScale;

	HMIPolygonBoxDataT m_bevParkingLotData[DEMO_APA_BEV_PARKING_PLOT_NUM];
	HMIPolygonBox* 	   m_bevParkingLot[DEMO_APA_BEV_PARKING_PLOT_NUM];
	unsigned char      m_bevParkingLotVisibility[DEMO_APA_BEV_PARKING_PLOT_NUM];
	unsigned char      m_bevParkingLotTexture[DEMO_APA_BEV_PARKING_PLOT_NUM];

    IActionTrigger *m_trigger[DEMO_APA_ICON_NUMS];

    int m_screenWidth;
    int m_screenHeight;

  public:
};

#endif //_CSV_DEMO_APA_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  1/4/18   Jensen Wang   Create the CSVDemoApaHmi class.
\*===========================================================================*/
