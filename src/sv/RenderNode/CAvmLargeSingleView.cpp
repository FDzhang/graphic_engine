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

CAvmLargeSingleView::CAvmLargeSingleView():m_lastLargeViewCmd(255)
{
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
	
	m_largeViewRegion.Set(100.0, XrGetScreenWidth(), black_width, XrGetScreenHeight() - black_width);
	m_camDebugViewRegion.Set(0.0, XrGetScreenWidth(), 0, XrGetScreenHeight());

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
			
			Region* singleViewRegion;
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