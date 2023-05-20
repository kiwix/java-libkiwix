
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
cmake_minimum_required(VERSION 3.18.1)

project("libkiwix_wrapper")

set(BUILD_DIR_PATH "${BUILD_DIR}")

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(BUILD_DIR_PATH "./../../../build")
endif ()

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${BUILD_DIR_PATH}/include/libkiwix
        ${BUILD_DIR_PATH}/include/libzim
        ${BUILD_DIR_PATH}/include/javah_generated
        #${CMAKE_SOURCE_DIR}/include/utils
)

add_library(zim_wrapper

        SHARED
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


add_library(kiwix_wrapper

        SHARED
        libkiwix/book.cpp
        libkiwix/filter.cpp
        libkiwix/kiwixicu.cpp
        libkiwix/kiwixserver.cpp
        libkiwix/library.cpp
        libkiwix/bookmark.cpp
        libkiwix/manager.cpp
        libkiwix/illustration.cpp
        )

# Linux target
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")

        find_package(JNI)

        include_directories(
                ${JNI_INCLUDE_DIRS}
        )

        add_library(libzim SHARED IMPORTED)
        set_target_properties(libzim PROPERTIES IMPORTED_LOCATION libzim.so)

        add_library(libkiwix SHARED IMPORTED)
        set_target_properties(libkiwix PROPERTIES IMPORTED_LOCATION libkiwix.so)

        target_link_libraries(
                zim_wrapper
                libzim
        )

        target_link_libraries(
                kiwix_wrapper
                libkiwix
                libzim
        )
endif ()

# Android target
if (ANDROID)
        set(CMAKE_ANDROID_STL_TYPE llvm-libc++_static)

        find_library(
                log-lib
                log)

        find_library(libzim
                zim
                PATHS
                ${BUILD_DIR_PATH}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libzim)
        if (NOT libzim)
                message(FATAL_ERROR "libzim not found!")
        endif ()
        add_library(libzim SHARED IMPORTED)

        set_property(TARGET
                libzim
                PROPERTY
                IMPORTED_LOCATION
                ${BUILD_DIR_PATH}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libzim/libzim.so)


        find_library(libkiwix
                kiwix
                PATHS
                ${BUILD_DIR_PATH}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libkiwix)
        if (NOT libkiwix)
                message(FATAL_ERROR "libkiwix not found!")
        endif ()
        add_library(libkiwix SHARED IMPORTED)

        set_property(TARGET
                libkiwix
                PROPERTY
                IMPORTED_LOCATION
                ${BUILD_DIR_PATH}/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/libkiwix/libkiwix.so)

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
endif ()