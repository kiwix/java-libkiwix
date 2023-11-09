
package org.kiwix.libkiwix;

public class Illustration
{
  public native int width();
  public native int height();
  public native String mimeType();
  public native String url();

  public native byte[] getData();
  @Override
  protected void finalize() { dispose();  }

  private native void dispose();
  private long nativeHandle;
}
