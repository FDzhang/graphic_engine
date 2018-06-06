#include "CSVV302RecordTab.h"
#include "gpu_log.h"

CSVV302RecordTab::CSVV302RecordTab(IUINode* pUiNode, int pUiNodeId)
{
    m_currentSvresNum = 0;
	memset(m_buttonStatus, 0, V302_RECORD_INDEX_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 0, V302_RECORD_INDEX_NUM * sizeof(unsigned char));   
}

CSVV302RecordTab::~CSVV302RecordTab()
{
    for (int i = 0; i < m_currentSvresNum; i++)
    {
        SAFE_DELETE(m_hmiSvresFileName[i]);
    }
    for (int i = V302_RECORD_INDEX_BG_IMAGE; i < V302_RECORD_INDEX_NUM; i++)
    {
        SAFE_DELETE(m_baseButton[i]);
    }
}

int CSVV302RecordTab::SetHmiParams()
{
    float scale = m_screenHeight / 1128.0;
    
    int index = 0;
    
    index = V302_RECORD_INDEX_BG_IMAGE;
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

    index = V302_RECORD_INDEX_RECPOINT;
    m_baseButtonData[index].pos[0] = 34.0 * scale;
    m_baseButtonData[index].pos[1] = 80.0 * scale;
    m_baseButtonData[index].width = 108.0 * scale;
    m_baseButtonData[index].height = 32.0 * scale;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[1];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    HmiInitSTBar();
    InitText();
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
//    CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_LEFT_SINGLE_VIEW);
    DVR_GUI_LAYOUT_INST_EXT dvrData;
	CAvmRenderDataBase::GetInstance()->GetDvrData(&dvrData);

	DVR_GRAPHIC_UIOBJ_EXT* fileListTabMsg = NULL;

	fileListTabMsg = dvrData.pTable;
    
    if(dvrData.curLayout == GUI_LAYOUT_RECORD_EXT)
    {
        for(int i = 0; i < dvrData.ObjNum; i++)
        {
            switch(fileListTabMsg[i].Id)
            {
              case  GUI_OBJ_ID_REC_VIEW_INDEX_EXT:
                SetDvrView(fileListTabMsg[i].uStatus.ObjVal);
                break;
              case  GUI_OBJ_ID_REC_VEHICLE_DATA_EXT:
                if(fileListTabMsg[i].status_type == GUI_OBJ_STATUS_TYPE_POINTER_EXT && fileListTabMsg[i].uStatus.ptr)
                {
                    SetStateBarVal(fileListTabMsg[i].uStatus.ptr);
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

int CSVV302RecordTab::RefreshHmi()
{
	for(int i = V302_RECORD_INDEX_BG_IMAGE; i < V302_RECORD_INDEX_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
    for(int i = V302_REC_TIME_TEXT; i < V302_REC_TEXT_NUM; i++)
    {
        m_textEdit[i]->Update(m_textEditData[i].textContent[0]);
    }
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302RecordTab::SetElementsVisibility(unsigned char pFlag)
{
    for (int i = V302_RECORD_INDEX_BG_IMAGE; i < V302_RECORD_INDEX_NUM; i++)
    {
        m_buttonVisibility[i] = pFlag;
        m_baseButton[i]->SetVisibility(pFlag);
    }

    for (int i = V302_REC_TIME_TEXT; i < V302_REC_TEXT_NUM; i++)
    {
        m_textEdit[i]->SetVisibility(pFlag);
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
    float scale = m_screenHeight / 1128.0;
    
    int svresIndex = 2;
    int index = V302_RECORD_INDEX_STBAR_BK;
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

    index = V302_RECORD_INDEX_STABR_SPEED;
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
    
    for (int index = V302_RECORD_INDEX_STABR_GEAR; index <= V302_RECORD_INDEX_STABR_ENGINE; index++)
    {
        m_baseButtonData[index].pos[0] = (708.0 + (index - V302_RECORD_INDEX_STABR_GEAR) * 40.0) * scale;
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
    
}

int CSVV302RecordTab::HmiInitLayer()
{  
    for (int index = V302_RECORD_INDEX_BG_IMAGE; index < V302_RECORD_INDEX_NUM; index++)
    {
        m_baseButton[index] = new HMIButton(&(m_baseButtonData[index]), m_uiNode);
        m_baseButton[index]->SetVisibility(0);
    }
    
    for (int index = V302_REC_TIME_TEXT; index < V302_REC_TEXT_NUM; index++)
    {
        m_textEdit[index] = new HmiTextEdit(&(m_textEditData[index]), m_uiNode);
        m_textEdit[index]->SetVisibility(0);
    }
}

int CSVV302RecordTab::HmiInitSvresList()
{
    int index = 0;
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sV302/record_bk.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sCar/DVR/record_red_dot_normal.dds", XR_RES);
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

unsigned char *CSVV302RecordTab::HmiGetSvresFile(int index)
{
    return m_hmiSvresFileName[index];
}

int CSVV302RecordTab::SetDvrView(unsigned char pViewCmd)
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

int CSVV302RecordTab::SetStateBarVal(void *ptr)
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

    sprintf(m_textEditData[V302_REC_TIME_TEXT].textContent[0],"%04d-%02d-%02d  %02d:%02d:%02d",recCanMsg->TimeYear,recCanMsg->TimeMon,recCanMsg->TimeDay,recCanMsg->TimeHour,recCanMsg->TimeMin,recCanMsg->TimeSec);

	char LatitudeTmpBuf[32] = {0};
	if(recCanMsg->GpsLatitude_IsNorth)
		sprintf(LatitudeTmpBuf, "N %03d.%02d'%02d\"", recCanMsg->GpsLatitude_Deg, recCanMsg->GpsLatitude_Min, recCanMsg->GpsLatitude_Sec);
	else
		sprintf(LatitudeTmpBuf, "S %03d.%02d'%02d\"", recCanMsg->GpsLatitude_Deg, recCanMsg->GpsLatitude_Min, recCanMsg->GpsLatitude_Sec);

	char LongitudeTmpBuf[32] = {0};
	if(recCanMsg->GpsLongitude_IsEast)
		sprintf(LongitudeTmpBuf, "E %03d.%02d'%02d\"", recCanMsg->GpsLongitude_Deg, recCanMsg->GpsLongitude_Min, recCanMsg->GpsLongitude_Sec);
	else
		sprintf(LongitudeTmpBuf, "W %03d.%02d'%02d\"", recCanMsg->GpsLongitude_Deg, recCanMsg->GpsLongitude_Min, recCanMsg->GpsLongitude_Sec);	

    sprintf(m_textEditData[V302_REC_GPS_TEXT].textContent[0],"%s  %s", LatitudeTmpBuf, LongitudeTmpBuf);

    sprintf(m_textEditData[V302_REC_SPEED_TEXT].textContent[0],"%03d",recCanMsg->VehicleSpeed);
    return HMI_SUCCESS;

}

int CSVV302RecordTab::InitText()
{
    float scale = m_screenHeight / 1128.0;

    int i = 0;

    i = V302_REC_TIME_TEXT;
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

    i = V302_REC_GPS_TEXT;
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

    i = V302_REC_SPEED_TEXT;
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

