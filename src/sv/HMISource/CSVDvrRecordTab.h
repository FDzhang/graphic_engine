#ifndef _CSV_DVR_RECORDTAB_HMI_H_
#define _CSV_DVR_RECORDTAB_HMI_H_

#include "ISVHmi.h"

typedef enum DvrRecordTabHmiElementTag
{
	DVR_RECORD_TAB_RECORD_BKG = 0,
    DVR_RECORD_TAB_HIDE_ICON,
    DVR_RECORD_TAB_SHOW_ICON,
	DVR_RECORD_TAB_RECORD_TITLE,
	DVR_RECORD_TAB_RECORD_SWITCH,
	DVR_RECORD_TAB_CAPTURE_TITLE,
	DVR_RECORD_TAB_CAPTURE_BKG,
	DVR_RECORD_TAB_CAPTURE_ICON,
	DVR_RECORD_TAB_EMERGENCY_TITLE,
	DVR_RECORD_TAB_EMERGENCY_BKG,
	DVR_RECORD_TAB_EMERGENCY_ICON,
	DVR_RECORD_TAB_VIEW_TITLE,
	DVR_RECORD_TAB_VIEW_BKG,
	DVR_RECORD_TAB_VIEW_FRONT,
	DVR_RECORD_TAB_VIEW_REAR,
	DVR_RECORD_TAB_VIEW_LEFT,
	DVR_RECORD_TAB_VIEW_RIGHT,
	DVR_RECORD_TAB_ELEMEMT_NUM,
}
DvrRecordTabHmiElementT;

class CSVDvrRecordTab : public ISVHmi
{
public:

	CSVDvrRecordTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	~CSVDvrRecordTab();
	HMI_BASE_INHERITANCE_FUNC()

	virtual int SetElementsVisibility(unsigned char pFlag);
    virtual int SetMenuVisibility();
	virtual int SetMenuHideCount(unsigned char visible);
	
private:
	int SetHmiParams();
	int RefreshHmi();
private:
	Hmi_Button_Data_T m_baseButtonData[DVR_RECORD_TAB_ELEMEMT_NUM];
    HMIButton* m_baseButton[DVR_RECORD_TAB_ELEMEMT_NUM];

	float m_buttonPos[DVR_RECORD_TAB_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[DVR_RECORD_TAB_ELEMEMT_NUM][BUTTON_SIZE];

	unsigned char m_buttonStatus[DVR_RECORD_TAB_ELEMEMT_NUM];
	unsigned char m_buttonVisibility[DVR_RECORD_TAB_ELEMEMT_NUM];
	unsigned char m_menuVisibility;

	IActionTrigger*	m_trigger[DVR_RECORD_TAB_ELEMEMT_NUM];


public:	
};

#endif //_CSV_DVR_RECORDTAB_HMI_H_
