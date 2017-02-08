/* TAGRELEASE: public */

#ifndef __INCLUDED_NV_HHDDS_INTERNAL_H
#define __INCLUDED_NV_HHDDS_INTERNAL_H

//================================================================================
// Various DDS file defines

#define DDSD_CAPS             0x00000001l
#define DDSD_HEIGHT           0x00000002l
#define DDSD_WIDTH            0x00000004l
#define DDSD_PIXELFORMAT      0x00001000l
#define DDS_ALPHAPIXELS       0x00000001l
#define DDS_FOURCC            0x00000004l
#define DDS_PITCH             0x00000008l
#define DDS_COMPLEX           0x00000008l
#define DDS_RGB               0x00000040l
#define DDS_TEXTURE           0x00001000l
#define DDS_MIPMAPCOUNT       0x00020000l
#define DDS_LINEARSIZE        0x00080000l
#define DDS_VOLUME            0x00200000l
#define DDS_MIPMAP            0x00400000l
#define DDS_DEPTH             0x00800000l

#define DDS_CUBEMAP           0x00000200L
#define DDS_CUBEMAP_POSITIVEX 0x00000400L
#define DDS_CUBEMAP_NEGATIVEX 0x00000800L
#define DDS_CUBEMAP_POSITIVEY 0x00001000L
#define DDS_CUBEMAP_NEGATIVEY 0x00002000L
#define DDS_CUBEMAP_POSITIVEZ 0x00004000L
#define DDS_CUBEMAP_NEGATIVEZ 0x00008000L

#define FOURCC_DXT1 0x31545844 //(MAKEFOURCC('D','X','T','1'))
#define FOURCC_DXT3 0x33545844 //(MAKEFOURCC('D','X','T','3'))
#define FOURCC_DXT5 0x35545844 //(MAKEFOURCC('D','X','T','5'))
#define FOURCC_DX10 0x30315844
#define FOURCC_ETC1 0x31435445 //(MAKEFOURCC('E','T','C','1'))
#define DDS_MAGIC_FLIPPED     0x0F7166ED

//================================================================================
// DXT data-layout structure definitions.
typedef struct 
{
    unsigned short col0; // 16-bit 565 interpolant endpoints
    unsigned short col1;
    unsigned char  row[4]; // 4x4 * 2bpp color-index == 4 bytes.
} DXTColBlock;

typedef struct 
{
    unsigned short row[4]; // 4x4 * 4bpp alpha == 8 bytes.  (pure 4-bit alpha values)
} DXT3AlphaBlock;

typedef struct 
{
    unsigned char alpha0; // 8-bit alpha interpolant endpoints
    unsigned char alpha1;
    unsigned char row[6]; // 4x4 * 3bpp alpha-index == 48bits == 6 bytes.
} DXT5AlphaBlock;

typedef struct
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
} Color8888;

//================================================================================
// DDS file format structures.
typedef struct _DDS_PIXELFORMAT 
{
    unsigned int dwSize;
    unsigned int dwFlags;
    unsigned int dwFourCC;
    unsigned int dwRGBBitCount;
    unsigned int dwRBitMask;
    unsigned int dwGBitMask;
    unsigned int dwBBitMask;
    unsigned int dwABitMask;
} DDS_PIXELFORMAT;

typedef struct _DDS_HEADER 
{
    unsigned int dwSize;
    unsigned int dwFlags;
    unsigned int dwHeight;
    unsigned int dwWidth;
    unsigned int dwPitchOrLinearSize;
    unsigned int dwDepth;
    unsigned int dwMipMapCount;
    unsigned int dwReserved1[11];
    DDS_PIXELFORMAT ddspf;
    unsigned int dwCaps1;
    unsigned int dwCaps2;
    unsigned int dwReserved2[3];
} DDS_HEADER;
#endif /* __INCLUDED_NV_HHDDS_INTERNAL_H */
