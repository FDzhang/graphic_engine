IF(NOT algocomm_FOUND AND NOT algocomm_SOURCE_FOUND)
	IF(NOT DEFINED ENV{ALGOCOMM_ROOT_DIR})
		SET(algocomm_root_dir "algo_common")
	ELSE()
		SET(algocomm_root_dir $ENV{ALGOCOMM_ROOT_DIR})
	ENDIF()

	MESSAGE(STATUS "set algocomm_root_dir as ${algocomm_root_dir}")

	#包含目录下的reuse.h是必存在的文件，以此为特征
	find_path(algocomm_INCLUDE_DIR reuse.h
			PATHS ${algocomm_root_dir}/include)


	#找到库目录和库文件，
	find_library(algocomm_LIBRARY NAMES algocomm PATHS ${algocomm_root_dir}/lib)
	find_path(algocomm_LIBRARY_DIR libalgocomm.so PATHS ${algocomm_root_dir}/lib)

	#库文件存在的话库目录必存在
	IF(algocomm_INCLUDE_DIR AND algocomm_LIBRARY)
		SET(algocomm_FOUND TRUE)
		MESSAGE(STATUS "Found algocomm library, inc:${algocomm_INCLUDE_DIR} lib:${algocomm_LIBRARY_DIR}")
	ELSE()
		STRING( REGEX REPLACE ".*/(.*)" "\\1" algocomm_SOURCE_DIR ${algocomm_root_dir} )
		#如果根目录下存在src目录，即带源码，可尝试源码编译
		IF(EXISTS ${PROJECT_SOURCE_DIR}/${algocomm_SOURCE_DIR}/src)
			SET(algocomm_SOURCE_FOUND TRUE)
			SET(algocomm_FOUND TRUE)
			MESSAGE(STATUS "Precompiled algomm library not found, use source instead.")
		ELSE()
			MESSAGE(FATAL_ERROR "Any precompiled algocomm library or source not found.")
		ENDIF()
	ENDIF()
ENDIF()

