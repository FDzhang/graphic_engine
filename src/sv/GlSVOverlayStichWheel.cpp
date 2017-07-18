
#include "GlSVOverlayStichWheel.h"

#include <math.h>
#include "AVMData.h"



/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

char StichWheelName[MAX_NAME_LENGTH] = "tyre_side.dds";

#define CENTER_ICON_POS_X  0.0
#define CENTER_ICON_POS_Y  -0.1
#define CENTER_ICON_WIDTH_HALF  0.23
#define CENTER_ICON_HEIGHT_HALF 0.23


#define ARROW_ICON_POS_X  0.0
#define ARROW_ICON_POS_Y  0.0
#define ARROR_ICON_WIDTH_HALF  0.2
#define ARROR_ICON_HEIGHT_HALF  0.4


#define SCROLL_WIDTH_HALF  0.2
#define SCROLL_HEIGHT_HALF  0.4





/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


GlSVOverlayStichWheel::GlSVOverlayStichWheel()
{

	
}

int GlSVOverlayStichWheel::Init(ISceneNode *pSeneNode,char *pFilePath,vehicle_param in_vehicle_param)
{


	int tempmaterialid;
	IMaterial *tempcarmtl;
	IMesh *pMeshTemp;
	float *TempBuffer;
	
	
	sprintf(m_stich_wheel_texture,"%s%s",pFilePath,StichWheelName);

	CalcWheelCenterPosWld(m_CenterPoint,in_vehicle_param);

	for(int i =0;i<4;i++)
	{
        CalcWheelRect(&m_wheel_rect_image[0],&m_CenterPoint[2*i],in_vehicle_param,0);	
	    InitRectNode(m_wheel_rect_image,&m_pWheelRectNode[i],pSeneNode,m_stich_wheel_texture,Material_Rigid_Blend,&m_pBuffer[i]);
	}
    

	m_vehicle_param = in_vehicle_param;
	
	return 0;
}

//SAE coordinate system
void GlSVOverlayStichWheel::CalcWheelCenterPosWld(float *pCenterPoseWld,vehicle_param veh_param)
{
	pCenterPoseWld[2*FRONT_LEFT_WHEEL]=veh_param.vehicle_axis_length;	 
	pCenterPoseWld[2*FRONT_LEFT_WHEEL+1]=-veh_param.vehicle_width/2.0+veh_param.vehicle_wheel_width/2.0;
	
	pCenterPoseWld[2*FRONT_RIGHT_WHEEL]=veh_param.vehicle_axis_length;   
	pCenterPoseWld[2*FRONT_RIGHT_WHEEL+1]=veh_param.vehicle_width/2.0-veh_param.vehicle_wheel_width/2.0;
	
	
	pCenterPoseWld[2*REAR_LEFT_WHEEL]=0.0;   
	pCenterPoseWld[2*REAR_LEFT_WHEEL+1]=-veh_param.vehicle_width/2.0+veh_param.vehicle_wheel_width/2.0;  
	
	 pCenterPoseWld[2*REAR_RIGHT_WHEEL]=0.0;	
	 pCenterPoseWld[2*REAR_RIGHT_WHEEL+1]=veh_param.vehicle_width/2.0-veh_param.vehicle_wheel_width/2.0;

    



}


void GlSVOverlayStichWheel::CalcWheelRect(GpuCvPoint2D32f RectPointImg[],float *pPosCenter,vehicle_param veh_param,float wheel_turn_angle)
{
    float pWorld[8];
	GpuCvPoint2D32f RectPointWolrd[4];
	GpuCvPoint2D32f RectPointWldRot[4];

    RectPointWolrd[0].x = pPosCenter[0] - veh_param.vehicle_wheel_radius*cos(wheel_turn_angle)-veh_param.vehicle_wheel_width/2.0*sin(wheel_turn_angle);	
    RectPointWolrd[0].y = pPosCenter[1] - veh_param.vehicle_wheel_width/2.0*cos(wheel_turn_angle)+veh_param.vehicle_wheel_radius*sin(wheel_turn_angle);
    
    RectPointWolrd[1].x = pPosCenter[0] - veh_param.vehicle_wheel_radius*cos(wheel_turn_angle)+veh_param.vehicle_wheel_width/2.0*sin(wheel_turn_angle);	
    RectPointWolrd[1].y = pPosCenter[1] + veh_param.vehicle_wheel_width/2.0*cos(wheel_turn_angle)+veh_param.vehicle_wheel_radius*sin(wheel_turn_angle);
    
    RectPointWolrd[2].x = pPosCenter[0] + veh_param.vehicle_wheel_radius*cos(wheel_turn_angle)-veh_param.vehicle_wheel_width/2.0*sin(wheel_turn_angle);	
    RectPointWolrd[2].y = pPosCenter[1] - veh_param.vehicle_wheel_width/2.0*cos(wheel_turn_angle)-veh_param.vehicle_wheel_radius*sin(wheel_turn_angle);
    
    RectPointWolrd[3].x = pPosCenter[0] + veh_param.vehicle_wheel_radius*cos(wheel_turn_angle)+veh_param.vehicle_wheel_width/2.0*sin(wheel_turn_angle);	
    RectPointWolrd[3].y = pPosCenter[1] + veh_param.vehicle_wheel_width/2.0*cos(wheel_turn_angle)-veh_param.vehicle_wheel_radius*sin(wheel_turn_angle);

	
	
#if 0
    RectPointWolrd[0].x = pPosCenter[0] - veh_param.vehicle_wheel_radius*cos(wheel_turn_angle)+veh_param.vehicle_wheel_width/2.0*;	
    RectPointWolrd[0].y = pPosCenter[1] - veh_param.vehicle_wheel_width/2.0;
	
    RectPointWolrd[1].x = pPosCenter[0] - veh_param.vehicle_wheel_radius;	
    RectPointWolrd[1].y = pPosCenter[1] + veh_param.vehicle_wheel_width/2.0;
	
    RectPointWolrd[2].x = pPosCenter[0] + veh_param.vehicle_wheel_radius;	
    RectPointWolrd[2].y = pPosCenter[1] - veh_param.vehicle_wheel_width/2.0;
	
    RectPointWolrd[3].x = pPosCenter[0] + veh_param.vehicle_wheel_radius;	
    RectPointWolrd[3].y = pPosCenter[1] + veh_param.vehicle_wheel_width/2.0;
	
	if(wheel_turn_angle >= 0.01||wheel_turn_angle <= -0.01)
	{
	    for(int i =0;i<4;i++)
	    {
		    RectPointWldRot[i].x = RectPointWolrd[i].x *cos(wheel_turn_angle)+RectPointWolrd[i].y*sin(wheel_turn_angle);
            RectPointWldRot[i].y = RectPointWolrd[i].y *cos(wheel_turn_angle)-RectPointWolrd[i].x*sin(wheel_turn_angle);	

			RectPointWolrd[i].x = RectPointWldRot[i].x;
			RectPointWolrd[i].y = RectPointWldRot[i].y;
			
	    }

	}
	#endif
	for(int i = 0;i<4;i++)
	{
	    AVMData::GetInstance()->m_2D_lut->CvtPointWorld2Image(RectPointWolrd[i],&RectPointImg[i]);
	}
   
}
	

int GlSVOverlayStichWheel::InitRectNode(GpuCvPoint2D32f *RectPoint,INode **pNode,ISceneNode *pSeneNode,char *pTextureName,MaterialType MtlType,float **pBuffer)
{
    
    int tempmaterialid;
    IMaterial *tempcarmtl;
    IMesh *pMeshTemp;
	Int32 iSize;
	XRVertexLayout data_format;
    int slotid=0;
	float textrue[8] = {0.0,0.0,1.0,0.0,0.0,1.0,1.0,1.0};
    tempmaterialid = pSeneNode->CreateMaterial(MtlType, &tempcarmtl);
   
    tempcarmtl->SetDiffuseMap(pTextureName);
    
   
    
    int lisenceMeshId = pSeneNode->CreateMesh(ModelType_Plane_Dynamic,2,  2,0, "ground", &pMeshTemp);
    int groundId = pSeneNode->CreateModel(0, tempmaterialid, -1, InsertFlag_Default,0.0,0.0,0.0, 1.0,pNode);
    
    (*pNode)->SetMesh(lisenceMeshId);
    pMeshTemp->LockData(pBuffer,&data_format,&iSize);
    for(int i =0;i<4;i++)
    {
        (*pBuffer)[slotid+0] = RectPoint[i].x;
		 (*pBuffer)[slotid+1] = RectPoint[i].y; 
		 (*pBuffer)[slotid+2] = 0;
		 
		 (*pBuffer)[slotid+6] = textrue[2*i];
		 (*pBuffer)[slotid+7] = 1.0-textrue[2*i+1]; 

		 

		slotid +=8;
    }
	pMeshTemp->UnLockData();
	return 0;
}
int GlSVOverlayStichWheel::UpdateRectNode(GpuCvPoint2D32f *RectPoint,INode *pNode,float *pBuffer)
{
    
    int tempmaterialid;
    IMaterial *tempcarmtl;
    IMesh *pMeshTemp;
	Int32 iSize;
	XRVertexLayout data_format;
    int slotid=0;
	float textrue[8] = {0.0,0.0,1.0,0.0,0.0,1.0,1.0,1.0};
    
    pNode->GetMesh(&pMeshTemp);
	
    for(int i =0;i<4;i++)
    {
        (pBuffer)[slotid+0] = RectPoint[i].x;
		 (pBuffer)[slotid+1] = RectPoint[i].y; 
		 (pBuffer)[slotid+2] = 0;
		 
		 (pBuffer)[slotid+6] = textrue[2*i];
		 (pBuffer)[slotid+7] = 1.0-textrue[2*i+1]; 

		 

		slotid +=8;
    }
	pMeshTemp->UnLockData();
	return 0;
}

int GlSVOverlayStichWheel::Update(float steering_angle)
{
    float wheel_turn_angle;
	static float pre_steering_angle=0;
	if(pre_steering_angle != steering_angle)
	{
	    wheel_turn_angle = (steering_angle/m_vehicle_param.max_steering_wheel_angle)*60.0*3.1415926/180.0;

    
	    CalcWheelRect(&m_wheel_rect_image[0],&m_CenterPoint[0],m_vehicle_param,wheel_turn_angle);
		UpdateRectNode(m_wheel_rect_image,m_pWheelRectNode[0],m_pBuffer[0]);
    
     	CalcWheelRect(&m_wheel_rect_image[0],&m_CenterPoint[2],m_vehicle_param,wheel_turn_angle);
     	UpdateRectNode(m_wheel_rect_image,m_pWheelRectNode[1],m_pBuffer[1]);

	}
	pre_steering_angle = steering_angle;
	return 0;
}
