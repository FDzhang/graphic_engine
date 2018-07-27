/*===========================================================================*\
 * FILE: CSVS302MainHmi.h
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


#ifndef _CSV_S302_MAIN_HMI_H_
#define _CSV_S302_MAIN_HMI_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"

enum
{
    S302_FRONT_LEFT_ICON = 0,
    S302_FRONT_RIGHT_ICON,
    S302_REAR_LEFT_ICON,
    S302_REAR_RIGHT_ICON,
    S302_FRONT120_ICON,
    S302_FRONT_LEFT_RIGHT180_ICON,
    S302_REAR120_ICON,
    S302_REAR_LEFT_RIGHT180_ICON,
};

typedef enum S302MainHmiElementTag
{
    S302_VIEW_STATUS_ICON,

    S302_REMIND_TXT,

    S302_MAIN_MENU_BKG,
    S302_MAIN_MENU_EXIT_ICON,
    S302_MAIN_MENU_2D_VIEW_ENTER_ICON,
    S302_MAIN_MENU_3D_VIEW_ENTER_ICON,
    S302_MAIN_MENU_DVR_ENTER_ICON,
    S302_MAIN_MENU_SETTING_ICON,

    S302_SETTING_MENU_ITEMS,
    S302_SETTING_MENU_RETURN_ICON,
    S302_SETTING_MENU_GUIDELINE_STATUS,
    S302_SETTING_MENU_MOD_STATUS,
    S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS,
    S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS,
    S302_SETTING_MENU_CALIBRATION_STATUS,

    S302_CONTROL_BUTTONS_HIDE,
    S302_CONTROL_BUTTONS_SHOW,

    S302_BEV_BK_ICON,
    S302_BEV_CAR_ICON,
    S302_VIEW180_LEFT_CUTLINE,
    S302_VIEW180_RIGHT_CUTLINE,

    S302_MAIN_ELEMENT_NUM,
}
S302MainHmiElementT;

typedef enum S302MenuAlgoHmiTag
{
    S302_DEMO_EOL_HMI = 0,
    S302_DEMO_GUIDELINE_HMI,
    S302_DEMO_MOD_HMI,
    S302_DEMO_SWITCH_VIEW_HMI,
    S302_DEMO_DVR_HMI,
    S302_MENU_SUB_HMI_NUM,	
}
S302MenuAlgoHmiT;


class CSVS302MainHmi : public ISVHmi
{
public:

    CSVS302MainHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    ~CSVS302MainHmi();
    HMI_BASE_INHERITANCE_FUNC()

    SetElementsVisibility(unsigned char pFlag);

private:
    int SetHmiParams();
    int RefreshHmi();
    void InitSubHmi(unsigned char pHmiIndex);
    void FreeSubHmi(unsigned char pHmiIndex);
	void SetHmiGuideline();
	void RefreshHmiGuideline();
	void ResetGuideLineEndPos(float pSteerAngle);
	void MockRefreshLicense();

private:
    Hmi_Button_Data_T m_baseButtonData[S302_MAIN_ELEMENT_NUM];
    HMIButton* m_baseButton[S302_MAIN_ELEMENT_NUM];

    float m_buttonPos[S302_MAIN_ELEMENT_NUM][BUTTON_POS];
    float m_buttonSize[S302_MAIN_ELEMENT_NUM][BUTTON_SIZE];

    unsigned char m_buttonVisibility[S302_MAIN_ELEMENT_NUM];
    unsigned char m_buttonShowImage[S302_MAIN_ELEMENT_NUM];

	float m_carOpacity;

    IActionTrigger*	m_trigger[S302_MAIN_ELEMENT_NUM];

    unsigned char m_subHmiInitFlag[S302_MENU_SUB_HMI_NUM];
    unsigned char m_subHmiVisibility[S302_MENU_SUB_HMI_NUM];
    ISVHmi*       m_subHmi[S302_MENU_SUB_HMI_NUM];

    ISVHmi* m_cameraHmi;

    int m_screenWidth;
    int m_screenHeight;

	HMIGuideLineDataT   m_guideLineData[DEMO_GUIDELINE_NUM];
    HMIGuideLine*       m_guideLine[DEMO_GUIDELINE_NUM];

	HMILicenseDataT     m_licenseData;
	HMILicense* 		m_licenese;
    
	unsigned char       m_singleViewDynGuideLineVisibility;
    unsigned char       m_bevDynGuideLineVisibility;
	unsigned char       m_bevDynOutLGuideLineVisibility;
	unsigned char       m_bevDynOutRGuideLineVisibility;
	unsigned char       m_bevAsitLDynGuideLineVisibility;
	unsigned char       m_bevAsitRDynGuideLineVisibility;

	HmiTextEditDataT 	m_textEditData;
	HmiTextEdit*     	m_textEdit;
	
public:

};

#endif //_CSV_S302_MAIN_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  01/18/18   Chunh Huang   Create the CSVS302MainHmi class.
\*===========================================================================*/