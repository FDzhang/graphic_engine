/*===========================================================================*\
 * FILE: CSVDemoEolHmi.h
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


#ifndef _CSV_DEMO_EOL_HMI_H_
#define _CSV_DEMO_EOL_HMI_H_

#include "ISVHmi.h"

typedef enum DemoEolHmiElementTag
{
    DEMO_EOL_STATUS_REMIND_TEXT = 0,
    DEMO_EOL_ICON_NUMS,
}
DemoEolHmiElementT;

typedef enum DemoEolStatusTag
{
    DEMO_EOL_CALIBRATION_PROCESS = 0,
    DEMO_EOL_CALIBRATION_SUCCEEDED,
    DEMO_EOL_CALIBRATION_FAILED,
    DEMO_EOL_STATUS_NUMS,
}
DemoEolStatusT;

class CSVDemoEolHmi : public ISVHmi
{
public:
    CSVDemoEolHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    virtual ~CSVDemoEolHmi();
    virtual int SetElementsVisibility(unsigned char pFlag);
    HMI_BASE_INHERITANCE_FUNC()

private:
    int SetHmiParams();
    int RefreshHmi();
    void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);

    //int ProcessEol(EolResultT pEolResult);

private:
    Hmi_Button_Data_T m_baseButtonData[DEMO_EOL_ICON_NUMS];
    HMIButton* m_baseButton[DEMO_EOL_ICON_NUMS];

    float m_buttonPos[DEMO_EOL_ICON_NUMS][BUTTON_POS];
    float m_buttonSize[DEMO_EOL_ICON_NUMS][BUTTON_SIZE];

    unsigned char m_buttonVisibility[DEMO_EOL_ICON_NUMS];
    unsigned char m_buttonImage[DEMO_EOL_ICON_NUMS];

    IActionTrigger*	m_trigger[DEMO_EOL_ICON_NUMS];

    int m_screenWidth;
    int m_screenHeight;


public:

};
#endif //_CSV_DEMO_EOL_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  3/5/18     Chunh Huang   Create the CSVDemoEolHmi class.
\*===========================================================================*/
