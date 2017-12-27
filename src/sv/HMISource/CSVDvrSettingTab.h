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

typedef enum DvrSettingDialogTag
{
	DVR_SETTING_DIALOG_FORMATCARD = 1,
	//DVR_SETTING_DIALOG_FORMATCARD_CAUTION,
	//DVR_SETTING_DIALOG_FORMATCARD_OK,
	//DVR_SETTING_DIALOG_FORMATCARD_FAILED,
	DVR_SETTING_DIALOG_DIALOG_NUM,	
}
DvrSettingDialogT;

class CSVDvrSettingTab : public ISVHmi
{
public:

	CSVDvrSettingTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	HMI_BASE_INHERITANCE_FUNC()

	virtual int SetElementsVisibility(unsigned char pFlag);
private:
	int SetHmiParams();
	int RefreshHmi();
private:
	Hmi_Button_Data_T m_baseButtonData[DVR_SETTING_TAB_ELEMEMT_NUM];
    HMIButton* m_baseButton[DVR_SETTING_TAB_ELEMEMT_NUM];

	float m_buttonPos[DVR_SETTING_TAB_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[DVR_SETTING_TAB_ELEMEMT_NUM][BUTTON_SIZE];

	IActionTrigger*	m_trigger[DVR_SETTING_TAB_ELEMEMT_NUM];

	HmiDialogDataT   m_dialogData[DVR_SETTING_DIALOG_DIALOG_NUM];
	HMIDialog*		 m_dialog[DVR_SETTING_DIALOG_DIALOG_NUM];
	unsigned char 	 m_dialogVisibility[DVR_SETTING_DIALOG_DIALOG_NUM];


	unsigned char m_buttonStatus[DVR_SETTING_TAB_ELEMEMT_NUM];
	unsigned char m_buttonVisibility[DVR_SETTING_TAB_ELEMEMT_NUM];

public:	
};

#endif //_CSV_DVR_SETTINGTAB_HMI_H_
