#include "CSVV302FileListTab.h"
#include "gpu_log.h"


CSVV302FileListTab::CSVV302FileListTab(IUINode* pUiNode = NULL, int pUiNodeId = -1)
{}

CSVV302FileListTab::~CSVV302FileListTab()
{
    for(int i = 0; i < V302_FILE_BUTTON_INDEX_NUM; i++)
    {
        SAFE_DELETE(m_baseButtonData[i].icon_file_name[0]);
        SAFE_DELETE(m_baseButton[i]);
    }    
}

int CSVV302FileListTab::SetHmiParams()
{
    m_baseButton[V302_FILE_BUTTON_INDEX_BG_IMAGE] = new HMIButton(&(m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE]),m_uiNode);
    m_baseButton[V302_FILE_BUTTON_INDEX_BG_IMAGE]->SetVisibility(0);

	m_imageGridList = new HMIImageGridList(&m_imageGridListData);

	for(int i = 0; i < V302_GRID_LIST_ITEM_NUM; i++)
	{
		m_imageGridListItem[i].objectId = 0;
		m_imageGridList->AddGridItem(&m_imageGridListItem[i]);
		m_imageItemId[i] = m_imageGridList->GetItemLayerId(m_imageGridListItem[i].objectId);
	}
	m_imageGridList->SetVisibility(0);

    return V302_MAIN_HMI_NORMAL;
}

int CSVV302FileListTab::Init(int window_width, int window_height)
{
    
    for(int i = 0; i < PREVIEW_HIGH * PREVIEW_WIDTH; i++)
    {
        m_tmpRGB[i * 3] = 255;
        m_tmpRGB[i * 3 + 1] = 255;
        m_tmpRGB[i * 3 + 2] = 0;
    }
    window_width = window_height / 1130.0 * 960.0;

    m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].pos[0] = 0;
    m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].pos[1] = 0;
	m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].width = window_width;
	m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].height = window_height;
	m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].delegate_func = NULL;
	m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].trigger = NULL;
    m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].icon_type = STATIC_ICON;
	m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].show_flag = 1;
	m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].show_icon_num = 0;
	m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].icon_file_name[0],"%sV302/filelist_bk.dds",XR_RES); 
	m_baseButtonData[V302_FILE_BUTTON_INDEX_BG_IMAGE].animationStyle = BUTTON_NOMAL;

    
    m_imageGridListData.renderUiNode = m_uiNode;
    m_imageGridListData.columnNums = 3;
    m_imageGridListData.rowNums = 4;
    m_imageGridListData.horizontalSpacing = 15.0 / 960.0 * window_width;
    m_imageGridListData.verticalSpacing = 40.0 / 1130.0 * window_height;
    m_imageGridListData.posX = 0.0 / 960.0 * window_width;
    m_imageGridListData.posY = 82.0 / 1130.0 * window_height;
    m_imageGridListData.itemWidth = 300.0 / 960.0 * window_width;
    m_imageGridListData.itemHeight = 170.0 / 1130.0 * window_height;    
    m_imageGridListData.gridListWidth = (m_imageGridListData.itemWidth + m_imageGridListData.horizontalSpacing) * m_imageGridListData.columnNums;
    m_imageGridListData.gridListHeight = (m_imageGridListData.itemHeight + m_imageGridListData.verticalSpacing) * m_imageGridListData.rowNums;

    m_imageGridListData.withTextFlag = 1;
    
	for(int i = 0; i < V302_GRID_LIST_ITEM_NUM; i++)
	{
		m_imageGridListItem[i].objectId = 0;
		m_imageGridListItem[i].selectedStatus = 0;
		m_imageGridListItem[i].imageWidth = PREVIEW_WIDTH;
		m_imageGridListItem[i].imageHeight = PREVIEW_HIGH;
		m_imageGridListItem[i].visibilityStatus = 0;
		m_imageGridListItem[i].refreshStatus = 0;
		m_imageGridListItem[i].imageData = new char[PREVIEW_WIDTH * PREVIEW_HIGH * 3];
		memset(m_imageGridListItem[i].imageData, 200, sizeof(char) * PREVIEW_WIDTH * PREVIEW_HIGH * 3);
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
		char* ptext = "2018/04/10/16/15/20.mp4";
		sprintf(m_textEditData[i].textContent[0],"%s", ptext);

		//m_imageGridListItem[i].textInfo = m_textEditData[i];
		memcpy(&m_imageGridListItem[i].textInfo, &m_textEditData[i], sizeof(HmiTextEditDataT));
		m_imageGridListItem[i].textInfo.textContent[0] = m_textEditData[i].textContent[0];

	}
    
    SetHmiParams();
    
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302FileListTab::Update(Hmi_Message_T& hmiMsg)
{
    /*
 	static int currentFileNum = 0;
	int 	   fileNumCnt = 0;
    static int waitCnt = 0;
    static int currentThumbTab = 0;
	
	DVR_GRAPHIC_UIOBJ* fileListTabMsg = NULL;
	
	GUI_OBJ_THUMB_EDIT_INST* editInst = NULL;
	
	GUI_OBJ_THUMB_FRAME_INST* frameInst = NULL;

	GUI_OBJ_DIALOG_INST*	  dialogInst = NULL;

    GUI_OBJ_THUMB_PAGENUM_INST* thumbPagenumInst = NULL;

	if((DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable)
	{
		fileListTabMsg = (DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable;
		
		for(int i = 0; i < hmiMsg.dvrTabMsg.objNum; i++)
		{			
			switch(fileListTabMsg[i].Id)
			{
			case GUI_OBJ_ID_THUMB_TAB:
				break;
			case GUI_OBJ_ID_THUMB_EDIT:
				break;
			case GUI_OBJ_ID_THUMB_EDIT_SEL_CHECKBOX:
				break;
			case  GUI_OBJ_ID_THUMB_FRAME:
				if(GUI_OBJ_STATUS_TYPE_POINTER == fileListTabMsg[i].status_type
					&& fileListTabMsg[i].uStatus.ptr)
				{
					frameInst = (GUI_OBJ_THUMB_FRAME_INST*)fileListTabMsg[i].uStatus.ptr;
					
					if(frameInst == NULL)
						break;

					if(IMAGE_GRID_LIST_ITEM_NUM != NUM_THUMBNAIL_PER_PAGE)
					{
						Log_Error("------The size of the file list isn't equal to the real nums of thumb!");
					}
					
					currentFileNum = 0;
					for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
					{
						if(frameInst->item[i].bValid)
						{
							currentFileNum ++;
							
							memcpy(m_imageGridListItem[i].imageData, frameInst->item[i].pPreviewBuf, sizeof(char) * PREVIEW_HIGH * PREVIEW_WIDTH * 3);

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
				}
				break;
			case GUI_OBJ_ID_THUMB_CAPACITY:	
				break;
			case GUI_OBJ_ID_DIALOG:
				break;
			case GUI_OBJ_ID_WARNING:
				break;
            case GUI_OBJ_ID_THUMB_PAGE_NUM:
                break;
			default:
				break;
			}	
		}

	}
    */
    for(int i = 0; i < V302_GRID_LIST_ITEM_NUM; i++)
    {
        memcpy(m_imageGridListItem[i].imageData, m_tmpRGB, sizeof(char) * PREVIEW_HIGH * PREVIEW_WIDTH * 3);
    }
    m_imageGridList->Update(1,1,12);

	RefreshHmi();   
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302FileListTab::RefreshHmi()
{
    
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302FileListTab::SetElementsVisibility(unsigned char pFlag)
{
    m_baseButton[V302_FILE_BUTTON_INDEX_BG_IMAGE]->SetVisibility(pFlag);
    m_imageGridList->SetVisibility(pFlag);    
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302FileListTab::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
    return V302_MAIN_HMI_NORMAL;
}

int CSVV302FileListTab::DestroyHmiElems()
{
    return V302_MAIN_HMI_NORMAL;
}






















