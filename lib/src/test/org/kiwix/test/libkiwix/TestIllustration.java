
package org.kiwix.test.libkiwix;

import org.kiwix.libkiwix.Illustration;

public class TestIllustration
{
  private Illustration inner;
  public TestIllustration(Illustration _inner) { inner = _inner; }

  public int width() { return inner.width(); }
  public int height() { return inner.height(); }
  public String mimeType() { return inner.mimeType(); }
  public String url() { return inner.url(); }
  public byte[] getData() { return inner.getData(); }
}
