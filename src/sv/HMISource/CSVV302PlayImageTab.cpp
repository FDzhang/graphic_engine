#include "CSVV302PlayImageTab.h"
#include "gpu_log.h"

CSVV302PlayImageTab::CSVV302PlayImageTab(IUINode *pUiNode = NULL, int pUiNodeId = -1)
{
    m_currentSvresNum = 0;
}

CSVV302PlayImageTab::~CSVV302PlayImageTab()
{
    for (int i = 0; i < m_currentSvresNum; i++)
    {
        SAFE_DELETE(m_hmiSvresFileName[i]);
    }
    SAFE_DELETE(m_baseButton[V302_IMAGE_INDEX_BG_IMAGE]);
}

int CSVV302PlayImageTab::SetHmiParams()
{
    int index = V302_IMAGE_INDEX_BG_IMAGE;
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

    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlayImageTab::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;
    HmiInitSvresList();
    SetHmiParams();
    HmiInitLayer();
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlayImageTab::Update(Hmi_Message_T &hmiMsg)
{
    DVR_GUI_LAYOUT_INST_EXT dvrData;
	CAvmRenderDataBase::GetInstance()->GetDvrData(&dvrData);

	DVR_GRAPHIC_UIOBJ_EXT* fileListTabMsg = NULL;

	fileListTabMsg = dvrData.pTable;
    
    if(dvrData.curLayout == GUI_LAYOUT_PLAYBACK_IMAGE_EXT)
    {
        for(int i = 0; i < dvrData.ObjNum; i++)
        {
            switch(fileListTabMsg[i].Id)
            {
              case  GUI_OBJ_ID_PB_VIEW_INDEX_EXT:
                SetDvrView(fileListTabMsg[i].uStatus.ObjVal);
                break;
              default:
                break;
            }
        }
    }
    RefreshHmi();
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlayImageTab::RefreshHmi()
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlayImageTab::SetElementsVisibility(unsigned char pFlag)
{
    m_baseButton[V302_IMAGE_INDEX_BG_IMAGE]->SetVisibility(pFlag);
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlayImageTab::ReturnHmiMsg(Hmi_Message_T *hmi_msg)
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlayImageTab::DestroyHmiElems()
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302PlayImageTab::HmiInitLayer()
{
    m_baseButton[V302_IMAGE_INDEX_BG_IMAGE] = new HMIButton(&(m_baseButtonData[V302_IMAGE_INDEX_BG_IMAGE]), m_uiNode);
    m_baseButton[V302_IMAGE_INDEX_BG_IMAGE]->SetVisibility(0);
}

int CSVV302PlayImageTab::HmiInitSvresList()
{
    int index = 0;
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/playimage_bk.dds", XR_RES);
    m_currentSvresNum = index;
}

unsigned char *CSVV302PlayImageTab::HmiGetSvresFile(int index)
{
    return m_hmiSvresFileName[index];
}

int CSVV302PlayImageTab::SetDvrView(unsigned char pViewCmd)
{
//    Log_Error("====================SetDvrView = %d",pViewCmd);
	if(pViewCmd == GUI_VIEW_INDEX_FRONT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_FRONT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_REAR_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_REAR_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_LEFT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_LEFT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_RIGHT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_RIGHT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_MATTS_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(MATTS_VIEW);
	}

	return HMI_SUCCESS;
}