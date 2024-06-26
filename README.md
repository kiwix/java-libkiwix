Libkiwix binding for Java/Kotlin
================================

Library for accessing [libkiwix](https://github.com/kiwix/libkiwix) and [libzim](https://github.com/openzim/libzim/) with Java or Kotlin on Android.

[![Maven Central](https://img.shields.io/maven-central/v/org.kiwix/libkiwix)](https://search.maven.org/artifact/org.kiwix/libkiwix)
[![Build Status](https://github.com/kiwix/java-libkiwix/workflows/CI/badge.svg?query=branch%3Amain)](https://github.com/kiwix/java-libkiwix/actions?query=workflow%3ACI+branch%3Amain)
[![Continuous Deployment](https://github.com/kiwix/java-libkiwix/workflows/CD/badge.svg?query=branch%3Amain)](https://github.com/kiwix/java-libkiwix/actions?query=workflow%3ACD+branch%3Amain)
[![CodeFactor](https://www.codefactor.io/repository/github/kiwix/java-libkiwix/badge)](https://www.codefactor.io/repository/github/kiwix/java-libkiwix)
[![Codecov](https://codecov.io/gh/kiwix/java-libkiwix/branch/main/graph/badge.svg)](https://codecov.io/gh/kiwix/java-libkiwix)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

# Build

The project requires `Java 17` to compile, Therefore set the `Gradle JDK` to `Java 17`.

## Install dependencies
```bash
./install_deps.sh
```

## Compile
```bash
./gradlew buildHeaders
./gradlew build
```

AAR file will be generated in directory `lib/build/outputs/aar`

### Use the library in your project

First, locate the compiled/generated `lib-debug.aar` in the
`lib/build/outputs/aar` directory. Then open your project's Gradle
configuration file and import the .aar file as a dependency.

If you are using Kotlin for your Gradle file, add the following code snippet:

```kotlin
dependencies {
    implementation(files("path-of-aar-file/lib-debug.aar"))
}
```

If you are using Groovy for your Gradle file, use this code snippet:

```kotlin
dependencies {
    implementation files("path-to-your-aar-file/lib-debug.aar")
}
```

### Load ZIM file

To load a ZIM file you need to create an `Archive` object.

```kotlin
val archive = Archive("your-file-path")
```

### Load ZIM main page

The `mainPage` property is used to retrieve the path of the main entry
page for a Kiwix content archive.  If the main entry is a redirect, it
will fetch the path of the redirected item; otherwise, it will return
the path of the main entry itself.  If the main entry is not found,
the archive will throw an `EntryNotFoundException`.

```kotlin
val mainPage: String?
    get() =
        try {
            archive.mainEntry.getItem(true).path
        } catch (entryNotFoundException: EntryNotFoundException) {
            // Return `null` if the main entry is not present in the archive.
            null
        } catch (exception: Exception) {
            // Other exception will thrown here e.g. the file is corrupted or any other error happened.
            null
        }
```

### Load a ZIM article via title

```kotlin
    try {
        // If the article with the specified title exists in the archive,
        // retrieve its path using the `getEntryByTitle` method.
        archive.getEntryByTitle(title).path
    } catch (entryNotFoundException: EntryNotFoundException) {
        // If the article with the specified title does not exist in the archive,
        // return `null`.
        null
    }
```

### Load a ZIM article via path

Ensure that the URL path is properly decode before passing it to `hasEntryByPath`,
as `Libzim` does not support encoded URLs.

```kotlin
    val decodedPath = URLDecoder.decode(actualpath, "UTF-8")
    try {
        // If the article with the specified URL exists in the archive,
        // retrieve its actual path using the `getEntryByPath` method.
        archive.getEntryByPath(decodedPath)
            .getItem(true)
            .path
    } catch (entryNotFoundException: EntryNotFoundException) {
        // If the article with the specified URL does not exist in the archive,
        // return `null`.
        null
    }
```

# License

[GPLv3](https://www.gnu.org/licenses/gpl-3.0) or later, see
[COPYING](COPYING) for more details.




