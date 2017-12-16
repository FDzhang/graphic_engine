#include "CSVDvrSettingTab.h"

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

CSVDvrSettingTab::CSVDvrSettingTab(IUINode* pUiNode = NULL, int pUiNodeId = -1): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	memset(m_trigger, NULL, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 1, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(unsigned char));
}
	
int CSVDvrSettingTab::SetHmiParams()
{

	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING].icon_file_name[0],"%sCar/DVR/record_time_setting.dds",XR_RES); 

	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_BKG].icon_file_name[0],"%sCar/DVR/record_time_setting_bkg.dds",XR_RES);

		
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_file_name[0],"%sCar/DVR/time_setting_first.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_FIRST].icon_file_name[1],"%sCar/DVR/time_setting_first_press.dds",XR_RES);
		
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_file_name[0],"%sCar/DVR/time_setting_second.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_SECOND].icon_file_name[1],"%sCar/DVR/time_setting_second_press.dds",XR_RES);

		
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].show_icon_num = 1;
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_file_name[0],"%sCar/DVR/time_setting_third.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_TIME_SETTING_THIRD].icon_file_name[1],"%sCar/DVR/time_setting_third_press.dds",XR_RES);

	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_TITLE].icon_file_name[0],"%sCar/DVR/sd_format_title.dds",XR_RES);

	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].show_flag = 1;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].show_icon_num = 0;
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[0],"%sCar/DVR/sd_format_normal.dds",XR_RES);
	sprintf(m_baseButtonData[DVR_SETTING_TAB_SD_FORMAT_NORMAL].icon_file_name[1],"%sCar/DVR/sd_format_press.dds",XR_RES);	

	for(int i = DVR_SETTING_TAB_TIME_SETTING; i < DVR_SETTING_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
		m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
		m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
		m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
		m_baseButtonData[i].delegate_func = NULL;
		m_baseButtonData[i].trigger = m_trigger[i];

		m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
		m_baseButton[i]->SetVisibility(1);
	}
	return true;
}
int CSVDvrSettingTab::Init(int window_width, int window_height)
{
	float radio = 227.0/1280.0;

	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING][BUTTON_SIZE_WIDTH] = 173.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_X] = radio*window_width + 50.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_Y] = 80.0 + 50.0;

	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_SIZE_WIDTH] = 428.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_X];
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_Y] + m_buttonSize[DVR_SETTING_TAB_TIME_SETTING][BUTTON_SIZE_HEIGHT] + 6.0;

		
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_SIZE_WIDTH] = 143.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y];
		
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_SIZE_WIDTH] = 143.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_POS_X] + m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_FIRST][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y];
		
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_THIRD][BUTTON_SIZE_WIDTH] = 143.0;
	m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_THIRD][BUTTON_SIZE_HEIGHT] = 57.0;
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_THIRD][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_POS_X] + m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_SECOND][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_THIRD][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_SIZE_WIDTH] = 174.0;
	m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING][BUTTON_POS_X];
	m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_POS_Y] + m_buttonSize[DVR_SETTING_TAB_TIME_SETTING_BKG][BUTTON_SIZE_HEIGHT] + 60.0;

	m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_SIZE_WIDTH] = 122.0;
	m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_SIZE_HEIGHT] = 58.0;
	m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_POS_X] = m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_SIZE_WIDTH] + 120.0;
	m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_POS_Y] = m_buttonPos[DVR_SETTING_TAB_SD_FORMAT_TITLE][BUTTON_POS_Y] - m_buttonSize[DVR_SETTING_TAB_SD_FORMAT_NORMAL][BUTTON_SIZE_HEIGHT] * 0.33;
	
	SetHmiParams();
	
	return HMI_SUCCESS;
}
int CSVDvrSettingTab::Update(Hmi_Message_T& hmiMsg)
{
	RefreshHmi();

	return HMI_SUCCESS;
}
int CSVDvrSettingTab::RefreshHmi()
{
	for(int i = DVR_SETTING_TAB_TIME_SETTING; i < DVR_SETTING_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}
	return HMI_SUCCESS;
}
int CSVDvrSettingTab::SetElementsVisibility(unsigned char pFlag)
{

	memset(m_buttonVisibility, pFlag, DVR_SETTING_TAB_ELEMEMT_NUM * sizeof(unsigned char));

	return HMI_SUCCESS;
}

int CSVDvrSettingTab::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVDvrSettingTab::DestroyHmiElems()
{
	return HMI_SUCCESS;
}
