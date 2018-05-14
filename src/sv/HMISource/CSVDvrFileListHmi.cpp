#include "CSVDvrFileListHmi.h"
#include "DVR_GUI_OBJ.h"

static int imageItemId[IMAGE_GRID_LIST_ITEM_NUM];

class CFileSelActionTrigger:public IActionTrigger
{
public:
	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		CGpuAvmEventDelegate m_eventDel(INPUT_EVENT_CTRL_CMD);
		Ctrl_Cmd_T m_dvrCmd;
		
		m_dvrCmd.MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd.MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd.parameter[0] = DVR_USER_CLICK_THUMB_SEL_TO_PLAY;
		for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
		{
			if(id == imageItemId[i])
			{			
				m_dvrCmd.parameter[1] = i;
			}
		}        
		m_eventDel.PostEventPayload((void*)&m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CFileSelActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};    

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
    int i = V302_FILE_BKG;
    m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
    m_baseButton[i]->SetVisibility(0);

	m_imageGridList = new HMIImageGridList(&m_imageGridListData);

	for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
	{
		m_imageGridListItem[i].objectId = 0;
		m_imageGridList->AddGridItem(&m_imageGridListItem[i]);
        imageItemId[i] = m_imageGridList->GetItemLayerId(m_imageGridListItem[i].objectId);
	}
	m_imageGridList->SetVisibility(0);

    m_pageNum = new HmiTextEdit(&m_pageNumData,m_uiNode);
    m_pageNum->SetVisibility(0);

    for(int i = V302_FILE_SCROLL_BACK; i < V302_FILE_BUTTON_NUM; i++)
    {
        m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
        m_baseButton[i]->SetVisibility(0);
    }
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

    float offset = 0;
	switch(currentVehicleTypeId)
	{
		case CHANGAN_S302:
			m_imageGridListData.columnNums = 4;
			m_imageGridListData.rowNums = 2;
			m_imageGridListData.horizontalSpacing = 75.0;  //100
			m_imageGridListData.verticalSpacing = 136.0;  //159
			m_imageGridListData.itemWidth = 192.0;
			m_imageGridListData.itemHeight = 112.0;
            m_imageGridListData.posX = offset + 0.0;
			m_imageGridListData.posY = 0.0;
			m_imageGridListData.gridListWidth = (m_imageGridListData.itemWidth + m_imageGridListData.horizontalSpacing) * m_imageGridListData.columnNums + m_imageGridListData.horizontalSpacing ;
			m_imageGridListData.gridListHeight = 700.0;
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
		m_imageGridListItem[i].trigger = new CFileSelActionTrigger;

		m_textEditData[i].pos[0] = (m_imageGridListData.itemWidth + m_imageGridListData.horizontalSpacing) * (i % m_imageGridListData.columnNums) + m_imageGridListData.horizontalSpacing - 25;
		m_textEditData[i].pos[1] = (m_imageGridListData.itemHeight + m_imageGridListData.verticalSpacing) * (i / m_imageGridListData.columnNums + 1) + 32.0;
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

    m_pageNumData.pos[0] = m_imageGridListData.posX + m_imageGridListData.gridListWidth * 0.5 - 12;
    m_pageNumData.pos[1] = 48;
    m_pageNumData.width = 25;
	m_pageNumData.font_size = 5.0;
	m_pageNumData.line_num = 1;
	m_pageNumData.visibilityStatus = 1;
	m_pageNumData.targetIndex = -1;
	m_pageNumData.insertFlag = InsertFlag_Default;
	m_pageNumData.fontTypeMtlName = XR_RES"text_box.ttf";
	m_pageNumData.trigger = NULL;
	m_pageNumData.textColor[0] = 0.625;
	m_pageNumData.textColor[1] = 0.625;
	m_pageNumData.textColor[2] = 0.625;
	m_pageNumData.textContent[0] = new char[100];
	char* ptext0 = "1234";
	sprintf(m_pageNumData.textContent[0],"%s", ptext0);

    int i = 0;

    i = V302_FILE_BKG;
    m_baseButtonData[i].pos[0] = offset;
    m_baseButtonData[i].pos[1] = 0;
    m_baseButtonData[i].width = window_width - offset;
    m_baseButtonData[i].height = window_height;
    m_baseButtonData[i].delegate_func = NULL;
    m_baseButtonData[i].trigger = NULL;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 0;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sCar/DVR/00.dds",XR_RES); 
    m_baseButtonData[i].animationStyle = BUTTON_NOMAL;
    
    i = V302_FILE_SCROLL_BACK;
    m_baseButtonData[i].pos[0] = m_imageGridListData.posX + m_imageGridListData.gridListWidth - 20;
    m_baseButtonData[i].pos[1] = 110;
    m_baseButtonData[i].width = 10;
    m_baseButtonData[i].height = 500;
    m_baseButtonData[i].delegate_func = NULL;
    m_baseButtonData[i].trigger = NULL;
	m_baseButtonData[i].icon_type = STATIC_ICON;
	m_baseButtonData[i].show_flag = 0;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sCar/DVR/edit_scroll_bkg.dds",XR_RES); 
    m_baseButtonData[i].animationStyle = BUTTON_NOMAL;

    i = V302_FILE_SCROLL_BLOCK;
    m_baseButtonData[i].pos[0] = m_baseButtonData[V302_FILE_SCROLL_BACK].pos[0];
    m_baseButtonData[i].pos[1] = 300;
    m_baseButtonData[i].width = 10;
    m_baseButtonData[i].height = 50;
    m_baseButtonData[i].delegate_func = NULL;
    m_baseButtonData[i].trigger = NULL;
    m_baseButtonData[i].icon_type = DYNAMIC_ICON;
	m_baseButtonData[i].show_flag = 0;
	m_baseButtonData[i].show_icon_num = 0;
	m_baseButtonData[i].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[i].icon_file_name[0],"%sS302/s302_scroll_block.dds",XR_RES); 
    m_baseButtonData[i].animationStyle = BUTTON_NOMAL;

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
    
    GUI_OBJ_THUMB_PAGENUM_INST_EXT* thumbPagenumInst = NULL;

	fileListTabMsg = dvrData.pTable;
//    Log_Error("=================dvrData.curLayout:%d",dvrData.curLayout);
//    dvrData.curLayout = GUI_LAYOUT_THUMB_EXT;

	if(dvrData.curLayout == GUI_LAYOUT_THUMB_EXT)
	{
		m_imageGridVisibility = 1;
		SetElementsVisibility(1);
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
					Log_Error("====================GUI_OBJ_ID_THUMB_FRAME_EXT:1");
					currentFileNum = 0;
					for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
					{
						if(frameInst->item[i].bValid)
						{
						    Log_Error("====================GUI_OBJ_ID_THUMB_FRAME_EXT:2 - %d",currentFileNum);
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
					Log_Error("====================GUI_OBJ_ID_THUMB_FRAME_EXT:3 - %d",currentFileNum);					
					m_imageGridList->Update(1,1,currentFileNum);
                    Log_Error("====================GUI_OBJ_ID_THUMB_FRAME_EXT:4");	
					//m_imageGridList->Update();
				}
				break;
			case GUI_OBJ_ID_THUMB_PAGE_NUM_EXT:
                
                if(GUI_OBJ_STATUS_TYPE_POINTER_EXT == fileListTabMsg[i].status_type && fileListTabMsg[i].uStatus.ptr)
                {
                    Log_Error("====================GUI_OBJ_ID_THUMB_PAGE_NUM_EXT:1");	
                    thumbPagenumInst = (GUI_OBJ_THUMB_PAGENUM_INST_EXT*)fileListTabMsg[i].uStatus.ptr;
                    unsigned char curPage = thumbPagenumInst->nCurPage;
                    unsigned char totalPage = thumbPagenumInst->nTotalPage;
                    Log_Error("curPage: %d, totalPage: %d", curPage, totalPage);
                    if(totalPage > 0)
                    {
                        sprintf(m_pageNumData.textContent[0],"%u / %u", curPage, totalPage);
                        m_pageNum->SetVisibility(1);
                        waitCnt = 0;
                        if(totalPage > 1)
                        {
                            float blockheight = m_baseButtonData[V302_FILE_SCROLL_BACK].height / totalPage;
                            if(curPage == 0) curPage = 1;
                            float blocklocation = m_baseButtonData[V302_FILE_SCROLL_BACK].pos[1] + (curPage - 1) * blockheight;
                            m_baseButton[V302_FILE_SCROLL_BLOCK]->SetVisibility(1);
                            m_baseButton[V302_FILE_SCROLL_BLOCK]->SetHeight(blockheight);
                            m_baseButton[V302_FILE_SCROLL_BLOCK]->SetY(blocklocation);
                        }
                        else 
                        {
                            m_baseButton[V302_FILE_SCROLL_BLOCK]->SetVisibility(0);
                        }
                    }
                    else
                    {
                        m_pageNum->SetVisibility(0);
                    }
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
//					SetDvrView(fileListTabMsg[i].uStatus.ObjVal);
				}
			}
		}
	}

	RefreshHmi();
	return HMI_SUCCESS;
}

int CSVDvrFileListHmi::RefreshHmi()
{
	m_imageGridList->SetVisibility(m_imageGridVisibility);
    m_pageNum->Update(m_pageNumData.textContent[0]);

    for(int i = V302_FILE_BKG; i < V302_FILE_BUTTON_NUM; i++)
    {
        m_baseButton[i]->Update();
    }
    
	return HMI_SUCCESS;
}
int CSVDvrFileListHmi::SetElementsVisibility(unsigned char pFlag)
{
	m_imageGridList->SetVisibility(pFlag);
    if(pFlag == 0)
    {
        m_pageNum->SetVisibility(pFlag);
        
    }
    for(int i = V302_FILE_BKG; i < V302_FILE_BUTTON_NUM; i++)
    {
        m_baseButton[i]->SetVisibility(pFlag);
    }    
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

