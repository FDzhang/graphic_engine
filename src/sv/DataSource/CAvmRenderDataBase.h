/*===========================================================================*\
 * FILE: CAvmRenderDataBase.h
 *===========================================================================
 * Copyright 2003 O-Film Technologies, Inc., All Rights Reserved.
 * O-Film Confidential
 *
 * DESCRIPTION:
 *
 * ABBREVIATIONS:
 *   TODO: List of abbreviations used, or reference(s) to external document(s)
 *
 * TRACEABILITY INFO:
 *   Design Document(s):
 *     TODO: Update list of design document(s)
 *
 *   Requirements Document(s):
 *     TODO: Update list of requirements document(s)
 *
 *   Applicable Standards (in order of precedence: highest first):
 *
 * DEVIATIONS FROM STANDARDS:
 *   TODO: List of deviations from standards in this file, or
 *   None.
 *
\*===========================================================================*/

#ifndef _CAVM_DATABASE_H_
#define _CAVM_DATABASE_H_

//#include <mutex>
#include "../../XrCore/XrSrc/External/XrHeaders.h"
#include "../SVNode2DStich.h"
#include "../DataStruct.h"
#include "../GlSV2D.h"
#include "GPU_Module_Interface.h"
#include "gpu_log.h"
#define PropertyBuilderByName(type, name, access_permission) \
    access_permission:\
        type* m_##name;\
        unsigned char m_##name##InitFlag;\
    public:\
        inline void Set##name(type* data){\
			static unsigned char initFlag = 0;\
			if(initFlag == 0)\
			{\
				m_##name = new type;\
				initFlag = 1;\
				m_##name##InitFlag = 1;\
			}\
			if(data == NULL)\
			{\
				return;\
			}\
			memcpy(m_##name, data, sizeof(type));\
        }\
        inline void Get##name(type* data){\
			if(data == NULL)\
			{\
				data = new type;\
			}\
			if(m_##name##InitFlag == 1)\
			{\
				memcpy(data, m_##name, sizeof(type));\
			}\
        }\
		inline void Get##name(type** data){\
			if(*data == NULL)\
			{\
				*data = new type;\
			}\
			if(m_##name##InitFlag == 1)\
			{\
				memcpy(*data, m_##name, sizeof(type));\
			}\
        }

#define PropertyBuilderExt1ByName(type, name, access_permission) \
    access_permission:\
        type* m_##name;\
    public:\
        inline void Set##name(type* data){\
			m_##name = data;\
        }\
        inline void Get##name(type* data){\
			data = m_##name;\
        }\
		inline void Get##name(type** data){\
			*data = m_##name;\
        }

#define PropertyBuilderExt2ByName(type1, type2, name, access_permission)\
    access_permission:\
        type1* m_##name##Param1;\
        type2* m_##name##Param1;\
        unsigned char m_##name##InitFlag;\
    public:\
        inline void Set##name(type1* data1, type2* data2){\
			static unsigned char initFlag = 0;\
			if(initFlag == 0)\
			{\
				m_##name##Param1 = new type1;\\
				m_##name##Param2 = new type2;\
				initFlag = 1;\
				m_##name##InitFlag = 1;\
			}\
			if(data1 == NULL)\
			{\
				return;\
			}\
			memcpy(m_##name##Param1, data1, sizeof(type1));\
			if(data2 == NULL)\
			{\
				return;\
			}\
			memcpy(m_##name##Param2, data2, sizeof(type2));\
        }\
        inline void Get##name(type1* data1, type2* data2){\
			if(data1 == NULL)\
			{\
				data1 = new type1;\
			}\
			if(data2 == NULL)\
			{\
				data2 = new type2;\
			}\
			if(m_##name##InitFlag == 1)\
			{\
				memcpy(data1, m_##name##Param1, sizeof(type1));\
				memcpy(data2, m_##name##Param2, sizeof(type2));\
			}\
        }

#define PropertyBuilderExt3ByName(type, name, access_permission) \
    access_permission:\
        type m_##name;\
    public:\
        inline void Set##name(type data){\
			m_##name = data;\
        }\
        inline void Get##name(type& data){\
			data = m_##name;\
        }

typedef struct TouchDataTag
{
	int x;
	int y;
	unsigned char touchAction;
}
TouchDataT;



class CAvmRenderDataBase
{
public:
	//CAvmRenderDataBase();
	//~CAvmRenderDataBase();

	static CAvmRenderDataBase* GetInstance();

    PropertyBuilderExt3ByName(unsigned char, VehicleTypeId, private)
	PropertyBuilderExt3ByName(unsigned char, DisplayViewCmd, private)
	PropertyBuilderExt3ByName(unsigned char, GuideLineCmd, private)
	PropertyBuilderExt3ByName(unsigned int, TimeStamp, private)
	PropertyBuilderByName(unsigned char, CanData, private)
	PropertyBuilderByName(TouchDataT, TouchData, private)

	PropertyBuilderExt3ByName(unsigned char, MouseIconVisibility, private)
	 
	PropertyBuilderByName(Region, 3dViewRegion, private)
	PropertyBuilderByName(Region, StitchViewRegion, private)	
	PropertyBuilderByName(Region, SingleViewRegion, private)
	PropertyBuilderByName(Region, ObjectViewRegion, private)
	PropertyBuilderByName(Region, LinearViewRegion, private)
	
	PropertyBuilderByName(SurroundViewCameraParamsT, ObjectViewCameraParams, private)
	PropertyBuilderByName(SurroundViewCameraParamsT, StitchViewCameraParams, private)
	PropertyBuilderByName(SurroundViewCameraParamsT, SingleViewCameraParams, private)
	PropertyBuilderByName(SurroundViewCameraParamsT, 3dViewCameraParams, private)	
	PropertyBuilderByName(SurroundViewCameraParamsT, LinearViewCameraParams, private)


	PropertyBuilderByName(unsigned char, SingleViewChannel, private)	
	PropertyBuilderExt3ByName(unsigned char, 3dViewIndex, private)

	PropertyBuilderExt1ByName(ISceneNode, SingleViewNode, private)
	PropertyBuilderExt1ByName(ISceneNode, StitchViewNode, private)
	PropertyBuilderExt1ByName(ISceneNode, 3dViewNode, private)
	PropertyBuilderExt1ByName(ISceneNode, ObjectViewNode, private)
	PropertyBuilderExt1ByName(SVNode2DStich, TimeStitcherNode, private)

	PropertyBuilderByName(APAOverlayStruct, ApaOverlayResult, private)

	PropertyBuilderExt1ByName(IAnimationManager, AnimationManager, private)

	PropertyBuilderExt1ByName(GlSV2D, Sv2dData, private)

	PropertyBuilderByName(unsigned char, StitchViewNodeStatus, private)
	PropertyBuilderByName(unsigned char, 3dViewNodeStatus, private)
	PropertyBuilderByName(unsigned char, SingleViewNodeStatus, private)
	PropertyBuilderByName(unsigned char, ObjectViewNodeStatus, private)
	PropertyBuilderByName(unsigned char, CarTransparentStatus, private)

	PropertyBuilderByName(LkaLcResultT, LkaLcResult, private)
	PropertyBuilderByName(MainMenuDataT, MainMenuStatus, private)
	PropertyBuilderByName(DVR_GUI_LAYOUT_INST_EXT, DvrData, private)
	PropertyBuilderByName(EolResultT, EolResult, private)
	PropertyBuilderByName(Tp_Result, TpResult, private)
	PropertyBuilderByName(PLDRadarResult, SonarResult, private)
	PropertyBuilderByName(Sea_Result_T, SeaResult, private)
	PropertyBuilderByName(PdResultT, PdResult, private)
	PropertyBuilderByName(Mod_Result_T, ModResult, private)
	PropertyBuilderByName(APAOverlayStruct, ApaResult, private)
	PropertyBuilderByName(VehInfoT, VehInfo, private)
	PropertyBuilderByName(CarTransparentResultT, CarTransptResult, private)
	PropertyBuilderByName(_3DFreeViewParamT, 3dFreeView, private)

	void SetSingleViewMesh(class IMesh* pSingleViewMesh[]);
	void GetSingleViewMesh(class IMesh* pSingleViewMesh[]);

	void SetSingleViewVertex(float* pSingleViewVertex[]);
	void GetSingleViewVertex(float* pSingleViewVertex[]);

	void SetSingleViewPlaneNode(class INode* pSingleViewPlaneNode[]);
	void GetSingleViewPlaneNode(class INode* pSingleViewPlaneNode[]);


	void Set3dViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void Get3dViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetStitchViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetStitchViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetObjectViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetObjectViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void Set180DegreeViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void Get180DegreeViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetLeftRightViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetLeftRightViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);
	void SetSideBySideSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char pFlag);
	void GetSideBySideSingleViewVisibility(VisibilityIndexT pFuncId, unsigned char& pFlag);


	void GetLeftRightViewRegion(Region** pLeftRightViewReg, unsigned char viewIndex);
	void SetLeftRightViewRegion(Region* pLeftRightViewReg, unsigned char viewIndex);
	void GetSideBySideSingleViewRegion(Region** pLeftRightViewReg, unsigned char viewIndex);
	void SetSideBySideSingleViewRegion(Region* pLeftRightViewReg, unsigned char viewIndex);
	void SetSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex);
	void GetSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex);
	void SetLargeSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex);
	void GetLargeSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex);

	void SetSideBySideSingleViewRoi(float* pSingleViewRoi, unsigned char pViewIndex);
	void GetSideBySideSingleViewRoi(float** pSingleViewRoi, unsigned char pViewIndex);

	
private:
	static CAvmRenderDataBase* m_Instance;

	unsigned char m_avm3dVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmSingleViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmStitchViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmObjViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avm180DegreeViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmLeftRightViewVisibility[PROCESS_FUNC_NUMS];
	unsigned char m_avmSideBySideSingleViewVisibility[PROCESS_FUNC_NUMS];

	class IMesh*	  m_singleViewMesh[4];
	class INode*	  m_singleViewPlaneNode[4];
	float*			  m_singleViewVertex[4];
	float*			  m_singleViewRoi[4];
	float*			  m_largeSingleViewRoi[4];
	float*			  m_sideBySideSingleViewRoi[4];

	Region 			  m_leftViewRegion;
	Region 			  m_rightViewRegion;

	Region 			  m_leftSingleViewRegion;
	Region 			  m_rightSingleViewRegion;

	

};


#endif // _CAVM_DATABASE_H_

/*===========================================================================*\
 * File Revision History (top to bottom: first revision to last revision)
 *===========================================================================
 *
 *   Date        userid       Description
 * ----------- ----------    -----------
 *  1/4/18   Jensen Wang   Create the CAvmRenderDataBase class.
\*===========================================================================*/
