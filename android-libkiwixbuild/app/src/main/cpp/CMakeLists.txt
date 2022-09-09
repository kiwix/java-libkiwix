# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_ANDROID_STL_TYPE llvm-libc++_static)
# Declares and names the project.

project("buildkiwix")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library(
        # Sets the name of the library.
        buildkiwix
        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        filter.cpp
        kiwixreader.cpp
        kiwixsearcher.cpp
        library.cpp
        manager.cpp
        kiwixserver.cpp
        )
#[[add_library(kiwix SHARED IMPORTED)

set_property(TARGET kiwix PROPERTY IMPORTED_LOCATION /home/hp-pc/Documents/android-publisher/android-libkiwixbuild/app/src/main/jniLibs/${ANDROID_ABI}/libkiwix.so)
add_library(zim SHARED IMPORTED)

set_property(TARGET zim PROPERTY IMPORTED_LOCATION /home/hp-pc/Documents/android-publisher/android-libkiwixbuild/app/src/main/jniLibs/${ANDROID_ABI}/libzim.so)]]
#
find_library(libkiwix
        kiwix # Lib's full name in this case - libfoo.so
        PATHS /home/hp-pc/Documents/android-publisher/android-libkiwixbuild/app/src/main/jniLibs/${ANDROID_ABI})
if (NOT libkiwix)
        message(FATAL_ERROR "kiwix not found!")
endif()

find_library(libzim
        zim # Lib's full name in this case - libfoo.so
        PATHS /home/hp-pc/Documents/android-publisher/android-libkiwixbuild/app/src/main/jniLibs/${ANDROID_ABI})
if (NOT libzim)
        message(FATAL_ERROR "libzim not found!")
endif()
add_library(libkiwix SHARED IMPORTED)

set_property(TARGET libkiwix PROPERTY IMPORTED_LOCATION /home/hp-pc/Documents/android-publisher/android-libkiwixbuild/app/src/main/jniLibs/${ANDROID_ABI}/libkiwix.so)
add_library(libzim SHARED IMPORTED)

set_property(TARGET libzim PROPERTY IMPORTED_LOCATION /home/hp-pc/Documents/android-publisher/android-libkiwixbuild/app/src/main/jniLibs/${ANDROID_ABI}/libzim.so)
include_directories(/home/hp-pc/Documents/android-publisher/android-libkiwixbuild/app/src/main/cpp/include)
include_directories(/home/hp-pc/Desktop/c_test/icu-main/icu4c/source/common/unicode)
target_link_libraries( # Specifies the target library.
        buildkiwix
        libkiwix
        libzim
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        )



# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.





