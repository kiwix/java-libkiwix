cmake_minimum_required (VERSION 3.16)
project (buildkiwix)

add_library(buildkiwix
SHARED
${PROJECT_SOURCE_DIR}/../main/cpp/libkiwix/book.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libkiwix/bookmark.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libkiwix/filter.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libkiwix/illustration.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libkiwix/kiwixicu.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libkiwix/kiwixserver.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libkiwix/library.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libkiwix/manager.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/archive.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/blob.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/entry.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/entry_iterator.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/item.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/query.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/search.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/search_iterator.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/searcher.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/suggestion_item.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/suggestion_iterator.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/suggestion_search.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/libzim/suggestion_searcher.cpp
${PROJECT_SOURCE_DIR}/../main/cpp/utils.h
)

find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")
endif()

include_directories(
/opt/hostedtoolcache/jdk/11.0.18/x64/include
/opt/hostedtoolcache/jdk/11.0.18/x64/include/linux
${PROJECT_SOURCE_DIR}/../main/cpp
${PROJECT_SOURCE_DIR}/../../build/include/libkiwix
${PROJECT_SOURCE_DIR}/../../build/include/libzim
${PROJECT_SOURCE_DIR}/../../build/include/javah_generated
)

target_link_libraries(buildkiwix
LINK_PUBLIC
${PROJECT_SOURCE_DIR}/../../build/libkiwix.so
${PROJECT_SOURCE_DIR}/../../build/libzim.so
)
