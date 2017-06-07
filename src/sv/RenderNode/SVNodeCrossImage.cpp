
#include "../AVMData.h"
#include "SVNodeCrossImage.h"
#include "../SVDelegate.h"
#include "../GlSV2D.h"
/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

extern IXrCore* g_pIXrCore;
extern IDeviceManager* rm;

/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/


extern char c_SV2DVertShaderSrcFileLUT[];   
extern char c_SV2DFragStaticShaderSrcFile[] ;

#define LEFT_X_END -1.0
#define CENTER_X  0.0
#define RIGHT_X_END 1.0
#define UP_Y_END 1.0
#define CENTER_Y 0.0
#define BOTTOM_Y_END -1.0

#define TEXTURE_LEFT 0.0
#define TEXTURE_RIGHT 1.0
#define TEXTURE_UP  0.0
#define TEXTURE_BOTTOM  1.0 

GLfloat fVerticesCrossSingleView[200]={
	LEFT_X_END,UP_Y_END,1.0,TEXTURE_LEFT,TEXTURE_UP,1.0,0.0,
		CENTER_X,UP_Y_END,1.0,TEXTURE_RIGHT,TEXTURE_UP,1.0,0.0,
		LEFT_X_END,CENTER_Y,1.000000,TEXTURE_LEFT,TEXTURE_BOTTOM,1.0,0.0,
		CENTER_X,CENTER_Y,1.000000,TEXTURE_RIGHT,TEXTURE_BOTTOM,1.0,0.0,
	CENTER_X,UP_Y_END,1.0,TEXTURE_LEFT,TEXTURE_UP,1.0,0.0,
			RIGHT_X_END,UP_Y_END,1.0,TEXTURE_RIGHT,TEXTURE_UP,1.0,0.0,
			CENTER_X,CENTER_Y,1.000000,TEXTURE_LEFT,TEXTURE_BOTTOM,1.0,0.0,
			RIGHT_X_END,CENTER_Y,1.000000,TEXTURE_RIGHT,TEXTURE_BOTTOM,1.0,0.0,
	LEFT_X_END,CENTER_Y,1.0,TEXTURE_LEFT,TEXTURE_UP,1.0,0.0,
		CENTER_X,CENTER_Y,1.0,TEXTURE_RIGHT,TEXTURE_UP,1.0,0.0,
		LEFT_X_END,BOTTOM_Y_END,1.000000,TEXTURE_LEFT,TEXTURE_BOTTOM,1.0,0.0,
		CENTER_X,BOTTOM_Y_END,1.000000,TEXTURE_RIGHT,TEXTURE_BOTTOM,1.0,0.0,
	CENTER_X,CENTER_Y,1.0,TEXTURE_LEFT,TEXTURE_UP,1.0,0.0,
			RIGHT_X_END,CENTER_Y,1.0,TEXTURE_RIGHT,TEXTURE_UP,1.0,0.0,
			CENTER_X,BOTTOM_Y_END,1.000000,TEXTURE_LEFT,TEXTURE_BOTTOM,1.0,0.0,
			RIGHT_X_END,BOTTOM_Y_END,1.000000,TEXTURE_RIGHT,TEXTURE_BOTTOM,1.0,0.0,
 };
unsigned short RectCrossImage[6] = {0,2,1,1,2,3};

SVNodeCrossImage::SVNodeCrossImage()
{


	
}
void SVNodeCrossImage::InitCameraSourceMateril(int SV2DMTL[])
{

    char VertexName[MAX_NAME_LENGTH];
	char FragShaderName[MAX_NAME_LENGTH];
	AVMData::GetInstance()->m_cam_source->GetShaderName(VertexName,SV_2D_VERTEX_SHADER);	
	AVMData::GetInstance()->m_cam_source->GetShaderName(FragShaderName,SV_2D_FRAGMENT_SHADER);
	
	sv2Ddelegate = new RenderDelegateSV2D;
#define Material_MAX 4
	//step 1. prepare for Material ,different camera input image 
	IRenderEffect *pIEffect;
	

	for(int i=0;i<Material_MAX;i++)
	{
		SV2DMTL[i] = m_RenderNode->CreateMaterial(Material_Custom, &m_SV2DMtl);
		m_SV2DMtl->CreateMaterialEffect(&pIEffect);
		
		AVMData::GetInstance()->m_cam_source->SetCameraSourceToMaterial(m_SV2DMtl,i);	

		pIEffect->InitShaderFromFile("Effect_SV2D_cross", VertexName, FragShaderName,	sizeof(SV2D_PARAM_CB), XR_VERTEX_LAYOUT_PTAK, 0);

		pIEffect->SetRenderDelegate(sv2Ddelegate);
	}


}


int SVNodeCrossImage::Init(Region *pRenderRegion)
{

	 Int32 tempmaterialid;	 
	 ICamera*pCamera;
	 INode *pGroundNode;
	 int cameraId;
	 XRVertexLayout  data_format;
	 Int32 icount;
	 int i=0;
	 float *pVertexData;
	 int MtlId[4];
	 char *MeshName[4]={"a","b","c","d"};
	 char ModelName[]={"s"};
	 int meshid[4];
	 int modelId;
	 
	 
	 
	 // create scene Node
	 m_GroundNodeId = g_pIXrCore->CreateRenderNodeScene(0, &m_RenderNode);
	 m_RenderNode->SetRenderROI(pRenderRegion);
	 
	 m_RenderNode->SetClear(true,true);
	 InitCameraSourceMateril(MtlId); 
	 
		   //step 2 prepare mesh for 2D stiching
	 for(int i =0;i<4;i++)
	 {
		 meshid[i] = m_RenderNode->CreateMesh(ModelType_Null, 0,0,0,MeshName[i], &m_pMeshCross[i]);
		 m_pMeshCross[i]->LoadVertexFromArray(&fVerticesCrossSingleView[i*7*4], XR_VERTEX_LAYOUT_PTAK, 4);
	 
		 m_pMeshCross[i]->SetName(ModelName);
		 m_pMeshCross[i]->LoadIndexFromArray(RectCrossImage ,12);
	 
	 
	 
		 modelId = m_RenderNode->CreateModel(0, MtlId[i], -1, InsertFlag_Default, 1, 0, 0, 1, &m_CrossMeshNode[i]);
		 m_CrossMeshNode[i]->SetMesh(meshid[i]);
		 m_CrossMeshNode[i]->SetName(ModelName);	 
		 m_CrossMeshNode[i]->SetTransitionStyle(500, AnimationStyle_EaseOut, AP_SX | AP_SY);
	 
		 
	 }
	 
	 
	 cameraId = m_RenderNode->CreateCamera(120, Float32(XrGetScreenWidth())/XrGetScreenHeight(), 10.0f, 16000.0f, &pCamera);
	 pCamera->Set2DCamera(1);
	 pCamera->SetPosition(0,0,2000);
	 pCamera->LookAt(0.0,1000.0,-0.0);
	 pCamera->RotateAround(0,45);
	 m_RenderNode->SetCamera(cameraId);
	 


	 return 0;
}



int SVNodeCrossImage::SetEnable(unsigned char flag)
{
    m_RenderNode->SetEnable(flag);
	return 0;
}

