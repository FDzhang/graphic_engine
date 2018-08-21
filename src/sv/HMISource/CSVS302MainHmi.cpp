/*===========================================================================*\
 * FILE: CSVS302MainHmi.cpp
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *
 * ABBREVIATIONS:
 *   TODO: List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     TODO: Update list of design document(s)
 *
 *   Requirements Document(s):
 *     TODO: Update list of requirements document(s)
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "CSVS302MainHmi.h"
#include "CSVDemoEolHmi.h"
#include "CSVDvrFileListHmi.h"
#include "CSVChangAnSwitchViewHmi.h"
#include "CSVS302DvrBase.h"
#include "CSVS302PdHmi.h"
//#include "CSVS302GuidelineHmi.h"
REGISTER_HMI_CLASS(CSVS302MainHmi)

static unsigned char s302HmiElementShowImage[S302_MAIN_ELEMENT_NUM];
static unsigned char s302ShowSettingMenu = 0;
static unsigned char s302ShowCtrlBtns = 0;

static CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);

class CS302Enter2dViewActionTrigger : public IActionTrigger
{
public:
    CS302Enter2dViewActionTrigger()
    {
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        
        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = CMD_2D_VIEW_MODE;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302Enter2dViewActionTrigger");
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {

        
    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302Enter3dViewActionTrigger : public IActionTrigger
{
public:
    CS302Enter3dViewActionTrigger()
    {
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;

        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = CMD_3D_VIEW_MODE;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302Enter3dViewActionTrigger");
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {

    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302EnterDvrActionTrigger : public IActionTrigger
{
public:
    CS302EnterDvrActionTrigger()
    {
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;

        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = ALGO_RECORD_BUTTON;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);

    
//		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
//		Ctrl_Cmd_T m_dvrCmd;
//		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
//		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
//		m_dvrCmd.parameter[0] = DVR_USER_CLICK_MAIN_MENU;
//		m_dvrCmd.parameter[1] = GUI_MAIN_MENU_TAB_THUMB;
//		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));        
//        //Log_Error("-----------CS302EnterDvrActionTrigger");
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {

    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302ExitMenuActionTrigger : public IActionTrigger
{
public:
    CS302ExitMenuActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = CMD_EXIT_AVM;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302ExitMenuActionTrigger");

    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302SettingActionTrigger : public IActionTrigger
{
public:
    CS302SettingActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        s302ShowSettingMenu = 1;

        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = CMD_SETTING_PAGE;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302SettingActionTrigger");
    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302SettingMenuReturnActionTrigger : public IActionTrigger
{
public:
    CS302SettingMenuReturnActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        s302ShowSettingMenu = 0;
    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302SettingMenuGuidelineActionTrigger : public IActionTrigger
{
public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        //can persist; Guideline is drawn by GPU, need not wait algo run;
        s302HmiElementShowImage[S302_SETTING_MENU_GUIDELINE_STATUS] = 1 - s302HmiElementShowImage[S302_SETTING_MENU_GUIDELINE_STATUS];

        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = CMD_GUIDE_LINE_BUTTON;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302SettingMenuReturnActionTrigger");


    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302SettingMenuModActionTrigger : public IActionTrigger
{
public:
    CS302SettingMenuModActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        //need delete, button should be control by SystemManager, NOT HMI;
        s302HmiElementShowImage[S302_SETTING_MENU_MOD_STATUS] = 1 - s302HmiElementShowImage[S302_SETTING_MENU_MOD_STATUS];

        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = ALGO_PD_BUTTON;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302SettingMenuModActionTrigger");



    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302SettingMenuTurnlampTriggerAvmActionTrigger : public IActionTrigger
{
public:
    CS302SettingMenuTurnlampTriggerAvmActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        s302HmiElementShowImage[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS] = 1 - s302HmiElementShowImage[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS];

        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = CMD_TURN_LIGHT_CONTRL_AVM;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302SettingMenuTurnlampTriggerAvmActionTrigger");

    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302SettingMenuRadarTriggerAvmActionTrigger : public IActionTrigger
{
public:
    CS302SettingMenuRadarTriggerAvmActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        s302HmiElementShowImage[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS] = 1 - s302HmiElementShowImage[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS];

        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = CMD_RADAR_CONTRL_AVM;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302SettingMenuTurnlampTriggerAvmActionTrigger");


    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302SettingMenuCalibrationActionTrigger : public IActionTrigger
{
public:
    CS302SettingMenuCalibrationActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        s302HmiElementShowImage[S302_SETTING_MENU_CALIBRATION_STATUS] = 1 ;

        Layout_Event_Payload_T* tmp_payload = NULL;
        tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
        memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
        
        tmp_payload->header.msg_id = ALGO_EOL_BUTTON;
        tmp_payload->body.onlyNotify = true;
        m_eventDel.PostEventPayload(tmp_payload);
        
        SAFE_FREE(tmp_payload);
        
        Log_Message("-----------CS302SettingMenuCalibrationActionTrigger");
    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302CtrlBtnHideActionTrigger : public IActionTrigger
{
public:
    CS302CtrlBtnHideActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        s302ShowCtrlBtns = 0;
    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

class CS302CtrlBtnShowActionTrigger : public IActionTrigger
{
public:
    CS302CtrlBtnShowActionTrigger()
    {
        ;
    }
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        int i = 0;
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
        s302ShowCtrlBtns = 1;
    }
    virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
    {

    }

private:
};

CSVS302MainHmi::CSVS302MainHmi(IUINode* pUiNode, int pUiNodeId): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
    memset(m_subHmiInitFlag, 0, S302_MENU_SUB_HMI_NUM * sizeof(unsigned char)); 
    memset(m_subHmiVisibility, 0, S302_MENU_SUB_HMI_NUM * sizeof(unsigned char));
    memset(m_subHmi, 0, S302_MENU_SUB_HMI_NUM * sizeof(ISVHmi*));
    memset(m_trigger, 0, S302_MAIN_ELEMENT_NUM * sizeof(IActionTrigger*));
	memset(m_baseButton, 0, S302_MAIN_ELEMENT_NUM * sizeof(HMIButton));
    memset(m_buttonVisibility, 0, S302_MAIN_ELEMENT_NUM * sizeof(unsigned char));
    memset(m_buttonShowImage, 0, S302_MAIN_ELEMENT_NUM * sizeof(unsigned char));
    memset(s302HmiElementShowImage, 0, S302_MAIN_ELEMENT_NUM * sizeof(unsigned char));
	m_carOpacity = 1.0;
/*
	m_licenseData.pos[0] = 0.0;
	m_licenseData.pos[1] = 0.0;
	m_licenseData.pos[2] = 0.0;
	m_licenseData.size[0] = 100.0;
	m_licenseData.size[1] = 100.0;
	m_licenseData.font_size = 60.0;
	m_licenseData.visibilityStatus = 1;
	m_licenseData.textColor[0] = 1.0;
	m_licenseData.textColor[1] = 1.0;
	m_licenseData.textColor[2] = 1.0;
	m_licenseData.fontTypeMtlName = new char[100];
	sprintf(m_licenseData.fontTypeMtlName,"%sBlackCh.dds",XR_RES); 
	m_licenseData.licenseMaterialType = Material_Glossy;
	CAvmRenderDataBase::GetInstance()->GetObjectViewNode(&m_licenseData.bindNode);

	m_licenese = new HMILicense(&m_licenseData);

	m_licenese->Update();
	m_licenese->SetBackgroundColor(0.24,0.2,0.48,1.0);
	m_licenese->SetFontSize(60.0);
	
	HMIPolygonBoxDataT polygonData;
	polygonData.renderRegion = REGION_3D;
	CAvmRenderDataBase::GetInstance()->GetObjectViewNode(&polygonData.renderNode);
	//AVMData::GetInstance()->GetStitchViewNode(&polygonData.renderNode);
	polygonData.polygonVertexNum = 4;
	polygonData.fillTextureName[0] = new char[50];
	sprintf(polygonData.fillTextureName[0],"%sCar/apa_left_parking_lot.dds",XR_RES);
	
	polygonData.fillTextureName[1] = new char[50];
	sprintf(polygonData.fillTextureName[1],"%sCar/plot_normal.dds",XR_RES);

	polygonData.fillTextureIndex = 0;
	polygonData.materialType = Material_Rigid_Texture;

	HMIPolygonBox* polygonBox = new HMIPolygonBox(&polygonData);
	float orig3dVertex[16] = {-240, 1000, -1050,280, 1000, -1050,-240,1200, -1050,280,1200, -1050,158,367,261,328};
	polygonBox->SetVisibility(0);
	polygonBox->Update(orig3dVertex,0);
	polygonBox->SetBoxImageEx(m_licenese->GetTextTextureId());*/
}

CSVS302MainHmi::~CSVS302MainHmi()
{
    /*for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
    {
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
		if(i != S302_REMIND_TXT
			&& i != S302_MAIN_MENU_BKG
			&& i != S302_SETTING_MENU_ITEMS)
        {
        	SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
		}
        if(i == S302_VIEW_STATUS_ICON)
        {
            for(int j = 0; j < 8; j++)
            SAFE_DELETE(m_baseButtonData[i].icon_file_name[j]);
        }
        SAFE_DELETE(m_trigger[i]);
        SAFE_DELETE(m_baseButton[i]);
    }*/
    int i = S302_BEV_CAR_ICON;
    SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
	SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
    SAFE_DELETE(m_baseButton[i]);
	for(i = S302_BEV_BK_ICON;i<=S302_VIEW180_RIGHT_CUTLINE;i++)
	{
		SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
    	SAFE_DELETE(m_baseButton[i]);
	}
}

int CSVS302MainHmi::SetHmiParams()
{
    for(int i=0; i< S302_MAIN_ELEMENT_NUM; i++)
    {
        m_baseButtonData[i].icon_type = STATIC_ICON;
        m_baseButtonData[i].show_flag = 1;
        m_buttonVisibility[i] = 1;
        m_baseButtonData[i].show_icon_num = 0;
        m_buttonShowImage[i] = 0;
    }
    for(int i=S302_SETTING_MENU_ITEMS; i< S302_MAIN_ELEMENT_NUM; i++)
    {
        m_baseButtonData[i].show_flag = 0;
        m_buttonVisibility[i] = 0;
    }
    m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[2] = new char [50];
    m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[3] = new char [50];
    m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[4] = new char [50];
    m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[5] = new char [50];
    m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[6] = new char [50];
    m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[7] = new char [50];

    sprintf(m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[0],"%sCar/s302_front_left.dds",XR_RES);
    sprintf(m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[1],"%sCar/s302_front_right.dds",XR_RES);
    sprintf(m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[2],"%sCar/s302_rear_left.dds",XR_RES);
    sprintf(m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[3],"%sCar/s302_rear_right.dds",XR_RES);
    sprintf(m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[4],"%sCar/s302_front120.dds",XR_RES);
    sprintf(m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[5],"%sCar/s302_front_left_right180.dds",XR_RES);
    sprintf(m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[6],"%sCar/s302_rear120.dds",XR_RES);
    sprintf(m_baseButtonData[S302_VIEW_STATUS_ICON].icon_file_name[7],"%sCar/s302_rear_left_right180.dds",XR_RES);

    m_baseButtonData[S302_REMIND_TXT].icon_file_name[0] = new char [50];
    sprintf(m_baseButtonData[S302_REMIND_TXT].icon_file_name[0],"%sCar/s302_remind_txt.dds",XR_RES);

    m_baseButtonData[S302_MAIN_MENU_BKG].icon_file_name[0] = new char [50];
    sprintf(m_baseButtonData[S302_MAIN_MENU_BKG].icon_file_name[0],"%sCar/s302_main_menu_bkg.dds",XR_RES);

    m_baseButtonData[S302_MAIN_MENU_EXIT_ICON].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_EXIT_ICON].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_EXIT_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    sprintf(m_baseButtonData[S302_MAIN_MENU_EXIT_ICON].icon_file_name[0],"%sCar/s302_exit_disable.dds",XR_RES);
    sprintf(m_baseButtonData[S302_MAIN_MENU_EXIT_ICON].icon_file_name[1],"%sCar/s302_exit_enable.dds",XR_RES);
    m_trigger[S302_MAIN_MENU_EXIT_ICON] = new CS302ExitMenuActionTrigger;

    m_baseButtonData[S302_MAIN_MENU_2D_VIEW_ENTER_ICON].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_2D_VIEW_ENTER_ICON].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_2D_VIEW_ENTER_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    sprintf(m_baseButtonData[S302_MAIN_MENU_2D_VIEW_ENTER_ICON].icon_file_name[0],"%sCar/s302_2d_view_disable.dds",XR_RES);
    sprintf(m_baseButtonData[S302_MAIN_MENU_2D_VIEW_ENTER_ICON].icon_file_name[1],"%sCar/s302_2d_view_enable.dds",XR_RES);
    m_trigger[S302_MAIN_MENU_2D_VIEW_ENTER_ICON] = new CS302Enter2dViewActionTrigger;

    m_baseButtonData[S302_MAIN_MENU_3D_VIEW_ENTER_ICON].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_3D_VIEW_ENTER_ICON].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_3D_VIEW_ENTER_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    sprintf(m_baseButtonData[S302_MAIN_MENU_3D_VIEW_ENTER_ICON].icon_file_name[0],"%sCar/s302_3d_view_disable.dds",XR_RES);
    sprintf(m_baseButtonData[S302_MAIN_MENU_3D_VIEW_ENTER_ICON].icon_file_name[1],"%sCar/s302_3d_view_enable.dds",XR_RES);
    m_trigger[S302_MAIN_MENU_3D_VIEW_ENTER_ICON] = new CS302Enter3dViewActionTrigger;

    m_baseButtonData[S302_MAIN_MENU_DVR_ENTER_ICON].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_DVR_ENTER_ICON].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_DVR_ENTER_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    sprintf(m_baseButtonData[S302_MAIN_MENU_DVR_ENTER_ICON].icon_file_name[0],"%sCar/s302_dvr_disable.dds",XR_RES);
    sprintf(m_baseButtonData[S302_MAIN_MENU_DVR_ENTER_ICON].icon_file_name[1],"%sCar/s302_dvr_enable.dds",XR_RES);
    m_trigger[S302_MAIN_MENU_DVR_ENTER_ICON] = new CS302EnterDvrActionTrigger;

    m_baseButtonData[S302_MAIN_MENU_SETTING_ICON].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_SETTING_ICON].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_MAIN_MENU_SETTING_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    sprintf(m_baseButtonData[S302_MAIN_MENU_SETTING_ICON].icon_file_name[0],"%sCar/s302_setting_disable.dds",XR_RES);
    sprintf(m_baseButtonData[S302_MAIN_MENU_SETTING_ICON].icon_file_name[1],"%sCar/s302_setting_enable.dds",XR_RES);
    m_trigger[S302_MAIN_MENU_SETTING_ICON] = new CS302SettingActionTrigger;

    m_baseButtonData[S302_SETTING_MENU_ITEMS].icon_file_name[0] = new char [50];
    sprintf(m_baseButtonData[S302_SETTING_MENU_ITEMS].icon_file_name[0],"%sCar/s302_setting_items.dds",XR_RES);

    m_baseButtonData[S302_SETTING_MENU_RETURN_ICON].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_SETTING_MENU_RETURN_ICON].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_SETTING_MENU_RETURN_ICON].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    sprintf(m_baseButtonData[S302_SETTING_MENU_RETURN_ICON].icon_file_name[0],"%sCar/s302_setting_return_disable.dds",XR_RES);
    sprintf(m_baseButtonData[S302_SETTING_MENU_RETURN_ICON].icon_file_name[1],"%sCar/s302_setting_return_enable.dds",XR_RES);
    m_trigger[S302_SETTING_MENU_RETURN_ICON] = new CS302SettingMenuReturnActionTrigger;

    m_baseButtonData[S302_SETTING_MENU_GUIDELINE_STATUS].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_SETTING_MENU_GUIDELINE_STATUS].icon_file_name[1] = new char [50];
    sprintf(m_baseButtonData[S302_SETTING_MENU_GUIDELINE_STATUS].icon_file_name[0],"%sCar/s302_close.dds",XR_RES);
    sprintf(m_baseButtonData[S302_SETTING_MENU_GUIDELINE_STATUS].icon_file_name[1],"%sCar/s302_open.dds",XR_RES);
    m_trigger[S302_SETTING_MENU_GUIDELINE_STATUS] = new CS302SettingMenuGuidelineActionTrigger;

    m_baseButtonData[S302_SETTING_MENU_MOD_STATUS].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_SETTING_MENU_MOD_STATUS].icon_file_name[1] = new char [50];
    sprintf(m_baseButtonData[S302_SETTING_MENU_MOD_STATUS].icon_file_name[0],"%sCar/s302_close.dds",XR_RES);
    sprintf(m_baseButtonData[S302_SETTING_MENU_MOD_STATUS].icon_file_name[1],"%sCar/s302_open.dds",XR_RES);
    m_trigger[S302_SETTING_MENU_MOD_STATUS] = new CS302SettingMenuModActionTrigger;

    m_baseButtonData[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS].icon_file_name[1] = new char [50];
    sprintf(m_baseButtonData[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS].icon_file_name[0],"%sCar/s302_close.dds",XR_RES);
    sprintf(m_baseButtonData[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS].icon_file_name[1],"%sCar/s302_open.dds",XR_RES);
    m_trigger[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS] = new CS302SettingMenuTurnlampTriggerAvmActionTrigger;

    m_baseButtonData[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS].icon_file_name[1] = new char [50];
    sprintf(m_baseButtonData[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS].icon_file_name[0],"%sCar/s302_close.dds",XR_RES);
    sprintf(m_baseButtonData[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS].icon_file_name[1],"%sCar/s302_open.dds",XR_RES);
    m_trigger[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS] = new CS302SettingMenuRadarTriggerAvmActionTrigger;

    m_baseButtonData[S302_SETTING_MENU_CALIBRATION_STATUS].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_SETTING_MENU_CALIBRATION_STATUS].icon_file_name[1] = new char [50];
    sprintf(m_baseButtonData[S302_SETTING_MENU_CALIBRATION_STATUS].icon_file_name[0],"%sCar/s302_calib_disable.dds",XR_RES);
    sprintf(m_baseButtonData[S302_SETTING_MENU_CALIBRATION_STATUS].icon_file_name[1],"%sCar/s302_calib_enable.dds",XR_RES);
    m_trigger[S302_SETTING_MENU_CALIBRATION_STATUS] = new CS302SettingMenuCalibrationActionTrigger;

    m_baseButtonData[S302_CONTROL_BUTTONS_HIDE].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_CONTROL_BUTTONS_HIDE].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_CONTROL_BUTTONS_HIDE].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    sprintf(m_baseButtonData[S302_CONTROL_BUTTONS_HIDE].icon_file_name[0],"%sCar/s302_ctrl_btn_hide_normal.dds",XR_RES);
    sprintf(m_baseButtonData[S302_CONTROL_BUTTONS_HIDE].icon_file_name[1],"%sCar/s302_ctrl_btn_hide_highlight.dds",XR_RES);
    m_trigger[S302_CONTROL_BUTTONS_HIDE] = new CS302CtrlBtnHideActionTrigger;

    m_baseButtonData[S302_CONTROL_BUTTONS_SHOW].icon_file_name[0] = new char [50];
    m_baseButtonData[S302_CONTROL_BUTTONS_SHOW].icon_file_name[1] = new char [50];
    m_baseButtonData[S302_CONTROL_BUTTONS_SHOW].animationStyle = BUTTON_FLASH_HIGHLIGHT;
    sprintf(m_baseButtonData[S302_CONTROL_BUTTONS_SHOW].icon_file_name[0],"%sCar/s302_ctrl_btn_show_normal.dds",XR_RES);
    sprintf(m_baseButtonData[S302_CONTROL_BUTTONS_SHOW].icon_file_name[1],"%sCar/s302_ctrl_btn_show_highlight.dds",XR_RES);
    m_trigger[S302_CONTROL_BUTTONS_SHOW] = new CS302CtrlBtnShowActionTrigger;

    for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
    {
        m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
        m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
        m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
        m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
        m_baseButtonData[i].delegate_func = NULL;
        m_baseButtonData[i].trigger = m_trigger[i];

        //m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
        //m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
    }

    return S302_MAIN_HMI_NORMAL;
}

int CSVS302MainHmi::Init(int window_width, int window_height)
{
    m_screenWidth = window_width;
    m_screenHeight = window_height;

    float heightInterval = 80.0;
    float stitchRegionWidth = window_width * 0.35;
    float stitchRegionHeight = window_height - heightInterval * 2.0;
    Region currentStitchRegion;
    CAvmRenderDataBase::GetInstance()->GetStitchViewRegion(&currentStitchRegion);
    stitchRegionWidth = currentStitchRegion.right - currentStitchRegion.left;
    stitchRegionHeight = currentStitchRegion.bottom- currentStitchRegion.top;
    heightInterval = (window_height - stitchRegionHeight) * 0.5;

    m_buttonSize[S302_VIEW_STATUS_ICON][BUTTON_SIZE_WIDTH] = 122.0;
    m_buttonSize[S302_VIEW_STATUS_ICON][BUTTON_SIZE_HEIGHT] = 116.0;
    m_buttonPos[S302_VIEW_STATUS_ICON][BUTTON_POS_X] = window_width - m_buttonSize[S302_VIEW_STATUS_ICON][BUTTON_SIZE_WIDTH];
    m_buttonPos[S302_VIEW_STATUS_ICON][BUTTON_POS_Y] = window_height - m_buttonSize[S302_VIEW_STATUS_ICON][BUTTON_SIZE_HEIGHT] - heightInterval - 10.0;

    m_buttonSize[S302_REMIND_TXT][BUTTON_SIZE_WIDTH] = 350.0;
    m_buttonSize[S302_REMIND_TXT][BUTTON_SIZE_HEIGHT] = 71.0;
    m_buttonPos[S302_REMIND_TXT][BUTTON_POS_X] = stitchRegionWidth + (window_width - stitchRegionWidth - m_buttonSize[S302_REMIND_TXT][BUTTON_SIZE_WIDTH]) * 0.5;
    m_buttonPos[S302_REMIND_TXT][BUTTON_POS_Y] = heightInterval;

    float mainMenuBkgWidth = 300.0;
    float mainMenuBkgHeight = window_height - heightInterval * 2.0;//560.0;
    m_buttonSize[S302_MAIN_MENU_BKG][BUTTON_SIZE_WIDTH] = mainMenuBkgWidth;
    m_buttonSize[S302_MAIN_MENU_BKG][BUTTON_SIZE_HEIGHT] = mainMenuBkgHeight;
    m_buttonPos[S302_MAIN_MENU_BKG][BUTTON_POS_X] = 0.0;
    m_buttonPos[S302_MAIN_MENU_BKG][BUTTON_POS_Y] = (window_height - mainMenuBkgHeight) * 0.5;

    float mainMenuBtnWidth = 202.0;
    float mainMenuBtnHeight = 82.0;
    int mainBtnNum = S302_MAIN_MENU_SETTING_ICON - S302_MAIN_MENU_EXIT_ICON + 1;
    float mainBtnDist = (mainMenuBkgHeight - 80.0)/mainBtnNum;
    for(int i =S302_MAIN_MENU_EXIT_ICON; i <= S302_MAIN_MENU_SETTING_ICON; i++)
    {
        m_buttonSize[i][BUTTON_SIZE_WIDTH] = mainMenuBtnWidth;
        m_buttonSize[i][BUTTON_SIZE_HEIGHT] = mainMenuBtnHeight;
        m_buttonPos[i][BUTTON_POS_X] = (mainMenuBkgWidth - mainMenuBtnWidth) * 0.5;
        m_buttonPos[i][BUTTON_POS_Y] = (window_height - mainMenuBkgHeight) * 0.5 + 40.0 + (mainBtnDist - mainMenuBtnHeight) * 0.5 + mainBtnDist * (i - S302_MAIN_MENU_EXIT_ICON);
    }

    float settingMenuBkgHeight = window_height - heightInterval * 2.0;//560.0;
    m_buttonSize[S302_SETTING_MENU_ITEMS][BUTTON_SIZE_WIDTH] = 630;
    m_buttonSize[S302_SETTING_MENU_ITEMS][BUTTON_SIZE_HEIGHT] = settingMenuBkgHeight;
    m_buttonPos[S302_SETTING_MENU_ITEMS][BUTTON_POS_X] = 0.0;
    m_buttonPos[S302_SETTING_MENU_ITEMS][BUTTON_POS_Y] = (window_height - settingMenuBkgHeight) * 0.5;

    m_buttonSize[S302_SETTING_MENU_RETURN_ICON][BUTTON_SIZE_WIDTH] = 260.0;
    m_buttonSize[S302_SETTING_MENU_RETURN_ICON][BUTTON_SIZE_HEIGHT] = 72.0;
    m_buttonPos[S302_SETTING_MENU_RETURN_ICON][BUTTON_POS_X] = 0.0;
    m_buttonPos[S302_SETTING_MENU_RETURN_ICON][BUTTON_POS_Y] = (window_height - settingMenuBkgHeight) * 0.5;

    float settingMenuSwitchWidth = 123.0;
    float settingMenuSwitchHeight = 51.0;
    int settingMenuSwitchNum = S302_SETTING_MENU_CALIBRATION_STATUS - S302_SETTING_MENU_GUIDELINE_STATUS + 1;
    float settingMenuSwitchDist = (settingMenuBkgHeight - 102.0)/settingMenuSwitchNum;
    for(int i = S302_SETTING_MENU_GUIDELINE_STATUS; i <= S302_SETTING_MENU_CALIBRATION_STATUS; i++)
    {
        m_buttonSize[i][BUTTON_SIZE_WIDTH] = settingMenuSwitchWidth;
        m_buttonSize[i][BUTTON_SIZE_HEIGHT] = settingMenuSwitchHeight;
        if(S302_SETTING_MENU_CALIBRATION_STATUS == i)
        {
            m_buttonSize[i][BUTTON_SIZE_WIDTH] = 137;
            m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 64;
        }
        m_buttonPos[i][BUTTON_POS_X] = m_buttonSize[S302_SETTING_MENU_ITEMS][BUTTON_SIZE_WIDTH] - 40.0 - m_buttonSize[i][BUTTON_SIZE_WIDTH];
        m_buttonPos[i][BUTTON_POS_Y] = (window_height - settingMenuBkgHeight) * 0.5 + 72.0 + (settingMenuSwitchDist - settingMenuSwitchHeight) * 0.5 + settingMenuSwitchDist * (i - S302_SETTING_MENU_GUIDELINE_STATUS);
        if(S302_SETTING_MENU_CALIBRATION_STATUS == i)
        {
            m_buttonPos[i][BUTTON_POS_Y] -= (64 - settingMenuSwitchHeight) * 0.5;
        }
    }

    float hide_show_button_width = 42.0;
    float hide_show_button_height = 45.0;
    for(int i = S302_CONTROL_BUTTONS_HIDE; i <= S302_CONTROL_BUTTONS_SHOW; i++)
    {
        m_buttonSize[i][BUTTON_SIZE_WIDTH] = hide_show_button_width;
        m_buttonSize[i][BUTTON_SIZE_HEIGHT] = hide_show_button_height;
        m_buttonPos[i][BUTTON_POS_X] = 0.0;
        m_buttonPos[i][BUTTON_POS_Y] = (window_height - hide_show_button_height) * 0.5;
    }

	InitSubHmi(S302_DEMO_DVR_HMI);

    /*m_textEditData.pos[0] = 200;
    m_textEditData.pos[1] = 110;
    m_textEditData.width = 85;
	m_textEditData.font_size = 85.0;
	m_textEditData.line_num = 1;
	m_textEditData.visibilityStatus = 1;
	m_textEditData.targetIndex = -1;
	m_textEditData.insertFlag = InsertFlag_Default;
	m_textEditData.fontTypeMtlName = XR_RES"text_box.ttf";
	m_textEditData.trigger = NULL;
	m_textEditData.textColor[0] = 1.0;
	m_textEditData.textColor[1] = 0.0;
	m_textEditData.textColor[2] = 0.0;
	m_textEditData.textContent[0] = new char[100];
	char* ptext0 = "1234";
	sprintf(m_textEditData.textContent[0],"%s", ptext0);    
    m_textEdit = new HmiTextEdit(&m_textEditData,m_uiNode);
    m_textEdit->SetVisibility(0);*/
	m_textEdit = NULL;



    //SetHmiParams();
	SetHmiGuideline();
    
    float bevCarPos[4];
    float bevRealCarPos[4];
    
    AVMData::GetInstance()->m_2D_lut->GetCarRect(&bevCarPos[0],rect_left);
    AVMData::GetInstance()->m_2D_lut->GetCarRect(&bevCarPos[1],rect_top);
    AVMData::GetInstance()->m_2D_lut->GetCarRect(&bevCarPos[2],rect_right);
    AVMData::GetInstance()->m_2D_lut->GetCarRect(&bevCarPos[3],rect_bottom);

    AVMData::GetInstance()->m_2D_lut->GetRealCarRect(&bevRealCarPos[0],rect_left);
    AVMData::GetInstance()->m_2D_lut->GetRealCarRect(&bevRealCarPos[1],rect_top);
    AVMData::GetInstance()->m_2D_lut->GetRealCarRect(&bevRealCarPos[2],rect_right);
    AVMData::GetInstance()->m_2D_lut->GetRealCarRect(&bevRealCarPos[3],rect_bottom);

	unsigned char carTransparentStatus = 0;
	CAvmRenderDataBase::GetInstance()->GetCarTransparentStatus(&carTransparentStatus);
	if(carTransparentStatus == 0)
	{
		m_carOpacity = 1.0;
	}
	else
	{
		m_carOpacity = 0.3;
	}
    
	int i = S302_BEV_BK_ICON;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = (bevCarPos[2] - bevCarPos[0]) * stitchRegionWidth * 0.5;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = (bevCarPos[1] - bevCarPos[3]) * stitchRegionHeight * 0.5;
	m_buttonPos[i][BUTTON_POS_X] = currentStitchRegion.left + stitchRegionWidth * 0.5 * (1 + bevCarPos[0]);
	m_buttonPos[i][BUTTON_POS_Y] = currentStitchRegion.top + stitchRegionHeight * 0.5 * (1 - bevCarPos[1]);
	
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 1;
	m_buttonVisibility[i] = 0;
	m_baseButtonData[i].show_icon_num = 0;
	m_buttonShowImage[i] = 0;

	m_baseButtonData[i].icon_file_name[0] = new char [50];
	m_baseButtonData[i].animationStyle = BUTTON_NOMAL;
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sgreen.dds",XR_RES);
	
	m_trigger[i] = NULL;
	
	m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
	m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
	m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
	m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
	m_baseButtonData[i].delegate_func = NULL;
	m_baseButtonData[i].trigger = NULL;

	m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode,m_carOpacity);
    m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);

	i = S302_BEV_CAR_ICON;
    m_buttonSize[i][BUTTON_SIZE_WIDTH] = (bevRealCarPos[2] - bevRealCarPos[0]) * stitchRegionWidth * 0.5 * 1.191;
    m_buttonSize[i][BUTTON_SIZE_HEIGHT] = (bevRealCarPos[1] - bevRealCarPos[3]) * stitchRegionHeight * 0.5;
    m_buttonPos[i][BUTTON_POS_X] = currentStitchRegion.left + stitchRegionWidth * 0.5 * (1 + bevRealCarPos[0]) - m_buttonSize[i][BUTTON_SIZE_WIDTH] * 0.09;
    m_buttonPos[i][BUTTON_POS_Y] = currentStitchRegion.top + stitchRegionHeight * 0.5 * (1 - bevRealCarPos[1]);
    
    m_baseButtonData[i].icon_type = STATIC_ICON;
    m_baseButtonData[i].show_flag = 1;
    m_buttonVisibility[i] = 0;
    m_baseButtonData[i].show_icon_num = 0;
    m_buttonShowImage[i] = 0;

    m_baseButtonData[i].icon_file_name[0] = new char [50];
	m_baseButtonData[i].icon_file_name[1] = new char [50];
    m_baseButtonData[i].animationStyle = BUTTON_NOMAL;
    sprintf(m_baseButtonData[i].icon_file_name[0],"%scar_icon_rx5.dds",XR_RES);
    sprintf(m_baseButtonData[i].icon_file_name[1],"%scar_icon_rx5.dds",XR_RES);
    //sprintf(m_baseButtonData[i].icon_file_name[1],"%scar_icon_rx5_black.dds",XR_RES);
	
    m_trigger[i] = NULL;
    
    m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
    m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
    m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
    m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
    m_baseButtonData[i].delegate_func = NULL;
    m_baseButtonData[i].trigger = NULL;
    
    //SetHmiParams();

    m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode,m_carOpacity);
    m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);

	i = S302_VIEW180_LEFT_CUTLINE;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 2.0;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 720.0;
	m_buttonPos[i][BUTTON_POS_X] = 340;
	m_buttonPos[i][BUTTON_POS_Y] = 0;
	
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 0;
	m_buttonVisibility[i] = 0;
	m_baseButtonData[i].show_icon_num = 0;
	m_buttonShowImage[i] = 0;

	m_baseButtonData[i].icon_file_name[0] = new char [50];
	m_baseButtonData[i].animationStyle = BUTTON_NOMAL;
	sprintf(m_baseButtonData[i].icon_file_name[0],"%scutline.dds",XR_RES);
	
	m_trigger[i] = NULL;
	
	m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
	m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
	m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
	m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
	m_baseButtonData[i].delegate_func = NULL;
	m_baseButtonData[i].trigger = NULL;

	m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
    m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);

    
	i = S302_VIEW180_RIGHT_CUTLINE;
	m_buttonSize[i][BUTTON_SIZE_WIDTH] = 2.0;
	m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 720.0;
	m_buttonPos[i][BUTTON_POS_X] = 1280 - 340 -2;
	m_buttonPos[i][BUTTON_POS_Y] = 0;
	
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 0;
	m_buttonVisibility[i] = 0;
	m_baseButtonData[i].show_icon_num = 0;
	m_buttonShowImage[i] = 0;

	m_baseButtonData[i].icon_file_name[0] = new char [50];
	m_baseButtonData[i].animationStyle = BUTTON_NOMAL;
	sprintf(m_baseButtonData[i].icon_file_name[0],"%scutline.dds",XR_RES);
	
	m_trigger[i] = NULL;
	
	m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
	m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
	m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
	m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
	m_baseButtonData[i].delegate_func = NULL;
	m_baseButtonData[i].trigger = NULL;

	m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
	m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);

    return S302_MAIN_HMI_NORMAL;
}

int CSVS302MainHmi::Update(Hmi_Message_T& hmiMsg)
{
    MainMenuDataT s302MainMenuData;
    memset(&s302MainMenuData, 0, sizeof(MainMenuDataT));

    CAvmRenderDataBase::GetInstance()->GetMainMenuStatus(&s302MainMenuData);

    if(s302MainMenuData.iconStatus[MAIN_MENU_PD] == 1)
    {
        s302HmiElementShowImage[S302_SETTING_MENU_MOD_STATUS] = BUTTON_ON_IMAGE;
    }
    else
    {
        s302HmiElementShowImage[S302_SETTING_MENU_MOD_STATUS] = BUTTON_OFF_IMAGE;
    }

    if(s302MainMenuData.iconStatus[MAIN_MENU_GUIDELINE] == 1)
    {
        s302HmiElementShowImage[S302_SETTING_MENU_GUIDELINE_STATUS] = BUTTON_ON_IMAGE;
    }
    else
    {
        s302HmiElementShowImage[S302_SETTING_MENU_GUIDELINE_STATUS] = BUTTON_OFF_IMAGE;
    }

    if(s302MainMenuData.iconStatus[MAIN_MENU_RADAR_CTRL_AVM] == 1)
    {
        s302HmiElementShowImage[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS] = BUTTON_ON_IMAGE;
    }
    else
    {
        s302HmiElementShowImage[S302_SETTING_MENU_RADAR_TRIGGER_AVM_STATUS] = BUTTON_OFF_IMAGE;
    }

    if(s302MainMenuData.iconStatus[MAIN_MENU_TURNLIGHT_CTRL_AVM] == 1)
    {
        s302HmiElementShowImage[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS] = BUTTON_ON_IMAGE;
    }
    else
    {
        s302HmiElementShowImage[S302_SETTING_MENU_TURNLAMP_TRIGGER_AVM_STATUS] = BUTTON_OFF_IMAGE;
    }

    if(s302MainMenuData.iconStatus[MAIN_MENU_EOL] == 1)
    {
        s302HmiElementShowImage[S302_SETTING_MENU_CALIBRATION_STATUS] = BUTTON_ON_IMAGE;
    }
    else
    {
        s302HmiElementShowImage[S302_SETTING_MENU_CALIBRATION_STATUS] = BUTTON_OFF_IMAGE;
    }

    if(s302MainMenuData.iconStatus[MAIN_MENU_DVR] == 1)
    {
        s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] = BUTTON_ON_IMAGE;
		s302HmiElementShowImage[S302_SETTING_MENU_MOD_STATUS] = BUTTON_OFF_IMAGE;
    }
	else
    {
        s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] = BUTTON_OFF_IMAGE;
    }

    //if(m_buttonShowImage[S302_SETTING_MENU_CALIBRATION_STATUS] == BUTTON_ON_IMAGE)
    {
        InitSubHmi(S302_DEMO_EOL_HMI);
        if(m_subHmi[S302_DEMO_EOL_HMI])
        {

            m_subHmiVisibility[S302_DEMO_EOL_HMI] = 1;
            m_subHmi[S302_DEMO_EOL_HMI]->Update(hmiMsg);
		
        }
    }

    if(s302HmiElementShowImage[S302_SETTING_MENU_MOD_STATUS] == BUTTON_ON_IMAGE)
    {
        InitSubHmi(S302_DEMO_MOD_HMI);
        if(m_subHmi[S302_DEMO_MOD_HMI])
        {

            m_subHmiVisibility[S302_DEMO_MOD_HMI] = 1;
            m_subHmi[S302_DEMO_MOD_HMI]->Update(hmiMsg);
        }
    }
    else
    {
        m_subHmiVisibility[S302_DEMO_MOD_HMI] = 0;
        FreeSubHmi(S302_DEMO_MOD_HMI);
    }

	
	if(s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] == BUTTON_ON_IMAGE)
    {
        InitSubHmi(S302_DEMO_DVR_HMI);
        if(m_subHmi[S302_DEMO_DVR_HMI])
        {
            m_subHmiVisibility[S302_DEMO_DVR_HMI] = 1;
            m_subHmi[S302_DEMO_DVR_HMI]->Update(hmiMsg);
        }
    }
    else
    {
        m_subHmiVisibility[S302_DEMO_DVR_HMI] = 0;
        //FreeSubHmi(S302_DEMO_DVR_HMI);
    }
	
	memset(m_buttonVisibility, 0, S302_MAIN_ELEMENT_NUM * sizeof(unsigned char));
    
    unsigned char currentViewStatus = 0;
    
    CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(currentViewStatus);

	
    m_buttonVisibility[S302_VIEW180_LEFT_CUTLINE] = 0;
    m_buttonVisibility[S302_VIEW180_RIGHT_CUTLINE] = 0;

    if(((currentViewStatus >= FRONT_SINGLE_VIEW && currentViewStatus <= FRONT_3D_VIEW)||
        (currentViewStatus >= BMW_LEFT_VIEW && currentViewStatus <= BMW_REAR_3D_VIEW)||
        (currentViewStatus >= BOSH_FRONT_VIEW && currentViewStatus <= BOSH_REAR_VIEW_TOP)||
        (currentViewStatus == LEFT_RIGHT_LINEAR_VIEW) || (currentViewStatus == TOUR_VIEW)) &&
		(s302MainMenuData.iconStatus[MAIN_MENU_DVR] == 0))
    {
        m_buttonVisibility[S302_BEV_BK_ICON] = 1;
        m_buttonVisibility[S302_BEV_CAR_ICON] = 1;
		
		VehInfoT vehInfo;

		CAvmRenderDataBase::GetInstance()->GetVehInfo(&vehInfo);

		//if(vehInfo.bodyStyle == 0)
		//{
			m_buttonShowImage[S302_BEV_CAR_ICON] = 0;

		//}
		//else if(vehInfo.bodyStyle == 1)
		//{	
		//	m_buttonShowImage[S302_BEV_CAR_ICON] = 1;
		//}
        
        Region currentStitchRegion;
        CAvmRenderDataBase::GetInstance()->GetStitchViewRegion(&currentStitchRegion);

        m_buttonVisibility[S302_VIEW180_LEFT_CUTLINE] = 1;
        m_baseButton[S302_VIEW180_LEFT_CUTLINE]->SetX(currentStitchRegion.right);
    }
    else
    {
        m_buttonVisibility[S302_BEV_BK_ICON] = 0;
        m_buttonVisibility[S302_BEV_CAR_ICON] = 0;
    }
    
	unsigned char carTransparentStatus = 0;
	CAvmRenderDataBase::GetInstance()->GetCarTransparentStatus(&carTransparentStatus);
	if(carTransparentStatus) {m_buttonVisibility[S302_BEV_BK_ICON] = 0;}

	if((currentViewStatus >= LINEAR_FRONT_180_DEGREE_VIEW && currentViewStatus <= LINEAR_REAR_180_DEGREE_VIEW) &&
		(s302MainMenuData.iconStatus[MAIN_MENU_DVR] == 0))
    {
        m_buttonVisibility[S302_VIEW180_LEFT_CUTLINE] = 1;
        m_buttonVisibility[S302_VIEW180_RIGHT_CUTLINE] = 1;
        m_baseButton[S302_VIEW180_LEFT_CUTLINE]->SetX(m_buttonPos[S302_VIEW180_LEFT_CUTLINE][BUTTON_POS_X]);
    }
    
    RefreshHmi();
	RefreshHmiGuideline();

    return S302_MAIN_HMI_NORMAL;
}

int CSVS302MainHmi::RefreshHmi()
{
    
    for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
    {
    	if(m_baseButton[i])
        {
        	m_baseButton[i]->SetShowIconNum(m_buttonShowImage[i]);
        	m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		}
    }
    for(int i = S302_MAIN_MENU_BKG; i <= S302_SETTING_MENU_CALIBRATION_STATUS; i++)
    {
        if(s302ShowCtrlBtns == 0
			&& m_baseButton[i])
        {
            m_baseButton[i]->SetVisibility(0);
        }
    }
    for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
    {
    	if(m_baseButton[i])
        {
        	m_baseButton[i]->Update();
		}
    }

    if(m_subHmi[S302_DEMO_EOL_HMI])
    {
        m_subHmi[S302_DEMO_EOL_HMI]->SetElementsVisibility(m_subHmiVisibility[S302_DEMO_EOL_HMI]);
    }
	
    if(m_subHmi[S302_DEMO_MOD_HMI])
    {
        m_subHmi[S302_DEMO_MOD_HMI]->SetElementsVisibility(m_subHmiVisibility[S302_DEMO_MOD_HMI]);
    }
	
	if(m_subHmi[S302_DEMO_SWITCH_VIEW_HMI])
    {
        m_subHmi[S302_DEMO_SWITCH_VIEW_HMI]->SetElementsVisibility(m_subHmiVisibility[S302_DEMO_SWITCH_VIEW_HMI]);
    }

	if(m_subHmi[S302_DEMO_DVR_HMI])
    {
        m_subHmi[S302_DEMO_DVR_HMI]->SetElementsVisibility(m_subHmiVisibility[S302_DEMO_DVR_HMI]);
    }

	if(m_textEdit)
	{
		unsigned int timeStamp = 0;
		CAvmRenderDataBase::GetInstance()->GetTimeStamp(timeStamp);
		sprintf(m_textEditData.textContent[0],"%d", timeStamp);
		m_textEdit->SetVisibility(1);
		m_textEdit->Update(m_textEditData.textContent[0]);
	}

    return S302_MAIN_HMI_NORMAL;
}

void CSVS302MainHmi::InitSubHmi(unsigned char pHmiIndex)
{
    if(m_subHmiInitFlag[pHmiIndex] == 0)
    {
        switch(pHmiIndex)
        {
            case S302_DEMO_EOL_HMI:
                m_subHmi[pHmiIndex] = new CSVDemoEolHmi(m_uiNode, m_uiNodeId);
            break;
            case S302_DEMO_MOD_HMI:
                m_subHmi[pHmiIndex] = new CSVS302PdHmi(m_uiNode, m_uiNodeId);
            break;
            case S302_DEMO_SWITCH_VIEW_HMI:
                m_subHmi[pHmiIndex] = new CSVChangAnSwitchViewHmi(m_uiNode, m_uiNodeId);
            break;
            case S302_DEMO_DVR_HMI:
                m_subHmi[pHmiIndex] = new CSVS302DvrBase(m_uiNode, m_uiNodeId);
            break;
            case S302_DEMO_GUIDELINE_HMI:
                //m_subHmi[pHmiIndex] = new CSVS302GuidelineHmi(m_uiNode, m_uiNodeId);
            break;
            default:
            break;
        }
        m_subHmi[pHmiIndex]->Init(m_screenWidth, m_screenHeight);
        m_subHmiVisibility[pHmiIndex] = 1;
        m_subHmiInitFlag[pHmiIndex] = 1;
    }

}
void CSVS302MainHmi::FreeSubHmi(unsigned char pHmiIndex)
{
    m_subHmiVisibility[pHmiIndex] = 0;
    SAFE_DELETE(m_subHmi[pHmiIndex]);
    m_subHmiInitFlag[pHmiIndex] = 0;
}


int CSVS302MainHmi::SetElementsVisibility(unsigned char pFlag)
{
    for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
    {
        if(pFlag == 0)
        {
            m_baseButton[i]->SetVisibility(0);
        }
        else
        {
            m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
        }
    }

    return S302_MAIN_HMI_NORMAL;
}

int CSVS302MainHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return S302_MAIN_HMI_NORMAL;
}

int CSVS302MainHmi::DestroyHmiElems()
{
    return S302_MAIN_HMI_NORMAL;
}
void CSVS302MainHmi::SetHmiGuideline()
{
    int i = 0;

    ISceneNode* m_avmViewNode = NULL;
    CAvmRenderDataBase::GetInstance()->GetStitchViewNode(&m_avmViewNode);
    ISceneNode* m_singleViewNode = NULL;
    CAvmRenderDataBase::GetInstance()->GetSingleViewNode(&m_singleViewNode);
	
	i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_L;
    m_guideLineData[i].guideLineEndPos = 6000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_POS_L";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 76.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 238.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

	i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_L1;
    m_guideLineData[i].guideLineEndPos = 6000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_POS_L1";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 225.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

	i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_L2;
    m_guideLineData[i].guideLineEndPos = 6000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_POS_L2";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 48.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

	i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_L3;
    m_guideLineData[i].guideLineEndPos = 6000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_POS_L3";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 48.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = -180.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

    i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_R;
    m_guideLineData[i].guideLineEndPos = 6000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_POS_R";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 76.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 238.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);

	i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_R1;
    m_guideLineData[i].guideLineEndPos = 6000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_POS_R1";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 225.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

	i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_R2;
    m_guideLineData[i].guideLineEndPos = 6000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_POS_R2";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 48.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = -180.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

	i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_R3;
    m_guideLineData[i].guideLineEndPos = 6000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_POS_R3";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 48.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

	i = DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L;
    m_guideLineData[i].guideLineEndPos = 10000.0;
	m_guideLineData[i].guideLineStartPos = 0.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_ASSIST_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 76.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 238.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 50;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);
	
	i = DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R;
    m_guideLineData[i].guideLineEndPos = 10000.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R";
    m_guideLineData[i].guideLineType = GUIDELINE_BEV_ASSIST_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 76.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 238.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLinePointNum = 50;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_avmViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

    i = DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L;
    m_guideLineData[i].guideLineEndPos = 4000.0;
	m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 26.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 212.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);  

    i = DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L1;
    m_guideLineData[i].guideLineEndPos = 4000.0;
	m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L1";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 225.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 20;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);    

	i = DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L2;
    m_guideLineData[i].guideLineEndPos = 4000.0;
	m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L2";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 18.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);  

	i = DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L3;
    m_guideLineData[i].guideLineEndPos = 4000.0;
	m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_L3";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_LEFT;
    m_guideLineData[i].guideLineWidth = 18.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = -210.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);    

    i = DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R;
    m_guideLineData[i].guideLineEndPos = 4000.0;
    m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 26.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 212.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);


    i = DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R1;
    m_guideLineData[i].guideLineEndPos = 4000.0;
	m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R1";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 225.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 20;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);   

	i = DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R2;
    m_guideLineData[i].guideLineEndPos = 4000.0;
	m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R2";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 18.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = -210.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);   

	i = DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R3;
    m_guideLineData[i].guideLineEndPos = 4000.0;
	m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R3";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
    m_guideLineData[i].guideLinePos = GUIDELINE_POS_RIGHT;
    m_guideLineData[i].guideLineWidth = 18.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 0.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 40;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/s302_dyn_orange_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]);  
    m_guideLine[i]->SetVisibility(1);   


	i = DEMO_GUIDELINE_SINGLEVIEW_SAVE_DIST;
    m_guideLineData[i].guideLineEndPos = 4000.0;
    m_guideLineData[i].guideLineStartPos = 500.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_SAVE_DIST";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_SAVE_DYNAMIC;
    m_guideLineData[i].guideLineWidth = 20.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 212.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 500.0;
    m_guideLineData[i].guideLinePointNum = 50;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/ep21_dyn_red_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(1);

	/*i = DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST;
    m_guideLineData[i].guideLineEndPos = 3000.0;
    m_guideLineData[i].guideLineName = "DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST";
    m_guideLineData[i].guideLineType = GUIDELINE_SINGLEVIEW_SAVE_DYNAMIC;
	m_guideLineData[i].customPropt = GUIDELINE_SECTIONAL_TYPE;
    m_guideLineData[i].guideLineWidth = 230.0;
    m_guideLineData[i].guideLineSideDistanceFromVehicle = 200.0;
    m_guideLineData[i].guideLineStartDistanceFromVehicle = 200.0;
    m_guideLineData[i].guideLinePointNum = 50;
    m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
    sprintf(m_guideLineData[i].guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/ep21_dyn_line.dds",XR_RES);
    m_guideLineData[i].guideLineTextureType = Material_Rigid_Blend;
    m_guideLine[i] = new HMIGuideLine(m_singleViewNode, &m_guideLineData[i]); 
    m_guideLine[i]->SetVisibility(0);*/

//    Log_Error("===============SetHmiGuideline==============");
}

void CSVS302MainHmi::RefreshHmiGuideline()
{
	if(s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] == BUTTON_ON_IMAGE)
	{	
		for(int i = DEMO_GUIDELINE_SINGLEVIEW_SAVE_DIST; i <= DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R3; i++)
		{
			if(i != DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST) 	
			{
				m_guideLine[i]->SetVisibility(0);
			}
		}

		for (int i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_L; i <= DEMO_GUIDELINE_BEV_DYNAMIC_POS_R3; i++)
		{
			{
				m_guideLine[i]->SetVisibility(0);
			}
		}
		m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L]->SetVisibility(0);
		m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R]->SetVisibility(0);
		return;
	}
    float steer_angle = 100.0;
    unsigned char gear_state = GEAR_R;
    unsigned char m_displayViewCmd = FRONT_SINGLE_VIEW;
	unsigned char carTransparentStatus = 0;
	//const unsigned char GEAR_SHIFT_R = 1;
    
    static int m_cnt = -500;

	CAvmRenderDataBase::GetInstance()->GetCarTransparentStatus(&carTransparentStatus);
	AVMData::GetInstance()->m_p_can_data->Get_Steer_Angle(&steer_angle);	
	AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(m_displayViewCmd);

	//steer_angle = m_cnt;
	//if(m_cnt > 500) m_cnt = -500;

	//m_cnt += 2;
	//Log_Message("steer_angle: %0.4f, gear_state: %d", steer_angle,gear_state);

	steer_angle = 0.0 - steer_angle;

	if(steer_angle > 600.0)
	{
		steer_angle = 600.0;
	}
	else if(steer_angle < -600.0)
	{
		steer_angle = -600.0;
	}
	
	m_singleViewDynGuideLineVisibility = 0;

    if(m_displayViewCmd == FRONT_SINGLE_VIEW)
    {    
        for (int i = DEMO_GUIDELINE_SINGLEVIEW_SAVE_DIST; i <= DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R3; i++)
        {
	        if(i != DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST)
            {
            	m_guideLine[i]->Update(steer_angle, GUIDELINE_DIR_FORWARD);
			}
        }
		m_singleViewDynGuideLineVisibility = 1;
    }   
    else if(m_displayViewCmd == REAR_SINGLE_VIEW)
    {    
        for (int i = DEMO_GUIDELINE_SINGLEVIEW_SAVE_DIST; i <= DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R3; i++)
        {
	        if(i != DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST)	
            {
            	m_guideLine[i]->Update(steer_angle, GUIDELINE_DIR_BACKWARD);
			}
        }
		m_singleViewDynGuideLineVisibility = 1;
    }
    else
    {
        m_singleViewDynGuideLineVisibility = 0;
    }


	for(int i = DEMO_GUIDELINE_SINGLEVIEW_SAVE_DIST; i <= DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R3; i++)
	{
		if(i != DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST)		
		{
			m_guideLine[i]->SetVisibility(m_singleViewDynGuideLineVisibility);
		}
	}

	//m_guideLine[DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST]->SetVisibility(0);

	if(carTransparentStatus == 0)
	{
	m_bevDynGuideLineVisibility = 1;
	m_bevDynOutLGuideLineVisibility = 0;
	m_bevDynOutRGuideLineVisibility = 0;
	m_bevAsitLDynGuideLineVisibility = 0;
	m_bevAsitRDynGuideLineVisibility = 0;
	
    for (int i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_L; i <= DEMO_GUIDELINE_BEV_DYNAMIC_POS_R3; i++)
    {
    	/*if(i == DEMO_GUIDELINE_BEV_DYNAMIC_POS_L
			|| i == DEMO_GUIDELINE_BEV_DYNAMIC_POS_L1
			|| i == DEMO_GUIDELINE_BEV_DYNAMIC_POS_R
			|| i == DEMO_GUIDELINE_BEV_DYNAMIC_POS_R1)*/
		{
	        if(gear_state == GEAR_R)
	        {
	            m_guideLine[i]->Update(steer_angle, GUIDELINE_DIR_BACKWARD);
	        }
	        else
	        {
	            m_guideLine[i]->Update(steer_angle, GUIDELINE_DIR_FORWARD);
	        }	
		}

    }
    if(gear_state == GEAR_R)
    {
		if(steer_angle > 1.0)
		{
			m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L]->Update(steer_angle, GUIDELINE_DIR_BACKWARD);
			m_bevAsitLDynGuideLineVisibility = 1;
			m_bevDynOutLGuideLineVisibility = 0;
			m_bevAsitRDynGuideLineVisibility = 0;
			m_bevDynOutRGuideLineVisibility = 1;
		}
		else if(steer_angle < -1.0)
		{
			m_bevAsitLDynGuideLineVisibility = 0;
			m_bevDynOutLGuideLineVisibility = 1;
			m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R]->Update(steer_angle, GUIDELINE_DIR_BACKWARD);
			m_bevAsitRDynGuideLineVisibility = 1;
			m_bevDynOutRGuideLineVisibility = 0;
		}

		else if(steer_angle <= 1.0
            && steer_angle >= -1.0)
        {
            m_bevAsitLDynGuideLineVisibility = 0;
			m_bevDynOutLGuideLineVisibility = 1;
            m_bevAsitRDynGuideLineVisibility = 0;
			m_bevDynOutRGuideLineVisibility = 1;
        }


	}
    else
    {
		if(steer_angle > 1.0)
		{
			m_bevAsitLDynGuideLineVisibility = 0;
			m_bevDynOutLGuideLineVisibility = 1;
			m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R]->Update(steer_angle, GUIDELINE_DIR_FORWARD);
			m_bevAsitRDynGuideLineVisibility = 1;
			m_bevDynOutRGuideLineVisibility = 0;
		}
		else if(steer_angle < -1.0)
		{
			m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L]->Update(steer_angle, GUIDELINE_DIR_FORWARD);
			m_bevAsitLDynGuideLineVisibility = 1;
			m_bevDynOutLGuideLineVisibility = 0;
			m_bevAsitRDynGuideLineVisibility = 0;
			m_bevDynOutRGuideLineVisibility = 1;
		}

		else if(steer_angle <= 1.0
            && steer_angle >= -1.0)
        {
            m_bevAsitLDynGuideLineVisibility = 0;
			m_bevDynOutLGuideLineVisibility = 1;
            m_bevAsitRDynGuideLineVisibility = 0;
			m_bevDynOutRGuideLineVisibility = 1;
        }

	}   
    for (int i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_L1; i <= DEMO_GUIDELINE_BEV_DYNAMIC_POS_R3; i++)
    {
    	if(i != DEMO_GUIDELINE_BEV_DYNAMIC_POS_R)
        {
       		m_guideLine[i]->SetVisibility(m_bevDynGuideLineVisibility);
		}
    }
	m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_POS_L]->SetVisibility(m_bevDynOutLGuideLineVisibility);
	m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_POS_R]->SetVisibility(m_bevDynOutRGuideLineVisibility);
	m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L]->SetVisibility(m_bevAsitLDynGuideLineVisibility);
	m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R]->SetVisibility(m_bevAsitRDynGuideLineVisibility);
	}
	
	unsigned char guideLineVisibility = 0;
	CAvmRenderDataBase::GetInstance()->GetGuideLineCmd(guideLineVisibility);

	if(guideLineVisibility == GUIDE_LINE_CMD_NOT_ACTIVE
		|| guideLineVisibility == GUIDE_LINE_CMD_CLOSE)
	{
		for(int i = DEMO_GUIDELINE_SINGLEVIEW_SAVE_DIST; i <= DEMO_GUIDELINE_SINGLEVIEW_DYNAMIC_POS_R3; i++)
		{
			if(i != DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST)		
			{
				m_guideLine[i]->SetVisibility(0);
			}
		}
		//m_guideLine[DEMO_GUIDELINE_SINGLEVIEW_MAX_DIST]->SetVisibility(0);

		for (int i = DEMO_GUIDELINE_BEV_DYNAMIC_POS_L; i <= DEMO_GUIDELINE_BEV_DYNAMIC_POS_R3; i++)
	    {
	        {
	       		m_guideLine[i]->SetVisibility(0);
			}
	    }
		m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L]->SetVisibility(0);
		m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R]->SetVisibility(0);
	}

}
void CSVS302MainHmi::ResetGuideLineEndPos(float pSteerAngle)
{
	float resetEndPos = 5000.0;
	unsigned char gear_state = GEAR_R;
	AVMData::GetInstance()->m_p_can_data->Get_Gear_State(&gear_state);
	if(gear_state != GEAR_R)
	{
		if(pSteerAngle > 300.0
			|| pSteerAngle < -300.0)
		{
			resetEndPos = 5000.0;
			m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L]->ResetEndPos(resetEndPos);
			m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R]->ResetEndPos(resetEndPos);	
		}
		else
		{
			resetEndPos = 10000.0;
			m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L]->ResetEndPos(resetEndPos);
			m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R]->ResetEndPos(resetEndPos);	
		
		}
	}
	else if(gear_state == GEAR_R)
	{
		resetEndPos = 10000.0;
		m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_L]->ResetEndPos(resetEndPos);
		m_guideLine[DEMO_GUIDELINE_BEV_DYNAMIC_ASSI_R]->ResetEndPos(resetEndPos);
	}
}

void CSVS302MainHmi::MockRefreshLicense()
{
	static int cnt = 0;
	static int frameCnt = 0;
	static char* pTextContent  = new char[50];

	char avd, avd2;

	if(frameCnt%25 == 0)
	{
		m_licenese->SetChineseText(cnt % 34);	

		if(cnt % 3 == 0)
		{
			avd = 'D';
			avd2 = 'F';
		}
		else
		{
			avd = 'A';
			avd2 = 'E';
		}
		
		sprintf(pTextContent, "%c-%c%d345", avd, avd2, cnt%10);
		m_licenese->SetNumText(pTextContent);
		cnt ++;
	}
	frameCnt ++;

}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  01/18/18   Chunh Huang   Create the CSVS302MainHmi class.
 *  01/21/18   Jensen Wang   Add the avm event.
\*===========================================================================*/
