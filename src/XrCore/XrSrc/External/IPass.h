#ifndef _IPASS_H
#define _IPASS_H

#include "xrIntrinsic.h"
#include "IResource.h"

class IVertexProgram;
class IFragmentProgram;

class IPass : virtual public IResource
{
public:
	virtual Void SetVertexProgram(IVertexProgram*) = 0;
	virtual Void SetFragmentProgram(IFragmentProgram*) = 0;
	virtual Void SetDrawMode(UInt32) = 0;
	virtual Void GenShaderObjectEx() = 0;
};

#endif