IF(NOT DEFINED ENV{ALGOCOMM_ROOT_DIR})
	SET(algocomm_root_dir "algocomm")
ELSE()
	SET(algocomm_root_dir $ENV{ALGOCOMM_ROOT_DIR})
ENDIF()

find_path(algocomm_INCLUDE_DIR reuse.h
		PATHS ${algocomm_root_dir}/include)
		
message("set algocomm_root_dir as $ENV{ALGOCOMM_ROOT_DIR}")

find_library(algocomm_LIBRARY NAMES algocomm PATHS ${algocomm_root_dir}/lib)
find_path(algocomm_LIBRARY_DIR libalgocomm.so PATHS ${algocomm_root_dir}/lib)


IF(algocomm_INCLUDE_DIR AND algocomm_LIBRARY)
	SET(algocomm_FOUND TRUE)
	MESSAGE(STATUS "Found algocomm library, inc:${algocomm_INCLUDE_DIR} lib:${algocomm_LIBRARY_DIR}")
ELSE()
	IF(EXISTS ${algocomm_root_dir}/src)
		SET(algocomm_SOURCE_FOUND TRUE)
		STRING( REGEX REPLACE ".*/(.*)" "\\1" algocomm_SOURCE_DIR ${algocomm_root_dir} )
		MESSAGE(STATUS "Precompiled algomm library not found, use source instead.")
	ELSE()
		MESSAGE(FATAL_ERROR "Any precompiled algocomm library or source not found.")

	ENDIF()
ENDIF()

