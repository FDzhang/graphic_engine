/*===========================================================================*\
 * FILE: CAvmStitchViewNode.h
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

#ifndef _CAVM_STITCHVIEW_NODE_H_
#define _CAVM_STITCHVIEW_NODE_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"
#include "../SVDelegate.h"

enum
{
	AVM_STITCHVIEW_NORMAL = 0,
	AVM_STITCHVIEW_INIT_FAILED,
	AVM_STITCHVIEW_NODE_INIT_FAILED,
	AVM_STITCHVIEW_XRCORE_NULL,
};

class CAvmStitchViewNode
{
public:
	CAvmStitchViewNode();
	virtual ~CAvmStitchViewNode();
	virtual int InitNode(class IXrCore* pXrcore);
	virtual int UpdateNode();
	virtual int SetVisibility(unsigned char pVisibilityFlag);
	virtual int ResetStitchViewNodeRegion(Region* pRegion);

	int GetAvmStitchViewNode(class ISceneNode* pStitchViewNode);
	

private:
	class ISceneNode* m_stitchViewNode;	
	int         m_stitchViewNodeId;
	class IXrCore*	m_xrCore;

	class ICamera*	m_stitchViewCamera;
	int			m_stitchViewCameraId;

	class RenderDelegateSV2D*		m_renderDelegate; 
	
	SurroundViewCameraParamsT*   m_stitchViewCameraParams;

	unsigned char m_visibilityFlag;

	class INode*	m_SV2Dplane[eMeshIndexMax];
	class INode*	m_plane[8];
	class IMaterial*			m_SV2DMtl;
	class IMesh*				m_planeMesh;
	class GlSV2D*				m_SV2DData;


};

#endif // _CAVM_STITCHVIEW_NODE_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvmStitchViewNode class.
\*===========================================================================*/