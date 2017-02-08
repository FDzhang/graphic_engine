#include "CShaderObject.h"


int CShaderObject::GenProgram(const char* vertexShader, const char* fragmentShader, const char** Attribs, int AttribsArraySize, const char** Uniforms, int UniformsArraySize, const char** Textures, int TextureArraySize)
{
	isInitialized = 0;
	return -1;
}



int CShaderObject::LoadFromFile(String vs, String ps)
{
	return -1;
}

int CShaderObject::GenLocation(const char** Attribs, int AttribsArraySize, const char** Uniforms, int UniformsArraySize, const char** Textures, int TextureArraySize)
{
	int i;

	return 0;
}

void CShaderObject::Release()
{
}