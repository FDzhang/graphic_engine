IF(NOT graphic_engine_FOUND)
	IF(NOT DEFINED ENV{GPU_ROOT_DIR})
		SET(graphic_engine_root_dir "graphic_engine")
	ELSE()
		SET(graphic_engine_root_dir $ENV{GPU_ROOT_DIR})
	ENDIF()

	find_path(graphic_engine_INCLUDE_DIR GPU_Module_Interface.h
			PATHS ${graphic_engine_root_dir}/include)
		
	message("set graphic_engine_root_dir as ${graphic_engine_root_dir}")

	find_library(graphic_engine_LIBRARY NAMES graphic_engine PATHS ${graphic_engine_root_dir}/lib)
	find_path(graphic_engine_LIBRARY_DIR libgraphic_engine.so PATHS ${graphic_engine_root_dir}/lib)


	IF(graphic_engine_INCLUDE_DIR AND graphic_engine_LIBRARY)
		SET(graphic_engine_FOUND TRUE)
		MESSAGE(STATUS "Found graphic_engine library, inc:${graphic_engine_INCLUDE_DIR} lib:${graphic_engine_LIBRARY_DIR}")
	ELSE()
		STRING( REGEX REPLACE ".*/(.*)" "\\1" graphic_engine_SOURCE_DIR ${graphic_engine_root_dir} )
		IF(EXISTS ${PROJECT_SOURCE_DIR}/${graphic_engine_SOURCE_DIR}/src)
			SET(graphic_engine_FOUND TRUE)
			SET(graphic_engine_SOURCE_FOUND TRUE)
		
			MESSAGE(STATUS "Precompiled graphic_engine library not found, use source instead.")
		ELSE()
			MESSAGE(FATAL_ERROR "Any precompiled graphic_engine library or source not found.")
		ENDIF()
	ENDIF()
ENDIF()

