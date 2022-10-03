#!/bin/bash

Green='\e[32m'
NC='\033[0m' # No Color

printf "${Green}Building lib Kiwix ${NC}"
printf  "\n${Green}Setting up Pyton enviourment!${NC}\n"
mkdir new-kiwix-setup
cd new-kiwix-setup
apt-get install python3-pip virtualenv
virtualenv -p python3 ./
source bin/activate

printf  "${Green}Downloading kiwix-build repo!${NC}\n"
git clone https://github.com/kiwix/kiwix-build.git
printf  "${Green}Done! \n${NC}"

cd kiwix-build
printf  "${Green}Installing python dependencies!${NC}\n"
pip3 install .
printf  hash -r
printf  "\n${Green}Done! \n${NC}"

printf  "${Green}Compiling libzim and libkiwix!${NC}\n"
kiwix-build libkiwix --target-platform android
printf  "${Green}Done! \n${NC}"

cd ..

printf  "${Green}Downloading Java Lib kiwix Repo!${NC}\n"
git clone https://github.com/kiwix/java-libkiwix.git -b 11.0.0
printf  "\n${Green}Done! ${NC}\n"


printf  "${Green}Coping requied header files! ${NC}\n"


printf  "\n ${Green}Libzim header files! ${NC}\n"
cp -r kiwix-build/SOURCE/libzim/include java-libkiwix/android-libkiwixbuild/app/src/main/cpp/include/libzim
printf  "\n${Green}Done! ${NC}\n"


printf  "\n ${Green}ICU header files! ${NC}\n"
cp -r kiwix-build/SOURCE/icu4c-58.2/source/i18n java-libkiwix/android-libkiwixbuild/app/src/main/cpp/include/icu
printf  "\n${Green}Done! ${NC}\n"


printf  "\n ${Green}Libkiwix header files! ${NC}\n"
cp -r kiwix-build/SOURCE/libkiwix/include java-libkiwix/android-libkiwixbuild/app/src/main/cpp/include/libkiwix
printf  "\n${Green}Done! ${NC}\n"



printf  "${Green}Coping binary files! ${NC}\n"

printf  "\n ${Green}Libzim shared library! ${NC}\n"

printf  "\n${Green} [ANDROID_ARM] ${NC}\n"
cp -r kiwix-build/BUILD_android_arm/libzim/src/libzim.so java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/armeabi-v7a/libzim
printf  "\n${Green}Done! ${NC}\n"


printf  "\n${Green} [ANDROID_ARM_64] ${NC}\n"
cp -r kiwix-build/BUILD_android_arm64/libzim/src/libzim.so java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/arm64-v8a/libzim
printf  "\n${Green}Done! ${NC}\n"


printf  "\n${Green} [ANDROID_x86] ${NC}\n"
cp -r kiwix-build/BUILD_android_x86/libzim/src/libzim.so java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/x86/libzim
printf  "\n${Green}Done! ${NC}\n"


printf  "\n${Green} [ANDROID_x86_64] ${NC}\n"
cp -r kiwix-build/BUILD_android_x86_64/libzim/src/libzim.so java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/x86_64/libzim

printf  "\n${Green}Done! ${NC}\n"


printf  "\n ${Green}Libkiwix shared library! ${NC}\n"

printf  "\n${Green} [ANDROID_ARM] ${NC}\n"
cp -r kiwix-build/BUILD_android_arm/libkiwix/src/libkiwix.so java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/armeabi-v7a/libkiwix
printf  "\n${Green}Done! ${NC}\n"


printf  "\n${Green} [ANDROID_ARM_64] ${NC}\n"
cp -r kiwix-build/BUILD_android_arm64/libkiwix/src/libkiwix.so java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/arm64-v8a/libkiwix
printf  "\n${Green}Done! ${NC}\n"


printf  "\n${Green} [ANDROID_x86] ${NC}\n"
cp -r kiwix-build/BUILD_android_x86/libkiwix/src/libkiwix.so java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/x86/libkiwix
printf  "\n${Green}Done! ${NC}\n"


printf  "\n${Green} [ANDROID_x86_64] ${NC}\n"
cp -r kiwix-build/BUILD_android_x86_64/libkiwix/src/libkiwix.so java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/x86_64/libkiwix
printf  "\n${Green}Done! ${NC}\n"


cd java-libkiwix/android-libkiwixbuild



