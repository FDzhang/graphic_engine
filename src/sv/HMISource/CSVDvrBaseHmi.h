#ifndef _CSV_DVR_BASE_HMI_H_
#define _CSV_DVR_BASE_HMI_H_

#include "ISVHmi.h"
#include "../CGpuAvmEventDelegate.h"

typedef enum DvrBaseHmiElementTag
{
	DVR_BASE_TITLE_BKG = 0,
	DVR_BASE_TAB_BKG,
	DVR_BASE_TITLE_ICON,
	DVR_BASE_LIVE_VIDEO_TAB,
	DVR_BASE_FILE_TAB,
	DVR_BASE_SETTING_TAB,
	DVR_BASE_ELEMEMT_NUM,
}
DvrBaseHmiElementT;

class CSVDvrBaseHmi : public ISVHmi
{
public:

	CSVDvrBaseHmi();
	
	virtual int Init(int window_width, int window_height);
	virtual int Update(Hmi_Message_T& hmiMsg);
	virtual int ReturnHmiMsg(Hmi_Message_T* hmi_msg);
	virtual int DestroyHMIElems();
private:
	int SetHmiParams();
private:
	Hmi_Button_Data_T m_baseButtonData[DVR_BASE_ELEMEMT_NUM];
    HMIButton* m_baseButton[DVR_BASE_ELEMEMT_NUM];

	float m_buttonPos[DVR_BASE_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[DVR_BASE_ELEMEMT_NUM][BUTTON_SIZE];

	IActionTrigger*	m_trigger[DVR_BASE_ELEMEMT_NUM];

	unsigned char m_dvrStatus;	
	unsigned char m_buttonStatus[DVR_BASE_ELEMEMT_NUM];
	unsigned char m_buttonVisibility[DVR_BASE_ELEMEMT_NUM];

	ISVHmi* m_dvrSettingTab;
	
public:	
	int SetDvrStatus(unsigned char pDvrStatus);
	int RefreshHmi();
};


#endif //_CSV_DVR_BASE_HMI_H_