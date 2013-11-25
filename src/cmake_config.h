// Filled in by the build system

#ifndef CMAKE_CONFIG_H
#define CMAKE_CONFIG_H

#define CMAKE_PROJECT_NAME "minetest"
#define CMAKE_VERSION_STRING "0.4.8-dev"
#define CMAKE_RUN_IN_PLACE 0
#define CMAKE_USE_GETTEXT 0
#define CMAKE_USE_CURL 1
#define CMAKE_USE_SOUND 1
#define CMAKE_USE_FREETYPE 0
#define CMAKE_STATIC_SHAREDIR "/usr/local/share/minetest"
#define CMAKE_USE_LEVELDB 0

#ifdef NDEBUG
	#define CMAKE_BUILD_TYPE "Release"
#else
	#define CMAKE_BUILD_TYPE "Debug"
#endif
#define CMAKE_BUILD_INFO "BUILD_TYPE="CMAKE_BUILD_TYPE" RUN_IN_PLACE=0 USE_GETTEXT=0 USE_SOUND=1 USE_CURL=1 USE_FREETYPE=0 USE_LUAJIT=0 STATIC_SHAREDIR=/usr/local/share/minetest"

#endif
