
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_ANDROID_STL_TYPE llvm-libc++_static)

project("libzim_wrapper")

add_library(
        libzim_wrapper

        SHARED
        common.cpp
        libzim/archive.cpp
        libzim/entry.cpp
        libzim/item.cpp
        libzim/blob.cpp
)

find_library(libzim
        zim
        PATHS
        ${BUILD_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libzim)
if (NOT libzim)
        message(FATAL_ERROR "libzim not found!")
endif()
add_library(libzim SHARED IMPORTED)

set_property(TARGET
        libzim
        PROPERTY
        IMPORTED_LOCATION
        ${BUILD_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libzim/libzim.so)

include_directories(
${CMAKE_SOURCE_DIR}
${BUILD_DIR}/include/libkiwix
${BUILD_DIR}/include/libzim
${BUILD_DIR}/include/javah_generated
#${CMAKE_SOURCE_DIR}/include/utils
)

find_library(
        log-lib
        log)

target_link_libraries(
        libzim_wrapper
        libzim

        ${log-lib}
        )

