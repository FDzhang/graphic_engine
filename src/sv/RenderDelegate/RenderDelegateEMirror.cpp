/*===========================================================================*\
 * FILE: template.c
 *===========================================================================
 * Copyright 2008 O-Film Technologies, Inc., All Rights Reserved.
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
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"	
#include "../../XrCore/XrSrc/XrCore/CDeviceManager.h"	
#include "../videoloader.h"
#include "../fileloader.h"
#include "../bev_config.h"
#include "../AVMData.h"
#include "RenderDelegateEMirror.h"

/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/
extern CDeviceManager *XRDM;

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/
	
 struct SV_EMIRROR_PARAM_CB {
	XRMat4 myPMVMatrix;
	XRMat4 uvPMVMatrix; 
};


/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * External Object Definitions
\*===========================================================================*/
extern CRenderContext* g_pXrRenderContext;

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/


/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Internal Function Definitions
\*===========================================================================*/




Int32 RenderDelegateEMirror::OnRender(
	/* [in] */ class IMaterial* pMtl,
	/* [in] */ const XRMat4* pModelMatrix,
	/* [in] */ const XRMat4* pViewMatrix,
	/* [in] */ const XRMat4* pProjMatrix,
	/* [in] */ class CLight* pLight,
	/* [in] */ class IObject* pIObject)
{
	CShaderObject* pShader;
	CUniformBlock* pUB;
	CRenderState* pRS;
	CVertexLayout* pLayout;
	static int cnt = 0;
	float luminance[3] = {1.0,1.0,1.0};
	int Index;
	int i;	
	XRMat4 tempRotate = XRMat4::Scale(-1.0,1.0,1.0);
	float yuv_temp[24];
	float yuv_ratio[24];	
	float pos_select[3];
	float pos_gate[2];




	pMtl->GetEffect()->GetEffectParam(&pShader, &pUB, &pRS, &pLayout);

	char id = pIObject->GetName()[0];
	XRMat4 mModel = XRMat4::Scale(1.0f, 1.0f, 1.0f);
	int chn;
	switch (id) {
		case '0':
			
			chn = left_camera_index;			
			pRS->Set(XR_CULLMODE_FRONT| m_front_face_config| XR_DEPTHTEST_ENABLE | XR_DEPTHTEST_LT| XR_DEPTHTEST_LT);
		break;				
		case '1':
			chn = rear_camera_index;			
			pRS->Set(XR_CULLMODE_FRONT | m_front_face_config| XR_DEPTHTEST_ENABLE | XR_DEPTHTEST_LT| XR_DEPTHTEST_LT|XR_BLEND_DEFAULT);

			break;
		case '2':
			chn = right_camera_index;			
			pRS->Set(XR_CULLMODE_FRONT | m_front_face_config| XR_DEPTHTEST_ENABLE | XR_DEPTHTEST_LT| XR_DEPTHTEST_LT);

			break;
		case '3':
			chn = m_chanleId;			
			pRS->Set(XR_CULLMODE_FRONT | m_front_face_config| XR_DEPTHTEST_ENABLE | XR_DEPTHTEST_LT| XR_DEPTHTEST_LT);

			break;			
		
	}
	
	String ModelName = pIObject->GetName();

	SV_EMIRROR_PARAM_CB sv_param;

	AVMData::GetInstance()->m_cam_source->UseCameraTexture(chn);
	AVMData::GetInstance()->m_cam_source->UseCameraMaskTexture(chn);		
	

	 XRMat4 *uvTransform;
	 XRMat4 *modeltransform;
	
	AVMData::GetInstance()->m_exParam->GetModelTransform(&modeltransform,chn);

				
		mModel = (*pModelMatrix);
		mModel = m_ModelFlipMatrix*mModel;
		mModel = (*pViewMatrix)*mModel;
		sv_param.myPMVMatrix = (*pProjMatrix)*mModel;
		sv_param.uvPMVMatrix = m_ModelFlipMatrix;
	

	g_pXrRenderContext->UpdateUniformBlock(pUB, &sv_param);
	g_pXrRenderContext->VSSetUniformBlock(0, pUB);
	g_pXrRenderContext->PSSetUniformBlock(0, pUB);

	return 0;
}

Void RenderDelegateEMirror::ProcessModel(INode* mdl, String modelName)
{
	IMesh* mesh=0;
	Float32* pData;
	Float32 maxy=0.0f,miny=0.0f;
	Int32 count, i,chanelID,pos=0;
	if(modelName !=NULL)
	mdl->SetName(modelName);
	mdl->GetMesh(&mesh);
	mesh->LockData(&pData, 0, &count);
	switch(*modelName)
	{
		case '0':
		case '1':		
		case '2':
		case '3':
			chanelID = (*modelName)-48;
			m_pNode[chanelID]=mdl;

		break;	
		case '4':
		case '5':
			chanelID = (*modelName)-50;
			
			m_pNode[chanelID]=mdl;
		break;
		case '6':
		case '7':
			pos = (*modelName)-50;	   //pos for model
			chanelID = (*modelName)-52;  //front/rear chanle
			
			m_pNode[pos]=mdl;
		break;

			
	}
	#if 0
	for (i=0;i<count;i++) {
		pData[8*i+3] = pData[8*i+0];
		pData[8*i+4] = pData[8*i+1];
		pData[8*i+5] = pData[8*i+2];
		//pData[8*i+6] = 0.2;

		if (maxy < pData[8*i+1]) maxy = pData[8*i+1];
		if (miny > pData[8*i+1]) miny = pData[8*i+1];
		AVMData::GetInstance()->CalcUVTextureSV(&pData[8*i+0],&pData[8*i+3], chanelID);
	}
	#endif
	
	mesh->UnLockData();
}
void RenderDelegateEMirror::UpdateExParamCalibRslt(float *pose)			
{

	for(int i =0;i<4;i++)
	{
		m_update_flag[i] = 1;
	}
}

void RenderDelegateEMirror::SetMirrorFlipEnable(unsigned char flag)			
{
	if(flag == 1)
	{
		m_front_face_config = XR_FRONTFACE_CW;
		m_ModelFlipMatrix = XRMat4::Scale(-1.0,1.0,1.0);
	}
	else
	{
		m_front_face_config = XR_FRONTFACE_CCW;
		
		m_ModelFlipMatrix = XRMat4::Scale(1.0,1.0,1.0);
	}
	


}



Void RenderDelegateEMirror::Init(void)
{
	int i;
		m_front_face_config = XR_FRONTFACE_CCW;
		
		m_ModelFlipMatrix = XRMat4::Scale(1.0,1.0,1.0);  
	for(i=0;i<4;i++)
	{

			m_update_flag[i] = 0;

	}

	
}

void RenderDelegateEMirror::SetChanleId(int camera_index)
{
    m_chanleId = camera_index;	
}



/*===========================================================================*\
 * External Function Definitions
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------

\*===========================================================================*/

