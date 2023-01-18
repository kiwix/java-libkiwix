
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_ANDROID_STL_TYPE llvm-libc++_static)

project("libkiwix_wrapper")

add_library(
        zim_wrapper

        SHARED
        common.cpp
        libzim/archive.cpp
        libzim/entry.cpp
        libzim/entry_iterator.cpp
        libzim/item.cpp
        libzim/blob.cpp
        libzim/searcher.cpp
        libzim/query.cpp
        libzim/search.cpp
        libzim/search_iterator.cpp
        libzim/suggestion_searcher.cpp
        libzim/suggestion_search.cpp
        libzim/suggestion_iterator.cpp
        libzim/suggestion_item.cpp
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


add_library(
        kiwix_wrapper

        SHARED
        libkiwix/book.cpp
        libkiwix/filter.cpp
        libkiwix/kiwixicu.cpp
        libkiwix/kiwixserver.cpp
        libkiwix/library.cpp
        libkiwix/manager.cpp
        libkiwix/illustration.cpp
)

find_library(libkiwix
        kiwix
        PATHS
        ${BUILD_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libkiwix)
if (NOT libkiwix)
        message(FATAL_ERROR "libkiwix not found!")
endif()
add_library(libkiwix SHARED IMPORTED)

set_property(TARGET
        libkiwix
        PROPERTY
        IMPORTED_LOCATION
        ${BUILD_DIR}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libkiwix/libkiwix.so)

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
        zim_wrapper
        libzim
        ${log-lib}
)

target_link_libraries(
        kiwix_wrapper
        libkiwix
        libzim
        ${log-lib}
        )

