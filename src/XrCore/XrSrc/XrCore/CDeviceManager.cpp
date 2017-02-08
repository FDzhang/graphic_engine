#include "CDeviceManager.h"
#include "../3rd/XrFileLoader.h"
#include "../Common/stringHash.h"
#include "CAnimationManager.h"
#include <stdlib.h>
#include "../XrResource/CDataStream.h"
#include "../XrNode/Material/CMaterial.h"

extern CAnimationManager* XRAM;
static int count = 0;

CDeviceManager::CDeviceManager()
{
    prepareHashInfoTable();
    XrMemset(m_tex, 0, sizeof(CXrTextureEx)*TexHashTableNum);
	XrMemset(m_shader, 0, sizeof(CShaderObjectEx)*ShaderHashTableNum);
}

CDeviceManager::~CDeviceManager()
{
    Int32 i=0;
    //BitmapEx nullBitmap;

    //free all resources
    while (i < TexHashTableNum)
    {
		if (m_tex[i].isInitialized) {
			m_tex[i].ForceRelease();
        }
        i++;
    }
    while (i < ShaderHashTableNum)
    {
		if (m_shader[i].isInitialized == 1) m_shader[i].ForceRelease();
        i++;
    }


	for (m_Mtls.First();!m_Mtls.IsDone();m_Mtls.Next()) {
		CMaterial* p = m_Mtls.GetCurrent();
		delete p;
	}
	for (m_renderTarget.First();!m_renderTarget.IsDone();m_renderTarget.Next()) {
		delete m_renderTarget.GetCurrent();
	}
}

Boolean CDeviceManager::QueryTexFileByString(ConstString wsName, Int32* slotId)
{
    int nHash = HashString(wsName, HASH_OFFSET),
        nHashA = HashString(wsName, HASH_A),
        nHashB = HashString(wsName, HASH_B),
        nHashStart = nHash % TexHashTableNum;

    if (nHashStart<0) nHashStart+=TexHashTableNum;			//fix minus case
    int nHashPos = nHashStart;

    while (m_tex[nHashPos].GetRefCnt()) {
        if (m_tex[nHashPos].hashA == nHashA && m_tex[nHashPos].hashB == nHashB) {
			*slotId = nHashPos;
            return TRUE;
        }
        else {
            nHashPos = (nHashPos + 1) % TexHashTableNum;
        }

        if (nHashPos == nHashStart) {
            *slotId = -1;
            break;
        }
    }

    *slotId = nHashPos;
    m_tex[nHashPos].hashA = nHashA;
    m_tex[nHashPos].hashB = nHashB;
    return FALSE;
}

Boolean CDeviceManager::QueryShaderByString(ConstString wsName, Int32* slotId)
{
    int nHash = HashString(wsName, HASH_OFFSET),
        nHashA = HashString(wsName, HASH_A),
        nHashB = HashString(wsName, HASH_B),
        nHashStart = nHash % ShaderHashTableNum;

    if (nHashStart<0) nHashStart+=ShaderHashTableNum;			//fix minus case
    int nHashPos = nHashStart;

    while (m_shader[nHashPos].GetRefCnt()) {
        if (m_shader[nHashPos].hashA == nHashA && m_shader[nHashPos].hashB == nHashB) {
			*slotId = nHashPos;
            return TRUE;
        }
        else {
            nHashPos = (nHashPos + 1) % ShaderHashTableNum;
        }

        if (nHashPos == nHashStart) {
            *slotId = -1;
            return FALSE;
        }
    }

    *slotId = nHashPos;
    m_shader[nHashPos].hashA = nHashA;
    m_shader[nHashPos].hashB = nHashB;
    return FALSE;
}

Int32 CDeviceManager::GetTexAdjacentSlot(Int32 id)
{
    Int32 startId = id;
    id++;
    while (m_tex[id].GetRefCnt() != 0) {
        id = (id+1)%TexHashTableNum;
        if (startId == id) return -1;
    }
    return id;
}

Int32 CDeviceManager::GetShaderAdjacentSlot(Int32 id)
{
    Int32 startId = id;
    id++;
    while (m_shader[id].GetRefCnt() != 0) {
        id = (id+1)%ShaderHashTableNum;
        if (startId == id) return -1;
    }
    return id;
}

Void CXrTextureEx::ForceRelease()
{
	CTexture::Release();
	hashA = 0;
	hashB = 0;

}

CXrTextureEx::~CXrTextureEx()
{
	CTexture::Release();
}

Void CXrTextureEx::Release()
{
    if (DecRef() <= 0) {
		ForceRelease();
		if (extraInfo) {
			delete (char*)extraInfo;
		}
    }
}

Void CShaderObjectEx::ForceRelease()
{
	CShaderObject::Release();
	hashA = 0;
	hashB = 0;

}

CShaderObjectEx::~CShaderObjectEx()
{
	CShaderObject::Release();
}

Void CShaderObjectEx::Release()
{
    if (DecRef() <= 0) {
		ForceRelease();
    }
}


Int32 CDeviceManager::CreateTextureFromFile(ConstString fileName, UInt32 type)
{
	Int32 tid;
	if (!fileName) return -1;
	if (QueryTexFileByString(fileName, &tid)) {
		m_tex[tid].AddRef();
	}
	else {
		if (tid < 0) return -1;
		if (XRFAILED(XRCreateTextureFromFile(fileName, type, &m_tex[tid]))) return -1;
		m_tex[tid].RefInit();
		m_tex[tid].m_id = tid;
	}
	return tid;
}

xr_state CDeviceManager::UpdateTexture(Void* pData, CTexture* pTexture)
{
	return m_renderDevice->UpdateTexture(pData, pTexture);
}

Int32 CDeviceManager::CreateSharedTexture(ConstString nameId, Int32 width, Int32 height, XRBufferFormat format, UInt32 mode, CXrTextureEx** ppTex, Boolean* isExist)
{
	Int32 tid=-1;

	//CHAR texName[MaxStringLen];
	//sprintf(texName, "%d", count);
	//count++;
	if (QueryTexFileByString(nameId, &tid)) {
		m_tex[tid].AddRef();
		if (isExist) *isExist = TRUE;
	}
	else {
		if (isExist) *isExist = FALSE;
		if (tid < 0) return -1;
		if (XRFAILED(m_renderDevice->CreateTexture(0, width, height, format, mode, (CTexture*)&m_tex[tid]))) return 0;
		m_tex[tid].RefInit();
		m_tex[tid].m_id = tid;
	}
	if (ppTex) *ppTex = &m_tex[tid];
	return tid;
}

Int32 CDeviceManager::CreateStreamingTexture(Int32 width, Int32 height, XRBufferFormat format, ITextureDelegate* pDelegate)
{
	Int32 tid=-1;
	CHAR texName[MaxStringLen];
	//_itoa_s(count, texName, MaxStringLen, 10);
    sprintf(texName, "%d", count);
	count++;
	if (QueryTexFileByString(texName, &tid)) {
		m_tex[tid].AddRef();
	}
	else {
		if (tid < 0) return -1;
		if (XRFAILED(pDelegate->OnCreate(width, height, format, &m_tex[tid]))) return 0;
		m_tex[tid].RefInit();
		m_tex[tid].m_id = tid;
		if (pDelegate->NeedUpdate()) {
			m_tex[tid].updateId = XRAM->AddUpdate(pDelegate);
		}
	}
	return tid;
}

Int32 CDeviceManager::CreateTexture(Void* pData, Int32 width, Int32 height, XRBufferFormat format, UInt32 mode, Int32 miplevel)
{
	Int32 tid=-1;
	CHAR texName[MaxStringLen];
    sprintf(texName, "%d", count);
	count++;
	if (QueryTexFileByString(texName, &tid)) {
		m_tex[tid].AddRef();
	}
	else {
		if (tid < 0) return tid;
		if (XRFAILED(device()->CreateTexture(pData, width, height, format, mode, &m_tex[tid], miplevel))) return -1;
		m_tex[tid].RefInit();
		m_tex[tid].m_id = tid;
	}
	return tid;
}


xr_state CDeviceManager::ReleaseTexture(Int32 id)
{
	if (id<0) return XR_FAILED;
	m_tex[id].Release();
	return XR_OK;
}

CXrTextureEx* CDeviceManager::AquireTexture(Int32 id)
{
	if (id<0) return 0;
	if (m_tex[id].GetRefCnt() <=0) return 0;
	m_tex[id].AddRef();
	return &m_tex[id];
}


Int32 CDeviceManager::CreateRenderTarget(Int32 width, Int32 height, XRBufferFormat format, XRBufferFormat depth,
     /* [out] */ IRenderTarget** ppIRenderTarget)
{
	CRenderTargetEx*	pRenderTarget;
	IRenderTarget*  Irt;
	Int32			nid;

	pRenderTarget = new CRenderTargetEx();
	XRDM->device()->CreateRenderTarget(width, height, format, depth, &pRenderTarget->m_rt);
	nid = m_renderTarget.Add(pRenderTarget);
	pRenderTarget->m_id = nid;
	Irt = (IRenderTarget*)pRenderTarget;

	if (ppIRenderTarget) *ppIRenderTarget = Irt;


	Int32 tid=-1;
	CHAR texName[MaxStringLen];
    sprintf(texName, "%d", count);
	count++;


	if (QueryTexFileByString(texName, &tid)) {
		m_tex[tid].AddRef();
	}
	else {
		if (tid < 0) return tid;
		m_tex[tid].RefInit();
		m_tex[tid].m_id = tid;
		CTexture* pTex = pRenderTarget->GetRenderTexture();
		pTex->m_id = tid;
		m_tex[tid].texid = pTex->texid;
		m_tex[tid].type = pTex->type;
		m_tex[tid].width = pTex->width;
		m_tex[tid].height = pTex->height;
		m_tex[tid].format = pTex->format;
	}
	return nid;
}

Int32 CDeviceManager::QueryShaderProgram(ConstString name, CShaderObjectEx** ppShaderObject)
{
	Int32 tid;
	if (QueryShaderByString(name, &tid)) {
		m_shader[tid].AddRef();
		*ppShaderObject = &m_shader[tid];
	}
	else {
		if (tid<0) {
			*ppShaderObject = 0;
			return -1;
		}
		m_shader[tid].RefInit();
		*ppShaderObject = &m_shader[tid];
	}
	return tid;
}

xr_state CDeviceManager::ReleaseShaderProgram(Int32 id)
{
	if (id<0) return XR_FAILED;
	m_shader[id].Release();
	return XR_OK;
}

xr_state CDeviceManager::RegisterShaderProgram(Int32 id, CShaderObjectEx* pShaderObject)
{
	return XR_OK;
}

Int32 CDeviceManager::CreateMaterial(
		/* [in] */ MaterialType materialType,
		/* [out] */ IMaterial** ppMtl)
{
	CMaterial* p = new CMaterial(materialType);
	*ppMtl = p;
	Int32 mid = m_Mtls.Add(p);
	p->SetID(mid);
	return mid;
}

CMaterial* CDeviceManager::AquireMaterial(Int32 idx)
{
	return m_Mtls.Get(idx);
}



XR_VERTEX_LAYOUT Vertex_layout_P[] = {
    {(String)"POSITION", 0, XR_R32G32B32F, 0},
};

XR_VERTEX_LAYOUT Vertex_layout_PT[] = {
    {(String)"POSITION", 0, XR_R32G32B32F, 0},
	{(String)"TEXCOORD", 0, XR_R32G32F, 12},
};

XR_VERTEX_LAYOUT Vertex_layout_PNT[] = {
    {(String)"POSITION", 0, XR_R32G32B32F, 0},
	{(String)"NORMAL", 0, XR_R32G32B32F, 12},
	{(String)"TEXCOORD", 0, XR_R32G32F, 24},
};

XR_VERTEX_LAYOUT Vertex_layout_PNTWI[] = {
    {(String)"POSITION", 0, XR_R32G32B32F, 0},
	{(String)"NORMAL", 0, XR_R32G32B32F, 12},
	{(String)"TEXCOORD", 0, XR_R32G32F, 24},
	{(String)"BLENDWEIGHT", 0, XR_R8G8B8A8, 32},
	{(String)"BLENDINDICES", 0, XR_R8G8B8A8U, 36},
};

XR_VERTEX_LAYOUT Vertex_layout_PNBT[] = {
    {(String)"POSITION", 0, XR_R32G32B32F, 0},
	{(String)"NORMAL", 0, XR_R32G32B32F, 12},
	{(String)"TANGENT", 0, XR_R32G32B32A32F, 24},
	{(String)"TEXCOORD", 0, XR_R32G32F, 40},
};

XR_VERTEX_LAYOUT Vertex_layout_PNBTWI[] = {
    {(String)"POSITION", 0, XR_R32G32B32F, 0},
	{(String)"NORMAL", 0, XR_R32G32B32F, 12},
	{(String)"TANGENT", 0, XR_R32G32B32A32F, 24},
	{(String)"TEXCOORD", 0, XR_R32G32F, 40},
	{(String)"BLENDWEIGHT", 0, XR_R8G8B8A8, 48},
	{(String)"BLENDINDICES", 0, XR_R8G8B8A8U, 52},
};
XR_VERTEX_LAYOUT Vertex_layout_PTAK[] = {
    {(String)"POSITION", 0, XR_R32G32B32F, 0},
	{(String)"TEXCOORD", 0, XR_R32G32F, 12},
	{(String)"ALPHAWEIGHT", 0, XR_R32F, 20},
	{(String)"LUMINANCECOF", 0, XR_R32F, 24},
};

void CDeviceManager::Init()
{
	device()->CreateVertexLayout(Vertex_layout_P, 1, &m_layout[0], VS_P_dummy_fx);
	device()->CreateVertexLayout(Vertex_layout_PT, 2, &m_layout[1], VS_PT_dummy_fx);
	device()->CreateVertexLayout(Vertex_layout_PNT, 3, &m_layout[2], VS_PNT_dummy_fx);
	device()->CreateVertexLayout(Vertex_layout_PNTWI, 5, &m_layout[3], VS_PNTWI_dummy_fx);
	device()->CreateVertexLayout(Vertex_layout_PNBT, 4, &m_layout[4], VS_PNBT_dummy_fx);
	device()->CreateVertexLayout(Vertex_layout_PNBTWI, 6, &m_layout[5], VS_PNBTWI_dummy_fx);
	device()->CreateVertexLayout(Vertex_layout_PTAK, 4, &m_layout[6], VS_PNBTWI_dummy_fx);

	device()->CreateSampler(XR_SAMPLER_WRAP | XR_SAMPLER_COLOR | XR_SAMPLER_LINEAR, &m_samplers[XR_SAMPLER_WRAP]);
	device()->CreateSampler(XR_SAMPLER_MIRROR | XR_SAMPLER_COLOR | XR_SAMPLER_LINEAR, &m_samplers[XR_SAMPLER_MIRROR]);
	device()->CreateSampler(XR_SAMPLER_CLAMP | XR_SAMPLER_COLOR | XR_SAMPLER_LINEAR, &m_samplers[XR_SAMPLER_CLAMP]);
	device()->CreateSampler(XR_SAMPLER_BORDER | XR_SAMPLER_COLOR | XR_SAMPLER_LINEAR, &m_samplers[XR_SAMPLER_BORDER]);
	device()->CreateSampler(XR_SAMPLER_CLAMP | XR_SAMPLER_DEPTH | XR_SAMPLER_NEAREST, &m_samplers[XR_SAMPLER_BORDER+1]);
}

CVertexLayout*  CDeviceManager::GetVertexLayout(XRVertexLayout layout)
{
	Int32 index=0;
	switch (layout) {
		case XR_VERTEX_LAYOUT_P:
			index=0;
			break;
		case XR_VERTEX_LAYOUT_PT:
			index=1;
			break;
		case XR_VERTEX_LAYOUT_PNT:
			index=2;
			break;
		case XR_VERTEX_LAYOUT_PNTWI:
			index=3;
			break;
		case XR_VERTEX_LAYOUT_PNBT:
			index=4;
			break;
		case XR_VERTEX_LAYOUT_PNBTWI:
			index=5;
			break;
		case XR_VERTEX_LAYOUT_PTAK:
			index=6;
			break;			
	}
	return &m_layout[index];
}
