/*===========================================================================*\
 * FILE: CAvmObjectViewNode.h
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

#ifndef _CAVM_OBJECTVIEW_NODE_H_
#define _CAVM_OBJECTVIEW_NODE_H_
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"
enum
{
	AVM_OBJVIEW_NORMAL = 0,
	AVM_OBJVIEW_INIT_FAILED,
	AVM_OBJVIEW_NODE_INIT_FAILED,
	AVM_OBJVIEW_XRCORE_NULL,
};

class CAvmObjectViewNode
{
	CAvmObjectViewNode();
	virtual ~CAvmObjectViewNode();
	virtual int InitNode(class IXrCore* pXrcore);
	virtual int UpdateNode();
	virtual int SetVisibility(unsigned char pVisibilityFlag);
	virtual int ResetObjViewNodeRegion(Region* pRegion);

	int GetAvmObjViewNode(class ISceneNode* pObjViewNode);
	

private:
	class ISceneNode* m_objViewNode;	
	int         m_objViewNodeId;
	class IXrCore*	m_xrCore;

	class ICamera*	m_objViewCamera;
	int			m_objViewCameraId;

    class IMesh*				m_planeMesh;
	class IMesh*				m_wheelMesh;
	class IMesh*				m_groundmesh;
	class IMesh*				m_pMeshStichGround[2];

	class IRenderTarget*		m_groundRT[2];
	class IRenderTarget*		m_lisenceRT;

	class RenderDelegateSV*		m_renderDelegate;
	
	SurroundViewCameraParamsT   m_objViewCameraParams;

	unsigned char m_visibilityFlag;

};

#endif // _CAVM_OBJECTVIEW_NODE_H_


/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/21/17   Jensen Wang   Create the CAvmObjectViewNode class.
\*===========================================================================*/