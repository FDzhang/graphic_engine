
#include "AVMData.h"
#include "SVNodeEMirror.h"
#include "SVDelegate.h"
#include "GlSV2D.h"
#include "RenderDelegate/RenderDelegateEMirror.h"
/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;
extern IAnimationManager* am;

/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


extern char c_SV2DVertShaderSrcFileLUT[];   
extern char c_SV2DFragStaticShaderSrcFile[] ;
#if 0
char Left_model_name[]="left_bowl.ofg";
char right_model_name[]="right_bowl.ofg";
char rear_model_name[]="rear_bowl.ofg";
#endif
char Left_model_name[]="emirror_left.ofg";
char right_model_name[]="emirror_right.ofg";
char rear_model_name[]="emirror_rear.ofg";


#define CAMERA_HEIGHT 600
extern char OVERLAPMASK[];
#define MIRROR_MODEL_POS_X  0
#define MIRROR_MODEL_POS_Y  0
#define MIRROR_MODEL_POS_Z  0

#define REAR_LEFT_DOWN_Y   0.05
#define REAR_LEFT_UP_Y       1.0
#define REAR_RIGHT_DOWN_Y      0.0
#define REAR_RIGHT_UP_Y       0.95


#define LEFT_LEFT_DOWN_Y  0.0
#define LEFT_LEFT_UP_Y   1.0
#define LEFT_RIGHT_DOWN_Y   0.0
#define LEFT_RIGHT_UP_Y  1.0


#define RIGHT_LEFT_DOWN_Y  0.0
#define RIGHT_LEFT_UP_Y   1.0
#define RIGHT_RIGHT_DOWN_Y   0.0
#define RIGHT_RIGHT_UP_Y  1.0


#define STICH_LEFT_START_X  -1.0
#define STICH_LEFT_END_X    -0.5
#define STICH_REAR_START_X -0.495
#define STICH_REAR_END_X     0.495
#define STICH_RIGHT_START_X  0.5
#define STICH_RIGHT_END_X   1.0

#define STICH_RIGHT_TEXTURE_TOP_LEFT_X 0.760630
#define STICH_RIGHT_TEXTURE_TOP_LEFT_Y 0.333483
#define STICH_RIGHT_TEXTURE_TOP_RIGHT_X 0.570498
#define STICH_RIGHT_TEXTURE_TOP_RIGHT_Y  0.311045
#define STICH_RIGHT_TEXTURE_BOTTOM_LEFT_X  0.717753
#define STICH_RIGHT_TEXTURE_BOTTOM_LEFT_Y  0.976314
#define STICH_RIGHT_TEXTURE_BOTTOM_RIGHT_X  0.500763
#define STICH_RIGHT_TEXTURE_BOTTOM_RIGHT_Y  0.997069


#define STICH_REAR_TEXTURE_TOP_LEFT_X 0.805469
#define STICH_REAR_TEXTURE_TOP_LEFT_Y 0.0
#define STICH_REAR_TEXTURE_TOP_RIGHT_X 0.242188
#define STICH_REAR_TEXTURE_TOP_RIGHT_Y  0.0
#define STICH_REAR_TEXTURE_BOTTOM_LEFT_X  0.805469
#define STICH_REAR_TEXTURE_BOTTOM_LEFT_Y  1.0
#define STICH_REAR_TEXTURE_BOTTOM_RIGHT_X  0.242188
#define STICH_REAR_TEXTURE_BOTTOM_RIGHT_Y  1.0


#define STICH_LEFT_TEXTURE_TOP_LEFT_X 0.401221
#define STICH_LEFT_TEXTURE_TOP_LEFT_Y 0.210478
#define STICH_LEFT_TEXTURE_TOP_RIGHT_X 0.227075
#define STICH_LEFT_TEXTURE_TOP_RIGHT_Y  0.163742
#define STICH_LEFT_TEXTURE_BOTTOM_LEFT_X  0.415254 
#define STICH_LEFT_TEXTURE_BOTTOM_LEFT_Y  0.867037
#define STICH_LEFT_TEXTURE_BOTTOM_RIGHT_X  0.211197
#define STICH_LEFT_TEXTURE_BOTTOM_RIGHT_Y  0.889512


#define SPEED_CHANGE_GATE_EMIRROR 10
#define SPEED_CHANGE_TIME_GATE_EMIRROR  30

#define LEFT_CAMERA_INDEX  0
#define REAR_CAMERA_INDEX 1
#define RIGHT_CAMERA_INDEX 2

SVNodeEMirror::SVNodeEMirror()
{


	
}
void SVNodeEMirror::InitRearSingleEmirrorNode(unsigned char clear_flag,Region RenderRegion,float scale_size )
{
	IMaterial* pISVmtl;
	IRenderEffect* pIEffect;
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
	AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_MIRROR_VERTEX_SHADER);	
	AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_MIRROR_FRAGMENT_SHADER);	
	INode *pNode;
	Int32 iSize;
	XRVertexLayout data_format;
	float *pVertex;
	int slotid =0;
	float textrue[8] = {1.0,REAR_LEFT_DOWN_Y,0.0,REAR_RIGHT_DOWN_Y,1.0,REAR_LEFT_UP_Y,0.0,REAR_RIGHT_UP_Y};
	float pose[8] ={-1.0,-1.0,1.0,-1.0,-1.0,1.0,1.0,1.0};

	Region *ScennodeAera;
	float f_camera_aspect;

	m_eMirrorSingleNodeId  = g_pIXrCore->CreateRenderNodeScene(0, &m_eMirrorSingleNode);

	if(1 == clear_flag)
	{
	    m_eMirrorSingleNode->SetClearColor(0.0,0.0,0.0,1.0);

    	m_eMirrorSingleNode->SetClear(TRUE, TRUE);
	}
	else
	{
    	m_eMirrorSingleNode->SetClear(FALSE, FALSE);
        
	}
	
	m_eMirrorSingleNode->SetRenderROI(&RenderRegion);
	

	int SVMTL = m_eMirrorSingleNode->CreateMaterial(Material_Custom, &pISVmtl);
	pISVmtl->CreateMaterialEffect(&pIEffect);
	AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(pISVmtl,rear_camera_index); 
	pISVmtl->SetAmbientMap(OVERLAPMASK);
	
		
	AVMData::GetInstance()->m_cam_source->SetCameraSourceMask(pISVmtl->GetAmbientMap()->texid,rear_camera_index); 
	
	pIEffect->InitShaderFromFile("Effect_Emirror", VertexName, FragShaderName, sizeof(SV_PARAM_CB), XR_VERTEX_LAYOUT_PNT, 0);
	pIEffect->SetRenderDelegate(m_render_delegate);

   
	
	int lisenceMeshId = m_eMirrorSingleNode->CreateMesh(ModelType_Plane_Dynamic,2,  2,0, "ground", &m_singleview_mesh);
	int groundId = m_eMirrorSingleNode->CreateModel(0, SVMTL, -1, InsertFlag_Default,0.0,0.0,0.0, 1.0,&pNode);
	
	pNode->SetMesh(lisenceMeshId);
	m_render_delegate->ProcessModel(pNode,"3");
	m_singleview_mesh->LockData(&pVertex,&data_format,&iSize);
	for(int i =0;i<4;i++)
	{
		(pVertex)[slotid+0] = pose[2*i];
		 (pVertex)[slotid+1] = pose[2*i+1]; 
		 (pVertex)[slotid+2] = 0;
		 (pVertex)[slotid+3] = 1;
		 
		 (pVertex)[slotid+6] = textrue[2*i];
		 (pVertex)[slotid+7] = 1.0-textrue[2*i+1]; 

		 

		slotid +=8;
	}
	m_singleview_mesh->UnLockData();
	m_render_delegate->SetChanleId(0);


	ScennodeAera = m_eMirrorSingleNode->GetRenderROI();
	
	f_camera_aspect = (ScennodeAera->right-ScennodeAera->left)/(-ScennodeAera->top+ScennodeAera->bottom);

    f_camera_aspect = 4.5;

	int cameraId = m_eMirrorSingleNode->CreateCamera(m_camera_fov, f_camera_aspect, 4.0f, 12000.0f, &m_Single_Camera);
	//camera->SetOrientation(0, 0, 0);
	m_Single_Camera->SetPosition(0, 100,CAMERA_HEIGHT);
	m_Single_Camera->LookAt(0.0,100.0,0.0);
	
	m_Single_Camera->Set2DCamera(1);
	m_eMirrorSingleNode->SetCamera(cameraId);

	m_eMirrorSingleNode->SetEnable(1);
	
	return ;
}

void SVNodeEMirror::InitEmirrorNode(unsigned char clear_flag,Region RenderRegion,float scale_size )
{
	Region *ScennodeAera;
	float f_camera_aspect;
	m_eMirrorNodeId  = g_pIXrCore->CreateRenderNodeScene(0, &m_eMirrorNode);
	
	if(1 == clear_flag)
	{
	    m_eMirrorNode->SetClearColor(0.0,0.0,0.0,1.0);

    	m_eMirrorNode->SetClear(TRUE, TRUE);
	}
	else
	{
    	m_eMirrorNode->SetClear(FALSE, FALSE);
        
	}

	m_eMirrorNode->SetRenderROI(&RenderRegion);
	


   // 0 --left mirror 1--rear mirror 2 right mirror
	int SVMTL[MIRROR_NODE_MAX];
	int camera_index[MIRROR_NODE_MAX] = {left_camera_index,rear_camera_index,right_camera_index}; 

	IMaterial* pISVmtl;
	IRenderEffect* pIEffect;
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
	AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_MIRROR_VERTEX_SHADER);	
	AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_MIRROR_FRAGMENT_SHADER);	
	
	for(int i =0;i<3;i++)
	{

		SVMTL[i] = m_eMirrorNode->CreateMaterial(Material_Custom, &pISVmtl);
		pISVmtl->CreateMaterialEffect(&pIEffect);
		AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(pISVmtl,camera_index[i]); 
		pISVmtl->SetAmbientMap(OVERLAPMASK);

			
		AVMData::GetInstance()->m_cam_source->SetCameraSourceMask(pISVmtl->GetAmbientMap()->texid,camera_index[i]);	
	
		pIEffect->InitShaderFromFile("Effect_Emirror", VertexName, FragShaderName, sizeof(SV_PARAM_CB), XR_VERTEX_LAYOUT_PNT, 0);
		pIEffect->SetRenderDelegate(m_render_delegate);

		
	}


	

#define SV_Y_POS 0
	int modelId;
	INode* pImdl;
	modelId = m_eMirrorNode->LoadModelFromFile(m_left_model_name,SVMTL[0], -1, InsertFlag_Default, 0, SV_Y_POS, -0, scale_size, &pImdl);

	m_render_delegate->ProcessModel(pImdl, "0");
	m_MirrorNode[0]=pImdl;
	#if 1
	modelId = m_eMirrorNode->LoadModelFromFile(m_rear_model_name ,SVMTL[1], -1, InsertFlag_Default, 0, SV_Y_POS, -0, scale_size, &pImdl);
	m_render_delegate->ProcessModel(pImdl, "1");
	m_MirrorNode[1]=pImdl;

	modelId = m_eMirrorNode->LoadModelFromFile(m_right_model_name ,SVMTL[2], -1, InsertFlag_Default, 0, SV_Y_POS, -0, scale_size, &pImdl);
	m_render_delegate->ProcessModel(pImdl, "2");
	m_MirrorNode[2]=pImdl;
#endif
#if 0
#define CONE_MODE
#ifdef CONE_MODE
//cone model

    for(int i =0;i<3;i++)
    {
        m_MirrorNode[i]->RotateZ(-90);
		
        m_MirrorNode[i]->RotateY(90);
	    m_MirrorNode[i]->SetScale(1.6,1.2,1.0);
    }
	#else
    for(int i =0;i<3;i++)
    {
        m_MirrorNode[i]->RotateZ(90);
		
        m_MirrorNode[i]->RotateY(90);
	    m_MirrorNode[i]->SetScale(2.0,0.7,1.0);
    }	
#endif
#endif
	/////////////////////////////cameraScene////////////////
	ScennodeAera = m_eMirrorNode->GetRenderROI();
	
	f_camera_aspect = (ScennodeAera->right-ScennodeAera->left)/(-ScennodeAera->top+ScennodeAera->bottom);

    f_camera_aspect = 4.5;

	int cameraId = m_eMirrorNode->CreateCamera(m_camera_fov, f_camera_aspect, 4.0f, 12000.0f, &m_Camera);
	//camera->SetOrientation(0, 0, 0);
	m_Camera->SetPosition(0, 100,CAMERA_HEIGHT);
	m_Camera->LookAt(0.0,100.0,0.0);
	
	m_eMirrorNode->SetCamera(cameraId);

	m_eMirrorNode->SetEnable(1);
	m_Camera->Set2DCamera(1);


}
//this is used for unstich no model e-mirror method
void SVNodeEMirror::InitEmirrorUnstichNode(unsigned char clear_flag,Region RenderRegion,float scale_size )
{
	Region *ScennodeAera;
	float f_camera_aspect;
	IMesh *pMeshTemp;
	INode *pNode;
	int slotid =0;
	
	Int32 iSize;
	XRVertexLayout data_format;
	float *pVertex;
	float textrue[8] = {STICH_REAR_TEXTURE_BOTTOM_LEFT_X,STICH_REAR_TEXTURE_BOTTOM_LEFT_Y,STICH_REAR_TEXTURE_BOTTOM_RIGHT_X,STICH_REAR_TEXTURE_BOTTOM_RIGHT_Y,
		STICH_REAR_TEXTURE_TOP_LEFT_X,STICH_REAR_TEXTURE_TOP_LEFT_Y,STICH_REAR_TEXTURE_TOP_RIGHT_X,STICH_REAR_TEXTURE_TOP_RIGHT_Y};
	
	float textrue_left[8] = {STICH_LEFT_TEXTURE_BOTTOM_LEFT_X,STICH_LEFT_TEXTURE_BOTTOM_LEFT_Y,STICH_LEFT_TEXTURE_BOTTOM_RIGHT_X,STICH_LEFT_TEXTURE_BOTTOM_RIGHT_Y,
		STICH_LEFT_TEXTURE_TOP_LEFT_X,STICH_LEFT_TEXTURE_TOP_LEFT_Y,STICH_LEFT_TEXTURE_TOP_RIGHT_X,STICH_LEFT_TEXTURE_TOP_RIGHT_Y};
	
	float textrue_right[8] = {STICH_RIGHT_TEXTURE_BOTTOM_LEFT_X,STICH_RIGHT_TEXTURE_BOTTOM_LEFT_Y,STICH_RIGHT_TEXTURE_BOTTOM_RIGHT_X,STICH_RIGHT_TEXTURE_BOTTOM_RIGHT_Y,
		STICH_RIGHT_TEXTURE_TOP_LEFT_X,STICH_RIGHT_TEXTURE_TOP_LEFT_Y,STICH_RIGHT_TEXTURE_TOP_RIGHT_X,STICH_RIGHT_TEXTURE_TOP_RIGHT_Y};
	
	float pose[8] ={STICH_REAR_START_X,-1.0,STICH_REAR_END_X,-1.0,STICH_REAR_START_X,1.0,STICH_REAR_END_X,1.0};
	
	float pose_left[8] ={STICH_LEFT_START_X,-1.0,STICH_LEFT_END_X,-1.0,STICH_LEFT_START_X,1.0,STICH_LEFT_END_X,1.0};
	float pose_right[8] ={STICH_RIGHT_START_X,-1.0,STICH_RIGHT_END_X,-1.0,STICH_RIGHT_START_X,1.0,STICH_RIGHT_END_X,1.0};
	m_eMirrorNodeId  = g_pIXrCore->CreateRenderNodeScene(0, &m_eMirrorNode);

	float *pTexture[3];
	float *pPose[3];
	pTexture[0]=textrue_left;
	pTexture[1]=textrue;
	pTexture[2]=textrue_right;

	pPose[0]=pose_left;
	pPose[1]=pose;
	pPose[2]=pose_right;

	
	if(1 == clear_flag)
	{
	    m_eMirrorNode->SetClearColor(0.0,0.0,0.0,1.0);

    	m_eMirrorNode->SetClear(TRUE, TRUE);
	}
	else
	{
    	m_eMirrorNode->SetClear(FALSE, FALSE);
        
	}

	m_eMirrorNode->SetRenderROI(&RenderRegion);
	


   // 0 --left mirror 1--rear mirror 2 right mirror
	int SVMTL[MIRROR_NODE_MAX];
	int camera_index[MIRROR_NODE_MAX] = {left_camera_index,rear_camera_index,right_camera_index}; 
	char *ModelName[3] = {"0","1","2"};

	IMaterial* pISVmtl;
	IRenderEffect* pIEffect;
	char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
	AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_MIRROR_VERTEX_SHADER);	
	AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_MIRROR_FRAGMENT_SHADER);	
	
	for(int i =0;i<3;i++)
	{

		SVMTL[i] = m_eMirrorNode->CreateMaterial(Material_Custom, &pISVmtl);
		pISVmtl->CreateMaterialEffect(&pIEffect);
		AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(pISVmtl,camera_index[i]); 
		pISVmtl->SetAmbientMap(OVERLAPMASK);

			
		AVMData::GetInstance()->m_cam_source->SetCameraSourceMask(pISVmtl->GetAmbientMap()->texid,camera_index[i]);	
	
		pIEffect->InitShaderFromFile("Effect_Emirror", VertexName, FragShaderName, sizeof(SV_PARAM_CB), XR_VERTEX_LAYOUT_PNT, 0);
		pIEffect->SetRenderDelegate(m_render_delegate);

    	int lisenceMeshId = m_eMirrorNode->CreateMesh(ModelType_Plane_Dynamic,2,  2,0, "ground", &pMeshTemp);
    	int groundId = m_eMirrorNode->CreateModel(0, SVMTL[i], -1, InsertFlag_Default,0.0,0.0,0.0, 1.0,&pNode);
    	
    	pNode->SetMesh(lisenceMeshId);
    	m_render_delegate->ProcessModel(pNode,ModelName[i]);
    	pMeshTemp->LockData(&pVertex,&data_format,&iSize);
		slotid = 0;
    	for(int j =0;j<4;j++)
    	{
    		(pVertex)[slotid+0] = (pPose[i])[2*j];
    		 (pVertex)[slotid+1] = (pPose[i])[2*j+1]; 
    		 (pVertex)[slotid+2] = 0;
    		 (pVertex)[slotid+3] = 1;
    		 
    		 (pVertex)[slotid+6] = (pTexture[i])[2*j];
    		 (pVertex)[slotid+7] = (pTexture[i])[2*j+1]; 
    
    		 
    
    		slotid +=8;
    	}
    	pMeshTemp->UnLockData();

		
	}


	


	/////////////////////////////cameraScene////////////////
	ScennodeAera = m_eMirrorNode->GetRenderROI();
	
	f_camera_aspect = (ScennodeAera->right-ScennodeAera->left)/(-ScennodeAera->top+ScennodeAera->bottom);

    f_camera_aspect = 4.5;

	int cameraId = m_eMirrorNode->CreateCamera(m_camera_fov, f_camera_aspect, 4.0f, 12000.0f, &m_Camera);
	//camera->SetOrientation(0, 0, 0);
	m_Camera->SetPosition(0, 100,CAMERA_HEIGHT);
	m_Camera->LookAt(0.0,100.0,0.0);
	m_Camera->Set2DCamera(1);
	m_eMirrorNode->SetCamera(cameraId);

	m_eMirrorNode->SetEnable(1);


}

int SVNodeEMirror::Init(unsigned char clear_flag,Region RenderRegion,float scale_size,char *pPath)
{
	IAProperty* rotX=0, *rotY;
	m_camera_fov=100;


	sprintf(m_left_model_name,"%s%s",pPath,Left_model_name);
	sprintf(m_rear_model_name,"%s%s",pPath,rear_model_name);
	sprintf(m_right_model_name,"%s%s",pPath,right_model_name);
	m_render_delegate = new RenderDelegateEMirror();
	
	m_render_delegate->Init();
 //   InitEmirrorUnstichNode(clear_flag,RenderRegion,scale_size);
	InitEmirrorNode(clear_flag,RenderRegion,1);
	am->CreateScrollingAnimation(&scrollX);
	am->CreateScrollingAnimation(&scrollY);
	m_Camera->GetCAProperty(AP_RX, &rotX);
	m_Camera->GetCAProperty(AP_RY, &rotY);
	
	
	scrollX->BindTarget(rotX);
	scrollY->BindTarget(rotY);
	scrollY->DockToValue(4);
	//scrollX->DockToValue(-5);
	InitRearSingleEmirrorNode(clear_flag,RenderRegion,scale_size);


	 return 0;
}

int SVNodeEMirror::SwitchSingleView(int view_index)
{
	float textrue[8] = {1.0,REAR_LEFT_DOWN_Y,0.0,REAR_RIGHT_DOWN_Y,1.0,REAR_LEFT_UP_Y,0.0,REAR_RIGHT_UP_Y};
	
	float textrue_left[8] = {1.0,LEFT_LEFT_DOWN_Y,0.0,LEFT_RIGHT_DOWN_Y,1.0,LEFT_LEFT_UP_Y,0.0,LEFT_RIGHT_UP_Y};
	
	float textrue_right[8] = {1.0,RIGHT_LEFT_DOWN_Y,0.0,RIGHT_RIGHT_DOWN_Y,1.0,RIGHT_LEFT_UP_Y,0.0,RIGHT_RIGHT_UP_Y};
	float pose[8] ={-1.0,-1.0,1.0,-1.0,-1.0,1.0,1.0,1.0};
	Int32 iSize;
	XRVertexLayout data_format;
	float *pVertex;
	int slotid =0;
	float *pTextureCoord;

    if(view_index == left_camera_index)
    {
	    pTextureCoord = textrue_left;
    }
	else if(view_index == right_camera_index)
	{
	    
	    pTextureCoord = textrue_right;
	}
	else
	{
	    pTextureCoord = textrue;
	}
    m_render_delegate->SetChanleId(view_index);

	m_singleview_mesh->LockData(&pVertex,&data_format,&iSize);
	for(int i =0;i<4;i++)
	{
		(pVertex)[slotid+0] = pose[2*i];
		 (pVertex)[slotid+1] = pose[2*i+1]; 
		 (pVertex)[slotid+2] = 0;
		 (pVertex)[slotid+3] = 1;
		 
		 (pVertex)[slotid+6] = pTextureCoord[2*i];
		 (pVertex)[slotid+7] = 1.0-pTextureCoord[2*i+1]; 

		 

		slotid +=8;
	}
	m_singleview_mesh->UnLockData();

	return 0;


}


int SVNodeEMirror::Update(float steering_wheel_angle,float vehicle_speed,unsigned char turn_light,unsigned char gear_state)
{
    static int speed_change_cnt = 0;
	unsigned char speed_flag = 0;
    if(vehicle_speed >= SPEED_CHANGE_GATE_EMIRROR)
    {
         if(speed_change_cnt >= SPEED_CHANGE_TIME_GATE_EMIRROR)
         {
             speed_flag = 1;
         }
		 else
		 {
		     speed_flag = 0;
			 speed_change_cnt ++;
		 }
    }
	else
	{
	    speed_flag=0;
		speed_change_cnt++;
	}


	if(turn_light == TURN_LIGHT_LEFT)
	{
	    m_eMirrorSingleNode->SetEnable(1);
		m_eMirrorNode->SetEnable(0);
		SwitchSingleView(left_camera_index);
	}
	else if (turn_light == TURN_LIGHT_RIGHT)
	{
	    m_eMirrorSingleNode->SetEnable(1);
		m_eMirrorNode->SetEnable(0);
		SwitchSingleView(right_camera_index);
	}
    else
    {

        if(speed_flag == 1)
        {
            m_eMirrorSingleNode->SetEnable(0);
    		m_eMirrorNode->SetEnable(1);
        }
        else
        {
            m_eMirrorSingleNode->SetEnable(1);
    		m_eMirrorNode->SetEnable(0);
			SwitchSingleView(rear_camera_index);

        }
    }

   
	return 0;

}
ICamera* SVNodeEMirror::GetCameraNode()
{
    return m_Camera;
}
void SVNodeEMirror::CameraRollTo(float rotx,float roty)
{
    scrollX->DockToValue(rotx);
	scrollY->DockToValue(roty);
    return;
}
void SVNodeEMirror::CameraRollDelta(float rotx,float roty)
{
    scrollX->DockToDeltaValue(rotx);
	scrollY->DockToDeltaValue(roty);
    return;
}


