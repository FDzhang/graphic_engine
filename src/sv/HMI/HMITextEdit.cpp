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

#include "HMITextEdit.h"

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


HmiTextEdit::HmiTextEdit(HmiTextEditDataT* pTextEditData,IUINode* uiNode):m_textVisibility(0)
{
	if(uiNode == NULL
		|| pTextEditData == NULL)
	{
		return;
	}
	m_uiNode = uiNode;
	m_textEditData = new HmiTextEditDataT;
	memcpy(m_textEditData, pTextEditData, sizeof(HmiTextEditDataT));
	m_textMtlId = m_uiNode->CreateUIFontMaterial(m_textEditData->fontTypeMtlName, &m_textMtl);
	m_textLayerId = m_uiNode->CreateTextLayer(-1, InsertFlag_Default, m_textMtlId, 1.0, m_textEditData->pos[0], m_textEditData->pos[1], &m_textLayer, m_textEditData->width,m_textEditData->font_size);
}
HmiTextEdit::~HmiTextEdit()
{
}
int HmiTextEdit::Init()
{
	return TEXT_EDIT_NORMAL;
}
int HmiTextEdit::Update(char* pText)
{
	if(m_textLayer == NULL)
	{
		return TEXT_EDIT_TEXTLAYER_INIT_ERROR;
	}

	m_textLayer->SetEnable(m_textVisibility);

	if(m_textVisibility == 1)
	{
		m_textLayer->SetText(pText);
        m_textLayer->SetColor(m_textEditData->textColor[0], m_textEditData->textColor[1], m_textEditData->textColor[2]);

	}
	else if(m_textVisibility == 0)
	{

	}
	return TEXT_EDIT_NORMAL;
}

int HmiTextEdit::SetVisibility(unsigned char pFlag)
{
	if(pFlag > 0)
	{
		pFlag = 1;
	}
	m_textVisibility = pFlag;
		
	if(m_textLayer == NULL)
	{
		return TEXT_EDIT_TEXTLAYER_INIT_ERROR;
	}
	m_textLayer->SetEnable(pFlag);
	return TEXT_EDIT_NORMAL;
}

int HmiTextEdit::SetTextColor(float pR, float pG, float pB)
{
	m_textEditData->textColor[0] = pR;
	m_textEditData->textColor[1] = pG;
	m_textEditData->textColor[2] = pB;

	if(m_textLayer == NULL)
	{
		return TEXT_EDIT_TEXTLAYER_INIT_ERROR;
	}

	m_textLayer->SetColor(m_textEditData->textColor[0], m_textEditData->textColor[1], m_textEditData->textColor[2]);
	
	return TEXT_EDIT_NORMAL;
}

Boolean HmiTextEdit::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	if (type == TouchEvent_Down) {
		if (m_trigger) m_trigger->OnPress(layerId);
	}
	else if (type == TouchEvent_Up) {
		if (m_trigger) m_trigger->OnRelease(layerId, true);
	}
	return TRUE;
}

Void HmiTextEdit::SetOnClickDelegate(IActionTrigger* trigger)
{
	if (m_textLayer) m_textLayer->SetEventResponder(this);
	m_trigger = trigger;
}
String HmiTextEdit::GetName()
{
	return m_name;
}

Void HmiTextEdit::SetName(String name)
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
 *  12/16/17   Jensen Wang   Create the HMITextEdit class.
\*===========================================================================*/