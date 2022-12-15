#!/bin/bash

Green='\e[32m'
NC='\033[0m' # No Color

cd android-libkiwixbuild/

printf "${Green}Check Current Java version${NC}\n"
./gradlew checkCurrentJavaVersion
printf  "\n${Green}Done! ${NC}\n"

printf "${Green}Downloading libzim ${NC}\n"
./gradlew downloadLibzimSoAndHeaderFiles unzipLibzim
printf  "\n${Green}Done! ${NC}\n"

hash -r

printf "${Green}Coping libzim header and so files ${NC}\n"
./gradlew checkCurrentLibzimDate copyLibzimHeaderFiles copyLibzimAndroidArm copyLibzimAndroidArm64 copyLibzimAndroidx86 copyLibzimAndroidx86_64 copyLibzimLinux_x86_64 renameLibzimSoFile
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libkiwix ${NC}\n"
./gradlew downloadLibkiwixSoAndHeaderFiles unzipLibkiwix
printf  "\n${Green}Done! ${NC}\n"

hash -r

printf "${Green}Coping libkiwix header and so files ${NC}\n"
./gradlew checkCurrentLibkiwixDate copyLibkiwixHeaderFiles copyLibkiwixAndroidArm copyLibkiwixAndroidArm64 copyLibkiwixAndroidx86 copyLibkiwixAndroidx86_64 copyLibkiwixLinux_x86_64 renameLibkiwixSoFile
printf  "\n${Green}Done! ${NC}\n"

printf "${Green}Generating header files from java wrapper files ${NC}\n"
./gradlew generateHeaderFilesFromJavaWrapper
printf  "\n${Green}Done! ${NC}\n"

hash -r