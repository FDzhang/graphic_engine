#ifndef _HMI_CUSTOM_IMAGEICON_H_ /* { */
#define _HMI_CUSTOM_IMAGEICON_H_
/*===========================================================================*\
 * FILE: HMICustomImageIcon.h
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

typedef enum CustomImageIconRenderRegionTag
{
	CI_REGION_3D = 0,
	CI_REGION_BEV,
	CI_FISHEYE_SINGLEVIEW,
	CI_LINEAR_SINGLEVIEW,
	CI_REGION_NUMS,
}
CustomImageIconRenderRegionTag;

enum
{
	MAX_CUSTOM_IMAGE_NUM = 4,
};

enum
{
	CI_NORMAL = 0,
	CI_INIT_FAILED = 1,
	CI_UPDATE_PARAMS_NULL = 2,
};//error code

typedef enum MovingModeTag
{
	NORMAL_MOVING = 0,
	GRID_MOVING = 1,
}
MovingModeT;

typedef struct HMICustomImageIconDataTag
{
	ISceneNode*				  renderNode;
	char*					  imageName[MAX_CUSTOM_IMAGE_NUM];
	int						  imageIndex;
	float					  customVertexBuffer[32];
}
HMICustomImageIconDataT;

class HMICustomImageIcon
{
public:
	HMICustomImageIcon(HMICustomImageIconDataT* pImageIconData);
	~HMICustomImageIcon();

	int Update(float* pVertexBuffer, unsigned char pUpdateStatus = 0);
	int SetVisibility(unsigned char flag);
private:
	HMICustomImageIconDataT* m_customImageIconData;

	INode*		m_modelNode;
	int			m_modelNodeId;
	IMaterial*  m_mtl;
	int			m_mtlId;
	IMesh*		m_mesh;
	int			m_meshId;

	float*		m_customVertex;
	int			m_vertexCount;

	unsigned char m_customImageIconVisibility;
};

typedef struct HMIRawDataImageIconDataTag
{
	ISceneNode*				  renderNode;
	IUINode*				  renderUiNode;
	void*					  imageData;
	int						  imageWidth;
	int						  imageHeight;
	float					  iconPosX;
	float					  iconPosY;
	float					  iconWidth;
	float					  iconHeight;
	float					  customVertexBuffer[32];
	int						  targetIndex;
	unsigned char			  visibilityStatus;
	unsigned char			  refreshStatus;
	InsertFlag				  insertFlag;
	IActionTrigger*			  trigger;
}
HMIRawDataImageIconDataT;
class HMIRawDataImageIcon: public IEventResponder
{
public:
	HMIRawDataImageIcon(HMIRawDataImageIconDataT* pRawDataImageIconData);
	~HMIRawDataImageIcon();
	int Update(void* pImageData, unsigned char pUpdateStatus = 0);

	int SetVisibility(unsigned char flag);
	
	int GetLayerId();

	int ResetImageIconSize(float pWidth, float pHeight);
	int ResetImageIconPos(float pX, float pY, MovingModeT pMovingMode = NORMAL_MOVING, float pParentPosY = 0.0, float pParentHeight = 0.0);
private:
	virtual Boolean OnTouchEvent(
	/* [in] */Int32 layerId,
	/* [in] */Int32 x,
	/* [in] */Int32 y,
	/* [in] */Int32 type);

	virtual String GetName();
	virtual Void SetName(
		/* [in] */ String name); 

	virtual Void* GetRealType() { return (Void*)this; }

	void SetOnClickDelegate(IActionTrigger* trigger);
private:

	HMIRawDataImageIconDataT* m_rawDataImageIconData;
	int						  m_textureId;

	INode*		m_modelNode;
	int			m_modelNodeId;
	IMaterial*  m_mtl;
	int			m_mtlId;
	IMesh*		m_mesh;
	int			m_meshId;

	float*		m_customVertex;
	int			m_vertexCount;

	int			m_spiritId;

	unsigned char m_rawDataImageIconVisibility;
	
	IActionTrigger*	m_trigger;
	String             m_name;


};
/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  11/06/17   Jensen Wang   Create the HMICustomImageIcon class.
 *  11/08/17   Jensen Wang   Create the HMIRawDataImageIcon class.
\*===========================================================================*/
#endif /* } _HMI_CUSTOM_IMAGEICON_H_ */



