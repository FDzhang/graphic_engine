IF(NOT rootfs_FOUND)
	IF(NOT DEFINED $ENV{J6_ROOTFS})
		SET(J6_ROOTFS ${PROJECT_SOURCE_DIR}/rootfs)
	ELSE()
		SET(J6_ROOTFS $ENV{J6_ROOTFS})
	ENDIF()

	IF(EXISTS ${J6_ROOTFS}/usr/lib)
		SET(rootfs_FOUND TRUE)
	ELSE()
		MESSAGE(FATAL_ERROR "No rootfs directory found for j6, please SET J6_ROOTFS to a valid rootfs directory, \n\t or make sure there is a named rootfs exists in project directory for j6!")
	ENDIF()
ENDIF()
	