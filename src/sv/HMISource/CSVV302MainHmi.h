/*===========================================================================*\
 * FILE: CSVV302MainHmi.h
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

#ifndef _CSV_V302_MAIN_HMI_H_
#define _CSV_V302_MAIN_HMI_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"

typedef enum V302MenuAlgoHmiTag {
    V302_FILE_VIEW_HMI = 0,
    V302_PlAY_VIEW_HMI,
    V302_IMAGE_VIEW_HMI,
    V302_RECORD_VIEW_HMI,
    V302_MENU_SUB_HMI_NUM,
} V302MenuAlgoHmiT;

typedef enum V302LogicControlTag {
    V302_DVR_STATUS = 0,
    V302_PB_STATUS,
    V302_IMAGE_STATUS,
    V302_RECORD_STATUS,
    V302_LOGIC_CONTROL_NUM,
} V302LogicControlT;

typedef enum V302DvrStatusTag {
    V302_DVR_STATUS_ON,
    V302_DVR_STATUS_OFF,
} V302DvrStatusT;

typedef enum V302MainButtonIndexTag {
    V302_MAIN_BUTTON_INDEX_BG_IMAGE,
    V302_MAIN_BUTTON_INDEX_STATUSBAR_BK,
    V302_MAIN_BUTTON_INDEX_STATUSBAR_SPEED,
    V302_MAIN_BUTTON_INDEX_STATUSBAR_GEAR,
    V302_MAIN_BUTTON_INDEX_STATUSBAR_BRAKE,
    V302_MAIN_BUTTON_INDEX_STATUSBAR_BUCKLE,
    V302_MAIN_BUTTON_INDEX_STATUSBAR_TURNLEFT,
    V302_MAIN_BUTTON_INDEX_STATUSBAR_TURNRIGHT,
    V302_MAIN_BUTTON_INDEX_STATUSBAR_ENGINE,
    V302_MAIN_BUTTON_INDEX_NUM,
} V302MainButtonIndexT;

class CSVV302MainHmi : public ISVHmi
{
  public:
    CSVV302MainHmi();
    ~CSVV302MainHmi();
    HMI_BASE_INHERITANCE_FUNC()

    virtual int SetElementsVisibility(unsigned char pFlag);

  private:
    int SetHmiParams();
    int RefreshHmi();
    void InitSubHmi(unsigned char pHmiIndex);
    void FreeSubHmi(unsigned char pHmiIndex);

  private:
    unsigned char m_iconStatus[V302_LOGIC_CONTROL_NUM];

    Hmi_Button_Data_T m_baseButtonData[V302_MAIN_BUTTON_INDEX_NUM];
    HMIButton* m_baseButton[V302_MAIN_BUTTON_INDEX_NUM];

    unsigned char m_subHmiInitFlag[V302_MENU_SUB_HMI_NUM];
    unsigned char m_subHmiVisibility[V302_MENU_SUB_HMI_NUM];
    ISVHmi* m_subHmi[V302_MENU_SUB_HMI_NUM];

    int m_screenWidth;
    int m_screenHeight;

    HmiTextEdit*     m_speed_value_text;
    HmiTextEditDataT m_speed_value_text_data;

  public:
};

#endif //_CSV_V302_MAIN_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  04/08/18   Zhu Hangman   Create the CSVV302MainHmi class.
\*===========================================================================*/
