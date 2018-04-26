#include "CSVDvrFileListHmi.h"

CSVDvrFileListHmi::CSVDvrFileListHmi(IUINode* pUiNode = NULL, int pUiNodeId = -1): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	m_imageGridVisibility = 0;
	memset(m_gridListTrigger, NULL, IMAGE_GRID_LIST_ITEM_NUM * sizeof(IActionTrigger*));
}

CSVDvrFileListHmi::~CSVDvrFileListHmi()
{
 
	for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
	{
		SAFE_DELETE(m_imageGridListItem[i].imageData);
		SAFE_DELETE(m_textEditData[i].textContent[0]);
        //SAFE_DELETE(m_textEditData[i].fontTypeMtlName);
		//SAFE_DELETE(m_textEdit[i]);
	}

}
int CSVDvrFileListHmi::SetHmiParams()
{

	m_imageGridList = new HMIImageGridList(&m_imageGridListData);

	for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
	{
		m_imageGridListItem[i].objectId = 0;
		m_imageGridList->AddGridItem(&m_imageGridListItem[i]);
	}
	m_imageGridList->SetVisibility(0);


	return HMI_SUCCESS;
}

int CSVDvrFileListHmi::Init(int window_width, int window_height)
{
	float radio = 227.0/1280.0;
	float titlePosXInterval = 80.0;
	float titleSelInterval = 10.0;
	float selBoxToImageInterval = 10.0;

	unsigned char currentVehicleTypeId;
	CAvmRenderDataBase::GetInstance()->GetVehicleTypeId(currentVehicleTypeId);

	m_imageGridListData.renderUiNode = m_uiNode;
	m_imageGridListData.withTextFlag = 1;

	switch(currentVehicleTypeId)
	{
		case CHANGAN_S302:
			m_imageGridListData.columnNums = 3;
			m_imageGridListData.rowNums = 2;
			m_imageGridListData.horizontalSpacing = 60.0;
			m_imageGridListData.verticalSpacing = 100.0;
			m_imageGridListData.posX = 0.0;
			m_imageGridListData.posY = 0.0;
			m_imageGridListData.gridListWidth = 1280.0;
			m_imageGridListData.gridListHeight = 720.0;
			m_imageGridListData.itemWidth = 192.0;
			m_imageGridListData.itemHeight = 112.0;	
			m_imageGridListData.gridListBkgImg = "default";			
			m_imageGridListData.gridListMode = GRIDLIST_BKG_MODE;
		break;
        case CHANGAN_V302:
			
        break;
		default:
			m_imageGridListData.columnNums = 3;
			m_imageGridListData.rowNums = 2;
			m_imageGridListData.horizontalSpacing = 60.0;
			m_imageGridListData.verticalSpacing = 100.0;
			m_imageGridListData.posX = 0.0;
			m_imageGridListData.posY = 0.0;
			m_imageGridListData.gridListWidth = 1280.0;
			m_imageGridListData.gridListHeight = 720.0;
			m_imageGridListData.itemWidth = 192.0;
			m_imageGridListData.itemHeight = 112.0;	
			m_imageGridListData.gridListBkgImg = "default";			
			m_imageGridListData.gridListMode = GRIDLIST_BKG_MODE;		
		break;
	}

	

	for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
	{
		m_imageGridListItem[i].objectId = 0;
		m_imageGridListItem[i].selectedStatus = 0;
		m_imageGridListItem[i].imageWidth = m_imageGridListData.itemWidth;
		m_imageGridListItem[i].imageHeight = m_imageGridListData.itemHeight;
		m_imageGridListItem[i].visibilityStatus = 0;
		m_imageGridListItem[i].refreshStatus = 0;
		m_imageGridListItem[i].imageData = new char[m_imageGridListItem[i].imageWidth * m_imageGridListItem[i].imageHeight * 3];
		memset(m_imageGridListItem[i].imageData, 200, sizeof(char)*m_imageGridListItem[i].imageWidth * m_imageGridListItem[i].imageHeight*3);
		m_imageGridListItem[i].trigger = NULL;

		m_textEditData[i].pos[0] = (m_imageGridListData.itemWidth + m_imageGridListData.horizontalSpacing) * (i % m_imageGridListData.columnNums) + m_imageGridListData.horizontalSpacing - 25;
		m_textEditData[i].pos[1] = (m_imageGridListData.itemHeight + m_imageGridListData.verticalSpacing) * (i / m_imageGridListData.columnNums + 1) + 5.0;
		m_textEditData[i].width = 20;
		m_textEditData[i].font_size = 4.0;
		m_textEditData[i].line_num = 1;
		m_textEditData[i].visibilityStatus = 1;
		m_textEditData[i].targetIndex = -1;
		m_textEditData[i].insertFlag = InsertFlag_Default;
		m_textEditData[i].fontTypeMtlName = XR_RES"text_box.ttf";
		m_textEditData[i].trigger = NULL;
		m_textEditData[i].textColor[0] = 1.0;
		m_textEditData[i].textColor[1] = 1.0;
		m_textEditData[i].textColor[2] = 1.0;
		m_textEditData[i].textContent[0] = new char[100];
		char* ptext = "17:30-17:40 16/12/12";
		sprintf(m_textEditData[i].textContent[0],"%s", ptext);

		//m_imageGridListItem[i].textInfo = m_textEditData[i];
		memcpy(&m_imageGridListItem[i].textInfo, &m_textEditData[i], sizeof(HmiTextEditDataT));
		m_imageGridListItem[i].textInfo.textContent[0] = m_textEditData[i].textContent[0];

	}

	SetHmiParams();
	
	return HMI_SUCCESS;
}

int CSVDvrFileListHmi::Update(Hmi_Message_T & hmiMsg)
{
	DVR_GUI_LAYOUT_INST_EXT dvrData;
	CAvmRenderDataBase::GetInstance()->GetDvrData(&dvrData);
	
	static int currentFileNum = 0;
	int 	   fileNumCnt = 0;
    static int waitCnt = 0;
    static int currentThumbTab = 0;
	
	DVR_GRAPHIC_UIOBJ_EXT* fileListTabMsg = NULL;
	
	GUI_OBJ_THUMB_FRAME_INST_EXT* frameInst = NULL;

	fileListTabMsg = dvrData.pTable;

	if(dvrData.curLayout == GUI_LAYOUT_THUMB_EXT)
	{
		m_imageGridVisibility = 1;
		
		for(int i = 0; i < dvrData.ObjNum; i++)
		{				
			switch(fileListTabMsg[i].Id)
			{
			case  GUI_OBJ_ID_THUMB_FRAME_EXT:
				
				if(GUI_OBJ_STATUS_TYPE_POINTER_EXT == fileListTabMsg[i].status_type
					&& fileListTabMsg[i].uStatus.ptr)
				{
					frameInst = (GUI_OBJ_THUMB_FRAME_INST_EXT*)fileListTabMsg[i].uStatus.ptr;
					
					if(frameInst == NULL)
						break;

					if(IMAGE_GRID_LIST_ITEM_NUM != NUM_THUMBNAIL_PER_PAGE_EXT)
					{
						Log_Error("------The size of the file list isn't equal to the real nums of thumb!");
					}
					
					currentFileNum = 0;
					for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
					{
						if(frameInst->item[i].bValid)
						{
							currentFileNum ++;
							
							memcpy(m_imageGridListItem[i].imageData, frameInst->item[i].pPreviewBuf, sizeof(unsigned char)*m_imageGridListItem[i].imageWidth * m_imageGridListItem[i].imageHeight*3);

                            unsigned char namelen = strlen(frameInst->item[i].filename);
                            if(namelen < 28)
                            {
                                unsigned char nameOffset = 28 - namelen - 1;
                                char fileName[56];
                                for(int j = 0; j < nameOffset; j++)
                                {
                                    fileName[j] = 0x20;
                                }
                                for(int j = 0; j < namelen; j++)
                                {
                                    fileName[j + nameOffset] = frameInst->item[i].filename[j];
                                }
                                fileName[namelen + nameOffset] = 0x00;
                                sprintf(m_imageGridListItem[i].textInfo.textContent[0],"%s", fileName);                               
                            }
                            else
                            {
                                sprintf(m_imageGridListItem[i].textInfo.textContent[0],"%s", frameInst->item[i].filename);
                            }
						}
						
					}
										
					m_imageGridList->Update(1,1,currentFileNum);
					//m_imageGridList->Update();
				}
				break;
			
			default:
				break;
			}	
		}

	}
	else
	{
		m_imageGridVisibility = 0;
		
		if((dvrData.curLayout == GUI_LAYOUT_RECORD_EXT
			|| dvrData.curLayout == GUI_LAYOUT_PLAYBACK_VIDEO_EXT
			|| dvrData.curLayout == GUI_LAYOUT_PLAYBACK_IMAGE_EXT)
			&& fileListTabMsg)
		{
			for(int i = 0; i < dvrData.ObjNum; i++)
			{
				if(fileListTabMsg[i].Id == GUI_OBJ_ID_REC_VIEW_INDEX_EXT
					|| fileListTabMsg[i].Id == GUI_OBJ_ID_PB_VIEW_INDEX_EXT)
				{
					SetDvrView(fileListTabMsg[i].uStatus.ObjVal);
				}
			}
		}
	}

	RefreshHmi();
	return HMI_SUCCESS;
}

int CSVDvrFileListHmi::SetDvrView(unsigned char pViewCmd)
{
	if(pViewCmd == GUI_VIEW_INDEX_FRONT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_FRONT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_REAR_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_REAR_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_LEFT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_LEFT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_RIGHT_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(DVR_RIGHT_SINGLE_VIEW);
	}
	else if(pViewCmd == GUI_VIEW_INDEX_MATTS_EXT)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(MATTS_VIEW);
	}

	return HMI_SUCCESS;
}

int CSVDvrFileListHmi::RefreshHmi()
{
	m_imageGridList->SetVisibility(m_imageGridVisibility);

	return HMI_SUCCESS;
}
int CSVDvrFileListHmi::SetElementsVisibility(unsigned char pFlag)
{
	m_imageGridList->SetVisibility(pFlag);

	return HMI_SUCCESS;
}
int CSVDvrFileListHmi::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVDvrFileListHmi::DestroyHmiElems()
{
	return HMI_SUCCESS;
}

