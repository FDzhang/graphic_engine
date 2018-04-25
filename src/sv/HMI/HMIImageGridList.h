#ifndef _HMI_IMAGE_GRIPLIST_H_ /* { */
#define _HMI_IMAGE_GRIPLIST_H_
/*===========================================================================*\
 * FILE: HMIImageGripList.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *
 * ABBREVIATIONS:
 *   TODO: List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     TODO: Update list of design document(s)
 *
 *   Requirements Document(s):
 *     TODO: Update list of requirements document(s)
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../DataStruct.h"
#include "HMIImageIcon.h"
#include "HMITextEdit.h"

typedef enum ImageGridListModeTag
{
	GRIDLIST_NORMAL_MODE = 0,
	GRIDLIST_BKG_MODE,
	GRIDLIST_MODE_NUM,
}
ImageGridListModeT;
enum
{
	MAX_IMAGE_GRID_LIST_NUM = 50,
};

enum
{
	IGL_NORMAL = 0,
	IGL_INIT_FAILED = 1,
	IGL_UPDATE_PARAMS_NULL = 2,
	IGL_FINISHED_ADDING = 3,
	IGL_ADDING_IMAGEICON_ERROR = 4,
};//error code

typedef struct ImageGridListItemTag
{
  unsigned int  objectId;
  unsigned char selectedStatus;
  unsigned char visibilityStatus;
  unsigned char refreshStatus;
  void*			imageData;
  int			imageWidth;
  int			imageHeight;
  IActionTrigger*	trigger;

  HmiTextEditDataT textInfo;
}
ImageGridListItemT;

typedef struct HMIImageGridListDataTag
{
	IUINode*	 renderUiNode;
	ImageGridListModeT gridListMode;
	unsigned int columnNums;
	unsigned int rowNums;
	float      posX;
	float      posY;
	float      itemWidth;
	float      itemHeight; 
	float	   gridListWidth;
	float	   gridListHeight;
	float      verticalSpacing;
	float      horizontalSpacing;  
	char*	   gridListBkgImg;
	unsigned char withTextFlag;
	//char*     editModeSelectedTexture[50];
	//char*     editModeNormalTexture[50];

}
HMIImageGridListDataT;




class HMIImageGridList
{
public:
	HMIImageGridList(HMIImageGridListDataT* pImageGridListData);
	~HMIImageGridList();
	int AddGridItem(ImageGridListItemT* pImageGridListItem);

	int Update(unsigned char pRefreshFlag = 0, unsigned char pRefreshVisibility = 0, unsigned char pCurrentItemNum = 6);
	//int RefreshGridItem(ImageGridListItemT& pImageGridListItem);

	int SetVisibility(unsigned char flag);
	int GetItemLayerId(int pObjectId);

private:

	HMIImageGridListDataT* m_imageGridListData;
	ImageGridListItemT    m_imageGridListItem[MAX_IMAGE_GRID_LIST_NUM];
	HMIRawDataImageIconDataT  m_rawDataImageIconData[MAX_IMAGE_GRID_LIST_NUM];
	HMIRawDataImageIcon*	m_rawDataImageIcon[MAX_IMAGE_GRID_LIST_NUM];	  
	HmiTextEditDataT m_textEditData[MAX_IMAGE_GRID_LIST_NUM];
	HmiTextEdit*     m_textEdit[MAX_IMAGE_GRID_LIST_NUM];

	int m_objectCnt;
	int m_gridListSpiritId;
	int m_gridListMtlId;
	IMaterial* m_gridListMtl;

	int m_occlusePanelId;

	int m_imageWidth;
	int m_imageHeight;

	int m_currentImageFileNum;
};
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/06/17   Jensen Wang   Create the HMIImageGridList class.
\*===========================================================================*/
#endif /* } _HMI_CUSTOM_IMAGEICON_H_ */


