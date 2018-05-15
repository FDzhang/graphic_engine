#ifndef _CSV_V302_DVR_BASE_H_
#define _CSV_V302_DVR_BASE_H_

#include "ISVHmi.h"

//#define PREVIEW_WIDTH 304
//#define PREVIEW_HIGH 176


enum
{
    V302_DVR_BASE_BKG = 0,
    V302_DVR_BASE_RET = 1,    
    V302_DVR_BASE_REC_TAB = 2,
    V302_DVR_BASE_PLAYBACK_TAB,
//    V302_DVR_BASE_IMAGE_TAB,

    V302_DVR_BASE_THUMB_TAB,
	V302_DVR_BASE_ELEMEMT_NUM,
};

class CSVV302DvrBase : public ISVHmi
{
public:

	CSVV302DvrBase();
	~CSVV302DvrBase();
	HMI_BASE_INHERITANCE_FUNC()

private:
	int SetHmiParams();
	int RefreshHmi();
	
private:
	Hmi_Button_Data_T m_baseButtonData[V302_DVR_BASE_ELEMEMT_NUM];
    HMIButton* m_baseButton[V302_DVR_BASE_ELEMEMT_NUM];

	Hmi_Message_T  m_hmiMsg;

	float m_buttonPos[V302_DVR_BASE_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[V302_DVR_BASE_ELEMEMT_NUM][BUTTON_SIZE];

	IActionTrigger*	m_trigger[V302_DVR_BASE_ELEMEMT_NUM];

	unsigned char m_dvrStatus;	
	unsigned char m_buttonStatus[V302_DVR_BASE_ELEMEMT_NUM];
	unsigned char m_buttonVisibility[V302_DVR_BASE_ELEMEMT_NUM];

	ISVHmi* m_dvrRecordTab;
	ISVHmi* m_dvrPlaybackTab;
	ISVHmi* m_dvrFileListTab;
    ISVHmi* m_dvrPlayImageTab;

	unsigned char m_dvrRecordTabVisibility;
	unsigned char m_dvrPlaybackTabVisibility;
	unsigned char m_dvrFileListVisibility;
    unsigned char m_dvrPlayImageTabVisibility;

    unsigned char m_avmViewLastStatus;

	int     m_windowHeight;
	int     m_windowWidth;
	
public:	
	int SetDvrStatus();
    
	
};


#endif //_CSV_V302_DVR_BASE_H_