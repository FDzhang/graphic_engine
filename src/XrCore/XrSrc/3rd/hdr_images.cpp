//----------------------------------------------------------------------------------
// File:        hdr_images.cpp
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

//#include <string.h>
#include <vector>
//#include <assert.h>
#include "hdr_images.h"

#define GL_RGBA 0
#define GL_UNSIGNED_BYTE 0
#define GL_RGB 0
#define GL_FLOAT 0
//
//
////////////////////////////////////////////////////////////
HDRImage::HDRImage() : _width(0), _height(0), _depth(0), _levelCount(0), _faces(0), _format(GL_RGBA),
    _internalFormat(GL_RGBA), _type(GL_UNSIGNED_BYTE), _elementSize(0) {
}

//
//
////////////////////////////////////////////////////////////
HDRImage::~HDRImage() {
    freeData();
}

//
//
////////////////////////////////////////////////////////////
void HDRImage::freeData() {
    for (std::vector<unsigned char*>::iterator it = _data.begin(); it != _data.end(); it++) {
        delete []*it;
    }
    _data.clear();
}

//
//
////////////////////////////////////////////////////////////
int HDRImage::getImageSize( int level) const {
    int w = _width >> level;
    int h = _height >> level;
    int d = _depth >> level;
    w = (w) ? w : 1;
    h = (h) ? h : 1;
    d = (d) ? d : 1;

    return w*h*d*_elementSize;
}


//
//
////////////////////////////////////////////////////////////
//const void* HDRImage::getLevel( int level, GLenum face) const {
//    assert( level < _levelCount);
//    assert( _faces == 0 || ( face >= GL_TEXTURE_CUBE_MAP_POSITIVE_X && face <= GL_TEXTURE_CUBE_MAP_NEGATIVE_Z));
//
//    face = face - GL_TEXTURE_CUBE_MAP_POSITIVE_X;
//
//    assert( (face*_levelCount + level) < (int)_data.size());
//    return _data[ face*_levelCount + level];
//}

//
//
////////////////////////////////////////////////////////////
void* HDRImage::getLevel( int level, int face) {


    //assert( (face*_levelCount + level) < (int)_data.size());
    return _data[ face*_levelCount + level];
}

bool HDRImage::loadHDRIFromFile( const char* file) {
    int width, height;
    XrFile *fp = XrFOpen((String)file, (String)"rb");
    if (!fp) {
        return false;
    }

    rgbe_header_info header;

    if (RGBE_ReadHeader( fp, &width, &height, &header)) {
        XrFClose(fp);
        return false;
    }

    unsigned char *data = (unsigned char*)new float[width*height*3];
    
    if (!data) {
        XrFClose(fp);
        return false;
    }

    if (RGBE_ReadPixels_RLE( fp, (float*)data, width, height)) {
        delete []data;
        XrFClose(fp);
        return false;
    }

    //set all the parameters
    _width = width;
    _height = height;
    _depth = 0;
    _levelCount = 1;
    _type = GL_FLOAT;
    _format = GL_RGB;
	// GL_RGB32F_ARB 0x8815
    _internalFormat = 0x8815;
    _faces = 0;
    _elementSize = 12;
    _data.push_back( data);

    //hdr images come in upside down
    flipSurface( data, _width, _height, _depth);

    XrFClose(fp);

    return true;
}

//
//
////////////////////////////////////////////////////////////
void HDRImage::flipSurface(unsigned char *surf, int width, int height, int depth)
{
    unsigned int lineSize;

    depth = (depth) ? depth : 1;

    lineSize = _elementSize * width;
    unsigned int sliceSize = lineSize * height;

    unsigned char *tempBuf = new unsigned char[lineSize];

    for ( int ii = 0; ii < depth; ii++) {
        unsigned char *top = surf + ii*sliceSize;
        unsigned char *bottom = top + (sliceSize - lineSize);
    
        for ( int jj = 0; jj < (height >> 1); jj++) {
            memcpy( tempBuf, top, lineSize);
            memcpy( top, bottom, lineSize);
            memcpy( bottom, tempBuf, lineSize);

            top += lineSize;
            bottom -= lineSize;
        }
    }

    delete []tempBuf;
}    

//
////////////////////////////////////////////////////////////
bool HDRImage::convertCrossToCubemap()
{
    //can't already be a cubemap
    if (isCubeMap())
        return false;

    //mipmaps are not supported
    if (_levelCount != 1)
        return false;

    //this function only supports vertical cross format for now (3 wide by 4 high)
    if (  (_width / 3 != _height / 4) || (_width % 3 != 0) || (_height % 4 != 0) || (_depth != 0))
        return false;

    //get the source data
    unsigned char *data = _data[0];

    int fWidth = _width / 3;
    int fHeight = _height / 4;

    //remove the old pointer from the vector
    _data.pop_back();
    
    unsigned char *face = new unsigned char[ fWidth * fHeight * _elementSize];
    unsigned char *ptr;

    //extract the faces

    // positive X
    ptr = face;
    for (int j=0; j<fHeight; j++) {
        memcpy( ptr, &data[((_height - (fHeight + j + 1))*_width + 2 * fWidth) * _elementSize], fWidth*_elementSize);
        ptr += fWidth*_elementSize;
    }
    _data.push_back(face);

    // negative X
    face = new unsigned char[ fWidth * fHeight * _elementSize];
    ptr = face;
    for (int j=0; j<fHeight; j++) {
        memcpy( ptr, &data[(_height - (fHeight + j + 1))*_width*_elementSize], fWidth*_elementSize);
        ptr += fWidth*_elementSize;
    }
    _data.push_back(face);

    // positive Y
    face = new unsigned char[ fWidth * fHeight * _elementSize];
    ptr = face;
    for (int j=0; j<fHeight; j++) {
        memcpy( ptr, &data[((4 * fHeight - j - 1)*_width + fWidth)*_elementSize], fWidth*_elementSize);
        ptr += fWidth*_elementSize;
    }
    _data.push_back(face);

    // negative Y
    face = new unsigned char[ fWidth * fHeight * _elementSize];
    ptr = face;
    for (int j=0; j<fHeight; j++) {
        memcpy( ptr, &data[((2*fHeight - j - 1)*_width + fWidth)*_elementSize], fWidth*_elementSize);
        ptr += fWidth*_elementSize;
    }
    _data.push_back(face);

    // positive Z
    face = new unsigned char[ fWidth * fHeight * _elementSize];
    ptr = face;
    for (int j=0; j<fHeight; j++) {
        memcpy( ptr, &data[((_height - (fHeight + j + 1))*_width + fWidth) * _elementSize], fWidth*_elementSize);
        ptr += fWidth*_elementSize;
    }
    _data.push_back(face);

    // negative Z
    face = new unsigned char[ fWidth * fHeight * _elementSize];
    ptr = face;
    for (int j=0; j<fHeight; j++) {
        for (int i=0; i<fWidth; i++) {
            memcpy( ptr, &data[(j*_width + 2 * fWidth - (i + 1))*_elementSize], _elementSize);
            ptr += _elementSize;
        }
    }
    _data.push_back(face);

    //set the new # of faces, width and height
    _faces = 6;
    _width = fWidth;
    _height = fHeight;

    //delete the old pointer
    delete []data;

    return true;
}


// -15 stored using a single precision bias of 127
const unsigned int  HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP = 0x38000000;
// max exponent value in single precision that will be converted
// to Inf or Nan when stored as a half-float
const unsigned int  HALF_FLOAT_MAX_BIASED_EXP_AS_SINGLE_FP_EXP = 0x47800000;

// 255 is the max exponent biased value
const unsigned int  FLOAT_MAX_BIASED_EXP = (0xFF << 23);

const unsigned int  HALF_FLOAT_MAX_BIASED_EXP = (0x1F << 10);


float convertHFloatToFloat(hfloat hf)
{
    unsigned int    sign = (unsigned int)(hf >> 15);
    unsigned int    mantissa = (unsigned int)(hf & ((1 << 10) - 1));
    unsigned int    exp = (unsigned int)(hf & HALF_FLOAT_MAX_BIASED_EXP);
    unsigned int    f;

    if (exp == HALF_FLOAT_MAX_BIASED_EXP)
    {
        // we have a half-float NaN or Inf
        // half-float NaNs will be converted to a single precision NaN
        // half-float Infs will be converted to a single precision Inf
        exp = FLOAT_MAX_BIASED_EXP;
        if (mantissa)
            mantissa = (1 << 23) - 1;    // set all bits to indicate a NaN
    }
    else if (exp == 0x0)
    {
        // convert half-float zero/denorm to single precision value
        if (mantissa)
        {
           mantissa <<= 1;
           exp = HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP;
           // check for leading 1 in denorm mantissa
           while ((mantissa & (1 << 10)) == 0)
           {
               // for every leading 0, decrement single precision exponent by 1
               // and shift half-float mantissa value to the left
               mantissa <<= 1;
               exp -= (1 << 23);
            }
            // clamp the mantissa to 10-bits
            mantissa &= ((1 << 10) - 1);
            // shift left to generate single-precision mantissa of 23-bits
            mantissa <<= 13;
        }
    }
    else
    {
        // shift left to generate single-precision mantissa of 23-bits
        mantissa <<= 13;
        // generate single precision biased exponent value
        exp = (exp << 13) + HALF_FLOAT_MIN_BIASED_EXP_AS_SINGLE_FP_EXP;
    }

    f = (sign << 31) | exp | mantissa;

	float temp = *((float *)&f);

    return *((float *)&f);
}

float
overflow ()
{
    volatile float f = 1e10;

    for (int i = 0; i < 10; i++)	
	f *= f;				// this will overflow before
					// the for�loop terminates
    return f;
}


hfloat
convertFloatToHFloat(float* f)
{
	unsigned int i = *(unsigned int *)f;
    register int s =  (i >> 16) & 0x00008000;
    register int e = ((i >> 23) & 0x000000ff) - (127 - 15);
    register int m =   i        & 0x007fffff;

    //
    // Now reassemble s, e and m into a half:
    //

    if (e <= 0)
    {
	if (e < -10)
	{
	    //
	    // E is less than -10.  The absolute value of f is
	    // less than HALF_MIN (f may be a small normalized
	    // float, a denormalized float or a zero).
	    //
	    // We convert f to a half zero with the same sign as f.
	    //

	    return s;
	}

	//
	// E is between -10 and 0.  F is a normalized float
	// whose magnitude is less than HALF_NRM_MIN.
	//
	// We convert f to a denormalized half.
	//

	//
	// Add an explicit leading 1 to the significand.
	// 

	m = m | 0x00800000;

	//
	// Round to m to the nearest (10+e)-bit value (with e between
	// -10 and 0); in case of a tie, round to the nearest even value.
	//
	// Rounding may cause the significand to overflow and make
	// our number normalized.  Because of the way a half's bits
	// are laid out, we don't have to treat this case separately;
	// the code below will handle it correctly.
	// 

	int t = 14 - e;
	int a = (1 << (t - 1)) - 1;
	int b = (m >> t) & 1;

	m = (m + a + b) >> t;

	//
	// Assemble the half from s, e (zero) and m.
	//

	return s | m;
    }
    else if (e == 0xff - (127 - 15))
    {
	if (m == 0)
	{
	    //
	    // F is an infinity; convert f to a half
	    // infinity with the same sign as f.
	    //

	    return s | 0x7c00;
	}
	else
	{
	    //
	    // F is a NAN; we produce a half NAN that preserves
	    // the sign bit and the 10 leftmost bits of the
	    // significand of f, with one exception: If the 10
	    // leftmost bits are all zero, the NAN would turn 
	    // into an infinity, so we have to set at least one
	    // bit in the significand.
	    //

	    m >>= 13;
	    return s | 0x7c00 | m | (m == 0);
	}
    }
    else
    {
	//
	// E is greater than zero.  F is a normalized float.
	// We try to convert f to a normalized half.
	//

	//
	// Round to m to the nearest 10-bit value.  In case of
	// a tie, round to the nearest even value.
	//

	m = m + 0x00000fff + ((m >> 13) & 1);

	if (m & 0x00800000)
	{
	    m =  0;		// overflow in significand,
	    e += 1;		// adjust exponent
	}

	//
	// Handle exponent overflow
	//

	if (e > 30)
	{
	    overflow ();	// Cause a hardware floating point overflow;
	    return s | 0x7c00;	// if this returns, the half becomes an
	}   			// infinity with the same sign as f.

	//
	// Assemble the half from s, e and m.
	//

	return s | (e << 10) | (m >> 13);
    }
}

inline float max(float a, float b) {
	if (a>b) return a;
	else return b;
}
float clamp(float val) {
	if (val >1.0) val = 1.0;
	if (val <0.0) val = 0.0;
	return val;
}
void convertFloatToRGBE(float* pt, UInt8* out)
{
#define R pt[0]
#define G pt[1]
#define B pt[2]
	//mediump vec4 ret ;
	float fLen = max(max(R, G),B);
	float fExp = floor( log(fLen)/log(1.05) );
	float exp = clamp( (fExp + 128.0) / 256.0);
	out[0] = clamp(R / pow(1.05, exp * 256.0 - 128.0))*255;
	out[1] = clamp(G / pow(1.05, exp * 256.0 - 128.0))*255;
	out[2] = clamp(B / pow(1.05, exp * 256.0 - 128.0))*255;
	out[3] = exp * 255;
}

void FP32toFP16(float* pt, hfloat* out,int width, int height)
{
	for (int i=0;i<width*height;i++) {
		out[i*4] = convertFloatToHFloat(&pt[i*3]);
		out[i*4+1] = convertFloatToHFloat(&pt[i*3+1]);
		out[i*4+2] = convertFloatToHFloat(&pt[i*3+2]);
		out[i*4+3] = 0.0;
	}
}

void FP32toRGBE(float* pt, UInt8* out,int width, int height)
{
	for (int i=0;i<width*height;i++) {
		convertFloatToRGBE(&pt[i*3], &out[i*4]);
	}
}
