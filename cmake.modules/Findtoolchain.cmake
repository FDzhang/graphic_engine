
IF(NOT toolchain_FOUND)
	#如果没设置ARCH环境变量，默认为ARM编译
	IF(NOT DEFINED ARCH)
	    IF(NOT DEFINED ENV{ARCH})
		SET(ENV{ARCH} "arm")
	    ENDIF()
    
	    SET(arch $ENV{ARCH})
	ELSE()
	    SET(arch $ENV{ARCH})
	    SET(ENV{ARCH} ${arch})
	ENDIF()

	IF(${arch} MATCHES "arm")
	    MESSAGE("Compile for ARM")
	    if(NOT DEFINED ENV{TOOLCHAIN_DIR}) 
			SET(toolchain_dir "/opt/arm-toolchain/linux/gcc-linaro-arm-linux-gnueabihf-4.7-2013.03-20130313_linux")
	    ELSE()
			SET(toolchain_dir $ENV{TOOLCHAIN_DIR})
	    ENDIF()
	    SET(CMAKE_CXX_COMPILER ${toolchain_dir}/bin/arm-linux-gnueabihf-g++)
	    SET(CMAKE_C_COMPILER ${toolchain_dir}/bin/arm-linux-gnueabihf-gcc)
	ENDIF()

	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wno-psabi -O0 -Dlinux")
	SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-psabi -g -O0 -Dlinux")
	SET(toolchain_FOUND TRUE)
ENDIF()
