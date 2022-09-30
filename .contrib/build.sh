#!/bin/bash

Green='\e[32m'
NC='\033[0m' 

printf "${Green}Building lib Kiwix ${NC}"
printf  "\n${Green}Setting up Pyton enviourment!${NC}\n"

mkdir kiwix-setup
cd kiwix-setup
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
git clone https://github.com/kiwix/java-libkiwix.git
printf  "\n${Green}Done! ${NC}\n"