cmake_minimum_required (VERSION 3.16)
project (MyLib)

# Adds the executable called "demo" that is built from the source files "main.cpp".
add_executable (MyLib ${CMAKE_SOURCE_DIR}/../../../../../main/cpp/kiwixreader.cpp)

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
)

target_link_libraries (MyLib 
LINK_PUBLIC 
/home/hp-pc03/Desktop/libkiwix.so
/home/hp-pc03/Desktop/libzim.so
/usr/lib/jvm/java-11-openjdk-amd64/lib/server/libjvm.so
)
