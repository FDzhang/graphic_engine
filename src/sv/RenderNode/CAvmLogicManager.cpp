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
	AVMData::GetInstance()->SetDisplayViewCmd(FRONT_SINGLE_VIEW);
	avmViewControlModel->SetCurrentView();
	avmViewControlModel->SetViewNodeVisibility(PROCESS_VIEW_DISPLAY_FUNC);

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