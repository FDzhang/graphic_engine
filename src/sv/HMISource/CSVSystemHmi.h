/*===========================================================================*\
 * FILE: CSVSystemHmi.h
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
#ifndef _CSV_SYSTEM_HMI_H_
#define _CSV_SYSTEM_HMI_H_

#include "ISVHmi.h"


typedef enum SystemHmiElementTag
{
	SYSTEM_HMI_MOUSE_ICON = 0,
	SYSTEM_HMI_ELEMEMT_NUM,
}
SystemHmiElementT;

class CSVSystemHmi : public ISVHmi
{
public:

	CSVSystemHmi();
	~CSVSystemHmi();
	HMI_BASE_INHERITANCE_FUNC()
    
private:
	int SetHmiParams();
	int RefreshHmi();
private:
	Hmi_Button_Data_T m_baseButtonData[SYSTEM_HMI_ELEMEMT_NUM];
    HMIButton* m_baseButton[SYSTEM_HMI_ELEMEMT_NUM];

	Hmi_Message_T  m_hmiMsg;

	float m_buttonPos[SYSTEM_HMI_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[SYSTEM_HMI_ELEMEMT_NUM][BUTTON_SIZE];

	IActionTrigger*	m_trigger[SYSTEM_HMI_ELEMEMT_NUM];
	
	unsigned char m_buttonStatus[SYSTEM_HMI_ELEMEMT_NUM];
	unsigned char m_buttonVisibility[SYSTEM_HMI_ELEMEMT_NUM];

	int     m_windowHeight;
	int     m_windowWidth;
	
};

#endif //_CSV_SYSTEM_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVSystemHmi class.
\*===========================================================================*/