/*===========================================================================*\
 * FILE: CAvmLeftRightView.h
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

#ifndef _CAVM_LEFTRIGHT_VIEW_H_
#define _CAVM_LEFTRIGHT_VIEW_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"

class CAvmLeftRightView
{
public:
	CAvmLeftRightView();
	~CAvmLeftRightView();
	
	virtual int InitNode(class IXrCore* pXrcore);
	virtual int UpdateNode();
	virtual int SetVisibility(unsigned char pVisibilityFlag);

	int SetClear(unsigned char pColorFlag, unsigned char pDepthFlag);

private:
	class ISceneNode* m_leftRightViewNode[2];	
	int         m_leftRightViewNodeId[2];
	class ISceneNode* m_rightViewNode;	
	int         m_rightViewNodeId;

	class IMaterial* m_leftRightViewMtl;
	int         m_leftRightViewMtlId;
	class IMesh*	 m_leftRightViewMesh[2];
	int			m_leftRightViewMeshId[2];
		
	class IMesh*	 m_leftViewMesh;
	int			m_leftViewMeshId;

	class INode*      m_leftRightViewPlane[2];

	class IXrCore*	m_xrCore;

	class ICamera*	m_leftRightViewCamera[2];
	int			m_leftRightViewCameraId[2];

	class RenderDelegateSV2D*		m_renderDelegate;
	class GlSV2D*				m_SV2DData;
	
	SurroundViewCameraParamsT*   m_leftRightViewCameraParams;

	float*			 m_leftRightviewVertex[4];

};

#endif // _CAVM_LEFTRIGHT_VIEW_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmLeftRightView class.
\*===========================================================================*/