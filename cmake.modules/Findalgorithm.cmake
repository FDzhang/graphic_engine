
IF(algorithm_FOUND)
	MESSAGE(STATUS "algorithm library found.")
ELSE()
	IF(NOT DEFINED ALGO_ROOT_DIR)
		IF(NOT DEFINED ENV{ALGO_ROOT_DIR})
			SET(algo_root_dir "algo")
		ELSE()
			SET(algo_root_dir $ENV{ALGO_ROOT_DIR})
		ENDIF()
	ELSE()
		SET(algo_root_dir ${ALGO_ROOT_DIR})
	ENDIF()
	MESSAGE(STATUS "algorithm set algo_root_dir to ${algo_root_dir}")
	
	#查看是否存在include目录
	find_path(algorithm_INCLUDE_DIR alg_embed.h
			PATHS ${algo_root_dir}/include)
	IF(NOT algorithm_INCLUDE_DIR)
		MESSAGE(FATAL_ERROR "${algo_root_dir} seems not a valid algorithm library directory")
	ENDIF()
	
	#查看是否存在lib库
	#find_library(algorithm_LIBRARY NAMES pld PATHS ${algo_root_dir}/lib)
	find_path(algorithm_LIBRARY_DIR libpld.so PATHS ${algo_root_dir}/lib)
	
	IF(algorithm_LIBRARY_DIR)
		SET(algorithm_FOUND TRUE)
        SET(algorithm_LIBRARY "bsd ldw lka pld pp oc stitcher")
		MESSAGE(STATUS "algorithm library found at ${algo_root_dir}")
	ELSEIF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${algo_root_dir}/src)
		#虽然没有库，但是有源代码，
		STRING( REGEX REPLACE ".*/(.*)" "\\1" algorithm_SOURCE_DIR ${algo_root_dir})
		SET(algorithm_SOURCE_FOUND TRUE)
		SET(algorithm_FOUND TRUE)
	ELSE()
		MESSAGE(FATAL_ERROR "No algorithm library or source found within directory ${algo_root_dir}")
	ENDIF()
ENDIF()