/*===========================================================================*\
 * FILE: CAvmLargeSingleViewNode.cpp
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
#include "CAvmLargeSingleView.h"
#include "../AVMData.h"

CAvmLargeSingleView::CAvmLargeSingleView():m_lastLargeViewCmd(255),m_singleViewNode(0)
{
	for(int i = 0; i < 4; i++)
	{
		m_singleViewPlaneNode[i] = NULL;
		m_singleViewVertex[i] = NULL;
		m_singleViewMesh[i] = NULL;
		m_singleViewRoi[i] = NULL;
	}
}
CAvmLargeSingleView::~CAvmLargeSingleView()
{
}

int CAvmLargeSingleView::Init()
{
	unsigned char singleViewNodeStatus = 0;
	CAvmRenderDataBase::GetInstance()->GetSingleViewNodeStatus(&singleViewNodeStatus);
	if(singleViewNodeStatus == 0)
	{
		return LARGE_SINGLE_VIEW_INIT_FAILED;
	}
	CAvmRenderDataBase::GetInstance()->GetSingleViewNode(&m_singleViewNode);
	CAvmRenderDataBase::GetInstance()->GetSingleViewPlaneNode(m_singleViewPlaneNode);
	CAvmRenderDataBase::GetInstance()->GetSingleViewVertex(m_singleViewVertex);
	CAvmRenderDataBase::GetInstance()->GetSingleViewMesh(m_singleViewMesh);
	//AVMData::GetInstance()->GetLargeSingleViewRoi(m_singleViewRoi);

    float stich_region_width = 0.35 *  XrGetScreenWidth();

	float black_width = 80.0;
	unsigned char current_vehicle_type_id;
	CAvmRenderDataBase::GetInstance()->GetVehicleTypeId(current_vehicle_type_id);
	
	m_largeViewRegion.Set(100.0, XrGetScreenWidth(), black_width, XrGetScreenHeight() - black_width);
	m_camDebugViewRegion.Set(0.0, XrGetScreenWidth(), 0, XrGetScreenHeight());
	float radio = 227.0/1280.0;
	m_dvrViewRegion.Set(radio * XrGetScreenWidth(), XrGetScreenWidth(), black_width, XrGetScreenHeight() - black_width);
	if(CHANGAN_S302 == current_vehicle_type_id)
	{
	    black_width = 0.0;
		m_largeViewRegion.Set(0.0, XrGetScreenWidth(), 0.0, XrGetScreenHeight());
		m_dvrViewRegion.Set(0.0, XrGetScreenWidth() - 240, 0.0, XrGetScreenHeight());
		//m_dvrViewRegion.Set(0.0 + 200, XrGetScreenWidth() - 40, 60.0, XrGetScreenHeight() - 60);
		//m_dvrViewRegion.Set(0.0, XrGetScreenWidth() - 240, 60.0, XrGetScreenHeight() - 60);
	}
    else if(CHANGAN_V302 == current_vehicle_type_id)
    {
        black_width = 0.0;
        m_largeViewRegion.Set(0.0, XrGetScreenWidth(), 0.0, XrGetScreenHeight());
        float tmp_width = XrGetScreenWidth();
        float tmp_height = XrGetScreenHeight();
        tmp_width = tmp_height / 1130.0 * 960.0;
        m_dvrViewRegion.Set(0.0, tmp_width, 342.0 / 1130.0 * tmp_height, 885.0 / 1130.0 * tmp_height);
    }
	return LARGE_SINGLE_VIEW_NORMAL;
}
int CAvmLargeSingleView::Update()
{
	unsigned char largeViewCmd = 0;

	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(largeViewCmd);
	
	if(largeViewCmd >= FRONT_LARGE_SINGLE_VIEW
		&& largeViewCmd <= RIGHT_LARGE_SINGLE_VIEW)
	{
		if(m_lastLargeViewCmd != largeViewCmd)
		{
			CAvmRenderDataBase::GetInstance()->GetLargeSingleViewRoi(&m_singleViewRoi[largeViewCmd - FRONT_LARGE_SINGLE_VIEW], largeViewCmd - FRONT_LARGE_SINGLE_VIEW);
			SetLargeViewVertextValue(m_singleViewRoi[largeViewCmd - FRONT_LARGE_SINGLE_VIEW], largeViewCmd - FRONT_LARGE_SINGLE_VIEW);
			m_singleViewNode->SetRenderROI(&m_largeViewRegion);
			m_singleViewNode->SetClear(TRUE,TRUE);
			m_lastLargeViewCmd = largeViewCmd;
		}
	}
	else if(largeViewCmd >= FRONT_SINGLE_VIEW
		&& largeViewCmd <= RIGHT_SINGLE_VIEW)
	{
		if(m_lastLargeViewCmd != largeViewCmd)
		{
			float* vertexData;
			
			CAvmRenderDataBase::GetInstance()->GetSingleViewRoi(&vertexData, largeViewCmd - FRONT_SINGLE_VIEW);
			SetVertextValue(vertexData, largeViewCmd - FRONT_SINGLE_VIEW);
			
			Region* singleViewRegion = NULL;
			CAvmRenderDataBase::GetInstance()->GetSingleViewRegion(&singleViewRegion);
			m_singleViewNode->SetRenderROI(singleViewRegion);
			m_singleViewNode->SetClear(FALSE,FALSE);
			m_lastLargeViewCmd = largeViewCmd;
		}
	}
	else if(largeViewCmd >= CAMERA_DEBUG_FRONT_SINGLE_VIEW
		&& largeViewCmd <= CAMERA_DEBUG_REAR_SINGLE_VIEW)
	{
		if(m_lastLargeViewCmd != largeViewCmd)
		{
			CAvmRenderDataBase::GetInstance()->GetLargeSingleViewRoi(&m_singleViewRoi[largeViewCmd - CAMERA_DEBUG_FRONT_SINGLE_VIEW], largeViewCmd - CAMERA_DEBUG_FRONT_SINGLE_VIEW);
			SetLargeViewVertextValue(m_singleViewRoi[largeViewCmd - CAMERA_DEBUG_FRONT_SINGLE_VIEW], largeViewCmd - CAMERA_DEBUG_FRONT_SINGLE_VIEW);
			m_singleViewNode->SetRenderROI(&m_camDebugViewRegion);
			m_singleViewNode->SetClear(TRUE,TRUE);
			m_lastLargeViewCmd = largeViewCmd;
		}
	}
	else if(largeViewCmd >= DVR_FRONT_SINGLE_VIEW
		&& largeViewCmd <= DVR_RIGHT_SINGLE_VIEW)
	{
		if(m_lastLargeViewCmd != largeViewCmd)
		{
			CAvmRenderDataBase::GetInstance()->GetLargeSingleViewRoi(&m_singleViewRoi[largeViewCmd - DVR_FRONT_SINGLE_VIEW], largeViewCmd - DVR_FRONT_SINGLE_VIEW);
			SetLargeViewVertextValue(m_singleViewRoi[largeViewCmd - DVR_FRONT_SINGLE_VIEW], largeViewCmd - DVR_FRONT_SINGLE_VIEW);
			m_singleViewNode->SetRenderROI(&m_dvrViewRegion);
			m_singleViewNode->SetClear(TRUE,TRUE);
			m_lastLargeViewCmd = largeViewCmd;
		}
	}

	return LARGE_SINGLE_VIEW_NORMAL;
}
int CAvmLargeSingleView::SetVertextValue(float* pVertex, int pViewIndex)
{
	if(pViewIndex < four_camera_index)
	{		
		for(int j = 0; j < 28; j++)
		{
			m_singleViewVertex[pViewIndex][j] = pVertex[j];
		}
		
		m_singleViewMesh[pViewIndex]->UnLockData();
	}

	return LARGE_SINGLE_VIEW_NORMAL;
}
int CAvmLargeSingleView::SetLargeViewVertextValue(float* pVertex, int pViewIndex)
{
	if(pViewIndex < four_camera_index)
	{		
		m_singleViewVertex[pViewIndex][3] = pVertex[REGION_POS_LEFT];
		m_singleViewVertex[pViewIndex][4] = pVertex[REGION_POS_TOP];
		m_singleViewVertex[pViewIndex][3 + 7] = pVertex[REGION_POS_RIGHT];
		m_singleViewVertex[pViewIndex][4 + 7] = pVertex[REGION_POS_TOP];
		m_singleViewVertex[pViewIndex][3 + 14] = pVertex[REGION_POS_LEFT];
		m_singleViewVertex[pViewIndex][4 + 14] = pVertex[REGION_POS_BOTTOM];
		m_singleViewVertex[pViewIndex][3 + 21] = pVertex[REGION_POS_RIGHT];
		m_singleViewVertex[pViewIndex][4 + 21] = pVertex[REGION_POS_BOTTOM];
		
		m_singleViewMesh[pViewIndex]->UnLockData();
	}

	return LARGE_SINGLE_VIEW_NORMAL;
}
int CAvmLargeSingleView::ResetLargeViewRegion()
{
	
	return LARGE_SINGLE_VIEW_NORMAL;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmLargeSingleViewNode class.
\*===========================================================================*/