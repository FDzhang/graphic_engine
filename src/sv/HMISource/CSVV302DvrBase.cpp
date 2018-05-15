#include "CSVV302DvrBase.h"
#include "CSVHmiIntent.h"
#include "CSVV302FileListTab.h"
#include "CSVV302RecordTab.h"
#include "CSVV302PlaybackTab.h"
#include "CSVV302PlayImageTab.h"


#include "DVR_GUI_OBJ.h"
#include "gpu_log.h"


REGISTER_HMI_CLASS(CSVV302DvrBase);


class CV302RecTabActionTrigger : public IActionTrigger
{
public:
	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_MAIN_MENU;
		m_dvrCmd.parameter[1] = GUI_MAIN_MENU_TAB_RECORD;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CLiveVideoTabActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
};

class CV302FileTabActionTrigger : public IActionTrigger
{
public:		
	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_MAIN_MENU;
		m_dvrCmd.parameter[1] = GUI_MAIN_MENU_TAB_THUMB;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CFileTabActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{		
	}
};


class CV302BackMainHmiActionTrigger:public IActionTrigger
{
public:
	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
        CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);       
		Layout_Event_Payload_T* tmp_payload = NULL;
		tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
		memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
		tmp_payload->header.msg_id = ALGO_RECORD_BUTTON;
		tmp_payload->body.onlyNotify = true;
		m_eventDel.PostEventPayload(tmp_payload);	
		SAFE_FREE(tmp_payload);
        Log_Message("-----------CBackMainHmiActionTrigger");
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
};
    
class CV302PlayQuitActionTrigger:public IActionTrigger
{
public:
	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_PLAYER_QUIT;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		Log_Message("-----------CV302PlayQuitActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
};

CSVV302DvrBase::CSVV302DvrBase():m_avmViewLastStatus(0)
{
	memset(m_trigger, 0, V302_DVR_BASE_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, V302_DVR_BASE_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 1, V302_DVR_BASE_ELEMEMT_NUM * sizeof(unsigned char));

	m_dvrRecordTab = NULL;
	m_dvrPlaybackTab = NULL;
	m_dvrFileListTab = NULL;
    m_dvrPlayImageTab = NULL;

	m_dvrRecordTab = new CSVV302RecordTab(m_uiNode, m_uiNodeId);
	m_dvrPlaybackTab = new CSVV302PlaybackTab(m_uiNode, m_uiNodeId);
	m_dvrFileListTab = new CSVV302FileListTab(m_uiNode, m_uiNodeId);
    m_dvrPlayImageTab = new CSVV302PlayImageTab(m_uiNode, m_uiNodeId);

	m_dvrRecordTabVisibility = 0;
	m_dvrPlaybackTabVisibility = 0;
	m_dvrFileListVisibility = 0;
    m_dvrPlayImageTabVisibility = 0;
	
}

CSVV302DvrBase::~CSVV302DvrBase()
{
	SAFE_DELETE(m_dvrRecordTab);
	SAFE_DELETE(m_dvrPlaybackTab);
	SAFE_DELETE(m_dvrFileListTab);
    SAFE_DELETE(m_dvrPlayImageTab);

    int i = V302_DVR_BASE_BKG;
    SAFE_DELETE(m_trigger[i]);
    SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
    SAFE_DELETE(m_baseButton[i]);

    i = V302_DVR_BASE_RET;
    SAFE_DELETE(m_trigger[i]);
    SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
    SAFE_DELETE(m_baseButton[i]);

	for(int i = V302_DVR_BASE_REC_TAB; i < V302_DVR_BASE_ELEMEMT_NUM; i++)
	{
	    SAFE_DELETE(m_trigger[i]);
	    SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
		SAFE_DELETE(m_baseButton[i]);
	}
	
}

	
int CSVV302DvrBase::SetHmiParams()
{
    int i = 0;
    
    i = V302_DVR_BASE_BKG;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/dvr_base_bkg0.dds",XR_RES); 
    m_trigger[i] = NULL;

    i = V302_DVR_BASE_RET;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
    m_baseButtonData[i].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
    m_baseButtonData[i].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/dvr_close_g.dds",XR_RES); 
    sprintf(m_baseButtonData[i].icon_file_name[1],"%sS302/dvr_close_h.dds",XR_RES); 
    m_trigger[i] = new CV302BackMainHmiActionTrigger;


    i = V302_DVR_BASE_REC_TAB;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
    m_baseButtonData[i].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/rec_tab_g.dds",XR_RES); 
    sprintf(m_baseButtonData[i].icon_file_name[1],"%sS302/rec_tab_h.dds",XR_RES); 
    m_trigger[i] = new CV302RecTabActionTrigger;

    i = V302_DVR_BASE_PLAYBACK_TAB;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
    m_baseButtonData[i].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/play_tab_g.dds",XR_RES); 
    sprintf(m_baseButtonData[i].icon_file_name[1],"%sS302/play_tab_h.dds",XR_RES); 
    m_trigger[i] = new CV302PlayQuitActionTrigger;

    i = V302_DVR_BASE_THUMB_TAB;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
    m_baseButtonData[i].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/file_tab_g.dds",XR_RES); 
    sprintf(m_baseButtonData[i].icon_file_name[1],"%sS302/file_tab_h.dds",XR_RES); 
    m_trigger[i] = new CV302FileTabActionTrigger;

	for(int i = V302_DVR_BASE_BKG; i < V302_DVR_BASE_ELEMEMT_NUM; i++)
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
int CSVV302DvrBase::Init(int window_width, int window_height)
{
	m_windowWidth = window_width;
	m_windowHeight = window_height;

	if(m_dvrRecordTab)
	{
		m_dvrRecordTab->Init(m_windowWidth, m_windowHeight);
	}
	if(m_dvrPlaybackTab)
	{
		m_dvrPlaybackTab->Init(m_windowWidth, m_windowHeight);
	}
	if(m_dvrFileListTab)
	{
		m_dvrFileListTab->Init(m_windowWidth, m_windowHeight);
	}
    if(m_dvrPlayImageTab)
	{
		m_dvrPlayImageTab->Init(m_windowWidth, m_windowHeight);
	}
    
	float radio = 227.0/1280.0;
    
    int i = 0;

    i = V302_DVR_BASE_BKG;
	m_buttonPos[i][BUTTON_POS_X] = window_width - 100;
	m_buttonPos[i][BUTTON_POS_Y] = 80.0;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 100;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 200;

    i = V302_DVR_BASE_RET;
	m_buttonPos[i][BUTTON_POS_X] = window_width - 100;
	m_buttonPos[i][BUTTON_POS_Y] = 80.0 + 44.0 * 0;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 44;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 44;
    
    i = V302_DVR_BASE_REC_TAB;
	m_buttonPos[i][BUTTON_POS_X] = window_width - 100;
	m_buttonPos[i][BUTTON_POS_Y] = 80.0 + 44.0 * 1;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 44;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 44;
		
    i = V302_DVR_BASE_PLAYBACK_TAB;
	m_buttonPos[i][BUTTON_POS_X] = window_width - 100;
	m_buttonPos[i][BUTTON_POS_Y] = 80.0 + 44.0 * 2;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 44;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 44;

    i = V302_DVR_BASE_THUMB_TAB;
	m_buttonPos[i][BUTTON_POS_X] = window_width - 100;
	m_buttonPos[i][BUTTON_POS_Y] = 80.0 + 44.0 * 3;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 44;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 44;

	SetHmiParams();

    CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(m_avmViewLastStatus);	

	return HMI_SUCCESS;
}
int CSVV302DvrBase::Update(Hmi_Message_T& hmiMsg)
{
    //模拟DVRdata
    //SetDvrStatus();
    
	DVR_GUI_LAYOUT_INST_EXT dvrGuiLayout;
	CAvmRenderDataBase::GetInstance()->GetDvrData(&dvrGuiLayout);

#if 0    
    DVR_GUI_LAYOUT_INST dvrGuiLayout0;
    if(0 == Dvr_App_Get_GuiLayOut(&dvrGuiLayout0)) dvrGuiLayout.curLayout = (DVR_GUI_LAYOUT_TYPE_EXT)dvrGuiLayout0.curLayout;
    CAvmRenderDataBase::GetInstance()->SetDvrData(&dvrGuiLayout);
#endif

    m_buttonStatus[V302_DVR_BASE_BKG] = BUTTON_OFF_IMAGE;
    m_buttonStatus[V302_DVR_BASE_RET] = BUTTON_OFF_IMAGE;
    m_buttonStatus[V302_DVR_BASE_THUMB_TAB] = BUTTON_OFF_IMAGE;
    m_buttonStatus[V302_DVR_BASE_PLAYBACK_TAB] = BUTTON_OFF_IMAGE;
    m_buttonStatus[V302_DVR_BASE_REC_TAB] = BUTTON_OFF_IMAGE;
    
//    Log_Error("=====================curLayout = %d",dvrGuiLayout.curLayout);
    switch(dvrGuiLayout.curLayout)
    {
      case GUI_LAYOUT_SETUP_EXT:
        break;
      case GUI_LAYOUT_RECORD_EXT:
        m_buttonStatus[V302_DVR_BASE_REC_TAB] = BUTTON_ON_IMAGE;
        if(dvrGuiLayout.pTable)
        {
            if(m_dvrRecordTab)
            {
                m_dvrRecordTab->Update(m_hmiMsg);
            }
        }
        m_dvrRecordTabVisibility = 1;
        m_dvrPlaybackTabVisibility = 0;
        m_dvrFileListVisibility = 0;
        m_dvrPlayImageTabVisibility = 0;

        break;
      case GUI_LAYOUT_THUMB_EXT:
        
        m_buttonStatus[V302_DVR_BASE_THUMB_TAB] = BUTTON_ON_IMAGE;
        if(dvrGuiLayout.pTable)
        {				
            if(m_dvrFileListTab)
            {
                m_dvrFileListTab->Update(m_hmiMsg);
            }
        }
        m_dvrRecordTabVisibility = 0;
        m_dvrPlaybackTabVisibility = 0;
        m_dvrFileListVisibility = 1;
        m_dvrPlayImageTabVisibility = 0;
        
        break;
      case GUI_LAYOUT_PLAYBACK_VIDEO_EXT:
        m_buttonStatus[V302_DVR_BASE_PLAYBACK_TAB] = BUTTON_ON_IMAGE;
        if(dvrGuiLayout.pTable)
        {				
            if(m_dvrPlaybackTab)
            {
                m_dvrPlaybackTab->Update(m_hmiMsg);
            }
        }
        m_dvrRecordTabVisibility = 0;
        m_dvrPlaybackTabVisibility = 1;
        m_dvrFileListVisibility = 0;
        m_dvrPlayImageTabVisibility = 0;
        
        break;
      case GUI_LAYOUT_PLAYBACK_IMAGE_EXT:
        if(dvrGuiLayout.pTable)
        {				
            if(m_dvrPlaybackTab)
            {
                m_dvrPlayImageTab->Update(m_hmiMsg);
            }
        }
        m_dvrRecordTabVisibility = 0;
        m_dvrPlaybackTabVisibility = 0;
        m_dvrFileListVisibility = 0;
        m_dvrPlayImageTabVisibility = 1;
               
        break;
      default:
        m_dvrRecordTabVisibility = 0;
        m_dvrPlaybackTabVisibility = 0;
        m_dvrFileListVisibility = 0;
        m_dvrPlayImageTabVisibility = 0;

        break;
    }
  
    RefreshHmi();

    return HMI_SUCCESS;
}

int CSVV302DvrBase::RefreshHmi()
{
	for(int i = V302_DVR_BASE_BKG; i < V302_DVR_BASE_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}

	Hmi_Message_T  hmiMsg;	
    
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

    if (m_dvrPlayImageTab)
    {
        m_dvrPlayImageTab->SetElementsVisibility(m_dvrPlayImageTabVisibility);
    }

    return HMI_SUCCESS;
}

int CSVV302DvrBase::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVV302DvrBase::DestroyHmiElems()
{
	return HMI_SUCCESS;
}

int CSVV302DvrBase::SetDvrStatus()
{

    GUI_OBJ_THUMB_FRAME_INST_EXT* tmpInst0 = NULL;
    GUI_OBJ_THUMB_PAGENUM_INST_EXT* tmpPageInst0 = NULL;
    DVR_GRAPHIC_UIOBJ* fileListTabMsg = NULL;

    GUI_OBJ_PLAY_FILENAME_INST_EXT* pbFilenameInst0 = NULL;
    GUI_OBJ_PLAY_TIME_INST_EXT* pbPlayTimeInst0 = NULL;
    
    static DVR_GUI_LAYOUT_INST dvrGuiLayout0;
    if(0 == Dvr_App_Get_GuiLayOut(&dvrGuiLayout0))
    {
        if(dvrGuiLayout0.pTable)
        {
            fileListTabMsg = (DVR_GRAPHIC_UIOBJ*) dvrGuiLayout0.pTable;
            for(int i = 0; i < dvrGuiLayout0.ObjNum; i++)
            {
                switch(fileListTabMsg[i].Id)
                {
                  case GUI_OBJ_ID_THUMB_FRAME:
                    if(GUI_OBJ_STATUS_TYPE_POINTER == fileListTabMsg[i].status_type && fileListTabMsg[i].uStatus.ptr)
                    {
                        tmpInst0 = (GUI_OBJ_THUMB_FRAME_INST_EXT*)fileListTabMsg[i].uStatus.ptr;
                    }                        
                    break;
                    
                  case GUI_OBJ_ID_THUMB_PAGE_NUM:
                    if(GUI_OBJ_STATUS_TYPE_POINTER == fileListTabMsg[i].status_type && fileListTabMsg[i].uStatus.ptr)
                    {
                        tmpPageInst0 = (GUI_OBJ_THUMB_PAGENUM_INST_EXT*)fileListTabMsg[i].uStatus.ptr;
                    } 
                    break;
                    
                  case GUI_OBJ_ID_PB_FILENAME:
                    if(GUI_OBJ_STATUS_TYPE_POINTER == fileListTabMsg[i].status_type && fileListTabMsg[i].uStatus.ptr)
                    {
                        pbFilenameInst0 = (GUI_OBJ_PLAY_FILENAME_INST_EXT*)fileListTabMsg[i].uStatus.ptr;
                    }                    
                    break;
                    
                  case GUI_OBJ_ID_PB_PLAY_TIMER:
                    if(GUI_OBJ_STATUS_TYPE_POINTER == fileListTabMsg[i].status_type && fileListTabMsg[i].uStatus.ptr)
                    {
                        pbPlayTimeInst0 = (GUI_OBJ_PLAY_TIME_INST_EXT*)fileListTabMsg[i].uStatus.ptr;
                        //Log_Error("------PB_PLAY_TIMER: %d, pos: %d", pbPlayTimeInst0->duration, pbPlayTimeInst0->position);
                    }
                    break;
                    
                  default:
                    break;
                }
            }
        }
    }
    
    unsigned char m_tmpRGB[304 * 176 * 3];
    memset(&m_tmpRGB, 220, 304 * 176 * 3);
    GUI_OBJ_THUMB_FRAME_INST_EXT tmpInst;
    GUI_OBJ_THUMB_ITEM_EXT tmp = {"1234213424", m_tmpRGB, 304, 176, 1, 1};
    //GUI_OBJ_THUMB_ITEM_EXT tmp = {0, 0, 0, 0, 0, 0};
    tmpInst.item[0] = tmp;
    tmpInst.item[1] = tmp;
    tmpInst.item[2] = tmp;
    tmpInst.item[3] = tmp;
    tmpInst.item[4] = tmp;
    tmpInst.item[5] = tmp;
    tmpInst.item[6] = tmp;
    tmpInst.item[7] = tmp;


    GUI_OBJ_THUMB_PAGENUM_INST_EXT tmpPageInst;
    tmpPageInst.nCurPage = 0;
    tmpPageInst.nTotalPage = 0;

    GUI_OBJ_REC_CAN_MSG_EXT    tmpCanMsg;
    tmpCanMsg.Brake = 1;
    tmpCanMsg.Buckle = 0;
    tmpCanMsg.Engine = 1;
    tmpCanMsg.Gear = 1;
    tmpCanMsg.TurnLeft = 1;
    tmpCanMsg.TurnRight = 0;

    tmpCanMsg.GpsLat = 1290445;
    tmpCanMsg.GpsLng = 691204;    
    
    tmpCanMsg.TimeYear = 2018;
    tmpCanMsg.TimeMon = 5;
    tmpCanMsg.TimeDay = 11;
    tmpCanMsg.TimeHour = 21;
    tmpCanMsg.TimeMin = 5;
    tmpCanMsg.TimeSec = 30;
    tmpCanMsg.Speed = 26;

    DVR_GRAPHIC_UIOBJ_EXT table[] = {
        {GUI_OBJ_ID_THUMB_FRAME_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_PAGE_NUM_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpPageInst},
        {GUI_OBJ_ID_REC_VIEW_INDEX_EXT,"asdfasdg",1,1,GUI_OBJ_STATUS_TYPE_U32_EXT,GUI_VIEW_INDEX_LEFT_EXT},
        {GUI_OBJ_ID_REC_CAN_MSG_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpCanMsg},
        {GUI_OBJ_ID_PB_VIEW_INDEX_EXT,"asdfasdg",1,1,GUI_OBJ_STATUS_TYPE_U32_EXT,GUI_VIEW_INDEX_FRONT_EXT},
        {GUI_OBJ_ID_PB_CAN_MSG_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpCanMsg},
        {GUI_OBJ_ID_PB_PLAY_TIMER_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)pbPlayTimeInst0},
        {GUI_OBJ_ID_PB_FILENAME_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)pbFilenameInst0},
    };

    DVR_GUI_LAYOUT_INST_EXT dvrData;
    dvrData.curLayout = GUI_LAYOUT_RECORD_EXT;
    dvrData.ObjNum = 13;
    for(int i = 0; i < dvrData.ObjNum; i++)
    {
    dvrData.pTable = table;
    }

    CAvmRenderDataBase::GetInstance()->SetDvrData(&dvrData);
	
    return HMI_SUCCESS;
    
      
    
}
