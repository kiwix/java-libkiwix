# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("libkiwix")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        kiwix

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        filter.cpp
        kiwixicu.cpp
        kiwixreader.cpp
        kiwixsearcher.cpp
        library.cpp
        manager.cpp
        kiwixserver.cpp
        )

add_library(libkiwix SHARED IMPORTED)
set_target_properties(libkiwix PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../../main/jniLibs/${ANDROID_ABI}/libkiwix.so)
add_library(libzim SHARED IMPORTED)
set_target_properties(libzim PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/../../main/jniLibs/${ANDROID_ABI}/libzim.so)
target_include_directories(libkiwix
        INTERFACE /home/hp-pc/Documents/android-publisher/android-libkiwixbuild/app/src/main/cpp/include)
# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        kiwix
        libkiwix
        libzim
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

