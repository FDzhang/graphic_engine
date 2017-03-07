IF(NOT framework_FOUND)
	IF(NOT DEFINED ENV{FRAMEWORK_ROOT_DIR})
		SET(framework_root_dir "a15_framework")
	ELSE()
		SET(framework_root_dir $ENV{FRAMEWORK_ROOT_DIR})
	ENDIF()

	find_path(framework_INCLUDE_DIR init.h
			PATHS ${framework_root_dir}/include)
		
	message("set framework_root_dir as ${framework_root_dir}")

	find_library(framework_LIBRARY NAMES framework PATHS ${framework_root_dir}/lib)
	find_path(framework_LIBRARY_DIR libframework.so PATHS ${framework_root_dir}/lib)

	IF(framework_INCLUDE_DIR AND framework_LIBRARY)
		SET(framework_FOUND TRUE)
		MESSAGE(STATUS "Found framework library, inc:${framework_INCLUDE_DIR} lib:${framework_LIBRARY_DIR}")
	ELSE()
		STRING( REGEX REPLACE ".*/(.*)" "\\1" framework_SOURCE_DIR ${framework_root_dir} )
		IF(EXISTS ${PROJECT_SOURCE_DIR}/${framework_SOURCE_DIR}/src)
			SET(framework_FOUND TRUE)
			SET(framework_SOURCE_FOUND TRUE)
			MESSAGE(STATUS "Precompiled framework library not found, use source instead.")
		ELSE()
			MESSAGE(FATAL_ERROR "Any precompiled framework library or source not found.")
		ENDIF()
	ENDIF()
ENDIF()
