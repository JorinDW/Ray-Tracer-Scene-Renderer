# Build configuration file for "Intro to Graphics"
#
#--- To understand its content:
#   http://www.cmake.org/cmake/help/syntax.html
#   http://www.cmake.org/Wiki/CMake_Useful_Variables
#

#--- This is how you show a status message in the build system
message(STATUS "Intro to Graphics - Loading Common Configuration")

#--- Tell CMake he'll be able to include ".cmake" configurations
# files in the folder where the current file is located
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

#--- Common headers/libraries for all the exercises
include_directories(${CMAKE_CURRENT_LIST_DIR})

#--- Make headers in common directory visible in the IDE
file(GLOB_RECURSE COMMON_DIR_HEADERS "${CMAKE_CURRENT_LIST_DIR}/*.h")
add_custom_target(common_headers SOURCES ${COMMON_DIR_HEADERS})

#--- Configures compiler for C++11
set(FOUND FALSE)
if(NOT FOUND AND UNIX AND EXISTS "/usr/local/bin/g++-5")
    message(STATUS "Using g++5 from homebrew.")
    set(CMAKE_CC_COMPILER "/usr/local/bin/gcc-5")
    set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-5")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    # eigen has few warnings in the with newest g++5
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
    set(FOUND TRUE)
endif()
if(NOT FOUND AND UNIX AND EXISTS "/usr/bin/icc")
    message(STATUS "Using ICC Intel Compiler.")
    set(CMAKE_CC_COMPILER "/usr/bin/icc")
    set(CMAKE_CXX_COMPILER "/usr/bin/icc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(FOUND TRUE)
endif()
if(NOT FOUND AND UNIX AND NOT APPLE)
    message(STATUS "Using default UNIX compiler.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(FOUND TRUE)
endif()
if(NOT FOUND AND UNIX AND APPLE)
    # Clang in OSX supports partially c++11 through extensions, but some code might not run
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++11-extensions")
    set(FOUND TRUE)
endif()
if(NOT FOUND AND WIN32)
    # MSVC12 supports c++11 natively
    set(FOUND TRUE)
endif()


