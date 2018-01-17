/*===========================================================================*\
 * FILE: HmiProcessBar.cpp
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
#include "gpu_log.h"
#include "HMIProcessBar.h"

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;
/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/



HmiProcessBar::HmiProcessBar(HmiProcessBarDataT* pProcessBarData,IUINode* uiNode)
{
	if(uiNode == NULL
		|| pProcessBarData == NULL)
	{
		return;
	}

	m_adjustScaleSignal = 0;
	m_rangeRightPos = 0;

	m_uiNode = uiNode;
	m_processBarData = new HmiProcessBarDataT;
	memcpy(m_processBarData, pProcessBarData, sizeof(HmiProcessBarDataT));

	if(m_processBarData->withBkgFlag == 1)
	{
		m_processBarBkgMtlId = m_uiNode->CreateUIMaterial(Material_UI_Spirit, m_processBarData->iconFileName[PROCESS_BAR_BACKGROUND],
			0.0, &m_processBarBkgMtl);
		m_bkgId = m_uiNode->CreateSpirit(-1, InsertFlag_Default, m_processBarBkgMtlId, 1.0, 
			m_processBarData->pos[0], m_processBarData->pos[1], 0, m_processBarData->width, m_processBarData->height);
		m_bkgVisibility = 0;

	}

	m_processBarMtlId = m_uiNode->CreateUIMaterial(Material_UI_Spirit, m_processBarData->iconFileName[PROCESS_BAR],
		0.0, &m_processBarMtl);
	m_processBarId = m_uiNode->CreateSpirit(-1, InsertFlag_Default, m_processBarMtlId, 1.0, 
		m_processBarData->pos[0], m_processBarData->pos[1], 0, m_processBarData->width, m_processBarData->height);
	m_processBarVisibility = 0;

	if(m_processBarData->withBarIconFlag == 1)
	{
		m_processBarIconMtlId = m_uiNode->CreateUIMaterial(Material_UI_Spirit, m_processBarData->iconFileName[PROCESS_BAR_ICON],
			0.0, &m_processBarIconMtl);
		m_barIconId = m_uiNode->CreateSpirit(-1, InsertFlag_Default, m_processBarIconMtlId, 1.0, 
			m_processBarData->pos[0], m_processBarData->pos[1], 0, m_processBarData->width, m_processBarData->height);
		m_barIconVisibility = 0;
	}

	if(m_processBarData->trigger)
	{
		SetOnClickDelegate(m_processBarData->trigger);
	}

}
HmiProcessBar::~HmiProcessBar()
{
}
int HmiProcessBar::Init()
{

	return HMI_PROCESSBAR_NORMAL;
}
int HmiProcessBar::Update()
{
	ISpirit *processBarLayer = m_uiNode->GetSpirit(m_processBarId);

	if(m_processBarVisibility == 0)
	{
		processBarLayer->SetEnable(0);

	}
	else
	{
		processBarLayer->SetEnable(1);


	}
	if(m_processBarData->withBkgFlag == 1)
	{
		ISpirit *processBarBkgLayer = m_uiNode->GetSpirit(m_bkgId);
		processBarBkgLayer->SetEnable(m_bkgVisibility);
	}
	return HMI_PROCESSBAR_NORMAL;
}

int HmiProcessBar::SetVisibility(unsigned char pFlag)
{
	if(pFlag > 0)
	{
		pFlag = 1;
	}
	m_processBarVisibility = pFlag;
	m_bkgVisibility = pFlag;

	ISpirit *processBarLayer = m_uiNode->GetSpirit(m_processBarId);
	processBarLayer->SetEnable(m_processBarVisibility);
	
	if(m_processBarData->withBkgFlag == 1)
	{
		ISpirit *processBarBkgLayer = m_uiNode->GetSpirit(m_bkgId);
		processBarBkgLayer->SetEnable(m_bkgVisibility);
	}
	return HMI_PROCESSBAR_NORMAL;
}

int HmiProcessBar::Move(float pScale, HmiProcessBarMovingModeT pMovingMode)
{
	/*if(m_adjustScaleSignal == 1)
	{
		return HMI_PROCESSBAR_NORMAL;
	}*/

	Region procBarTextureReg;
	float rangeLeftPos = 0.0;
	//float rangeRightPos = 1.0;
	float rangeTopPos = 0.0;
	float rangeBottomPos = 1.0;
	ISpirit *processBarLayer = m_uiNode->GetSpirit(m_processBarId);

	if(pMovingMode == PROCESS_BAR_FORWARD)
	{
		if(pScale > 1.0)
		{
			pScale = 1.0;
		}
		procBarTextureReg.Set(rangeLeftPos, pScale, rangeTopPos, rangeBottomPos);

		processBarLayer->SetMaterialROI(&procBarTextureReg);
		processBarLayer->SetWidth(pScale * m_processBarData->width);

	}

	return HMI_PROCESSBAR_NORMAL;
}


int HmiProcessBar::CalProcessBarPos(int x, int y)
{
	m_adjustScaleSignal = 1;

	Region procBarTextureReg;

	float rangeLeftPos = 0.0;
	float rangeRightPos = 1.0;
	float rangeTopPos = 0.0;
	float rangeBottomPos = 1.0;

	m_rangeRightPos = (float)x / m_processBarData->width;

	procBarTextureReg.Set(rangeLeftPos, m_rangeRightPos, rangeTopPos, rangeBottomPos);
	
	ISpirit *processBarLayer = m_uiNode->GetSpirit(m_processBarId);
	processBarLayer->SetMaterialROI(&procBarTextureReg);
	processBarLayer->SetWidth(x);

	return HMI_PROCESSBAR_NORMAL;
}
Boolean HmiProcessBar::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	if (type == TouchEvent_Down) {
		m_clickX = x;
        if (m_trigger) m_trigger->OnPress(layerId);
//		CalProcessBarPos(x, y);
	}
	else if (type == TouchEvent_Up) {
		if (m_trigger) m_trigger->OnRelease(layerId, true);
		m_adjustScaleSignal = 0;
	}
	else if(type == TouchEvent_Move)
	{
		if(x > m_processBarData->width)
		{
			x = m_processBarData->width;
		}
		else if(x < 0)
		{
			x = 0;
		}
		CalProcessBarPos(x, y);
	}
	return TRUE;
}

Void HmiProcessBar::SetOnClickDelegate(IActionTrigger* trigger)
{
	ISpirit *processBarLayer = m_uiNode->GetSpirit(m_processBarId);
	if (processBarLayer) processBarLayer->SetEventResponder(this);

	if(m_processBarData->withBkgFlag == 1)
	{
		ISpirit *processBarBkgLayer = m_uiNode->GetSpirit(m_bkgId);
		if (processBarBkgLayer) processBarBkgLayer->SetEventResponder(this);
	}

	m_trigger = trigger;
}
String HmiProcessBar::GetName()
{
	return m_name;
}

Void HmiProcessBar::SetName(String name)
{
	if (!m_name) {m_name = new CHAR[MaxNameLen];
	}
	if (!m_name) return;
	strcpy(m_name, name);
}

int HmiProcessBar::GetClickX()
{
    return m_clickX;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the HmiProcessBar class.
\*===========================================================================*/
