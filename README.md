[![Maven Central](https://img.shields.io/maven-central/v/org.kiwix.kiwixlib/kiwixlib)](https://search.maven.org/artifact/org.kiwix.kiwixlib/kiwixlib)
[![CodeFactor](https://www.codefactor.io/repository/github/kiwix/java-libkiwix/badge)](https://www.codefactor.io/repository/github/kiwix/java-libkiwix)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

# Java Libkiwix binding for Java/Kotlin

Android Library for accessing libkiwix and libzim in android with JAVA wrapper.

# Steps to build

## Clone java-libkiwix

```bash
git clone https://github.com/kiwix/java-libkiwix.git
cd java-libkiwix
```

## Install dependencies

```bash
./install_deps.sh
```

## Compile


```bash
./gradlew generateHeader
./gradlew build
```

AAR file will be generated in directory `lib/build/outputs/aar`




