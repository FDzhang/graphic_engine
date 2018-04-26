#ifndef _CSV_DVR_FILELIST_HMI_H_
#define _CSV_DVR_FILELIST_HMI_H_

#include "ISVHmi.h"


static const int IMAGE_GRID_LIST_ITEM_NUM = 6;

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
	int SetDvrView(unsigned char pViewCmd);

private:		

	HMIImageGridListDataT m_imageGridListData;
	HMIImageGridList* m_imageGridList;
	ImageGridListItemT m_imageGridListItem[IMAGE_GRID_LIST_ITEM_NUM];

	HmiTextEditDataT m_textEditData[IMAGE_GRID_LIST_ITEM_NUM];
	HmiTextEdit*     m_textEdit[IMAGE_GRID_LIST_ITEM_NUM];

	unsigned char m_imageGridVisibility;

	IActionTrigger* m_gridListTrigger[IMAGE_GRID_LIST_ITEM_NUM];

};

#endif //_CSV_DVR_FILELIST_TAB_H_
