#ifndef __GL_FILE_H__
#define __GL_FILE_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIN32
typedef struct                       /**** BMP file header structure ****/
    {
    unsigned short bfType;           /* Magic number for file */
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
    } BITMAPFILEHEADER;

#  define BF_TYPE 0x4D42             /* "MB" */

typedef struct                       /**** BMP file info structure ****/
    {
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of color planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colors used */
    unsigned int   biClrImportant;   /* Number of important colors */
    } BITMAPINFOHEADER;

/*
 * Constants for the biCompression field...
 */

#  define BI_RGB       0             /* No compression - straight BGR data */
#  define BI_RLE8      1             /* 8-bit run-length compression */
#  define BI_RLE4      2             /* 4-bit run-length compression */
#  define BI_BITFIELDS 3             /* RGB bitmap with RGB masks */


typedef struct                       
    {
    unsigned char  rgbBlue;   
    unsigned char  rgbGreen;     
    unsigned char  rgbRed;         
    unsigned char  rgbReserved; 
    } _RGBQUAD;

typedef struct                       /**** Bitmap information structure ****/
    {
    BITMAPINFOHEADER bmiHeader;      /* Image header */
    _RGBQUAD          bmiColors[256]; /* Image colormap */
    } BITMAPINFO;
#else
#include "Windows.h"
#endif

/*
 * Prototypes...
 */

unsigned char *LoadDIBitmap(const char *filename, BITMAPINFO **info);
int SaveDIBitmap(const char *filename, BITMAPINFO *info, unsigned char *bits);

//int LoadPNG(char* file_name, Bitmap* pBitmap);
int LoadShaderFromFile(char* file_name, char** pString);
char* GetValidFilePath(char* path[], char* filename);
bool ReadFloatSpaceTxtFile(char *filename,float *content,int size);
bool ReadFloatBinFile(char *filename,float *content,int size);
bool ReadIntSpaceTxtFile(char *filename,int *content,int size);

#ifdef __cplusplus
}
#endif

#endif // __GL_FILE_H__
