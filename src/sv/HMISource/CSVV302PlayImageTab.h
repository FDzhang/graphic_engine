/*===========================================================================*\
 * FILE: CSVV302PlayImageTab.h
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

#ifndef _CSV_V302_PLAYIMAGE_TAB_H_
#define _CSV_V302_PLAYIMAGE_TAB_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"

#define MAX_SVRES_NUM 50

typedef enum V302PlayImageTabControlTag {
    V302_IMAGE_STATUS_Image = 0,
    V302_IMAGE_STATUS_NUM,
} V302PlayImageTabControlT;

typedef enum V302PlayImageStatusVideoTag {
    V302_IMAGE_STATUS_VIDEO_ON = 0,
    V302_IMAGE_STATUS_VIDEO_PAUSE,
} V302PlayImageStatusVideoT;

typedef enum V302PlayImageTabButtonIndexTag {
    V302_IMAGE_INDEX_BG_IMAGE = 0,
    V302_IMAGE_INDEX_IMAGE_NAME_BK,
    V302_IMAGE_INDEX_NUM,
} V302PlayImageTabButtonIndexT;

class CSVV302PlayImageTab : public ISVHmi
{
  public:
    CSVV302PlayImageTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    ~CSVV302PlayImageTab();
    HMI_BASE_INHERITANCE_FUNC()

    virtual int SetElementsVisibility(unsigned char pFlag);

  private:
    int SetHmiParams();
    int RefreshHmi();
    int SetDvrView(unsigned char pViewCmd);

  private:
    unsigned char m_iconStatus[V302_IMAGE_STATUS_NUM];

    Hmi_Button_Data_T m_baseButtonData[V302_IMAGE_INDEX_NUM];
    HMIButton *m_baseButton[V302_IMAGE_INDEX_NUM];

    int HmiInitLayer();
    int HmiInitSvresList();

    unsigned char *HmiGetSvresFile(int index);

    unsigned char *m_hmiSvresFileName[MAX_SVRES_NUM];
    unsigned char m_currentSvresNum;

    int m_screenWidth;
    int m_screenHeight;

  public:
};

#endif //_CSV_V302_PLAYBACK_TAB_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  04/17/18   Zhu Hangman   Create the CSVV302PlayImageTab class.
\*===========================================================================*/
