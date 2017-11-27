/*===========================================================================*\
 * FILE: CAvmApaBevOverlay.h
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

#ifndef _IAVM_APA_BEV_OVERLAY_H_
#define _IAVM_APA_BEV_OVERLAY_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"
#include "IAvmOverlay.h"

#define DRIVE_BACKWARD  -1
#define DRIVE_FOWARD 1
#define DRIVE_NONE_DIRECT 0

#define NO_PARK_LOT  0
#define PARK_LOT_RECT 1

#define PARKABLE_PARK_LOT 0
#define UNPARKABLE_PORK_LOT 1
#define UNLOCKPARKABLE_PORK_LOT 2

class CAvmApaBevOverlay:public IAvmOverlay
{
public:

	virtual int Init(class ISceneNode* pRootNode);
	virtual int Update();

private:
	int InitApaOverlay(ISceneNode *pSeneNode,char *pFilePath,AVM_Calib_2D_T calib_rslt);
	int InitRectNode(float *pose,INode **pNode,ISceneNode *pSeneNode,char *pTextureName,MaterialType MtlType,float **pBuffer);
	int UpdateApaOverlay(APAOverlayStruct OverlayReslt);
	int ProcessStopSign(unsigned char sopt_flag,unsigned char end_flag,unsigned char park_lot_flag,unsigned char online_detect_flag);
	int ProcessArrowSign(int direct_indicate);
	int ProcessScrollSign(int direct_indicate,float scroll_rate);
	int CalScrollPos(float scroll_rate,float *Inrect,float*pOutputRect,int direct);
	int Cal_World_2_Image_Coordinate(float *out_Model_Coord,float *in_world_coord)	;
	int ProcessParkLotSign(int park_lot_flag,float *lot_pos,unsigned char park_lot_type);


private:

    APAOverlayStruct m_APA_result;
    char m_stop_sign_texture[MAX_NAME_LENGTH];
	char m_end_sign_texture[MAX_NAME_LENGTH];
	char m_foward_arrow_texture[MAX_NAME_LENGTH];
	char m_backward_arrow_texture[MAX_NAME_LENGTH];
	char m_scroll_texture[MAX_NAME_LENGTH];
	char m_scroll_backward_texture[MAX_NAME_LENGTH];	
	char m_parklot_texture[MAX_NAME_LENGTH];
	char m_parklotdetect_texture[MAX_NAME_LENGTH];
	char m_online_enable_texture[MAX_NAME_LENGTH];
	char m_online_apa_conflict_texture[MAX_NAME_LENGTH];
	char m_parklot_unpark_texture[MAX_NAME_LENGTH];
	char m_parklot_unlockpark_texture[MAX_NAME_LENGTH];
	INode *m_pSignNode;
	INode *m_pArrowNode;
	INode *m_pScrollNode;
	INode *m_pParkLotNode;

	float *m_Scroll_buffer;
	float *m_Parklot_buffer;
	

    AVM_Calib_2D_T m_calib_rslt;
};

#endif // _IAVM_APA_BEV_OVERLAY_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/28/17   Jensen Wang   Create the CAvmApaBevOverlay class.
\*===========================================================================*/