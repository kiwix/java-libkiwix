#!/bin/bash


set -e

Green='\e[32m'
NC='\033[0m' # No Color

printf "${Green}Check Current Java version${NC}\n"
./gradlew checkCurrentJavaVersion
printf  "\n${Green}Done! ${NC}\n"

printf "${Green}Downloading libzim ${NC}\n"
./gradlew downloadLibzimSoAndHeaderFiles unzipLibzim
printf  "\n${Green}Done! ${NC}\n"

printf "${Green}Coping libzim header and so files ${NC}\n"
./gradlew renameLibzimFolders copyLibzimHeaderAndSoFiles renameLibzimSoFile
printf  "\n${Green}Down! ${NC}\n"

printf "${Green}Downloading libkiwix ${NC}\n"
./gradlew downloadLibkiwixSoAndHeaderFiles unzipLibkiwix
printf  "\n${Green}Done! ${NC}\n"

printf "${Green}Coping libkiwix header and so files ${NC}\n"
./gradlew renameLibkiwixFolders copyLibkiwixHeaderAndSoFiles renameLibkiwixSoFile
printf  "\n${Green}Done! ${NC}\n"
