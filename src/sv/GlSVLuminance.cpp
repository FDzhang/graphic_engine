
//#include "../inc/common.h"
#include "GlSVLuminance.h"
#include "../XrCore/XrSrc/3rd/XrFileLoader.h"
#include "AVMData.h"

/*----------------------------------------------


---------------DEFINES-------------------------


----------------------------------------------*/
extern	unsigned int VideoTextureId[4];

#ifdef WIN32
#define _BEVPATH_ "./svres/BEV/"

#else
#define _BEVPATH_ "/opt/svres/BEV/"
#endif



char c_LBCVertShaderSrcFile[] = _BEVPATH_"BCVertShader.vtx";
char c_LBCRenderFragShaderSrcFile[] = _BEVPATH_"BCRenderFragShader.frg";
char c_LBCReadFragShaderSrcFile[] = _BEVPATH_"BCReadFragShader.frg";

#define NUMBER_PER_VERTEX 7
#define FRAMEBUFFER_NUMBER_PER_VERTEX 6
//#define FRAME_BUFFER_TEXT_WIDTH 280
//#define FRAME_BUFFER_TEXT_HEIGHT 320
#define FRAME_BUFFER_TEXT_WIDTH 108
#define FRAME_BUFFER_TEXT_HEIGHT 216

#define TEXTURE_BUFFER_TEXT_WIDTH 640
#define TEXTURE_BUFFER_TEXT_HEIGHT 480

#define GPU_LOG //
enum EVertexAttrib {	
VERTEX_ARRAY,NORMAL_ARRAY, TEXCOORD_ARRAY,TEXT_ALPHA,TEXT_LINEAR,eNumAttribs };





const char* g_aszAttribNames[] = {	"myVertex" ,"myNormal","myUV","myAlpha","myCofLinear"};

const char* g_aszBackAttribNames[] = {
	"inVertex", "inNormal", "inTexCoords"
};


const char* g_aszBackUniformNames[] = {
	 "sampler2d"
};
const char* g_aszUniformNames[] = {"sampler2d" };



GLfloat *pfDataSecond;
GLushort *pucIndexSecond;

GLfloat *pfDataThird;
GLushort *pucIndexThird;


//GLuint	m_uiTexture[17];
#define RECT_START_X 0.0 
#define RECT_START_Y 0.0
#define RECT_STEP_X  0.5
#define RECT_STEP_Y  0.25

float fTemp[]=
{

-1.0,1.0,0.0,RECT_START_X,RECT_STEP_Y,1.0,//k1
  1.0,1.0,0.0,RECT_STEP_X,RECT_STEP_Y,1.0,
  -1.0,-1.0,0.0,RECT_START_X,RECT_START_Y,1.0,
  1.0,-1.0,0.0,RECT_STEP_X,RECT_START_Y,1.0,  
 -1.0,1.0,0.0,RECT_START_X+RECT_STEP_X,RECT_STEP_Y,1.0,//k2
  1.0,1.0,0.0,RECT_STEP_X+RECT_STEP_X,RECT_STEP_Y,1.0,
  -1.0,-1.0,0.0,RECT_START_X+RECT_STEP_X,RECT_START_Y,1.0,
  1.0,-1.0,0.0,RECT_STEP_X+RECT_STEP_X,RECT_START_Y,1.0,  
 -1.0,1.0,0.0,RECT_START_X,2*RECT_STEP_Y,1.0,//k3
  1.0,1.0,0.0,RECT_STEP_X,2*RECT_STEP_Y,1.0,
  -1.0,-1.0,0.0,RECT_START_X,RECT_STEP_Y,1.0,
  1.0,-1.0,0.0,RECT_STEP_X,RECT_STEP_Y,1.0,    
 -1.0,1.0,0.0,RECT_START_X+RECT_STEP_X,2*RECT_STEP_Y,1.0,//k4
  1.0,1.0,0.0,RECT_STEP_X+RECT_STEP_X,2*RECT_STEP_Y,1.0,
  -1.0,-1.0,0.0,RECT_START_X+RECT_STEP_X,RECT_STEP_Y,1.0,
  1.0,-1.0,0.0,RECT_STEP_X+RECT_STEP_X,RECT_STEP_Y,1.0,  
 -1.0,1.0,0.0,RECT_START_X,3*RECT_STEP_Y,1.0,//k5
  1.0,1.0,0.0,RECT_STEP_X,3*RECT_STEP_Y,1.0,
  -1.0,-1.0,0.0,RECT_START_X,2*RECT_STEP_Y,1.0,
  1.0,-1.0,0.0,RECT_STEP_X,2*RECT_STEP_Y,1.0,  
 -1.0,1.0,0.0,RECT_START_X+RECT_STEP_X,3*RECT_STEP_Y,1.0,//k6
  1.0,1.0,0.0, RECT_STEP_X+RECT_STEP_X,3*RECT_STEP_Y,1.0,
  -1.0,-1.0,0.0,RECT_START_X+RECT_STEP_X,2*RECT_STEP_Y,1.0,
  1.0,-1.0,0.0, RECT_STEP_X+RECT_STEP_X,2*RECT_STEP_Y,1.0,  
 -1.0,1.0,0.0,RECT_START_X,4*RECT_STEP_Y,1.0,//k7
  1.0,1.0,0.0,RECT_STEP_X,4*RECT_STEP_Y,1.0,
  -1.0,-1.0,0.0,RECT_START_X,3*RECT_STEP_Y,1.0,
  1.0,-1.0,0.0,RECT_STEP_X,3*RECT_STEP_Y,1.0, 
 -1.0,1.0,0.0,RECT_START_X+RECT_STEP_X,4*RECT_STEP_Y,1.0,//k8
  1.0,1.0,0.0,RECT_STEP_X+RECT_STEP_X,4*RECT_STEP_Y,1.0,
  -1.0,-1.0,0.0,RECT_START_X+RECT_STEP_X,3*RECT_STEP_Y,1.0,
  1.0,-1.0,0.0,RECT_STEP_X+RECT_STEP_X,3*RECT_STEP_Y,1.0,    
};





GLuint CarViewIndex[]={0,2,1,1,2,3};
GLuint glErrorReturn = 0;








#define GL_CHECK_ERROR   glErrorReturn=glGetError();\
	                                           if(glErrorReturn != 0)\
	                                           {\
                                                       PRINT_GL_ERROR("\r\n glGetError return 0x%x at file %s line%d",glErrorReturn,__FILE__,__LINE__);\
	                                           }
/****************************************

----------referenced functions-------------------


*************************************************/


/************************************************

---------functions---------------

/************************************************/

GLuint LoadShader ( GLenum type, const char *shaderSrc )
{
   GLuint shader;
   GLint compiled;
   
   // Create the shader object
   shader = glCreateShader ( type );

   if ( shader == 0 )
   	return 0;

   // Load the shader source
   glShaderSource ( shader, 1, &shaderSrc, NULL );
   
   // Compile the shader
   glCompileShader ( shader );

   // Check the compile status
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled ) 
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );
      
      if ( infoLen > 1 )
      {
         char* infoLog =(char *) malloc (sizeof(char) * infoLen );
		 // buffer file %s,line %d",__FILE__,__LINE__);

         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
         printf ( "Error compiling shader:\n%s\n", infoLog );      
         
         free ( infoLog );
      }

      glDeleteShader ( shader );
      return 0;
   }

   return shader;

}
//XiaQing
int ReadPixel(GLint *eReadType,GLint *eReadFormat,int *size)
{
    glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE,eReadType);
    glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT,eReadFormat);
    switch(*eReadType)
	{
       case GL_UNSIGNED_BYTE:
	   	switch(*eReadFormat)
	   	{
		case GL_RGBA:
			*size = 4;
		    break;
			case GL_RGB:
				*size = 3;
				break;
			case GL_LUMINANCE_ALPHA:
				*size=2;
			break;
			case GL_ALPHA:
			case GL_LUMINANCE:
				*size=1;
			break;
			default:
				*size=4;
			break;
	   	}
		break;
//		case GL_UNSIGNED_SHORT_444:
		//case GL_UNSIGNED_SHART_5_5_5_1:
		case GL_UNSIGNED_SHORT_5_6_5:
			*size = 2;
		break;	
    }
	return TRUE;

}

int GlSVLuminance::RenderFramebufferScene(unsigned char ucSingleViewSel)
{
    unsigned int uiIndex[6]={0,2,1,1,2,3};
	float fmatrix[] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	float temp = 0.0;

	

	GLubyte ucpixel[16]={0,};

	int Index=0;
    GLint eReadType;
    GLint eReadFormat;
    GLint size=0;
	int loop = 0;
	static int cnt=0;
	int temptemptemp=0;
	//for test print texture data to file for test.
	temp = (float)TEXTURE_BUFFER_TEXT_WIDTH*FRAME_BUFFER_TEXT_HEIGHT/800;
	glUseProgram(m_BCShaderProgram.uiId);
	GL_CHECK_ERROR;

        //PRINT_GL_ERROR("\r\nLine 696  in RenderFramebuffer glUniformMatrix4fv returns 0x%x",glGetError());	
		glViewport(0, 0,1, 1);
	glUniform1i(m_BCShaderProgram.auiLoc[eSmpleLoc],0);
	GL_CHECK_ERROR;
	

	
	glDisable(GL_BLEND);


	GL_CHECK_ERROR;
    //first draw to the frame buffer.
	glBindFramebuffer(GL_FRAMEBUFFER,m_uipFramebuffer[1]);
	
	int temptemp= glCheckFramebufferStatus(GL_FRAMEBUFFER);
	GL_CHECK_ERROR;
	//glBindFramebuffer(GL_FRAMEBUFFER,0);	
	//glClearColor(1.0,0.0,0.0,1.0);
	GL_CHECK_ERROR;
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GL_CHECK_ERROR;
	

	glBindTexture(GL_TEXTURE_2D, m_uipFrametexture[0]);
	GL_CHECK_ERROR;
	cnt++;
    for(Index=0;Index<8;Index++)
    {
    	glBindBuffer(GL_ARRAY_BUFFER, m_ui32Fbo[Index]);
	GL_CHECK_ERROR;

    	
    	glEnableVertexAttribArray(VERTEX_ARRAY);
	GL_CHECK_ERROR;
    	glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, m_ui32BackVertexStride, 0);
	GL_CHECK_ERROR;
    	
    	// Pass the texture coordinates data
    	glEnableVertexAttribArray(TEXCOORD_ARRAY);
	GL_CHECK_ERROR;
    	glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, m_ui32BackVertexStride, (void*) (sizeof(GLfloat) * 3) /* Uvs start after the position */);
  
	GL_CHECK_ERROR;  	
    	glEnableVertexAttribArray(TEXT_ALPHA);
	GL_CHECK_ERROR;
    	glVertexAttribPointer(TEXT_ALPHA, 1, GL_FLOAT, GL_FALSE, m_ui32BackVertexStride, (void*) (sizeof(GLfloat) * 5) /* Uvs start after the position */);
 
	GL_CHECK_ERROR;   	
    	
    	glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,uiIndex);
	GL_CHECK_ERROR;

		ReadPixel(&eReadType,&eReadFormat,&size);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
temptemptemp = eglGetError();
		GPU_LOG("\r\nchanel[%d] start to read pixel",Index);
		//glReadBuffer( GL_FRONT );

        glReadPixels(0,0,1,1,0x1908,0x1401,&ucpixel[0]);
temptemptemp = eglGetError();
	GL_CHECK_ERROR;

	// PRINT_GL_ERROR("\r\n%d index",Index); 
        GPU_LOG("\r\nchanel[%d] finish to read pixel value is %d",Index,ucpixel[0]);
        
        if(cnt%100 == 99)
        {
           // printf("\r\n uiAerage[%d]:",Index);
        }
        for(loop = 0;loop<3;loop++)
        {
            m_uiAverageIllum[Index][loop]=ucpixel[loop];
           // if(cnt%100 == 99)
            //printf("    [%d]=%d;   ",loop, m_uiAverageIllum[Index][loop]);        
        }
        if(cnt%100 == 99)
        {
        	//printf("\r\n");
        }
    }




	GPU_LOG("\r\n end stich");

	return TRUE;
   
}
int GlSVLuminance::InitFrameBuffer(void)
{
    GLenum status;
	int i=0;
	glGenRenderbuffers(RENDER_BUFFER_TOTAL,&m_uipRenderbuffer[0]);
	GL_CHECK_ERROR;
	glGenFramebuffers(FRAME_BUFFER_TOTAL,&m_uipFramebuffer[0]);	
	GL_CHECK_ERROR;
    glGenTextures(RENDER_BUFFER_TOTAL,&m_uipFrametexture[0]);
	GL_CHECK_ERROR;

	glBindTexture(GL_TEXTURE_2D,m_uipFrametexture[0]);
	GL_CHECK_ERROR;
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,FRAME_BUFFER_TEXT_WIDTH,FRAME_BUFFER_TEXT_HEIGHT,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
	GL_CHECK_ERROR;
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	GL_CHECK_ERROR;
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);    
	GL_CHECK_ERROR;
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	GL_CHECK_ERROR;
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	GL_CHECK_ERROR;

	glBindFramebuffer(GL_FRAMEBUFFER,m_uipFramebuffer[0]);
	GL_CHECK_ERROR;
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_uipFrametexture[0],0);
	GL_CHECK_ERROR;
    status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	GL_CHECK_ERROR;
	if(GL_FRAMEBUFFER_COMPLETE == status)
	{
	   printf("succeed \n");
	}
	else
	{
	    printf("failed \n");
		return FALSE;
	}
    for(i=0;i<8;i++)
    {
        glGenBuffers(1, &m_ui32Fbo[i]);
        
	GL_CHECK_ERROR;
        m_ui32BackVertexStride = FRAMEBUFFER_NUMBER_PER_VERTEX * sizeof(GLfloat); // 3 floats for the pos, 2 for the UVs,3for normals
        
        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_ui32Fbo[i]);
	GL_CHECK_ERROR;
        
        // Set the buffer's data
        glBufferData(GL_ARRAY_BUFFER,4* m_ui32BackVertexStride, &fTemp[i*FRAMEBUFFER_NUMBER_PER_VERTEX*4], GL_STATIC_DRAW);
     
	GL_CHECK_ERROR;   
        // Unbind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
	GL_CHECK_ERROR;
    }

    glBindTexture(GL_TEXTURE_2D,m_uipFrametexture[1]);
	GL_CHECK_ERROR;
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,1,1,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
	GL_CHECK_ERROR;
	
	//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,FRAME_BUFFER_TEXT_WIDTH,FRAME_BUFFER_TEXT_HEIGHT,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,NULL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	GL_CHECK_ERROR;
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);    
	GL_CHECK_ERROR;
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	GL_CHECK_ERROR;
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	GL_CHECK_ERROR;

	glBindFramebuffer(GL_FRAMEBUFFER,m_uipFramebuffer[1]);
	GL_CHECK_ERROR;
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_uipFrametexture[1],0);
	GL_CHECK_ERROR;
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	GL_CHECK_ERROR;
	if(GL_FRAMEBUFFER_COMPLETE == status)
	{
	   printf("succeed \n");
	}
	else
	{
	    printf("failed \n");
		return FALSE;
	}
    return TRUE;
	
}

GlSVLuminance::GlSVLuminance()
{

	uiBcConfigFirst = NULL;
	uiBcConfigLast=NULL;
	
	

	
	BCFrontLeftIndex=NULL;
	BCFrontRightIndex=NULL;
	BCRearLeftIndex=NULL;
	BCRearRightIndex=NULL;
	BCLeftFrontIndex=NULL;
	BCRightFrontIndex=NULL;
	BCLeftRearIndex=NULL;
	BCRightRearIndex=NULL;
}


void GlSVLuminance::SetLuminance(unsigned int **pInput)
{
    *pInput = &m_uiAverageIllum[0][0];
}


int GlSVLuminance::Init()
{

	//InitVideoTexture(pDisplayContext);


	String vShaderStr,fShaderStr,fBCShaderStr;
	LoadTextFromFile((String)c_LBCVertShaderSrcFile, &vShaderStr);
	LoadTextFromFile((String)c_LBCRenderFragShaderSrcFile,&fShaderStr);
	LoadTextFromFile((String)c_LBCReadFragShaderSrcFile,&fBCShaderStr);

	
 
    GLuint vertexShader;
    GLuint fragmentShader;
    GLint linked;
    GLint uniforms;
	float temp;
	GLfloat *pVertex;
    int i = 0;
	GLenum BufferConfig=GL_STREAM_DRAW;

	
    // Load the vertex/fragment shaders
    vertexShader = LoadShader ( GL_VERTEX_SHADER, vShaderStr );
    fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, fShaderStr );
   
    // Create the program object
    programObject = glCreateProgram ( );
    
    if ( programObject == 0 )
   	return 0;
   
    glAttachShader ( programObject, vertexShader );
    glAttachShader ( programObject, fragmentShader );
    //Bind Attrib
    for(i = 0; i < eNumAttribs; ++i) 
    {	  
   	  glBindAttribLocation(programObject, i, g_aszAttribNames[i]);	
    }
    // Link the program
    glLinkProgram ( programObject );
    glGetProgramiv(programObject, GL_ACTIVE_UNIFORMS, &uniforms);
   
    // Check the link status
    glGetProgramiv ( programObject, GL_LINK_STATUS, &linked );
   
    if ( !linked ) 
    {
      	GLint infoLen = 0;
      
      	glGetProgramiv ( programObject, GL_INFO_LOG_LENGTH, &infoLen );
      	
      	if ( infoLen > 1 )
      	{
      	   char* infoLog =(char*) malloc (sizeof(char) * infoLen );
      // buffer file %s,line %d",__FILE__,__LINE__);
      	   glGetProgramInfoLog ( programObject, infoLen, NULL, infoLog );
      	   printf( "Error linking program:\n%s\n", infoLog );			
      	   
      	   free ( infoLog );
      	}
      
      
      	
      	glDeleteProgram ( programObject );
      	return FALSE;
    }
    m_ShaderProgram.uiId = programObject;
    
    for (i = 0; i < eBackNumUniforms; ++i) 
    {	   
        m_ShaderProgram.auiLoc[i] = glGetUniformLocation(m_ShaderProgram.uiId, g_aszBackUniformNames[i]);   
       // PRINT_GL_ERROR("\r\n glGetUniformLocation %s in RegularShader return 0x%x!",g_aszBackUniformNames[i],glGetError());		
	   GL_CHECK_ERROR;

    }

    //Init BC Program
    
    vertexShader = LoadShader ( GL_VERTEX_SHADER, vShaderStr );
    fragmentShader = LoadShader ( GL_FRAGMENT_SHADER, fBCShaderStr );
    
    // Create the program object
    BCprogramObject = glCreateProgram ( );
    
    if ( BCprogramObject == 0 )
    return 0;
    
    glAttachShader ( BCprogramObject, vertexShader );
    glAttachShader ( BCprogramObject, fragmentShader );
    //Bind Attrib
    for(i = 0; i < eNumAttribs; ++i) 
    {	
        glBindAttribLocation(BCprogramObject, i, g_aszAttribNames[i]);  
    }
    // Link the program
    glLinkProgram ( BCprogramObject );
    glGetProgramiv(BCprogramObject, GL_ACTIVE_UNIFORMS, &uniforms);
    
    // Check the link status
    glGetProgramiv ( BCprogramObject, GL_LINK_STATUS, &linked );
    
    if ( !linked ) 
    {
        GLint infoLen = 0;
        
        glGetProgramiv ( BCprogramObject, GL_INFO_LOG_LENGTH, &infoLen );
        
        if ( infoLen > 1 )
        {
         char* infoLog =(char*)  malloc (sizeof(char) * infoLen );
        // buffer file %s,line %d",__FILE__,__LINE__);
         glGetProgramInfoLog ( BCprogramObject, infoLen, NULL, infoLog );
         printf ( "Error linking program:\n%s\n", infoLog );			  
         
         free ( infoLog );
        }
             
        glDeleteProgram ( BCprogramObject );
        return FALSE;
    }
    
    m_BCShaderProgram.uiId = BCprogramObject;
    
    for (i = 0; i < eNumUniforms; ++i) 
    {	   
        m_BCShaderProgram.auiLoc[i] = glGetUniformLocation(m_BCShaderProgram.uiId, g_aszUniformNames[i]);  
        //PRINT_GL_ERROR("\r\n glGetUniformLocation %s in BCShader return 0x%x!",g_aszUniformNames[i],glGetError());
		GL_CHECK_ERROR;
    }
   // glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	
    InitFrameBuffer();
	
	glUseProgram ( m_ShaderProgram.uiId  );    

	GL_CHECK_ERROR;



	

    AVMData::GetInstance()->m_2D_lut->GetLutConfig(&uiBcConfigFirst,2);
    AVMData::GetInstance()->m_2D_lut->GetLutConfig(&uiBcConfigLast,3);

    AVMData::GetInstance()->m_2D_lut->GetLutIndex(&BCFrontLeftIndex,8);
    AVMData::GetInstance()->m_2D_lut->GetLutIndex(&BCFrontRightIndex,9);
    AVMData::GetInstance()->m_2D_lut->GetLutIndex(&BCRearLeftIndex,10);
    AVMData::GetInstance()->m_2D_lut->GetLutIndex(&BCRearRightIndex,11);
    AVMData::GetInstance()->m_2D_lut->GetLutIndex(&BCLeftFrontIndex,12);
    AVMData::GetInstance()->m_2D_lut->GetLutIndex(&BCRightFrontIndex,13);
    AVMData::GetInstance()->m_2D_lut->GetLutIndex(&BCLeftRearIndex,14);
    AVMData::GetInstance()->m_2D_lut->GetLutIndex(&BCRightRearIndex,15);	



	m_ui32VertexStride = NUMBER_PER_VERTEX * sizeof(GLfloat);

	//use this for test.
    for(int i=0;i<8;i++)
    {
		AVMData::GetInstance()->m_2D_lut->GetLutData(&pVertex,8+i);

	
        glGenBuffers(1, &m_ui32VboForBC[i]);
    	GL_CHECK_ERROR;
        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, m_ui32VboForBC[i]);	
    	GL_CHECK_ERROR;
        // Set the buffer's data
        if(i<4)
        glBufferData(GL_ARRAY_BUFFER, uiBcConfigFirst[2*i+1]* m_ui32VertexStride, pVertex, BufferConfig);	 
		else		
        glBufferData(GL_ARRAY_BUFFER, uiBcConfigLast[2*(i-4)+1]* m_ui32VertexStride, pVertex, BufferConfig);	 
        // Unbind the VBO
    	GL_CHECK_ERROR;
        glBindBuffer(GL_ARRAY_BUFFER, 0);    
    }
	
	return 0;
}


int GlSVLuminance::Update(void)
{
    //glEnable(GL_DEPTH_TEST);
	GL_CHECK_ERROR;
//    glDepthMask(GL_TRUE);
	GL_CHECK_ERROR;
	glDisable(GL_CULL_FACE);

	GL_CHECK_ERROR;

	//glViewport(0, 0, 720,480);
	GL_CHECK_ERROR;


	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GL_CHECK_ERROR;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glViewport ( 0, 0, FRAME_BUFFER_TEXT_WIDTH, FRAME_BUFFER_TEXT_HEIGHT );
	GL_CHECK_ERROR;
	//glClearColor(0.0,0.0,0.0,1.0);
	GL_CHECK_ERROR;



    GLint i =0;
    GLfloat light_value[16] = {
    1.0, 0.0f,  0.0f, 0.0f,
    0.0f, 1.0f,  0.0f,  0.0f,
    0.0f, 0.0f,  1.0f, 0.0f,
    0.0f, 0.0f, 0.0f,  1.0f
    };
	   

	
    static int trend= 0;

    

   // glClear ( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //	glClearColor(0.0,0.0,0.0,1.0);
    // Use the program object
    glUseProgram ( m_ShaderProgram.uiId);
	GL_CHECK_ERROR;
    GPU_LOG("\r\nDraw BC overlap");
    glBindFramebuffer(GL_FRAMEBUFFER,m_uipFramebuffer[0]);   
	
	//glViewport ( 0, 0, 1280, 720 );
  // glBindFramebuffer(GL_FRAMEBUFFER,0);   
	//glViewport ( 0, 0, 704, 480 );
	GL_CHECK_ERROR;
    //glBindFramebuffer(GL_FRAMEBUFFER,0);
   int temptemp= glCheckFramebufferStatus(GL_FRAMEBUFFER);

  
    
    glUniform1i(m_ShaderProgram.auiLoc[eSmpleLoc], 0);   
	GL_CHECK_ERROR;
    
    
    glDisable(GL_BLEND); 
	GL_CHECK_ERROR; 
    int Old_engine_chanel_num;
	int New_engine_chanel_num;
    for (i =0;i<8;i++)
    {	  
        if(5==i)
        {
            //BindVideoTexture(3);
			Old_engine_chanel_num = 3;
           
        }
        else if(6==i)
        {
           // BindVideoTexture(2);
			
			Old_engine_chanel_num = 2;
		   
        }
        else
        {
            //BindVideoTexture(i/2);
			
			Old_engine_chanel_num = i/2;
        }
        if(3 == Old_engine_chanel_num)
        {
			AVMData::GetInstance()->m_cam_source->UseCameraTexture(right_camera_index);
        }
		else if(2 == Old_engine_chanel_num)
        {
			AVMData::GetInstance()->m_cam_source->UseCameraTexture(left_camera_index);
        }
		else if(1 == Old_engine_chanel_num)
        {
			AVMData::GetInstance()->m_cam_source->UseCameraTexture(rear_camera_index);
        }
		else if(0 == Old_engine_chanel_num)
        {
			AVMData::GetInstance()->m_cam_source->UseCameraTexture(front_camera_index);
        }	

        glBindBuffer(GL_ARRAY_BUFFER, m_ui32VboForBC[i]);

        glEnableVertexAttribArray(VERTEX_ARRAY);   
	GL_CHECK_ERROR;
        glVertexAttribPointer(VERTEX_ARRAY, 3, GL_FLOAT, GL_FALSE, m_ui32VertexStride, 0); 
	GL_CHECK_ERROR;
        // Pass the texture coordinates data	
        glEnableVertexAttribArray(TEXCOORD_ARRAY); 
	GL_CHECK_ERROR;
        glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, m_ui32VertexStride, (void*) (sizeof(GLfloat) * 3)) ;
	GL_CHECK_ERROR;
        
        glEnableVertexAttribArray(TEXT_ALPHA); 
	GL_CHECK_ERROR;
        glVertexAttribPointer(TEXT_ALPHA, 1, GL_FLOAT, GL_FALSE, m_ui32VertexStride, (void*) (sizeof(GLfloat) * 5) /* Uvs start after the position */);  
  
	GL_CHECK_ERROR;     
	glEnableVertexAttribArray(TEXT_LINEAR);
	GL_CHECK_ERROR;
        glVertexAttribPointer(TEXT_LINEAR, 1, GL_FLOAT, GL_FALSE, m_ui32VertexStride, (void*) (sizeof(GLfloat) * 6) /* Uvs start after the position */);
        
	GL_CHECK_ERROR;
        
        if(i<4)
        {
            if(0 == i)
            {		  
                glDrawElements(GL_TRIANGLES,uiBcConfigFirst[2*(i+1)],GL_UNSIGNED_SHORT,BCFrontLeftIndex);  
	GL_CHECK_ERROR;
            }
            else if(1 == i)
            {		  
                glDrawElements(GL_TRIANGLES,uiBcConfigFirst[2*(i+1)],GL_UNSIGNED_SHORT,BCFrontRightIndex);  
	GL_CHECK_ERROR; 
            }
            else if(2 == i)
            {		  
                glDrawElements(GL_TRIANGLES,uiBcConfigFirst[2*(i+1)],GL_UNSIGNED_SHORT,BCRearLeftIndex);  
	GL_CHECK_ERROR;
            }	  
            else if(3 == i)
            {		  
                glDrawElements(GL_TRIANGLES,uiBcConfigFirst[2*(i+1)],GL_UNSIGNED_SHORT,BCRearRightIndex);	
	GL_CHECK_ERROR;  
            }		  
        }
        else
        {
            if(4 == i)
            {		  
               glDrawElements(GL_TRIANGLES,uiBcConfigLast[2*(i-3)],GL_UNSIGNED_SHORT,BCLeftFrontIndex);  
	GL_CHECK_ERROR;
            }
            else if(5 == i)
            {		  
                glDrawElements(GL_TRIANGLES,uiBcConfigLast[2*(i-3)],GL_UNSIGNED_SHORT,BCRightFrontIndex); 
	GL_CHECK_ERROR;  
            }
            else if(6 == i)
            {		  
                glDrawElements(GL_TRIANGLES,uiBcConfigLast[2*(i-3)],GL_UNSIGNED_SHORT,BCLeftRearIndex);  
	GL_CHECK_ERROR;
            }	  
            else if(7 == i)
            {		  
                glDrawElements(GL_TRIANGLES,uiBcConfigLast[2*(i-3)],GL_UNSIGNED_SHORT,BCRightRearIndex);	
	GL_CHECK_ERROR;  
            }		  
            
        }
     }
	 GPU_LOG("finish draw the overlap aera\n");
	 RenderFramebufferScene(0);
	 GPU_LOG("start to draw overlay\n");
	// glUniform1i(m_ShaderProgram.auiLoc[eTextureType],1);	
	GL_CHECK_ERROR;	  
	 GPU_LOG("\r\n start to draw overlay");
	GL_CHECK_ERROR;
         //PRINT_GL_ERROR("\r\nLine 1907  in update  glUniformMatrix4fv returns 0x%x",glGetError());	 
      glBindFramebuffer(GL_FRAMEBUFFER,0);		 
	  glBindTexture(GL_TEXTURE_2D, 0);
	  glBindBuffer(GL_ARRAY_BUFFER, 0);

	return 0;
}



