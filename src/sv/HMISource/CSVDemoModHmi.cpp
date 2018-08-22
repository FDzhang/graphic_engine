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
#include "CSVDemoModHmi.h"
#include "gpu_log.h"


CSVDemoModHmi::CSVDemoModHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
    memset(m_trigger, 0, DEMO_MOD_ELEM_NUMS * sizeof(IActionTrigger*));
    
    memset(m_buttonVisibility, 1, DEMO_MOD_ELEM_NUMS * sizeof(unsigned char));

    memset(m_buttonImage, 0, DEMO_MOD_ELEM_NUMS * sizeof(unsigned char));

    memset(m_polygonBox, 0, sizeof(HMIPolygonBox*) * DEMO_MOD_ELEM_NUMS);
    memset(m_modWarningStatus, 0, sizeof(unsigned char) * DEMO_MOD_TARGET4);
    memset(m_modTargetShowFlag, 0, sizeof(unsigned char) * DEMO_MOD_TARGET4);

}

CSVDemoModHmi::~CSVDemoModHmi()
{
	for(int i = DEMO_MOD_TARGET1; i < DEMO_MOD_ELEM_NUMS; i++)
	{
		SAFE_DELETE(m_polygonBox[i]);
		SAFE_DELETE(m_polygonBoxData[i].fillTextureName[0]);

		if(i >= DEMO_MOD_TARGET1
			&& i <= DEMO_MOD_TARGET4)
		{
			SAFE_DELETE(m_polygonBoxData[i].fillTextureName[1]);
		}
	}

}
    
int CSVDemoModHmi::SetHmiParams()
{
 

    return DEMO_MOD_HMI_NORMAL;
}

int CSVDemoModHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;

    m_singleViewNode = NULL;
    CAvmRenderDataBase::GetInstance()->GetSingleViewNode(&m_singleViewNode);

    if(m_singleViewNode == NULL)
    {
        return GET_SINGEL_VIEW_NODE_NULL;
    }
    
    for(int i = DEMO_MOD_TARGET1;i <= DEMO_MOD_TARGET4;i++)
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
    
    return DEMO_MOD_HMI_NORMAL;
}
int CSVDemoModHmi::Update(Hmi_Message_T& hmiMsg)
{ 
	float modTargetVertex[DEMO_MOD_TARGET4 - DEMO_MOD_TARGET1 + 1][8];

	static int lastTargetNum = 0;

    memset(&m_modResult, 0, sizeof(Mod_Result_T));
    CAvmRenderDataBase::GetInstance()->GetModResult(&m_modResult);

	//float CamWidth = 1280.0;
	//AVMData::GetInstance()->m_camInstrinct->GetCameraWidth(&CamWidth,0);
	
	//Log_Error("TargetNum: %d", m_modResult.l32ObjNum);
	int targetNum = DEMO_MOD_TARGET4 + 1;
	targetNum = (m_modResult.l32ObjNum > targetNum) ? targetNum : m_modResult.l32ObjNum;

	if(targetNum > 0)
	{
		//Log_Error("--------------------------");
		for(int i = 0; i < lastTargetNum; i++)
		{
			m_polygonBox[DEMO_MOD_TARGET1 + i]->SetVisibility(0);
		}
						
		lastTargetNum = targetNum;
		
		for(int i = 0; i < targetNum; i++)
		{
			modTargetVertex[i][0] = m_modResult.stRstData[i].al32VertexLeftBtm[0]; 		
			modTargetVertex[i][1] = m_modResult.stRstData[i].al32VertexLeftBtm[1];
			modTargetVertex[i][2] = m_modResult.stRstData[i].al32VertexRightBtm[0]; 		
			modTargetVertex[i][3] = m_modResult.stRstData[i].al32VertexRightBtm[1];
			modTargetVertex[i][4] = m_modResult.stRstData[i].al32VertexLeftTop[0]; 		
			modTargetVertex[i][5] = m_modResult.stRstData[i].al32VertexLeftTop[1]; 			
			modTargetVertex[i][6] = m_modResult.stRstData[i].al32VertexRightTop[0]; 		
			modTargetVertex[i][7] = m_modResult.stRstData[i].al32VertexRightTop[1];

			m_polygonBox[DEMO_MOD_TARGET1 + i]->SetPolygonBoxImage(0);

			m_polygonBox[DEMO_MOD_TARGET1 + i]->SetVisibility(1);
		}
		
		/*for(int i = 0; i < m_modResult.l32ObjNum; i++)
		{
			Log_Error("LeftTargetVertex[%d]: %d, %d", i,m_modResult.stRstData[i].al32VertexLeftBtm[0], m_modResult.stRstData[i].al32VertexLeftBtm[1]);
		Log_Error("TargetVertex[%d]: %d, %d", i,m_modResult.stRstData[i].al32VertexRightBtm[0], m_modResult.stRstData[i].al32VertexRightBtm[1]);
		Log_Error("TargetVertex[%d]: %d, %d", i,m_modResult.stRstData[i].al32VertexLeftTop[0], m_modResult.stRstData[i].al32VertexLeftTop[1]);
		Log_Error("TargetVertex[%d]: %d, %d", i,m_modResult.stRstData[i].al32VertexRightTop[0], m_modResult.stRstData[i].al32VertexRightTop[1]);

		}*/
	}
	else
	{
		for(int i = 0; i < lastTargetNum; i++)
		{
			m_polygonBox[DEMO_MOD_TARGET1 + i]->SetVisibility(0);
		}

	} 

	unsigned char tmpView;
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(tmpView);
	for(int i = 0; i < lastTargetNum; i++)
	{
		m_polygonBox[DEMO_MOD_TARGET1 + i]->Update(modTargetVertex[i], tmpView);
	}


    RefreshHmi();

    return DEMO_MOD_HMI_NORMAL;
}
int CSVDemoModHmi::RefreshHmi()
{   

    return DEMO_MOD_HMI_NORMAL;
}

int CSVDemoModHmi::SetElementsVisibility(unsigned char pFlag)
{
    return DEMO_MOD_HMI_NORMAL;
}

int CSVDemoModHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return DEMO_MOD_HMI_NORMAL;
}
int CSVDemoModHmi::DestroyHmiElems()
{
    return DEMO_MOD_HMI_NORMAL;
}

void CSVDemoModHmi::SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight)
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
 *  2/24/18   Jensen Wang   Create the CSVDemoModHmi class.
\*===========================================================================*/
