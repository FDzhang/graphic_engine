#include "CGLESShaderHelper.h"

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------

Void CGLESShaderHelper::Release()
{
	int i;
	for (i=0;i<attributeNum;i++) {
		delete attributeNames[i];
	}
	for (i=0;i<uniformNum;i++) {
		delete uniformNames[i];
	}
	for (i=0;i<samplerNum;i++) {
		delete samplerNames[i];
	}
}

String CGLESShaderHelper::GetAttributeNames(Int32 id)
{
	return attributeNames[id];
}

String CGLESShaderHelper::GetUniformNames(Int32 id)
{
	return uniformNames[id];
}

String CGLESShaderHelper::GetSamplerNames(Int32 id)
{
	return samplerNames[id];
}

Int32 CGLESShaderHelper::GetAttributeNum()
{
	return attributeNum;
}

Int32 CGLESShaderHelper::GetUniformNum()
{
	return uniformNum;
}

Int32 CGLESShaderHelper::GetSamplerNum()
{
	return samplerNum;
}

Int32 CGLESShaderHelper::GetVertexSize()
{
	Int32 size=0;
	for (Int32 i=0;i<attributeNum;i++) {
		size+=attributeSizes[i];
	}
	return size;
}

Void CGLESShaderHelper::Parse(ConstString vs, ConstString fs)
{
#define NameLen 64
	Int32 count;
	String curr, curr2;

	//GetAttributes
	count=0;
	curr = strstr((String)vs,"attribute");
	while (curr) {
		attributeNames[count] = new char[NameLen];
		curr = WriteAtbUni(attributeNames[count], &attributeSizes[count], curr);
		count++;
		curr = strstr((String)curr,"attribute");
	}
	attributeNum = count;
	 
	//GetUniforms
	count=0;
	curr = strstr((String)vs,"uniform");
	while (curr) {
		if (IsSampler(curr)) {
			curr = NextLine(curr);
			continue;
		}
		
		uniformNames[count] = new char[NameLen];
		curr = WriteAtbUni(uniformNames[count], &uniformSizes[count], curr);
		ReadBackElementCount(&uniformElementCounts[count], curr);
		uniformType[count] = UniformType_VS;
		count++;
		curr = strstr(curr,"uniform");
	}
	
	curr = strstr((String)fs,"uniform");
	while (curr) {
		if (IsSampler(curr)) {
			curr = NextLine(curr);
			curr = strstr(curr,"uniform");
			continue;
		}
		uniformNames[count] = new char[NameLen];
		curr = WriteAtbUni(uniformNames[count], &uniformSizes[count], curr);
		ReadBackElementCount(&uniformElementCounts[count], curr);
		uniformType[count] = UniformType_PS;
		count++;
		curr = strstr((String)curr,"uniform");
	}
	uniformNum = count;

	//GetSamplers
	count=0;
	curr2 = strstr((String)fs,"sampler2D");
	if (!curr2) curr = strstr((String)fs,"samplerCube");
	else curr = curr2;
	while (curr) {
		samplerNames[count] = new char[NameLen];
		curr = WriteSpl(samplerNames[count], curr);
		count++;
		curr2 = strstr((String)curr,"sampler2D");
		if (!curr2) curr = strstr((String)curr,"samplerCube");
		else curr = curr2;
	}
	samplerNum = count;
}

Void CGLESShaderHelper::ReadBackElementCount(Int32* countPos, String src)
{
	String pt = src-2;
	Int32 len=0,i;
	CHAR count[8];
	if (*pt==']') {
		pt--;
		while (*pt!='[') {
			pt--;
			len++;
		}
		pt++;
		for (i=0;i<len;i++) {
			count[i] = pt[i];
		}
		count[len]=0;
		*countPos = atoi(count);
	}
	else {
		*countPos = 1;
	}
}

String CGLESShaderHelper::NextLine(String str)
{
	while (*str != ';') {
		str++;
		if (!str) return 0;
	}
	str++;
	String temp = str;
	if (temp) {
		if (*temp == '\\') temp++;
		else return str;
	}
	if (temp) {
		if (*temp == 'n') temp++;
		else return str;
	}
	return temp;
}

Boolean CGLESShaderHelper::IsSampler(String str)
{
	if (*(str+8)=='s' || *(str+13)=='s' ||*(str+14)=='s' ||*(str+16)=='s') return true;
	else return false;
}

String CGLESShaderHelper::WriteSpl(String dst, String src)
{
	while (*src != ';') {
		src++;
		if (!src) return 0;
	}
	while (*src != ' ') {
		src--;
	}
	src++;
	while (*src != ';') {
		*dst=*src;
		dst++;
		src++;
	}
	*dst=0;
	src++;
	return src;
}
String CGLESShaderHelper::GetElementSize(String src, DataType* size)
{
	String out;
	if (*src=='f') {
		out = src+6;
		*size = Type_Float;
	}
	else if (*src=='v') {
		out = src+3;
		if (*out=='2') *size = Type_Vec2;
		else if (*out=='3') *size = Type_Vec3;
		else if (*out=='4') *size = Type_Vec4;
		out+=2;
	}
	else if (*src=='m') {
		out = src+3;
		if (*out=='3') *size = Type_Mat3;
		else if (*out=='4') *size = Type_Mat4;
		out+=2;
	}
	else if (*src=='i') {
		out = src+4;
	   *size =Type_Int ;
	}	
	return out;
}

//return nextline
String CGLESShaderHelper::WriteAtbUni(String dst, DataType* size, String src)
{
	while (*src != ';') {
		src++;
		if (!src) return 0;
	}
	while (*src != ' ') {
		src--;
	}
	src--;
	while (*src != ' ') {
		src--;
	}
	src++;
	src = GetElementSize(src, size);

	while (*src != ';') {
		if (*src == '[') {
			while (*src != ';') {
				src++;
			}
			break;
		}
		*dst=*src;
		dst++;
		src++;
	}
	*dst=0;
	src++;
	
	return src;
}

Int32 CGLESShaderHelper::GetVSUniformSize()
{
	Int32 size=0,id=0,currentSize=0;
	while (uniformType[id] != UniformType_PS && id<uniformNum) {
		currentSize+=uniformSizes[id]*uniformElementCounts[id];
		id++;
	}

	return currentSize;
}
Int32 CGLESShaderHelper::GetPSUniformSize()
{
	Int32 size=0,id=0,currentSize=0,PScounts;
	while (uniformType[id] != UniformType_PS && id<uniformNum) {
		id++;
	}
	PScounts = uniformNum-id;
	while (PScounts>0) {
		currentSize += uniformSizes[id] * uniformElementCounts[id];
		PScounts--;
		id++;
	}
	//while
	return currentSize;
}
Void CGLESShaderHelper::UpdateVSUniform(Void* pData, int offset, int size)
{
	Int32 id=0, currentPos = 0, restSize=size;
	UInt8* dataPt=(UInt8*)pData;
	while (currentPos<offset) {
		currentPos += uniformSizes[id] * uniformElementCounts[id];
		id++;
	}

	//dataPt+=currentPos;
	if (restSize==0) restSize = GetVSUniformSize()-currentPos;
	while(restSize>0) {
		UpdateUniform(uniformLocations[id], dataPt, uniformSizes[id], uniformElementCounts[id]);
		restSize-=uniformSizes[id]*uniformElementCounts[id];
		dataPt += uniformSizes[id] * uniformElementCounts[id];
		id++;
	}
}

Void CGLESShaderHelper::UpdatePSUniform(Void* pData, int offset, int size)
{
	Int32 id=0, currentPos = 0,currentPSPos = 0, restSize=size;
	UInt8* dataPt=(UInt8*)pData;

	while (uniformType[id] != UniformType_PS && id<uniformNum) {
		currentPos+=uniformSizes[id]*uniformElementCounts[id];
		id++;
	}
	while (currentPos<offset) {
		currentPos += uniformSizes[id] * uniformElementCounts[id];
		currentPSPos += uniformSizes[id] * uniformElementCounts[id];
		id++;
	}
	dataPt+=currentPos;
	if (restSize==0) restSize = GetPSUniformSize()-currentPSPos;
	while(restSize>0) {
		UpdateUniform(uniformLocations[id], dataPt, uniformSizes[id], uniformElementCounts[id]);
		restSize -= uniformSizes[id] * uniformElementCounts[id];
		dataPt += uniformSizes[id] * uniformElementCounts[id];
		id++;
	}
}

Void CGLESShaderHelper::UpdateUniform(Int32 loc, Void* pData, DataType type, Int32 count)
{
	switch (type) {
		case Type_Float:
			glUniform1fv(loc, count, (GLfloat*)pData);
			break;
		case Type_Vec2:
			glUniform2fv(loc, count, (GLfloat*)pData);
			break;
		case Type_Vec3:
			glUniform3fv(loc, count, (GLfloat*)pData);
			break;
		case Type_Vec4:
			glUniform4fv(loc, count, (GLfloat*)pData);
			break;
		case Type_Mat3:
			glUniformMatrix3fv(loc, count, FALSE, (GLfloat*)pData);
			break;
		case Type_Mat4:
			glUniformMatrix4fv(loc, count, FALSE, (GLfloat*)pData);
			break;
		case Type_Int:			
			glUniform1i(loc,*((GLint*)pData)); 	
			break;
	}
	Int32 pos=0;
}

Void CGLESShaderHelper::BindCurrentVertexLayout(CVertexLayout* layout)
{

}
