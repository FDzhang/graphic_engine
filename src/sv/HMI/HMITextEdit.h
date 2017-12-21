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

#ifndef _HMI_TEXT_EDIT_H_
#define _HMI_TEXT_EDIT_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../DataStruct.h"

static const int MAX_TEXT_LINE_NUM = 20;

typedef enum HmiTextEditErrorCodeTag
{
	TEXT_EDIT_NORMAL,
	TEXT_EDIT_TEXTLAYER_INIT_ERROR,
	TEXT_EDIT_ERROR_CODE_NUM,
}
HmiTextEditErrorCodeTag;

typedef struct HmiTextEditDataTag
{
	float pos[2];
	float width;
	float font_size;
	int line_num;
	unsigned char visibilityStatus;
	float textColor[3];
	char *textContent[MAX_TEXT_LINE_NUM];
	char* fontTypeMtlName;
	int textEditId;
	int targetIndex;
	InsertFlag insertFlag;
	IActionTrigger*    trigger;
}
HmiTextEditDataT;

class HmiTextEdit : public IEventResponder
{
public:
	HmiTextEdit(HmiTextEditDataT* pTextEditData,IUINode* uiNode);
	virtual ~HmiTextEdit();
	virtual  int Init();
	virtual int Update(char* pText);
	int SetVisibility(unsigned char pFlag);
	int SetTextColor(float pR, float pG, float pB);
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

	HmiTextEditDataT* m_textEditData;
	
	int m_textLayerId;
	ITextLayer* m_textLayer;
	int m_textMtlId;
	IUINode* m_uiNode;
	IMaterial* m_textMtl;

	unsigned char m_textVisibility;

	 IActionTrigger*	m_trigger;
	 String             m_name;
};

#endif // _HMI_TEXT_EDIT_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  12/16/17   Jensen Wang   Create the HMITextEdit class.
\*===========================================================================*/