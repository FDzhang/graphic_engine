/*===========================================================================*\
 * FILE: IAvmOverlay.h
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

#ifndef _IAVM_OVERLAY_H_
#define _IAVM_OVERLAY_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"

typedef enum AvmOverlayErrorCodeTag
{
	AVM_OVERLAY_NORMAL,
	AVM_OVERLAY_GET_NODE_FALIED,
};

class IAvmOverlay
{
public:

	virtual int Init(class ISceneNode* pRootNode);
	virtual int Update();

protected:
	class ISceneNode* m_rootNode;
};

#endif // _IAVM_OVERLAY_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/28/17   Jensen Wang   Create the IAvmOverlay class.
\*===========================================================================*/