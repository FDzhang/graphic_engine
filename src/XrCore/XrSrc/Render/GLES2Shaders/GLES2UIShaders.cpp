
#include "GLES2Shaders.h"

#include "../XrRender.h"

#ifndef USE_DX11


const char* VS_P_dummy_fx = "";
const char* VS_PT_dummy_fx = "";
const char* VS_PNT_dummy_fx = "";
const char* VS_PNTWI_dummy_fx = "";
const char* VS_PNBT_dummy_fx = "";
const char* VS_PNBTWI_dummy_fx = "";
const char* VS_PTACDEFGHJL_dummy_fx = "";

const char* UI_Spirit = "UI_Spirit";
/////////////////// 001 Shader_UI_Spirit /////////////////////
const char* UI_Spirit_vs = "\
	attribute highp vec4 VertexPos;\n\
	attribute highp vec4 VertexNormal;\n\
	attribute highp vec2 InTexCood;\n\
	uniform highp mat4 TransformMatrix;\n\
	varying highp vec4 color;\n\
	varying highp vec2 TexCoord;\n\
	void main(void)\
	{\
		gl_Position = TransformMatrix * vec4(VertexPos.x, VertexPos.y, 2.0, 1.0);\n\
		TexCoord = InTexCood;\n\
		color.a = VertexPos.z;\n\
		color.rgb = VertexNormal.xyz;\n\
	}";
const char* UI_Spirit_fs = "\
	uniform highp sampler2D sampler2d;\n\
	varying highp vec2 TexCoord;\n\
	varying highp vec4 color;\n\
	void main (void)\
	{\
	   gl_FragColor = texture2D(sampler2d, TexCoord);\n\
	   gl_FragColor.rgb = gl_FragColor.rgb*color.rgb;\n\
	   gl_FragColor.a = gl_FragColor.a * color.a;\n\
	}";

XRVertexLayout UI_Spirit_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 UI_Spirit_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_BLEND_DEFAULT;

const char* UI_Font = "UI_Font";
/////////////////// 001 Shader_UI_Font /////////////////////
const char* UI_Font_vs = "\
	attribute highp vec4 VertexPos;\n\
	attribute highp vec4 VertexNormal;\n\
	attribute highp vec2 InTexCood;\n\
	uniform highp mat4 TransformMatrix;\n\
	varying highp vec2 TexCoord;\n\
	varying highp vec4 color;\n\
	void main(void)\
	{\
		gl_Position = TransformMatrix * vec4(VertexPos.x, VertexPos.y, 2.0, 1.0);\n\
		TexCoord = InTexCood;\n\
		color.a = VertexPos.z; \
		color.rgb = VertexNormal.xyz; \
	}";
const char* UI_Font_fs = "\
	uniform highp sampler2D sampler2d;\n\
	varying highp vec2 TexCoord;\n\
	varying highp vec4 color;\n\
	void main (void)\
	{\
		gl_FragColor.a = texture2D(sampler2d, TexCoord).a*color.a;\n\
		gl_FragColor.rgb = color.rgb;\n\
	}";

XRVertexLayout UI_Font_layout_index = XR_VERTEX_LAYOUT_PNT;
UInt32 UI_Font_render_state = XR_CULLMODE_NONE | XR_FRONTFACE_CCW | XR_BLEND_DEFAULT;


#endif
//UInt32 UI_Font_render_state = XR_CULLMODE_BACK | XR_FRONTFACE_CW | XR_DEPTHTEST_ENABLE | XR_DEPTHWRITE_ENABLE | XR_DEPTHTEST_LT | XR_BLEND_DEFAULT;