#include "CSVDvrSettingTab.h"
#include "DVR_GUI_OBJ.h"
#include "gpu_log.h"

class CTimeFirstSelectorActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CTimeFirstSelectorActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_SETUP_LOOPENC_SPLIT_TIME;
		m_dvrCmd->parameter[1] = GUI_SETUP_SPLIT_TIME_1MIN;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CTimeSelectorFirstActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CTimeSecondSelectorActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CTimeSecondSelectorActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_SETUP_LOOPENC_SPLIT_TIME;
		m_dvrCmd->parameter[1] = GUI_SETUP_SPLIT_TIME_3MIN;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CTimeSecondSelectorActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CTimeThirdSelectorActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CTimeThirdSelectorActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_SETUP_LOOPENC_SPLIT_TIME;
		m_dvrCmd->parameter[1] = GUI_SETUP_SPLIT_TIME_5MIN;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CTimeThirdSelectorActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CSdFormatActionTrigger  : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CSdFormatActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_SETUP_FORMAT_CARD;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CSdFormatActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};
	
CSVDvrSettingTab::CSVDvrSettingTab(IUINode* pUiNode = NULL, int pUiNodeId = -1): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	memset(m_trigger, NULL, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 1, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(unsigned char));
}
	
int CSVDvrSettingTab::SetHmiParams()
{

	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].icon_file_name[0],"%sCar/DVR/record_time_setting.dds",XR_RES); 

	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].icon_file_name[0],"%sCar/DVR/record_time_setting_bkg.dds",XR_RES);

		
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_file_name[0],"%sCar/DVR/time_setting_first.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_file_name[1],"%sCar/DVR/time_setting_first_press.dds",XR_RES);
	m_trigger[DVR_SETTING_TAB_TIME_SETTING_FIRST] = new CTimeFirstSelectorActionTrigger;
	
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_file_name[0],"%sCar/DVR/time_setting_second.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_file_name[1],"%sCar/DVR/time_setting_second_press.dds",XR_RES);
	m_trigger[DVR_SETTING_TAB_TIME_SETTING_SECOND] = new CTimeSecondSelectorActionTrigger;
		
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].show_icon_num = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_file_name[0],"%sCar/DVR/time_setting_third.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_file_name[1],"%sCar/DVR/time_setting_third_press.dds",XR_RES);
	m_trigger[DVR_SETTING_TAB_TIME_SETTING_THIRD] = new CTimeThirdSelectorActionTrigger;

	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].icon_file_name[0],"%sCar/DVR/sd_format_title.dds",XR_RES);

	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[0],"%sCar/DVR/sd_format_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[1],"%sCar/DVR/sd_format_press.dds",XR_RES);	
	m_trigger[DVR_SETTING_TAB_SD_FORMAT_NORMAL] = new CSdFormatActionTrigger;


	for(int i = DVR_SETTING_TAB_TIME_SETTING; i < DVR_SETTING_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
		m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
		m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
		m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
		m_baseButtonData[i].delegate_func = NULL;
		m_baseButtonData[i].trigger = m_trigger[i];

		m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
		m_baseButton[i]->SetVisibility(1);
	}
	return true;
}
int CSVDvrSettingTab::Init(int window_width, int window_height)
{
	float radio = 227.0/1280.0;

	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING][BUTTON_SIZE_WIDTH] = 173.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_X] = radio*window_width + 50.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_Y] = 80.0 + 50.0;

	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_SIZE_WIDTH] = 428.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_X];
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_Y] + m_buttonSize[DVR_SETTING_TAB_TIME_SETTING][BUTTON_SIZE_HEIGHT] + 6.0;

		
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_SIZE_WIDTH] = 143.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y];
		
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_SIZE_WIDTH] = 143.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_POS_X] + m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y];
		
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_THIRD][BUTTON_SIZE_WIDTH] = 143.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_THIRD][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_THIRD][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_POS_X] + m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_THIRD][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_SIZE_WIDTH] = 174.0;
	m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_X];
	m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y] + m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_SIZE_WIDTH] + 120.0;
	m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_POS_Y] - m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_SIZE_HEIGHT] * 0.33;
	
	SetHmiParams();
	
	return HMI_SUCCESS;
}
int CSVDvrSettingTab::Update(Hmi_Message_T& hmiMsg)
{
	DVR_GRAPHIC_UIOBJ* settigTabMsg = NULL;
	
	/*DVR_GRAPHIC_UIOBJ setup_gui_table[] =
	{
		{ GUI_OBJ_ID_MAIN_MENU_TAB, "main_menu", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_MAIN_MENU_TAB_SETUP },
		{ GUI_OBJ_ID_SETUP_SPLIT_TIME, "split_time", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_SETUP_SPLIT_TIME_1MIN },
		{ GUI_OBJ_ID_SETUP_VIDEO_QUALITY, "video_quality", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_SETUP_VIDEO_QUALITY_SFINE },
		{ GUI_OBJ_ID_SETUP_PHOTO_QUALITY, "photo_quality", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_SETUP_PHOTO_QUALITY_SFINE },
		{ GUI_OBJ_ID_SETUP_FORMAT_CARD, "format_card", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, 0 },
		{ GUI_OBJ_ID_DIALOG, "dialog", 1, 0, GUI_OBJ_STATUS_TYPE_ADDRESS, (unsigned int)&m_dialog },
		{ GUI_OBJ_ID_WARNING, "warning", 1, 0, GUI_OBJ_STATUS_TYPE_VALUE, GUI_WARNING_NONE }
	};*/
		
	if((DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable)
	{
		settigTabMsg = (DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable;
		for(int i = 0; i < hmiMsg.dvrTabMsg.objNum; i++)
		{			
			switch(settigTabMsg[i].Id)
			{
			case GUI_OBJ_ID_SETUP_SPLIT_TIME:
				m_buttonStatus[DVR_SETTING_TAB_TIME_SETTING_FIRST] = 0;
				m_buttonStatus[DVR_SETTING_TAB_TIME_SETTING_SECOND] = 0;
				m_buttonStatus[DVR_SETTING_TAB_TIME_SETTING_THIRD] = 0;
				if(settigTabMsg[i].uStatus.ObjVal == GUI_SETUP_SPLIT_TIME_1MIN)
				{
					m_buttonStatus[DVR_SETTING_TAB_TIME_SETTING_FIRST] = BUTTON_ON_IMAGE;
				}
				else if(settigTabMsg[i].uStatus.ObjVal == GUI_SETUP_SPLIT_TIME_3MIN)
				{
					m_buttonStatus[DVR_SETTING_TAB_TIME_SETTING_SECOND] = BUTTON_ON_IMAGE;
				}
				else if(settigTabMsg[i].uStatus.ObjVal == GUI_SETUP_SPLIT_TIME_5MIN)
				{
					m_buttonStatus[DVR_SETTING_TAB_TIME_SETTING_THIRD] = BUTTON_ON_IMAGE;
				}
				break;
			case GUI_OBJ_ID_SETUP_FORMAT_CARD:
				m_buttonStatus[DVR_SETTING_TAB_SD_FORMAT_NORMAL] = 0;
				break;
			default:
				break;
			}	
		}

	}
	
	RefreshHmi();

	return HMI_SUCCESS;
}
int CSVDvrSettingTab::RefreshHmi()
{
	for(int i = DVR_SETTING_TAB_TIME_SETTING; i < DVR_SETTING_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
	return HMI_SUCCESS;
}
int CSVDvrSettingTab::SetElementsVisibility(unsigned char pFlag)
{

	memset(m_buttonVisibility, pFlag, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	for(int i = DVR_SETTING_TAB_TIME_SETTING; i < DVR_SETTING_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetVisibility(pFlag);
	}

	return HMI_SUCCESS;
}

int CSVDvrSettingTab::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVDvrSettingTab::DestroyHmiElems()
{
	return HMI_SUCCESS;
}
