/*===========================================================================*\
 * FILE: HMIGuideLine.h
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

#ifndef _HMI_GUIDELINE_H_
#define _HMI_GUIDELINE_H_

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../DataStruct.h"
typedef enum
{
    GUIDELINE_NORMAL,
};

typedef enum GuideLineTypeTag
{
    GUIDELINE_BEV_DYNAMIC = 0,
    GUIDELINE_BEV_STATIC,
    GUIDELINE_SINGLEVIEW_DYNAMIC,
    GUIDELINE_SINGLEVIEW_DYNAMIC_NEW,
    GUIDELINE_SINGLEVIEW_STATIC,
	GUIDELINE_DX3_LEFT_SINGLEVIEW_STATIC,
	GUIDELINE_DX3_RIGHT_SINGLEVIEW_STATIC,
	GUIDELINE_3D_DYNAMIC,
    GUIDELINE_3D_STATIC,
    GUIDELINE_BEV_ASSIST_DYNAMIC,
    GUIDELINE_BEV_ASSIST_STATIC,
    GUIDELINE_BEV_WHEEL_DYNAMIC,
    GUIDELINE_TYPE_NUM,
}
GuideLineTypeT;

typedef enum GuideLineAlignModeTag
{
    GUIDELINE_ALIGH_MODE_NUM,
}
GuideLineAlignModeT;

typedef enum GuideLinePosTag
{
    GUIDELINE_POS_LEFT = 0,
    GUIDELINE_POS_RIGHT,
    GUIDELINE_POS_NUM,
}
GuideLinePosT;

typedef enum GuideLineCamPosTag
{
    GUIDELINE_CAM_ZONE_LEFT=0,
	GUIDELINE_CAM_ZONE_TOP,
    GUIDELINE_CAM_ZONE_RIGHT,
	GUIDELINE_CAM_ZONE_BOTTOM,	
}
GuideLineCamPosT;
typedef enum GuideLineTextureFlagTag
{
    GUIDELINE_TEXTURE_NORMAL=0,
	GUIDELINE_TEXTURE_NUM,	
}
GuideLineTextureFlagT;

typedef enum GuideLineCamIndexTag
{
	GUIDELINE_DIR_FORWARD = 0,
	GUIDELINE_DIR_BACKWARD,
	GUIDELINE_DIR_LEFT,
	GUIDELINE_DIR_RIGHT,

}
GuideLineCamIndexT;


#define GUIDELINE_PI 3.1415926

typedef struct HMIGuideLineDataTag
{
	char*		   guideLineName;
    GuideLineTypeT guideLineType;
    GuideLinePosT  guideLinePos;
    
	//��λ��mm
    float guideLineWidth;
    float guideLineLength;
    float guideLineSideDistanceFromVehicle;
    float guideLineStartDistanceFromVehicle;

    int   guideLinePointNum;

	char* guideLineTexture[GUIDELINE_TEXTURE_NUM];
	MaterialType    guideLineTextureType;

	float* guideLineVertexData;

}
HMIGuideLineDataT;

/***************ʹ�ð���***************/
/*
	//��̬�����߰���
	HMIGuideLineDataT guideLineData;

	guideLineData.guideLineLength = 3000.0;
	guideLineData.guideLineName = "test";
	guideLineData.guideLineType = GUIDELINE_SINGLEVIEW_DYNAMIC;
	guideLineData.guideLinePos = GUIDELINE_POS_LEFT;
	guideLineData.guideLineWidth = 200.0;
	guideLineData.guideLineSideDistanceFromVehicle = 200.0;
	guideLineData.guideLineStartDistanceFromVehicle = 0.0;
	guideLineData.guideLinePointNum = 40;
	guideLineData.guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
	sprintf(guideLineData.guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/guide_line_red.dds",XR_RES);
	guideLineData.guideLineTextureType = Material_Rigid_Blend;

	HMIGuideLine*      guideLine;
	ISceneNode*		   guideLineNode;
	AVMData::GetInstance()->GetSingleViewNode(&guideLineNode);
	guideLine = new HMIGuideLine(guideLineNode, &guideLineData);
	guideLine->Update(400.0, GUIDELINE_DIR_BACKWARD);
	guideLine->SetVisibility(0);

	HMIGuideLine*      guideLine2;
	guideLineData.guideLinePos = GUIDELINE_POS_RIGHT;
	guideLine2 = new HMIGuideLine(guideLineNode, &guideLineData);
	guideLine2->Update(600.0, GUIDELINE_DIR_BACKWARD);
	guideLine2->SetVisibility(0);

	//���Ͼ�̬�����߰���
	HMIGuideLineDataT guideLineData1;

	guideLineData1.guideLineName = "test";
	guideLineData1.guideLineType = GUIDELINE_DX3_RIGHT_SINGLEVIEW_STATIC;
	guideLineData1.guideLinePointNum = 2;
	guideLineData1.guideLineTexture[GUIDELINE_TEXTURE_NORMAL] = new char[50];
	sprintf(guideLineData1.guideLineTexture[GUIDELINE_TEXTURE_NORMAL],"%sCar/guide_line_green.dds",XR_RES);
	guideLineData1.guideLineTextureType = Material_Rigid_Blend;

	//��൥��ͼx������ʵ���෴
	static float pos[8] = {1937.0, 0.9, 1837.5, 0.9, 1923.0, 3167.0, 1837.5, 3163.0};
	guideLineData1.guideLineVertexData = tmp;
	
	HMIGuideLine*      guideLine3;
	guideLine3 = new HMIGuideLine(guideLineNode, &guideLineData1);
	guideLine3->Update(600.0, GUIDELINE_DIR_RIGHT);
*/
class HMIGuideLine
{
public:
    HMIGuideLine(ISceneNode* pRootNode = NULL, HMIGuideLineDataT* pGuideLineData = NULL);
    ~HMIGuideLine();

    int Update(float pSteeringWheel,int pDriveDirection);
	int ResetCamZone(unsigned char pCamPos, float* pCamZone);
	int SetVisibility(unsigned char pFlag);

private:
    int CalSteeringWheel2Radius(float *pRadius,float pSteerAngle,int pGearState);
    int CaculateCenter(float* pCenterX, float* pCenterY, 
						float pRadius[], float* pTheta, float pSteeringWheel, int pDirect);
    int GenerateDynamicGuideLine(float pCenterX, float pCenterY,float pRadius[],
							float pStartAngle[],float*pVertex);
	int GenerateStaticGuideLine(float* pVertex);
    int CalWorld2ModelCoordinate(float *out_Model_Coord,float *in_world_coord,float *out_texture);

private:
    HMIGuideLineDataT* m_guideLineData;
	unsigned char      m_currentCamPos;
	float			   m_frontCamZone[4];
	float			   m_rearCamZone[4];
	float			   m_leftCamZone[4];
	float			   m_rightCamZone[4];

	ISceneNode*		   m_rootNode;

	IMaterial*		   m_guideLineMtl;
	int				   m_guideLineMtlId;

	IMesh*			   m_guideLineMesh;
	int				   m_guideLineMeshId;

	INode*			   m_guideLineNode;
	int				   m_guideLineNodeId;

	float			   m_modelBottom;
	float			   m_modelScale;

	float			   m_calibCenterX;
	float		       m_calibCenterY;
	float              m_calibMmppX;
	float		       m_calibMmppY;

	float              m_bevRoiWidth;
	float              m_bevRoiHeight;

	Veh_Param_T*	   m_vehParam;

	float*              m_vertext;

	unsigned char		m_guideLineVisibility;

    float m_guideLineLength;
    float m_guideLineStartDistanceFromVehicle;
};

#endif //_HMI_GUIDELINE_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  21/01/18   Jensen Wang   Create the HMIGuideLine class.
\*===========================================================================*/