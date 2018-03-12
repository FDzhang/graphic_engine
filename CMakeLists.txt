CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake.modules)
FIND_PACKAGE(toolchain REQUIRED)

IF(NOT rootfs_FOUND)
	FIND_PACKAGE(rootfs)
ENDIF()

if(NOT algorithm_FOUND AND NOT algorithm_SOURCE_FOUND)
    find_package(algorithm)
endif()

IF(NOT algocomm_FOUND AND NOT algocomm_SOURCE_FOUND)
	FIND_PACKAGE(j6armcomm)
ENDIF()

IF(NOT rootfs_FOUND)
	MESSAGE(FATAL_ERROR "No rootfs found!")
ENDIF()

IF(NOT j6armcomm_FOUND AND NOT j6armcomm_SOURCE_FOUND)
	MESSAGE(FATAL_ERROR "No j6armcomm library found!")
ENDIF()


#设置包含目录
INCLUDE_DIRECTORIES(include)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

#添加子目录
ADD_SUBDIRECTORY(src)
