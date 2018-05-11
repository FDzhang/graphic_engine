#include "CSVS302DvrBase.h"
#include "CSVHmiIntent.h"
#include "CSVDvrFileListHmi.h"
#include "CSVS302RecordTab.h"


#include "DVR_GUI_OBJ.h"
#include "gpu_log.h"


REGISTER_HMI_CLASS(CSVS302DvrBase);


class CS302RecTabActionTrigger : public IActionTrigger
{

	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CLiveVideoTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
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

class CS302FileTabActionTrigger : public IActionTrigger
{

	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CFileTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
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


class CS302BackMainHmiActionTrigger:public IActionTrigger
{
	//ACTION_TRIGGER_EVENT_CONSTRUCTION(CBackMainHmiActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
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


CSVS302DvrBase::CSVS302DvrBase():m_avmViewLastStatus(0)
{
	memset(m_trigger, 0, S302_DVR_BASE_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, S302_DVR_BASE_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 1, S302_DVR_BASE_ELEMEMT_NUM * sizeof(unsigned char));

	m_dvrRecordTab = NULL;
	m_dvrPlaybackTab = NULL;
	m_dvrFileListTab = NULL;
    m_dvrPlayImageTab = NULL;

	m_dvrRecordTab = new CSVS302RecordTab(m_uiNode, m_uiNodeId);
//	m_dvrPlaybackTab = new CSVDvrPlaybackTab(m_uiNode, m_uiNodeId);
	m_dvrFileListTab = new CSVDvrFileListHmi(m_uiNode, m_uiNodeId);
//    m_dvrPlayImageTab = new CSVDvrPlayImageTab(m_uiNode, m_uiNodeId);

	m_dvrRecordTabVisibility = 0;
	m_dvrPlaybackTabVisibility = 0;
	m_dvrFileListVisibility = 0;
    m_dvrPlayImageTabVisibility = 0;
	
}

CSVS302DvrBase::~CSVS302DvrBase()
{
	SAFE_DELETE(m_dvrRecordTab);
	SAFE_DELETE(m_dvrPlaybackTab);
	SAFE_DELETE(m_dvrFileListTab);
    SAFE_DELETE(m_dvrPlayImageTab);

    int i = S302_DVR_BASE_BKG;
    SAFE_DELETE(m_trigger[i]);
    SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
    SAFE_DELETE(m_baseButton[i]);

    i = S302_DVR_BASE_RET;
    SAFE_DELETE(m_trigger[i]);
    SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
    SAFE_DELETE(m_baseButton[i]);

	for(int i = S302_DVR_BASE_REC_TAB; i < S302_DVR_BASE_ELEMEMT_NUM; i++)
	{
	    SAFE_DELETE(m_trigger[i]);
	    SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
		SAFE_DELETE(m_baseButton[i]);
	}
	
}

	
int CSVS302DvrBase::SetHmiParams()
{
    int i = 0;
    
    i = S302_DVR_BASE_BKG;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/dvr_base_bkg0.dds",XR_RES); 
    m_trigger[i] = NULL;

    i = S302_DVR_BASE_RET;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/dvr_base_ret.dds",XR_RES); 
    m_trigger[i] = new CS302BackMainHmiActionTrigger;


    i = S302_DVR_BASE_REC_TAB;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
    m_baseButtonData[i].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/dvr_base_tab_nm.dds",XR_RES); 
    sprintf(m_baseButtonData[i].icon_file_name[1],"%sS302/dvr_base_tab_hl.dds",XR_RES); 
    m_trigger[i] = new CS302RecTabActionTrigger;

    i = S302_DVR_BASE_PLAYBACK_TAB;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
    m_baseButtonData[i].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/dvr_base_tab_nm.dds",XR_RES); 
    sprintf(m_baseButtonData[i].icon_file_name[1],"%sS302/dvr_base_tab_hl.dds",XR_RES); 
    m_trigger[i] = NULL;

    i = S302_DVR_BASE_THUMB_TAB;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
    m_baseButtonData[i].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/dvr_base_tab_nm.dds",XR_RES); 
    sprintf(m_baseButtonData[i].icon_file_name[1],"%sS302/dvr_base_tab_hl.dds",XR_RES); 
    m_trigger[i] = new CS302FileTabActionTrigger;

	for(int i = S302_DVR_BASE_BKG; i < S302_DVR_BASE_ELEMEMT_NUM; i++)
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
	return HMI_SUCCESS;
}
int CSVS302DvrBase::Init(int window_width, int window_height)
{
	m_windowWidth = window_width;
	m_windowHeight = window_height;

	float radio = 227.0/1280.0;
    
    int i = 0;

    i = S302_DVR_BASE_BKG;
	m_buttonPos[i][BUTTON_POS_X] = 0.0;
	m_buttonPos[i][BUTTON_POS_Y] = 0.0;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 200;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = m_windowHeight;

    i = S302_DVR_BASE_RET;
	m_buttonPos[i][BUTTON_POS_X] = 23.0;
	m_buttonPos[i][BUTTON_POS_Y] = 100.0;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 47;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 45;
    
    i = S302_DVR_BASE_REC_TAB;
	m_buttonPos[i][BUTTON_POS_X] = 20.0;
	m_buttonPos[i][BUTTON_POS_Y] = 200.0;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 54;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 54;
		
    i = S302_DVR_BASE_PLAYBACK_TAB;
	m_buttonPos[i][BUTTON_POS_X] = 20.0;
	m_buttonPos[i][BUTTON_POS_Y] = 254.0;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 54;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 54;

    i = S302_DVR_BASE_THUMB_TAB;
	m_buttonPos[i][BUTTON_POS_X] = 20.0;
	m_buttonPos[i][BUTTON_POS_Y] = 308.0;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 54;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 54;


	SetHmiParams();

    CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(m_avmViewLastStatus);	

	return HMI_SUCCESS;
}
int CSVS302DvrBase::Update(Hmi_Message_T& hmiMsg)
{
 //   static DVR_GUI_LAYOUT_INST dvrGuiLayout;
    
	DVR_GUI_LAYOUT_INST_EXT dvrGuiLayout;
	CAvmRenderDataBase::GetInstance()->GetDvrData(&dvrGuiLayout);
    
    m_buttonStatus[S302_DVR_BASE_BKG] = BUTTON_OFF_IMAGE;
    m_buttonStatus[S302_DVR_BASE_RET] = BUTTON_OFF_IMAGE;
    m_buttonStatus[S302_DVR_BASE_THUMB_TAB] = BUTTON_OFF_IMAGE;
    m_buttonStatus[S302_DVR_BASE_PLAYBACK_TAB] = BUTTON_OFF_IMAGE;
    m_buttonStatus[S302_DVR_BASE_REC_TAB] = BUTTON_OFF_IMAGE;        
    switch(dvrGuiLayout.curLayout)
    {
      case GUI_LAYOUT_SETUP_EXT:
        break;
      case GUI_LAYOUT_RECORD_EXT:
        m_buttonStatus[S302_DVR_BASE_REC_TAB] = BUTTON_ON_IMAGE;
        if(dvrGuiLayout.pTable)
        {				
//            m_hmiMsg.dvrTabMsg.tabMsgTable = (void *)dvrGuiLayout.pTable;
//            m_hmiMsg.dvrTabMsg.objNum = dvrGuiLayout.ObjNum;
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
        //SetDvrStatus();
        m_buttonStatus[S302_DVR_BASE_THUMB_TAB] = BUTTON_ON_IMAGE;
        if(dvrGuiLayout.pTable)
        {				
//            m_hmiMsg.dvrTabMsg.tabMsgTable = (void *)dvrGuiLayout.pTable;
//            m_hmiMsg.dvrTabMsg.objNum = dvrGuiLayout.ObjNum;

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
        m_buttonStatus[S302_DVR_BASE_PLAYBACK_TAB] = BUTTON_ON_IMAGE;
        if(dvrGuiLayout.pTable)
        {				
//            m_hmiMsg.dvrTabMsg.tabMsgTable = (void *)dvrGuiLayout.pTable;
//            m_hmiMsg.dvrTabMsg.objNum = dvrGuiLayout.ObjNum;

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
        break;
      default:
        m_dvrRecordTabVisibility = 0;
        m_dvrPlaybackTabVisibility = 0;
        m_dvrFileListVisibility = 0;
        m_dvrPlayImageTabVisibility = 0;

        break;
    }
  
    RefreshHmi();
    
    MainMenuDataT mainMenuData;
	memset(&mainMenuData, 0, sizeof(MainMenuDataT));

	CAvmRenderDataBase::GetInstance()->GetMainMenuStatus(&mainMenuData);

    if(mainMenuData.iconStatus[MAIN_MENU_DVR] == BUTTON_OFF_IMAGE)
    {
        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(m_avmViewLastStatus);
        char* hmiName;
		unsigned char currentVehicleTypeId;
		CAvmRenderDataBase::GetInstance()->GetVehicleTypeId(currentVehicleTypeId);

		switch(currentVehicleTypeId)
		{
		case CHANGAN_S302:
			hmiName = "CSVS302MainHmi";
			break;
		case CHANGAN_V302:
		    hmiName = "CSVV302MainHmi";
		    break;
		default:
			hmiName = "CSVDemoMainHmi";
		}
		
        CSVHmiIntent::GetInstance()->Intent(hmiName);                       
    }

    return HMI_SUCCESS;
}

int CSVS302DvrBase::RefreshHmi()
{
	for(int i = S302_DVR_BASE_BKG; i < S302_DVR_BASE_ELEMEMT_NUM; i++)
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

int CSVS302DvrBase::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVS302DvrBase::DestroyHmiElems()
{
	return HMI_SUCCESS;
}

int CSVS302DvrBase::SetDvrStatus()
{
    unsigned char m_tmpRGB[192 * 112 * 3];
    memset(&m_tmpRGB, 180, 192 * 112 * 3);

    GUI_OBJ_THUMB_ITEM_EXT tmp = {"1234213424", m_tmpRGB, 192, 112, 1, 1};
    GUI_OBJ_THUMB_FRAME_INST_EXT tmpInst;
    tmpInst.item[0] = tmp;
    tmpInst.item[1] = tmp;
    tmpInst.item[2] = tmp;
    tmpInst.item[3] = tmp;
    tmpInst.item[4] = tmp;
    tmpInst.item[5] = tmp;
    tmpInst.item[6] = tmp;
    tmpInst.item[7] = tmp;

    GUI_OBJ_THUMB_PAGENUM_INST_EXT tmpPageInst;

    tmpPageInst.nCurPage = 3;
    tmpPageInst.nTotalPage = 5;

    DVR_GRAPHIC_UIOBJ_EXT table[] = {
        {GUI_OBJ_ID_THUMB_FRAME_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
        {GUI_OBJ_ID_THUMB_PAGE_NUM_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpPageInst},
    };

    DVR_GUI_LAYOUT_INST_EXT dvrData;
    dvrData.curLayout = GUI_LAYOUT_THUMB_EXT;
    dvrData.ObjNum = 7;
    for(int i = 0; i < dvrData.ObjNum; i++)
    {
    dvrData.pTable = table;
    }

    CAvmRenderDataBase::GetInstance()->SetDvrData(&dvrData);
	
    return HMI_SUCCESS;
    
}