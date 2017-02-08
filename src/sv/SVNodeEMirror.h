#ifndef __SV_NODE_EMIRROR_STICH_H__
#define __SV_NODE_EMIRROR_STICH_H__

//#include "fileloader.h"
#include "DataStruct.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"

#define MIRROR_NODE_MAX 3

class SVNodeEMirror 
{
public:
	SVNodeEMirror();

	int Init(unsigned char clear_flag,Region RenderRegion,float scale_size,char *pPath);
	int Update(float steering_wheel_angle,float vehicle_speed,unsigned char turn_light,unsigned char gear_state);
	ICamera* GetCameraNode();
	void InitRearSingleEmirrorNode(unsigned char clear_flag,Region RenderRegion,float scale_size );
	
	void InitEmirrorUnstichNode(unsigned char clear_flag,Region RenderRegion,float scale_size );
	void InitEmirrorNode(unsigned char clear_flag,Region RenderRegion,float scale_size );
	void CameraRollTo(float rotx,float roty);
	void CameraRollDelta(float rotx,float roty);
	int SwitchSingleView(int view_index);

private:
	INode *m_MirrorNode[MIRROR_NODE_MAX];

    ISceneNode* 		m_eMirrorNode;
	Int32               m_eMirrorNodeId;

    ISceneNode* 		m_eMirrorSingleNode;
	Int32               m_eMirrorSingleNodeId;
	
	class RenderDelegateEMirror *m_render_delegate;
	float m_camera_fov;
	
	ICamera*			m_Camera;
	ICamera*			m_Single_Camera;

	char m_left_model_name[MAX_NAME_LENGTH];
	char m_rear_model_name[MAX_NAME_LENGTH];
	char m_right_model_name[MAX_NAME_LENGTH];
	
	IScrollingAnimation*	scrollX;
	IScrollingAnimation*	scrollY;
	IMesh *m_singleview_mesh;

	
};

#endif //#ifndef __GL_SV_DEMO_H__
