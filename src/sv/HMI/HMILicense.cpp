/*===========================================================================*\
 * FILE: HMILicense.h
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

#include "HMILicense.h"

/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/

const static int LICENSE_RENDER_BUFFER_WIDTH = 225;
const static int LICENSE_RENDER_BUFFER_HEIGHT = 100;

HMILicense::HMILicense(HMILicenseDataT* pLiscenseData)
{
	if(pLiscenseData == NULL)
	{
		return;
	}

	IXrCore* xrCore = 0;
	xrCore = GetXrCoreInterface();
	IDeviceManager* rm = 0;
	if(xrCore)
	{
		xrCore->GetDeviceManager(&rm);
	}
	if(xrCore == NULL
		|| rm == NULL)
	{
		return ;
	}
	m_uiRenderTargetId = rm->CreateRenderTarget(LICENSE_RENDER_BUFFER_WIDTH, LICENSE_RENDER_BUFFER_HEIGHT, XR_R8G8B8A8, XR_NONE, &m_uiRenderTarget);
	m_uiNodeId = xrCore->CreateRenderNodeUI(RenderNodeType_UI2D, m_uiRenderTargetId, &m_uiNode);

	m_licenseData = new HMILicenseDataT;
	memcpy(m_licenseData, pLiscenseData, sizeof(HMILicenseDataT));
	m_textMtlId = m_uiNode->CreateUIChineseFontMaterial(m_licenseData->fontTypeMtlName, &m_textMtl);
	m_textLayerId = m_uiNode->CreateChineseTextLayer(-1, InsertFlag_Default, m_textMtlId, 1.0, m_licenseData->pos[0], m_licenseData->pos[1], &m_textLayer, m_licenseData->size[0],m_licenseData->font_size);
	
	float offset_y = 0.0;
	float offset_x = 65.0;
	m_numTextMtlId = m_uiNode->CreateUIFontMaterial(XR_RES"SEASANS.TTF", &m_numTextMtl);
	m_numTextLayerId = m_uiNode->CreateTextLayer(-1, InsertFlag_Default, m_numTextMtlId, 1.0, m_licenseData->pos[0] + offset_x, m_licenseData->pos[1] + offset_y, &m_numTextLayer, m_licenseData->size[0] + 70.0,m_licenseData->font_size);


	int index=0;
	m_textLayer->SetText(index);
	m_textLayer->SetFontSize(m_licenseData->font_size);

	m_numTextLayer->SetText("A-F0236");
    m_numTextLayer->SetFontSize(m_licenseData->font_size + 4);


	m_uiNode->SetClear(true,false);
	m_uiNode->SetClearColor(0.0,0.0,0.0,0.0);

	m_textVisibility = m_licenseData->visibilityStatus;

}
HMILicense::~HMILicense()
{
}
int HMILicense::GetTextTextureId()
{
	return m_uiRenderTarget->GetTextureId();
}
int HMILicense::Init()
{
	return LICENSE_TEXT_NORMAL;
}
int HMILicense::Update()
{
	if(m_textLayer == NULL)
	{
		return HMI_LICENSE_INIT_FAILED;
	}

	m_textLayer->SetEnable(m_textVisibility);

/*	if(m_textVisibility == 1)
	{
		m_textLayer->SetText(pText);
        m_textLayer->SetColor(m_licenseData->textColor[0], m_licenseData->textColor[1], m_licenseData->textColor[2]);

	}
*/

	return LICENSE_TEXT_NORMAL;
}
int HMILicense::SetChineseText(unsigned char pTextId, unsigned char pTextLayerIndex)
{
	m_textLayer->SetText(pTextId);
	return LICENSE_TEXT_NORMAL;
}

int HMILicense::SetNumText(char* pText)
{
	m_numTextLayer->SetText(pText);
	return LICENSE_TEXT_NORMAL;
}

int HMILicense::GetTextWH(
	/* [out] */ Float32* width,
	/* [out] */ Float32* height)
{
	*width = m_textLayer->GetWidth();
	*height = m_textLayer->GetHeight();
	//m_textLayer->GetTextWH(width, height);
	return LICENSE_TEXT_NORMAL;
}
int HMILicense::SetVisibility(unsigned char pFlag)
{
	if(pFlag > 0)
	{
		pFlag = 1;
	}
	m_textVisibility = pFlag;
		
	if(m_textLayer == NULL)
	{
		return HMI_LICENSE_INIT_FAILED;
	}
	m_textLayer->SetEnable(pFlag);
	return LICENSE_TEXT_NORMAL;
}

int HMILicense::SetTextColor(float pR, float pG, float pB)
{
	m_licenseData->textColor[0] = pR;
	m_licenseData->textColor[1] = pG;
	m_licenseData->textColor[2] = pB;

	if(m_textLayer == NULL)
	{
		return HMI_LICENSE_INIT_FAILED;
	}

	m_textLayer->SetColor(m_licenseData->textColor[0], m_licenseData->textColor[1], m_licenseData->textColor[2]);
	
	return LICENSE_TEXT_NORMAL;
}
int HMILicense::SetFontSize(float pSize)
{
	m_textLayer->SetFontSize(pSize);

	return LICENSE_TEXT_NORMAL;
}
int HMILicense::SetBackgroundColor(float pR, float pG, float pB, float pOpacity)
{
	m_uiNode->SetClear(true,false);
	m_uiNode->SetClearColor(pR,pG,pB,pOpacity);

	return LICENSE_TEXT_NORMAL;
}
Boolean HMILicense::OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type)
{
	/*if (type == TouchEvent_MOVE) {
		if (m_trigger) m_trigger->OnMove(layerId);
	}*/
	if (type == TouchEvent_Down) {
		if (m_trigger) m_trigger->OnPress(layerId);
	}
	else if (type == TouchEvent_Up) {
		if (m_trigger) m_trigger->OnRelease(layerId, true);
	}
	return TRUE;
}

Void HMILicense::SetOnClickDelegate(IActionTrigger* trigger)
{
	if (m_textLayer) m_textLayer->SetEventResponder(this);
	m_trigger = trigger;
}
String HMILicense::GetName()
{
	return m_name;
}

Void HMILicense::SetName(String name)
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
 *  12/16/17   Jensen Wang   Create the HmiLicense class.
\*===========================================================================*/