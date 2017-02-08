
#ifndef _BLUR_SHADER_GENERATOR_H_
#define _BLUR_SHADER_GENERATOR_H_

float *generateGaussianWeights(float s, int &n);
float *generateTriangleWeights(int width);
unsigned int generate1DConvolutionFP_filter(float *weights, int width, bool vertical, bool tex2D, int img_width, int img_height, class CShaderObject* pShaderObject);

#endif //_BLUR_SHADER_GENERATOR_H_
