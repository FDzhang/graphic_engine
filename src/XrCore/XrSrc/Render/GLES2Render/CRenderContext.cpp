#include "CRenderContext.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CRenderTarget.h"
#include "CGLESShaderHelper.h"

static CShaderObject* currentShaderObject=0;
static CRenderState currentRenderState;
static CVertexBuffer* currentVertexBuffer=0;

CShaderObject* GetCurrentShader()
{
	return currentShaderObject;
}

CRenderContext::CRenderContext():
	m_zNear(0.0f),
	m_zFar(1.0f),
	m_pDefaultSampler(0)
{
}

xr_state CRenderContext::SetRenderTarget(class CRenderTarget* pRenderTarget, Region* reg)
{
	m_pRenderTarget = pRenderTarget;
	glBindFramebuffer(GL_FRAMEBUFFER, pRenderTarget->fboid);
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
	if (reg) glViewport(reg->left, reg->top, reg->right - reg->left, reg->bottom - reg->top);
	else glViewport(0, 0, pRenderTarget->m_renderTexture.width, pRenderTarget->m_renderTexture.height);
	}
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); 
	return XR_OK;
}

void CRenderContext::SetViewport(Region* reg)
{
	glViewport(reg->left, reg->top, reg->right - reg->left, reg->bottom - reg->top);
}

void CRenderContext::SetViewport(Int32 x, Int32 y, Int32 width, Int32 height)
{
    // Setup the viewport
    glViewport(x, y, width, height);
}

xr_state CRenderContext::SetRenderState(CRenderState* pRenderState)
{
	//if (currentRenderState.m_state == pRenderState->m_state) {
		//return XR_OK;
	//}

    UInt32 state = pRenderState->m_state;

	if (state & XR_CULLMODE_MODE) {
		
		if ((state&XR_CULLMODE_MODE)==XR_CULLMODE_FRONT) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
		}
		else if ((state&XR_CULLMODE_MODE)==XR_CULLMODE_BACK) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
		else if ((state&XR_CULLMODE_MODE)==XR_CULLMODE_NONE) {
			glDisable(GL_CULL_FACE);
			//glCullFace(GL_BACK);
		}

		if ((state&XR_FRONTFACE) == XR_FRONTFACE_CW) {
			glFrontFace(GL_CW);
		}
		else if ((state&XR_FRONTFACE) == XR_FRONTFACE_CCW) {
			glFrontFace(GL_CCW);
		}
	}

	if (state & XR_DEPTHTEST_ENABLE) {
		glEnable(GL_DEPTH_TEST);
	}
	else {
		glDisable(GL_DEPTH_TEST);
		
		//glEnable(GL_DEPTH_TEST);
	}
	
	if (state & XR_DEPTHWRITE_ENABLE) {
		glDepthMask(true);
		//glDepthFunc(GetGLDepthStencilFunction(state));
	}
	else {
		glDepthMask(false);
		
		//glDepthMask(true);
	}

	if (state & XR_BLEND_BITS) {
		if ((state&XR_BLEND_BITS)==XR_BLEND_DEFAULT) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
	}
	else {
		glDisable(GL_BLEND);
	}

	currentRenderState.m_state = pRenderState->m_state;

	return XR_OK;
}

Void CRenderContext::SetVertexLayout(CVertexLayout* layout)
{
	GLenum err;
	//err = glGetError();
	if (!currentVertexBuffer) return;
	//m_pVertexLayout = layout;
	//m_pImmediateContext->IASetInputLayout( layout->m_pDX11VertexLayout );
	Int32 _layout = layout->layout, index=0, stride = currentVertexBuffer->vertexSize,offset=0;
	if (_layout & XR_VERTEX_LAYOUT_P) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		index++;
		offset+= 3*4;
	}
	if (_layout & XR_VERTEX_LAYOUT_N) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		index++;
		offset+= 3*4;
	}
	if (_layout & XR_VERTEX_LAYOUT_B) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		index++;
		offset+= 4*4;
	}
	if (_layout & XR_VERTEX_LAYOUT_T) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		index++;
		offset+= 2*4;
	}
	if (_layout & XR_VERTEX_LAYOUT_W) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, (void*)offset);
		index++;
		offset+= 4;
	}
	if (_layout & XR_VERTEX_LAYOUT_I) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 4, GL_UNSIGNED_BYTE, GL_FALSE, stride, (void*)offset);
		index++;
		offset+= 4;
	}
	if (_layout & XR_VERTEX_LAYOUT_A) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		index++;
		offset+= 4;
	}
	if (_layout & XR_VERTEX_LAYOUT_K) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, stride, (void*)offset);
		index++;
		offset+= 4;
	}

}

Void CRenderContext::DisableVertexLayout(CVertexLayout* layout)
{
	GLenum err;
	//err = glGetError();
	if (!currentVertexBuffer) return;
	//m_pVertexLayout = layout;
	//m_pImmediateContext->IASetInputLayout( layout->m_pDX11VertexLayout );
	Int32 _layout = layout->layout, index=0, stride = currentVertexBuffer->vertexSize,offset=0;
	if (_layout & XR_VERTEX_LAYOUT_P) {
		glDisableVertexAttribArray(index);
		index++;
	}
	if (_layout & XR_VERTEX_LAYOUT_N) {
		glDisableVertexAttribArray(index);
		index++;
	}
	if (_layout & XR_VERTEX_LAYOUT_T) {
		glDisableVertexAttribArray(index);
		index++;
	}
	if (_layout & XR_VERTEX_LAYOUT_W) {
		glDisableVertexAttribArray(index);
		index++;
	}
	if (_layout & XR_VERTEX_LAYOUT_I) {
		glDisableVertexAttribArray(index);
		index++;
	}
	if (_layout & XR_VERTEX_LAYOUT_B) {
		glDisableVertexAttribArray(index);
		index++;
	}
	if (_layout & XR_VERTEX_LAYOUT_A) {
		glDisableVertexAttribArray(index);
		index++;
	}	
	if (_layout & XR_VERTEX_LAYOUT_K) {
		glDisableVertexAttribArray(index);
		index++;
	}	
}

xr_state CRenderContext::SetVertexBuffer(Int32 index, class CVertexBuffer* pVertexBuffer, CVertexLayout* layout)
{
    // Set vertex buffer
   // UINT stride =  pVertexBuffer-> pVertexLayout->GetVertexSize();
    //UINT offset = 0;
	//m_pImmediateContext->IASetVertexBuffers( index, 1, &pVertexBuffer->g_pDX11VertexBuffer, &stride, &offset );
	glBindBuffer( GL_ARRAY_BUFFER, pVertexBuffer->vboId);
	currentVertexBuffer = pVertexBuffer;

	SetVertexLayout(layout);

	return XR_OK;
}


xr_state CRenderContext::SetIndexBuffer(class CIndexBuffer* pIndexBuffer)
{
    // Set index buffer
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->GetIBO());

	return XR_OK;
}


Void CRenderContext::SetShaders(class CShaderObject* pShaders)
{
	currentShaderObject = pShaders;
	glUseProgram(pShaders->uiProgramObject);
}

xr_state CRenderContext::SetPrimitiveType(XRPrimitiveType type)
{
	switch (type) {
	case XRPT_TRIANGLE_LIST:
		m_primitiveTopology = GL_TRIANGLES;
		break;
	case XRPT_TRIANGLE_STRIP:
		m_primitiveTopology = GL_TRIANGLE_STRIP;
		break;
	case XRPT_TRIANGLE_FAN:
		m_primitiveTopology = GL_TRIANGLE_FAN;
		break;
	default:
		return XR_OK;
	}

	return XR_OK;
}

Void CRenderContext::DrawPrimitive(Int32 count, Int32 offset)
{
	glDrawArrays(m_primitiveTopology, offset, count);
}

Void CRenderContext::DrawIndexedPrimitive(Int32 count, Int32 indexOffset, Int32 vertexOffset)
{
	glDrawElements(m_primitiveTopology, count, GL_UNSIGNED_SHORT, 0);
}

Void CRenderContext::ClearRenderTarget(Float32 r, Float32 g, Float32 b, Float32 a)
{
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
	//m_pImmediateContext->ClearRenderTargetView( m_pRenderTarget->m_pDX11RenderTarget, ClearColor );
}

Void CRenderContext::ClearDepthStencil(Float32 depth, UInt8 stencil)
{
    //
    // Clear the depth buffer to 1.0 (max depth)
    //
   // m_pImmediateContext->ClearDepthStencilView( m_pRenderTarget->m_pDX11DepthStencil, D3D11_CLEAR_DEPTH, depth, stencil );
	glDepthMask(true);
	glClearDepthf(depth);
	glClearStencil(stencil);
	glClear(GL_DEPTH_BUFFER_BIT);
}

Void CRenderContext::ClearDepthStencil()
{
	//ClearDepthStencil(1.0,0);
	glDepthMask(true);
	glClearDepthf(1.0);
	glClearStencil(0);
	glClear(GL_DEPTH_BUFFER_BIT);
}

Void CRenderContext::SetColorMask(Boolean r, Boolean g, Boolean b, Boolean a)
{
	glColorMask (r, g, b, a);
}


xr_state CRenderContext::PSSetTexture(Int32 index, CTexture* pTexture, CSampler* pSampler)
{
	if (!pTexture || !pTexture->type) {
		//glActiveTexture(GL_TEXTURE0+index);
		if(pTexture&&pTexture->type == 0)
		{
		glActiveTexture(GL_TEXTURE0+index);
		glBindTexture(GL_TEXTURE_2D, pTexture->texid);
		}
		return XR_OK;
	}
	glActiveTexture(GL_TEXTURE0+index);
	glBindTexture(pTexture->type, pTexture->texid);

	if (pSampler && pTexture->samplerMode != pSampler->mode) {
		pTexture->samplerMode = pSampler->mode;
		pSampler->Bind(pTexture->type);
	}
	return XR_OK;
}

xr_state CRenderContext::VSSetTexture(Int32 index, CTexture* pTexture, CSampler* pSampler)
{
	if (!pTexture) return XR_OK;
	glBindTexture(pTexture->type, pTexture->texid);

	if (pTexture->samplerMode != pSampler->mode) {
		pSampler->Bind(pTexture->type);
	}
	return XR_OK;
}

xr_state CRenderContext::VSSetUniformBlock(Int32 index, CUniformBlock* pBlock)
{
	CShaderObject* current = GetCurrentShader();
	current->helper.UpdateVSUniform(pBlock->GetData(), 0, 0);

	return XR_OK;
}

xr_state CRenderContext::PSSetUniformBlock(Int32 index, CUniformBlock* pBlock)
{
	CShaderObject* current = GetCurrentShader();
	current->helper.UpdatePSUniform(pBlock->GetData(), 0, 0);

	return XR_OK;
}

xr_state CRenderContext::PSDisableUniformBlock(Int32 index)
{
	return XR_OK;
}

xr_state CRenderContext::UpdateUniformBlock(CUniformBlock* pBlock, Void* pData, Int32 offset, Int32 size)
{
	//m_pImmediateContext->UpdateSubresource( pBlock->m_pDX11UniformBlock, 0, NULL, pData, 0, 0 );
	if (size == 0) size = pBlock->GetSize();
	pBlock->Update(pData, offset, size);
	//pBlock->pData = pData;
	//pBlock->offset = offset;
	//pBlock->dataSize = size;
	return XR_OK;
}
Void* CRenderContext::LockUniformBlock(CUniformBlock* pBlock)
{
	return pBlock->GetData();
}

Void CRenderContext::UnlockUniformBlock(CUniformBlock* pBlock)
{
}

xr_state CRenderContext::UpdateVertexBuffer(CVertexBuffer* pVertexBuffer, Void* pData, Int32 size)
{
	glBindBuffer(GL_ARRAY_BUFFER, pVertexBuffer->vboId);
	glBufferData(GL_ARRAY_BUFFER, size, pData, pVertexBuffer->mode);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return XR_OK;
}

xr_state CRenderContext::UpdateIndexBuffer(CIndexBuffer* pIndexBuffer, Void* pData, Int32 size)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->m_iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pData, pIndexBuffer->m_mode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return XR_OK;
}

xr_state CRenderContext::LockRenderedData(class CRenderTarget* pRenderTarget, void** pData, int* rowPitch, int* colPitch)
{
	return XR_OK;
}

xr_state CRenderContext::UnlockRenderedData(class CRenderTarget* pRenderTarget)
{
	return XR_OK;
}
