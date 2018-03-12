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
#include "CSVDemoSeaHmi.h"
#include "gpu_log.h"


CSVDemoSeaHmi::CSVDemoSeaHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
    memset(m_trigger, NULL, DEMO_SEA_ELEM_NUMS * sizeof(IActionTrigger*));
    
    memset(m_buttonVisibility, 1, DEMO_SEA_ELEM_NUMS * sizeof(unsigned char));

    memset(m_buttonImage, 0, DEMO_SEA_ELEM_NUMS * sizeof(unsigned char));

    memset(m_polygonBox, 0, sizeof(HMIPolygonBox*) * DEMO_SEA_ELEM_NUMS);
    memset(m_seaWarningStatus, 0, sizeof(unsigned char) * DEMO_SEA_TARGET4);
    memset(m_seaTargetShowFlag, 0, sizeof(unsigned char) * DEMO_SEA_TARGET4);

}

CSVDemoSeaHmi::~CSVDemoSeaHmi()
{
	for(int i = DEMO_SEA_ROI; i < DEMO_SEA_ELEM_NUMS; i++)
	{
		SAFE_DELETE(m_polygonBox[i]);
		SAFE_DELETE(m_polygonBoxData[i].fillTextureName[0]);

		if(i >= DEMO_SEA_TARGET1
			&& i <= DEMO_SEA_TARGET4)
		{
			SAFE_DELETE(m_polygonBoxData[i].fillTextureName[1]);
		}
	}

}
    
int CSVDemoSeaHmi::SetHmiParams()
{
 

    return DEMO_SEA_HMI_NORMAL;
}

int CSVDemoSeaHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;

    m_singleViewNode = NULL;
    CAvmRenderDataBase::GetInstance()->GetSingleViewNode(&m_singleViewNode);

    if(m_singleViewNode == NULL)
    {
        return GET_SINGEL_VIEW_NODE_NULL;
    }

    for(int i = DEMO_SEA_ROI;i <= DEMO_SEA_ROI_WARNING;i++)
    {
        m_polygonBoxData[i].renderRegion = REGION_FISHEYE_SINGLEVIEW;
        m_polygonBoxData[i].renderNode = m_singleViewNode;
        m_polygonBoxData[i].polygonVertexNum = 8;
        m_polygonBoxData[i].fillTextureName[0] = new char[50];
        
        m_polygonBoxData[i].fillTextureIndex = 0;
        m_polygonBoxData[i].materialType = Material_Rigid_Blend;
    }
    
    sprintf(m_polygonBoxData[DEMO_SEA_ROI].fillTextureName[0],"%sCar/green_roi_area.dds",XR_RES);
    sprintf(m_polygonBoxData[DEMO_SEA_ROI_WARNING].fillTextureName[0],"%sCar/warning_roi_area.dds",XR_RES);
    
    m_polygonBox[DEMO_SEA_ROI] = new HMIPolygonBox(&m_polygonBoxData[DEMO_SEA_ROI]);
    m_polygonBox[DEMO_SEA_ROI_WARNING] = new HMIPolygonBox(&m_polygonBoxData[DEMO_SEA_ROI_WARNING]);
    
    for(int i = DEMO_SEA_5M_LINE; i <= DEMO_SEA_15M_LINE; i ++)
    {
        m_polygonBoxData[i].renderRegion = REGION_FISHEYE_SINGLEVIEW;
        m_polygonBoxData[i].renderNode = m_singleViewNode;
        m_polygonBoxData[i].polygonVertexNum = 4;
        m_polygonBoxData[i].fillTextureName[0] = new char[50];
        
        m_polygonBoxData[i].fillTextureIndex = 0;
        m_polygonBoxData[i].materialType = Material_Rigid_Blend;
    
        sprintf(m_polygonBoxData[i].fillTextureName[0],"%sCar/sea_red_line.dds",XR_RES);
        m_polygonBox[i] = new HMIPolygonBox(&m_polygonBoxData[i]);
    }
    
    for(int i = DEMO_SEA_TARGET1;i <= DEMO_SEA_TARGET4;i++)
    {
        m_polygonBoxData[i].renderRegion = REGION_FISHEYE_SINGLEVIEW;
        m_polygonBoxData[i].renderNode = m_singleViewNode;
        m_polygonBoxData[i].polygonVertexNum = 4;
        m_polygonBoxData[i].fillTextureName[0] = new char[50];
        sprintf(m_polygonBoxData[i].fillTextureName[0],"%sCar/sea_normal_reminder.dds",XR_RES);
        m_polygonBoxData[i].fillTextureName[1] = new char[50];
        sprintf(m_polygonBoxData[i].fillTextureName[1],"%sCar/sea_warning.dds",XR_RES);
        
        m_polygonBoxData[i].fillTextureIndex = 0;
        m_polygonBoxData[i].materialType = Material_Rigid_Blend;
    
        m_polygonBox[i] = new HMIPolygonBox(&m_polygonBoxData[i]);
    }


    SetHmiParams();
    
    return DEMO_SEA_HMI_NORMAL;
}
int CSVDemoSeaHmi::Update(Hmi_Message_T& hmiMsg)
{ 
	float seaRoiVertex[16];
	float seaRoiWarningVertex[16];
	float seaTargetVertex[DEMO_SEA_TARGET4 - DEMO_SEA_TARGET1 + 1][8];
	float lineWidth = 10.0;
	float seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE + 1][8];

	static int lastTargetNum = 0;

    memset(&m_seaResult, 0, sizeof(Sea_Result_T));
    CAvmRenderDataBase::GetInstance()->GetSeaResult(&m_seaResult);
	
	//0 - 1
	seaRoiVertex[0] = m_seaResult.Sea_Mask_ROI.pts_left[1].x;
	seaRoiVertex[1] = m_seaResult.Sea_Mask_ROI.pts_left[1].y;
	seaRoiWarningVertex[0] = m_seaResult.Sea_Mask_ROI.pts_left_warning[1].x;
	seaRoiWarningVertex[1] = m_seaResult.Sea_Mask_ROI.pts_left_warning[1].y;

	//1 - 0
	seaRoiVertex[2] = m_seaResult.Sea_Mask_ROI.pts_left[0].x;
	seaRoiVertex[3] = m_seaResult.Sea_Mask_ROI.pts_left[0].y;
	seaRoiWarningVertex[2] = m_seaResult.Sea_Mask_ROI.pts_left_warning[0].x;
	seaRoiWarningVertex[3] = m_seaResult.Sea_Mask_ROI.pts_left_warning[0].y;

	//2 - 2
	seaRoiVertex[4] = m_seaResult.Sea_Mask_ROI.pts_left[2].x;
	seaRoiVertex[5] = m_seaResult.Sea_Mask_ROI.pts_left[2].y;
	seaRoiWarningVertex[4] = m_seaResult.Sea_Mask_ROI.pts_left_warning[2].x;
	seaRoiWarningVertex[5] = m_seaResult.Sea_Mask_ROI.pts_left_warning[2].y;

	//3 - 7
	seaRoiVertex[6] = m_seaResult.Sea_Mask_ROI.pts_left[7].x;
	seaRoiVertex[7] = m_seaResult.Sea_Mask_ROI.pts_left[7].y;
	seaRoiWarningVertex[6] = m_seaResult.Sea_Mask_ROI.pts_left_warning[7].x;
	seaRoiWarningVertex[7] = m_seaResult.Sea_Mask_ROI.pts_left_warning[7].y;

	//4 - 3
	seaRoiVertex[8] = m_seaResult.Sea_Mask_ROI.pts_left[3].x;
	seaRoiVertex[9] = m_seaResult.Sea_Mask_ROI.pts_left[3].y;
	seaRoiWarningVertex[8] = m_seaResult.Sea_Mask_ROI.pts_left_warning[3].x;
	seaRoiWarningVertex[9] = m_seaResult.Sea_Mask_ROI.pts_left_warning[3].y;

	//5 - 6
	seaRoiVertex[10] = m_seaResult.Sea_Mask_ROI.pts_left[6].x;
	seaRoiVertex[11] = m_seaResult.Sea_Mask_ROI.pts_left[6].y;
	seaRoiWarningVertex[10] = m_seaResult.Sea_Mask_ROI.pts_left_warning[6].x;
	seaRoiWarningVertex[11] = m_seaResult.Sea_Mask_ROI.pts_left_warning[6].y;

	//6 - 4
	seaRoiVertex[12] = m_seaResult.Sea_Mask_ROI.pts_left[4].x;
	seaRoiVertex[13] = m_seaResult.Sea_Mask_ROI.pts_left[4].y;
	seaRoiWarningVertex[12] = m_seaResult.Sea_Mask_ROI.pts_left_warning[4].x;
	seaRoiWarningVertex[13] = m_seaResult.Sea_Mask_ROI.pts_left_warning[4].y;

	//7 - 5
	seaRoiVertex[14] = m_seaResult.Sea_Mask_ROI.pts_left[5].x;
	seaRoiVertex[15] = m_seaResult.Sea_Mask_ROI.pts_left[5].y;
	seaRoiWarningVertex[14] = m_seaResult.Sea_Mask_ROI.pts_left_warning[5].x;
	seaRoiWarningVertex[15] = m_seaResult.Sea_Mask_ROI.pts_left_warning[5].y;

	seaLineVertex[DEMO_SEA_5M_LINE - DEMO_SEA_5M_LINE][0] = m_seaResult.Sea_Mask_ROI.pts_5[0].x;
	seaLineVertex[DEMO_SEA_5M_LINE - DEMO_SEA_5M_LINE][1] = m_seaResult.Sea_Mask_ROI.pts_5[0].y;

	seaLineVertex[DEMO_SEA_5M_LINE - DEMO_SEA_5M_LINE][2] = m_seaResult.Sea_Mask_ROI.pts_5[1].x;
	seaLineVertex[DEMO_SEA_5M_LINE - DEMO_SEA_5M_LINE][3] = m_seaResult.Sea_Mask_ROI.pts_5[1].y;

	seaLineVertex[DEMO_SEA_5M_LINE - DEMO_SEA_5M_LINE][4] = m_seaResult.Sea_Mask_ROI.pts_5[0].x + lineWidth;
	seaLineVertex[DEMO_SEA_5M_LINE - DEMO_SEA_5M_LINE][5] = m_seaResult.Sea_Mask_ROI.pts_5[0].y;

	seaLineVertex[DEMO_SEA_5M_LINE - DEMO_SEA_5M_LINE][6] = m_seaResult.Sea_Mask_ROI.pts_5[1].x + lineWidth;
	seaLineVertex[DEMO_SEA_5M_LINE - DEMO_SEA_5M_LINE][7] = m_seaResult.Sea_Mask_ROI.pts_5[1].y;

	seaLineVertex[DEMO_SEA_10M_LINE - DEMO_SEA_5M_LINE][0] = m_seaResult.Sea_Mask_ROI.pts_10[0].x;
	seaLineVertex[DEMO_SEA_10M_LINE - DEMO_SEA_5M_LINE][1] = m_seaResult.Sea_Mask_ROI.pts_10[0].y;

	seaLineVertex[DEMO_SEA_10M_LINE - DEMO_SEA_5M_LINE][2] = m_seaResult.Sea_Mask_ROI.pts_10[1].x;
	seaLineVertex[DEMO_SEA_10M_LINE - DEMO_SEA_5M_LINE][3] = m_seaResult.Sea_Mask_ROI.pts_10[1].y;

	seaLineVertex[DEMO_SEA_10M_LINE - DEMO_SEA_5M_LINE][4] = m_seaResult.Sea_Mask_ROI.pts_10[0].x + lineWidth;
	seaLineVertex[DEMO_SEA_10M_LINE - DEMO_SEA_5M_LINE][5] = m_seaResult.Sea_Mask_ROI.pts_10[0].y;

	seaLineVertex[DEMO_SEA_10M_LINE - DEMO_SEA_5M_LINE][6] = m_seaResult.Sea_Mask_ROI.pts_10[1].x + lineWidth;
	seaLineVertex[DEMO_SEA_10M_LINE - DEMO_SEA_5M_LINE][7] = m_seaResult.Sea_Mask_ROI.pts_10[1].y;

	seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE][0] = m_seaResult.Sea_Mask_ROI.pts_15[0].x;
	seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE][1] = m_seaResult.Sea_Mask_ROI.pts_15[0].y;

	seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE][2] = m_seaResult.Sea_Mask_ROI.pts_15[1].x;
	seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE][3] = m_seaResult.Sea_Mask_ROI.pts_15[1].y;

	seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE][4] = m_seaResult.Sea_Mask_ROI.pts_15[0].x + lineWidth;
	seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE][5] = m_seaResult.Sea_Mask_ROI.pts_15[0].y;

	seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE][6] = m_seaResult.Sea_Mask_ROI.pts_15[1].x + lineWidth;
	seaLineVertex[DEMO_SEA_15M_LINE - DEMO_SEA_5M_LINE][7] = m_seaResult.Sea_Mask_ROI.pts_15[1].y;

	//Log_Error("TargetNum: %d", m_seaResult.target_num);

	if(m_seaResult.target_num > 0)
	{
		//Log_Error("--------------------------");
		for(int i = 0; i < lastTargetNum; i++)
		{
			m_polygonBox[DEMO_SEA_TARGET1 + i]->SetVisibility(0);
		}
						
		lastTargetNum = m_seaResult.target_num;
		
		for(int i = 0; i < m_seaResult.target_num; i++)
		{
			seaTargetVertex[i][0] = m_seaResult.Sea_Result_target[i].fisherPT[3].x; 		
			seaTargetVertex[i][1] = m_seaResult.Sea_Result_target[i].fisherPT[3].y;
			seaTargetVertex[i][2] = m_seaResult.Sea_Result_target[i].fisherPT[2].x; 		
			seaTargetVertex[i][3] = m_seaResult.Sea_Result_target[i].fisherPT[2].y;
			seaTargetVertex[i][4] = m_seaResult.Sea_Result_target[i].fisherPT[0].x; 		
			seaTargetVertex[i][5] = m_seaResult.Sea_Result_target[i].fisherPT[0].y; 			
			seaTargetVertex[i][6] = m_seaResult.Sea_Result_target[i].fisherPT[1].x; 		
			seaTargetVertex[i][7] = m_seaResult.Sea_Result_target[i].fisherPT[1].y;

			//m_seaWarningStatus[i] = m_seaResult.Sea_Result_target[i].warning;
			m_polygonBox[DEMO_SEA_TARGET1 + i]->SetPolygonBoxImage(m_seaResult.Sea_Result_target[i].warning);

			m_polygonBox[DEMO_SEA_TARGET1 + i]->SetVisibility(1);
		}
		
		//Log_Error("Targetwarning: %d", m_seaResult.Sea_Result_target[0].warning);
		//for(int i = 0; i < 4; i++)
		{
			//Log_Error("TargetVertex[%d]: %d, %d", i, m_seaResult.Sea_Result_target[0].fisherPT[i].x, m_seaResult.Sea_Result_target[0].fisherPT[i].y );
		}
	}
	else
	{
		for(int i = 0; i < lastTargetNum; i++)
		{
			m_polygonBox[DEMO_SEA_TARGET1 + i]->SetVisibility(0);
		}

	}

	m_polygonBox[DEMO_SEA_ROI]->SetVisibility(1);
	m_polygonBox[DEMO_SEA_ROI_WARNING]->SetVisibility(1);
	for(int i = DEMO_SEA_5M_LINE; i <= DEMO_SEA_15M_LINE; i ++)
	{
		m_polygonBox[i]->SetVisibility(1);
	}   


	if(m_polygonBox[DEMO_SEA_ROI])
	{
		unsigned char tmpView;
		CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(tmpView);
		//Log_Error("--------Current View: %d", tmpView);		
		
		if(tmpView != LEFT_SINGLE_VIEW)
		{
			m_polygonBox[DEMO_SEA_ROI]->SetVisibility(0);
			m_polygonBox[DEMO_SEA_ROI_WARNING]->SetVisibility(0);
			for(int i = DEMO_SEA_5M_LINE; i <= DEMO_SEA_15M_LINE; i ++)
			{
				m_polygonBox[i]->SetVisibility(0);
			}
			for(int i = 0; i < lastTargetNum; i++)
			{
				m_polygonBox[DEMO_SEA_TARGET1 + i]->SetVisibility(0);
			}
		}
		
		m_polygonBox[DEMO_SEA_ROI]->Update(seaRoiVertex, tmpView);
		m_polygonBox[DEMO_SEA_ROI_WARNING]->Update(seaRoiWarningVertex,tmpView);
		for(int i = DEMO_SEA_5M_LINE; i <= DEMO_SEA_15M_LINE; i ++)
		{
			m_polygonBox[i]->Update(seaLineVertex[i - DEMO_SEA_5M_LINE], tmpView);
		}
		for(int i = 0; i < lastTargetNum; i++)
		{
			m_polygonBox[DEMO_SEA_TARGET1 + i]->Update(seaTargetVertex[i], tmpView);
		}
	}	

    RefreshHmi();

    return DEMO_SEA_HMI_NORMAL;
}
int CSVDemoSeaHmi::RefreshHmi()
{   

    return DEMO_SEA_HMI_NORMAL;
}

int CSVDemoSeaHmi::SetElementsVisibility(unsigned char pFlag)
{
	if(pFlag == 0)
	{
		if(m_polygonBox[DEMO_SEA_ROI])
		{
			m_polygonBox[DEMO_SEA_ROI]->SetVisibility(0);
			m_polygonBox[DEMO_SEA_ROI_WARNING]->SetVisibility(0);
			for(int i = DEMO_SEA_5M_LINE; i <= DEMO_SEA_15M_LINE; i ++)
			{
				m_polygonBox[i]->SetVisibility(0);
			}
			for(int i = DEMO_SEA_5M_LINE; i <= DEMO_SEA_15M_LINE; i ++)
			{
				m_polygonBox[i]->SetVisibility(0);
			}
		}	
	}

    return DEMO_SEA_HMI_NORMAL;
}

int CSVDemoSeaHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return DEMO_SEA_HMI_NORMAL;
}
int CSVDemoSeaHmi::DestroyHmiElems()
{
    return DEMO_SEA_HMI_NORMAL;
}

void CSVDemoSeaHmi::SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight)
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
 *  2/24/18   Jensen Wang   Create the CSVDemoSeaHmi class.
\*===========================================================================*/
