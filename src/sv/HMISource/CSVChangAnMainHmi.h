/*===========================================================================*\
 * FILE: CSVChangAnMainHmi.h
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


#ifndef _CSV_CHANGAN_MAIN_HMI_H_
#define _CSV_CHANGAN_MAIN_HMI_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"


typedef enum ChangAnMainHmiElementTag
{
	CHANGAN_MAIN_MENU_BKG = 0,
	CHANGAN_MAIN_MENU_ENTER_ICON = 1,
	CHANGAN_MAIN_MENU_EXIT_ICON,
	CHANGAN_MAIN_DVR_START_ICON,

	CHANGAN_MAIN_ELEMENT_NUM,
}
ChangAnMainHmiElementT;


class CSVChangAnMainHmi : public ISVHmi
{
public:

	CSVChangAnMainHmi();
	~CSVChangAnMainHmi();
	HMI_BASE_INHERITANCE_FUNC()



private:
	int SetHmiParams();
	int RefreshHmi();

private:
	Hmi_Button_Data_T m_baseButtonData[CHANGAN_MAIN_ELEMENT_NUM];
    HMIButton* m_baseButton[CHANGAN_MAIN_ELEMENT_NUM];
	
	float m_buttonPos[CHANGAN_MAIN_ELEMENT_NUM][BUTTON_POS];
	float m_buttonSize[CHANGAN_MAIN_ELEMENT_NUM][BUTTON_SIZE];

	unsigned char m_buttonVisibility[CHANGAN_MAIN_ELEMENT_NUM];

	IActionTrigger*	m_trigger[CHANGAN_MAIN_ELEMENT_NUM];


	int m_screenWidth;
	int m_screenHeight;
public:	

};


#endif //_CSV_CHANGAN_MAIN_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVChangAnMainHmi class.
\*===========================================================================*/