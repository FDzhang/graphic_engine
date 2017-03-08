
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

#define LEFT_SINGLE_LEFT 0.29456
#define LEFT_SINGLE_RIGHT 0.95652 
#define LEFT_SINGLE_TOP   0.0196
#define LEFT_SINGLE_BOTTOM  1.0



#define RIGHT_SINGLE_LEFT  0.75
#define RIGHT_SINGLE_RIGHT  0.05
#define RIGHT_SINGLE_TOP   1.0
#define RIGHT_SINGLE_BOTTOM  0.0196

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
	else
	{
	    *BufSize = 4;
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
	else
	{
	    *BufSize = 6;
	}	
	return 0;
}

