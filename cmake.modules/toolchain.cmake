
#如果没设置ARCH环境变量，默认为ARM编译
IF(NOT DEFINED ENV${ARCH})
    SET(arch "arm")
ELSE()
    SET(arch $ENV{ARCH})
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