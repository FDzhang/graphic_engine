/*===========================================================================*\
 * FILE: CAvmFrontRearLinearView.h
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

#ifndef _CAVM_FRONT_REAR_LINEAR_VIEW_H_
#define _CAVM_FRONT_REAR_LINEAR_VIEW_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"

class CAvmFrontRearLinearView
{
public:
	CAvmFrontRearLinearView();
	~CAvmFrontRearLinearView();
	
	virtual int InitNode(class IXrCore* pXrcore);
	virtual int UpdateNode();
	virtual int SetVisibility(unsigned char pVisibilityFlag);

	int SetClear(unsigned char pColorFlag, unsigned char pDepthFlag);
private:
	int InitPlaneNode(int pPlaneIndex, unsigned char pViewIndex);
private:
	class ISceneNode* m_linearViewNode[2];	
	int         m_linearViewNodeId[2];


	class IMaterial* m_linearViewMtl;
	int         m_linearViewMtlId;
	class IMesh*	 m_linearViewMesh[2];
	int			m_linearViewMeshId[2];
		

	class INode*      m_linearViewPlane[2];

	class IXrCore*	m_xrCore;

	class ICamera*	m_linearViewCamera[2];
	int			m_linearViewCameraId[2];

	class RenderDelegateSV2D*		m_renderDelegate;
	class GlSV2D*				m_SV2DData;
	
	SurroundViewCameraParamsT*   m_linearViewCameraParams;

	float*			 m_linearViewVertex[4];
	
	unsigned char m_depthClearFlag;
	unsigned char m_colorClearFlag;
};

#endif // _CAVM_FRONT_REAR_LINEAR_VIEW_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmFrontRearLinearView class.
\*===========================================================================*/