
SET( UDEV_LIBRARY )
SET( UDEV_INCLUDE_DIR )

FIND_PATH( UDEV_INCLUDE_DIR libudev.h
	/usr/include
	/usr/local/include
)

FIND_LIBRARY( UDEV_LIBRARY NAMES udev
	PATHS
	/usr/lib
	/usr/local/lib
)

# check if udev is usable for us
INCLUDE (CheckSymbolExists)
SET(CMAKE_REQUIRED_LIBRARIES udev)
CHECK_SYMBOL_EXISTS(udev_enumerate_new libudev.h USABLE_UDEV)
SET(CMAKE_REQUIRED_LIBRARIES "")

FIND_PACKAGE_HANDLE_STANDARD_ARGS( Udev DEFAULT_MSG UDEV_LIBRARY UDEV_INCLUDE_DIR USABLE_UDEV)
MARK_AS_ADVANCED(  UDEV_LIBRARY UDEV_INCLUDE_DIR )
