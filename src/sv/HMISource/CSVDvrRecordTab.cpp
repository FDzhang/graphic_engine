#include "CSVDvrRecordTab.h"
#include "DVR_GUI_OBJ.h"


class CRecordSwitchActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CRecordSwitchActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_RECORD_SWITCH;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CRecordSwitchActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CCaptureActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CCaptureActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{

	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_PHOTO_SHUTTER;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));

		Log_Message("-----------CCaptureActionTrigger: %d", sizeof(Ctrl_Cmd_T));

	}
};

class CEventRecordActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEventRecordActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_EVENT_RECORD;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CEventRecordActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CRecordFrontViewActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CRecordFrontViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_LIVE_VIEW;
		m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_FRONT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CRecordFrontViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CRecordRearViewActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CRecordRearViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_LIVE_VIEW;
		m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_REAR;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CRecordRearViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CRecordLeftViewActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CRecordLeftViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_LIVE_VIEW;
		m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_LEFT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CRecordLeftViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};

class CRecordRightViewActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CRecordRightViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_LIVE_VIEW;
		m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_RIGHT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CRecordRightViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
};


CSVDvrRecordTab::CSVDvrRecordTab(IUINode* pUiNode = NULL, int pUiNodeId = -1): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	memset(m_trigger, NULL, DVR_RECORD_TAB_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, DVR_RECORD_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 0, DVR_RECORD_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	
}
	
int CSVDvrRecordTab::SetHmiParams()
{

	m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].icon_file_name[0],"%sCar/DVR/record_tab_bkg.dds",XR_RES); 
	
	m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].icon_file_name[0],"%sCar/DVR/record_title.dds",XR_RES); 
		
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_file_name[0],"%sCar/DVR/record_switch_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_file_name[1],"%sCar/DVR/record_switch_press.dds",XR_RES); 
	m_trigger[DVR_RECORD_TAB_RECORD_SWITCH] = new CRecordSwitchActionTrigger;

	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].icon_file_name[0],"%sCar/DVR/capture_title.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].icon_file_name[0],"%sCar/DVR/capture_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_file_name[0],"%sCar/DVR/capture_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_file_name[1],"%sCar/DVR/capture_hightlight.dds",XR_RES); 
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_trigger[DVR_RECORD_TAB_CAPTURE_ICON] = new CCaptureActionTrigger;

	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].icon_file_name[0],"%sCar/DVR/emergency_title.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].icon_file_name[0],"%sCar/DVR/emergency_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_file_name[0],"%sCar/DVR/emergency_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_file_name[1],"%sCar/DVR/emergency_highlight.dds",XR_RES); 
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_trigger[DVR_RECORD_TAB_EMERGENCY_ICON] = new CEventRecordActionTrigger;

	m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].icon_file_name[0],"%sCar/DVR/record_view_title.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].icon_file_name[0],"%sCar/DVR/record_view_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_file_name[0],"%sCar/DVR/record_view_front_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_file_name[1],"%sCar/DVR/record_view_front_highlight.dds",XR_RES); 
	m_trigger[DVR_RECORD_TAB_VIEW_FRONT] = new CRecordFrontViewActionTrigger;

	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_file_name[0],"%sCar/DVR/record_view_rear_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_file_name[1],"%sCar/DVR/record_view_rear_highlight.dds",XR_RES); 
	m_trigger[DVR_RECORD_TAB_VIEW_REAR] = new CRecordRearViewActionTrigger;

	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_file_name[0],"%sCar/DVR/record_view_left_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_file_name[1],"%sCar/DVR/record_view_left_highlight.dds",XR_RES); 
	m_trigger[DVR_RECORD_TAB_VIEW_LEFT] = new CRecordLeftViewActionTrigger;

	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_file_name[0],"%sCar/DVR/record_view_right_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_file_name[1],"%sCar/DVR/record_view_right_highlight.dds",XR_RES); 
	m_trigger[DVR_RECORD_TAB_VIEW_RIGHT] = new CRecordRightViewActionTrigger;

	for(int i = DVR_RECORD_TAB_RECORD_BKG; i < DVR_RECORD_TAB_ELEMEMT_NUM; i++)
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
int CSVDvrRecordTab::Init(int window_width, int window_height)
{
	float radio = 227.0/1280.0;

	m_buttonSize[DVR_RECORD_TAB_RECORD_BKG][BUTTON_SIZE_WIDTH] = 372.0;
	m_buttonSize[DVR_RECORD_TAB_RECORD_BKG][BUTTON_SIZE_HEIGHT] = 560.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_BKG][BUTTON_POS_X] = radio*window_width;
	m_buttonPos[DVR_RECORD_TAB_RECORD_BKG][BUTTON_POS_Y] = 80.0;
	
	m_buttonSize[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_RECORD_BKG][BUTTON_POS_X] + 50.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_Y] = 80.0 + 80.0;
		
	m_buttonSize[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_SIZE_WIDTH] = 114.0;
	m_buttonSize[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_SIZE_HEIGHT] = 47.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_SIZE_WIDTH] + 100.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_Y]+ m_buttonSize[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_SIZE_WIDTH] + 100.0;
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_Y];
		
	m_buttonSize[DVR_RECORD_TAB_CAPTURE_ICON][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_RECORD_TAB_CAPTURE_ICON][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_ICON][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_POS_Y];
		
	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_SIZE_WIDTH] = 114.0;
	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_SIZE_HEIGHT] = 30.0;
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_SIZE_WIDTH] + 35;
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_ICON][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_ICON][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_ICON][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_RECORD_TAB_VIEW_BKG][BUTTON_SIZE_WIDTH] = 296.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_BKG][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_VIEW_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_SIZE_HEIGHT] + 10.0;

	m_buttonSize[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_VIEW_REAR][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_REAR][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_REAR][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_RECORD_TAB_VIEW_REAR][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_REAR][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_VIEW_REAR][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_REAR][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_VIEW_RIGHT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_RIGHT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_RIGHT][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_RECORD_TAB_VIEW_RIGHT][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_POS_Y];

	SetHmiParams();
	
	return HMI_SUCCESS;
}
int CSVDvrRecordTab::Update(Hmi_Message_T& hmiMsg)
{	
	DVR_GRAPHIC_UIOBJ* recordTabMsg = NULL;
	
	/*DVR_GRAPHIC_UIOBJ rec_gui_table[] =
{
	{ GUI_OBJ_ID_MAIN_MENU_TAB, "main_menu", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_MAIN_MENU_TAB_RECORD },
	{ GUI_OBJ_ID_CARD_STATE, "card_state", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_CARD_STATE_NO_CARD },
	{ GUI_OBJ_ID_REC_SWITCH, "record_switch", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_SWITCH_STATE_OFF },
	{ GUI_OBJ_ID_REC_STATE, "record_state", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_REC_STATE_STOP },
	{ GUI_OBJ_ID_REC_EVENT_RECORD_STATE, "event_record_state", 1, 0, GUI_OBJ_STATUS_TYPE_VALUE, GUI_EMERGENCY_REC_STOP },
	{ GUI_OBJ_ID_REC_VIEW_INDEX, "record_view", 1, 1, GUI_OBJ_STATUS_TYPE_VALUE, GUI_VIEW_INDEX_FRONT }
};*/
		
	if((DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable)
	{
		recordTabMsg = (DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable;
		for(int i = 0; i < hmiMsg.dvrTabMsg.objNum; i++)
		{			
			switch(recordTabMsg[i].Id)
			{
			case GUI_OBJ_ID_REC_SWITCH:
				
				if(recordTabMsg[i].uStatus.ObjVal == GUI_SWITCH_STATE_OFF)
				{
					m_buttonStatus[DVR_RECORD_TAB_RECORD_SWITCH] = BUTTON_OFF_IMAGE;
				}
				else if(recordTabMsg[i].uStatus.ObjVal == GUI_SWITCH_STATE_ON)
				{
					m_buttonStatus[DVR_RECORD_TAB_RECORD_SWITCH] = BUTTON_ON_IMAGE;
				}
				
				break;
			case GUI_OBJ_ID_REC_STATE:
				break;
			case  GUI_OBJ_ID_REC_EVENT_RECORD_STATE:
				if(recordTabMsg[i].uStatus.ObjVal == GUI_EMERGENCY_REC_STOP)
				{
					m_buttonStatus[DVR_RECORD_TAB_EMERGENCY_ICON] = BUTTON_OFF_IMAGE;
				}
				else if(recordTabMsg[i].uStatus.ObjVal == GUI_EMERGENCY_REC_RUNNING)
				{
					m_buttonStatus[DVR_RECORD_TAB_EMERGENCY_ICON] = BUTTON_ON_IMAGE;
				}
				break;
			case GUI_OBJ_ID_REC_VIEW_INDEX:
				
				m_buttonStatus[DVR_RECORD_TAB_VIEW_FRONT] = BUTTON_OFF_IMAGE;
				m_buttonStatus[DVR_RECORD_TAB_VIEW_REAR] = BUTTON_OFF_IMAGE;
				m_buttonStatus[DVR_RECORD_TAB_VIEW_LEFT] = BUTTON_OFF_IMAGE;
				m_buttonStatus[DVR_RECORD_TAB_VIEW_RIGHT] = BUTTON_OFF_IMAGE;
				
				if(recordTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_FRONT)
				{
					AVMData::GetInstance()->SetDisplayViewCmd(FRONT_SINGLE_VIEW);
					
					m_buttonStatus[DVR_RECORD_TAB_VIEW_FRONT] = BUTTON_ON_IMAGE;
				}
				else if(recordTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_REAR)
				{
				
					AVMData::GetInstance()->SetDisplayViewCmd(REAR_SINGLE_VIEW);
					m_buttonStatus[DVR_RECORD_TAB_VIEW_REAR] = BUTTON_ON_IMAGE;
				}
				else if(recordTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_LEFT)
				{
				
					AVMData::GetInstance()->SetDisplayViewCmd(LEFT_SINGLE_VIEW);
					m_buttonStatus[DVR_RECORD_TAB_VIEW_LEFT] = BUTTON_ON_IMAGE;
				}
				else if(recordTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_RIGHT)
				{
				
					AVMData::GetInstance()->SetDisplayViewCmd(RIGHT_SINGLE_VIEW);
					m_buttonStatus[DVR_RECORD_TAB_VIEW_RIGHT] = BUTTON_ON_IMAGE;
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
int CSVDvrRecordTab::RefreshHmi()
{
	for(int i = DVR_RECORD_TAB_RECORD_BKG; i < DVR_RECORD_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
	return HMI_SUCCESS;
}
int CSVDvrRecordTab::SetElementsVisibility(unsigned char pFlag)
{
	memset(m_buttonVisibility, pFlag, DVR_RECORD_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	for(int i = DVR_RECORD_TAB_RECORD_BKG; i < DVR_RECORD_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetVisibility(pFlag);
	}

	return HMI_SUCCESS;
}
int CSVDvrRecordTab::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVDvrRecordTab::DestroyHmiElems()
{
	return HMI_SUCCESS;
}
