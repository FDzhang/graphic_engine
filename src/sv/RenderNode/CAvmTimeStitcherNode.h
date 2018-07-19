/*===========================================================================*\
 * FILE: CAvmTimeStitcherNode.h
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

#ifndef _CAVM_TIMESTITCHER_NODE_H_
#define _CAVM_TIMESTITCHER_NODE_H_

#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../DataStruct.h"
#include "../HMI/HMIGuideLine.h"
#include "../HMI/HMIButton.h"

typedef enum AvmTimeStitcherErrorCodeTag
{
	TIME_STITCHER_NORMAL = 0,
	TIME_STITCHER_XRCORE_NULL,
};

class CAvmTimeStitcherNode
{
public:
	CAvmTimeStitcherNode();
	~CAvmTimeStitcherNode();
	virtual int InitNode(class IXrCore* pXrcore);
	virtual int UpdateNode();
	virtual int SetVisibility(unsigned char pVisibilityFlag);
	int UpdateStich2DReslt();	
	int UpdateExternCalib2DReslt();
	int SetClear(unsigned char pColorFlag, unsigned char pDepthFlag);
private:
	int CalcGroundTexture();
	int AddOverlay(class IAvmOverlay * pOverlay);
	
	int InitAvmBackground();
	void SetHmiGuideline();
    void RefreshHmiGuideline();
	void ResetGuideLineEndPos(float pSteerAngle);
protected:
	class IXrCore*       m_xrCore;
	class ISceneNode*   m_stitchViewNode;
	class IMaterial*    m_stitchViewMtl;
	class IMaterial*	m_SV2DMtl;

	class IMesh*		m_planeMesh;
	class IMesh*		m_avmBkMesh;
	class IMaterial*	m_carBodyMtl;
	int					m_stitchViewNodeId;
	int 				m_planeMeshId;
	int 				m_avmBkMeshId;

	class INode*		m_avmBkNode;
	class INode*		m_carImageNode;

	class GlSV2D*				m_SV2DData;

	class RenderDelegateSV2D*		m_renderDelegate; 
	
	class SVNode2DStich*			m_timeStitchNode;

	SurroundViewCameraParamsT*   m_stitchViewCameraParams;
	class ICamera*	m_stitchViewCamera;
	int			m_stitchViewCameraId;

	unsigned char m_visibilityFlag;

	class IAvmOverlay*			m_overlay;
	class SVNodeSonar*			m_sonarNode;
	HMIGuideLineDataT   m_guideLineData[DEMO_GUIDELINE_NUM];
    HMIGuideLine*       m_guideLine[DEMO_GUIDELINE_NUM];

    unsigned char       m_bevDynGuideLineVisibility;
	unsigned char       m_bevDynOutLGuideLineVisibility;
	unsigned char       m_bevDynOutRGuideLineVisibility;
    unsigned char       m_bevAsitLDynGuideLineVisibility;
    unsigned char       m_bevAsitRDynGuideLineVisibility;
};
#endif // _CAVM_TIMESTITCHER_NODE_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the CAvmTimeStitcherNode class.
\*===========================================================================*/
