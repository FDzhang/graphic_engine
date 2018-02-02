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
#include "CSVDemoSonarPldHmi.h"
#include "gpu_log.h"

class CSonarPldActionTrigger : public IActionTrigger
{
public:
	CSonarPldActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}

private:
};

CSVDemoSonarPldHmi::CSVDemoSonarPldHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{	
	for(int i = 0; i < SONAR_PLD_BEV_PARKING_PLOT_NUM; i++)
	{
		m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i] = 0;
		m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i] = 0;
		m_polygonBoxVertex[SONAR_PLD_BEV_PARKING_PLOT][i] = 0;
	}
}

CSVDemoSonarPldHmi::~CSVDemoSonarPldHmi()
{
}
	
int CSVDemoSonarPldHmi::SetHmiParams()
{
	for(int i = 0; i < SONAR_PLD_BEV_PARKING_PLOT_NUM; i++)
	{
 		m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i] = new HMIPolygonBox(&m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i]);
		m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i]->SetVisibility(m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i]);
	}
	return DEMO_SP_HMI_NORMAL;
}
int CSVDemoSonarPldHmi::Init(int window_width, int window_height)
{
	m_screenWidth = window_width;
	m_screenHeight = window_height;

	for(int i = 0; i < SONAR_PLD_BEV_PARKING_PLOT_NUM; i++)
	{
		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].renderRegion = REGION_BEV_APA_PARKING_LOT;
		CAvmRenderDataBase::GetInstance()->GetStitchViewNode(&(m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].renderNode));
		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].polygonVertexNum = 8;
		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].fillTextureName[0] = new char[50];
		sprintf(m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].fillTextureName[0],"%sCar/apa_right_parking_lot.dds",XR_RES);
		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].fillTextureName[1] = new char[50];
		sprintf(m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].fillTextureName[1],"%sCar/apa_left_parking_lot.dds",XR_RES);	

		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].fillTextureIndex = 0;
		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].materialType = Material_Rigid_Blend;
	}

	SetHmiParams();
	
	return DEMO_SP_HMI_NORMAL;
}
int CSVDemoSonarPldHmi::Update(Hmi_Message_T& hmiMsg)
{
	PLDRadarResult pldRadarReslt;
	memset(&pldRadarReslt, 0, sizeof(PLDRadarResult));
	CAvmRenderDataBase::GetInstance()->GetSonarResult(&pldRadarReslt);
	
	for(int i = 0; i < SONAR_PLD_BEV_PARKING_PLOT_NUM; i++)
	{
		m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i] = 0;
	}

	const int TMP_PLOT_POINT_NUM = 8;
	static float plotPoints[TMP_PLOT_POINT_NUM] = {0.0};

	const int PARKING_LOT_POINT_NUM = 4;
	const int LEFT_PARKING_LOT = 1;
	const int RIGHT_PARKING_LOT = 0;

	float tmpPointX = 0.0;
	float tmpPointY = 0.0;

	unsigned char parkingLotTextureIndex = 0;

/*
	pldRadarReslt.nParkingGarageNum = 1;

	pldRadarReslt.gstParkingLotList[0].psSlotPoints[0].y = 1.0;
	pldRadarReslt.gstParkingLotList[0].psSlotPoints[0].x = 0.0;

	pldRadarReslt.gstParkingLotList[0].psSlotPoints[1].y = 3.0;
	pldRadarReslt.gstParkingLotList[0].psSlotPoints[1].x = 0.0;


	pldRadarReslt.gstParkingLotList[0].psSlotPoints[2].y = 1.0;
	pldRadarReslt.gstParkingLotList[0].psSlotPoints[2].x = 3.0;


	pldRadarReslt.gstParkingLotList[0].psSlotPoints[3].y = 3.0;
	pldRadarReslt.gstParkingLotList[0].psSlotPoints[3].x = 3.0;

	pldRadarReslt.gstParkingLotList[0].nlocation = RIGHT_PARKING_LOT;

	Log_Error("----------Pld");
*/
	for(int i = 0; i < pldRadarReslt.nParkingGarageNum; i++)
	{
		if(i >= SONAR_PLD_BEV_PARKING_PLOT_NUM)
		{
			break;
		}

		/* Left: 3 - 2  Right: 2 - 3 */
		/*       |   |         |   | */
		/*       1 - 0         0 - 1 */

		for(int j = 0; j < PARKING_LOT_POINT_NUM; j++)
		{
			if(j >= PARKING_LOT_POINT_NUM)
			{
				break;
			}

			plotPoints[2 * j + 0] = pldRadarReslt.gstParkingLotList[i].psSlotPoints[j].y * 1000.0;
			plotPoints[2 * j + 1] = pldRadarReslt.gstParkingLotList[i].psSlotPoints[j].x * 1000.0;
		}	

		if(pldRadarReslt.gstParkingLotList[i].nlocation == LEFT_PARKING_LOT)
		{
			tmpPointX = plotPoints[0];
			tmpPointY = plotPoints[1];

			plotPoints[0] = plotPoints[2];
			plotPoints[1] = plotPoints[3];

			plotPoints[2] = tmpPointX;
			plotPoints[3] = tmpPointY;

			tmpPointX = plotPoints[4];
			tmpPointY = plotPoints[5];

			plotPoints[4] = plotPoints[6];
			plotPoints[5] = plotPoints[7];

			plotPoints[6] = tmpPointX;
			plotPoints[7] = tmpPointY;

			parkingLotTextureIndex = LEFT_PARKING_LOT;
			
		}
		else if(pldRadarReslt.gstParkingLotList[i].nlocation == RIGHT_PARKING_LOT)
		{
			parkingLotTextureIndex = RIGHT_PARKING_LOT;
		}		
		
		m_polygonBoxVertex[SONAR_PLD_BEV_PARKING_PLOT][i] = plotPoints;
		
		if(m_polygonBoxVertex[SONAR_PLD_BEV_PARKING_PLOT][i])
		{
			m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i] = 1;
			m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i]->SetPolygonBoxImage(parkingLotTextureIndex);
			m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i]->Update(m_polygonBoxVertex[SONAR_PLD_BEV_PARKING_PLOT][i]);
		}
	}

	RefreshHmi();

	return DEMO_SP_HMI_NORMAL;
}
int CSVDemoSonarPldHmi::RefreshHmi()
{
	for(int i = 0; i < SONAR_PLD_BEV_PARKING_PLOT_NUM; i++)
	{
		if(m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i])
		{
			m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i]->SetVisibility(m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i]);		
		}
	}

	return DEMO_SP_HMI_NORMAL;
}

int CSVDemoSonarPldHmi::SetElementsVisibility(unsigned char pFlag)
{
	for(int i = 0; i < SONAR_PLD_BEV_PARKING_PLOT_NUM; i++)
	{
		if(m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i])
		{
			m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i] = pFlag;
			m_polygonBox[SONAR_PLD_BEV_PARKING_PLOT][i]->SetVisibility(m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i]);		
		}
	}	

	return DEMO_SP_HMI_NORMAL;
}

int CSVDemoSonarPldHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return DEMO_SP_HMI_NORMAL;
}
int CSVDemoSonarPldHmi::DestroyHmiElems()
{
	return DEMO_SP_HMI_NORMAL;
}

void CSVDemoSonarPldHmi::SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight)
{
	m_buttonSize[pIconIndex][BUTTON_SIZE_WIDTH] = pIconWidth;
	m_buttonSize[pIconIndex][BUTTON_SIZE_HEIGHT] = pIconHeight;
	m_buttonPos[pIconIndex][BUTTON_POS_X] = pIconPosX;
	m_buttonPos[pIconIndex][BUTTON_POS_Y] = pIconPosY;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  1/4/18   Jensen Wang   Create the CSVDemoSonarPldHmi class.
\*===========================================================================*/
