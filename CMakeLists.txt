project (scp-machine)
site_name (www.ostis.net)
cmake_minimum_required (VERSION 2.6)

set(SC_MACHINE_ROOT "${CMAKE_SOURCE_DIR}/../sc-machine/")
set(SCP_MACHINE_ROOT "${CMAKE_SOURCE_DIR}")

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS_DEBUG "-DSCP_DEBUG")

add_definitions(-DSCP_MATH)
add_definitions(-DSCP_STRING)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SC_MACHINE_ROOT}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SC_MACHINE_ROOT}/bin)

link_directories(${SC_MACHINE_ROOT}/bin)

set(SC_MEMORY_SRC "${SC_MACHINE_ROOT}/sc-memory/")

add_subdirectory(scp_lib)
add_subdirectory(scp_interpreter)
add_subdirectory(test)

# find dependencies
if (${UNIX})
	include(FindPkgConfig)
	pkg_check_modules (GLIB2 REQUIRED glib-2.0)
	pkg_check_modules (GLIB2_MODULE REQUIRED gmodule-2.0)

        find_path(GLIB_INCLUDE_DIRS NAMES glib.h PATH_SUFFIXES glib-2.0)

        set (GLIB2_LIBRARIES "${GLIB2_LIBRARIES}" "${GLIB2_MODULE_LIBRARIES}")
endif(${UNIX})

if (${CMAKE_SYSTEM_NAME} STREQUAL Windows)
	if(MSVC)
		message(STATUS "Compiler: MSVC, version: " ${MSVC_VERSION})
	endif(MSVC)
	if(BORLAND) 
		message(STATUS "Compiler: BCC") 
	endif(BORLAND) 
	else(${CMAKE_SYSTEM_NAME} STREQUAL Linux) 
		message(STATUS "Only GCC is supported on Linux")
	endif(${CMAKE_SYSTEM_NAME} STREQUAL Windows) 

message(STATUS "CMake generates " ${CMAKE_GENERATOR})

