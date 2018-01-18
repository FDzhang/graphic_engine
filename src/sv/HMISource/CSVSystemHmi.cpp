/*===========================================================================*\
 * FILE: CSVSystemHmi.cpp
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
#include "CSVSystemHmi.h"

#include "gpu_log.h"

	
class CMouseIconActionTrigger : public IActionTrigger
{

	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CLiveVideoTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};


CSVSystemHmi::CSVSystemHmi()
{
	memset(m_trigger, NULL, SYSTEM_HMI_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, SYSTEM_HMI_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 1, SYSTEM_HMI_ELEMEMT_NUM * sizeof(unsigned char));
	
}

CSVSystemHmi::~CSVSystemHmi()
{

	for(int i = SYSTEM_HMI_MOUSE_ICON; i < SYSTEM_HMI_ELEMEMT_NUM; i++)
	{
		
	    SAFE_DELETE(m_trigger[i]);

		SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
	
		SAFE_DELETE(m_baseButton[i]);
	}
		
	Log_Error("----------Release CSVSystemHmi!");
}

	
int CSVSystemHmi::SetHmiParams()
{
	m_baseButtonData[SYSTEM_HMI_MOUSE_ICON].icon_type = DYNAMIC_ICON;
	m_baseButtonData[SYSTEM_HMI_MOUSE_ICON].show_flag = 1;
	m_baseButtonData[SYSTEM_HMI_MOUSE_ICON].show_icon_num = 0;
	m_baseButtonData[SYSTEM_HMI_MOUSE_ICON].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[SYSTEM_HMI_MOUSE_ICON].icon_file_name[0],"%sCar/cursor.dds",XR_RES); 


	for(int i = SYSTEM_HMI_MOUSE_ICON; i < SYSTEM_HMI_ELEMEMT_NUM; i++)
	{
		m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
		m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
		m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
		m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
		m_baseButtonData[i].delegate_func = NULL;
		m_baseButtonData[i].trigger = m_trigger[i];
		m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
		m_baseButton[i]->SetVisibility(0);
	}


	return HMI_SUCCESS;
}
int CSVSystemHmi::Init(int window_width, int window_height)
{
	m_windowWidth = window_width;
	m_windowHeight = window_height;

	m_buttonPos[SYSTEM_HMI_MOUSE_ICON][BUTTON_POS_X] = 0.0;
	m_buttonPos[SYSTEM_HMI_MOUSE_ICON][BUTTON_POS_Y] = 80.0;
	m_buttonSize[SYSTEM_HMI_MOUSE_ICON][BUTTON_SIZE_WIDTH] = 64;
	m_buttonSize[SYSTEM_HMI_MOUSE_ICON][BUTTON_SIZE_HEIGHT] = 64;

	SetHmiParams();

	return HMI_SUCCESS;
}
int CSVSystemHmi::Update(Hmi_Message_T& hmiMsg)
{

	CAvmRenderDataBase::GetInstance()->GetMouseIconVisibility(m_buttonVisibility[SYSTEM_HMI_MOUSE_ICON]);
    //m_buttonVisibility[SYSTEM_HMI_MOUSE_ICON] = 1;

	TouchDataT touchData;
	CAvmRenderDataBase::GetInstance()->GetTouchData(&touchData);

	if(touchData.touchAction == TouchEvent_Move)
	{
		m_baseButton[SYSTEM_HMI_MOUSE_ICON]->SetX(touchData.x);
		m_baseButton[SYSTEM_HMI_MOUSE_ICON]->SetY(touchData.y);		
	}

	static ISVHmi* m_lastHmi = NULL;

	static int cnt = 0;
	if((CSVHmiIntent::GetInstance()->GetCurrentHmi()
		&& CSVHmiIntent::GetInstance()->GetCurrentHmi() != m_lastHmi))
	{
		m_lastHmi = CSVHmiIntent::GetInstance()->GetCurrentHmi();
	
		CSVHmiIntent::GetInstance()->MoveToAfter(CSVHmiIntent::GetInstance()->GetCurrentHmi()->GetSvHmiNodeId(), m_uiNodeId);
	}
	

    RefreshHmi();

    return HMI_SUCCESS;
}

int CSVSystemHmi::RefreshHmi()
{
	for(int i = SYSTEM_HMI_MOUSE_ICON; i < SYSTEM_HMI_ELEMEMT_NUM; i++)

	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
		
	return HMI_SUCCESS;
}

int CSVSystemHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVSystemHmi::DestroyHmiElems()
{
	return HMI_SUCCESS;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVSystemHmi class.
\*===========================================================================*/


