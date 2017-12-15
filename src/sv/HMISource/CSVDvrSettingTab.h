#ifndef _CSV_DVR_SETTINGTAB_HMI_H_
#define _CSV_DVR_SETTINGTAB_HMI_H_

#include "ISVHmi.h"

typedef enum DvrSettingTabHmiElementTag
{
	DVR_SETTING_TAB_TIME_SETTING = 0,
	DVR_SETTING_TAB_TIME_SETTING_BKG,
	DVR_SETTING_TAB_TIME_SETTING_FIRST,
	DVR_SETTING_TAB_TIME_SETTING_SECOND,
	DVR_SETTING_TAB_TIME_SETTING_THIRD,
	DVR_SETTING_TAB_SD_FORMAT_TITLE,
	DVR_SETTING_TAB_SD_FORMAT_NORMAL,
	DVR_SETTING_TAB_ELEMEMT_NUM,
}
DvrSettingTabHmiElementT;

class CSVDvrSettingTab : public ISVHmi
{
public:

	CSVDvrSettingTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	
	virtual int Init(int window_width, int window_height);
	virtual int Update(Hmi_Message_T& hmiMsg);
	virtual int ReturnHmiMsg(Hmi_Message_T* hmi_msg);
	virtual int DestroyHMIElems();
private:
	int SetHmiParams();

private:
	Hmi_Button_Data_T m_baseButtonData[DVR_SETTING_TAB_ELEMEMT_NUM];
    HMIButton* m_baseButton[DVR_SETTING_TAB_ELEMEMT_NUM];

	float m_buttonPos[DVR_SETTING_TAB_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[DVR_SETTING_TAB_ELEMEMT_NUM][BUTTON_SIZE];

	IActionTrigger*	m_trigger[DVR_SETTING_TAB_ELEMEMT_NUM];

public:	
};

#endif //_CSV_DVR_SETTINGTAB_HMI_H_