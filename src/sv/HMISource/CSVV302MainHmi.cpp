#include "CSVV302MainHmi.h"
#include "CSVV302FileListTab.h"

#include "gpu_log.h"

REGISTER_HMI_CLASS(CSVV302MainHmi)


CSVV302MainHmi::CSVV302MainHmi()
{}

CSVV302MainHmi::~CSVV302MainHmi()
{}

int CSVV302MainHmi::SetHmiParams()
{
    m_baseButton[V302_MAIN_BUTTON_INDEX_BG_IMAGE] = new HMIButton(&(m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE]),m_uiNode);
    m_baseButton[V302_MAIN_BUTTON_INDEX_BG_IMAGE]->SetVisibility(0);
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;
    
    window_width = window_height / 1130.0 * 960.0;

    m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].pos[0] = 0;
    m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].pos[1] = 0;
	m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].width = window_width;
	m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].height = window_height;
	m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].delegate_func = NULL;
	m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].trigger = NULL;
    m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].icon_type = STATIC_ICON;
	m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].show_flag = 1;
	m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].show_icon_num = 0;
	m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].icon_file_name[0],"%sV302/main_bk.dds",XR_RES); 
	m_baseButtonData[V302_MAIN_BUTTON_INDEX_BG_IMAGE].animationStyle = BUTTON_NOMAL;    

    SetHmiParams();
    
//    Log_Error("=============CSVV302MainHmi::Init");
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::Update(Hmi_Message_T& hmiMsg)
{
	MainMenuDataT mainMenuData;
	memset(&mainMenuData, 0, sizeof(MainMenuDataT));

	CAvmRenderDataBase::GetInstance()->GetMainMenuStatus(&mainMenuData);

    m_iconStatus[V302_DVR_STATUS] = mainMenuData.iconStatus[MAIN_MENU_DVR];

    if(m_iconStatus[V302_DVR_STATUS] == 1)
    {
        InitSubHmi(V302_FILE_VIEW_HMI);   
    }
    else
    {
        if(m_subHmi[V302_FILE_VIEW_HMI])
        {
            FreeSubHmi(V302_FILE_VIEW_HMI);
        }
        SetElementsVisibility(1);
    }
    if(m_subHmi[V302_FILE_VIEW_HMI])
    {
        m_subHmiVisibility[V302_FILE_VIEW_HMI] = 1;
        m_subHmi[V302_FILE_VIEW_HMI]->SetElementsVisibility(m_subHmiVisibility[V302_FILE_VIEW_HMI]);
        m_subHmi[V302_FILE_VIEW_HMI]->Update(hmiMsg);
    }
    
    RefreshHmi();
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::RefreshHmi()
{
    
    return V302_MAIN_HMI_NORMAL;
}

void CSVV302MainHmi::InitSubHmi(unsigned char pHmiIndex)
{
    if(pHmiIndex >= V302_MENU_SUB_HMI_NUM) return;
    if(m_subHmiInitFlag[pHmiIndex] == 0)
    {
        switch(pHmiIndex)
        {
            case V302_FILE_VIEW_HMI:
                m_subHmi[pHmiIndex] = new CSVV302FileListTab(m_uiNode, m_uiNodeId);
            break;
            case V302_PlAY_VIEW_HMI:
                m_subHmi[pHmiIndex] = new CSVV302FileListTab(m_uiNode, m_uiNodeId);
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
    }
}


void CSVV302MainHmi::FreeSubHmi(unsigned char pHmiIndex)
{
    if(pHmiIndex < V302_MENU_SUB_HMI_NUM)
    {
        m_subHmiVisibility[pHmiIndex] = 0;
        SAFE_DELETE(m_subHmi[pHmiIndex]);
        m_subHmiInitFlag[pHmiIndex] = 0;       
    }
}

int CSVV302MainHmi::SetElementsVisibility(unsigned char pFlag)
{
    m_baseButton[V302_MAIN_BUTTON_INDEX_BG_IMAGE]->SetVisibility(pFlag);
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302MainHmi::DestroyHmiElems()
{
    return V302_MAIN_HMI_NORMAL;
}
















