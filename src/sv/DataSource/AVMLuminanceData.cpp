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
#include "AVMLuminanceData.h"
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
int AVMLuminanceData::get_Lumin_para_from_file(Lumin_para *myLumin_para, char *filename)
{
  float *K_FL = (myLumin_para->K_FL);
  float *K_FR = (myLumin_para->K_FR);
  float *K_BL = (myLumin_para->K_BL);
  float *K_BR = (myLumin_para->K_BR);
  float *point_TL = (myLumin_para->Lumin_point_TL);
  float *point_TR = (myLumin_para->Lumin_point_TR);
  float *point_RT = (myLumin_para->Lumin_point_RT);
  float *point_RB = (myLumin_para->Lumin_point_RB);
  FILE *f;
  char buf[CMV_MAX_BUF];
  int i;

  //Open file
  if(!(f=fopen(filename,"r")))
	{
		printf("File %s cannot be opened\n", filename);
	   return -1;
	}
  
		*(K_FL+0) = 1.0;
		*(K_FL+1) = 1.0;
		*(K_FL+2 )= 1.0;
		
		 *(K_BL+0) = 1.0;
		 *(K_BL+1) = 1.0;
		 *(K_BL+2 )= 1.0;
		 
		 *(K_FR+0) = 1.0;
		 *(K_FR+1) = 1.0;
		 *(K_FR+2 )= 1.0;
		 
		 *(K_BR+0) = 1.0;
		 *(K_BR+1) = 1.0;
		 *(K_BR+2 )= 1.0;


 fscanf(f,"\n");
 fgets(buf,CMV_MAX_BUF,f);
 fscanf(f,"%f,%f,%f",point_TL,point_TL+1,point_TL+2);
 
 printf("\r\n m_lumin_para.Lumin_point_TL = %f",*point_TL);

 
 fscanf(f,"\n");
 fgets(buf,CMV_MAX_BUF,f);
 fscanf(f,"%f,%f,%f",point_TR,point_TR+1,point_TR+2);


fscanf(f,"\n");
fgets(buf,CMV_MAX_BUF,f);
fscanf(f,"%f,%f,%f",point_RB,point_RB+1,point_RB+2);


fscanf(f,"\n");
fgets(buf,CMV_MAX_BUF,f);
fscanf(f,"%f,%f,%f",point_RT,point_RT+1,point_RT+2);

}



/*===========================================================================*\
 * Local Inline Function Definitions and Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * Internal Function Definitions
\*===========================================================================*/

AVMLuminanceData::AVMLuminanceData()
{
    Reset();
}
AVMLuminanceData::~AVMLuminanceData()
{



}
void AVMLuminanceData::CalcLuminanceCof(float *first_lumin,float *second_lumin,float *first_cof,float *second_cof)
{
        float sigma_N = 6502500.0;
		float sigma_g = 80277.8;
        float A,B,C,D,temp;

		for(int i=0;i<3;i++)
		{

            A=0.0-first_lumin[i]*second_lumin[i]*sigma_N;
			B=second_lumin[i]*second_lumin[i]*sigma_N+sigma_g;
			C=first_lumin[i]*first_lumin[i]*sigma_N+sigma_g;
			D = A;

			temp = A*D-C*B;
			first_cof[i]=(D-B)/temp*sigma_g;
			second_cof[i]=(A-C)/temp*sigma_g;





		}

}

/*Init from pose file ,file sotre camera pose index as front right rear left*/	
void AVMLuminanceData::Init( char *pfilename)
{
     int i=0;

	get_Lumin_para_from_file(&m_lumin_para,pfilename);
	

}

void AVMLuminanceData::SetLuminanceNormalizeRGB(float *pLuminance)
{
	memcpy(m_luminance_normalize_rgb,pLuminance,24*sizeof(float));
	ConvertRgb2YuvNorm();
	CalcLuminanceCof();

   return;

}
void AVMLuminanceData::SetLuminanceNormalizeYUV(float *pLuminance)
{
   memcpy(m_luminance_normalize_yuv,pLuminance,24*sizeof(float));
   CalcLuminanceCof();
   return;

}

void AVMLuminanceData::ConvertRgb2Yuv(float *pLuminancergb,float *pYUV)
{

   pYUV[0] = (float)(pLuminancergb[0])*0.299+(float)(pLuminancergb[1])*0.587 + (pLuminancergb[2])*0.11413;
   
   pYUV[1]=(float)0.5+(float)(pLuminancergb[0])*(-0.169)+(float)(pLuminancergb[1])*(-0.331) + (pLuminancergb[2])*0.5;
   
   pYUV[2]=(float)0.5+(float)(pLuminancergb[0])*0.5+(float)(pLuminancergb[1])*(-0.419)+ (pLuminancergb[2])*(-0.081);

   return;

}
void AVMLuminanceData::ConvertRgb2YuvNorm(void)
{
   for(int i =0;i<8;i++)
   {
       ConvertRgb2Yuv(&m_luminance_normalize_rgb[3*i],&m_luminance_normalize_yuv[3*i]);
   }
   return;

}
void AVMLuminanceData::GetLuminCof(Lumin_para **pLumin)
{

   *pLumin = &m_lumin_para;
   return;

}

void AVMLuminanceData::GetLuminCof(float **pLumin)
{

   *pLumin = m_lumin_cof;
   return;

}

void AVMLuminanceData::Reset()
{
    for(int i = 0; i < 24; ++i)
    {
        m_lumin_cof[i] = 1.0;
    }
    for(int i = 0; i<3;i++)
    {
        m_lumin_para.K_FL[i] = 1.0f;
        m_lumin_para.K_FR[i] = 1.0f;
        m_lumin_para.K_RF[i] = 1.0f;
        m_lumin_para.K_RB[i] = 1.0f;
        m_lumin_para.K_BL[i] = 1.0f;
        m_lumin_para.K_BR[i] = 1.0f;
        m_lumin_para.K_LF[i] = 1.0f;
        m_lumin_para.K_LB[i] = 1.0f;
    }
}


void AVMLuminanceData::CalcLuminanceCof()
{
	CalcLuminanceCof(&(m_luminance_normalize_yuv[3*eLeftFront]),&(m_luminance_normalize_yuv[3*eFrontLeft]),m_lumin_para.K_LF,m_lumin_para.K_FL);
	CalcLuminanceCof(&(m_luminance_normalize_yuv[3*eFrontRight]),&(m_luminance_normalize_yuv[3*eRightFront]),m_lumin_para.K_FR,m_lumin_para.K_RF);		
	CalcLuminanceCof(&(m_luminance_normalize_yuv[3*eRearLeft]),&(m_luminance_normalize_yuv[3*eLeftRear]),m_lumin_para.K_BL,m_lumin_para.K_LB);
	CalcLuminanceCof(&(m_luminance_normalize_yuv[3*eRightRear]),&(m_luminance_normalize_yuv[3*eRearRight]),m_lumin_para.K_RB,m_lumin_para.K_BR);   
	
    MergeDataToAll(m_lumin_cof,&m_lumin_para);
}
void AVMLuminanceData::MergeDataToAll(float *pCof,Lumin_para *pCofSeparate)
{
    for(int i =0;i<3;i++)
    {
        pCof[3*eLeftFront+i] = pCofSeparate->K_LF[i];
		pCof[3*eFrontLeft+i] = pCofSeparate->K_FL[i];
		pCof[3*eFrontRight+i] = pCofSeparate->K_FR[i];
		pCof[3*eRightFront+i] = pCofSeparate->K_RF[i];
		pCof[3*eRearLeft+i] = pCofSeparate->K_BL[i];
		pCof[3*eLeftRear+i] = pCofSeparate->K_LB[i];
		pCof[3*eRightRear+i] = pCofSeparate->K_RB[i];
		pCof[3*eRearRight+i] = pCofSeparate->K_BR[i];
    }

}
void AVMLuminanceData::Normalize(unsigned int *pInput,float *pOutput)
{
    for(int i =0;i <24;i++)
    {
        *(pOutput+i) = (float)(*(pInput+i))/255.0;
    }
}
void AVMLuminanceData::SetLuminanceUnNormalizeRGB(unsigned int *pLuminance)
{
	memcpy(m_luminance_rgb,pLuminance,24*sizeof(unsigned int));
	Normalize(m_luminance_rgb,m_luminance_normalize_rgb);
	ConvertRgb2YuvNorm();
	CalcLuminanceCof();	
   return;

}

void AVMLuminanceData::SetLuminanceUnNormalizeYUV(unsigned int *pLuminance)
{
	memcpy(m_luminance_yuv,pLuminance,24*sizeof(unsigned int));
	Normalize(m_luminance_yuv,m_luminance_normalize_yuv);
	CalcLuminanceCof();	
   return;

}

void AVMLuminanceData::SetLuminanceCofYUVReslt(CoefYUV *pLuminance)
{

   for(int i =0;i<3;i++)
   {
       m_lumin_para.K_FL[i] = pLuminance->K_FL[i];
	   m_lumin_para.K_FR[i] = pLuminance->K_FR[i];
	   m_lumin_para.K_RF[i] = pLuminance->K_RF[i];
	   m_lumin_para.K_RB[i] = pLuminance->K_RB[i];
	   m_lumin_para.K_LF[i] = pLuminance->K_LF[i];
	   m_lumin_para.K_LB[i] = pLuminance->K_LB[i];
	   m_lumin_para.K_BL[i] = pLuminance->K_BL[i];	   
	   m_lumin_para.K_BR[i] = pLuminance->K_BR[i];

   }

   MergeDataToAll(m_lumin_cof,&m_lumin_para);

   return;

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

