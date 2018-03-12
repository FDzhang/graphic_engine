/*===========================================================================*\
 * FILE: HMIDialog.cpp
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

#include "HMIDialog.h"

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;
/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/



HMIDialog::HMIDialog(HmiDialogDataT* pDialogData,IUINode* uiNode)
{
	if(uiNode == NULL
		|| pDialogData == NULL)
	{
		return;
	}

	m_uiNode = uiNode;
	m_dialogData = new HmiDialogDataT;

	memcpy(m_dialogData, pDialogData, sizeof(HmiDialogDataT));

    float dialogIconPos[2];
    float dialogIconSize[2]; //0:width, 1:height
    float iconInterval = 10.0;

    if(m_dialogData->dialogType == DIALOG_NORMAL)
    {
        m_dialogMtlId = m_uiNode->CreateUIMaterial(Material_UI_Spirit, m_dialogData->iconFileName[DIALOG_CONFIRM_CANCEL_BACKGROUND],
            0.0, &m_dialogMtl);

        m_dialogId = m_uiNode->CreateSpirit(-1, InsertFlag_Default, m_dialogMtlId, 1.0, 
            m_dialogData->pos[0], m_dialogData->pos[1], 0, m_dialogData->width, m_dialogData->height);
        
        m_dialogVisibility = m_dialogData->showFlag;
        ISpirit *dialogLayer = m_uiNode->GetSpirit(m_dialogId);
        dialogLayer->SetEnable(m_dialogVisibility);

        
    /*      dialogIconSize[0] = 1.0/5.0 * m_dialogData->width;
        dialogIconSize[1] = 1.0/5.0 * m_dialogData->height;
        dialogIconPos[0] = m_dialogData->pos[0] + m_dialogData->width * 0.5 - dialogIconSize[0] * 0.5;
        dialogIconPos[1] = m_dialogData->pos[1] + m_dialogData->height - dialogIconSize[1] - 10.0;
        iconInterval += dialogIconSize[0];
    */

        m_dialogTitleData.pos[0] = m_dialogData->pos[0] + 0.5 * (m_dialogData->width - m_dialogData->titleWidth);
        m_dialogTitleData.pos[1] = m_dialogData->pos[1] + 0.5 * (2.0/3.0 * m_dialogData->height - m_dialogData->titleHeight);
        m_dialogTitleData.width =  m_dialogData->titleWidth;
        m_dialogTitleData.height =  m_dialogData->titleHeight;
        m_dialogTitleData.show_icon_num = 0;
        m_dialogTitleData.icon_type = STATIC_ICON;
        m_dialogTitleData.show_flag = 1;
        m_dialogTitleData.animationStyle = BUTTON_NOMAL;        
        m_dialogTitleData.icon_file_name[0] = new char[100];
        sprintf(m_dialogTitleData.icon_file_name[0],"%s",m_dialogData->iconFileName[DIALOG_TITLE_IMG]);

        dialogIconSize[0] = 100.0/348 * m_dialogData->width;
        dialogIconSize[1] = 38.0/183.0 * m_dialogData->height;
        dialogIconPos[0] = m_dialogData->pos[0] + m_dialogData->width * 0.5 - dialogIconSize[0] * 0.5;
        dialogIconPos[1] = m_dialogData->pos[1] + 2.0/3.0 * m_dialogData->height;

        m_dialogButtonData[DIALOG_CONFIRM - 1].pos[0] = dialogIconPos[0];
        m_dialogButtonData[DIALOG_CONFIRM - 1].pos[1] = dialogIconPos[1];
        m_dialogButtonData[DIALOG_CONFIRM - 1].width = dialogIconSize[0];
        m_dialogButtonData[DIALOG_CONFIRM - 1].height = dialogIconSize[1];
        m_dialogButtonData[DIALOG_CONFIRM - 1].show_icon_num = 0;
        m_dialogButtonData[DIALOG_CONFIRM - 1].icon_type = STATIC_ICON;
        m_dialogButtonData[DIALOG_CONFIRM - 1].show_flag = 1;
        m_dialogButtonData[DIALOG_CONFIRM - 1].animationStyle = BUTTON_FLASH_HIGHLIGHT;
        m_dialogButtonData[DIALOG_CONFIRM - 1].icon_file_name[0] = new char[100];
        sprintf(m_dialogButtonData[DIALOG_CONFIRM - 1].icon_file_name[0],"%s",m_dialogData->iconFileName[DIALOG_CONFIRM_NORMAL_IMG]);
        m_dialogButtonData[DIALOG_CONFIRM - 1].icon_file_name[1] = new char[100];
        sprintf(m_dialogButtonData[DIALOG_CONFIRM - 1].icon_file_name[1],"%s",m_dialogData->iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG]);

        m_dialogVisibility = 1;

        if(m_dialogData->trigger[DIALOG_CONFIRM])
        {
            m_dialogButtonData[DIALOG_CONFIRM - 1].trigger = m_dialogData->trigger[DIALOG_CONFIRM];
        }

        m_dialogTitle = new HMIButton(&m_dialogTitleData, m_uiNode);
        m_dialogTitle->SetVisibility(m_dialogVisibility);
        
        m_dialogButton[DIALOG_CONFIRM - 1] = new HMIButton(&m_dialogButtonData[DIALOG_CONFIRM - 1], m_uiNode);
        m_dialogButton[DIALOG_CONFIRM - 1]->SetVisibility(m_dialogVisibility);
        
    }
	else if(m_dialogData->dialogType == DIALOG_CONFIRM_CANCEL)
	{
		m_dialogMtlId = m_uiNode->CreateUIMaterial(Material_UI_Spirit, m_dialogData->iconFileName[DIALOG_CONFIRM_CANCEL_BACKGROUND],
			0.0, &m_dialogMtl);

		m_dialogId = m_uiNode->CreateSpirit(-1, InsertFlag_Default, m_dialogMtlId, 1.0, 
			m_dialogData->pos[0], m_dialogData->pos[1], 0, m_dialogData->width, m_dialogData->height);
		
		m_dialogVisibility = m_dialogData->showFlag;
		ISpirit *dialogLayer = m_uiNode->GetSpirit(m_dialogId);
		dialogLayer->SetEnable(m_dialogVisibility);
		
/*		dialogIconSize[0] = 1.0/5.0 * m_dialogData->width;
		dialogIconSize[1] = 1.0/5.0 * m_dialogData->height;
		dialogIconPos[0] = m_dialogData->pos[0] + m_dialogData->width * 0.5 - dialogIconSize[0] * 0.5;
		dialogIconPos[1] = m_dialogData->pos[1] + m_dialogData->height - dialogIconSize[1] - 10.0;
		iconInterval += dialogIconSize[0];
*/

        m_dialogTitleData.pos[0] = m_dialogData->pos[0] + 0.5 * (m_dialogData->width - m_dialogData->titleWidth);
        m_dialogTitleData.pos[1] = m_dialogData->pos[1] + 0.5 * (2.0/3.0 * m_dialogData->height - m_dialogData->titleHeight);
        m_dialogTitleData.width =  m_dialogData->titleWidth;
        m_dialogTitleData.height =  m_dialogData->titleHeight;
        m_dialogTitleData.show_icon_num = 0;
        m_dialogTitleData.icon_type = STATIC_ICON;
        m_dialogTitleData.show_flag = 1;
        m_dialogTitleData.animationStyle = BUTTON_NOMAL;        
		m_dialogTitleData.icon_file_name[0] = new char[100];
		sprintf(m_dialogTitleData.icon_file_name[0],"%s",m_dialogData->iconFileName[DIALOG_TITLE_IMG]);

        dialogIconSize[0] = 100.0/348 * m_dialogData->width;
		dialogIconSize[1] = 38.0/183.0 * m_dialogData->height;
		dialogIconPos[0] = m_dialogData->pos[0] + m_dialogData->width * 0.5 - dialogIconSize[0] - 24;
		dialogIconPos[1] = m_dialogData->pos[1] + 2.0/3.0 * m_dialogData->height;
		iconInterval += dialogIconSize[0];

		m_dialogButtonData[DIALOG_CONFIRM - 1].pos[0] = dialogIconPos[0];
		m_dialogButtonData[DIALOG_CONFIRM - 1].pos[1] = dialogIconPos[1];
		m_dialogButtonData[DIALOG_CONFIRM - 1].width = dialogIconSize[0];
		m_dialogButtonData[DIALOG_CONFIRM - 1].height = dialogIconSize[1];
		m_dialogButtonData[DIALOG_CONFIRM - 1].show_icon_num = 0;
		m_dialogButtonData[DIALOG_CONFIRM - 1].icon_type = STATIC_ICON;
		m_dialogButtonData[DIALOG_CONFIRM - 1].show_flag = 1;
		m_dialogButtonData[DIALOG_CONFIRM - 1].animationStyle = BUTTON_FLASH_HIGHLIGHT;
		m_dialogButtonData[DIALOG_CONFIRM - 1].icon_file_name[0] = new char[100];
		sprintf(m_dialogButtonData[DIALOG_CONFIRM - 1].icon_file_name[0],"%s",m_dialogData->iconFileName[DIALOG_CONFIRM_NORMAL_IMG]);
		m_dialogButtonData[DIALOG_CONFIRM - 1].icon_file_name[1] = new char[100];
		sprintf(m_dialogButtonData[DIALOG_CONFIRM - 1].icon_file_name[1],"%s",m_dialogData->iconFileName[DIALOG_CONFIRM_HIGHLIGHT_IMG]);

		m_dialogButtonData[DIALOG_CANCEL - 1].pos[0] = m_dialogData->pos[0] + m_dialogData->width * 0.5 + 24;
		m_dialogButtonData[DIALOG_CANCEL - 1].pos[1] = dialogIconPos[1];
		m_dialogButtonData[DIALOG_CANCEL - 1].width = dialogIconSize[0];
		m_dialogButtonData[DIALOG_CANCEL - 1].height = dialogIconSize[1];
		m_dialogButtonData[DIALOG_CANCEL - 1].show_icon_num = 0;
		m_dialogButtonData[DIALOG_CANCEL - 1].icon_type = STATIC_ICON;
		m_dialogButtonData[DIALOG_CANCEL - 1].show_flag = 1;
		m_dialogButtonData[DIALOG_CANCEL - 1].animationStyle = BUTTON_FLASH_HIGHLIGHT;
		m_dialogButtonData[DIALOG_CANCEL - 1].icon_file_name[0] = new char[100];
		sprintf(m_dialogButtonData[DIALOG_CANCEL - 1].icon_file_name[0],"%s",m_dialogData->iconFileName[DIALOG_CANCEL_NORMAL_IMG]);
		m_dialogButtonData[DIALOG_CANCEL - 1].icon_file_name[1] = new char[100];
		sprintf(m_dialogButtonData[DIALOG_CANCEL - 1].icon_file_name[1],"%s",m_dialogData->iconFileName[DIALOG_CANCEL_HIGHLIGHT_IMG]);

		m_dialogVisibility = 1;

		if(m_dialogData->trigger[DIALOG_CONFIRM])
		{
			m_dialogButtonData[DIALOG_CONFIRM - 1].trigger = m_dialogData->trigger[DIALOG_CONFIRM];

		}
		if(m_dialogData->trigger[DIALOG_CANCEL])
		{
			m_dialogButtonData[DIALOG_CANCEL - 1].trigger = m_dialogData->trigger[DIALOG_CANCEL];

		}
		if(m_dialogData->trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND])
		{
			SetOnClickDelegate(m_dialogData->trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND]);
		}

        m_dialogTitle = new HMIButton(&m_dialogTitleData, m_uiNode);
        m_dialogTitle->SetVisibility(m_dialogVisibility);
        
		m_dialogButton[DIALOG_CONFIRM - 1] = new HMIButton(&m_dialogButtonData[DIALOG_CONFIRM - 1], m_uiNode);
		m_dialogButton[DIALOG_CONFIRM - 1]->SetVisibility(m_dialogVisibility);
		m_dialogButton[DIALOG_CANCEL - 1] = new HMIButton(&m_dialogButtonData[DIALOG_CANCEL - 1], m_uiNode);
		m_dialogButton[DIALOG_CANCEL - 1]->SetVisibility(m_dialogVisibility);

	}


}
HMIDialog::~HMIDialog()
{
    ISpirit* DialogLayer = m_uiNode->GetSpirit(m_dialogId);
	if(DialogLayer && m_dialogMtl)
	{
    	DialogLayer->Release();
		m_uiNode->ReleaseMaterial(m_dialogMtlId);
	}
    SAFE_DELETE(m_dialogMtl);    
    SAFE_DELETE(m_dialogTitle);   
    for(int i = DIALOG_CONFIRM; i < DIALOG_CONFIRM_CANCEL_ELEMENT_NUM; i++)
    {
        SAFE_DELETE(m_dialogButton[i - 1]);
    }
    SAFE_DELETE(m_dialogMtl);   
}
int HMIDialog::Init()
{
	return HMI_DIALOG_NORMAL;
}
int HMIDialog::Update()
{
	return HMI_DIALOG_NORMAL;
}

int HMIDialog::SetVisibility(unsigned char pFlag)
{
	if(pFlag > 0)
	{
		pFlag = 1;
	}
	m_dialogVisibility = pFlag;

	ISpirit *dialogLayer = m_uiNode->GetSpirit(m_dialogId);
	dialogLayer->SetEnable(m_dialogVisibility);

    m_dialogTitle->SetVisibility(m_dialogVisibility);	

    if(m_dialogData->dialogType == DIALOG_NORMAL)
    {
        m_dialogButton[DIALOG_CONFIRM - 1]->SetVisibility(m_dialogVisibility);
    }
	else if(m_dialogData->dialogType == DIALOG_CONFIRM_CANCEL)
	{
		m_dialogButton[DIALOG_CONFIRM - 1]->SetVisibility(m_dialogVisibility);
		m_dialogButton[DIALOG_CANCEL - 1]->SetVisibility(m_dialogVisibility);
	}
	return HMI_DIALOG_NORMAL;
}
Boolean HMIDialog::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	if (type == TouchEvent_Down) {

		if(m_dialogData->dialogType == DIALOG_CONFIRM_CANCEL)
		{
			if (m_trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND]) 
				m_trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND]->OnPress(layerId);
		}
	}
	else if (type == TouchEvent_Up) {
		if(m_dialogData->dialogType == DIALOG_CONFIRM_CANCEL)
		{
			if (m_trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND]) 
				m_trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND]->OnRelease(layerId, true);
		}
	}

	return TRUE;
}

Void HMIDialog::SetOnClickDelegate(IActionTrigger* trigger)
{
	ISpirit *dialogLayer = m_uiNode->GetSpirit(m_dialogId);
	if (dialogLayer) dialogLayer->SetEventResponder(this);

	m_trigger[DIALOG_CONFIRM_CANCEL_BACKGROUND] = trigger;
}
String HMIDialog::GetName()
{
	return m_name;
}
Void HMIDialog::SetName(String name)
{
	if (!m_name) {m_name = new CHAR[MaxNameLen];
	}
	if (!m_name) return;
	strcpy(m_name, name);
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the HMIDialog class.
\*===========================================================================*/