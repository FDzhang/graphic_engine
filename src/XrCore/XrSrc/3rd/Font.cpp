#include "Font.h"
extern char *gl_path[];
#include "../Common/XrInternal.h"
#include "../XrCore/CDeviceManager.h"

XrFont::XrFont()
{
	m_pFontData = 0;
	m_VertCount = 0;
	m_dynamic = 0;
}

XrFont::~XrFont()
{
}

int XrFont::GenVertex(int charNum, float offsetX, float offsetY, float size, float* vBuffer, unsigned short* iBuffer, int VertStartNum, float* color)
{
	float scale = size/FONT_SIZE;
	int x, y, count=charNum-32, width, height, horiBearingY, horiBearingX;
	int vCount=0, iCount=0;
	if (count < 0 || count > 126) return -1;
	y = (count / FONT_DIV) * FONT_SIZE;
	x = (count % FONT_DIV) * FONT_SIZE;

	width = m_texInfo[count].width * scale;
	height = m_texInfo[count].height * scale;
	horiBearingY = m_texInfo[count].horiBearingY * scale;
	horiBearingX = m_texInfo[count].horiBearingX * scale;

	vBuffer[0] = offsetX+horiBearingX;
	vBuffer[1] = offsetY-horiBearingY+size;
	vBuffer[2] = color[3];
	vBuffer[3] = color[0];
	vBuffer[4] = color[1];
	vBuffer[5] = color[2];
	vBuffer[6] = float(x)/FONT_TEX_SIZE;
	vBuffer[7] = float(y)/FONT_TEX_SIZE;

	vBuffer[8+0] = offsetX+horiBearingX;
	vBuffer[8+1] = offsetY-horiBearingY+height+size;
	vBuffer[8+2] = color[3];
	vBuffer[8+3] = color[0];
	vBuffer[8+4] = color[1];
	vBuffer[8+5] = color[2];
	vBuffer[8+6] = float(x)/FONT_TEX_SIZE;
	vBuffer[8+7] = float(y+m_texInfo[count].height)/FONT_TEX_SIZE;

	vBuffer[8*2+0] = offsetX+horiBearingX+width;
	vBuffer[8*2+1] = offsetY-horiBearingY+height+size;
	vBuffer[8*2+2] = color[3];
	vBuffer[8*2+3] = color[0];
	vBuffer[8*2+4] = color[1];
	vBuffer[8*2+5] = color[2];
	vBuffer[8*2+6] = float(x+m_texInfo[count].width)/FONT_TEX_SIZE;
	vBuffer[8*2+7] = float(y+m_texInfo[count].height)/FONT_TEX_SIZE;

	vBuffer[8*3+0] = offsetX+horiBearingX+width;
	vBuffer[8*3+1] = offsetY-horiBearingY+size;
	vBuffer[8*3+2] = color[3];
	vBuffer[8*3+3] = color[0];
	vBuffer[8*3+4] = color[1];
	vBuffer[8*3+5] = color[2];
	vBuffer[8*3+6] = float(x+m_texInfo[count].width)/FONT_TEX_SIZE;
	vBuffer[8*3+7] = float(y)/FONT_TEX_SIZE;

	iBuffer[0] = VertStartNum;
	iBuffer[1] = VertStartNum + 1;
	iBuffer[2] = VertStartNum + 2;
	iBuffer[3] = VertStartNum;
	iBuffer[4] = VertStartNum + 2;
	iBuffer[5] = VertStartNum + 3;
}

int XrFont::AddText(float x, float y, float size, char* text, float* vBuffer, unsigned short* iBuffer, int* vCount, int* iCount, float* color)
{
	float scale = size/FONT_SIZE;
	int dx = 0, num = 0, wordCount=0, VertStartNum = *vCount;
	int charNum = *text++;
	//wordSegment[m_wordCount].startIndex = m_VertCount;
	while (charNum) {
		GenVertex(charNum, x+dx, y, size, &vBuffer[wordCount*4*8], &iBuffer[wordCount*6], VertStartNum, color);
		dx+= m_texInfo[charNum-32].advanceX*scale;
		charNum = *text++;
		wordCount++;
		VertStartNum+=4;
	}
	*vCount += wordCount*4;
	*iCount += wordCount*6;
	return wordCount;
}

int XrFont::MeasureText(char* text, float size, float* w, float* h)
{
	float scale = size/FONT_SIZE;
	int x = 0,wordCount=0, y=0;
	int charNum = *text++;
	//wordSegment[m_wordCount].startIndex = m_VertCount;
	while (charNum) {
		x+= m_texInfo[charNum-32].advanceX*scale;
		if (y<m_texInfo[charNum-32].height*scale) y=m_texInfo[charNum-32].height*scale;
		charNum = *text++;
		wordCount++;
	}
	*w = x;
	*h = y;
	return wordCount;
}

void XrFont::Clear()
{
	m_VertCount = 0;
}

void XrFont::SaveTexFontInfo(FT_GlyphSlot slot, int id)
{
//	printf("set id = %d\n", id);
	m_texInfo[id].id = id;
	m_texInfo[id].width = slot->bitmap.width;
	m_texInfo[id].height = slot->bitmap.rows;
	m_texInfo[id].horiBearingX = slot->metrics.horiBearingX>>6;
	m_texInfo[id].horiBearingY = slot->metrics.horiBearingY>>6;
	m_texInfo[id].advanceX = slot->advance.x>>6;
	m_texInfo[id].advanceY = slot->advance.y>>6;
}

bool XrFont::DeInit()
{
	if (m_pFontData) {
		delete m_pFontData;
		FT_Done_FreeType(m_library);
	}
	
	m_pFontData = 0;
	return TRUE;
}

bool XrFont::Init(const char* filename)
{
	int x,y;
	FT_Error   error;

	error = FT_Init_FreeType( &m_library );

	if ( error ) {
	  return -1;
	}
    char tempPath[256];
    //GetFileFullPath(filename, tempPath);
	error = FT_New_Face(m_library, filename, 0, &m_face );
	if ( error == FT_Err_Unknown_File_Format ) return -1;
	else if ( error ) return -1;

	m_pFontData = new unsigned char[FONT_TEX_SIZE*FONT_TEX_SIZE];
	if (!m_pFontData) return -1;

	//error = FT_Set_Char_Size(
	//          m_face,    /* handle to face object         */
	//          0,       /* char_width in 1/64th of points  */
	//          16*64,   /* char_height in 1/64th of points */
	//          300,     /* horizontal device resolution    */
	//          300 );   /* vertical device resolution      */

	error = FT_Set_Pixel_Sizes(
            m_face,   /* handle to face object */
            FONT_SIZE,      /* pixel_width           */
            FONT_SIZE );   /* pixel_height          */

	FT_GlyphSlot  slot = m_face->glyph;  /* a small shortcut */
	FT_UInt       glyph_index;
	int           pen_x, pen_y, n;

  //... initialize library ...
  //... create face object ...
  //... set character size ...

	unsigned char* dst = m_pFontData;
	for (int y=0; y<FONT_TEX_SIZE; y++) {
		for (int x=0; x<FONT_TEX_SIZE; x++) {
			dst[x] = 0x0;
		}
		dst+=FONT_TEX_SIZE;
	}

	//int num_chars = 15;//sizeof(TextContent);

	for (y = 0; y < FONT_DIV; y++ ) {
		pen_y = y*FONT_SIZE;
		for (x = 0; x < FONT_DIV; x++ ) {
			pen_x = x*FONT_SIZE;
			/* load glyph image into the slot (erase previous one) */
			int character = 32+y*FONT_DIV+x;
			if (character>126) break;
			error = FT_Load_Char(m_face, character, FT_LOAD_RENDER );
			if ( error )
			  continue;  /* ignore errors */

			slot->metrics;

			/* now, draw to our target surface */
			DrawFont2Tex( &slot->bitmap,
							pen_x+OFFSET_SIZE,
							pen_y+OFFSET_SIZE, //pen_y + FON_SIZE - (slot->metrics.horiBearingY>>6
							0xFFFFFFFF);
			SaveTexFontInfo(slot, y*FONT_DIV+x);
		}
	}
	return 0;
}

int XrFont::FillTexture(CTexture* tex)
{
	XRDM->UpdateTexture(m_pFontData, tex);
	return 0;
}

void XrFont::DrawFont2Tex(FT_Bitmap* bitmap, int advx, int advy, unsigned int color)
{
	unsigned char* src = bitmap->buffer;
	unsigned char* dst = m_pFontData+advx+advy*FONT_TEX_SIZE;
	int width = bitmap->width;
	int height= bitmap->rows;

	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) {
			dst[x] = src[x];
		}
		dst+=FONT_TEX_SIZE;
		src+=width;
	}
}
