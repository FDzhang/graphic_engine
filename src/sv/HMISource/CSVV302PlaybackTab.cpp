#include "CSVV302PlaybackTab.h"
#include "DVR_GUI_OBJ.h"
#include "gpu_log.h"

unsigned int V302ProcessBarWidth;
unsigned int V302ProcessBarTotalTime;

class CV302PbSetPosActionTrigger : public IActionTrigger
{
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
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_PLAYER_SEEK;
		m_dvrCmd.parameter[1] = 1000 * x * V302ProcessBarTotalTime / V302ProcessBarWidth;
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));

//        Log_Message("-----------CV302PbSetPosActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {
    }
};
CSVV302PlaybackTab::CSVV302PlaybackTab(IUINode* pUiNode, int pUiNodeId)
{
    m_currentSvresNum = 0;
	memset(m_buttonStatus, 0, V302_PB_INDEX_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 0, V302_PB_INDEX_NUM * sizeof(unsigned char));   
    m_processBarVisibility = 0;
	m_processBarForwardScale = 0;
}

CSVV302PlaybackTab::~CSVV302PlaybackTab()
{
    for (int i = 0; i < m_currentSvresNum; i++)
    {
        SAFE_DELETE(m_hmiSvresFileName[i]);
    }
    SAFE_DELETE(m_baseButton[V302_PB_INDEX_BG_IMAGE]);
    for (int i = V302_PB_INDEX_STBAR_BK; i <= V302_PB_INDEX_STABR_ENGINE; i++)
    {
        SAFE_DELETE(m_baseButton[i]);
    }
    SAFE_DELETE(m_processBarData.iconFileName[PROCESS_BAR]);	
    SAFE_DELETE(m_processBarData.iconFileName[PROCESS_BAR_BACKGROUND]);
}

int CSVV302PlaybackTab::SetHmiParams()
{
    float scale = m_screenHeight / 1128.0;
    
    int index = V302_PB_INDEX_BG_IMAGE;
    
    m_baseButtonData[index].pos[0] = 0;
    m_baseButtonData[index].pos[1] = 0;
    m_baseButtonData[index].width = 960.0 * scale;
    m_baseButtonData[index].height = 1128.0 * scale;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[0];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    HmiInitSTBar();
    HmiInitPlayBar();

    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;
    HmiInitSvresList();
    SetHmiParams();
    HmiInitLayer();
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::Update(Hmi_Message_T &hmiMsg)
{
    DVR_GUI_LAYOUT_INST_EXT dvrData;
	CAvmRenderDataBase::GetInstance()->GetDvrData(&dvrData);

	DVR_GRAPHIC_UIOBJ_EXT* playbackTabMsg = NULL;
    GUI_OBJ_PLAY_FILENAME_INST_EXT* playbackFileName = NULL;
    GUI_OBJ_PLAY_TIME_INST_EXT* playbackTimeInfo = NULL;

	playbackTabMsg = dvrData.pTable;
    
    if(dvrData.curLayout == GUI_LAYOUT_PLAYBACK_VIDEO_EXT)
    {
        for(int i = 0; i < dvrData.ObjNum; i++)
        {
            switch(playbackTabMsg[i].Id)
            {
              case  GUI_OBJ_ID_PB_VIEW_INDEX_EXT:
                SetDvrView(playbackTabMsg[i].uStatus.ObjVal);
                break;
              
              case  GUI_OBJ_ID_PB_VEHICLE_DATA_EXT:
                if(playbackTabMsg[i].status_type == GUI_OBJ_STATUS_TYPE_POINTER_EXT && playbackTabMsg[i].uStatus.ptr)
                {
                    SetStateBarVal(playbackTabMsg[i].uStatus.ptr);
                }
                break;
                
             case GUI_OBJ_ID_PB_FILENAME_EXT:
				if(GUI_OBJ_STATUS_TYPE_POINTER_EXT == playbackTabMsg[i].status_type && playbackTabMsg[i].uStatus.ptr)
				{
					playbackFileName = (GUI_OBJ_PLAY_FILENAME_INST_EXT*)playbackTabMsg[i].uStatus.ptr;
					sprintf(m_textEditData[V302_PB_FILENAME_TITLE].textContent[0],"%s",playbackFileName->filename);
				}
				break;

              case GUI_OBJ_ID_PB_PLAY_TIMER_EXT:
                if(GUI_OBJ_STATUS_TYPE_POINTER_EXT == playbackTabMsg[i].status_type && playbackTabMsg[i].uStatus.ptr)
                {
                    playbackTimeInfo = (GUI_OBJ_PLAY_TIME_INST_EXT*)playbackTabMsg[i].uStatus.ptr;
					ToString(playbackTimeInfo->duration, &m_textEditData[V302_PB_DURATION_TIME].textContent[0]);
					ToString(playbackTimeInfo->position, &m_textEditData[V302_PB_CURRENT_TIME].textContent[0]);
                    m_processBarForwardScale = ((float)playbackTimeInfo->position / (float)playbackTimeInfo->duration);
                }
                break;
                
              default:
                break;
            }
        }
    }
    RefreshHmi();
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::RefreshHmi()
{	
    for(int i = V302_PB_INDEX_BG_IMAGE; i < V302_PB_INDEX_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
    for(int i = V302_PB_TIME_TEXT; i < V302_PB_TEXT_NUM; i++)
    {
        m_textEdit[i]->Update(m_textEditData[i].textContent[0]);
    }
    
	m_processBar->Move(m_processBarForwardScale, PROCESS_BAR_FORWARD);
	m_processBar->SetVisibility(m_processBarVisibility);
	m_processBar->Update();

    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::SetElementsVisibility(unsigned char pFlag)
{
//    m_baseButton[V302_PB_INDEX_BG_IMAGE]->SetVisibility(pFlag);
    for (int i = V302_PB_INDEX_BG_IMAGE; i <= V302_PB_INDEX_STABR_ENGINE; i++)
    {
        m_baseButton[i]->SetVisibility(pFlag);
    }
    for (int i = V302_PB_TIME_TEXT; i < V302_PB_TEXT_NUM; i++)
    {
        m_textEdit[i]->SetVisibility(pFlag);
    }
    m_processBarVisibility = pFlag;
    m_processBar -> SetVisibility(pFlag);
    
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::ReturnHmiMsg(Hmi_Message_T *hmi_msg)
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::DestroyHmiElems()
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::HmiInitSTBar()
{
    float scale = m_screenHeight / 1128.0;

    int svresIndex = 1;
    int index = V302_PB_INDEX_STBAR_BK;
    m_baseButtonData[index].pos[0] = 0.0 * scale;
    m_baseButtonData[index].pos[1] = 0.0 * scale;
    m_baseButtonData[index].width = 960.0 * scale;
    m_baseButtonData[index].height = 70.0 * scale;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_PB_INDEX_STABR_SPEED;
    m_baseButtonData[index].pos[0] = 600.0 * scale;
    m_baseButtonData[index].pos[1] = 30.0 * scale;
    m_baseButtonData[index].width = 108.0 * scale;
    m_baseButtonData[index].height = 36.0 * scale;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].icon_file_name[1] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;    
    
    for (int index = V302_PB_INDEX_STABR_GEAR; index <= V302_PB_INDEX_STABR_ENGINE; index++)
    {
        m_baseButtonData[index].pos[0] = (708.0 + (index - V302_PB_INDEX_STABR_GEAR) * 40.0) * scale;
        m_baseButtonData[index].pos[1] = 30.0 * scale;
        m_baseButtonData[index].width = 36.0 * scale;
        m_baseButtonData[index].height = 36.0 * scale;
        m_baseButtonData[index].delegate_func = NULL;
        m_baseButtonData[index].trigger = NULL;
        m_baseButtonData[index].icon_type = STATIC_ICON;
        m_baseButtonData[index].show_flag = 1;
        m_baseButtonData[index].show_icon_num = 0;
        m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[svresIndex++];
        m_baseButtonData[index].icon_file_name[1] = m_hmiSvresFileName[svresIndex++];
        m_baseButtonData[index].animationStyle = BUTTON_NOMAL;
    }
    
    InitTimeGps();
}

int CSVV302PlaybackTab::HmiInitPlayBar()
{
    float scale = m_screenHeight / 1128.0;
    
    m_processBarData.width = 550.0 * scale;
    m_processBarData.height = 6.0 * scale;
    m_processBarData.pos[0] = 130.0 * scale;
    m_processBarData.pos[1] = 1090.0 * scale;
    m_processBarData.withBkgFlag = 1;
    m_processBarData.withBarIconFlag = 0;
    V302ProcessBarWidth = m_processBarData.width;
    m_processBarData.iconFileName[PROCESS_BAR] = new char[100];
    sprintf(m_processBarData.iconFileName[PROCESS_BAR], "%sCar/DVR/pb_processbar.dds", XR_RES);
    m_processBarData.iconFileName[PROCESS_BAR_BACKGROUND] = new char[100];
    sprintf(m_processBarData.iconFileName[PROCESS_BAR_BACKGROUND], "%sCar/DVR/pb_processbar_bkg.dds", XR_RES);
    m_processBarData.trigger = new CV302PbSetPosActionTrigger;

    int i = V302_PB_FILENAME_TITLE;
    m_textEditData[i].width = 18;
    m_textEditData[i].pos[0] = 250.0 * scale;
    m_textEditData[i].pos[1] = 1050.0 * scale;
    m_textEditData[i].font_size = 4.0;
    m_textEditData[i].line_num = 1;
    m_textEditData[i].targetIndex = -1;
    m_textEditData[i].insertFlag = InsertFlag_Default;
    m_textEditData[i].trigger = NULL;
    m_textEditData[i].textColor[0] = 1.0;
    m_textEditData[i].textColor[1] = 1.0;
    m_textEditData[i].textColor[2] = 1.0;

    m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
    m_textEditData[i].textContent[0] = new char[100];
    m_textEditContent[i] = "17:30-17:40 16/12/12";
    sprintf(m_textEditData[i].textContent[0], "%s", m_textEditContent[i]);

    i = V302_PB_CURRENT_TIME;
    m_textEditData[i].width = 18;
    m_textEditData[i].pos[0] = 130.0 * scale;
    m_textEditData[i].pos[1] = 1050.0 * scale;
    m_textEditData[i].font_size = 3.0;
    m_textEditData[i].line_num = 1;
    m_textEditData[i].targetIndex = -1;
    m_textEditData[i].insertFlag = InsertFlag_Default;
    m_textEditData[i].trigger = NULL;
    m_textEditData[i].textColor[0] = 1.0;
    m_textEditData[i].textColor[1] = 1.0;
    m_textEditData[i].textColor[2] = 1.0;

    m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
    m_textEditData[i].textContent[0] = new char[100];
    m_textEditContent[i] = "00 : 30";
    sprintf(m_textEditData[i].textContent[0], "%s", m_textEditContent[i]);

    i = V302_PB_DURATION_TIME;
    m_textEditData[i].width = 18;
    m_textEditData[i].pos[0] = 630.0 * scale;
    m_textEditData[i].pos[1] = 1050.0 * scale;
    m_textEditData[i].font_size = 3.0;
    m_textEditData[i].line_num = 1;
    m_textEditData[i].targetIndex = -1;
    m_textEditData[i].insertFlag = InsertFlag_Default;
    m_textEditData[i].trigger = NULL;
    m_textEditData[i].textColor[0] = 1.0;
    m_textEditData[i].textColor[1] = 1.0;
    m_textEditData[i].textColor[2] = 1.0;

    m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
    m_textEditData[i].textContent[0] = new char[100];
    m_textEditContent[i] = "02 : 00";
    sprintf(m_textEditData[i].textContent[0], "%s", m_textEditContent[i]);
}

int CSVV302PlaybackTab::HmiInitLayer()
{
    for (int index = V302_PB_INDEX_BG_IMAGE; index < V302_PB_INDEX_NUM; index++)
    {
        m_baseButton[index] = new HMIButton(&(m_baseButtonData[index]), m_uiNode);
        m_baseButton[index]->SetVisibility(0);
    }
    
    m_processBar = new HmiProcessBar(&m_processBarData, m_uiNode);
    m_processBar->SetVisibility(0);
    
    for (int index = V302_PB_TIME_TEXT; index < V302_PB_TEXT_NUM; index++)
    {
        m_textEdit[index] = new HmiTextEdit(&(m_textEditData[index]), m_uiNode);
        m_textEdit[index]->SetVisibility(0);
    }
}

int CSVV302PlaybackTab::HmiInitSvresList()
{
    int index = 0;
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/playback_bk.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_bk.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_speed_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_speed_g.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_brake_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_brake_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_buckle_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_buckle_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnleft_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnleft_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnright_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnright_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_engine_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_engine_r.dds", XR_RES);
    m_currentSvresNum = index;

}

char *CSVV302PlaybackTab::HmiGetSvresFile(int index)
{
    return m_hmiSvresFileName[index];
}

int CSVV302PlaybackTab::ToString(int pTime, char **pOutString)
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

    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::SetDvrView(unsigned char pViewCmd)
{
//    Log_Error("====================SetDvrView = %d",pViewCmd);
	if(pViewCmd == GUI_VIEW_INDEX_FRONT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(FRONT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_REAR_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(REAR_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_LEFT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(LEFT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_RIGHT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(RIGHT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_MATTS_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(MATTS_VIEW);
	}

	return HMI_SUCCESS;
}

int CSVV302PlaybackTab::SetStateBarVal(void *ptr)
{
    GUI_OBJ_VEHICLE_DATA_INST_EXT *recCanMsg = NULL;
    recCanMsg = (GUI_OBJ_VEHICLE_DATA_INST_EXT*)ptr;
    if(recCanMsg == NULL) return HMI_SUCCESS;

#if 0    
    m_buttonStatus[S302_PLAYBACK_INDEX_STABR_GEAR] = recCanMsg->Gear;
    m_buttonStatus[S302_PLAYBACK_INDEX_STABR_BRAKE] = recCanMsg->Brake;
    m_buttonStatus[S302_PLAYBACK_INDEX_STABR_BUCKLE] = recCanMsg->Buckle;
    m_buttonStatus[S302_PLAYBACK_INDEX_STABR_TURNLEFT] = recCanMsg->TurnLeft;
    m_buttonStatus[S302_PLAYBACK_INDEX_STABR_TURNRIGHT] = recCanMsg->TurnRight;
    m_buttonStatus[S302_PLAYBACK_INDEX_STABR_ENGINE] = recCanMsg->Engine;
#endif

    sprintf(m_textEditData[V302_PB_TIME_TEXT].textContent[0],"%04d-%02d-%02d  %02d:%02d:%02d",recCanMsg->TimeYear,recCanMsg->TimeMon,recCanMsg->TimeDay,recCanMsg->TimeHour,recCanMsg->TimeMin,recCanMsg->TimeSec);

    sprintf(m_textEditData[V302_PB_GPS_TEXT].textContent[0],"N %03d.%02d'%02d\"  E %03d.%02d'%02d\"",recCanMsg->GpsLongitude / 10000,(recCanMsg->GpsLongitude % 10000) / 100,recCanMsg->GpsLongitude % 100,recCanMsg->GpsLatitude / 10000,(recCanMsg->GpsLatitude % 10000) / 100,recCanMsg->GpsLatitude % 100);
    
    sprintf(m_textEditData[V302_PB_SPEED_TEXT].textContent[0],"%03d",recCanMsg->VehicleSpeed);
    return HMI_SUCCESS;
}

int CSVV302PlaybackTab::InitTimeGps()
{
    float scale = m_screenHeight / 1128.0;

    int i = 0;

    i = V302_PB_TIME_TEXT;
    m_textEditData[i].pos[0] = 24.0 * scale;
    m_textEditData[i].pos[1] = 30.0 * scale;
    m_textEditData[i].width = 18;
	m_textEditData[i].font_size = 3.0;
	m_textEditData[i].line_num = 1;
	m_textEditData[i].visibilityStatus = 1;
	m_textEditData[i].targetIndex = -1;
	m_textEditData[i].insertFlag = InsertFlag_Default;
	m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
	m_textEditData[i].trigger = NULL;
	m_textEditData[i].textColor[0] = 0.9;
	m_textEditData[i].textColor[1] = 0.9;
	m_textEditData[i].textColor[2] = 0.9;
	m_textEditData[i].textContent[0] = new char[100];
	char* ptext0 = "2018-05-11  18:00:00";
	sprintf(m_textEditData[i].textContent[0],"%s", ptext0);

    i = V302_PB_GPS_TEXT;
    m_textEditData[i].pos[0] = 300.0 * scale;
    m_textEditData[i].pos[1] = 30.0 * scale;
    m_textEditData[i].width = 18;
	m_textEditData[i].font_size = 3.0;
	m_textEditData[i].line_num = 1;
	m_textEditData[i].visibilityStatus = 1;
	m_textEditData[i].targetIndex = -1;
	m_textEditData[i].insertFlag = InsertFlag_Default;
	m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
	m_textEditData[i].trigger = NULL;
	m_textEditData[i].textColor[0] = 0.9;
	m_textEditData[i].textColor[1] = 0.9;
	m_textEditData[i].textColor[2] = 0.9;
	m_textEditData[i].textContent[0] = new char[100];
	char* ptext1 = "N 00.00'00\"  E 00.00'00\"";
	sprintf(m_textEditData[i].textContent[0],"%s", ptext1);

    i = V302_PB_SPEED_TEXT;
    m_textEditData[i].pos[0] = 610.0 * scale;
    m_textEditData[i].pos[1] = 30.0 * scale;
    m_textEditData[i].width = 18;
	m_textEditData[i].font_size = 3.0;
	m_textEditData[i].line_num = 1;
	m_textEditData[i].visibilityStatus = 1;
	m_textEditData[i].targetIndex = -1;
	m_textEditData[i].insertFlag = InsertFlag_Default;
	m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
	m_textEditData[i].trigger = NULL;
	m_textEditData[i].textColor[0] = 0.9;
	m_textEditData[i].textColor[1] = 0.9;
	m_textEditData[i].textColor[2] = 0.9;
	m_textEditData[i].textContent[0] = new char[100];
	char* ptext2 = "025";
	sprintf(m_textEditData[i].textContent[0],"%s", ptext2);
    
    return HMI_SUCCESS;
}


