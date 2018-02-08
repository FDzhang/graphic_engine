#include "CSVDvrFileListTab.h"
#include "DVR_GUI_OBJ.h"

static int imageItemId[IMAGE_GRID_LIST_ITEM_NUM];
static int selBoxItemId[IMAGE_GRID_LIST_ITEM_NUM];
static int selFlagItemId[IMAGE_GRID_LIST_ITEM_NUM];
static int editStatus = GUI_SWITCH_STATE_OFF;

class CLoopRecTabActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CLoopRecTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_TAB;
		m_dvrCmd->parameter[1] = GUI_THUMB_TAB_LOOPENC;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CLoopRecTabActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}

};

class CEmergencyTabActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEmergencyTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_TAB;
		m_dvrCmd->parameter[1] = GUI_THUMB_TAB_EMERGENCY;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CEmergencyTabActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CPhotoFileTabActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CPhotoFileTabActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_TAB;
		m_dvrCmd->parameter[1] = GUI_THUMB_TAB_PHOTO;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CPhotoFileTabActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_EDIT;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
	
		Log_Message("-----------CEditActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};
	
class CEditCancelActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditCancelActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_EDIT_CANCEL;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CEditCancelActionTrigger: %d", sizeof(Ctrl_Cmd_T));

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditSaveActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditSaveActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_EDIT_SAVE;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CEditSaveActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditDeleteActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditDeleteActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_EDIT_DELETE;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CEditDeleteActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditSelAllActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditSelAllActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_EDIT_SELECT_ALL;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CEditSelAllActionTrigger: %d", sizeof(Ctrl_Cmd_T));

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditSelActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditSelActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);

		if(editStatus == GUI_SWITCH_STATE_OFF)
		{
			m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_SEL_TO_PLAY;
		}
		else if(editStatus == GUI_SWITCH_STATE_ON)
		{		
			m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_EDIT_SEL;
		}

		for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
		{
			if(id == imageItemId[i])
			{			
				m_dvrCmd->parameter[1] = i;
			}
		}
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		Log_Message("-----------CEditSelActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{

	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditSelBoxActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditSelBoxActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);

        m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_EDIT_SEL;

        for (int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
        {
            if (id == selBoxItemId[i])
            {
                m_dvrCmd->parameter[1] = i;
            }
        }
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CEditSelBoxActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditSelFlagActionTrigger : public IActionTrigger
{
    ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditSelFlagActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
  public:
    virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
    {
        m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
        m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);

        m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_EDIT_SEL;

        for (int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
        {
            if (id == selFlagItemId[i])
            {
                m_dvrCmd->parameter[1] = i;
            }
        }
        m_eventDel->PostEventPayload((void *)m_dvrCmd, sizeof(Ctrl_Cmd_T));

        Log_Message("-----------CEditSelFlagActionTrigger: %d", sizeof(Ctrl_Cmd_T));
    }
    virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
    {
    }
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditDialogDelConfirmActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditDialogDelConfirmActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_DIALOG;
		m_dvrCmd->parameter[1] = DIALOG_SEL_YES;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CEditDialogDelConfirmActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CEditDialogDelCancelActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CEditDialogDelCancelActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_DIALOG;
		m_dvrCmd->parameter[1] = DIALOG_SEL_NO;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CEditDialogDelCancelActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};


class CFileScrollUpActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CFileScrollUpActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_PREV_PAGE;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CFileScrollUpActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};

class CFileScrollDownActionTrigger : public IActionTrigger
{
	ACTION_TRIGGER_EVENT_CONSTRUCTION(CFileScrollDownActionTrigger, m_eventDel, INPUT_EVENT_CTRL_CMD, Ctrl_Cmd_T, m_dvrCmd)
public:

	virtual Void OnPress(Int32 id, Int32 x = 0, Int32 y = 0)
	{
	}
	virtual Void OnRelease(Int32 id, Boolean isIn, Int32 x = 0, Int32 y = 0)
	{
		m_dvrCmd->MsgHead.MsgType = IPC_MSG_TYPE_M4_A15_DVR_CMD;
		m_dvrCmd->MsgHead.MsgSize = sizeof(Ctrl_Cmd_T);
		m_dvrCmd->parameter[0] = DVR_USER_CLICK_THUMB_NEXT_PAGE;
		m_eventDel->PostEventPayload((void*)m_dvrCmd, sizeof(Ctrl_Cmd_T));
		
		Log_Message("-----------CFileScrollDownActionTrigger: %d", sizeof(Ctrl_Cmd_T));
	}
	virtual Void OnMove(Int32 id, Int32 x = 0, Int32 y = 0)
	{
		
	}
};


CSVDvrFileListTab::CSVDvrFileListTab(IUINode* pUiNode = NULL, int pUiNodeId = -1): ISVHmi::ISVHmi(pUiNode, pUiNodeId)
{
	memset(m_trigger, NULL, DVR_FILELIST_TAB_ELEMEMT_NUM * sizeof(IActionTrigger*));
	memset(m_buttonStatus, 0, DVR_FILELIST_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	memset(m_buttonVisibility, 0, DVR_FILELIST_TAB_ELEMEMT_NUM * sizeof(unsigned char));
	m_imageGridVisibility = 0;
	memset(m_dialogVisibility, 0, DVR_FILELIST_DIALOG_NUM * sizeof(unsigned char));
	memset(m_gridListTrigger, NULL, IMAGE_GRID_LIST_ITEM_NUM * sizeof(IActionTrigger*));
}

CSVDvrFileListTab::~CSVDvrFileListTab()
{
    for(int i = 0; i < DVR_FILELIST_TAB_ELEMEMT_NUM; i++)
	{	
		//SAFE_DELETE(m_baseButton[i]);
		SAFE_DELETE(m_trigger[i]);	
		for(int j = 0; j < DVR_FILELIST_TAB_ELEMEMT_NUM; j++)
		{
		    SAFE_DELETE(m_baseButtonData[j].icon_file_name[0]);

			if(j == DVR_FILELIST_TAB_EDIT_ICON
				|| j == DVR_FILELIST_TAB_EDIT_CANCEL
				|| j == DVR_FILELIST_TAB_EDIT_SAVE
				|| j == DVR_FILELIST_TAB_EDIT_DELETE
				|| j == DVR_FILELIST_TAB_EDIT_SELECTED_ALL
				|| j == DVR_FILELIST_TAB_SCROLL_UP
				|| j == DVR_FILELIST_TAB_SCROLL_DOWN)
			{
				SAFE_DELETE(m_baseButtonData[j].icon_file_name[1]);
			}
                
			if(j == DVR_FILELIST_TAB_EDIT_SAVE)
			{
				SAFE_DELETE(m_baseButtonData[j].icon_file_name[2]);
			}                
		}
	}
	for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
	{
		SAFE_DELETE(m_imageGridListItem[i].imageData);
		SAFE_DELETE(m_textEditData[i].textContent[0]);
		//SAFE_DELETE(m_textEdit[i]);
	}
	for(int i = 0; i < DVR_FILELIST_DIALOG_NUM; i++)
	{
		for(int j = 0; j < DIALOG_IMAGE_NUM; j++)
		{
		    SAFE_DELETE(m_dialogData[i].iconFileName[j]);
	    }
		//SAFE_DELETE(m_dialog[i]);
	}	

	for(int i = 0; i < DIALOG_CONFIRM_CANCEL_ELEMENT_NUM; i++)
	{
		SAFE_DELETE(m_dialogData[DVR_FILELIST_DIALOG_DEL].trigger[i]);
	}
    SAFE_DELETE(m_pageNumData.textContent[0]);
    SAFE_DELETE(m_noFileTextData.textContent[0]);
	//SAFE_DELETE(m_imageGridList);		

}
int CSVDvrFileListTab::SetHmiParams()
{

	m_imageGridList = new HMIImageGridList(&m_imageGridListData);

	for(int i = 0; i < IMAGE_GRID_LIST_ITEM_NUM; i++)
	{
		m_imageGridListItem[i].objectId = 0;
		m_imageGridList->AddGridItem(&m_imageGridListItem[i]);
		imageItemId[i] = m_imageGridList->GetItemLayerId(m_imageGridListItem[i].objectId);
	}
	m_imageGridList->SetVisibility(0);

	//m_imageGridList->Update();
	//m_imageGridList->SetVisibility(1);

	//memset(m_imageGridListItem[0].imageData, 0, sizeof(char)*m_imageGridListItem[2].imageWidth * m_imageGridListItem[2].imageHeight*3);

	//m_imageGridList->Update(1,1,1);

	m_baseButtonData[DVR_FILELIST_TAB_LOOP_REC_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_LOOP_REC_TITLE].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_LOOP_REC_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_LOOP_REC_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_LOOP_REC_TITLE].icon_file_name[0],"%sCar/DVR/loop_rec_title.dds",XR_RES); 
	m_trigger[DVR_FILELIST_TAB_LOOP_REC_TITLE] = new CLoopRecTabActionTrigger;

	m_baseButtonData[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE].icon_file_name[0] = new char[100];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE].icon_file_name[0],"%sCar/DVR/file_tab_emergency_save_title.dds",XR_RES); 
	m_trigger[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE] = new CEmergencyTabActionTrigger;

	m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE].icon_file_name[0],"%sCar/DVR/picture_title.dds",XR_RES); 
	m_trigger[DVR_FILELIST_TAB_PICTURE_TITLE] = new CPhotoFileTabActionTrigger;
		
	m_baseButtonData[DVR_FILELIST_TAB_LR_TITLE_SELECTED].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_LR_TITLE_SELECTED].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_LR_TITLE_SELECTED].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_LR_TITLE_SELECTED].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_LR_TITLE_SELECTED].icon_file_name[0],"%sCar/DVR/title_selected_icon.dds",XR_RES); 
	
	m_baseButtonData[DVR_FILELIST_TAB_ES_TITLE_SELECTED].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_ES_TITLE_SELECTED].show_flag = 0;
	m_baseButtonData[DVR_FILELIST_TAB_ES_TITLE_SELECTED].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_ES_TITLE_SELECTED].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_ES_TITLE_SELECTED].icon_file_name[0],"%sCar/DVR/title_selected_icon.dds",XR_RES); 
		
	m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED].show_flag = 0;
	m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED].icon_file_name[0],"%sCar/DVR/title_selected_icon.dds",XR_RES); 

	m_baseButtonData[DVR_FILELIST_TAB_EDIT_ICON].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_ICON].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_ICON].show_icon_num = 1;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_ICON].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_ICON].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_ICON].icon_file_name[0],"%sCar/DVR/edit_icon_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_ICON].icon_file_name[1],"%sCar/DVR/edit_icon_press.dds",XR_RES); 	
	m_trigger[DVR_FILELIST_TAB_EDIT_ICON] = new CEditActionTrigger;

	m_baseButtonData[DVR_FILELIST_TAB_EDIT_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_BKG].show_flag = 0;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_BKG].icon_file_name[0],"%sCar/DVR/edit_contrl_bkg.dds",XR_RES); 

	m_baseButtonData[DVR_FILELIST_TAB_EDIT_CANCEL].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_CANCEL].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_CANCEL].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_CANCEL].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_CANCEL].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_CANCEL].icon_file_name[0],"%sCar/DVR/edit_cancel_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_CANCEL].icon_file_name[1],"%sCar/DVR/edit_cancel_press.dds",XR_RES); 
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_CANCEL].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_trigger[DVR_FILELIST_TAB_EDIT_CANCEL] = new CEditCancelActionTrigger;

	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].icon_file_name[1] = new char[50];
    m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].icon_file_name[2] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].icon_file_name[0],"%sCar/DVR/edit_save_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].icon_file_name[1],"%sCar/DVR/edit_save_press.dds",XR_RES); 
    sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].icon_file_name[2],"%sCar/DVR/edit_save_disable.dds",XR_RES); 
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SAVE].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_trigger[DVR_FILELIST_TAB_EDIT_SAVE] = new CEditSaveActionTrigger;

	m_baseButtonData[DVR_FILELIST_TAB_EDIT_DELETE].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_DELETE].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_DELETE].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_DELETE].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_DELETE].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_DELETE].icon_file_name[0],"%sCar/DVR/edit_delete_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_DELETE].icon_file_name[1],"%sCar/DVR/edit_delete_press.dds",XR_RES); 
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_DELETE].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_trigger[DVR_FILELIST_TAB_EDIT_DELETE] = new CEditDeleteActionTrigger;

	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SELECTED_ALL].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SELECTED_ALL].show_flag = 1;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SELECTED_ALL].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SELECTED_ALL].icon_file_name[0] = new char[50];
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SELECTED_ALL].icon_file_name[1] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_SELECTED_ALL].icon_file_name[0],"%sCar/DVR/edit_sel_all_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_EDIT_SELECTED_ALL].icon_file_name[1],"%sCar/DVR/edit_sel_all_press.dds",XR_RES); 
	m_baseButtonData[DVR_FILELIST_TAB_EDIT_SELECTED_ALL].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_trigger[DVR_FILELIST_TAB_EDIT_SELECTED_ALL] = new CEditSelAllActionTrigger;


	for(int i = DVR_FILELIST_TAB_EDIT_SEL_BOX_1; i <= DVR_FILELIST_TAB_EDIT_SEL_FLAG_6; i += 2)
	{
		m_baseButtonData[i].icon_type = STATIC_ICON;
		m_baseButtonData[i].show_flag = 0;
		m_baseButtonData[i].show_icon_num = 0;
		m_baseButtonData[i].icon_file_name[0] = new char[50];
		sprintf(m_baseButtonData[i].icon_file_name[0],"%sCar/DVR/edit_box.dds",XR_RES); 
        m_trigger[i] = new CEditSelBoxActionTrigger;

		m_baseButtonData[i + 1].icon_type = STATIC_ICON;
		m_baseButtonData[i + 1].show_flag = 0;
		m_baseButtonData[i + 1].show_icon_num = 0;
		m_baseButtonData[i + 1].icon_file_name[0] = new char[50];
		sprintf(m_baseButtonData[i + 1].icon_file_name[0],"%sCar/DVR/edit_sel_flag.dds",XR_RES);
        m_trigger[i + 1] = new CEditSelFlagActionTrigger;

	}

	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_BKG].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_BKG].show_flag = 0;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_BKG].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_BKG].icon_file_name[0] = new char[50];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_SCROLL_BKG].icon_file_name[0],"%sCar/DVR/edit_scroll_bkg.dds",XR_RES); 
	
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_UP].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_UP].show_flag = 0;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_UP].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_UP].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_UP].icon_file_name[1] = new char[100];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_SCROLL_UP].icon_file_name[0],"%sCar/DVR/edit_scroll_up_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_SCROLL_UP].icon_file_name[1],"%sCar/DVR/edit_scroll_up_press.dds",XR_RES); 
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_UP].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_trigger[DVR_FILELIST_TAB_SCROLL_UP] = new CFileScrollUpActionTrigger;

	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_DOWN].icon_type = STATIC_ICON;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_DOWN].show_flag = 0;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_DOWN].show_icon_num = 0;
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_DOWN].icon_file_name[0] = new char[100];
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_DOWN].icon_file_name[1] = new char[100];
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_SCROLL_DOWN].icon_file_name[0],"%sCar/DVR/edit_scroll_down_normal.dds",XR_RES); 
	sprintf(m_baseButtonData[DVR_FILELIST_TAB_SCROLL_DOWN].icon_file_name[1],"%sCar/DVR/edit_scroll_down_press.dds",XR_RES); 
	m_baseButtonData[DVR_FILELIST_TAB_SCROLL_DOWN].animationStyle = BUTTON_FLASH_HIGHLIGHT;
	m_trigger[DVR_FILELIST_TAB_SCROLL_DOWN] = new CFileScrollDownActionTrigger;

	for(int i = DVR_FILELIST_TAB_LOOP_REC_TITLE; i < DVR_FILELIST_TAB_ELEMEMT_NUM; i++)
	{
		m_baseButtonData[i].pos[0] = m_buttonPos[i][BUTTON_POS_X];
		m_baseButtonData[i].pos[1] = m_buttonPos[i][BUTTON_POS_Y];
		m_baseButtonData[i].width = m_buttonSize[i][BUTTON_SIZE_WIDTH];
		m_baseButtonData[i].height = m_buttonSize[i][BUTTON_SIZE_HEIGHT];
		m_baseButtonData[i].delegate_func = NULL;
		m_baseButtonData[i].trigger = m_trigger[i];

		m_baseButton[i] = new HMIButton(&(m_baseButtonData[i]),m_uiNode);
		m_baseButton[i]->SetVisibility(0);
	}

    for(int i = DVR_FILELIST_TAB_EDIT_SEL_BOX_1; i <= DVR_FILELIST_TAB_EDIT_SEL_FLAG_6; i += 2)
    {
        selBoxItemId[(i - DVR_FILELIST_TAB_EDIT_SEL_BOX_1)/2] = m_baseButton[i]->GetButtonId();
        selFlagItemId[(i + 1 - DVR_FILELIST_TAB_EDIT_SEL_FLAG_1)/2] = m_baseButton[i + 1]->GetButtonId();
    }

	m_dialogData[DVR_FILELIST_DIALOG_DEL].dialogType = DIALOG_CONFIRM_CANCEL;
	m_dialogData[DVR_FILELIST_DIALOG_DEL].showFlag = 0;
	m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_BACKGROUND_IMG] = new char[100];
	sprintf(m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_BACKGROUND_IMG],"%sCar/DVR/dlg_bkg.dds",XR_RES); 
	m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_TITLE_IMG] = new char[100];
    sprintf(m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_TITLE_IMG],"%sCar/DVR/dlg_title_del_file.dds",XR_RES);  
    m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_CONFIRM_NORMAL_IMG] = new char[100];
	sprintf(m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_CONFIRM_NORMAL_IMG],"%sCar/DVR/dlg_icon_ok.dds",XR_RES); 
	m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG] = new char[100];
	sprintf(m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG],"%sCar/DVR/dlg_icon_ok_highlight.dds",XR_RES); 

	m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_CANCEL_NORMAL_IMG] = new char[100];
	sprintf(m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_CANCEL_NORMAL_IMG],"%sCar/DVR/dlg_icon_cancel.dds",XR_RES); 
	m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG] = new char[100];
	sprintf(m_dialogData[DVR_FILELIST_DIALOG_DEL].iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG],"%sCar/DVR/dlg_icon_cancel_highlight.dds",XR_RES); 

	m_dialogData[DVR_FILELIST_DIALOG_DEL].trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND] = NULL;//new CSelectorFirstActionTrigger;
	m_dialogData[DVR_FILELIST_DIALOG_DEL].trigger[DIALOG_CONFIRM] = new CEditDialogDelConfirmActionTrigger;
	m_dialogData[DVR_FILELIST_DIALOG_DEL].trigger[DIALOG_CANCEL] = new CEditDialogDelCancelActionTrigger;

	m_dialog[DVR_FILELIST_DIALOG_DEL] = new HMIDialog(&m_dialogData[DVR_FILELIST_DIALOG_DEL], m_uiNode);
	m_dialog[DVR_FILELIST_DIALOG_DEL]->SetVisibility(0);

    m_pageNum = new HmiTextEdit(&m_pageNumData,m_uiNode);
    m_pageNum->SetVisibility(0);

    m_noFileText = new HmiTextEdit(&m_noFileTextData,m_uiNode);
    m_noFileText->SetVisibility(0);
    

	return HMI_SUCCESS;
}
int CSVDvrFileListTab::Init(int window_width, int window_height)
{
	float radio = 227.0/1280.0;
	float titlePosXInterval = 80.0;
	float titleSelInterval = 10.0;
	float selBoxToImageInterval = 10.0;

	m_buttonSize[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_SIZE_WIDTH] = 113.0;
	m_buttonSize[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_X] = radio*window_width + titlePosXInterval;
	m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_Y] = 80.0 + 12.0;

	m_buttonSize[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_SIZE_WIDTH] = 114.0;
	m_buttonSize[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_SIZE_HEIGHT] = 30.0;
	m_buttonPos[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_X] + m_buttonSize[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_SIZE_WIDTH] + titlePosXInterval;
	m_buttonPos[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_FILELIST_TAB_PICTURE_TITLE][BUTTON_SIZE_WIDTH] = 57.0;
	m_buttonSize[DVR_FILELIST_TAB_PICTURE_TITLE][BUTTON_SIZE_HEIGHT] = 29.0;
	m_buttonPos[DVR_FILELIST_TAB_PICTURE_TITLE][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_POS_X]+ m_buttonSize[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_SIZE_WIDTH] + titlePosXInterval;
	m_buttonPos[DVR_FILELIST_TAB_PICTURE_TITLE][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_FILELIST_TAB_LR_TITLE_SELECTED][BUTTON_SIZE_WIDTH] = 136.0;
	m_buttonSize[DVR_FILELIST_TAB_LR_TITLE_SELECTED][BUTTON_SIZE_HEIGHT] = 5.0;
	m_buttonPos[DVR_FILELIST_TAB_LR_TITLE_SELECTED][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_X] - (m_buttonSize[DVR_FILELIST_TAB_LR_TITLE_SELECTED][BUTTON_SIZE_WIDTH] - m_buttonSize[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_FILELIST_TAB_LR_TITLE_SELECTED][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_SIZE_HEIGHT] + titleSelInterval;

	m_buttonSize[DVR_FILELIST_TAB_ES_TITLE_SELECTED][BUTTON_SIZE_WIDTH] = 136.0;
	m_buttonSize[DVR_FILELIST_TAB_ES_TITLE_SELECTED][BUTTON_SIZE_HEIGHT] = 5.0;
	m_buttonPos[DVR_FILELIST_TAB_ES_TITLE_SELECTED][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_POS_X] - (m_buttonSize[DVR_FILELIST_TAB_ES_TITLE_SELECTED][BUTTON_SIZE_WIDTH] - m_buttonSize[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_FILELIST_TAB_ES_TITLE_SELECTED][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_SIZE_HEIGHT] + titleSelInterval;

	m_buttonSize[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED][BUTTON_SIZE_WIDTH] = 136.0;
	m_buttonSize[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED][BUTTON_SIZE_HEIGHT] = 5.0;
	m_buttonPos[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_PICTURE_TITLE][BUTTON_POS_X] - (m_buttonSize[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED][BUTTON_SIZE_WIDTH] - m_buttonSize[DVR_FILELIST_TAB_PICTURE_TITLE][BUTTON_SIZE_WIDTH]) * 0.5;
	m_buttonPos[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_PICTURE_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_FILELIST_TAB_PICTURE_TITLE][BUTTON_SIZE_HEIGHT] + titleSelInterval;

	m_imageGridListData.renderUiNode = m_uiNode;
	m_imageGridListData.columnNums = 3;
	m_imageGridListData.rowNums = 2;
	m_imageGridListData.horizontalSpacing = 60.0;
	m_imageGridListData.verticalSpacing = 100.0;
	m_imageGridListData.posX = m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_X] - m_imageGridListData.horizontalSpacing;
	m_imageGridListData.posY = m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_Y] + m_buttonSize[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_SIZE_HEIGHT] - m_imageGridListData.verticalSpacing + 60.0;
	m_imageGridListData.gridListWidth = 1000.0;
	m_imageGridListData.gridListHeight = 1000.0;
	m_imageGridListData.itemWidth = 192.0;
	m_imageGridListData.itemHeight = 112.0;
	m_imageGridListData.withTextFlag = 1;

	m_imageGridListData.gridListMode = GRIDLIST_NORMAL_MODE;

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
		m_imageGridListItem[i].trigger = new CEditSelActionTrigger;

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

	m_buttonSize[DVR_FILELIST_TAB_EDIT_ICON][BUTTON_SIZE_WIDTH] = 34.0;
	m_buttonSize[DVR_FILELIST_TAB_EDIT_ICON][BUTTON_SIZE_HEIGHT] = 33.0;
	m_buttonPos[DVR_FILELIST_TAB_EDIT_ICON][BUTTON_POS_X] = m_imageGridListData.posX + (m_imageGridListData.itemWidth + m_imageGridListData.horizontalSpacing) * m_imageGridListData.columnNums - m_buttonSize[DVR_FILELIST_TAB_EDIT_ICON][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_FILELIST_TAB_EDIT_ICON][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_LOOP_REC_TITLE][BUTTON_POS_Y];

	m_buttonSize[DVR_FILELIST_TAB_EDIT_BKG][BUTTON_SIZE_WIDTH] = 753.0;
	m_buttonSize[DVR_FILELIST_TAB_EDIT_BKG][BUTTON_SIZE_HEIGHT] = 61.0;
	m_buttonPos[DVR_FILELIST_TAB_EDIT_BKG][BUTTON_POS_X] = radio * window_width + 13.0;
	m_buttonPos[DVR_FILELIST_TAB_EDIT_BKG][BUTTON_POS_Y] = window_height - m_buttonSize[DVR_FILELIST_TAB_EDIT_BKG][BUTTON_SIZE_HEIGHT] - 80.0;

	m_buttonSize[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_SIZE_WIDTH] = 188.0;
	m_buttonSize[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_SIZE_HEIGHT] = 60.0;
	m_buttonPos[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_EDIT_BKG][BUTTON_POS_X];
	m_buttonPos[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_EDIT_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_FILELIST_TAB_EDIT_SAVE][BUTTON_SIZE_WIDTH] = 188.0;
	m_buttonSize[DVR_FILELIST_TAB_EDIT_SAVE][BUTTON_SIZE_HEIGHT] = 60.0;
	m_buttonPos[DVR_FILELIST_TAB_EDIT_SAVE][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_POS_X] + m_buttonSize[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_FILELIST_TAB_EDIT_SAVE][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_POS_Y];

	m_buttonSize[DVR_FILELIST_TAB_EDIT_DELETE][BUTTON_SIZE_WIDTH] = 188.0;
	m_buttonSize[DVR_FILELIST_TAB_EDIT_DELETE][BUTTON_SIZE_HEIGHT] = 60.0;
	m_buttonPos[DVR_FILELIST_TAB_EDIT_DELETE][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_EDIT_SAVE][BUTTON_POS_X] + m_buttonSize[DVR_FILELIST_TAB_EDIT_SAVE][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_FILELIST_TAB_EDIT_DELETE][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_EDIT_SAVE][BUTTON_POS_Y];

	m_buttonSize[DVR_FILELIST_TAB_EDIT_SELECTED_ALL][BUTTON_SIZE_WIDTH] = 188.0;
	m_buttonSize[DVR_FILELIST_TAB_EDIT_SELECTED_ALL][BUTTON_SIZE_HEIGHT] = 60.0;
	m_buttonPos[DVR_FILELIST_TAB_EDIT_SELECTED_ALL][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_EDIT_DELETE][BUTTON_POS_X] + m_buttonSize[DVR_FILELIST_TAB_EDIT_DELETE][BUTTON_SIZE_WIDTH];
	m_buttonPos[DVR_FILELIST_TAB_EDIT_SELECTED_ALL][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_EDIT_DELETE][BUTTON_POS_Y];


	for(int i = DVR_FILELIST_TAB_EDIT_SEL_BOX_1; i <= DVR_FILELIST_TAB_EDIT_SEL_FLAG_6; i += 2)
	{
		m_buttonSize[i][BUTTON_SIZE_WIDTH] = 21.0;
		m_buttonSize[i][BUTTON_SIZE_HEIGHT] = 22.0;
		m_buttonPos[i][BUTTON_POS_X] = m_imageGridListData.posX + (m_imageGridListData.horizontalSpacing + m_imageGridListData.itemWidth) * (((i - DVR_FILELIST_TAB_EDIT_SEL_BOX_1)/2)%m_imageGridListData.columnNums + 1) - m_buttonSize[i][BUTTON_SIZE_WIDTH] - selBoxToImageInterval;
		m_buttonPos[i][BUTTON_POS_Y] = m_imageGridListData.posY + (m_imageGridListData.verticalSpacing + m_imageGridListData.itemHeight) * (((i - DVR_FILELIST_TAB_EDIT_SEL_BOX_1)/2)/m_imageGridListData.columnNums) + m_imageGridListData.verticalSpacing + selBoxToImageInterval;
	
		m_buttonSize[i + 1][BUTTON_SIZE_WIDTH] = 21.0;
		m_buttonSize[i + 1][BUTTON_SIZE_HEIGHT] = 16.0;
		m_buttonPos[i + 1][BUTTON_POS_X] = m_imageGridListData.posX + (m_imageGridListData.horizontalSpacing + m_imageGridListData.itemWidth) * (((i - DVR_FILELIST_TAB_EDIT_SEL_BOX_1)/2)%m_imageGridListData.columnNums + 1) - m_buttonSize[i][BUTTON_SIZE_WIDTH] - selBoxToImageInterval;
		m_buttonPos[i + 1][BUTTON_POS_Y] = m_imageGridListData.posY + (m_imageGridListData.verticalSpacing + m_imageGridListData.itemHeight) * (((i - DVR_FILELIST_TAB_EDIT_SEL_BOX_1)/2)/m_imageGridListData.columnNums) + m_imageGridListData.verticalSpacing + selBoxToImageInterval;

	}

	m_buttonSize[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_SIZE_WIDTH] = 9.0;
	m_buttonSize[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_SIZE_HEIGHT] = 437.0;
	m_buttonPos[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_POS_X] = m_imageGridListData.posX + m_imageGridListData.horizontalSpacing + (m_imageGridListData.horizontalSpacing + m_imageGridListData.itemWidth) * m_imageGridListData.columnNums;
	m_buttonPos[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_POS_Y] = m_imageGridListData.posY + m_imageGridListData.verticalSpacing - 40.0;

	m_buttonSize[DVR_FILELIST_TAB_SCROLL_UP][BUTTON_SIZE_WIDTH] = 16;
	m_buttonSize[DVR_FILELIST_TAB_SCROLL_UP][BUTTON_SIZE_HEIGHT] = 10;
	m_buttonPos[DVR_FILELIST_TAB_SCROLL_UP][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_POS_X] - 4.0;
	m_buttonPos[DVR_FILELIST_TAB_SCROLL_UP][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_POS_Y];

	m_buttonSize[DVR_FILELIST_TAB_SCROLL_DOWN][BUTTON_SIZE_WIDTH] = 16;
	m_buttonSize[DVR_FILELIST_TAB_SCROLL_DOWN][BUTTON_SIZE_HEIGHT] = 10;
	m_buttonPos[DVR_FILELIST_TAB_SCROLL_DOWN][BUTTON_POS_X] = m_buttonPos[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_POS_X] - 4.0;
	m_buttonPos[DVR_FILELIST_TAB_SCROLL_DOWN][BUTTON_POS_Y] = m_buttonPos[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_POS_Y] + m_buttonSize[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_SIZE_HEIGHT] -  m_buttonSize[DVR_FILELIST_TAB_SCROLL_DOWN][BUTTON_SIZE_HEIGHT];

    m_pageNumData.pos[0] = (m_imageGridListData.posX + m_buttonPos[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_POS_X]) * 0.5 - 20;
    m_pageNumData.pos[1] = m_buttonPos[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_POS_Y] - 32;
    m_pageNumData.width = 25;
	m_pageNumData.font_size = 5.0;
	m_pageNumData.line_num = 1;
	m_pageNumData.visibilityStatus = 0;
	m_pageNumData.targetIndex = -1;
	m_pageNumData.insertFlag = InsertFlag_Default;
	m_pageNumData.fontTypeMtlName = XR_RES"text_box.ttf";
	m_pageNumData.trigger = NULL;
	m_pageNumData.textColor[0] = 0.625;
	m_pageNumData.textColor[1] = 0.625;
	m_pageNumData.textColor[2] = 0.625;
	m_pageNumData.textContent[0] = new char[100];
	char* ptext0 = "     ";
	sprintf(m_pageNumData.textContent[0],"%s", ptext0);    

    m_noFileTextData.pos[0] = (m_imageGridListData.posX + m_buttonPos[DVR_FILELIST_TAB_SCROLL_BKG][BUTTON_POS_X]) * 0.5 - 64;
    m_noFileTextData.pos[1] = (m_imageGridListData.posX + m_buttonPos[DVR_FILELIST_TAB_EDIT_CANCEL][BUTTON_POS_Y]) * 0.5 - 64;
    m_noFileTextData.width = 40;
	m_noFileTextData.font_size = 8.0;
	m_noFileTextData.line_num = 1;
	m_noFileTextData.visibilityStatus = 0;
	m_noFileTextData.targetIndex = -1;
	m_noFileTextData.insertFlag = InsertFlag_Default;
	m_noFileTextData.fontTypeMtlName = XR_RES"text_box.ttf";
	m_noFileTextData.trigger = NULL;
	m_noFileTextData.textColor[0] = 0.625;
	m_noFileTextData.textColor[1] = 0.625;
	m_noFileTextData.textColor[2] = 0.625;
	m_noFileTextData.textContent[0] = new char[100];
	char* ptext1 = "No File !";
	sprintf(m_noFileTextData.textContent[0],"%s", ptext1);        

/*	m_dialogData[DVR_FILELIST_DIALOG_DEL].width = 300.0;
	m_dialogData[DVR_FILELIST_DIALOG_DEL].height = 200.0;

	m_dialogData[DVR_FILELIST_DIALOG_DEL].pos[0] = m_buttonPos[DVR_FILELIST_TAB_EMERGENCY_SAVE_TITLE][BUTTON_POS_X];
	m_dialogData[DVR_FILELIST_DIALOG_DEL].pos[1] = 80.0 + 0.5 * (window_height - 160.0 - m_dialogData[DVR_FILELIST_DIALOG_DEL].height);
*/
	m_dialogData[DVR_FILELIST_DIALOG_DEL].width = 348.0;
	m_dialogData[DVR_FILELIST_DIALOG_DEL].height = 183.0;
    m_dialogData[DVR_FILELIST_DIALOG_DEL].titleWidth = 224.0;
    m_dialogData[DVR_FILELIST_DIALOG_DEL].titleHeight = 23.0;
	m_dialogData[DVR_FILELIST_DIALOG_DEL].pos[0] = (1 + radio) * 0.5 * window_width - 0.5 * m_dialogData[DVR_FILELIST_DIALOG_DEL].width;
	m_dialogData[DVR_FILELIST_DIALOG_DEL].pos[1] = 0.5 * (window_height - m_dialogData[DVR_FILELIST_DIALOG_DEL].height);

	SetHmiParams();
	
	return HMI_SUCCESS;
}

int CSVDvrFileListTab::Update(Hmi_Message_T & hmiMsg)
{
	static int currentFileNum = 0;
	int 	   fileNumCnt = 0;
    static int waitCnt = 0;
    static int currentThumbTab = 0;
	
	DVR_GRAPHIC_UIOBJ* fileListTabMsg = NULL;
	
	GUI_OBJ_THUMB_EDIT_INST* editInst = NULL;
	
	GUI_OBJ_THUMB_FRAME_INST* frameInst = NULL;

	GUI_OBJ_DIALOG_INST*	  dialogInst = NULL;

    GUI_OBJ_THUMB_PAGENUM_INST* thumbPagenumInst = NULL;
/*
DVR_GRAPHIC_UIOBJ thumb_gui_table[] =
{
	{ GUI_OBJ_ID_MAIN_MENU_TAB, "main_menu", 1, 1, GUI_OBJ_STATUS_TYPE_U32, GUI_MAIN_MENU_TAB_THUMB },
	{ GUI_OBJ_ID_THUMB_TAB, "thumb_tab", 1, 1, GUI_OBJ_STATUS_TYPE_U32, GUI_THUMB_TAB_LOOPENC },
	{ GUI_OBJ_ID_THUMB_EDIT, "thumb_edit_state", 1, 1, GUI_OBJ_STATUS_TYPE_U32, GUI_SWITCH_STATE_OFF },
	{ GUI_OBJ_ID_THUMB_EDIT_SEL_CHECKBOX, "thumb_edit_sel_chkbox", 1, 0, GUI_OBJ_STATUS_TYPE_POINTER, (unsigned int)&m_thumb_edit },
	{ GUI_OBJ_ID_THUMB_FRAME, "thumb_content", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER, (unsigned int)&m_thumb_frame },
	{ GUI_OBJ_ID_THUMB_CAPACITY, "thumb_capacity", 1, 1, GUI_OBJ_STATUS_TYPE_POINTER, (unsigned int)&m_capacity },
	{ GUI_OBJ_ID_DIALOG, "dialog", 1, 0, GUI_OBJ_STATUS_TYPE_POINTER, (unsigned int)&m_dialog },
	{ GUI_OBJ_ID_WARNING, "warning", 1, 0, GUI_OBJ_STATUS_TYPE_U32, GUI_WARNING_NONE },
};

*/
	if((DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable)
	{
		fileListTabMsg = (DVR_GRAPHIC_UIOBJ*) hmiMsg.dvrTabMsg.tabMsgTable;
		
		for(int i = 0; i < hmiMsg.dvrTabMsg.objNum; i++)
		{			
			switch(fileListTabMsg[i].Id)
			{
			case GUI_OBJ_ID_THUMB_TAB:
				if(GUI_OBJ_STATUS_TYPE_U32 == fileListTabMsg[i].status_type)
				{
					m_buttonVisibility[DVR_FILELIST_TAB_LR_TITLE_SELECTED] = 0;
					m_buttonVisibility[DVR_FILELIST_TAB_ES_TITLE_SELECTED] = 0;
					m_buttonVisibility[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED] = 0;
					
					if(fileListTabMsg[i].uStatus.ObjVal == GUI_THUMB_TAB_LOOPENC)
					{
						m_buttonVisibility[DVR_FILELIST_TAB_LR_TITLE_SELECTED] = 1;
					}
					else if(fileListTabMsg[i].uStatus.ObjVal == GUI_THUMB_TAB_EMERGENCY)
					{
						m_buttonVisibility[DVR_FILELIST_TAB_ES_TITLE_SELECTED] = 1;
					}
					else if(fileListTabMsg[i].uStatus.ObjVal == GUI_THUMB_TAB_PHOTO)
					{
						m_buttonVisibility[DVR_FILELIST_TAB_PICTURE_TITLE_SELECTED] = 1;
					}
                    
                    if(currentThumbTab != fileListTabMsg[i].uStatus.ObjVal)
                    {
                        currentThumbTab = fileListTabMsg[i].uStatus.ObjVal;
                        waitCnt = 0;
                    }
				}
				break;
			case GUI_OBJ_ID_THUMB_EDIT:
				if(GUI_OBJ_STATUS_TYPE_U32 == fileListTabMsg[i].status_type)
				{
                    if(fileListTabMsg[i].uStatus.ObjVal == GUI_THUMB_EDIT_STATE_OFF)
                    {
    					m_buttonStatus[DVR_FILELIST_TAB_EDIT_ICON] = BUTTON_OFF_IMAGE;
    					
    					for(int i = 0; i < NUM_THUMBNAIL_PER_PAGE; i++)
    					{							
    						m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SEL_BOX_1 + 2 * i] = 0;												
    						m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SEL_FLAG_1 + 2 * i] = 0;
    					}

    					m_buttonVisibility[DVR_FILELIST_TAB_EDIT_CANCEL] = 0;
    					m_buttonStatus[DVR_FILELIST_TAB_EDIT_CANCEL] = 0;
    					m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SAVE] = 0;
    					m_buttonStatus[DVR_FILELIST_TAB_EDIT_SAVE] = 0;
    					m_buttonVisibility[DVR_FILELIST_TAB_EDIT_DELETE] = 0;
    					m_buttonStatus[DVR_FILELIST_TAB_EDIT_DELETE] = 0;
    					m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SELECTED_ALL] = 0;
    					m_buttonStatus[DVR_FILELIST_TAB_EDIT_SELECTED_ALL] = 0;
    					m_buttonVisibility[DVR_FILELIST_TAB_EDIT_BKG] = 0;

    					editStatus = GUI_SWITCH_STATE_OFF;                    
                    }
                    else if(fileListTabMsg[i].uStatus.ObjVal < GUI_THUMB_EDIT_STATE_NUM)
                    {
                        m_buttonStatus[DVR_FILELIST_TAB_EDIT_ICON] = BUTTON_ON_IMAGE;
                        for(int i = 0; i < NUM_THUMBNAIL_PER_PAGE; i++)
                        {   
                            if(i < currentFileNum)
                            {
                                m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SEL_BOX_1 + 2 * i] = 1;
                            }
                            else
                            {
                                m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SEL_BOX_1 + 2 * i] = 0;
                            }
                            
                            m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SEL_FLAG_1 + 2 * i] = 0;
                        }
                        
                        m_buttonVisibility[DVR_FILELIST_TAB_EDIT_CANCEL] = 1;
                        m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SAVE] = 1;
                        m_buttonVisibility[DVR_FILELIST_TAB_EDIT_DELETE] = 1;
                        m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SELECTED_ALL] = 1;
                        m_buttonVisibility[DVR_FILELIST_TAB_EDIT_BKG] = 1;
                
                        editStatus = GUI_SWITCH_STATE_ON;
                    }
                    
                    if(fileListTabMsg[i].uStatus.ObjVal == GUI_THUMB_EDIT_STATE_NORMAL_ON)
                    {
                        if(m_buttonStatus[DVR_FILELIST_TAB_EDIT_SAVE] == 2)
                        {
                            m_buttonStatus[DVR_FILELIST_TAB_EDIT_SAVE] = 0;
                        }
                        else if(m_buttonStatus[DVR_FILELIST_TAB_EDIT_SAVE] == 0)
                        {
                            m_baseButton[DVR_FILELIST_TAB_EDIT_SAVE]->SetAnimationStyle(BUTTON_FLASH_HIGHLIGHT);
                        }
                    }
                    else if(fileListTabMsg[i].uStatus.ObjVal == GUI_THUMB_EDIT_STATE_EMERGENCY_ON
                        ||fileListTabMsg[i].uStatus.ObjVal == GUI_THUMB_EDIT_STATE_PHOTO_ON)
                    {
                        m_buttonStatus[DVR_FILELIST_TAB_EDIT_SAVE] = 2;
                        m_baseButton[DVR_FILELIST_TAB_EDIT_SAVE]->SetAnimationStyle(BUTTON_NOMAL);
                    }
				}
				break;
			case GUI_OBJ_ID_THUMB_EDIT_SEL_CHECKBOX:
								
				if(GUI_OBJ_STATUS_TYPE_POINTER == fileListTabMsg[i].status_type
					&& fileListTabMsg[i].uStatus.ptr)
				{
					editInst = (GUI_OBJ_THUMB_EDIT_INST*)fileListTabMsg[i].uStatus.ptr;

					if(IMAGE_GRID_LIST_ITEM_NUM != NUM_THUMBNAIL_PER_PAGE)
					{
						Log_Error("------The size of the file list isn't equal to the real nums of thumb!");
					}
					for(int i = 0; i < currentFileNum; i++)
					{	
						m_buttonVisibility[DVR_FILELIST_TAB_EDIT_SEL_FLAG_1 + 2 * i] = editInst->check_box[i] & fileListTabMsg[i].bShow;
					}
				}
				
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
			case GUI_OBJ_ID_THUMB_CAPACITY:

				
				
				break;
			case GUI_OBJ_ID_DIALOG:
				if(GUI_OBJ_STATUS_TYPE_POINTER == fileListTabMsg[i].status_type
					&& fileListTabMsg[i].uStatus.ptr)
				{
					dialogInst = (GUI_OBJ_DIALOG_INST*)fileListTabMsg[i].uStatus.ptr;
					m_dialogVisibility[dialogInst->subjectId] = fileListTabMsg[i].bShow;
//                    Log_Error("dialog type: %d, Id: %d, show: %d", dialogInst->type, dialogInst->subjectId, fileListTabMsg[i].bShow);
				}

				break;

			case GUI_OBJ_ID_WARNING:
				if(GUI_OBJ_STATUS_TYPE_U32 == fileListTabMsg[i].status_type)
				{
				}
				break;
            case GUI_OBJ_ID_THUMB_PAGE_NUM:
                if(GUI_OBJ_STATUS_TYPE_POINTER == fileListTabMsg[i].status_type
                    && fileListTabMsg[i].uStatus.ptr)
                {
                    thumbPagenumInst = (GUI_OBJ_THUMB_PAGENUM_INST*)fileListTabMsg[i].uStatus.ptr;
                    unsigned char curPage = thumbPagenumInst->nCurPage;
                    unsigned char totalPage = thumbPagenumInst->nTotalPage;
//                    Log_Error("curPage: %d, totalPage: %d", curPage, totalPage);
                    if(totalPage > 0)
                    {
                        sprintf(m_pageNumData.textContent[0],"%u / %u", curPage, totalPage);
                        m_pageNum->SetVisibility(1);
                        m_noFileText->SetVisibility(0);
                        waitCnt = 0;
                    }
                    else
                    {
                        waitCnt ++;
                        if(waitCnt < 50)
                        {
                            char* ptext = "Waiting..";
                            sprintf(m_noFileTextData.textContent[0],"%s", ptext);
                        }
                        else
                        {
                            waitCnt = 50;
                            char* ptext = "No File !";
                            sprintf(m_noFileTextData.textContent[0],"%s", ptext);                            
                        }
                        m_pageNum->SetVisibility(0);
                        m_noFileText->SetVisibility(1);
                    }     
                }
                break;
			default:
				break;
			}	
		}

	}

	RefreshHmi();
	return HMI_SUCCESS;
}
int CSVDvrFileListTab::RefreshHmi()
{
	for(int i = DVR_FILELIST_TAB_LOOP_REC_TITLE; i < DVR_FILELIST_TAB_ELEMEMT_NUM; i++)

	{
		m_baseButton[i]->SetShowIconNum(m_buttonStatus[i]);
		m_baseButton[i]->SetVisibility(m_buttonVisibility[i]);
		m_baseButton[i]->Update();
	}

	for(int i = DVR_FILELIST_DIALOG_DEL; i < DVR_FILELIST_DIALOG_NUM; i++)
	{
		m_dialog[i]->SetVisibility(m_dialogVisibility[i]);
	}

    m_pageNum->Update(m_pageNumData.textContent[0]);
    m_noFileText->Update(m_noFileTextData.textContent[0]);
    
	return HMI_SUCCESS;
}
int CSVDvrFileListTab::SetElementsVisibility(unsigned char pFlag)
{
	//memset(m_buttonVisibility, pFlag, DVR_FILELIST_TAB_ELEMEMT_NUM * sizeof(unsigned char));
    if(pFlag == 0)
    {
        m_pageNum->SetVisibility(0);
        m_noFileText->SetVisibility(0);
    }
    
	m_imageGridList->SetVisibility(pFlag);

	if(pFlag > 0)
	{
		for(int i = DVR_FILELIST_TAB_LOOP_REC_TITLE; i <= DVR_FILELIST_TAB_PICTURE_TITLE; i++)

		{
		
			m_buttonVisibility[i] = pFlag;
			m_baseButton[i]->SetVisibility(pFlag);
		}
		m_buttonVisibility[DVR_FILELIST_TAB_EDIT_ICON] = pFlag;
		m_baseButton[DVR_FILELIST_TAB_EDIT_ICON]->SetVisibility(pFlag);
		
		for(int i = DVR_FILELIST_TAB_SCROLL_BKG; i < DVR_FILELIST_TAB_ELEMEMT_NUM; i++)

		{
		
			m_buttonVisibility[i] = pFlag;
			m_baseButton[i]->SetVisibility(pFlag);
		}
	}
	else
	{
		for(int i = DVR_FILELIST_TAB_LOOP_REC_TITLE; i < DVR_FILELIST_TAB_ELEMEMT_NUM; i++)

		{		
			m_buttonVisibility[i] = pFlag;
			m_baseButton[i]->SetVisibility(pFlag);
		}
		for(int i = DVR_FILELIST_DIALOG_DEL; i < DVR_FILELIST_DIALOG_NUM; i++)
		{
			m_dialogVisibility[i] = pFlag;
			m_dialog[i]->SetVisibility(m_dialogVisibility[i]);
		}
	}

	return HMI_SUCCESS;
}
int CSVDvrFileListTab::ReturnHmiMsg(Hmi_Message_T* hmi_msg)
{
	return HMI_SUCCESS;
}
int CSVDvrFileListTab::DestroyHmiElems()
{
	return HMI_SUCCESS;
}

