/*===========================================================================*\
 * FILE: CSVDemoMainHmi.h
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


#ifndef _CSV_DEMO_MAIN_HMI_H_
#define _CSV_DEMO_MAIN_HMI_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"

typedef enum Demo_Guideline_Type_Tag
{
    DEMO_GUIDELINE_BEV_DYNAMIC_POS_L,
    DEMO_GUIDELINE_BEV_DYNAMIC_POS_R,

    DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L,
    DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R,
   
	DEMO_GUIDELINE_LEFT_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_RIGHT_SINGLEVIEW_STATIC,

    DEMO_GUIDELINE_REAR_1mL_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_1mR_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_2mL_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_2mR_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_3mL_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_3mR_SINGLEVIEW_STATIC,

    DEMO_GUIDELINE_REAR_1mL_HORIZON_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_1mR_HORIZON_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_2mL_HORIZON_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_2mR_HORIZON_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_3mL_HORIZON_SINGLEVIEW_STATIC,
    DEMO_GUIDELINE_REAR_3mR_HORIZON_SINGLEVIEW_STATIC,

    DEMO_GUIDELINE_NUM,
}
Demo_Guideline_Type_T;

typedef enum DemoHmiElementTag
{
	DEMO_MAIN_MENU_BKG = 0, 
	DEMO_MAIN_MENU_OC,
	DEMO_MAIN_MENU_LDW,
	DEMO_MAIN_MENU_LKA,
	DEMO_MAIN_MENU_LC,
	DEMO_MAIN_MENU_BSD,
	DEMO_MAIN_MENU_PARKING_I,
	DEMO_MAIN_MENU_PARKING_O,
	DEMO_MAIN_MENU_PARKING_T,
	DEMO_MAIN_MENU_CTA,
	DEMO_MAIN_MENU_PD,
	DEMO_MAIN_MENU_SEA,
	DEMO_MAIN_MENU_MOD,
	DEMO_MAIN_MENU_DVR,	
	DEMO_MAIN_ELEMENT_NUM,
}
DemoMainHmiElementT;


typedef enum DemoMenuAlgoHmiTag
{
	DEMO_LKA_LC_HMI = 0,
	DEMO_TP_HMI,
	DEMO_SEA_HMI,
	DEMO_MOD_HMI,
	DEMO_APA_HMI,
	DEMO_SWITCH_VIEW_HMI,
	DEMO_MENU_SUB_HMI_NUM,	
}
DemoMenuAlgoHmiT;

class CSVDemoMainHmi : public ISVHmi
{
public:

	CSVDemoMainHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	~CSVDemoMainHmi();
	HMI_BASE_INHERITANCE_FUNC()

private:
	int SetHmiParams();
	int RefreshHmi();
	void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);
	void InitSubHmi(unsigned char pHmiIndex);
	void FreeSubHmi(unsigned char pHmiIndex);

    void SetHmiGuideline();
    void RefreshHmiGuideline();
    

private:
	Hmi_Button_Data_T m_baseButtonData[DEMO_MAIN_ELEMENT_NUM];
    HMIButton* m_baseButton[DEMO_MAIN_ELEMENT_NUM];
	
	float m_buttonPos[DEMO_MAIN_ELEMENT_NUM][BUTTON_POS];
	float m_buttonSize[DEMO_MAIN_ELEMENT_NUM][BUTTON_SIZE];

	unsigned char m_buttonVisibility[DEMO_MAIN_ELEMENT_NUM];
	unsigned char m_buttonImage[DEMO_MAIN_ELEMENT_NUM];

	IActionTrigger*	m_trigger[DEMO_MAIN_ELEMENT_NUM];

	unsigned char m_subHmiInitFlag[DEMO_MENU_SUB_HMI_NUM];
	unsigned char m_subHmiVisibility[DEMO_MENU_SUB_HMI_NUM];
	ISVHmi*		  m_subHmi[DEMO_MENU_SUB_HMI_NUM];
	
	int m_screenWidth;
	int m_screenHeight;

    HMIGuideLineDataT   m_guideLineData[DEMO_GUIDELINE_NUM];
    HMIGuideLine*       m_guideLine[DEMO_GUIDELINE_NUM];
    
public:	

};


#endif //_CSV_DEMO_MAIN_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVDemoMainHmi class.
 *  01/04/18   Jensen Wang   Add new menu.
 *  01/05/18   Jensen Wang   Modify algo hmi.
\*===========================================================================*/