/*===========================================================================*\
 * FILE: CAvmLarge3dView.cpp
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
#include "CAvmLarge3dView.h"
#include "../AVMData.h"

CAvmLarge3dView::CAvmLarge3dView():m_lastLargeViewCmd(255)
{
}
CAvmLarge3dView::~CAvmLarge3dView()
{
}

int CAvmLarge3dView::Init()
{
	unsigned char avm3dViewNodeStatus = 0;
	CAvmRenderDataBase::GetInstance()->Get3dViewNodeStatus(&avm3dViewNodeStatus);
	unsigned char avmObjViewNodeStatus = 0;
	CAvmRenderDataBase::GetInstance()->GetObjectViewNodeStatus(&avmObjViewNodeStatus);

	if(avm3dViewNodeStatus == 0
		|| avmObjViewNodeStatus == 0)
	{
		return LARGE_3D_VIEW_NODE_INIT_FAILED;
	}
	CAvmRenderDataBase::GetInstance()->Get3dViewNode(&m_3dViewNode);
	CAvmRenderDataBase::GetInstance()->GetObjectViewNode(&m_objViewNode);

    float stich_region_width = 0.35 *  XrGetScreenWidth();

	float black_width = 80.0;
	
	m_largeViewRegion.Set(100.0, XrGetScreenWidth(), black_width, XrGetScreenHeight() - black_width);

	return LARGE_3D_VIEW_NORMAL;
}
int CAvmLarge3dView::Update()
{
	if(m_3dViewNode == NULL)
	{
		return LARGE_3D_VIEW_NODE_INIT_FAILED;
	}
	unsigned char largeViewCmd = 0;

	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(largeViewCmd);
	
	if(largeViewCmd == TOUR_LARGE_3D_VIEW)
	{
		if(m_lastLargeViewCmd != largeViewCmd)
		{
			m_3dViewNode->SetRenderROI(&m_largeViewRegion);
			m_objViewNode->SetRenderROI(&m_largeViewRegion);
			m_objViewNode->SetClear(TRUE, TRUE);
			m_lastLargeViewCmd = largeViewCmd;
		}
	}
	else
	{
		if(m_lastLargeViewCmd != largeViewCmd)
		{
			Region* avm3dViewRegion;
			Region* avmObjViewRegion;
			CAvmRenderDataBase::GetInstance()->Get3dViewRegion(&avm3dViewRegion);
			m_3dViewNode->SetRenderROI(avm3dViewRegion);

			CAvmRenderDataBase::GetInstance()->GetObjectViewRegion(&avmObjViewRegion);
			m_objViewNode->SetRenderROI(avmObjViewRegion);
			m_objViewNode->SetClear(FALSE, TRUE);
			
			m_lastLargeViewCmd = largeViewCmd;
		}
	}


	return LARGE_3D_VIEW_NORMAL;
}

int CAvmLarge3dView::ResetLargeViewRegion()
{
	
	return LARGE_3D_VIEW_NORMAL;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmLarge3dView class.
\*===========================================================================*/
