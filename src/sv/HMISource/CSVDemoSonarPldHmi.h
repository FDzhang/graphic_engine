/*===========================================================================*\
 * FILE: CSVDemoSonarPldHmi.h
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


#ifndef _CSV_SONAR_PLD_HMI_H_
#define _CSV_SONAR_PLD_HMI_H_

#include "ISVHmi.h"


typedef enum DemoSonarPldHmiElemenTag
{

    DEMO_SONAR_PLD_ELEM_NUMS,
}
DemoSonarPldHmiElementT;

typedef enum DemoSonarPldParkingPlotTag
{
	SONAR_PLD_BEV_PARKING_PLOT = 0,
	SONAR_PLD_PARKING_PLOT_NUMS,
}
DemoSonarPldParkingPlotT;

typedef enum DemoSonarPldParkingPlotNumTag
{
	SONAR_PLD_BEV_PARKING_PLOT_NUM = 10,
}
DemoSonarPldParkingPlotNumT;

class CSVDemoSonarPldHmi : public ISVHmi
{
public:
	CSVDemoSonarPldHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	virtual ~CSVDemoSonarPldHmi();
	virtual int SetElementsVisibility(unsigned char pFlag);
	HMI_BASE_INHERITANCE_FUNC()
	
private:
	int SetHmiParams();
	int RefreshHmi();
	void SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight);
	
	int ProcessLka(LkaLcResultT pLkaLcResult);
	int ProcessLc(LkaLcResultT pLkaLcResult);

private:

	HMIPolygonBoxDataT m_polygonBoxData[SONAR_PLD_PARKING_PLOT_NUMS][SONAR_PLD_BEV_PARKING_PLOT_NUM];
	HMIPolygonBox* 	   m_polygonBox[SONAR_PLD_PARKING_PLOT_NUMS][SONAR_PLD_BEV_PARKING_PLOT_NUM];
	unsigned char      m_polygonBoxVisibility[SONAR_PLD_PARKING_PLOT_NUMS][SONAR_PLD_BEV_PARKING_PLOT_NUM];
	float*			   m_polygonBoxVertex[SONAR_PLD_PARKING_PLOT_NUMS][SONAR_PLD_BEV_PARKING_PLOT_NUM];

	Hmi_Button_Data_T m_baseButtonData[DEMO_SONAR_PLD_ELEM_NUMS];
    HMIButton* m_baseButton[DEMO_SONAR_PLD_ELEM_NUMS];

	float m_buttonPos[DEMO_SONAR_PLD_ELEM_NUMS][BUTTON_POS];
	float m_buttonSize[DEMO_SONAR_PLD_ELEM_NUMS][BUTTON_SIZE];

	unsigned char m_buttonVisibility[DEMO_SONAR_PLD_ELEM_NUMS];
	unsigned char m_buttonImage[DEMO_SONAR_PLD_ELEM_NUMS];
	
	IActionTrigger*	m_trigger[DEMO_SONAR_PLD_ELEM_NUMS];


	int m_screenWidth;
	int m_screenHeight;


public:	

};


#endif //_CSV_SONAR_PLD_HMI_H_


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  1/4/18   Jensen Wang   Create the CSVDemoSonarPldHmi class.
\*===========================================================================*/
