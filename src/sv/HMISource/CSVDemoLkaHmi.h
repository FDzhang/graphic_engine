/*===========================================================================*\
 * FILE: CSVDemoLkaHmi.h
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


#ifndef _CSV_DEMO_LKA_HMI_H_
#define _CSV_DEMO_LKA_HMI_H_

#include "ISVHmi.h"


typedef enum DemoLkaHmiElementTag
{
	DEMO_LKA_STATUS_BAR_BKG = 0,
	DEMO_LKA_SPEED_PROMPT,
	DEMO_LKA_DIRECTION_PROMPT,
	DEMO_LKA_STEERING_PROMPT,
	DEMO_LKA_WARNING,
	DEMO_LKA_LANE_BKG,
	DEMO_LKA_LEFT_SIDE_LANE,
	DEMO_LKA_RIGHT_SIDE_LANE,
	DEMO_LKA_CAR,
	DEMO_LKA_ERROR_WARNING_BKG,
	DEMO_LKA_ERROR_WARNING_TXT,
    DEMO_LKA_ICON_NUMS,
}
DemoLkaHmiElementT;


class CSVDemoLkaHmi : public ISVHmi
{
public:
	CSVDemoLkaHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	virtual ~CSVDemoLkaHmi();
	virtual int SetElementsVisibility(unsigned char pFlag);
	HMI_BASE_INHERITANCE_FUNC()
	
private:
	int SetHmiParams();
	int RefreshHmi();
	void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);
	
	int ProcessLka(LkaLcResultT pLkaLcResult);
	int ProcessLc(LkaLcResultT pLkaLcResult);

private:
	Hmi_Button_Data_T m_baseButtonData[DEMO_LKA_ICON_NUMS];
    HMIButton* m_baseButton[DEMO_LKA_ICON_NUMS];

	float m_buttonPos[DEMO_LKA_ICON_NUMS][BUTTON_POS];
	float m_buttonSize[DEMO_LKA_ICON_NUMS][BUTTON_SIZE];

	unsigned char m_buttonVisibility[DEMO_LKA_ICON_NUMS];
	unsigned char m_buttonImage[DEMO_LKA_ICON_NUMS];
	
	IActionTrigger*	m_trigger[DEMO_LKA_ICON_NUMS];


	int m_screenWidth;
	int m_screenHeight;


public:	

};


#endif //_CSV_DEMO_LKA_HMI_H_


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  1/4/18   Jensen Wang   Create the CSVDemoLkaHmi class.
\*===========================================================================*/
