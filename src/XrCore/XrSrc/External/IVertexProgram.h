#ifndef _IVERTEXPROGRAM_H
#define _IVERTEXPROGRAM_H
#include "xrTypes.h"
#include "IResource.h"


class IVertexProgram  : virtual public IResource
{
public:
	virtual Void AddUniform(const String&) = 0;
	virtual Void AddAttribute(const String&) = 0;
	virtual Void SetVP(const String&) = 0;
};

#endif