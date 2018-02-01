#ifndef _CSV_DVR_PLAYBACK_IMAGE_TAB_H_
#define _CSV_DVR_PLAYBACK_IMAGE_TAB_H_

#include "ISVHmi.h"

typedef enum DvrPlayImageHmiElementTag {
    DVR_PLAYBACK_IMAGE_TAB_PLAYER_BKG = 0,
    DVR_PLAYBACK_IMAGE_TAB_FILE_TITLE_BKG,
//    DVR_PLAYBACK_IMAGE_TAB_PLAY,
    DVR_PLAYBACK_IMAGE_TAB_NEXT_PAGE,
    DVR_PLAYBACK_IMAGE_TAB_PRE_PAGE,

    DVR_PLAYBACK_IMAGE_TAB_MENU_BKG,

    DVR_PLAYBACK_IMAGE_TAB_MENU_HIDE_ICON,
    DVR_PLAYBACK_IMAGE_TAB_MENU_SHOW_ICON,

    DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_TITLE,
    DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_BKG,
    DVR_PLAYBACK_IMAGE_TAB_EMERGENCY_ICON,

    DVR_PLAYBACK_IMAGE_TAB_DELETE_TITLE,
    DVR_PLAYBACK_IMAGE_TAB_DELETE_BKG,
    DVR_PLAYBACK_IMAGE_TAB_DELETE_ICON,

    DVR_PLAYBACK_IMAGE_TAB_DC_TITLE,
    DVR_PLAYBACK_IMAGE_TAB_DC_SWITCH,

    DVR_PLAYBACK_IMAGE_TAB_VIEW_TITLE,
    DVR_PLAYBACK_IMAGE_TAB_VIEW_BKG,
    DVR_PLAYBACK_IMAGE_TAB_VIEW_FRONT,
    DVR_PLAYBACK_IMAGE_TAB_VIEW_REAR,
    DVR_PLAYBACK_IMAGE_TAB_VIEW_LEFT,
    DVR_PLAYBACK_IMAGE_TAB_VIEW_RIGHT,

    DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM,
} DvrPlayImageHmiElementT;

typedef enum DvrPlayImageDialogTag {
    DVR_PLAYBACK_IMAGE_DIALOG_DEL = 0,
    DVR_PLAYBACK_IMAGE_DIALOG_NUM,
} DvrPlayImageDialogT;

typedef enum ImageTextDisplayTag {
    IMAGE_TEXT_NAME_TITLE,
    IMAGE_TEXT_DISPLAY_NUM,
} ImageTextDisplayT;

class CSVDvrPlayImageTab : public ISVHmi
{
  public:
    CSVDvrPlayImageTab(IUINode *pUiNode = NULL, int pUiNodeId = -1);
    ~CSVDvrPlayImageTab();
    HMI_BASE_INHERITANCE_FUNC()
    virtual int SetElementsVisibility(unsigned char pFlag);
    virtual int SetMenuVisibility();
    virtual int SetMenuHideCount(unsigned char visible);

  private:
    int SetHmiParams();
    int RefreshHmi();
    int ToString(int pTime, char **pOutString);

  private:
    Hmi_Button_Data_T   m_baseButtonData[DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM];
    HMIButton*          m_baseButton[DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM];

    float               m_buttonPos[DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM][BUTTON_POS];
    float               m_buttonSize[DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM][BUTTON_SIZE];
    unsigned char       m_buttonStatus[DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM];
    unsigned char       m_buttonVisibility[DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM];
    IActionTrigger*     m_trigger[DVR_PLAYBACK_IMAGE_TAB_ELEMEMT_NUM];

    HmiDialogDataT      m_dialogData[DVR_PLAYBACK_IMAGE_DIALOG_NUM];
    HMIDialog*          m_dialog[DVR_PLAYBACK_IMAGE_DIALOG_NUM];
    unsigned char       m_dialogVisibility[DVR_PLAYBACK_IMAGE_DIALOG_NUM];
    unsigned char       m_menuVisibility;

    HmiTextEditDataT    m_textEditData[IMAGE_TEXT_DISPLAY_NUM];
    HmiTextEdit*        m_textEdit[IMAGE_TEXT_DISPLAY_NUM];
    unsigned char       m_textEditVisibility[IMAGE_TEXT_DISPLAY_NUM];
    char*               m_textEditContent[IMAGE_TEXT_DISPLAY_NUM];
};

#endif //_CSV_DVR_PLAYBACK_TAB_H_
