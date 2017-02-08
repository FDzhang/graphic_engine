#ifndef __AVM_2DLUT_H__
#define __AVM_2DLUT_H__

/*===========================================================================*\
 * FILE: example.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *    This file is used for all the input data for all AVM moudules, including
 *    calib data,CAN data ,and so on.
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
#include "../DataStruct.h"
#include "../../XrCore/XrSrc/External/XrHeaders.h"
/*===========================================================================*\
 * Other Header Files
\*===========================================================================*/


#define CMV_MAX_BUF 1024


/*===========================================================================*\
 * Exported Preprocessor #define Constants
\*===========================================================================*/

/*===========================================================================*\
 * Exported Preprocessor #define MACROS
\*===========================================================================*/

/*===========================================================================*\
 * Exported Type Declarations
\*===========================================================================*/

/*===========================================================================*\
 * Exported Object Declarations
\*===========================================================================*/
class AVM2DLUT
{
public:

    AVM2DLUT();
    ~AVM2DLUT();
    /*Init from pose file ,file sotre camera pose index as front right rear left*/	
    void Init( char *pConfigfilename,char *pIndexfilename,char *datafilename,char *carposefile,char *carposeadjustfile,char *calibfile);
    void GetLutData(float **pData,int index);
    void GetLutIndex(GLushort **pData,int index);
    void GetLutData(float **pData);
    void GetLutIndex(GLushort **pData);
	void GetLutConfig(GLuint **pData,int index);


    void UpdateLUT(GLfloat *pData,GLushort *pIndex);
	int  GetDataTotalCnt(void );	
	int  GetIndexTotalCnt(void );	
	void GetCarRect(float *pData,int index);
	void GetCarShadowAdjust(float *pData,int index);
	void CvtPointImage2Wolrd(CvPoint2D32f InPoint,CvPoint2D32f *pOutPoint);
	void CvtPointWorld2Image(CvPoint2D32f InPoint,CvPoint2D32f *pOutPoint);

private:
	void AdjustCarPose(float *car_pose,float width_adjust,float height_adjust);
	int LoadConfigFile(char *pFileName,GLuint **pContent);
    int LoadDataFile(char *pFileName,GLfloat **pContent,int num);
	int LoadDataFile(char *pFileName,GLfloat *pContent,int num);
	
    int SaveTxtFile(char *pFileName,GLfloat *pBuf,int size);
    int SaveTxtFileShort(char *pFileName,GLushort *pBuf,int size);
    int LoadIndexFile(char *pFileName,GLushort **pContent,int num);
    void read_file_from_bin(void *pData,char *pName,int size);
    void LoadConfigBinFile( char *pName,unsigned int *pui_config);
    void LoadDataBinFile(GLfloat**pInput, char *pName,unsigned int Config[][eConfigEnd],float **pVertex);
    void LoadDataBinFileTotal(GLfloat**pInput, char *pName,unsigned int Config[][eConfigEnd]);
    void LoadIndexBinFileTotal(GLushort **pInputIndex,char *pName,unsigned int Config[][eConfigEnd]);
    void LoadIndexBinFile(GLushort **pInputIndex,char *pName,unsigned int Config[][eConfigEnd],GLushort **pVertex);


	GLfloat *m_pfSrcData[16];
	GLushort *m_puiIndex[16];
	GLuint m_uiConfigBin[4][eConfigEnd];
	//int m_uiConfigBin[4][eConfigEnd];
	GLfloat *m_pfDataTotal;
	GLushort *m_pucIndexTotal;
	int m_total_data_size;
	int m_total_index_size;
	float m_car_rect[4];
	float m_car_shadow_adjust_rect[4];
	float m_calib_para[4];


};
/*===========================================================================*\
 * Exported Function Prototypes
\*===========================================================================*/

/*===========================================================================*\
 * Exported Inline Function Definitions and #define Function-Like Macros
\*===========================================================================*/

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 * Date             SCR                   userid                   Description
 * ----------------------------------------------------------------------------------

\*===========================================================================*/


#endif //#ifndef __GL_SV_DEMO_H__
