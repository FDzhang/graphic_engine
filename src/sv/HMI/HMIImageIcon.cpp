/*===========================================================================*\
 * FILE: HMICustomImageIcon.c
 *===========================================================================
 * Copyright 2015 O-Film Technologies, Inc., All Rights Reserved.
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
 *     TODO: Update list of other applicable standards
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 *
\*===========================================================================*/

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "HMIImageIcon.h"
#include "../AVMData.h"

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;

HMICustomImageIcon::HMICustomImageIcon(HMICustomImageIconDataT* pImageIconData):m_customImageIconVisibility(1)
{
	if(pImageIconData == NULL
		|| pImageIconData->renderNode == NULL)
	{
		return;
	}
	XRVertexLayout  data_format;

	m_customImageIconData = new HMICustomImageIconDataT;
	memcpy(m_customImageIconData, pImageIconData, sizeof(HMICustomImageIconDataT));
	m_mtlId = m_customImageIconData->renderNode->CreateMaterial(Material_Rigid_Texture, &m_mtl);
	m_mtl->SetDiffuseMap(m_customImageIconData->imageName[0]);

	m_meshId = m_customImageIconData->renderNode->CreateMesh(ModelType_Plane_Dynamic,2, 2 ,0, "custom_image_icon", &m_mesh);
	m_modelNodeId = m_customImageIconData->renderNode->CreateModel(0, m_mtlId, -1, InsertFlag_Default,0,0,0, 1.0, &m_modelNode);
	m_modelNode->SetMesh(m_meshId);

	m_mesh->LockData(&m_customVertex, &data_format, &m_vertexCount); 

	memcpy(m_customVertex, m_customImageIconData->customVertexBuffer, sizeof(m_customImageIconData->customVertexBuffer));

	m_mesh->UnLockData();

}

HMICustomImageIcon::~HMICustomImageIcon()
{
	m_customImageIconData->renderNode->ReleaseModel(m_modelNodeId);
	m_customImageIconData->renderNode->ReleaseMaterial(m_mtlId);
	m_customImageIconData->renderNode->ReleaseMesh(m_meshId);

	delete m_customImageIconData;
}
int HMICustomImageIcon::Update(float* pVertexBuffer, unsigned char pUpdateStatus)
{
	if(pVertexBuffer == NULL)
	{
		return CI_UPDATE_PARAMS_NULL;
	}

	if(pUpdateStatus == 1)
	{
		memcpy(m_customVertex, pVertexBuffer, sizeof(m_customImageIconData->customVertexBuffer));
	
		m_mesh->UnLockData();
	}

	m_modelNode->SetEnable(m_customImageIconVisibility);
	
	return CI_NORMAL;
}

int HMICustomImageIcon::SetVisibility(unsigned char flag)
{
	if(flag > 1)
	{
		flag = 1;
	}
	else if(flag < 0)
	{
		flag = 0;
	}

	m_customImageIconVisibility = flag;

	return CI_NORMAL;
}

HMIRawDataImageIcon::HMIRawDataImageIcon(HMIRawDataImageIconDataT* pRawDataImageIconData):m_rawDataImageIconVisibility(1)
{
	if(pRawDataImageIconData == NULL
		|| pRawDataImageIconData->imageData == NULL)
	{
		return;
	}
	m_rawDataImageIconData = new HMIRawDataImageIconDataT;
	memcpy(m_rawDataImageIconData, pRawDataImageIconData, sizeof(HMIRawDataImageIconDataT));
	
	m_textureId = rm->CreateTexture(m_rawDataImageIconData->imageData, m_rawDataImageIconData->imageWidth, m_rawDataImageIconData->imageHeight, XR_R8G8B8, XR_SAMPLER_LINEAR | XR_SAMPLER_WRAP);

	XRVertexLayout  data_format;

	m_mtlId = m_rawDataImageIconData->renderUiNode->CreateMaterial(Material_UI_Spirit, &m_mtl);
	m_mtl->SetDiffuseMap(m_textureId);
	if(m_rawDataImageIconData->insertFlag != InsertFlag_Default)
	{
		m_spiritId = m_rawDataImageIconData->renderUiNode->CreateSpirit(m_rawDataImageIconData->targetIndex, m_rawDataImageIconData->insertFlag , m_mtlId, 1.0, m_rawDataImageIconData->iconPosX , m_rawDataImageIconData->iconPosY , 0, m_rawDataImageIconData->iconWidth,  m_rawDataImageIconData->iconHeight);
	}
	else
	{
		m_spiritId = m_rawDataImageIconData->renderUiNode->CreateSpirit(-1, InsertFlag_Default, m_mtlId, 1.0, m_rawDataImageIconData->iconPosX , m_rawDataImageIconData->iconPosY , 0, m_rawDataImageIconData->iconWidth,  m_rawDataImageIconData->iconHeight);
	}

	if(m_rawDataImageIconData->trigger)
	{
		SetOnClickDelegate(m_rawDataImageIconData->trigger);
	}
/*
	m_mtlId = m_rawDataImageIconData->renderNode->CreateMaterial(Material_Rigid_Texture, &m_mtl);
	m_mtl->SetDiffuseMap(m_textureId);

	m_meshId = m_rawDataImageIconData->renderNode->CreateMesh(ModelType_Plane_Dynamic,2, 2 ,0, "raw_data_image_icon", &m_mesh);
	m_modelNodeId = m_rawDataImageIconData->renderNode->CreateModel(0, m_mtlId, -1, InsertFlag_Default,0,0,0, 1.0, &m_modelNode);
	m_modelNode->SetMesh(m_meshId);

	m_mesh->LockData(&m_customVertex, &data_format, &m_vertexCount); 

	memcpy(m_customVertex, m_rawDataImageIconData->customVertexBuffer, sizeof(m_rawDataImageIconData->customVertexBuffer));

	m_mesh->UnLockData();
*/
}

HMIRawDataImageIcon::~HMIRawDataImageIcon()
{

}
int HMIRawDataImageIcon::Update(void* pImageData, unsigned char pUpdateStatus)
{
	if(pUpdateStatus == 1)
	{
		rm->UpdateTexture(pImageData, m_mtl->GetDiffuseMap());
	}

	ISpirit * imageLayer;

    imageLayer = m_rawDataImageIconData->renderUiNode->GetSpirit(m_spiritId);
	imageLayer->SetEnable(m_rawDataImageIconVisibility);

	//m_modelNode->SetEnable(1);

	return CI_NORMAL;
}

int HMIRawDataImageIcon::SetVisibility(unsigned char flag)
{
	if(flag > 1)
	{
		flag = 1;
	}
	else if(flag < 0)
	{
		flag = 0;
	}

	m_rawDataImageIconVisibility = flag;

	ISpirit * imageLayer;

    imageLayer = m_rawDataImageIconData->renderUiNode->GetSpirit(m_spiritId);
	imageLayer->SetEnable(m_rawDataImageIconVisibility);

	return CI_NORMAL;
}

int HMIRawDataImageIcon::ResetImageIconSize(float pWidth, float pHeight)
{
	ISpirit * imageLayer;

    imageLayer = m_rawDataImageIconData->renderUiNode->GetSpirit(m_spiritId);
	imageLayer->SetWidth(pWidth);
	imageLayer->SetHeight(pHeight);

	return CI_NORMAL; 
}
int HMIRawDataImageIcon::ResetImageIconPos(float pX, float pY,  MovingModeT pMovingMode, float pParentPosY, float pParentHeight)
{
	ISpirit * imageLayer;

    imageLayer = m_rawDataImageIconData->renderUiNode->GetSpirit(m_spiritId);
	imageLayer->SetEnable(1);

	float iconWidth = m_rawDataImageIconData->iconWidth;
	float iconHeight = m_rawDataImageIconData->iconHeight;
	Region textureReg;
	textureReg.Set(0.0, 1.0, 0.0, 1.0);
	m_rawDataImageIconVisibility = 1;
	switch(pMovingMode)
	{
	case GRID_MOVING:
		if(pY <= 0.0001
			&& pY + iconHeight >= 0.0001)
		{
			ResetImageIconSize(m_rawDataImageIconData->iconWidth, m_rawDataImageIconData->iconHeight + pY);
			textureReg.Set(0.0, 1.0, (m_rawDataImageIconData->iconHeight + pY)/m_rawDataImageIconData->iconHeight, 1.0);
			pY = 0.0;
		}
		if(pY + iconHeight < 0.0001)
		{
			m_rawDataImageIconVisibility = 0;
		}
		if((pY + iconHeight) > pParentHeight
				&&( pY <= pParentHeight - 0.001))
		{
			ResetImageIconSize(m_rawDataImageIconData->iconWidth, pParentHeight - pY);
			textureReg.Set(0.0, 1.0, 0.0, (pParentHeight - pY)/m_rawDataImageIconData->iconHeight);
		}
		if((pY + iconHeight) > pParentHeight
				&& pY > pParentHeight - 0.001)
		{
			m_rawDataImageIconVisibility = 0;
		}
		break;
	default:
		break;
	}
	imageLayer->SetMaterialROI(&textureReg);
	imageLayer->SetX(pX);
	imageLayer->SetY(pY);
	imageLayer->SetEnable(m_rawDataImageIconVisibility);
	return CI_NORMAL;
}

int HMIRawDataImageIcon::GetLayerId()
{
	return m_spiritId;
}


Boolean HMIRawDataImageIcon::OnTouchEvent(
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

Void HMIRawDataImageIcon::SetOnClickDelegate(IActionTrigger* trigger)
{
	ISpirit *buttonLayer = m_rawDataImageIconData->renderUiNode->GetSpirit(m_spiritId);
	if (buttonLayer) buttonLayer->SetEventResponder(this);
	m_trigger = trigger;
}
String HMIRawDataImageIcon::GetName()
{
	return m_name;
}

Void HMIRawDataImageIcon::SetName(String name)
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
 *  11/06/17   Jensen Wang   Create the HMICustomImageIcon class.
 *  11/08/17   Jensen Wang   Create the HMIRawDataImageIcon class.
 *  11/13/17   Jensen Wang   Add resetting size and pos func.
\*===========================================================================*/
