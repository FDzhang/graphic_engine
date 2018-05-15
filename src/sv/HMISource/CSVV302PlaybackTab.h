/*===========================================================================*\
 * FILE: CSVV302PlaybackTab.h
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

#ifndef _CSV_V302_PLAYBACK_TAB_H_
#define _CSV_V302_PLAYBACK_TAB_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"

#define MAX_SVRES_NUM 50

typedef enum V302PlaybackTabControlTag {
    V302_PB_STATUS_VIDEO = 0,
    V302_PB_STATUS_NUM,
} V302PlaybackTabControlT;

typedef enum V302PlayBackStatusVideoTag {
    V302_PB_STATUS_VIDEO_ON = 0,
    V302_PB_STATUS_VIDEO_PAUSE,
} V302PlayBackStatusVideoT;

typedef enum V302PlaybackTabButtonIndexTag {
    V302_PB_INDEX_BG_IMAGE = 0,
//    V302_PB_INDEX_PLAYNAME_BK,
//    V302_PB_INDEX_PLAYPOINT,
    V302_PB_INDEX_STBAR_BK,
    V302_PB_INDEX_STABR_SPEED,
    V302_PB_INDEX_STABR_GEAR,
    V302_PB_INDEX_STABR_BRAKE,
    V302_PB_INDEX_STABR_BUCKLE,
    V302_PB_INDEX_STABR_TURNLEFT,
    V302_PB_INDEX_STABR_TURNRIGHT,
    V302_PB_INDEX_STABR_ENGINE,
    V302_PB_INDEX_NUM,
} V302PlaybackTabButtonIndexT;

enum
{
    V302_PB_TIME_TEXT = 0,
    V302_PB_GPS_TEXT,
    V302_PB_SPEED_TEXT,

    V302_PB_FILENAME_TITLE,
    V302_PB_CURRENT_TIME,
    V302_PB_DURATION_TIME,
    V302_PB_TEXT_NUM,
};

class CSVV302PlaybackTab : public ISVHmi
{
  public:
    CSVV302PlaybackTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    ~CSVV302PlaybackTab();
    HMI_BASE_INHERITANCE_FUNC()

    virtual int SetElementsVisibility(unsigned char pFlag);

  private:
    int SetHmiParams();
    int RefreshHmi();
    int ToString(int pTime, char** pOutString);
    int SetDvrView(unsigned char pViewCmd);
    int SetStateBarVal(void *ptr);
    int InitTimeGps();
  private:
    unsigned char m_iconStatus[V302_PB_STATUS_NUM];

    Hmi_Button_Data_T m_baseButtonData[V302_PB_INDEX_NUM];
    HMIButton *m_baseButton[V302_PB_INDEX_NUM];
    
	unsigned char m_buttonStatus[V302_PB_INDEX_NUM];
	unsigned char m_buttonVisibility[V302_PB_INDEX_NUM];

    int HmiInitSTBar();
    int HmiInitPlayBar();
    int HmiInitLayer();
    int HmiInitSvresList();

    char *HmiGetSvresFile(int index);

    char *m_hmiSvresFileName[MAX_SVRES_NUM];
    unsigned char m_currentSvresNum;

    int m_screenWidth;
    int m_screenHeight;

    HmiTextEdit *m_speed_value_text;
    HmiTextEditDataT m_speed_value_text_data;

    HmiProcessBarDataT  m_processBarData;
    HmiProcessBar*      m_processBar;
    unsigned char       m_processBarVisibility;
    float               m_processBarForwardScale;

    HmiTextEditDataT    m_textEditData[V302_PB_TEXT_NUM];
    HmiTextEdit*        m_textEdit[V302_PB_TEXT_NUM];
    unsigned char       m_textEditVisibility[V302_PB_TEXT_NUM];
    char*               m_textEditContent[V302_PB_TEXT_NUM];
  public:
};

#endif //_CSV_V302_PLAYBACK_TAB_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  04/17/18   Zhu Hangman   Create the CSVV302PlaybackTab class.
\*===========================================================================*/
