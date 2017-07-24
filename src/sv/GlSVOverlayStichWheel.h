#ifndef __GL_SV_OVERLAY_STICH_WHEEL_H__
#define __GL_SV_OVERLAY_STICH_WHEEL_H__

#include "../XrCore/XrSrc/External/XrHeaders.h"
#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "DataStruct.h"


#define FRONT_LEFT_WHEEL 0
#define FRONT_RIGHT_WHEEL 1
#define REAR_LEFT_WHEEL  2
#define REAR_RIGHT_WHEEL 3




class GlSVOverlayStichWheel
{
public:
	GlSVOverlayStichWheel();

	int Init(ISceneNode *pSeneNode,char *pFilePath,vehicle_param in_vehicle_param);
	int InitRectNode(GpuCvPoint2D32f *RectPoint,INode **pNode,ISceneNode *pSeneNode,char *pTextureName,MaterialType MtlType,float **pBuffer);
	int Update(float steering_angle);
	int UpdateRectNode(GpuCvPoint2D32f *RectPoint,INode *pNode,float *pBuffer);
	void CalcWheelCenterPosWld(float *pCenterPoseWld,vehicle_param veh_param);
	void CalcWheelRect(GpuCvPoint2D32f RectPointImg[],float *pPosCenter,vehicle_param veh_param,float wheel_turn_angle);


private:

    char m_stich_wheel_texture[MAX_NAME_LENGTH];
	float m_CenterPoint[8];
	GpuCvPoint2D32f  m_wheel_rect_image[4];
	float *m_pBuffer[4];

	INode *m_pWheelRectNode[4];

	
	vehicle_param m_vehicle_param;


};

#endif //#ifndef __GL_SV_DEMO_H__
