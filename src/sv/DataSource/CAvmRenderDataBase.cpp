/*===========================================================================*\
 * FILE: CAvmRenderInterface.h
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
#include "CAvmRenderDataBase.h"
#include "../AVMData.h"

CAvmRenderDataBase* CAvmRenderDataBase::m_Instance = NULL;

CAvmRenderDataBase* CAvmRenderDataBase::GetInstance()
{
	if(m_Instance == NULL)
	{
		m_Instance = new CAvmRenderDataBase;
	}
	return m_Instance;
}

void CAvmRenderDataBase::SetSingleViewMesh(class IMesh* pSingleViewMesh[])
{
	m_singleViewMesh[0] = pSingleViewMesh[0];
	m_singleViewMesh[1] = pSingleViewMesh[1];
	m_singleViewMesh[2] = pSingleViewMesh[2];
	m_singleViewMesh[3] = pSingleViewMesh[3];
}
void CAvmRenderDataBase::GetSingleViewMesh(class IMesh* pSingleViewMesh[])
{
	pSingleViewMesh[0] = m_singleViewMesh[0];
	pSingleViewMesh[1] = m_singleViewMesh[1];
	pSingleViewMesh[2] = m_singleViewMesh[2];
	pSingleViewMesh[3] = m_singleViewMesh[3];
}

void CAvmRenderDataBase::SetSingleViewVertex(float* pSingleViewVertex[])
{
	m_singleViewVertex[0] = pSingleViewVertex[0];
	m_singleViewVertex[1] = pSingleViewVertex[1];
	m_singleViewVertex[2] = pSingleViewVertex[2];
	m_singleViewVertex[3] = pSingleViewVertex[3];
}
void CAvmRenderDataBase::GetSingleViewVertex(float* pSingleViewVertex[])
{
	pSingleViewVertex[0] = m_singleViewVertex[0];
	pSingleViewVertex[1] = m_singleViewVertex[1];
	pSingleViewVertex[2] = m_singleViewVertex[2];
	pSingleViewVertex[3] = m_singleViewVertex[3];
}

void CAvmRenderDataBase::SetSingleViewPlaneNode(class INode* pSingleViewPlaneNode[])
{
	m_singleViewPlaneNode[0] = pSingleViewPlaneNode[eFrontSingle];
	m_singleViewPlaneNode[1] = pSingleViewPlaneNode[eRearSingle];
	m_singleViewPlaneNode[2] = pSingleViewPlaneNode[eLeftSingle];
	m_singleViewPlaneNode[3] = pSingleViewPlaneNode[eRightSingle];
}
void CAvmRenderDataBase::GetSingleViewPlaneNode(class INode* pSingleViewPlaneNode[])
{
	pSingleViewPlaneNode[0] = m_singleViewPlaneNode[0];
	pSingleViewPlaneNode[1] = m_singleViewPlaneNode[1];
	pSingleViewPlaneNode[2] = m_singleViewPlaneNode[2];
	pSingleViewPlaneNode[3] = m_singleViewPlaneNode[3];
}

void CAvmRenderDataBase::SetSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;

	static unsigned initFlag[4] = {0};
	if(initFlag[pViewIndex] == 0)
	{
		m_singleViewRoi[pViewIndex] = new float[28];
		initFlag[pViewIndex] = 1;
	}
	
	memcpy(m_singleViewRoi[pViewIndex], pSingleViewRoi, sizeof(float)*28);
}
void CAvmRenderDataBase::GetSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;
	*pSingleViewRoi = m_singleViewRoi[pViewIndex];
}

void CAvmRenderDataBase::SetLargeSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;

	static unsigned initFlag[4] = {0};
	if(initFlag[pViewIndex] == 0)
	{
		m_largeSingleViewRoi[pViewIndex] = new float[4];
		initFlag[pViewIndex] = 1;
	}
	
	memcpy(m_largeSingleViewRoi[pViewIndex], pSingleViewRoi, sizeof(float)*4);
}
void CAvmRenderDataBase::GetLargeSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;
	*pSingleViewRoi = m_largeSingleViewRoi[pViewIndex];
}

void CAvmRenderDataBase::SetSideBySideSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;

	static unsigned initFlag[4] = {0};
	if(initFlag[pViewIndex] == 0)
	{
		m_sideBySideSingleViewRoi[pViewIndex] = new float[4];
		initFlag[pViewIndex] = 1;
	}
	
	memcpy(m_largeSingleViewRoi[pViewIndex], pSingleViewRoi, sizeof(float)*4);
}
void CAvmRenderDataBase::GetSideBySideSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex)
{
	if(pViewIndex > right_camera_index)
		pViewIndex = 0;
	*pSingleViewRoi = m_sideBySideSingleViewRoi[pViewIndex];
}


void CAvmRenderDataBase::GetLeftRightViewRegion(Region** pLeftRightViewReg, unsigned char viewIndex)
{
	if(viewIndex == left_camera_index)
	{
		*pLeftRightViewReg = &m_leftViewRegion; 
	}
	else if(viewIndex == right_camera_index)
	{
		*pLeftRightViewReg = &m_rightViewRegion; 
	}	
}
void CAvmRenderDataBase::SetLeftRightViewRegion(Region* pLeftRightViewReg, unsigned char viewIndex)
{
	if(viewIndex == left_camera_index)
	{
		m_leftViewRegion = *pLeftRightViewReg; 
	}
	else if(viewIndex == right_camera_index)
	{
		m_rightViewRegion = *pLeftRightViewReg; 
	}
}
void CAvmRenderDataBase::GetSideBySideSingleViewRegion(Region** pLeftRightViewReg, unsigned char viewIndex)
{
	if(viewIndex == left_camera_index)
	{
		*pLeftRightViewReg = &m_leftSingleViewRegion; 
	}
	else if(viewIndex == right_camera_index)
	{
		*pLeftRightViewReg = &m_rightSingleViewRegion; 
	}	
}
void CAvmRenderDataBase::SetSideBySideSingleViewRegion(Region* pLeftRightViewReg, unsigned char viewIndex)
{
	if(viewIndex == left_camera_index)
	{
		m_leftSingleViewRegion = *pLeftRightViewReg; 
	}
	else if(viewIndex == right_camera_index)
	{
		m_rightSingleViewRegion = *pLeftRightViewReg; 
	}
}


void CAvmRenderDataBase::Set3dViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avm3dVisibility[pFuncId] = pFlag;
}
void CAvmRenderDataBase::Get3dViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avm3dVisibility[pFuncId];
}
void CAvmRenderDataBase::SetStitchViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avmStitchViewVisibility[pFuncId] = pFlag;
}
void CAvmRenderDataBase::GetStitchViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avmStitchViewVisibility[pFuncId];
}
void CAvmRenderDataBase::SetSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avmSingleViewVisibility[pFuncId] = pFlag;
}
void CAvmRenderDataBase::GetSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avmSingleViewVisibility[pFuncId];
}
void CAvmRenderDataBase::SetObjectViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avmObjViewVisibility[pFuncId] = pFlag;
}
void CAvmRenderDataBase::GetObjectViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avmObjViewVisibility[pFuncId];
}
void CAvmRenderDataBase::Set180DegreeViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avm180DegreeViewVisibility[pFuncId] = pFlag;
}
void CAvmRenderDataBase::Get180DegreeViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avm180DegreeViewVisibility[pFuncId];
}
void CAvmRenderDataBase::SetLeftRightViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avmLeftRightViewVisibility[pFuncId] = pFlag;
}
void CAvmRenderDataBase::GetLeftRightViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avmLeftRightViewVisibility[pFuncId];
}

void CAvmRenderDataBase::SetSideBySideSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag)
{
	m_avmSideBySideSingleViewVisibility[pFuncId] = pFlag;
}

void CAvmRenderDataBase::GetSideBySideSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag)
{
	pFlag = m_avmSideBySideSingleViewVisibility[pFuncId];
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  1/4/18     Jensen Wang   Create the CAvmRenderInterface .
\*===========================================================================*/
