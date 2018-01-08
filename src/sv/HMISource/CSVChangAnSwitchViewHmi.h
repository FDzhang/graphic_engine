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


#ifndef _CSV_CHANGAN_SWITCH_VIEW_HMI_H_
#define _CSV_CHANGAN_SWITCH_VIEW_HMI_H_

#include "ISVHmi.h"


typedef enum ChangAnSwitchViewHmiElementTag
{
	CHANGAN_RED_TRACK,
    CHANGAN_TRACK_FRONT_CAMERA,
    CHANGAN_TRACK_REAR_CAMERA,
    CHANGAN_TRACK_LEFT_CAMERA,
    CHANGAN_TRACK_RIGHT_CAMERA,
    CHANGAN_TRACK_FRONT_LEFT_CAMERA,
    CHANGAN_TRACK_FRONT_RIGHT_CAMERA,
    CHANGAN_TRACK_REAR_LEFT_CAMERA,
    CHANGAN_TRACK_REAR_RIGHT_CAMERA,
	CHANGAN_CAMERA_FRONT,
	CHANGAN_CAMERA_REAR,
	CHANGAN_CAMERA_LEFT,
	CHANGAN_CAMERA_RIGHT,
    CHANGAN_ICON_NUMS,
}
ChangAnSwitchViewHmiElementT;


class CSVChangAnSwitchViewHmi : public ISVHmi
{
public:
	CSVChangAnSwitchViewHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	~CSVChangAnSwitchViewHmi();
	virtual int SetElementsVisibility(unsigned char pFlag);
	HMI_BASE_INHERITANCE_FUNC()
	
private:
	int SetHmiParams();
	int RefreshHmi();
    int ProcessCarRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action);
	int ProcessTrackCamRegionTouchEvent(unsigned int pos_x, unsigned int pos_y, unsigned char action);
	
private:
	Hmi_Button_Data_T m_baseButtonData[CHANGAN_ICON_NUMS];
    HMIButton* m_baseButton[CHANGAN_ICON_NUMS];

	float m_buttonPos[CHANGAN_ICON_NUMS][BUTTON_POS];
	float m_buttonSize[CHANGAN_ICON_NUMS][BUTTON_SIZE];
	float m_carRectPos[BUTTON_POS];
	float m_carRectSize[BUTTON_SIZE];

	unsigned char m_buttonVisibility[CHANGAN_ICON_NUMS];
	unsigned char m_buttonImage[CHANGAN_ICON_NUMS];
	
	IActionTrigger*	m_trigger[CHANGAN_ICON_NUMS];


	int m_screenWidth;
	int m_screenHeight;

	unsigned char m_cameraIconsVisibility;
	unsigned int m_currentTime;
	
public:	
	static unsigned int m_startCountTime;
	static unsigned char m_hasBeenTouched;

};


#endif //_CSV_CHANGAN_SWITCH_VIEW_HMI_H_


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVChangAnSwitchViewHmi class.
 *  01/03/18   Chunh Huang   Add camera icons display logic.
\*===========================================================================*/
