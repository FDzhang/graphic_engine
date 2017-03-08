#ifndef __SV_NODE_CROSS_IMAGE_H__
#define __SV_NODE_CROSS_IMAGE_H__

#include "sv/DataStruct.h"
#include "XrCore/XrSrc/External/XrHeaders.h"

#include "XrCore/XrSrc/XrUILibrary/XrUILibrary.h"





class SVNodeCrossImage 
{
public:
	SVNodeCrossImage();

	int Init(Region *pRenderRegion);
	void InitCameraSourceMateril(int SV2DMTL[]);

	int SetEnable(unsigned char flag);


private:


    ISceneNode* 		m_RenderNode;
	Int32               m_GroundNodeId;
	INode*				m_CrossMeshNode[4];
    IMesh*              m_pMeshCross[4];


	class RenderDelegateSV2D*	sv2Ddelegate;
	IMaterial*			m_SV2DMtl;

	 
};

#endif //#ifndef __GL_SV_DEMO_H__
