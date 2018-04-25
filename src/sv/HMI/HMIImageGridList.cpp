/*===========================================================================*\
 * FILE: HMIImageGridList.c
 *===========================================================================
 * Copyright 2015 O-Film Technologies, Inc., All Rights Reserved.
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
 *     TODO: Update list of other applicable standards
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "HMIImageGridList.h"
#include "../AVMData.h"
#include "gpu_log.h"

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;

HMIImageGridList::HMIImageGridList(HMIImageGridListDataT* pImageGridListData):m_objectCnt(0),m_currentImageFileNum(0)
{
	if(pImageGridListData == NULL
		|| pImageGridListData->renderUiNode == NULL)
	{
		return;
	}
	m_imageGridListData = new HMIImageGridListDataT;
	memcpy(m_imageGridListData, pImageGridListData, sizeof(HMIImageGridListDataT));

	if(m_imageGridListData->gridListMode == GRIDLIST_BKG_MODE)
	{
		m_gridListMtlId = m_imageGridListData->renderUiNode->CreateMaterial(Material_UI_Spirit, &m_gridListMtl);
		m_gridListMtl->SetDiffuseMap(m_imageGridListData->gridListBkgImg);
		m_gridListSpiritId = m_imageGridListData->renderUiNode->CreateSpirit(-1, InsertFlag_Default, m_gridListMtlId, 1.0, m_imageGridListData->posX, m_imageGridListData->posY, 0, m_imageGridListData->gridListWidth, m_imageGridListData->gridListHeight);
	}
	else if(m_imageGridListData->gridListMode == GRIDLIST_NORMAL_MODE)
	{
		m_gridListSpiritId = m_imageGridListData->renderUiNode->CreateLayoutPanel(-1, InsertFlag_Default, m_imageGridListData->posX, m_imageGridListData->posY, m_imageGridListData->gridListWidth, m_imageGridListData->gridListHeight, LayoutMode_Grid, 0);
	}
	m_imageWidth = m_imageGridListData->itemWidth;
	m_imageHeight = m_imageGridListData->itemHeight;

}

HMIImageGridList::~HMIImageGridList()
{

}
int HMIImageGridList::AddGridItem(ImageGridListItemT* pImageGridListItem)
{
	if(pImageGridListItem->objectId == m_objectCnt
		&& pImageGridListItem->objectId != 0)
	{
		return IGL_FINISHED_ADDING;
	}
	if(pImageGridListItem->imageData == NULL)
	{
		return IGL_ADDING_IMAGEICON_ERROR;
	}

	pImageGridListItem->objectId = m_objectCnt;

	m_rawDataImageIconData[m_objectCnt].renderUiNode = m_imageGridListData->renderUiNode;
	m_rawDataImageIconData[m_objectCnt].imageData = pImageGridListItem->imageData;

	m_rawDataImageIconData[m_objectCnt].iconPosX = 0.0 + m_imageGridListData->itemWidth * (m_objectCnt%m_imageGridListData->columnNums)  + m_imageGridListData->horizontalSpacing * ((m_objectCnt%m_imageGridListData->columnNums) + 1);
	m_rawDataImageIconData[m_objectCnt].iconPosY = 0.0 + m_imageGridListData->itemHeight * (m_objectCnt/m_imageGridListData->columnNums) + m_imageGridListData->verticalSpacing * ((m_objectCnt/m_imageGridListData->columnNums) + 1);

	m_rawDataImageIconData[m_objectCnt].iconWidth = m_imageGridListData->itemWidth;
	m_rawDataImageIconData[m_objectCnt].iconHeight = m_imageGridListData->itemHeight;

	m_rawDataImageIconData[m_objectCnt].imageWidth = pImageGridListItem->imageWidth;
	m_rawDataImageIconData[m_objectCnt].imageHeight = pImageGridListItem->imageHeight;

	m_rawDataImageIconData[m_objectCnt].targetIndex = m_gridListSpiritId;
	m_rawDataImageIconData[m_objectCnt].insertFlag = InsertFlag_Child;

	m_rawDataImageIconData[m_objectCnt].visibilityStatus = pImageGridListItem->visibilityStatus;
	m_rawDataImageIconData[m_objectCnt].refreshStatus = pImageGridListItem->refreshStatus;
	
	m_rawDataImageIconData[m_objectCnt].trigger = pImageGridListItem->trigger;

	m_rawDataImageIcon[m_objectCnt] = new HMIRawDataImageIcon(&m_rawDataImageIconData[m_objectCnt]);

	if(m_imageGridListData->withTextFlag == 1)
	{
		memcpy(&m_textEditData[m_objectCnt], &pImageGridListItem->textInfo, sizeof(HmiTextEditDataT));
		m_textEditData[m_objectCnt].textContent[0] = pImageGridListItem->textInfo.textContent[0];
		m_textEditData[m_objectCnt].targetIndex = m_gridListSpiritId;
		m_textEditData[m_objectCnt].insertFlag = InsertFlag_Child;
		m_textEdit[m_objectCnt] = new HmiTextEdit(&m_textEditData[m_objectCnt], m_imageGridListData->renderUiNode);
	}

	m_objectCnt ++;

	return IGL_NORMAL;
}
int HMIImageGridList::Update(unsigned char pRefreshFlag, unsigned char pRefreshVisibility, unsigned char pCurrentItemNum)
{
	if(m_imageGridListData->gridListMode == GRIDLIST_BKG_MODE)
	{
		ISpirit * imageGridLayer;
		imageGridLayer = m_rawDataImageIconData->renderUiNode->GetSpirit(m_gridListSpiritId);
		imageGridLayer->SetEnable(1);
		imageGridLayer->MasksToBound(TRUE);
	}
	else if(m_imageGridListData->gridListMode == GRIDLIST_NORMAL_MODE)
	{
		ILayoutPanel * imageGridLayer;
		imageGridLayer = m_rawDataImageIconData->renderUiNode->GetLayoutPanel(m_gridListSpiritId);
		imageGridLayer->SetEnable(1);
		imageGridLayer->MasksToBound(TRUE);
	}
	m_currentImageFileNum = m_objectCnt;
	if(pRefreshVisibility)
	{
		pCurrentItemNum = m_objectCnt < pCurrentItemNum ? m_objectCnt : pCurrentItemNum;
		m_currentImageFileNum = pCurrentItemNum;
		for(int i = 0; i < m_objectCnt; i++)
		{
			if(i < pCurrentItemNum)
			{
				m_rawDataImageIcon[i]->SetVisibility(1);
				if(m_imageGridListData->withTextFlag == 1)
				{
					m_textEdit[i]->SetVisibility(1);
				}
			}
			else
			{
				m_rawDataImageIcon[i]->SetVisibility(0);
				if(m_imageGridListData->withTextFlag == 1)
				{
					m_textEdit[i]->SetVisibility(0);
				}
			}
		}
	}

	for(int i = 0; i < m_objectCnt; i++)
	{
		unsigned char* tmp = (unsigned char*) m_rawDataImageIconData[i].imageData;
		m_rawDataImageIcon[i]->Update(m_rawDataImageIconData[i].imageData, pRefreshFlag);
		if(m_imageGridListData->withTextFlag == 1)
		{
			m_textEdit[i]->Update(m_textEditData[i].textContent[0]);
		}

		//m_rawDataImageIcon[i]->ResetImageIconPos(m_rawDataImageIconData[i].iconPosX , m_rawDataImageIconData[i].iconPosY + 320.0, GRID_MOVING, m_imageGridListData->posY, m_imageGridListData->gridListHeight);
	}
	return IGL_NORMAL;
}
int HMIImageGridList::SetVisibility(unsigned char flag)
{
	int textFlag = 0;

	for(int i = 0; i < m_objectCnt; i++)
	{
		m_rawDataImageIcon[i]->SetVisibility(flag);
		textFlag = flag;

		if(flag > 0 
			&& i >= m_currentImageFileNum)
		{
			m_rawDataImageIcon[i]->SetVisibility(0);
			textFlag = 0;
		}
		if(m_imageGridListData->withTextFlag == 1)
		{
			m_textEdit[i]->SetVisibility(textFlag);
		}				
	}
	
	if(m_imageGridListData->gridListMode == GRIDLIST_BKG_MODE)
	{
		ISpirit * imageGridLayer;
		imageGridLayer = m_rawDataImageIconData->renderUiNode->GetSpirit(m_gridListSpiritId);
		imageGridLayer->SetEnable(flag);
	}
	else if(m_imageGridListData->gridListMode == GRIDLIST_NORMAL_MODE)
	{
		ILayoutPanel * imageGridLayer;
		imageGridLayer = m_rawDataImageIconData->renderUiNode->GetLayoutPanel(m_gridListSpiritId);
		imageGridLayer->SetEnable(flag);
	}


	return IGL_NORMAL;
}
int HMIImageGridList::GetItemLayerId(int pObjectId)
{
	if(pObjectId >= m_objectCnt)
	{
		return 0;
	}

	return m_rawDataImageIcon[pObjectId]->GetLayerId();
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/06/17   Jensen Wang   Create the HMIImageGridList class.
\*===========================================================================*/
