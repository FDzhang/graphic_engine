/*===========================================================================*\
 * FILE: CAvmLeftLinearView.h
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

#ifndef _CAVM_LEFTLINEAR_VIEW_H_
#define _CAVM_LEFTLINEAR_VIEW_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"

class CAvmLeftLinearView
{
public:
	CAvmLeftLinearView();
	~CAvmLeftLinearView();
	
	virtual int InitNode(class IXrCore* pXrcore);
	virtual int UpdateNode();
	virtual int SetVisibility(unsigned char pVisibilityFlag);

	int SetClear(unsigned char pColorFlag, unsigned char pDepthFlag);

private:
	class ISceneNode* m_leftLinearViewNode;	
	int         m_leftLinearViewNodeId;
	class ISceneNode* m_LinearViewNode;	
	int         m_LinearViewNodeId;

	class IMaterial* m_leftLinearViewMtl;
	int         m_leftLinearViewMtlId;
	class IMesh*	 m_leftLinearViewMesh;
	int			m_leftLinearViewMeshId;
		
	class IMesh*	 m_leftViewMesh;
	int			m_leftViewMeshId;

	class INode*      m_leftLinearViewPlane;

	class IXrCore*	m_xrCore;

	class ICamera*	m_leftLinearViewCamera;
	int			m_leftLinearViewCameraId;

	class RenderDelegateSV2D*		m_renderDelegate;
	class GlSV2D*				m_SV2DData;
	
	SurroundViewCameraParamsT*   m_leftLinearViewCameraParams;

	float*			 m_leftLinearviewVertex;

};

#endif // _CAVM_LEFTLINEAR_VIEW_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmLeftLinearView class.
\*===========================================================================*/
