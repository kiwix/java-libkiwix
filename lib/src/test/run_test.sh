#!/usr/bin/bash

# This script runs the unit test to test the java wrapper.
# This is not integrated in meson because ... this is not so easy.

die()
{
  echo >&2 "!!! ERROR: $*"
  exit 1
}

KIWIX_LIB_JAR=$(readlink -f "$1")
KIWIX_LIB_DIR=$(readlink -f "$2")
TEST_SOURCE_DIR=$(dirname "$(readlink -f $0)")

cd "$TEST_SOURCE_DIR"

javac -g -d . -s . -cp "junit-4.13.jar:$KIWIX_LIB_JAR" test.java \
  || die "Compilation failed"

java -Djava.library.path="$KIWIX_LIB_DIR" \
     -javaagent:jacoco-0.8.7/lib/jacocoagent.jar -cp "junit-4.13.jar:hamcrest-core-1.3.jar:$KIWIX_LIB_JAR:." \
     org.junit.runner.JUnitCore test \
  || die "Unit test failed"

java -jar jacoco-0.8.7/lib/jacococli.jar report jacoco.exec \
--classfiles org/kiwix/libkiwix/ \
--classfiles org/kiwix/libzim/ \
--html ../../build/coverage-report --xml coverage.xml