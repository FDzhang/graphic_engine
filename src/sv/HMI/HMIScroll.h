#ifndef _HMI_SCROLL_H_ /* { */
#define _HMI_SCROLL_H_
/*===========================================================================*\
 * FILE: HMIScroll.h
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

enum
{
    MAX_SCROLL_IMAGE_NUM = 10,
};
enum
{
	SCROLL_HORIZONTAL = 0,
	SCROLL_VERTICAL = 1,
};
enum
{
	SCROLL_NORMAL = 0,
};//button error code

typedef struct HmiScrollDataTag
{
	float pos[2];
    float width;
    float height;
	unsigned char showFlag;
	unsigned char scrollType;
	int   scrollImageNum;
	char* scrollImageName[MAX_SCROLL_IMAGE_NUM];
}
HmiScrollDataT;

class HMIScroll
{
public:
	HMIScroll(HmiScrollDataT* pHmiScrollData);
	~HMIScroll();

	int Update(float pRate);
	int SetVisibility(unsigned char flag);

	virtual int CalcScrollActiveArea(float pRate);

private:
	int Init();
	
private:
	int m_renderNodeId;
	class ISceneNode* m_renderNode;
	class ICamera*    m_renderCamera;
	
	HmiScrollDataT*   m_hmiScrollData;

	int m_materialId;
	IMaterial*  m_mtl;

	int m_meshId;
	IMesh*      m_mesh;

	int m_nodeId;
	INode*		m_node;

	float m_scrollPos[8];
	float m_texturePos[8];

	float* m_vertex;

	float m_regionTopLeft_x;
	float m_regiontopLeft_y;
	float m_regionBottomRight_x;
	float m_regionBottomRight_y;

	unsigned char m_scrollVisibility;


};

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  10/11/17   Jensen Wang   Create the HMIScroll class.
\*===========================================================================*/
#endif /* } _HMI_SCROLL_H_ */



