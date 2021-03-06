/*===========================================================================*\
 * FILE: CAvmLarge3dView.h
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

#ifndef _CAVM_LARGE_3D_VIEW_H_
#define _CAVM_LARGE_3D_VIEW_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"


class CAvmLarge3dView
{
public:
	CAvmLarge3dView();
	~CAvmLarge3dView();
	
	virtual int Init();
	virtual int Update();

	int ResetLargeViewRegion();

private:
	class ISceneNode* m_3dViewNode;
	class ISceneNode* m_objViewNode;
	Region m_largeViewRegion;
	unsigned char m_lastLargeViewCmd;
};

#endif // _CAVM_LARGE_SINGLEVIEW_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/24/17   Jensen Wang   Create the CAvmLarge3dView class.
\*===========================================================================*/