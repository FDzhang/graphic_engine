/*===========================================================================*\
 * FILE: CAvmMattsView.cpp
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

#include "CAvmMattsView.h"
#include "../AVMData.h"

#define LEFT_X_END -1.0
#define CENTER_X  0.0
#define RIGHT_X_END 1.0
#define UP_Y_END 1.0
#define CENTER_Y 0.0
#define BOTTOM_Y_END -1.0

#define TEXTURE_LEFT 0.0
#define TEXTURE_RIGHT 1.0
#define TEXTURE_UP  0.0
#define TEXTURE_BOTTOM  1.0 

static GLfloat fVerticesMattsSingleView[200]={
	LEFT_X_END,UP_Y_END,1.0,TEXTURE_LEFT,TEXTURE_UP,1.0,0.0,
		CENTER_X,UP_Y_END,1.0,TEXTURE_RIGHT,TEXTURE_UP,1.0,0.0,
		LEFT_X_END,CENTER_Y,1.000000,TEXTURE_LEFT,TEXTURE_BOTTOM,1.0,0.0,
		CENTER_X,CENTER_Y,1.000000,TEXTURE_RIGHT,TEXTURE_BOTTOM,1.0,0.0,
	CENTER_X,UP_Y_END,1.0,TEXTURE_LEFT,TEXTURE_UP,1.0,0.0,
			RIGHT_X_END,UP_Y_END,1.0,TEXTURE_RIGHT,TEXTURE_UP,1.0,0.0,
			CENTER_X,CENTER_Y,1.000000,TEXTURE_LEFT,TEXTURE_BOTTOM,1.0,0.0,
			RIGHT_X_END,CENTER_Y,1.000000,TEXTURE_RIGHT,TEXTURE_BOTTOM,1.0,0.0,
	LEFT_X_END,CENTER_Y,1.0,TEXTURE_LEFT,TEXTURE_UP,1.0,0.0,
		CENTER_X,CENTER_Y,1.0,TEXTURE_RIGHT,TEXTURE_UP,1.0,0.0,
		LEFT_X_END,BOTTOM_Y_END,1.000000,TEXTURE_LEFT,TEXTURE_BOTTOM,1.0,0.0,
		CENTER_X,BOTTOM_Y_END,1.000000,TEXTURE_RIGHT,TEXTURE_BOTTOM,1.0,0.0,
	CENTER_X,CENTER_Y,1.0,TEXTURE_LEFT,TEXTURE_UP,1.0,0.0,
			RIGHT_X_END,CENTER_Y,1.0,TEXTURE_RIGHT,TEXTURE_UP,1.0,0.0,
			CENTER_X,BOTTOM_Y_END,1.000000,TEXTURE_LEFT,TEXTURE_BOTTOM,1.0,0.0,
			RIGHT_X_END,BOTTOM_Y_END,1.000000,TEXTURE_RIGHT,TEXTURE_BOTTOM,1.0,0.0,
 };

CAvmMattsView::CAvmMattsView()
{

}
CAvmMattsView::~CAvmMattsView()
{

}
int CAvmMattsView::Init()
{
	unsigned char singleViewNodeStatus = 0;
	CAvmRenderDataBase::GetInstance()->GetSingleViewNodeStatus(&singleViewNodeStatus);
	if(singleViewNodeStatus == 0)
	{
		return MATTS_VIEW_INIT_FAILED;
	}
	CAvmRenderDataBase::GetInstance()->GetSingleViewNode(&m_singleViewNode);
	CAvmRenderDataBase::GetInstance()->GetSingleViewPlaneNode(m_singleViewPlaneNode);
	CAvmRenderDataBase::GetInstance()->GetSingleViewVertex(m_singleViewVertex);
	CAvmRenderDataBase::GetInstance()->GetSingleViewMesh(m_singleViewMesh);

	m_mattsViewRegion.Set(0.0, XrGetScreenWidth(), 0.0, XrGetScreenHeight());

	return MATTS_VIEW_NORMAL;
}
int CAvmMattsView::Update()
{	
	unsigned char mattsViewCmd = 0;

	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(mattsViewCmd);

	static unsigned char lastMattsViewCmd = 255;

	
	if(mattsViewCmd == MATTS_VIEW)
	{
		for(int i =eFrontSingle;i <= eRightSingle;i++)
		{
			if(lastMattsViewCmd != mattsViewCmd)
			{
				SetVertextValue(fVerticesMattsSingleView, four_camera_index);
				lastMattsViewCmd = mattsViewCmd;
			}
			m_singleViewPlaneNode[i -eFrontSingle]->SetEnable(1);
		}
		m_singleViewNode->SetRenderROI(&m_mattsViewRegion);
	}
	else if(mattsViewCmd >= FRONT_SINGLE_VIEW
		&& mattsViewCmd <= RIGHT_SINGLE_VIEW)
	{
		if(lastMattsViewCmd != mattsViewCmd)
		{
			float* vertexData;
			for(int i =eFrontSingle;i <= eRightSingle;i++)
			{
				CAvmRenderDataBase::GetInstance()->GetSingleViewRoi(&vertexData, i - eFrontSingle);
				SetVertextValue(vertexData, i - eFrontSingle);
			}
			Region* singleViewRegion;
			CAvmRenderDataBase::GetInstance()->GetSingleViewRegion(&singleViewRegion);
			m_singleViewNode->SetRenderROI(singleViewRegion);

			lastMattsViewCmd = mattsViewCmd;
		}
	}

	return MATTS_VIEW_NORMAL;
}
int CAvmMattsView::SetVertextValue(float* pVertex, int pViewIndex)
{
	if(pViewIndex == four_camera_index)
	{
		for(int i =eFrontSingle;i < eFrontSingle + four_camera_index;i++)
		{
			for(int j = 0; j < 28; j++)
			{
				m_singleViewVertex[i - eFrontSingle][j] = pVertex[(i - eFrontSingle)*28 + j];
			}
			m_singleViewMesh[i - eFrontSingle]->UnLockData();
		
		}
	}
	else if(pViewIndex < four_camera_index)
	{
		for(int j = 0; j < 28; j++)
		{
			m_singleViewVertex[pViewIndex][j] = pVertex[j];
		}
		m_singleViewMesh[pViewIndex]->UnLockData();
	}

	return MATTS_VIEW_NORMAL;
}
int CAvmMattsView::ResetMattsViewRegion()
{
	return MATTS_VIEW_NORMAL;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmMattsView class.
\*===========================================================================*/