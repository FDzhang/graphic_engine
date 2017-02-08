#ifndef __TGA_H__
#define __TGA_H__


//#include <windows.h>									// Standard windows header
//#include <stdio.h>										// Standard I/O header 

#include "../Common/XrInternal.h"

typedef struct
{
	unsigned char Header[12];									// TGA File Header
} TGAHeader;

typedef struct
{
	unsigned char		header[6];								// First 6 Useful Bytes From The Header
	unsigned int		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	unsigned int		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	unsigned int		temp;									// Temporary Variable
	unsigned int		type;	
	unsigned int		Height;									//Height of Image
	unsigned int		Width;									//Width ofImage
	unsigned int		Bpp;									// Bits Per Pixel
} TGA;

bool LoadTGA(XrBuffer* buffer, char * filename);				// Load a TGA file

#endif






