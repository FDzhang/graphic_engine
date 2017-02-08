#ifndef __GL_SV_LUMINANCE_H__
#define __GL_SV_LUMINANCE_H__

#include "fileloader.h"
#include "../XrCore/XrSrc/External/XrHeaders.h"

#include "../XrCore/XrSrc/XrUILibrary/XrUILibrary.h"
#include "videoloader.h"

#define RENDER_BUFFER_TOTAL 2
#define FRAME_BUFFER_TOTAL 2
#define PRINT_GL_ERROR printf

enum EUniform {	eSmpleLoc,eNumUniforms };


enum EBackUniform {
	eSmpler2D,  eBackNumUniforms
};


class GlSVLuminance 
{
public:
	GlSVLuminance();

	int Init();
	int Update(void);



	//void DrawAxisAlignedQuadHalf(PVRTVec2 afLowerLeft, PVRTVec2 afUpperRight);
	//void draw_4plane(PVRTMat4& View, PVRTMat4& Proj, int ShaderID);

	int RenderFramebufferScene(unsigned char ucSingleViewSel);
	
	int InitFrameBuffer(void);
	void SetLuminance(unsigned int **pInput);
	


private:
	unsigned int m_uiAverageIllum[8][3];

	
	GLuint m_ui32Vbo[12];
	GLuint m_ui32VboSingleView[6];
	GLuint m_ui32VboForBC[8];
	GLuint m_uipRenderbuffer[RENDER_BUFFER_TOTAL];
	GLuint m_uipFramebuffer[FRAME_BUFFER_TOTAL];
	GLuint m_uipFrametexture[FRAME_BUFFER_TOTAL];
	GLuint m_ui32Fbo[8];
	unsigned int m_ui32BackVertexStride;
	GLuint *uiConfig;
	
	GLuint *uiConfigAlpha;
	GLuint *uiBcConfigFirst;
	GLuint *uiBcConfigLast;
	
	GLfloat *fVerticesFront;
	GLfloat *fVerticesRear;
	GLfloat *fVerticesLeft;
	GLfloat *fVerticesRight;
	GLfloat *fVerticesFrontLeft;
	GLfloat *fVerticesRearLeft;
	GLfloat *fVerticesFrontRight;
	GLfloat *fVerticesRearRight;
	
	GLushort *FrontIndex;
	GLushort *RearIndex;
	GLushort *LeftIndex;
	GLushort *RightIndex;
	GLushort *FrontLeftIndex;
	GLushort *RearLeftIndex;
	GLushort *FrontRightIndex;
	GLushort *RearRightIndex;
	
	
	
	GLfloat *fBCVerticesFrontLeft;
	GLfloat *fBCVerticesFrontRight;
	GLfloat *fBCVerticesRearLeft;
	GLfloat *fBCVerticesRearRight;
	GLfloat *fBCVerticesLeftFront;
	GLfloat *fBCVerticesRightFront;
	GLfloat *fBCVerticesLeftRear;
	GLfloat *fBCVerticesRightRear;
	
	
	GLushort *BCFrontLeftIndex;
	GLushort *BCFrontRightIndex;
	GLushort *BCRearLeftIndex;
	GLushort *BCRearRightIndex;
	GLushort *BCLeftFrontIndex;
	GLushort *BCRightFrontIndex;
	GLushort *BCLeftRearIndex;
	GLushort *BCRightRearIndex;


	int				m_ui32VertexStride;

struct	{		
	    GLuint uiId;	
		GLuint auiLoc[eNumUniforms];	
		}	m_ShaderProgram;

struct	{		
	    GLuint uiId;	
		GLuint auiLoc[eNumUniforms];	
		}	m_BCShaderProgram;



GLuint programObject;
GLuint BCprogramObject;	


};

#endif //#ifndef __GL_SV_DEMO_H__
