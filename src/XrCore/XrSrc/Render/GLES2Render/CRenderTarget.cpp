#include "CRenderTarget.h"
#include <stdio.h>
#include <stdlib.h>

CRenderTarget::CRenderTarget()
{
}

CRenderTarget::~CRenderTarget() {
}

bool CRenderTarget::Init(int width, int height, ColorType color, DepthType depth)
{

  return true;
}

void CRenderTarget::ActivateFB() {
}

void CRenderTarget::DeactivateFB() {
}

bool CRenderTarget::InitFromSwapChain(int width, int height, class CSwapChain* pSwapChain)
{

    // Create a render target view
    //ID3D11Texture2D* pBackBuffer = NULL;
    //hr = pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
    //if( FAILED( hr ) )
    //    return hr;

    //hr = g_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );
    //pBackBuffer->Release();
    //if( FAILED( hr ) )
    //    return hr;

	return 0;
}

void CRenderTarget::GetPBOData(void* pData)
{
}

void CRenderTarget::SetPBOData(void* pData)
{

}

void CRenderTarget::SaveCurrentFB()
{
}

void CRenderTarget::RestoreSaveDFB()
{
}
