/*===========================================================================*\
 * FILE: CAvmMattsView.h
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
#ifndef _CAVM_MATTSVIEW_H_
#define _CAVM_MATTSVIEW_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"

enum AvmMattsViewErrorCodeTag
{
	MATTS_VIEW_NORMAL = 0,
	MATTS_VIEW_INIT_FAILED,
};

class CAvmMattsView
{
public:
	CAvmMattsView();
	~CAvmMattsView();
	virtual int Init();
	virtual int Update();
	int ResetMattsViewRegion();
private:
	int SetVertextValue(float* pVertex, int pViewIndex);
	int SetLargeViewVertextValue(float* pVertex, int pViewIndex);
private:
	class ISceneNode* m_singleViewNode;
	class INode*	  m_singleViewPlaneNode[4];
	class IMesh*	  m_singleViewMesh[4];
	float*			  m_singleViewVertex[4];

	Region			  m_mattsViewRegion;
	
	float*			  m_singleViewRoi[4];
};

#endif

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmMattsView class.
\*===========================================================================*/
