#include "CVertexLayout.h"

bool CVertexLayout::Init(XR_VERTEX_LAYOUT* pLayout, Int32 num)
{
	Int32 _layout = XR_VERTEX_LAYOUT_NULL;
	for (Int32 i=0; i<num; i++) {
		desc[i].semanticName = pLayout[i].semanticName;
		desc[i].format = pLayout[i].format;
		desc[i].index = pLayout[i].index;
		desc[i].offset = pLayout[i].offset;

		if (!strcmp(desc[i].semanticName, "POSITION")) {
			_layout |= XR_VERTEX_LAYOUT_P;
		}
		else if (!strcmp(desc[i].semanticName, "NORMAL")) {
			_layout |= XR_VERTEX_LAYOUT_N;
		}
		else if (!strcmp(desc[i].semanticName, "TEXCOORD")) {
			_layout |= XR_VERTEX_LAYOUT_T;
		}
		else if (!strcmp(desc[i].semanticName, "BLENDWEIGHT")) {
			_layout |= XR_VERTEX_LAYOUT_W;
		}
		else if (!strcmp(desc[i].semanticName, "BLENDINDICES")) {
			_layout |= XR_VERTEX_LAYOUT_I;
		}
		else if (!strcmp(desc[i].semanticName, "TANGENT")) {
			_layout |= XR_VERTEX_LAYOUT_B;
		}
		else if (!strcmp(desc[i].semanticName, "ALPHAWEIGHT")) {
			_layout |= XR_VERTEX_LAYOUT_A;
		}
		else if (!strcmp(desc[i].semanticName, "LUMINANCECOF")) {
			_layout |= XR_VERTEX_LAYOUT_K;
		}		
	}
	layout = (XRVertexLayout)_layout;
	elementNum = num;
	return TRUE;
}

Int32 CVertexLayout::GetVertexSize()
{
	Int32 size=0;
	for (Int32 i=0; i<elementNum; i++) {
		size+= XR_BUFFER_ELEMENT_SIZE(desc[i].format);
	}
	return size;
}


 //   // Define the input layout
 //   D3D11_INPUT_ELEMENT_DESC layout[] =
 //   {
 //       { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
 //   };

 //   // Create the input layout
	//hr = g_pd3dDevice->CreateInputLayout( layout, numElements, pVSBlob->GetBufferPointer(),
 //                                         pVSBlob->GetBufferSize(), &g_pVertexLayout );
	//pVSBlob->Release();
	//if( FAILED( hr ) )
 //       return hr;

 //   // Set the input layout
 //   g_pImmediateContext->IASetInputLayout( g_pVertexLayout );

 //   // Compile the vertex shader
 //   ID3DBlob* pVSBlob = NULL;
 //   hr = CompileShaderFromFile( L"Tutorial03.fx", "VS", "vs_4_0", &pVSBlob );
 //   if( FAILED( hr ) )
 //   {
 //       MessageBox( NULL,
 //                   L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
 //       return hr;
 //   }

	//// Create the vertex shader
	//hr = g_pd3dDevice->CreateVertexShader( pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader );
	//if( FAILED( hr ) )
	//{	
	//	pVSBlob->Release();
 //       return hr;
	//}

	//// Compile the pixel shader
	//ID3DBlob* pPSBlob = NULL;
 //   hr = CompileShaderFromFile( L"Tutorial03.fx", "PS", "ps_4_0", &pPSBlob );
 //   if( FAILED( hr ) )
 //   {
 //       MessageBox( NULL,
 //                   L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK );
 //       return hr;
 //   }

	//// Create the pixel shader
	//hr = g_pd3dDevice->CreatePixelShader( pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader );
	//pPSBlob->Release();
 //   if( FAILED( hr ) )
 //       return hr;

