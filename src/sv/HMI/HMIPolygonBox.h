#ifndef _HMI_POLYGONBOX_H_ /* { */
#define _HMI_POLYGONBOX_H_
/*===========================================================================*\
 * FILE: HMIPolygonBox.h
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

/*===========================================================================*\
 * Standard Header Files
\*===========================================================================*/
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "../DataStruct.h"

typedef enum PolygonBoxRenderRegionTag
{
	REGION_3D = 0,
	REGION_BEV,
	REGION_FISHEYE_SINGLEVIEW,
	REGION_LINEAR_SINGLEVIEW,
	REGION_BEV_APA_PARKING_LOT,
	REGION_FULL_SCREEN,
	REGION_NUMS,
}
PolygonBoxRenderRegionTag;

enum
{
	MAX_POLYGON_BOX_IMAGE_NUM = 4,
};

enum
{
	POLYGON_BOX_NORMAL = 0,
};//error code

typedef struct HMIPolygonBoxDataTag
{
	PolygonBoxRenderRegionTag renderRegion;
	ISceneNode*				  renderNode;
	unsigned int			  polygonVertexNum;
	//float*					  polygonVertex;
	char*					  fillTextureName[MAX_POLYGON_BOX_IMAGE_NUM];
	int						  fillTextureIndex;
	MaterialType			  materialType;
}
HMIPolygonBoxDataT;

class HMIPolygonBox
{
public:
	HMIPolygonBox(HMIPolygonBoxDataT* pPolygonBoxData);
	~HMIPolygonBox();

	int Update(float* pVertex, unsigned char pCameraIndex = 0);
	int SetVisibility(unsigned char flag);
	int SetPolygonBoxImage(unsigned char flag);

private:
	int Init();
	int CvtCoordinate(float* pInVertex, unsigned char pCameraIndex);
private:

	HMIPolygonBoxDataT* m_polygonBoxData;

	int			m_renderNodeId;
	INode*		m_modelNode;
	int			m_modelNodeId;
	IMaterial*  m_mtl;
	int			m_mtlId;
	IMesh*		m_mesh;
	int			m_meshId;

	float*		m_polygonVertex;
	int			m_vertexCount;
	
	float		m_calibCenterX;
	float		m_calibCenterY;
	float       m_calibMmppX;
	float		m_calibMmppY;

	unsigned char m_polygonBoxVisibility;

};

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/01/17   Jensen Wang   Create the HMIRectangularBox class.
\*===========================================================================*/
#endif /* } _HMI_POLYGONBOX_H_ */



