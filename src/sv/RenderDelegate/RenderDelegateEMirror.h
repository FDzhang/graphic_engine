#ifndef __RENDER_DELEGATE_EMIRROR_H__
#define __RENDER_DELEGATE_EMIRROR_H__

/*===========================================================================*\
 * FILE: example.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *    This file is used for all the input data for all AVM moudules, including
 *    calib data,CAN data ,and so on.
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
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"	


/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/
class RenderDelegateEMirror : public IRenderDelegate
{ 
public:
	RenderDelegateEMirror() {

	}
	virtual ~RenderDelegateEMirror()
	{

	}
	virtual Int32 OnRender(
		/* [in] */ class IMaterial* pMtl,
		/* [in] */ const XRMat4* pModelMatrix,
		/* [in] */ const XRMat4* pViewMatrix,
		/* [in] */ const XRMat4* pProjMatrix,
		/* [in] */ class CLight* pLight,
		/* [in] */ class IObject* pIObject);
	
	virtual Void ProcessModel(INode* mdl, String modelName);
	void UpdateExParamCalibRslt(float *pose);
	
	void SetMirrorFlipEnable(unsigned char flag);
	void SetChanleId(int camera_index);



	Void Init(void);

	INode*	m_pNode[6];
	unsigned char m_update_flag[4];
	XRMat4 m_ModelFlipMatrix;
	unsigned char m_front_face_config;
	int m_chanleId;
	
};

/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------

\*===========================================================================*/


#endif //#ifndef __GL_SV_DEMO_H__
