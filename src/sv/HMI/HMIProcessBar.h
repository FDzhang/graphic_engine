/*===========================================================================*\
 * FILE: HMIProcessBar.h
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

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/

#ifndef _HMI_PROCESSBAR_H_
#define _HMI_PROCESSBAR_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../DataStruct.h"

typedef enum HmiProcessBarElementTag
{
	PROCESS_BAR,
	PROCESS_BAR_ICON,
	PROCESS_BAR_BACKGROUND,
	PROCESS_BAR_HIGHLIGHT,
	PROCESS_BAR_ELEMENT_NUM,
}
HmiProcessBarElementT;

typedef enum HmiProcessBarErrorCodeTag
{
	HMI_PROCESSBAR_NORMAL,
	HMI_PROCESSBAR_ERROR_CODE_NUM,
}
HmiProcessBarErrorCodeTag;

typedef enum HmiProcessBarMovingModeTag
{
	PROCESS_BAR_FORWARD = 0,
	PROCESS_BAR_BACKWARD,
	PROCESS_BAR_MOVING_MODE_NUM,
}
HmiProcessBarMovingModeT;

typedef struct HmiProcessBarDataTag
{
	float pos[2];
	float width;
	float height;
	unsigned char withBkgFlag;
	unsigned char withBarIconFlag;
	char* iconFileName[PROCESS_BAR_ELEMENT_NUM];
	int targetIndex;
	InsertFlag insertFlag;
	IActionTrigger*    trigger;
}
HmiProcessBarDataT;

class HmiProcessBar : public IEventResponder
{
public:
	HmiProcessBar(HmiProcessBarDataT* pProcessBarData, IUINode* uiNode);
	virtual ~HmiProcessBar();
	virtual  int Init();
	virtual int Update();
	int SetVisibility(unsigned char pFlag);
	int Move(float pScale, HmiProcessBarMovingModeT pMovingMode);
private:
	int CalProcessBarPos(int x, int y);
private:
	virtual Boolean OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type);

	virtual String GetName();
	virtual Void SetName(
		/* [in] */ String name); 

	virtual Void* GetRealType() { return (Void*)this; }

	void SetOnClickDelegate(IActionTrigger* trigger);
private:
	int m_mtlId;
	int m_bkgId;
	int m_barIconId;
	int m_processBarId;

	IMaterial* m_processBarBkgMtl;
	int m_processBarBkgMtlId;
	IMaterial* m_processBarIconMtl;
	int m_processBarIconMtlId;

	unsigned char m_bkgVisibility;
	unsigned char m_barIconVisibility;
	unsigned char m_processBarVisibility;

	IMaterial* m_processBarMtl;
	int m_processBarMtlId;

	HmiProcessBarDataT* m_processBarData;
	
	IUINode*			m_uiNode;

	 IActionTrigger*	m_trigger;
	 String             m_name;

	 unsigned char      m_adjustScaleSignal;
	 float				m_rangeRightPos;
	 
};

#endif // _HMI_PROCESSBAR_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the HMIProcessBar class.
\*===========================================================================*/
