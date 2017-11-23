/*===========================================================================*\
 * FILE: CAvm3dViewNode.h
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

#ifndef _CAVM_3DVIEW_NODE_H_
#define _CAVM_3DVIEW_NODE_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"
#include "../SVDelegate.h"

enum
{
	AVM_3DVIEW_NORMAL = 0,
	AVM_3DVIEW_INIT_FAILED,
	AVM_3DVIEW_NODE_INIT_FAILED,
	AVM_3DVIEW_XRCORE_NULL,
};

class CAvm3dViewNode
{
public:
	CAvm3dViewNode();
	virtual ~CAvm3dViewNode();
	virtual int InitNode(class IXrCore* pXrcore);
	virtual int UpdateNode();
	virtual int SetVisibility(unsigned char pVisibilityFlag);
	virtual int Reset3dViewNodeRegion(Region* pRegion);
	

	class ISceneNode*  GetAvm3dViewNode();
	class ICamera*  GetAvm3dViewCamera();
	int SetClear(unsigned char pColorFlag, unsigned char pDepthFlag);

private:
	class ISceneNode* m_3dViewNode;	
	int         m_3dViewNodeId;
	class IXrCore*	m_xrCore;

	class ICamera*	m_3dViewCamera;
	int			m_3dViewCameraId;

	class RenderDelegateSV*		m_renderDelegate;
	
	SurroundViewCameraParamsT*   m_3dViewCameraParams;

	unsigned char m_visibilityFlag;
};

#endif // _CAVM_3DVIEW_NODE_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvm3dViewNode class.
\*===========================================================================*/