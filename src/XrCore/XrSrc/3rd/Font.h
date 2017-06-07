#ifndef __XRFont_H_
#define __XRFont_H_

#define FONT_TEX_SIZE 512

#define OFFSET_SIZE 0
#define FONT_DIV 10
#define FONT_SIZE (FONT_TEX_SIZE/FONT_DIV)
#define ADJ_SIZE 0

//Include our header file.
#include "ft2build.h"
#include FT_FREETYPE_H

typedef struct tagUIVertex{
	float x;
	float y;
	float u;
	float v;
} UIVertex;

typedef struct tagTexFontInfo{
	unsigned int id;
	unsigned int width;
	unsigned int height;
	int horiBearingX;
	int horiBearingY;
	int advanceX;
	int advanceY;
} TexFontInfo;

class XrFont
{
public:
	XrFont();
	~XrFont();

	bool Init(const char* filename);
	bool DeInit();
	void SaveTexFontInfo(FT_GlyphSlot slot, int id);

	void SetColor(float R, float G, float B);
	
	void DrawFont2Tex(FT_Bitmap* bitmap, int x, int y, unsigned int color);
	int AddText(float x, float y, float size, char* text, float* vBuffer, unsigned short* iBuffer, int* vCount, int* iCount, float* color);
	int MeasureText(char* text, float size, float* w, float* h);
	int GenVertex(int charNum, float offsetX, float offsetY, float size, float* vBuffer, unsigned short* iBuffer, int VertStartNum, float* color);
	int FillTexture(class CTexture* tex);
	void Clear();
	void Draw();
	void Test();
	void flush();
	static int GetTexSize() { return FONT_TEX_SIZE; }
//private:
	struct {
		unsigned int uiId;
		unsigned int textColor;
	} m_uiTextObject;

	FT_Library		m_library;
	FT_Face			m_face;
	unsigned int	m_fontTexture;
	unsigned char*	m_pFontData;
	float			m_fontColor[3];
	TexFontInfo		m_texInfo[FONT_DIV*FONT_DIV];

	#define MAX_TEXT_COUNT 128
	#define MAX_WORD_COUNT 16

	int				m_wordCount;
	unsigned int	m_screenWidth;
	unsigned int	m_screenHeight;
	unsigned int	m_textVert;
	unsigned int	m_textIndx;
	int				m_dynamic;
	int				m_VertCount;
};


#endif /* __XRFont_H_ */
