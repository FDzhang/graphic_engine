#ifndef _CSV_S302_DVR_BASE_H_
#define _CSV_S302_DVR_BASE_H_

#include "ISVHmi.h"

typedef enum S302DvrHmiElemTag
{
    S302_DVR_BASE_BKG = 0,
    S302_DVR_BASE_RET = 1,    
    S302_DVR_BASE_REC_TAB = 2,
    S302_DVR_BASE_PLAYBACK_TAB,
//    S302_DVR_BASE_IMAGE_TAB,

    S302_DVR_BASE_THUMB_TAB,
	S302_DVR_BASE_ELEMEMT_NUM,
}
S302DvrHmiElemT;

class CSVS302DvrBase : public ISVHmi
{
public:

	CSVS302DvrBase(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	~CSVS302DvrBase();
	HMI_BASE_INHERITANCE_FUNC()
	int SetElementsVisibility(unsigned char pFlag);
private:
	int SetHmiParams();
	int RefreshHmi();
	
private:
	Hmi_Button_Data_T m_baseButtonData[S302_DVR_BASE_ELEMEMT_NUM];
    HMIButton* m_baseButton[S302_DVR_BASE_ELEMEMT_NUM];

	Hmi_Message_T  m_hmiMsg;

	float m_buttonPos[S302_DVR_BASE_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[S302_DVR_BASE_ELEMEMT_NUM][BUTTON_SIZE];

	IActionTrigger*	m_trigger[S302_DVR_BASE_ELEMEMT_NUM];

	unsigned char m_dvrStatus;	
	unsigned char m_buttonStatus[S302_DVR_BASE_ELEMEMT_NUM];
	unsigned char m_buttonVisibility[S302_DVR_BASE_ELEMEMT_NUM];

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


#endif //_CSV_S302_DVR_BASE_H_