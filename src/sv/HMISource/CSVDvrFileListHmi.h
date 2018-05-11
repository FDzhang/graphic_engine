#ifndef _CSV_DVR_FILELIST_HMI_H_
#define _CSV_DVR_FILELIST_HMI_H_

#include "ISVHmi.h"

enum
{
    V302_FILE_BKG = 0,
	V302_FILE_SCROLL_BACK = 1,
    V302_FILE_SCROLL_BLOCK,
    V302_FILE_BUTTON_NUM,
};

static const int IMAGE_GRID_LIST_ITEM_NUM = 8;

class CSVDvrFileListHmi : public ISVHmi
{
public:
	CSVDvrFileListHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1);
	~CSVDvrFileListHmi();
	HMI_BASE_INHERITANCE_FUNC()
	virtual int SetElementsVisibility(unsigned char pFlag);
private:
	int RefreshHmi();
	int SetHmiParams();


private:	
    
	Hmi_Button_Data_T m_baseButtonData[V302_FILE_BUTTON_NUM];
    HMIButton* m_baseButton[V302_FILE_BUTTON_NUM];

	HMIImageGridListDataT m_imageGridListData;
	HMIImageGridList* m_imageGridList;
	ImageGridListItemT m_imageGridListItem[IMAGE_GRID_LIST_ITEM_NUM];

	HmiTextEditDataT m_textEditData[IMAGE_GRID_LIST_ITEM_NUM];
	HmiTextEdit*     m_textEdit[IMAGE_GRID_LIST_ITEM_NUM];

	unsigned char m_imageGridVisibility;

	IActionTrigger* m_gridListTrigger[IMAGE_GRID_LIST_ITEM_NUM];
    
    HmiTextEdit*     m_pageNum;
    HmiTextEditDataT m_pageNumData;   

};

#endif //_CSV_DVR_FILELIST_TAB_H_
