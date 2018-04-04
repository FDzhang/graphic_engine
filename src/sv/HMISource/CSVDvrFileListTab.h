#ifndef _CSV_DVR_FILELIST_TAB_H_
#define _CSV_DVR_FILELIST_TAB_H_

#include "ISVHmi.h"

typedef enum DvrFileListHmiElementTag
{
	DVR_FILELIST_TAB_LOOP_REC_TITLE = 0,
	DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE,
	DVR_FILELIST_TAB_PICTURE_TITLE,
	DVR_FILELIST_TAB_LR_TITLE_SELECTED,
	DVR_FILELIST_TAB_ES_TITLE_SELECTED,
	DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED,
	DVR_FILELIST_TAB_EDIT_ICON,
	DVR_FILELIST_TAB_EDIT_BKG,
	DVR_FILELIST_TAB_EDIT_CANCEL,
	DVR_FILELIST_TAB_EDIT_SAVE,
	DVR_FILELIST_TAB_EDIT_DELETE,
	DVR_FILELIST_TAB_EDIT_SELECTED_ALL,
	DVR_FILELIST_TAB_EDIT_SEL_BOX_1,
	DVR_FILELIST_TAB_EDIT_SEL_FLAG_1,
	DVR_FILELIST_TAB_EDIT_SEL_BOX_2,
	DVR_FILELIST_TAB_EDIT_SEL_FLAG_2,
	DVR_FILELIST_TAB_EDIT_SEL_BOX_3,
	DVR_FILELIST_TAB_EDIT_SEL_FLAG_3,
	DVR_FILELIST_TAB_EDIT_SEL_BOX_4,
	DVR_FILELIST_TAB_EDIT_SEL_FLAG_4,
	DVR_FILELIST_TAB_EDIT_SEL_BOX_5,
	DVR_FILELIST_TAB_EDIT_SEL_FLAG_5,
	DVR_FILELIST_TAB_EDIT_SEL_BOX_6,
	DVR_FILELIST_TAB_EDIT_SEL_FLAG_6,
	DVR_FILELIST_TAB_SCROLL_BKG,
	DVR_FILELIST_TAB_SCROLL_UP,
	DVR_FILELIST_TAB_SCROLL_DOWN,
	DVR_FILELIST_TAB_ELEMEMT_NUM,
}
DvrFileListHmiElementT;

typedef enum DvrFileListDialogTag
{
	DVR_FILELIST_DIALOG_DEL = 0,
	DVR_FILELIST_DIALOG_NUM,	
}
DvrFileListDialogT;


static const int IMAGE_GRID_LIST_ITEM_NUM = 6;

class CSVDvrFileListTab : public ISVHmi
{
public:
	CSVDvrFileListTab(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	~CSVDvrFileListTab();
	HMI_BASE_INHERITANCE_FUNC()
	virtual int SetElementsVisibility(unsigned char pFlag);
private:
	int RefreshHmi();
	int SetHmiParams();

private:		
	Hmi_Button_Data_T m_baseButtonData[DVR_FILELIST_TAB_ELEMEMT_NUM];
    HMIButton* m_baseButton[DVR_FILELIST_TAB_ELEMEMT_NUM];

	HMIImageGridListDataT m_imageGridListData;
	HMIImageGridList* m_imageGridList;
	ImageGridListItemT m_imageGridListItem[IMAGE_GRID_LIST_ITEM_NUM];

    HmiTextEdit*     m_pageNum;
    HmiTextEditDataT m_pageNumData;    

    HmiTextEdit*     m_noFileText;
    HmiTextEditDataT m_noFileTextData;    

	HmiTextEditDataT m_textEditData[IMAGE_GRID_LIST_ITEM_NUM];
	HmiTextEdit*     m_textEdit[IMAGE_GRID_LIST_ITEM_NUM];

	HmiDialogDataT   m_dialogData[DVR_FILELIST_DIALOG_NUM];
	HMIDialog*		 m_dialog[DVR_FILELIST_DIALOG_NUM];

	float m_buttonPos[DVR_FILELIST_TAB_ELEMEMT_NUM][BUTTON_POS];
	float m_buttonSize[DVR_FILELIST_TAB_ELEMEMT_NUM][BUTTON_SIZE];

	unsigned char m_buttonStatus[DVR_FILELIST_TAB_ELEMEMT_NUM];
	unsigned char m_buttonVisibility[DVR_FILELIST_TAB_ELEMEMT_NUM];
	unsigned char m_imageGridVisibility;
	unsigned char m_dialogVisibility[DVR_FILELIST_DIALOG_NUM];

	IActionTrigger*	m_trigger[DVR_FILELIST_TAB_ELEMEMT_NUM];
	IActionTrigger* m_gridListTrigger[IMAGE_GRID_LIST_ITEM_NUM];

};

#endif //_CSV_DVR_FILELIST_TAB_H_
