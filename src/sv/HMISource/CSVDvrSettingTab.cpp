#include "CSVDvrSettingTab.h"
#include "DVR_GUI_OBJ.h"
#include "gpu_log.h"


class CTimeFirstSelectorActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CTimeFirstSelectorActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_SETUP_LOOPENC_SPLIT_TIME;
		m_dvrCmd.parameter[1] = GUI_SETUP_SPLIT_TIME_1MIN;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CTimeSelectorFirstActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}

};

class CTimeSecondSelectorActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CTimeSecondSelectorActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_SETUP_LOOPENC_SPLIT_TIME;
		m_dvrCmd.parameter[1] = GUI_SETUP_SPLIT_TIME_3MIN;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CTimeSecondSelectorActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}

};

class CTimeThirdSelectorActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CTimeThirdSelectorActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_SETUP_LOOPENC_SPLIT_TIME;
		m_dvrCmd.parameter[1] = GUI_SETUP_SPLIT_TIME_5MIN;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CTimeThirdSelectorActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CSdFormatActionTrigger  : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CSdFormatActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_SETUP_FORMAT_CARD;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CSdFormatActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CSettingDialogFormatConfirmActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbDialogDelConfirmActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_DIALOG;
		m_dvrCmd.parameter[1] = DIALOG_SEL_YES;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CPbDialogDelConfirmActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CSettingDialogFormatCancelActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbDialogDelCancelActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_DIALOG;
		m_dvrCmd.parameter[1] = DIALOG_SEL_NO;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CPbDialogDelCancelActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CSettingDialogCautionConfirmActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbDialogDelConfirmActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_DIALOG;
		m_dvrCmd.parameter[1] = DIALOG_SEL_YES;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CSettingDialogCautionConfirmActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CSettingDialogCautionCancelActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbDialogDelCancelActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_DIALOG;
		m_dvrCmd.parameter[1] = DIALOG_SEL_NO;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CSettingDialogCautionCancelActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CSettingDialogFormatOKActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbDialogDelCancelActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_DIALOG;
		m_dvrCmd.parameter[1] = DIALOG_SEL_OK;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CSettingDialogCautionCancelActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};
	
class CSettingDialogFormatFailedActionTrigger : public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbDialogDelCancelActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{	
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_DIALOG;
		m_dvrCmd.parameter[1] = DIALOG_SEL_OK;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CSettingDialogFormatFailedActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

CSVDvrSettingTab::CSVDvrSettingTab(IUINode* pUiNode = NULL, int pUiNodeId = -1): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	memset(m_trigger, NULL, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 0, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	
	memset(m_dialogVisibility, 0, DVR_SETTING_DIALOG_DIALOG_NUM * sizeof(unsigned char));
}

CSVDvrSettingTab::~CSVDvrSettingTab()
{
    for(int i = 0; i < DVR_SETTING_TAB_ELEMEMT_NUM; i++)
    {
		SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);

		if(i == DVR_SETTING_TAB_TIME_SETTING_FIRST
			|| i == DVR_SETTING_TAB_TIME_SETTING_SECOND
			|| i == DVR_SETTING_TAB_TIME_SETTING_THIRD)
		{
			SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
		}            
        else if(i == DVR_SETTING_TAB_SD_FORMAT_NORMAL)
        {
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[2]);
        }

		SAFE_DELETE(m_trigger[i]);
    }
	for(int i = 1; i < DVR_SETTING_DIALOG_DIALOG_NUM; i++)
	{
	    for(int j = 0; j < DIALOG_CONFIRM_CANCEL_ELEMENT_NUM; j++)
	    {
            SAFE_DELETE(m_dialogData[i].trigger[j]);
	    }
        if(i == DVR_SETTING_DIALOG_FORMATCARD || i == DVR_SETTING_DIALOG_FORMATCARD_CAUTION)
        {
    		for(int j = 0; j < DIALOG_IMAGE_NUM; j++)
    		{
    		    SAFE_DELETE(m_dialogData[i].iconFileName[j]);
    		}            
        }
        else if(i == DVR_SETTING_DIALOG_FORMATCARD_OK ||
            i == DVR_SETTING_DIALOG_FORMATCARD_FAILED)
        {
    		for(int j = 0; j < DIALOG_CANCEL_NORMAL_IMG; j++)
    		{
    		    SAFE_DELETE(m_dialogData[i].iconFileName[j]);
    		}            
        }
		//SAFE_DELETE(m_dialog[i]);
	}
	//Log_Error("----------Release ~CSVDvrSettingTab!");
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
    m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[2] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[0],"%sCar/DVR/sd_format_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[1],"%sCar/DVR/sd_format_press.dds",XR_RES);	
    sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[2],"%sCar/DVR/sd_format_disable.dds",XR_RES);
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].animationStyle = BUTTON_FLASH_HIGHLIGHT;
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
		m_baseButton[i]->SetVisibility(0);
	}

	
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].dialogType = DIALOG_CONFIRM_CANCEL;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].showFlag = 0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_BACKGROUND_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_BACKGROUND_IMG],"%sCar/DVR/dlg_bkg.dds",XR_RES); 
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_TITLE_IMG] = new char[100];
    sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_TITLE_IMG],"%sCar/DVR/dlg_title_formate_sd.dds",XR_RES);  
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_CONFIRM_NORMAL_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_CONFIRM_NORMAL_IMG],"%sCar/DVR/dlg_icon_ok.dds",XR_RES); 
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG],"%sCar/DVR/dlg_icon_ok_highlight.dds",XR_RES); 

	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_CANCEL_NORMAL_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_CANCEL_NORMAL_IMG],"%sCar/DVR/dlg_icon_cancel.dds",XR_RES); 
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG],"%sCar/DVR/dlg_icon_cancel_highlight.dds",XR_RES); 
	
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND] = NULL;//new CSelectorFirstActionTrigger;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].trigger[DIALOG_CONFIRM] = new CSettingDialogFormatConfirmActionTrigger;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].trigger[DIALOG_CANCEL] = new CSettingDialogFormatCancelActionTrigger;

	m_dialog[DVR_SETTING_DIALOG_FORMATCARD] = new HMIDialog(&m_dialogData[DVR_SETTING_DIALOG_FORMATCARD], m_uiNode);
	m_dialog[DVR_SETTING_DIALOG_FORMATCARD]->SetVisibility(0);


    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].dialogType = DIALOG_CONFIRM_CANCEL;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].showFlag = 0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_BACKGROUND_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_BACKGROUND_IMG],"%sCar/DVR/dlg_bkg.dds",XR_RES); 
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_TITLE_IMG] = new char[100];
    sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_TITLE_IMG],"%sCar/DVR/dlg_title_alarm.dds",XR_RES);  
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_CONFIRM_NORMAL_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_CONFIRM_NORMAL_IMG],"%sCar/DVR/dlg_icon_ok.dds",XR_RES); 
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG],"%sCar/DVR/dlg_icon_ok_highlight.dds",XR_RES); 

	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_CANCEL_NORMAL_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_CANCEL_NORMAL_IMG],"%sCar/DVR/dlg_icon_cancel.dds",XR_RES); 
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG],"%sCar/DVR/dlg_icon_cancel_highlight.dds",XR_RES); 
	
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND] = NULL;//new CSelectorFirstActionTrigger;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].trigger[DIALOG_CONFIRM] = new CSettingDialogCautionConfirmActionTrigger;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].trigger[DIALOG_CANCEL] = new CSettingDialogCautionCancelActionTrigger;

	m_dialog[DVR_SETTING_DIALOG_FORMATCARD_CAUTION] = new HMIDialog(&m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION], m_uiNode);
	m_dialog[DVR_SETTING_DIALOG_FORMATCARD_CAUTION]->SetVisibility(0);


    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].dialogType = DIALOG_NORMAL;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].showFlag = 0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].iconFileName[DIALOG_BACKGROUND_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].iconFileName[DIALOG_BACKGROUND_IMG],"%sCar/DVR/dlg_bkg.dds",XR_RES); 
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].iconFileName[DIALOG_TITLE_IMG] = new char[100];
    sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].iconFileName[DIALOG_TITLE_IMG],"%sCar/DVR/dlg_title_formate_success.dds",XR_RES);  
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].iconFileName[DIALOG_CONFIRM_NORMAL_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].iconFileName[DIALOG_CONFIRM_NORMAL_IMG],"%sCar/DVR/dlg_icon_ok.dds",XR_RES); 
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG],"%sCar/DVR/dlg_icon_ok_highlight.dds",XR_RES); 

	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND] = NULL;//new CSelectorFirstActionTrigger;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].trigger[DIALOG_CONFIRM] = new CSettingDialogFormatOKActionTrigger;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].trigger[DIALOG_CANCEL] = NULL;

	m_dialog[DVR_SETTING_DIALOG_FORMATCARD_OK] = new HMIDialog(&m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK], m_uiNode);
	m_dialog[DVR_SETTING_DIALOG_FORMATCARD_OK]->SetVisibility(0);

    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].dialogType = DIALOG_NORMAL;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].showFlag = 0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].iconFileName[DIALOG_BACKGROUND_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].iconFileName[DIALOG_BACKGROUND_IMG],"%sCar/DVR/dlg_bkg.dds",XR_RES); 
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].iconFileName[DIALOG_TITLE_IMG] = new char[100];
    sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].iconFileName[DIALOG_TITLE_IMG],"%sCar/DVR/dlg_title_formate_failed.dds",XR_RES);  
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].iconFileName[DIALOG_CONFIRM_NORMAL_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].iconFileName[DIALOG_CONFIRM_NORMAL_IMG],"%sCar/DVR/dlg_icon_ok.dds",XR_RES); 
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG] = new char[100];
	sprintf(m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG],"%sCar/DVR/dlg_icon_ok_highlight.dds",XR_RES); 

	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND] = NULL;//new CSelectorFirstActionTrigger;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].trigger[DIALOG_CONFIRM] = new CSettingDialogFormatFailedActionTrigger;;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].trigger[DIALOG_CANCEL] = NULL;

	m_dialog[DVR_SETTING_DIALOG_FORMATCARD_FAILED] = new HMIDialog(&m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED], m_uiNode);
	m_dialog[DVR_SETTING_DIALOG_FORMATCARD_FAILED]->SetVisibility(0);


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

	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].width = 348.0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].height = 183.0;
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].titleWidth = 185.0;
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].titleHeight = 23.0;

	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].pos[0] = (1 + radio) * 0.5 * window_width - 0.5 * m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].width;
//	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].pos[1] = 80.0 + 0.5 * (window_height - 160.0 - m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].height);
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].pos[1] = 0.5 * (window_height - m_dialogData[DVR_SETTING_DIALOG_FORMATCARD].height);

	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].width = 348.0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].height = 183.0;
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].titleWidth = 294.0;
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].titleHeight = 52.0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].pos[0] = (1 + radio) * 0.5 * window_width - 0.5 * m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].width;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].pos[1] = 0.5 * (window_height - m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_CAUTION].height);

	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].width = 348.0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].height = 183.0;
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].titleWidth = 127.0;
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].titleHeight = 23.0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].pos[0] = (1 + radio) * 0.5 * window_width - 0.5 * m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].width;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].pos[1] = 0.5 * (window_height - m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_OK].height);

    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].width = 348.0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].height = 183.0;
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].titleWidth = 127.0;
    m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].titleHeight = 23.0;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].pos[0] = (1 + radio) * 0.5 * window_width - 0.5 * m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].width;
	m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].pos[1] = 0.5 * (window_height - m_dialogData[DVR_SETTING_DIALOG_FORMATCARD_FAILED].height);
	
	SetHmiParams();
	
	return HMI_SUCCESS;
}
int CSVDvrSettingTab::Update(Hmi_Message_T& hmiMsg)
{
	DVR_GRAPHIC_UIOBJ* settigTabMsg = NULL;
	
	GUI_OBJ_DIALOG_INST*	    dialogInst = NULL;
	
	/*DVR_GRAPHIC_UIOBJ setup_gui_table[] =
	{
		{ GUI_OBJ_ID_MAIN_MENU_TAB, "main_menu", 1, 1, GUI_OBJ_STATUS_TYPE_U32, GUI_MAIN_MENU_TAB_SETUP },
		{ GUI_OBJ_ID_SETUP_SPLIT_TIME, "split_time", 1, 1, GUI_OBJ_STATUS_TYPE_U32, GUI_SETUP_SPLIT_TIME_1MIN },
		{ GUI_OBJ_ID_SETUP_VIDEO_QUALITY, "video_quality", 1, 1, GUI_OBJ_STATUS_TYPE_U32, GUI_SETUP_VIDEO_QUALITY_SFINE },
		{ GUI_OBJ_ID_SETUP_PHOTO_QUALITY, "photo_quality", 1, 1, GUI_OBJ_STATUS_TYPE_U32, GUI_SETUP_PHOTO_QUALITY_SFINE },
		{ GUI_OBJ_ID_SETUP_FORMAT_CARD, "format_card", 1, 1, GUI_OBJ_STATUS_TYPE_U32, 0 },
		{ GUI_OBJ_ID_DIALOG, "dialog", 1, 0, GUI_OBJ_STATUS_TYPE_POINTER, (unsigned int)&m_dialog },
		{ GUI_OBJ_ID_WARNING, "warning", 1, 0, GUI_OBJ_STATUS_TYPE_U32, GUI_WARNING_NONE }
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
                if(settigTabMsg[i].bEnable == 1)
                {
                   m_buttonStatus[DVR_SETTING_TAB_SD_FORMAT_NORMAL] = 0; 
                   m_baseButton[DVR_SETTING_TAB_SD_FORMAT_NORMAL]->SetAnimationStyle(BUTTON_FLASH_HIGHLIGHT);
                }
				else if(settigTabMsg[i].bEnable == 0)
                {
                   m_buttonStatus[DVR_SETTING_TAB_SD_FORMAT_NORMAL] = 2; 
                   m_baseButton[DVR_SETTING_TAB_SD_FORMAT_NORMAL]->SetAnimationStyle(BUTTON_NOMAL);
                }
				break;
			case GUI_OBJ_ID_DIALOG:
				if(GUI_OBJ_STATUS_TYPE_POINTER == settigTabMsg[i].status_type
					&& settigTabMsg[i].uStatus.ptr)
				{
					dialogInst = (GUI_OBJ_DIALOG_INST*)settigTabMsg[i].uStatus.ptr;
                    for(int j = DVR_SETTING_DIALOG_FORMATCARD; j < DVR_SETTING_DIALOG_DIALOG_NUM; j ++)
                    {
                        if(j == dialogInst->subjectId)
                        {
                            m_dialogVisibility[j] = settigTabMsg[i].bShow;
                        }
                        else
                        {
                            m_dialogVisibility[j] = 0;    
                        }                    
                    }
                    
					//Log_Error("dialog type: %d, Id: %d, show: %d", dialogInst->type, dialogInst->subjectId, settigTabMsg[i].bShow);
				}

				break;

			case GUI_OBJ_ID_WARNING:
				if(GUI_OBJ_STATUS_TYPE_U32 == settigTabMsg[i].status_type)
				{
//					Log_Error("warning : %d", settigTabMsg[i].status_type);
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
int CSVDvrSettingTab::RefreshHmi()
{
	for(int i = DVR_SETTING_TAB_TIME_SETTING; i < DVR_SETTING_TAB_ELEMEMT_NUM; i++)

	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
	for(int i = DVR_SETTING_DIALOG_FORMATCARD; i < DVR_SETTING_DIALOG_DIALOG_NUM; i++)
	{
		m_dialog[i]->SetVisibility(m_dialogVisibility[i]);
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
	if(pFlag == 1)
	{		
/*		for(int i = DVR_SETTING_DIALOG_FORMATCARD; i < DVR_SETTING_DIALOG_DIALOG_NUM; i++)
		{
			m_dialogVisibility[i] = pFlag;
		
			m_dialog[i]->SetVisibility(m_dialogVisibility[i]);
		}
*/
//   		m_dialogVisibility[DVR_SETTING_DIALOG_FORMATCARD] = 0;
		m_dialog[DVR_SETTING_DIALOG_FORMATCARD]->SetVisibility(m_dialogVisibility[DVR_SETTING_DIALOG_FORMATCARD]);
//        m_dialogVisibility[DVR_SETTING_DIALOG_FORMATCARD_CAUTION] = 0;
		m_dialog[DVR_SETTING_DIALOG_FORMATCARD_CAUTION]->SetVisibility(m_dialogVisibility[DVR_SETTING_DIALOG_FORMATCARD_CAUTION]);
//     	m_dialogVisibility[DVR_SETTING_DIALOG_FORMATCARD_OK] = 0;
		m_dialog[DVR_SETTING_DIALOG_FORMATCARD_OK]->SetVisibility(m_dialogVisibility[DVR_SETTING_DIALOG_FORMATCARD_OK]);  
        m_dialog[DVR_SETTING_DIALOG_FORMATCARD_FAILED]->SetVisibility(m_dialogVisibility[DVR_SETTING_DIALOG_FORMATCARD_FAILED]);         
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
