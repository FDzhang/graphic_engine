#ifndef __XR_CONFIG_H__
#define __XR_CONFIG_H__

//Precision
#define DefaultTransitionDuration 500
#define	DefaultSmoothDuration 50
#define UI_SPIRITOFFSET 0.0001f
#define Z_DEPTH_CLEAR_VAL  1.0
#define Z_OFFSET_FACTOR 0.65
#define Z_OFFSET_UNIT 0.65

//Resources
#define DefaultNumLayer				512
#define DefaultNumModel				512
#define DefaultMeshNum				512
#define DefaultMaterialNum			128
#define DefaultNumRenderNode		16
#define DefaultNumRenderTarget		16
#define DefaultNumFont				16
#define DefaultLightNum				16
#define DefaultCameraNum			8
#define MaxNumCPL				20


//ApManager
#define DefaultNumAnime				64
#define DefaultNumUpdate			64
#define DefaultNumAP				64
#define DefaultNumSkeletonAnim		8


#define DefaultEventNum				16
//xrCore
#define DefaultNumSessions			64

#define MaxStringLen			128
#define MaxNameLen				32
#define XrFontTexSize  256

//#define UIVertexBlock		4096
#define UIVertexBlock		5082

#define TexHashTableNum 1024
#define ShaderHashTableNum 256

#define DefaultNumMesh	1024
#define DefaultNumSkeleton 8
#define DefaultNumMaterail	521
#define DefaultNumVertexPrg	20
#define DefaultNumFragmentPrg	20


#define MaxBoneNumOneSkeleton 32
#define MaxBoneNumOneMesh  8	
#define MaxInfluenceBoneNum  4	

#define CAM_NEAR 2.0f
#define CAM_FAR 1000.0f

#define MaxNumStack             1024
#define MaxNumReusableLayerType 128
#define DefaultNumStack			64
//xrTansaction
//#define MaxNumTransaction   127

//xrException
//#define MaxNumException     16



#endif //__XR_CONFIG_H__
