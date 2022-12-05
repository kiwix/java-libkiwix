#!/bin/bash

Green='\e[32m'
NC='\033[0m' # No Color

cd android-libkiwixbuild/

printf "${Green}Check latest libzim version${NC}\n"
./gradlew checkLatestNightlyForLibzim checkLatestLibzimVersion
printf  "\n${Green}Done! ${NC}\n"

printf "${Green}Check latest libkiwix version${NC}\n"
./gradlew checkLatestNightlyForLibkiwix checkLatestLibkiwixVersion
printf  "\n${Green}Done! ${NC}\n"

printf "${Green}Downloading libzim ${NC}\n"
./gradlew downloadLibzimSoAndHeaderFiles unzipLibzim
printf  "\n${Green}Done! ${NC}\n"

hash -r

printf "${Green}Coping libzim header and so files ${NC}\n"
./gradlew copyLibzimHeaderFiles copyLibzimAndroidArm copyLibzimAndroidArm64 copyLibzimAndroidx86 copyLibzimAndroidx86_64 copyLibzimLinux_x86_64 renameLibzimSoFile
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libkiwix ${NC}\n"
./gradlew downloadLibkiwixSoAndHeaderFiles unzipLibkiwix
printf  "\n${Green}Done! ${NC}\n"

hash -r

printf "${Green}Coping libkiwix header and so files ${NC}\n"
./gradlew copyLibkiwixHeaderFiles copyLibkiwixAndroidArm copyLibkiwixAndroidArm64 copyLibkiwixAndroidx86 copyLibkiwixAndroidx86_64 copyLibkiwixLinux_x86_64 renameLibkiwixSoFile
printf  "\n${Green}Done! ${NC}\n"

cd app/src/main/java/org/kiwix/

printf "${Green}Generating header files from java wrapper files ${NC}\n"
javac -h ../../../cpp/include/javah_generated/ -d target kiwixlib/Book.java kiwixlib/DirectAccessInfo.java kiwixlib/Filter.java kiwixlib/JNIICU.java kiwixlib/JNIKiwixBool.java kiwixlib/JNIKiwixException.java kiwixlib/JNIKiwixInt.java kiwixlib/JNIKiwixReader.java kiwixlib/JNIKiwixSearcher.java kiwixlib/JNIKiwixServer.java kiwixlib/JNIKiwixString.java kiwixlib/Library.java kiwixlib/Manager.java
printf  "\n${Green}Done! ${NC}\n"

hash -r

cd ../../../../../../

printf "${Green}Copy generated java wrapper class files to testing folder${NC}\n"
./gradlew copyJavaGeneratedClassFileToTestingFolder
printf  "\n${Green}Done! ${NC}\n"