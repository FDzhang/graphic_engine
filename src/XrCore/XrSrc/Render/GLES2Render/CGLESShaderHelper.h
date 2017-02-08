#ifndef __CGLES_SHADER_HELPER_H__
#define __CGLES_SHADER_HELPER_H__

#include "utilityGLES2.h"
#include "../intrinsic.h"
#include "../../Platform/XrCrt.h"
//#include "XrVertexLayout.h"

class CGLESShaderHelper
{
public:
	enum DataType {
		Type_Int                            = 0x00000002,
		Type_Float						    = 0x00000004,
		Type_Vec2						    = 0x00000008,
		Type_Vec3							= 0x0000000C,
		Type_Vec4							= 0x00000010,
		Type_Mat3							= 0x00000024,
		Type_Mat4							= 0x00000040,
	}; 
	enum UniformType {
		UniformType_VS						    = 0x00000000,
		UniformType_PS						    = 0x00000001,
	};
	CGLESShaderHelper()
	{
	}
	~CGLESShaderHelper() {
		Release();
	}

	String GetAttributeNames(Int32 id);
	String GetUniformNames(Int32 id);
	String GetSamplerNames(Int32 id);

	Int32 GetAttributeNum();
	Int32 GetUniformNum();
	Int32 GetSamplerNum();

	Int32 GetVertexSize();

	Void Release();

	Int32 GetIBO() { return m_iboId; }
	Void Parse(ConstString vs, ConstString fs);

	Void UpdateVSUniform(Void* pData, int offset, int size);
	Void UpdatePSUniform(Void* pData, int offset, int size);

	Void BindCurrentVertexLayout(class CVertexLayout* layout);

	Int32  uniformLocations[64];

private:
	String GetElementSize(String src, DataType* size);
	Void ReadBackElementCount(Int32* countPos, String src);

	Int32 GetVSUniformSize();
	Int32 GetPSUniformSize();
	Void UpdateUniform(Int32 loc,Void* pData, DataType type, Int32 count);

	String WriteAtbUni(String dst, DataType* size, String src);
	String WriteSpl(String dst, String src);
	String NextLine(String str);
	Boolean IsSampler(String str);

	String attributeNames[8];
	//Int32 attributeIndex[8];
	DataType attributeSizes[8];

	String uniformNames[64];
	DataType  uniformSizes[64];
	Int32  uniformElementCounts[64];
	UniformType  uniformType[64];

	String samplerNames[16];

	Int32 attributeNum;
	Int32 uniformNum;
	Int32 samplerNum;

	int m_size;
	unsigned int m_iboId;
};

#endif // __CGLES_SHADER_HELPER_H__

