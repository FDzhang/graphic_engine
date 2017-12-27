#ifndef _CSV_DVR_PLAYBACK_TAB_H_
#define _CSV_DVR_PLAYBACK_TAB_H_

#include "ISVHmi.h"

typedef enum DvrPlaybackHmiElementTag
{
	DVR_PLAYBACK_TAB_PLAYER_BKG = 0,
	DVR_PLAYBACK_TAB_FILE_TITLE_BKG,
	DVR_PLAYBACK_TAB_PLAY,
	DVR_PLAYBACK_TAB_FF,
	DVR_PLAYBACK_TAB_FB,
	DVR_PLAYBACK_TAB_NEXT_PAGE,
	DVR_PLAYBACK_TAB_PRE_PAGE,
	DVR_PLAYBACK_TAB_SPEED,

	DVR_PLAYBACK_TAB_MENU_BKG,

	DVR_PLAYBACK_TAB_EMERGENCY_TITLE,
	DVR_PLAYBACK_TAB_EMERGENCY_BKG,
	DVR_PLAYBACK_TAB_EMERGENCY_ICON,

	DVR_PLAYBACK_TAB_DELETE_TITLE,
	DVR_PLAYBACK_TAB_DELETE_BKG,
	DVR_PLAYBACK_TAB_DELETE_ICON,

	DVR_PLAYBACK_TAB_DC_TITLE,
	DVR_PLAYBACK_TAB_DC_SWITCH,

	DVR_PLAYBACK_TAB_VIEW_TITLE,
	DVR_PLAYBACK_TAB_VIEW_BKG,
	DVR_PLAYBACK_TAB_VIEW_FRONT,
	DVR_PLAYBACK_TAB_VIEW_REAR,
	DVR_PLAYBACK_TAB_VIEW_LEFT,
	DVR_PLAYBACK_TAB_VIEW_RIGHT,

	DVR_PLAYBACK_TAB_ELEMEMT_NUM,
}
DvrPlaybackHmiElementT;

typedef enum DvrPlaybackDialogTag
{
	DVR_PLAYBACK_DIALOG_DEL = 0,
	DVR_PLAYBACK_DIALOG_NUM,	
}
DvrPlaybackDialogT;

typedef enum TextDisplayTag
{
	PB_FILENAME_TITLE,
	PB_FILE_CURRENT_TIME,
	PB_FILE_DURATION_TIME,
	PB_TEXT_DISPLAY_NUM,
}
TextDisplayT;

class CSVDvrPlaybackTab : public ISVHmi
{
public:
	CSVDvrPlaybackTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	HMI_BASE_INHERITANCE_FUNC()
	virtual int SetElementsVisibility(unsigned char pFlag);
	
private:
	int SetHmiParams();
	int RefreshHmi();

	int ToString(int pTime, char** pOutString);

private:
		
	Hmi_Button_Data_T m_baseButtonData[DVR_PLAYBACK_TAB_ELEMEMT_NUM];
    HMIButton* m_baseButton[DVR_PLAYBACK_TAB_ELEMEMT_NUM];

	float m_buttonPos[DVR_PLAYBACK_TAB_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[DVR_PLAYBACK_TAB_ELEMEMT_NUM][BUTTON_SIZE];
	unsigned char m_buttonStatus[DVR_PLAYBACK_TAB_ELEMEMT_NUM];
	unsigned char m_buttonVisibility[DVR_PLAYBACK_TAB_ELEMEMT_NUM];

	HmiDialogDataT   m_dialogData[DVR_PLAYBACK_DIALOG_NUM];
	HMIDialog*		 m_dialog[DVR_PLAYBACK_DIALOG_NUM];
	unsigned char 	 m_dialogVisibility[DVR_PLAYBACK_DIALOG_NUM];


	IActionTrigger*	m_trigger[DVR_PLAYBACK_TAB_ELEMEMT_NUM];

	HmiProcessBarDataT m_processBarData;
	HmiProcessBar*     m_processBar;
	unsigned char      m_processBarVisibility;
	float			   m_processBarForwardScale;

	HmiTextEditDataT m_textEditData[PB_TEXT_DISPLAY_NUM];
	HmiTextEdit*     m_textEdit[PB_TEXT_DISPLAY_NUM];	
	unsigned char    m_textEditVisibility[PB_TEXT_DISPLAY_NUM];
	char*			 m_textEditContent[PB_TEXT_DISPLAY_NUM];
};

#endif //_CSV_DVR_PLAYBACK_TAB_H_
