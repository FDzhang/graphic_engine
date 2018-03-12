/*===========================================================================*\
 * FILE: CSVDemoSeaHmi.h
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


#ifndef _CSV_DEMO_SEA_HMI_H_
#define _CSV_DEMO_SEA_HMI_H_

#include "ISVHmi.h"


typedef enum DemoSeaHmiElementTag
{
	DEMO_SEA_ROI = 0,
	DEMO_SEA_ROI_WARNING,
	DEMO_SEA_TARGET1,
	DEMO_SEA_TARGET2,
	DEMO_SEA_TARGET3,
	DEMO_SEA_TARGET4,
	DEMO_SEA_5M_LINE,
	DEMO_SEA_10M_LINE,
	DEMO_SEA_15M_LINE,
	DEMO_SEA_ELEM_NUMS,
}
DemoSeaHmiElementT;


class CSVDemoSeaHmi : public ISVHmi
{
public:
	CSVDemoSeaHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	virtual ~CSVDemoSeaHmi();
	virtual int SetElementsVisibility(unsigned char pFlag);
	HMI_BASE_INHERITANCE_FUNC()
	
private:
	int SetHmiParams();
	int RefreshHmi();
	void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);

private:
	Hmi_Button_Data_T m_baseButtonData[DEMO_SEA_ELEM_NUMS];
    HMIButton* m_baseButton[DEMO_SEA_ELEM_NUMS];

	float m_buttonPos[DEMO_SEA_ELEM_NUMS][BUTTON_POS];
	float m_buttonSize[DEMO_SEA_ELEM_NUMS][BUTTON_SIZE];

	unsigned char m_buttonVisibility[DEMO_SEA_ELEM_NUMS];
	unsigned char m_buttonImage[DEMO_SEA_ELEM_NUMS];
	
	IActionTrigger*	m_trigger[DEMO_SEA_ELEM_NUMS];

	HMIPolygonBoxDataT m_polygonBoxData[DEMO_SEA_ELEM_NUMS];
	HMIPolygonBox*	   m_polygonBox[DEMO_SEA_ELEM_NUMS];
	unsigned char	   m_initSeaElemFlag;

	Sea_Result_T m_seaResult;
	int			 m_seaStatus;
	unsigned char m_seaWarningStatus[DEMO_SEA_TARGET4];
	unsigned char m_seaTargetShowFlag[DEMO_SEA_TARGET4];

	ISceneNode*   m_singleViewNode;


	int m_screenWidth;
	int m_screenHeight;


public:	

};


#endif //_CSV_DEMO_SEA_HMI_H_


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  2/24/18   Jensen Wang   Create the CSVDemoSeaHmi class.
\*===========================================================================*/
