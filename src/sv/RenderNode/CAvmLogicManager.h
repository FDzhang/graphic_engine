/*===========================================================================*\
 * FILE: CAvmLogicManager.h
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

#ifndef _CAVM_LOGIC_CONTROL_H_
#define _CAVM_LOGIC_CONTROL_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"
#include<vector>

using namespace std;

typedef enum AvmLogicManagerErrorCodeTag
{
	AVM_LOGIC_CONTROL_NORMAL,
	AVM_LOGIC_VIEW_MODEL_INIT_FAILED,

};

class ISVHmi;

class CAvmLogicManager
{
public:
	CAvmLogicManager();
	virtual ~CAvmLogicManager();
	virtual int Init();
	virtual int Update();
	virtual int ProcessTouchEvent();

	int UpdateRenderStatus();
	int UpdateStitchAngle();	
	int UpdateExternCalib2DReslt();
	int UpdateExternCalib3DReslt();
	int SetAdasHmiParams(st_ADAS_Mdl_HMI_T** pAdasMdl, int hmiNums);

private:
	virtual int InitViewModel();
	virtual int InitOverlayModel();
	virtual int InitAlgoHmiModel();
	virtual int InitHmi();
	virtual int SetMainHmiName();
	virtual int AddHmi(ISVHmi* pSvHmi, vector<ISVHmi*>* pHmi);

	virtual int UpdateViewModel();
	virtual int UpdateOverlayModel();
	virtual int UpdateAlgoHmiModel();
	virtual int UpdateHmi();

	virtual int RemoveHmi(vector<ISVHmi*>* pHmi, ISVHmi* pHmiObj);
private:
	class CAvmViewControlModel* m_avmViewControlModel;
	class SVNodeAdasHMI*		m_adasHmi;
	st_ADAS_Mdl_HMI_T **			m_adasMdl;
	int m_hmiNums;

	ISVHmi* m_systemHmi;

	char* m_mainHmiName;
	
	vector<ISVHmi*> m_avmHmi;
	vector<ISVHmi*> m_dvrHmi;
private:

};

#endif // _CAVM_LOGIC_CONTROL_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/23/17   Jensen Wang   Create the CAvmLogicManager class.
\*===========================================================================*/
