#ifndef __XRINTRINSIC_H__
#define __XRINTRINSIC_H__

#include "xrUtility.h"
//#define Mat4ToXRMat4(mat)  (*((XRMat4*)( &(mat) )))

struct Bitmap {
	Bitmap(UInt8* data, Int32 w, Int32 h, Int32 p, UInt32 info) 
	{
		pData = data;
		width = w;
		height = h;
		pitch = p;
		typeInfo = info;
	}
	Bitmap() {}
	UInt8* 	pData;
	Int32		width;
	Int32		height;
	Int32		pitch;
	UInt32	typeInfo;
	Int32		id;
	Boolean IsValid()
	{
		if (pData) return true;
		else return false;
	}
};

struct XrBuffer {
	XrBuffer(UInt8* pD, Int32 w, Int32 h, UInt32 fmt) 
	{
		pData = pD;
		width = w;
		height = h;
		format = fmt;
	}
	XrBuffer() {};
	UInt8* 		pData;
	Int32		width;
	Int32		height;
	UInt32		format;
};

struct Region {
	Region() { bottom = top = left = right = 0; }
	Region(Float32 l, Float32 r, Float32 t, Float32 b)
	{
		Set(l, r, t, b);
	}
	Void Set(Float32 l, Float32 r, Float32 t, Float32 b)
	{
		left = l; right = r; top = t; bottom = b;
	}
	Void operator=(Region& src)
	{
		left = src.left;
		right = src.right;
		top = src.top;
		bottom = src.bottom;
	}
	Boolean IsIn(Float32 x, Float32 y)
	{
		return (x >= left && x < right
        && y >= top && y < bottom);
	}
	Boolean IsEmpty() 
	{
		if (right<=left || bottom<=top) return TRUE;
		else return FALSE;
	}
	Float32		left;
	Float32		right;
	Float32		top;
	Float32		bottom;
};

struct Rect {
	Rect() { x = y = width = height = 0; }
	Rect(Float32 _x, Float32 _y, Float32 _width, Float32 _height)
	{
		Set(_x, _y, _width, _height);
	}
	Void Set(Float32 _x, Float32 _y, Float32 _width, Float32 _height)
	{
		x = _x; y = _y; width = _width; height = _height;
	}
	Void operator=(Rect& src)
	{
		x = src.x;
		y = src.y;
		width = src.width;
		height = src.height;
	}
	Void operator=(Region& src)
	{
		x = src.left;
		y = src.top;
		width = src.right - src.left;
		height = src.bottom - src.top;
	}
	Boolean IsIn(Rect& rect)
	{
		if (x>=rect.x && y>=rect.y && width<=rect.width && height<=rect.height) return TRUE;
		else return FALSE;
	}

	Void Clip(Rect& clip)
	{
		Float32 _x = x; 
		Float32 _y = y;

		if (x < clip.x) {
			width = width - (clip.x - x);
			x = clip.x;
		}
		if (y < clip.y) {
			height = height - (clip.y - y);
			y = clip.y;
		}
		
		if (width+x > clip.width+clip.x) {
			width = clip.x+clip.width - x;
		}
		if (height+y > clip.height+clip.y) {
			height = clip.y+clip.height - y;
		}

	}

	Boolean IsEmpty() 
	{
		if (width<=0 || height<=0) return TRUE;
		else return FALSE;
	}
	Float32		x;
	Float32		y;
	Float32		width;
	Float32		height;
};

struct Cuboid {
	Cuboid() { x = y = z = depth = width = height = 0; }
	Cuboid(Float32 _x, Float32 _y, Float32 _z, Float32 _width, Float32 _height, Float32 _depth)
	{
		Set(_x, _y, _z, _width, _height, _depth);
	}
	Void Set(Float32 _x, Float32 _y, Float32 _z, Float32 _width, Float32 _height, Float32 _depth)
	{
		x = _x; y = _y; z = _z; width = _width; height = _height; depth =_depth;
	}
	Void operator=(Cuboid& src)
	{
		x = src.x;
		y = src.y;
		z = src.z;
		width = src.width;
		height = src.height;
		depth = src.depth;
	}
	Float32		x;
	Float32		y;
	Float32		z;
	Float32		width;
	Float32		height;
	Float32		depth;
};

struct Volume {
	Volume() { bottom = top = left = right = front = back = 0; }
	Volume(Float32 l, Float32 r, Float32 f, Float32 t, Float32 b, Float32 bk)
	{
		Set(l, r, f, t, b, bk);
	}
	Void Set(Float32 l, Float32 r, Float32 f, Float32 t, Float32 b, Float32 bk)
	{
		left = l; right = r; front = f; top = t; bottom = b; back = bk;
	}

	Void operator=(Volume& src)
	{
		left = src.left;
		right = src.right;
		front = src.front;
		top = src.top;
		bottom = src.bottom;
		back = src.back;
	}
	Boolean IsIn(Float32 x, Float32 y, Float32 z)
	{
		return (x >= left && x < right
			 && y >= top && y < bottom
			 && z >= back && z < front);
	}

	Float32		left;
	Float32		right;
	Float32     front;
	Float32		top;
	Float32		bottom;
	Float32		back;
};


struct TouchPackage {
	Float32			x;
	Float32			y;
	TouchEvent		touchEvent;
};

struct KeyPackage {
	UInt32			code;
	KeyEvent		keyEvent;
};


//struct ShaderObject {
//	Int32	FrgId, VtxId;		/* Used to hold the fragment and vertex shader handles */
//	Int32	ProgramId;					/* Used to hold the program handle (made out of the two previous shaders */
//	Int32	UniformLoc[29];
//};


struct TransformInfo {
	TransformInfo()
	{
		Reset();
	}

	Void Reset()
	{
		tx =  ty = tz = rx = ry = rz = 0;
		sx = sy = sz = 1.0;
		enable = 0;
	}

	Void DeltaTranslation(Float32 _tx, Float32 _ty, Float32 _tz) { tx+=_tx; ty+=_ty; tz+=_tz; }
	Void DeltaRotation(Float32 _rx, Float32 _ry, Float32 _rz) { rx+=_rx; ry+=_ry; rz+=_rz; }
	Void DeltaScale(Float32 _sx, Float32 _sy, Float32 _sz) { sx*=_sx; sy*=_sy; sz*=_sz; }

	Void SetTranslation(Float32 _tx, Float32 _ty, Float32 _tz) { tx=_tx; ty=_ty; tz=_tz; }
	Void SetRotation(Float32 _rx, Float32 _ry, Float32 _rz) { rx=_rx; ry=_ry; rz=_rz; }
	Void SetScale(Float32 _sx, Float32 _sy, Float32 _sz) { sx=_sx; sy=_sy; sz=_sz; }

    Float32       tx;
    Float32       ty;
	Float32       tz;
    Float32       rx;
    Float32       ry;
	Float32       rz;
	Float32       sx;
	Float32       sy;
	Float32       sz;
	Int32		  enable;
};

struct RenderPass {
	Void Default()
	{
		drawMode[0] = DrawMode_Triangles;
		drawMode[1] = DrawMode_Triangles;
		drawModeOverride = 0;
		num = 1;
	}

#define MAX_PASS 2
	UInt32 				drawMode[MAX_PASS];
	UInt32				drawModeOverride;
	UInt32				num;
};


//struct MaterialDesc
//{
//	UInt32 matrialId;
//	UInt32 matrialMeshStartIndex;//
//	UInt32 matrialMeshEndIndex;  // -1 means whole mesh
//};

struct XRMHeader
{
	UInt32 magicNumber;
	UInt32 versionInfo;//
	UInt32 meshBlockStartOffset;  // -1 means whole mesh
	UInt32 materialBlockStartOffset;  // -1 means whole mesh
	UInt32 boneBlockStartOffset;  // -1 means whole mesh
	UInt32 animationBlockStartOffset;  // -1 means whole mesh
};


enum XRMSignature{
	Header_Sig           = 0xFF00FF00,
	Scene_Block_Sig      = 0xFF00FF01,
	Mesh_Block_Sig       = 0xFF00FF02,
	Material_Block_Sig   = 0xFF00FF03,
	BoneSet_Block_Sig    = 0xFF00FF04,
	Mesh_Sig			 = 0xFF00FF05,
	Material_Sig		= 0xFF00FF06,
	BoneSet_Sig			= 0xFF00FF07,
	Bone_Sig			= 0xFF00FF08,
	Animation_Block_Sig   = 0xFF00FF09,
	Animation_Layer_Sig = 0xFF00FF0A,
	Animation_Node_Sig = 0xFF00FF0B,
  Animation_Curve_Sig = 0xFF00FF0C,
};

struct XRBoneElement
{
	Float32 translation[16];
	Float32 rotation[16];
	Float32 scale[16];
};

struct MeshBlock
{
	CHAR name[128];
	Int32 meshBoneIndex;
	UInt32 vaType;
	Int32 controlPointCount;
	Float32* controlPointData;
	Int32 vertexAttributeCount;
	Float32* vertexAttributeData;
	Int32 indexCount;
	Int32* indexData;
};

struct MaterialBlock
{
	Void SetNull()
	{
		name[0] = 0;
		for (Int32 i=0;i<3;i++) {
			ambient[i]=0;
			diffuse[i]=0;
			specular[i]=0;
			emissive[i]=0;
		}
		transparency = 0;
		shininess = 0;

		diffuseTex[0] = 0;
		normalTex[0] = 0;
		specularTex[0] = 0;
		roughnessTex[0] = 0;
		ambientTex[0] = 0;
		emissiveTex[0] = 0;
		type = Material_Null;
	}

	CHAR name[MAX_NAME];
	Float32 ambient[3];
	Float32 diffuse[3];
	Float32 specular[3];
	Float32 emissive[3];
	Float32 transparency;
	Float32 shininess;
	MaterialType type;
    CHAR diffuseTex[MAX_PATH];
	CHAR normalTex[MAX_PATH];
	CHAR specularTex[MAX_PATH];
	CHAR roughnessTex[MAX_PATH];
	CHAR ambientTex[MAX_PATH];
	CHAR emissiveTex[MAX_PATH];
};

struct Bone{
	CHAR name[MAX_NAME];
	Int32 linkedVertexCount;
	Float32 meshTrans[16];
	Float32 bindPos[16];
	Int32* index;
	Float32* weight;
};

struct BoneSet{
	Int32 meshIndex;
	Int32 boneCount;
	Bone* bone;
};

enum VertexAttribute {
	VA_Normal	= 0x00000001,
	VA_Color	= 0x00000010,
	VA_UV		= 0x00000100,
};

inline Int32 GetVASize(Int32 va) {
	Int32 size = 0;
	if (va & VA_Normal) size+=3*4;
	if (va & VA_UV) size+=2*4;
	if (va & VA_Color) size+=4*4;
	return size;
}

#define MAX_ANIMATION_LAYER_NUM 32
#define MAX_ANIMATION_NODE_NUM 1024

struct CAnimationFrame
{
	float time;
	float value;
};

struct CAnimationCurve
{
	CAnimationCurve() {
		frames = 0;
		frameNum = 0;
		type = 0;
		currentFrame = 0;
	}
	CAnimationFrame* frames;
	unsigned int frameNum;
	unsigned int type;
	unsigned int currentFrame;
};

struct CAnimationNode
{
	CAnimationNode() {
		pTarget = 0;
		propertys = 0;
	}
	//CAnimationNode(CAnimationNode* pNode) {
	//	for (int i=0;i<9;i++) {
	//		curves[i].frameNum = pNode->curves[i].frameNum;
	//		curves[i].frames = pNode->curves[i].frameNum;
	//		curves[i].frameNum = pNode->curves[i].frameNum;
	//	}
	//	//curveNum = pNode->curveNum;
	//	propertys = pNode->propertys;
	//}
	CAnimationCurve curves[9];
	class CNode* pTarget;
	unsigned int propertys;//APType
};

struct CAnimationLayer
{
	CAnimationLayer() {
		duration = 0.0;
		nodeNum = 0;
	}
	CAnimationNode nodes[MAX_ANIMATION_NODE_NUM];
	unsigned int nodeNum;
	float duration;
};

/*
XRM file format

-------header block---------
32bit '.XRM'  head
32bit versionInfo
32bit MeshBlockStartOffset
32bit MaterialBlockStartOffset
32bit BoneSetBlockStartOffset

-------Nodes Block---------
Scene_Block_Sig
----RootNode------
{
NodeNameStringLen
NodeNameString
localTranslate
localRotation
localScale
AnimationNodeIndex
meshCunt
MeshIndex
MaterialIndex
MeshIndex
MaterialIndex
..
..
IsBone
{
----Node2----
}
{
---Node3-----
}
{
---NodeN-----
}
}

------MeshesBlock--------
Mesh_Block_Sig
NumofMeshes
-------Mesh0------
Mesh_Sig
MeshNameLen
MeshName
VertexAttribute type
ControlPointCount
DATA..
VertexAttributesCount
DATA..
IndexCount(polygonCount*3)   32bit cp,32bit va
DATA..
....
..
-------------------
Mesh1...
.....
MeshN...  
--------------------------

------MaterialBlock--------
Material_Block_Sig
NumofMaterials
-------Material0------
MATERIAL_SIG
MaterialNameLen
MaterialName
FLOAT3 Ambient Color
FLOAT3 Diffuse Color
FLOAT3 Specular Color
FLOAT3 Emissive Color
FLOAT Transparenct
FLOAT Shininess

DiffuseTexStringLen
DiffuseTexString
NormalTexStringLen
NormalTexString
SpecularTexStringLen
SpecularTexString
RoughnessTexStringLen
RoughnessTexString
AmbientTexStringLen
AmbientTexString
EmissiveTexStringLen
EmissiveTexString

-------------------
Material1...
...
MaterialN...  

---------------------------


------BoneSetsBlock--------
BoneSet_Block_Sig
NumofBoneSets
-------BoneSet0------
BoneSet_Sig
BoneCount
Bone_Sig
BoneNameLen
BoneName
Float32 tran[16]
Float32 bind[16]
LinkedIndexCount
VertexIndex,Weight
VertexIndex,Weight
....
VertexIndex,Weight
Bone_Sig
BoneNameLen
BoneName
LinkedIndexCount
...
...
-------------------
BoneSet1...
.....
BoneSetN...  
--------------------------

------AnimationBlock--------
Animation_Block_Sig
NumofAnimationLayers
------AnimationLayer0------
Animation_Layer_Sig
NodesCount
	Animation_Node_Sig
	nodeIndex
	CurvesCount
		Animation_Curve_Sig
		AnimationType
		FrameCount
		Time
		Value
		...
		Time
		Value
		Animation_Curve_Sig
		AnimationType
		FrameCount
		Time
		Value
		...
		Time
		Value
		..
-------------------
AnimationLayer1...
.....
AnimationLayerN...  
--------------------------

*/
#endif  //__XRINTRINSIC_H__