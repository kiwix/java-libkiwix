
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_ANDROID_STL_TYPE llvm-libc++_static)


project("buildkiwix")

add_library(
        buildkiwix

        SHARED

        filter.cpp
        kiwixreader.cpp
        kiwixsearcher.cpp
        library.cpp
        manager.cpp
        kiwixserver.cpp
        kiwixicu.cpp
)

find_library(libkiwix
        kiwix
        PATHS
        ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libkiwix)
if (NOT libkiwix)
        message(FATAL_ERROR "kiwix not found! -->  ${CMAKE_SOURCE_DIR} ")
endif()

find_library(libzim
        zim
        PATHS
        ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libzim)
if (NOT libzim)
        message(FATAL_ERROR "libzim not found!")
endif()
add_library(libkiwix SHARED IMPORTED)

set_property(TARGET libkiwix
        PROPERTY
        IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libkiwix/libkiwix.so)
add_library(libzim SHARED IMPORTED)

set_property(TARGET
        libzim
        PROPERTY
        IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libzim/libzim.so)

include_directories(
${CMAKE_SOURCE_DIR}
${CMAKE_SOURCE_DIR}/include/libkiwix
${CMAKE_SOURCE_DIR}/include/libzim
${CMAKE_SOURCE_DIR}/include/javah_generated
${CMAKE_SOURCE_DIR}/include/utils
)

find_library(
        log-lib
        log)

target_link_libraries(
        buildkiwix
        libkiwix
        libzim

        ${log-lib}
        )

