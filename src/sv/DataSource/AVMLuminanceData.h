#ifndef __AVM_LUMINANCE_DATA_H__
#define __AVM_LUMINANCE_DATA_H__

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
class AVMLuminanceData
{
public:

	AVMLuminanceData();
	~AVMLuminanceData();


	void CalcLuminanceCof(float *first_lumin,float *second_lumin,float *first_cof,float *second_cof);

	void Init( char *pfilename);

	void SetLuminanceNormalizeRGB(float *pLuminance);

	void SetLuminanceNormalizeYUV(float *pLuminance);



	void GetLuminCof(Lumin_para **pLumin);

	void GetLuminCof(float **pLumin);

	void SetLuminanceCofYUVReslt(CoefYUV *pLuminance);


	void SetLuminanceUnNormalizeRGB(unsigned int *pLuminance);

	void SetLuminanceUnNormalizeYUV(unsigned int *pLuminance);

private:
	void CalcLuminanceCof();
	void MergeDataToAll(float *pCof,Lumin_para *pCofSeparate);
	void Normalize(unsigned int *pInput,float *pOutput);
	void ConvertRgb2Yuv(float *pLuminancergb,float *pYUV);
	void ConvertRgb2YuvNorm(void);
	void InitDefaultLuminanceParams();

	int get_Lumin_para_from_file(Lumin_para *myLumin_para, char *filename);

    Lumin_para m_lumin_para;
	float m_luminance_normalize_yuv[24];
	float m_luminance_normalize_rgb[24];
	unsigned int m_luminance_rgb[24];
	unsigned int m_luminance_yuv[24];
	float m_lumin_cof[24];


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
