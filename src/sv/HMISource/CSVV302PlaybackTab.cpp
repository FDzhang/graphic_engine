#include "CSVV302PlaybackTab.h"
#include "DVR_GUI_OBJ.h"
#include "gpu_log.h"

unsigned int V302ProcessBarWidth;
unsigned int V302ProcessBarTotalTime;

class CV302PbSetPosActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CV302PbSetPosActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
        m_dvrCmd->parameter[0] = DVR_USER_CLICK_PLAYER_SEEK;
        m_dvrCmd->parameter[1] = 1000 * x * V302ProcessBarTotalTime / V302ProcessBarWidth;
//        Log_Error("time = %d",m_dvrCmd->parameter[1]);
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));
//        Log_Message("-----------CV302PbSetPosActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {
    }
};
CSVV302PlaybackTab::CSVV302PlaybackTab(IUINode* pUiNode, int pUiNodeId)
{
    m_currentSvresNum = 0;
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
}

int CSVV302PlaybackTab::SetHmiParams()
{
    int index = V302_PB_INDEX_BG_IMAGE;
    m_baseButtonData[index].pos[0] = 0;
    m_baseButtonData[index].pos[1] = 0;
    m_baseButtonData[index].width = m_screenHeight / 1130.0 * 960.0;
    m_baseButtonData[index].height = m_screenHeight;
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
    DVR_GRAPHIC_UIOBJ *playbackTabMsg = NULL;
    GUI_OBJ_PLAY_FILENAME_INST *playbackFileName = NULL;
    GUI_OBJ_PLAY_TIME_INST *playbackTimeInfo = NULL;

    if ((DVR_GRAPHIC_UIOBJ *)hmiMsg.dvrTabMsg.tabMsgTable)
    {
        playbackTabMsg = (DVR_GRAPHIC_UIOBJ *)hmiMsg.dvrTabMsg.tabMsgTable;
        for (int i = 0; i < hmiMsg.dvrTabMsg.objNum; i++)
        {
            switch (playbackTabMsg[i].Id)
            {
            case GUI_OBJ_ID_PB_PLAY_STATE:
                break;
            case GUI_OBJ_ID_PB_PLAY_SPEED:
                break;
            case GUI_OBJ_ID_PB_VIEW_INDEX:
                if (GUI_OBJ_STATUS_TYPE_U32 == playbackTabMsg[i].status_type)
                {
                    if (playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_FRONT)
                    {
                        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_FRONT_SINGLE_VIEW);
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_REAR)
                    {
                        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_REAR_SINGLE_VIEW);
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_LEFT)
                    {
                        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_LEFT_SINGLE_VIEW);
                    }
                    else if (playbackTabMsg[i].uStatus.ObjVal == GUI_VIEW_INDEX_RIGHT)
                    {
                        CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_RIGHT_SINGLE_VIEW);                    }
                }
                break;
            case GUI_OBJ_ID_PB_FILENAME:

                if (GUI_OBJ_STATUS_TYPE_POINTER == playbackTabMsg[i].status_type && playbackTabMsg[i].uStatus.ptr)
                {
                    playbackFileName = (GUI_OBJ_PLAY_FILENAME_INST *)playbackTabMsg[i].uStatus.ptr;
                    sprintf(m_textEditContent[V302_PB_FILENAME_TITLE], "%s", playbackFileName->filename);
                }
                break;
            case GUI_OBJ_ID_PB_DC_SWITCH:
                break;
            case GUI_OBJ_ID_PB_PLAY_TIMER:

                if (GUI_OBJ_STATUS_TYPE_POINTER == playbackTabMsg[i].status_type && playbackTabMsg[i].uStatus.ptr)
                {
                    playbackTimeInfo = (GUI_OBJ_PLAY_TIME_INST *)playbackTabMsg[i].uStatus.ptr;
                    //Log_Error("------PB_PLAY_TIMER: %d, pos: %d", playbackTimeInfo->duration, playbackTimeInfo->position);

                    ToString(playbackTimeInfo->duration, &m_textEditContent[V302_PB_FILE_DURATION_TIME]);
                    ToString(playbackTimeInfo->position, &m_textEditContent[V302_PB_FILE_CURRENT_TIME]);
                    V302ProcessBarTotalTime = playbackTimeInfo->duration;
                    m_processBarForwardScale = ((float)playbackTimeInfo->position / (float)playbackTimeInfo->duration);
                    //Log_Error("-------------------------duration = %d, position = %d----------------",playbackTimeInfo->duration,playbackTimeInfo->position);
                }
                break;
            case GUI_OBJ_ID_DIALOG:
                break;
            case GUI_OBJ_ID_WARNING:
                break;
            case GUI_OBJ_ID_SIDEBAR:
                break;
            case GUI_OBJ_ID_PB_MODE:
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
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlaybackTab::SetElementsVisibility(unsigned char pFlag)
{
    m_baseButton[V302_PB_INDEX_BG_IMAGE]->SetVisibility(pFlag);
    for (int i = V302_PB_INDEX_STBAR_BK; i <= V302_PB_INDEX_STABR_ENGINE; i++)
    {
        m_baseButton[i]->SetVisibility(pFlag);
    }
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
    float screenYscal = m_screenHeight / 1130.0;
    float screenXscal = screenYscal;
    int svresIndex = 1;
    int index = V302_PB_INDEX_STBAR_BK;
    m_baseButtonData[index].pos[0] = 560.0 * screenXscal;
    m_baseButtonData[index].pos[1] = 1.0;
    m_baseButtonData[index].width = 400.0 * screenXscal;
    m_baseButtonData[index].height = 50.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    for (int index = V302_PB_INDEX_STABR_SPEED; index <= V302_PB_INDEX_STABR_ENGINE; index++)
    {
        m_baseButtonData[index].pos[0] = (659.0 + (index - V302_PB_INDEX_STABR_SPEED) * 43.0) * screenXscal;
        m_baseButtonData[index].pos[1] = 2.0;
        m_baseButtonData[index].width = 43.0 * screenXscal;
        m_baseButtonData[index].height = 48.0 * screenYscal;
        m_baseButtonData[index].delegate_func = NULL;
        m_baseButtonData[index].trigger = NULL;
        m_baseButtonData[index].icon_type = STATIC_ICON;
        m_baseButtonData[index].show_flag = 1;
        m_baseButtonData[index].show_icon_num = 0;
        m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[svresIndex++];
        m_baseButtonData[index].icon_file_name[1] = m_hmiSvresFileName[svresIndex++];
        m_baseButtonData[index].animationStyle = BUTTON_NOMAL;
    }
}

int CSVV302PlaybackTab::HmiInitPlayBar()
{
    m_processBarData.width = 833.0;
    m_processBarData.height = 6.0;
    m_processBarData.pos[0] = (m_screenWidth - m_processBarData.width) * 0.5;
    m_processBarData.pos[1] = 0;
    m_processBarData.withBkgFlag = 1;
    m_processBarData.withBarIconFlag = 0;
    V302ProcessBarWidth = m_processBarData.width;
    m_processBarData.iconFileName[PROCESS_BAR] = new char[100];
    sprintf(m_processBarData.iconFileName[PROCESS_BAR], "%sCar/DVR/pb_processbar.dds", XR_RES);
    m_processBarData.iconFileName[PROCESS_BAR_BACKGROUND] = new char[100];
    sprintf(m_processBarData.iconFileName[PROCESS_BAR_BACKGROUND], "%sCar/DVR/pb_processbar_bkg.dds", XR_RES);
    m_processBarData.trigger = new CV302PbSetPosActionTrigger;

    int i = V302_PB_FILENAME_TITLE;
    m_textEditData[i].width = 30;
    m_textEditData[i].pos[0] = 0;
    m_textEditData[i].pos[1] = 0;
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

    i = V302_PB_FILE_CURRENT_TIME;
    m_textEditData[i].width = 20;
    m_textEditData[i].pos[0] = 0;
    m_textEditData[i].pos[1] = 0;
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
    m_textEditContent[i] = "00 : 30";
    sprintf(m_textEditData[i].textContent[0], "%s", m_textEditContent[i]);

    i = V302_PB_FILE_DURATION_TIME;
    m_textEditData[i].width = 20;
    m_textEditData[i].pos[0] = 0;
    m_textEditData[i].pos[1] = 0;
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
    m_textEditContent[i] = "02 : 00";
    sprintf(m_textEditData[i].textContent[0], "%s", m_textEditContent[i]);
}

int CSVV302PlaybackTab::HmiInitLayer()
{
    m_baseButton[V302_PB_INDEX_BG_IMAGE] = new HMIButton(&(m_baseButtonData[V302_PB_INDEX_BG_IMAGE]), m_uiNode);
    m_baseButton[V302_PB_INDEX_BG_IMAGE]->SetVisibility(0);    
    for (int index = V302_PB_INDEX_STBAR_BK; index <= V302_PB_INDEX_STABR_ENGINE; index++)
    {
        m_baseButton[index] = new HMIButton(&(m_baseButtonData[index]), m_uiNode);
        m_baseButton[index]->SetVisibility(0);
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
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_speed_enable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_speed_disable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_gear_enable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_gear_disable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_brake_enable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_brake_disable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_buckle_enable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_buckle_disable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];                   
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_turnleft_enable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_turnleft_disable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_turnright_enable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_turnright_disable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_engine_enable.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/statebar_engine_disable.dds", XR_RES);
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
