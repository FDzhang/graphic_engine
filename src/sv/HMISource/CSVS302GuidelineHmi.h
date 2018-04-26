/*===========================================================================*\
 * FILE: CSVS302GuidelineHmi.h
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


#ifndef _CSV_S302_GUIDELINE_HMI_H_
#define _CSV_S302_GUIDELINE_HMI_H_

#include "ISVHmi.h"

typedef enum S302_Guideline_Type_Tag
{
    /*S302_GUIDELINE_BEV_DYNAMIC_LEFT,
    S302_GUIDELINE_BEV_DYNAMIC_RIGHT,

    S302_GUIDELINE_REAR_SINGLEVIEW_DYNAMIC_LEFT,
    S302_GUIDELINE_REAR_SINGLEVIEW_DYNAMIC_RIGHT,
    S302_GUIDELINE_REAR_SINGLEVIEW_DYNAMIC_MIDDLE,

    S302_GUIDELINE_FRONT_SINGLEVIEW_DYNAMIC_LEFT,
    S302_GUIDELINE_FRONT_SINGLEVIEW_DYNAMIC_RIGHT,
    S302_GUIDELINE_FRONT_SINGLEVIEW_DYNAMIC_MIDDLE,*/

    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL1,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL1,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL2,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL2,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_VERTICAL3,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_VERTICAL3,

    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL1,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL1,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL2,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL2,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_LEFT_HORIZONTAL3,
    S302_GUIDELINE_REAR_SINGLEVIEW_STATIC_RIGHT_HORIZONTAL3,

    S302_GUIDELINE_NUM,
}
S302_Guideline_Type_T;

class CSVS302GuidelineHmi : public ISVHmi
{
public:
    CSVS302GuidelineHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
    virtual ~CSVS302GuidelineHmi();
    virtual int SetElementsVisibility(unsigned char pFlag);
    HMI_BASE_INHERITANCE_FUNC()

private:
    void SetHmiGuideline();
    void RefreshHmiGuideline();

private:
    HMIGuideLineDataT   m_guideLineData[S302_GUIDELINE_NUM];
    HMIGuideLine*       m_guideLine[S302_GUIDELINE_NUM];

    unsigned char       m_singleViewStaGuideLineVisibility;
    //unsigned char       m_singleViewDynGuideLineVisibility;
    //unsigned char       m_bevDynGuideLineVisibility;

    int m_screenWidth;
    int m_screenHeight;

public:

};
#endif //_CSV_S302_GUIDELINE_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  04/24/18   Chunh Huang   Create the CSVS302GuidelineHmi class.
\*===========================================================================*/
