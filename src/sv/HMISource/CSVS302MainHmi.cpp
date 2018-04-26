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
#include "CSVS302GuidelineHmi.h"

static unsigned char s302HmiElementShowImage[S302_MAIN_ELEMENT_NUM];
static unsigned char s302ShowSettingMenu = 0;
static unsigned char s302ShowCtrlBtns = 0;

static CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);

REGISTER_HMI_CLASS(CSVS302MainHmi)

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
        
        Log_Message("-----------CS302EnterDvrActionTrigger");
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

CSVS302MainHmi::CSVS302MainHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
    memset(m_subHmiInitFlag, 0, S302_MENU_SUB_HMI_NUM * sizeof(unsigned char)); 
    memset(m_subHmiVisibility, 0, S302_MENU_SUB_HMI_NUM * sizeof(unsigned char));
    memset(m_subHmi, NULL, S302_MENU_SUB_HMI_NUM * sizeof(ISVHmi*));
    memset(m_trigger, 0, S302_MAIN_ELEMENT_NUM * sizeof(IActionTrigger*));
    memset(m_buttonVisibility, 0, S302_MAIN_ELEMENT_NUM * sizeof(unsigned char));
    memset(m_buttonShowImage, 0, S302_MAIN_ELEMENT_NUM * sizeof(unsigned char));
    memset(s302HmiElementShowImage, 0, S302_MAIN_ELEMENT_NUM * sizeof(unsigned char));
}

CSVS302MainHmi::~CSVS302MainHmi()
{
    for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
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

        m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
        m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
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

    SetHmiParams();

    return S302_MAIN_HMI_NORMAL;
}

int CSVS302MainHmi::Update(Hmi_Message_T& hmiMsg)
{
//Log_Error("CSVS302MainHmi::Update");
    MainMenuDataT s302MainMenuData;
    memset(&s302MainMenuData, 0, sizeof(S302MainMenuDataT));

    //debug code,need delete;
    /*static unsigned char initflag = 0;
    if(initflag == 0)
    {
        s302MainMenuData.menuVisibility = 1;
        CAvmRenderDataBase::GetInstance()->SetS302MainMenuStatus(&s302MainMenuData);
        initflag=1;
    }*/

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
    }
	else
    {
        s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] = BUTTON_OFF_IMAGE;
    }

    for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
    {
        m_buttonVisibility[i] = 1;
    }

    if(s302ShowSettingMenu == 1)
    {
        for(int i = S302_MAIN_MENU_BKG; i <= S302_MAIN_MENU_SETTING_ICON; i++)
        {
            m_buttonVisibility[i] = 0;
        }
    }
    else if(s302ShowSettingMenu == 0)
    {
        for(int i = S302_SETTING_MENU_ITEMS; i <= S302_SETTING_MENU_CALIBRATION_STATUS; i++)
        {
            m_buttonVisibility[i] = 0;
        }
    }
    
    for(int i = S302_SETTING_MENU_ITEMS; i <= S302_SETTING_MENU_CALIBRATION_STATUS; i++)
    {
        m_buttonShowImage[i] = s302HmiElementShowImage[i];
    }

    if(s302ShowCtrlBtns == 0)
    {
        m_buttonVisibility[S302_CONTROL_BUTTONS_HIDE] = 0;
    }
    else if(s302ShowCtrlBtns == 1)
    {
        m_buttonVisibility[S302_CONTROL_BUTTONS_SHOW] = 0;
    }

    unsigned char currentViewType = 0;
    CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(currentViewType);
    switch(currentViewType)
    {
        case FRONT_SINGLE_VIEW:
            m_buttonShowImage[S302_VIEW_STATUS_ICON] = S302_FRONT120_ICON;
            break;
        case REAR_SINGLE_VIEW:
            m_buttonShowImage[S302_VIEW_STATUS_ICON] = S302_REAR120_ICON;
            break;
        case LINEAR_FRONT_180_DEGREE_VIEW:
            m_buttonShowImage[S302_VIEW_STATUS_ICON] = S302_FRONT_LEFT_RIGHT180_ICON;
            break;
        case LINEAR_REAR_180_DEGREE_VIEW:
            m_buttonShowImage[S302_VIEW_STATUS_ICON] = S302_REAR_LEFT_RIGHT180_ICON;
            break;
        default:
            m_buttonVisibility[S302_VIEW_STATUS_ICON] = 0;
            break;
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

    InitSubHmi(S302_DEMO_SWITCH_VIEW_HMI);
    if(m_subHmi[S302_DEMO_SWITCH_VIEW_HMI])
    {
        m_subHmiVisibility[S302_DEMO_SWITCH_VIEW_HMI] = 1;
        m_subHmi[S302_DEMO_SWITCH_VIEW_HMI]->Update(hmiMsg);
    }

	/*if(s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] == BUTTON_ON_IMAGE)
	{
		unsigned char m_tmpRGB[192 * 112 * 3];
		memset(&m_tmpRGB, 0, 192 * 112 * 3);

		GUI_OBJ_THUMB_ITEM_EXT tmp = {"1234213424", m_tmpRGB, 192, 112, 1, 1};
		GUI_OBJ_THUMB_FRAME_INST_EXT tmpInst;
		tmpInst.item[0] = tmp;
		tmpInst.item[1] = tmp;
		tmpInst.item[2] = tmp;
		tmpInst.item[3] = tmp;
		tmpInst.item[4] = tmp;
		tmpInst.item[5] = tmp;

		
      	DVR_GRAPHIC_UIOBJ_EXT table[] = {
			{GUI_OBJ_ID_THUMB_FRAME_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
			{GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
			{GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
			{GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
			{GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
			{GUI_OBJ_ID_THUMB_TAB_EXT, "asdsfsd", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER_EXT, (void*)&tmpInst},
      		};

    	DVR_GUI_LAYOUT_INST_EXT dvrData;
		dvrData.curLayout = GUI_LAYOUT_THUMB_EXT;
		dvrData.ObjNum = 6;
		for(int i = 0; i < dvrData.ObjNum; i++)
		{
			dvrData.pTable = table;
		}
		
		CAvmRenderDataBase::GetInstance()->SetDvrData(&dvrData);
	}*/

	s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] = BUTTON_ON_IMAGE;

	#if 1
	if(s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] == BUTTON_ON_IMAGE)
    {
		
        InitSubHmi(S302_DEMO_DVR_FILELIST_HMI);
        if(m_subHmi[S302_DEMO_DVR_FILELIST_HMI])
        {
            m_subHmiVisibility[S302_DEMO_DVR_FILELIST_HMI] = 1;
            m_subHmi[S302_DEMO_DVR_FILELIST_HMI]->Update(hmiMsg);
        }
    }
    else
    {
        m_subHmiVisibility[S302_DEMO_DVR_FILELIST_HMI] = 0;
        FreeSubHmi(S302_DEMO_DVR_FILELIST_HMI);
    }
    #endif

    /*InitSubHmi(S302_DEMO_GUIDELINE_HMI);
    if(m_subHmi[S302_DEMO_GUIDELINE_HMI])
    {
        m_subHmiVisibility[S302_DEMO_GUIDELINE_HMI] = 1;
        m_subHmi[S302_DEMO_GUIDELINE_HMI]->Update(hmiMsg);
    }*/

    /*if(s302HmiElementShowImage[S302_MAIN_MENU_DVR_ENTER_ICON] == BUTTON_ON_IMAGE
		&& hmiMsg.dvrTabMsg.playbackMode != 1)
    {
        char* hmiName = "CSVDvrBaseHmi";
        CSVHmiIntent::GetInstance()->Intent(hmiName);
    }*/


    if(s302MainMenuData.menuVisibility == 0)
    {
        //memset(m_subHmiVisibility, 0, S302_MENU_SUB_HMI_NUM * sizeof(unsigned char));
        //memset(m_buttonVisibility, 0, S302_MAIN_ELEMENT_NUM * sizeof(unsigned char));
    }

    RefreshHmi();

    return S302_MAIN_HMI_NORMAL;
}

int CSVS302MainHmi::RefreshHmi()
{
    
    for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
    {
        m_baseButton[i]->SetShowIconNum(m_buttonShowImage[i]);
        m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
    }
    for(int i = S302_MAIN_MENU_BKG; i <= S302_SETTING_MENU_CALIBRATION_STATUS; i++)
    {
        if(s302ShowCtrlBtns == 0)
        {
            m_baseButton[i]->SetVisibility(0);
        }
    }
    for(int i = 0; i < S302_MAIN_ELEMENT_NUM; i++)
    {
        m_baseButton[i]->Update();
    }

    if(m_subHmi[S302_DEMO_EOL_HMI])
    {
        m_subHmi[S302_DEMO_EOL_HMI]->SetElementsVisibility(m_subHmiVisibility[S302_DEMO_EOL_HMI]);
    }

	if(m_subHmi[S302_DEMO_SWITCH_VIEW_HMI])
    {
        m_subHmi[S302_DEMO_SWITCH_VIEW_HMI]->SetElementsVisibility(m_subHmiVisibility[S302_DEMO_SWITCH_VIEW_HMI]);
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
            case S302_DEMO_SWITCH_VIEW_HMI:
                m_subHmi[pHmiIndex] = new CSVChangAnSwitchViewHmi(m_uiNode, m_uiNodeId);
            break;
            case S302_DEMO_DVR_FILELIST_HMI:
                m_subHmi[pHmiIndex] = new CSVDvrFileListHmi(m_uiNode, m_uiNodeId);
            break;
            case S302_DEMO_GUIDELINE_HMI:
                m_subHmi[pHmiIndex] = new CSVS302GuidelineHmi(m_uiNode, m_uiNodeId);
            break;
            //case S302_DEMO_DVR_HMI:
            //    m_subHmi[pHmiIndex] = new CSVDvrBaseHmi(m_uiNode, m_uiNodeId);
            //    break;
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

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  01/18/18   Chunh Huang   Create the CSVS302MainHmi class.
 *  01/21/18   Jensen Wang   Add the avm event.
\*===========================================================================*/
