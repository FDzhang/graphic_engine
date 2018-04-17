#include "CSVV302RecordTab.h"
#include "gpu_log.h"

CSVV302RecordTab::CSVV302RecordTab(IUINode* pUiNode = NULL, int pUiNodeId = -1)
{
    m_currentSvresNum = 0;
}

CSVV302RecordTab::~CSVV302RecordTab()
{
    for (int i = 0; i < m_currentSvresNum; i++)
    {
        SAFE_DELETE(m_hmiSvresFileName[i]);
    }
    SAFE_DELETE(m_baseButton[V302_RECORD_INDEX_BG_IMAGE]);
    for (int i = V302_RECORD_INDEX_STBAR_BK; i <= V302_RECORD_INDEX_STABR_ENGINE; i++)
    {
        SAFE_DELETE(m_baseButton[i]);
    }
}

int CSVV302RecordTab::SetHmiParams()
{
    int index = V302_RECORD_INDEX_BG_IMAGE;
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
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302RecordTab::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;
    HmiInitSvresList();
    SetHmiParams();
    HmiInitLayer();
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302RecordTab::Update(Hmi_Message_T &hmiMsg)
{
    RefreshHmi();
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302RecordTab::RefreshHmi()
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302RecordTab::SetElementsVisibility(unsigned char pFlag)
{
    m_baseButton[V302_RECORD_INDEX_BG_IMAGE]->SetVisibility(pFlag);
    for (int i = V302_RECORD_INDEX_STBAR_BK; i <= V302_RECORD_INDEX_STABR_ENGINE; i++)
    {
        m_baseButton[i]->SetVisibility(pFlag);
    }
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302RecordTab::ReturnHmiMsg(Hmi_Message_T *hmi_msg)
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302RecordTab::DestroyHmiElems()
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302RecordTab::HmiInitSTBar()
{
    float screenYscal = m_screenHeight / 1130.0;
    float screenXscal = screenYscal;
    int svresIndex = 1;
    int index = V302_RECORD_INDEX_STBAR_BK;
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

    for (int index = V302_RECORD_INDEX_STABR_SPEED; index <= V302_RECORD_INDEX_STABR_ENGINE; index++)
    {
        m_baseButtonData[index].pos[0] = (659.0 + (index - V302_RECORD_INDEX_STABR_SPEED) * 43.0) * screenXscal;
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

int CSVV302RecordTab::HmiInitLayer()
{
    m_baseButton[V302_RECORD_INDEX_BG_IMAGE] = new HMIButton(&(m_baseButtonData[V302_RECORD_INDEX_BG_IMAGE]), m_uiNode);
    m_baseButton[V302_RECORD_INDEX_BG_IMAGE]->SetVisibility(0);    
    for (int index = V302_RECORD_INDEX_STBAR_BK; index <= V302_RECORD_INDEX_STABR_ENGINE; index++)
    {
        m_baseButton[index] = new HMIButton(&(m_baseButtonData[index]), m_uiNode);
        m_baseButton[index]->SetVisibility(0);
    }
}

int CSVV302RecordTab::HmiInitSvresList()
{
    int index = 0;
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/record_bk.dds", XR_RES);
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

unsigned char *CSVV302RecordTab::HmiGetSvresFile(int index)
{
    return m_hmiSvresFileName[index];
}