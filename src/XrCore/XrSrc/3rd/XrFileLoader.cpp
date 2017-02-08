#include "XrFileLoader.h"
//#include "../Render/GLES2/GLUtility.h"
#include "../XrNode/CNode.h"
//#include "../3rd/metaseq.h"
#include "../Platform/XrCrt.h"
#include "../XrCore/CDeviceManager.h"
#include "tga.h"
#include "bmp.h"
#include "hdr_images.h"

void conv24to32(XrBuffer* buffer)
{
	if (buffer->format != XR_R8G8B8) return;
	UInt8* old=buffer->pData;
	buffer->pData = (UInt8*)malloc(buffer->width*buffer->height*4);
	for (int x=0;x<buffer->width*buffer->height;x++) {
		buffer->pData[x*4+0] = old[x*3+0];
		buffer->pData[x*4+1] = old[x*3+1];
		buffer->pData[x*4+2] = old[x*3+2];
		buffer->pData[x*4+3] = 1.0;
	}
	free(old);
	buffer->format = XR_R8G8B8A8;
}

Void createCubemapTexture(HDRImage *img, CTexture* pTexture, UInt32 type)
{
	
    // load face data
	if (type&XR_TEXTURE_TYPE_RGBE) {
		UInt8* rgbeOut[6];
		for(int i=0; i<6; i++) {
			rgbeOut[i] = new UInt8[img->getWidth()*img->getHeight()*4];
			FP32toRGBE((float*)img->getLevel(0, i), rgbeOut[i], img->getWidth(),img->getHeight());
		}
		XRDM->device()->CreateTextureCube((void**)rgbeOut, img->getWidth(),img->getHeight(),XR_R8G8B8A8, pTexture);
		for(int i=0; i<6; i++) {
			delete rgbeOut[i];
		}
	}
    else {
		hfloat* out[6];
		for(int i=0; i<6; i++) {
			out[i] = new hfloat[img->getWidth()*img->getHeight()*4];
			FP32toFP16((float*)img->getLevel(0, i), out[i], img->getWidth(),img->getHeight());
		}
		XRDM->device()->CreateTextureCube((void**)out, img->getWidth(),img->getHeight(),XR_R16G16B16A16F, pTexture);
		for(int i=0; i<6; i++) {
			delete out[i];
		}
	}


}

xr_state XRCreateTextureFromFile(ConstString fileName, UInt32 type, CTexture* pTexture)
{
	Int32 isTGA;
	Int32 isBMP;
	Int32 isJPEG;
	Int32 isHDR;   
	Int32 isDDS;   
	Int32 isYUV;   	
	UInt32	texFmt;
	XrBuffer buffer;
	UInt32 format;
	char ext[4];
	if ( fileName == NULL ) return XR_FAILED;
	size_t namelen = strlen(fileName);
	ext[0] = tolower(fileName[namelen-3]);
	ext[1] = tolower(fileName[namelen-2]);
	ext[2] = tolower(fileName[namelen-1]);
	ext[3] = 0x00;
	isTGA = (strcmp(ext,"tga")==0)?1:0;
	isBMP = (strcmp(ext,"bmp")==0)?1:0;
	isHDR = (strcmp(ext,"hdr")==0)?1:0;
	isDDS = (strcmp(ext,"dds")==0)?1:0;
	isYUV = (strcmp(ext,"yuv")==0)?1:0;
 	if (isTGA) {
		LoadTGA(&buffer, (char*)fileName);
		if (type==XR_TEXTURE_TYPE_DIFFUSE_SRGB) {
			format = buffer.format | XR_SRGB;
		}
		else format = (XRBufferFormat)buffer.format ;
		//if (format == XR_R8G8B8A8_SRGB) {
		//	memset(buffer.pData, 128, buffer.width * buffer.height * 4);
		//}
		//else memset(buffer.pData, 0, buffer.width * buffer.height * 3);
		XRDM->device()->CreateTexture(buffer.pData, buffer.width, buffer.height, (XRBufferFormat)format, XR_SAMPLER_CLAMP | XR_SAMPLER_LINEAR,pTexture);
		free(buffer.pData);
	}
	else if (isBMP) {
		bmpread_t p_bmp_out;
		bmpread(fileName, 0, &buffer);
		conv24to32(&buffer);
		if (type==XR_TEXTURE_TYPE_DIFFUSE_SRGB) {
			format = buffer.format | XR_SRGB;
		}
		else format = (XRBufferFormat)buffer.format ;
		//memset(buffer.pData, 0, buffer.width * buffer.height * 3);
		if(XR_TEXTURE_TYPE_CUBE != type)
		{
		    XRDM->device()->CreateTexture(buffer.pData, buffer.width, buffer.height, (XRBufferFormat)format, XR_SAMPLER_CLAMP | XR_SAMPLER_LINEAR, pTexture);
		}
		else
		{
				UInt8* rgbeOut[6];
		for(int i=0; i<6; i++) {
			rgbeOut[i] = new UInt8[buffer.width*buffer.height*4];
			
			//// buffer file %s,line %d",__FILE__,__LINE__);
			memcpy(rgbeOut[i],buffer.pData,buffer.width*buffer.height*4);
			
		}
		    XRDM->device()->CreateTextureCube((void **)rgbeOut, buffer.width,buffer.height,(XRBufferFormat)format, pTexture);
		    
		}
		free(buffer.pData);
	}
	else if (isHDR) {
		HDRImage* hdrimage = new HDRImage;
		if (!hdrimage->loadHDRIFromFile(fileName)) {
			exit(-1);
		}
		if (!hdrimage->convertCrossToCubemap()) {
			fprintf(stderr, "Error converting image to cubemap\n");
			exit(-1);
		};
		createCubemapTexture(hdrimage, pTexture, type);
	}
	else if (isDDS) {
		XRDM->device()->CreateTextureFromFile(fileName, pTexture);
	}
	else if (isYUV) {
        YUVread(fileName, 0, &buffer);
		
		XRDM->device()->CreateTexture(buffer.pData, buffer.width, buffer.height, (XRBufferFormat)buffer.format, XR_SAMPLER_CLAMP | XR_SAMPLER_LINEAR, pTexture);
	}

	return XR_OK;
}

xr_state LoadTextFromFile(String fileName, String* pString)
{
    //GetFileFullPath(fileName, tempPath);
    
	FILE			*fd;
	int r = 0, length = 0;
	fd = fopen(fileName,"rb");
	if (fd==NULL) return XR_FAILED;
	
	if (fseek(fd, 0, SEEK_END)) {
		fclose(fd);
		return XR_FAILED;
	}
    r = ftell(fd);
	fseek(fd, 0, SEEK_SET);
	length = r;
	*pString  = (char*)calloc(length+2, 1);

	if((r = fread(*pString, sizeof( char ), length, fd)) < length) {
		//__E("read from %s: %s", fname, strerror(errno));
		return XR_FAILED;
	}
	(*pString)[length] = 0;
	(*pString)[length+1] = 0;

	fclose(fd);
	return XR_OK;
}
