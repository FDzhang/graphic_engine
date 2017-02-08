//----------------------------------------------------------------------------------
// File:        hdr_images.h
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
#ifndef _HDRI_H_
#define _HDRI_H_

#include <vector>
#include "rgbe.h"

typedef unsigned short    hfloat;

hfloat convertFloatToHFloat(float *f);
float convertHFloatToFloat(hfloat hf);

void FP32toFP16(float* pt, hfloat* out,int width, int height);
void FP32toRGBE(float* pt, UInt8* out,int width, int height);


class HDRImage {
public:

    HDRImage();
    virtual ~HDRImage();

    // return the width of the image
   int getWidth() const { return _width; }

    //return the height of the image
   int getHeight() const { return _height; }

    //return the dpeth of the image (0 for images with no depth)
   int getDepth() const { return _depth; }

    //return the number of mipmap levels available for the image
   int getMipLevels() const { return _levelCount; }

    //return the number of cubemap faces available for the image (0 for non-cubemap images)
   int getFaces() const { return _faces; }

    //return the format of the image data (GL_RGB, GL_BGR, etc)
   int getFormat() const { return _format; }

    //return the suggested internal format for the data
   int getInternalFormat() const { return _internalFormat; }

    //return the type of the image data
   int getType() const { return _type; }

    //return the Size in bytes of a level of the image 
   int getImageSize(int level = 0) const;

    //return whether the image represents a cubemap
   bool isCubeMap() const { return _faces > 0; }

    //return whether the image represents a volume
   bool isVolume() const { return _depth > 0; }

    //get a pointer to level data
   //const void* getLevel( int level, GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X) const;
   void* getLevel( int level, int face);

    //initialize an image from a file
   bool loadHDRIFromFile( const char* file);

    //convert a suitable image from a cubemap cross to a cubemap (returns false for unsuitable images)
   bool convertCrossToCubemap();

    //load an image from memory, for the purposes of saving
  // bool setImage( int width, int height, GLenum format, GLenum type, const void* data);

    //save an image to a file
   bool saveImageToFile( const char* file);

protected:
    int _width;
    int _height;
    int _depth;
    int _levelCount;
    int _faces;
    int _format;
    int _internalFormat;
    int _type;
    int _elementSize;

    //pointers to the levels
    std::vector<unsigned char*> _data;

   void freeData();
   void flipSurface(unsigned char *surf, int width, int height, int depth);
};


#endif

