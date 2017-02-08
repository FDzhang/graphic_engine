#include "CRenderDevice.h"
#include "CSwapChain.h"
#include "../../External/xrIntrinsic.h"
#include "../../3rd/hhdds.h"
#include "../../3rd/XrFileLoader.h"
#include "CGLESShaderHelper.h"

//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------

xr_state CRenderDevice::CreateRenderState(UInt32 state, CRenderState* pRenderState)
{
	pRenderState->m_state = state;

	return XR_OK;
}

CRenderDevice::CRenderDevice()
{

}

xr_state CRenderDevice::Init()
{
	//SetDefaultDepthState(m_pd3dDevice,true,D3D11_DEPTH_WRITE_MASK_ALL,D3D11_COMPARISON_GREATER);
	//SetDefaultRenderState(m_pd3dDevice);
	return true;
}

xr_state CRenderDevice::CreateRenderTargetFromSwapChain(CSwapChain* pSwapChain, CRenderTarget* pRenderTarget)
{
	pRenderTarget->fboid = pSwapChain->fbid;
	pRenderTarget->m_renderTexture.width = pSwapChain->m_width;
	pRenderTarget->m_renderTexture.height = pSwapChain->m_height;
	return XR_OK;
}

#if 0
xr_state CRenderDevice::CreateRenderTarget(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth, CRenderTarget* pRenderTarget)
{
	GLenum err;
	UInt32 glformat, gltype,depth_format;
	pRenderTarget->m_width = width;
	pRenderTarget->m_height = height;
	pRenderTarget->GetRenderTexture()->width = width;
	pRenderTarget->GetRenderTexture()->height = height;
	pRenderTarget->GetDepthStencilTexture()->width = width;
	pRenderTarget->GetDepthStencilTexture()->height = height;

	glGenFramebuffers(1, &pRenderTarget->fboid);
	err = glGetError();
	glBindFramebuffer(GL_FRAMEBUFFER, pRenderTarget->fboid);
	err = glGetError();

	GetGLTextureFormat(format, &glformat, &gltype);

	glGenTextures(1, &pRenderTarget->GetRenderTexture()->texid);
	glBindTexture(GL_TEXTURE_2D, pRenderTarget->GetRenderTexture()->texid);
	pRenderTarget->GetRenderTexture()->type = GL_TEXTURE_2D;
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	pRenderTarget->GetRenderTexture()->samplerMode = XR_SAMPLER_CLAMP;

	glTexImage2D(GL_TEXTURE_2D, 0, glformat, width, height, 0,glformat, gltype, 0);
	err = glGetError();
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pRenderTarget->GetRenderTexture()->texid, 0);

  // Create depth buffer
	if(!depth) goto End;
	switch (depth) {
	case XR_D24:
			depth_format = GL_DEPTH_COMPONENT24_OES;
			break;
	}
    glGenRenderbuffers(1, &pRenderTarget->GetDepthStencilTexture()->texid);
    glBindRenderbuffer(GL_RENDERBUFFER, pRenderTarget->GetDepthStencilTexture()->texid);
	err = glGetError();
    glRenderbufferStorage(GL_RENDERBUFFER, depth_format, width, height);
	err = glGetError();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pRenderTarget->GetDepthStencilTexture()->texid);
	err = glGetError();
    glBindRenderbuffer(GL_RENDERBUFFER, 0);    

End:
  // Finalize
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    printf("failed to make complete rtt framebuffer object %x\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  return true;
  return XR_OK;
}
#else
xr_state CRenderDevice::CreateRenderTarget(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth, CRenderTarget* pRenderTarget)
{
	GLenum err;
	UInt32 glformat, gltype,depth_format;
	pRenderTarget->GetRenderTexture()->width = width;
	pRenderTarget->GetRenderTexture()->height = height;
	pRenderTarget->GetDepthStencilTexture()->width = width;
	pRenderTarget->GetDepthStencilTexture()->height = height;

	glGenFramebuffers(1, &pRenderTarget->fboid);
	err = glGetError();
	glBindFramebuffer(GL_FRAMEBUFFER, pRenderTarget->fboid);
	err = glGetError();

	if (format) {
		GetGLTextureFormat(format, &glformat, &gltype);
		glGenTextures(1, &pRenderTarget->GetRenderTexture()->texid);
		glBindTexture(GL_TEXTURE_2D, pRenderTarget->GetRenderTexture()->texid);
		pRenderTarget->GetRenderTexture()->type = GL_TEXTURE_2D;
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		pRenderTarget->GetRenderTexture()->samplerMode = XR_SAMPLER_CLAMP;

		glTexImage2D(GL_TEXTURE_2D, 0, glformat, width, height, 0,glformat, gltype, 0);
		err = glGetError();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pRenderTarget->GetRenderTexture()->texid, 0);
		err = glGetError();
		glBindTexture(GL_TEXTURE_2D, 0);

	}

  // Create depth buffer
	GLenum type;
	if (depth) {
		if(depth==XR_D24 || depth==XR_D24S8) {
			depth_format = GL_DEPTH_COMPONENT24_OES;
			type = GL_FLOAT;
			depth_format = GL_DEPTH_COMPONENT;
			type = GL_UNSIGNED_INT;
		}
		else if(depth==XR_D24I) {
			depth_format = GL_DEPTH_COMPONENT;
			type = GL_UNSIGNED_INT;
		}
		glGenTextures(1, &pRenderTarget->GetDepthStencilTexture()->texid);
		glBindTexture(GL_TEXTURE_2D, pRenderTarget->GetDepthStencilTexture()->texid);
		pRenderTarget->GetDepthStencilTexture()->type = GL_TEXTURE_2D;
		glTexImage2D(GL_TEXTURE_2D, 0, depth_format, width, height, 0, GL_DEPTH_COMPONENT, type, NULL);
		err = glGetError();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		pRenderTarget->GetDepthStencilTexture()->samplerMode = XR_SAMPLER_CLAMP;
		err = glGetError();
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, pRenderTarget->GetDepthStencilTexture()->texid, 0);
		err = glGetError();
	}


End:
  // Finalize
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    printf("failed to make complete rtt framebuffer object %x\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
  }
  glClearColor(0.0,0.0,0.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  return true;
  return XR_OK;
}
#endif
xr_state CRenderDevice::CreateRenderTargetCube(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth, CRenderTarget* pRenderTarget)
{
	glGenTextures(1, &pRenderTarget->GetDepthStencilTexture()->texid);	
	glBindTexture(GL_TEXTURE_CUBE_MAP, pRenderTarget->GetDepthStencilTexture()->texid);
	for (unsigned int i=0; i < 6; i++)	
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT24_OES, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	//glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	//glGenTextures(1, &m_uiCubeTexturemap);	
	//glBindTexture(GL_TEXTURE_CUBE_MAP, m_uiCubeTexturemap);
	//for (unsigned int i=0; i < 6; i++)		
	//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_R32UI, SHADOWMAP_SIZE, SHADOWMAP_SIZE, 0, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);

	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Create a frame buffer with only the depth buffer attached					
	glGenFramebuffers(1, &pRenderTarget->fboid);
	glBindFramebuffer(GL_FRAMEBUFFER, pRenderTarget->fboid);
	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X, m_uiCubeTexturemap, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X, pRenderTarget->GetDepthStencilTexture()->texid, 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		return false;
	}

}

xr_state CRenderDevice::CreateAccessibleRenderTarget(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth, CRenderTarget* pRenderTarget)
{

	// Initialize the render target texture description.

	if (depth) {
	}
	return XR_OK;
}

xr_state CRenderDevice::CreateVertexBuffer(Void* pBuffer, Int32 vertexSize, Int32 vertexNum, CVertexBuffer* pVertexBuffer, XRBufferUsage usage)
{
	GLenum glUsage=GL_STATIC_DRAW;
	if (usage==XR_BUFFER_DYNAMIC) {
		glUsage = GL_STREAM_DRAW;
	}
	pVertexBuffer->mode = glUsage;
	pVertexBuffer->size = vertexSize* vertexNum;
	pVertexBuffer->vertexSize = vertexSize;

	glGenBuffers(1, &pVertexBuffer->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, pVertexBuffer->vboId);
	glBufferData(GL_ARRAY_BUFFER, pVertexBuffer->size, pBuffer, pVertexBuffer->mode);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return 0;
}

xr_state CRenderDevice::CreateIndexBuffer(Void* pBuffer, Int32 size, CIndexBuffer* pIndexBuffer, XRBufferUsage usage)
{
	GLenum glUsage=GL_STATIC_DRAW;
	if (usage==XR_BUFFER_DYNAMIC) {
		glUsage = GL_STREAM_DRAW;
	}
	glGenBuffers(1, &pIndexBuffer->m_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pBuffer, glUsage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	pIndexBuffer->m_mode = glUsage;
	pIndexBuffer->m_size = size;
	return 0;
}
xr_state CRenderDevice::UpdateVertexBuffer(Void* pBuffer, CVertexBuffer* pVertexBuffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, pVertexBuffer->vboId);
	glBufferData(GL_ARRAY_BUFFER, pVertexBuffer->size, pBuffer, pVertexBuffer->mode);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return XR_OK;
}

xr_state CRenderDevice::UpdateIndexBuffer(Void* pBuffer, CIndexBuffer* pIndexBuffer)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->m_size, pBuffer, pIndexBuffer->m_mode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	return XR_OK;
}

xr_state CRenderDevice::CreateShaderFromFile(ConstString vtxName, ConstString frgName, CShaderObject* pShaderObject, XR_VERTEX_LAYOUT* desc, Int32 num,  CVertexLayout* pLayout)
{
	String vtx, frg;
	LoadTextFromFile((String)vtxName, &vtx);
	LoadTextFromFile((String)frgName, &frg);
	CreateShaderFromMemory((ConstString)vtx, (ConstString)frg, pShaderObject, desc, num, pLayout);
	free(vtx);
	free(frg);
	return XR_OK;
}

xr_state CRenderDevice::CreateShaderFromMemory(ConstString vs, ConstString fs, CShaderObject* pShaderObject, XR_VERTEX_LAYOUT* desc, Int32 num, CVertexLayout* pLayout)
{
	GLenum err;

	if (pShaderObject->isInitialized) return -1; 

	int i;

	//create fragment shader object
	pShaderObject->uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);

	//load shader source from string
	glShaderSource(pShaderObject->uiFragShader, 1, (const char**)&fs, 0);

	//compile the source code
	glCompileShader(pShaderObject->uiFragShader);

	GLint bShaderCompiled;
	//check if compilation succeed
  glGetShaderiv(pShaderObject->uiFragShader, GL_COMPILE_STATUS, &bShaderCompiled);

	if (!bShaderCompiled)
	{
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(pShaderObject->uiFragShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
        glGetShaderInfoLog(pShaderObject->uiFragShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
		//xrprintf("fs compile failed!");
		//LOGW(pszInfoLog);
				xrprintf("\r\n fs %s compile failed!",fs);

		xrprintf("\r\nErrorLog:%s!",pszInfoLog);

		delete[] pszInfoLog;
		goto cleanup;
	}

	//now start loading vertex shader in the same way
	pShaderObject->uiVertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(pShaderObject->uiVertShader, 1, (const char**)&vs, 0);
	glCompileShader(pShaderObject->uiVertShader);
    glGetShaderiv(pShaderObject->uiVertShader, GL_COMPILE_STATUS, &bShaderCompiled);

	if (!bShaderCompiled)
	{
		int i32InfoLogLength, i32CharsWritten;
		glGetShaderiv(pShaderObject->uiVertShader, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
        glGetShaderInfoLog(pShaderObject->uiVertShader, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
		//LOGW("vs compile failed!");
		//LOGW(pszInfoLog);
				xrprintf("\r\n vs %s compile failed!",vs);

		xrprintf("\r\nErrorLog:%s!",pszInfoLog);
		delete[] pszInfoLog;
		goto cleanup;
	}

	//create the shader program
    pShaderObject->uiProgramObject = glCreateProgram();

	//attach the vertex and fragment shaders
	glAttachShader(pShaderObject->uiProgramObject, pShaderObject->uiVertShader);
    glAttachShader(pShaderObject->uiProgramObject, pShaderObject->uiFragShader);

	pShaderObject->helper.Parse(vs, fs);
	//bind the vertex attribute from string Attribs[i] to location i
	for (i = 0; i < pShaderObject->helper.GetAttributeNum(); i++) {
		glBindAttribLocation(pShaderObject->uiProgramObject, i, pShaderObject->helper.GetAttributeNames(i));
		err = glGetError();
	}

	//link the program
    glLinkProgram(pShaderObject->uiProgramObject);

    GLint bLinked;
    glGetProgramiv(pShaderObject->uiProgramObject, GL_LINK_STATUS, &bLinked);
	if (!bLinked)
	{
		int i32InfoLogLength, i32CharsWritten;
		glGetProgramiv(pShaderObject->uiProgramObject, GL_INFO_LOG_LENGTH, &i32InfoLogLength);
		char* pszInfoLog = new char[i32InfoLogLength];
		glGetProgramInfoLog(pShaderObject->uiProgramObject, i32InfoLogLength, &i32CharsWritten, pszInfoLog);
		//LOGW("link failed!");
		xrprintf("\r\n link %s and %s failed!",fs,vs);

		xrprintf("\r\nErrorLog:%s!",pszInfoLog);		//LOGW(pszInfoLog);

		delete[] pszInfoLog;
		goto cleanup;
	}


	glUseProgram(pShaderObject->uiProgramObject);


	//get location of uniform from string Uniforms[i]
	for (i=0; i<pShaderObject->helper.GetUniformNum(); i++) {
		pShaderObject->helper.uniformLocations[i] = glGetUniformLocation(pShaderObject->uiProgramObject, pShaderObject->helper.GetUniformNames(i));
	}

	//set the sampler2D named by string Textures[i] to texture i
	for (i=0; i<pShaderObject->helper.GetSamplerNum(); i++) {
		glUniform1i(glGetUniformLocation(pShaderObject->uiProgramObject, pShaderObject->helper.GetSamplerNames(i)), i);
		err = glGetError();
		xrprintf("\r\nglGetError return 0x%x,name[%s]",err,pShaderObject->helper.GetSamplerNames(i));
	}
	pShaderObject->isInitialized = 1;
	return 0;

cleanup:
	glDeleteProgram(pShaderObject->uiProgramObject);
	glDeleteShader(pShaderObject->uiFragShader);
	glDeleteShader(pShaderObject->uiVertShader);
	pShaderObject->isInitialized = 0;
}

xr_state CRenderDevice::CreateVertexLayout(XR_VERTEX_LAYOUT* desc, Int32 num, CVertexLayout* pLayout, ConstString vs)
{

	pLayout->Init(desc, num);

	return XR_OK;
}

xr_state CRenderDevice::CreateUniformBlock(Int32 size, CUniformBlock* pUniformBlock)
{
	CShaderObject* shader = GetCurrentShader();
	pUniformBlock->Alloc(size);
	return XR_OK;
}

static int LoadTextureFromDDSData(GLenum target, Int32 startLevel, const NVHHDDSImage *pImage, Boolean useMipmaps )
{
    Int32 w, h, level, m;
    Int32 powerOfTwo, mipLevelsToLoad, maxLevel;
    GLenum baseTarget = (target == GL_TEXTURE_2D) ? GL_TEXTURE_2D : GL_TEXTURE_CUBE_MAP;

    if ( pImage == NULL ) {
        return 0;
    }

    w = pImage->width;
    h = pImage->height;
    level = startLevel;

    /* Need to detect if the image has a non-pow-2 dimension */
    powerOfTwo = ((w & (w - 1)) == 0) && ((h & (h - 1)) == 0);

    /* Only pow-2 images that are tagged for using mipmaps get them */
    mipLevelsToLoad = ((powerOfTwo && useMipmaps) ? pImage->numMipmaps : 1);

    maxLevel = level + mipLevelsToLoad;

    for ( m = 0; level < maxLevel; level++, m++ ) {
        if (pImage->compressed) {
            glCompressedTexImage2D( target, m, pImage->format, w, h,
                                    0, pImage->size[level],
                                    pImage->data[level] );
			 GLint err = glGetError();

        } else {
            glTexImage2D( target, m, pImage->format, w, h, 0,
                          pImage->format, pImage->componentFormat,
                          pImage->data[level]);
        }

        w = (w == 1) ? w : w >> 1;
        h = (h == 1) ? h : h >> 1;
    }

    if (mipLevelsToLoad > 1)
    {
        glTexParameterf(baseTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    }
    else
    {
        glTexParameterf(baseTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    glTexParameterf(baseTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* For now, we clamp everyone - apps wanting wrapping for a texture can set it manually */
    glTexParameterf(baseTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(baseTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return 1;
}


xr_state CRenderDevice::CreateTextureFromFile(ConstString fileName, CTexture* pTexture)
{
    // Load the Texture
	Int32 useMipmaps = 0;
    NVHHDDSImage* image = NVHHDDSLoad(fileName, 0);
    printf("\r\nLoad testure file %s return 0x%x",fileName,image);
    if(!image) return XR_OK;

	int i,j,mipWidth = image->width;
    int mipHeight = image->height;
    int numMipmaps = image->numMipmaps;
    int numCubeFaces = (image->cubemap ? 6 : 1);
    GLenum texTarget = (image->cubemap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D);
    GLenum uploadTarget = (image->cubemap ? GL_TEXTURE_CUBE_MAP_POSITIVE_X : GL_TEXTURE_2D);

    glGenTextures(1, &pTexture->texid);
    glBindTexture(texTarget, pTexture->texid);
    glTexParameteri(texTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(texTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	pTexture->type = texTarget;
	pTexture->width = image->width;
	pTexture->height = image->height;
    for (i=0; i<numCubeFaces; i++) {
        mipWidth = image->width;
        mipHeight = image->height;

        for (j=0; j<numMipmaps; j++) {
            if(image->compressed) {

                glCompressedTexImage2D(uploadTarget+i, j, image->format,
                    mipWidth, mipHeight, 0,
                    image->size[i*numMipmaps+j],
                    image->data[i*numMipmaps+j]);
            } else {

                glTexImage2D(uploadTarget+i, j, image->format,
                    mipWidth, mipHeight, 0, image->format, GL_UNSIGNED_BYTE,
                    image->data[i*numMipmaps+j]);
            }

            // shrink to next power of 2
            mipWidth  >>= 1;
            mipHeight >>= 1;
            if (mipWidth < 1) { mipWidth = 1; }
            if (mipHeight < 1) { mipHeight = 1; }
        }
    }


    NVHHDDSFree(image);

	return XR_OK;

    if (image)
    {

		glGenTextures(1, &pTexture->texid);
        if (!image->cubemap)
        {
            glBindTexture(GL_TEXTURE_2D, pTexture->texid);
            LoadTextureFromDDSData(GL_TEXTURE_2D, 0, image, useMipmaps);
			pTexture->type = GL_TEXTURE_2D;
        }
        else
        {
            Int32 baseLevel = 0;
            glBindTexture(GL_TEXTURE_CUBE_MAP, pTexture->texid);

            LoadTextureFromDDSData(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, baseLevel, image, useMipmaps);
            baseLevel += image->numMipmaps ? image->numMipmaps : 1;

            LoadTextureFromDDSData(GL_TEXTURE_CUBE_MAP_POSITIVE_X, baseLevel, image, useMipmaps);
            baseLevel += image->numMipmaps ? image->numMipmaps : 1;

            LoadTextureFromDDSData(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, baseLevel, image, useMipmaps);
            baseLevel += image->numMipmaps ? image->numMipmaps : 1;

            LoadTextureFromDDSData(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, baseLevel, image, useMipmaps);
            baseLevel += image->numMipmaps ? image->numMipmaps : 1;

            LoadTextureFromDDSData(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, baseLevel, image, useMipmaps);
            baseLevel += image->numMipmaps ? image->numMipmaps : 1;

            LoadTextureFromDDSData(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, baseLevel, image, useMipmaps);
            baseLevel += image->numMipmaps ? image->numMipmaps : 1;
			pTexture->type = GL_TEXTURE_CUBE_MAP;
        }

        GLint err = glGetError();
		
		pTexture->width = image->width;
		pTexture->height = image->height;

        NVHHDDSFree(image);
    }

	return XR_OK;
}

xr_state CRenderDevice::CreateTexture(Void* pData, Int32 width, Int32 height, XRBufferFormat format, UInt32 mode, CTexture* pTexture, Int32 miplevel)
{
	GLenum err;
	UInt32 glformat,gltype;
	UInt32 gladdress, glfiltermag, glfiltermin;

	GetGLTextureFormat(format, &glformat, &gltype);
	GetGLSamplerMode(mode, &gladdress, &glfiltermag, &glfiltermin);
	pTexture->type = GL_TEXTURE_2D;
	pTexture->width = width;
	pTexture->height = height;
	pTexture->format = format;
    glGenTextures(1, &pTexture->texid);
    glBindTexture(GL_TEXTURE_2D, pTexture->texid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glfiltermag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glfiltermin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gladdress);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gladdress);
	pTexture->samplerMode = mode;

    glTexImage2D(GL_TEXTURE_2D, 0, glformat, width, height, 0, glformat, gltype, pData);

	glGenerateMipmap(GL_TEXTURE_2D);

	return XR_OK;
}

xr_state CRenderDevice::UpdateTexture(Void* pData, CTexture* pTexture)
{
	UInt32 glformat,gltype;
	GetGLTextureFormat(pTexture->format, &glformat, &gltype);
    glBindTexture(GL_TEXTURE_2D, pTexture->texid);
    glTexImage2D(GL_TEXTURE_2D, 0, glformat, pTexture->width, pTexture->height, 0, glformat, gltype, pData);

	return XR_OK;
}

xr_state CRenderDevice::CreateTextureCube(Void** pData, Int32 width, Int32 height, XRBufferFormat format, CTexture* pTexture)
{
	GLenum err;
	UInt32 glformat,gltype;

	GetGLTextureFormat(format, &glformat, &gltype);
	pTexture->type = GL_TEXTURE_CUBE_MAP;
	pTexture->format = format;
    glGenTextures(1, &pTexture->texid);
    glBindTexture(GL_TEXTURE_CUBE_MAP, pTexture->texid);
	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	pTexture->samplerMode = XR_SAMPLER_CLAMP;

    for(int i=0; i<6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                     glformat, width, height, 0, 
                     glformat, gltype, pData[i]);
    }
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	return XR_OK;
}

xr_state CRenderDevice::CreateSampler(UInt32 mode, CSampler* pSampler)
{
    // Create the sample state
	pSampler->mode = mode;
	return XR_OK;
}

