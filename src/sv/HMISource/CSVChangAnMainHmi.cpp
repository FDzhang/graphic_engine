/*===========================================================================*\
 * FILE: CSVChangAnMainHmi.cpp
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
#include "CSVChangAnMainHmi.h"
#include "CSVChangAnSwitchViewHmi.h"
#include "CSVHmiIntent.h"

static unsigned char hmiElementVisibility[CHANGAN_MAIN_ELEMENT_NUM];
static unsigned char dvrStatus = 0;

REGISTER_HMI_CLASS(CSVChangAnMainHmi)

class CEnterMenuActionTrigger : public IActionTrigger
{
public:
	CEnterMenuActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		Log_Message("-----------CEnterMenuActionTrigger: %d", sizeof(Ctrl_Cmd_T));
		for(int i = 0; i < CHANGAN_MAIN_ELEMENT_NUM; i ++)
		{
			hmiElementVisibility[i] = 1;
		}
		hmiElementVisibility[CHANGAN_MAIN_MENU_ENTER_ICON] = 0;
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{

	}
	

private:
};

class CExitMenuActionTrigger : public IActionTrigger
{
public:
	CExitMenuActionTrigger()
	{ 
		;
	}
	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	
		Log_Message("-----------CExitMenuActionTrigger: %d", sizeof(Ctrl_Cmd_T));
		for(int i = 0; i < CHANGAN_MAIN_ELEMENT_NUM; i ++)
		{
			hmiElementVisibility[i] = 0;
		}
		hmiElementVisibility[CHANGAN_MAIN_MENU_ENTER_ICON] = 1;
	}

	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
private:
};

class CStartDvrActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CStartDvrActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{

	}

	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	/*
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);

		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		char* hmiName = "CSVDvrBaseHmi";
		CSVHmiIntent::GetInstance()->Intent(hmiName);

		Log_Message("-----------CStartDvrActionTrigger: %d", sizeof(Ctrl_Cmd_T));

		//Release();
		
		dvrStatus = 1;
*/
	}

	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{

	}

private:

};


CSVChangAnMainHmi::CSVChangAnMainHmi()
{
	memset(m_trigger, NULL, CHANGAN_MAIN_ELEMENT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonVisibility, 1, CHANGAN_MAIN_ELEMENT_NUM * sizeof(unsigned char));

	m_cameraHmiVisibility = 1;
	
	for(int i = CHANGAN_MAIN_MENU_BKG; i < CHANGAN_MAIN_ELEMENT_NUM; i ++)
	{
		hmiElementVisibility[i] = 0;
	}
	hmiElementVisibility[CHANGAN_MAIN_MENU_ENTER_ICON] = 1;

	m_cameraHmi = NULL;
	//m_cameraHmi = new CSVChangAnSwitchViewHmi(m_uiNode, m_uiNodeId);

}

CSVChangAnMainHmi::~CSVChangAnMainHmi()
{
	for(int i = 0; i < CHANGAN_MAIN_ELEMENT_NUM; i++)
	{
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);

		if(i > CHANGAN_MAIN_MENU_BKG)
		{
	        SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);		
		}
	    
		SAFE_DELETE(m_baseButton[i]);
		SAFE_DELETE(m_trigger[i]);
	}

	SAFE_DELETE(m_cameraHmi);
	
	Log_Error("----------Release ~CSVChangAnMainHmi!");
}
	
int CSVChangAnMainHmi::SetHmiParams()
{
	m_baseButtonData[CHANGAN_MAIN_MENU_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_MAIN_MENU_BKG].show_flag = 1;
	m_baseButtonData[CHANGAN_MAIN_MENU_BKG].show_icon_num = 0;
	m_baseButtonData[CHANGAN_MAIN_MENU_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[CHANGAN_MAIN_MENU_BKG].icon_file_name[0],"%sCar/MAIN/main_menu_bkg.dds",XR_RES);


	m_baseButtonData[CHANGAN_MAIN_MENU_ENTER_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_MAIN_MENU_ENTER_ICON].show_flag = 1;
	m_baseButtonData[CHANGAN_MAIN_MENU_ENTER_ICON].show_icon_num = 0;
	m_baseButtonData[CHANGAN_MAIN_MENU_ENTER_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_baseButtonData[CHANGAN_MAIN_MENU_ENTER_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[CHANGAN_MAIN_MENU_ENTER_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[CHANGAN_MAIN_MENU_ENTER_ICON].icon_file_name[0],"%sCar/MAIN/menu_enter_normal.dds",XR_RES);
	sprintf(m_baseButtonData[CHANGAN_MAIN_MENU_ENTER_ICON].icon_file_name[1],"%sCar/MAIN/menu_enter_press.dds",XR_RES);	
	m_trigger[CHANGAN_MAIN_MENU_ENTER_ICON] = new CEnterMenuActionTrigger;

	m_baseButtonData[CHANGAN_MAIN_MENU_EXIT_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_MAIN_MENU_EXIT_ICON].show_flag = 1;
	m_baseButtonData[CHANGAN_MAIN_MENU_EXIT_ICON].show_icon_num = 0;	
	m_baseButtonData[CHANGAN_MAIN_MENU_EXIT_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_baseButtonData[CHANGAN_MAIN_MENU_EXIT_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[CHANGAN_MAIN_MENU_EXIT_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[CHANGAN_MAIN_MENU_EXIT_ICON].icon_file_name[0],"%sCar/MAIN/menu_exit_normal.dds",XR_RES);
	sprintf(m_baseButtonData[CHANGAN_MAIN_MENU_EXIT_ICON].icon_file_name[1],"%sCar/MAIN/menu_exit_press.dds",XR_RES);	
	m_trigger[CHANGAN_MAIN_MENU_EXIT_ICON] = new CExitMenuActionTrigger;


	m_baseButtonData[CHANGAN_MAIN_DVR_START_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[CHANGAN_MAIN_DVR_START_ICON].show_flag = 1;
	m_baseButtonData[CHANGAN_MAIN_DVR_START_ICON].show_icon_num = 0;
	m_baseButtonData[CHANGAN_MAIN_DVR_START_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[CHANGAN_MAIN_DVR_START_ICON].icon_file_name[1] = new char[50];
	m_baseButtonData[CHANGAN_MAIN_DVR_START_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	sprintf(m_baseButtonData[CHANGAN_MAIN_DVR_START_ICON].icon_file_name[0],"%sCar/MAIN/menu_dvr_normal.dds",XR_RES);
	sprintf(m_baseButtonData[CHANGAN_MAIN_DVR_START_ICON].icon_file_name[1],"%sCar/MAIN/menu_dvr_press.dds",XR_RES);	
	m_trigger[CHANGAN_MAIN_DVR_START_ICON] = new CStartDvrActionTrigger;

	for(int i = CHANGAN_MAIN_MENU_BKG; i < CHANGAN_MAIN_ELEMENT_NUM; i++)
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

	if(m_cameraHmi)
	{
		m_cameraHmi->Init(m_screenWidth, m_screenHeight);
	}

	return CHANGAN_MAIN_HMI_NORMAL;
}
int CSVChangAnMainHmi::Init(int window_width, int window_height)
{
	m_screenWidth = window_width;
	m_screenHeight = window_height;

	m_buttonSize[CHANGAN_MAIN_MENU_BKG][BUTTON_SIZE_WIDTH] = 90.0;
	m_buttonSize[CHANGAN_MAIN_MENU_BKG][BUTTON_SIZE_HEIGHT] = 76.0;
	m_buttonPos[CHANGAN_MAIN_MENU_BKG][BUTTON_POS_X] = window_width - m_buttonSize[CHANGAN_MAIN_MENU_BKG][BUTTON_SIZE_WIDTH];
	m_buttonPos[CHANGAN_MAIN_MENU_BKG][BUTTON_POS_Y] = window_height - m_buttonSize[CHANGAN_MAIN_MENU_BKG][BUTTON_SIZE_HEIGHT] - 10.0;

	m_buttonSize[CHANGAN_MAIN_MENU_ENTER_ICON][BUTTON_SIZE_WIDTH] = 32.0;
	m_buttonSize[CHANGAN_MAIN_MENU_ENTER_ICON][BUTTON_SIZE_HEIGHT] = 32.0;
	m_buttonPos[CHANGAN_MAIN_MENU_ENTER_ICON][BUTTON_POS_X] = window_width - m_buttonSize[CHANGAN_MAIN_MENU_ENTER_ICON][BUTTON_SIZE_WIDTH] - 5.0;
	m_buttonPos[CHANGAN_MAIN_MENU_ENTER_ICON][BUTTON_POS_Y] = m_buttonPos[CHANGAN_MAIN_MENU_BKG][BUTTON_POS_Y] + (m_buttonSize[CHANGAN_MAIN_MENU_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[CHANGAN_MAIN_MENU_ENTER_ICON][BUTTON_SIZE_HEIGHT]) * 0.5;

	m_buttonSize[CHANGAN_MAIN_MENU_EXIT_ICON][BUTTON_SIZE_WIDTH] = 32.0;
	m_buttonSize[CHANGAN_MAIN_MENU_EXIT_ICON][BUTTON_SIZE_HEIGHT] = 32.0;
	m_buttonPos[CHANGAN_MAIN_MENU_EXIT_ICON][BUTTON_POS_X] = m_buttonPos[CHANGAN_MAIN_MENU_BKG][BUTTON_POS_X] - 20.0;
	m_buttonPos[CHANGAN_MAIN_MENU_EXIT_ICON][BUTTON_POS_Y] = m_buttonPos[CHANGAN_MAIN_MENU_ENTER_ICON][BUTTON_POS_Y];

	m_buttonSize[CHANGAN_MAIN_DVR_START_ICON][BUTTON_SIZE_WIDTH] = 90.0;
	m_buttonSize[CHANGAN_MAIN_DVR_START_ICON][BUTTON_SIZE_HEIGHT] = 76.0;
	m_buttonPos[CHANGAN_MAIN_DVR_START_ICON][BUTTON_POS_X] = m_buttonPos[CHANGAN_MAIN_MENU_BKG][BUTTON_POS_X];
	m_buttonPos[CHANGAN_MAIN_DVR_START_ICON][BUTTON_POS_Y] = m_buttonPos[CHANGAN_MAIN_MENU_BKG][BUTTON_POS_Y];

	SetHmiParams();
	
	return CHANGAN_MAIN_HMI_NORMAL;
}
int CSVChangAnMainHmi::Update(Hmi_Message_T& hmiMsg)
{
	for(int i = CHANGAN_MAIN_MENU_BKG; i < CHANGAN_MAIN_ELEMENT_NUM; i++)
	{
		m_buttonVisibility[i] = hmiElementVisibility[i];	
	}

	m_cameraHmiVisibility = 1;
	
	if(m_cameraHmi)
	{
		m_cameraHmi->Update(hmiMsg);
	}

	RefreshHmi();

	return CHANGAN_MAIN_HMI_NORMAL;
}
 
int CSVChangAnMainHmi::RefreshHmi()
{

	for(int i = CHANGAN_MAIN_MENU_BKG; i < CHANGAN_MAIN_ELEMENT_NUM; i++)
	{
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}

	if(m_cameraHmi)
	{
		m_cameraHmi->SetElementsVisibility(m_cameraHmiVisibility);
	}
	return CHANGAN_MAIN_HMI_NORMAL;
}

int CSVChangAnMainHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{

	
	return CHANGAN_MAIN_HMI_NORMAL;
}
int CSVChangAnMainHmi::DestroyHmiElems()
{
	return CHANGAN_MAIN_HMI_NORMAL;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVChangAnMainHmi class.
\*===========================================================================*/
