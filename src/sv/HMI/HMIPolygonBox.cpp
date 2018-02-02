/*===========================================================================*\
 * FILE: HMIPolygonBox.c
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
#include "HMIPolygonBox.h"
#include "../AVMData.h"

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;

HMIPolygonBox::HMIPolygonBox(HMIPolygonBoxDataT* pPolygonBoxData):m_modelNode(NULL),
																		m_mtl(NULL),
																		m_mesh(NULL),
																		m_polygonBoxVisibility(0)
{
	if(pPolygonBoxData == NULL
		|| pPolygonBoxData->polygonVertexNum == 0)
	{
		return;
	}

	m_polygonBoxData = new HMIPolygonBoxDataT;
	memcpy(m_polygonBoxData, pPolygonBoxData, sizeof(HMIPolygonBoxDataT));

	XRVertexLayout data_format;
	
	if(m_polygonBoxData->renderRegion == REGION_FULL_SCREEN)
	{
		m_renderNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_polygonBoxData->renderNode);
		Region renderRegion;	
		renderRegion.Set(0.0, XrGetScreenWidth(),0.0, XrGetScreenHeight());
		m_polygonBoxData->renderNode->SetRenderROI(&renderRegion);
		ICamera*	  m_renderCamera;
		int cameraId = m_polygonBoxData->renderNode->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &m_renderCamera);
		m_renderCamera->Set2DCamera(1);
		m_renderCamera->SetPosition(0,0,3600.0);
		m_renderCamera->LookAt(0.0,0.0,-0.0);
		m_renderCamera->RotateAround(0,45);
		m_polygonBoxData->renderNode->SetCamera(cameraId);
	}

	m_mtlId = m_polygonBoxData->renderNode->CreateMaterial(m_polygonBoxData->materialType, &m_mtl);
	m_mtl->SetDiffuseMap(m_polygonBoxData->fillTextureName[m_polygonBoxData->fillTextureIndex]);

	m_modelNodeId = m_polygonBoxData->renderNode->CreateModel(0, m_mtlId, -1, InsertFlag_Default, 0.0, 0.0, 0.0, 1.0, &m_modelNode);

	if(m_polygonBoxData->renderRegion == REGION_FULL_SCREEN)
	{
		m_meshId = m_polygonBoxData->renderNode->CreateMesh(ModelType_Plane_Dynamic, 2, m_polygonBoxData->polygonVertexNum, 0, "polygon_box",&m_mesh);
	}
	else
	{
		m_meshId = m_polygonBoxData->renderNode->CreateMesh(ModelType_Plane_Dynamic, 2, m_polygonBoxData->polygonVertexNum/2, 0, "polygon_box",&m_mesh);
	}

	m_modelNode->SetMesh(m_meshId);
	m_modelNode->SetEnable(m_polygonBoxVisibility);

	m_mesh->LockData(&m_polygonVertex, &data_format, &m_vertexCount);

	m_calibCenterX = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CY);
	m_calibCenterY = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_CX);
	m_calibMmppX = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMY);
	m_calibMmppY = AVMData::GetInstance()->m_2D_lut->GetCalibReslt(POS_CALIB_PPMMX);

}
HMIPolygonBox::~HMIPolygonBox()
{
	m_polygonBoxData->renderNode->ReleaseModel(m_modelNodeId);
	m_polygonBoxData->renderNode->ReleaseMaterial(m_mtlId);
	m_polygonBoxData->renderNode->ReleaseMesh(m_meshId);

	delete m_polygonBoxData;

}
int HMIPolygonBox::Update(float* pVertex, unsigned char pCameraIndex)
{
	if(pVertex != NULL
		&& pCameraIndex < right_camera_index)
	{
		CvtCoordinate(pVertex, pCameraIndex);
	}
	m_mtl->SetDiffuseMap(m_polygonBoxData->fillTextureName[m_polygonBoxData->fillTextureIndex]);
	m_mesh->UnLockData();
	m_modelNode->SetEnable(m_polygonBoxVisibility);

	return POLYGON_BOX_NORMAL;
}
int HMIPolygonBox::SetVisibility(unsigned char flag)
{
	m_polygonBoxVisibility = flag;

	m_modelNode->SetEnable(m_polygonBoxVisibility);

	return POLYGON_BOX_NORMAL;
}
int HMIPolygonBox::SetPolygonBoxImage(unsigned char flag)
{
	m_polygonBoxData->fillTextureIndex = flag;
	m_mtl->SetDiffuseMap(m_polygonBoxData->fillTextureName[m_polygonBoxData->fillTextureIndex]);

	return POLYGON_BOX_NORMAL;
}

int HMIPolygonBox::Init()
{
	return POLYGON_BOX_NORMAL;
}

int HMIPolygonBox::CvtCoordinate(float* pInVertex, unsigned char pCameraIndex)
{
	unsigned int slotid=0;
	float imageCoord[3]={0,0,0};
	float gpuModelCoord[3];
	float interval = 0.15;
	float k[2],b[2];
	
	switch(m_polygonBoxData->renderRegion)
	{
	case REGION_3D:
		break;
	case REGION_BEV:
		
		for(int i = 0; i < m_polygonBoxData->polygonVertexNum; i++)
		{    
			imageCoord[0] = pInVertex[2*i];
			imageCoord[1] = pInVertex[2*i+1];		
        
			gpuModelCoord[1] = 1.0-(((imageCoord[1])/(0.0-m_calibMmppY) + m_calibCenterY)/240.0);
			gpuModelCoord[0] =((imageCoord[0])/m_calibMmppX + m_calibCenterX-108.0)/108.0;	

			m_polygonVertex[slotid+0]= gpuModelCoord[0];
			m_polygonVertex[slotid+2]= gpuModelCoord[1];
			m_polygonVertex[slotid+1]= m_polygonVertex[slotid+2];

			slotid+=8;

		}

		break;
	case REGION_BEV_APA_PARKING_LOT:

		static float x[8], y[8];
		for(int i = 0; i < 4; i++)
		{    
			imageCoord[0] = pInVertex[2*i];
			imageCoord[1] = pInVertex[2*i+1];		
        
			gpuModelCoord[1] = 1.0-(((imageCoord[1])/(0.0-m_calibMmppY) + m_calibCenterY)/240.0);
			gpuModelCoord[0] =((imageCoord[0])/m_calibMmppX + m_calibCenterX-108.0)/108.0;	

			x[i] = gpuModelCoord[0];
			y[i] = gpuModelCoord[1];

			slotid+=8;

		}
		
		for(int i = 0; i < 2; i++)
		{
			k[0 + i] = (y[0 + i] - y[2 + i])/(x[0 + i] - x[2 + i]);
			if((IsFloatEqual(x[0 + i], x[2 + i], 0.0001)))
			{
				k[0 + i] = 0.00001;
			}
			if(k[0 + i] == 0.0)
			{
				k[0 + i] = 0.00001;
			}

			b[0 + i] = y[0 + i] - k[0 + i] * x[0 + i];

			if((IsFloatEqual(x[0 + i], x[2 + i], 0.001)))
			{
				x[4 + i] = x[2 + i];
				x[6 + i] = x[4 + i];
				y[4 + i] = y[2 + i];
				y[6 + i] = y[4 + i] + interval;
				y[2 + i] = y[0 + i];
				y[0 + i] = y[2 + i] - interval;
			}
			else
			{
				y[4 + i] = y[2 + i];
				y[6 + i] = y[4 + i] + interval;
				y[2 + i] = y[0 + i];
				y[0 + i] = y[2 + i] - interval;

				x[4 + i] = x[2 + i];
				x[2 + i] = x[0 + i];
				x[0 + i] = (y[0 + i] - b[0 + i])/k[0 + i];
				x[6 + i] = (y[6 + i] - b[0 + i])/k[0 + i];
			}
		}

		slotid = 0;

		for(int i = 0; i < m_polygonBoxData->polygonVertexNum; i++)
		{
			m_polygonVertex[slotid+0]= x[i];
			m_polygonVertex[slotid+2]= y[i];
			m_polygonVertex[slotid+1]= m_polygonVertex[slotid+2];
			
			if(i == 0 || i == 1)
			{
				m_polygonVertex[slotid+7] = 1.0;
			}
			else if(i == 2 || i == 3)
			{
				m_polygonVertex[slotid+7] = 0.76;
			}
			else if(i == 4 || i == 5)
			{
				m_polygonVertex[slotid+7] = 0.24;
			}
			else if(i == 6 || i == 7)
			{
				m_polygonVertex[slotid+7] = 0.0;
			}

			slotid+=8;
		}
		break;
	case REGION_FISHEYE_SINGLEVIEW:
		for(int i = 0; i < m_polygonBoxData->polygonVertexNum; i++)
		{    
			imageCoord[0] = pInVertex[2*i];
			imageCoord[1] = pInVertex[2*i+1];		
        
			AVMData::GetInstance()->cvtSingleViewImagePoint2GpuPoint(gpuModelCoord,imageCoord,pCameraIndex);

			m_polygonVertex[slotid+0]= gpuModelCoord[0];
			m_polygonVertex[slotid+1]= gpuModelCoord[1];
			m_polygonVertex[slotid+2]= gpuModelCoord[2];

			slotid+=8;

		}
	
		break;
	case REGION_LINEAR_SINGLEVIEW:
		break;
	case REGION_FULL_SCREEN:
		static float storePoint[2];
		static float lineWidth = 2.0;
		for(int i = 0; i < m_polygonBoxData->polygonVertexNum; i++)
		{    
			
			
			imageCoord[0] = pInVertex[2*i];
			imageCoord[1] = pInVertex[2*i+1];	

			gpuModelCoord[2] = 0.0;
    		gpuModelCoord[1] = -imageCoord[1]/XrGetScreenHeight()/0.5+1;
			gpuModelCoord[0] = imageCoord[0]/XrGetScreenWidth()/0.5-1;
	
			m_polygonVertex[slotid+0]= gpuModelCoord[0];
			m_polygonVertex[slotid+1]= gpuModelCoord[1];
			m_polygonVertex[slotid+2]= gpuModelCoord[2];

			slotid+=8;
					
			imageCoord[1] += lineWidth;	
			gpuModelCoord[2] = 0.0;
    		gpuModelCoord[1] = -imageCoord[1]/XrGetScreenHeight()/0.5+1;
			gpuModelCoord[0] = imageCoord[0]/XrGetScreenWidth()/0.5-1;

			m_polygonVertex[slotid+0]= gpuModelCoord[0];
			m_polygonVertex[slotid+1]= gpuModelCoord[1];
			m_polygonVertex[slotid+2]= gpuModelCoord[2];

			slotid+=8;
			
		}
		break;
	default:
		break;
	}
	return POLYGON_BOX_NORMAL;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the HMIRectangularBox class.
\*===========================================================================*/
