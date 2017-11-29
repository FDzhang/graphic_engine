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
#include "gpu_log.h"

CAvmLogicManager::CAvmLogicManager()
{
	m_adasHmi = new SVNodeAdasHMI;
}
CAvmLogicManager::~CAvmLogicManager()
{

}
int CAvmLogicManager::Init()
{
	InitViewModel();
	InitOverlayModel();
	InitAlgoHmiModel();

	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::Update()
{
	UpdateViewModel();
	UpdateOverlayModel();
	UpdateAlgoHmiModel();

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

	ISceneNode* singleViewNode;
	ISceneNode* stitchViewNode;
	AVMData::GetInstance()->GetSingleViewNode(&singleViewNode);
	AVMData::GetInstance()->GetStitchViewNode(&stitchViewNode);
	m_adasHmi->Init(bevConfig,singleViewNode,stitchViewNode,m_adasMdl,m_hmiNums);
	return AVM_LOGIC_CONTROL_NORMAL;
}

int CAvmLogicManager::UpdateViewModel()
{
	if(m_avmViewControlModel == NULL)
	{
		return AVM_LOGIC_VIEW_MODEL_INIT_FAILED;
	}
	unsigned char direction = REAR_LARGE_SINGLE_VIEW;
	static int cnt = 0;
	static int init_flag = 0;
	static const int START_UP_TURN_TIME = 120;
	/*if(init_flag ==1)
    {
        if(cnt>= START_UP_TURN_TIME)
        {       
			direction = REAR_SINGLE_VIEW;
			init_flag =2;
                
        }
    }
    if(init_flag==0)
    {
		direction = TOUR_VIEW;
		init_flag = 1;
    }
	if(cnt > START_UP_TURN_TIME)
	{
	   AVMData::GetInstance()->GetDisplayViewCmd(direction);
	   cnt++;
	}
	else 
	{
	    cnt++;
	}
*/
	AVMData::GetInstance()->GetDisplayViewCmd(direction);
	//Log_Error("----------direction: %d", direction);
	m_avmViewControlModel->SetCurrentView();
	if(direction >= FRONT_LARGE_SINGLE_VIEW
		&& direction <= RIGHT_LARGE_SINGLE_VIEW)
	{
		m_avmViewControlModel->SetViewNodeVisibility(PROCESS_LARGE_SINGLVIEW_FUNC);
	}
	else if(direction == MATTS_VIEW)
	{		
		m_avmViewControlModel->SetViewNodeVisibility(PROCESS_MATTS_FUNC);

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

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/23/17   Jensen Wang   Create the CAvmLogicManager class.
\*===========================================================================*/