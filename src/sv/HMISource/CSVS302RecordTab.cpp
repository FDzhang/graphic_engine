#include "CSVS302RecordTab.h"
#include "gpu_log.h"

CSVS302RecordTab::CSVS302RecordTab(IUINode* pUiNode, int pUiNodeId)
{
    m_currentSvresNum = 0;
	memset(m_buttonStatus, 0, S302_RECORD_INDEX_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 0, S302_RECORD_INDEX_NUM * sizeof(unsigned char));   
}

CSVS302RecordTab::~CSVS302RecordTab()
{
    for (int i = 0; i < m_currentSvresNum; i++)
    {
        SAFE_DELETE(m_hmiSvresFileName[i]);
    }
    SAFE_DELETE(m_baseButton[S302_RECORD_INDEX_BG_IMAGE]);
    for (int i = S302_RECORD_INDEX_STBAR_BK; i <= S302_RECORD_INDEX_STABR_ENGINE; i++)
    {
        SAFE_DELETE(m_baseButton[i]);
    }
}

int CSVS302RecordTab::SetHmiParams()
{
    int offset = 200;
    int index = S302_RECORD_INDEX_BG_IMAGE;
    m_baseButtonData[index].pos[0] = offset;
    m_baseButtonData[index].pos[1] = 0;
    m_baseButtonData[index].width = m_screenWidth - offset;
    m_baseButtonData[index].height = 60;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[0];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = S302_RECORD_INDEX_RECPOINT;
    m_baseButtonData[index].pos[0] = offset + 60;
    m_baseButtonData[index].pos[1] = 20;
    m_baseButtonData[index].width = 108;
    m_baseButtonData[index].height = 26;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[1];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;
    
    HmiInitSTBar();
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302RecordTab::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;
    HmiInitSvresList();
    SetHmiParams();
    HmiInitLayer();
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302RecordTab::Update(Hmi_Message_T &hmiMsg)
{
//    CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_LEFT_SINGLE_VIEW);
    
    RefreshHmi();
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302RecordTab::RefreshHmi()
{
	for(int i = S302_RECORD_INDEX_BG_IMAGE; i < S302_RECORD_INDEX_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302RecordTab::SetElementsVisibility(unsigned char pFlag)
{
    for (int i = S302_RECORD_INDEX_BG_IMAGE; i <= S302_RECORD_INDEX_STABR_ENGINE; i++)
    {
        m_buttonVisibility[i] = pFlag;
        m_baseButton[i]->SetVisibility(pFlag);
    }
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302RecordTab::ReturnHmiMsg(Hmi_Message_T *hmi_msg)
{
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302RecordTab::DestroyHmiElems()
{
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302RecordTab::HmiInitSTBar()
{
    int svresIndex = 2;
    int index = S302_RECORD_INDEX_STBAR_BK;
    m_baseButtonData[index].pos[0] = 750;
    m_baseButtonData[index].pos[1] = 20.0;
    m_baseButtonData[index].width = 300.0;
    m_baseButtonData[index].height = 40.0;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = S302_RECORD_INDEX_STABR_SPEED;
    m_baseButtonData[index].pos[0] = 880.0;
    m_baseButtonData[index].pos[1] = 22.0;
    m_baseButtonData[index].width = 108;
    m_baseButtonData[index].height = 36;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].icon_file_name[1] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;    
    
    for (int index = S302_RECORD_INDEX_STABR_GEAR; index <= S302_RECORD_INDEX_STABR_ENGINE; index++)
    {
        m_baseButtonData[index].pos[0] = 990.0 + (index - S302_RECORD_INDEX_STABR_GEAR) * 40.0;
        m_baseButtonData[index].pos[1] = 22.0;
        m_baseButtonData[index].width = 36;
        m_baseButtonData[index].height = 36;
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

int CSVS302RecordTab::HmiInitLayer()
{  
    for (int index = S302_RECORD_INDEX_BG_IMAGE; index <= S302_RECORD_INDEX_STABR_ENGINE; index++)
    {
        m_baseButton[index] = new HMIButton(&(m_baseButtonData[index]), m_uiNode);
        m_baseButton[index]->SetVisibility(0);
    }
}

int CSVS302RecordTab::HmiInitSvresList()
{
    int index = 0;
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/record_bk.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sCar/DVR/record_red_dot_normal.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_bk.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_speed_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_speed_g.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_brake_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_brake_g.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_buckle_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_buckle_g.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnleft_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnleft_g.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnright_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnright_g.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_engine_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_engine_g.dds", XR_RES);
    m_currentSvresNum = index;
}

unsigned char *CSVS302RecordTab::HmiGetSvresFile(int index)
{
    return m_hmiSvresFileName[index];
}