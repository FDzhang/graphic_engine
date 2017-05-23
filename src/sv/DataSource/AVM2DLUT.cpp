/*===========================================================================*\
 * FILE: template.c
 *===========================================================================
 * Copyright 2008 O-Film Technologies, Inc., All Rights Reserved.
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
#include "AVM2DLUT.h"
#include "../fileloader.h"
#include "../DataStruct.h"
#include "sv/SurroundView.h"
/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Local Preprocessor #define MACROS
\*===========================================================================*/


/*===========================================================================*\
 * Local Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * External Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Object Definitions
\*===========================================================================*/

/*===========================================================================*\
 * Local Function Prototypes
\*===========================================================================*/

int AVM2DLUT::LoadConfigFile(char *pFileName,GLuint **pContent)
{
    FILE *fp_table;
    FILE *fp_sourcetable;
    fp_table = fopen(pFileName,"r");
    if(fp_table == NULL)
    {
        printf("\r\n can not find file %s",pFileName);
	    return true;
    }
    fp_sourcetable = fp_table;
    GLuint tempUint;
    fscanf( fp_table , "%d," , &tempUint);
    GLuint num = tempUint;
    *pContent = new GLuint[num+1];

	// buffer file %s,line %d",__FILE__,__LINE__);
    **pContent = tempUint;
    int i;
    for(i = 1;i < num+1  ;i ++)
    {
 	    fscanf( fp_table , "%d," , &tempUint);

        *(*pContent+i) = tempUint;
    }

    if(fp_table != NULL)
    {
        if(fileno(fp_table)>0)
        {
            printf("\r\n fp_table = %d",fp_table);
            fclose(fp_table);
        }
	    return false;
    }

    return false;

}
int AVM2DLUT::LoadDataFile(char *pFileName,GLfloat **pContent,int num)
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
int AVM2DLUT::LoadDataFile(char *pFileName,GLfloat *pContent,int num)
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
    //*pContent = new GLfloat[num];

	// buffer file %s,line %d",__FILE__,__LINE__);
    printf("\r\nstart to read file %s",pFileName);
    for(i = 0;i < num  ;i ++)
    {
 	    fscanf( fp_table , "%f," , &tempUint);
		*(pContent+i) = tempUint;
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

int AVM2DLUT::SaveTxtFile(char *pFileName,GLfloat *pBuf,int size)
{

    FILE *fp_table;
    fp_table = fopen(pFileName,"wb");
    if(fp_table == NULL)
    {
    	printf("\r\n can not find file %s",pFileName);
    	return true;
    }
    GLfloat tempUint;

    int i;
    for(i = 0;i < size  ;i ++)
    {
    	fprintf( fp_table , "%f," , pBuf[i]);

		if(i%7==6)
		fprintf(fp_table, "\r\n");
    }
   // printf("\r\n read [%d] over",num);

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
int AVM2DLUT::SaveTxtFileShort(char *pFileName,GLushort *pBuf,int size)
{

    FILE *fp_table;
    fp_table = fopen(pFileName,"wb");
    if(fp_table == NULL)
    {
    	printf("\r\n can not find file %s",pFileName);
    	return true;
    }
    GLfloat tempUint;

    int i;
    for(i = 0;i < size  ;i ++)
    {
    	fprintf( fp_table , "%d," , pBuf[i]);

		if(i%20==19)
		fprintf(fp_table, "\r\n");
    }
   // printf("\r\n read [%d] over",num);

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


int AVM2DLUT::LoadIndexFile(char *pFileName,GLushort **pContent,int num)
{
    FILE *fp_table;
    GLuint tempUint;
    int i;

	printf("\r\n into loadindexfile");
    fp_table = fopen(pFileName,"r");
    if(fp_table == NULL)
    {
        printf("\r\n could not find specilized index file");
        printf("\r\n can not find file %s",pFileName);
	    return true;
    }
	printf("\r\ncomplete step2");



    *pContent = new GLushort[num];
	// buffer file %s,line %d",__FILE__,__LINE__);

    for(i = 0;i < num  ;i ++)
    {
 	fscanf( fp_table , "%d," , &tempUint);
	*(*pContent+i) = tempUint;

	}

    if(fp_table != NULL)
    {
        if(fileno(fp_table)>0)
        {
            fclose(fp_table);
         }

	    return false;
    }

    return false;

}
bool AVM2DLUT::read_file_from_bin(void *pData,char *pName,int size)
{
    FILE *fp_table;
    bool ret = false;

    fp_table = fopen(pName,"rb");
    if(fp_table == NULL)
    {
	    printf("\r\n can not find file %s",pName);
	    return false;
    }

    if(fread(pData,size,1,fp_table) > 0)
    {
        ret = true;
    }
    else
    {
        printf("read file[%s] failed, expected size[%d], please check it.\n", pName, size);
    }
    fclose(fp_table);
    return ret;

}
bool AVM2DLUT::LoadConfigBinFile( char *pName,unsigned int *pui_config)
{
    return read_file_from_bin(pui_config,pName,eConfigEnd*4*sizeof(unsigned int));
}

bool AVM2DLUT::LoadDataBinFile(GLfloat**pInput, char *pName,unsigned int Config[][eConfigEnd],float **pVertex,  GLfloat* ext)
{
    unsigned int vertex_num=0;
	unsigned int IndexType,IndexNum;
	unsigned int uiSize[16];
	unsigned int previous_load=0;
	bool ret = false;
	//float *pInputData;

    for(int i=0;i<16;i++)
    {
        IndexType = i/4;
        IndexNum = i%4*2+1;
        uiSize[i] = Config[IndexType][IndexNum]*7;
        vertex_num +=uiSize[i];
    }

    *pInput = new GLfloat [vertex_num];
    m_total_data_size = vertex_num;

    if(*pInput == NULL)
    {
        printf("AVM2DLUT::LoadDataBinFile: No memory to hold data binary data.\n");
        return false;
    }

    if(ext == NULL)
    {//一旦外部提供，就直接使用外部数据
        ret = read_file_from_bin(*pInput,pName,vertex_num*sizeof(float));
        if(ret != true)
        {
            return ret;
        }
    }
    else
    {
        memcpy(*pInput, ext, vertex_num*sizeof(float));
    }

	for(int i=0;i<16;i++)
	{
        IndexType = i/4;
        IndexNum = i%4*2+1;
        pVertex[i] =   (*pInput)+previous_load;//  new float [Config[IndexType][IndexNum]*7];
			//memcpy((pVertex[i]),pInputData+previous_load,Config[IndexType][IndexNum]*7*sizeof(float));

        previous_load += Config[IndexType][IndexNum]*7;
	}

	return true;


}

bool AVM2DLUT::LoadDataBinFileTotal(GLfloat**pInput, char *pName,unsigned int Config[][eConfigEnd])
{
    unsigned int vertex_num=0;
	unsigned int IndexType,IndexNum;
	unsigned int uiSize[16];
	unsigned int previous_load=0;
	//float *pInputData;

	for(int i=0;i<16;i++)
	{
			IndexType = i/4;
			IndexNum = i%4*2+1;
			uiSize[i] = Config[IndexType][IndexNum]*7;
	        vertex_num +=uiSize[i];
	}

    *pInput = new GLfloat [vertex_num];
    return read_file_from_bin(*pInput,pName,vertex_num*sizeof(float));

	//delete [] pInputData;

}
bool AVM2DLUT::LoadIndexBinFileTotal(GLushort **pInputIndex,char *pName,unsigned int Config[][eConfigEnd])
{
    unsigned int vertex_num=0;
	unsigned int IndexType,IndexNum;
	unsigned int uiSize[16];
	unsigned int previous_load=0;
	GLushort *pInputData;

	for(int i=0;i<16;i++)
	{
			IndexType = i/4;
			IndexNum = i%4*2+2;
			uiSize[i] = Config[IndexType][IndexNum];
	        vertex_num +=uiSize[i];
	}

    *pInputIndex = new GLushort [vertex_num];
    return read_file_from_bin(*pInputIndex,pName,vertex_num*sizeof(GLushort));
}

bool AVM2DLUT::LoadIndexBinFile(GLushort **pInputIndex,char *pName,unsigned int Config[][eConfigEnd],GLushort **pVertex, GLushort* ext)
{
    unsigned int vertex_num=0;
	unsigned int IndexType,IndexNum;
	unsigned int uiSize[16];
	unsigned int previous_load=0;
	//GLushort *pInputData;

	for(int i=0;i<16;i++)
	{
        IndexType = i/4;
        IndexNum = i%4*2+2;
        uiSize[i] = Config[IndexType][IndexNum];
        vertex_num +=uiSize[i];
	}

    *pInputIndex = new GLushort [vertex_num];
    if(*pInputIndex == NULL)
    {
        printf("AVM2DLUT::LoadIndexBinFile: No memory to hold index binary data.");
        return false;
    }
	m_total_index_size = vertex_num;

	if(ext == NULL)
	{
        if(read_file_from_bin(*pInputIndex,pName,vertex_num*sizeof(GLushort)) != true)
        {
            return false;
        }
    }
    else
    {
        memcpy(*pInputIndex, ext, vertex_num*sizeof(GLushort));
    }

	for(int i=0;i<16;i++)
	{

        pVertex[i] =(*pInputIndex)+ previous_load;
        previous_load += uiSize[i];
	}
	return true;


}

/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Internal Function Definitions
\*===========================================================================*/

AVM2DLUT::AVM2DLUT()
{

}
AVM2DLUT::~AVM2DLUT()
{



}
void AVM2DLUT::AdjustCarPose(float *car_pose,float width_adjust,float height_adjust)
{
    car_pose[rect_left]=car_pose[rect_left]-width_adjust;
	car_pose[rect_right]=car_pose[rect_right]+width_adjust;
    car_pose[rect_top]=car_pose[rect_top]+height_adjust;
	car_pose[rect_bottom]=car_pose[rect_bottom]-height_adjust;

}

/*Init from pose file ,file sotre camera pose index as front right rear left*/
void AVM2DLUT::Init( char *pConfigfilename,char *pIndexfilename,char *datafilename,char *carposefile,char *carposeadjustfile,char *calibfile)
{


    LoadConfigBinFile(pConfigfilename,&m_uiConfigBin[0][0]);

	LoadDataBinFile(&m_pfDataTotal,datafilename,m_uiConfigBin,m_pfSrcData);

	LoadIndexBinFile(&m_pucIndexTotal,pIndexfilename,m_uiConfigBin,m_puiIndex);
    LoadDataFile(carposefile,&(m_car_rect[0]),4);

    LoadDataFile(carposeadjustfile,&(m_car_shadow_adjust_rect[0]),4);
	LoadDataFile(calibfile,&(m_calib_para[0]),4);

	AdjustCarPose(m_car_rect,0.005,0.01);
}


bool AVM2DLUT::Init( char *pConfigfilename,char *pIndexfilename,char *datafilename,char *carposefile,StitcherResult *pSticherReslt)
{
    unsigned int** out_config_store;
    float* data_buffer;
    short* gui_index_buffer;
    str_avm_pose_t pose;
    bool ret = false;

    if(pSticherReslt != NULL)
    {//当有可能从外部获取拼接数据时，即从外部获取
        Gpu2dLutParam_T* param = pSticherReslt->gpu_2dlut_param;
        m_pfDataTotal = param->gpu_lut_data;
        m_pucIndexTotal = param->gpu_lut_index;
        memcpy(m_uiConfigBin, param->gpu_lut_config, sizeof(m_uiConfigBin));

        if(LoadDataBinFile(&m_pfDataTotal,datafilename,m_uiConfigBin,m_pfSrcData, param->gpu_lut_data))
        {
            if(LoadIndexBinFile(&m_pucIndexTotal,pIndexfilename,m_uiConfigBin,m_puiIndex, (GLushort*)param->gpu_lut_index) == true)
            {
                //更新小车区域
                m_car_rect[0] = -1.0+2.0*(float)pSticherReslt->car_Icon_Rect.x/(float)pSticherReslt->bev_img_width - 0.03;
                m_car_rect[1] = 1.0-2.0*(float)pSticherReslt->car_Icon_Rect.y/(float)pSticherReslt->bev_img_height + 0.08;

                m_car_rect[2] = -1.0+2.0*((float)pSticherReslt->car_Icon_Rect.x+(float)pSticherReslt->car_Icon_Rect.width)/(float)pSticherReslt->bev_img_width + 0.03;
                m_car_rect[3] = 1.0-2.0*((float)pSticherReslt->car_Icon_Rect.y+(float)pSticherReslt->car_Icon_Rect.height)/(float)pSticherReslt->bev_img_height - 0.08;

                //更新pgs
                m_calib_para[0] = pSticherReslt->cx;
                m_calib_para[1] = pSticherReslt->cy;
                m_calib_para[2] = pSticherReslt->ppmmx;
                m_calib_para[3] = pSticherReslt->ppmmy;

                return true;
            }
            else
            {//index加载失败，释放data
                delete [] m_pfDataTotal;
            }
        }
    }


    m_pfDataTotal = NULL;
    m_pucIndexTotal = NULL;

    if(LoadConfigBinFile(pConfigfilename,&m_uiConfigBin[0][0]))
    {
        if(LoadDataBinFile(&m_pfDataTotal,datafilename,m_uiConfigBin,m_pfSrcData) == true)
        {
            if(LoadIndexBinFile(&m_pucIndexTotal,pIndexfilename,m_uiConfigBin,m_puiIndex) == true)
            {
                ret = true;
            }
            else
            {
                delete [] m_pfDataTotal;
            }
        }
    }

    return ret;
}

void AVM2DLUT::GetLutData(float **pData,int index)
{
    *pData = m_pfSrcData[index];
	return;

}
void AVM2DLUT::GetLutIndex(GLushort **pData,int index)
{
    *pData = m_puiIndex[index];
	return;

}
void AVM2DLUT::GetLutConfig(GLuint **pData,int index)
{
    *pData = m_uiConfigBin[index];
	return;

}

void AVM2DLUT::GetLutData(float **pData)
{
    *pData = m_pfDataTotal;
	return;

}
void AVM2DLUT::GetCarRect(float *pData,int index)
{
    *pData = m_car_rect[index];
	return;

}
void AVM2DLUT::GetCarShadowAdjust(float *pData,int index)
{
    *pData = m_car_shadow_adjust_rect[index];
	return;

}

void AVM2DLUT::GetLutIndex(GLushort **pData)
{
    *pData = m_pucIndexTotal;
	return;

}
void AVM2DLUT::UpdateLUT(GLfloat *pData,GLushort *pIndex)
{
	memcpy(m_pfDataTotal,pData,m_total_data_size*sizeof(GLfloat));
	memcpy(m_pucIndexTotal,pIndex,m_total_index_size*sizeof(GLushort));

}

int  AVM2DLUT::GetDataTotalCnt(void )
{
	return m_total_data_size;

}

int  AVM2DLUT::GetIndexTotalCnt(void )
{
	return m_total_index_size;

}
void AVM2DLUT::CvtPointImage2Wolrd(CvPoint2D32f InPoint,CvPoint2D32f *pOutPoint)
{
     pOutPoint->x =  -((-InPoint.y*240+240)-m_calib_para[POS_CALIB_CX])*m_calib_para[POS_CALIB_PPMMX]/1000.0;
	 pOutPoint->y = ((InPoint.x*108+108)-m_calib_para[POS_CALIB_CY])*m_calib_para[POS_CALIB_PPMMY]/1000.0;

}
void AVM2DLUT::CvtPointWorld2Image(CvPoint2D32f InPoint,CvPoint2D32f *pOutPoint)
{

	 pOutPoint->y = 1.0-(((InPoint.x*1000.0)/(0.0-m_calib_para[POS_CALIB_PPMMX])+m_calib_para[POS_CALIB_CX])/240.0);
	  pOutPoint->x =((InPoint.y*1000.0)/m_calib_para[POS_CALIB_PPMMY]+m_calib_para[POS_CALIB_CY]-108.0)/108.0;

}

/*===========================================================================*\
 * External Function Definitions
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------

\*===========================================================================*/

