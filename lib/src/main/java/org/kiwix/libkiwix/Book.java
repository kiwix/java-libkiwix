
package org.kiwix.libkiwix;

import org.kiwix.libzim.Archive;
import org.kiwix.libkiwix.Illustration;

public class Book
{
  public Book() { allocate(); }


  public native void update(Book book);
  public native void update(Archive archive);

  @Override
  protected void finalize() { dispose();  }

  public native String getId();
  public native String getPath();
  public native boolean isPathValid();
  public native String getTitle();
  public native String getDescription();
  public native String getLanguage();
  public native String getCreator();
  public native String getPublisher();
  public native String getDate();
  public native String getUrl();
  public native String getName();
  public native String getFlavour();
  public native String getCategory();
  public native String getTags();
  /**
   * Return the value associated to the tag tagName
   *
   * @param tagName the tag name to search for.
   * @return The value of the tag. If the tag is not found, return empty string.
   */
  public native String getTagStr(String tagName);

  public native long getArticleCount();
  public native long getMediaCount();
  public native long getSize();

  public native Illustration[] getIllustrations();
  public native Illustration getIllustration(int size);

  private native void allocate();
  private native void dispose();
  private long nativeHandle;
}
