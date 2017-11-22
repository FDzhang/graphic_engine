/*===========================================================================*\
 * FILE: CAvmSingleViewNode.h
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

#ifndef _CAVM_SINGLEVIEW_NODE_H_
#define _CAVM_SINGLEVIEW_NODE_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"
#include "../SVDelegate.h"

enum
{
	AVM_SINGLEVIEW_NORMAL = 0,
	AVM_SINGLEVIEW_INIT_FAILED,
	AVM_SINGLEVIEW_NODE_INIT_FAILED,
	AVM_SINGLEVIEW_XRCORE_NULL,
};

class CAvmSingleViewNode
{
public:
	CAvmSingleViewNode();
	virtual ~CAvmSingleViewNode();
	virtual int InitNode(class IXrCore* pXrcore);
	virtual int UpdateNode();
	virtual int SetVisibility(unsigned char pVisibilityFlag);
	virtual int ResetSingleViewNodeRegion(Region* pRegion);

	int GetAvmSingleViewNode(class ISceneNode* pSingleViewNode);
	

private:
	class ISceneNode* m_singleViewNode;	
	int         m_singleViewNodeId;
	class IXrCore*	m_xrCore;

	class ICamera*	m_singleViewCamera;
	int			m_singleViewCameraId;

	class RenderDelegateSV2D*		m_renderDelegate; 
	
	SurroundViewCameraParamsT*   m_singleViewCameraParams;

	unsigned char m_visibilityFlag;

	class INode*	 m_SV2Dplane[eMeshIndexMax];
	class INode*	 m_plane[8];
	class IMaterial* m_SVSingleMtl;
	class IMesh*	 m_singleViewMesh[4];
	class GlSV2D*	 m_SV2DData;

	float*			 m_singleviewVertex[4];


};

#endif // _CAVM_SINGLEVIEW_NODE_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvmSingleViewNode class.
\*===========================================================================*/