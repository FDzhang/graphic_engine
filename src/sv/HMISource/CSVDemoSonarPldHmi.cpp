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
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
	}


private:
};

CSVDemoSonarPldHmi::CSVDemoSonarPldHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{	
	for(int i = 0; i < SONAR_PLD_BEV_PARKING_PLOT_NUM; i++)
	{
		m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i] = 0;
	}
	memset(m_polygonBox, 0, SONAR_PLD_PARKING_PLOT_NUMS * SONAR_PLD_BEV_PARKING_PLOT_NUM * sizeof(HMIPolygonBox));
	memset(m_polygonBoxVertex, 0, SONAR_PLD_PARKING_PLOT_NUMS * SONAR_PLD_BEV_PARKING_PLOT_NUM * sizeof(float));
	 
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
		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].renderRegion = REGION_BEV;
		CAvmRenderDataBase::GetInstance()->GetStitchViewNode(&m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].renderNode);
		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].polygonVertexNum = 4;
		m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].fillTextureName[0] = new char[50];
		sprintf(m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].fillTextureName[0],"%sCar/green_blind_area.dds",XR_RES);
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

	static float plotPoints[8] = {0};
	for(int i = 0; i < pldRadarReslt.nParkingGarageNum; i++)
	{
		if(i >= SONAR_PLD_BEV_PARKING_PLOT_NUM)
		{
			break;
		}

		for(int i = 0; i < m_polygonBoxData[SONAR_PLD_BEV_PARKING_PLOT][i].polygonVertexNum; i++)
		{
			plotPoints[2 * i + 0] = pldRadarReslt.gstParkingLotList[i].psSlotPoints[i].x;
			plotPoints[2 * i + 1] = pldRadarReslt.gstParkingLotList[i].psSlotPoints[i].y;
		}		
		m_polygonBoxVertex[SONAR_PLD_BEV_PARKING_PLOT][i] = plotPoints;
		if(m_polygonBoxVertex[SONAR_PLD_BEV_PARKING_PLOT][i])
		{
			m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i] = 1;
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
			m_polygonBoxVisibility[SONAR_PLD_BEV_PARKING_PLOT][i] = 0;
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
