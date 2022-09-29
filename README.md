# Java Libkiwix binding for Java/Kotlin

Android Library for accessing libkiwix and libzim in android with JAVA wrapper.

# Steps to build


## Step 1

### Download Java Libkiwix and install gradle dependencies


```bash
git clone https://github.com/kiwix/java-libkiwix.git
```

## Step 2

### Copy ``` LibKiwix``` header files in ```/include``` directory.

```bash
java-libkiwix/android-libkiwixbuild/app/src/main/cpp/include/libkiwix
```

### Copy ``` Libzim``` header files in ```/include``` directory.

```bash
java-libkiwix/android-libkiwixbuild/app/src/main/cpp/include/libzim
```
### Copy ``` icu``` header files in ```/include``` directory.

```bash
java-libkiwix/android-libkiwixbuild/app/src/main/cpp/include/icu
```

## Step 3

### Copy ``` .so``` files in ```/jniLibs``` directory for both ```libzim``` and ```libkiwix``` for each architecture. 

## Libzim

```bash
java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/{ANDROID_ABI}/libkiwix
```
## Libkiwix
```bash
java-libkiwix/android-libkiwixbuild/app/src/main/jniLibs/{ANDROID_ABI}/libzim
```

# Compilation

### Go to source directory and run bash command

```bash
./gradlew build
```

### AAR file will be generated on path :  

```bash
java-libkiwix/android-libkiwixbuild/app/build/outputs/aar
```
