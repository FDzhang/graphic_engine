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
	AVMData::GetInstance()->GetSingleViewNodeStatus(singleViewNodeStatus);
	if(singleViewNodeStatus == 0)
	{
		return LARGE_SINGLE_VIEW_INIT_FAILED;
	}
	AVMData::GetInstance()->GetSingleViewNode(&m_singleViewNode);
	AVMData::GetInstance()->GetSingleViewPlaneNode(m_singleViewPlaneNode);
	AVMData::GetInstance()->GetSingleViewVertex(m_singleViewVertex);
	AVMData::GetInstance()->GetSingleViewMesh(m_singleViewMesh);
	//AVMData::GetInstance()->GetLargeSingleViewRoi(m_singleViewRoi);

	m_largeViewRegion.Set(0.0, XrGetScreenWidth(), 0.0, XrGetScreenHeight());

	return LARGE_SINGLE_VIEW_NORMAL;
}
int CAvmLargeSingleView::Update()
{
	unsigned char largeViewCmd = 0;

	AVMData::GetInstance()->GetDisplayViewCmd(largeViewCmd);
	
	if(largeViewCmd >= FRONT_LARGE_SINGLE_VIEW
		&& largeViewCmd <= RIGHT_LARGE_SINGLE_VIEW)
	{
		if(m_lastLargeViewCmd != largeViewCmd)
		{
			AVMData::GetInstance()->GetLargeSingleViewRoi(m_singleViewRoi, largeViewCmd - FRONT_LARGE_SINGLE_VIEW);
			SetLargeViewVertextValue(m_singleViewRoi[largeViewCmd - FRONT_LARGE_SINGLE_VIEW], largeViewCmd - FRONT_LARGE_SINGLE_VIEW);
			m_singleViewNode->SetRenderROI(&m_largeViewRegion);
			m_lastLargeViewCmd = largeViewCmd;
		}
	}
	else if(largeViewCmd >= FRONT_SINGLE_VIEW
		&& largeViewCmd <= RIGHT_SINGLE_VIEW)
	{
		if(m_lastLargeViewCmd != largeViewCmd)
		{
			float* vertexData;
			
			AVMData::GetInstance()->GetSingleViewRoi(&vertexData, largeViewCmd - FRONT_SINGLE_VIEW);
			SetVertextValue(vertexData, largeViewCmd - FRONT_SINGLE_VIEW);
			
			Region* singleViewRegion;
			AVMData::GetInstance()->GetSingleViewRegion(&singleViewRegion);
			m_singleViewNode->SetRenderROI(singleViewRegion);

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