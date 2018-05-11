/*===========================================================================*\
 * FILE: CSVS302RecordTab.h
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

#ifndef _CSV_S302_RECORD_TAB_H_
#define _CSV_S302_RECORD_TAB_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"

#define MAX_SVRES_NUM 50

typedef enum S302RecordTabControlTag {
    S302_RECORD_STATUS_VIDEO = 0,
    S302_RECORD_STATUS_NUM,
} S302RecordTabControlT;

typedef enum S302RecordStatusVideoTag {
    S302_RECORD_STATUS_VIDEO_ON = 0,
    S302_RECORD_STATUS_VIDEO_PAUSE,
} S302RecordStatusVideoT;

typedef enum S302RecordTabButtonIndexTag {
    S302_RECORD_INDEX_BG_IMAGE = 0,
    S302_RECORD_INDEX_RECPOINT,
    S302_RECORD_INDEX_STBAR_BK,
    S302_RECORD_INDEX_STABR_SPEED,
    S302_RECORD_INDEX_STABR_GEAR,
    S302_RECORD_INDEX_STABR_BRAKE,
    S302_RECORD_INDEX_STABR_BUCKLE,
    S302_RECORD_INDEX_STABR_TURNLEFT,
    S302_RECORD_INDEX_STABR_TURNRIGHT,
    S302_RECORD_INDEX_STABR_ENGINE,
    S302_RECORD_INDEX_NUM,
} S302RecordTabButtonIndexT;

class CSVS302RecordTab : public ISVHmi
{
  public:
    CSVS302RecordTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    ~CSVS302RecordTab();
    HMI_BASE_INHERITANCE_FUNC()

    virtual int SetElementsVisibility(unsigned char pFlag);

  private:
    int SetHmiParams();
    int RefreshHmi();
	int SetDvrView(unsigned char pViewCmd);

  private:
    unsigned char m_iconStatus[S302_RECORD_STATUS_NUM];

    Hmi_Button_Data_T m_baseButtonData[S302_RECORD_INDEX_NUM];
    HMIButton *m_baseButton[S302_RECORD_INDEX_NUM];
    
	unsigned char m_buttonStatus[S302_RECORD_INDEX_NUM];
	unsigned char m_buttonVisibility[S302_RECORD_INDEX_NUM];

    int HmiInitSTBar();
    int HmiInitLayer();
    int HmiInitSvresList();

    unsigned char *HmiGetSvresFile(int index);

    unsigned char *m_hmiSvresFileName[MAX_SVRES_NUM];
    unsigned char m_currentSvresNum;

    int m_screenWidth;
    int m_screenHeight;

    HmiTextEdit *m_speed_value_text;
    HmiTextEditDataT m_speed_value_text_data;

  public:
};

#endif //_CSV_S302_RECORD_TAB_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  04/17/18   Zhu Hangman   Create the CSVS302RecordTab class.
\*===========================================================================*/
