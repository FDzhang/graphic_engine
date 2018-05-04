/*===========================================================================*\
 * FILE: CSVV302FileListTab.h
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

#ifndef _CSV_V302_FILE_LIST_TAB_H_
#define _CSV_V302_FILE_LIST_TAB_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"

static const int IMAGE_GRID_LIST_ITEM_NUM = 6;

typedef enum V302FileListStatusTag
{
    V302_FILE_TAB_SELECT_STATUS,
    V302_FILE_ALLSELECT_ICON_STATUS,
    V302_FILE_COPY_ICON_STATUS,
    V302_FILE_DELET_ICON_STATUS,
    V302_FILE_LOCK_ICON_STATUS,
    V302_FILE_EDIT_ICON_STATUS,
    V302_FILE_STATUS_NUM,
}V302FileListStatusT;


typedef enum V302FileListButtonIndexTag
{
    V302_FILE_BUTTON_INDEX_BG_IMAGE,
    V302_FILE_BUTTON_INDEX_NUM,
}V302FileListButtonIndexT;



static const int V302_GRID_LIST_ITEM_NUM = 12;
static const int V302_GRID_LIST_ITEM_ROW = 4;
static const int V302_GRID_LIST_ITEM_COLUMN = 3;

#define PREVIEW_WIDTH 304
#define PREVIEW_HIGH 176

class CSVV302FileListTab : public ISVHmi
{
public:

    CSVV302FileListTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    ~CSVV302FileListTab();
    HMI_BASE_INHERITANCE_FUNC()

    virtual int SetElementsVisibility(unsigned char pFlag);

private:
    int SetHmiParams();
    int RefreshHmi();
    
   	HMIImageGridListDataT   m_imageGridListData;
	HMIImageGridList*       m_imageGridList;
	ImageGridListItemT      m_imageGridListItem[V302_GRID_LIST_ITEM_NUM];
    HmiTextEditDataT        m_textEditData[V302_GRID_LIST_ITEM_NUM];

    
  	Hmi_Button_Data_T m_baseButtonData[V302_FILE_BUTTON_INDEX_NUM];
    HMIButton* m_baseButton[V302_FILE_BUTTON_INDEX_NUM];

    int m_imageItemId[V302_GRID_LIST_ITEM_NUM];
    unsigned char m_imageGridVisibility;
    unsigned char m_tmpRGB[PREVIEW_WIDTH * PREVIEW_HIGH * 3];
private:


public:

};

#endif //_CSV_V302_FILE_LIST_TAB_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  04/08/18   Zhu Hangman   Create the CSVV302FileListTab class.
\*===========================================================================*/

