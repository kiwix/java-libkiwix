#!/bin/bash

Green='\e[32m'
NC='\033[0m' # No Color

ls

cd android-libkiwixbuild/

./gradlew build