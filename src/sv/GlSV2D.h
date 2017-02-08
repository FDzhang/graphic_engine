#ifndef __GL_SV_2D_H__
#define __GL_SV_2D_H__
#include "DataStruct.h"
#include "fileloader.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"

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






class GlSV2D 
{
public:
	GlSV2D();

	int Init();
	int Update(void);


	int GetIndexBuffer(int Index,GLushort **pIndexBuffer, unsigned int *BufSize);
	
	int GetVertexBuffer(int Index,float **pVertexBuffer, unsigned int *BufSize);


private:

	GLuint *uiConfig;
	
	GLuint *uiConfigAlpha;

	

	GLfloat *m_pfVertexBuff[eMeshIndexMax];
	
	//GLfloat *m_pfVertexSingleView[eSingleEnd];

	
	GLushort	 *m_pucIndexBuff[eMeshIndexMax];
	
	





};

#endif //#ifndef __GL_SV_DEMO_H__
