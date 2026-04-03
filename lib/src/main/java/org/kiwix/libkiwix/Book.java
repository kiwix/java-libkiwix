
package org.kiwix.libkiwix;

import org.kiwix.libzim.Archive;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class Book
{
  public Book() { allocate(); }
  public Book(long handle) {
    nativeHandle = handle;
  }


  public native void update(@NonNull Book book);
  public native void update(@NonNull Archive archive);


  @Override
  protected void finalize() { dispose();  }

  @NonNull public native String getId();
  @Nullable public native String getPath();
  @Nullable public native String getHumanReadableIdFromPath();
  public native boolean isPathValid();
  @Nullable public native String getTitle();
  @Nullable public native String getDescription();
  @Nullable public native String getLanguage();
  @Nullable public native String getCreator();
  @Nullable public native String getPublisher();
  @Nullable public native String getDate();
  @Nullable public native String getUrl();
  @Nullable public native String getName();
  @Nullable public native String getFlavour();
  @Nullable public native String getCategory();
  @Nullable public native String getTags();
  /**
   * Return the value associated to the tag tagName
   *
   * @param tagName the tag name to search for.
   * @return The value of the tag. If the tag is not found, return empty string.
   */
  @Nullable public native String getTagStr(@NonNull String tagName);

  public native long getArticleCount();
  public native long getMediaCount();
  public native long getSize();

  @NonNull public native Illustration[] getIllustrations();
  @Nullable public native Illustration getIllustration(int size);

  private native void allocate();
  private native void dispose();
  private long nativeHandle;
}
