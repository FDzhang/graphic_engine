/*===========================================================================*\
 * FILE: CSVDemoMainHmi.h
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


#ifndef _CSV_DEMO_MAIN_HMI_H_
#define _CSV_DEMO_MAIN_HMI_H_

#include <iostream>
#include <memory>
#include "ISVHmi.h"


typedef enum DemoHmiElementTag
{
	DEMO_MAIN_MENU_BKG = 0, 
	DEMO_MAIN_MENU_SETTING,
	DEMO_MAIN_MENU_LDW,
	DEMO_MAIN_MENU_LKA,
	DEMO_MAIN_MENU_LC,
	DEMO_MAIN_MENU_BSD,
	DEMO_MAIN_MENU_PARKING_I,
	DEMO_MAIN_MENU_PARKING_O,
	DEMO_MAIN_MENU_PARKING_T,
	DEMO_MAIN_MENU_CTA,
	DEMO_MAIN_MENU_PD,
	DEMO_MAIN_MENU_DVR,
	DEMO_MAIN_ELEMENT_NUM,
}
DemoMainHmiElementT;


class CSVDemoMainHmi : public ISVHmi
{
public:

	CSVDemoMainHmi();
	~CSVDemoMainHmi();
	HMI_BASE_INHERITANCE_FUNC()



private:
	int SetHmiParams();
	int RefreshHmi();
	void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);

private:
	Hmi_Button_Data_T m_baseButtonData[DEMO_MAIN_ELEMENT_NUM];
    HMIButton* m_baseButton[DEMO_MAIN_ELEMENT_NUM];
	
	float m_buttonPos[DEMO_MAIN_ELEMENT_NUM][BUTTON_POS];
	float m_buttonSize[DEMO_MAIN_ELEMENT_NUM][BUTTON_SIZE];

	unsigned char m_buttonVisibility[DEMO_MAIN_ELEMENT_NUM];
	unsigned char m_buttonImage[DEMO_MAIN_ELEMENT_NUM];

	IActionTrigger*	m_trigger[DEMO_MAIN_ELEMENT_NUM];

	unsigned char m_lkaLcInitFlag;
	unsigned char m_lkaLcHmiVisibility;
	ISVHmi*       m_lkaLcHmi;
	
	int m_screenWidth;
	int m_screenHeight;
public:	

};


#endif //_CSV_DEMO_MAIN_HMI_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVDemoMainHmi class.
 *  01/04/18   Jensen Wang   Add new menu.
\*===========================================================================*/