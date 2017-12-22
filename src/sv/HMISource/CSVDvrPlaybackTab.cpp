#include "CSVDvrPlaybackTab.h"
#include "DVR_GUI_OBJ.h"

enum
{
	DVR_STATE_PLAY_NORMAL = 0,
	DVR_STATE_PLAY_HIGHLIGHT,	
	DVR_STATE_SUSPEND_NORMAL,
	DVR_STATE_SUSPEND_HIGHLIGHT,
	DVR_STATE_PLAYSPEED_X1_NORMAL = 0,
	DVR_STATE_PLAYSPEED_X1_HIGHLIGHT,
	DVR_STATE_PLAYSPEED_X1_5_NORMAL,
	DVR_STATE_PLAYSPEED_X1_5_HIGHLIGHT,	
	DVR_STATE_PLAYSPEED_X2_NORMAL,
	DVR_STATE_PLAYSPEED_X2_HIGHLIGHT,
	
};

class CPbPlayActionTrigger : public IActionTrigger
{

	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbPlayActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_PLAY;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbPlayActionTrigger: %d", sizeof(Ctrl_Cmd_T));
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

};
class CPbPreFileActionTrigger : public IActionTrigger
{

	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbPreFileActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_PREV;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbPreFileActionTrigger: %d", sizeof(Ctrl_Cmd_T));
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

};
class CPbNextFileActionTrigger : public IActionTrigger
{

	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbNextFileActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_NEXT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbNextFileActionTrigger: %d", sizeof(Ctrl_Cmd_T));
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

};

class CPbPlaySpeedActionTrigger : public IActionTrigger
{

	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbPlaySpeedActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		static int pressCnt = 0;
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_SPEED;
		m_dvrCmd->parameter[1] = pressCnt % GUI_PLAY_SPEED_X8;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbPlaySpeedActionTrigger: %d", sizeof(Ctrl_Cmd_T));
		pressCnt++;
		if(pressCnt > 1000)
		{
			pressCnt = 1;
		}
		
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

};


class CPbFrontViewActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbFrontViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_VIEW;
		m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_FRONT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbFrontViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CPbRearViewActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbRearViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_VIEW;
		m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_REAR;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbRearViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CPbLeftViewActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbLeftViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_VIEW;
		m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_LEFT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbLeftViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CPbRightViewActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbRightViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_VIEW;
		m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_RIGHT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbRightViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CPbEmergencySaveActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbEmergencySaveActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_SAVE;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbEmergencySaveActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CPbDeleteActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbDeleteActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_DELETE;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbDeleteActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CPbDcSwitchActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbDcSwitchActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_DC_SWITCH;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPbDcSwitchActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};


CSVDvrPlaybackTab::CSVDvrPlaybackTab(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	memset(m_trigger, NULL, DVR_PLAYBACK_TAB_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, DVR_PLAYBACK_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 1, DVR_PLAYBACK_TAB_ELEMEMT_NUM * sizeof(unsigned char));
}
	
int CSVDvrPlaybackTab::SetHmiParams()
{
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAYER_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAYER_BKG].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAYER_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAYER_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_PLAYER_BKG].icon_file_name[0],"%sCar/DVR/player_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_FILE_TITLE_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_FILE_TITLE_BKG].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_FILE_TITLE_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_FILE_TITLE_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_FILE_TITLE_BKG].icon_file_name[0],"%sCar/DVR/time_title_bkg.dds",XR_RES); 
	
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].show_icon_num =2;
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_file_name[1] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_file_name[2] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_file_name[3] = new char[100];

	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_file_name[0],"%sCar/DVR/player_play_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_file_name[1],"%sCar/DVR/player_play_highlight.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_file_name[2],"%sCar/DVR/player_suspend_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_PLAY].icon_file_name[3],"%sCar/DVR/player_suspend_hightlight.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_PLAY] = new CPbPlayActionTrigger;

	m_baseButtonData[DVR_PLAYBACK_TAB_FF].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_FF].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_FF].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_FF].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_FF].icon_file_name[1] = new char[100];

	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_FF].icon_file_name[0],"%sCar/DVR/player_ff_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_FF].icon_file_name[1],"%sCar/DVR/player_ff_press.dds",XR_RES); 
	

	m_baseButtonData[DVR_PLAYBACK_TAB_FB].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_FB].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_FB].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_FB].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_FB].icon_file_name[1] = new char[100];

	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_FB].icon_file_name[0],"%sCar/DVR/player_fb_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_FB].icon_file_name[1],"%sCar/DVR/player_fb_press.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_NEXT_PAGE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_NEXT_PAGE].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_NEXT_PAGE].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_NEXT_PAGE].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_NEXT_PAGE].icon_file_name[1] = new char[100];

	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_NEXT_PAGE].icon_file_name[0],"%sCar/DVR/player_np_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_NEXT_PAGE].icon_file_name[1],"%sCar/DVR/player_np_press.dds",XR_RES); 
	
	m_trigger[DVR_PLAYBACK_TAB_NEXT_PAGE] = new CPbNextFileActionTrigger;

	m_baseButtonData[DVR_PLAYBACK_TAB_PRE_PAGE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_PRE_PAGE].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_PRE_PAGE].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_PRE_PAGE].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_PRE_PAGE].icon_file_name[1] = new char[100];

	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_PRE_PAGE].icon_file_name[0],"%sCar/DVR/player_pp_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_PRE_PAGE].icon_file_name[1],"%sCar/DVR/player_pp_press.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_PRE_PAGE] = new CPbPreFileActionTrigger;
	

	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[1] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[2] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[3] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[4] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[5] = new char[100];

	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[0],"%sCar/DVR/player_speed_1_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[1],"%sCar/DVR/player_speed_1_highlight.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[2],"%sCar/DVR/player_speed_1.5_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[3],"%sCar/DVR/player_speed_1.5_hightlight.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[4],"%sCar/DVR/player_speed_2_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_SPEED].icon_file_name[5],"%sCar/DVR/player_speed_2_hightlight.dds",XR_RES); 
	
	m_trigger[DVR_PLAYBACK_TAB_SPEED] = new CPbPlaySpeedActionTrigger;

	m_baseButtonData[DVR_PLAYBACK_TAB_MENU_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_MENU_BKG].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_MENU_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_MENU_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_MENU_BKG].icon_file_name[0],"%sCar/DVR/record_tab_bkg.dds",XR_RES); 
	
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_TITLE].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_TITLE].icon_file_name[0],"%sCar/DVR/emergency_save_title.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_BKG].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_BKG].icon_file_name[0],"%sCar/DVR/emergency_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_ICON].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_ICON].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_ICON].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_ICON].icon_file_name[1] = new char[100];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_ICON].icon_file_name[0],"%sCar/DVR/emergency_save_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_EMERGENCY_ICON].icon_file_name[1],"%sCar/DVR/emergency_save_press.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_EMERGENCY_ICON] = new CPbEmergencySaveActionTrigger;

	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_TITLE].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_TITLE].icon_file_name[0],"%sCar/DVR/playback_delete_title.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_BKG].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_BKG].icon_file_name[0],"%sCar/DVR/emergency_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_ICON].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_ICON].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_ICON].icon_file_name[0],"%sCar/DVR/playback_delete_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_DELETE_ICON].icon_file_name[1],"%sCar/DVR/playback_delete_press.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_DELETE_ICON] = new CPbDeleteActionTrigger;
	

	m_baseButtonData[DVR_PLAYBACK_TAB_DC_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_DC_TITLE].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_DC_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_DC_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_DC_TITLE].icon_file_name[0],"%sCar/DVR/dc_title.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_DC_SWITCH].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_DC_SWITCH].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_DC_SWITCH].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_DC_SWITCH].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_PLAYBACK_TAB_DC_SWITCH].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_DC_SWITCH].icon_file_name[0],"%sCar/DVR/record_switch_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_DC_SWITCH].icon_file_name[1],"%sCar/DVR/record_switch_press.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_DC_SWITCH] = new CPbDcSwitchActionTrigger;

	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_TITLE].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_TITLE].icon_file_name[0],"%sCar/DVR/record_view_title.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_BKG].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_BKG].icon_file_name[0],"%sCar/DVR/record_view_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_FRONT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_FRONT].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_FRONT].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_FRONT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_FRONT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_FRONT].icon_file_name[0],"%sCar/DVR/record_view_front_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_FRONT].icon_file_name[1],"%sCar/DVR/record_view_front_highlight.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_VIEW_FRONT] = new CPbFrontViewActionTrigger;

	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_REAR].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_REAR].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_REAR].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_REAR].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_REAR].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_REAR].icon_file_name[0],"%sCar/DVR/record_view_rear_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_REAR].icon_file_name[1],"%sCar/DVR/record_view_rear_highlight.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_VIEW_REAR] = new CPbRearViewActionTrigger;

	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_LEFT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_LEFT].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_LEFT].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_LEFT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_LEFT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_LEFT].icon_file_name[0],"%sCar/DVR/record_view_left_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_LEFT].icon_file_name[1],"%sCar/DVR/record_view_left_highlight.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_VIEW_LEFT] = new CPbLeftViewActionTrigger;

	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_RIGHT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_RIGHT].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_RIGHT].show_icon_num = 0;
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_RIGHT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_RIGHT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_RIGHT].icon_file_name[0],"%sCar/DVR/record_view_right_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_TAB_VIEW_RIGHT].icon_file_name[1],"%sCar/DVR/record_view_right_highlight.dds",XR_RES); 
	m_trigger[DVR_PLAYBACK_TAB_VIEW_RIGHT] = new CPbRightViewActionTrigger;

	for(int i = DVR_PLAYBACK_TAB_PLAYER_BKG; i < DVR_PLAYBACK_TAB_ELEMEMT_NUM; i++)
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
int CSVDvrPlaybackTab::Init(int window_width, int window_height)
{
	float radio = 227.0/1280.0;
	float playerIconInterval = 10.0;

	m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH] = 683.0;
	m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] = 81.0;
	m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_X] = radio*window_width + ((1.0 - radio)*window_width - m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_Y] = window_height - 80.0 - m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT];

	m_buttonSize[DVR_PLAYBACK_TAB_FILE_TITLE_BKG][BUTTON_SIZE_WIDTH] = 683.0;
	m_buttonSize[DVR_PLAYBACK_TAB_FILE_TITLE_BKG][BUTTON_SIZE_HEIGHT] = 80.0;
	m_buttonPos[DVR_PLAYBACK_TAB_FILE_TITLE_BKG][BUTTON_POS_X] = radio*window_width + ((1.0 - radio)*window_width - m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_PLAYBACK_TAB_FILE_TITLE_BKG][BUTTON_POS_Y] = 80.0;
	
	m_buttonSize[DVR_PLAYBACK_TAB_PLAY][BUTTON_SIZE_WIDTH] = 56.0;
	m_buttonSize[DVR_PLAYBACK_TAB_PLAY][BUTTON_SIZE_HEIGHT] = 65.0;
	m_buttonPos[DVR_PLAYBACK_TAB_PLAY][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH] * 0.5 - m_buttonSize[DVR_PLAYBACK_TAB_PLAY][BUTTON_SIZE_WIDTH] * 0.5;
	m_buttonPos[DVR_PLAYBACK_TAB_PLAY][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_TAB_PLAY][BUTTON_SIZE_HEIGHT]) * 0.5;
		
	m_buttonSize[DVR_PLAYBACK_TAB_FF][BUTTON_SIZE_WIDTH] = 85.0;
	m_buttonSize[DVR_PLAYBACK_TAB_FF][BUTTON_SIZE_HEIGHT] = 64.0;
	m_buttonPos[DVR_PLAYBACK_TAB_FF][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_PLAY][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_PLAY][BUTTON_SIZE_WIDTH] + playerIconInterval;
	m_buttonPos[DVR_PLAYBACK_TAB_FF][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_TAB_FF][BUTTON_SIZE_HEIGHT]) * 0.5;

	m_buttonSize[DVR_PLAYBACK_TAB_FB][BUTTON_SIZE_WIDTH] = 85.0;
	m_buttonSize[DVR_PLAYBACK_TAB_FB][BUTTON_SIZE_HEIGHT] = 65.0;
	m_buttonPos[DVR_PLAYBACK_TAB_FB][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_PLAY][BUTTON_POS_X]- playerIconInterval - m_buttonSize[DVR_PLAYBACK_TAB_FB][BUTTON_SIZE_WIDTH] ;
	m_buttonPos[DVR_PLAYBACK_TAB_FB][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_TAB_FB][BUTTON_SIZE_HEIGHT]) * 0.5;

	m_buttonSize[DVR_PLAYBACK_TAB_NEXT_PAGE][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[DVR_PLAYBACK_TAB_NEXT_PAGE][BUTTON_SIZE_HEIGHT] = 66.0;
	m_buttonPos[DVR_PLAYBACK_TAB_NEXT_PAGE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_FF][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_FF][BUTTON_SIZE_WIDTH] + playerIconInterval;
	m_buttonPos[DVR_PLAYBACK_TAB_NEXT_PAGE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_TAB_NEXT_PAGE][BUTTON_SIZE_HEIGHT]) * 0.5;
		
	m_buttonSize[DVR_PLAYBACK_TAB_PRE_PAGE][BUTTON_SIZE_WIDTH] = 64.0;
	m_buttonSize[DVR_PLAYBACK_TAB_PRE_PAGE][BUTTON_SIZE_HEIGHT] = 66.0;
	m_buttonPos[DVR_PLAYBACK_TAB_PRE_PAGE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_FB][BUTTON_POS_X]- playerIconInterval - m_buttonSize[DVR_PLAYBACK_TAB_PRE_PAGE][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_PLAYBACK_TAB_PRE_PAGE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_TAB_PRE_PAGE][BUTTON_SIZE_HEIGHT]) * 0.5;
		
	m_buttonSize[DVR_PLAYBACK_TAB_SPEED][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_PLAYBACK_TAB_SPEED][BUTTON_SIZE_HEIGHT] = 39.0;
	m_buttonPos[DVR_PLAYBACK_TAB_SPEED][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH] - playerIconInterval;
	m_buttonPos[DVR_PLAYBACK_TAB_SPEED][BUTTON_POS_Y] =  m_buttonPos[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_TAB_SPEED][BUTTON_SIZE_HEIGHT]) * 0.5;

	m_buttonSize[DVR_PLAYBACK_TAB_MENU_BKG][BUTTON_SIZE_WIDTH] = 372.0;
	m_buttonSize[DVR_PLAYBACK_TAB_MENU_BKG][BUTTON_SIZE_HEIGHT] = 560.0;
	m_buttonPos[DVR_PLAYBACK_TAB_MENU_BKG][BUTTON_POS_X] = radio*window_width;
	m_buttonPos[DVR_PLAYBACK_TAB_MENU_BKG][BUTTON_POS_Y] = 80.0;

	m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_SIZE_WIDTH] = 113.0;
	m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_SIZE_HEIGHT] = 30.0;
	m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_MENU_BKG][BUTTON_POS_X] + 50.0;;
	m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_POS_Y] = 80.0 + 80.0;

	m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_BKG][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_BKG][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_SIZE_WIDTH] + 100.0;
	m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_ICON][BUTTON_SIZE_WIDTH] = m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_BKG][BUTTON_SIZE_WIDTH];
	m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_ICON][BUTTON_SIZE_HEIGHT] = m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_BKG][BUTTON_SIZE_HEIGHT];
	m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_ICON][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_BKG][BUTTON_POS_Y]; 

	m_buttonSize[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_SIZE_WIDTH] = 59.0;
	m_buttonSize[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_POS_Y]+ m_buttonSize[DVR_PLAYBACK_TAB_EMERGENCY_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_PLAYBACK_TAB_DELETE_BKG][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_PLAYBACK_TAB_DELETE_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_PLAYBACK_TAB_DELETE_BKG][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_SIZE_WIDTH] + 100.0;
	m_buttonPos[DVR_PLAYBACK_TAB_DELETE_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_PLAYBACK_TAB_DELETE_ICON][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_PLAYBACK_TAB_DELETE_ICON][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_PLAYBACK_TAB_DELETE_ICON][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_DELETE_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_PLAYBACK_TAB_DELETE_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_DELETE_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_PLAYBACK_TAB_DELETE_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_PLAYBACK_TAB_DC_SWITCH][BUTTON_SIZE_WIDTH] = 114.0;
	m_buttonSize[DVR_PLAYBACK_TAB_DC_SWITCH][BUTTON_SIZE_HEIGHT] = 47.0;
	m_buttonPos[DVR_PLAYBACK_TAB_DC_SWITCH][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_SIZE_WIDTH] + 35.0;
	m_buttonPos[DVR_PLAYBACK_TAB_DC_SWITCH][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_PLAYBACK_TAB_DC_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_BKG][BUTTON_SIZE_WIDTH] = 296.0;
	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_BKG][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_PLAYBACK_TAB_VIEW_TITLE][BUTTON_SIZE_HEIGHT] + 10.0;

	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_FRONT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_FRONT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_FRONT][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_FRONT][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_REAR][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_REAR][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_REAR][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_FRONT][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_VIEW_FRONT][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_REAR][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_FRONT][BUTTON_POS_Y];

	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_LEFT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_LEFT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_LEFT][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_REAR][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_VIEW_REAR][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_LEFT][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_REAR][BUTTON_POS_Y];

	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_RIGHT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_PLAYBACK_TAB_VIEW_RIGHT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_RIGHT][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_LEFT][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_TAB_VIEW_LEFT][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_PLAYBACK_TAB_VIEW_RIGHT][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_TAB_VIEW_LEFT][BUTTON_POS_Y];

	SetHmiParams();
	
	return HMI_SUCCESS;
}
int CSVDvrPlaybackTab::Update(Hmi_Message_T & hmiMsg)
{
	static int currentFileNum = 0;
	int 	   fileNumCnt = 0;
	
	DVR_GRAPHIC_UIOBJ* playbackTabMsg = NULL;
	GUI_OBJ_PLAY_FILENAME_INST* playbackFileName = NULL;


/*DVR_GRAPHIC_UIOBJ pb_video_gui_table[] =
{
	{ GUI_OBJ_ID_MAIN_MENU_TAB, "main_menu", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_MAIN_MENU_TAB_THUMB },
	{ GUI_OBJ_ID_PB_PLAY_STATE, "play_state", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_PLAY_STATE_INVALID },
	{ GUI_OBJ_ID_PB_PLAY_TIMER, "play_timer", 1, 1, GUI_OBJ_STATUS_TYPE_ADDRESS, (unsigned int)&m_play_time },
	{ GUI_OBJ_ID_PB_PLAY_SPEED, "play_speed", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_PLAY_SPEED_X1 },
	{ GUI_OBJ_ID_PB_FILENAME, "play_file_name", 1, 1, GUI_OBJ_STATUS_TYPE_ADDRESS, (unsigned int)&m_play_filename },
	{ GUI_OBJ_ID_PB_VIEW_INDEX, "play_view", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_VIEW_INDEX_FRONT },
	{ GUI_OBJ_ID_PB_DC_SWITCH, "play_dc_switch", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_SWITCH_STATE_OFF },
	{ GUI_OBJ_ID_DIALOG, "dialog", 1, 0, GUI_OBJ_STATUS_TYPE_ADDRESS, (unsigned int)&m_dialog }

	
};*/

	if((DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable)
	{
		playbackTabMsg = (DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable;
		
		for(int i = 0; i < hmiMsg.dvrTabMsg.objNum; i++)
		{			
			switch(playbackTabMsg[i].Id)
			{
			case GUI_OBJ_ID_PB_PLAY_STATE:

				if(GUI_OBJ_STATUS_TYPE_VALUE == playbackTabMsg[i].status_type)
				{
					
					if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_RUNNING)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_PLAY] = DVR_STATE_SUSPEND_NORMAL;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_PAUSE)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_PLAY] = DVR_STATE_PLAY_NORMAL;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_FAST_FORWARD)
					{
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_FAST_BACKWARD)
					{
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_INVALID)
					{
					}
				}
				break;
			case GUI_OBJ_ID_PB_PLAY_SPEED:
				
				if(GUI_OBJ_STATUS_TYPE_VALUE == playbackTabMsg[i].status_type)
				{
					
					if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_SPEED_X1)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_SPEED] = DVR_STATE_PLAYSPEED_X1_NORMAL;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_SPEED_X2)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_SPEED] = DVR_STATE_PLAYSPEED_X1_5_NORMAL;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_SPEED_X4)
					{					
						m_buttonStatus[DVR_PLAYBACK_TAB_SPEED] = DVR_STATE_PLAYSPEED_X2_NORMAL;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_SPEED_X8)
					{
					}
					
				}
				
				break;
			case GUI_OBJ_ID_PB_VIEW_INDEX:
							
				if(GUI_OBJ_STATUS_TYPE_VALUE == playbackTabMsg[i].status_type)
				{
					
					if(playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_FRONT)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_VIEW_FRONT] = BUTTON_ON_IMAGE;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_FRONT)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_VIEW_REAR] = BUTTON_ON_IMAGE;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_FRONT)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_VIEW_LEFT] = BUTTON_ON_IMAGE;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_FRONT)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_VIEW_RIGHT] = BUTTON_ON_IMAGE;
					}
					
				}
				
				break;

			case GUI_OBJ_ID_PB_FILENAME:
								
				if(GUI_OBJ_STATUS_TYPE_ADDRESS == playbackTabMsg[i].status_type
					&& playbackTabMsg[i].uStatus.ptr)
				{
					playbackFileName = (GUI_OBJ_PLAY_FILENAME_INST*)playbackTabMsg[i].uStatus.ptr;

					
				}
				
				break;
			case  GUI_OBJ_ID_PB_DC_SWITCH:
				if(GUI_OBJ_STATUS_TYPE_VALUE == playbackTabMsg[i].status_type)
				{
					
					if(playbackTabMsg[i].uStatus.ObjVal == GUI_SWITCH_STATE_ON)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_DC_SWITCH] = BUTTON_ON_IMAGE;
					}
					else if(playbackTabMsg[i].uStatus.ObjVal == GUI_SWITCH_STATE_OFF)
					{
						m_buttonStatus[DVR_PLAYBACK_TAB_DC_SWITCH] = BUTTON_OFF_IMAGE;
					}
					
				}
				
				
				break;

				
			default:
				break;
			}	
		}

	}
	
	RefreshHmi();
	
	return HMI_SUCCESS;
}
int CSVDvrPlaybackTab::RefreshHmi()
{
	for(int i = DVR_PLAYBACK_TAB_PLAYER_BKG; i < DVR_PLAYBACK_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
	return HMI_SUCCESS;
}
int CSVDvrPlaybackTab::SetElementsVisibility(unsigned char pFlag)
{
	memset(m_buttonVisibility, pFlag, DVR_PLAYBACK_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	for(int i = DVR_PLAYBACK_TAB_PLAYER_BKG; i < DVR_PLAYBACK_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetVisibility(pFlag);
	}

	return HMI_SUCCESS;
}
int CSVDvrPlaybackTab::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVDvrPlaybackTab::DestroyHmiElems()
{
	return HMI_SUCCESS;
}

