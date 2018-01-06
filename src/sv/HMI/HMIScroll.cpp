/*===========================================================================*\
 * FILE: HMIScroll.c
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
#include "HMIScroll.h"
#include "../AVMData.h"
#include <log/log.h>

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;

HMIScroll::HMIScroll(HmiScrollDataT* pHmiScrollData):m_scrollVisibility(1)
{
	if(pHmiScrollData == NULL)
	{
		return;
	}

	m_hmiScrollData = new HmiScrollDataT;
	memcpy(m_hmiScrollData, pHmiScrollData, sizeof(HmiScrollDataT));

	m_renderNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_renderNode);
	Region renderRegion;
	m_regionTopLeft_x = m_hmiScrollData->pos[0];
	m_regiontopLeft_y = XrGetScreenHeight() - m_hmiScrollData->pos[1];
	m_regionBottomRight_x = m_regionTopLeft_x + m_hmiScrollData->width;
	m_regionBottomRight_y = m_regiontopLeft_y - m_hmiScrollData->height;
	renderRegion.Set(m_regionTopLeft_x, m_regionBottomRight_x, m_regionBottomRight_y, m_regiontopLeft_y);
	m_renderNode->SetRenderROI(&renderRegion);

	m_scrollVisibility = m_hmiScrollData->showFlag;

	m_texturePos[0] = 0.0;
	m_texturePos[1] = 0.0;

	m_texturePos[2] = 1.0;
	m_texturePos[3] = 0.0;

	m_texturePos[4] = 0.0;
	m_texturePos[5] = 1.0;

	m_texturePos[6] = 1.0;
	m_texturePos[7] = 1.0;

	m_scrollPos[0] = -1.0;
	m_scrollPos[1] = -1.0;

	m_scrollPos[2] = 1.0;
	m_scrollPos[3] = -1.0;

	m_scrollPos[4] = -1.0;
	m_scrollPos[5] = 1.0;

	m_scrollPos[6] = 1.0;
	m_scrollPos[7] = 1.0;

	Init();

}

HMIScroll::~HMIScroll()
{
	delete m_hmiScrollData;
	
	m_renderNode->ReleaseModel(m_nodeId);
	m_renderNode->ReleaseMaterial(m_materialId);
	m_renderNode->ReleaseMesh(m_meshId);
	
}

int HMIScroll::Init()
{
	Int32 iSize;
	XRVertexLayout data_format;

	m_materialId = m_renderNode->CreateMaterial(Material_Rigid_Blend, &m_mtl);
	m_mtl->SetDiffuseMap(m_hmiScrollData->scrollImageName[m_hmiScrollData->scrollImageNum]);

	m_meshId = m_renderNode->CreateMesh(ModelType_Plane_Dynamic,2,  2,0, "scroll", &m_mesh);

	m_nodeId = m_renderNode->CreateModel(0, m_materialId, -1, InsertFlag_Default,0.0,0.0,0.0, 1.0, &m_node);

	m_node->SetMesh(m_meshId);
	m_node->SetEnable(1);

	m_mesh->LockData(&m_vertex, &data_format, &iSize);

	int slotid=0;
	for(int i =0;i<4;i++)
    {
        m_vertex[slotid+0] = m_scrollPos[2*i];
		m_vertex[slotid+1] = m_scrollPos[2*i+1]; 
		m_vertex[slotid+2] = 0;
		 
		m_vertex[slotid+6] = m_texturePos[2*i];
		m_vertex[slotid+7] = m_texturePos[2*i+1]; 

		slotid +=8;
    }
	m_mesh->UnLockData();
	
	int cameraId = m_renderNode->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &m_renderCamera);
	m_renderCamera->Set2DCamera(1);
	m_renderCamera->SetPosition(0,0,3600);
	m_renderCamera->LookAt(0.0,0.0,-0.0);
	m_renderCamera->RotateAround(0,45);
	m_renderNode->SetCamera(cameraId);

	CalcScrollActiveArea(0.0);

	return SCROLL_NORMAL;
}

int HMIScroll::Update(float pRate)
{
	if(m_scrollVisibility == 0)
	{
		return SCROLL_NORMAL;
	}

	m_node->SetEnable(m_scrollVisibility);
	CalcScrollActiveArea(pRate);

	return SCROLL_NORMAL;
}

int HMIScroll::CalcScrollActiveArea(float pRate)
{
	Region renderRegion;
	int horizonalPointIndex1 = 14;
	int horizonalPointIndex2 = 30;
	int verticalPointIndex1 = 23;
	int verticalPointIndex2 = 31;

	if(m_hmiScrollData->scrollType == SCROLL_HORIZONTAL)
	{
		m_vertex[horizonalPointIndex1] = pRate;
		m_vertex[horizonalPointIndex2] = pRate;
					
		m_regionBottomRight_x = m_regionTopLeft_x + m_hmiScrollData->width * pRate;
	
		renderRegion.Set(m_regionTopLeft_x, m_regionBottomRight_x, m_regionBottomRight_y, m_regiontopLeft_y);
	
		m_renderNode->SetRenderROI(&renderRegion);
	}
	else if(m_hmiScrollData->scrollType == SCROLL_VERTICAL)
	{
		m_vertex[verticalPointIndex1] = pRate;
		m_vertex[verticalPointIndex2] = pRate;
					
		m_regiontopLeft_y = XrGetScreenHeight() - m_hmiScrollData->pos[1] -  m_hmiScrollData->height * (1.0 - pRate);
	
		renderRegion.Set(m_regionTopLeft_x, m_regionBottomRight_x, m_regionBottomRight_y, m_regiontopLeft_y);
	
		m_renderNode->SetRenderROI(&renderRegion);
	}
	m_mesh->UnLockData();

	return SCROLL_NORMAL;
}

int HMIScroll::SetVisibility(unsigned char flag)
{
	if(flag > 1)
	{
		flag = 1;
	}
	else if(flag < 0)
	{
		flag = 0;
	}

	m_scrollVisibility = flag;
	m_node->SetEnable(m_scrollVisibility);

	return SCROLL_NORMAL;
}

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  10/11/17   Jensen Wang   Create the HMIScroll class.
\*===========================================================================*/
