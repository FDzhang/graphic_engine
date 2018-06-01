/*===========================================================================*\
 * FILE: CAvmViewControlModel.h
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

#ifndef _CAVM_VIEWCONTROL_MODEL_H_
#define _CAVM_VIEWCONTROL_MODEL_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"

enum
{
	AVM_VIEWCONTROLMODEL_NORMAL,

};
typedef enum ViewNodeNameTag
{
	AVM_3D_VIEW_NODE = 0,
	AVM_SINGLE_VIEW_NODE,
	AVM_STITCH_VIEW_NODE,
	AVM_TIME_STITCHER_VIEW_NODE,
	AVM_OBJECT_VIEW_NODE,
	AVM_MATTS_VIEW_NODE,
	AVM_LARGESINGLE_VIEW_NODE,
	AVM_LINEAR_180VIEW_NODE,
	AVM_LEFT_RIGHT_VIEW_NODE,
	AVM_LARGE_3D_VIEW_NODE,
	AVM_VIEW_NODE_NUMS,
}
ViewNodeNameT;

typedef struct ViewNodeVisibilityTag
{
	VisibilityIndexT funcId;
	unsigned char flag;
}
ViewNodeVisibilityT;

class CAvmViewControlModel
{
public:
	CAvmViewControlModel();
	virtual ~CAvmViewControlModel();
	virtual int InitViewNode();

	virtual int Process3dTouchData();

	virtual int SetCurrentView();
	virtual int SetViewNodeVisibility(VisibilityIndexT pFuncId);

	int UpdateStitchAngle();
	int UpdateExternCalib2DReslt();
	int UpdateExternCalib3DReslt();

private:
	virtual int ProcessSingleViewDisplay();
	virtual int Process3dViewDisplay();
	virtual int Avm3dViewMode(unsigned char pViewIndex);
		
	virtual int InitDisplayEffect();
	virtual int InitBevDisplayEffect();
	virtual int InitTourDisplaySecEffect();

private:
	int ProcessTourView();
	int ProcessMattsView();
	int ProcessLargeSingleView();
	int ProcessTimeStitcher();
	int Process180DegreeView();
	int ProcessLeftRightView();
	int ProcessLarge3dView();
	int ProcessSideBySideSingleView();
	int SetViewNodeVisibility(ViewNodeVisibilityT pViewNodeVisibility[AVM_VIEW_NODE_NUMS]);

private:
	class CAvm3dViewNode* m_avm3dViewNode;
	class CAvmSingleViewNode* m_avmSingleViewNode;
	class CAvmStitchViewNode* m_avmStitchViewNode;
	class CAvmTimeStitcherNode* m_avmTimeStitcherNode;
	class CAvmObjectViewNode* m_avmObjViewNode;
	class CAvmMattsView*      m_avmMattsView;
	class CAvmLargeSingleView* m_avmLargeSingleView;
	class CAvmLinearViewNode*  m_avm180DegreeView;
	class CAvmLeftRightView* m_avmLeftRightView;
	class CAvmLeftLinearView* m_avmLeftLinearView;
	class CAvmRightLinearView* m_avmRightLinearView;
	class CAvmLarge3dView *  m_avmLarge3dView;
	class CAvmSideBySideSingleView* m_avmSideBySideSingleView;

	class IScrollingAnimation*	m_scrollX;
	class IScrollingAnimation*	m_scrollY;
	class IScrollingAnimation*	m_sliderX;
	class IScrollingAnimation*	m_sliderY;

	IXrCore* m_xrCore;
	int		 m_xrCoreId;

	IDeviceManager* m_rm;
	IAnimationManager* m_am;

	class IKeyAnimation*		m_wheelRot;
	class IKeyAnimation*		m_bulletrun;
	class IKeyAnimation*		m_bevdisplay[2];
	class IKeyAnimation*		m_bevTour[2];
	class IKeyAnimation*		m_bevSecTour[2];

};

#endif // _CAVM_VIEWCONTROL_MODEL_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/23/17   Jensen Wang   Create the CAvmViewControlModel class.
\*===========================================================================*/
