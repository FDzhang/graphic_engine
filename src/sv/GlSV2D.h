#ifndef __GL_SV_2D_H__
#define __GL_SV_2D_H__
#include "DataStruct.h"
#include "fileloader.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "AVMData.h"

#include "TS_config.h"

#define RENDER_BUFFER_TOTAL 2
#define FRAME_BUFFER_TOTAL 2
#define PRINT_GL_ERROR printf

#define REAR_SINGLE_LEFT 0.83375
#define REAR_SINGLE_RIGHT  0.19
#define REAR_SINGLE_TOP   0.0645
#define REAR_SINGLE_BOTTOM  0.9335
#if 0
#define FRONT_SINGLE_LEFT 0.0625
#define FRONT_SINGLE_RIGHT 0.9021 
#define FRONT_SINGLE_TOP   0.1
#define FRONT_SINGLE_BOTTOM  0.85
#else
#define FRONT_SINGLE_LEFT 0.143
#define FRONT_SINGLE_RIGHT 0.831
#define FRONT_SINGLE_TOP   0.035
#define FRONT_SINGLE_BOTTOM 0.904

#endif

#define LEFT_SINGLE_LEFT 0.29456
#define LEFT_SINGLE_RIGHT 0.95652 
#define LEFT_SINGLE_TOP   0.0196
#define LEFT_SINGLE_BOTTOM  1.0



#define RIGHT_SINGLE_LEFT  0.75
#define RIGHT_SINGLE_RIGHT  0.05
#define RIGHT_SINGLE_TOP   1.0
#define RIGHT_SINGLE_BOTTOM  0.0196


enum
{
  ROT_X_ADJ=0,
  ROT_Y_ADJ,
  ROT_Z_ADJ,
  POS_X_ADJ,
  POS_Y_ADJ,
  POS_Z_ADJ,
};


enum
{
   ADJUST_DIRECT_POS=0,
   ADJUST_DIRECT_NEG
};


#define RENDER_BUFFER_TOTAL 2
#define FRAME_BUFFER_TOTAL 2
#define PRINT_GL_ERROR printf

#define REAR_SINGLE_LEFT 0.81
#define REAR_SINGLE_RIGHT  0.19
#define REAR_SINGLE_TOP   0.01
#define REAR_SINGLE_BOTTOM  0.85
#if 0
#define REAR_SINGLE_LEFT 0.8320
#define REAR_SINGLE_RIGHT  0.203125
#define REAR_SINGLE_TOP   0.0645
#define REAR_SINGLE_BOTTOM  0.9335
#endif
#if 0
#define FRONT_SINGLE_LEFT 0.0625
#define FRONT_SINGLE_RIGHT 0.9021 
#define FRONT_SINGLE_TOP   0.1
#define FRONT_SINGLE_BOTTOM  0.85
#else
//#define FRONT_SINGLE_LEFT 0.19
//#define FRONT_SINGLE_RIGHT 0.81
#define FRONT_SINGLE_LEFT 0.2
#define FRONT_SINGLE_RIGHT 0.8
#define FRONT_SINGLE_TOP   0.02
#define FRONT_SINGLE_BOTTOM 0.93

#endif

class GlSV2D 
{
public:
	GlSV2D();

	int Init();
	int InitLinear();
	int Update(void);


	int GetIndexBuffer(int Index,GLushort **pIndexBuffer, unsigned int *BufSize);
	
	int GetVertexBuffer(int Index,float **pVertexBuffer, unsigned int *BufSize);
	int GenerateFishSideSingleViewLUT(int camera_index,float *pVert);
	int GenerateCyliSideSingleViewLUT(int camera_index,float *pVert);
	int GenerateSideSingleViewLUT(int camera_index,float *pVert);
	int InitSideViewBuffer(int width, int height, GLfloat **pData, GLushort **pIndex, unsigned int *puiVertSize, unsigned int *puiIndexSize,unsigned char index_flag = 0);
	void AdjustSideSingleViewLUT(int camera_index,unsigned char adjust_port,unsigned char adjust_direct);
	int InitFrontRearViewBuffer(int width,int height,GLfloat **pData,GLushort **pIndex,unsigned int *puiVertSize,unsigned int *puiIndexSize);
	int GenerateFrontRearSingleViewLUT(int camera_index,float *pVert);

	int InitFrontRearSingleViewCamLUT(int camera_index);

private:

	GLuint *uiConfig;
	
	GLuint *uiConfigAlpha;

	

	GLfloat *m_pfVertexBuff[eMeshIndexMax];
	
	//GLfloat *m_pfVertexSingleView[eSingleEnd];

	
	GLushort	 *m_pucIndexBuff[eMeshIndexMax];
	
	
	unsigned int m_SideViewVertSize[4];
	unsigned int m_SideViewIndexSize[4];
	
	Cam_Model *m_cam_linear[4];
	Cam_Model *m_cam_fish_side[4];
	Cam_Model_Cyli *m_cam_clc_side[4];
	Cam_Model_Cyli *m_cam_clc[4];
	float m_linear_cam[4][3];
	
	unsigned char m_camType;

};

#endif //#ifndef __GL_SV_DEMO_H__
