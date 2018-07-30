
#include "GlSV2D.h"
#include "AVMData.h"

/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/

#ifdef WIN32
#define _BEVPATH_ "./svres/BEV/"

#else
#define _BEVPATH_ "/opt/svres/BEV/"
#endif

//#define _READ_TXT_FILE
#define _READ_BIN_FILE_

int LoadDataFile(char *pFileName,GLfloat **pContent,int num)
{
    FILE *fp_table;
    fp_table = fopen(pFileName,"r");
    if(fp_table == NULL)
    {
        printf("\r\n can not find file %s",pFileName);
	    return true;
    }
    GLfloat tempUint;
   
    int i;
    *pContent = new GLfloat[num];
	
	// buffer file %s,line %d",__FILE__,__LINE__);
    printf("\r\nstart to read file %s",pFileName);
    for(i = 0;i < num  ;i ++)
    {
 	    fscanf( fp_table , "%f," , &tempUint);       	
		*(*pContent+i) = tempUint;
    }
    printf("\r\n read [%d] over",num);


    if(fp_table != NULL)
    {
        if(fileno(fp_table)>0)
        {     
            printf("\r\n fp_table = %d",fp_table);   
            fclose(fp_table);
         }        
	return 0;
    }	

    return 0;

}




extern GLfloat *pfSrcData[];
extern GLushort *puiIndex[];
extern GLuint uiConfigBin[][eConfigEnd];


#define NUMBER_PER_VERTEX 7

//car image aera


#define CAR_VIEW_LEFT -0.425532
#define CAR_VIEW_FRONT 0.553719
#define CAR_VIEW_RIGHT 0.414894
#define CAR_VIEW_REAR -0.553719
#define RIGHT_VIEW_START_X  (-1.0)
#define RIGHT_VIEW_END_X   (1.0)
#define BOTTOM_HMI_Y   -1.0

#define TOP_HMI_Y    1.0
#define SINGLE_VIEW_BOTTOM_Y  BOTTOM_HMI_Y

#define TOP_LIMIT_Y   1.0


static GLfloat fCarView[]={
	CAR_VIEW_LEFT,CAR_VIEW_FRONT,0.000000,0.0,0.0,1.0,0.0,
		CAR_VIEW_RIGHT,CAR_VIEW_FRONT,0.000000,1.0,0.0,1.0,0.0,
		CAR_VIEW_LEFT,CAR_VIEW_REAR,0.000000,0.0,1.0,1.0,0.0,
		CAR_VIEW_RIGHT,CAR_VIEW_REAR,0.000000,1.0,1.0,1.0,0.0,


    };
unsigned short RectIndex[6] = {0,2,1,1,2,3};
#if 0
GLfloat fVerticesSingleView[]={
	RIGHT_VIEW_START_X,TOP_HMI_Y,0.000000,FRONT_SINGLE_LEFT,FRONT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,0.000000,FRONT_SINGLE_RIGHT,FRONT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_START_X,SINGLE_VIEW_BOTTOM_Y,0.000000,FRONT_SINGLE_LEFT,FRONT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,SINGLE_VIEW_BOTTOM_Y,0.000000,FRONT_SINGLE_RIGHT,FRONT_SINGLE_BOTTOM,1.0,0.0,
	RIGHT_VIEW_START_X,TOP_HMI_Y,0.000000,REAR_SINGLE_LEFT,REAR_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,0.000000,REAR_SINGLE_RIGHT,REAR_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_START_X,SINGLE_VIEW_BOTTOM_Y,0.000000,REAR_SINGLE_LEFT,REAR_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,SINGLE_VIEW_BOTTOM_Y,0.000000,REAR_SINGLE_RIGHT,REAR_SINGLE_BOTTOM,1.0,0.0,
	RIGHT_VIEW_START_X,TOP_HMI_Y,0.000000,LEFT_SINGLE_RIGHT,LEFT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,0.000000,LEFT_SINGLE_RIGHT,LEFT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_START_X,SINGLE_VIEW_BOTTOM_Y,0.000000,LEFT_SINGLE_LEFT,LEFT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,SINGLE_VIEW_BOTTOM_Y,0.000000,LEFT_SINGLE_LEFT,LEFT_SINGLE_BOTTOM,1.0,0.0,
	RIGHT_VIEW_START_X,TOP_HMI_Y,0.000000,RIGHT_SINGLE_RIGHT,RIGHT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,0.000000,RIGHT_SINGLE_RIGHT,RIGHT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_START_X,SINGLE_VIEW_BOTTOM_Y,0.000000,RIGHT_SINGLE_LEFT,RIGHT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,SINGLE_VIEW_BOTTOM_Y,0.000000,RIGHT_SINGLE_LEFT,RIGHT_SINGLE_BOTTOM,1.0,0.0,
	-1.0,1.0,0.000000,FRONT_SINGLE_LEFT,FRONT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,1.0,0.000000,FRONT_SINGLE_RIGHT,FRONT_SINGLE_TOP,1.0,0.0,
		-1.0,-1.0,0.000000,FRONT_SINGLE_LEFT,FRONT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,-1.0,0.000000,FRONT_SINGLE_RIGHT,FRONT_SINGLE_BOTTOM,1.0,0.0, 	
	-1.0,1.0,0.000000,REAR_SINGLE_LEFT,REAR_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,1.0,0.000000,REAR_SINGLE_RIGHT,REAR_SINGLE_TOP,1.0,0.0,
		-1.0,-1.0,0.000000,REAR_SINGLE_LEFT,REAR_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,-1.0,0.000000,REAR_SINGLE_RIGHT,REAR_SINGLE_BOTTOM,1.0,0.0,		
 };
#endif
GLfloat fVerticesSingleView[]={
	RIGHT_VIEW_START_X,TOP_HMI_Y,-1.0,FRONT_SINGLE_LEFT,FRONT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,-1.0,FRONT_SINGLE_RIGHT,FRONT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_START_X,SINGLE_VIEW_BOTTOM_Y,-1.000000,FRONT_SINGLE_LEFT,FRONT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,SINGLE_VIEW_BOTTOM_Y,-1.000000,FRONT_SINGLE_RIGHT,FRONT_SINGLE_BOTTOM,1.0,0.0,
	RIGHT_VIEW_START_X,TOP_HMI_Y,-1.000000,REAR_SINGLE_LEFT,REAR_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,-1.000000,REAR_SINGLE_RIGHT,REAR_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_START_X,SINGLE_VIEW_BOTTOM_Y,-1.000000,REAR_SINGLE_LEFT,REAR_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,SINGLE_VIEW_BOTTOM_Y,-1.000000,REAR_SINGLE_RIGHT,REAR_SINGLE_BOTTOM,1.0,0.0,
	RIGHT_VIEW_START_X,TOP_HMI_Y,-1.000000,LEFT_SINGLE_LEFT,LEFT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,-1.000000,LEFT_SINGLE_RIGHT,LEFT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_START_X,SINGLE_VIEW_BOTTOM_Y,-1.000000,LEFT_SINGLE_LEFT,LEFT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,SINGLE_VIEW_BOTTOM_Y,-1.000000,LEFT_SINGLE_RIGHT,LEFT_SINGLE_BOTTOM,1.0,0.0,
	RIGHT_VIEW_START_X,TOP_HMI_Y,-1.000000,RIGHT_SINGLE_RIGHT,RIGHT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,-1.000000,RIGHT_SINGLE_LEFT,RIGHT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_START_X,SINGLE_VIEW_BOTTOM_Y,-1.000000,RIGHT_SINGLE_RIGHT,RIGHT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,SINGLE_VIEW_BOTTOM_Y,-1.000000,RIGHT_SINGLE_LEFT,RIGHT_SINGLE_TOP,1.0,0.0,
	-0.5,1.0,-1.000000,FRONT_SINGLE_LEFT,FRONT_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,1.0,-1.000000,FRONT_SINGLE_RIGHT,FRONT_SINGLE_TOP,1.0,0.0,
		-0.5,-1.0,-1.000000,FRONT_SINGLE_LEFT,FRONT_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,-1.0,-1.000000,FRONT_SINGLE_RIGHT,FRONT_SINGLE_BOTTOM,1.0,0.0, 	
	-1.0,1.0,-1.000000,REAR_SINGLE_LEFT,REAR_SINGLE_TOP,1.0,0.0,
		RIGHT_VIEW_END_X,1.0,-1.000000,REAR_SINGLE_RIGHT,REAR_SINGLE_TOP,1.0,0.0,
		-1.0,-1.0,-1.000000,REAR_SINGLE_LEFT,REAR_SINGLE_BOTTOM,1.0,0.0,
		RIGHT_VIEW_END_X,-1.0,-1.000000,REAR_SINGLE_RIGHT,REAR_SINGLE_BOTTOM,1.0,0.0,		
 };

GLfloat fTopView[]={
	RIGHT_VIEW_START_X,TOP_LIMIT_Y,0.000000,0.0,0.0,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_LIMIT_Y,0.000000,1.0,0.0,1.0,0.0,
		RIGHT_VIEW_START_X,TOP_HMI_Y,0.000000,0.0,1.0,1.0,0.0,
		RIGHT_VIEW_END_X,TOP_HMI_Y,0.000000,1.0,1.0,1.0,0.0,


    };
GLfloat fBottomView[]={
	RIGHT_VIEW_START_X,BOTTOM_HMI_Y,0.000000,0.0,0.0,1.0,0.0,
		RIGHT_VIEW_END_X,BOTTOM_HMI_Y,0.000000,1.0,0.0,1.0,0.0,
		RIGHT_VIEW_START_X,-1.0,0.000000,0.0,1.0,1.0,0.0,
		RIGHT_VIEW_END_X,-1.0,0.000000,1.0,1.0,1.0,0.0,


    };


typedef enum SvCamTypeTag
{
	CAM_FRONT_LINEAR,
	CAM_REAR_LINEAR,
	CAM_LEFT_LINEAR,
	CAM_RIGHT_LINEAR,

	CAM_FRONT_FISHEYE,
	CAM_REAR_FISHEYE,
	CAM_LEFT_FISHEYE,
	CAM_RIGHT_FISHEYE,

	CAM_TYPE_NUM,
}
SvCamTypeT;


/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/





GlSV2D::GlSV2D()
{
	uiConfig = NULL;
	
	uiConfigAlpha=NULL;
    for(int i=0;i<eMeshIndexMax;i++)
    {
	    m_pfVertexBuff[i] = NULL;
	    m_pucIndexBuff[i] = NULL;
    }

	
}
int GlSV2D::InitLinear()
{
	 GLfloat *pf_car_pose;

	 #ifdef _READ_BIN_FILE_

	 //for(int i=0;i<8;i++)
	 {
		 //AVMData::GetInstance()->m_2D_lut->GetLutData(&m_pfVertexBuff[i],i);
		 //AVMData::GetInstance()->m_2D_lut->GetLutIndex(&m_pucIndexBuff[i],i);
	 

	 }

    AVMData::GetInstance()->m_2D_lut->GetLutConfig(&uiConfig,0);
    AVMData::GetInstance()->m_2D_lut->GetLutConfig(&uiConfigAlpha,1);	 

	 #endif

	// AVMData::GetInstance()->m_2D_lut->GetCarRect(&fCarView[0],rect_left);
	// AVMData::GetInstance()->m_2D_lut->GetCarRect(&fCarView[1],rect_top);
	// AVMData::GetInstance()->m_2D_lut->GetCarRect(&fCarView[7],rect_right);
	// AVMData::GetInstance()->m_2D_lut->GetCarRect(&fCarView[15],rect_bottom);


    //fCarView[8] = fCarView[1];
   // fCarView[14] = fCarView[0];
	//fCarView[21] = fCarView[7];
    //fCarView[22] = fCarView[15];

	 
    //m_pfVertexBuff[eCarImageMesh] = fCarView;
	//for(int i = eFrontSingle; i < eMeshIndexMax; i++)
	//{
	//     m_pfVertexBuff[i]= fVerticesSingleView+28*(i-eFrontSingle);
	//	 
	//	 m_pucIndexBuff[i] = RectIndex;
	//}	 

#if 1

    InitSideViewBuffer(RIGHT_SIDE_VIEW_MESH_WIDTH,RIGHT_SIDE_VIEW_MESH_HEIGHT,
		&m_pfVertexBuff[eLeftSingle],&m_pucIndexBuff[eLeftSingle],
		&m_SideViewVertSize[left_camera_index],&m_SideViewIndexSize[left_camera_index], 1);
	//GenerateSideSingleViewLUT(left_camera_index,m_pfVertexBuff[eLeftSingle]);
	//GenerateCyliSideSingleViewLUT(left_camera_index,m_pfVertexBuff[eLeftSingle]);
	GenerateFishSideSingleViewLUT(left_camera_index,m_pfVertexBuff[eLeftSingle]);
	InitSideViewBuffer(RIGHT_SIDE_VIEW_MESH_WIDTH,RIGHT_SIDE_VIEW_MESH_HEIGHT,
	&m_pfVertexBuff[eRightSingle],&m_pucIndexBuff[eRightSingle],
		&m_SideViewVertSize[right_camera_index],&m_SideViewIndexSize[right_camera_index]);

	m_pucIndexBuff[eRightSingle] = m_pucIndexBuff[eLeftSingle];
	m_SideViewIndexSize[right_camera_index] = m_SideViewIndexSize[left_camera_index];
	
	//GenerateSideSingleViewLUT(right_camera_index,m_pfVertexBuff[eRightSingle]);
	//GenerateCyliSideSingleViewLUT(right_camera_index,m_pfVertexBuff[eRightSingle]);
	GenerateFishSideSingleViewLUT(right_camera_index,m_pfVertexBuff[eRightSingle]);


	InitFrontRearViewBuffer(FRONT_CLC_VIEW_MESH_WIDTH,FRONT_CLC_VIEW_MESH_HEIGHT,
		&m_pfVertexBuff[eFrontSingle],&m_pucIndexBuff[eFrontSingle],
		&m_SideViewVertSize[front_camera_index],&m_SideViewIndexSize[front_camera_index]);
    InitFrontRearViewBuffer(REAR_CLC_VIEW_MESH_WIDTH,REAR_CLC_VIEW_MESH_HEIGHT,
		&m_pfVertexBuff[eRearSingle],&m_pucIndexBuff[eRearSingle],
		&m_SideViewVertSize[rear_camera_index],&m_SideViewIndexSize[rear_camera_index]);

	//GenerateSideSingleViewLUT(right_camera_index,m_pfVertexBuff[eRightSingle]);
	
	GenerateFrontRearSingleViewLUT(front_camera_index,m_pfVertexBuff[eFrontSingle]);
	GenerateFrontRearSingleViewLUT(rear_camera_index,m_pfVertexBuff[eRearSingle]);

#else
	int ret = 0;	
	ret = InitFrontRearSingleViewCamLUT(front_camera_index);
	ret = InitFrontRearSingleViewCamLUT(rear_camera_index);

	ret = InitSideViewParams(&m_pfVertexBuff[eLeftSingle], &m_pucIndexBuff[eLeftSingle], left_camera_index);
	ret = InitSideViewParams(&m_pfVertexBuff[eRightSingle], &m_pucIndexBuff[eRightSingle], right_camera_index);
	ret = InitSideViewParams(&m_pfVertexBuff[eFrontSingle], &m_pucIndexBuff[eFrontSingle], front_camera_index);
	ret = InitSideViewParams(&m_pfVertexBuff[eRearSingle], &m_pucIndexBuff[eRearSingle], rear_camera_index);

#endif
	//m_pucIndexBuff[eCarImageMesh] = RectIndex;
	//m_pucIndexBuff[eRightBottomMesh] = RectIndex;

	m_camType = CAM_LEFT_LINEAR;
	return 0;
}

int GlSV2D::Init()
{
    GLfloat *pf_car_pose;

	 #ifdef _READ_BIN_FILE_

	 for(int i=0;i<8;i++)
	 {
		 AVMData::GetInstance()->m_2D_lut->GetLutData(&m_pfVertexBuff[i],i);
		 AVMData::GetInstance()->m_2D_lut->GetLutIndex(&m_pucIndexBuff[i],i);
	 

	 }

    AVMData::GetInstance()->m_2D_lut->GetLutConfig(&uiConfig,0);
    AVMData::GetInstance()->m_2D_lut->GetLutConfig(&uiConfigAlpha,1);	 

	 #endif

	 AVMData::GetInstance()->m_2D_lut->GetCarRect(&fCarView[0],rect_left);
	 AVMData::GetInstance()->m_2D_lut->GetCarRect(&fCarView[1],rect_top);
	 AVMData::GetInstance()->m_2D_lut->GetCarRect(&fCarView[7],rect_right);
	 AVMData::GetInstance()->m_2D_lut->GetCarRect(&fCarView[15],rect_bottom);


    fCarView[8] = fCarView[1];
    fCarView[14] = fCarView[0];
	fCarView[21] = fCarView[7];
    fCarView[22] = fCarView[15];

	 
	//m_pfVertexBuff[eSingleViewMesh] = fVerticesSingleView;
    m_pfVertexBuff[eCarImageMesh] = fCarView;
	for(int i=eFrontSingle;i<eMeshIndexMax;i++)
	{
	     m_pfVertexBuff[i]= fVerticesSingleView+28*(i-eFrontSingle);
		 
		 m_pucIndexBuff[i] = RectIndex;
	}	
//	m_pfVertexBuff[eRightBottomMesh] = fBottomView;
	m_pucIndexBuff[eCarImageMesh] = RectIndex;
	//m_pucIndexBuff[eRightBottomMesh] = RectIndex;

	m_camType = CAM_LEFT_FISHEYE;

	
	return 0;
}


int GlSV2D::Update(void)
{
	return 0;
}

int GlSV2D::GetVertexBuffer(int Index,float **pVertexBuffer, unsigned int *BufSize)
{
	  *pVertexBuffer= m_pfVertexBuff[Index];
	 
	 if(Index <= eRightMesh)
	 {
		 *BufSize = uiConfig[Index*2+1];
	 
	 }
	 else if(Index <= eRearRightMesh)
	 {
		 *BufSize = uiConfigAlpha[(Index-eFrontLeftMesh)*2+1];
	 
	 }
	 else if(Index == eCarImageMesh)
	 {
		 *BufSize = 4;
	 }
	 else
	 {
		 if(m_camType >= CAM_FRONT_FISHEYE && m_camType <= CAM_RIGHT_FISHEYE )
		 {
			 *BufSize = 4;
		 }
		 else
		 {
			 *BufSize =m_SideViewVertSize[Index-eFrontSingle];
		 }
	 }

	return 0;
}
int GlSV2D::GetIndexBuffer(int Index,GLushort **pIndexBuffer, unsigned int *BufSize)
{
    *pIndexBuffer = m_pucIndexBuff[Index];
	if(Index <= eRightMesh)
	{
	    *BufSize = uiConfig[Index*2+2];
	
	}
	else  if(Index <= eRearRightMesh)
	{
	    *BufSize = uiConfigAlpha[(Index-eFrontLeftMesh)*2+2];
	
	}
	else if(Index == eCarImageMesh)
	{
		 *BufSize = 6;
	}
	else
	{
	
		if(m_camType >= CAM_FRONT_FISHEYE && m_camType <= CAM_RIGHT_FISHEYE )
		{
			*BufSize = 6;
		}
		else
		{
				*BufSize = m_SideViewIndexSize[Index-eFrontSingle];
		}
	}

	return 0;
}

extern "C" FLT_T Cam_Lut_Linear[];
//for side single view undistortion and turn function
int GlSV2D::InitSideViewBuffer(int width,int height,GLfloat **pData,GLushort **pIndex,unsigned int *puiVertSize,unsigned int *puiIndexSize, unsigned char index_flag)
{
	GLushort *pIndexTemp;
	float Rot[3]={-1.57,0,0};
	*pData = (GLfloat*)malloc(width*height*7*4);
	int x, y;
	//*pIndex = (GLushort*)malloc((width-1)*(height-1)*6*2);
	*puiIndexSize = (width-1)*(height-1)*6;
	*puiVertSize = width*height;

	if(index_flag == 1)
	{
		int slotId=0;
		*pIndex = (GLushort*)malloc((width-1)*(height-1)*6*2);
		pIndexTemp = *pIndex;

	for (y=0; y<width-1; y++) {
		for (x=0; x<height-1; x++) {

			pIndexTemp[slotId] = y*width + x;
			pIndexTemp[slotId + 1] = y*width + x + 1;
			pIndexTemp[slotId + 2] = (y + 1)*width + x;
			pIndexTemp[slotId + 3] = y*width + x + 1;
			pIndexTemp[slotId + 4] = (y + 1)*width + x + 1;
			pIndexTemp[slotId + 5] = (y + 1)*width + x;

				slotId+=6;

			}
		}

		if(slotId == *puiIndexSize)
		{
		    printf("\r\n succeed in size check");
		}
	}

	return 0;

	
}

int GlSV2D::InitFrontRearViewBuffer(int width,int height,GLfloat **pData,GLushort **pIndex,unsigned int *puiVertSize,unsigned int *puiIndexSize)
{
	GLushort *pIndexTemp;
	float Rot[3]={-1.57,0,0};
	*pData = (GLfloat*)malloc(width*height*7*4);
	int x, y;
	*pIndex = (GLushort*)malloc((width-1)*(height-1)*6*2);
	*puiIndexSize = (width-1)*(height-1)*6;
	*puiVertSize = width*height;
	
	int slotId=0;
	pIndexTemp = *pIndex;

	for (y=0; y<width-1; y++) {
		for (x=0; x<height-1; x++) {

			pIndexTemp[slotId] = y*width + x;
			pIndexTemp[slotId + 1] = y*width + x + 1;
			pIndexTemp[slotId + 2] = (y + 1)*width + x;
			pIndexTemp[slotId + 3] = y*width + x + 1;
			pIndexTemp[slotId + 4] = (y + 1)*width + x + 1;
			pIndexTemp[slotId + 5] = (y + 1)*width + x;

			slotId+=6;

		}
	}

    if(slotId == *puiIndexSize)
    {
        printf("\r\n succeed in size check");
    }

	return 0;

	
}

#define CAMERA_NUM 2
#define IMAGE_WIDTH 1280    //?�����䨪??��
#define IMAGE_HEIGHT 720    //?�����䨪???
#define LINE_WIDTH 4        //��|?��???��
#define LINE_BRIGHTNESS 30       //��|?��??����?��
#define IMAGE_CENTER_RATIO_W 2     //3?��??��?�����䨪??DD?????
#define IMAGE_CENTER_RATIO_H 1.2   //3?��??��?�����䨪??DD?????

int GlSV2D::GenerateFrontRearSingleViewLUT(int camera_index,float *pVert)
{
    Cam_Model *pRealCam;
	int vertex_num;
    float prsource[3];
	float ptsource[3];
    int config[7]={FRONT_CLC_VIEW_ROI_START_X,
		FRONT_CLC_VIEW_ROI_START_Y,
		FRONT_CLC_VIEW_ROI_END_X,
		FRONT_CLC_VIEW_ROI_END_Y,
		FRONT_CLC_VIEW_MESH_WIDTH, 
		FRONT_CLC_VIEW_MESH_HEIGHT,0};
	float roll = CLC_CAM_PITCH;
	AVMData::GetInstance()->m_exParam->GetCameraPos(ptsource,camera_index);	
	AVMData::GetInstance()->m_exParam->GetCameraAngle(prsource,camera_index);
	Log_Debug("------hch: FrontRear camera_index = %d,ptsource = %f, %f, %f",camera_index,ptsource[0],ptsource[1],ptsource[2]);
	Log_Debug("------hch: FrontRear camera_index = %d,prsource = %f, %f, %f",camera_index,prsource[0],prsource[1],prsource[2]);
	/*if(camera_index == 0)
	{
		ptsource[0] = 3754.837402;
		ptsource[1] = 12.166937;
		ptsource[2] = -780.820374;
		prsource[0] = -2.022081;
		prsource[1] = 3.138451;
		prsource[2] = -1.594613;
	}
	else if(camera_index == 1)
	{
		ptsource[0] = -987.406677;
		ptsource[1] = 35.075394;
		ptsource[2] = -1080.743896;
		prsource[0] = 0.845056;
		prsource[1] = -0.027668;
		prsource[2] = -1.580048;
	}*/
	
	if (prsource[0] < 0)
	{		
		prsource[0] = -(prsource[0] / fabs(prsource[0]))*fabs(fabs(prsource[0]) - PI);
		prsource[1] = (prsource[1] / fabs(prsource[1]))*fabs(fabs(prsource[1]) - PI);
		prsource[2] = -(prsource[2] / fabs(prsource[2]))*fabs(fabs(prsource[2]) - PI);
	}
	
    pRealCam = AVMData::GetInstance()->m_camInstrinct->GetFullCameraModel(camera_index,prsource,ptsource);

	Cam_Model_Intrinsic* matrix = new Cam_Model_Intrinsic;
	AVMData::GetInstance()->m_camInstrinct->GetCameraInstrinct(&matrix,camera_index);
	
	float cv = IMAGE_HEIGHT - (matrix->cv - matrix->fv * tan(PI / 2 - prsource[0]));
	//IMAGE_HEIGHT/IMAGE_CENTER_RATIO_H
	m_cam_clc[camera_index] = new Cam_Model_Cyli;
    if(camera_index == rear_camera_index)
		roll = REAR_CLC_CAM_PITCH;
	Cam_Init_Cyli(m_cam_clc[camera_index],
		IMAGE_WIDTH,IMAGE_HEIGHT,
		IMAGE_WIDTH/IMAGE_CENTER_RATIO_W,cv,
		prsource[0],prsource[1],0);
	
	AVMData::GetInstance()->m_camInstrinct->SetUndistCyliCameraModel(camera_index,m_cam_clc[camera_index]);
    if(camera_index == rear_camera_index)
    {
        config[0] = REAR_CLC_VIEW_ROI_END_X;
		config[1] = REAR_CLC_VIEW_ROI_START_Y;
		config[2] = REAR_CLC_VIEW_ROI_START_X;
		config[3] = REAR_CLC_VIEW_ROI_END_Y;
		config[6] =1 ;
		
    }
	
	AVMData::GetInstance()->m_camInstrinct->SetUndistCamROI(camera_index,config[0],config[1],config[2],config[3]);
	Cam_MapImage_Fish2Cyli_GenerateGPULUT(
		pRealCam, 
		m_cam_clc[camera_index],
		config[0],
		config[1],
		config[2],
		config[3],
		config[4], 
		config[5],
		config[6],
		&vertex_num,
		pVert);

	return 0;


}

int GlSV2D::InitFrontRearSingleViewCamLUT(int camera_index)
{
    Cam_Model *pRealCam;
	int vertex_num;
    float prsource[3];
	float ptsource[3];
    int config[7]={FRONT_CLC_VIEW_ROI_START_X,
		FRONT_CLC_VIEW_ROI_START_Y,
		FRONT_CLC_VIEW_ROI_END_X,
		FRONT_CLC_VIEW_ROI_END_Y,
		FRONT_CLC_VIEW_MESH_WIDTH, 
		FRONT_CLC_VIEW_MESH_HEIGHT,0};
	float roll = CLC_CAM_PITCH;
	AVMData::GetInstance()->m_exParam->GetCameraPos(ptsource,camera_index);	
	AVMData::GetInstance()->m_exParam->GetCameraAngle(prsource,camera_index);
    pRealCam = AVMData::GetInstance()->m_camInstrinct->GetFullCameraModel(camera_index,prsource,ptsource);

	m_cam_clc[camera_index] = new Cam_Model_Cyli;
    if(camera_index == rear_camera_index)
		roll = REAR_CLC_CAM_PITCH;
	Cam_Init_Cyli(m_cam_clc[camera_index],
		CLC_CAM_WIDTH,CLC_CAM_HEIGHT,
		CLC_CAM_CX,CLC_CAM_CY,
		roll*deg2rad,CLC_CAM_ROLL*deg2rad,CLC_CAM_YAW*deg2rad);
	AVMData::GetInstance()->m_camInstrinct->SetUndistCyliCameraModel(camera_index,m_cam_clc[camera_index]);
    if(camera_index == rear_camera_index)
    {
        config[0] = REAR_CLC_VIEW_ROI_START_X;
		config[1] = REAR_CLC_VIEW_ROI_START_Y;
		config[2] = REAR_CLC_VIEW_ROI_END_X;
		config[3] = REAR_CLC_VIEW_ROI_END_Y;
		config[6] =1 ;
		
    }
	AVMData::GetInstance()->m_camInstrinct->SetUndistCamROI(camera_index,config[0],config[1],config[2],config[3]);


	return 0;


}
void normalize_angles(float angles[3])
{
  for(int i = 0; i < 3; i++)
  {
    if(angles[i]>3.1415926/2)
      angles[i] = angles[i]-3.1415926;
    else if(angles[i]<-3.1415926/2)
      angles[i] = 3.1415926+angles[i];
  }
}
int GlSV2D::GenerateSideSingleViewLUT(int camera_index,float *pVert)
{
    Cam_Model *pRealCam;
    float view_angle = 90.0;
	int vertex_num;
    float pR[3]={RIGHT_LINEAR_CAM_R_X,RIGHT_LINEAR_CAM_R_Y,RIGHT_LINEAR_CAM_R_Z};
	float pT[3] = {RIGHT_LINEAR_CAM_T_X,RIGHT_LINEAR_CAM_T_Y,RIGHT_LINEAR_CAM_T_Z};
    float prsource[3];
	float ptsource[3];
    int config[6]={RIGHT_SIDE_VIEW_ROI_START_X,
		RIGHT_SIDE_VIEW_ROI_START_Y,
		RIGHT_SIDE_VIEW_ROI_END_X,
		RIGHT_SIDE_VIEW_ROI_END_Y,
		RIGHT_SIDE_VIEW_MESH_WIDTH, 
		RIGHT_SIDE_VIEW_MESH_HEIGHT};
	AVMData::GetInstance()->m_exParam->GetCameraPos(ptsource,camera_index);	
	AVMData::GetInstance()->m_exParam->GetCameraAngle(prsource,camera_index);
	Log_Debug("------hch: Side camera_index = %d,ptsource = %f, %f, %f",camera_index,ptsource[0],ptsource[1],ptsource[2]);
	Log_Debug("------hch: Side camera_index = %d,prsource = %f, %f, %f",camera_index,prsource[0],prsource[1],prsource[2]);
	/*if(camera_index == 2)
	{
		ptsource[0] = 1855.828491;
		ptsource[1] = -1061.214722;
		ptsource[2] = -1204.462158;
		prsource[0] = 0.806223;
		prsource[1] = -0.041962;
		prsource[2] = 0.004450;
	}
	else if(camera_index == 3)
	{
		ptsource[0] = 1852.984131;
		ptsource[1] = 1034.933716;
		ptsource[2] = -1229.751099;
		prsource[0] = -2.313069;
		prsource[1] = -3.136924;
		prsource[2] = -0.002362;
	}*/
    pRealCam = AVMData::GetInstance()->m_camInstrinct->GetFullCameraModel(camera_index,prsource,ptsource);
	m_cam_linear[camera_index] = new Cam_Model;

	normalize_angles(prsource);
	Cam_Init(m_cam_linear[camera_index], 
		LINEAR_CAMERA_WIDTH,LINEAR_CAMERA_HEIGHT,
		LINEAR_CAMERA_WIDTH/2, LINEAR_CAMERA_HEIGHT/2, 
		LINEAR_CAMERA_SKEW_C, LINEAR_CAMERA_SKEW_D, LINEAR_CAMERA_SKER_E, 
		Cam_Lut_Linear,
		LINEAR_CAMERA_HFOV*deg2rad, 
		LINEAR_CAMERA_VFOV*deg2rad, 
		true, 
		prsource, 
		ptsource
		);
		
	FLT_T a[3]={RIGHT_LINEAR_CAM_ROT_X*deg2rad, RIGHT_LINEAR_CAM_ROT_Y*deg2rad, RIGHT_LINEAR_CAM_ROT_Z*deg2rad};
    //FLT_T a[3] = {-pR[0], view_angle * deg2rad - pR[1], -pR[2]};
    int deltaX = 0;
	float deltaY = 3.4;
	float deltaZ = 2.7;
	if(camera_index == left_camera_index)
    {
        config[0] = LEFT_SIDE_VIEW_ROI_START_X;
		config[1] = LEFT_SIDE_VIEW_ROI_START_Y;
		config[2] = LEFT_SIDE_VIEW_ROI_END_X;
		config[3] = LEFT_SIDE_VIEW_ROI_END_Y;
		a[0] = -prsource[0]- deltaX * 3.14159 / 180.f;
		a[1] = -view_angle*deg2rad + prsource[1] - deltaY * 3.14159 / 180.f;
		a[2] = -prsource[2] - deltaZ * 3.14159 / 180.f;;	
		
    }
	else 
	{
		 a[0] = -prsource[0]- deltaX * 3.14159 / 180.f;
		 a[1] = view_angle*deg2rad - prsource[1] - deltaY * 3.14159 / 180.f;
		 a[2] = -prsource[2] - deltaZ * 3.14159 / 180.f;	
	}
	
	m_linear_cam[camera_index][0]=a[0];
	m_linear_cam[camera_index][1]=a[1];
	m_linear_cam[camera_index][2]=a[2];

	Cam_UpdateViewRotation(m_cam_linear[camera_index], a);
	AVMData::GetInstance()->m_camInstrinct->SetUndistLinearCameraModel(camera_index,m_cam_linear[camera_index]);
	AVMData::GetInstance()->m_camInstrinct->SetLinearCamROI(camera_index,config[0],config[1],config[2],config[3]);

	Cam_MapImage_GenerateGPULUT(
		pRealCam, 
		m_cam_linear[camera_index],
		config[0],
		config[1],
		config[2],
		config[3],
		config[4], 
		config[5],
		&vertex_num,
		pVert);

	return 0;


}
int GlSV2D::GenerateCyliSideSingleViewLUT(int camera_index,float *pVert)
{
    Cam_Model *pRealCam;
    float view_angle = 90.0;
	int vertex_num;
    float pR[3]={RIGHT_LINEAR_CAM_R_X,RIGHT_LINEAR_CAM_R_Y,RIGHT_LINEAR_CAM_R_Z};
	float pT[3] = {RIGHT_LINEAR_CAM_T_X,RIGHT_LINEAR_CAM_T_Y,RIGHT_LINEAR_CAM_T_Z};
    float prsource[3];
	float ptsource[3];
    int config[6]={RIGHT_SIDE_VIEW_ROI_START_X,
		RIGHT_SIDE_VIEW_ROI_START_Y,
		RIGHT_SIDE_VIEW_ROI_END_X,
		RIGHT_SIDE_VIEW_ROI_END_Y,
		RIGHT_SIDE_VIEW_MESH_WIDTH, 
		RIGHT_SIDE_VIEW_MESH_HEIGHT};
	AVMData::GetInstance()->m_exParam->GetCameraPos(ptsource,camera_index);	
	AVMData::GetInstance()->m_exParam->GetCameraAngle(prsource,camera_index);

    pRealCam = AVMData::GetInstance()->m_camInstrinct->GetFullCameraModel(camera_index,prsource,ptsource);
	m_cam_clc_side[camera_index] = new Cam_Model_Cyli;
	
	normalize_angles(prsource);
	_Cam_Init_Cyli(m_cam_clc_side[camera_index], 
		LINEAR_CAMERA_WIDTH,LINEAR_CAMERA_HEIGHT,
		LINEAR_CAMERA_WIDTH/2, LINEAR_CAMERA_HEIGHT/2, 
		prsource,
		ptsource,
		prsource[0],0,0
		);
	FLT_T a[3]={RIGHT_LINEAR_CAM_ROT_X*deg2rad, RIGHT_LINEAR_CAM_ROT_Y*deg2rad, RIGHT_LINEAR_CAM_ROT_Z*deg2rad};
    //FLT_T a[3] = {-pR[0], view_angle * deg2rad - pR[1], -pR[2]};
	int deltaX = 0;
	float deltaY = 3.4;
	float deltaZ = 0.0;
    if(camera_index == left_camera_index)
    {
        config[0] = LEFT_SIDE_VIEW_ROI_START_X;
		config[1] = LEFT_SIDE_VIEW_ROI_START_Y;
		config[2] = LEFT_SIDE_VIEW_ROI_END_X;
		config[3] = LEFT_SIDE_VIEW_ROI_END_Y;
	
		a[0] = 0;
		a[1] = 0;
		a[2] = -view_angle*deg2rad - deltaZ * 3.14159 / 180.f;
		m_cam_clc_side[camera_index]->cam_int.offSetX = 0;
		m_cam_clc_side[camera_index]->cam_int.offSetY = 0;
	
    }
	else 
	{
		a[0] = 0;
		a[1] = 0;
		a[2] = view_angle*deg2rad - deltaZ * 3.14159 / 180.f;
		m_cam_clc_side[camera_index]->cam_int.offSetX = 0;
		m_cam_clc_side[camera_index]->cam_int.offSetY = 0;

	}

	_Cam_UpdateViewRotation(m_cam_clc_side[camera_index], a);

	AVMData::GetInstance()->m_camInstrinct->SetUndistCyliCameraModel(camera_index,m_cam_clc_side[camera_index]);
	AVMData::GetInstance()->m_camInstrinct->SetUndistCamROI(camera_index,config[0],config[1],config[2],config[3]);

	Cam_MapImage_Fish2Cyli_GenerateGPULUT(
		pRealCam, 
		m_cam_clc_side[camera_index],
		config[0],
		config[1],
		config[2],
		config[3],
		config[4], 
		config[5],
		config[6],
		&vertex_num,
		pVert);

	return 0;

}
int GlSV2D::GenerateFishSideSingleViewLUT(int camera_index,float *pVert)
{
    Cam_Model *pRealCam;
    float view_angle = 90.0;
	int vertex_num;
    float pR[3]={RIGHT_LINEAR_CAM_R_X,RIGHT_LINEAR_CAM_R_Y,RIGHT_LINEAR_CAM_R_Z};
	float pT[3] = {RIGHT_LINEAR_CAM_T_X,RIGHT_LINEAR_CAM_T_Y,RIGHT_LINEAR_CAM_T_Z};
    float prsource[3];
	float ptsource[3];
    int config[6]={RIGHT_SIDE_VIEW_ROI_START_X,
		RIGHT_SIDE_VIEW_ROI_START_Y,
		RIGHT_SIDE_VIEW_ROI_END_X,
		RIGHT_SIDE_VIEW_ROI_END_Y,
		RIGHT_SIDE_VIEW_MESH_WIDTH, 
		RIGHT_SIDE_VIEW_MESH_HEIGHT};
	AVMData::GetInstance()->m_exParam->GetCameraPos(ptsource,camera_index);	
	AVMData::GetInstance()->m_exParam->GetCameraAngle(prsource,camera_index);

    pRealCam = AVMData::GetInstance()->m_camInstrinct->GetFullCameraModel(camera_index,prsource,ptsource);
	m_cam_fish_side[camera_index] = new Cam_Model;
	
	normalize_angles(prsource);
	Cam_Init(m_cam_fish_side[camera_index], 
		LINEAR_CAMERA_WIDTH,LINEAR_CAMERA_HEIGHT,
		LINEAR_CAMERA_WIDTH/2, LINEAR_CAMERA_HEIGHT/2, 
		1,0,0,
		pRealCam->cam_int.lut,
		90*deg2rad,70*deg2rad,
		1,
		pRealCam->cam_ext.pose_r,
		pRealCam->cam_ext.pose_t
		);

	FLT_T a[3]={RIGHT_LINEAR_CAM_ROT_X*deg2rad, RIGHT_LINEAR_CAM_ROT_Y*deg2rad, RIGHT_LINEAR_CAM_ROT_Z*deg2rad};
    //FLT_T a[3] = {-pR[0], view_angle * deg2rad - pR[1], -pR[2]};
	int deltaX = 0;
	float deltaY = 3.4;
	float deltaZ = 0.0;
    if(camera_index == left_camera_index)
    {
        config[0] = LEFT_SIDE_VIEW_ROI_START_X;
		config[1] = LEFT_SIDE_VIEW_ROI_START_Y;
		config[2] = LEFT_SIDE_VIEW_ROI_END_X;
		config[3] = LEFT_SIDE_VIEW_ROI_END_Y;
	
		a[0] = -pRealCam->cam_ext.pose_r[0];
		a[1] = view_angle*deg2rad + pRealCam->cam_ext.pose_r[1];
		a[2] = -pRealCam->cam_ext.pose_r[2];
    }
	else 
	{
		a[0] = -pRealCam->cam_ext.pose_r[0];
		a[1] = -view_angle*deg2rad - pRealCam->cam_ext.pose_r[1];
		a[2] = 180*deg2rad-pRealCam->cam_ext.pose_r[2];
	}

	Cam_UpdateViewRotation(m_cam_fish_side[camera_index], a);

	AVMData::GetInstance()->m_camInstrinct->SetUndistCyliCameraModel(camera_index,m_cam_clc_side[camera_index]);
	AVMData::GetInstance()->m_camInstrinct->SetUndistCamROI(camera_index,config[0],config[1],config[2],config[3]);

	Cam_MapImage_GenerateGPULUT(
		pRealCam, 
		m_cam_fish_side[camera_index],
		config[0],
		config[1],
		config[2],
		config[3],
		config[4], 
		config[5],
		&vertex_num,
		pVert);

	return 0;

}
void GlSV2D::AdjustSideSingleViewLUT(int camera_index,unsigned char adjust_port,unsigned char adjust_direct)
{
	FLT_T a[3]={0*deg2rad, 0*deg2rad, 0*deg2rad};
    float pR[3]={RIGHT_LINEAR_CAM_R_X,RIGHT_LINEAR_CAM_R_Y,RIGHT_LINEAR_CAM_R_Z};
	float pT[3] = {RIGHT_LINEAR_CAM_T_X,RIGHT_LINEAR_CAM_T_Y,RIGHT_LINEAR_CAM_T_Z};
	float prsource[3];
	float ptsource[3];
	Cam_Model *pRealCam = AVMData::GetInstance()->m_camInstrinct->GetFullCameraModel(camera_index,prsource,ptsource);
    int vertex_num;
    float *pVert;

	if(camera_index == right_camera_index)
	{
	     pVert=m_pfVertexBuff[eRightSingle];
		 	
	}
	else
	{
	
	    pVert=m_pfVertexBuff[eLeftSingle];
	}
    if(adjust_port >=POS_X_ADJ)
    {
    
    	Cam_Init(m_cam_linear[camera_index], 
    		LINEAR_CAMERA_WIDTH,LINEAR_CAMERA_HEIGHT,
    		LINEAR_CAMERA_CX, LINEAR_CAMERA_CY, 
    		LINEAR_CAMERA_SKEW_C, LINEAR_CAMERA_SKEW_D, LINEAR_CAMERA_SKER_E, 
    		Cam_Lut_Linear,
    		LINEAR_CAMERA_HFOV*deg2rad, 
    		LINEAR_CAMERA_VFOV*deg2rad, 
    		true, 
    		pR, 
    		pT
    		);	
    }
	else
	{
	    if(adjust_port==ROT_X_ADJ)
	    {
	        if(adjust_direct == ADJUST_DIRECT_POS)
	        {
	            a[0] = ANGLE_ADJUST_STEP*deg2rad;
	        }
			else
			{
			    a[0] = -ANGLE_ADJUST_STEP*deg2rad;
			}
	    }
	    else if(adjust_port==ROT_Y_ADJ)
	    {
	        if(adjust_direct == ADJUST_DIRECT_POS)
	        {
	            a[1] = ANGLE_ADJUST_STEP*deg2rad;
	        }
			else
			{
			    a[1] = -ANGLE_ADJUST_STEP*deg2rad;
			}
	    }
	    else if(adjust_port==ROT_Z_ADJ)
	    {
	        if(adjust_direct == ADJUST_DIRECT_POS)
	        {
	            a[2] = ANGLE_ADJUST_STEP*deg2rad;
	        }
			else
			{
			    a[2] = -ANGLE_ADJUST_STEP*deg2rad;
			}
	    }

		
	    Cam_UpdateViewRotation(m_cam_linear[camera_index], a);
    	m_linear_cam[camera_index][0]+=a[0];
    	m_linear_cam[camera_index][1]+=a[1];
    	m_linear_cam[camera_index][2]+=a[2];		
	}
	Cam_MapImage_GenerateGPULUT(
		pRealCam, 
		m_cam_linear[camera_index],
		RIGHT_SIDE_VIEW_ROI_START_X,
		RIGHT_SIDE_VIEW_ROI_START_Y,
		RIGHT_SIDE_VIEW_ROI_END_X,
		RIGHT_SIDE_VIEW_ROI_END_Y,
		RIGHT_SIDE_VIEW_MESH_WIDTH, 
		RIGHT_SIDE_VIEW_MESH_HEIGHT,
		&vertex_num,
		pVert);

}


