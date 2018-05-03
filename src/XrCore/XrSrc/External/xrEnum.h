#ifndef __XRENUM_H__
#define __XRENUM_H__

#pragma warning( disable : 4250 )


//enum TexFormat {
//    TexFormat_NULL					= 0x00000000,
//    TexFormat_RGB					= 0x00000001,
//	TexFormat_RGBA					= 0x00010001,
//	TexFormat_Alpha					= 0x00010000,
//    TexFormat_Luminance				= 0x00000010,
//	TexFormat_LuminanceA			= 0x00010010,
//	TexFormat_Depth					= 0x00100000,
//};

//enum TexOption {
//    TexOption_Default				= 0x00000000,
//    TexOption_Clamp					= 0x00000000,
//	TexOption_Repeat				= 0x00000001,
//	TexOption_Linear				= 0x00000000,
//	TexOption_Nearest			    = 0x00000010,
//};

enum StackingRank {
	StackingRank_Lowest			= 0x00000000,
	StackingRank_Lower			= 0x0000001F,
	StackingRank_Low			= 0x0000003F,
	StackingRank_Normal			= 0x0000007F,
	StackingRank_High			= 0x000000AF,
	StackingRank_Higher			= 0x000000CF,
	StackingRank_Highest		= 0x000000FF,
};

enum RenderNodeType {
    RenderNodeType_NULL                    = 0x00000000,
	RenderNodeType_3D					   = 0x00000010,
	RenderNodeType_SPIRIT				   = 0x0000000F,
	RenderNodeType_UI					   = 0x00000001,
    RenderNodeType_UI2D                    = 0x00000001,
	RenderNodeType_UI3D                    = 0x00000011,
	RenderNodeType_EFFECT				   = 0x00FF0000,
	RenderNodeType_Effect_Blur			   = 0x00010000,
	RenderNodeType_Effect_Ripple		   = 0x00020000,
	RenderNodeType_Effect_Frost			   = 0x00030000,
	RenderNodeType_PostProcessing		   = 0x00040000,
	RenderNodeType_Opaque				   = 0x00100000,
};


enum BlendMode {
	BlendMode_Defualt						= 0x00000000,
    BlendMode_Add							= 0x00001000,
	BlendMode_Multiply						= 0x00002000,
};

//!!!!!!!!!
enum DrawMode {
	DrawMode_Points							= 0x00000001,
    DrawMode_Lines							= 0x00000002,
	DrawMode_LineLoop						= 0x00000003,
	DrawMode_LineStrip						= 0x00000004,
    DrawMode_Triangles						= 0x00000005,
	DrawMode_TriangleStrip					= 0x00000006,
	DrawMode_TriangleFan					= 0x00000007,
	DrawMode_DrawStyle						= 0x0000000F,
	DrawMode_StateDisable					= 0x00FF0000,
	DrawMode_NoFaceCulling					= 0x00010000,
	DrawMode_NoDepthTest					= 0x00020000,
	DrawMode_NoDepthMask					= 0x00040000,
	DrawMode_NoColorMask					= 0x00080000,
	DrawMode_NoColorBlend					= 0x00100000,
	DrawMode_StateEnable					= 0xFF000000,
	DrawMode_DoFaceCulling					= 0x01000000,
	DrawMode_DoDepthTest					= 0x02000000,
	DrawMode_DoDepthMask					= 0x04000000,
	DrawMode_DoColorMask					= 0x08000000,
	DrawMode_DoColorBlend					= 0x10000000,
	DrawMode_DepthFuncGE					= 0x00000010,
	DrawMode_DepthFuncEQ					= 0x00000020,
	DrawMode_DepthFuncLE					= 0x00000040,
	DrawMode_DrawFaceCW						= 0x00000100,
	DrawMode_DrawFaceCCW					= 0x00000200,
	DrawMode_AlphaBlend						= 0x00001000,
	DrawMode_AdditiveBlend					= 0x00002000,
	DrawMode_DepthOffset					= 0x00000800,
	DrawMode_DrawState						= 0x00000FF0,
};

enum MaterialType {
	Material_Null							= 0x00000000,
    Material_UI_Spirit				        = 0x00000001,
	Material_DiffuseOnly                    = 0x00000001,
	Material_UI_Glow				        = 0x00001001,
	Material_UI_Shadow				        = 0x00002001,
	Material_UI_Spirit_With_Mask			= 0x00004001,
	Material_Mask    						= 0x00004000,
	Material_Video							= 0x01000001,
	Material_UI_Font						= 0x00000002,
	Material_AlphaShape   					= 0x00000002,
	Material_Embose							= 0x00000004,
	Material_DynMsk							= 0x00000007,
	Material_Matte							= 0x00000010,
	Material_Reflect						= 0x00000011,
	Material_Refract						= 0x00000012,
	Material_Rigid_Texture					= 0x00000013,
	Material_RigidColor_Texture				= 0x0000001b,	
	Material_Skinned_Texture                = 0x00010013,
	Material_Rigid_Bump						= 0x00000014,
	Material_Skinned_Bump		            = 0x00010014,
	Material_RigidVideo_Texture			    = 0x0000001A,	
	Material_Skinned			            = 0x00010000,
	Material_Glass							= 0x00000016,
	Material_Glossy							= 0x00000017,
	Material_Glossy_Color					= 0x00000018,
	Material_Glass_Alpha    				= 0x00000019,	
	Material_Glossy_Alpha					= 0x00000021,
	Material_Shadow_Skinned		            = 0x00110000,
	Material_Shadow				            = 0x00100000,
	Material_Simple_Video					= 0x01000013,
	Material_Simple_Video_Mask				= 0x01010013,
	Material_SkyBox							= 0x00000015,	
	Material_Rigid_Blend					= 0x00000020,
	Material_Dynamic_Blend					= 0x00000030,	
	Material_Color_Plot                     = 0x00000070,
	Material_Custom							= 0x10000000,
};

enum ModelType {
	ModelType_Null							= 0x00000000,
	ModelType_Cube							= 0x00000001,
	ModelType_Plane_Dynamic					= 0x00000002,   //plane with special curve
	ModelType_Plane 						= 0x00000004,
	ModelType_ArrowPath 					= 0x00000005,
	ModelType_Plane_ARC 						= 0x00000008,
	ModelType_Line      					= 0x00000006,	
	ModelType_Internal						= 0x000000FF,
	ModelType_External						= 0x00000100,	//load from file
};

enum LightType {
	LightType_Null							= 0x00000000,
	LightType_Ambient						= 0x00000001,
	LightType_Directional					= 0x00000002,
	LightType_Point							= 0x00000003,
	LightType_Spot							= 0x00000004,
};

enum APType {
	AP_None						= 0x00000000,
	AP_X							= 0x00000001,
	AP_Y							= 0x00000002,
	AP_Z 							= 0x00000004,
	AP_RX							= 0x00000010,
	AP_RY							= 0x00000020,
	AP_RZ 							= 0x00000040,
	AP_SX							= 0x00000100,
	AP_SY							= 0x00000200,
	AP_SZ 							= 0x00000400,
	AP_WIDTH						= 0x00000008,
	AP_HEIGHT						= 0x00000080,
	AP_OPACITY						= 0x00000800,
	AP_SRX							= 0x00001000,	//self rotation
	AP_SRY							= 0x00002000,
	AP_SRZ 							= 0x00004000,
	AP_CamAtX						= 0x00010000,
	AP_CamAtY						= 0x00020000,
	AP_CamAtZ 						= 0x00040000,
	AP_VX							= 0x00010000,
	AP_VY							= 0x00020000,
	AP_VZ 							= 0x00040000,
	AP_CamFOV				= 0x00100000,
	AP_ALL						= 0xFFFFFFF,
};



enum DrawFace {
	DrawFace_None							= 0x00000000,
	DrawFace_CCW							= 0x00000001,
	DrawFace_CW							    = 0x00000002,
	DrawFace_Both							= 0x00000003,
};

enum ThreadApartment {
    ThreadApartment_UIMain                      = 0x00000000,
    ThreadApartment_XrCore                      = 0x00010000,
};

enum BindingStyle {
    BindingStyle_None                           = 0x00000000,
    BindingStyle_OneWaySrcToDst                 = 0x00000001,
    BindingStyle_OneWayDstToSrc                 = 0x00000002,
    BindingStyle_TwoWay                         = 0x00000003,
};

enum AnimationStyle {
	AnimationStyle_Disable						= 0x00000000,
    AnimationStyle_Default                      = 0x00000001,
    AnimationStyle_EaseIn                       = 0x00000002,
    AnimationStyle_EaseOut                      = 0x00000003,
    AnimationStyle_EaseInOut                    = 0x00000004,
	AnimationStyle_Transition                   = 0x0000000F,
	AnimationStyle_KeyLinear                    = 0x00000010,
	AnimationStyle_KeySpline                    = 0x00000020,
	AnimationStyle_KeySimpleLinear				= 0x00000040,
	
};

enum AnimationProperty {
    //NormalProperties
    AnimationProperty_X                         = 0x00030000,
    AnimationProperty_Y                         = 0x00030001,
    AnimationProperty_Width                     = 0x00030002,
    AnimationProperty_Height                    = 0x00030004,
    AnimationProperty_Opacity                   = 0x00030008,
    AnimationProperty_Color                     = 0x00030010,
    //BinaryProperties
    AnimationProperty_Visible                   = 0x00030020,
    AnimationProperty_IsHit                     = 0x00030040,

    AnimationProperty_All                       = 0x0003FFFF,
};

#define HORIZONTAL_MASK  0x0F
#define VERTICAL_MASK    0xF0

enum XrAlignMode {
	XrAlignMode_Default								= 0x00000000,
    XrAlignMode_Left								= 0x00000000,	
	XrAlignMode_LeftTop								= 0x00000000,
	XrAlignMode_Top									= 0x00000000,
	XrAlignMode_Center							    = 0x00000001,				
	XrAlignMode_CenterTop							= 0x00000001,
	XrAlignMode_Right   							= 0x00000002,
	XrAlignMode_RightTop							= 0x00000002,
	XrAlignMode_RightMiddle                         = 0x00000012,
	XrAlignMode_RightBottom                         = 0x00000022,
	XrAlignMode_CenterBottom                        = 0x00000021,
	XrAlignMode_LeftBottom							= 0x00000020,
	XrAlignMode_LeftMiddle							= 0x00000010,
	XrAlignMode_Bottom								= 0x00000020,
	XrAlignMode_Middle								= 0x00000010,
	XrAlignMode_CenterMiddle                        = 0x00000011,
	XrAlignMode_Stretch								= 0x00110000,
	XrAlignMode_StretchAutoAdapt					= 0x01000000,
	//XrAlignMode_StretchHollow                       = 0x00020000,      
	XrAlignMode_Custom								= 0x10000000,
	XrAlignMode_DockBottom							= 0x00010020,  
	XrAlignMode_DockLeft							= 0x00100000,  
	XrAlignMode_DockRight							= 0x00100002,  
	XrAlignMode_DockTop								= 0x00010000, 
	XrAlignMode_DockStretch							= 0x00110000,  
	
};

enum LayoutMode {
    LayoutMode_Free                             = 0x00000000,
    LayoutMode_StackX                           = 0x00000001,
    LayoutMode_StackY                           = 0x00000002,
    LayoutMode_WrapX                            = 0x00000003,
	LayoutMode_WrapY                            = 0x00000004,
    LayoutMode_Dock                             = 0x00000005,
    LayoutMode_Grid                             = 0x00000006,
};

enum ScrollMode {
    ScrollMode_None                             = 0x00000000,
    ScrollMode_X                                = 0x00000001,
    ScrollMode_Y                                = 0x00000002,
    ScrollMode_Z                                = 0x00000004,
};

enum VHMode {
    VHMode_None                                 = 0x00000000,
    VHMode_X                                    = 0x00000001,
    VHMode_Y                                    = 0x00000002,
    VHMode_XY                                   = 0x00000003,
};

enum ConvertorType {
    ConvertorType_None                          = 0x00000000,
    ConvertorType_Bool2Int                      = 0x00000001,
};

enum DependentProperty {
    DependentProperty_Void                      = 0x00000000,
    DependentProperty_Int                       = 0x00000001,
    DependentProperty_Bool                      = 0x00000002,
    DependentProperty_Color                     = 0x00000003,
    DependentProperty_String                    = 0x00000004,
};

// bit7:rootlayer, bit6:bufferedlayer
enum LayerType {
    LayerType_DefaultLayer                      = 0x00000000,
	LayerType_Spirit                            = 0x00010000,
    LayerType_LayoutPanel                       = 0x00010001,
    LayerType_ScrollPanel                       = 0x00010042,
    LayerType_VirtualPanel                      = 0x00010003,
	LayerType_Vector                            = 0x00010004,
	LayerType_Text								= 0x00011000,
	LayerType_ComplexLayer						= 0x00001000,
    LayerType_BufferedLayer                     = 0x00010040,
    LayerType_WindowLayer                       = 0x000100C0,
    LayerType_FilterLayer                       = 0x000100C1,
    LayerType_PresentationLayer                 = 0x000100C2,
    LayerType_CustomWindow                      = 0x000100C3,
    LayerType_CursorLayer                       = 0x000100C4,
	LayerType_Renderable						= 0x00010000
};

enum EventStyle {
    EventStyle_Ignore							= 0x00000000,
	EventStyle_Receive				     		= 0x00000001,
    EventStyle_Peek								= 0x00000010,
};

enum InsertFlag {
    InsertFlag_Isolate                           = 0x00000000,
	InsertFlag_Default                           = 0x00000001,
    InsertFlag_Child							= 0x00000002,
    InsertFlag_SiblingBefore                      = 0x00000003,
    InsertFlag_SiblingAfter						= 0x00000004,
};

enum FilterType {
    FilterType_None                             = 0x00000000,
    FilterType_Wave                             = 0x00000001,
    FilterType_Blur                             = 0x00000002,
};

enum ResourceType {
    ResourceType_Bitmap                         = 0x00040001,
};

enum AnimationType {
    AnimationType_Defualt                       = 0x00000000,
    AnimationType_LayerAnimation                = 0x00000001,
};

enum TouchEvent {
    TouchEvent_Down							= 0x00000001,
    TouchEvent_Move                         = 0x00000002,
    TouchEvent_Up							= 0x00000003,
};

enum KeyEvent {
    KeyEvent_Down									= 0x00000001,
    KeyEvent_Up										= 0x00000002,
    KeyEvent_Held									= 0x00000003,
    KeyEvent_Released								= 0x00000004,
};

enum TransactionState {
    TransactionState_Free                       = 0x00000000,
    TransactionState_UnCommitted                = 0x08000000,
    TransactionState_UnProcessed                = 0x10000000,
    TransactionState_ForceReturn                = 0x40000000,
};

enum LayerEventConfig {
    LayerEventConfig_None                       = 0x0000,
    LayerEventConfig_Penetrable                 = 0x0001,
    LayerEventConfig_Peek                       = 0x0002,
    LayerEventConfig_Grab                       = 0x0003,
    LayerEventConfig_Ignore                     = 0x0004,

};

enum TransitionType {
    TransitionType_None                         = 0x00000000,
    TransitionType_Fly                          = 0x00000001,
    TransitionType_Push                         = 0x00000002,
    TransitionType_Fade                         = 0x00000004,
    TransitionType_Zoom                         = 0x00000008,
    TransitionType_Custom                       = 0xFFFFFFFF,
};

enum ModelFormat {
    ModelFormat_None							= 0x00000000,
    ModelFormat_MQO								= 0x00000001,
    ModelFormat_OBJ								= 0x00000002,
	ModelFormat_MESH								= 0x00000004,
	ModelFormat_OFG								= 0x00000008,

};

enum EPickerType
{
	NORMALPICKER,
};
enum EPickMSGType
{
	EPickMSG_Picked,
	EPickMSG_Drag,
	EPickMSG_UnPick
};
enum EBoundType
{
	BoundType_AABBox = 1,
};


enum XRBufferFormat {
	XR_R32								= 0x00000008,
	XR_G32								= 0x00000080,
	XR_B32								= 0x00000800,
	XR_A32								= 0x00008000,

	XR_R16								= 0x00000004,
	XR_G16								= 0x00000040,
	XR_B16								= 0x00000400,
	XR_A16								= 0x00004000,

	XR_R8								= 0x00000002,
	XR_G8								= 0x00000020,
	XR_B8								= 0x00000200,
	XR_A8								= 0x00002000,

	XR_NONE								= 0x00000000,
    XR_R32G32B32A32F					= 0x00028888,
	XR_R32G32B32F						= 0x00020888,
	XR_R32G32F							= 0x00020088,
	XR_R32F								= 0x00020008,

	XR_INT								= 0x00010000,
	XR_FLOAT							= 0x00020000,
    XR_R32G32B32A32I					= 0x00018888,
	XR_R32G32B32I						= 0x00010888,
	XR_R32G32I							= 0x00010088,
	XR_R32I								= 0x00010008,

    XR_R16G16B16A16F					= 0x00024444,
	XR_R16G16B16F						= 0x00020444,
	XR_R16G16F							= 0x00020044,
	XR_R16F								= 0x00020004,

	XR_R8G8B8A8U						= 0x01012222,
    XR_R8G8B8A8							= 0x00012222,
	XR_R8G8B8							= 0x00010222,
	XR_R8G8								= 0x00010022,
	XR_R8G8B8_SRGB					    = 0x00030222,
	XR_R8G8B8A8_SRGB					= 0x00032222,

	XR_D24								= 0x00200000,
	XR_D24I								= 0x00210000,
	XR_D24S8							= 0x01200000,
	XR_SRGB								= 0x00030000,
	XR_YUV                              = 0x10000000,
};

enum XRRenderState {
	XR_NULL								= 0x00000000,
	XR_CULLMODE_MODE					= 0x00000F00,
    XR_CULLMODE_NONE					= 0x00000100,
	XR_CULLMODE_FRONT					= 0x00000200,
	XR_CULLMODE_BACK					= 0x00000300,

	XR_FRONTFACE						= 0x000000F0,
	XR_FRONTFACE_CW						= 0x00000010,
	XR_FRONTFACE_CCW					= 0x00000020,

	XR_DEPTHTEST_OP						= 0x0000000F,
	XR_DEPTHTEST_NEVER					= 0x00000001,
	XR_DEPTHTEST_LT						= 0x00000002,
	XR_DEPTHTEST_EQ						= 0x00000003,
	XR_DEPTHTEST_LE						= 0x00000004,
	XR_DEPTHTEST_GT						= 0x00000005,
	XR_DEPTHTEST_NE						= 0x00000006,
	XR_DEPTHTEST_GE						= 0x00000007,
	XR_DEPTHTEST_ALWAYS					= 0x00000008,

	XR_DEPTHTEST_ENABLE                 = 0x00001000,
	XR_DEPTHWRITE_ENABLE                = 0x00002000,

	XR_BLEND_BITS						= 0x000F0000,
	XR_BLEND_DISABLE                    = 0x00000000,
	XR_BLEND_DEFAULT					= 0x00010000,
	XR_BLEND_ADD						= 0x00020000,
	XR_BLEND_MULTIPLY					= 0x00030000,
};

enum XRSamplerMode {
	XR_SAMPLER_WRAP						= 0x00000001,
	XR_SAMPLER_MIRROR					= 0x00000002,
    XR_SAMPLER_CLAMP					= 0x00000003,
	XR_SAMPLER_BORDER					= 0x00000004,
	XR_ADDRESS_BIT						= 0x0000000F,
	XR_SAMPLER_LINEAR					= 0x00000010,
	XR_SAMPLER_NEAREST					= 0x00000020,
	XR_FILTER_BIT						= 0x000000F0,
};

enum XRSamplerType {
	XR_SAMPLER_COLOR						= 0x00010000,
	XR_SAMPLER_DEPTH						= 0x00020000,
	XR_SAMPLER_STENCIL						= 0x00040000,
	XR_SAMPLER_TYPE_BIT						= 0x000F0000,
};

enum XRBufferUsage {
	XR_BUFFER_STATIC					= 0x00000001,
	XR_BUFFER_DYNAMIC					= 0x00000002,
};

//P:Position N:Normal T:Texture B:BiNormal W:Weight I:Index
enum XRVertexLayout {
	XR_VERTEX_LAYOUT_NULL				= 0x00000000,
	XR_VERTEX_LAYOUT_P					= 0x00000001,
	XR_VERTEX_LAYOUT_N					= 0x00000002,
	XR_VERTEX_LAYOUT_T					= 0x00000004,
	XR_VERTEX_LAYOUT_B					= 0x00000008,
	XR_VERTEX_LAYOUT_W					= 0x00000010,
	XR_VERTEX_LAYOUT_I					= 0x00000020,
	XR_VERTEX_LAYOUT_A					= 0x00000040,	
	XR_VERTEX_LAYOUT_K					= 0x00000080,
	XR_VERTEX_LAYOUT_C                  = 0x00000100,
	XR_VERTEX_LAYOUT_D                  = 0x00000200,
	XR_VERTEX_LAYOUT_E                  = 0x00000400,
	XR_VERTEX_LAYOUT_F                  = 0x00000800,
	XR_VERTEX_LAYOUT_G                  = 0x00001000,
	XR_VERTEX_LAYOUT_H                  = 0x00002000,
	XR_VERTEX_LAYOUT_J                  = 0x00004000,
	XR_VERTEX_LAYOUT_L                  = 0x00008000,

	XR_VERTEX_LAYOUT_PT					= 0x00000005,
	XR_VERTEX_LAYOUT_PNT				= 0x00000007,
	XR_VERTEX_LAYOUT_PNBT				= 0x0000000F,
	XR_VERTEX_LAYOUT_PNTWI				= 0x00000037,
	XR_VERTEX_LAYOUT_PNBTWI				= 0x0000003F,
	XR_VERTEX_LAYOUT_PTAK  			= 0x000000C5,
	XR_VERTEX_LAYOUT_PTACDEFGHJL        = 0x0000FF45,
	
};

enum XRTextureType {
	XR_TEXTURE_TYPE_DIFFUSE				= 0x00000001,
	XR_TEXTURE_TYPE_DIFFUSE_SRGB        = 0x00001001,
	XR_TEXTURE_TYPE_NORMAL				= 0x00000002,
	XR_TEXTURE_TYPE_SPECULAR			= 0x00000003,
	XR_TEXTURE_TYPE_ROUGHNESS			= 0x00000004,
	XR_TEXTURE_TYPE_AMBIENT				= 0x00000005,
	XR_TEXTURE_TYPE_EMISSIVE			= 0x00000006,
	XR_TEXTURE_TYPE_TRANSPARENCY		= 0x00000006,
	XR_TEXTURE_TYPE_SRGB				= 0x00001000,
	XR_TEXTURE_TYPE_CUBE				= 0x00010000,
	XR_TEXTURE_TYPE_FP16				= 0x00100000,
	XR_TEXTURE_TYPE_RGBE				= 0x01000000,
};

#endif//__XRENUM_H__