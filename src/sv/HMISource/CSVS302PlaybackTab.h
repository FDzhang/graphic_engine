/*===========================================================================*\
 * FILE: CSVS302PlaybackTab.h
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

#ifndef _CSV_S302_PLAYBACK_TAB_H_
#define _CSV_S302_PLAYBACK_TAB_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"

#define MAX_SVRES_NUM 50

typedef enum S302PlaybackTabControlTag {
    S302_PLAYBACK_STATUS_VIDEO = 0,
    S302_PLAYBACK_STATUS_NUM,
} S302PlaybackTabControlT;

typedef enum S302PlaybackStatusVideoTag {
    S302_PLAYBACK_STATUS_VIDEO_ON = 0,
    S302_PLAYBACK_STATUS_VIDEO_PAUSE,
} S302PlaybackStatusVideoT;

typedef enum S302PlaybackTabButtonIndexTag {
    S302_PLAYBACK_INDEX_BG_IMAGE = 0,
    S302_PLAYBACK_INDEX_STABR_SPEED,
    S302_PLAYBACK_INDEX_STABR_GEAR,
    S302_PLAYBACK_INDEX_STABR_ACC,
    S302_PLAYBACK_INDEX_STABR_BRAKE,
    S302_PLAYBACK_INDEX_STABR_TURNLEFT,
    S302_PLAYBACK_INDEX_STABR_TURNRIGHT,
    S302_PLAYBACK_INDEX_STABR_BUCKLE,
    S302_PLAYBACK_INDEX_NUM,
} S302PlaybackTabButtonIndexT;

enum
{
    S302_TIME_TEXT = 0,
    S302_GPS_TEXT,
    S302_SPEED_TEXT,
    S302_TEXT_NUM,
};



class CSVS302PlaybackTab : public ISVHmi
{
  public:
    CSVS302PlaybackTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    ~CSVS302PlaybackTab();
    HMI_BASE_INHERITANCE_FUNC()

    virtual int SetElementsVisibility(unsigned char pFlag);

  private:
    int SetHmiParams();
    int RefreshHmi();
	int SetDvrView(unsigned char pViewCmd);
    int SetStateBarVal(void *ptr);
    int InitText();
  private:
    unsigned char m_iconStatus[S302_PLAYBACK_STATUS_NUM];

    Hmi_Button_Data_T m_baseButtonData[S302_PLAYBACK_INDEX_NUM];
    HMIButton *m_baseButton[S302_PLAYBACK_INDEX_NUM];
    
	unsigned char m_buttonStatus[S302_PLAYBACK_INDEX_NUM];
	unsigned char m_buttonVisibility[S302_PLAYBACK_INDEX_NUM];

    int HmiInitSTBar();
    int HmiInitLayer();
    int HmiInitSvresList();

    char *HmiGetSvresFile(int index);

    char *m_hmiSvresFileName[MAX_SVRES_NUM];
    unsigned char m_currentSvresNum;

    int m_screenWidth;
    int m_screenHeight;
    
	HmiTextEditDataT m_textEditData[S302_TEXT_NUM];
	HmiTextEdit*     m_textEdit[S302_TEXT_NUM];

  public:
};

#endif //_CSV_S302_PLAYBACK_TAB_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  04/17/18   Zhu Hangman   Create the CSVS302PlaybackTab class.
\*===========================================================================*/
