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


typedef enum S302MainHmiElementTag
{
    S302_VIEW_STATUS_ICON,

    S302_REMIND_TXT,

    S302_MAIN_MENU_BKG,
    S302_MAIN_MENU_EXIT_ICON,
    S302_MAIN_MENU_2D_VIEW_ENTER_ICON,
    S302_MAIN_MENU_3D_VIEW_ENTER_ICON,
    S302_MAIN_MENU_SETTING_ICON,

    S302_SETTING_MENU_ITEMS,
    S302_SETTING_MENU_RETURN_ICON,
    S302_SETTING_MENU_GUIDELINE_STATUS,
    S302_SETTING_MENU_MOD_STATUS,
    S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS,
    S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS,
    S302_SETTING_MENU_CALIBRATION_STATUS,

    S302_MAIN_ELEMENT_NUM,
}
S302MainHmiElementT;

class CSVS302MainHmi : public ISVHmi
{
public:

    CSVS302MainHmi();
    ~CSVS302MainHmi();
    HMI_BASE_INHERITANCE_FUNC()

    SetElementsVisibility(unsigned char pFlag);

private:
    int SetHmiParams();
    int RefreshHmi();

private:
    Hmi_Button_Data_T m_baseButtonData[S302_MAIN_ELEMENT_NUM];
    HMIButton* m_baseButton[S302_MAIN_ELEMENT_NUM];

    float m_buttonPos[S302_MAIN_ELEMENT_NUM][BUTTON_POS];
    float m_buttonSize[S302_MAIN_ELEMENT_NUM][BUTTON_SIZE];

    unsigned char m_buttonVisibility[S302_MAIN_ELEMENT_NUM];
    unsigned char m_buttonShowImage[S302_MAIN_ELEMENT_NUM];

    IActionTrigger*	m_trigger[S302_MAIN_ELEMENT_NUM];

    ISVHmi* m_cameraHmi;

    int m_screenWidth;
    int m_screenHeight;
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