
package org.kiwix.test.libkiwix;

import org.kiwix.libkiwix.JNIICU;

public class TestJNIICU {
  static public void setDataDirectory(String directory) {
    JNIICU.setDataDirectory(directory);
  }
}
