#ifndef __SV_NODE_2D_STICH_H__
#define __SV_NODE_2D_STICH_H__

//#include "fileloader.h"
#include "DataStruct.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "vehicle_motion_model.h"
#include "TS_config.h"

#define LEFT_BOTTOM_POINT_INDEX 2
#define RIGHT_BOTTOM_POINT_INDEX 3
#define LEFT_TOP_POINT_INDEX  0
#define RIGHT_TOP_POINT_INDEX 1

#define CAR_LENGTH 4.667f
#define CAR_WIDTH 1.839f


class SVNode2DStich 
{
public:
	SVNode2DStich();

	virtual int Init();
	virtual int Update(float steering_wheel_angle,float vehicle_speed,float left_wheel_speed,float right_wheel_speed,unsigned char gear_state,int time_offset,float yaw_rate);
	int GetKeyFrameTextureId();
	int GetGroundTextureId();
	virtual int GetStichFrameTextureId();
	virtual void InitStichKeyFrameNodeRT(int j);

	virtual void Init2DGroundNodeRT(int j);
	
	int ProcessGroundCoord(float steering_wheel_angle,float vehicle_speed,float left_wheel_speed, float right_wheel_speed,unsigned char gear_state,int time_offset,float yaw_rate);
	virtual void UpdateGoundTextureCoord(GpuCvPoint2D32f *pTextureIndex);
	//Update(unsigned char update_key_flag)
	virtual int SetEnable(unsigned char flag);
	
	void UpdateStich2DReslt(int index);
	virtual void InitStichAreaRT(void);
	void CalcShadowTextureCoord(float *car_rect,float *shadow_rect,float *pshadow_texture);
	void Update2DStichRslt(void);

protected:
		void Cvt4Point2Rect(float *pPoint,GpuCvPoint2D32f *pRect);
		//void CvtPointWorld2Image(CvPoint2D32f InPoint,CvPoint2D32f *pOutPoint);
		//void CvtPointImage2Wolrd(CvPoint2D32f InPoint,CvPoint2D32f *pOutPoint);

    ISceneNode* 		m_GroundNode;
    IMaterial*			m_ground_mtl;
	IRenderTarget*		m_groundRT;	
	Int32               m_GroundNodeId;
    IMesh*              m_pMeshStichGround;
	class RenderDelegateSV2D_TS *svGroundDelegate;


	ISceneNode* 		m_StichNode[IMG_NUM_LIMIT + 1];
	IMaterial*			m_StichNode_mtl[IMG_NUM_LIMIT + 1];
	IRenderTarget*		m_StichNodeRT[IMG_NUM_LIMIT + 1];
	Int32               m_StichNodeId[IMG_NUM_LIMIT + 1];
    ISceneNode* 		m_StichAreaNode;
    IMaterial*			m_StichArea_mtl;
	IRenderTarget*		m_StichAreaRT;	
	Int32               m_StichAreaNodeId;   
	class RenderDelegateSV2D*	sv2Ddelegate;
	IMaterial*			m_SV2DMtl;

    IMesh*				m_planeMesh;
	INode*				m_SV2Dplane[3*eMeshIndexMax];

	unsigned char m_key_frame_index;
	unsigned char m_init_flag;

    class GlSV2D	*m_SV2DData;

     
     float m_calib[4];
	 float m_transform_step[9];
	 XRMat3 m_transform_matrix;
	 float m_car_rect_on_key[4];
	 float32_t m_track;
	 float32_t m_t[ 9 ];
	 float32_t m_Move_Matrix[ 9 ];
	 XRMat3 m_transform_matrix_gpu;
	 VehicleMotion *m_vehicle_motion;
	 GpuCvPoint2D32f m_Car_rect[4];
	 GpuCvPoint2D32f m_CarPoint_Image[4];
	 float m_adjust_ground_texture[4];
	 
};

#endif //#ifndef __GL_SV_DEMO_H__
