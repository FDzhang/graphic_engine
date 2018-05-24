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

#ifndef _HMI_LICENSE_H_
#define _HMI_LICENSE_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../DataStruct.h"


typedef enum HmiLicenseErrorCodeTag
{
	LICENSE_TEXT_NORMAL,
	HMI_LICENSE_INIT_FAILED,
	LICENSE_TEXT_TEXTLAYER_INIT_ERROR,
	LICENSE_TEXT_ERROR_CODE_NUM,
}
HmiLicenseErrorCodeT;

typedef enum HmiLicenseTypeTag
{
	LICENSE_NORMAL = 0,
	LICENSE_TYPE_NUM,

}
HmiLicenseTypeT;

typedef struct HmiLicenseDataTag
{
	float pos[3];
	float size[2];
	float font_size;
	unsigned char visibilityStatus;
	float textColor[3];
	//char *textContent[MAX_TEXT_LINE_NUM];
	char* fontTypeMtlName;
	
	MaterialType licenseMaterialType;
	//char* licenseMtlName;

	ISceneNode*    bindNode;
}
HMILicenseDataT;

class HMILicense : public IEventResponder
{
public:
	HMILicense(HMILicenseDataT* pLiscenseData);
	virtual ~HMILicense();
	virtual  int Init();
	virtual int Update();
	int GetTextWH(
	/* [out] */ Float32* width,
	/* [out] */ Float32* height);
	int GetTextTextureId();
	int SetVisibility(unsigned char pFlag);
	int SetFontSize(float pSize);
	int SetTextColor(float pR, float pG, float pB);
	int SetChineseText(unsigned char pTextId, unsigned char pTextLayerIndex = 0);
	int SetNumText(char* pText);
	int SetBackgroundColor(float pR, float pG, float pB, float pOpacity);
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

	HMILicenseDataT* m_licenseData;
	
	int m_textLayerId;
	ITextLayer* m_textLayer;
	int m_textMtlId;

	int m_numTextLayerId;
	ITextLayer* m_numTextLayer;
	int m_numTextMtlId;

	int m_uiRenderTargetId;
	IRenderTarget*	m_uiRenderTarget;

	int m_uiNodeId;
	IUINode* m_uiNode;
	IMaterial* m_textMtl;
	IMaterial* m_numTextMtl;


	unsigned char m_textVisibility;

	IActionTrigger*	m_trigger;
	String          m_name;
};

#endif // _HMI_LICENSE_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  05/07/18   Jensen Wang   Create the HMILicense class.
\*===========================================================================*/