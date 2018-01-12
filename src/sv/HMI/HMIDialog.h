/*===========================================================================*\
 * FILE: HMIDialog.h
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

#ifndef _HMI_DIALOG_H_
#define _HMI_DIALOG_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "HMIButton.h"
#include "../DataStruct.h"

typedef enum HmiNormalDialogElementTag
{
	DIALOG_NORAML_BACKGROUND = 0,
	DIALOG_NORMAL_ELEMENT_NUM,
}
HmiNormalDialogElementT;
typedef enum HmiConfirmCancelDialogElementTag
{
	DIALOG_CONFIRM_CANCEL_BACKGROUND = 0,
	DIALOG_CONFIRM,
	DIALOG_CANCEL,
	DIALOG_CONFIRM_CANCEL_ELEMENT_NUM,
}
HmiConfirmCancelDialogElementT;
typedef enum HmiConfirmCancelDialogImageTag
{
	DIALOG_BACKGROUND_IMG = 0,
    DIALOG_TITLE_IMG,
	DIALOG_CONFIRM_NORMAL_IMG,
	DIALOG_CONFIRM_HIGHLIGHT_IMG,
	DIALOG_CANCEL_NORMAL_IMG,
	DIALOG_CANCEL_HIGHLIGHT_IMG,
	DIALOG_IMAGE_NUM,
}
HmiConfirmCancelDialogImageT;
typedef enum HmiDialogTypeTag
{
	DIALOG_NORMAL = 0,
	DIALOG_CONFIRM_CANCEL,
	DIALOG_TYPE_NUM,
}
HmiDialogTypeT;

typedef enum HmiDialogErrorCodeTag
{
	HMI_DIALOG_NORMAL = 0,
	HMI_DIALOG_ERROR_CODE_NUM,
}
HmiDialogErrorCodeT;

typedef struct HmiDialogDataTag
{
    float pos[2];
    float width;
    float height;
    float titleWidth;
    float titleHeight;

	HmiDialogTypeT dialogType; 
    bool showFlag;
    char *iconFileName[DIALOG_IMAGE_NUM];

	IActionTrigger*    trigger[DIALOG_CONFIRM_CANCEL_ELEMENT_NUM];
}
HmiDialogDataT;

class HMIDialog : public IEventResponder
{
public:
	HMIDialog(HmiDialogDataT* pDialogData, IUINode* uiNode);
	virtual ~HMIDialog();
	virtual  int Init();
	virtual int Update();
	int SetVisibility(unsigned char pFlag);

private:
	virtual Boolean OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type);

	virtual String GetName();
	virtual Void SetName(
		/* [in] */ String name); 

	virtual Void* GetRealType() { return (Void*)this; }

	void SetOnClickDelegate(IActionTrigger* trigger);
private:
	int m_dialogId;

	IMaterial* m_dialogMtl;
	int m_dialogMtlId;

	unsigned char m_dialogVisibility;
	unsigned char m_confirmIconVisibility;
	unsigned char m_cancelIconVisibility;

	HmiDialogDataT*	m_dialogData;

	Hmi_Button_Data_T m_dialogButtonData[DIALOG_CONFIRM_CANCEL_ELEMENT_NUM - 1];
	HMIButton* m_dialogButton[DIALOG_CONFIRM_CANCEL_ELEMENT_NUM - 1];

    Hmi_Button_Data_T m_dialogTitleData;
    HMIButton* m_dialogTitle;
    
	IUINode*			m_uiNode;

	IActionTrigger*	m_trigger[DIALOG_CONFIRM_CANCEL_ELEMENT_NUM];
	String             m_name;
};

#endif // _HMI_DIALOG_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the HMIDialog class.
\*===========================================================================*/