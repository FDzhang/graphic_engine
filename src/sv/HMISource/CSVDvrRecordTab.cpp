#include "CSVDvrRecordTab.h"

class CTimeSelectorFirstActionTrigger : public IActionTrigger
{
public:
	CTimeSelectorFirstActionTrigger() 
	{ 
		;
	}
	virtual Void OnPress(Int32 id)
	{
		int i = 0;
	}
	virtual Void OnRelease(Int32 id, Boolean isIn)
	{

	}
private:
	//class CGpuAvmEventDelegate* m_titleIconEventDel;
};

CSVDvrRecordTab::CSVDvrRecordTab(IUINode* pUiNode = NULL, int pUiNodeId = -1): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	memset(m_trigger, NULL, DVR_RECORD_TAB_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, DVR_RECORD_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 1, DVR_RECORD_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	
}
	
int CSVDvrRecordTab::SetHmiParams()
{

	m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_RECORD_BKG].icon_file_name[0],"%sCar/DVR/record_tab_bkg.dds",XR_RES); 
	
	m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_RECORD_TITLE].icon_file_name[0],"%sCar/DVR/record_title.dds",XR_RES); 
		
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_file_name[0],"%sCar/DVR/record_switch_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_RECORD_SWITCH].icon_file_name[1],"%sCar/DVR/record_switch_press.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_CAPTURE_TITLE].icon_file_name[0],"%sCar/DVR/capture_title.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_CAPTURE_BKG].icon_file_name[0],"%sCar/DVR/capture_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_file_name[0],"%sCar/DVR/capture_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_CAPTURE_ICON].icon_file_name[1],"%sCar/DVR/capture_hightlight.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_TITLE].icon_file_name[0],"%sCar/DVR/emergency_title.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_BKG].icon_file_name[0],"%sCar/DVR/emergency_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_file_name[0],"%sCar/DVR/emergency_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_EMERGENCY_ICON].icon_file_name[1],"%sCar/DVR/emergency_highlight.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_TITLE].icon_file_name[0],"%sCar/DVR/record_view_title.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_BKG].icon_file_name[0],"%sCar/DVR/record_view_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_file_name[0],"%sCar/DVR/record_view_front_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_FRONT].icon_file_name[1],"%sCar/DVR/record_view_front_highlight.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_file_name[0],"%sCar/DVR/record_view_rear_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_REAR].icon_file_name[1],"%sCar/DVR/record_view_rear_highlight.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_file_name[0],"%sCar/DVR/record_view_left_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_LEFT].icon_file_name[1],"%sCar/DVR/record_view_left_highlight.dds",XR_RES); 

	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].show_flag = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].show_icon_num = 1;
	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_file_name[0],"%sCar/DVR/record_view_right_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_RECORD_TAB_VIEW_RIGHT].icon_file_name[1],"%sCar/DVR/record_view_right_highlight.dds",XR_RES); 

	for(int i = DVR_RECORD_TAB_RECORD_BKG; i < DVR_RECORD_TAB_ELEMEMT_NUM; i++)
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
	return HMI_SUCCESS;
}
int CSVDvrRecordTab::Init(int window_width, int window_height)
{
	float radio = 227.0/1280.0;

	m_buttonSize[DVR_RECORD_TAB_RECORD_BKG][BUTTON_SIZE_WIDTH] = 372.0;
	m_buttonSize[DVR_RECORD_TAB_RECORD_BKG][BUTTON_SIZE_HEIGHT] = 560.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_BKG][BUTTON_POS_X] = radio*window_width;
	m_buttonPos[DVR_RECORD_TAB_RECORD_BKG][BUTTON_POS_Y] = 80.0;
	
	m_buttonSize[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_RECORD_BKG][BUTTON_POS_X] + 50.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_Y] = 80.0 + 80.0;
		
	m_buttonSize[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_SIZE_WIDTH] = 114.0;
	m_buttonSize[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_SIZE_HEIGHT] = 47.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_SIZE_WIDTH] + 100.0;
	m_buttonPos[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_RECORD_TITLE][BUTTON_POS_Y]+ m_buttonSize[DVR_RECORD_TAB_RECORD_SWITCH][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_SIZE_WIDTH] + 100.0;
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_Y];
		
	m_buttonSize[DVR_RECORD_TAB_CAPTURE_ICON][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_RECORD_TAB_CAPTURE_ICON][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_ICON][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_CAPTURE_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_BKG][BUTTON_POS_Y];
		
	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_SIZE_WIDTH] = 114.0;
	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_SIZE_HEIGHT] = 30.0;
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_RECORD_TAB_CAPTURE_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_SIZE_WIDTH] + 35;
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_ICON][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_RECORD_TAB_EMERGENCY_ICON][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_ICON][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_EMERGENCY_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_SIZE_WIDTH] = 58.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_RECORD_TAB_EMERGENCY_TITLE][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_RECORD_TAB_VIEW_BKG][BUTTON_SIZE_WIDTH] = 296.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_BKG][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_VIEW_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_RECORD_TAB_VIEW_TITLE][BUTTON_SIZE_HEIGHT] + 10.0;

	m_buttonSize[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_VIEW_REAR][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_REAR][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_REAR][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_RECORD_TAB_VIEW_REAR][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_FRONT][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_REAR][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_VIEW_REAR][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_REAR][BUTTON_POS_Y];

	m_buttonSize[DVR_RECORD_TAB_VIEW_RIGHT][BUTTON_SIZE_WIDTH] = 75.0;
	m_buttonSize[DVR_RECORD_TAB_VIEW_RIGHT][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_RECORD_TAB_VIEW_RIGHT][BUTTON_POS_X] = m_buttonPos[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_POS_X] + m_buttonSize[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_RECORD_TAB_VIEW_RIGHT][BUTTON_POS_Y] = m_buttonPos[DVR_RECORD_TAB_VIEW_LEFT][BUTTON_POS_Y];

	SetHmiParams();
	
	return HMI_SUCCESS;
}
int CSVDvrRecordTab::Update(Hmi_Message_T& hmiMsg)
{
	RefreshHmi();
	return HMI_SUCCESS;
}
int CSVDvrRecordTab::RefreshHmi()
{
	for(int i = DVR_RECORD_TAB_RECORD_BKG; i < DVR_RECORD_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
	return HMI_SUCCESS;
}
int CSVDvrRecordTab::SetElementsVisibility(unsigned char pFlag)
{
	memset(m_buttonVisibility, pFlag, DVR_RECORD_TAB_ELEMEMT_NUM * sizeof(unsigned char));

	return HMI_SUCCESS;
}
int CSVDvrRecordTab::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVDvrRecordTab::DestroyHmiElems()
{
	return HMI_SUCCESS;
}
