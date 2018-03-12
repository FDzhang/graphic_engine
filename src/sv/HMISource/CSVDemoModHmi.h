/*===========================================================================*\
 * FILE: CSVDemoModHmi.h
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


#ifndef _CSV_DEMO_MOD_HMI_H_
#define _CSV_DEMO_MOD_HMI_H_

#include "ISVHmi.h"


typedef enum DemoModHmiElementTag
{
	DEMO_MOD_TARGET1,
	DEMO_MOD_TARGET2,
	DEMO_MOD_TARGET3,
	DEMO_MOD_TARGET4,
	DEMO_MOD_ELEM_NUMS,
}
DemoModHmiElementT;


class CSVDemoModHmi : public ISVHmi
{
public:
	CSVDemoModHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	virtual ~CSVDemoModHmi();
	virtual int SetElementsVisibility(unsigned char pFlag);
	HMI_BASE_INHERITANCE_FUNC()
	
private:
	int SetHmiParams();
	int RefreshHmi();
	void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);

private:
	Hmi_Button_Data_T m_baseButtonData[DEMO_MOD_ELEM_NUMS];
    HMIButton* m_baseButton[DEMO_MOD_ELEM_NUMS];

	float m_buttonPos[DEMO_MOD_ELEM_NUMS][BUTTON_POS];
	float m_buttonSize[DEMO_MOD_ELEM_NUMS][BUTTON_SIZE];

	unsigned char m_buttonVisibility[DEMO_MOD_ELEM_NUMS];
	unsigned char m_buttonImage[DEMO_MOD_ELEM_NUMS];
	
	IActionTrigger*	m_trigger[DEMO_MOD_ELEM_NUMS];

	HMIPolygonBoxDataT m_polygonBoxData[DEMO_MOD_ELEM_NUMS];
	HMIPolygonBox*	   m_polygonBox[DEMO_MOD_ELEM_NUMS];
	unsigned char	   m_initmodElemFlag;

	Mod_Result_T m_modResult;
	int			 m_modStatus;
	unsigned char m_modWarningStatus[DEMO_MOD_ELEM_NUMS];
	unsigned char m_modTargetShowFlag[DEMO_MOD_ELEM_NUMS];

	ISceneNode*   m_singleViewNode;


	int m_screenWidth;
	int m_screenHeight;


public:	

};


#endif //_CSV_DEMO_MOD_HMI_H_


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  2/24/18   Jensen Wang   Create the CSVDemoModHmi class.
\*===========================================================================*/
