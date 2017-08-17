CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(gpu_project_name graphic_engine)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -Wl,-Bsymbolic")
SET(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Wl,-Bsymbolic")

file(GLOB_RECURSE gpu_c_src "*.c")
file(GLOB_RECURSE gpu_cpp_src "*.c??")
file(GLOB_RECURSE free_type_c_src "freetype/*.c")
list(REMOVE_ITEM gpu_c_src ${free_type_c_src})
list(APPEND gpu_c_src "${CMAKE_CURRENT_BINARY_DIR}/version.c")

execute_process(COMMAND "./version.sh"  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/version.c")

AUX_SOURCE_DIRECTORY(extra extra_srcs)
AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_BINARY_DIR} dynamic_gen_srcs)

execute_process(COMMAND "./version.sh"  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/version.c")

INCLUDE_DIRECTORIES(${J6_ROOTFS}/usr/include ${J6_ROOTFS}/usr/include/freetype2 
                    ${j6armcomm_INCLUDE_DIR} ${j6armcomm_INCLUDE_DIR}/avm .
                    ${algorithm_INCLUDE_DIR}/
                    ${algorithm_INCLUDE_DIR}/common
		    ${algorithm_INCLUDE_DIR}/../src/alg/apa/interface
                    )
LINK_DIRECTORIES(${J6_ROOTFS}/lib ${J6_ROOTFS}/usr/lib)

execute_process(COMMAND "${CMAKE_LINKER}" "-m${OUTPUT_LINK_MODE}" "-verbose" 
                    COMMAND "${CMAKE_SOURCE_DIR}/ldsfilter.sh" "GpuLogctrl" #OUTPUT_VARIABLE TT
                     OUTPUT_FILE ${CMAKE_BINARY_DIR}/graphic_engine.lds
                    )
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -T ${CMAKE_BINARY_DIR}/graphic_engine.lds")

ADD_LIBRARY(${gpu_project_name} SHARED ${gpu_c_src} ${gpu_cpp_src})
#设置输出路径
SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

set_target_properties(${gpu_project_name} PROPERTIES LINKER_LANGUAGE C)
