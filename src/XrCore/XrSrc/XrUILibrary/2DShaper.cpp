#include "2DShaper.h"
#include "../Platform/XrOS.h"

Void* GenLineA8(Int32 len, Int32 interval, Int32 gradLen)
{
	unsigned char* buff = new unsigned char[len];
	unsigned int level;
	for (int i=0;i<len/2;i++) {
		if (i<interval) {
			buff[i] = 0;
		}
		else {
			level = (i-interval)*255/gradLen;
			buff[i] = level > 255 ? 255 : level;
		}
	}
	for (int i=len/2;i<len;i++) {
		buff[i] = buff[len-i-1];
	}
	return buff;
}
 
Void* GenLineRGBA(Int32 len, Int32 interval, Int32 gradLen, UInt32 color)
{
	unsigned int* buff = new unsigned int[len];
	unsigned int level;
	color &= 0x00FFFFFF;
	for (int i=0;i<len/2;i++) {
		if (i<interval) {
			buff[i] = color;
		}
		else {
			buff[i] = color;
			if (gradLen) level = (i-interval)*255/gradLen;
			else level = 255;
			buff[i] |= (level > 255 ? 255 : level)<<24;
		}
	}
	for (int i=len/2;i<len;i++) {
		buff[i] = buff[len-i-1];
	}
	return buff;
}
