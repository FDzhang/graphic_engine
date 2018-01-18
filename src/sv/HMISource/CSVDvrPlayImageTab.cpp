#include "CSVDvrPlayImageTab.h"
#include "DVR_GUI_OBJ.h"

#define PB_IMAGE_HIDE_TIME 5000;
unsigned int PbImageStartTime;
unsigned int PbImageHideTimeCount;

enum
{
	DVR_STATE_PLAY_NORMAL = 0,
	DVR_STATE_PLAY_HIGHLIGHT,	
	DVR_STATE_SUSPEND_NORMAL,
	DVR_STATE_SUSPEND_HIGHLIGHT,	
};

static int pressCnt = 0;

class CPbImageMenuHideActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageMenuHideActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_SIDEBAR;
        m_dvrCmd->parameter[1] = GUI_SIDEBAR_STATUS_HIDE;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageMenuHideActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageMenuShowActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageMenuShowActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_SIDEBAR;
        m_dvrCmd->parameter[1] = GUI_SIDEBAR_STATUS_SHOW;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageMenuShowActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbPlayImageActionTrigger : public IActionTrigger
{

    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbPlayImageActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
/*        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_PLAY;

        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));
*/
        Log_Message("-----------CPbPlayImageActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbPreImageActionTrigger : public IActionTrigger
{

    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbPreImageActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_PREV;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbPreImageActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbNextImageActionTrigger : public IActionTrigger
{

    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbNextImageActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_NEXT;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbNextImageActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageFrontViewActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageFrontViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_VIEW;
        m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_FRONT;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageFrontViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageRearViewActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageRearViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_VIEW;
        m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_REAR;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageRearViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageLeftViewActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageLeftViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_VIEW;
        m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_LEFT;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageLeftViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageRightViewActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageRightViewActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_VIEW;
        m_dvrCmd->parameter[1] = GUI_VIEW_INDEX_RIGHT;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageRightViewActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageEmergencySaveActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageEmergencySaveActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_SAVE;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageEmergencySaveActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageDeleteActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageDeleteActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_DELETE;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageDeleteActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageDcSwitchActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageDcSwitchActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_DC_SWITCH;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageDcSwitchActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageDialogDelConfirmActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageDialogDelConfirmActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_DIALOG;
        m_dvrCmd->parameter[1] = DIALOG_SEL_YES;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbDialogDelCoCPbImageDialogDelConfirmActionTriggernfirmActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPbImageDialogDelCancelActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CPbImageDialogDelCancelActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_DIALOG;
        m_dvrCmd->parameter[1] = DIALOG_SEL_NO;
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CPbImageDialogDelCancelActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

CSVDvrPlayImageTab::~CSVDvrPlayImageTab()
{
    for (int i = 0; i < DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM; i++)
    {
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);

        if (i == DVR_PLAYBACK_IMAGE_TAB_PLAY)
        {
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[2]);
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[3]);
        }

        if (i == DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE || i == DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE || i == DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON || i == DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON || i == DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH || i == DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT

            || i == DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR || i == DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT || i == DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT)
        {
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
        }

        if (i == DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON)
        {
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
        }
        if (i == DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON)
        {
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
        }
        //SAFE_DELETE(m_baseButton[i]);
        SAFE_DELETE(m_trigger[i]);
    }
    for (int i = 0; i < DVR_PLAYBACK_IMAGE_DIALOG_NUM; i++)
    {
        for (int j = 0; j < DIALOG_CONFIRM_CANCEL_ELEMENT_NUM; j++)
        {
            SAFE_DELETE(m_dialogData[i].trigger[j]);
        }
        for (int j = 0; j < DIALOG_IMAGE_NUM; j++)
        {
            SAFE_DELETE(m_dialogData[i].iconFileName[j]);
        }
        //SAFE_DELETE(m_dialog[i]);
    }

    for (int i = 0; i < IMAGE_TEXT_DISPLAY_NUM; i++)
    {
        SAFE_DELETE(m_textEditData[i].trigger);
        SAFE_DELETE(m_textEditData[i].textContent[0]);
        //SAFE_DELETE(m_textEdit[i]);
    }

    //SAFE_DELETE(m_processBar);
//    Log_Error("----------Release ~CSVDvrPlaybackTab!");
}

CSVDvrPlayImageTab::CSVDvrPlayImageTab(IUINode *pUiNode, int pUiNodeId) : ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
    memset(m_trigger, NULL, DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM * sizeof(IActionTrigger *));
    memset(m_buttonStatus, 0, DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM * sizeof(unsigned char));
    memset(m_buttonVisibility, 1, DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM * sizeof(unsigned char));
    memset(m_textEditVisibility, 0, IMAGE_TEXT_DISPLAY_NUM * sizeof(unsigned char));

    memset(m_dialogVisibility, 0, DVR_PLAYBACK_IMAGE_DIALOG_NUM * sizeof(unsigned char));

    m_menuVisibility = GUI_SIDEBAR_STATUS_SHOW;
    PbImageStartTime = 0;
    PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
}

int CSVDvrPlayImageTab::SetHmiParams()
{
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG].icon_file_name[0], "%sCar/DVR/player_bkg.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG].icon_file_name[0], "%sCar/DVR/time_title_bkg.dds", XR_RES);

	m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].show_flag = 1;
	m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].show_icon_num =2;
	m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_file_name[1] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_file_name[2] = new char[100];
	m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_file_name[3] = new char[100];
	sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_file_name[0],"%sCar/DVR/player_play_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_file_name[1],"%sCar/DVR/player_play_highlight.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_file_name[2],"%sCar/DVR/player_suspend_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PLAY].icon_file_name[3],"%sCar/DVR/player_suspend_hightlight.dds",XR_RES); 

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE].icon_file_name[0] = new char[100];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE].icon_file_name[1] = new char[100];

    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE].icon_file_name[0], "%sCar/DVR/player_np_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE].icon_file_name[1], "%sCar/DVR/player_np_press.dds", XR_RES);
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE].animationStyle = BUTTON_FLASH_HIGHLIGHT;

    m_trigger[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE] = new CPbNextImageActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE].icon_file_name[0] = new char[100];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE].icon_file_name[1] = new char[100];

    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE].icon_file_name[0], "%sCar/DVR/player_pp_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE].icon_file_name[1], "%sCar/DVR/player_pp_press.dds", XR_RES);
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE] = new CPbPreImageActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG].icon_file_name[0], "%sCar/DVR/record_tab_bkg.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].icon_file_name[0] = new char[50];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].icon_file_name[0], "%sCar/DVR/menu_hide_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].icon_file_name[1], "%sCar/DVR/menu_hide_hightlight.dds", XR_RES);
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON] = new CPbImageMenuHideActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].icon_file_name[0] = new char[50];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].icon_file_name[0], "%sCar/DVR/menu_show_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].icon_file_name[1], "%sCar/DVR/menu_show_hightlight.dds", XR_RES);
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON] = new CPbImageMenuShowActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE].icon_file_name[0], "%sCar/DVR/emergency_save_title.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG].icon_file_name[0], "%sCar/DVR/emergency_bkg.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON].icon_file_name[0] = new char[100];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON].icon_file_name[1] = new char[100];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON].icon_file_name[0], "%sCar/DVR/emergency_save_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON].icon_file_name[1], "%sCar/DVR/emergency_save_press.dds", XR_RES);
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON] = NULL;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE].icon_file_name[0], "%sCar/DVR/playback_delete_title.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG].icon_file_name[0], "%sCar/DVR/emergency_bkg.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON].icon_file_name[0] = new char[50];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON].icon_file_name[0], "%sCar/DVR/playback_delete_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON].icon_file_name[1], "%sCar/DVR/playback_delete_press.dds", XR_RES);
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON] = new CPbImageDeleteActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE].icon_file_name[0], "%sCar/DVR/dc_title.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH].icon_file_name[0] = new char[50];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH].icon_file_name[0], "%sCar/DVR/record_switch_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH].icon_file_name[1], "%sCar/DVR/record_switch_press.dds", XR_RES);
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH] = new CPbImageDcSwitchActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE].icon_file_name[0], "%sCar/DVR/record_view_title.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG].icon_file_name[0], "%sCar/DVR/record_view_bkg.dds", XR_RES);

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT].icon_file_name[0] = new char[50];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT].icon_file_name[0], "%sCar/DVR/record_view_front_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT].icon_file_name[1], "%sCar/DVR/record_view_front_highlight.dds", XR_RES);
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT] = new CPbImageFrontViewActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR].icon_file_name[0] = new char[50];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR].icon_file_name[0], "%sCar/DVR/record_view_rear_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR].icon_file_name[1], "%sCar/DVR/record_view_rear_highlight.dds", XR_RES);
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR] = new CPbImageRearViewActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT].icon_file_name[0] = new char[50];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT].icon_file_name[0], "%sCar/DVR/record_view_left_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT].icon_file_name[1], "%sCar/DVR/record_view_left_highlight.dds", XR_RES);
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT] = new CPbImageLeftViewActionTrigger;

    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT].icon_type = STATIC_ICON;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT].show_flag = 1;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT].show_icon_num = 0;
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT].icon_file_name[0] = new char[50];
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT].icon_file_name[0], "%sCar/DVR/record_view_right_normal.dds", XR_RES);
    sprintf(m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT].icon_file_name[1], "%sCar/DVR/record_view_right_highlight.dds", XR_RES);
    m_trigger[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT] = new CPbImageRightViewActionTrigger;

    m_textEditData[IMAGE_TEXT_NAME_TITLE].fontTypeMtlName = XR_RES "text_box.ttf";
    m_textEditData[IMAGE_TEXT_NAME_TITLE].textContent[0] = new char[100];
    m_textEditContent[IMAGE_TEXT_NAME_TITLE] = "17:30-17:40 16/12/12";
    sprintf(m_textEditData[IMAGE_TEXT_NAME_TITLE].textContent[0], "%s", m_textEditContent[IMAGE_TEXT_NAME_TITLE]);

    for (int i = DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG; i < DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM; i++)
    {
        m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
        m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
        m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
        m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
        m_baseButtonData[i].delegate_func = NULL;
        m_baseButtonData[i].trigger = m_trigger[i];

        m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]), m_uiNode);
        m_baseButton[i]->SetVisibility(0);
    }

    for (int i = IMAGE_TEXT_NAME_TITLE; i < IMAGE_TEXT_DISPLAY_NUM; i++)
    {
        m_textEdit[i] = new HmiTextEdit(&m_textEditData[i], m_uiNode);
        m_textEdit[i]->SetVisibility(0);
    }

    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].dialogType = DIALOG_CONFIRM_CANCEL;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].showFlag = 0;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_BACKGROUND_IMG] = new char[100];
    sprintf(m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_BACKGROUND_IMG], "%sCar/DVR/dlg_bkg.dds", XR_RES);
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_TITLE_IMG] = new char[100];
    sprintf(m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_TITLE_IMG], "%sCar/DVR/dlg_title_del_file.dds", XR_RES);
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_CONFIRM_NORMAL_IMG] = new char[100];
    sprintf(m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_CONFIRM_NORMAL_IMG], "%sCar/DVR/dlg_icon_ok.dds", XR_RES);
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG] = new char[100];
    sprintf(m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG], "%sCar/DVR/dlg_icon_ok_highlight.dds", XR_RES);

    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_CANCEL_NORMAL_IMG] = new char[100];
    sprintf(m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_CANCEL_NORMAL_IMG], "%sCar/DVR/dlg_icon_cancel.dds", XR_RES);
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG] = new char[100];
    sprintf(m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG], "%sCar/DVR/dlg_icon_cancel_highlight.dds", XR_RES);

    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND] = NULL; //new CSelectorFirstActionTrigger;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].trigger[DIALOG_CONFIRM] = new CPbImageDialogDelConfirmActionTrigger;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].trigger[DIALOG_CANCEL] = new CPbImageDialogDelCancelActionTrigger;

    m_dialog[DVR_PLAYBACK_IMAGE_DIALOG_DEL] = new HMIDialog(&m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL], m_uiNode);
    m_dialog[DVR_PLAYBACK_IMAGE_DIALOG_DEL]->SetVisibility(0);

    return HMI_SUCCESS;
}
int CSVDvrPlayImageTab::Init(int window_width, int window_height)
{
    float radio = 227.0 / 1280.0;
    float playerIconInterval = 10.0;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH] = 683.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] = 81.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_POS_X] = radio * window_width + ((1.0 - radio) * window_width - m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH]) * 0.5;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_POS_Y] = window_height - 80.0 - m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG][BUTTON_SIZE_WIDTH] = 683.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG][BUTTON_SIZE_HEIGHT] = 80.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG][BUTTON_POS_X] = radio * window_width + ((1.0 - radio) * window_width - m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH]) * 0.5;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG][BUTTON_POS_Y] = 80.0;

	m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_SIZE_WIDTH] = 56.0;
	m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_SIZE_HEIGHT] = 65.0;
	m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_WIDTH] * 0.5 - m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_SIZE_WIDTH] * 0.5;
	m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_SIZE_HEIGHT]) * 0.5;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE][BUTTON_SIZE_WIDTH] = 64.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE][BUTTON_SIZE_HEIGHT] = 66.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_SIZE_WIDTH] + playerIconInterval;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE][BUTTON_SIZE_HEIGHT]) * 0.5;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE][BUTTON_SIZE_WIDTH] = 64.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE][BUTTON_SIZE_HEIGHT] = 66.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAY][BUTTON_POS_X]- playerIconInterval - m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE][BUTTON_SIZE_WIDTH] ;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE][BUTTON_POS_Y] =  m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_POS_Y] + (m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG][BUTTON_SIZE_HEIGHT] - m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE][BUTTON_SIZE_HEIGHT]) * 0.5;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG][BUTTON_SIZE_WIDTH] = 372.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG][BUTTON_SIZE_HEIGHT] = 560.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG][BUTTON_POS_X] = radio * window_width;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG][BUTTON_POS_Y] = 80.0;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON][BUTTON_SIZE_WIDTH] = 42.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON][BUTTON_SIZE_HEIGHT] = 45.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON][BUTTON_POS_X] = radio * window_width;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON][BUTTON_POS_Y] = 0.5 * window_height - 23;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON][BUTTON_SIZE_WIDTH] = 42.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON][BUTTON_SIZE_HEIGHT] = 45.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON][BUTTON_POS_X] = radio * window_width;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON][BUTTON_POS_Y] = 0.5 * window_height - 23;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_SIZE_WIDTH] = 113.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_SIZE_HEIGHT] = 30.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG][BUTTON_POS_X] + 50.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_POS_Y] = 80.0 + 80.0;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_SIZE_WIDTH] = 122.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_SIZE_WIDTH] + 60.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_POS_Y];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON][BUTTON_SIZE_WIDTH] = m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_SIZE_WIDTH];
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON][BUTTON_SIZE_HEIGHT] = m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_SIZE_HEIGHT];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_POS_Y];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE][BUTTON_SIZE_WIDTH] = 59.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG][BUTTON_SIZE_WIDTH] = 122.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE][BUTTON_POS_Y];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON][BUTTON_SIZE_WIDTH] = 122.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON][BUTTON_SIZE_HEIGHT] = 58.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG][BUTTON_POS_Y];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH][BUTTON_SIZE_WIDTH] = 114.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH][BUTTON_SIZE_HEIGHT] = 47.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE][BUTTON_POS_Y];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_DC_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG][BUTTON_SIZE_WIDTH] = 296.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE][BUTTON_SIZE_HEIGHT] + 10.0;

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT][BUTTON_SIZE_WIDTH] = 75.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT][BUTTON_SIZE_HEIGHT] = 57.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG][BUTTON_POS_X];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG][BUTTON_POS_Y];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR][BUTTON_SIZE_WIDTH] = 75.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR][BUTTON_SIZE_HEIGHT] = 57.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT][BUTTON_SIZE_WIDTH];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT][BUTTON_POS_Y];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT][BUTTON_SIZE_WIDTH] = 75.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT][BUTTON_SIZE_HEIGHT] = 57.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR][BUTTON_SIZE_WIDTH];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR][BUTTON_POS_Y];

    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT][BUTTON_SIZE_WIDTH] = 75.0;
    m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT][BUTTON_SIZE_HEIGHT] = 57.0;
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT][BUTTON_POS_X] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT][BUTTON_POS_X] + m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT][BUTTON_SIZE_WIDTH];
    m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT][BUTTON_POS_Y] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT][BUTTON_POS_Y];

    m_textEditData[IMAGE_TEXT_NAME_TITLE].width = 30;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].pos[0] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG][BUTTON_POS_X] + (m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG][BUTTON_POS_X] - m_textEditData[0].width) * 0.5;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].pos[1] = m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG][BUTTON_POS_Y] + 20.0;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].font_size = 4.0;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].line_num = 1;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].targetIndex = -1;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].insertFlag = InsertFlag_Default;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].trigger = NULL;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].textColor[0] = 1.0;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].textColor[1] = 1.0;
    m_textEditData[IMAGE_TEXT_NAME_TITLE].textColor[2] = 1.0;

    /*	m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].width = 300.0;
	m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].height = 200.0;

	m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].pos[0] = window_width * 0.5;
	m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].pos[1] = 80.0 + 0.5 * (window_height - 160.0 - m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].height);
*/
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].width = 348.0;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].height = 183.0;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].titleWidth = 224.0;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].titleHeight = 23.0;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].pos[0] = (1 + radio) * 0.5 * window_width - 0.5 * m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].width;
    m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].pos[1] = 0.5 * (window_height - m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_DEL].height);

    SetHmiParams();

    return HMI_SUCCESS;
}
int CSVDvrPlayImageTab::Update(Hmi_Message_T &hmiMsg)
{
    static int currentFileNum = 0;
    int fileNumCnt = 0;

    DVR_GRAPHIC_UIOBJ *playbackTabMsg = NULL;
    GUI_OBJ_PLAY_FILENAME_INST *playbackFileName = NULL;
    GUI_OBJ_PLAY_TIME_INST *playbackTimeInfo = NULL;
    GUI_OBJ_DIALOG_INST *dialogInst = NULL;

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

    if ((DVR_GRAPHIC_UIOBJ *)hmiMsg.dvrTabMsg.tabMsgTable)
    {
        playbackTabMsg = (DVR_GRAPHIC_UIOBJ *)hmiMsg.dvrTabMsg.tabMsgTable;

        for (int i = 0; i < hmiMsg.dvrTabMsg.objNum; i++)
        {
            switch (playbackTabMsg[i].Id)
            {
            case GUI_OBJ_ID_PB_PLAY_STATE:

                if (GUI_OBJ_STATUS_TYPE_U32 == playbackTabMsg[i].status_type)
                {

                    if (playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_RUNNING)
                    {
                        m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_PLAY] = DVR_STATE_SUSPEND_NORMAL;
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_PAUSE)
                    {
                        m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_PLAY] = DVR_STATE_PLAY_NORMAL;
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_FAST_FORWARD)
                    {
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_FAST_BACKWARD)
                    {
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_PLAY_STATE_INVALID)
                    {
                    }
                }
                break;
            case GUI_OBJ_ID_PB_PLAY_SPEED:
                break;
            case GUI_OBJ_ID_PB_VIEW_INDEX:

                if (GUI_OBJ_STATUS_TYPE_U32 == playbackTabMsg[i].status_type)
                {
                    m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT] = BUTTON_OFF_IMAGE;
                    m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR] = BUTTON_OFF_IMAGE;
                    m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT] = BUTTON_OFF_IMAGE;
                    m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT] = BUTTON_OFF_IMAGE;

                    if (playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_FRONT)
                    {
                        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_FRONT_SINGLE_VIEW);
                        m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT] = BUTTON_ON_IMAGE;
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_REAR)
                    {
                        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_REAR_SINGLE_VIEW);
                        m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR] = BUTTON_ON_IMAGE;
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_LEFT)
                    {
                        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_LEFT_SINGLE_VIEW);
                        m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT] = BUTTON_ON_IMAGE;
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_RIGHT)
                    {
                        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_RIGHT_SINGLE_VIEW);
                        m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT] = BUTTON_ON_IMAGE;
                    }
                }

                break;

            case GUI_OBJ_ID_PB_FILENAME:

                if (GUI_OBJ_STATUS_TYPE_POINTER == playbackTabMsg[i].status_type && playbackTabMsg[i].uStatus.ptr)
                {
                    playbackFileName = (GUI_OBJ_PLAY_FILENAME_INST *)playbackTabMsg[i].uStatus.ptr;

                    sprintf(m_textEditContent[IMAGE_TEXT_NAME_TITLE], "%s", playbackFileName->filename);
                }

                break;
            case GUI_OBJ_ID_PB_DC_SWITCH:
                if (GUI_OBJ_STATUS_TYPE_U32 == playbackTabMsg[i].status_type)
                {
                    if (playbackTabMsg[i].uStatus.ObjVal == GUI_SWITCH_STATE_ON)
                    {
                        m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH] = BUTTON_ON_IMAGE;
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_SWITCH_STATE_OFF)
                    {
                        m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH] = BUTTON_OFF_IMAGE;
                    }
                }

                break;

            case GUI_OBJ_ID_PB_PLAY_TIMER:
                break;
            case GUI_OBJ_ID_DIALOG:
                if (GUI_OBJ_STATUS_TYPE_POINTER == playbackTabMsg[i].status_type && playbackTabMsg[i].uStatus.ptr)
                {
                    dialogInst = (GUI_OBJ_DIALOG_INST *)playbackTabMsg[i].uStatus.ptr;
                    //					Log_Error("dialog type: %d, Id: %d, show: %d", dialogInst->type, dialogInst->subjectId, playbackTabMsg[i].bShow);
                    m_dialogVisibility[dialogInst->subjectId] = playbackTabMsg[i].bShow;
                }

                break;

            case GUI_OBJ_ID_WARNING:
                if (GUI_OBJ_STATUS_TYPE_U32 == playbackTabMsg[i].status_type)
                {
                    //					Log_Error("warning : %d", playbackTabMsg[i].status_type);
                }
                break;
            case GUI_OBJ_ID_SIDEBAR:

                if (playbackTabMsg[i].bShow == GUI_SIDEBAR_STATUS_HIDE)
                {
                    m_menuVisibility = GUI_SIDEBAR_STATUS_HIDE;
                }
                else if (playbackTabMsg[i].bShow == GUI_SIDEBAR_STATUS_SHOW)
                {
                    m_menuVisibility = GUI_SIDEBAR_STATUS_SHOW;
                }

                for (int i = DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG; i < DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM; i++)
                {
                    m_buttonVisibility[i] = m_menuVisibility;
                }
                if (m_menuVisibility == GUI_SIDEBAR_STATUS_SHOW)
                {
                    m_buttonVisibility[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON] = 1;
                    m_buttonVisibility[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON] = 0;
                }
                else if (m_menuVisibility == GUI_SIDEBAR_STATUS_HIDE)
                {
                    m_buttonVisibility[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON] = 0;
                    m_buttonVisibility[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON] = 1;
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
int CSVDvrPlayImageTab::RefreshHmi()
{
    for (int i = DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG; i < DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM; i++)
    {
        m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
        m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
        m_baseButton[i]->Update();
    }
    for (int i = IMAGE_TEXT_NAME_TITLE; i < IMAGE_TEXT_DISPLAY_NUM; i++)
    {
        m_textEdit[i]->SetVisibility(m_textEditVisibility[i]);
        m_textEdit[i]->Update(m_textEditContent[i]);
    }
    for (int i = DVR_PLAYBACK_IMAGE_DIALOG_DEL; i < DVR_PLAYBACK_IMAGE_DIALOG_NUM; i++)
    {
        m_dialog[i]->SetVisibility(m_dialogVisibility[i]);
    }
    return HMI_SUCCESS;
}

int CSVDvrPlayImageTab::SetMenuVisibility()
{
    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON].trigger->OnPress(0);
    return HMI_SUCCESS;
}

int CSVDvrPlayImageTab::SetMenuHideCount(unsigned char visible)
{
    unsigned int endTime, durTime;
    if (visible == 0)
    {
        PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
        PbImageStartTime = XrGetTime();
    }
    else
    {
        if (m_menuVisibility == GUI_SIDEBAR_STATUS_HIDE)
        {
            PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
            PbImageStartTime = XrGetTime();
        }
        else
        {
            if (PbImageStartTime == 0)
            {
                PbImageStartTime = XrGetTime();
                Log_Message("startTime = %d", PbImageStartTime);
            }
            else
            {
                endTime = XrGetTime();
                durTime = endTime - PbImageStartTime;
                Log_Message("durTime = %d", durTime);
                PbImageStartTime = endTime;
                if (PbImageHideTimeCount > durTime)
                {
                    PbImageHideTimeCount = PbImageHideTimeCount - durTime;
                    Log_Message("hideTimeCount > durTime");
                }
                else
                {
                    PbImageHideTimeCount = PB_IMAGE_HIDE_TIME;
                    m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON].trigger->OnPress(0);
                    Log_Message("hideTimeCount < durTime");
                }
            }
        }
    }
    Log_Message("par = %d,Visible = %d,WaitTime = %d", visible, m_menuVisibility, PbImageHideTimeCount);
    return HMI_SUCCESS;
}

int CSVDvrPlayImageTab::SetElementsVisibility(unsigned char pFlag)
{
    memset(m_buttonVisibility, pFlag, DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM * sizeof(unsigned char));
    if (pFlag == BUTTON_HIDE)
    {
        for (int i = DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG; i < DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM; i++)

        {
            m_baseButton[i]->SetVisibility(BUTTON_HIDE);
        }
    }
    else if (pFlag == BUTTON_SHOW)
    {
        for (int i = DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG; i < DVR_PLAYBACK_IMAGE_TAB_MENU_BKG; i++)
        {
            m_baseButton[i]->SetVisibility(BUTTON_SHOW);
        }
        if (m_menuVisibility == GUI_SIDEBAR_STATUS_HIDE)
        {
            m_baseButton[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG]->SetVisibility(BUTTON_HIDE);
            m_baseButton[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON]->SetVisibility(BUTTON_HIDE);
            m_baseButton[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON]->SetVisibility(BUTTON_SHOW);
            for (int i = DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE; i < DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM; i++)
            {
                m_baseButton[i]->SetVisibility(BUTTON_HIDE);
            }
        }
        else if (m_menuVisibility == GUI_SIDEBAR_STATUS_SHOW)
        {
            m_baseButton[DVR_PLAYBACK_IMAGE_TAB_MENU_BKG]->SetVisibility(BUTTON_SHOW);
            m_baseButton[DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON]->SetVisibility(BUTTON_SHOW);
            m_baseButton[DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON]->SetVisibility(BUTTON_HIDE);
            for (int i = DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE; i < DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM; i++)
            {
                m_baseButton[i]->SetVisibility(BUTTON_SHOW);
            }
        }
    }

    for (int i = IMAGE_TEXT_NAME_TITLE; i < IMAGE_TEXT_DISPLAY_NUM; i++)
    {
        m_textEdit[i]->SetVisibility(pFlag);
        m_textEditVisibility[i] = pFlag;
    }

    if (pFlag == 0)
    {
        for (int i = DVR_PLAYBACK_IMAGE_DIALOG_DEL; i < DVR_PLAYBACK_IMAGE_DIALOG_NUM; i++)
        {
            m_dialogVisibility[i] = pFlag;
            m_dialog[i]->SetVisibility(m_dialogVisibility[i]);
        }
    }
    return HMI_SUCCESS;
}
int CSVDvrPlayImageTab::ReturnHmiMsg(Hmi_Message_T *hmi_msg)
{
    return HMI_SUCCESS;
}
int CSVDvrPlayImageTab::DestroyHmiElems()
{
    return HMI_SUCCESS;
}

int CSVDvrPlayImageTab::ToString(int pTime, char **pOutString)
{

    int time_sec = pTime % 60;
    int time_min = pTime / 60;

    if ((*pOutString) == NULL)
    {
        (*pOutString) = new char[100];
    }

    if (time_min < 10)
    {
        if (time_sec < 10)
        {
            sprintf((*pOutString), "0%d : 0%d", time_min, time_sec);
        }
        else
        {
            sprintf((*pOutString), "0%d : %d", time_min, time_sec);
        }
    }
    else
    {
        if (time_sec < 10)
        {
            sprintf((*pOutString), "%d : 0%d", time_min, time_sec);
        }
        else
        {
            sprintf((*pOutString), "%d : %d", time_min, time_sec);
        }
    }

    return HMI_SUCCESS;
}
