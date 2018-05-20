/*===========================================================================*\
 * FILE: CSVS302PdHmi.h
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


#ifndef _CSV_S302_PD_HMI_H_
#define _CSV_S302_PD_HMI_H_

#include "ISVHmi.h"

typedef enum S302PdHmiElementTag
{
    S302_PD_FRONT_WARNING,
    S302_PD_REAR_WARNING,
    S302_PD_LEFT_WARNING,
    S302_PD_RIGHT_WARNING,
    S302_PD_ELEM_NUMS,
}
S302PdHmiElementT;

class CSVS302PdHmi : public ISVHmi
{
public:
    CSVS302PdHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    virtual ~CSVS302PdHmi();
    virtual int SetElementsVisibility(unsigned char pFlag);
    HMI_BASE_INHERITANCE_FUNC()

private:
    int SetHmiParams();
    int RefreshHmi();
    void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);

private:
    Hmi_Button_Data_T m_baseButtonData[S302_PD_ELEM_NUMS];
    HMIButton* m_baseButton[S302_PD_ELEM_NUMS];

    float m_buttonPos[S302_PD_ELEM_NUMS][BUTTON_POS];
    float m_buttonSize[S302_PD_ELEM_NUMS][BUTTON_SIZE];

    unsigned char m_buttonVisibility[S302_PD_ELEM_NUMS];
    unsigned char m_buttonImage[S302_PD_ELEM_NUMS];

    IActionTrigger*	m_trigger[S302_PD_ELEM_NUMS];

    int m_screenWidth;
    int m_screenHeight;

public:

};


#endif //_CSV_S302_PD_HMI_H_


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  05/16/18   Chunh Huang   Create the CSVS302PdHmi class.
\*===========================================================================*/
