#ifndef __C_SHADER_OBJECT_H__
#define __C_SHADER_OBJECT_H__
#include "utilityGLES2.h"
#include "../intrinsic.h"
#include "CGLESShaderHelper.h"

class CShaderObject
{
public:
	CShaderObject() { isInitialized = 0; }
	~CShaderObject() {
	}
	int GenProgram(const char* vertexShader, const char* fragmentShader, const char** Attribs, int AttribsArraySize, const char** Uniforms, int UniformsArraySize, const char** Textures, int TextureArraySize);
	int LoadFromFile(String vs, String ps);
	int GenLocation(const char** Attribs, int AttribsArraySize, const char** Uniforms, int UniformsArraySize, const char** Textures, int TextureArraySize);
	void Release();
	int Init();
	//int	auiLocation[32];
	unsigned int 	uiFragShader, uiVertShader;	
	unsigned int	uiProgramObject;				
	int	isInitialized;
	CGLESShaderHelper helper;

private:
	friend class CRenderDevice; 
	friend class CRenderContext; 
	
	//ID3D11VertexShader*                 m_pDX11VertexShader;
	//ID3D11PixelShader*                  m_pDX11PixelShader;
};

#endif // __CSHADER_OBJECT_H__
