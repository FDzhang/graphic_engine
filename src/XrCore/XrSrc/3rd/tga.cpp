/********************************************************************************
/Name:		TGA.cpp																*
/Header:	tga.h																*
/Purpose:	Load Compressed and Uncompressed TGA files							*
/Functions:	LoadTGA(Texture * texture, char * filename)							*
/			LoadCompressedTGA(Texture * texture, char * filename, XrFile * fTGA)	*
/			LoadUncompressedTGA(Texture * texture, char * filename, XrFile * fTGA)*	
/*******************************************************************************/
#include "tga.h"


/********************************************************************************
/name :		LoadTGA(Texture * texture, char * filename)							*
/function:  Open and test the file to make sure it is a valid TGA file			*	
/parems:	texture, pointer to a Texture structure								*
/			filename, string pointing to file to open							*
/********************************************************************************/

unsigned char uTGAcompare[12] = {0,0,2, 0,0,0,0,0,0,0,0,0};	// Uncompressed TGA Header
unsigned char cTGAcompare[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// Compressed TGA Header
bool LoadUncompressedTGA(XrBuffer * buffer, char * name, XrFile * fp);	// Load an Uncompressed file
bool LoadCompressedTGA(XrBuffer *buffer , char * name, XrFile * fp);		// Load a Compressed file

TGAHeader tgaheader;									// TGA header
TGA tga;												// TGA image data
bool LoadTGA(XrBuffer* buffer, char * filename)				// Load a TGA file
{
	XrFile * fTGA;												// File pointer to texture file
	fTGA = XrFOpen(filename, (String)"rb");								// Open file for reading

	if(fTGA == NULL)											// If it didn't open....
	{
		//MessageBox(NULL, "Could not open texture file", "ERROR", MB_OK);	// Display an error message
		return false;														// Exit function
	}

	if(XrFRead(&tgaheader, sizeof(TGAHeader), 1, fTGA) == 0)					// Attempt to read 12 byte header from file
	{
		//MessageBox(NULL, "Could not read file header", "ERROR", MB_OK);		// If it fails, display an error message 
		if(fTGA != NULL)													// Check to seeiffile is still open
		{
			XrFClose(fTGA);													// If it is, close it
		}
		return false;														// Exit function
	}

	if(memcmp(uTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)				// See if header matches the predefined header of 
	{																		// an Uncompressed TGA image
		LoadUncompressedTGA(buffer, filename, fTGA);						// If so, jump to Uncompressed TGA loading code
	}
	else if(memcmp(cTGAcompare, &tgaheader, sizeof(tgaheader)) == 0)		// See if header matches the predefined header of
	{																		// an RLE compressed TGA image
		LoadCompressedTGA(buffer, filename, fTGA);							// If so, jump to Compressed TGA loading code
	}
	else																	// If header matches neither type
	{
		//MessageBox(NULL, "TGA file be type 2 or type 10 ", "Invalid Image", MB_OK);	// Display an error
		XrFClose(fTGA);
		return false;																// Exit function
	}
	return true;															// All went well, continue on
}

bool LoadUncompressedTGA(XrBuffer * texture, char * filename, XrFile * fTGA)	// Load an uncompressed TGA (note, much of this code is based on NeHe's 
{																			// TGA Loading code nehe.gamedev.net)
	if(XrFRead(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Read TGA header
	{										
		//MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display error
		if(fTGA != NULL)													// if file is still open
		{
			XrFClose(fTGA);													// Close it
		}
		return false;														// Return failular
	}	

	texture->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	int bpp	= tga.header[4];										// Determine the bits per pixel
	tga.Width		= texture->width;										// Copy width into local structure						
	tga.Height		= texture->height;										// Copy height into local structure
	tga.Bpp			= bpp;											// Copy BPP into local structure

	if((texture->width <= 0) || (texture->height <= 0) || ((bpp != 24) && (bpp !=32)))	// Make sure all information is valid
	{
		//MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);	// Display Error
		if(fTGA != NULL)													// Check if file is still open
		{
			XrFClose(fTGA);													// If so, close it
		}
		return false;														// Return failed
	}

	if(bpp == 24)													// If the BPP of the image is 24...
		texture->format	= XR_R8G8B8;											// Set Image type to GL_RGB
	else																	// Else if its 32 BPP
		texture->format	= XR_R8G8B8A8;											// Set image type to GL_RGBA

	tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute the number of BYTES per pixel
	tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute the total amout ofmemory needed to store data
	texture->pData	= (unsigned char *)malloc(tga.imageSize);					// Allocate that much memory

	if(texture->pData == NULL)											// If no space was allocated
	{
		//MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);	// Display Error
		XrFClose(fTGA);														// Close the file
		return false;														// Return failed
	}

	if(XrFRead(texture->pData, 1, tga.imageSize, fTGA) != tga.imageSize)	// Attempt to read image data
	{
		//MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);		// Display Error
		if(texture->pData != NULL)										// If imagedata has data in it
		{
			free(texture->pData);										// Delete data from memory
		}
		XrFClose(fTGA);														// Close file
		return false;														// Return failed
	}

	// Byte Swapping Optimized By Steve Thomas
	for(int cswap = 0; cswap < (int)tga.imageSize; cswap += tga.bytesPerPixel)
	{
		texture->pData[cswap] ^= texture->pData[cswap+2] ^=
		texture->pData[cswap] ^= texture->pData[cswap+2];
	}

	XrFClose(fTGA);															// Close file
	return true;															// Return success
}

bool LoadCompressedTGA(XrBuffer * texture, char * filename, XrFile * fTGA)		// Load COMPRESSED TGAs
{ 
	if(XrFRead(tga.header, sizeof(tga.header), 1, fTGA) == 0)					// Attempt to read header
	{
		//MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display Error
		if(fTGA != NULL)													// If file is open
		{
			XrFClose(fTGA);													// Close it
		}
		return false;														// Return failed
	}

	texture->width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
	texture->height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
	int bpp	= tga.header[4];										// Determine Bits Per Pixel
	tga.Width		= texture->width;										// Copy width to local structure
	tga.Height		= texture->height;										// Copy width to local structure
	tga.Bpp			= bpp;											// Copy width to local structure

	if((texture->width <= 0) || (texture->height <= 0) || ((bpp != 24) && (bpp !=32)))	//Make sure all texture info is ok
	{
		//MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);	// If it isnt...Display error
		if(fTGA != NULL)													// Check if file is open
		{
			XrFClose(fTGA);													// Ifit is, close it
		}
		return false;														// Return failed
	}

	if(bpp == 24)													// If the BPP of the image is 24...
		texture->format	= XR_R8G8B8;											// Set Image type to GL_RGB
	else																	// Else if its 32 BPP
		texture->format	= XR_R8G8B8A8;											// Set image type to GL_RGBA

	tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute BYTES per pixel
	tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute amout of memory needed to store image
	texture->pData	= (unsigned char *)malloc(tga.imageSize);					// Allocate that much memory

	if(texture->pData == NULL)											// If it wasnt allocated correctly..
	{
		//MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);	// Display Error
		XrFClose(fTGA);														// Close file
		return false;														// Return failed
	}

	unsigned int pixelcount	= tga.Height * tga.Width;							// Nuber of pixels in the image
	unsigned int currentpixel	= 0;												// Current pixel being read
	unsigned int currentbyte	= 0;												// Current byte 
	unsigned char * colorbuffer = (unsigned char *)malloc(tga.bytesPerPixel);			// Storage for 1 pixel

	do
	{
		unsigned char chunkheader = 0;											// Storage for "chunk" header

		if(XrFRead(&chunkheader, sizeof(unsigned char), 1, fTGA) == 0)				// Read in the 1 byte header
		{
			//MessageBox(NULL, "Could not read RLE header", "ERROR", MB_OK);	// Display Error
			if(fTGA != NULL)												// If file is open
			{
				XrFClose(fTGA);												// Close file
			}
			if(texture->pData != NULL)									// If there is stored image data
			{
				free(texture->pData);									// Delete image data
			}
			return false;													// Return failed
		}

		if(chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
		{																	// that follow the header
			chunkheader++;													// add 1 to get number of following color values
			for(short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
			{
				if(XrFRead(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel) // Try to read 1 pixel
				{
					//MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);		// IF we cant, display an error

					if(fTGA != NULL)													// See if file is open
					{
						XrFClose(fTGA);													// If so, close file
					}

					if(colorbuffer != NULL)												// See if colorbuffer has data in it
					{
						free(colorbuffer);												// If so, delete it
					}

					if(texture->pData != NULL)										// See if there is stored Image data
					{
						free(texture->pData);										// If so, delete it too
					}

					return false;														// Return failed
				}
																						// write to memory
				texture->pData[currentbyte		] = colorbuffer[2];				    // Flip R and B vcolor values around in the process 
				texture->pData[currentbyte + 1	] = colorbuffer[1];
				texture->pData[currentbyte + 2	] = colorbuffer[0];

				if(tga.bytesPerPixel == 4)												// if its a 32 bpp image
				{
					texture->pData[currentbyte + 3] = colorbuffer[3];				// copy the 4th byte
				}

				currentbyte += tga.bytesPerPixel;										// Increase thecurrent byte by the number of bytes per pixel
				currentpixel++;															// Increase current pixel by 1

				if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
				{
					//MessageBox(NULL, "Too many pixels read", "ERROR", NULL);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						XrFClose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->pData != NULL)										// If there is Image data
					{
						free(texture->pData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
		else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
		{
			chunkheader -= 127;															// Subteact 127 to get rid of the ID bit
			if(XrFRead(colorbuffer, 1, tga.bytesPerPixel, fTGA) != tga.bytesPerPixel)		// Attempt to read following color values
			{	
				//MessageBox(NULL, "Could not read from file", "ERROR", MB_OK);			// If attempt fails.. Display error (again)

				if(fTGA != NULL)														// If thereis a file open
				{
					XrFClose(fTGA);														// Close it
				}

				if(colorbuffer != NULL)													// If there is data in the colorbuffer
				{
					free(colorbuffer);													// delete it
				}

				if(texture->pData != NULL)											// If thereis image data
				{
					free(texture->pData);											// delete it
				}

				return false;															// return failed
			}

			for(short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
			{																			// by the header
				texture->pData[currentbyte		] = colorbuffer[2];					// switch R and B bytes areound while copying
				texture->pData[currentbyte + 1	] = colorbuffer[1];
				texture->pData[currentbyte + 2	] = colorbuffer[0];

				if(tga.bytesPerPixel == 4)												// If TGA images is 32 bpp
				{
					texture->pData[currentbyte + 3] = colorbuffer[3];				// Copy 4th byte
				}

				currentbyte += tga.bytesPerPixel;										// Increase current byte by the number of bytes per pixel
				currentpixel++;															// Increase pixel count by 1

				if(currentpixel > pixelcount)											// Make sure we havent written too many pixels
				{
					//MessageBox(NULL, "Too many pixels read", "ERROR", NULL);			// if there is too many... Display an error!

					if(fTGA != NULL)													// If there is a file open
					{
						XrFClose(fTGA);													// Close file
					}	

					if(colorbuffer != NULL)												// If there is data in colorbuffer
					{
						free(colorbuffer);												// Delete it
					}

					if(texture->pData != NULL)										// If there is Image data
					{
						free(texture->pData);										// delete it
					}

					return false;														// Return failed
				}
			}
		}
	}

	while(currentpixel < pixelcount);													// Loop while there are still pixels left
	XrFClose(fTGA);																		// Close the file
	return true;																		// return success
}
