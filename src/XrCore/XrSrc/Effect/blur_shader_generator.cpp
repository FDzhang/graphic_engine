//----------------------------------------------------------------------------------
// File:        blur_shader_generator.cpp
// SDK Version: v10.10 
// Email:       tegradev@nvidia.com
// Site:        http://developer.nvidia.com/
//
// Copyright (c) 2007-2012, NVIDIA CORPORATION.  All rights reserved.
//
// TO  THE MAXIMUM  EXTENT PERMITTED  BY APPLICABLE  LAW, THIS SOFTWARE  IS PROVIDED
// *AS IS*  AND NVIDIA AND  ITS SUPPLIERS DISCLAIM  ALL WARRANTIES,  EITHER  EXPRESS
// OR IMPLIED, INCLUDING, BUT NOT LIMITED  TO, IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL  NVIDIA OR ITS SUPPLIERS
// BE  LIABLE  FOR  ANY  SPECIAL,  INCIDENTAL,  INDIRECT,  OR  CONSEQUENTIAL DAMAGES
// WHATSOEVER (INCLUDING, WITHOUT LIMITATION,  DAMAGES FOR LOSS OF BUSINESS PROFITS,
// BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
// ARISING OUT OF THE  USE OF OR INABILITY  TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
// BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
//
//
//----------------------------------------------------------------------------------


#include "../Common/XrInternal.h"
#include "../XrCore/CDeviceManager.h"
#include "blur_shader_generator.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include "../Platform/XrOS.h"

#define NV_PI   float(3.1415926535897932384626433832795)


#ifdef USE_DX11
const char* PP_Blur = "PP_Blur";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* PP_Blur_fx = "\
Texture2D txDiffuse : register( t0 );\
SamplerState samLinear : register( s0 );\
struct VS_INPUT\
{\
    float4 Pos : POSITION;\
    float2 Tex : TEXCOORD0;\
};\
struct PS_INPUT\
{\
    float4 Pos : SV_POSITION;\
    float2 Tex : TEXCOORD0;\
};\
PS_INPUT VS( VS_INPUT input )\
{\
    return input;\
}";

XRVertexLayout PP_Blur_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_Blur_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;

float gaussian(float x, float s)
{
    return expf(-(s*x)*(s*x));
}

float *generateGaussianWeights(float s, int &width)
{
    width = 3.0/s;
    int size = width*2+1;
    float *weight = new float [size];

    float sum = 0.0;
    int x;
    for(x=0; x<size; x++) {
        weight[x] = gaussian((float) x-width, s);
        sum += weight[x];
    }

    for(x=0; x<size; x++) {
        weight[x] /= sum;
    }
    return weight;
}

float *generateTriangleWeights(int width)
{
    float *weights = new float [width];
    float sum = 0.0f;
    for(int i=0; i<width; i++) {
        float t = i / (float) (width-1);
        weights[i] = 1.0f - abs(t-0.5f)*2.0f;
        sum += weights[i];
    }
    for(int i=0; i<width; i++) {
        weights[i] /= sum;
    }
    return weights;
}

/*
  Generate fragment program code for a separable convolution, taking advantage of linear filtering.
  This requires roughly half the number of texture lookups.

  We want the general convolution:
    a*f(i) + b*f(i+1)
  Linear texture filtering gives us:
    f(x) = (1-alpha)*f(i) + alpha*f(i+1);
  It turns out by using the correct weight and offset we can use a linear lookup to achieve this:
    (a+b) * f(i + b/(a+b))
  as long as 0 <= b/(a+b) <= 1
*/

unsigned int generate1DConvolutionFP_filter(float *weights, int width, bool vertical, bool tex2D, int img_width, int img_height, CShaderObject* pShaderObject)
{
	const char* vs = PP_Blur_fx;
    // calculate new set of weights and offsets
    int nsamples = 2*width+1;
    int nsamples2 = (int) ceilf(nsamples/2.0f);
	
    float *weights2 = new float [nsamples2];
    float *offsets = new float [nsamples2];

    for(int i=0; i<nsamples2; i++) {
        float a = weights[i*2];
        float b;
        if (i*2+1 > nsamples-1)
            b = 0;
        else
            b = weights[i*2+1];
        weights2[i] = a + b;
        offsets[i] = b / (a + b);
        //    printf("%d: %f %f\n", i, weights2[i], offsets[i]);
    }
//    printf("nsamples = %d\n", nsamples2);

	char szBuffer[16];
    std::ostringstream ost;
    ost <<
	"Texture2D txDiffuse : register( t0 );\n"
	"SamplerState samLinear : register( s0 );\n"
	"struct PS_INPUT\n"
	"{\n"
		"float4 Pos : SV_POSITION;\n"
		"float2 Tex : TEXCOORD0;\n"
	"};\n"
	"float4 PS( PS_INPUT input) : SV_Target\n"
    "{\n"
	"float3 sum = float3(0.0,0.0,0.0);\n"
	"float2 texcoord;\n";

    for(int i=0; i<nsamples2; i++) {
        float x_offset = 0, y_offset = 0;
        if (vertical) {
            y_offset = (i*2)-width+offsets[i];
        } else {
            x_offset = (i*2)-width+offsets[i];
        }
        if (tex2D) {
            x_offset = x_offset / img_width;
            y_offset = y_offset / img_height;
        }
        float weight = weights2[i];
		sprintf(szBuffer, "%f", x_offset);
		ost << "texcoord = input.Tex + float2(" << szBuffer;
		sprintf(szBuffer, "%f", y_offset);
		ost << ", " << szBuffer << ");\n";
		sprintf(szBuffer, "%f", weight);
		ost << "sum += txDiffuse.Sample( samLinear, texcoord ).rgb*" << szBuffer << ";\n";
    }

    ost << 
        "return float4(sum, 1.0);\n"
        "}\n";

    delete [] weights2;
    delete [] offsets;

	XRDM->device()->CreateShaderFromMemory((ConstString)vs, (ConstString)ost.str().c_str(), pShaderObject);
	return 0;
}
#else


const char* PP_Blur = "PP_Blur";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* PP_Blur_fx = "\
attribute vec3 PosAttribute;\
attribute vec2 TexAttribute;\
precision mediump float;\
varying mediump vec2 TexCoord0;\
void main()\
{\
	gl_Position = vec4(PosAttribute, 1.0);\
	TexCoord0 = TexAttribute;\
}";

XRVertexLayout PP_Blur_layout_index = XR_VERTEX_LAYOUT_PT;
UInt32 PP_Blur_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW;


//// 1d Gaussian distribution, s is standard deviation
//float gaussian(float x, float s)
//{
//    return expf(-x*x/(2.0f*s*s)) / (s*sqrtf(2.0f*NV_PI));
//}
//
//
//// generate array of weights for Gaussian blur
//float *
//generateGaussianWeights(float s, int &width)
//{
//    width = (int) floor(3.0f*s)-1;
//    int size = width*2+1;
//    float *weight = new float [size];
//
//    float sum = 0.0;
//    int x;
//    for(x=0; x<size; x++) {
//        weight[x] = gaussian((float) x-width, s);
//        sum += weight[x];
//    }
//
//    for(x=0; x<size; x++) {
//        weight[x] /= sum;
//    }
//    return weight;
//}

float gaussian(float x, float s)
{
    return expf(-(s*x)*(s*x));
}


float *
generateGaussianWeights(float s, int &width)
{
    width = 3.0/s;
    int size = width*2+1;
    float *weight = new float [size];

    float sum = 0.0;
    int x;
    for(x=0; x<size; x++) {
        weight[x] = gaussian((float) x-width, s);
        sum += weight[x];
    }

    for(x=0; x<size; x++) {
        weight[x] /= sum;
    }
    return weight;
}

float *
generateTriangleWeights(int width)
{
    float *weights = new float [width];
    float sum = 0.0f;
    for(int i=0; i<width; i++) {
        float t = i / (float) (width-1);
        weights[i] = 1.0f - abs(t-0.5f)*2.0f;
        sum += weights[i];
    }
    for(int i=0; i<width; i++) {
        weights[i] /= sum;
    }
    return weights;
}

/*
  Generate fragment program code for a separable convolution, taking advantage of linear filtering.
  This requires roughly half the number of texture lookups.

  We want the general convolution:
    a*f(i) + b*f(i+1)
  Linear texture filtering gives us:
    f(x) = (1-alpha)*f(i) + alpha*f(i+1);
  It turns out by using the correct weight and offset we can use a linear lookup to achieve this:
    (a+b) * f(i + b/(a+b))
  as long as 0 <= b/(a+b) <= 1
*/

unsigned int generate1DConvolutionFP_filter(float *weights, int width, bool vertical, bool tex2D, int img_width, int img_height, CShaderObject* pShaderObject)
{
	const char* vs = PP_Blur_fx;
    // calculate new set of weights and offsets
    int nsamples = 2*width+1;
 //   int nsamples2 = (int) ceilf(nsamples/2.0f);
 //   float *weights2 = new float [nsamples2];
 //   float *offsets = new float [nsamples2];

 //   for(int i=0; i<nsamples2; i++) {
 //       float a = weights[i*2];
 //       float b;
 //       if (i*2+1 > nsamples-1)
 //           b = 0;
 //       else
 //           b = weights[i*2+1];
 //       weights2[i] = a + b;
 //       offsets[i] = b / (a + b);
 //       //    printf("%d: %f %f\n", i, weights2[i], offsets[i]);
 //   }
	////    printf("nsamples = %d\n", nsamples2);

	char szBuffer[16];
    std::ostringstream ost;
    ost <<
		"uniform sampler2D TexSampler;\n"
		"varying mediump vec2 TexCoord0;\n"
		"mediump vec4 EncodeRGBE8( mediump vec3 rgb )\n"
		"{\n"
			"mediump vec4 ret ;\n"
			"mediump float fLen = max(rgb.r, rgb.g) ;\n"
			"fLen = max(fLen, rgb.b) ;\n"
			"mediump float fExp = floor( log(fLen)/log(1.05) ) ;\n"
			"ret.a = clamp( (fExp + 128.0) / 256.0, 0.0, 1.0 ) ;\n"
			"ret.rgb = rgb / pow(1.05, ret.a * 256.0 - 128.0) ;\n"
			"return ret;\n"
		"}\n"
		"mediump vec3 texture2DRGBE8( sampler2D sampler, mediump vec2 texCoord)\n"
		"{\n"
			"mediump vec4 rgbe = texture2D(sampler, texCoord);\n"
			"mediump float fExp = rgbe.a * 256.0 - 128.0 ;\n"
			"mediump float fScaler = pow(1.05, fExp);\n"
			"return (rgbe.rgb * fScaler) ;\n"
		"}\n"
		"void main()\n"
		"{\n"
		"mediump vec3 sum = vec3(0.0,0.0,0.0);\n"
		"mediump vec2 texcoord;\n";

    for(int i=0; i<nsamples; i++) {
        float x_offset = 0, y_offset = 0;
        if (vertical) {
            y_offset = (i)-nsamples/2;
        } else {
            x_offset = (i)-nsamples/2;
        }
        if (tex2D) {
            x_offset = (x_offset) / img_width;
            y_offset = (y_offset) / img_height;
        }
        float weight = weights[i];
		sprintf(szBuffer, "%f", x_offset);
		ost << "texcoord = TexCoord0 + vec2(" << szBuffer;
		sprintf(szBuffer, "%f", y_offset);
		ost << ", " << szBuffer << ");\n";
		sprintf(szBuffer, "%f", weight);
		ost << "sum += texture2DRGBE8(TexSampler, texcoord).rgb*" << szBuffer << ";\n";
    }

    ost << 
		"gl_FragColor = EncodeRGBE8(sum);\n"
        "}\n";

	XRDM->device()->CreateShaderFromMemory((ConstString)vs, (ConstString)ost.str().c_str(), pShaderObject);
	//return CShaderObjects::GenProgram(vs, (char*)ost.str().c_str());
	return 0;
}

#endif
