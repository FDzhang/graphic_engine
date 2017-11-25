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

CAvmLogicManager::CAvmLogicManager()
{
	
}
CAvmLogicManager::~CAvmLogicManager()
{

}
int CAvmLogicManager::InitViewModel()
{
	avmViewControlModel = new CAvmViewControlModel;
	avmViewControlModel->InitViewNode();

	return AVM_LOGIC_CONTROL_NORMAL;
}
int CAvmLogicManager::Update()
{
	unsigned char direction = TOUR_VIEW;
	static int cnt = 0;
	static int init_flag = 0;
	static const int START_UP_TURN_TIME = 120;
	if(init_flag ==1)
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
	   direction = FRONT_LARGE_SINGLE_VIEW;
	   cnt++;
	}
	else 
	{
	    cnt++;
	}

	if(cnt > 500)
	{
		direction = FRONT_SINGLE_VIEW;
	}
	//direction = MATTS_VIEW;
	//direction = FRONT_SINGLE_VIEW;
	//direction = FRONT_LARGE_SINGLE_VIEW;
	AVMData::GetInstance()->SetDisplayViewCmd(direction);
	avmViewControlModel->SetCurrentView();
	if(direction >= FRONT_LARGE_SINGLE_VIEW
		&& direction <= RIGHT_LARGE_SINGLE_VIEW)
	{
		avmViewControlModel->SetViewNodeVisibility(PROCESS_LARGE_SINGLVIEW_FUNC);
	}
	else if(direction == MATTS_VIEW)
	{		
		avmViewControlModel->SetViewNodeVisibility(PROCESS_MATTS_FUNC);

	}
	else
	{
		avmViewControlModel->SetViewNodeVisibility(PROCESS_VIEW_DISPLAY_FUNC);
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
\*===========================================================================*/