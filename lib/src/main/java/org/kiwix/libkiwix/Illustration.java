
package org.kiwix.libkiwix;
import org.kiwix.Wrapper;

public class Illustration extends Wrapper
{
  public native int width();
  public native int height();
  public native String mimeType();
  public native String url();

  public native String getData();


  private Illustration(Wrapper.Resource res) { super(res); }
}
