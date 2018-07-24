/*===========================================================================*\
 * FILE: CAvmLogicManager.h
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
#include "CAvmLogicManager.h"
#include "CAvmViewControlModel.h"
#include "../AVMData.h"
#include "../SVNodeAdasHmi.h"
#include "../HMISource/ISVHmi.h"
#include "../HMISource/CSVChangAnHmi.h"
#include "../HMISource/CSVChangAnMainHmi.h"
#include "../HMISource/CSVDemoMainHmi.h"
#include "../HMISource/CSVSystemHmi.h"
#include "../HMISource/CSVS302MainHmi.h"
#include "../HMISource/CSVV302MainHmi.h"

#include "gpu_log.h"

CAvmLogicManager::CAvmLogicManager():m_systemHmi(0)
{
	m_adasHmi = new SVNodeAdasHMI;
}
CAvmLogicManager::~CAvmLogicManager()
{

}
int CAvmLogicManager::Init()
{
	Log_Error("------------Init GPU!");
	InitViewModel();
	InitOverlayModel();
	//InitAlgoHmiModel();
	InitHmi();
	Log_Error("------------Init GPU finished!");	
	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::ProcessTouchEvent()
{
	if(m_avmViewControlModel)
	{
		m_avmViewControlModel->Process3dTouchData();
	}
	
	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::Update()
{
	UpdateHmi();
	UpdateViewModel();	
	UpdateOverlayModel();	
	//UpdateAlgoHmiModel();	

	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::UpdateRenderStatus()
{

	if(m_avmViewControlModel)
	{
		m_avmViewControlModel->UpdateRenderStatus();
	}

	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::UpdateStitchAngle()
{
	if(m_avmViewControlModel)
	{
		m_avmViewControlModel->UpdateStitchAngle();
	}
	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::UpdateExternCalib2DReslt()

{	
	if(m_avmViewControlModel)
	{
		m_avmViewControlModel->UpdateExternCalib2DReslt();
	}
	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::UpdateExternCalib3DReslt()

{	
	if(m_avmViewControlModel)
	{
		m_avmViewControlModel->UpdateExternCalib3DReslt();
	}
	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::SetAdasHmiParams(st_ADAS_Mdl_HMI_T** pAdasMdl, int hmiNums)
{
	m_adasMdl = pAdasMdl;
	m_hmiNums = hmiNums;
	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::InitViewModel()
{
	m_avmViewControlModel = NULL;
	m_avmViewControlModel = new CAvmViewControlModel;
	m_avmViewControlModel->InitViewNode();

	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::InitOverlayModel()
{
	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::InitAlgoHmiModel()
{
	BEV_CONFIG_T bevConfig;
	AVMData::GetInstance()->GetBevConfig(&bevConfig);

	ISceneNode* singleViewNode = NULL;
	ISceneNode* stitchViewNode = NULL;
	CAvmRenderDataBase::GetInstance()->GetSingleViewNode(&singleViewNode);
	CAvmRenderDataBase::GetInstance()->GetStitchViewNode(&stitchViewNode);
	if(singleViewNode != NULL
		&& stitchViewNode != NULL)
	{
		m_adasHmi->Init(bevConfig,singleViewNode,stitchViewNode,m_adasMdl,m_hmiNums);
	}
	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::InitHmi()
{

	SetMainHmiName();
	CSVHmiIntent::GetInstance()->Intent(m_mainHmiName);

	
	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::SetMainHmiName()
{
	unsigned char currentVehicleTypeId;
	CAvmRenderDataBase::GetInstance()->GetVehicleTypeId(currentVehicleTypeId);

    //currentVehicleTypeId = CHANGAN_S302;

	switch(currentVehicleTypeId)
	{
		case CHANGAN_S302:
			m_mainHmiName = "CSVS302MainHmi";
			break;
        case CHANGAN_V302:
            m_mainHmiName = "CSVV302MainHmi";
            break;
		default:
			m_mainHmiName = "CSVDemoMainHmi";
	}
	
	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::AddHmi(ISVHmi* pSvHmi, vector<ISVHmi*>* pHmi)
{
	if(pSvHmi)
	{
		pSvHmi->Init(XrGetScreenWidth(), XrGetScreenHeight());
		
		(*pHmi).push_back(pSvHmi);
	}
	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::UpdateHmi()
{
	Hmi_Message_T hmiMsg;

	CSVHmiIntent::GetInstance()->StartHmi(&hmiMsg);

	for(vector<ISVHmi*>::iterator hmiObj = m_avmHmi.begin(); hmiObj != m_avmHmi.end(); hmiObj++)
	{
		(*hmiObj)->Update(hmiMsg);
	}
	//RemoveHmi(&m_avmHmi, m_dvrBaseHmi);

	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::UpdateViewModel()
{
	if(m_avmViewControlModel == NULL)
	{
		return AVM_LOGIC_VIEW_MODEL_INIT_FAILED;
	}
	unsigned char direction = FRONT_3D_VIEW;

	CAvmRenderDataBase::GetInstance()->GetDisplayViewCmd(direction);
	//Log_Error("----------direction: %d", direction);
	m_avmViewControlModel->SetCurrentView();
	if((direction >= FRONT_LARGE_SINGLE_VIEW
		&& direction <= RIGHT_LARGE_SINGLE_VIEW)
		|| (direction >= CAMERA_DEBUG_FRONT_SINGLE_VIEW
		&& direction <= CAMERA_DEBUG_REAR_SINGLE_VIEW)
		||(direction >= DVR_FRONT_SINGLE_VIEW
		&& direction <= DVR_RIGHT_SINGLE_VIEW))
	{
		m_avmViewControlModel->SetViewNodeVisibility(PROCESS_LARGE_SINGLVIEW_FUNC);
	}
	else if(direction == MATTS_VIEW)
	{		
		m_avmViewControlModel->SetViewNodeVisibility(PROCESS_MATTS_FUNC);

	}
	else if(direction >= TOTAL_VIEW_NUM)
	{
		CAvmRenderDataBase::GetInstance()->SetDisplayViewCmd(REAR_SINGLE_VIEW);
		m_avmViewControlModel->SetViewNodeVisibility(PROCESS_VIEW_DISPLAY_FUNC);
	}
	else if(direction == TOUR_LARGE_3D_VIEW)
	{
		m_avmViewControlModel->SetViewNodeVisibility(PROCESS_LARGE_3DVIEW_FUNC);
	}
	else
	{
		m_avmViewControlModel->SetViewNodeVisibility(PROCESS_VIEW_DISPLAY_FUNC);
	}

	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::UpdateOverlayModel()
{
	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::UpdateAlgoHmiModel()
{
	m_adasHmi->Update();
	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::RemoveHmi(vector<ISVHmi*>* pHmi, ISVHmi* pHmiObj)
{
	if((*pHmi).empty())
	{
		return AVM_LOGIC_CONTROL_NORMAL;
	}
	for(vector<ISVHmi*>::iterator index = (*pHmi).begin(); index != (*pHmi).end(); )
	{
	
		if((*index) != NULL)
		{
			if(*index == pHmiObj) 
			{	
				delete *index;
				*index = NULL;
          		index = (*pHmi).erase(index);  
      		}
			else  
            {
            	index ++ ; 
			}
		}
	}
		
	return AVM_LOGIC_CONTROL_NORMAL;
}
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/23/17   Jensen Wang   Create the CAvmLogicManager class.
 *  12/15/17   Jensen Wang   add the Hmi init, update, remove function.
\*===========================================================================*/
