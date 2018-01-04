/*===========================================================================*\
 * FILE: CSVDemoMainHmi.cpp
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
#include "CSVDemoMainHmi.h"
#include "CSVDemoLkaHmi.h"
#include "CSVHmiIntent.h"

REGISTER_HMI_CLASS(CSVDemoMainHmi)

class CMainSettingActionTrigger : public IActionTrigger
{
public:
	CMainSettingActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{

		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

private:
};

class CMainLdwActionTrigger : public IActionTrigger
{
public:
	virtual Void OnPress(Int32 id)
	{
		CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);
	
		Layout_Event_Payload_T* tmp_payload = NULL;
		tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
		memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));

		tmp_payload->header.msg_id = ALGO_LDW_BUTTON;
		tmp_payload->body.onlyNotify = true;
		m_eventDel.PostEventPayload(tmp_payload);

		SAFE_FREE(tmp_payload);

		Log_Message("-----------CMainLdwActionTrigger");

	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainLkaActionTrigger : public IActionTrigger
{
public:
	CMainLkaActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainLcActionTrigger : public IActionTrigger
{
public:
	CMainLcActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainBsdActionTrigger : public IActionTrigger
{
public:
	CMainBsdActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);
	
		Layout_Event_Payload_T* tmp_payload = NULL;
		tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
		memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
		tmp_payload->header.msg_id = ALGO_BSD_BUTTON;
		tmp_payload->body.onlyNotify = true;
		m_eventDel.PostEventPayload(tmp_payload);
	
		SAFE_FREE(tmp_payload);

		Log_Message("-----------CMainLdwActionTrigger");
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainParkingInActionTrigger : public IActionTrigger
{
public:
	CMainParkingInActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);
	
		Layout_Event_Payload_T* tmp_payload = NULL;
		tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
		memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
		tmp_payload->header.msg_id = ALGO_APA_IN_BUTTON;
		tmp_payload->body.onlyNotify = true;
		m_eventDel.PostEventPayload(tmp_payload);
	
		SAFE_FREE(tmp_payload);
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainParkingOutActionTrigger : public IActionTrigger
{
public:
	CMainParkingOutActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);
	
		Layout_Event_Payload_T* tmp_payload = NULL;
		tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
		memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
		tmp_payload->header.msg_id = ALGO_APA_OUT_BUTTON;
		tmp_payload->body.onlyNotify = true;
		m_eventDel.PostEventPayload(tmp_payload);
	
		SAFE_FREE(tmp_payload);
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainTrainedParkingActionTrigger : public IActionTrigger
{
public:
	CMainTrainedParkingActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainCtaActionTrigger : public IActionTrigger
{
public:
	CMainCtaActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);
	
		Layout_Event_Payload_T* tmp_payload = NULL;
		tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
		memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
		tmp_payload->header.msg_id = ALGO_CTA_BUTTON;
		tmp_payload->body.onlyNotify = true;
		m_eventDel.PostEventPayload(tmp_payload);
	
		SAFE_FREE(tmp_payload);
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainPdActionTrigger : public IActionTrigger
{
public:
	CMainPdActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

class CMainDvrActionTrigger : public IActionTrigger
{
public:
	CMainDvrActionTrigger()
	{ 
	}
	virtual Void OnPress(Int32 id)
	{
		CGpuAvmEventDelegate m_eventDel(ALGOHMI_EVENT_NAME);
	
		Layout_Event_Payload_T* tmp_payload = NULL;
		tmp_payload = (Layout_Event_Payload_T*) malloc(sizeof(Layout_Event_Payload_T));
		memset(tmp_payload, 0, sizeof(Layout_Event_Payload_T));
		tmp_payload->header.msg_id = ALGO_RECORD_BUTTON;
		tmp_payload->body.onlyNotify = true;
		m_eventDel.PostEventPayload(tmp_payload);
	
		SAFE_FREE(tmp_payload);
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}

	

private:
};

CSVDemoMainHmi::CSVDemoMainHmi():m_lkaLcInitFlag(0),m_lkaLcHmi(0)
{
	memset(m_trigger, NULL, DEMO_MAIN_ELEMENT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonVisibility, 1, DEMO_MAIN_ELEMENT_NUM * sizeof(unsigned char));	
	memset(m_buttonImage, 0, DEMO_MAIN_ELEMENT_NUM * sizeof(unsigned char));

}

CSVDemoMainHmi::~CSVDemoMainHmi()
{
	for(int i = 0; i < DEMO_MAIN_ELEMENT_NUM; i++)
	{
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
	    if(i > DEMO_MAIN_MENU_BKG)
		{
			SAFE_DELETE(m_baseButtonData[i].icon_file_name[1]);
		}
		SAFE_DELETE(m_baseButton[i]);
		SAFE_DELETE(m_trigger[i]);
	}

	
	Log_Error("----------Release ~CSVChangAnMainHmi!");
}
	
int CSVDemoMainHmi::SetHmiParams()
{
	m_baseButtonData[DEMO_MAIN_MENU_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DEMO_MAIN_MENU_BKG].show_flag = 1;
	m_baseButtonData[DEMO_MAIN_MENU_BKG].show_icon_num = 0;
	m_baseButtonData[DEMO_MAIN_MENU_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_BKG].icon_file_name[0],"%sCar/MAIN/demo_menu_bkg.dds",XR_RES);

	for(int i = DEMO_MAIN_MENU_SETTING; i <= DEMO_MAIN_MENU_DVR; i++)
	{
		m_baseButtonData[i].icon_type = STATIC_ICON;
		m_baseButtonData[i].show_flag = 1;
		m_baseButtonData[i].show_icon_num = 0;
		m_baseButtonData[i].icon_file_name[0] = new char[50];
		m_baseButtonData[i].icon_file_name[1] = new char[50];	
	}

	sprintf(m_baseButtonData[DEMO_MAIN_MENU_SETTING].icon_file_name[0],"%sCar/MAIN/setting_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_SETTING].icon_file_name[1],"%sCar/MAIN/setting_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_SETTING] = new CMainSettingActionTrigger;

	sprintf(m_baseButtonData[DEMO_MAIN_MENU_LDW].icon_file_name[0],"%sCar/MAIN/ldw_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_LDW].icon_file_name[1],"%sCar/MAIN/ldw_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_LDW] = new CMainLdwActionTrigger;

	sprintf(m_baseButtonData[DEMO_MAIN_MENU_LKA].icon_file_name[0],"%sCar/MAIN/lka_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_LKA].icon_file_name[1],"%sCar/MAIN/lka_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_LKA] = new CMainLkaActionTrigger;
	
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_LC].icon_file_name[0],"%sCar/MAIN/lc_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_LC].icon_file_name[1],"%sCar/MAIN/lc_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_LC] = new CMainLcActionTrigger;
	
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_BSD].icon_file_name[0],"%sCar/MAIN/bsd_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_BSD].icon_file_name[1],"%sCar/MAIN/bsd_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_BSD] = new CMainBsdActionTrigger;

	sprintf(m_baseButtonData[DEMO_MAIN_MENU_PARKING_I].icon_file_name[0],"%sCar/MAIN/park_in_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_PARKING_I].icon_file_name[1],"%sCar/MAIN/park_in_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_PARKING_I] = new CMainParkingInActionTrigger;
	
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_PARKING_O].icon_file_name[0],"%sCar/MAIN/park_out_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_PARKING_O].icon_file_name[1],"%sCar/MAIN/park_out_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_PARKING_O] = new CMainParkingOutActionTrigger;

	sprintf(m_baseButtonData[DEMO_MAIN_MENU_PARKING_T].icon_file_name[0],"%sCar/MAIN/trained_park_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_PARKING_T].icon_file_name[1],"%sCar/MAIN/trained_park_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_PARKING_T] = new CMainTrainedParkingActionTrigger;

	sprintf(m_baseButtonData[DEMO_MAIN_MENU_CTA].icon_file_name[0],"%sCar/MAIN/cta_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_CTA].icon_file_name[1],"%sCar/MAIN/cta_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_CTA] = new CMainCtaActionTrigger;

	sprintf(m_baseButtonData[DEMO_MAIN_MENU_PD].icon_file_name[0],"%sCar/MAIN/pd_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_PD].icon_file_name[1],"%sCar/MAIN/pd_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_PD] = new CMainPdActionTrigger;

	sprintf(m_baseButtonData[DEMO_MAIN_MENU_DVR].icon_file_name[0],"%sCar/MAIN/dvr_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DEMO_MAIN_MENU_DVR].icon_file_name[1],"%sCar/MAIN/dvr_press.dds",XR_RES);
	m_trigger[DEMO_MAIN_MENU_DVR] = new CMainDvrActionTrigger;


	for(int i = DEMO_MAIN_MENU_BKG; i < DEMO_MAIN_ELEMENT_NUM; i++)
	{
		m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
		m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
		m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
		m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
		m_baseButtonData[i].delegate_func = NULL;
		m_baseButtonData[i].trigger = m_trigger[i];

		m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
		m_baseButton[i]->SetVisibility(0);
	}

	return DEMO_HMI_NORMAL;
}
int CSVDemoMainHmi::Init(int window_width, int window_height)
{
	m_screenWidth = window_width;
	m_screenHeight = window_height;
	float heightInterval = 80.0;
	float menuIconInterval = 0.0;//(window_height - 160.0)/(DEMO_MAIN_MENU_DVR - DEMO_MAIN_MENU_SETTING + 1.0) - 20.0;

	SetHmiElementProperty(DEMO_MAIN_MENU_BKG, 0.0, heightInterval - 10.0, 117.0, 586.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_SETTING,m_buttonPos[DEMO_MAIN_MENU_BKG][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_BKG][BUTTON_POS_Y] + 25.0, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_LDW, m_buttonPos[DEMO_MAIN_MENU_SETTING][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_SETTING][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_SETTING][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_LKA, m_buttonPos[DEMO_MAIN_MENU_LDW][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_LDW][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_LDW][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_LC, m_buttonPos[DEMO_MAIN_MENU_LKA][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_LKA][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_LKA][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_BSD, m_buttonPos[DEMO_MAIN_MENU_LC][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_LC][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_LC][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_PARKING_I, m_buttonPos[DEMO_MAIN_MENU_BSD][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_BSD][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_BSD][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_PARKING_O, m_buttonPos[DEMO_MAIN_MENU_PARKING_I][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_PARKING_I][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_PARKING_I][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_PARKING_T, m_buttonPos[DEMO_MAIN_MENU_PARKING_O][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_PARKING_O][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_PARKING_O][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_CTA, m_buttonPos[DEMO_MAIN_MENU_PARKING_T][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_PARKING_T][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_PARKING_T][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_PD, m_buttonPos[DEMO_MAIN_MENU_CTA][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_CTA][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_CTA][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);
	SetHmiElementProperty(DEMO_MAIN_MENU_DVR, m_buttonPos[DEMO_MAIN_MENU_PD][BUTTON_POS_X], m_buttonPos[DEMO_MAIN_MENU_PD][BUTTON_POS_Y] + m_buttonSize[DEMO_MAIN_MENU_PD][BUTTON_SIZE_HEIGHT] + menuIconInterval, 116.0, 47.0);

	SetHmiParams();
	
	return DEMO_HMI_NORMAL;
}
int CSVDemoMainHmi::Update(Hmi_Message_T& hmiMsg)
{
	MainMenuDataT mainMenuData;
	memset(&mainMenuData, 0, sizeof(MainMenuDataT));

	CAvmRenderDataBase::GetInstance()->GetMainMenuStatus(&mainMenuData);

	m_buttonImage[DEMO_MAIN_MENU_SETTING] = mainMenuData.iconStatus[MAIN_MENU_SETTING];
	m_buttonImage[DEMO_MAIN_MENU_LDW] = mainMenuData.iconStatus[MAIN_MENU_LDW];
	m_buttonImage[DEMO_MAIN_MENU_LKA] = mainMenuData.iconStatus[MAIN_MENU_LKA];
	m_buttonImage[DEMO_MAIN_MENU_LC] = mainMenuData.iconStatus[MAIN_MENU_LC];
	m_buttonImage[DEMO_MAIN_MENU_BSD] = mainMenuData.iconStatus[MAIN_MENU_BSD];
	m_buttonImage[DEMO_MAIN_MENU_PARKING_I] = mainMenuData.iconStatus[MAIN_MENU_PARKING_IN];
	m_buttonImage[DEMO_MAIN_MENU_PARKING_O] = mainMenuData.iconStatus[MAIN_MENU_PARKING_OUT];
	m_buttonImage[DEMO_MAIN_MENU_PARKING_T] = mainMenuData.iconStatus[MAIN_MENU_TRAINED_PARKING];
	m_buttonImage[DEMO_MAIN_MENU_CTA] = mainMenuData.iconStatus[MAIN_MENU_CTA];
	m_buttonImage[DEMO_MAIN_MENU_PD] = mainMenuData.iconStatus[MAIN_MENU_PD];
	m_buttonImage[DEMO_MAIN_MENU_DVR] = mainMenuData.iconStatus[MAIN_MENU_DVR];

	//m_buttonImage[DEMO_MAIN_MENU_LKA] = 1;

	if(m_buttonImage[DEMO_MAIN_MENU_LKA] == BUTTON_ON_IMAGE
		|| m_buttonImage[DEMO_MAIN_MENU_LC] == BUTTON_ON_IMAGE)
	{
		if(m_lkaLcInitFlag == 0)
		{
			m_lkaLcHmi = new CSVDemoLkaHmi(m_uiNode, m_uiNodeId);
			m_lkaLcHmi->Init(m_screenWidth, m_screenHeight);
			m_lkaLcHmiVisibility = 1;
			m_lkaLcInitFlag = 1;
		}

		if(m_lkaLcHmi)
		{
			m_lkaLcHmi->Update(hmiMsg);
		}
	}
	else
	{
		m_lkaLcHmiVisibility = 0;
	}
	
	RefreshHmi();

	return DEMO_HMI_NORMAL;
}
 
int CSVDemoMainHmi::RefreshHmi()
{
	for(int i = DEMO_MAIN_MENU_BKG; i < DEMO_MAIN_ELEMENT_NUM; i++)
	{
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->SetShowIconNum(m_buttonImage[i]);
		m_baseButton[i]->Update();
	}

	if(m_lkaLcHmi)
	{
		m_lkaLcHmi->SetElementsVisibility(m_lkaLcHmiVisibility);
	}

	return DEMO_HMI_NORMAL;
}

int CSVDemoMainHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{

	
	return DEMO_HMI_NORMAL;
}
int CSVDemoMainHmi::DestroyHmiElems()
{
	return DEMO_HMI_NORMAL;
}
void CSVDemoMainHmi::SetHmiElementProperty(unsigned char pIconIndex, float pIconPosX, float pIconPosY, float pIconWidth, float pIconHeight)
{
	m_buttonSize[pIconIndex][BUTTON_SIZE_WIDTH] = pIconWidth;
	m_buttonSize[pIconIndex][BUTTON_SIZE_HEIGHT] = pIconHeight;
	m_buttonPos[pIconIndex][BUTTON_POS_X] = pIconPosX;
	m_buttonPos[pIconIndex][BUTTON_POS_Y] = pIconPosY;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the CSVDemoMainHmi class.
 *  01/04/18   Jensen Wang   Add new menu.
\*===========================================================================*/
