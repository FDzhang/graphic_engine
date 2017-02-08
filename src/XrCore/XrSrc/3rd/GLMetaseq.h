#ifndef __GLMETASEQ_H__
#define __GLMETASEQ_H__

#define MAX_TEXTURE				100			                                          
#define MAX_OBJECT				50			                                                          
#define SIZE_STR				256			                                    
#define DEF_IS_LITTLE_ENDIAN	1			                                           
#define DEF_USE_LIBJPEG			0			                                             
#define DEF_USE_LIBPNG			0			                                             
                      
#ifdef D_JPEG
	#undef	DEF_USE_LIBJPEG
	#define	DEF_USE_LIBJPEG 1
#endif
                         
#ifdef D_NO_JPEG
	#undef	DEF_USE_LIBJPEG
	#define	DEF_USE_LIBJPEG 0
#endif
      
#ifdef D_PNG
	#undef	DEF_USE_LIBPNG
	#define	DEF_USE_LIBPNG 1
#endif

                        
#ifdef D_NO_PNG
	#undef	DEF_USE_LIBPNG
	#define	DEF_USE_LIBPNG 0
#endif                                                                                                                                                             

#ifdef WIN32
	#include <windows.h>
#else
	#ifndef MAX_PATH
		#define MAX_PATH    256
	#endif
	#ifndef TRUE
		#define TRUE    (1==1)
	#endif
	#ifndef FALSE
	    #define FALSE   (1!=1)
	#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#else
	                                
#include <GLES2/gl2.h>
                        
#endif

#if DEF_USE_LIBJPEG

	#define XMD_H                                               
	#ifdef FAR
		#undef FAR
	#endif

	#include "jpeglib.h"
	#pragma comment(lib,"libjpeg.lib")

#endif                                                                                                                                                                                     

#if DEF_USE_LIBPNG

	#include "png.h"
	#include "zlib.h"
	#pragma comment(lib,"libpng.lib")
	#pragma comment(lib,"zlib.lib")

#endif

#ifndef MAX
	#define MAX(a, b)  (((a) > (b)) ? (a) : (b))
#endif


                                                                                                                                                                                             

#define DEF_TGA_COLOR_MAP_FLAG_VALID	1
#define DEF_TGA_TYPE_NON				0
#define DEF_TGA_TYPE_INDEX				1
#define DEF_TGA_TYPE_FULL				2
#define DEF_TGA_TYPE_MONO				3
#define DEF_TGA_TYPE_RLEINDEX			9
#define DEF_TGA_TYPE_RLEFULL			10
#define DEF_TGA_TYPE_RLEMONO			11
#define DEF_TGA_BIT_INFO_RIGHT_TO_LEFT	0x00
#define DEF_TGA_BIT_INFO_LEFT_TO_RIGHT	0x10
#define DEF_TGA_BIT_INFO_DOWN_TO_TOP	0x00
#define DEF_TGA_BIT_INFO_TOP_TO_DOWN	0x20

typedef struct {
	unsigned char	id;
	unsigned char	color_map_flag;
	unsigned char	type;
	unsigned short	color_map_entry;
	unsigned char	color_map_entry_size;
	unsigned short	x;
	unsigned short	y;
	unsigned short	width;
	unsigned short	height;
	unsigned char	depth;
	unsigned char	bit_info;
} STR_TGA_HEAD;


                                                                                                                                                                                                         
typedef struct {
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
} glCOLOR4f;


                                                                                                                                                                                                                 
typedef struct {
	GLfloat x;
	GLfloat y;
} glPOINT2f;


                                                                                                                                                                                                                 
typedef struct tag_glPOINT3f {
	GLfloat x;
	GLfloat y;
	GLfloat z;
} glPOINT3f;


                                                                                                                                                                                          
typedef struct {
	int			n;		                                                   
	int			m;		                     
	int			v[4];	                                    
	glPOINT2f	uv[4];	              
} MQO_FACE;


                                                                                                                                                                                                                                                      
typedef struct {
	char		matname[SIZE_STR];	
	glCOLOR4f	col;				      
	GLfloat		dif[4];				            
	GLfloat		amb[4];				            
	GLfloat		emi[4];				               
	GLfloat		spc[4];				            
	GLfloat		power;				                     
	int			useTex;				                           
	char		texFile[SIZE_STR];	                              
	char		alpFile[SIZE_STR];	                                          
	GLuint		texName;			                     
} MQO_MATDATA;


                                                                                                                                                                                                                                    
typedef struct {
	char		objname[SIZE_STR];	               
	int			visible;			               
	int			shading;			                                                          
	float		facet;				                        
	int			n_face;				         
	int			n_vertex;			            
	MQO_FACE	*F;					      
	glPOINT3f	*V;					         
} MQO_OBJDATA;


                                                                                                                                                                                                
typedef struct {
	GLuint			texture_id;			                    
	int				texsize;			                           
	char			texfile[MAX_PATH];	                              
	char			alpfile[MAX_PATH];	                                          
	unsigned char	alpha;				               
} TEXTURE_POOL;


                                                                                                                                                                                                                     
typedef struct {		
	GLfloat point[3];	                         
	GLfloat normal[3];	                         
	GLfloat uv[2];		                  
} VERTEX_TEXUSE;


                                                                                                                                                                                                                        
typedef struct {
	GLfloat point[3];	                         
	GLfloat normal[3];	                         
} VERTEX_NOTEX;


                                                                                                                                                                                                                                             
typedef struct {
	char			matname[SIZE_STR];  
	int				isValidMaterialInfo;                                        
	int				isUseTexture;		                                                         
	GLuint			texture_id;			                                   
	GLuint			VBO_id;				                                                                   
	int				datanum;			            
	GLfloat			color[4];			                         
	GLfloat			dif[4];				            
	GLfloat			amb[4];				            
	GLfloat			emi[4];				               
	GLfloat			spc[4];				            
	GLfloat			power;				                     
	VERTEX_NOTEX	*vertex_p;			                                          
	VERTEX_TEXUSE	*vertex_t;			                                          
	unsigned short	*vertex_i;			
} MQO_MATERIAL;


                                                                                                                                                                                                                               
typedef struct {
	char			objname[SIZE_STR];		                        
	int				isVBOSupported;
	int				isVisible;				                                     
	int				isShadingFlat;			                                 
	int				matnum;					                           
	MQO_MATERIAL	*mat;					                        
} MQO_INNER_OBJECT;


                                                                                                                                                                                                                                                    
typedef struct {
	unsigned char		alpha;				                                                                        
	int					objnum;				                              
	MQO_INNER_OBJECT	obj[MAX_OBJECT];	                                 
} MQO_OBJECT;


                                                                                                                                                                                          
typedef MQO_OBJECT * MQO_MODEL;		                                                      


                                                                                                                                                                                          
typedef struct {
	MQO_MODEL	model;		            
	int			n_frame;	                  
} MQO_SEQUENCE;


                                                                                                                                                                                                                 
#ifdef WIN32
	#define GL_ARRAY_BUFFER_ARB	0x8892
	#define GL_STATIC_DRAW_ARB	0x88E4
	typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC)    (GLenum target, GLuint buffer);
	typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
	typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC)    (GLsizei n, GLuint *buffers);
	typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC)    (GLenum target, int size, const GLvoid *data, GLenum usage);
#endif


                                                                                                                                                                                         

#ifdef __GLMETASEQ_C__
	#define __GLMETASEQ_C__EXTERN
#else
	#define __GLMETASEQ_C__EXTERN extern
#endif

__GLMETASEQ_C__EXTERN int g_isVBOSupported;	                                                   

#ifdef WIN32	
	                                      
	__GLMETASEQ_C__EXTERN PFNGLGENBUFFERSARBPROC glGenBuffersARB;		                   
	__GLMETASEQ_C__EXTERN PFNGLBINDBUFFERARBPROC glBindBufferARB;		                   
	__GLMETASEQ_C__EXTERN PFNGLBUFFERDATAARBPROC glBufferDataARB;		                         
	__GLMETASEQ_C__EXTERN PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;	             
#endif

#undef __GLMETASEQ_C__EXTERN


                                                                                                                                                                          

#ifdef __cplusplus
extern "C" {
#endif


            
void mqoInit(void);

               
void mqoCleanup(void);

                  
MQO_MODEL mqoCreateModel(char *filename, double scale, int loadVBO);

                        
MQO_SEQUENCE mqoCreateSequence(const char *format, int n_file, double scale);

                                       
MQO_SEQUENCE mqoCreateSequenceEx(const char *format, int n_file, double scale,
								 int fade_inout, unsigned char alpha);

                        
void mqoCallModel(MQO_MODEL model);

                              
void mqoCallSequence(MQO_SEQUENCE seq, int i);

                     
void mqoDeleteModel(MQO_MODEL model);

                           
void mqoDeleteSequence(MQO_SEQUENCE seq);


#ifdef __cplusplus
}
#endif




#endif	                      


