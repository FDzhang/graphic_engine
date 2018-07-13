#include "CSVV302MainHmi.h"
#include "CSVV302FileListTab.h"
#include "CSVV302PlaybackTab.h"
#include "CSVV302PlayImageTab.h"
#include "CSVV302RecordTab.h"



#include "gpu_log.h"

static CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);

REGISTER_HMI_CLASS(CSVV302MainHmi)

CSVV302MainHmi::CSVV302MainHmi()
{
    for (int i = V302_FILE_VIEW_HMI; i < V302_MENU_SUB_HMI_NUM; i++)
    {
        m_subHmi[i] = NULL;
        m_subHmiInitFlag[i] = 0;
    }
}

CSVV302MainHmi::~CSVV302MainHmi()
{
}

int CSVV302MainHmi::SetHmiParams()
{
    for (int i = V302_MAIN_BUTTON_INDEX_BG_IMAGE; i < V302_MAIN_BUTTON_INDEX_NUM; i++)
    {
        m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]), m_uiNode);
        m_baseButton[i]->SetVisibility(0);
    }
    
    m_speed_value_text = new HmiTextEdit(&m_speed_value_text_data,m_uiNode);
    m_speed_value_text->SetVisibility(0);
    
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;

//    window_width = window_height / 1130.0 * 960.0;

    
    float screenYscal = window_height / 1128.0;
    float screenXscal = screenYscal;

    int index = 0;

    index = V302_MAIN_BUTTON_INDEX_BG_IMAGE;
    m_baseButtonData[index].pos[0] = 0;
    m_baseButtonData[index].pos[1] = 0;
    m_baseButtonData[index].width = 960.0 * screenXscal;
    m_baseButtonData[index].height = 1128.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/record_bk.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_MAIN_BUTTON_INDEX_STATUSBAR_BK;
    m_baseButtonData[index].pos[0] = 560.0 * screenXscal;
    m_baseButtonData[index].pos[1] = 1.0;
    m_baseButtonData[index].width = 400.0 * screenXscal;
    m_baseButtonData[index].height = 50.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/statebar_bk.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_MAIN_BUTTON_INDEX_STATUSBAR_SPEED;
    m_baseButtonData[index].pos[0] = 659.0 * screenXscal;
    m_baseButtonData[index].pos[1] = 2.0;
    m_baseButtonData[index].width = 43.0 * screenXscal;
    m_baseButtonData[index].height = 48.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/statebar_speed_enable.dds", XR_RES);
    m_baseButtonData[index].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[1], "%sV302/statebar_speed_disable.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_MAIN_BUTTON_INDEX_STATUSBAR_GEAR;
    m_baseButtonData[index].pos[0] = (659.0 + (index - V302_MAIN_BUTTON_INDEX_STATUSBAR_SPEED) * 43.0) * screenXscal;
    m_baseButtonData[index].pos[1] = 2.0;
    m_baseButtonData[index].width = 43.0 * screenXscal;
    m_baseButtonData[index].height = 48.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/statebar_gear_enable.dds", XR_RES);
    m_baseButtonData[index].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[1], "%sV302/statebar_gear_disable.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_MAIN_BUTTON_INDEX_STATUSBAR_BRAKE;
    m_baseButtonData[index].pos[0] = (659.0 + (index - V302_MAIN_BUTTON_INDEX_STATUSBAR_SPEED) * 43.0) * screenXscal;
    m_baseButtonData[index].pos[1] = 2.0;
    m_baseButtonData[index].width = 43.0 * screenXscal;
    m_baseButtonData[index].height = 48.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/statebar_brake_enable.dds", XR_RES);
    m_baseButtonData[index].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[1], "%sV302/statebar_brake_disable.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_MAIN_BUTTON_INDEX_STATUSBAR_BUCKLE;
    m_baseButtonData[index].pos[0] = (659.0 + (index - V302_MAIN_BUTTON_INDEX_STATUSBAR_SPEED) * 43.0) * screenXscal;
    m_baseButtonData[index].pos[1] = 2.0;
    m_baseButtonData[index].width = 43.0 * screenXscal;
    m_baseButtonData[index].height = 48.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/statebar_buckle_enable.dds", XR_RES);
    m_baseButtonData[index].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[1], "%sV302/statebar_buckle_disable.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_MAIN_BUTTON_INDEX_STATUSBAR_TURNLEFT;
    m_baseButtonData[index].pos[0] = (659.0 + (index - V302_MAIN_BUTTON_INDEX_STATUSBAR_SPEED) * 43.0) * screenXscal;
    m_baseButtonData[index].pos[1] = 2.0;
    m_baseButtonData[index].width = 43.0 * screenXscal;
    m_baseButtonData[index].height = 48.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/statebar_turnleft_enable.dds", XR_RES);
    m_baseButtonData[index].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[1], "%sV302/statebar_turnleft_disable.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_MAIN_BUTTON_INDEX_STATUSBAR_TURNRIGHT;
    m_baseButtonData[index].pos[0] = (659.0 + (index - V302_MAIN_BUTTON_INDEX_STATUSBAR_SPEED) * 43.0) * screenXscal;
    m_baseButtonData[index].pos[1] = 2.0;
    m_baseButtonData[index].width = 43.0 * screenXscal;
    m_baseButtonData[index].height = 48.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/statebar_turnright_enable.dds", XR_RES);
    m_baseButtonData[index].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[1], "%sV302/statebar_turnright_disable.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = V302_MAIN_BUTTON_INDEX_STATUSBAR_ENGINE;
    m_baseButtonData[index].pos[0] = (659.0 + (index - V302_MAIN_BUTTON_INDEX_STATUSBAR_SPEED) * 43.0) * screenXscal;
    m_baseButtonData[index].pos[1] = 2.0;
    m_baseButtonData[index].width = 43.0 * screenXscal;
    m_baseButtonData[index].height = 48.0 * screenYscal;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[0], "%sV302/statebar_engine_enable.dds", XR_RES);
    m_baseButtonData[index].icon_file_name[1] = new char[50];
    sprintf(m_baseButtonData[index].icon_file_name[1], "%sV302/statebar_engine_disable.dds", XR_RES);
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;


    m_speed_value_text_data.pos[0] = 586.0 * screenXscal;
    m_speed_value_text_data.pos[1] = 4 * screenYscal;
    m_speed_value_text_data.width = 40 * screenXscal;
	m_speed_value_text_data.font_size = 8.0;
	m_speed_value_text_data.line_num = 1;
	m_speed_value_text_data.visibilityStatus = 0;
	m_speed_value_text_data.targetIndex = -1;
	m_speed_value_text_data.insertFlag = InsertFlag_Default;
	m_speed_value_text_data.fontTypeMtlName = XR_RES"text_box.ttf";
	m_speed_value_text_data.trigger = NULL;
	m_speed_value_text_data.textColor[0] = 0.9375;
	m_speed_value_text_data.textColor[1] = 0.9375;
	m_speed_value_text_data.textColor[2] = 0.9375;
	m_speed_value_text_data.textContent[0] = new char[10];
	char* ptext1 = "060";
	sprintf(m_speed_value_text_data.textContent[0],"%s", ptext1);   


    SetHmiParams();

    //    Log_Error("=============CSVV302MainHmi::Init");
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::Update(Hmi_Message_T &hmiMsg)
{
    MainMenuDataT mainMenuData;
    memset(&mainMenuData, 0, sizeof(MainMenuDataT));
    static unsigned char speedvalue = 0;
    
    CAvmRenderDataBase::GetInstance()->GetMainMenuStatus(&mainMenuData);

    m_iconStatus[V302_DVR_STATUS] = mainMenuData.iconStatus[MAIN_MENU_DVR];
    m_iconStatus[V302_DVR_STATUS] = 0;

    
    //CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(LEFT_SINGLE_VIEW);
#if 0
    if (m_iconStatus[V302_DVR_STATUS] == 1)
    {
        InitSubHmi(V302_FILE_VIEW_HMI);
    }
    else if (m_iconStatus[V302_PB_STATUS] == 1)
    {
        InitSubHmi(V302_PlAY_VIEW_HMI);
    }
    else if (m_iconStatus[V302_IMAGE_STATUS] == 1)
    {
        InitSubHmi(V302_IMAGE_VIEW_HMI);
    }
    else if (m_iconStatus[V302_RECORD_STATUS] == 1)
    {
        InitSubHmi(V302_RECORD_VIEW_HMI);
    }
    else
    {
        if (m_subHmi[V302_FILE_VIEW_HMI])
        {
            FreeSubHmi(V302_FILE_VIEW_HMI);
        }
        if (m_subHmi[V302_PlAY_VIEW_HMI])
        {
            FreeSubHmi(V302_PlAY_VIEW_HMI);
        }
        if (m_subHmi[V302_IMAGE_VIEW_HMI])
        {
            FreeSubHmi(V302_IMAGE_VIEW_HMI);
        }
        if (m_subHmi[V302_RECORD_VIEW_HMI])
        {
            FreeSubHmi(V302_RECORD_VIEW_HMI);
        }

        SetElementsVisibility(1);
        
        sprintf(m_speed_value_text_data.textContent[0],"%03u", speedvalue);
        
        m_speed_value_text->Update(m_speed_value_text_data.textContent[0]);

        speedvalue ++;

        if(speedvalue == 250) speedvalue = 0;
    }
    if (m_subHmi[V302_FILE_VIEW_HMI])
    {
        m_subHmiVisibility[V302_FILE_VIEW_HMI] = 1;
        m_subHmi[V302_FILE_VIEW_HMI]->SetElementsVisibility(m_subHmiVisibility[V302_FILE_VIEW_HMI]);
        m_subHmi[V302_FILE_VIEW_HMI]->Update(hmiMsg);
    }
    if (m_subHmi[V302_PlAY_VIEW_HMI])
    {
        m_subHmiVisibility[V302_PlAY_VIEW_HMI] = 1;
        m_subHmi[V302_PlAY_VIEW_HMI]->SetElementsVisibility(m_subHmiVisibility[V302_PlAY_VIEW_HMI]);
        m_subHmi[V302_PlAY_VIEW_HMI]->Update(hmiMsg);        
    }
    if (m_subHmi[V302_IMAGE_VIEW_HMI])
    {
        m_subHmiVisibility[V302_IMAGE_VIEW_HMI] = 1;
        m_subHmi[V302_IMAGE_VIEW_HMI]->SetElementsVisibility(m_subHmiVisibility[V302_IMAGE_VIEW_HMI]);
        m_subHmi[V302_IMAGE_VIEW_HMI]->Update(hmiMsg);
    }
    if (m_subHmi[V302_RECORD_VIEW_HMI])
    {
        m_subHmiVisibility[V302_RECORD_VIEW_HMI] = 1;
        m_subHmi[V302_RECORD_VIEW_HMI]->SetElementsVisibility(m_subHmiVisibility[V302_RECORD_VIEW_HMI]);
        m_subHmi[V302_RECORD_VIEW_HMI]->Update(hmiMsg);
    }
#endif
    
    RefreshHmi();
    
    if(m_iconStatus[V302_DVR_STATUS] == 1)
    {
        char* hmiName = "CSVV302DvrBase";
	    CSVHmiIntent::GetInstance()->Intent(hmiName);
    }
    
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::RefreshHmi()
{

    return V302_MAIN_HMI_NORMAL;
}

void CSVV302MainHmi::InitSubHmi(unsigned char pHmiIndex)
{
    if (pHmiIndex >= V302_MENU_SUB_HMI_NUM)
        return;
    if (m_subHmiInitFlag[pHmiIndex] == 0)
    {
        switch (pHmiIndex)
        {
        case V302_FILE_VIEW_HMI:
            m_subHmi[pHmiIndex] = new CSVV302FileListTab(m_uiNode, m_uiNodeId);
            break;
        case V302_PlAY_VIEW_HMI:
            m_subHmi[pHmiIndex] = new CSVV302PlaybackTab(m_uiNode, m_uiNodeId);
            break;
        case V302_IMAGE_VIEW_HMI:
            m_subHmi[pHmiIndex] = new CSVV302PlayImageTab(m_uiNode, m_uiNodeId);
            break;
        case V302_RECORD_VIEW_HMI:
            m_subHmi[pHmiIndex] = new CSVV302RecordTab(m_uiNode, m_uiNodeId);
            break;
        default:
            break;
        }
        if(m_subHmi[pHmiIndex])
        {
            m_subHmi[pHmiIndex]->Init(m_screenWidth, m_screenHeight);
            m_subHmiVisibility[pHmiIndex] = 1;
            m_subHmiInitFlag[pHmiIndex] = 1;
        }
        else
        {
        }
    }
}

void CSVV302MainHmi::FreeSubHmi(unsigned char pHmiIndex)
{
    if (pHmiIndex < V302_MENU_SUB_HMI_NUM)
    {
        m_subHmiVisibility[pHmiIndex] = 0;
        SAFE_DELETE(m_subHmi[pHmiIndex]);
        m_subHmiInitFlag[pHmiIndex] = 0;
    }
}

int CSVV302MainHmi::SetElementsVisibility(unsigned char pFlag)
{
    for (int i = V302_MAIN_BUTTON_INDEX_BG_IMAGE; i < V302_MAIN_BUTTON_INDEX_NUM; i++)
    {
        m_baseButton[i]->SetVisibility(pFlag);
    }
    m_speed_value_text->SetVisibility(pFlag);
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::ReturnHmiMsg(Hmi_Message_T *hmi_msg)
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::DestroyHmiElems()
{
    return V302_MAIN_HMI_NORMAL;
}
