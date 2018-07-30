#include "CSVS302RecordTab.h"
#include "gpu_log.h"

CSVS302RecordTab::CSVS302RecordTab(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
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
    for (int i = S302_RECORD_INDEX_STABR_SPEED; i <= S302_RECORD_INDEX_STABR_BUCKLE; i++)
    {
        SAFE_DELETE(m_baseButton[i]);
    }
}

int CSVS302RecordTab::SetHmiParams()
{
    int offset = 0;
    int index = S302_RECORD_INDEX_BG_IMAGE;
    m_baseButtonData[index].pos[0] = offset;
    m_baseButtonData[index].pos[1] = 0;
    m_baseButtonData[index].width = m_screenWidth;
    m_baseButtonData[index].height = 60;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[0];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;

    index = S302_RECORD_INDEX_RECPOINT;
    m_baseButtonData[index].pos[0] = offset + 34;
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
    InitText();
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

			case GUI_OBJ_ID_REC_STATE_EXT:
				
			  	//Log_Error("------------GUI_OBJ_ID_REC_STATE_EXT: %d, bShow: %d", fileListTabMsg[i].uStatus.ObjVal, fileListTabMsg[i].bShow);
                if(fileListTabMsg[i].uStatus.ObjVal == 1)
                {
                    if(fileListTabMsg[i].bShow == 1)
                    {
                        m_buttonVisibility[S302_RECORD_INDEX_RECPOINT] = 1;
                    }
                    else if(fileListTabMsg[i].bShow == 0)
                    {
                        m_buttonVisibility[S302_RECORD_INDEX_RECPOINT] = 0;
                    }
                }
                else if(fileListTabMsg[i].uStatus.ObjVal == 0)
                {
                    m_buttonVisibility[S302_RECORD_INDEX_RECPOINT] = 0;
                }
			break;
				
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
    for(int i = S302_REC_TIME_TEXT; i < S302_REC_TEXT_NUM; i++)
    {
        m_textEdit[i]->Update(m_textEditData[i].textContent[0]);
    }
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302RecordTab::SetElementsVisibility(unsigned char pFlag)
{
    for (int i = S302_RECORD_INDEX_BG_IMAGE; i <= S302_RECORD_INDEX_STABR_BUCKLE; i++)
    {		
    	if(i == S302_RECORD_INDEX_RECPOINT)
        {
        	if(pFlag == 0)
        	{
        		m_buttonVisibility[i] = pFlag;
        		m_baseButton[i]->SetVisibility(pFlag);
    		}
		}
		else
		{
			m_buttonVisibility[i] = pFlag;
			m_baseButton[i]->SetVisibility(pFlag);
		}

    }

    for (int i = S302_REC_TIME_TEXT; i < S302_REC_TEXT_NUM; i++)
    {
        m_textEdit[i]->SetVisibility(pFlag);
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

    int index = S302_RECORD_INDEX_STABR_SPEED;
    m_baseButtonData[index].pos[0] = 810.0;
    m_baseButtonData[index].pos[1] = 12.0;
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

    index = S302_RECORD_INDEX_STABR_GEAR;
    m_baseButtonData[index].pos[0] = 920.0;
    m_baseButtonData[index].pos[1] = 12.0;
    m_baseButtonData[index].width = 36;
    m_baseButtonData[index].height = 36;
    m_baseButtonData[index].delegate_func = NULL;
    m_baseButtonData[index].trigger = NULL;
    m_baseButtonData[index].icon_type = STATIC_ICON;
    m_baseButtonData[index].show_flag = 1;
    m_baseButtonData[index].show_icon_num = 0;
    m_baseButtonData[index].icon_file_name[0] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].icon_file_name[1] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].icon_file_name[2] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].icon_file_name[3] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].icon_file_name[4] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].icon_file_name[5] = m_hmiSvresFileName[svresIndex++];
    m_baseButtonData[index].animationStyle = BUTTON_NOMAL;
    
    for (int index = S302_RECORD_INDEX_STABR_ACC; index <= S302_RECORD_INDEX_STABR_BUCKLE; index++)
    {
        m_baseButtonData[index].pos[0] = 920.0 + (index - S302_RECORD_INDEX_STABR_GEAR) * 40.0;
        m_baseButtonData[index].pos[1] = 12.0;
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
    for (int index = S302_RECORD_INDEX_BG_IMAGE; index <= S302_RECORD_INDEX_STABR_BUCKLE; index++)
    {
        m_baseButton[index] = new HMIButton(&(m_baseButtonData[index]), m_uiNode);
        m_baseButton[index]->SetVisibility(0);
    }
    
    for (int index = S302_REC_TIME_TEXT; index < S302_REC_TEXT_NUM; index++)
    {
        m_textEdit[index] = new HmiTextEdit(&(m_textEditData[index]), m_uiNode);
        m_textEdit[index]->SetVisibility(0);
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
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_speed_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_speed_g.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_p.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_n.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_d.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_m.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_gear_invalid.dds", XR_RES);
    
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_acc_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_acc_r.dds", XR_RES);
    
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_brake_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_brake_r.dds", XR_RES);

    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnleft_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnleft_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnright_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_turnright_r.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_buckle_w.dds", XR_RES);
    m_hmiSvresFileName[index] = new char[50];
    sprintf(m_hmiSvresFileName[index++], "%sS302/statebar_buckle_r.dds", XR_RES);

    m_currentSvresNum = index;
}

char *CSVS302RecordTab::HmiGetSvresFile(int index)
{
    return m_hmiSvresFileName[index];
}

int CSVS302RecordTab::SetDvrView(unsigned char pViewCmd)
{
	uint8_t displayCmd;

//    Log_Error("====================SetDvrView = %d",pViewCmd);
	if(pViewCmd == GUI_VIEW_INDEX_FRONT_EXT)
	{
		displayCmd = DVR_FRONT_SINGLE_VIEW;
	}
	else if(pViewCmd == GUI_VIEW_INDEX_REAR_EXT)
	{
		displayCmd = DVR_REAR_SINGLE_VIEW;
	}
	else if(pViewCmd == GUI_VIEW_INDEX_LEFT_EXT)
	{
		displayCmd = DVR_LEFT_SINGLE_VIEW;
	}
	else if(pViewCmd == GUI_VIEW_INDEX_RIGHT_EXT)
	{
		displayCmd = DVR_RIGHT_SINGLE_VIEW;
	}
	else if(pViewCmd == GUI_VIEW_INDEX_MATTS_EXT)
	{
		displayCmd = MATTS_VIEW;
	}

	UpdateRenderData(RENDER_DATA_VIEW_CMD, &displayCmd, sizeof(uint8_t));

	return HMI_SUCCESS;
}

int CSVS302RecordTab::SetStateBarVal(void *ptr)
{
    GUI_OBJ_VEHICLE_DATA_INST_EXT *recCanMsg = NULL;
    recCanMsg = (GUI_OBJ_VEHICLE_DATA_INST_EXT*)ptr;
    if(recCanMsg == NULL) return HMI_SUCCESS;
    
    if(recCanMsg->GearShiftPositon < 4)
    {
        m_buttonStatus[S302_RECORD_INDEX_STABR_GEAR] = recCanMsg->GearShiftPositon;
    }
    else if(recCanMsg->GearShiftPositon < 6)
    {
        m_buttonStatus[S302_RECORD_INDEX_STABR_GEAR] = 3;
    }
    else if(recCanMsg->GearShiftPositon == 7)
    {   
        m_buttonStatus[S302_RECORD_INDEX_STABR_GEAR] = 4;
    }
    else
    {
        m_buttonStatus[S302_RECORD_INDEX_STABR_GEAR] = 5;
    }
//    m_buttonStatus[S302_RECORD_INDEX_STABR_GEAR] = (recCanMsg->GearShiftPositon > 1) ? 0 : recCanMsg->GearShiftPositon;
    m_buttonStatus[S302_RECORD_INDEX_STABR_ACC] = (recCanMsg->AccePedalPosition > 0) ? 1 : 0;
    m_buttonStatus[S302_RECORD_INDEX_STABR_BRAKE] = (recCanMsg->BrakePedalStatus > 1) ? 0 : recCanMsg->BrakePedalStatus;    
    m_buttonStatus[S302_RECORD_INDEX_STABR_TURNLEFT] = (recCanMsg->LeftTurnLampStatus > 1) ? 0 : recCanMsg->LeftTurnLampStatus;
    m_buttonStatus[S302_RECORD_INDEX_STABR_TURNRIGHT] = (recCanMsg->RightTurnLampStatus > 1) ? 0 : recCanMsg->RightTurnLampStatus;
    m_buttonStatus[S302_RECORD_INDEX_STABR_BUCKLE] = (recCanMsg->DriverBuckleSwitchStatus > 1) ? 0 : recCanMsg->DriverBuckleSwitchStatus; 

    sprintf(m_textEditData[S302_REC_TIME_TEXT].textContent[0],"%04d-%02d-%02d  %02d:%02d:%02d",recCanMsg->TimeYear,recCanMsg->TimeMon,recCanMsg->TimeDay,recCanMsg->TimeHour,recCanMsg->TimeMin,recCanMsg->TimeSec);

	char LatitudeTmpBuf[32] = {0};
	if(recCanMsg->GpsLatitude_IsNorth)
		sprintf(LatitudeTmpBuf, "N %02d.%02d'%02d\"", recCanMsg->GpsLatitude_Deg, recCanMsg->GpsLatitude_Min, recCanMsg->GpsLatitude_Sec);
	else
		sprintf(LatitudeTmpBuf, "S %02d.%02d'%02d\"", recCanMsg->GpsLatitude_Deg, recCanMsg->GpsLatitude_Min, recCanMsg->GpsLatitude_Sec);

	char LongitudeTmpBuf[32] = {0};
	if(recCanMsg->GpsLongitude_IsEast)
		sprintf(LongitudeTmpBuf, "E %03d.%02d'%02d\"", recCanMsg->GpsLongitude_Deg, recCanMsg->GpsLongitude_Min, recCanMsg->GpsLongitude_Sec);
	else
		sprintf(LongitudeTmpBuf, "W %03d.%02d'%02d\"", recCanMsg->GpsLongitude_Deg, recCanMsg->GpsLongitude_Min, recCanMsg->GpsLongitude_Sec);	
		
    sprintf(m_textEditData[S302_REC_GPS_TEXT].textContent[0],"%s  %s", LatitudeTmpBuf, LongitudeTmpBuf);
    
    sprintf(m_textEditData[S302_REC_SPEED_TEXT].textContent[0],"%03d",recCanMsg->VehicleSpeed);
    return HMI_SUCCESS;
}

int CSVS302RecordTab::InitText()
{
    int i = 0;

    i = S302_REC_TIME_TEXT;
    m_textEditData[i].pos[0] = 165;
    m_textEditData[i].pos[1] = 12;
    m_textEditData[i].width = 30;
	m_textEditData[i].font_size = 5.0;
	m_textEditData[i].line_num = 1;
	m_textEditData[i].visibilityStatus = 1;
	m_textEditData[i].targetIndex = -1;
	m_textEditData[i].insertFlag = InsertFlag_Default;
	m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
	m_textEditData[i].trigger = NULL;
	m_textEditData[i].textColor[0] = 1.0;
	m_textEditData[i].textColor[1] = 1.0;
	m_textEditData[i].textColor[2] = 1.0;
	m_textEditData[i].textContent[0] = new char[100];
	char* ptext0 = "2018-05-11  18:00:00";
	sprintf(m_textEditData[i].textContent[0],"%s", ptext0);

    i = S302_REC_GPS_TEXT;
    m_textEditData[i].pos[0] = 465;
    m_textEditData[i].pos[1] = 12;
    m_textEditData[i].width = 30;
	m_textEditData[i].font_size = 5.0;
	m_textEditData[i].line_num = 1;
	m_textEditData[i].visibilityStatus = 1;
	m_textEditData[i].targetIndex = -1;
	m_textEditData[i].insertFlag = InsertFlag_Default;
	m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
	m_textEditData[i].trigger = NULL;
	m_textEditData[i].textColor[0] = 1.0;
	m_textEditData[i].textColor[1] = 1.0;
	m_textEditData[i].textColor[2] = 1.0;
	m_textEditData[i].textContent[0] = new char[100];
	char* ptext1 = "N 00.00'00\"  E 00.00'00\"";
	sprintf(m_textEditData[i].textContent[0],"%s", ptext1);

    i = S302_REC_SPEED_TEXT;
    m_textEditData[i].pos[0] = 824;
    m_textEditData[i].pos[1] = 14;
    m_textEditData[i].width = 25;
	m_textEditData[i].font_size = 5.0;
	m_textEditData[i].line_num = 1;
	m_textEditData[i].visibilityStatus = 1;
	m_textEditData[i].targetIndex = -1;
	m_textEditData[i].insertFlag = InsertFlag_Default;
	m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
	m_textEditData[i].trigger = NULL;
	m_textEditData[i].textColor[0] = 1.0;
	m_textEditData[i].textColor[1] = 1.0;
	m_textEditData[i].textColor[2] = 1.0;
	m_textEditData[i].textContent[0] = new char[100];
	char* ptext2 = "025";
	sprintf(m_textEditData[i].textContent[0],"%s", ptext2);
    return HMI_SUCCESS;
}


