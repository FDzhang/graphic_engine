IF(NOT j6armcomm_FOUND AND NOT j6armcomm_SOURCE_FOUND)
	IF(NOT DEFINED ENV{J6ARMCOMM_ROOT_DIR})
		SET(j6armcomm_root_dir "j6_arm_common")
	ELSE()
		SET(j6armcomm_root_dir $ENV{J6ARMCOMM_ROOT_DIR})
	ENDIF()

	MESSAGE(STATUS "set j6armcomm_root_dir as ${j6armcomm_root_dir}")

	#包含目录下的reuse.h是必存在的文件，以此为特征
	find_path(j6armcomm_INCLUDE_DIR reuse.h
			PATHS ${j6armcomm_root_dir}/include)


	#找到库目录和库文件，
	find_library(j6armcomm_LIBRARY NAMES j6armcomm PATHS ${j6armcomm_root_dir}/lib)
	find_path(j6armcomm_LIBRARY_DIR libj6armcomm.so PATHS ${j6armcomm_root_dir}/lib)

	#库文件存在的话库目录必存在
	IF(j6armcomm_INCLUDE_DIR AND j6armcomm_LIBRARY)
		SET(j6armcomm_FOUND TRUE)
		MESSAGE(STATUS "Found j6armcomm library, inc:${j6armcomm_INCLUDE_DIR} lib:${j6armcomm_LIBRARY_DIR}")
	ELSE()
		STRING( REGEX REPLACE ".*/(.*)" "\\1" j6armcomm_SOURCE_DIR ${j6armcomm_root_dir} )
		#如果根目录下存在src目录，即带源码，可尝试源码编译
		IF(EXISTS ${PROJECT_SOURCE_DIR}/${j6armcomm_SOURCE_DIR}/src)
			SET(j6armcomm_SOURCE_FOUND TRUE)
			SET(j6armcomm_FOUND TRUE)
			MESSAGE(STATUS "Precompiled algomm library not found, use source instead.")
		ELSE()
			MESSAGE(FATAL_ERROR "Any precompiled j6armcomm library or source not found.")
		ENDIF()
	ENDIF()
ENDIF()

