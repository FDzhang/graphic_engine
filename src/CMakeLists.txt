CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(gpu_project_name graphic_engine)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

AUX_SOURCE_DIRECTORY(. gpu_srcs)

#添加sv子目录所有代码
AUX_SOURCE_DIRECTORY(sv/DataSource svdatasrc_srcs)
AUX_SOURCE_DIRECTORY(sv/HMI svhmi_srcs)
AUX_SOURCE_DIRECTORY(sv/HMISource svhmisrc_srcs)
AUX_SOURCE_DIRECTORY(sv/RenderDelegate svrender_srcs)
AUX_SOURCE_DIRECTORY(sv/VideoSource svvideosrc_srcs)
AUX_SOURCE_DIRECTORY(sv/RenderNode svrendernode_srcs)
AUX_SOURCE_DIRECTORY(sv sv_srcs)

AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrResource xrres_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/Render xrrender_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/Render/GLES2Shaders xrrshaders_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/Render/GLES2Render xrrshader_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/Platform xrplatform_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/Effect xreffect_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode xrnode_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode/Lighting xrlight_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode/Layer xrlayer_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode/Intersect xrinter_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode/Material xrmeterial_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode/Camera xrcamera_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode/Mesh xrmesh_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode/Animation xranimat_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrNode/Scene xrscene_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrCore xrcore_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/XrUILibrary xruilib_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/External xrext_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/3rd xr3rd_srcs)
AUX_SOURCE_DIRECTORY(XrCore/XrSrc/Common srccomm_srcs)


INCLUDE_DIRECTORIES(${J6_ROOTFS}/usr/include ${J6_ROOTFS}/usr/include/freetype2 ${algocomm_INCLUDE_DIR} ${algocomm_INCLUDE_DIR}/avm .)
LINK_DIRECTORIES(${J6_ROOTFS}/lib ${J6_ROOTFS}/usr/lib)

ADD_LIBRARY(${gpu_project_name} SHARED ${gpu_srcs} ${svdatasrc_srcs} ${svhmi_srcs} ${svhmisrc_srcs} ${svrender_srcs} ${svrendernode_srcs}
		${svvideosrc_srcs} ${sv_srcs} ${xrres_srcs} ${xrrender_srcs} ${xrrshaders_srcs} ${xrrshader_srcs}
		 ${xrplatform_srcs} ${xreffect_srcs} ${xrnode_srcs}  ${xrlight_srcs} ${xrlayer_srcs} ${xrinter_srcs} 
		 ${xrmeterial_srcs} ${xrcamera_srcs} ${xrmesh_srcs} ${xranimat_srcs} ${xrscene_srcs} ${xrcore_srcs} 
		 ${xruilib_srcs} ${xrext_srcs} ${xr3rd_srcs} ${srccomm_srcs})
#设置输出路径
SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")
