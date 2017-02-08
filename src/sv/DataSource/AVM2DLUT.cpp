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
void AVM2DLUT::read_file_from_bin(void *pData,char *pName,int size)
{

    FILE *fp_table;
   fp_table = fopen(pName,"rb");
   if(fp_table == NULL)
   {
	   printf("\r\n can not find file %s",pName,size);
	   return ;
   }

  fread(pData,size,1,fp_table); 
  fclose(fp_table); 
   return ;


}
void AVM2DLUT::LoadConfigBinFile( char *pName,unsigned int *pui_config)
{
    read_file_from_bin(pui_config,pName,eConfigEnd*4*sizeof(unsigned int));
	
}
void AVM2DLUT::LoadDataBinFile(GLfloat**pInput, char *pName,unsigned int Config[][eConfigEnd],float **pVertex)
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
	m_total_data_size = vertex_num;
    read_file_from_bin(*pInput,pName,vertex_num*sizeof(float));
	
	for(int i=0;i<16;i++)
	{
			IndexType = i/4;
			IndexNum = i%4*2+1;
			pVertex[i] =   (*pInput)+previous_load;//  new float [Config[IndexType][IndexNum]*7];
			//memcpy((pVertex[i]),pInputData+previous_load,Config[IndexType][IndexNum]*7*sizeof(float));
				
			previous_load += Config[IndexType][IndexNum]*7;
	}

	//delete [] pInputData;
	
}	

void AVM2DLUT::LoadDataBinFileTotal(GLfloat**pInput, char *pName,unsigned int Config[][eConfigEnd])
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
    read_file_from_bin(*pInput,pName,vertex_num*sizeof(float));
	
	//delete [] pInputData;
	
}	
void AVM2DLUT::LoadIndexBinFileTotal(GLushort **pInputIndex,char *pName,unsigned int Config[][eConfigEnd])
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
    read_file_from_bin(*pInputIndex,pName,vertex_num*sizeof(GLushort));

	
}


void AVM2DLUT::LoadIndexBinFile(GLushort **pInputIndex,char *pName,unsigned int Config[][eConfigEnd],GLushort **pVertex)
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
	m_total_index_size = vertex_num;
    read_file_from_bin(*pInputIndex,pName,vertex_num*sizeof(GLushort));
	for(int i=0;i<16;i++)
	{

			pVertex[i] =(*pInputIndex)+ previous_load;
				
			previous_load += uiSize[i];
	}

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

