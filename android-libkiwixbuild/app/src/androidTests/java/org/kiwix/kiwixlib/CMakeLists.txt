cmake_minimum_required (VERSION 3.16)
project (buildkiwix)

# Adds the executable called "demo" that is built from the source files "main.cpp".
add_library(buildkiwix
SHARED 
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/base64.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/book.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/filter.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/kiwixicu.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/kiwixreader.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/kiwixsearcher.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/kiwixserver.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/library.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/manager.cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/utils.h
)

find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

include_directories(
/usr/lib/jvm/java-11-openjdk-amd64/include
/usr/lib/jvm/java-11-openjdk-amd64/include/linux
${CMAKE_SOURCE_DIR}/../../../../../main/cpp
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/include/libkiwix
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/include/libzim
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/include/javah_generated
${CMAKE_SOURCE_DIR}/../../../../../main/cpp/include/utils
)

target_link_libraries(buildkiwix
LINK_PUBLIC 
/home/hp-pc03/Desktop/libkiwix.so
${CMAKE_SOURCE_DIR}/../../../../../../build/libzim.so
)
