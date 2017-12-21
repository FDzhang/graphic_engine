#include "CSVDvrBaseHmi.h"
#include "CSVDvrSettingTab.h"
#include "CSVDvrRecordTab.h"
#include "CSVDvrPlaybackTab.h"
#include "CSVDvrFileListTab.h"

#include "DVR_GUI_OBJ.h"
#include "gpu_log.h"

	
class CLiveVideoTabActionTrigger : public IActionTrigger
{

	ACTION_TRIGGER_EVENT_CONSTRUCTION(CLiveVideoTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_MAIN_MENU;
		m_dvrCmd->parameter[1] = GUI_MAIN_MENU_TAB_RECORD;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CLiveVideoTabActionTrigger: %d", sizeof(Ctrl_Cmd_T));
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

};

class CFileTabActionTrigger : public IActionTrigger
{

	ACTION_TRIGGER_EVENT_CONSTRUCTION(CFileTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:		
	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_MAIN_MENU;
		m_dvrCmd->parameter[1] = GUI_MAIN_MENU_TAB_THUMB;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CFileTabActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

};
;
class CSettingTabActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CSettingTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_MAIN_MENU;
		m_dvrCmd->parameter[1] = GUI_MAIN_MENU_TAB_SETUP;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CSettingTabActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

};

class CReturnDvrActionTrigger:public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CReturnDvrActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_QUIT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CReturnDvrActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

};

CSVDvrBaseHmi::CSVDvrBaseHmi()
{
	memset(m_trigger, NULL, DVR_BASE_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, DVR_BASE_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 1, DVR_BASE_ELEMEMT_NUM * sizeof(unsigned char));

	m_dvrSettingTab = NULL;
	m_dvrRecordTab = NULL;
	m_dvrPlaybackTab = NULL;
	m_dvrFileListTab = NULL;

	m_dvrSettingTab = new CSVDvrSettingTab(m_uiNode, m_uiNodeId);
	m_dvrRecordTab = new CSVDvrRecordTab(m_uiNode, m_uiNodeId);
	m_dvrPlaybackTab = new CSVDvrPlaybackTab(m_uiNode, m_uiNodeId);
	m_dvrFileListTab = new CSVDvrFileListTab(m_uiNode, m_uiNodeId);

	m_dvrSettingTabVisibility = 0;
	m_dvrRecordTabVisibility = 0;
	m_dvrPlaybackTabVisibility = 0;
	m_dvrFileListVisibility = 0;
	
}
	
int CSVDvrBaseHmi::SetHmiParams()
{
	m_baseButtonData[DVR_BASE_TITLE_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_BASE_TITLE_BKG].show_flag = 1;
	m_baseButtonData[DVR_BASE_TITLE_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_BASE_TITLE_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_BASE_TITLE_BKG].icon_file_name[0],"%sCar/DVR/title_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_BASE_TAB_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_BASE_TAB_BKG].show_flag = 1;
	m_baseButtonData[DVR_BASE_TAB_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_BASE_TAB_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_BASE_TAB_BKG].icon_file_name[0],"%sCar/DVR/base_tab_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_BASE_TITLE_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_BASE_TITLE_ICON].show_flag = 1;
	m_baseButtonData[DVR_BASE_TITLE_ICON].show_icon_num = 0;
	m_baseButtonData[DVR_BASE_TITLE_ICON].icon_file_name[0] = new char[50];	
	m_baseButtonData[DVR_BASE_TITLE_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_BASE_TITLE_ICON].icon_file_name[0],"%sCar/DVR/dvr_title.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_BASE_TITLE_ICON].icon_file_name[1],"%sCar/DVR/playback_return.dds",XR_RES); 
	m_trigger[DVR_BASE_TITLE_ICON] = new CReturnDvrActionTrigger;

	m_baseButtonData[DVR_BASE_LIVE_VIDEO_TAB].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_BASE_LIVE_VIDEO_TAB].show_flag = 1;
	m_baseButtonData[DVR_BASE_LIVE_VIDEO_TAB].show_icon_num = 0;
	m_baseButtonData[DVR_BASE_LIVE_VIDEO_TAB].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_BASE_LIVE_VIDEO_TAB].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_BASE_LIVE_VIDEO_TAB].icon_file_name[0],"%sCar/DVR/live_video_tab_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_BASE_LIVE_VIDEO_TAB].icon_file_name[1],"%sCar/DVR/live_video_tab_press.dds",XR_RES); 
	m_trigger[DVR_BASE_LIVE_VIDEO_TAB] = new CLiveVideoTabActionTrigger;


	m_baseButtonData[DVR_BASE_FILE_TAB].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_BASE_FILE_TAB].show_flag = 1;
	m_baseButtonData[DVR_BASE_FILE_TAB].show_icon_num = 0;
	m_baseButtonData[DVR_BASE_FILE_TAB].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_BASE_FILE_TAB].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_BASE_FILE_TAB].icon_file_name[0],"%sCar/DVR/file_tab_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_BASE_FILE_TAB].icon_file_name[1],"%sCar/DVR/file_tab_press.dds",XR_RES); 
	m_trigger[DVR_BASE_FILE_TAB] = new CFileTabActionTrigger;


	m_baseButtonData[DVR_BASE_SETTING_TAB].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_BASE_SETTING_TAB].show_flag = 1;
	m_baseButtonData[DVR_BASE_SETTING_TAB].show_icon_num = 0;
	m_baseButtonData[DVR_BASE_SETTING_TAB].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_BASE_SETTING_TAB].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_BASE_SETTING_TAB].icon_file_name[0],"%sCar/DVR/setting_tab_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_BASE_SETTING_TAB].icon_file_name[1],"%sCar/DVR/setting_tab_press.dds",XR_RES); 
	m_trigger[DVR_BASE_SETTING_TAB] = new CSettingTabActionTrigger;


	for(int i = DVR_BASE_TITLE_BKG; i < DVR_BASE_ELEMEMT_NUM; i++)
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

	m_dvrSettingTab->Init(m_windowWidth, m_windowHeight);

	m_dvrRecordTab->Init(m_windowWidth, m_windowHeight);

	m_dvrPlaybackTab->Init(m_windowWidth, m_windowHeight);

	m_dvrFileListTab->Init(m_windowWidth, m_windowHeight);
	
	return HMI_SUCCESS;
}
int CSVDvrBaseHmi::Init(int window_width, int window_height)
{
	m_windowWidth = window_width;
	m_windowHeight = window_height;

	float radio = 227.0/1280.0;

	m_buttonPos[DVR_BASE_TITLE_BKG][BUTTON_POS_X] = 0.0;
	m_buttonPos[DVR_BASE_TITLE_BKG][BUTTON_POS_Y] = 80.0;
	m_buttonSize[DVR_BASE_TITLE_BKG][BUTTON_SIZE_WIDTH] = radio*window_width;
	m_buttonSize[DVR_BASE_TITLE_BKG][BUTTON_SIZE_HEIGHT] = window_height - 160.0;
		
	m_buttonPos[DVR_BASE_TAB_BKG][BUTTON_POS_X] = radio*window_width;
	m_buttonPos[DVR_BASE_TAB_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_BASE_TITLE_BKG][BUTTON_POS_Y];
	m_buttonSize[DVR_BASE_TAB_BKG][BUTTON_SIZE_WIDTH] = (1.0 - radio) * window_width;
	m_buttonSize[DVR_BASE_TAB_BKG][BUTTON_SIZE_HEIGHT] = window_height - 160.0;

	m_buttonSize[DVR_BASE_TITLE_ICON][BUTTON_SIZE_WIDTH] = 142.0;
	m_buttonSize[DVR_BASE_TITLE_ICON][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_BASE_TITLE_ICON][BUTTON_POS_X] = (m_buttonSize[DVR_BASE_TITLE_BKG][BUTTON_SIZE_WIDTH] - m_buttonSize[DVR_BASE_TITLE_ICON][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_BASE_TITLE_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_BASE_TITLE_BKG][BUTTON_POS_Y] + 12.0;

	m_buttonSize[DVR_BASE_LIVE_VIDEO_TAB][BUTTON_SIZE_WIDTH] = 225.0;
	m_buttonSize[DVR_BASE_LIVE_VIDEO_TAB][BUTTON_SIZE_HEIGHT] = 105.0;
	m_buttonPos[DVR_BASE_LIVE_VIDEO_TAB][BUTTON_POS_X] = (m_buttonSize[DVR_BASE_TITLE_BKG][BUTTON_SIZE_WIDTH] - m_buttonSize[DVR_BASE_LIVE_VIDEO_TAB][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_BASE_LIVE_VIDEO_TAB][BUTTON_POS_Y] = m_buttonPos[DVR_BASE_TITLE_ICON][BUTTON_POS_Y] + 40.0;

	m_buttonSize[DVR_BASE_FILE_TAB][BUTTON_SIZE_WIDTH] = 225.0;
	m_buttonSize[DVR_BASE_FILE_TAB][BUTTON_SIZE_HEIGHT] = 105.0;
	m_buttonPos[DVR_BASE_FILE_TAB][BUTTON_POS_X] = (m_buttonSize[DVR_BASE_TITLE_BKG][BUTTON_SIZE_WIDTH] - m_buttonSize[DVR_BASE_FILE_TAB][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_BASE_FILE_TAB][BUTTON_POS_Y] = m_buttonPos[DVR_BASE_LIVE_VIDEO_TAB][BUTTON_POS_Y] + m_buttonSize[DVR_BASE_LIVE_VIDEO_TAB][BUTTON_SIZE_HEIGHT] - 30.0;

	m_buttonSize[DVR_BASE_SETTING_TAB][BUTTON_SIZE_WIDTH] = 225.0;
	m_buttonSize[DVR_BASE_SETTING_TAB][BUTTON_SIZE_HEIGHT] = 105.0;
	m_buttonPos[DVR_BASE_SETTING_TAB][BUTTON_POS_X] = (m_buttonSize[DVR_BASE_TITLE_BKG][BUTTON_SIZE_WIDTH] - m_buttonSize[DVR_BASE_SETTING_TAB][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_BASE_SETTING_TAB][BUTTON_POS_Y] = m_buttonPos[DVR_BASE_FILE_TAB][BUTTON_POS_Y] + m_buttonSize[DVR_BASE_FILE_TAB][BUTTON_SIZE_HEIGHT] - 30.0;

	SetHmiParams();
	
	return HMI_SUCCESS;
}
int CSVDvrBaseHmi::Update(Hmi_Message_T& hmiMsg)
{
	static int cnt_dvr_alive = 0;


	if(cnt_dvr_alive > 300)
	{
	static DVR_GUI_LAYOUT_INST dvrGuiLayout;
	m_buttonVisibility[DVR_BASE_TAB_BKG] = 1;			
	m_buttonStatus[DVR_BASE_TITLE_ICON] = 0;

	if(0 == Dvr_App_Get_GuiLayOut(&dvrGuiLayout))
	{
		switch(dvrGuiLayout.curLayout)
		{
		case GUI_LAYOUT_SETUP:
			m_buttonStatus[DVR_BASE_SETTING_TAB] = BUTTON_ON_IMAGE;
			m_buttonStatus[DVR_BASE_FILE_TAB] = BUTTON_OFF_IMAGE;
			m_buttonStatus[DVR_BASE_LIVE_VIDEO_TAB] = BUTTON_OFF_IMAGE;

			if(dvrGuiLayout.pTable)
			{
			
				Log_Error("-------------GUI_LAYOUT_SETUP------------");
				for(int i = 0; i < dvrGuiLayout.ObjNum; i++)
				{
					Log_Error("dvrGuiLayout[%d].Id: %d", i, dvrGuiLayout.pTable[i].Id);
					Log_Error("dvrGuiLayout.pTable[%d].ObjVal: %d", i, dvrGuiLayout.pTable[i].uStatus.ObjVal);
					
				}
				
				m_hmiMsg.dvrTabMsg.tabMsgTable = (void *)dvrGuiLayout.pTable;
				m_hmiMsg.dvrTabMsg.objNum = dvrGuiLayout.ObjNum;
				m_dvrSettingTab->Update(m_hmiMsg);
			}
			m_dvrSettingTabVisibility = 1;
			m_dvrRecordTabVisibility = 0;
			m_dvrPlaybackTabVisibility = 0;
			m_dvrFileListVisibility = 0;
			break;
		case GUI_LAYOUT_RECORD:
			m_buttonStatus[DVR_BASE_SETTING_TAB] = BUTTON_OFF_IMAGE;
			m_buttonStatus[DVR_BASE_FILE_TAB] = BUTTON_OFF_IMAGE;
			m_buttonStatus[DVR_BASE_LIVE_VIDEO_TAB] = BUTTON_ON_IMAGE;

			if(dvrGuiLayout.pTable)
			{
				Log_Error("-------------GUI_LAYOUT_RECORD------------");
			
				for(int i = 0; i < dvrGuiLayout.ObjNum; i++)
				{
					Log_Error("dvrGuiLayout[%d].Id: %d", i, dvrGuiLayout.pTable[i].Id);
					Log_Error("dvrGuiLayout.pTable[%d].ObjVal: %d", i, dvrGuiLayout.pTable[i].uStatus.ObjVal);
				}
				
				m_hmiMsg.dvrTabMsg.tabMsgTable = (void *)dvrGuiLayout.pTable;
				m_hmiMsg.dvrTabMsg.objNum = dvrGuiLayout.ObjNum;
				m_dvrRecordTab->Update(m_hmiMsg);
			}
			
			m_buttonVisibility[DVR_BASE_TAB_BKG] = 0;
			m_dvrSettingTabVisibility = 0;
			m_dvrRecordTabVisibility = 1;
			m_dvrPlaybackTabVisibility = 0;
			m_dvrFileListVisibility = 0;

			break;
		case GUI_LAYOUT_THUMB:
			m_buttonStatus[DVR_BASE_SETTING_TAB] = BUTTON_OFF_IMAGE;
			m_buttonStatus[DVR_BASE_FILE_TAB] = BUTTON_ON_IMAGE;
			m_buttonStatus[DVR_BASE_LIVE_VIDEO_TAB] = BUTTON_OFF_IMAGE;
			if(dvrGuiLayout.pTable)
			{
				Log_Error("-------------GUI_LAYOUT_THUMB------------");
			
				for(int i = 0; i < dvrGuiLayout.ObjNum; i++)
				{
					Log_Error("dvrGuiLayout[%d].Id: %d", i, dvrGuiLayout.pTable[i].Id);
					Log_Error("dvrGuiLayout.pTable[%d].ObjVal: %d", i, dvrGuiLayout.pTable[i].uStatus.ObjVal);
				}
				
				m_hmiMsg.dvrTabMsg.tabMsgTable = (void *)dvrGuiLayout.pTable;
				m_hmiMsg.dvrTabMsg.objNum = dvrGuiLayout.ObjNum;
				m_dvrFileListTab->Update(m_hmiMsg);
			}
			
			m_dvrSettingTabVisibility = 0;
			m_dvrRecordTabVisibility = 0;
			m_dvrPlaybackTabVisibility = 0;
			m_dvrFileListVisibility = 1;
			break;
		case GUI_LAYOUT_PLAYBACK_VIDEO:	

			if(dvrGuiLayout.pTable)
			{
				Log_Error("-------------GUI_LAYOUT_PLAYBACK_VIDEO------------");
			
				for(int i = 0; i < dvrGuiLayout.ObjNum; i++)
				{
					Log_Error("dvrGuiLayout[%d].Id: %d", i, dvrGuiLayout.pTable[i].Id);
					Log_Error("dvrGuiLayout.pTable[%d].ObjVal: %d", i, dvrGuiLayout.pTable[i].uStatus.ObjVal);
				}
				
				m_hmiMsg.dvrTabMsg.tabMsgTable = (void *)dvrGuiLayout.pTable;
				m_hmiMsg.dvrTabMsg.objNum = dvrGuiLayout.ObjNum;
				m_dvrPlaybackTab->Update(m_hmiMsg);
			}

			m_buttonVisibility[DVR_BASE_TAB_BKG] = 0;	
			m_buttonStatus[DVR_BASE_TITLE_ICON] = 1;
			m_dvrSettingTabVisibility = 0;
			m_dvrRecordTabVisibility = 0;
			m_dvrPlaybackTabVisibility = 1;
			m_dvrFileListVisibility = 0;
			
			break;
		default:
			m_dvrSettingTabVisibility = 0;
			m_dvrRecordTabVisibility = 0;
			m_dvrPlaybackTabVisibility = 0;
			m_dvrFileListVisibility = 0;
			break;
		}
	}
	}
	
	RefreshHmi();
	
	if(cnt_dvr_alive > 300)
	{
		cnt_dvr_alive = 301;
	}
	else
	{
		//Log_Message("---------Wait Dvr Init!");
	}
	cnt_dvr_alive++;

	return HMI_SUCCESS;
}
int CSVDvrBaseHmi::SetDvrStatus(unsigned char pDvrStatus)
{
	m_dvrStatus = pDvrStatus;
	return HMI_SUCCESS;
}

int CSVDvrBaseHmi::RefreshHmi()
{
	for(int i = DVR_BASE_TITLE_BKG; i < DVR_BASE_ELEMEMT_NUM; i++)

	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}

	Hmi_Message_T  hmiMsg;	

	if(m_dvrSettingTab)
	{
		m_dvrSettingTab->SetElementsVisibility(m_dvrSettingTabVisibility);	
	}

	if(m_dvrRecordTab)
	{
	
		m_dvrRecordTab->SetElementsVisibility(m_dvrRecordTabVisibility);
	}
	
	if(m_dvrPlaybackTab)
	{
	
		m_dvrPlaybackTab->SetElementsVisibility(m_dvrPlaybackTabVisibility);
	}

	if(m_dvrFileListTab)
	{
	
		m_dvrFileListTab->SetElementsVisibility(m_dvrFileListVisibility);
	}
		
	return HMI_SUCCESS;
}

int CSVDvrBaseHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVDvrBaseHmi::DestroyHmiElems()
{
	return HMI_SUCCESS;
}