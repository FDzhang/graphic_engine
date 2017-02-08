#include "CSampler.h"

Void CSampler::Bind(UInt32 type)
{
	UInt32 gladdress, glfiltermag, glfiltermin;
	GetGLSamplerMode(type, &gladdress, &glfiltermag, &glfiltermin );
	glTexParameterf(type, GL_TEXTURE_MIN_FILTER, glfiltermin);
	glTexParameterf(type, GL_TEXTURE_MAG_FILTER, glfiltermag);

	glTexParameterf(type, GL_TEXTURE_WRAP_S, gladdress);
	glTexParameterf(type, GL_TEXTURE_WRAP_T, gladdress);
}
