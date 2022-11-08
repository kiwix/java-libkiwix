#!/bin/bash

Green='\e[32m'
NC='\033[0m' # No Color

printf "${Green}Downloading libzim for android_arm ${NC}"
wget https://download.openzim.org/nightly/2022-11-08/libzim_android-arm-2022-11-08.tar.gz
tar -xf libzim_android-arm-2022-11-08.tar.gz
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libzim for android_arm64 ${NC}"
wget https://download.openzim.org/nightly/2022-11-08/libzim_android-arm64-2022-11-08.tar.gz
tar -xf libzim_android-arm64-2022-11-08.tar.gz
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libzim for android_x86 ${NC}"
wget https://download.openzim.org/nightly/2022-11-08/libzim_android-x86-2022-11-08.tar.gz
tar -xf libzim_android-x86-2022-11-08.tar.gz
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libzim for android_x86_64 ${NC}"
wget https://download.openzim.org/nightly/2022-11-08/libzim_android-x86_64-2022-11-08.tar.gz
tar -xf libzim_android-x86_64-2022-11-08.tar.gz
printf  "\n${Green}Down! ${NC}\n"

printf  "${Green}Coping libzim required header and so files! ${NC}\n"

printf  "\n ${Green}Libzim header files! ${NC}\n"
cp -r libzim_android-arm-2022-11-08/include/* android-libkiwixbuild/app/src/main/cpp/include/libzim
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Coping libzim android_arm so file! ${NC}\n"
cp -r libzim_android-arm-2022-11-08/lib/arm-linux-androideabi/libzim.so android-libkiwixbuild/app/src/main/jniLibs/armeabi-v7a/libzim
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Coping libzim android_arm64 so file! ${NC}\n"
cp -r libzim_android-arm64-2022-11-08/lib/aarch64-linux-android/libzim.so android-libkiwixbuild/app/src/main/jniLibs/arm64-v8a/libzim
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Coping libzim android_x86 so file! ${NC}\n"
cp -r libzim_android-x86-2022-11-08/lib/i686-linux-android/libzim.so android-libkiwixbuild/app/src/main/jniLibs/x86/libzim
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Coping libzim android_x86_64 so file! ${NC}\n"
cp -r libzim_android-x86_64-2022-11-08/lib/x86_64-linux-android/libzim.so android-libkiwixbuild/app/src/main/jniLibs/x86_64/libzim
printf  "\n${Green}Done! ${NC}\n"

printf "${Green}Downloading libkiwix for android_arm ${NC}"
wget https://download.kiwix.org/nightly/2022-11-08/libkiwix_android-arm-2022-11-08.tar.gz
tar -xf libkiwix_android-arm-2022-11-08.tar.gz
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libkiwix for android_arm64 ${NC}"
wget https://download.kiwix.org/nightly/2022-11-08/libkiwix_android-arm64-2022-11-08.tar.gz
tar -xf libkiwix_android-arm64-2022-11-08.tar.gz
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libkiwix for android_x86 ${NC}"
wget https://download.kiwix.org/nightly/2022-11-08/libkiwix_android-x86-2022-11-08.tar.gz
tar -xf libkiwix_android-x86-2022-11-08.tar.gz
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libkiwix for android_x86_64 ${NC}"
wget https://download.kiwix.org/nightly/2022-11-08/libkiwix_android-x86_64-2022-11-08.tar.gz
tar -xf libkiwix_android-x86_64-2022-11-08.tar.gz
printf  "\n${Green}Down! ${NC}\n"

printf  "${Green}Coping libkiwix required header and so files! ${NC}\n"

printf  "\n ${Green}Copying libkiwix header files! ${NC}\n"
cp -r libkiwix_android-arm-2022-11-08/include/kiwix/* android-libkiwixbuild/app/src/main/cpp/include/libkiwix
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Coping libkiwix android_arm so file! ${NC}\n"
cp -r libkiwix_android-arm-2022-11-08/lib/arm-linux-androideabi/libkiwix.so android-libkiwixbuild/app/src/main/jniLibs/armeabi-v7a/libkiwix
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Coping libkiwix android_arm64 so file! ${NC}\n"
cp -r libkiwix_android-arm64-2022-11-08/lib/aarch64-linux-android/libkiwix.so android-libkiwixbuild/app/src/main/jniLibs/arm64-v8a/libkiwix
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Coping libkiwix android_x86 so file! ${NC}\n"
cp -r libkiwix_android-x86-2022-11-08/lib/i686-linux-android/libkiwix.so android-libkiwixbuild/app/src/main/jniLibs/x86/libkiwix
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Coping libkiwix android_x86_64 so file! ${NC}\n"
cp -r libkiwix_android-x86_64-2022-11-08/lib/x86_64-linux-android/libkiwix.so android-libkiwixbuild/app/src/main/jniLibs/x86_64/libkiwix
printf  "\n${Green}Done! ${NC}\n"

printf  "\n ${Green}Generate java header files! ${NC}\n"


cd android-libkiwixbuild

./gradlew build

