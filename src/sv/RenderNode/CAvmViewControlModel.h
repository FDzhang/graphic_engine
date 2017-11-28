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

class CAvmViewControlModel
{
public:
	CAvmViewControlModel();
	virtual ~CAvmViewControlModel();
	virtual int InitViewNode();

	virtual int SetCurrentView();
	virtual int SetViewNodeVisibility(VisibilityIndexT pFuncId);

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

private:
	class CAvm3dViewNode* m_avm3dViewNode;
	class CAvmSingleViewNode* m_avmSingleViewNode;
	class CAvmStitchViewNode* m_avmStitchViewNode;
	class CAvmTimeStitcherNode* m_avmTimeStitcherNode;
	class CAvmObjectViewNode* m_avmObjViewNode;
	class CAvmMattsView*      m_avmMattsView;
	class CAvmLargeSingleView* m_avmLargeSingleView;

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